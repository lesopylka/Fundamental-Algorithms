#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ToInteger(char c) {
    if (c >= 'A' && c <= 'Z') 
        return c - 'A' + 10;
    else if (c >= 'a' && c <= 'z') 
        return c - 'a' + 10;
    else if (c >= '0' && c <= '9') 
        return c - '0';
    return 0;
}

char ToChar(char c) {
    if (c >= 10 && c <= 26)
        return c + 'A' - 10;
    else if (c >= 0 && c <= 9)
        return c + '0';
    else return -1;
    return 0;
}

void Assimilation(char * a, char * b) {
  int n = strlen(b);
  for (int i = 0; i < n; ++i) {
    a[i] = b[i];
  }
}

int main(void) {
  int n, f;
  printf("enter a number system in the range from 2 to 36:\n");
  scanf("%d", & n);
  if (n < 2 || n > 36) {
    printf("wrong number system entered, learn to read!");
    return 0;
  }
  char c[50];
  char stop[4] = "Stop";
  char MaxStr[50];
  int max_str_len = 0;
  printf("\nenter numbers no more than 50 characters long (Don`t forget, to stop typing, you must enter Stop with a capital letter!)\n");
  do {
    scanf("%s", & c);
    if (strcmp(c, "stop") != 0) {
      int x = strlen(c);
      if (c[0] == '-') --x;
      if (x > max_str_len) {
        Assimilation( & MaxStr, & c);
        max_str_len = x;
      } else if (x == max_str_len) {
        if (strcmp(c, MaxStr) > 0) {
          Assimilation( & MaxStr, & c);
        }
      }
    } else {
      break;
    }
  } while (1);

  long long p = 1, result = 0, minus = 0;
  for (int i = max_str_len - 1; i >= 0; --i) {
    if (MaxStr[i] == '-' && i == 0) {
      minus = 1;
      continue;
    }
    f = ToInteger(MaxStr[i]);
    if (f == -1) {
      printf("invalid character encountered on line %s ", MaxStr);
      return 0;
    };
    result += (p * f);
    p *= n;
  }
  MaxStr[max_str_len] = '\0';
  printf("\nmax str: %s  In decimal number system: %d\n", MaxStr, (minus) ? -result : result);

  int LenCC = 0, j = 0;
  char MassCC[50];

  for (int cc = 9; cc <= 36; cc += 9) {
    p = result;
    while (p) {
      MassCC[LenCC] = ToChar(p % cc);
      p /= cc;
      LenCC++;
    }
    printf("in counting system %d -> ", cc);
    printf("%s", (minus) ? "-" : "");
    for (int i = LenCC - 1; i >= 0; --i) {
      printf("%c", MassCC[i]);
    }
    printf("\n");
    LenCC = 0;
  }

  return 0;
}