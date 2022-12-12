#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

//вынести в отдельный файл для 6.2
// typedef struct {
//   char * data;
//   unsigned int len;
// }
// String;

// int comp(char a, char b) {
//   return a - b;
// }

// void freeAll(int count, ...) {
//   va_list args;
//   va_start(args, count);
//   for (int x = 0; x < count; x++) {
//     free(va_arg(args, void * ));
//   }
// }

// int createString(String ** result,
//   const char * string) {
//   int len = 0;
//   char * data = NULL;
//   String * res;
//   if (string != NULL) {
//     while (string[len] != '\0')
//       len++;
//     if (len == 0)
//       return 2;
//     data = (char * ) malloc(sizeof(char) * len);
//     if (data == NULL) {
//       return 1;
//     }
//     memcpy(data, string, len * sizeof(char));
//   }
//   res = (String * ) malloc(sizeof(String));
//   if (res == NULL) {
//     if (data != NULL)
//       free(data);
//     return 1;
//   }
//   res -> len = len;
//   res -> data = data;
//   * result = res;
//   return 0;
// }

// void clearString(String * string) {
//   if (string -> len == 0)
//     return;
//   free(string -> data);
//   string -> len = 0;
// }

// int compareStrings(String * str1, String * str2, int( * comparator)(char, char)) {
//   for (int x = 0; x < (str1 -> len > str2 -> len ? str2 -> len : str1 -> len); x++) {
//     int code = comparator(str1 -> data[x], str2 -> data[x]);
//     if (code > 0) {
//       return 1;
//     } else if (code < 0) {
//       return -1;
//     }
//   }
//   if (str1 -> len > str2 -> len)
//     return 1;
//   if (str1 -> len < str2 -> len)
//     return -1;
//   return 0;
// }

// void freeString(String * string) {
//   clearString(string);
//   free(string);
// }

// int copyString(String * string, String * destination) {
//   clearString(destination);
//   char * data = (char * ) malloc(sizeof(char) * string -> len);
//   if (data == NULL) {
//     return 1;
//   }
//   memcpy(data, string -> data, string -> len * sizeof(char));
//   destination -> len = string -> len;
//   destination -> data = data;
//   return 0;
// }

// int concatStrings(String ** result, int count, ...) {
//   String ** strings = (String ** ) malloc(sizeof(String * ) * count);
//   if (strings == NULL)
//     return 1;
//   va_list args;
//   va_start(args, count);
//   unsigned int resLen = 0;
//   for (int x = 0; x < count; x++) {
//     strings[x] = va_arg(args, String * );
//     resLen += strings[x] -> len;
//   }
//   char * data = (char * ) malloc(sizeof(char) * resLen);
//   if (data == NULL) {
//     free(strings);
//     return 1;
//   }
//   String * res = (String * ) malloc(sizeof(String));
//   if (res == NULL) {
//     freeAll(2, data, strings);
//     return 1;
//   }
//   resLen = 0;
//   for (int x = 0; x < count; x++) {
//     memcpy(data + resLen, strings[x] -> data, strings[x] -> len * sizeof(char));
//     resLen += strings[x] -> len;
//   }
//   res -> len = resLen;
//   res -> data = data;
//   * result = res;
//   free(strings);
//   return 0;
// }

// int duplicateString(String ** result, String * string) {
//   switch (createString(result, NULL)) {
//   case 1:
//     return 1;
//   case 2:
//     return 2;
//   }
//   switch (copyString(string, * result)) {
//   case 1:
//     freeString( * result);
//     return 3;
//   }
//   return 0;
// }

int main(int argc, char * argv[]) {
  String * s1, * s2, * s3, * s4;
  createString( & s1, "kek");
  createString( & s2, "lol");
  printString(s1);
  printf("\n");
  printString(s2);
  printf("\n");
  concatStrings( & s3, 2, s1, s2);
  printString(s3);
  printf("\n");
  duplicateString( & s4, s3);
  printString(s4);
  printf("\n");
  printf("%d\n", compareStrings(s1, s3, comp));

  freeAll(4, s1, s2, s3, s4);
  return 0;
}


from math import sqrt
import random as rnd

def s(point1, point2):
    return sqrt((point1[0] - point2[0])**2 + (point1[1] - point2[1])**2)

n = int(input("Введите количество строк: "))
mass = [(rnd.randint(1,99), rnd.randint(1,99)) for i in range(n)]

[print(*obj) for obj in mass]

max = 0
max_index = [0, 0]

for i in range(n):
    for j in range(i + 1, n):
        l = s(mass[i], mass[j])
        if max < l:
            max = l
            max_index = [i, j]

print(f"{int(max)}: p1: {mass[max_index[0]]}, p2: {mass[max_index[1]]}")
