#include <stdio.h>
#include <stdlib.h>

int n1() {
    int n, res;
    if (scanf("%d", &n) != 1) return 1;

    for (int i = n; i > 0; i/=5) {
        res += i % 5;
        res *= 10;
    }
    printf("%d\n", res / 10);

    return 0;
}

int n2() {
    int n;
    if (scanf("%d", &n) != 1) return 1;

    int f1 = 1, f2 = 1, f3 = 2, no = 3;
    while (f3 < n) {
        f1 = f2;
        f2 = f3;
        f3 = f1 + f2;
        no += 1;
    }
    printf("%d %d \n", no, f3);

    return 0;
}

int n3() {
    int n, f = 0, len = 0, i1, x;
    if (scanf("%d", &n) != 1) return 1;
    i1 = n % 10;

    for (int i = n; i > 0; i/=10) {
        x = i % 10;
        if (i1 > x) {
            f = 1;
            break;
        } 
        i1 = x;
    }
    if (f == 0) {
        printf("decreasing");
        return 0;
    }

    f = 0;

    for (int i = n; i > 0; i/=10) {
        x = i % 10;
        if (i1 < x) {
            f = 1;
            break;
        } 
        i1 = x;
    }
    if (f == 0) {
        printf("increasing");
        return 0;
    }

    printf("no");
    return 0;
}

int n4() {
    int x, sum = 0;
    if (scanf("%d", &x) != 1) return 1;

    for (int i = 0; x != 0; i++) {
        if (scanf("%d", &x) != 1) return 1;
        if (x % 2 == 1 && i % 2 == 0) sum += x;
    }

    printf("%d", sum);

    return 0;
}

int n5() {
    for (int a = 1; a < 10; a++) {
        for (int b = 1; b < 10; b++) {
            for (int c = 1; c < 10; c++) {
                if (abs(a - b) < 3 || abs(a - c) < 3 || abs(c - b) < 3) printf("%d%d%d\n", a, b, c);
            }
        }
    }
}

int n6() {
    int a, b;
    if (scanf("%d%d", &a, &b) != 1) return 1;
    int c = a*b;
    while (a != 0 && b != 0) {
        if (a > b) a = a%b;
        else b = b%a;
    }
    printf("%d%d", a + b, c / (a + b));
    return 0;
}

int n7() {
    int x, to_cube = 1, i = 1, sum = 0;
    if (scanf("%d", &x) != 1) return 1;

    for (to_cube = 1; to_cube <= x; to_cube += 1) {
        for (int c = 0; c < to_cube; c += 1) {
            if (to_cube == x) sum += i;
            i += 2;
        }
    }
    printf("%d", sum);

    return 0;
}

int n8() {
    int x, f = 0;
    if (scanf("%d", &x) != 1) return 1;

    for (int i = 0; i <= x; i++) {
        for (int j = i; j <= x; j++) {
            if (i * i + j * j == x) {
                f = 1;
                printf("%d %d\n", i * i, j * j);
            }
        }
    }
}

int main() {
    // n1();
    // n2();
    // n3();
    // n4();
    // n5();
    // n6();
    // n7();
    n8();

    return 0;
}