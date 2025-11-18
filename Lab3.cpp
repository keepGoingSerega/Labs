#include <iostream>

int main() {
    int N;
    std::cout << "Введите положительное число N: ";
    std::cin >> N;
    std::cout << "Простые числа до " << N << ": " << std::endl;

    for (int num = 2; num <= N; num++) {
        bool isPrime = true;
        if (num <= 1) {
            isPrime = false;
        } else if (num == 2) {
            isPrime = true;
        } else if (num % 2 == 0) {
            isPrime = false;
        } else {
            for (int i = 3; i * i <= num; i += 2) {
                if (num % i == 0) {
                    isPrime = false;
                    break;
                }
            }
        }
        if (isPrime) {
            std::cout << num << " ";
        }
        if (num % 10 == 0) {
          std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    
    return 0;
}