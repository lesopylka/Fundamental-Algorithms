// Напишите функцию, которая находит корень уравнения методом дихотомии. 
// Аргументами функции являются границы интервала, на котором находится корень и точность, 
// с которой корень необходимо найти. Уравнение задается программно.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double answer(double( * func)(double), double begin, double end, int accuracy) {
  double result = 0.0;
  double eps = pow(10, -accuracy);

  do {
    result = (begin + end) / 2;
    if (func(result) * func(begin) <= eps) end = result;
    else begin = result;
  } while (fabs(begin - end) >= eps);
  return result;
}

double function (double x) {
  return x - sin(x) - 1;
}

int main() {
  printf("%.10lf\n", answer(function, (double) - 10, (double) 10, 3));
  return 0;
}