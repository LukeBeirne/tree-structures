#ifndef AVL_H
#define AVL_H
#include <stdio.h>
#include <stdbool.h>



/*
 * avl tree function declarations
 */

node_t *avl_insert_node(node_t *check, int value, bool *present);
node_t *avl_remove_node(node_t *check, int value, bool *present);

int avl_depth(node_t *node);

bool avl_tree_node_present(node_t *check, int value);

void print_avl(tree_t *tree);



#endif