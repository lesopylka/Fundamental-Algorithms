#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

const double EPS = 1.0E-7;

bool is_flag(const char * arg_flag) {
  return strlen(arg_flag) == 2 &&
    (arg_flag[0] == '-' || arg_flag[0] == '/') &&
    (arg_flag[1] == 'q' || arg_flag[1] == 'm' || arg_flag[1] == 't');
}

bool is_number(const char * arg) {
  int len = strlen(arg);
  if (len == 1 && arg[0] == '-') {
    return false;
  }

  for (int i = 1; i < len; ++i) {
    if (!isdigit(arg[i])) {
      return false;
    }
  }

  if (isdigit(arg[0]) || arg[0] == '-')
    return true;

  return false;
}

int isnum(char c) {
    return (c > 47 && c < 58)? 1 : 0;
}

int issign(char c) {
    return (c == '+' || c == '-')? 1 : 0;
}

double dicriminant(double a, double b, double c) {
    return (b * b - 4 * a * c);
}

int myatoi(char * s) {
  int sign = 1;
  int i = 0;
  long int ret = 0;

  while (s[i] == ' ') {
    ++i;
  }

  if (issign(s[i])) {
    if (s[i] == '-') {
      sign = -1;
    }
    if (issign(s[i + 1])) {
      return 0;
    }
    ++i;
  }
  while (s[i] == '0') {
    ++i;
  }
  while (isnum(s[i])) {
    ret *= 10;
    ret += s[i] - '0';
    if (ret <= 0 || ret > __INT_MAX__) {
      return (sign > 0) ? 2147483647 : -2147483648;
    }
    ++i;
  }
  return (ret * sign);
}

int IntToString(int x, char str[], int d){ // возвращает индекс символа конца строки
  int i = 0;
  while (x) {
      str[i++] = (x % 10) + '0';
      x = x / 10;
  }
  while (i < d)
      str[i++] = '0';
  reverse(str, i);
  str[i] = '\0';
  return i;
}

int myftoa(double n, char* res, int after_point){ // возвращает индекс символа конца строки
  int i_part = (int)n;
  double f_part = n - (double)i_part;
  int i = intToStr(i_part, res, 0);
  if (after_point != 0) {
      res[i] = '.';
      f_part = f_part * pow(10, after_point);
      intToStr((int)f_part, res + i + 1, after_point);
  }
  return i;
}

int number_of_parameters(char c) {
  if (c == 'q' || c == 't')
    return 3;
  if (c == 'm')
    return 2;
  return 0;
}

int toggles_q(double a, double b, double c) {
  double d;
  printf("For the: (%.3lf) * x^2 + (%.3lf) * x + (%.3lf) = 0\n", a, b, c);
  if (fabs(a - 0) <= EPS) {
    printf("The number 'a' is not a parameter of the quadratic equation, because it should not be equal to 0\n\n");
  } else {
    d = dicriminant(a, b, c);
    if (d < 0 - EPS) {
      printf("No roots.\n");
    } else if (fabs(d - 0) <= EPS) {
      printf("x = %lf\n", (-b + sqrt(d)) / (2 * a));
    } else {
      printf("x1 = %lf\n", (-b + sqrt(d)) / (2 * a));
      printf("x2 = %lf\n", (-b - sqrt(d)) / (2 * a));
    }
    printf("\n");
  }
  return 0;
}

bool toggles_m(int i, int k) {
  if (!i || !k) {
    return false;
  }
  return i % k == 0;
}

bool toggles_t(float a, float b, float c) {
  if (a > 0 && b > 0 && c > 0)
    return fabs((a * a + b * b) - (c * c)) <= EPS ||
           fabs((a * a + c * c) - (b * b)) <= EPS ||
           fabs((b * b + c * c) - (a * a)) <= EPS;
  else 
    printf("Something went wrong\n");
    return 0;
}

char* main(int argc, char ** argv) {
  // типы возвр значений
  // true, false под false ещё ошибка может быть
  // x, x1 x2
  // наш протокол
  // флаги:
  //    -e это ошибка, текст ошибки
  //    -a это ответ флоат, количество ответов, ответ/ы
  //    -b ответ тру или фалсе
  if(!is_flag(argv[1])){
    char* message = "-e Inappropriate flag position\n";
    return message;
  }
  if(!argc - 1 == number_of_parameters(argv[1][1])){
    char* message = "-e Inappropriate parameters count\n";
    return message;
  }

  switch (argv[1][1]) {
    case 'q':
      double x1 = 0, x2 = 0;
      int answ = toggles_q(atof(argv[2]), atof(argv[3]), atof(argv[4]));
      if (answ == 0) {
        char* message = "-e With the entered coefficients does not exist\n";
        return message;
      } else if (answ == 1) {
        char message[100];
        strcpy(message, "-a 1 ");
        char* ans;
        myftoa(x1, ans, 2);
        strcat(message, ans);
        return message;
      } else if (answ == 2) {
        char message[100];
        strcpy(message, "-a 2 ");
        char* ans1;
        myftoa(x1, ans1, 2);
        char* ans2;
        myftoa(x2, ans2, 2);
        strcat(message, ans1);
        strcat(message, ans2);
        return message;
        printf("%f  %f\n", x1, x2);
      }
      break;
    case 'm':
      if (toggles_m(myatoi(argv[2]), myatoi(argv[3]))){
        char* message = "-b true\n";
        return message;
          }
      else {

        char* message = "-b false\n";
        return message;
      break;
      }
    case 't':
      if (toggles_t(atof(argv[2]), atof(argv[3]), atof(argv[4]))){
        char* message = "-b true\n";
        return message;
      } 
      else if (atof(argv[2]) > 0 && atof(argv[3]) > 0 && atof(argv[4]) > 0) {
        char* message = "-b false\n";
        return message;
      }
      break;
}

// принтф плохо
// сравнение вещественных чисел переделывай
// везде где тупо ==
// надо сделать сравнение модуля разности чисел со значением эпсилон, которое было бы круто как параметр функции приделать
// через == сравнивать нельзя