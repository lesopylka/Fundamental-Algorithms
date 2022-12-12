#include <stdio.h>
#include <stdarg.h>
#include <math.h>

//лекция 22 сентября

double geometric_mean(int n, ...) {
  double result = 1;
  va_list factor;
  va_start(factor, n);
  for (int i = 0; i < n; i++)
    result *= pow(va_arg(factor, double), 1. / n);  
  va_end(factor);
  return result;
}

double exponentiation(double a, int n) { //медленно
  if (n == 0) return 1;
  else if (n > 0) return exponentiation(a, n - 1) * a;
  else return exponentiation(a, n + 1) * (1. / a); //exp
}

int main(void) {
  printf("%lf\n", geometric_mean(4, 2.6, 1.5, 4.4, 5.8)); 
  printf("%.8lf\n", exponentiation(3, -3));

}