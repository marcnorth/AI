#include "pch.h"
#include "CppUnitTest.h"

#include "../MatrixLibrary/Matrix.h"
#include "../MatrixLibrary/Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixLibraryTests
{
	TEST_CLASS(MatrixLibraryTests)
	{
	public:
		
		TEST_METHOD(init) {
			Matrix m1(2, 3);
			Assert::AreEqual(2, m1.getNumberOfRows());
			Assert::AreEqual(3, m1.getNumberOfColumns());
			Assert::AreEqual(0.0, m1.getEntry(0, 1), 0.00001);
			Assert::AreEqual(0.0, m1.getEntry(1, 2), 0.00001);
			Assert::ExpectException<std::out_of_range>([&m1] { m1.getEntry(3, 0); });
			Matrix m2{ {1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0} };
			Matrix m3{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0} };
			Assert::AreEqual(3, m2.getNumberOfRows());
			Assert::AreEqual(2, m2.getNumberOfColumns());
			Assert::AreEqual(2, m3.getNumberOfRows());
			Assert::AreEqual(3, m3.getNumberOfColumns());
			Assert::AreEqual(1.0, m3.getEntry(0, 0), 0.0001);
			Assert::AreEqual(5.0, m3.getEntry(1, 1), 0.0001);
			Assert::ExpectException<std::invalid_argument>([] { Matrix m4{ {1.0, 2.0}, {3.0} }; });
		}

		TEST_METHOD(equals) {
			Matrix m1(2, 3);
			Matrix m2(2, 3);
			Matrix m3(2, 3);
			Matrix m4(3, 4);
			m3.setEntry(0, 1, 3.0);
			Assert::AreEqual(3.0, m3.getEntry(0, 1), 0.00001);
			Assert::IsTrue(m1.hasSameShapeAs(m2));
			Assert::IsTrue(m1.hasSameShapeAs(m3));
			Assert::IsFalse(m1.hasSameShapeAs(m4));
			Assert::IsTrue(m1.equalsWithPrecision(m2, 0.00001));
			Assert::IsFalse(m1.equalsWithPrecision(m3, 0.00001));
			Assert::ExpectException<std::invalid_argument>([&m1, &m4] { m1.equalsWithPrecision(m4, 0.00001); });
		}

		TEST_METHOD(set) {
			Matrix m1(2, 3);
			m1 = 1.0, 2.0, 3.0,
				 4.0, 5.0, 6.0;
			Assert::AreEqual(2.0, m1.getEntry(0, 1), 0.00001);
			Assert::AreEqual(5.0, m1.getEntry(1, 1), 0.00001);
			Assert::AreEqual(6.0, m1.getEntry(1, 2), 0.00001);
			Assert::ExpectException<std::out_of_range>([&m1] { m1 = 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0; });
		}

		TEST_METHOD(selfAssign) {
			Matrix m1(2, 3);
			m1 = 1.0, 2.0, 3.0,
				4.0, 5.0, 6.0;
			m1 = m1;
			Assert::IsTrue(m1.equalsWithPrecision({ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0} }, 0.00000001));
		}

		TEST_METHOD(transpose) {
			Matrix m1(2, 3);
			m1 = 1.0, 2.0, 3.0,
				 4.0, 5.0, 6.0;
			Matrix correctResult(3, 2);
			correctResult = 1.0, 4.0,
				            2.0, 5.0,
				            3.0, 6.0;
			Matrix incorrectResult(3, 2);
			incorrectResult = 5.0, 3.0,
				              2.0, 8.0,
				              6.0, 2.0;
			Matrix result = m1.transpose();
			Assert::IsTrue(result.equalsWithPrecision(correctResult, 0.0001));
			Assert::IsFalse(result.equalsWithPrecision(incorrectResult, 0.0001));
		}

		TEST_METHOD(add) {
			Matrix m1(2, 3);
			m1 = 1.0, 2.0, 3.0,
				 4.0, 5.0, 6.0;
			Matrix wrongShape(2, 4);
			Assert::ExpectException<std::invalid_argument>([&m1, &wrongShape] { m1 + wrongShape; });
			Matrix m2(2, 3);
			m2 = 2.0, 3.0, 4.0,
				 5.0, 6.0, 7.0;
			Matrix result = m1 + m2;
			Matrix correctResult(2, 3);
			correctResult = 3.0,  5.0,  7.0,
							9.0, 11.0, 13.0;
			Matrix incorrectResult(2,3);
			incorrectResult = 3.0, 6.0, 7.0,
							  9.0, 8.0, 7.0;
			Assert::IsTrue(result.equalsWithPrecision(correctResult, 0.0001));
			Assert::IsFalse(result.equalsWithPrecision(incorrectResult, 0.0001));
		}

		TEST_METHOD(multiply) {
			Matrix m1(2, 3);
			m1 = 1.0, 2.0, 3.0,
				 4.0, 5.0, 6.0;
			Matrix wrongShape(2, 4);
			Assert::ExpectException<std::invalid_argument>([&m1, &wrongShape] { m1 * wrongShape; });
			Matrix m2(3, 4);
			m2 = 2.0, 3.0, 4.0, 5.0,
				 1.0, 2.0, 3.0, 4.0,
				 4.0, 3.0, 2.0, 1.0;
			Matrix result = m1 * m2;
			Matrix correctResult(2, 4);
			correctResult = 16.0, 16.0, 16.0, 16.0,
							37.0, 40.0, 43.0, 46.0;
			Matrix incorrectResult(2, 4);
			incorrectResult = 10.0, 16.0, 16.0, 16.0,
							  37.0, 40.0, 43.0, 46.0;
			Assert::IsTrue(result.equalsWithPrecision(correctResult, 0.0001));
			Assert::IsFalse(result.equalsWithPrecision(incorrectResult, 0.0001));
		}

		TEST_METHOD(map) {
			Matrix m1(2, 3);
			m1 = 1.0, 2.0, 3.0,
				4.0, 5.0, 6.0;
			Matrix result = m1.map([](double v) { return v / 2.0; });
			Matrix correctResult(2, 3);
			correctResult = 0.5, 1.0, 1.5,
							2.0, 2.5, 3.0;
			Matrix incorrectResult(2, 3);
			incorrectResult = 1.5, 1.0, 6.0,
							  2.0, 2.5, 3.0;
			Assert::IsTrue(result.equalsWithPrecision(correctResult, 0.0001));
			Assert::IsFalse(result.equalsWithPrecision(incorrectResult, 0.0001));
		}

		TEST_METHOD(vectorMultiplication) {
			Vector v1(3);
			v1 = 1.0, 2.0, 3.0;
			Matrix wrongShape(4, 5);
			Assert::ExpectException<std::invalid_argument>([&v1, &wrongShape] { wrongShape * v1; });
			Matrix m1(4, 3);
			m1 = 2.0, 3.0, 4.0,
				 3.0, 4.0, 5.0,
				 4.0, 5.0, 6.0,
				 5.0, 6.0, 7.0;
			Vector result = m1 * v1;
			Vector correctResult(4);
			correctResult = 20.0, 26.0, 32.0, 38.0;
			Vector incorrectResult(4);
			incorrectResult = 19.0, 26.0, 32.0, 40.0;
			Assert::IsTrue(result.equalsWithPrecision(correctResult, 0.0001));
			Assert::IsFalse(result.equalsWithPrecision(incorrectResult, 0.0001));
		}

	};
}
