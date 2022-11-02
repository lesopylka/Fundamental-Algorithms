#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

typedef enum {
  male,
  female
}
Sex;

typedef struct {
  char * lastname;
  char * name;
  char * patronymic;
  char * birthDate;
  Sex sex;
  double salary;
}
Person;

typedef Person ListType;

typedef struct Node Node;
struct Node {
  ListType * data;
  Node * next;
};

typedef struct {
  Node * first;
  int size;
}
List;