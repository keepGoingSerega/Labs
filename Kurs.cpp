#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Глобальные переменные
vector<vector<double>> A; // Имитация матрицы через двойные векторы
vector<vector<double>> B;
vector<vector<double>> C;
int n = 0; // Храним размерность наших матриц

// Функция для безопасного ввода числа (защита от ввода текста)
double inputCheck() {
    double value;
    while (!(cin >> value)) {
        cout << "Ошибка! Введите число: ";
        cin.clear();
        while (cin.get() != '\n') continue;
    }
    return value;
}

// Создание матриц
void allocateMemory() {
    A.resize(n, vector<double>(n)); // выделение памяти и инициализацию трех матриц A, B и C
    B.resize(n, vector<double>(n));
    C.resize(n, vector<double>(n, 0.0));// C заполняем нулями
    cout << "Матрица C заполнена нулями" << endl;
}

// Ввод матрицы с клавиатуры
void inputMatrix(vector<vector<double>>& matrix, const string& name) {
    cout << "Ввод матрицы " << name << ":" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << name << "[" << i << "][" << j << "] = ";
            matrix[i][j] = inputCheck();
        }
    }
}

// Вывод матрицы на экран
void printMatrix(const vector<vector<double>>& matrix, const string& name) {
    cout << "Матрица " << name << ":" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Редактирование элемента матрицы
void editMatrixElement(vector<vector<double>>& matrix, const string& name) {
    int row, col;
    cout << "Редактирование матрицы " << name << endl;
    
    // Ввод и проверка номера строки
    cout << "Введите номер строки (0-" << n-1 << "): ";
    row = inputCheck();
    while (row < 0 || row >= n) {
        cout << "Ошибка! Номер строки должен быть от 0 до " << n-1 << ". Введите заново: ";
        row = inputCheck();
    }
    
    // Ввод и проверка номера столбца
    cout << "Введите номер столбца (0-" << n-1 << "): ";
    col = inputCheck();
    while (col < 0 || col >= n) {
        cout << "Ошибка! Номер столбца должен быть от 0 до " << n-1 << ". Введите заново: ";
        col = inputCheck();
    }
    
    cout << "Текущее значение " << name << "[" << row << "][" << col << "] = " << matrix[row][col] << endl;
    cout << "Введите новое значение: ";
    matrix[row][col] = inputCheck();
    cout << "Элемент успешно изменен!" << endl;
}

// Вычисление среднего арифметического
double calculateAverage(const vector<vector<double>>& matrix) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += matrix[i][j];
        }
    }
    return sum / (n * n);
}

// Подсчет элементов столбца, превышающих среднее
int countAboveAverage(const vector<vector<double>>& matrix, int col, double average) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (matrix[i][col] > average) {
            count++;
        }
    }
    return count;
}

// Основная функция задания №25
void executeTask() {
    cout << "Выполнение задания №25..." << endl;
    
    double avgA = calculateAverage(A);
    double avgB = calculateAverage(B);
    
    cout << "Среднее матрицы A: " << avgA << endl;
    cout << "Среднее матрицы B: " << avgB << endl;
    
    for (int j = 0; j < n; j++) {
        int countA = countAboveAverage(A, j, avgA);
        int countB = countAboveAverage(B, j, avgB);
        
        if (countA >= countB) {
            for (int i = 0; i < n; i++) {
                C[i][j] = A[i][j];
            }
            cout << "Столбец " << j << " взят из A (" << countA << " > " << countB << ")" << endl;
        } else {
            for (int i = 0; i < n; i++) {
                C[i][j] = B[i][j];
            }
            cout << "Столбец " << j << " взят из B (" << countB << " > " << countA << ")" << endl;
        }
    }
    
    cout << "Задание выполнено!" << endl;
    printMatrix(C, "C");
}

// Сохранение матрицы в файл
void saveToFile(const vector<vector<double>>& matrix, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Ошибка сохранения!" << endl;
        return;
    }
    
    file << n << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file << matrix[i][j] << " ";
        }
        file << endl;
    }
    file.close();
    cout << "Сохранено в " << filename << endl;
}

// Загрузка матрицы из файла
void loadFromFile(vector<vector<double>>& matrix, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Ошибка загрузки!" << endl;
        return;
    }
    
    int size;
    file >> size;
    
    if (size != n) {
        cout << "Неверный размер в файле!" << endl;
        return;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> matrix[i][j];
        }
    }
    file.close();
    cout << "Загружено из " << filename << endl;
}

