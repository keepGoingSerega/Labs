#include <iostream>

using namespace std;

int main() {
    int N;
    cout << "Введите целое положительное число N: ";
    cin >> N;

    if (N == 1) {
        return 0;
    }
    
    // Создаем решето
    bool* isPrime = new bool[N + 1];
    for (int i = 0; i <= N; i++) {
        isPrime[i] = false;
    }
    
    // 2 и 3  простые
    if (N >= 2) isPrime[2] = true;
    if (N >= 3) isPrime[3] = true;
    
    // Квадратичные формы решета Аткина
    for (int x = 1; x * x <= N; x++) {
        int x2 = x * x;
        
        for (int y = 1; y * y <= N; y++) {
            int n = 4 * x2 + y * y;
            if (n <= N && (n % 12 == 1 || n % 12 == 5)) {
                isPrime[n] = !isPrime[n];
            }
            
            n = 3 * x2 + y * y;
            if (n <= N && n % 12 == 7) {
                isPrime[n] = !isPrime[n];
            }
            
            if (x > y) { n = 3 * x2 - y * y;
                if (n <= N && n % 12 == 11) {
                    isPrime[n] = !isPrime[n];
                }
            }
        }
    }
    
    // Удаляем квадраты простых чисел
    for (int i = 5; i * i <= N; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= N; j += i * i) {
                isPrime[j] = false;
            }
        }
    }
    
    cout << "Простые числа, не превосходящие " << N << ":" << endl;
    
    bool first = true;
    for (int i = 2; i <= N; i++) {
        if (isPrime[i]) {
            if (!first) cout << " ";
            cout << i;
            first = false;
        }
    }
    cout << endl;
    
    delete[] isPrime;
    return 0;
}