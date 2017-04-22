#include <stdlib.h>
#include "utils.h"
#include "text.h"
#include "kmp.h"

/*
    Space Complexity: O(m)
        Where m = pattern length
    Space Complexity: O(m)
        Where m = pattern length
*/
NTable make_prefix_table(Text p) {
    NTable t;

    t.list = (unsigned*)malloc(sizeof(unsigned)*p.len);
    t.list[0] = 0;
    t.list[1] = 0;
    t.size = p.len;

    for (unsigned i = 0, j = 2; j < p.len; j++) {
        // If the character right after the prefix
        // matches the last, then the next value of
        // the table is i+1.
        // If not, keep testing the longest prefixes
        // of the previous substrings.
        // If it doesn't match, i will stop at zero.
        while (p.val[i] != p.val[j] && i > 0)
            i = t.list[i-1];

        if (p.val[i] == p.val[j])
            i++;

        t.list[j] = i;
    }

    return t;
}

/*
    Time Complexity: O(n+m)
        Where n = text length
              m = pattern length
    Space Complexity: O(m)
        Where m = pattern length
*/
int kmp_search(Text t, Text p, NTable tbl) {
    unsigned i = 0;
    unsigned j = 0;
    while (i < t.len) {
        if (t.val[i] == p.val[j]) {
            i++;
            j++;

            if (j == p.len)
                return i - j;
        } else if (j != 0) {
            j = tbl.list[j-1];
        } else {
            i++;
        }
    }

    return -1;
}
