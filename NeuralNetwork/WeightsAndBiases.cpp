#include "pch.h"
#include "WeightsAndBiases.h"
#include <vector>
#include <stdexcept>

WeightsAndBiases::WeightsAndBiases(std::vector<Matrix> weights, std::vector<Vector> biases) :
	weights(weights), biases(biases)
{

}

WeightsAndBiases::WeightsAndBiases() {

}


WeightsAndBiases::WeightsAndBiases(std::initializer_list<int> layers) {
	if (layers.size() < 2) {
		throw std::invalid_argument("Network must have at least two layers");
	}
	int previousLayerSize = *layers.begin();
	for (const int* it = layers.begin() + 1; it < layers.end(); it++) {
		int layerSize = *it;
		this->weights.push_back(Matrix(layerSize, previousLayerSize));
		this->biases.push_back(Vector(layerSize));
		previousLayerSize = layerSize;
	}
}

WeightsAndBiases::WeightsAndBiases(std::vector<int> layers) {
	if (layers.size() < 2) {
		throw std::invalid_argument("Network must have at least two layers");
	}
	int previousLayerSize = layers.at(0);
	for (int i = 1; i < layers.size(); i++) {
		int layerSize = layers.at(i);
		this->weights.push_back(Matrix(layerSize, previousLayerSize));
		this->biases.push_back(Vector(layerSize));
		previousLayerSize = layerSize;
	}
}

WeightsAndBiases WeightsAndBiases::operator+(const WeightsAndBiases& other) const {
	WeightsAndBiases result;
	for (int i = 0; i < other.weights.size(); i++) {
		result.weights.push_back(weights.at(i) + other.weights.at(i));
	}
	for (int i = 0; i < other.biases.size(); i++) {
		result.biases.push_back(biases.at(i) + other.biases.at(i));
	}
	return result;
}

WeightsAndBiases WeightsAndBiases::operator*(double multiplier) const {
	WeightsAndBiases result;
	for (int i = 0; i < weights.size(); i++) {
		result.weights.push_back(weights.at(i) * multiplier);
	}
	for (int i = 0; i < biases.size(); i++) {
		result.biases.push_back(biases.at(i) * multiplier);
	}
	return result;
}