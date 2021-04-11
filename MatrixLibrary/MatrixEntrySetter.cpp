#include "MatrixEntrySetter.h"
#include "Matrix.h"

MatrixEntrySetter::MatrixEntrySetter(Matrix* matrix) {
	this->matrix = matrix;
	this->currentEntry = 0;
}

MatrixEntrySetter MatrixEntrySetter::operator,(double value) {
	return setNextEntry(value);
}

MatrixEntrySetter MatrixEntrySetter::setNextEntry(double value) {
	int column = currentEntry % matrix->getNumberOfColumns();
	int row = currentEntry / matrix->getNumberOfColumns();
	matrix->setEntry(row, column, value);
	currentEntry++;
	return *this;
}