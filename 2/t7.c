#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

bool СonvexTriangle(int count, ...){
{
    if (count < 6 || count % 2 != 0)
        return "Something went wrong";
    va_list iter;
    va_start(iter, count);

    bool sign = false;
    
    int n = count / 2;
    int X[n], Y[n];
    int x = 0, y = 0;

    for (int i = 0; i < count; i ++) {
        if (i % 2 == 0)
            X[x++] = va_arg(iter, int);
        else
            Y[y++] = va_arg(iter, int);
    }

    va_end(iter);

    for (int i = 0; i < n; i++) {
        int x1 = X[(i + 1) % n] - X[i % n];
        int y1 = Y[(i + 1) % n] - Y[i % n];

        int x2 = X[(i + 2) % n] - X[i % n];
        int y2 = Y[(i + 2) % n] - Y[i % n];

        int det = x1 * y2 - x2 * y1;

        if (i == 0)
            sign = (det > 0);
        else if (sign != (det > 0))
            return false;
    }
    return true;
}

double DegreePolynomialValue(double x, int index, ...){
    va_list iter;
    va_start(iter, index);

    double res = 0;

    for (int i = 0; i <= index; i++)
        res = res * x + va_arg(iter, double);

    va_end(iter);

    return res;
}

int main(int argc, char *argv[]){
    return 0;
}