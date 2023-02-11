#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <limits.h>

double EPS = 1.0f;

enum VALIDATION_ENUM {
  ok = 0,
    invalidinput = 5,
    noRealSolutions = 6,

};

void printValidationError(enum VALIDATION_ENUM error) {
  switch (error) {
  case invalidinput:
    printf("Error: Invalid input!\n");
    break;
  case noRealSolutions:
    printf("There are no real solutions\n");
    break;
  default:
    printf("Unexpected error\n");
  }
}


int char_to_int(char * string) {
  int result = 0;
  int sign = 1;
  if ( * string == '-') {
    sign = -1;
    string++;
  }
  while ( * string) {
    result = result * 10 + ( * string - '0');
    string++;
  }
  return result * sign;
}

double char_to_double(char * string) {
  int sign = 1, sm = 0, point_pos = 0;
  double backp = 0, free = 1;
  if ( * string == '-') {
    sm++;
    sign = -1;
  }
  for (int i = sm; string[i] != '\0'; i++) {
    if (point_pos) {
      free = free / 10;
      backp = backp + free * (string[i] - '0');
    } else {
      if (string[i] == '.') {
        point_pos = 1;
      } else {
        backp = backp * 10 + (string[i] - '0');
      }
    }
  }
  return sign * backp;
}

int square_equation(double a, double b, double c, double * x1, double * x2) {
  double D;

  if (fabs(a) < EPS) {
    return 5;
  }
  
  D = pow(b, 2) - (4 * a * c);

  if (fabs(D) < -EPS) { return noRealSolutions; } else {
    * x1 = (-b + sqrt(D)) / ((2 * a));
    * x2 = (-b - sqrt(D)) / ((2 * a));
    
  }
  return 0;
}

void solveEqation(double a, double b, double c, double * x1, double * x2) {
  double arr[3] = { a, b, c };
  int counter = 1;

  for (int i = 0; i <= 2; i++) {
    for (int j = 0; j <= 2; j++) {
      for (int k = 0; k <= 2; k++) {
        if (i != j && i != k && j != k) {
          printf("%d) ", counter);
          counter++;
          square_equation(arr[i], arr[j], arr[k],  x1, x2);
        }
      }
    }
  }
}

int main(int argc, char * argv[]) {

  if (strlen(argv[1]) != 2) {
    printf("Error: Wrong flag length!\n");
  }
  double a, b, c;
  int num1, num2, num3;
  double x1, x2;
  if (argv[1][0] == '-' || argv[1][0] == '/') {
    switch (argv[1][1]) {
    case 'q':
    
      if (argc != 5) {
        printf("Error: Invalid number of parameters!\n");
        break;
      }
      a = char_to_double(argv[2]);
      b = char_to_double(argv[3]);
      c = char_to_double(argv[4]);
      solveEqation(a, b, c, & x1, & x2);
      printf(" a = %lf, b = %lf, c = %lf:\n", a, b, c);
      printf("Roots - %lf %lf\n", x1, x2);

      break;

    case 'm':
      if (argc != 4) {
        printf("Error: Invalid number of parameters!\n");
        break;
      }
      num1 = char_to_int(argv[2]);
      num2 = char_to_int(argv[3]);

      if (num1 > 0 && num2 > 0) {
        if (num1 % num2 == 0) {
          printf("The first number is a multiple of the second\n");
        } else {
          printf("Numbers are not multiples\n");
        }
      } else {
        printf("Error: Invalid input!\n");
      }

      break;
    case 't':

      if (argc != 5) {
        printf("Error: Invalid number of parameters!\n");
        break;
      }
      num1 = char_to_int(argv[2]);
      num2 = char_to_int(argv[3]);
      num3 = char_to_int(argv[4]);

      if (num1 > 0 && num2 > 0 && num3 > 0) {
        num1 *= num1;
        num2 *= num2;
        num3 *= num3;
        if (num1 == num2 + num3 || num2 == num1 + num3 || num3 == num1 + num2) {
          printf("These are the sides of a right triangle\n");
        } else {
          printf("The entered values ​​cannot be the sides of a right triangle\n");
        }
      } else {
        printf("Error: Invalid input!\n");
      }
      break;
    }
  }
  return 0;
}