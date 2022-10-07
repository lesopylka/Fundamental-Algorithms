#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double *generate_matrix(int *size) {
  *size = rand() % 50 + 10;

  double *matrix = (double*) malloc(sizeof(double) **size);
  for (int i = 0; i < *size; i++) {
    matrix[i] = rand() % 500 - 100;
  }

  return matrix;
}

void output_matrix(double *matrix, int size) {
  for (int i = 0; i < size; i++) {
    printf("%.1lf ", matrix[i]);
  }
}

double *result_matrix(double *matrix_1, int sizem1, double *matrix_2, int sizem2) {
  double *result = NULL;

  result = (double*) malloc(sizeof(double*) *sizem1);

  for (int i = 0; i < sizem1; i++) {
    result[i] = matrix_1[i] + ((i >= sizem2) ? matrix_2[sizem2 - 1] : matrix_2[i]);
  }

  return result;
}

int main() {
  srand(time(0));
  int sizem1 = 0;
  int sizem2 = 0;
  double *matrix_1 = generate_matrix(&sizem1);
  double *matrix_2 = generate_matrix(&sizem2);

  printf("matrix A:\n");
  output_matrix(matrix_1, sizem1);
  printf("matrix B:\n");
  output_matrix(matrix_2, sizem2);

  printf("matrix C:\n");
  double *matrix_3 = result_matrix(matrix_1, sizem1, matrix_2, sizem2);
  output_matrix(matrix_3, sizem1);

  free(matrix_1);
  free(matrix_2);
  free(matrix_3);
  return 0;
}