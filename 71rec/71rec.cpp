#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

// Рекурсивна функція для створення матриці
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

// Рекурсивна функція для виведення матриці
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

// Рекурсивна функція для перестановки стовпців
void SwapColumns(int** matrix, int col1, int col2, const int rowCount, int i = 0) {
    if (i >= rowCount) {
        return;  // База рекурсії: коли всі рядки оброблені
    }
    int temp = matrix[i][col1];
    matrix[i][col1] = matrix[i][col2];
    matrix[i][col2] = temp;

    SwapColumns(matrix, col1, col2, rowCount, i + 1);
}

// Рекурсивна функція для сортування стовпців матриці
void SortMatrix(int** matrix, const int rowCount, const int colCount, int i = 0, int j = 0) {
    // База рекурсії: коли всі стовпці оброблені
    if (i >= colCount - 1) {
        return;
    }

    // Порівнюємо поточну пару стовпців для сортування за першим рядком (зліва направо)
    if (j < colCount - i - 1) {
        if (matrix[0][j] > matrix[0][j + 1]) {
            SwapColumns(matrix, j, j + 1, rowCount);  // Переставляємо стовпці
        }
        // Якщо в першому рядку однакові елементи, сортуємо за другим рядком (справа наліво)
        else if (matrix[0][j] == matrix[0][j + 1]) {
            if (matrix[1][j] < matrix[1][j + 1]) {
                SwapColumns(matrix, j, j + 1, rowCount);
            }
            // Якщо і в другому рядку однакові елементи, сортуємо за третім рядком (справа наліво)
            else if (matrix[1][j] == matrix[1][j + 1]) {
                if (matrix[2][j] < matrix[2][j + 1]) {
                    SwapColumns(matrix, j, j + 1, rowCount);
                }
            }
        }

        // Викликаємо рекурсивно для наступної пари стовпців у поточній ітерації
        SortMatrix(matrix, rowCount, colCount, i, j + 1);
    }
    else {
        // Переходимо до наступної ітерації (зменшуємо кількість елементів для порівняння)
        SortMatrix(matrix, rowCount, colCount, i + 1, 0);
    }
}

// Рекурсивна функція для обчислення суми та кількості елементів
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
    srand((unsigned)time(NULL));  // Ініціалізація генератора випадкових чисел
    const int Low = 18;           // Нижня межа значень елементів
    const int High = 74;          // Верхня межа значень елементів
    const int rowCount = 9;       // Кількість рядків
    const int colCount = 6;       // Кількість стовпців

    // Виділення пам'яті для матриці
    int** matrix = new int* [rowCount];
    for (int i = 0; i < rowCount; i++) {
        matrix[i] = new int[colCount];
    }

    // Створення та виведення початкової матриці
    CreateMatrix(matrix, rowCount, colCount, Low, High);
    cout << "Original matrix:" << endl;
    PrintMatrix(matrix, rowCount, colCount);

    // Сортування матриці
    SortMatrix(matrix, rowCount, colCount);
    cout << "\nSorted matrix:" << endl;
    PrintMatrix(matrix, rowCount, colCount);

    // Обчислення кількості та суми елементів, що відповідають критерію
    int count = 0, sum = 0;
    CalculateAndReplace(matrix, rowCount, colCount, count, sum);
    cout << "\nModified matrix with zeros (elements satisfying the condition were replaced with 0):" << endl;
    PrintMatrix(matrix, rowCount, colCount);

    // Виведення результату
    cout << "\nCount of elements satisfying the condition: " << count << endl;
    cout << "Sum of elements satisfying the condition: " << sum << endl;

    // Звільнення пам'яті
    for (int i = 0; i < rowCount; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
