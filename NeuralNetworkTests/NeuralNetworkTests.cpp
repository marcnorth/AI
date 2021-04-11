#include <vector>

#include "pch.h"
#include "CppUnitTest.h"
#include "../NeuralNetwork/FeedforwardNetwork.h"
#include "../NeuralNetwork/FeedforwardOutput.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NeuralNetworkTests
{
	TEST_CLASS(NeuralNetworkTests)
	{
	public:

		TEST_METHOD(init)
		{
			FeedforwardNetwork nn{ 4, 3, 2 };
			Assert::AreEqual(4, nn.inputSize());
			Assert::AreEqual(2, nn.outputSize());
			Assert::AreEqual(1, nn.hiddenLayerCount());
			std::vector<int> shape = nn.getShape();
			Assert::AreEqual(std::size_t{ 3 }, shape.size());
			Assert::AreEqual(4, shape[0]);
			Assert::AreEqual(3, shape[1]);
			Assert::AreEqual(2, shape[2]);
			Assert::ExpectException<std::invalid_argument>([] { FeedforwardNetwork{ 4 }; });
		}

		TEST_METHOD(updateWeights)
		{
			FeedforwardNetwork nn{ 4, 3, 2 };
			Matrix weights1{ {0., 0., 0.}, {0., 0., 0.} };
			Matrix weights2{ {1., 2., 4.}, {3., 2., 3.} };
			Matrix result{ {2., 4., 8.}, {6., 4., 6.} };
			Assert::IsTrue(weights1.equalsWithPrecision(nn.getLayerWeights(3), 0.0001));
			Assert::IsFalse(weights2.equalsWithPrecision(nn.getLayerWeights(3), 0.0001));
			nn.shiftWeights({ Matrix(3, 4), weights2 });
			Assert::IsFalse(weights1.equalsWithPrecision(nn.getLayerWeights(3), 0.001));
			Assert::IsTrue(weights2.equalsWithPrecision(nn.getLayerWeights(3), 0.001));
			nn.shiftWeights({ Matrix(3, 4), weights2 });
			Assert::IsFalse(weights1.equalsWithPrecision(nn.getLayerWeights(3), 0.001));
			Assert::IsTrue(result.equalsWithPrecision(nn.getLayerWeights(3), 0.001));
		}

		TEST_METHOD(updateBiases)
		{
			FeedforwardNetwork nn{ 4, 3, 2 };
			Vector biases1{0., 0., 0.};
			Vector biases2{1., 2., 4.};
			Vector result{2., 4., 8.};
			Assert::IsTrue(biases1.equalsWithPrecision(nn.getLayerBiases(2), 0.0001));
			Assert::IsFalse(biases2.equalsWithPrecision(nn.getLayerBiases(2), 0.0001));
			nn.shiftBiases({ biases2, Vector(2) });
			Assert::IsFalse(biases1.equalsWithPrecision(nn.getLayerBiases(2), 0.001));
			Assert::IsTrue(biases2.equalsWithPrecision(nn.getLayerBiases(2), 0.001));
			nn.shiftBiases({ biases2, Vector(2) });
			Assert::IsFalse(biases1.equalsWithPrecision(nn.getLayerBiases(2), 0.001));
			Assert::IsTrue(result.equalsWithPrecision(nn.getLayerBiases(2), 0.001));
		}
		
		TEST_METHOD(feedforward)
		{
			FeedforwardNetwork nn{ 4, 3, 2 };
			nn.shiftWeights({
				{{0.01, 0.02, 0.03, 0.04}, {0.01, 0.02, 0.03, 0.04}, {0.02, 0.02, 0.03, 0.04}},
				{{1, 2, 3}, {3, 2, 1}}
			});
			// 0.03, 0.03, 0.031
			// 0.04, 0.05, 0.061
			// 0.5099986668799654659151, 0.5124973964842103436615, 0.5152452729880800108149

			// 3.080729278812626, 3.0702360665963968
			// 3.110729278812626, 3.1102360665963968
			// 0.9573331541227931453993, 0.9573130036413796116695
			nn.shiftBiases({
				{0.01, 0.02, 0.03},
				{0.03, 0.04}
			});
			Assert::ExpectException<std::invalid_argument>([] { FeedforwardNetwork{ 4 }; });
			FeedforwardOutput resultObject = nn.feedforwardGetOutput({ 0.1, 0.2, 0.3, 0.4 });
			Assert::IsTrue(resultObject.z[0].equalsWithPrecision({ 0.04, 0.05, 0.061 }, 0.00000001));
			Assert::IsTrue(resultObject.a[0].equalsWithPrecision({ 0.5099986668799654659151, 0.5124973964842103436615, 0.5152452729880800108149 }, 0.00000001));
			Assert::IsTrue(resultObject.z[1].equalsWithPrecision({ 3.110729278812626, 3.1102360665963968 }, 0.00000001));
			Assert::IsTrue(resultObject.a[1].equalsWithPrecision({ 0.9573331541227931453993, 0.9573130036413796116695 }, 0.00000001));
			Vector result = nn.feedforward({ 0.1, 0.2, 0.3, 0.4 });
			Assert::IsTrue(resultObject.getOutput().equalsWithPrecision(result, 0.00000001));
			Vector correctResult = { 0.9573331541227931453993, 0.9573130036413796116695 };
			Assert::IsTrue(result.equalsWithPrecision(correctResult, 0.00000001));
		}

	};
}
