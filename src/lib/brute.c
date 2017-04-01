#include <stdlib.h>
#include <stdbool.h>
#include "brute.h"

/*
    Time Complexity: O(mn)
        Where m = pattern length
              n = text length
    Space Complexity: O(1)
*/
int brute_search(Text text, Text pattern) {
    unsigned max = text.len - pattern.len + 1;
    for (unsigned i = 0; i < max; i++) {
        bool found = true;
        for (unsigned j = 0; j < pattern.len; j++) {
            if (text.val[i+j] != pattern.val[j]) {
                found = false;
            }
        }

        if (found) {
            return i;
        }
    }

    return -1;
}
