#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

char* input_validation(int argc, char * argv[], unsigned * number) {
  if (argc == 1) {
    return "Invalid Input: no arguments";
  }
  if (argc != 3) {
    return "Invalid Input: wrong number of arguments";
  }
  if (strlen(argv[2]) != 2) {
    return "Invalid Input: unexpected toggles";
  }
  if ((argv[1][0] == '0') && (argv[1][1] == 0)) {
    return "Invalid Input: unexpected number";
  }
  char * symbol = argv[1];
  char difference = *symbol - '0';
  while ( * symbol) {
    if ((( difference) < 0) || (( difference) > 9)) {
      return "Invalid Input: unexpected number";
    }
    if (( * number > UINT_MAX / 10)) {
      return "Invalid Number: overflow";
    }
    if ((( * number * 10) / 2 + ( difference) / 2) > UINT_MAX / 2) {
      return "Invalid Number: overflow";
    }
    * number = * number * 10 + ( * symbol++ - '0');
  }

  if (!(argv[2][0] == '-' || argv[2][0] == '/')) {
    return "Invalid Input: symbol '-' or '/' before toggles not found";
  }

  return "";
}

unsigned long long binpow(unsigned long long number, unsigned long long n) {
  unsigned long long res = 1;
  while (n) {
    if (n & 1) {
      res *= number;
    }
    number *= number;

    n >>= 1;
  }

  return res;
}

unsigned digits_kol(unsigned number) {
  if (number == 0) {
    return 1;
  }
  unsigned length = 0;
  while (number != 0) {
    length++;
    number /= 10;
  }
  return length;
}

void toggles_h(unsigned n) {
  int maxValue = 100;
  if (n < maxValue) {
    maxValue = n;
  }

  for(unsigned number = 2; number < maxValue; ++number) {
    if (n % number != 0) {
       continue;
    }
    printf("%u ", number);
  }
  printf("\n");
}

unsigned toggles_f(unsigned number) {
  if (number <= 1) {
    return 1;
  }
  return number * toggles_f(number - 1);
}

int toggles_p(unsigned number) {
  if (number == 4) {
    return 0;
  }

  int result = toggles_f(number - 1) % number;

  if (result == number - 1) {
    return 1;
  }
  return 0;
}

void toggles_s(unsigned number, unsigned digits_kol) {
  unsigned tmp = pow(10, digits_kol - 1);
  while (tmp > 0) {
    unsigned digit = number / tmp;

    printf("%u ", digit);

    number = number % tmp; 
    tmp = tmp / 10;
  }
  printf("\n");
}

int toggles_e(unsigned number) {
  if (number > 10) {
    return 1;
  }
  // неэффективно? O(9 * N * logN) -> O(N * logN)
  for (unsigned long long i = 2; i <= 10; i++) {
    printf("%llu: ", i);
    for (unsigned long long k = 1; k <= number; k++) {
      printf("%lld ", binpow(i, k));
    }
    printf("\n");
  }
  return 0;
}

unsigned toggles_a(unsigned number) {
  return number * (number + 1) / 2;
}

int main(int argc, char * argv[]) {
  unsigned number = 0;
  
  char* validation_result = input_validation(argc, argv, & number);

  if (strcmp(validation_result, "")) {
    printf("%s\n", validation_result);
    return 1;
  }

  char toggle = argv[2][0];
  char command = argv[2][1];

  switch (command) {
    case 'h':
      toggles_h(number);
      break;
    case 'p':
      if (toggles_p(number)) {
        printf("%d is prime\n", number);
        return 0;
      }
      printf("%d is composite\n", number);    
      break;
    case 's':
      toggles_s(number, digits_kol(number));

      break;
    case 'e':
      if (toggles_e(number)) {
        printf("Input Error: the number is bigger than 10 (toggles e)\n");
      }
      break;
    case 'a':
      printf("sum of numbers from 1 to %u is %u\n", number, toggles_a(number));
      break;
    case 'f':
      printf("Factorial of %u: %u\n", number, toggles_f(number));
      break;
    default:
      printf("Invalid toggles: unexpected toggles '%c'\n", command);
      break;
  }

  return 0;
}



// 7 строка: зачем возвращать строку? чтобы потом strcmp дёргать который имеет линейную сложность? возвращай статускод (enum для этого свой определи) и его хендли в вызывающем коде
// + 17 строка: проще чекнуть что argv[1][1] == 0, без вызова strlen
// + 22 строка и далее: 100500 раз вычисляется выражение *symbol - '0'. Вычисли один раз на каждой итерации, сохрани в переменную и используй её
// +- 42 и 52 строки: тип возвращаемого значения функции unsigned long long, так зачем вычислять в int? 
// 55 строка: функция digits_kol: от транслита отказываемся + можно параметризовать основание системы счисления
// 73 строка: зачем перебирать все числа? возьми n, сохрани в аккумулятор и прибавляй на каждой итерации к аккумулятору n
// 82 строка: зачем рекурсивно считать, если можно итеративно
// алгоритм определения простоты не понятен
// 119 строка: у Тебя O(n^2 * log(n)), сделай за O(n^2) 
// как насчёт во вложенном цикле умножать аккумулятор на возводимое в степень число и сразу печатать?