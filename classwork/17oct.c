#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct 
{
    size_t capacity;
    int top;
    int *array;
} Stack;

Stack * init(int volume) {
    if (volume < 1) return NULL;

    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (!stack) return NULL;

    stack->top = -1;
    stack->capacity = volume;
    stack->array = (int *) malloc(stack->capacity * sizeof(int));
    if (!stack->array) {
        free(stack);
        return NULL;
    }

    return stack;
}

int is_full(const Stack *stack) {
    return stack != NULL && stack->capacity - 1 == stack->top;
}

int is_empty(const Stack *stack) {
    return stack != NULL && stack->capacity == 0;
}

int push(Stack * stack, int item) {
    if (stack == NULL) return 0;
    if (is_full(stack)) {
        if (stack->capacity > INT_MAX / 2) return 0;

        int new_capacity = stack->capacity * 2;
        int * tmp = (int *) realloc(stack->array, new_capacity * sizeof(int));
        if (!tmp) return 0;     // tmp and new_capacity for case if they become NULL
                                   // -- not to make original stack array become NULL
        stack->array = tmp;
        stack->capacity = new_capacity;
    }
    stack->top++;
    stack->array[stack->top] = item;
    return 1;
}

int pop(Stack * stack, int *out) {
    if (!stack || !out || is_empty(stack)) return 0;

    *out = stack->array[stack->top];
    stack->top--;
    return 1;
}

int peek(Stack * stack, int * out) {
    if (!stack || !out || is_empty(stack)) return 0;

    *out = stack->array[stack->top];
    return 1;
}

int clear(Stack * stack) {
    if (!stack) return 0;
    free(stack->array);
    free(stack);
    return 1;
}

int main() {
    Stack *st = init(10);
    int x, y;
    push(st, 10);
    push(st, 20);
    push(st, 30);
    push(st, 40);

    peek(st, &x);
    pop(st, &x);
    peek(st, &y);
    printf("%d %d\n", x, y);
    return 0;
}