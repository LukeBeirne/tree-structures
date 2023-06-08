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
	int num_elements;
	compare_func compare_fp;
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

static void destroy_node(node_t *node) {
	if(node == NULL) {
		return;
	}
	
	if(node->child1 != NULL) {
		destroy_node(node->child1);
	}
	if(node->child2 != NULL) {
		destroy_node(node->child2);
	}
	
	free(node);
}



/*
 * tree struct function definitions
 */

tree_t *create_tree(int rootValue, compare_func c_func) {
	tree_t *tree = (tree_t *)malloc(sizeof(tree_t));
	tree->root = create_node(rootValue);
	//tree->depth = 1;
	tree->num_elements = 1;
	tree->compare_fp = c_func;
	return tree;
}

void destroy_tree(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	//destroy_node function traverses through tree to destroy each node
	destroy_node(tree->root);
	free(tree);
}

/*
 * tree traversal functions
 *
 * Notes about this section of functions:
 * I had noticed that some of the functions were
 * effectively traversing the given tree in the exact
 * same way, the only difference between the functions
 * is what they do when they reach the correct node
 *
 * The current tree functions that do this are:
 * insert_node, remove_node, tree_node_present and once
 * the print_tree function is implemented it will incorporate
 * all three traversal methods, so it is also included
 *
 * Because of this observation, my idea was to have
 * a collection of functions that would traverse through
 * a given tree whether it be inorder, preorder, or postorder
 * and upon arriving at the correct node, perform the action
 * of the input function, thereby eliminating the code duplication
 * present in the other tree functions
 */
void tree_inorder(traversal_func t_func) {
	//inorder traversal
	return;
}
void tree_preorder(traversal_func t_func) {
	//preorder traversal
	return;
}
void tree_postorder(traversal_func t_func) {
	//postorder traversal
	return;
}


static node_t *insert_node_impl(node_t *check, int value) {
	if(check == NULL) {
		return create_node(value);
	}
	
	
	int nodeval = check->value;
	
	if(nodeval == value) {
		printf("node values are equivalent\n");
	}
	
	if(value < nodeval) {
		//left child
		check->child1 = insert_node_impl(check->child1, value);
	}
	
	if(value > nodeval) {
		//right child
		check->child2 = insert_node_impl(check->child2, value);
	}
	
	return check;
}


void insert_node(tree_t *tree, int value) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	
	tree->root = insert_node_impl(tree->root, value);
	tree->num_elements += 1;
}


static void remove_node_impl(node_t *check, int value) {
	if(check == NULL) {
		return;
	}
	
	
	int nodeval = check->value;
	
	if(nodeval == value) {
		destroy_node(check);
	}
	
	if(value < nodeval) {
		//left child
		remove_node_impl(check->child1, value);
	}
	
	if(value > nodeval) {
		//right child
		remove_node_impl(check->child2, value);
	}
	
	return;
}


void remove_node(tree_t *tree, int value) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	remove_node_impl(tree->root, value);
	return;
}

bool tree_empty(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return true;
	}
	
	
	if(tree->root == NULL) {
		return true;
	}
	
	return false;
}


/* algorithm used to calculate
 * tree depth:
 * https://www.baeldung.com/cs/binary-tree-height#:~:text=A%20similar%20concept%20in%20a,the%20most%20distant%20leaf%20node.
 */

static int tree_depth_impl(node_t *node) {
	if(node == NULL) {
		return 0;
	}
	
	
	int left = tree_depth_impl(node->child1);
	int right = tree_depth_impl(node->child2);
	
	if(left > right) {
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


int tree_get_num_elements(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return 0;
	}
	
	
	return tree->num_elements;
}


bool tree_node_present_impl(node_t *check, int value) {
	int checkval = check->value;
	
	if(checkval == value) {
		return true;
	}
	
	if(value < checkval) {
		if(check->child1 == NULL) {
			return false;
		}
		return tree_node_present_impl(check->child1, value);
	}
	
	if(check->child2 == NULL) {
		return false;
	}
	return tree_node_present_impl(check->child2, value);
}

bool tree_node_present(tree_t *tree, int value) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return false;
	}
	
	
	return tree_node_present_impl(tree->root, value);
}

void print_tree(tree_t *tree, transversal_e transversal) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	switch(transversal) {
		case 0: //inorder
			//function pointers?
			printf("inorder\n");
			break;
		case 1: //preorder
			
			break;
		case 2: //postorder
			
			break;
		default: //invalid
			fprintf(stderr, "Invalid transversal in print_tree function\n");
			return;
	}
	
}