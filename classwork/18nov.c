#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t n, m;
    printf("enter matix size: ");
    scanf("%zu%zu", &n, &m);
    printf("\n");
    int * matrix = malloc(n * m * sizeof(int));
    if (matrix == NULL) {
        printf("malloc error");
        return 1;
    } else {
        int * ptr = matrix;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < m; j++) {
                *ptr = i + j;
                printf("%d ", *ptr);
                ptr++;
            }
            printf("\n");
        }
    }
    int * ptr = matrix;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", *ptr);
            ptr++;
        }
        printf("\n");
    }
    free(matrix);

    return 0;
}