#pragma once

class Vector;

class VectorEntrySetter {

	public:
		VectorEntrySetter(Vector*);
		VectorEntrySetter setNextEntry(double);
		VectorEntrySetter operator,(double);

	private:
		Vector* vector;
		int currentEntry;

};