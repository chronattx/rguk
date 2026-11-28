#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN    20
#define SURNAME_LEN 20

#define PLANE_SIZE 12

struct seat {
    char n;
    char reserved;
    char name[NAME_LEN];
    char surname[SURNAME_LEN];
} base_seat = {0, 0, "", ""};

void flush_line() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void show_available_count(struct seat * plane) {
    size_t count = 0;
    for (size_t i = 0; i < PLANE_SIZE; i++) count += plane[i].reserved;
    printf("%zu\n", PLANE_SIZE - count);
}

void show_available_list(struct seat * plane) {
    for (size_t i = 0; i < PLANE_SIZE; i++) if (plane[i].reserved == 0) printf("%d ", plane[i].n);
    printf("\n");
}

void show_occupied_list(struct seat * plane) {
    for (size_t i = 0; i < PLANE_SIZE; i++) if (plane[i].reserved == 1) { 
        printf("%d %s %s\n", plane[i].n, plane[i].name, plane[i].surname);
    }
}

int read_line(const char * prompt, char * buf, size_t buflen) {
    printf("%s", prompt);
    if (!fgets(buf, (int)buflen, stdin)) return 0;
    size_t len = strlen(buf);
    if (len && buf[len - 1] == '\n') buf[--len] = '\0';
    else flush_line();
    return 1;
}

int occupy(struct seat * plane, const int n, char * name, char * surname) {
    if (plane[n - 1].reserved == 1) return 0;
    plane[n - 1].reserved = 1;
    strncpy(plane[n - 1].name, name, NAME_LEN);
    strncpy(plane[n - 1].surname, surname, SURNAME_LEN);
    return 1;
}

int legal_occupy(struct seat *plane) {
    int n;
    printf("write a seat number ('0' to exit)\n");
    while (1) {
        if (scanf("%d", &n) != 1) {
            flush_line();
            printf("please, write a number from 0 to %d\n", PLANE_SIZE);
            continue;
        }
        if (n == 0) return 0;    
        if (n < 1 || n > PLANE_SIZE) {
            printf("please, write a number from 0 to %d\n", PLANE_SIZE);
            continue;
        }
        break;
    }

    if (plane[n - 1].reserved == 1) {
        printf("seat %d is already occupied\n", n);
        return 0;
    }

    flush_line();

    char name[NAME_LEN];
    char surname[SURNAME_LEN];

    if (!read_line("name: ",    name,    sizeof(name)))    return 0;
    if (!read_line("surname: ", surname, sizeof(surname))) return 0;

    return occupy(plane, n, name, surname);
}

int unoccupy(struct seat * plane, const int n) {
    if (plane[n - 1].reserved == 0) return 0;
    plane[n - 1].reserved = 0;
    return 1;
}

int legal_unoccupy(struct seat * plane) {
    int n;
    printf("write a seat number to free ('0' to exit)\n");
    while (1) {
        if (scanf("%d", &n) != 1) {
            flush_line();
            printf("please, write a number from 0 to %d\n", PLANE_SIZE);
            continue;
        }
        if (n == 0) return 0;
        if (n < 1 || n > PLANE_SIZE) {
            printf("please, write a number from 0 to %d\n", PLANE_SIZE);
            continue;
        }
        break;
    }
    if (unoccupy(plane, n) == 1) printf("success\n");
    else printf("already free");
    return 1;
}

int main() {
    struct seat plane[PLANE_SIZE];
    for (size_t i = 0; i < PLANE_SIZE; i++) {
        plane[i] = base_seat;
        plane[i].n = i + 1;
    }

    char choice = '\0';
    do {
        printf("--------- MENU ---------\n");
        printf("a) show available count \n");
        printf("b) show available seats \n");
        printf("c) show occupied seats  \n");
        printf("d) occupy a seat        \n");
        printf("e) unoccupy             \n");
        printf("f) EXIT                 \n");
        printf("------------------------\n");
        
        while(1) {
            int c;
            while ((c = getchar()) == '\n' || c == ' ') { } 
            if (c == EOF) return 0;
            if (c >= 'a' && c <= 'f') { 
                choice = (char) c; 
                break;
            }
            printf("please, write a single letter from a to f\n");
        }

        switch (choice) {
            case 'a': show_available_count(plane); break;
            case 'b': show_available_list(plane) ; break;
            case 'c': show_occupied_list(plane)  ; break;
            case 'd': legal_occupy(plane)        ; break;
            case 'e': legal_unoccupy(plane)      ; break;
            default:                               break;
        }
    } while (choice != 'f');

    // strncpy(plane[0].name, "Amy", NAME_LEN);
    // strncpy(plane[1].name, "Leo", NAME_LEN);
    // puts(plane[0].name);
    // puts(plane[1].name);

    return 0;
}