#include <iostream>

using namespace std;

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
  int rows_A, cols_A, rows_B, cols_B;
  
  // Ввод размерности матрицы A
  cout << "Введите количество строк матрицы A: ";
  cin >> rows_A;
  cout << "Введите количество столбцов матрицы A: ";
  cin >> cols_A;
  
  // Ввод размерности матрицы B
  cout << "Введите количество строк матрицы B: ";
  cin >> rows_B;
  cout << "Введите количество столбцов матрицы B: ";
  cin >> cols_B;
  
  // Проверка возможности умножения матриц
  if (cols_A != rows_B) {
    cout << "Ошибка: Умножение матриц невозможно!\n";
    cout << "Количество столбцов матрицы A должно равняться количеству строк матрицы B.\n";
    return 1;
  }
  
  // Создание динамических массивов
  int* A = new int[rows_A * cols_A];
  int* B = new int[rows_B * cols_B];
  int* C = new int[rows_A * cols_B];
  
  // матрица A
  cout << "\nВведите матрицу A(" << rows_A << "x" << cols_A << "):\n";
  for (int i = 0; i < rows_A; i++) {
    for (int j = 0; j < cols_A; j++) {
      cin >> *(A + i * cols_A + j);
    }
  }
  
  // матрица B
  cout << "\nВведите матрицу B(" << rows_B << "x" << cols_B << "):\n";
  for (int i = 0; i < rows_B; i++) {
    for (int j = 0; j < cols_B; j++) {
      cin >> *(B + i * cols_B + j);
    }
  }
  
  // Вывод введенных матриц
  cout << "\nМатрица A:\n";
  printMatrix(A, rows_A, cols_A);
  
  cout << "\nМатрица B:\n";
  printMatrix(B, rows_B, cols_B);
  
  // перемножение
  for (int i = 0; i < rows_A; i++) {
    for (int j = 0; j < cols_B; j++) {
      *(C + i * cols_B + j) = 0;
      for (int k = 0; k < cols_A; k++) {
        // A[i][k] * B[k][j]
        *(C + i * cols_B + j) += *(A + i * cols_A + k) * *(B + k * cols_B + j);
      }
    }
  }
  
  // матрица C
  cout << "\nРезультат (Матрица C):\n";
  printMatrix(C, rows_A, cols_B);
  
  delete[] A, B, C;
  
  return 0;
}