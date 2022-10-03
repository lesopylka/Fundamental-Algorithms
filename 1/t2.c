#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

bool is_flag(const char * arg) {
  return strlen(arg) == 2 &&
    (arg[0] == '-' || arg[0] == '/') &&
    isalpha(arg[1]);
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

int number_parameters_count(char c) {
  if (c == 'q' || c == 't')
    return 3;

  if (c == 'm')
    return 2;

  return 0;
}

int toggles_q(double a, double b, double c) {
  double d;
  printf("For the: (%.3lf) * x^2 + (%.3lf) * x + (%.3lf) = 0\n", a, b, c);
  if (a == 0) {
    printf("The number 'a' is not a parameter of the quadratic equation, because it should not be equal to 0\n\n");
  } else {
    d = dicriminant(a, b, c);
    if (d < 0) {
      printf("No roots.\n");
    } else if (d == 0) {
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
    return a * a + b * b == c * c ||
      a * a + c * c == b * b ||
      b * b + c * c == a * a;
  else
    printf("Something went wrong\n");
    return 0;
}

int main(int argc, char ** argv) {
  char flag;
  int flag_params[10];
  int param_count;
  int arg_index = 1;
  while (arg_index < argc) {
    if (is_flag(argv[arg_index])) {
      flag = argv[arg_index][1];
      ++arg_index;
    } else {
      printf("Inappropriate flag position\n");
      return 1;
    }
    if (argc - arg_index < number_parameters_count(flag)) {
      printf("Inappropriate parameters count\n");
      return 1;
    }
    param_count = number_parameters_count(flag);
    for (int i = 0; i < number_parameters_count(flag); ++i) {
      if (!is_number(argv[arg_index + i])) {
        printf("Inappropriate parameters count\n");
        return 1;
      } else {
        flag_params[i] = myatoi(argv[arg_index + i]);
      }
    }
    arg_index += number_parameters_count(flag);
  }
  if (argv[1][1] == 'q') {
    double x1 = 0, x2 = 0;
    int answ = toggles_q(atof(argv[2]), atof(argv[3]), atof(argv[4]));
    if (answ == 0) {
      printf("With the entered coefficients does not exist\n");
    } else if (answ == 1) {
      printf("%f\n", x1);
    } else if (answ == 2) {
      printf("%f  %f\n", x1, x2);
    }
  } else if (argv[1][1] == 'm') {
    if (toggles_m(myatoi(argv[2]), myatoi(argv[3])))
      printf("Yes\n");
    else
      printf("No\n");
  } else if (argv[1][1] == 't') {
    if (toggles_t(atof(argv[2]), atof(argv[3]), atof(argv[4])))
      printf("Yes\n");
    else if (atof(argv[2]) > 0 && atof(argv[3]) > 0 && atof(argv[4]) > 0) {
      printf("No\n");
    }
  }
}