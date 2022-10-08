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

int length(){
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
    return 0;
}