#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

unsigned int fileSymbolsCount(char* fileName) {
    FILE* input_file = fopen(fileName, "r");
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

// тут передаваться должен не char* arrrayFile, а FILE* file, соответственно строка 29 должна быть реализована не через arrayFile
// соответственно в функции find на 67 строке будет другой аргумент у функции
void searchSubstring(int fileSize, char* str, char* arrayFile, char* c) {
    int flag;
    int n = strlen(str);
    for (int i = 0; i < fileSize; i++) {
        flag = 1;
        for (int j = 0; j < n; j++) {
            if (str[j] != arrayFile[i + j]) {
                flag = 0;
                break;
            }
        }
        // если строка найдена - печатается номер файла
        if (flag) {
            printf("Entry in file: %s on position: %d\n", c, i);
        }
    }
}

void find(char* str, char* fileName, ...) {
    va_list factor; // указатель на необязательный параметр
    va_start(factor, fileName); // устанавливаем указатель
    int count = 0;
    for (char* c = fileName; *c;) {
        ++count;
        FILE* input_file = fopen(c, "r");
        if (input_file == NULL) {
            printf("Error: file cannot be open.\n");
            return;
        }
        char header;
        unsigned fileSize = 0;
        fileSize = fileSymbolsCount(c);

        // Запись файла в массив
        // нет смысла записывать файл в массив, тк считывание идет напрямую через fgetc, без необходимости копирования в массив-буффер
        char* arrayFile = (char*)malloc(sizeof(char) * fileSize);
        int i = 0;
        while ((header = fgetc(input_file)) != EOF) {
            if (header != '\n' && header != '\t') {
                arrayFile[i] = header;
                i++;
            }
        }

        searchSubstring(fileSize, str, arrayFile, c);
        if (count == 3) {
            break;
        }
        c = va_arg(factor, char*);
    }
    va_end(factor);
    return;
}

int main() {
    char str[100];
    char file1[100], file2[100], file3[100];
    gets_s(str);
    gets_s(file1);
    gets_s(file2);
    gets_s(file3);
    find(str, file1, file2, file3);
    return 0;
}
