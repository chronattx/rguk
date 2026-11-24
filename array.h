#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>

#define ARR_ERR_SIZE -1
#define ARR_ERR_IN -2
#define MAX_SIZE 100

void print_error(int code);

void swap(int * a, int * b);

int true_scan(int * buf, size_t n);

int true_print(int * begin, int * end);

int bubble_sort(int * begin, int * end, char flag);

int insert_sort(int * begin, int * end, char flag);

int quick_sort(int * begin, int * end, char flag);



#endif