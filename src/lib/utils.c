#include <stdlib.h>
#include "utils.h"

unsigned char2index(char c) {
    int i = c;
    return i < 0 ? 256 + i : i;
}

void free_ntable(NTable *t) {
    free(t->list);
}
