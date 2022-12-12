#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int main(int argc, char* argv[]) {
    if(argc < 3) {
        printf("Error: not enough arguments.\n");
        return 1;
    }

    char *input_file_path = argv[2];
    int slashIndex = 0;
    for (int x = strlen(input_file_path) - 1; x >= 0; x--) {
        if (input_file_path[x] == '/' || input_file_path[x] == '\\') {
            slashIndex = x;
            break;
        }
    }
    // получение выходного пути файла
    char * file_path = (char *) malloc ( (strlen(input_file_path) + 5) * sizeof(char)); //char file_path[strlen(input_file_path) + 4]; 
    if (file_path == NULL) {return 2;} 
    if (slashIndex) {
        strncat(file_path, input_file_path, slashIndex + 1);
    }
    strcat(file_path, "out_");
    strcat(file_path, input_file_path + slashIndex + (slashIndex == 0 ? 0 : 1));
    // strncat(file_path, "out_", strlen(input_file_path)-strlen(extension_of_file)); // добавили out_ к названию
    // strncat(file_path, extension_of_file, strlen(input_file_path)-strlen(extension_of_file) + 4); // добавим расширение к названию файла
    char* output_file_path = file_path;

    int flag_argv_indx = 1;
    if(argv[flag_argv_indx][0] != '/' && argv[flag_argv_indx][0] != '-') {
        printf("Error: flag not found.\n");
        return 1;
    }
    //проверка флага на корректность и если есть n то определяю файл выходной по аргв
    int task_letter_in_flag = 1;
    if(argv[flag_argv_indx][task_letter_in_flag] == 'n') {
        if(strlen(argv[flag_argv_indx]) < 3) {
            printf("Error: incorrect flag.\n");
            return 1;
        }
        task_letter_in_flag = 2;
        if(argc == 4) {
            output_file_path = argv[3];
        }
    }

    FILE* input_file = fopen(input_file_path, "r");
    if(input_file == NULL) {
        printf("Error: input file cannot be open.\n");
        return -2;
    
    }
    FILE* output_file = fopen(output_file_path, "a"); 
    if(output_file == NULL) {
        printf("Error: output file cannot be open.\n");
        fclose(input_file);
        return -1;
    }
    char c;
    int kol_string = 1;
    switch (argv[flag_argv_indx][task_letter_in_flag]) {
        case 'd':
            // необходимо исключить символы цифр из файла
            while ((c = fgetc(input_file)) != EOF) {
                if (!(isdigit(c))) {
                    fputc(c, output_file);
                }
            }
            break;
        case 'i':
            // необходимо в выходной файл написать, сколько раз в каждой
            // строке встречаются символы букв
            while ((c = fgetc(input_file)) != EOF) {
                int count = 0;
                while (c != '\n') {
                    if (isalpha(c)) {
                        count++;
                    }
                    fprintf(output_file, "string = %d\n", count);
                    count = 0;
                }
            }
            break;
        case 's':
            // необходимо в выходной файл написать, сколько раз в каждой
            // строке встречаются символы, отличные от символов цифр, символов
            // букв и символа пробела
            while ((c = fgetc(input_file)) != EOF) {
                int count = 0;
                while (c != '\n') {
                    if (!isalnum(c)) {//вместо пробела можно !isspace но там не только пробелл
                        count++;
                    }
                    fprintf(output_file, "string = %d\n", count);
                    count = 0;
                }
            }
            break;
        case 'a':
            // необходимо заменить символы, отличные от цифр, их строковым
            // представлением ASCII-кода
            while ((c = fgetc(input_file)) != EOF) {
                fputc(c, output_file);
            }
            break;
        case 'f':
            // создать выходной файл таким образом, чтобы в каждой в каждой
            // второй лексеме все буквы были переписаны в строчные, а также в
            // каждой пятой лексеме все символы были заменены на
            // эквивалентные им ASCII-коды
            while ((c = fgetc(input_file)) != EOF) {
                if (c == '\n' || c == ' ') {
                    fputc(c, output_file);
                    kol_string++;
                } else if (kol_string % 10 == 0) {
                    fputc(floor(c), output_file);
                } else if (kol_string % 5 == 0) {
                    fputc(c, output_file);
                } else if (kol_string & 1 == 0) {
                    fputc(floor(c), output_file);
                } else {
                    fputc(c, output_file);
                }
            }
            break;
    }
    fclose(input_file);
    fclose(output_file);
    free(file_path);
    return 0;
}
