#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>

void swap(char * s, int left, int right) {
  char tmp = s[left];
  s[left] = s[right];
  s[right] = tmp;
}

int length(const char * str) {
  int i = -1;
  while (str[++i]);
  return i;
}

void reverse(char * str) {
  int n = length(str);
  for (int i = 0; i < n / 2; ++i)
    swap(str, i, n - 1 - i);
}

void upper_register_through_2(char * str) {
  int i = 0;
  while (i < length(str)) {
    str[i] = toupper(str[i]);
    i += 2;
  }
}

char * replace(char * str) {
  int n = length(str), i, j;
  int pointers[] = {
    0,
    0,
    0
  };
  char * result = (char * ) malloc(sizeof(char) * (n + 1));
  char * letters = (char * ) malloc(sizeof(char) * (n + 1));
  char * others = (char * ) malloc(sizeof(char) * (n + 1));
  for (i = 0; i < n; ++i) {
    if (isdigit(str[i])) {
      result[pointers[0]] = str[i];
      pointers[0]++;
    } else if (isalpha(str[i])) {
      letters[pointers[1]] = str[i];
      pointers[1]++;
    } else {
      others[pointers[2]] = str[i];
      pointers[2]++;
    }
  }
  for (j = 0; j < pointers[1]; ++j) {
    result[pointers[0]] = letters[j];
    pointers[0]++;
  }
  for (j = 0; j < pointers[2]; ++j) {
    result[pointers[0]] = others[j];
    pointers[0]++;
  }
  result[pointers[0]] = '\0';
  free(letters);
  free(others);
  return result;
}

char * concat(char * s1, char * s2) {

  int len1 = length(s1);
  int len2 = length(s2);

  char * result = malloc(sizeof(int) * (len1 + len2 + 1));

  if (!result) {
    fprintf(stderr, "malloc() failed: insufficient memory!\n");
    return NULL;
  }

  memcpy(result, s1, len1);
  memcpy(result + len1, s2, len2 + 1);

  return result;
}

int main(int argc, char * argv[]) {

  if (argc == 1) {
    printf("Parameters no entered!\n");
    return 0;
  } else if (argc < 3) {
    printf("Needs minimum 3 arguments! (namefile, string, flag)\n");
    return 0;
  }

  char * parametrs[5] = {
    "-l",
    "-r",
    "-u",
    "-n",
    "-c"
  };
  int good_flag = 0, flag;

  for (flag = 0; flag < 5; ++flag) {
    if (!strcmp(parametrs[flag], argv[2])) {
      good_flag = 1;
      switch (parametrs[flag][1]) {
      case 'l':
        printf("Length of string: %d\n", length(argv[1]));
        break;
      case 'r':
        reverse(argv[1]);
        printf("Reverse: %s\n", argv[1]);
        break;
      case 'u':
        upper_register_through_2(argv[1]);
        printf("Result: %s\n", argv[1]);
        break;
      case 'n':
        printf("Replaced: %s\n", replace(argv[1]));
        break;
      case 'c':
        if (argc >= 4) {
          printf("%s", concat(argv[1], argv[3]));
        } else {
          printf("Need one more argument!");
        }
        break;
      }
      break;
    }
  }
  if (!good_flag) {
    printf("Invalid flag entered! (Flag start in '-' and then one of the 'lrunc')\n");
  }

  return 0;
}