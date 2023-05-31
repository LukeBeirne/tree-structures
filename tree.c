#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"


/*
 * struct definitions and typedefs
 */

struct tree {
	node_t *root;
	//int depth;
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
	//tree->depth = 1;
	return tree;
}

void destroy_tree(tree_t *a) {
	if(a == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	//traverse tree to free each node?
	free(a->root);
	free(a);
}

/*
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
*/

/*
 * was not sure if a recursive impl function
 * call was better than a while true statement
 * for the insert_node function
 */
void insert_node(tree_t *tree, int value) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	node_t *node = tree->root;
	int nodeval = node->value;
	
	//insert_node_impl(tree->root, value);
	while(true) {
		if(nodeval == value) {
		printf("node values are equivalent\n");
		//do something
		return;
		}
	
		if(nodeval < value) {
			//left child
			if(node->child1 == NULL) {
				node_t *b = create_node(value);
				node->child1 = b;
				return;
			}
			node = node->child1;
		}
	
		if(nodeval > value) {
			//right child
			if(node->child2 == NULL) {
				node_t *b = create_node(value);
				node->child2 = b;
				return;
			}
			node = node->child2;
		}
	}
}

void remove_node(tree_t *tree, int value) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	if((tree->root)->value == value) {
		if((tree->root)->child1 =! NULL || (tree->root)->child2 =! NULL) {
			//free other children
		}
		free(tree->root);
		tree->root = NULL;
		return;
	}
	//other stuff
}

bool tree_empty(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return true;
	}
	
	if((tree->root)->child1 == NULL && (tree->root)->child2 == NULL) {
		return true;
	}
	
	return false;
}


/* algorithm used to calculate
 * tree depth:
 * https://www.baeldung.com/cs/binary-tree-height#:~:text=A%20similar%20concept%20in%20a,the%20most%20distant%20leaf%20node.
 */

static void tree_depth_impl(node_t *node) {
	if(node == NULL) {
		return 0;
	}
	
	int left = tree_depth_impl(node->child1);
	int right = tree_depth_impl(node->child2);
	
	if(left < right) {
		return left + 1;
	}
	return right + 1;
}

int tree_depth(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return 0;
	}
	
	node_t *node = tree->root;
	
	if(node == NULL) {
		return 0;
	}
	
	return tree_depth_impl(node);
		
}

bool tree_node_present(tree_t *tree, int value) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return false;
	}
	//some fancy calculation
	return false;
}
