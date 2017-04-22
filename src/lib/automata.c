#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "matching.h"
#include "automata.h"

/*
    Time Complexity: ...
    Space Complexity: ...
*/
unsigned compute_pi(Text p, unsigned i, unsigned j) {
    for (unsigned k = i; k > 0; k--) {
        // Find a prefix which is also a suffix
        // of the substring p[0..i-1]
        if (char2index(p.val[k-1]) == j) {
            unsigned c;
            for (c = 0; c < k-1 &&
                    p.val[c] == p.val[i+c+1-k]; c++);
            if (c == k-1)
                return k;
        }
    }

    return 0;
}

/*
    Time Complexity: O(m*a)
        Where m = pattern length
              a = alphabet size
    Space Complexity: O(m*a)
        Where m = pattern length
              a = alphabet size
*/
Automata make_automata(Text p) {
    Automata aut;
    aut.size = p.len + 1;
    aut.table = (unsigned**)malloc(aut.size*sizeof(unsigned*));

    for (unsigned i = 0; i < aut.size; i++) {
        aut.table[i] = (unsigned*)calloc(CRANGE, sizeof(unsigned));

        for (unsigned j = 0; j < CRANGE; j++) {
            if (j == char2index(p.val[i]) && i < p.len) {
                // Trivial states
                aut.table[i][j] = i+1;
            } else {
                // Other states
                aut.table[i][j] = compute_pi(p, i, j);
            }
        }
    }


    return aut;
}

/* 
    Time Complexity: O(m*a)
        Where m = pattern length
              a = alphabet size
    Space Complexity: O(1)
*/
void print_automata(Automata aut, unsigned min, unsigned max) {
    printf("* ");
    for (unsigned h = min; h <= max; h++)
        printf("%c ", h);
    printf("\n");
    for (unsigned i = 0; i < aut.size; i++) {
        printf("%d ", i);
        for (unsigned j = min; j <= max; j++)
            printf("%d ", aut.table[i][j]);
        printf("\n");
    }
}

/*
    Time Complexity: O(m)
        Where m = pattern length
    Space Complexity: O(1)
*/
void free_automata(Automata *aut) {
    for (unsigned i = 0; i < aut->size; i++)
        free(aut->table[i]);

    free(aut->table); 
}

/*
    Time Complexity: O(n)
        Where n = text length
    Space Complexity: O(m*a)
        Where m = pattern length
              a = alphabet size
*/
int automata_search(Text text, Text pattern, Automata aut) {
    unsigned state = 0;
    unsigned index;

    for (unsigned i = 0; i < text.len; i++) {
        index = char2index(text.val[i]);
        state = aut.table[state][index];

        if (state == pattern.len)
            return i - pattern.len + 1;
    }

    return -1;
}
