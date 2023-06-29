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

void heap_remove_root(tree_t *tree);
void heap_remove_last(tree_t *tree);

int heap_depth(tree_t *tree);

bool heap_tree_node_present(tree_t *tree, int value);

void print_heap(tree_t *tree);



#endif