#include <iostream>
using namespace std;

int main() {
    const int SIZE = 5;
    int arr1[SIZE], arr2[SIZE];
    
    // Ввод первого массива
    cout << "Введите 5 элементов первого массива: ";
    for (int i = 0; i < SIZE; i++) {
        cin >> arr1[i];
    }
    
    // Ввод второго массива
    cout << "Введите 5 элементов второго массива: ";
    for (int i = 0; i < SIZE; i++) {
        cin >> arr2[i];
    }
    
    // Вывод исходных массивов
    cout << "\nИсходные массивы:\n";
    cout << "Массив 1: ";
    for (int i = 0; i < SIZE; i++) {
        cout << arr1[i] << " ";
    }
    cout << "\nМассив 2: ";
    for (int i = 0; i < SIZE; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    
    // Перераспределение элементов
    for (int i = 0; i < SIZE; i++) {
        // Обработка первого массива
        if (arr1[i] < 0) {
            // Ищем место во втором массиве для отрицательного числа
            for (int j = 0; j < SIZE; j++) {
                if (arr2[j] >= 0) {
                    // Меняем местами
                    int temp = arr1[i];
                    arr1[i] = arr2[j];
                    arr2[j] = temp;
                    break;
                }
            }
        }
        
        // Обработка второго массива
        if (arr2[i] >= 0) {
            // Ищем место в первом массиве для неотрицательного числа
            for (int j = 0; j < SIZE; j++) {
                if (arr1[j] < 0) {
                    // Меняем местами
                    int temp = arr2[i];
                    arr2[i] = arr1[j];
                    arr1[j] = temp;
                    break;
                }
            }
        }
    }
    
    // Заполнение оставшихся позиций нулями
    for (int i = 0; i < SIZE; i++) {
        if (arr1[i] < 0) arr1[i] = 0;
        if (arr2[i] >= 0) arr2[i] = 0;
    }
    
    // Вывод результата
    cout << "\nРезультат перераспределения:\n";
    cout << "Массив 1 (положительные): ";
    for (int i = 0; i < SIZE; i++) {
        cout << arr1[i] << " ";
    }
    cout << "\nМассив 2 (отрицательные): ";
    for (int i = 0; i < SIZE; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    
    return 0;
}