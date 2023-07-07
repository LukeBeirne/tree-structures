#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define valid_tree_type(t) \
	(t) >= inorder && (t) < invalid_transversal



/*
 * struct definitions and typedefs
 */

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

tree_t *create_tree(tree_e type, compare_func c_func, int heap_size) {
	tree_t *tree = (tree_t *)calloc(1, sizeof(tree_t));
	tree->compare_fp = c_func;
	tree->type = type;
	if(tree->type == heap) {
		tree->heap_array = (int *)malloc(heap_size*sizeof(int));
		tree->heap_size = heap_size;
	}
	return tree;
}


void destroy_tree(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	
	switch(tree->type) {
		case binary:
			//destroy_node function traverses through tree to destroy each node
			destroy_node(tree->root);
			free(tree);
			break;
		case heap:
			free(tree->heap_array);
			free(tree);
			break;
		case avl:
			//avl
			break;
		default: //invalid tree type
			fprintf(stderr, "Invalid tree type\n");
			break;
	}
	
}


void insert_node(tree_t *tree, int value) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	bool present = false;
	
	switch(tree->type) {
		case binary:
			//case where tree is empty, value inserted as root
			if(tree->root == NULL) {
				tree->root = create_node(value);
				tree->num_elements += 1;
				return;
			}
			
			tree->root = binary_insert_node(tree->root, value, &present);
	
			if(!present) {
				tree->num_elements += 1;
			}
			return;
			
		case heap:
			heap_insert_node(tree, value);
			return;
		case avl:
			//case where tree is empty, value inserted as root
			if(tree->root == NULL) {
				tree->root = create_node(value);
				tree->num_elements += 1;
				return;
			}
			
			tree->root = avl_insert_node(tree->root, value, &present);
	
			if(!present) {
				tree->num_elements += 1;
			}
			return;
		default: //invalid tree type
			fprintf(stderr, "Invalid tree type\n");
			break;
	}
	
}


void remove_node(tree_t *tree, int value) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	
	switch(tree->type) {
		case binary: ;
			bool present = false;
			tree->root = binary_remove_node(tree->root, value, &present);
			if(present) {
				tree->num_elements -= 1;
			}
			return;
			
		case heap:
			if(value == (tree->heap_array)[0]) {
				heap_remove_root(tree);
				return;
			}
			
			if(value == (tree->heap_array)[tree->num_elements-1]) {
				heap_remove_last(tree);
				return;
			}
			
			fprintf(stderr, "Cannot remove middle value from heap structure\n");
			return;
			
		case avl:
			//avl
			break;
		default: //invalid tree type
			fprintf(stderr, "Invalid tree type\n");
			break;
	}
	
}

bool tree_empty(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return true;
	}
	
	
	if(tree->num_elements == 0) {
		return true;
	}
	
	return false;
}


/* 
 * algorithm used to calculate tree depth:
 * https://www.baeldung.com/cs/binary-tree-height#:~:text=A%20similar%20concept%20in%20a,the%20most%20distant%20leaf%20node.
 */
int tree_depth(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return 0;
	}
	
	
	switch(tree->type) {
		case binary:
			return binary_depth(tree->root);
			break;
		case heap:
			return heap_depth(tree);
		case avl:
			//avl
			break;
		default: //invalid tree type
			fprintf(stderr, "Invalid tree type\n");
			return 0;
	}
	
	return 0;	
}


int tree_get_num_elements(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return 0;
	}
	
	
	return tree->num_elements;
}


bool tree_node_present(tree_t *tree, int value) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return false;
	}
	
	
	switch(tree->type) {
		case binary:			
			return binary_tree_node_present(tree->root, value);
			
		case heap:
			return heap_tree_node_present(tree, value);
			
		case avl:
			//avl
			break;
		default: //invalid tree type
			//invalid
			break;
	}
	
	return false;
}


void print_tree(tree_t *tree, transversal_e transversal) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	switch(tree->type) {
		case binary:
			print_binary(tree);
			return;
		case heap:
			print_heap(tree);
			return;
		case avl:
			//avl
			break;
		default: //invalid tree type
			//invalid
			break;
	}
	
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

void tree_inorder(tree_t *tree, traversal_func t_func) {
	//inorder traversal
	return;
}
void tree_preorder(tree_t *tree, traversal_func t_func) {
	//preorder traversal
	return;
}
void tree_postorder(tree_t *tree, traversal_func t_func) {
	//postorder traversal
	return;
}
*/