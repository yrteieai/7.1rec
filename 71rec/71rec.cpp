#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

// ���������� ������� ��� ��������� �������
void CreateMatrix(int** matrix, const int rowCount, const int colCount, const int Low, const int High, int i = 0, int j = 0) {
    if (i >= rowCount) {
        return;
    }
    matrix[i][j] = Low + rand() % (High - Low + 1);

    if (j < colCount - 1) {
        CreateMatrix(matrix, rowCount, colCount, Low, High, i, j + 1);
    }
    else {
        CreateMatrix(matrix, rowCount, colCount, Low, High, i + 1, 0);
    }
}

// ���������� ������� ��� ��������� �������
void PrintMatrix(int** matrix, const int rowCount, const int colCount, int i = 0, int j = 0) {
    if (i >= rowCount) {
        return;
    }
    if (j < colCount) {
        cout << setw(4) << matrix[i][j];
        PrintMatrix(matrix, rowCount, colCount, i, j + 1);
    }
    else {
        cout << endl;
        PrintMatrix(matrix, rowCount, colCount, i + 1, 0);
    }
}

// ���������� ������� ��� ������������ ��������
void SwapColumns(int** matrix, int col1, int col2, const int rowCount, int i = 0) {
    if (i >= rowCount) {
        return;  // ���� ������: ���� �� ����� ��������
    }
    int temp = matrix[i][col1];
    matrix[i][col1] = matrix[i][col2];
    matrix[i][col2] = temp;

    SwapColumns(matrix, col1, col2, rowCount, i + 1);
}

// ���������� ������� ��� ���������� �������� �������
void SortMatrix(int** matrix, const int rowCount, const int colCount, int i = 0, int j = 0) {
    // ���� ������: ���� �� ������� ��������
    if (i >= colCount - 1) {
        return;
    }

    // ��������� ������� ���� �������� ��� ���������� �� ������ ������ (���� �������)
    if (j < colCount - i - 1) {
        if (matrix[0][j] > matrix[0][j + 1]) {
            SwapColumns(matrix, j, j + 1, rowCount);  // ������������� �������
        }
        // ���� � ������� ����� ������� ��������, ������� �� ������ ������ (������ �����)
        else if (matrix[0][j] == matrix[0][j + 1]) {
            if (matrix[1][j] < matrix[1][j + 1]) {
                SwapColumns(matrix, j, j + 1, rowCount);
            }
            // ���� � � ������� ����� ������� ��������, ������� �� ����� ������ (������ �����)
            else if (matrix[1][j] == matrix[1][j + 1]) {
                if (matrix[2][j] < matrix[2][j + 1]) {
                    SwapColumns(matrix, j, j + 1, rowCount);
                }
            }
        }

        // ��������� ���������� ��� �������� ���� �������� � ������� ��������
        SortMatrix(matrix, rowCount, colCount, i, j + 1);
    }
    else {
        // ���������� �� �������� �������� (�������� ������� �������� ��� ���������)
        SortMatrix(matrix, rowCount, colCount, i + 1, 0);
    }
}

// ���������� ������� ��� ���������� ���� �� ������� ��������
void CalculateAndReplace(int** matrix, const int rowCount, const int colCount, int& count, int& sum, int i = 0, int j = 0) {
    if (i >= rowCount) {
        return;
    }

    if (j < colCount) {
        if (matrix[i][j] % 2 == 0 && matrix[i][j] % 7 != 0) {
            sum += matrix[i][j];
            count++;
            matrix[i][j] = 0;
        }
        CalculateAndReplace(matrix, rowCount, colCount, count, sum, i, j + 1);
    }
    else {
        CalculateAndReplace(matrix, rowCount, colCount, count, sum, i + 1, 0);
    }
}

int main() {
    srand((unsigned)time(NULL));  // ����������� ���������� ���������� �����
    const int Low = 18;           // ����� ���� ������� ��������
    const int High = 74;          // ������ ���� ������� ��������
    const int rowCount = 9;       // ʳ������ �����
    const int colCount = 6;       // ʳ������ ��������

    // �������� ���'�� ��� �������
    int** matrix = new int* [rowCount];
    for (int i = 0; i < rowCount; i++) {
        matrix[i] = new int[colCount];
    }

    // ��������� �� ��������� ��������� �������
    CreateMatrix(matrix, rowCount, colCount, Low, High);
    cout << "Original matrix:" << endl;
    PrintMatrix(matrix, rowCount, colCount);

    // ���������� �������
    SortMatrix(matrix, rowCount, colCount);
    cout << "\nSorted matrix:" << endl;
    PrintMatrix(matrix, rowCount, colCount);

    // ���������� ������� �� ���� ��������, �� ���������� �������
    int count = 0, sum = 0;
    CalculateAndReplace(matrix, rowCount, colCount, count, sum);
    cout << "\nModified matrix with zeros (elements satisfying the condition were replaced with 0):" << endl;
    PrintMatrix(matrix, rowCount, colCount);

    // ��������� ����������
    cout << "\nCount of elements satisfying the condition: " << count << endl;
    cout << "Sum of elements satisfying the condition: " << sum << endl;

    // ��������� ���'��
    for (int i = 0; i < rowCount; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
