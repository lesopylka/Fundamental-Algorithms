#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

int input_validation(int argc, char * argv[], unsigned * number) {
  if (argc == 1) {
    printf("Invalid Input: no arguments\n");
    return (0);
  }
  if (argc != 3) {
    printf("Invalid Input: wrong number of arguments\n");
    return (0);
  }
  if (strlen(argv[2]) != 2) {
    printf("Invalid Input: unexpected toggles\n");
    return (0);
  }
  if ((argv[1][0] == '0') && (strlen(argv[1]) != 1)) {
    printf("Invalid Input: unexpected number\n");
    return (0);
  }
  char * symbol = argv[1];
  while ( * symbol) {
    if ((( * symbol - '0') < 0) || (( * symbol - '0') > 9)) {
      printf("Invalid Input: unexpected number\n");
      return (0);
    }
    if (( * number > UINT_MAX / 10)) {
      printf("Invalid Number: overflow\n");
      return (0);
    }
    if ((( * number * 10) / 2 + ( * symbol - '0') / 2) > UINT_MAX / 2) {
      printf("Invalid Number: overflow\n");
      return (0);
    }
    * number = * number * 10 + ( * symbol++ - '0');
  }
  return 0;
}

unsigned digits_kol(unsigned number) {
  if (number != 0) {
    return 1 + digits_kol(number / 10);
  } else {
    return 0;
  }
}

int toggles_h(unsigned number, unsigned multiples) {

  if (multiples > 1) {
    toggles_h(number, multiples - 1);
  }
  printf("%u ", number * (multiples));
  return 0;
}

void toggles_p(unsigned number) {
  // неэффективно
  // никаких экзитов - верни результат наверх, принцип везде один и тот же
  // иначе код не будет переиспользуемым в разных контекстах использования (
  // опять экзиты(
  for (unsigned i = 2; i <= (number / 2); i++) {
    if ((number % i) == 0) {
      printf("Number %u is composite\n", number);
      return (0);
    }
  }
  printf("Number %u is prime\n", number);
  return (0);
}

int toggles_s(unsigned number, unsigned digits_kol) {
  unsigned tmp = pow(10, digits_kol);
  while (tmp > 0) {
    number = number % tmp;
    tmp = tmp / 10;
    if (tmp == 1) {
      printf("%u\n", number / tmp);
      return (0);
    }
    printf("%u ", number / tmp);
  }
  return 0;
}

int toggles_e(unsigned number) {
  if (number > 10) {
    printf("Input Error: the number is bigger than 10 (toggles e)\n");
    return (0);
  }
  // неэффективно
  for (unsigned i = 0; i <= 10; i++) {
    printf("%u: ", i);
    for (unsigned k = 1; k <= number; k++) {
      if ((i == 10) && (k == 10)) {
        printf("%lld ", (long long) pow(i, k));
      } else {
        printf("%u ", (unsigned) pow(i, k));
      }
    }
    printf("\n");
  }
  return (0);
}

int toggles_a(unsigned number) {
  if ((number > UINT_MAX / (number - 1))) {
    printf("toggles 'a' Error: overflow\n");
    return (0);
  }
  printf("Sum of numbers from 1 to %u is %u\n", number, number * (number - 1) / 2 + (number));
  return (0);
}

int toggles_f(unsigned number) {
  if (number == 0 || number == 1) {
    return 1;
  }
  if (number > 1 && toggles_f(number - 1) > 1 && number > UINT_MAX / toggles_f(number - 1)) {
    printf("toggles 'f' Error: overflow\n");
    return (0);
  }
  return number * toggles_f(number - 1);
}

int main(int argc, char * argv[]) {
  unsigned number = 0;
  input_validation(argc, argv, & number);
  if (argv[2][0] == '-' || argv[2][0] == '/') {
    if (argv[2][1] == 'h') {
      if (100 / number == 0) {
        printf("No multiples of %u within 100!\n", number);
        return (0);
      }
      printf("Multiples of %u within 100: ", number);
      toggles_h(number, 100 / number);
      return (0);
    } else if (argv[2][1] == 'p') {
      toggles_p(number);
    } else if (argv[2][1] == 's') {
      toggles_s(number, digits_kol(number));
    } else if (argv[2][1] == 'e') {
      toggles_e(number);
    } else if (argv[2][1] == 'a') {
      toggles_a(number);
    } else if (argv[2][1] == 'f') {
      printf("Factorial of %u: %u\n", number, toggles_f(number));
      return (0);
    } else {
      printf("Invalid toggles: unexpected toggles '%c'\n", argv[2][1]);
      return (0);
    }
  } else {
    printf("Invalid Input: symbol '-' or '/' before toggles not found\n");
    return (0);
  }
}

// в 1 лабе интересно почему вдруг в записи числа 0 пристствует 0 цифр

// функция digits_col

// toggles_p - ну типа...

// функция возвращает 0, как тип возвращаемого значения может быть void?

// и почему всегда 0 возвращается? Тебе надо определить является ли число простым

// например верни 1 когда оно простое и 0 когда не простое

// toggles_s аналогично

// toggles_e аналогично

// и не надо printf'ами обмазывать

// в функциях которые вычисляют значения

// обмажь в main если так уж хочется

// то что вернёт функция которая значение вычислит

// input_validation тоже

// значение вернул

// а надо бы на него в main обратить внимание

// switch поставить какойнибудь
