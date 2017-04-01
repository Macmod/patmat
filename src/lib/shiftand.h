#ifndef SHIFT_H
#define SHIFT_H
#include "matching.h"

typedef struct MaskTable {
    unsigned *masks;
    unsigned bitlen;
    unsigned size;
} MaskTable;

MaskTable make_mask_table(Text);
void print_mask_table(MaskTable);
int shift_and_search(Text, Text, MaskTable);
int shift_and_fuzzy(Text, Text, MaskTable, unsigned);

#endif
