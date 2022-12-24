#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

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
// guiшка есть какая-нибудь чтобы веточки смотреть
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
      return (sign > 0) ? INT_MAX : INT_MIN;
    }
    ++i;
  }
  return (ret * sign);
}

int IntToString(int x, char str[], int d){ // возвращает индекс символа конца строки
  int i = 0;
  int len = 0;
  int tmpX = x;
  while (tmpX) {
    len++;
    tmpX /= 10;
  }
  str[len] = '\0';
  len--;
  while (len >= 0) {
      str[len] = (x % 10) + '0';
      len--;
  }
  // while (i < d)
  //     str[i++] = '0';
  // reverse(str, i);
  // str[i] = '\0';
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

int* toggles_q(double a, double b, double c) {
  double d;
  int* roots = NULL;
  printf("For the: (%.3lf) * x^2 + (%.3lf) * x + (%.3lf) = 0\n", a, b, c);
  if (a <= EPS) {
    printf("The number 'a' is not a parameter of the quadratic equation, because it should not be equal to 0\n\n");
  } else {
    d = dicriminant(a, b, c);
    if (d < -EPS) {
      printf("No roots.\n");
    } else if (fabs(d) <= EPS) {
      roots = (int*)malloc(sizeof(int));
      if (roots == NULL) { return NULL; }
      int x1 = (-b + sqrt(d)) / (2 * a);
      *roots = x1;
      printf("x = %d\n", x1);
    } else {
      roots = (int*)malloc(sizeof(int) * 2);
      if (roots == NULL) { return NULL; }
      int x1 = (-b + sqrt(d)) / (2 * a);
      int x2 = (-b - sqrt(d)) / (2 * a);
      *roots = x1;
      *(roots + 1) = x2;
      printf("x1 = %lf\n", (-b + sqrt(d)) / (2 * a));
      printf("x2 = %lf\n", (-b - sqrt(d)) / (2 * a));
    }
    printf("\n");
  }
  return roots;
}

bool toggles_m(int i, int k) {
  if (!i || !k) {
    return false;
  }
  return i % k == 0;
}

bool toggles_t(float a, float b, float c) {
  float aabbcc = ((a * a + b * b) - (c * c));
  float aaccbb = ((a * a + c * c) - (b * b));
  float bbccaa = ((b * b + c * c) - (a * a));
  if (a > EPS && b > EPS && c > EPS)
    return fabs(aabbcc) <= EPS ||
           fabs(aaccbb) <= EPS ||
           fabs(bbccaa) <= EPS;
  else 
    return 0;
}

int main(int argc, char ** argv) {
  // типы возвр значений
  // true, false под false ещё ошибка может быть
  // x, x1 x2
  // наш протокол
  // флаги:
  //    -e это ошибка, текст ошибки
  //    -a это ответ флоат, количество ответов, ответ/ы
  //    -b ответ тру или фалсе
  if(!is_flag(argv[1])){
    printf("-e Inappropriate flag position\n");
    return 1;
  }
  if(!argc - 1 == number_of_parameters(argv[1][1])){
    printf("-e Inappropriate parameters count\n");
    return 1;
  }

  switch (argv[1][1]) {
    case 'q':
      double x1 = 0;
      double x2 = 0;
      int answ = toggles_q(atof(argv[2]), atof(argv[3]), atof(argv[4]));
      if (answ == 0) {
        printf("-e With the entered coefficients does not exist\n");
        return 0;
      } else if (answ == 1) {
        char message[100];
        strcpy(message, "-a 1 ");
        char* ans;
        myftoa(x1, ans, 2);
        strcat(message, ans);
        printf("%s\n", message);
        return 0;
      } else if (answ == 2) {
        char message[100];
        strcpy(message, "-a 2 ");
        char* ans1;
        myftoa(x1, ans1, 2);
        char* ans2;
        myftoa(x2, ans2, 2);
        strcat(message, ans1);
        strcat(message, ans2); 
        printf("%s\n", message);
        printf("%f  %f\n", x1, x2);
        return 0;
        
      }
      break;
    case 'm':
      if (toggles_m(myatoi(argv[2]), myatoi(argv[3]))){
        printf("-b true\n");
        return 0;
          }
      else {
        printf("-b false\n");
        return 0;
      break;
      }
    case 't':
      if (toggles_t(atof(argv[2]), atof(argv[3]), atof(argv[4]))){
        printf("-b true\n");
        return 0;
      } 
      else if (atof(argv[2]) > 0 && atof(argv[3]) > 0 && atof(argv[4]) > 0) {
        printf("-b false\n");
        return 0;
      }
      break;
  }
}

//  toggles_q:
//   убери printf в main
//   где проверки на malloc +
//   fabs(d - 0) - зочем, если можно просто fabs(d) +
//   не увидел где возвращается статускод метода чтобы можно было его обработать выше
//  toggles_t:
//   зачем трижды считать произведения если можно сохранить и пользоваться вычисленными значениями
//   аналогично, printf здесь не должно быть
//  main
//   196 и 198 строки: Ты передаёшь в функцию неинициализированные указатели, а в функции под них чтото пишешь, так делать нельзя
//   вызов toggles_q из main: вроде как функция возвращает значение типа int*, а Ты его в int кладёшь. Ну и как же без утечки памяти (=
// IntToString: слишком долго работает, сделай без reverse