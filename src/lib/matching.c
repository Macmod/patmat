#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matching.h"

Text make_text(char text[], unsigned size) {
    Text t;
    t.len = strlen(text);

    if (size == 0)
        size = t.len;

    if (t.len <= size) {
        t.val = (char*)malloc(sizeof(char)*size);
        t.size = size;
        set_text(&t, text);

        return t;
    } else {
        printf("Text length %d exceeds size %d.\n", t.len, size);
        exit(1);
    }
}

void set_text(Text *t, char *val) {
    t->len = strlen(val);
    strcpy(t->val, val);
}

void free_text(Text *t) {
    free(t->val);
}
