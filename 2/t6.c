#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>


int KMP(char * pat, char * txt) {
  int M = strlen(pat);
  int N = strlen(txt);
  int lps[M];
  int len = 0;
  lps[0] = 0;
  int i = 1;
  while (i < M) {
    if (pat[i] == pat[len]) {
      len++;
      lps[i] = len;
      i++;
    } else {
      if (len != 0) {
        len = lps[len - 1];
      } else {
        lps[i] = 0;
        i++;
      }
    }
  }
  i = 0;
  int j = 0;
  while ((N - i) >= (M - j)) {
    if (pat[j] == txt[i]) {
      j++;
      i++;
    }
    if (j == M) {
      return i - j;
    } else if (i < N && pat[j] != txt[i]) {
      if (j != 0)
        j = lps[j - 1];
      else
        i = i + 1;
    }
  }
  return -1;
}

int isInclude(char * string, char * path) {
  FILE * file = fopen(path, "r");
  if (file == NULL) {
    return -1;
  }
  int stringLen = strlen(string);
  int buffLen = stringLen > 50 ? stringLen * 3 : 100;
  char * buff = (char * ) malloc(sizeof(char) * buffLen);
  if (buff == NULL) {
    return -1;
  }
  int result;
  char c;
  int ind = 0;
  while ((c = fgetc(file)) != EOF) {
    buff[ind] = c;
    ind++;
    if (ind + 1 == buffLen) {
      buff[ind] = '\0';
      result = KMP(string, buff);
      if (result >= 0) {
        free(buff);
        return 1;
      }
      ind = 0;
      for (int x = buffLen - stringLen; x < buffLen - 1; x++) {
        buff[ind] = buff[x];
        ind++;
      }
    }
  }
  buff[ind] = '\0';
  result = KMP(string, buff);
  if (result >= 0) {
    free(buff);
    return 1;
  }
  free(buff);
  return 0;
}

char ** find(char * string, int pathCount, ...) {
  va_list args;
  va_start(args, pathCount);
  int resCapacity = 1;
  int count = 0;
  char ** res = (char ** ) malloc(sizeof(char * ) * (resCapacity + 1));
  if (res == NULL)
    return NULL;
  char * path;
  for (int x = 0; x < pathCount; x++) {
    path = va_arg(args, char * );
    int include = isInclude(string, path);
    if (include == -1) {
      free(res);
      return NULL;
    } else if (include == 1) {
      if (count == resCapacity) {
        resCapacity *= 2;
        char ** newRes = (char ** ) realloc(res, sizeof(char * ) * (resCapacity + 1));
        if (newRes == NULL) {
          free(res);
          return NULL;
        }
        res = newRes;
      }
      res[count] = path;
      count++;
    }
  }
  res[count] = NULL;
  return res;
}

int main() {
  char path1[] = "in1.txt";
  char path2[] = "in1.txt";
  char string[] = "Ilya";
  char ** result = find(string, 2, path1, path2);
  if (result == NULL) {
    printf("Insufficient memory\n");
    return 1;
  }
  printf("'%s' contain files:\n", string);
  int x = 0;
  while (result[x] != NULL) {
    printf("%s\n", result[x]);
    x++;
  }
  free(result);
  return 0;
}