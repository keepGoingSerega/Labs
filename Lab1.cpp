#include <iostream>

// Координаты вершин прямоугольного треугольника (гипотенуза на y=x)
const double Ax = 0.0, Ay = 0.0;
const double Bx = 10.0, By = 0.0;
const double Cx = 10.0, Cy = 10.0;

// площадь треугольника
double calculateArea(double x1, double y1, double x2, double y2, double x3, double y3) {
  return 0.5 * std::abs((x2-x1)*(y3-y1) - (x3-x1)*(y2-y1));
}

// Проверка, лежит ли точка (x, y) внутри ABC
bool isInside(double x, double y) {
  // ABC
  double S = calculateArea(Ax, Ay, Bx, By, Cx, Cy);
  
  // Вычисляем площади трех треугольников, образованных точкой (x,y) с вершинами
  double S1 = calculateArea(x, y, Bx, By, Cx, Cy);
  double S2 = calculateArea(Ax, Ay, x, y, Cx, Cy);
  double S3 = calculateArea(Ax, Ay, Bx, By, x, y);
  std::cout << S << std::endl;
  std::cout << S1+S2+S3 << std::endl;
  return std::abs(S - (S1 + S2 + S3)) < 1e-10;
  
}

int main() {
  std::cout << "Введите координаты точек (x y), для завершения введите 0 0:\n";
  double x, y;
  while (true) {
    std::cin >> x >> y;
    if (x == 0.0 && y == 0.0) break;
    if (isInside(x, y)) {
      std::cout << "Точка (" << x << ", " << y << ") попала в треугольник.\n";
    } else {
      std::cout << "Точка (" << x << ", " << y << ") не попала в треугольник.\n";
    }
  }
  return 0;
}