#ifndef BINARY_H
#define BINARY_H
#include <stdio.h>
#include <stdbool.h>



/*
 * binary tree function declarations
 */

int binary_depth(node_t *node);

void print_binary(tree_t *tree);



/* function catalogue
tree_t *create_tree(tree_e type, compare_func cp_f, int heap_size);
void destroy_tree(tree_t *tree);

//does nothing if inserted value already exists
void insert_node(tree_t *tree, int value);

void remove_node(tree_t *tree, int value);

//returns true if input tree is NULL
bool tree_empty(tree_t *tree);

//returns false if input tree is NULL
bool tree_node_present(tree_t *tree, int value);

//inorder = 0, preorder = 1, postorder = 2, invalid = 3
//transversal value is ignored for heap trees
//prints "NULL" if tree is empty and returns
void print_tree(tree_t *tree, transversal_e transversal);
*/


#endif