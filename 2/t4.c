#include <stdio.h>
#include <stdarg.h>

double function1(int n, ...) {
  double result = 1;
  va_list factor;
  va_start(factor, n);
  for (int i = 0; i < n; i++) {
    result *= va_arg(factor, double);
  }
  va_end(factor);
  return sqrt(result);
}

double power(double a, int n) {
  if (n == 0) return 1;
  else if (n > 0) return power(a, n - 1) * a;
  else if (n < 0) return power(a, n + 1) * (1.0 / a);
}

int main(void) {
  printf("%lf\n", function1(4, 1.6, 2.5, 3.4, 4.8));
  printf("%.8lf\n", power(2, -2));

}