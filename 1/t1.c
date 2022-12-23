#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

enum VALIDATION_ENUM {
  ok = 0,
    noArguments = 1,
    wrongNumberOfArguments = 2,
    unexpectedToggles = 3,
    unexpectedNumber = 4,
    overflow = 5,
    symbolBeforeTogglesNotFound = 6,
};

void printValidationError(enum VALIDATION_ENUM error) {
  switch (error) {
  case noArguments:
    printf("Invalid Input: no arguments\n");
    break;
  case wrongNumberOfArguments:
    printf("Invalid Input: wrong number of arguments\n");
    break;
  case unexpectedToggles:
    printf("Invalid Input: unexpected toggles\n");
    break;
  case unexpectedNumber:
    printf("Invalid Input: unexpected number\n");
    break;
  case overflow:
    printf("Invalid Number: overflow\n");
    break;
  case symbolBeforeTogglesNotFound:
    printf("Invalid Input: symbol '-' or '/' before toggles not found\n");
    break;
  default:
    printf("Unexpected error\n");
  }
}

enum VALIDATION_ENUM validationArg(int argc, char * argv[], unsigned * number) {
  if (argc == 1) {
    return noArguments;
  }
  if (argc != 3) {
    return wrongNumberOfArguments;
  }
  if (strlen(argv[2]) != 2) {
    return unexpectedToggles;
  }
  if ((argv[1][0] == '0') && (argv[1][1] == 0)) {
    return unexpectedNumber;
  }
  char * symbol = argv[1];
  char difference = * symbol - '0';
  while ( * symbol) {
    if (((difference) < 0) || ((difference) > 9)) {
      return unexpectedNumber;
    }
    if (( * number > UINT_MAX / 10)) {
      return overflow;
    }
    if ((( * number * 10) / 2 + (difference) / 2) > UINT_MAX / 2) {
      return overflow;
    }
    * number = * number * 10 + ( * symbol++ - '0');
  }

  if (!(argv[2][0] == '-' || argv[2][0] == '/')) {
    return symbolBeforeTogglesNotFound;
  }

  return ok;
}

unsigned numberDigitsCount(unsigned number, unsigned numberSystemBase) {
  if (number == 0) {
    return 1;
  }
  unsigned length = 0;
  while (number != 0) {
    length++;
    number /= numberSystemBase;
  }
  return length;
}

void toggles_h(unsigned n) {
  if (n >= 100) {
    printf("no such numbers\n");
    return;
  }
  for (unsigned acc = n; acc < 100; acc += n) {
    printf("%d ", acc);
  }
  printf("\n");
}

unsigned toggles_f(unsigned number) {
  unsigned long long result = 1;

  for (unsigned i = 1; i <= number; ++i) {
    result *= i;
  }

  return result;
}

int toggles_p(unsigned number) {
  // testiruesh chislo 65537 na prostotu naprimer
  // determinirovannym algoritmom

    // i = [2, 3, ..., sqrt(65537) primerno ravno 256]
  // delim na 2, potom na 3, tipa vse ok
  // no zachem delitj na 4 esli na 2 ne delitsja ._.
  // zachem delitj na 9 esli ne delitsja na 3
  // nu i tak dalee
  // to est' po-horoshemu, nuZhno delitj tol'ko na prostie chisla iZ doapoZona
  // a ne na vse
  // uberi hotya by kratnie 2, 3, 5
  // eta ochenj legko
  // delaj prjam seichas ._. чт....
// zachem vsjo stiratj-to o_O
//так все говно же
// хотя бля говно но хотя бы не жидкое =)
// верни как было и просто отбрось числа кратные 2 3 и 5
// надо к счетчику не 1 прибавлять а логику инкремента его значения продумать чуть и норм будет
// меньше итераций потратишь чем втупую все подряд перебирать
// делай кароч а я пошел пить пиво =)
// 
  for (int i = 2; i < floor(sqrt(number)); i++) {
    if (number % i == 0) {
      return 0;
    }
  }
  return 0;
  // и return-коды разные сделай а то только 0 маловато будет
  // я пошел
  // как будет готово кидай
  // я обязательно это не посмотрю
  // =)
  //спасибо!
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
    for (unsigned long long k = 1, result = k * i; k <= number; k++, result *= i) {
      printf("%lld ", result);
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

  enum VALIDATION_ENUM validation_result = validationArg(argc, argv, & number);

  if (validation_result != ok) {
    printValidationError(validation_result);
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
      printf("%d is composite\n", number);
      return 0;
    }
    printf("%d is prime\n", number);
    break;
  case 's':
    toggles_s(number, numberDigitsCount(number, 10));

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
