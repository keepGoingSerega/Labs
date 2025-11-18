#include<iostream>

using namespace std;

const int SIZE = 15;

// Ввод
void inputArray(int arr[]) {
    cout << "Заполните массив из 15 чисел:" << endl;
    for (int i = 0; i < SIZE; i++) {
        cin >> arr[i];
    }
}

// Вывод
void printArray(int arr[]) {
    cout << "Введённый массив:" << endl;
    cout << "[";
    for (int i = 0; i < SIZE; i++) {
        cout << arr[i] << " ";
    }
    cout << "\b]" << endl;

    // Первая пятерка
    cout << "Первая часть:";
    cout << "[";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << "\b]";

    // Вторая пятерка
    cout << "\tВторая часть:";
    cout << "[";
    for (int i = 5; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << "\b]";

    // Третья пятерка
    cout << "\tТретья часть:";
    cout << "[";
    for (int i = 10; i < 15; i++) {
        cout << arr[i] << " ";
    }
    cout << "\b]" << endl;
}

// Функция для поиска и вывода минимумов всех трех частей массива
void findMinInParts(int arr[]) {
    int minValues[3];
    
    // Минимум первой пятерки
    minValues[0] = arr[0];
    for (int i = 1; i < 5; i++) {
        if (arr[i] < minValues[0]) {
            minValues[0] = arr[i];
        }
    }

    cout << "Минимум первой части: " << minValues[0];

    // Минимум второй пятерки
    minValues[1] = arr[5];
    for (int i = 6; i < 10; i++) {
        if (arr[i] < minValues[1]) {
            minValues[1] = arr[i];
        }
    }

    cout << "\t\tМинимум второй части: " << minValues[1];
    
    // Минимум третьей пятерки
    minValues[2] = arr[10];
    for (int i = 11; i < 15; i++) {
        if (arr[i] < minValues[2]) {
            minValues[2] = arr[i];
        }
    }
    
    cout << "\t\tМинимум третьей части: " << minValues[2] << endl;
}

// Функция сортировки по возрастанию
void bubbleSort(int arr[]) {
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Обмен элементов
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Функция для вывода отсортированного массива
void printSortedArray(int arr[]) {
    cout << "Отсортированный массив (по возрастанию):" << endl;
    cout << "[";
    for (int i = 0; i < SIZE; i++) {
        cout << arr[i] << " ";
    }
    cout << "\b]" << endl;
}

// Функция для подсчета уникальных повторений сортированного массива
void countPairs(int arr[]) {
    int duplicateCount = 0;
    
    for (int i = 0; i < SIZE - 1; i++) {
        // Если текущий элемент равен следующему и это первое вхождение дубликата
        if (arr[i] == arr[i + 1] && (i == 0 || arr[i] != arr[i - 1])) {
            duplicateCount++;
        }
    }
    
    cout << "Количество чисел, имеющих пары: " << duplicateCount << endl;
}

// Функция для проверки, является ли число степенью двойки
bool isPowerOfTwo(int n) {
    if (n <= 0) return false;
    return (n & (n - 1)) == 0; // 4: 00000100 3: 00000011 4&3:00000000 = true
} 

// Функция для поиска всех последовательностей степеней двойки
void findPowersOfTwo(int arr[]) {
    bool found = false;
    int i = 0;
    
    while (i < SIZE - 1) {
        if (isPowerOfTwo(arr[i])) {
            int start = i;
            int length = 1;
            
            // Определяем длину последовательности
            while (i < SIZE - 1 && isPowerOfTwo(arr[i + 1]) && arr[i + 1] > arr[i]) {
                length++;
                i++;
            }
            
            // Если последовательность достаточной длины
            if (length >= 2) {
                cout << "Последовательность из " << length << " элементов: ";
                cout << "начинается с индекса " << start << " (";
                for (int k = start; k < start + length; k++) {
                    cout << arr[k];
                    if (k < start + length - 1) cout << " ";
                }
                cout << ")" << endl;
                found = true;
            }
        }
        i++;
    }
    
    if (!found) {
        cout << "Последовательностей степеней двойки не найдено" << endl;
    }
}

int main() {
    int arr[SIZE];
    inputArray(arr);
    printArray(arr);
    findMinInParts(arr);
    findPowersOfTwo(arr);
    bubbleSort(arr);
    printSortedArray(arr);
    countPairs(arr); 
}