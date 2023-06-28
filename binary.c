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
 * binary tree function definitions
 */

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