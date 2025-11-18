#include <iostream>

// Функция для вывода массива через запятую
void printNumbers(int numbers[], int count) {
    for (int i = 0; i < count; i++) {
        std::cout << numbers[i];
        if (i < count - 1) {
            std::cout << "; ";
        }
    }
}

// Среднее арифметическое
double avg(int numbers[], int count) {
    if (count == 0) {
        exit(1);
    }
    int sum = 0;
    // Цикл for для подсчета суммы
    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }
    return double(sum) / count;
}

// Разница между максимальным и минимальным значением
short int findRange(int numbers[], int count) {
    int min = numbers[0];
    int max = min;
    
    // Цикл for для поиска минимума и максимума
    for (int i = 1; i < count; i++) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }
    
    return max - min;
}
// кратные пяти
short int MultiplesOfFive(int numbers[], int count) {
    int count2 = 0;

    // Цикл for для проверки каждого числа
    for (int i = 0; i < count; i++) {
        if (numbers[i] > 0 && numbers[i] % 5 == 0) {
            count2++;
        }
    }
    
    return count2;
}
    
// Является ли число степенью двойки
bool isPowerOfTwo(int n) {
    if (n <= 0) return false;
    return (n & (n - 1)) == 0; // Битовая проверка степени двойки
}

// Функция для нахождения количества чисел, превышающих сумму двух предшествующих чисел
short int SumOfPrevious(int numbers[], int count) {
    int counter = 0;
    
    // Цикл for, начиная с третьего элемента (индекс 2)
    for (int i = 2; i < count; i++) {
        int sumOfPrevious = numbers[i-1] + numbers[i-2];
        if (numbers[i] > sumOfPrevious) {
            counter++;
        }
    }
    
    return counter;
}

int main() {
    setlocale(0, "");
    int numbers[1000];
    int num;
    int count = 0;
    int powerOfTwoCount = 0;
    std::cout << "Вводите числа (0 для завершения):" << std::endl;
    
    while (true) {
        std::cout << "Введите число: ";
        std::cin >> num;
        
        if (num == 0) {
            break; 
        }
    
        numbers[count] = num; // Сохраняем число в массив
        count++;

        // считаем кол-во степеней двойки
        if (isPowerOfTwo(num)) {
            powerOfTwoCount++;
        } 
    }

    double average = avg(numbers, count);
    short int range = findRange(numbers, count);
    short int positiveMultiplesOfFive = MultiplesOfFive(numbers, count);
    short int exceedingSumCount = SumOfPrevious(numbers, count);
    std::cout << "Введенные числа: {"; printNumbers(numbers, count); std::cout << "}" << std::endl;
    std::cout << "Среднее арифметическое: " << average << std::endl;
    std::cout << "Разница между максимумом и минимумом: " << range << std::endl;
    std::cout << "Положительных чисел, кратных 5: " << positiveMultiplesOfFive << std::endl;
    std::cout << "Степеней двойки: " << powerOfTwoCount << std::endl;
    std::cout << "Чисел, превышающих сумму двух предыдущих: " << exceedingSumCount << std::endl;
    return 0;
}
