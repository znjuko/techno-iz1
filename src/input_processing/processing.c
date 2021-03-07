//
// Created by Черных Никита Алекандрович on 3/5/21.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "processing.h"

char get_char() {
    char c = '\0';
    int result = 0;

    do {
        result = scanf("%c", &c);
    } while (result != 1);

    return c;
};

// Returns NUL on error
char *get_string() {
    struct buffer {
        char *string;
        size_t size;
        size_t cap;
    } buf = {NULL, 0, 0};
    char c = '\0';

    while (c = get_char(), c != EOF && c != '\n') {
        if (buf.size + 1 >= buf.cap) {
            size_t new_cap = !buf.cap ? 1 : buf.cap * 2;

            char *tmp = (char *)malloc((new_cap + 1) * sizeof(char));

            if (!tmp) {
                if (buf.string) {
                    free(buf.string);
                }
                return NULL;
            }

            if (buf.string) {
                tmp = strcpy(tmp, buf.string);
                free(buf.string);
            }

            buf.string = tmp;
            buf.cap = new_cap;
        }

        buf.string[buf.size] = c;
        buf.string[buf.size + 1] = '\0';
        ++buf.size;
    }

    return buf.string;
};

