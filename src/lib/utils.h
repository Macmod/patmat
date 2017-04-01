#ifndef UTILS_H
#define UTILS_H
#define CRANGE 128

typedef struct NTable {
    unsigned *list;
    unsigned size;
} NTable;

unsigned char2index(char c);
void free_ntable(NTable*);

#endif
