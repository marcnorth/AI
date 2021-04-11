#pragma once

#include "FeedforwardOutput.h"
#include "../MatrixLibrary/Vector.h"

class OutputWithExpected {

	public:
		FeedforwardOutput output;
		Vector expectedOutput;
		OutputWithExpected(FeedforwardOutput, Vector);

};