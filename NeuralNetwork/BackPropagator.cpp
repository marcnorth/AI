#include "pch.h"
#include "BackPropagator.h"

BackPropagator::BackPropagator(FeedforwardNetwork nn) : nn(nn) {

}

double BackPropagator::calculateError(const OutputWithExpected& outputWithExpected) const {
	// Quadratic cost
	double sum = 0;
	Vector output = outputWithExpected.output.getOutput();
	for (int i = 0; i < outputWithExpected.expectedOutput.getSize(); i++) {
		sum += pow(output.getEntry(i) - outputWithExpected.expectedOutput.getEntry(i), 2);
	}
	return 0.5 * sum;
}

WeightsAndBiases BackPropagator::calculateWeightAndBiasGradients(const OutputWithExpected& outputWithExpected) const {
	std::vector<Vector> localErrors = calculateLocalErrors(outputWithExpected);
	std::vector<Vector> biasGradients = calculateBiasGradients(localErrors);
	std::vector<Matrix> weightGradients = calculateWeightGradients(localErrors, outputWithExpected.output);
	return WeightsAndBiases(weightGradients, biasGradients);
}

std::vector<Vector> BackPropagator::calculateLocalErrors(const OutputWithExpected& outputWithExpected) const {
	std::vector<Vector> errors;
	FeedforwardOutput output = outputWithExpected.output;
	Vector costGradient = output.a.back() - outputWithExpected.expectedOutput;
	Vector activationDerivative = this->activationDerivative(output.a.back());
	errors.push_back(costGradient.hadamardProduct(activationDerivative));
	for (int i = nn.hiddenLayerCount() + 1; i > 1; i--) {
		Vector wd = nn.getLayerWeights(i+1).transpose() * errors.at(0);
		Vector activationDerivative = this->activationDerivative(output.a.at(i-2));
		errors.insert(errors.begin(), wd.hadamardProduct(activationDerivative));
	}
	return errors;
}

std::vector<Vector> BackPropagator::calculateBiasGradients(const std::vector<Vector>& localErrors) const {
	return localErrors;
}

std::vector<Matrix> BackPropagator::calculateWeightGradients(const std::vector<Vector>& localErrors, const FeedforwardOutput& output) const {
	std::vector<Matrix> weightGradients;
	std::vector<int> shape = nn.getShape();
	for (int layerNum = shape.size() - 1; layerNum > 0; layerNum--) {
		Matrix layerWeightGradients(shape.at(layerNum), shape.at(layerNum - 1));
		for (int i = 0; i < layerWeightGradients.getNumberOfRows(); i++) {
			for (int j = 0; j < layerWeightGradients.getNumberOfColumns(); j++) {
				Vector aa = layerNum > 1 ? output.a.at(layerNum - 2) : output.x;
				Vector ee = localErrors.at(layerNum - 1);
				double gradient = aa.getEntry(j) * ee.getEntry(i);
				layerWeightGradients.setEntry(i, j, gradient);
			}
		}
		weightGradients.insert(weightGradients.begin(), layerWeightGradients);
	}
	return weightGradients;
}


Vector BackPropagator::activationDerivative(const Vector& activations) const {
	return activations.map([](double a) { return a * (1 - a); });
}