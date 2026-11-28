#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *  data;
    size_t size;
    size_t capacity;
} IntStack;

int stack_init(IntStack * s) {
    s ->     size = 0;
    s -> capacity = 2;
    s ->     data = (int *) malloc(2 * sizeof(int));

    if (s -> data == NULL) return 0;
    return 1;
}

int stack_push(IntStack * s, int value) {
    if (s->capacity == s->size) {
        size_t new_capacity = s->capacity * 2;

        int * tmp = realloc(s->data, new_capacity * sizeof(int));
        if (tmp == NULL) return 0;

        s ->     data = tmp;
        s -> capacity = new_capacity;
    }
    s->data[s->size] = value;
    s->size++;
    return 1;
}

int stack_pop(IntStack * s, int * dest) {
    if (s->size == 0) return 0;
    *dest = s->data[s->size - 1];
    s->size--;
    return 1;
}
void stack_destroy(IntStack * s) {
    free(s->data);
}

char * my_strdup(const char * s) {
    const char * ptr = s;
    while (*ptr != '\0') ptr++;

    size_t size = ptr - s + 1;
    char * new_s = (char *) malloc(size);

    for (size_t c = 0; c < size; c++) {
        new_s[c] = s[c];
    }
    return new_s;
}

int split(const char * str, char *** str_arr, char delim, int * count) {
    const char * ptr = str;
    *count = 0;
    while (*ptr != '\0') {
        if (*ptr == delim) (*count)++;
        ptr++;
    }
    if (ptr == str) {
        return 0;
    }
    (*count)++;
    size_t arr_len = *count * sizeof(char*);
    *str_arr = (char **) malloc(arr_len);
    if (*str_arr == NULL) return 1;

    ptr = str;
    size_t len = 0;
    size_t arr_i = 0;
    while (*ptr != '\0') {
        len++;
        if (*ptr == delim) {
            char * new_str = malloc(len);
            if (new_str == NULL) return 1;

            const char * ptr1 = ptr - len + 1;
            for (size_t i = 0; i < len - 1; i++) { 
                new_str[i] = ptr1[i];
            }
            new_str[len - 1] = '\0';
            *str_arr[arr_i++] = new_str;
            len = 0;
        }
        ptr++;
    }
    char * new_str = malloc(len);
    if (new_str == NULL) return 1;

    const char * ptr1 = ptr - len + 1;
    for (size_t i = 0; i < len - 1; i++) {
        new_str[i] = ptr1[i];
    }
    new_str[len - 1] = '\0';
    *str_arr[arr_i] = new_str;
    return 0;
}

int main() {
    // char s[] = "meowmeow";
    // char * s1;
    // s1 = my_strdup(s);
    // puts(s1);

    // IntStack s;
    // if (!stack_init(&s)) return 1;
    // if (!stack_push(&s, 1)) return 1;
    // if (!stack_push(&s, 2)) return 1;
    // if (!stack_push(&s, 3)) return 1;
    // if (!stack_push(&s, 4)) return 1;
    // if (!stack_push(&s, 5)) return 1;
    // if (!stack_push(&s, 6)) return 1;
    // int a;
    // if (!stack_pop(&s, &a)) return 1;
    // printf("%d\n", a);
    // if (!stack_pop(&s, &a)) return 1;
    // printf("%d\n", a);
    // if (!stack_pop(&s, &a)) return 1;
    // printf("%d\n", a);
    // if (!stack_pop(&s, &a)) return 1;
    // printf("%d\n", a);
    // stack_destroy(&s);
    // if (!stack_push(&s, 4)) return 1;
    // if (!stack_pop(&s, &a)) return 1;
    // printf("%d\n", a);

    char s[] = "a,b,ccc,d";
    char ** arr;
    int a;
    if (split(s, &arr, ',', &a) != 0) return 1;
    for (int i = 0; i < a; i++) {
        puts(arr[i]);
    }

    return 0;
}