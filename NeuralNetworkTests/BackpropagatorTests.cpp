#include <vector>

#include "pch.h"
#include "CppUnitTest.h"
#include "../NeuralNetwork/BackPropagator.h"
#include "../NeuralNetwork/FeedforwardNetwork.h"
#include "../NeuralNetwork/FeedforwardOutput.h"
#include "../NeuralNetwork/OutputWithExpected.h"
#include "../NeuralNetwork/Game.h"
#include "../NeuralNetwork/Agent.h"
#include "../NeuralNetwork/Trainer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NeuralNetworkTests
{
	TEST_CLASS(BackpropagatorTests)
	{
	public:

		TEST_METHOD(singleError)
		{
			FeedforwardNetwork nn{ 4, 3, 2 };
			nn.shiftWeights({
				{{0.01, 0.02, 0.03, 0.04}, {0.01, 0.02, 0.03, 0.04}, {0.02, 0.02, 0.03, 0.04}},
				{{1, 2, 3}, {3, 2, 1}}
			});
			nn.shiftBiases({
				{0.01, 0.02, 0.03},
				{0.03, 0.04}
			});
			BackPropagator backPropagator(nn);
			FeedforwardOutput output = nn.feedforwardGetOutput({ 0.1, 0.2, 0.3, 0.4 });
			Vector expectedOutput{ 0., 1. };
			OutputWithExpected outputWithExpected{ output, expectedOutput };
			double error = backPropagator.calculateError(outputWithExpected);
			double correctError = 0.45915447382;
			Assert::AreEqual(correctError, error, 0.0000001);
		}

		TEST_METHOD(weightAndBiases)
		{
			WeightsAndBiases wbs{4, 3, 2};
			Assert::AreEqual(std::size_t{ 2 }, wbs.weights.size());
			Assert::AreEqual(std::size_t{ 2 }, wbs.biases.size());
			Matrix w1 = { { 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0 } };
			Assert::IsTrue(wbs.weights.at(0).equalsWithPrecision(w1, 0.00001));
			Matrix w2 = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 } };
			Assert::IsTrue(wbs.weights.at(1).equalsWithPrecision(w2, 0.00001));
			Vector b1 = { 0.0, 0.0, 0.0 };
			Assert::IsTrue(wbs.biases.at(0).equalsWithPrecision(b1, 0.00001));
			Vector b2 = { 0.0, 0.0 };
			Assert::IsTrue(wbs.biases.at(1).equalsWithPrecision(b2, 0.00001));
			WeightsAndBiases wbs2({
				{ { 1.0, 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 } },
				{ { 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0 } }
			},
				{ { 1.0, 1.0, 1.0 } , { 1.0, 1.0 } }
			);
			WeightsAndBiases additionResult = wbs + wbs2;
			Matrix correctResult1 = { { 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0 } };
			Assert::IsTrue(additionResult.weights.at(1).equalsWithPrecision(correctResult1, 0.00001));
			WeightsAndBiases multiplyResult = wbs2 * 2;
			Matrix correctResult2 = { { 2.0, 2.0, 2.0 }, { 2.0, 2.0, 2.0 } };
			Assert::IsTrue(multiplyResult.weights.at(1).equalsWithPrecision(correctResult2, 0.00001));
		}

		TEST_METHOD(trainer)
		{
			std::shared_ptr<FeedforwardNetwork> pNn(new FeedforwardNetwork{ 2, 3, 1 });
			Game game;
			Agent agent(pNn);
			Trainer trainer(game, agent);
			trainer.setBatchSize(100);
			std::vector<double> scores;
			scores.push_back(trainer.test(100));
			for (int i = 0; i < 10; i++) {
				trainer.runBatches(50);
				scores.push_back(trainer.test(100));
			}
			Assert::IsTrue(scores.at(0) < scores.at(2));
			Assert::IsTrue(scores.at(2) < scores.at(10));
		}

	};
}
