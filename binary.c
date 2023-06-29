#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define valid_tree_type(t) \
	(t) >= inorder && (t) < invalid_transversal



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
 * binary tree function definitions
 */

node_t *binary_insert_node(node_t *check, int value, bool *present) {
	if(check == NULL) {
		return create_node(value);
	}
	
	
	int nodeval = check->value;
	
	if(nodeval == value) {
		printf("Value %d already present in tree\n", value);
		*present = true;
	}
	
	if(value < nodeval) {
		//left child
		check->child1 = binary_insert_node(check->child1, value, present);
	}
	
	if(value > nodeval) {
		//right child
		check->child2 = binary_insert_node(check->child2, value, present);
	}
	
	return check;
}


static node_t *find_left_leaf(node_t *node) {
	if(node == NULL) {
		return NULL;
	}
	
	if(node->child1 == NULL) {
		return node;
	} else return find_left_leaf(node->child1);
	
}

node_t *binary_remove_node(node_t *check, int value, bool *present) {
	if(check == NULL) {
		return NULL;
	}
	
	
	int nodeval = check->value;
	
	if(nodeval == value) {
		*present = true;
		//node to be removed has no children
		if(check->child1 == NULL && check->child2 == NULL) {
			destroy_node(check);
			return NULL;
		
		//node to be removed has one child
		} else if((check->child1 != NULL) ^ (check->child2 != NULL)) {
			
			//case for left child
			if(check->child1 != NULL) {
				node_t *temp = check->child1;
				destroy_node(check);
				return temp;
				
			//case for right child
			} else {
				node_t *temp = check->child2;
				destroy_node(check);
				return temp;
			}
			
		//node to be removed has two children
		} else {
			node_t *leaf = find_left_leaf(check->child2);
			check->value = leaf->value;
			check->child2 = binary_remove_node(check->child2, check->value, present);
			return check;
		}
	}
	
	if(value < nodeval) {
		//left child
		check->child1 = binary_remove_node(check->child1, value, present);
	}
	
	if(value > nodeval) {
		//right child
		check->child2 = binary_remove_node(check->child2, value, present);
	}
	
	return check;
}


int binary_depth(node_t *node) {	
	if(node == NULL) {
		return 0;
	}
	
	
	int left = binary_depth(node->child1);
	int right = binary_depth(node->child2);
	
	if(left > right) {
		return left + 1;
	}
	return right + 1;
}


bool binary_tree_node_present(node_t *check, int value) {
	int checkval = check->value;
	
	if(checkval == value) {
		return true;
	}
	
	if(value < checkval) {
		if(check->child1 == NULL) {
			return false;
		}
		return binary_tree_node_present(check->child1, value);
	}
	
	if(check->child2 == NULL) {
		return false;
	}
	return binary_tree_node_present(check->child2, value);
}


static void print_tree_inorder(node_t *node) {
	if(node == NULL) {
		printf("NULL\n");
	}
	
	
	if(node->child1 != NULL) {
		print_tree_inorder(node->child1);
	}
	
	printf("%d\n", node->value);
	
	if(node->child2 != NULL) {
		print_tree_inorder(node->child2);
	}
	
	return;
}

static void print_tree_preorder(node_t *node) {
	if(node == NULL) {
		printf("NULL\n");
	}
	
	
	printf("%d\n", node->value);
	
	if(node->child1 != NULL) {
		print_tree_preorder(node->child1);
	}
	
	if(node->child2 != NULL) {
		print_tree_preorder(node->child2);
	}
	
	return;
}

static void print_tree_postorder(node_t *node) {
	if(node == NULL) {
		printf("NULL\n");
	}
	
	
	if(node->child1 != NULL) {
		print_tree_postorder(node->child1);
	}
	
	if(node->child2 != NULL) {
		print_tree_postorder(node->child2);
	}
	
	printf("%d\n", node->value);
	
	return;
}

void print_binary(tree_t *tree, transversal_e transversal) {
	//check for valid transversal type
	if(!(valid_tree_type(transversal))) {
		fprintf(stderr, "Invalid transversal in print_tree function\n");
		return;
	}
	
	//check for empty tree
	if(tree->root == NULL) {
		printf("NULL\n");
		return;
	}
			
	//transversal switch case for
	//binary tree
	switch(transversal) {
		case inorder:
			print_tree_inorder(tree->root);
			break;
		case preorder:
			print_tree_preorder(tree->root);
			break;
		case postorder:
			print_tree_postorder(tree->root);
			break;
		default:
			fprintf(stderr, "Invalid transversal in print_tree function\n");
			return;
	}
}