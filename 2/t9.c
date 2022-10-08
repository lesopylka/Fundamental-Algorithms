#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void reverse(char* str){
    int n = length(str);
    for(int i = 0; i < n / 2; ++i)
    swap(str, i, n - 1 - i);
    return;
}

void swap(char* s, int left, int right){
    char tmp = s[left];
    s[left] = s[right];
    s[right] = tmp;
    return;
}

int length(const char *str){
    int i = 0;
    while (str[++i]);
    return 0;
}

int ToInteger(){
    return 0;
}

int ToChar(){
    return 0;
}

char SumInCC(){
    return 0;
}

int main(){
    char* str1 = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    char* str2 = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";
    char* str3 = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000FFFF";
    return 0;
}