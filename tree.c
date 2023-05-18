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
 * node struct function definitions
 */

static node_t *create_node(int value) {
	node_t *node = (node_t *)malloc(sizeof(node_t));
	node->value = value;
	node->child1 = NULL;
	node->child2 = NULL;
	return node;
}

static void destroy_node(node_t *a) {
	if(a == NULL) {
		return;
	}
	
	free(a);
}



/*
 * tree struct function definitions
 */

tree_t *create_tree(int rootValue) {
	tree_t *tree = (tree_t *)malloc(sizeof(tree_t));
	node_t *root = create_node(rootValue);
	tree->root = root;
	tree->depth = 1;
	return tree;
}

void destroy_tree(tree_t *a) {
	if(a == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	free(a->root);
	free(a);
}

static void insert_node_impl(node_t *a, int value) {
	int nodeval = a->value;
	
	if(nodeval == value) {
		printf("node values are equivalent\n");
		return;
	}
	
	if(nodeval < value) {
		//left child
		if(a->child1 == NULL) {
			node_t *b = create_node(value);
			a->child1 = b;
			return;
		}
		insert_node_impl(a->child1, value);
	}
	
	if(nodeval > value) {
		//right child
		if(a->child2 == NULL) {
			node_t *b = create_node(value);
			a->child2 = b;
			return;
		}
		insert_node_impl(a->child2, value);
	}
}

void insert_node(tree_t *a, int value) {
	if(a == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	insert_node_impl(a->root, value);
}

void remove_node(tree_t *a, int value) {
	if(a == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	if((a->root)->value == value) {
		free(a->root);
		return;
	}
	//other stuff
}

bool tree_empty(tree_t *a) {
	if(a == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return true;
	}
	
	if((a->root)->child1 == NULL && (a->root)->child2 == NULL) {
		return true;
	}
	
	return false;
}

int tree_depth(tree_t *a) {
	return a->depth;
}

bool tree_node_present(tree_t *a, int value) {
	if(a == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return false;
	}
	
	return false;
}
