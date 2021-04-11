#pragma once

#include "FeedforwardNetwork.h"
#include "OutputWithExpected.h"
#include "WeightsAndBiases.h"

class BackPropagator {

	public:
		BackPropagator(FeedforwardNetwork);
		double calculateError(const OutputWithExpected&) const;
		WeightsAndBiases calculateWeightAndBiasGradients(const OutputWithExpected&) const;

	private:
		Vector activationDerivative(const Vector& activations) const;
		std::vector<Vector> calculateLocalErrors(const OutputWithExpected&) const;
		std::vector<Vector> calculateBiasGradients(const std::vector<Vector>& localErrors) const;
		std::vector<Matrix> calculateWeightGradients(const std::vector<Vector>& localErrors, const FeedforwardOutput& output) const;
		
	private:
		FeedforwardNetwork nn;

};