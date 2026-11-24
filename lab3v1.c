#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITER 100

double f(double x) {
    return 1.0 / (1 + x * x);
}

double trapezoid(double h) {
    int n = (int) round(1.0 /  h);
    double sum = f(0.0) + f(1.0);

    for (int i = 1; i < n; i++) sum += 2.0 * f(i * h); 
    return 2.0 * h * sum;
}

int pi_search() {
    double eps;
    double h, cur_pi;
    int iterations = 0;

    printf("eps (for example 1e-6): ");
    if (scanf("%lf", &eps) != 1 || eps <= 0.0) {
        printf("uncorrect eps\n");
        return 1;
    }

    h = 1.0; 
    while (iterations++ < MAX_ITER) {
        cur_pi = trapezoid(h);

        if (fabs(cur_pi - M_PI) < eps) break;

        h /= 2.0;
    }
    printf("got %.12f\nM_PI  %.12f\niterations %d\n", cur_pi, M_PI, iterations);
    return 0;
}

int local_max() {
    size_t n;
    if (scanf("%zu", &n) != 1) return 2;
    if (n < 2) return 2; 

    int * a = (int *) malloc(n * sizeof(int));
    if (a == NULL) return 1;
    for (size_t i = 0; i < n; i++) {
        if (scanf("%d", a + i) != 1) {
            free(a);
            return 2;
        }
    }

    for (size_t i = 1; i < n - 1; i++) if (a[i] > a[i - 1] && a[i] > a[i + 1]) printf("%d ", a[i]);
    printf("\n");

    free(a);
    return 0;
}

int max_increase() {
    size_t n;
    if (scanf("%zu", &n) != 1) return 2;
    if (n < 2) return 2; 

    int * a = (int *) malloc(n * sizeof(int));
    if (a == NULL) return 1;
    for (size_t i = 0; i < n; i++) {
        if (scanf("%d", a + i) != 1) {
            free(a);
            return 2;
        }
    }

    size_t max_len = 0, cur_len = 1, max_i = 0, cur_i = 0;
    for (size_t i = 1; i < n; i++) {
        if (a[i] > a[i - 1]) {
            if (cur_len == 1) cur_i = i - 1;
            cur_len++;
        }
        else {
            if (cur_len > max_len) {
                max_len = cur_len;
                max_i = cur_i;
            }
            cur_len = 1;
        }
    }
    if (cur_len > max_len) {
        max_len = cur_len;
        max_i = cur_i;
    }
    for (size_t i = max_i; i < max_i + max_len; i++) printf("%d ", a[i]);
    printf("\n");

    free(a);
    return 0;
}

int random_upsidedown() {
    int a[30];
    for (size_t i = 0; i < 30; i++) {
        a[i] = rand() % 100000;
        printf("%d ", a[i]);
    }
    printf("\n");
    for (size_t i = 0; i < 30; i++) {
        int new = 0;
        while (a[i] > 0) {
            new *= 10;
            new += a[i] % 10;
            a[i] /= 10;
        }
        a[i] = new;
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}

int caesar() {
    char ch, delta;
    ch = getchar();
    if ('A' <= ch && ch <= 'Z' || 'a' <= ch && ch <= 'z') delta = (char) (rand() % 10);
    else if ('0' <= ch && ch <= '9') {
        delta = ch - '0';
        ch = getchar();
    }
    else return 1;
    do {
        if ('A' <= ch && ch <= 'Z') ch = 'A' + (ch + delta - 'A') % ('Z' - 'A' + 1);
        else if ('a' <= ch && ch <= 'z') ch = 'a' + (ch + delta - 'a') % ('z' - 'a' + 1);
        printf("%c", ch);
    } while ((ch = getchar()) != '\n' && ch != EOF);
    printf("\n%d\n", delta);

    return 0;
}

int lil_to_big_s() {
    size_t max_len = 100, buf_len = 0;
    char * buf = (char *) malloc(max_len);
    if (buf == NULL) return 1;
    char ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (buf_len == max_len - 1) {
            if (max_len > SIZE_MAX / 2) {
                free(buf);
                return 1;
            }

            char * tmp = (char*) realloc(buf, max_len * 2);
            if (tmp == NULL) {
                free(buf);
                return 1;
            }
            buf = tmp;
            max_len *= 2;
        }
        buf[buf_len] = ch;
        buf_len++;
    }
    buf[buf_len] = '\0';

    while (1) {
        size_t shortest_len = max_len + 1, shortest_i = 0, current_len = 0, current_i = 0;
        for (size_t i = 0; i < buf_len + 1; i++) {
            if (buf[i] == '\0' || buf[i] == '\n' || buf[i] == ' ') {
                if (current_len < shortest_len && current_len != 0) {
                    shortest_len = current_len;
                    shortest_i = current_i;
                }
                current_i = i + 1;
                current_len = 0;
            } else {
                current_len++;
            }
        }
        if (shortest_len == max_len) break;
        for (size_t i = shortest_i; i < shortest_i + shortest_len; i++) {
            printf("%c", buf[i]);
            buf[i] = ' ';
        }
        printf("\n");
    }

    free(buf);
    return 0;
}

void print_error(int code) {
    switch (code) {
        case 0: break; 
        case 1:
            printf("Error 1: memory allocation failed (malloc/realloc).\n");
            break;
        case 2:
            printf("Error 2: invalid input data (scanf failed or bad value).\n");
            break;
        default:
            printf("Unknown error code: %d\n", code);
            break;
    }
}

int main() {
    srand(time(NULL));
    printf("  Student: Molodykh Yulia, itpm126\n");
    printf("  Laboratory work 3\n");

    int choice;
    do {
        printf("\n============== MAIN MENU ==============\n");
        printf("  1. Approximate pi\n");
        printf("  2. Local maxima of array\n");
        printf("  3. Longest increasing subsequence\n");
        printf("  4. Reverse digits\n");
        printf("  5. Caesar cipher\n");
        printf("  6. Shortest words\n");
        printf("  0. Exit\n");
        printf("=======================================\n");
        printf("Choose menu item: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Try again.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
            continue;
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }

        int rc = 0;
        switch (choice) {
            case 1:  rc = pi_search();         break;
            case 2:  rc = local_max();         break;
            case 3:  rc = max_increase();      break;
            case 4:  rc = random_upsidedown(); break;
            case 5:  rc = caesar();            break;
            case 6:  rc = lil_to_big_s();      break;
            case 0:  printf("Exit.\n");        break;
            default: printf("No such item.\n"); break;
        }
        if (choice >= 1 && choice <= 6) print_error(rc);
        
    } while (choice != 0);
    return 0;
}