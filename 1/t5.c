#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char * argv[]) {
  // генерация названия файла.

  char * Output;
  int j = 0, Pointer = -1;
  int LenАrgv = strlen(argv[0]);
  Output = malloc(sizeof(char) * 69);
  for (j = 0; j < LenАrgv ; j++) {
    if (argv[0][j] == '\\') {
      Pointer = j;
    }
  }

  for (j = 0; j <= Pointer; j++) {
    Output[j] = argv[0][j];
  }

  for (j = Pointer + 1; j < Pointer + 9; j++) {
    int l = j - (Pointer + 1);
    if (l == 0) {
      Output[j] = 'i';
    } else if (l == 1) {
      Output[j] = 'd';
    } else if (l == 2) {
      Output[j] = 'k';
    } else if (l == 3) {
      Output[j] = '.';
    } else if (l == 4) {
      Output[j] = 't';
    } else if (l == 5) {
      Output[j] = 'x';
    } else if (l == 6) {
      Output[j] = 't';
    } else if (l == 7) {
      Output[j] = '\0';
    }
  }

  FILE * OutputFile = fopen(Output, "w");

  if (OutputFile == NULL) {
    printf("file is not open");
    return 0;
  } else return 1;

  char * Toggles[3] = {
    "-fi",
    "-cin",
    "-arg"
  };

  FILE * InputFile;
  FILE * InputFilesInFile;
  char c;
  char mass[300];

  int i, good_flag = 0;
  for (i = 0; i < 5; i++) {
    if (!strcmp(Toggles[i], argv[1])) {
      good_flag = 1;
      switch (Toggles[i][1]) {
      case 'fi':
        InputFile = fopen(argv[2], "r");
        if (InputFile == NULL) {
          printf("error opening input file\n");
          return 0;
        }

        while (1) {
          if (fscanf(InputFile, "%s", & mass) == 1) {
            InputFilesInFile = fopen(mass, "r");
            if (InputFilesInFile != NULL) {
              while ((c = fgetc(InputFilesInFile)) != EOF) {
                fprintf(OutputFile, "%c", c);
              }
              fclose(InputFilesInFile);
            }
          } else {
            break;
          }
        }
        fclose(InputFile);
        break;
      case 'cin':
        while (1) {
          if (scanf("%s", & mass) == 1) {
            InputFilesInFile = fopen(mass, "r");
            if (InputFilesInFile != NULL) {
              while ((c = fgetc(InputFilesInFile)) != EOF) {
                fprintf(OutputFile, "%c", c);
              }
              fclose(InputFilesInFile);
            }
          } else {
            break;
          }
        }
        break;
      case 'arg':
        for (int file = 2; file < argc; ++file) {
          InputFilesInFile = fopen(argv[file], "r");
          if (InputFilesInFile != NULL) {
            while ((c = fgetc(InputFilesInFile)) != EOF) {
              fprintf(OutputFile, "%c", c);
            }
            fclose(InputFilesInFile);
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

  fclose(OutputFile);
  free(Output);

  return 0;
}


// 12 строка: проверки на корректность выделения памяти нет, пофиксить с возможностью обработки ситуации в вызывающем коде
// 12 строка: 7 символов точно всегда хватит? не уверен
// 23-42 строки: выглядит очень убого (ктрлц ктрлв), перепиши чтобы выглядело не так ущербно
// +- 48 строка: приложение завершилось не успешно, вероятно надо вернуть из main что-нибудь не равное 0
// 75, 91 строка: mas это уже char*, зачем брать его адрес в fscanf, не понятно