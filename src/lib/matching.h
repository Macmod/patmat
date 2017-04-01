#ifndef MATCH_H
#define MATCH_H

typedef struct Text {
    char *val;
    unsigned len;
    unsigned size;
} Text;

Text make_text(char[], unsigned);
void set_text(Text*, char*);
void free_text(Text*);

#endif
