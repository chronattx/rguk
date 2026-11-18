#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LEN 100

int main() {
    FILE * fp = fopen("21oct.txt", "r");
    if (fp == NULL) return 1;

    char word[MAX_WORD_LEN];
    char res_word[MAX_WORD_LEN];
    size_t word_len, res_word_len = 0;
    while (fscanf(fp, "%s", word) == 1) {
        word_len = strlen(word);
        if (word_len >= res_word_len) {
            strcpy(res_word, word);
            res_word_len = word_len;
        }
    }
    if (ferror(fp)) return 1;
    fclose(fp);

    printf("%d %s\n", res_word_len, res_word);

    return 0;
}