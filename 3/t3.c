#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "FibonacciHeap.h"

const int TMP_STRING_LENGTH = 150;

const char INPUT_FILE_DELIMETER = ' ';
struct RawInput {
  struct Employee employee;
  int id;
};

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

 struct RawInput readStr(char* str) {
  char *w;
  int state = 0;
  w = strtok(str, &INPUT_FILE_DELIMETER);
  char *name, *surname;
  int id;
  double wage;
  while(w != NULL) {
    if (state == 0) {
      id = atoi(w);
    }
    if (state == 1) {
      name = w;
    }
    if (state == 2) {
      surname = w;
    }
    if (state == 3) {
      wage = strtod(w, NULL);
    }
    state++;
    w = strtok(NULL, &INPUT_FILE_DELIMETER);
  }
  struct Employee employee = { .name=name, .surname=surname, .wage=wage};

  struct RawInput rawInput = { .id=id, .employee=employee};
  return rawInput;
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

int read(char *fileName, FIB_HEAP *heap) { 
  FILE * fp = fopen(fileName, "r");// чтение всего файла

  if (fp == NULL) {
    return 1;
  }

  char tmpString[TMP_STRING_LENGTH];

  while(1) {
      if(fgets(tmpString, TMP_STRING_LENGTH, fp) == NULL) {
        break;
      }
      struct RawInput tmp = readStr(tmpString);
      NODE *node = malloc(sizeof(NODE));
      insertion(heap, node, tmp.id, tmp.employee);
    }
  fclose(fp);

  return 0;
  //чтение строки -> чтение всех символов в строке -> чтение символа -> int c = fgetc(fp)
}

int fileCheck(char* fileName) {
  FILE* input_file = fopen(fileName, "r");
  if (input_file == NULL) {   
    printf("Error: file cannot be open.\n"); 
  }

  
  char header;
  unsigned int count = 0;

  while ((header = fgetc(input_file)) != EOF) {
    while(header != '/n') { 
      if(!isDigit(header))
        printf("Error: incorrect id.\n");//допилить норм обработку
      header = fgetc(input_file);
    } 
  }
}

int main(int argc, char * argv[]) {
    enum VALIDATION_ENUM validationResult = validationArg(argc, argv);

    char* inputFileName = argv[1];
    char* outputFileName = argv[2]; 

    if (validationResult != ok) {
      printValidationError(validationResult);
      return 1;
    }

    FIB_HEAP *heap = make_fib_heap();
 
    if (read(inputFileName, heap)) {
      printValidationError(inputFileError);
    }
}

// 1. ввод аргументов +
// 2. валидация аргументов +
// 3. отображение ошибки (если есть) +
// 4. чтение файла +
// 5. валидация строк (проверка на соотвествие структуре)
// 6. заполнить фибоначчиеву пирамиду данными с пукта 5 +
// 7. сортировка пирамиды в зависимости от поданного флага
// 8. вывод отсортированной даты в файл 