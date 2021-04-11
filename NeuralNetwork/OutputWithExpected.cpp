#include "pch.h"
#include "OutputWithExpected.h"

OutputWithExpected::OutputWithExpected(FeedforwardOutput output, Vector expectedOutput) :
	output(output),
	expectedOutput(expectedOutput)
{

}