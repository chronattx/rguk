#include <stdio.h>

int gcd(int a, int b) {
    if (b > a) {
        int c = a;
        a = b;
        b = c;
    }
    if (b == 0) return a;
    if (b == 1) return 1;
    while (b != 0) {
        int c = b;
        b = a % b;
        a = c;
    }
    return a;
}

int gcd_rec(int a, int b) {
    if (b == 0) return a;
    return gcd_rec(b, a % b);
}

int spf() {
    int x, y;
    int ok;

    ok = scanf("%d%d", &x, &y);    // scanf returns an amount of successfully read values
    if (ok == 2) {                 // so we can check if everything's recorded correctly
        printf("%d\n", x + y);
    }
    return 0;
}

int bitwise_shift() {
    int fc = -13;
    if (fc > 127 || fc < -127) {
        return 0;
    }
    unsigned char c = (unsigned char) fc;
    for (int i = 7; i >= 0; --i) {    // with the help of bitwise shift we discover how the value is recorded in memory
        int bit = (c >> i) & 1;       // we do & op to get only 1 bit
        printf("%d", bit);
    }
}

int f(int n) {
    if (n == 0) return 0;
    if (n == 1 || n == 2) return 1;
    return f(n - 1) + f(n - 2);
}

int fac(int n) {
    if (n == 1) return 1;
    return n * fac(n - 1);
}

int main() {
    int x;
    scanf("%d", &x);
    printf("%d", fac(x));
    
    return 0;
}