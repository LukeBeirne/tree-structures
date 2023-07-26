#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define valid_tree_type(t) \
	(t) >= inorder && (t) < invalid_transversal



struct node {
	void *value;
	node_t *child1;
	node_t *child2;
};


/*
 * node struct function definitions
 */

static node_t *create_node(tree_t *tree, void *value) {
	node_t *node = (node_t *)malloc(sizeof(node_t));
	memcpy(node->value, value, tree->type_size);
	//node->value = value;
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

tree_t *binary_create(tree_t *tree, int heap_size) {
	return tree;
}

void binary_destroy(tree_t *tree) {
	//destroy_node function traverses through tree to destroy each node
	destroy_node(tree->root);
}


static node_t *binary_insert_impl(tree_t *tree, node_t *check, void *value, bool *present) {
	if(check == NULL) {
		return create_node(tree, value);
	}
	
	int comp = tree->compare_fp(check->value, value);
	
	switch(comp) {
		case 0:
			printf("Inserted value already present in tree\n");
			*present = true;
			break;
		case 1:
			check->child1 = binary_insert_impl(tree, check->child1, value, present);
			break;
		case -1:
			check->child2 = binary_insert_impl(tree, check->child2, value, present);
			break;
		default:
			fprintf(stderr, "Compare function returns invalid value\n");
			break;
	}
	
	return check;
}

void binary_insert(tree_t *tree, void *value) {
	
	bool present = false;
	
	tree->root = binary_insert_impl(tree, tree->root, value, &present);
	
	if(!present) {
		tree->num_elements += 1;
	}
}


static node_t *find_left_leaf(node_t *node) {
	if(node == NULL) {
		return NULL;
	}
	
	if(node->child1 == NULL) {
		return node;
	} else return find_left_leaf(node->child1);
	
}

node_t *binary_remove_impl(tree_t *tree, node_t *check, void *value, bool *present) {
	if(check == NULL) {
		return NULL;
	}
	
	
	int comp = tree->compare_fp(check->value, value);
	
	switch(comp) {
		case 0:
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
					check->child1 = NULL;
					destroy_node(check);
					return temp;
				
				//case for right child
				} else {
					node_t *temp = check->child2;
					check->child2 = NULL;
					destroy_node(check);
					return temp;
				}
			
			//node to be removed has two children
			} else {
				node_t *leaf = find_left_leaf(check->child2);
				check->value = leaf->value;
				check->child2 = binary_remove_impl(tree, check->child2, check->value, present);
				return check;
			}
			
			break;
		case 1:
			//left child
			check->child1 = binary_remove_impl(tree, check->child1, value, present);
			break;
		case -1:
			//right child
			check->child2 = binary_remove_impl(tree, check->child2, value, present);
			break;
		default:
			fprintf(stderr, "Compare function returns invalid value\n");
			break;
	}
	
	return check;
}

void binary_remove(tree_t *tree, void *value) {
	
	bool present = false;
	
	tree->root = binary_remove_impl(tree, tree->root, value, &present);
	
	if(present) {
		tree->num_elements -= 1;
	}
}

void binary_pop(tree_t *tree) {
	if(tree->num_elements == 0) {
		fprintf(stderr, "Cannot pop empty tree\n");
		return;
	}
	
	bool present = false;
	
	binary_remove_impl(tree, tree->root, tree->root->value, &present);
	
	tree->num_elements -= 1;
}


int binary_depth_impl(node_t *node) {	
	if(node == NULL) {
		return 0;
	}
	
	
	int left = binary_depth_impl(node->child1);
	int right = binary_depth_impl(node->child2);
	
	if(left > right) {
		return left + 1;
	}
	return right + 1;
}

int binary_depth(tree_t *tree) {
	return binary_depth_impl(tree->root);
}


bool binary_present_impl(tree_t *tree, node_t *check, void *value) {
	
	int comp = tree->compare_fp(check->value, value);
	
	switch(comp) {
		case 0:
			return true;
			break;
		case 1:
			if(check->child1 == NULL) {
				return false;
			}
			return binary_present_impl(tree, check->child1, value);
			break;
		case -1:
			return false;
			break;
		default:
			fprintf(stderr, "Compare function returns invalid value\n");
			break;
	}
	
	return binary_present_impl(tree, check->child2, value);
}

bool binary_present(tree_t *tree, void *value) {
	if(tree->num_elements == 0) {
		return false;
	}
	
	return binary_present_impl(tree, tree->root, value);
}


static void print_tree_inorder(tree_t *tree, node_t *node) {
	if(node == NULL) {
		printf("NULL\n");
	}
	
	
	if(node->child1 != NULL) {
		print_tree_inorder(tree, node->child1);
	}
	
	tree->print_fp(node->value);
	
	if(node->child2 != NULL) {
		print_tree_inorder(tree, node->child2);
	}
	
	return;
}

static void print_tree_preorder(tree_t *tree, node_t *node) {
	if(node == NULL) {
		printf("NULL\n");
	}
	
	
	tree->print_fp(node->value);
	
	if(node->child1 != NULL) {
		print_tree_preorder(tree, node->child1);
	}
	
	if(node->child2 != NULL) {
		print_tree_preorder(tree, node->child2);
	}
	
	return;
}

static void print_tree_postorder(tree_t *tree, node_t *node) {
	if(node == NULL) {
		printf("NULL\n");
	}
	
	
	if(node->child1 != NULL) {
		print_tree_postorder(tree, node->child1);
	}
	
	if(node->child2 != NULL) {
		print_tree_postorder(tree, node->child2);
	}
	
	tree->print_fp(node->value);
	
	return;
}

void binary_print(tree_t *tree, transversal_e transversal) {
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
	
	
	switch(transversal) {
		case inorder:
			print_tree_inorder(tree, tree->root);
			break;
		case preorder:
			print_tree_preorder(tree, tree->root);
			break;
		case postorder:
			print_tree_postorder(tree, tree->root);
			break;
		default:
			fprintf(stderr, "Invalid transversal in print_tree function\n");
			return;
	}
}



tree_ops_t binary_ops = {
	.create = binary_create,
	.destroy = binary_destroy,
	.insert = binary_insert,
	.remove = binary_remove,
	.pop = binary_pop,
	.depth = binary_depth,
	.present = binary_present,
	.print = binary_print
};