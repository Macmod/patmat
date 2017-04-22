#ifndef AUTO_H
#define AUTO_H

typedef struct Automata {
    unsigned **table;
    unsigned size;
} Automata;

Automata make_automata(Text);
void print_automata(Automata, unsigned, unsigned);
void free_automata(Automata*);
int automata_search(Text, Text, Automata);

#endif
