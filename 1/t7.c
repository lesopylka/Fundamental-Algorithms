#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void Swap(int * a, int * b) {
  int c;
  c = * a;
  * a = * b;
  * b = c;
}

int main(void) {
  int n = 20, i, j;
  int * matrix = (int * ) malloc(sizeof(int) * n);
  srand(time(0));
  int min, max, nmin = 0, nmax = 0;
  for (i = 0; i < n; i++) {
    matrix[i] = (rand() % 100) * (rand() % 8 == 0 ? -1 : 1);
    printf("%d ", matrix[i]);

    if (i == 0) {
      max = matrix[i];
      min = matrix[i];
    } else {
      if (matrix[i] > max) {
        max = matrix[i];
        nmax = i;
      } else if (matrix[i] < min) {
        min = matrix[i];
        nmin = i;
      }
    }
  }
  Swap( & matrix[nmin], & matrix[nmax]);
  printf(" min = %d, max = %d\n", min, max);

  for (i = 0; i < n; i++) {
    printf("%d ", matrix[i]);
  }
  printf(" — result tranfer");

  free(matrix);

  return 0;
}