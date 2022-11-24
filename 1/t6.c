#include <stdio.h>
#include <string.h>
#include <math.h>

char * FileNameGeneration(const char * str) {
  char * Output;
  int j = 0, Pointer = -1;
  int LenArgv = strlen(str);
  Output = malloc(sizeof(char) * (LenArgv + 4));
  if (Output == NULL)
    return NULL;
  for (j = LenArgv - 1; j >= 0; --j) {
    if (str[j] == '\\') {
      Pointer = j;
      break;
    } else return 1; //хз
  } 

  for (j = 0; j <= Pointer; j++) {
    Output[j] = str[j];
  }

  for (j = Pointer + 1; j < LenArgv+ 4; j++) {
    int l = j - (Pointer + 1);
    if (l == 0) {
      Output[j] = 'o';
    } else if (l == 1) {
      Output[j] = 'u';
    } else if (l == 2) {
      Output[j] = 't';
    } else if (l == 3) {
      Output[j] = '_';
    } else {
      Output[j] = str[j - 4];
    }
  }
  return Output;
}

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

  // генерация названия файла.
  char * Output = FileNameGeneration(argv[1]);

  FILE * OutputFile = fopen(Output, "w");
  if (OutputFile == NULL) {
    printf("error opening Output file\n");
    return 0;
  }

  char Array[50]; //сюда должно влезать число в какой-то системе счисления.
  int Flag = 0;
  int Max = 1;
  while ((c = fgetc(InputFile))) {
    if (c != ' ' && c != '\n' && c != EOF) {
      Array[i] = c;
      if (ToInteger(c) == -1) {
        printf("file contains invalid characters...");
        return 0;
      }
      if (ToInteger(c) > Max) {
        Max = ToInteger(c);
      }
      fprintf(OutputFile, "%c", c);
      Flag = 0;
      ++i;
    } else if (!Flag) {
      Max++;
      fprintf(OutputFile, " - minimum number system: %d  =>  ", Max);
      long long p = 1, result = 0;
      for (int l = i - 1; l >= 0; l--) {
        result += (p * ToInteger(Array[l]));
        p *= (Max);
      }
      fprintf(OutputFile, "%lld\n", result);
      Flag = 1;
      Max = 1;
      i = 0;
      if (c == EOF) break;
    }
  }

  fclose(InputFile);
  fclose(OutputFile);
  free(Output);
  return 0;
}

// 9 строка: проверки на корректность выделения памяти нет, пофиксить с возможностью обработки ситуации в вызывающем коде
// аналогично 1.5, с exit code в main при неуспешном завершении приложения +-
// 79 строка: а точно ли влезет?) используй дин массив и прикручивай realloc как было на семинаре