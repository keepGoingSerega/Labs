#include <iostream>

using namespace std;

const int ROWS_A = 2;
const int COLS_A = 3;
const int ROWS_B = 3;
const int COLS_B = 5;

// вывод матрицы
void printMatrix(int* matrix, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << *(matrix + i * cols + j) << " ";
    }
    cout << "\n";
  }
}

int main() {
  int A[ROWS_A][COLS_A];
  int B[ROWS_B][COLS_B];
  int C[ROWS_A][COLS_B];

  // матрица A
  cout << "Введите матрицу A(" << ROWS_A << "x" << COLS_A << "):\n";
  for (int i = 0; i < ROWS_A; i++) {
    for (int j = 0; j < COLS_A; j++) {
      cin >> A[i][j];
    }
  }

  // матрица B
  cout << "Введите матрицу Б(" << ROWS_B << "x" << COLS_B << "):\n";
  for (int i = 0; i < ROWS_B; i++) {
    for (int j = 0; j < COLS_B; j++) {
      cin >> B[i][j];
    }
  }

  // Вывод введенных матриц
  cout << "\nМатрица A:\n";
  printMatrix((int*)A, ROWS_A, COLS_A);
  
  cout << "\nМатрица Б:\n";
  printMatrix((int*)B, ROWS_B, COLS_B);

  // перемножение
  for (int i = 0; i < ROWS_A; i++) {
    for (int j = 0; j < COLS_B; j++) {
      C[i][j] = 0;
      for (int k = 0; k < COLS_A; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  // матрица c
  cout << "\nРезультат(Матрица C):\n";
  printMatrix((int*)C, ROWS_A, COLS_B);

  return 0;
}