// Сохранение всех матриц в один файл
void saveAllToSingleFile() {
    string filename;
    cout << "Введите имя файла для сохранения всех матриц: ";
    cin >> filename;
    
    ofstream file(filename);
    if (!file) {
        cout << "Ошибка сохранения!" << endl;
        return;
    }
    
    // Сохраняем размер матриц
    file << n << endl;
    
    // Сохраняем матрицу A
    file << "MATRIX_A" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file << A[i][j] << " ";
        }
        file << endl;
    }
    
    // Сохраняем матрицу B
    file << "MATRIX_B" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file << B[i][j] << " ";
        }
        file << endl;
    }
    
    // Сохраняем матрицу C
    file << "MATRIX_C" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file << C[i][j] << " ";
        }
        file << endl;
    }
    
    file.close();
    cout << "Все матрицы сохранены в " << filename << endl;
}

// Сохранение всех матриц в отдельные файлы
void saveAllToSeparateFiles() {
    saveToFile(A, "matrixA.txt");
    saveToFile(B, "matrixB.txt");
    saveToFile(C, "matrixC.txt");
    cout << "Все матрицы сохранены в отдельные файлы, названия были заданы автоматически" << endl;
}

// Сохранение отдельных матриц
void saveIndividualMatrix() {
    int matrixChoice;
    cout << "\nКакую матрицу сохранить?" << endl;
    cout << "1. Матрицу A" << endl;
    cout << "2. Матрицу B" << endl;
    cout << "3. Матрицу C" << endl;
    cout << "Выберите матрицу: ";
    matrixChoice = inputCheck();
    
    string filename;
    cout << "Введите имя файла для сохранения: ";
    cin >> filename;
    
    switch (matrixChoice) {
        case 1: saveToFile(A, filename); break;
        case 2: saveToFile(B, filename); break;
        case 3: saveToFile(C, filename); break;
        default: cout << "Неверный выбор матрицы!" << endl;
    }
}

// Объединенная функция сохранения матриц
void saveMatrices() {
    if (n == 0) {
        cout << "Нет данных для сохранения!" << endl;
        return;
    }
    
    int saveChoice;
    cout << "\n===СОХРАНЕНИЕ МАТРИЦ===" << endl;
    cout << "1. Сохранить все матрицы в один файл" << endl;
    cout << "2. Сохранить все матрицы в отдельные файлы" << endl;
    cout << "3. Сохранить отдельную матрицу" << endl;
    cout << "Выберите режим сохранения: ";
    saveChoice = inputCheck();
    
    switch (saveChoice) {
        case 1:
            saveAllToSingleFile();
            break;
        case 2:
            saveAllToSeparateFiles();
            break;
        case 3:
            saveIndividualMatrix();
            break;
        default:
            cout << "Неверный выбор!" << endl;
    }
}

// Меню
void showMenu() {
    cout << "\n===МЕНЮ=========================" << endl;
    cout << "1. Задать размер матриц" << endl;
    cout << "2. Ввести матрицы A и B" << endl;
    cout << "3. Показать матрицы" << endl;
    cout << "4. Редактировать матрицу A" << endl;
    cout << "5. Редактировать матрицу B" << endl;
    cout << "6. Выполнить задание(Собрать C)" << endl;
    cout << "7. Сохранить матрицы" << endl;
    cout << "8. Загрузить матрицы из файлов" << endl;
    cout << "0. Выход" << endl;
    cout << "================================" << endl;
    cout << "Выберите действие: ";
}

int main() {
    int choice;
    do {
        showMenu();
        choice = inputCheck();
        
        switch (choice) {
            case 1: {
                cout << "Введите размер матриц: ";
                n = inputCheck();
                while (n < 2) {
                    cout << "Ошибка! Размерность должна быть больше или равна 2. Введите новое значение: ";
                    n = inputCheck();
                }
                allocateMemory();
                break;
            }
            case 2: {
                if (n == 0) {
                    cout << "Сначала задайте размер матриц!" << endl;
                    break;
                }
                inputMatrix(A, "A");
                inputMatrix(B, "B");
                break;
            }
            case 3: {
                if (n == 0) {
                    cout << "Матрицы не созданы!" << endl;
                    break;
                }
                printMatrix(A, "A");
                printMatrix(B, "B");
                printMatrix(C, "C");
                break;
            }
            case 4: editMatrixElement(A, "A"); break;
            case 5: editMatrixElement(B, "B"); break;
            case 6: {
                if (n == 0) {
                    cout << "Сначала создайте матрицы!" << endl;
                    break;
                }
                executeTask();
                break;
            }
            case 7: saveMatrices(); break;
            case 8: {
                if (n == 0) {
                    cout << "Сначала задайте размер матриц!" << endl;
                    break;
                }
                string filenameA, filenameB;
                cout << "Укажите имя файла для матрицы A: ";
                cin >> filenameA;
                loadFromFile(A, filenameA);
                cout << "Укажите имя файла для матрицы B: ";
                cin >> filenameB;
                loadFromFile(B, filenameB);
                break;
            }
            case 0: cout << "Выход..." << endl; break;
            default: cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);
    
    return 0;
}