#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>


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
}

char *Stacking(char *str1, char *str2, int n) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len_result = ((len1 > len2) ? len1: len2) + 2;
    char *result = (char *) malloc(sizeof(char) * len_result);
    if (*result = NULL) 
    {
        return 1;
    }
    for (int i = 0; i < len_result - 1; ++i) result[i] = '0';
    result[len_result - 1] = '\0';
    int p[] = {
            len1 - 1,
            len2 - 1
    };
    int s = 0;
    for (int i = len_result - 2; i >= 0; --i) {

        result[i] = ((p[0] >= 0) ? (ToInteger(str1[p[0]])) : 0) +
                    ((p[1] >= 0) ? (ToInteger(str2[p[1]])) : 0) + s;
        s = result[i] / n;
        result[i] = ToChar(result[i] % n);
        --p[0];
        --p[1];
    }

    return result;
}

char* summ(int system_num, unsigned num, char* first, ...) 
{
    num = num-2;
    char **p = &first;
    char* sum = Stacking(*p,*(++p), system_num);
    p++;
    while (num--)
    {
        char* tmp = Stacking(sum,*p, system_num);
        memcpy(sum, tmp, strlen(tmp));
        free(tmp);
        p++;
    }
    return sum;
}


int main() {
    int n = 2;
    char str1[] = "00001";
    char str2[] = "0000000010";
    char str3[] = "0000010000";
    char str4[] = "0010000000";
    char *res = summ(2,4,&str1,&str2,&str3,&str4);//Stacking(&str1,&str2,2);

    printf("%s\n", res);
    free(res);
    return 0;
}
