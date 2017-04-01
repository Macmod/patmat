#ifndef KMP_H
#define KMP_H
#include "utils.h"

NTable make_prefix_table(Text);
int kmp_search(Text, Text, NTable);

#endif
