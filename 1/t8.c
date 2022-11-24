#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int IsDigit(char c) {
  return (c >= '0' && c <= '9');
}

int main(int argc, char * argv[]) {

  if (argc < 3) {
    printf("please, input path to the file and Flag one of the ( 'a)' , 'b)', 'c)', 'd)', 'e)' )\n");
    return 0;
  } else if (argc > 3) {
    printf("too much arguments.\n");
    return 0;
  }

  FILE * input_file = fopen(argv[1], "r");

  if (input_file == NULL) {
    printf("error opening input file\n");
    return 0;
  }

  long long array[128];
  int SizeArray = 0, Flag = 1, Minus = 0;
  long long n = 0;
  char c;
  while ((c = fgetc(input_file))) {
    if (IsDigit(c)) {
      n = n * 10 + (c - '0');
      Flag = 0;
    } else if (Flag == 0) {
      if (Minus) {
        n = -n;
        Minus = 0;
      }
      array[SizeArray] = n;
      SizeArray++;
      n = 0;
      Flag = 1;
    } else if (Flag == 1) {
      if (c == '-') {
        Minus = 1;
      }
    }
    if (c == EOF) break;
  }
  printf("\nstart array from file: ");
  for (int j = 0; j < SizeArray; j++) {
    printf("%lld ", array[j]);
  }

  fclose(input_file);
  int good_flag = 0;
  char Parameters[5][3] = {
    "a)",
    "b)",
    "c)",
    "d)",
    "e)"
  };

  long long array2[128];
  int SizeArray2 = 0;
  int i;
  int CurrentElement;
  long long s = 0;
  for (i = 0; i < 5; i++) {
    if (!strcmp(Parameters[i], argv[2])) {
      good_flag = 1;
      switch (Parameters[i][0]) {
      case 'a':
        printf("numbers at odd indices: ");
        for (int l = 1; l < SizeArray; l += 2) {
          array2[SizeArray2] = array[l];
          SizeArray2++;
        }

        break;
      case 'b':
        printf("even numbers: ");
        for (int l = 0; l < SizeArray; ++l) {
          if (array[l] & 1 == 0) {
            array2[SizeArray2] = array[l];
            SizeArray2++;
          }
        }
        break;
      case 'c':
        printf("enter the index of the current element: ");
        scanf("%d", & CurrentElement);
        if (CurrentElement > SizeArray - 1 || CurrentElement < 0) {
          printf("invalid pointer!\n");
          return 0;
        }
        long long Minim = array[0], maxim = array[0];
        for (int l = 0; l < SizeArray; ++l) {
          if (array[l] > maxim) {
            maxim = array[l];
          }
          if (array[l] < Minim) {
            Minim = array[l];
          }
        }
        printf("farthest (in value) from it: ");
        if (maxim - array[CurrentElement] > array[CurrentElement] - Minim) {
          printf("%lld", maxim);
        } else {
          printf("%lld", Minim);
        }

        break;
      case 'd':
        printf("enter the index of the current element: ");
        scanf("%d", & CurrentElement);

        if (CurrentElement > SizeArray - 1 || CurrentElement < 0) {
          printf("invalid pointer!\n");
          return 0;
        }

        for (int l = 0; l < CurrentElement; ++l)
          s += array[l];

        printf("sum: %lld", s);

        break;
      case 'e':
        printf("enter the index of the current element: ");
        scanf("%d", & CurrentElement);

        if (CurrentElement > SizeArray - 1 || CurrentElement < 0) {
          printf("invalid pointer!\n");
          return 0;
        }

        for (int l = 0; l < SizeArray; ++l)
          if (array[l] < array[CurrentElement])
            s += array[l];

        printf("sum: %lld", s);

        break;
      }
    }
  }
  if (!good_flag) {
    printf("invalid flag entered\n");
    return 0;
  } else return 1;

  for (int l = 0; l < SizeArray2; ++l) {
    printf("%lld ", array2[l]);
  }
  printf("\n");

  return 0;
}



// аналогично 1.5 и 1.6, с exit code в main при неуспешном завершении приложения +-
// 86 строка: быстрее выполнить &1, чем %2 +