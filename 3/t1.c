#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

const char ALPHABET[] = "0123456789abcdefghijklmnopqrstuvwxyz";

// меняет символы местами на позициях left и right в строке s
void swap(char * s, int left, int right) {
  char tmp = s[left];
  s[left] = s[right];
  s[right] = tmp;
}

// возвращает длинну строки 
int length(const char * str) {
  int i = -1;
  while (str[++i]);
  return i;
}

void reverse(char * str) {
  int n = length(str);
  for (int i = 0; i < n / 2; ++i)
    swap(str, i, n - 1 - i);
}

// сумма через бинарные операции
int add(int a, int b) {
    int res = 0, carry = 0;
    res = a ^ b;
    carry = (a & b) << 1;
    while(carry) {
        int tmp = res;
        res ^= carry;
        carry = (tmp & carry) << 1;
    }
    return res;
}

// отрицательное число через бинарные операции
int negative(int n) {
    return add(~n, 1);
}

// разность через бо
int sub(int a, int b) {
    return add(a, negative(b));
}

// получение знака
int getSign(int n ) {
    return n << 31;
}

// положительное ли число
int positive(int n) {
    return (getSign(n) & 1) ? negative(n) : n;
}

// уможение через бинаогые лпеоацтт
int multiply(int a, int b) {
    int isNegtive = 0;
    if(getSign(a) ^ getSign(b))
        isNegtive = 1;
    a = positive(a);
    b = positive(b);
    int res = 0;
    while (b | 0) {
        if(b & 1)
            res = add(res, a);
        a = a << 1;
        b = b >> 1;
    }
    return res;
}


// number
// r -> 2^r
// k = 2 -> [01][010][101] -> 00001010
// 8 1 -> 3-> 5-> 7 -> 9!
// 01[010]101 -> >> r * (k - 1) << 
// получение k-тые r бит числа n
char get(int number, int mask, int r, int k) {
    int index = number & mask;
    index = index >> multiply(r, sub(k, 1));
    char result[] = {ALPHABET[index]};
    return ALPHABET[index];
}

// функция конвертации числа number в СИ 2^r
void convert(int number, int r) {
    int mask = 0;
    char res[] = "";
    for (int i = 0, tmp = 1; i < r; i = add(i, 1), tmp = multiply(tmp, 2)) {
        mask = add(mask, tmp);
    }
    
    int k = 1;
    char result[32] = "";

    while(multiply(k, r) <= 31) {
        char digit = get(number, mask, r, k);
        strncat(result, &digit, 1);
        k = add(k, 1);
        mask <<= r;
    }
    reverse(result);
    printf("%s\n", result);
}

// Валидация аргументов командной строки
int input_validate(int argc, char * argv[]) {
    if (argc != 3) {
        return 1;
    }

    if (atoi(argv[2]) > 5 || atoi(argv[2]) < 1) {
        return 1;
    }

    return 0;
}

int main(int argc, char * argv[]) {
    int validate = input_validate(argc, argv);
    if (validate) {
        printf("validatation error\n");
        return 1;
    }

    int number = atoi(argv[1]);
    int r = atoi(argv[2]);

    convert(number, r);
    
    return 0;
}

