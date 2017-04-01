#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "shiftand.h"
#include "matching.h"

/*
   Time Complexity: O(m)
       Where m = pattern size
   Space Complexity: O(a)
       Where a = alphabet size
*/
MaskTable make_mask_table(Text p) {
    MaskTable M;
    M.masks = (unsigned*)calloc(
        sizeof(unsigned),
        CRANGE
    );

    for (unsigned i = 0; i < p.len; i++) {
        unsigned index = char2index(p.val[i]);
        if (index < 128)
            M.masks[index] |= 1 << i;
    }
    M.bitlen = p.len;

    return M;
}

/*
   Time Complexity: O(m)
       Where m = pattern size
*/
void print_mask_table(MaskTable M) {
    for (unsigned i = 0; i < CRANGE; i++) {
        printf("'%c': ", i);

        for (unsigned j = 0; j < M.bitlen; j++)
            printf("%u", (1 << j) & M.masks[i] ? 1 : 0);

        printf("\n");
    }
}

/*
   Time Complexity: O(n)
       Where n = text size
   Space Complexity: O(a)
       Where a = alphabet size
*/
int shift_and_search(Text t, Text p, MaskTable M) {
    unsigned d = 0;
    unsigned match = 1 << (p.len - 1);
    unsigned index;

    for (unsigned i = 0; i < t.len; i++) {
        index = char2index(t.val[i]);
        d = (d << 1) | 1;
        d &= M.masks[index];

        if (d & match)
            return i - p.len + 1;
    }

    return -1;
}

/*
    Time Complexity: O(kn(m/w))
    Space Complexity: O(k+c)
*/
int shift_and_fuzzy(Text t, Text p, MaskTable M, unsigned k) {
    // Build D list according to level of error (k)
    unsigned d[k+1],
             dp, dn;

    d[0] = 0;
    for (unsigned i = 1; i <= k; i++) {
        d[i] = d[i-1] | (1 << (i-1));
    }

    unsigned match = 1 << (p.len - 1);
    unsigned index;

    for (unsigned i = 0; i < t.len; i++) {
        index = char2index(t.val[i]);

        dp = d[0];
        dn = ((dp << 1) | 1) & M.masks[index];
        d[0] = dn;

        for (unsigned j = 1; j <= k; j++) {
            dn = (d[j] << 1) & M.masks[index];
            dn |= dp;
            dn |= ((dp | dn) << 1);

            dp = d[j];
            d[j] = dn | 1;
        }

        if (dn & match)
            return i - p.len + 1;
    }

    return -1;
}
