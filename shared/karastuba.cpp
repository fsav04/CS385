#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>
using namespace std;
int getSize(long num)
{
    int count = 0;
    while (num > 0)
    {
        count++;
        num /= 10;
    }
    return count;
}

long karatsuba(long X, long Y)
{
    
    if (X < 10 && Y < 10)
        return X * Y;

    int size = fmax(getSize(X), getSize(Y));

    int n = (int)ceil(size / 2.0);
    long p = (long)pow(10, n);
    long a = (long)floor(X / (double)p);
    long b = X % p;
    long c = (long)floor(Y / (double)p);
    long d = Y % p;


    long ac = karatsuba(a, c);
    long bd = karatsuba(b, d);
    long e = karatsuba(a + b, c + d) - ac - bd;


    return (long)(pow(10 * 1L, 2 * n) * ac + pow(10 * 1L, n) * e + bd);
}

int main(int argc, char *argv[]){
    cout << karatsuba(50, 50) << endl;
    return 0;
}