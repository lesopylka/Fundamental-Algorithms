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
  unsigned length_ = length(str);
  while (i < length_) {
    str[i] = toupper(str[i]);
    i += 2;
  }
}

char* replace(char * str) {
  int n = length(str), i, j;
  
  char* result = (char*) malloc(sizeof(char) * (n + 1));
  if( result == NULL ) {
    printf( "Insufficient memory available\n" );
    return NULL;
  }

  char* letters = (char*) malloc(sizeof(char) * (n + 1));
  if( letters == NULL ) {
    printf( "Insufficient memory available\n" );
    return NULL;
  }

  char* others = (char*) malloc(sizeof(char) * (n + 1));
  if( others == NULL ) {
    printf( "Insufficient memory available\n" );
    return NULL;
  }

  int digitCount=0, letterCount=0, otherCount=0;
  
  for (i = 0; i < n; ++i) {
    if (isdigit(str[i])) {
      result[digitCount] = str[i];
      digitCount++;
    } else if (isalpha(str[i])) {
      letters[letterCount] = str[i];
      letterCount++;
    } else {
      others[otherCount] = str[i];
      otherCount++;
    }
  }

  int count = digitCount;
  for (j = 0; j < letterCount; ++j) {
    result[count] = letters[j];
    count++;
  }
  for (j = 0; j < otherCount; ++j) {
    result[count] = others[j];
    count++;
  }
  
  free(letters);
  free(others);
  return (result);
}

char * concat(char * s1, char * s2) {

  size_t len1 = strlen(s1);
  size_t len2 = strlen(s2);

  char * result = malloc(sizeof(char) * (len1 + len2));

  if (!result) {
    fprintf(stderr, "malloc() failed: insufficient memory!\n");
    return NULL;
  }

  strcpy(result, s1);
  strcpy(result + len1, s2);

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
      char* result = NULL; 
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
        result = replace(argv[1]);
        printf("Replaced: %s\n", result);
        free(result);
        result = NULL;
        break;
      case 'c':
        if (argc >= 4) {
          result = concat(argv[1], argv[3]);
          printf("%s\n", result);
          free(result);
        } else {
          printf("Need one more argument!\n");
        }
        break;
      }
    }
  }
  if (!good_flag) {
    printf("Invalid flag entered! (Flag start in '-' and then one of the 'lrunc')\n");
  }
  return 0;
}