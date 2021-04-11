#include "pch.h"
#include "FeedforwardNetwork.h"

FeedforwardNetwork::FeedforwardNetwork(std::initializer_list<int> layers) {
	if (layers.size() < 2) {
		throw std::invalid_argument("Network must have at least two layers");
	}
	int previousLayerSize = *layers.begin();
	this->shape.push_back(previousLayerSize);
	for (const int* it = layers.begin() + 1; it < layers.end(); it++) {
		int layerSize = *it;
		this->shape.push_back(layerSize);
		this->weights.push_back(Matrix(layerSize, previousLayerSize));
		this->biases.push_back(Vector(layerSize));
		previousLayerSize = layerSize;
	}
}

FeedforwardNetwork::~FeedforwardNetwork() {}

int FeedforwardNetwork::inputSize() const {
	return shape[0];
}

int FeedforwardNetwork::outputSize() const {
	return shape[shape.size()-1];
}

int FeedforwardNetwork::hiddenLayerCount() const {
	return shape.size() - 2;
}

std::vector<int> FeedforwardNetwork::getShape() const {
	return shape;
}

Matrix FeedforwardNetwork::getLayerWeights(int layer) const {
	return weights[layer - 2];
}

void FeedforwardNetwork::shiftWeights(std::vector<Matrix> matrixDeltas) {
	if (matrixDeltas.size() != shape.size() - 1) {
		throw std::invalid_argument("Matrix list must match number of layers - 1");
	}
	for (int i = 0; i < matrixDeltas.size(); i++) {
		weights[i] = weights[i] + matrixDeltas[i];
	}
}

Vector FeedforwardNetwork::getLayerBiases(int layer) const {
	return biases[layer - 2];
}

void FeedforwardNetwork::shiftBiases(std::vector<Vector> biasDeltas) {
	if (biasDeltas.size() != shape.size() - 1) {
		throw std::invalid_argument("Vector list must match number of layers - 1");
	}
	for (int i = 0; i < biasDeltas.size(); i++) {
		biases[i] = biases[i] + biasDeltas[i];
	}
}

Vector FeedforwardNetwork::feedforward(const Vector input) const {
	return feedforwardGetOutput(input).a.back();
}

FeedforwardOutput FeedforwardNetwork::feedforwardGetOutput(const Vector input) const {
	std::vector<Vector> z;
	std::vector<Vector> a;
	Vector output = input;
	for (int i = 0; i < weights.size(); i++) {
		output = weights[i] * output + biases[i];
		z.push_back(output);
		output = output.map([output](double x) { return 1 / (1 + exp(-x)); });
		a.push_back(output);
	}
	return FeedforwardOutput(input, z, a);
}