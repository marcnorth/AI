#include "VectorEntrySetter.h"
#include "Vector.h"

VectorEntrySetter::VectorEntrySetter(Vector* vector) {
	this->vector = vector;
	this->currentEntry = 0;
}

VectorEntrySetter VectorEntrySetter::operator,(double value) {
	return setNextEntry(value);
}

VectorEntrySetter VectorEntrySetter::setNextEntry(double value) {
	vector->setEntry(currentEntry, value);
	currentEntry++;
	return *this;
}