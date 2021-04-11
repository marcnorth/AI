#include "Matrix.h"
#include <stdexcept>

Matrix::Matrix(int numberOfRows, int numberOfColumns) {
	this->numberOfRows = numberOfRows;
	this->numberOfColumns = numberOfColumns;
	this->entries = new double[numberOfRows * numberOfColumns]();
}

Matrix::Matrix(const Matrix &other) : Matrix(other.getNumberOfRows(), other.getNumberOfColumns()) {
	memcpy(this->entries, other.entries, sizeof(double) * numberOfRows * numberOfColumns);
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> values) : Matrix(values.size(), values.begin()->size()) {
	for (const std::initializer_list<double>* rowValues = values.begin(); rowValues < values.end(); rowValues++) {
		int row = rowValues - values.begin();
		if (rowValues->size() != numberOfColumns) {
			throw std::invalid_argument("Row size does not match number of columns");
		}
		for (const double* it = rowValues->begin(); it < rowValues->end(); it++) {
			this->entries[row * numberOfColumns + it - rowValues->begin()] = *it;
		}
	}
}

Matrix::~Matrix() {
	delete[] entries;
}

Matrix Matrix::operator=(Matrix rhs) {
	if (!hasSameShapeAs(rhs)) {
		throw std::invalid_argument("Matricies do not have the same shape");
	}
	memcpy(this->entries, rhs.entries, sizeof(double) * numberOfRows * numberOfColumns);
	return *this;
}

int Matrix::getNumberOfRows() const {
	return numberOfRows;
}

int Matrix::getNumberOfColumns() const {
	return numberOfColumns;
}

void Matrix::setEntry(int row, int column, double value) {
	int index = row * numberOfColumns + column;
	if (index < 0 || index >= numberOfRows * numberOfColumns) {
		throw std::out_of_range("Entry is out of range");
	}
	this->entries[index] = value;
}

double Matrix::getEntry(int row, int column) const {
	int index = row * numberOfColumns + column;
	if (index < 0 || index >= numberOfRows * numberOfColumns) {
		throw std::out_of_range("Entry is out of range");
	}
	return this->entries[index];
}

bool Matrix::equalsWithPrecision(const Matrix &other, const double precision) const {
	if (!hasSameShapeAs(other)) {
		throw std::invalid_argument("Matricies do not have the same shape");
	}
	for (int row = 0; row < numberOfRows; row++) {
		for (int col = 0; col < numberOfColumns; col++) {
			if (abs(getEntry(row, col) - other.getEntry(row, col)) >= precision) {
				return false;
			}
		}
	}
	return true;
}

bool Matrix::hasSameShapeAs(const Matrix &other) const {
	return numberOfColumns == other.getNumberOfColumns() && numberOfRows == other.getNumberOfRows();
}

Matrix Matrix::transpose() const {
	Matrix t(numberOfColumns, numberOfRows);
	for (int i = 0; i < numberOfRows; i++) {
		for (int j = 0; j < numberOfColumns; j++) {
			t.setEntry(j, i, getEntry(i, j));
		}
	}
	return t;
}

Matrix Matrix::operator+(const Matrix &other) const {
	return add(other);
}

Matrix Matrix::add(const Matrix &other) const {
	if (!hasSameShapeAs(other)) {
		throw std::invalid_argument("Matricies do not have the same shape");
	}
	Matrix result = Matrix(numberOfRows, numberOfColumns);
	for (int row = 0; row < numberOfRows; row++) {
		for (int col = 0; col < numberOfColumns; col++) {
			result.setEntry(row, col, getEntry(row, col) + other.getEntry(row, col));
		}
	}
	return result;
}

Matrix Matrix::operator*(const Matrix &other) const {
	return multiply(other);
}

Matrix Matrix::multiply(const Matrix &other) const {
	if (numberOfColumns != other.getNumberOfRows()) {
		throw std::invalid_argument("Matricies do not have the correct shape");
	}
	Matrix result = Matrix(numberOfRows, other.getNumberOfColumns());
	for (int row = 0; row < result.getNumberOfRows(); row++) {
		for (int col = 0; col < result.getNumberOfColumns(); col++) {
			double value = 0;
			for (int i = 0; i < numberOfColumns; i++) {
				value += getEntry(row, i) * other.getEntry(i, col);
			}
			result.setEntry(row, col, value);
		}
	}
	return result;
}

Vector Matrix::operator*(const Vector& vector) const {
	return multiply(vector);
}

Vector Matrix::multiply(const Vector& vector) const {
	if (vector.getSize() != numberOfColumns) {
		throw std::invalid_argument("Matrix columns does not match vector size");
	}
	Vector result(numberOfRows);
	for (int row = 0; row < numberOfRows; row++) {
		double value = 0.0;
		for (int col = 0; col < numberOfColumns; col++) {
			value += vector.getEntry(col) * getEntry(row, col);
		}
		result.setEntry(row, value);
	}
	return result;
}

Matrix Matrix::operator*(double multiplier) const {
	return multiply(multiplier);
}

Matrix Matrix::multiply(double multiplier) const {
	Matrix result(numberOfRows, numberOfColumns);
	for (int row = 0; row < numberOfRows; row++) {
		for (int col = 0; col < numberOfColumns; col++) {
			result.setEntry(row, col, getEntry(row, col) * multiplier);
		}
	}
	return result;
}

Matrix Matrix::map(std::function<double(double)> mapFunction) {
	Matrix result(numberOfRows, numberOfColumns);
	for (int row = 0; row < result.getNumberOfRows(); row++) {
		for (int col = 0; col < result.getNumberOfColumns(); col++) {
			double newEntry = mapFunction(getEntry(row, col));
			result.setEntry(row, col, newEntry);
		}
	}
	return result;
}

MatrixEntrySetter Matrix::operator=(double firstValue) {
	MatrixEntrySetter setter(this);
	setter.setNextEntry(firstValue);
	return setter;
}