#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int ARRAY_SIZE = 50;
const int MEMORY_MULTIPLIER = 2;

int ToInteger(char c) {
    if (c >= 'A' && c <= 'Z') 
        return c - 'A' + 10;
    else if (c >= 'a' && c <= 'z') 
        return c - 'a' + 10;
    else if (c >= '0' && c <= '9') 
        return c - '0';
    return 0;
}

int main(int argc, char * argv[]) {

  if (argc < 2) {
    printf("please, input path to the file");
    return 0;
  } else if (argc > 2) {
    printf("check the correctness of the entered data");
    return 0;
  }

  FILE * InputFile = fopen(argv[1], "r");

  if (InputFile == NULL) {
    printf("error opening input file\n");
    return 0;
  }

  char c;
  int i = 0;

  FILE * OutputFile = fopen("out_file.txt", "w");

  if (OutputFile == NULL) {
    printf("error opening Output file\n");
    return 0;
  }

  int size = ARRAY_SIZE;
  int currentSize = 0;
  char* Array = (char *)malloc(sizeof(char) * size);

  int Flag = 0;
  int Max = 1;
  while ((c = fgetc(InputFile))) {
    if (c != ' ' && c != '\n' && c != EOF) {
      if (currentSize == size) {
        size *= MEMORY_MULTIPLIER;
        Array = (char *) realloc(Array, sizeof(char) * size); //листочек с tmp
      }

      if (ToInteger(c) == -1) {
        printf("file contains invalid characters...");
        free(Array);
        return 0;
      }
      *(Array + currentSize) = c;
      if (ToInteger(c) > Max) {
        Max = ToInteger(c);
      }
      fprintf(OutputFile, "%c", c);
      Flag = 0;
      currentSize++;
      i++;
    } else if (!Flag) {
      Max++;
      fprintf(OutputFile, " - minimum number system: %d\n", Max);
      long long p = 1, result = 0;
      for (int l = i - 1; l >= 0; l--) {
        result += (p * ToInteger(Array[l]));
        p *= (Max);
      }
      Flag = 1;
      Max = 1;
      i = 0;
      if (c == EOF) break;
    }
  }

  fclose(InputFile);
  fclose(OutputFile);
  free(Array);
  return 0;
}
