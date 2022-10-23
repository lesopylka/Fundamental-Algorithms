#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int is_digit(char c) {
  return (c >= '0' && c <= '9');
}

int main(int argc, char * argv[]) {

  if (argc < 3) {
    printf("Please, input path to the file and flag one of the ( 'a)' , 'b)', 'c)', 'd)', 'e)' )\n");
    return 0;
  } else if (argc > 3) {
    printf("Сheck the correctness of the entered data. Too much arguments.\n");
    return 0;
  }

  FILE * input_file = fopen(argv[1], "r");

  if (input_file == NULL) {
    printf("Error opening input file\n");
    return 0;
  }

  long long array[128];
  int size_array = 0, flag = 1, minus = 0;
  long long n = 0;
  char c;
  while ((c = fgetc(input_file))) {
    if (is_digit(c)) {
      n = n * 10 + (c - '0');
      flag = 0;
    } else if (flag == 0) {
      if (minus) {
        n = -n;
        minus = 0;
      }
      array[size_array] = n;
      size_array++;
      n = 0;
      flag = 1;
    } else if (flag == 1) {
      if (c == '-') {
        minus = 1;
      }
    }
    if (c == EOF) break;
  }
  printf("\nStart array from file: ");
  for (int j = 0; j < size_array; j++) {
    printf("%lld ", array[j]);
  }
  printf("\n");

  fclose(input_file);
  int good_flag = 0;
  char parametrs[5][3] = {
    "a)",
    "b)",
    "c)",
    "d)",
    "e)"
  };

  long long array2[128];
  int size_array2 = 0;
  int i;
  int current_element;
  long long s = 0;
  for (i = 0; i < 5; i++) {
    if (!strcmp(parametrs[i], argv[2])) {
      good_flag = 1;
      switch (parametrs[i][0]) {
      case 'a':
        printf("Numbers at odd indices: ");
        for (int l = 1; l < size_array; l += 2) {
          array2[size_array2] = array[l];
          size_array2++;
        }

        break;
      case 'b':
        printf("Even numbers: ");
        for (int l = 0; l < size_array; ++l) {
          if (array[l] % 2 == 0) {
            array2[size_array2] = array[l];
            size_array2++;
          }
        }
        break;
      case 'c':
        printf("Enter the index of the current element: ");
        scanf("%d", & current_element);
        if (current_element > size_array - 1 || current_element < 0) {
          printf("Invalid pointer!\n");
          return 0;
        }
        long long minim = array[0], maxim = array[0];
        for (int l = 0; l < size_array; ++l) {
          if (array[l] > maxim) {
            maxim = array[l];
          }
          if (array[l] < minim) {
            minim = array[l];
          }
        }
        printf("Farthest (in value) from it: ");
        if (maxim - array[current_element] > array[current_element] - minim) {
          printf("%lld", maxim);
        } else {
          printf("%lld", minim);
        }

        break;
      case 'd':
        printf("Enter the index of the current element: ");
        scanf("%d", & current_element);

        if (current_element > size_array - 1 || current_element < 0) {
          printf("Invalid pointer!\n");
          return 0;
        }

        for (int l = 0; l < current_element; ++l)
          s += array[l];

        printf("Sum: %lld", s);

        break;
      case 'e':
        printf("Enter the index of the current element: ");
        scanf("%d", & current_element);

        if (current_element > size_array - 1 || current_element < 0) {
          printf("Invalid pointer!\n");
          return 0;
        }

        for (int l = 0; l < size_array; ++l)
          if (array[l] < array[current_element])
            s += array[l];

        printf("Sum: %lld", s);

        break;
      }
    }
  }
  if (!good_flag) {
    printf("Invalid flag entered! flag one of the ( 'a)' , 'b)', 'c)', 'd)', 'e)' )\n");
    return 0;
  }

  for (int l = 0; l < size_array2; ++l) {
    printf("%lld ", array2[l]);
  }
  printf("\n");

  return 0;
}