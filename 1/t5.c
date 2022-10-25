#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char * argv[]) {
  // генерация названия файла.

  char * output;
  int j = 0, pointer = -1;
  int len_argv = strlen(argv[0]);
  output = malloc(sizeof(char) * 7);
  for (j = 0; j < len_argv; j++) {
    if (argv[0][j] == '\\') {
      pointer = j;
    }
  }

  for (j = 0; j <= pointer; j++) {
    output[j] = argv[0][j];
  }

  for (j = pointer + 1; j < pointer + 9; j++) {
    int l = j - (pointer + 1);
    if (l == 0) {
      output[j] = 'i';
    } else if (l == 1) {
      output[j] = 'd';
    } else if (l == 2) {
      output[j] = 'k';
    } else if (l == 3) {
      output[j] = '.';
    } else if (l == 4) {
      output[j] = 't';
    } else if (l == 5) {
      output[j] = 'x';
    } else if (l == 6) {
      output[j] = 't';
    } else if (l == 7) {
      output[j] = '\0';
    }
  }

  FILE * output_file = fopen(output, "w");

  if (output_file == NULL) {
    printf("file is not open");
    return 0;
  }

  char * toggles[3] = {
    "-fi",
    "-cin",
    "-arg"
  };

  FILE * input_file;
  FILE * input_files_in_file;
  char c;
  char mass[300];

  int i, good_flag = 0;
  for (i = 0; i < 5; i++) {
    if (!strcmp(toggles[i], argv[1])) {
      good_flag = 1;
      switch (toggles[i][1]) {
      case 'fi':
        input_file = fopen(argv[2], "r");
        if (input_file == NULL) {
          printf("error opening input file\n");
          return 0;
        }

        while (1) {
          if (fscanf(input_file, "%s", & mass) == 1) {
            input_files_in_file = fopen(mass, "r");
            if (input_files_in_file != NULL) {
              while ((c = fgetc(input_files_in_file)) != EOF) {
                fprintf(output_file, "%c", c);
              }
              fclose(input_files_in_file);
            }
          } else {
            break;
          }
        }
        fclose(input_file);
        break;
      case 'cin':
        while (1) {
          if (scanf("%s", & mass) == 1) {
            input_files_in_file = fopen(mass, "r");
            if (input_files_in_file != NULL) {
              while ((c = fgetc(input_files_in_file)) != EOF) {
                fprintf(output_file, "%c", c);
              }
              fclose(input_files_in_file);
            }
          } else {
            break;
          }
        }
        break;
      case 'arg':
        for (int file = 2; file < argc; ++file) {
          input_files_in_file = fopen(argv[file], "r");
          if (input_files_in_file != NULL) {
            while ((c = fgetc(input_files_in_file)) != EOF) {
              fprintf(output_file, "%c", c);
            }
            fclose(input_files_in_file);
          }
        }
        break;
      }
    }
  }
  if (!good_flag) {
    printf("invalid flag entered!\n");
    return 0;
  }

  fclose(output_file);
  free(output);

  return 0;
}