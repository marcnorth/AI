#pragma once

#include <array>
#include <functional>
#include "MatrixEntrySetter.h"
#include "Vector.h"

class Matrix {

	public:
		Matrix(int rows, int columns);
		Matrix(const Matrix &);
		Matrix(std::initializer_list<std::initializer_list<double>>);
		~Matrix();
		Matrix operator=(const Matrix);
		int getNumberOfRows() const;
		int getNumberOfColumns() const;
		void setEntry(int row, int column, double value);
		double getEntry(int row, int column) const;
		bool hasSameShapeAs(const Matrix &) const;
		bool equalsWithPrecision(const Matrix &, const double) const;
		Matrix transpose() const;
		Matrix operator+(const Matrix &) const;
		Matrix add(const Matrix &) const;
		Matrix operator*(const Matrix &) const;
		Matrix multiply(const Matrix &) const;
		Vector operator*(const Vector&) const;
		Vector multiply(const Vector&) const;
		Matrix operator*(double) const;
		Matrix multiply(double) const;
		Matrix map(std::function<double(double)>);
		MatrixEntrySetter operator=(double firstValue);

	private:
		int numberOfRows;
		int numberOfColumns;
		double* entries;

};