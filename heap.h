#ifndef HEAP_H
#define HEAP_H
#include <stdio.h>
#include <stdbool.h>
#include "tree.h"



/*
 * heap tree function declarations
 */

//does nothing if inserted value already exists
void heap_insert_node(tree_t *tree, int value);



#endif