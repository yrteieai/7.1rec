#include "pch.h"
#include "CppUnitTest.h"
#include "../7.1_rec/7.1_rec.cpp"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest71rec
{
    TEST_CLASS(UnitTest71rec)
    {
    public:

        TEST_METHOD(TestCreateMatrix)
        {
            const int rowCount = 9;
            const int colCount = 6;
            const int Low = 18;
            const int High = 74;

            int** matrix = new int* [rowCount];
            for (int i = 0; i < rowCount; i++) {
                matrix[i] = new int[colCount];
            }

            CreateMatrix(matrix, rowCount, colCount, Low, High);

            for (int i = 0; i < rowCount; i++) {
                for (int j = 0; j < colCount; j++) {
                    Assert::IsTrue(matrix[i][j] >= Low && matrix[i][j] <= High, L"Matrix element out of bounds.");
                }
            }

            for (int i = 0; i < rowCount; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }

        TEST_METHOD(TestSortMatrix)
        {
            const int rowCount = 3;
            const int colCount = 3;

            int** matrix = new int* [rowCount];
            for (int i = 0; i < rowCount; i++) {
                matrix[i] = new int[colCount];
            }

            matrix[0][0] = 5; matrix[0][1] = 3; matrix[0][2] = 8;
            matrix[1][0] = 9; matrix[1][1] = 7; matrix[1][2] = 1;
            matrix[2][0] = 6; matrix[2][1] = 4; matrix[2][2] = 2;

            SortMatrix(matrix, rowCount, colCount);

            Assert::IsTrue(matrix[0][0] <= matrix[0][1] && matrix[0][1] <= matrix[0][2], L"First row is not sorted correctly.");

            for (int i = 0; i < rowCount; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }

        // Тест для функції підрахунку кількості та суми елементів
        TEST_METHOD(TestCalculateAndReplace)
        {
            const int rowCount = 3;
            const int colCount = 3;
            int** matrix = new int* [rowCount];
            for (int i = 0; i < rowCount; i++) {
                matrix[i] = new int[colCount];
            }

            matrix[0][0] = 28; matrix[0][1] = 35; matrix[0][2] = 42;
            matrix[1][0] = 12; matrix[1][1] = 14; matrix[1][2] = 7;
            matrix[2][0] = 36; matrix[2][1] = 49; matrix[2][2] = 56;

            int count = 0, sum = 0;
            CalculateAndReplace(matrix, rowCount, colCount, count, sum);

            Assert::AreEqual(2, count, L"Incorrect count of elements.");
            Assert::AreEqual(48, sum, L"Incorrect sum of elements.");

            Assert::AreEqual(0, matrix[1][0], L"Element not replaced with 0.");
            Assert::AreEqual(0, matrix[2][0], L"Element not replaced with 0.");

            for (int i = 0; i < rowCount; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
    };
}
