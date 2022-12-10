// Напишите функции, вычисляющее значения чисел
// 𝑒, π, ln 𝑙𝑛 2 , 2, γ с точностью 𝑙 знаков после запятой. 
// Для каждой константы реализовать три способа вычисления: например,
// как сумму ряда, как решение специального уравнения, как значение предела.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

long double fabs(long double x) {
  return x > 0 ? x : -x;
}

long double limit(long double lim(int n), double eps) {
  int i = 1 / eps / eps, step = 1 / eps;
  long double res = 0, prevRes = 0;
  eps *= eps;

  while (fabs(res - prevRes) > eps || prevRes == 0) {
    prevRes = res;
    res = lim(i += step);
  }

  return res;
}

long double sum(long double
  function (int n), double eps, int start) {
  long double res = 0, prevRes = 0;
  for (int k = start;
    (fabs(res - prevRes) > eps || fabs(prevRes) < eps || (res - prevRes == 0)); k++) {
    prevRes = res;
    res += function (k);
  }
  return res;
}

long double mult(long double
  function (int n), double eps, int start) {
  long double res = 1, prevRes = 0, eps_func = eps / 10;
  for (int k = start; fabs(prevRes - res) > eps_func || fabs(prevRes) < eps; k++) {
    prevRes = res;
    res *= function (k);
  }
  return res;
}

long double factorial(int num) {
  if (num == 0) {
    return 1;
  }
  int res = 1;
  while (num > 0) {
    res *= num;
    num--;
  }
  return res;
}

long double eLim(int n) {
  return pow(1 + 1.0 / n, n);
}

long double piLim(int n) {
  int tmp = n;
  long double res = 1;
  while (tmp) {
    res *= 4.0 * tmp * tmp / (2 * tmp) / (2 * tmp - 1);
    tmp--;
  }
  res /= sqrt(n);
  return res *= res;
}

long double ln2Lim(int n) {
  return n * (pow(2, 1.0 / n) - 1);
}

long double sqrt2Lim(double eps) {
  int i = 0, j;
  long double res = -0.5, prevRes = 0;
  eps *= eps;

  while (fabs(res - prevRes) > eps || prevRes == 0) {
    prevRes = res;
    res = res - ((res * res) / 2) + 1;
  }

  return res;
}

long double eRow(int n) {
  return 1.0 / factorial(n);
}

long double piRow(int n) {
  return 4 * pow(-1.0, n - 1) / (2.0 * n - 1);
}

long double ln2Row(int n) {
  return pow(-1.0, n - 1) / n;
}

long double sqrt2Mult(int k) {
  return pow(2, pow(2, -k));
}

long double gammaRow(double eps, int start) {
  long double res = 0, eps_func = 1e-15, prevRes = 0, func_returned = 0;

  for (int k = start;
    (fabs(res - prevRes) > eps_func || fabs(prevRes) < eps || (res - prevRes == 0)); k++) {
    prevRes = res;
    func_returned = 1.0 / pow(floor(sqrt(k)), 2) - 1.0 / k;
    res += func_returned;
  }
  return res;
}

double equationDichotomy(double equation(double x), double a, double b, double eps) {
  double functResult_middle;
  while (fabs(a - b) > eps) {
    functResult_middle = equation((a + b) / 2);
    if (equation(a) * functResult_middle > 0) {
      a = (a + b) / 2;
    }

    if (equation(b) * functResult_middle > 0) {
      b = (a + b) / 2;
    }
  }
  return (a + b) / 2;
}

double eEquation(double x) {
  return log(x) - 1;
}

double piEquation(double x) {
  return -sin(x);
}

double ln2Equation(double x) {
  return pow(M_E, x) - 2;
}

double sqrt2Equation(double x) {
  return x * x - 2;
}

void simpleNumsGenerate(long ** simpleNums, unsigned long long toGenerate, unsigned long long * generated) {
  int count = 0;
  long * tmp = NULL, i, j, * arraySieve = NULL;

  if (!(arraySieve = (long * ) calloc((toGenerate + 1), sizeof(long)))) {
    return;
  }

  for (int i = 2; i <= toGenerate; i++) {
    if (!arraySieve[i]) {
      count++;
      for (int j = i + i; j <= toGenerate; j += i) {
        arraySieve[j] = 1;
      }
    }
  }

  if (( * simpleNums == NULL || ( * generated) == 0)) {
    if (!(( * simpleNums) = (long * ) calloc(count, sizeof(long)))) {
      return;
    }
  } else {
    if (!(tmp = (long * ) realloc(( * simpleNums), sizeof(long) * (count + ( * generated))))) {
      free( * simpleNums);
      return;
    }
    ( * simpleNums) = tmp;
  }

  i = (!( * generated) ? 2 : ( * simpleNums)[( * generated) - 1] + 1);
  for (int i = 0; i <= toGenerate; i++) {
    if (!arraySieve[i]) {
      ( * simpleNums)[( * generated) ++] = i;
    }
  }

  free(arraySieve);

}

