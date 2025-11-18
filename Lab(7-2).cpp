#include <iostream>

using namespace std;

const int ROWS_A = 3; 
const int COLS_A = ROWS_A; 
const int ROWS_B = ROWS_A; 
const int COLS_B = COLS_A;

// Вывод матрицы
void printMatrix(int* matrix, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << *(matrix + i * cols + j) << " ";
    }
    cout << "\n";
  }
}

// Перемножение матриц
void multiplyMatrices(int A[ROWS_A][COLS_A], int B[ROWS_B][COLS_B], int C[ROWS_A][COLS_B]) {
  for (int i = 0; i < ROWS_A; i++) {
    for (int j = 0; j < COLS_B; j++) {
      C[i][j] = 0;
      for (int k = 0; k < COLS_A; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

// Возведение в степень
void matrixPower(int matrix[ROWS_A][COLS_A], int result[ROWS_A][COLS_A], int power) {
  // Если степень 0 - возвращаем единичную матрицу
  if (power == 0) {
    for (int i = 0; i < ROWS_A; i++) {
      for (int j = 0; j < COLS_A; j++) {
        result[i][j] = (i == j) ? 1 : 0;
      }
    }
    return;
  }
  
  // Если степень 1 - просто копируем матрицу
  if (power == 1) {
    for (int i = 0; i < ROWS_A; i++) {
      for (int j = 0; j < COLS_A; j++) {
        result[i][j] = matrix[i][j];
      }
    }
    return;
  }
  
  // Для степеней больше 1 - умножаем матрицу саму на себя power раз
  int temp[ROWS_A][COLS_A];
  
  // Начинаем с исходной матрицы
  for (int i = 0; i < ROWS_A; i++) {
    for (int j = 0; j < COLS_A; j++) {
      result[i][j] = matrix[i][j];
    }
  }
  
  // Умножаем power раз
  for (int p = 1; p < power; p++) {
    for (int i = 0; i < ROWS_A; i++) {
      for (int j = 0; j < COLS_A; j++) {
        temp[i][j] = result[i][j];
      }
    }
    // Умножаем temp на исходную матрицу
    multiplyMatrices(temp, matrix, result);
  }
}

int main() {
  int A[ROWS_A][COLS_A];
  int B[ROWS_B][COLS_B];
  int C[ROWS_A][COLS_B];
  int D[ROWS_A][COLS_A]; // Для результата возведения в степень

  // Матрица A
  cout << "Введите матрицу A (" << ROWS_A << "x" << COLS_A << "):\n";
  for (int i = 0; i < ROWS_A; i++) {
    for (int j = 0; j < COLS_A; j++) {
      cin >> A[i][j];
    }
  }

  // Матрица B
  cout << "Введите матрицу B (" << ROWS_B << "x" << COLS_B << "):\n";
  for (int i = 0; i < ROWS_B; i++) {
    for (int j = 0; j < COLS_B; j++) {
      cin >> B[i][j];
    }
  }

  cout << "\nМатрица A:\n";
  printMatrix((int*)A, ROWS_A, COLS_A);
  
  cout << "\nМатрица B:\n";
  printMatrix((int*)B, ROWS_B, COLS_B);

  multiplyMatrices(A, B, C);

  // Вывод результата перемножения
  cout << "\nРезультат A*B = С:\n";
  printMatrix((int*)C, ROWS_A, COLS_B);

  // Возведение матрицы C в степень
  int power;
  cout << "\nВ какую степень возвести матрицу C?: ";
  cin >> power;
  
  matrixPower(C, D, power);
  
  cout << "\nМатрица C возведена в степень:" << power << ":\n";
  printMatrix((int*)D, ROWS_A, COLS_A);

  return 0;
}