#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    double xBegin, xEnd, dx, a, b, c;
    
    cout << "Введите начало и конец интервала: ";
    cin >> xBegin >> xEnd;
    cout << "Введите шаг: ";
    cin >> dx;
    cout << "Введите a b c: ";
    cin >> a >> b >> c;

    // целые части 
    int A_int = (int)a;  
    int B_int = (int)b;  
    int C_int = (int)c;  

    bool shouldBeReal = ((A_int | B_int) & (A_int | C_int)) != 0;

    //заголовок таблицы
    cout << "\n" << string(25, '=') << endl;
    cout << "|" << setw(10) << "x" << " |" << setw(10) << "F(x)" << " |" << endl;
    cout << string(25, '=') << endl;

    for(double x = xBegin; x <= xEnd; x += dx) {
        double result = 0;
        
        if(x < 0 && b != 0)
            result = a * x * x + b;
        else if(x > 0 && b == 0)
            result = (x - a) / (x - c);
        else
            result = x / c;
            
        cout << "|" << setw(10) << fixed << setprecision(3) << x << " |";
        
        // Проверяем тип результата согласно условию
        if(shouldBeReal) {
            // Должен быть действительным - выводим как есть
            cout << setw(10) << result << " |";
        } else {
            // Должен быть целым - приводим к int
            cout << setw(10) << (int)result << " |";
        }
        cout << endl;
    }
    
    cout << string(25, '=') << endl;
    
    return 0;
}