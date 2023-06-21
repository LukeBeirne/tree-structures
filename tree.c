#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define valid_tree_type(t) \
	(t) >= inorder && (t) < invalid_transversal

/*
modify create_tree
change int parameters to name
try heap
*/


/*
 * struct definitions and typedefs
 */

struct tree {
	node_t *root;
	tree_e type;
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

tree_t *create_tree(int rootValue, tree_e type, compare_func c_func) {
	tree_t *tree = (tree_t *)malloc(sizeof(tree_t));
	tree->root = create_node(rootValue);
	//make root NULL to begin with
	//tree->depth = 1;
	tree->type = type;
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


static node_t *insert_node_impl(node_t *check, int value, bool *present) {
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
		check->child1 = insert_node_impl(check->child1, value, present);
	}
	
	if(value > nodeval) {
		//right child
		check->child2 = insert_node_impl(check->child2, value, present);
	}
	
	return check;
}

void insert_node(tree_t *tree, int value) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	bool present = false;
	tree->root = insert_node_impl(tree->root, value, &present);
	
	if(!present) {
		tree->num_elements += 1;
	}
	return;
}


static node_t *find_left_leaf(node_t *node) {
	if(node == NULL) {
		return NULL;
	}
	
	if(node->child1 == NULL) {
		return node;
	} else return find_left_leaf(node->child1);
	
}

static node_t *remove_node_impl(node_t *check, int value, bool *present) {
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
			check->child2 = remove_node_impl(check->child2, check->value, present);
			return check;
		}
	}
	
	if(value < nodeval) {
		//left child
		check->child1 = remove_node_impl(check->child1, value, present);
	}
	
	if(value > nodeval) {
		//right child
		check->child2 = remove_node_impl(check->child2, value, present);
	}
	
	return check;
}

void remove_node(tree_t *tree, int value) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	
	bool present = false;
	tree->root = remove_node_impl(tree->root, value, &present);
	if(present) {
		tree->num_elements -= 1;
	}
	return;
}

bool tree_empty(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return true;
	}
	
	
	if((tree->root)->value == 0 && (tree->root)->child1 == NULL && (tree->root)->child2 == NULL) {
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


void print_tree_inorder(node_t *node) {
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

void print_tree_preorder(node_t *node) {
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

void print_tree_postorder(node_t *node) {
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

void print_tree(tree_t *tree, transversal_e transversal) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	if(!(valid_tree_type(transversal))) {
		fprintf(stderr, "Invalid transversal in print_tree function\n");
		return;
	}
	
	switch(transversal) {
		case 0: //inorder
			print_tree_inorder(tree->root);
			break;
		case 1: //preorder
			print_tree_preorder(tree->root);
			break;
		case 2: //postorder
			print_tree_postorder(tree->root);
			break;
		default: //invalid
			fprintf(stderr, "Invalid transversal in print_tree function\n");
			return;
	}
	
	return;
	
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