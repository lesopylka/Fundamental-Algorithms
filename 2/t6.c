#include <stdio.h>
#include <stdarg.h>

unsigned int fileSymbolsCount(char *fileName){
    FILE* input_file = fopen(fileName, "r");
        if(input_file == NULL) {
            printf("Error: file cannot be open.\n");
        }
        char header;
        unsigned int count = 0;
        while ((header = fgetc(input_file)) != EOF) {
                    if (header != '\n' && header != '\t') {
                        count++;
                    }
                }
    return(count);
}
 
void ilyaneebipls(char* str, char* fileName, ...) {
    va_list factor;         // указатель на необязательный параметр
    va_start(factor, fileName);   // устанавливаем указатель

    for(char *c = fileName; *c; c++){
        FILE* input_file = fopen(fileName, "r");
        if(input_file == NULL) {
            printf("Error: file cannot be open.\n");
        }
        char header;
        int fileSize = 0;
        while ((header = fgetc(input_file)) != EOF) {
                if (!(isdigit(c))) {

                }
            }
    }
    va_end(factor);
}

int main() {   
    ilyaneebipls();
    return 0;
}