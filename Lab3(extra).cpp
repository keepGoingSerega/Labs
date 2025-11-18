#include <iostream>

// Функция для проверки, является ли число простым
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// Функция для вычисления суммы цифр числа
int sumOfDigits(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int main() {
    int N;
    std::cout << "Введите положительное число N: ";
    std::cin >> N;
    std::cout << "Простые числа до " << N << ", сумма цифр которых тоже простое число: " << std::endl;

    int count = 0; // счетчик найденных чисел
    int current_decade = -1; // текущий десяток
    
    for (int num = 2; num <= N; num++) {
        if (isPrime(num)) {
            int digitSum = sumOfDigits(num);
            if (isPrime(digitSum)) {
                int decade = num / 10; // определяем десяток числа
                
                // Если перешли к новому десятку, начинаем новую строку
                if (decade != current_decade) {
                    if (current_decade != -1) {
                        std::cout << std::endl;
                    }
                    current_decade = decade;
                } else {
                    // Если в том же десятке, выводим пробел между числами
                    std::cout << " ";
                }
                
                std::cout << num;
                count++;
            }
        }
    }
    
    // Завершаем последнюю строку
    if (count > 0) {
        std::cout << std::endl;
    }
    
    std::cout << "Найдено " << count << " таких чисел." << std::endl;
    
    return 0;
}