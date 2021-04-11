#pragma once

#include <vector>
#include "../MatrixLibrary/Vector.h"

class FeedforwardOutput {

	public:
		Vector x;
		std::vector<Vector> z;
		std::vector<Vector> a;

	public:
		FeedforwardOutput(Vector x, std::vector<Vector> z, std::vector<Vector> a);
		Vector getOutput() const;

};