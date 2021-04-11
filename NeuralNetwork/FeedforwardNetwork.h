#pragma once

#include <initializer_list>
#include <stdexcept>
#include <vector>
#include "FeedforwardOutput.h"
#include "../MatrixLibrary/Matrix.h"
#include "../MatrixLibrary/Vector.h"

class FeedforwardNetwork {

	public:
		FeedforwardNetwork(std::initializer_list<int> layers);
		~FeedforwardNetwork();
		int inputSize() const;
		int outputSize() const;
		int hiddenLayerCount() const;
		std::vector<int> getShape() const;
		Vector feedforward(const Vector input) const;
		FeedforwardOutput feedforwardGetOutput(const Vector input) const;
		Matrix getLayerWeights(int) const;
		Vector getLayerBiases(int) const;
		void shiftWeights(std::vector<Matrix> weightDeltas);
		void shiftBiases(std::vector<Vector> vectorDeltas);

	private:
		std::vector<int> shape;
		std::vector<Matrix> weights;
		std::vector<Vector> biases;

};