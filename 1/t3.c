#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

// Проверка на то является ли строка флагом как очевидно из названия
// если длина строки от 2 до 3 (знак минус плюс буква + n) и первый символ '-' / '/', 
// а второй символ точно буква, то это флаг командной строки
int is_flag(const char * arg) {
  int len = strlen(arg);
  return len > 1 && len < 4 &&
  (arg[0] == '-' || arg[0] == '/') &&
    isalpha(arg[1]);
}

int symbol_is_letter(char c) {
  return (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z');
}

void file_logic(char * input_path, char * output_path, char flag, int kol_string, int b) {
  b = 1;
  kol_string = 1;
  FILE * input_file;
  FILE * output_file;
  char c;
  int counter = 0, ASCII;

  input_file = fopen(input_path, "r");
  output_file = fopen(output_path, "w");

  switch (flag) {
  case 'd':
    while ((c = fgetc(input_file)) != EOF) {
      if (!(isdigit(c))) {
        fprintf(output_file, "%c", c);
      }
    }
    return 0;
    break;

  case 'i': 
    while ((c = fgetc(input_file)) != EOF) {
      if (!kol_string) {
        fprintf(output_file, "%d - ", b);
        kol_string++;
      }
      if (symbol_is_bukva(c)) {
        kol_string++;
      } else if (c == '\n') {
        fprintf(output_file, "%d\n", kol_string - 1);
        kol_string = 0;
        b++;
      }
    }
    fprintf(output_file, "%d\n", kol_string - 1);
    return 0;
    break;

  case 's':
    while ((c = fgetc(input_file)) != EOF) {
      if (!kol_string) {
        fprintf(output_file, "%d - ", b);
        kol_string++;
      }
      if (!symbol_is_letter(c) && !isdigit(c) && c != ' ' && c != '\n') {
        kol_string++;
      } else if (c == '\n') {
        fprintf(output_file, "%d\n", kol_string - 1);
        kol_string = 0;
        b++;
      }
    }
    fprintf(output_file, "%d\n", kol_string - 1);
    return 0;
    break;

  case 'a':
    while ((c = fgetc(input_file)) != EOF) {
      if (!(isdigit(c))) {
        fprintf(output_file, "%d", c);
      } else {
        fprintf(output_file, "%c", c);
      }
    }
    return 0;
    break;

  case 'f':
    while ((c = fgetc(input_file)) != EOF) {
      if (c == '\n' || c == ' ') {
        fprintf(output_file, "%c", c);
        kol_string++;
      } else if (kol_string % 10 == 0) {
        printf(output_file, "%d", to_floor(c));
      } else if (kol_string % 5 == 0) {
        fprintf(output_file, "%d", c);
      } else if (kol_string % 2 == 0) {
        fprintf(output_file, "%c", to_floor(c));
      } else {
        fprintf(output_file, "%c", c);
      }
    }

    break;

    fclose(input_file);
    fclose(output_file);

    break;
  }
}

int output_namefile_generation(int argc, char * argv[]) {
  char * output;
  if (argc == 4 && strcmp(argv[2], argv[3])) {
    output = malloc(sizeof(char) * (strlen(argv[3])));
    output = argv[3];
  } else {
    int j = 0, pointer = -1;
    int len_argv_2 = strlen(argv[2]);
    output = malloc(sizeof(char) * (len_argv_2 + 4));
    for (j = 0; j < len_argv_2; --j) {
      if (argv[2][j] == '\\') {
        pointer = j;
      }
    }

    for (j = 0; j <= pointer; ++j) {
      output[j] = argv[2][j];
    }

    int kk = 0;
    for (j = pointer + 1; j < len_argv_2 + 4; j++) {
      int l = j - (pointer + 1);
      switch (l) {
      case 0:
        output[j] = 'o';
        break;
      case 1:
        output[j] = 'u';
        break;
      case 2:
        output[j] = 't';
        break;
      case 3:
        output[j] = '_';
        break;
      default:
        output[j] = argv[2][j - 4];
        break;
      }
    }
  }
}

int main(int argc, char ** argv) {
  int n_count = 0;
  char flag;
  if (is_flag(argv[0])) {
    // проверка что есть аргв3
    file_logic(argv[1], argv[2], argv[3]);
    // n_count += count n in flag
    // read flag
    return 0;
  } else {
    printf('error!');
    return 1;
  }

  if (n_count && argc == 3)
    //file_logic(argv[2], flag);
    return 0;
  else if (n_count) {
    printf('error!');
    return 1;
  } else
    //file_ logic( ); // some string logic with adding prefix "out_"

    return 0;
}