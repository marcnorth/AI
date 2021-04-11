#pragma once

#include <vector>
#include "../MatrixLibrary/Matrix.h"
#include "../MatrixLibrary/Vector.h"

class WeightsAndBiases {

	public:
		std::vector<Matrix> weights;
		std::vector<Vector> biases;

		WeightsAndBiases();
		WeightsAndBiases(std::vector<Matrix> weights, std::vector<Vector> biases);
		WeightsAndBiases(std::initializer_list<int> layers);
		WeightsAndBiases(std::vector<int> layers);

		WeightsAndBiases operator+ (const WeightsAndBiases& other) const;
		WeightsAndBiases operator* (double multiplier) const;

};