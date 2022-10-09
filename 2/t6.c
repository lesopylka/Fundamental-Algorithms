#include <stdio.h>
#include <stdarg.h>

unsigned int fileSymbolsCount(char * fileName) {
  FILE * input_file = fopen(fileName, "r");
  if (input_file == NULL) {
    printf("Error: file cannot be open.\n");
  }
  char header;
  unsigned int count = 0;
  while ((header = fgetc(input_file)) != EOF) {
    if (header != '\n' && header != '\t') {
      count++;
    }
  }
  return (count);
}

void ilyaneebipls(char * str, char * fileName, ...) {
  va_list factor; // указатель на необязательный параметр
  va_start(factor, fileName); // устанавливаем указатель

  for (char * c = fileName;* c; c++) {
    FILE * input_file = fopen(fileName, "r");
    if (input_file == NULL) {
      printf("Error: file cannot be open.\n");
    }
    char header;
    unsigned int fileSize = 0;
    fileSize = fileSymbolsCount(fileName);
    char * arrayFile = (char * ) realloc(sizeof(char) * fileSize);
    int i = 0;
    while ((header = fgetc(input_file)) != EOF) {
      if (header != '\n' && header != '\t') {
        arrayFile[i] = header;
        i++;
      }
    }

  int n = sizeof(str);
  for(int i = 0; i < fileSize; i++) {
  for(int j=0; j < n; j++) {
  if (str[j] = arrayFile[i+j]) {

      }
    }
  }
/*
        сравниваем str с arrayfile, допустим в str 3 элемента. Сравниваем  str[0] с arrayfile[0], 
        str[1] с arrayfile[1],str[2] с arrayfile[2], увеличиваем счетчик int i=0 на 1 и сравниваем уже
        str[0] с arrayfile[1], str[1] с arrayfile[2],str[2] с arrayfile[3] и так до конца. Если все три
        сравнения были успешны, то мы нашли вхождение подстроки в строке.
    */
  }
  va_end(factor);
}

int main() {
  ilyaneebipls("abobus", "1.txt", "2.txt", "3.txt");
  return 0;
}