#include <stdio.h>

int numBits(int k){
    return 2 << (k - 1);
}

long long factorial(int n){
    if (n > 22)
        return 2;
    else if (n == 0)
        return 1;
    else
        return (long long) n * factorial(n - 1);
}

int getMem(int l, int k){
    long long a = factorial(k);
    long long b = factorial(l);
    long long c = factorial(k - l);
    return (int) (a / (b * c));
}

int checkBits(){
   
}

int bitsIn(){

}

int bitsForward(){

}

void print(int *list, int ln){
    for (int i = 0; i < ln; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int main(){

}