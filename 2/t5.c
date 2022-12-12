#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void fill_array(int * array, int SIZE, int left_bound, int right_bound) { //проверять 
  for (int i = 0; i < SIZE; ++i) {
    array[i] = rand() % (right_bound - left_bound + 1) + left_bound;
  }
}

void swap(int * a, int * b) {
  int c;
  c = * a;
  * a = * b;
  * b = c;
}

void exchange_min_max(int * array, int SIZE) { 
  int * max = NULL;
  int * min = NULL;
  max = array;
  min = array;
  for (int i = 1; i < SIZE; ++i) {
    if (array[i] > * max) {
      max = array + i;
    }
    if (array[i] < * min) {
      min = array + i;
    }
  }
  swap(max, min);
}

int * unique_elems_array(int * array, int SIZE) {
  int * sub_array = (int * ) malloc(sizeof(int) * SIZE);
    if (sub_array = NULL){return 0;}
  int k = 0;
  int flag;
  for (int i = 0; i < SIZE; ++i) {
    flag = 1;
    for (int j = 0; j < i; ++j) {
      if (array[j] == array[i]) {
        flag = 0;
        break;
      }
    }
    if (flag) {
      sub_array[k] = array[i];
      ++k;
    }
  }
  int * final_array = (int * ) malloc(sizeof(int) * (k));
    if (final_array = NULL){return NULL;}
  for (int i = 0; i < k; ++i) {
    final_array[i] = sub_array[i];
  }
  for (int i = 0; i < k; ++i) {
    printf("%d\n", final_array[i]); //убрать принтф
  }
  free(sub_array);
  return final_array;
}

int main() {
  srand(time(NULL));
  const int SIZE = 40;
  int a, b;
  scanf("%d", & a);
  scanf("%d", & b);
  int * array = (int * ) malloc(sizeof(int) * SIZE); 
    if (array = NULL){return 1;}
  fill_array(array, SIZE, a, b);
  printf("select an option\n1: change max and min\n 2: create an array of unique elements\n");
  int option;
  for (int i = 0; i < SIZE; ++i) {
    printf("%d\n", array[i]);
  }
  scanf("%d", & option);
  switch (option) {
  case 1:
    exchange_min_max(array, SIZE);
    break;
  case 2:
    unique_elems_array(array, SIZE); //утечка плохо
    break;
  default:
    printf("Incorrect option\n");
  }
  free(array);
  return 0;
}