double eulerEquation(double eps) {
  double result = 1, prevResult = 0;
  int step = 1. / eps / 100;
  long * simpleNums = NULL;
  unsigned long long t = 1.0 / eps / eps, generated = 0, i;
  eps /= 1000;

  for (int t = 0; fabs(result - prevResult) > eps; t += step) {
    prevResult = result;
    result = 1;
    simpleNumsGenerate( & simpleNums, t, & generated);
    for (int i = 0; i < generated; i++) {
      result *= (double)(simpleNums[i] - 1) / simpleNums[i];
    }
    result *= log(t);
    result = -log(result);
  }

  free(simpleNums);
  return result;
}

void pascalTableGenerate(unsigned long long ** * table, int * generated, int toGenerate) {
  unsigned long long ** tmpTable = NULL, * tmpString = NULL;
  if (!( * generated)) {
    if (!(( ** table) = (unsigned long long * ) malloc(sizeof(unsigned long long)))) {
      return;
    }
    ( * table)[0][0] = 1;
    ( * generated) ++;
  }

  // gen enough strings
  if (!(tmpTable = (unsigned long long ** ) realloc(( * table), sizeof(unsigned long long * ) * (toGenerate + 1)))) {
    return;
  }
  ( * table) = tmpTable;

  int str, col, stringItemsCount;
  for (str = ( * generated); str < toGenerate + 1; str++) {
    // gen array (string) with enough memory for items
    stringItemsCount = str + 1;
    if (!(( * table)[str] = (unsigned long long * ) malloc(sizeof(unsigned long long) * stringItemsCount))) {
      return;
    }

    for (col = 0; col <= str; col++) {
      if (col == 0 || col == str) {
        ( * table)[str][col] = 1;
      } else {
        ( * table)[str][col] = ( * table)[str - 1][col - 1] + ( * table)[str - 1][col];
      }
    }
  }
  ( * generated) = str;
}

long double eulerLim(double eps) {
  unsigned long long ** pascalTable = NULL;
  if (!(pascalTable = (unsigned long long ** ) calloc(1, sizeof(long * )))) {
    return NAN;
  }

  int k, m = 32, i = 0, generatedStrings = 0;
  long double partialSum = 1, logSum = 0, res = 0, prevRes = 0;
  eps /= 100;

  while (fabs(prevRes - res) > eps || fabs(prevRes - res) == 0) {
    prevRes = res;
    res = 0;
    logSum = 0;
    partialSum = 1;

    pascalTableGenerate( & pascalTable, & generatedStrings, m);

    for (int k = 1; k <= m; k++) {
      partialSum *= (long double) pascalTable[m][k] / k;
      partialSum *= (long double)(k & 1 ? -1 : 1);

      logSum += log(k);

      res += logSum * partialSum;
      partialSum = 1;
    }
    m++;
  }

  for (int i = 0; i < generatedStrings; i++) {
    free(pascalTable[i]);
  }
  free(pascalTable);

  return res;
}

int main(void) {
  int l;
  double eps = pow(10, -l);
  printf("enter precision: ");
  scanf("%d", & l);
  l++;

  printf("e constant:\n");
  printf("\tas limit value: %.*Lf\n", l, limit(eLim, eps));
  printf("\tas row sum: %.*Lf\n", l, sum(eRow, eps, 0));
  printf("\tas solution of an equation: %.*lf\n", l, equationDichotomy(eEquation, 2., 3., eps));

  printf("pi constant:\n");
  printf("\tas limit value: %.*Lf\n", l, limit(piLim, eps));
  printf("\tas row sum: %.*Lf\n", l, sum(piRow, eps, 1));
  printf("\tas solution of an equation: %.*lf\n", l, equationDichotomy(piEquation, 3, 3.5, eps));

  printf("ln(2) constant:\n");
  printf("\tas limit value: %.*Lf\n", l, limit(ln2Lim, eps));
  printf("\tas row sum: %.*Lf\n", l, sum(ln2Row, eps, 1));
  printf("\tas solution of an equation: %.*lf\n", l, equationDichotomy(ln2Equation, 0, 1, eps));

  printf("sqrt(2) constant:\n");
  printf("\tas limit value: %.*Lf\n", l, sqrt2Lim(eps));
  printf("\tas row product: %.*Lf\n", l, mult(sqrt2Mult, eps, 2));
  printf("\tas solution of an equation: %.*lf\n", l, equationDichotomy(sqrt2Equation, 1, 2, eps));

  printf("Euler's constant:\n");
  printf("\tas limit value: %.*Lf\n", l, eulerLim(eps));
  double constant_pi = M_PI * M_PI / 6;
  printf("\tas row sum: %.*Lf\n", l, gammaRow(eps, 2) - constant_pi);
  printf("\tas solution of an equation: %.*lf\n", l, eulerEquation(eps));

  return 0;
}