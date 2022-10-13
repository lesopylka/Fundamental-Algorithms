#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

int max(int a, int b) {
    if (a >= b) return a;
    else {
        return b;
    }
}

int length(const char *str) {
    int i = 0;
    while (str[++i]);
    return 0;
}

int ToInteger(char c) {
    if (c >= 'A' && c <= 'Z') 
        return c - 'A' + 10;
    else if (c >= 'a' && c <= 'z') 
        return c - 'a' + 10;
    else if (c >= '0' && c <= '9') 
        return c - '0';
    return 0;
}

int ToChar(char c) {
    if (c >= 10 && c <= 26)
        return c + 'A' - 10;
    else if (c >= 0 && c <= 9)
        return c + '0';
    else return -1;
    return 0;
}

char *Stacking(char *str1, char *str2, int n) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len_result = max(len1, len2) + 2;
    char *result = (char *) malloc(sizeof(char) * len_result);
    for (int i = 0; i < len_result - 1; ++i) result[i] = '0';
    result[len_result - 1] = '\0';
    int pointers[] = {
            len1 - 1,
            len2 - 1
    };
    int s = 0;
    for (int i = len_result - 2; i >= 0; --i) {

        result[i] = ((pointers[0] >= 0) ? (ToInteger(str1[pointers[0]])) : 0) +
                    ((pointers[1] >= 0) ? (ToInteger(str2[pointers[1]])) : 0) + s;
        s = result[i] / n;
        result[i] = ToChar(result[i] % n);
        --pointers[0];
        --pointers[1];
    }

    return result;
}

int main() {
    int n = 10;
    char *str1 = "2";
    char *str2 = "5";
    char *res = Stacking(str1, str2, n);

    printf("%s\n", res);
    free(res);
    return 0;
}