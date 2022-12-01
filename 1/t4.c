// Дан файл, содержащий некоторую информацию, которая представлена в трех столбцах 
// (каждая строка файла содержит три лексемы). Необходимо перезаписать этот файл таким образом, 
// чтобы первый столбец стоял на месте второго, второй – на месте третьего, а третий – на месте первого.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

char **generate_matrix(int row, int col) {

    char **matrix = (char**)malloc(sizeof(char*) * row);

    if (matrix == NULL)
        return NULL;

    for (int i = 0; i < row; i++) {
        matrix[i] = (char*)malloc(sizeof(char) * col);

        if (matrix[i] == NULL)
            return NULL;
    }

    return matrix;
}

char* file_name_generation(const char* str) {
    int j, ukazatel_na_slash = -1;
    char* output = malloc(sizeof(char) * 300);
    for (j = 0; str[j] != '\0'; j++) {
        if (str[j] == '\\') {
            ukazatel_na_slash = j;
        }
    }

    for (j = 0; j <= ukazatel_na_slash; j++) {
        output[j] = str[j];
    }
    strcpy(output, "out.txt");
    return output;
}

void free_matrix(char **matrix, int row) {
    for (int i = 0; i < row; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("error! input path to the file");
        return 0;
    } else if (argc > 2) {
        printf("Сheck the correctness of the entered data");
        return 0;
    }

    FILE* input_file = fopen(argv[1], "r");

    if (input_file == NULL) {
        printf("Error opening input file\n");
        return 0;
    }


    int i, n = 16, j;

    char** matrix = generate_matrix(3, n);

    char* output = file_name_generation(argv[0]);


    FILE* output_file = fopen(output, "w");
    if (output_file == NULL) {
        printf("Error opening output file\n");
        return 0;
    }

    i = 0, j = 0;
    char ch, _c = 0;

    while (!feof(input_file)) {
        ch = fgetc(input_file);
        if (!isspace(ch)) {
            if(j >= n) {
                n *= 2;
                matrix[i] = realloc(matrix[i], n);
            }
            matrix[i][j] = ch;
            j++;
        } else if (isspace(ch) && !isspace(_c)){
            if(j >= n) {
                n *= 2;
                matrix[i] = realloc(matrix[i], n);
            }
            matrix[i][j] = '\0';
            i++;
            if (i == 3) {
                for (int k = 0; k < 3; ++k){
                    fprintf(output_file, "%s ", matrix[(k + 2) % 3]);
                }
                fprintf(output_file, "\n");
                i = 0;
            }
            j = 0;
        }
        _c = ch;
    }

    free_matrix(matrix, 3);

    fclose(input_file);
    fclose(output_file);

    input_file = fopen(output, "r");
    output_file = fopen(argv[1], "w");

    char c;
    while((c = getc(input_file)) != EOF) {
        fprintf(output_file, "%c", c);
    }
    fclose(input_file);
    fclose(output_file);

    free(output);
    remove(output);
    return 0;
}
