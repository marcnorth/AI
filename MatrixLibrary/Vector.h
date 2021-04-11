#pragma once

#include <functional>
#include "VectorEntrySetter.h"

class Vector {
	
	public:
		Vector(int size);
		Vector(const Vector &);
		Vector(std::initializer_list<double>);
		~Vector();
		Vector operator=(const Vector&);
		void setEntry(const int, const double);
		double getEntry(const int) const;
		int getSize() const;
		bool hasSameSizeAs(const Vector &) const;
		bool equalsWithPrecision(const Vector &, const double precision) const;
		Vector operator*(double) const;
		Vector operator+(const Vector&) const;
		Vector operator-(const Vector&) const;
		Vector multiply(double) const;
		Vector add(const Vector&) const;
		Vector minus(const Vector&) const;
		double dot(const Vector&) const;
		Vector hadamardProduct(const Vector&) const;
		VectorEntrySetter operator=(double firstValue);
		Vector map(std::function<double(double)>) const;

	private:
		int size;
		double* entries;

};