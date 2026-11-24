#include "array.h"

void swap(int *a, int *b) { 
    int t = *a; 
    *a = *b; 
    *b = t; 
}

int bubble_sort(int * begin, int * end, char flag) {
    for (int * i = begin; i != end - 1; i++) {
        int swapped = 0;
        for (int * j = begin; j != end - 1 - (i - begin); j++) {
            if (j[0] > j[1]) {
                swap(j + 1, j);
                swapped = 1;
            }
        } 
        if (!swapped) break;
        if (flag == 't') true_print(begin, end);
    }
    return 0;
}

int insert_sort(int * begin, int * end, char flag) {
    for (int * i = begin + 1; i != end; i++) {
        for (int * j = i; j != begin; j--) {
            if (j[0] < *(j - 1)) {
                swap(j - 1, j);
            } else break;
        } 
        if (flag == 't') true_print(begin, end);
    }
    return 0;
}

int * partition(int * begin, int * end) {
    int pivot = *(end - 1);
    int * ptr = begin;
    for (int * i = begin; i != end - 1; i++) {
        if (i[0] < pivot) swap(i, ptr++);
    }
    swap(ptr, end - 1);
    return ptr;
}

int quick_sort(int * begin, int * end, char flag) {
    if ((int) (end - begin) > 0) {
        if (flag == 't') true_print(begin, end);
        int * ptr = partition(begin, end);
        quick_sort(begin, ptr, flag);
        quick_sort(ptr + 1, end, flag);
    }
    return 0;
}

int true_scan(int * buf, size_t n) {
    char ch;
    int x = 0, sign = 1;
    int * ptr = buf;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch >= '0' && ch <= '9') {
            x = x * 10 + (ch - '0');
        } else if (ch == ',' || ch == ']') {
            if ((size_t) (ptr - buf) >= n) return -1;
            *ptr = x * sign;
            ptr++;
            x = 0;
            sign = 1;
        } else if (ch == '-') sign *= -1;
    }
    return (int)(ptr - buf);
}

int true_print(int * begin, int * end) {
    if (begin == end) { 
        printf("[]\n"); 
        return 0; 
    }

    printf("[");
    for (int * i = begin; i != end - 1; i++) {
        printf("%d, ", *i);
    }
    printf("%d]\n", *(end - 1));
    return 0;
}

void print_error(int code) {
    switch (code) {
        case 0:            break;   /* успех — молчим */
        case ARR_ERR_SIZE: printf("Error: too many elements (max %d).\n", MAX_SIZE); break;
        case ARR_ERR_IN:   printf("Error: invalid input format.\n"); break;
        default:           printf("Unknown error code: %d\n", code); break;
    }
}