#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "FibonacciHeap.h"

const int TMP_STRING_LENGTH = 150;

enum VALIDATION_ENUM {
    ok = 0,
    noArguments = 1,
    wrongNumberOfArguments = 2,
    unexpectedToggles = 3,
    symbolBeforeTogglesNotFound = 4,
    inputFileError = 5,
    outputFileError = 6,
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
        case symbolBeforeTogglesNotFound:
            printf("Invalid Input: symbol '-' or '/' before toggles not found\n");
            break;
        case inputFileError:
            printf("Open error: input file\n");
            break;
        case outputFileError:
            printf("Open error: output file\n");
            break;
        default:
            printf("Unexpected error\n");
    }
}

enum VALIDATION_ENUM validationArg(int argc, char * argv[]) {
  FILE *ifp = fopen(argv[1], "r");
  
  if (argc == 1) {
    return noArguments;
  }
  if (argc != 4) {
    return wrongNumberOfArguments;
  }
  if (!((argv[3][1] == 'a' || argv[2][1] == 'd') && strlen(argv[3]) == 2)) {
    return unexpectedToggles;
  }
  if (!(argv[3][0] == '-' || argv[3][0] == '/')) {
    return symbolBeforeTogglesNotFound;
  }  
  if (ifp == NULL) {
    return inputFileError;
  }
  return ok;
}

void read(char *fileName) { 
  FILE * fp = fopen(fileName, "r");// чтение всего файла
  char tmpString[TMP_STRING_LENGTH];

  if (fp == NULL) {
    printValidationError(inputFileError);
    return;
  }

  while(1) {
    if(fgets(tmpString, TMP_STRING_LENGTH, fp) == NULL) {
      break;
    }
    puts(tmpString);
  }
  fclose(fp);
  //чтение строки -> чтение всех символов в строке -> чтение символа -> int c = fgetc(fp)
}

int main(int argc, char * argv[]) {
    enum VALIDATION_ENUM validationResult = validationArg(argc, argv);

    char* inputFilename = argv[1];
    char* outputFilename = argv[2];

    if (validationResult != ok) {
      printValidationError(validationResult);
      return 1;
    }

    read(inputFilename);
}


// 1. ввод аргументов +
// 2. валидация аргументов +
// 3. отображение ошибки (если есть) +
// 4. чтение файла +
// 5. валидация строк (проверка на соотвествие структуре)
// 6. заполнить фибоначчиеву пирамиду данными с пукта 5
// 7. сортировка пирамиды в зависимости от поданного флага
// 8. вывод отсортированной даты в файл 