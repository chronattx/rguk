#include <stdio.h>
#include <stdlib.h>

int n1() {
    int x, sum = 0;
    if (scanf("%d", &x));
    else return 1;
    for (int i = x; i > 0; i/=10) {
        int c = i % 10;
        printf("%d\t", c);

        int f;
        if (scanf("%d", &f) && (f == 0 || f == 1));
        else return 1;

        sum += c * f;
    }
    printf("%d\n", sum);
    return 0;
}

int n2() {
    int x;
    if (scanf("%d", &x));
    else return 1;
    for (int i = x; i > 0; i/=10) {
        printf("%d", i % 10 % 2);
    }
    printf("\n");    
    return 0;
}

void print_tri(double x1, double y1, double x2, double y2) {
    double a = y1 - y2, b = x2 - x1, c = x1*y2 - y1*x2;
    printf("%.3gx%+.3gy%+.3g=0\n", a, b, c);
}

int n3() {
    double x1, x2, x3, y1, y2, y3;
    if (scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3) == 6);
    else return 1;

    print_tri(x1, y1, x2, y2);
    print_tri(x2, y2, x3, y3);
    print_tri(x3, y3, x1, y1);
    return 0;
}

int n4() {
    printf("a\tb\tc\taVb\t-(aVb)\t-(aVb)&c\t(-(aVb)&c)~a\n");
    for (int a = 0; a < 2; a++) {
        for (int b = 0; b < 2; b++) {
            for (int c = 0; c < 2; c++) {
                printf("%d\t%d\t%d\t", a, b, c);
                int res = a || b;
                printf("%d\t", res);
                res = 1 - res;
                printf("%d\t", res);
                res = res && c;
                printf("%d\t", res);
                res = res == a;
                printf("%d\t\n", res);
            }
        }
    }

    return 0;
}

int n5() {
    int abc, xyz;
    if (scanf("%d%d", &abc, &xyz) == 2);
    else return 1;

    int x1, x2;
    x1 = abc / 100;
    x2 = xyz % 10;
    printf("%d\n", x1 + x2);

    x1 = abc / 10 % 10;
    x2 = xyz / 100;
    printf("%d\n", x1 + x2);
    
    x1 = abc % 10;
    x2 = xyz / 10 % 10;
    printf("%d\n", x1 + x2);
}

int n6() {
    int abcd;
    if (scanf("%d", &abcd));
    else return 1;

    printf("%d", abcd / 100 + abcd % 100);

    return 0;
}

int n7() {
    int a, b;
    if (scanf("%d%d", &a, &b) == 2);
    else return 1;

    printf("%d", (a + b + abs(a - b)) / 2);

    return 0;
}

int main() {
    // n1();
    // n2();
    n3();
    // n4();
    // n5();
    // n6();
    // n7();

    return 0;
}