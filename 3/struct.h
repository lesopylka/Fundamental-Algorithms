#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

typedef struct {
  unsigned int id;
  char * lastname;
  char * name;
  int course;
  char * group;
  int * marks;
}
Student;