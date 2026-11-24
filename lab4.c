#include <stdio.h>
#include <stdlib.h>
#include "array.h"


unsigned int a(unsigned int m, unsigned int n) {
    if (m == 0) return n + 1;
    if (n == 0) return a(m - 1, 1);
    return a(m - 1, a(m, n - 1));
}

int aa() {
    int m, n;
    if (scanf("%d%d", &m, &n) != 2 || m < 0 || n < 0) {
        printf("Error: m and n must be non-negative\n");
        return 1;
    }
    if (m > 2) {
        printf("please don't input m larger than 2...\n");
        return 1;
    }
    printf("%u", a(m, n));
    return 0;
}

int main() {
    int a[MAX_SIZE];
    int n = 0;
    int have_array = 0;
    printf("  Student: Molodykh Yulia, itpm126\n");
    printf("  Laboratory work 3\n");
    int choice;
    do {
        
        printf("\n============== MAIN MENU ==============\n");
        printf("  1.  Input array\n");
        printf("  2.  Print array\n");
        printf("  3.  Bubble sort      (trace ON)\n");
        printf("  4.  Bubble sort      (trace OFF)\n");
        printf("  5.  Insertion sort   (trace ON)\n");
        printf("  6.  Insertion sort   (trace OFF)\n");
        printf("  7.  Quick sort       (trace ON)\n");
        printf("  8.  Quick sort       (trace OFF)\n");
        printf("  0.  Exit\n");
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

        switch (choice) {
            case 1: {
                printf("Enter array, e.g. [1,2,3]: ");
                int rc = true_scan(a, MAX_SIZE);
                if (rc < 0) {
                    print_error(rc);
                    have_array = 0;
                    n = 0;
                } else {
                    n = rc;
                    have_array = 1;
                    printf("Read %d element(s).\n", n);
                }
                break;
            }
            case 2:
                if (!have_array) { printf("Array is empty. Input first (item 1).\n"); break; }
                true_print(a, a + n);
                break;
            case 3:
                if (!have_array) { printf("Array is empty. Input first (item 1).\n"); break; }
                bubble_sort(a, a + n, 't');
                printf("Result: ");
                true_print(a, a + n);
                break;
            case 4:
                if (!have_array) { printf("Array is empty. Input first (item 1).\n"); break; }
                bubble_sort(a, a + n, 'f');
                printf("Result: ");
                true_print(a, a + n);
                break;
            case 5:
                if (!have_array) { printf("Array is empty. Input first (item 1).\n"); break; }
                insert_sort(a, a + n, 't');
                printf("Result: ");
                true_print(a, a + n);
                break;
            case 6:
                if (!have_array) { printf("Array is empty. Input first (item 1).\n"); break; }
                insert_sort(a, a + n, 'f');
                printf("Result: ");
                true_print(a, a + n);
                break;
            case 7:
                if (!have_array) { printf("Array is empty. Input first (item 1).\n"); break; }
                quick_sort(a, a + n, 't');
                printf("Result: ");
                true_print(a, a + n);
                break;
            case 8:
                if (!have_array) { printf("Array is empty. Input first (item 1).\n"); break; }
                quick_sort(a, a + n, 'f');
                printf("Result: ");
                true_print(a, a + n);
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("No such menu item.\n");
                break;
        }
    } while (choice != 0);
    return 0;
}