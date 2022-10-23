#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int to_cc(char c) {
  if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
  else if (c >= 'a' && c <= 'z') return c - 'a' + 10;
  else if (c >= '0' && c <= '9') return c - '0';
  else return -1;
}

char to_char_in_cc(int x) {
  if (x >= 0 && x <= 9) return x + '0';
  else return x + 'A' - 10;
}

void func_prisvaiv(char * a, char * b) {
  int n = strlen(b);
  for (int i = 0; i < n; ++i) {
    a[i] = b[i];
  }
}

int main(void) {
  int n, f;
  printf("Enter a number system in the range from 2 to 36:\n");
  scanf("%d", & n);
  if (n < 2 || n > 36) {
    printf("Wrong number system entered, learn to read!");
    return 0;
  }
  char c[50];
  char stop[4] = "Stop";
  char max_str[50];
  int max_str_len = 0;
  printf("\nEnter numbers no more than 50 characters long (Don`t forget, to stop typing, you must enter Stop with a capital letter!)\n");
  do {
    scanf("%s", & c);
    if (strcmp(c, "Stop") != 0) {
      int x = strlen(c);
      if (c[0] == '-') --x;
      if (x > max_str_len) {
        func_prisvaiv( & max_str, & c);
        max_str_len = x;
      } else if (x == max_str_len) {
        if (strcmp(c, max_str) > 0) {
          func_prisvaiv( & max_str, & c);
        }
      }
    } else {
      break;
    }
  } while (1);

  long long p = 1, result = 0, minus = 0;
  for (int i = max_str_len - 1; i >= 0; --i) {
    if (max_str[i] == '-' && i == 0) {
      minus = 1;
      continue;
    }
    f = to_cc(max_str[i]);
    if (f == -1) {
      printf("Invalid character encountered on line %s ", max_str);
      return 0;
    };
    result += (p * f);
    p *= n;
  }
  max_str[max_str_len] = '\0';
  printf("\nMax str: %s  In decimal number system: %d\n", max_str, (minus) ? -result : result);

  int len_cc = 0, j = 0;
  char mass_cc[50];

  for (int cc = 9; cc <= 36; cc += 9) {
    p = result;
    while (p) {
      mass_cc[len_cc] = to_char_in_cc(p % cc);
      p /= cc;
      len_cc++;
    }
    printf("In counting system %d -> ", cc);
    printf("%s", (minus) ? "-" : "");
    for (int i = len_cc - 1; i >= 0; --i) {
      printf("%c", mass_cc[i]);
    }
    printf("\n");
    len_cc = 0;
  }

  return 0;
}