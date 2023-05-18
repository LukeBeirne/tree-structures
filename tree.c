#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"


/*
 * struct definitions and typedefs
 */

struct tree {
	node_t *root;
	int depth;
};

struct node {
	int value;
	node_t *child1;
	node_t *child2;
};



/*
 * tree struct function definitions
 */

tree_t *create_tree(node_t *root) {
	if(root == NULL) {
		return NULL;
	}
	
	tree_t *tree = (tree_t *)malloc(sizeof(tree_t));
	tree->root = root;
	return tree;
}

void destroy_tree(tree_t *a) {
	if(a == NULL) {
		return;
	}
	
	free(a);
}



/*
 * node struct function definitions
 */

node_t *create_node(int value) {
	node_t *node = (node_t *)malloc(sizeof(node_t));
	node->value = value;
	node->child1 = NULL;
	node->child2 = NULL;
	return node;
}

void destroy_node(node_t *a) {
	if(a == NULL) {
		return;
	}
	
	free(a);
}