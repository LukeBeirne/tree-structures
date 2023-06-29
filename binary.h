#ifndef BINARY_H
#define BINARY_H
#include <stdio.h>
#include <stdbool.h>



/*
 * binary tree function declarations
 */

node_t *binary_insert_node(node_t *check, int value, bool *present);
node_t *binary_remove_node(node_t *check, int value, bool *present);

int binary_depth(node_t *node);

bool binary_tree_node_present(node_t *check, int value);

void print_binary(tree_t *tree);



#endif