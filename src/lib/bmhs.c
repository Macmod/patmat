#include <stdlib.h>
#include "utils.h"
#include "matching.h"
#include "bmhs.h"

/*
    Time Complexity: O(m + c)
        Where m = pattern length
              c = alphabet size
    Space Complexity: O(c)
        Where c = alphabet size
*/
NTable make_delta_table(Text pattern) {
    NTable d;

    d.list = (unsigned*)malloc(sizeof(unsigned)*CRANGE);
    d.size = CRANGE;

    for (unsigned i = 0; i < CRANGE; i++) {
        d.list[i] = pattern.len + 1;
    }

    for (unsigned i = 0; i < pattern.len; i++) {
        unsigned index = char2index(pattern.val[i]);
        d.list[index] = pattern.len - i;
    }

    return d;
}

/*
    Time Complexity:
        Best: O(m/n)
        Avg: O(m/n)
        Worst: O(mn)
            Where n = text length
                  m = pattern length
    Space Complexity: O(c)
        Where c = alphabet size
*/
int bmhs_search(Text text, Text pattern, NTable tbl) {
    unsigned m = pattern.len - 1;
    unsigned n = text.len;
    unsigned index;

    for (unsigned i = m; i < n; i += tbl.list[index]) {
        index = char2index(text.val[i+1]);

        unsigned k = i;
        unsigned j = m;
        while (text.val[k] == pattern.val[j]) {
            if (j == 0) {
                return k;
            } else {
                j--;
                k--;
            }
        }
    }

    return -1;
}
