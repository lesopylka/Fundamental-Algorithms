#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ERROR 0.01

void FreeMatrix(double ** Matrix, int Row) {
  for (int i = 0; i < Row; i++) {
    free(Matrix[i]);
  }
  free(Matrix);
}

double ** GenerateMatrix(int * Row, int * Col) {
  //*Row = rand() % 10 + 1;
  //*Col = rand() % 10 + 1;

  double ** Matrix = (double ** ) malloc(sizeof(double * ) * * Row);
  for (int i = 0; i < * Row; i++) {
    Matrix[i] = (double * ) malloc(sizeof(double) * * Col);
    for (int j = 0; j < * Col; j++) {
      Matrix[i][j] = rand() % 200 - 100;
    }
  }

  return Matrix;
}

void output_matrix(double ** Matrix, int Row, int Col) {
  for (int i = 0; i < Row; i++) {
    for (int j = 0; j < Col; j++) {
      printf("%10.0lf ", Matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

double ** MultiplyMatrix(double ** Matrix1, int Row1, int Col1, double ** Matrix2, int Row2, int Col2) {
  double ** result = NULL;

  if (Col1 == Row2) {
    result = (double ** ) malloc(sizeof(double * ) * Row1);
    for (int i = 0; i < Row1; i++) {
      result[i] = (double * ) malloc(sizeof(double) * Col2);
    }

    for (int i = 0; i < Row1; i++) {
      for (int j = 0; j < Col2; j++) {
        result[i][j] = 0;
        for (int k = 0; k < Col1; k++) {
          result[i][j] += Matrix1[i][k] * Matrix2[k][j];
        }
      }
    }
  }

  return result;
}

void row_decrement(double * RowBegin, double * Row, double dec, int Col) {
  for (int i = 0; i < Col; i++) {
    Row[i] -= dec * RowBegin[i];
  }
}

double determinant(double ** Matrix, int Row, int Col) {
  if (Row == Col) {
    double Res = 1.0;
    int Size = Row;
    double ** CopyMatrix = (double ** ) malloc(sizeof(double * ) * Size);

    for (int i = 0; i < Size; i++) {
      CopyMatrix[i] = (double * ) malloc(sizeof(double) * Size);
      for (int j = 0; j < Size; j++) {
        CopyMatrix[i][j] = Matrix[i][j];
      }
    }

    for (int RowBegin = 0; RowBegin < Size; RowBegin++) {
      for (int RowDec = RowBegin + 1; RowDec < Size; RowDec++) {
        row_decrement(CopyMatrix[RowBegin], CopyMatrix[RowDec], CopyMatrix[RowDec][RowBegin] / CopyMatrix[RowBegin][RowBegin], Size);
      }
    }

    for (int i = 0; i < Row; i++) {
      Res *= CopyMatrix[i][i];
    }

    FreeMatrix(CopyMatrix, Size);

    return Res;
  }

  return ERROR;
}

int main() {
  srand(time(0));
  int Row1 = 3;
  int Col1 = 3;
  int Row2 = 3;
  int Col2 = 3;
  double ** Matrix1 = GenerateMatrix( & Row1, & Col1);
  double ** Matrix2 = GenerateMatrix( & Row2, & Col2);
  double ** multiply = MultiplyMatrix(Matrix1, Row1, Col1, Matrix2, Row2, Col2);

  printf("A:\n");
  output_matrix(Matrix1, Row1, Col1);
  printf("B:\n");
  output_matrix(Matrix2, Row2, Col2);

  if (multiply != NULL) {
    printf("A x B:\n");
    output_matrix(multiply, Row1, Col2);
  } else {
    fprintf(stderr, "%s\n\n", "A x B:\nMultiplication cannot be done");
  }

  if (determinant(Matrix1, Row1, Col1) != ERROR) {
    printf("det(A) = %lf\n", determinant(Matrix1, Row1, Col1));
  } else {
    fprintf(stderr, "%s\n\n", "det(A): Invalid count of Row and Col");
  }

  if (determinant(Matrix2, Row2, Col2) != ERROR) {
    printf("det(B) = %lf\n", determinant(Matrix2, Row2, Col2));
  } else {
    fprintf(stderr, "%s\n\n", "det(B): Invalid count of Row and Col");
  }

  if (multiply != NULL) {
    if (determinant(multiply, Row1, Col2) != ERROR) {
      printf("det(A x B) = %lf\n", determinant(multiply, Row1, Col2));
    } else {
      fprintf(stderr, "%s\n\n", "det(A x B): Invalid count of Row and Col");
    }
    FreeMatrix(multiply, Row1);
  } else {
    fprintf(stderr, "%s\n\n", "det(A x B): Multiplication cannot be done");
  }

  FreeMatrix(Matrix1, Row1);
  FreeMatrix(Matrix2, Row2);

  return 0;
}


// 19, 21, 44, 46, 72, 75 строка: проверки на корректность выделения памяти нет, пофиксить с возможностью обработки ситуации в вызывающем коде
// в функции умножения стоит проверить, можно ли вообще умножить такие две матрицы
// в main непонятно зачем сначала сравнивать возвращаемое значение функции, считающей определитель, с ERROR, а потом заново вычислять определитель
// а если определитель матрицы будет равен ERROR вдруг? обрабатывай такие ситуации через статус-коды
// сравнивать вещественные числа нужно исключительно с заданной точностью вследствие формата их хранения