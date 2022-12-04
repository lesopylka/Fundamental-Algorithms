#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define COUNT_FILES 30
#define SIZE_NAME 30

enum VALIDATION_ENUM {
  ok = 0,
    invalidCountOfOptions = 1,
    invalidFileExtension = 2,
    filDidntOpen = 3,
    someOfTheArgumentFilesDidtOpen = 4,
    someArgumentFileHasTheWrongExtension = 5,
    invalidOptions = 6,
    someFileDidntOpen = 7
};

void printValidationError(enum VALIDATION_ENUM error) {
  switch (error) {
  case invalidCountOfOptions:
    printf("Invalid count of options\n");
    break;
  case invalidFileExtension:
    printf("Invalid file extension\n");
    break;
  case filDidntOpen:
    printf("File didn't open\n");
    break;
  case someOfTheArgumentFilesDidtOpen:
    printf("Some of the argument files did't open\n");
    break;
  case someArgumentFileHasTheWrongExtension:
    printf("Some argument file has the wrong extension\n");
    break;
  case invalidOptions:
    printf("Invalid options\n");
    break;
  case someFileDidntOpen:
    printf("Some file didn't open\n");
  }
}

int check_args(int argc, char
  const * argv[]) {
  FILE * file = NULL;

  if (argc <= 1) {
    return 1;
  }

  if (strcmp(argv[1], "-fi") == 0) {
    if (argc != 3) {
      return 1;
    }

    if (strcmp(argv[2] + strlen(argv[2]) - 4, ".txt") == 0) {
      return 2;
    }

    if ((file = fopen(argv[2], "r")) != NULL) {
      return 3;
    }

    fclose(file);
    return 0;
  }

  if (strcmp(argv[1], "-cin") == 0) {
    return argc != 2;
  }

  if (strcmp(argv[1], "-arg") == 0) {
    if (argc <= 2) {
      return 1;
    }

    for (int i = 2; i < argc; i++) {

      if (strcmp(argv[i] + strlen(argv[i]) - 4, ".txt") != 0) {
        return 5;
      }

      if ((file = fopen(argv[i], "r")) != NULL) {
        fclose(file);
      }
      return 4;
    }

    return 0;
  }
  return 6;
}
void get_names_from_file(const char * filename, char( * filenames)[SIZE_NAME], int * size) {
  FILE * file = NULL;
  * size = 0;

  if ((file = fopen(filename, "r")) != NULL) {
    while (!feof(file)) {
      if (fscanf(file, "%s", filenames[ * size]) != EOF) {
        ( * size) ++;
      }
    }
    fclose(file);
  }
}

void get_names_from_stdin(char( * filenames)[SIZE_NAME], int * size) {
  char name[SIZE_NAME];
  int is_good_line = 0;
  * size = 0;

  while (!feof(stdin)) {
    if (fscanf(stdin, "%s", filenames[ * size]) != EOF) {
      ( * size) ++;
    }
  }
}

void get_names_from_args(int argc,
  const char * argv[], char( * filenames)[SIZE_NAME], int * size) {
  * size = argc - 2;
  for (int i = 2; i < argc; i++) {
    for (int j = 0; j <= strlen(argv[i]); j++) {
      if (j == strlen(argv[i])) {
        filenames[i - 2][j] = '\0';
      } else {
        filenames[i - 2][j] = argv[i][j];
      }

      // filenames[i - 2][j] = j == strlen(argv[i]) ? '\0' : argv[i][j];
    }
  }
}

bool is_all_file_closed(bool * closed, int size) {
  for (int i = 0; i < size; i++) {
    if (!closed[i]) {
      return false;
    }
  }

  return true;
}

bool write_files(char( * files)[SIZE_NAME], int count_files) {
  FILE * opened_files[count_files];
  FILE * result_file = fopen("out_file.txt", "w");
  bool closed[count_files];
  char symb = 0;

  for (int i = 0; i < count_files; i++) {
    closed[i] = false;
    opened_files[i] = NULL;
  }

  while (!is_all_file_closed(closed, count_files)) {
    for (int i = 0; i < count_files; i++) {
      if (opened_files[i] == NULL) {
        if ((opened_files[i] = fopen(files[i], "r")) != NULL) {
          ;
        } else {
          return false;
        }
      }
      symb = fgetc(opened_files[i]);
      if (symb != EOF) {
        fputc(symb, result_file);
      } else {
        closed[i] = true;
        fclose(opened_files[i]);
      }
    }
  }

  fclose(result_file);

  return true;
}

int main(int argc, char
    const * argv[]) {
    int check = check_args(argc, argv);
    char filenames[COUNT_FILES][SIZE_NAME];
    int size = 0;
    enum VALIDATION_ENUM validationResult = validationArg(argc, argv);

    if (check == 0) {
      if (strcmp(argv[1], "-fi") == 0) {
        get_names_from_file(argv[2], filenames, & size);
      }
      if (strcmp(argv[1], "-cin") == 0) {
        get_names_from_stdin(filenames, & size);
      }
      if (strcmp(argv[1], "-arg") == 0) {
        get_names_from_args(argc, argv, filenames, & size);
      }

      if (validationResult != ok) {
        printValidationError(validationResult);
        return 1;
      }

      //   if (!write_files(filenames, size)) {
      //     fprintf(stderr, "%s\n", "Some file didn't open");
      //   }
      // } else {
      //   if (check == 1) {
      //     fprintf(stderr, "%s\n", "Invalid count of options");
      //   }
      //   if (check == 2) {
      //     fprintf(stderr, "%s\n", "Invalid file extension");
      //   }
      //   if (check == 3) {
      //     fprintf(stderr, "%s\n", "File didn't open");
      //   }
      //   if (check == 4) {
      //     fprintf(stderr, "%s\n", "Some of the argument files did't open");
      //   }
      //   if (check == 5) {
      //     fprintf(stderr, "%s\n", "Some argument file has the wrong extension");
      //   }
      //   if (check == 6) {
      //     fprintf(stderr, "%s\n", "Invalid options");
      //   }
      // }

      return 0;
    }