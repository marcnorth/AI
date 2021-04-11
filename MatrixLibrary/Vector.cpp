#include "Vector.h"

#include <stdexcept>

Vector::Vector(int size) {
	this->size = size;
	this->entries = new double[size]();
}

Vector::Vector(const Vector &other) : Vector(other.getSize()) {
	memcpy(this->entries, other.entries, sizeof(double) * size);
}

Vector::Vector(std::initializer_list<double> values) : Vector(values.size()) {
	for (const double* it = values.begin(); it != values.end(); it++) {
		this->entries[it - values.begin()] = *it;
	}
}

Vector::~Vector() {
	delete[] this->entries;
}

Vector Vector::operator=(const Vector& rhs) {
	delete[] this->entries;
	this->size = rhs.getSize();
	this->entries = new double[rhs.getSize()];
	memcpy(this->entries, rhs.entries, sizeof(double) * size);
	return *this;
}

int Vector::getSize() const {
	return size;
}

bool Vector::hasSameSizeAs(const Vector &other) const {
	return other.getSize() == size;
}

void Vector::setEntry(const int i, const double value) {
	if (i < 0 || i >= size) {
		throw std::out_of_range("Vector entry out of range");
	}
	entries[i] = value;
}

double Vector::getEntry(const int i) const {
	if (i < 0 || i >= size) {
		throw std::out_of_range("Vector entry out of range");
	}
	return this->entries[i];
}

bool Vector::equalsWithPrecision(const Vector& other, const double precision) const {
	if (!hasSameSizeAs(other)) {
		throw std::invalid_argument("Vectors are different sizes");
	}
	for (int i = 0; i < size; i++) {
		if (abs(getEntry(i) - other.getEntry(i)) >= precision) {
			return false;
		}
	}
	return true;
}

VectorEntrySetter Vector::operator=(double firstValue) {
	VectorEntrySetter setter(this);
	setter.setNextEntry(firstValue);
	return setter;
}

Vector Vector::operator*(double multiplier) const {
	return multiply(multiplier);
}

Vector Vector::multiply(double multiplier) const {
	Vector result = Vector(size);
	for (int entry = 0; entry < size; entry++) {
		result.setEntry(entry, getEntry(entry) * multiplier);
	}
	return result;
}

Vector Vector::operator+(const Vector& other) const {
	return add(other);
}

Vector Vector::add(const Vector& other) const {
	if (!hasSameSizeAs(other)) {
		throw std::invalid_argument("Vectors do not have the same shape");
	}
	Vector result = Vector(size);
	for (int entry = 0; entry < size; entry++) {
		result.setEntry(entry, getEntry(entry) + other.getEntry(entry));
	}
	return result;
}

Vector Vector::operator-(const Vector& other) const {
	return minus(other);
}

Vector Vector::minus(const Vector& other) const {
	if (!hasSameSizeAs(other)) {
		throw std::invalid_argument("Vectors do not have the same shape");
	}
	Vector result = Vector(size);
	for (int entry = 0; entry < size; entry++) {
		result.setEntry(entry, getEntry(entry) - other.getEntry(entry));
	}
	return result;
}

double Vector::dot(const Vector& other) const {
	if (size != other.getSize()) {
		throw std::invalid_argument("Vector sizes do not match");
	}
	double result = 0;
	for (int i = 0; i < size; i++) {
		result += getEntry(i) * other.getEntry(i);
	}
	return result;
}

Vector Vector::hadamardProduct(const Vector& other) const {
	if (size != other.getSize()) {
		throw std::invalid_argument("Vector sizes do not match");
	}
	Vector result(size);
	for (int i = 0; i < size; i++) {
		result.setEntry(i, getEntry(i) * other.getEntry(i));
	}
	return result;
}

Vector Vector::map(std::function<double(double)> mapFunction) const {
	Vector result(size);
	for (int i = 0; i < size; i++) {
		result.setEntry(i, mapFunction(getEntry(i)));
	}
	return result;
}