#include <stdio.h>
#include <stdarg.h>
 
void ilyaneebipls(char* str, char* fileName, ...) {
    int d; 
    double f;
    va_list factor;         // указатель на необязательный параметр
    va_start(factor, fileName);   // устанавливаем указатель

    for(char *c = fileName; *c; c++){
        FILE* input_file = fopen(fileName, "r");
        if(input_file == NULL) {
            printf("Error: file cannot be open.\n");
        }
    }
    va_end(factor);
}

int main() {   
    ilyaneebipls();
    return 0;
}