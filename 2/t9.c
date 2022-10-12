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

void swap(char *s, int left, int right) {
    char tmp = s[left];
    s[left] = s[right];
    s[right] = tmp;
    return;
}

int length(const char *str) {
    int i = 0;
    while (str[++i]);
    return 0;
}

void reverse(char *str) {
    int n = length(str);
    for (int i = 0; i < n / 2; ++i)
        swap(str, i, n - 1 - i);
    return;
}


int ToInteger(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    else if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    else if (c >= '0' && c <= '9') return c - '0';
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
    int n = 15;
    char *str1 = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    char *str2 = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";
    char *str3 = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000FFFF";
    char *res = Stacking(str2, str3, n);

    printf("%s\n", res);
    free(res);
    return 0;
}