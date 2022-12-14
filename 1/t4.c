// Дан файл, содержащий некоторую информацию, которая представлена в трех столбцах 
// (каждая строка файла содержит три лексемы). Необходимо перезаписать этот файл таким образом, 
// чтобы первый столбец стоял на месте второго, второй – на месте третьего, а третий – на месте первого.

//3 1 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

char ** generate_matrix(int row, int col) {

  char ** matrix = calloc(row, sizeof(char * ));

  if (matrix == NULL)
    return NULL;

  for (int i = 0; i < row; i++) 
  {
    matrix[i] = calloc(col, sizeof(char));

    if (matrix[i] == NULL) 
    {
      for (int j = 0; j <= i; j++)
        free(matrix[j]);
      free(matrix);
      return NULL; 
    }
  }

  return matrix;
}

void swap_col(char **mat, int i, int j, int rw)
{
  char tmp;
  for(int l=0; l<rw; l++)
    {
      tmp = mat[l][i];
      mat[l][i] = mat[l][j];
      mat[l][j] = tmp;
    }
}

void free_matrix(char **matrix, int row) {
  for (int i = 0; i < row; i++) {
    free(matrix[i]);
  }
  
  free(matrix);
}

int main(int argc, char * argv[]) {

  if (argc < 2) {
    printf("\nerror! input path to the file\n");
    return 0;
  } else if (argc > 2) {
    printf("\nСheck the correctness of the entered data\n");
    return 0;
  }

  FILE * input_file = fopen(argv[1], "r");

  if (input_file == NULL) {
    printf("\nError opening input file\n");
    return 0;
  }

  int i = 0, n = 1, j = 0;
  char ch;

  while ((ch = fgetc(input_file)) != EOF) 
    if (ch == '\n') 
      n++;
  rewind(input_file);

  char **matrix = generate_matrix(n, 3);

  while ((ch = fgetc(input_file)) != EOF) 
  {
    if(ch != ' ')
    {
      if (ch == '\n') 
      {
        j++;
        i=0;
      }
      else
      {
        matrix[j][i] = ch;
        i++;
      }
    }
  }

  swap_col(matrix, 1, 2, n);
  swap_col(matrix, 0, 1, n);

  fclose(input_file);
  FILE * output_file = fopen(argv[1], "w");

  for (i=0; i<n; i++)
  {
    for (j=0; j<3; j++)
    {
      fprintf(output_file, "%c ", matrix[i][j]);
    }
    fprintf(output_file, "\n");
  }
  fclose(input_file);
  free_matrix(matrix, n);
  return 0;
}
