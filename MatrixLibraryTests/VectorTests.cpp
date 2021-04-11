#include "pch.h"
#include "CppUnitTest.h"

#include "../MatrixLibrary/Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VectorTests
{
	TEST_CLASS(VectorTests)
	{
	public:

		TEST_METHOD(init) {
			Vector v1(3);
			Assert::AreEqual(3, v1.getSize());
			Assert::AreEqual(0.0, v1.getEntry(0), 0.00001);
			Assert::AreEqual(0.0, v1.getEntry(1), 0.00001);
			Assert::ExpectException<std::out_of_range>([&v1] { v1.getEntry(3); });
			Vector v2{ 1.0, 2.0, 3.0 };
			Vector v3{ 1.0, 2.0, 3.0, 4.0 };
			Assert::AreEqual(3, v2.getSize());
			Assert::AreEqual(4, v3.getSize());
			Assert::AreEqual(1.0, v2.getEntry(0), 0.00001);
			Assert::AreEqual(2.0, v2.getEntry(1), 0.00001);
		}

		TEST_METHOD(equals) {
			Vector v1(3);
			Vector v2(3);
			Vector v3(3);
			Vector v4(4);
			v3.setEntry(1, 3.0);
			Assert::AreEqual(3.0, v3.getEntry(1), 0.00001);
			Assert::IsTrue(v1.hasSameSizeAs(v2));
			Assert::IsTrue(v1.hasSameSizeAs(v3));
			Assert::IsFalse(v1.hasSameSizeAs(v4));
			Assert::IsTrue(v1.equalsWithPrecision(v2, 0.00001));
			Assert::IsFalse(v1.equalsWithPrecision(v3, 0.00001));
			Assert::ExpectException<std::invalid_argument>([&v1, &v4] { v1.equalsWithPrecision(v4, 0.00001); });
		}

		TEST_METHOD(set) {
			Vector v1(3);
			v1 = 1.0, 2.0, 3.0;
			Assert::AreEqual(1.0, v1.getEntry(0), 0.00001);
			Assert::AreEqual(2.0, v1.getEntry(1), 0.00001);
			Assert::AreEqual(3.0, v1.getEntry(2), 0.00001);
			Assert::ExpectException<std::out_of_range>([&v1] { v1 = 1.0, 2.0, 3.0, 4.0; });
		}

		TEST_METHOD(add) {
			Vector v1(3);
			v1 = 1.0, 2.0, 3.0;
			Vector wrongSize(4);
			Assert::ExpectException<std::invalid_argument>([&v1, &wrongSize] { v1 + wrongSize; });
			Vector v2(3);
			v2 = 2.0, 3.0, 4.0;
			Vector result = v1 + v2;
			Vector correctResult(3);
			correctResult = 3.0, 5.0, 7.0;
			Vector incorrectResult(3);
			incorrectResult = 3.0, 6.0, 9.0;
			Assert::IsTrue(result.equalsWithPrecision(correctResult, 0.0001));
			Assert::IsFalse(result.equalsWithPrecision(incorrectResult, 0.0001));
		}

		TEST_METHOD(minus) {
			Vector v1(3);
			v1 = 1.0, 2.0, 3.0;
			Vector wrongSize(4);
			Assert::ExpectException<std::invalid_argument>([&v1, &wrongSize] { v1 - wrongSize; });
			Vector v2(3);
			v2 = 2.0, 3.0, 4.0;
			Vector result = v1 - v2;
			Vector correctResult(3);
			correctResult = -1.0, -1.0, -1.0;
			Vector incorrectResult(3);
			incorrectResult = 3.0, 6.0, 9.0;
			Assert::IsTrue(result.equalsWithPrecision(correctResult, 0.0001));
			Assert::IsFalse(result.equalsWithPrecision(incorrectResult, 0.0001));
		}

		TEST_METHOD(dot) {
			Vector v1(3);
			v1 = 1.0, 2.0, 3.0;
			Vector wrongSize(4);
			Assert::ExpectException<std::invalid_argument>([&v1, &wrongSize] { v1.hadamardProduct(wrongSize); });
			Vector v2(3);
			v2 = 2.0, 3.0, 4.0;
			double result = v1.dot(v2);
			double correctResult = 20.0;
			double incorrectResult = 15;
			Assert::AreEqual(result, correctResult, 0.0001);
			Assert::AreNotEqual(result, incorrectResult, 0.0001);
		}

		TEST_METHOD(hadamardProduct) {
			Vector v1(3);
			v1 = 1.0, 2.0, 3.0;
			Vector wrongSize(4);
			Assert::ExpectException<std::invalid_argument>([&v1, &wrongSize] { v1.hadamardProduct(wrongSize); });
			Vector v2(3);
			v2 = 2.0, 3.0, 4.0;
			Vector result = v1.hadamardProduct(v2);
			Vector correctResult(3);
			correctResult = 2.0, 6.0, 12.0;
			Vector incorrectResult(3);
			incorrectResult = 2.0, 6.0, 11.0;
			Assert::IsTrue(result.equalsWithPrecision(correctResult, 0.0001));
			Assert::IsFalse(result.equalsWithPrecision(incorrectResult, 0.0001));
		}

		TEST_METHOD(map) {
			Vector v1(3);
			v1 = 1.0, 2.0, 3.0;
			Vector result = v1.map([](double v) { return v / 2.0; });
			Vector correctResult(3);
			correctResult = 0.5, 1.0, 1.5;
			Vector incorrectResult(3);
			incorrectResult = 1.5, 1.0, 6.0;
			Assert::IsTrue(result.equalsWithPrecision(correctResult, 0.0001));
			Assert::IsFalse(result.equalsWithPrecision(incorrectResult, 0.0001));
		}

	};

}