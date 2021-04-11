#include "pch.h"
#include "FeedforwardOutput.h"

FeedforwardOutput::FeedforwardOutput(Vector x, std::vector<Vector> z, std::vector<Vector> a) :
	x(x),
	z(z),
	a(a)
{
	
}

Vector FeedforwardOutput::getOutput() const {
	return a[a.size()-1];
}