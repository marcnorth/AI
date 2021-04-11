#pragma once

class Matrix;

class MatrixEntrySetter {

	public:
		MatrixEntrySetter(Matrix*);
		MatrixEntrySetter setNextEntry(double);
		MatrixEntrySetter operator,(double);

	private:
		Matrix* matrix;
		int currentEntry;

};