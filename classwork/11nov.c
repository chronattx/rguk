#include <stdio.h>
typedef int * IntPtr;

void upper(char * ptr, size_t n) {
    while (n > 1) {
        if (*ptr >= 'a' && *ptr <= 'z') *ptr -= 'a' - 'A';
        ptr += 2;
        n -= 2;
    }
}

int main() {
    IntPtr p1, p2;
    
    char s[] = "Hello, worlda";
    char * ptr = s;
    upper(ptr, sizeof(s)/sizeof(s[0]));
    printf("%s\n", s);

    int a = 5;
    int *x = &a;
    int **y = &x;
    printf("a = %d, adr = %p\n", a, (void*) x);
    printf("x = %p, adr = %p\n", (void*) x, (void*) y);
    printf("y = %p, adr = %p\n", (void*) y, (void*) &y);
    
    return 0;
}
