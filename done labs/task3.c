#include <stdio.h>
#include <string.h>
#define BUFFER_LENGTH 1024

int legal_date(char *s) {
    for (char * ptr = s; ptr - s < 4; ptr++) {
        if (*ptr < '0' || *ptr > '9') return 7;
    }
    if (s[4] != '-') return 7;

    char num = 0;
    if (s[5] < '0' || s[5] > '9') return 7;
    num = (s[5] - '0') * 10;
    if (s[6] < '0' || s[6] > '9') return 7;
    num += s[6] - '0';
    if (num < 1 || num > 12) return 7;
    if (s[7] != '-') return 7;

    num = 0;
    if (s[8] < '0' || s[8] > '9') return 7;
    num = (s[8] - '0') * 10;
    if (s[9] < '0' || s[9] > '9') return 7;
    num += s[9] - '0';
    if (num < 1 || num > 31) return 7;
    if (s[10] != ' ') return 7;

    num = 0;
    if (s[11] < '0' || s[11] > '9') return 7;
    num = (s[11] - '0') * 10;
    if (s[12] < '0' || s[12] > '9') return 7;
    num += s[12] - '0';
    if (num < 0 || num > 23) return 7;
    if (s[13] != ':') return 7;

    num = 0;
    if (s[14] < '0' || s[14] > '9') return 7;
    num = (s[14] - '0') * 10;
    if (s[15] < '0' || s[15] > '9') return 7;
    num += s[15] - '0';
    if (num < 0 || num > 59) return 7;
    if (s[16] != ':') return 7;

    num = 0;
    if (s[17] < '0' || s[17] > '9') return 7;
    num = (s[17] - '0') * 10;
    if (s[18] < '0' || s[18] > '9') return 7;
    num += s[18] - '0';
    if (num < 0 || num > 59) return 7;
    if (s[19] != ';') return 7;

    return 0;
}

int get_level(char * s) {
    char *p = s + 20;

    if (strncmp(p, "INFO;", 5) == 0)
        return 1;
    if (strncmp(p, "WARN;", 5) == 0)
        return 2;
    if (strncmp(p, "ERROR;", 6) == 0)
        return 3;

    return 7;
}

int main() {
    FILE *fp = fopen("testfile1.txt", "r");
    if (fp == NULL) return 2;

    char buffer[BUFFER_LENGTH];
    unsigned long line_no = 0;
    unsigned long too_long = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        line_no += 1;
        size_t len = strlen(buffer);
        if (buffer[len - 1] == '\n') buffer[len - 1] = '\0';
        else if (feof(fp)) {}
        else { 
            too_long += 1;
            int c;
            while ((c = fgetc(fp)) != EOF && c != '\n');
            continue;
        }
        if (legal_date(buffer) != 0) printf("invalid, %d\n", get_level(buffer));
        else printf("valid, %d\n", get_level(buffer));
    }



    fclose(fp);

    return 0;
}