#include <stdio.h>
#include <stdarg.h>
#include <math.h>

//лекция 22 сентября

double geometric_mean(int n, ...) {
  double result = 1;
  va_list factor;
  va_start(factor, n);
  for (int i = 0; i < n; i++) {
    result *= va_arg(factor, double);
  }
  va_end(factor);
  return sqrt(result);
}

double exponentiation(double a, int n) {
  if (n == 0) return 1;
  else if (n > 0) return exponentiation(a, n - 1) * a;
  else return exponentiation(a, n + 1) * (1. / a);
}

int main(void) {
  printf("%lf\n", geometric_mean(4, 1.6, 2.5, 3.4, 4.8));
  printf("%.8lf\n", exponentiation(2, -2));

}