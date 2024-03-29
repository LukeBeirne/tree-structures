#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define valid_tree_type(t) \
	(t) >= inorder && (t) < invalid_transversal

#define GET_PRIV(t) \
	(node_t *)((t)->priv)


struct node {
	void *value;
	node_t *child1;
	node_t *child2;
	int balance;
};


/*
 * node struct function definitions
 */

static node_t *create_node(tree_t *tree, void *value) {
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
 * avl tree function definitions
 */

void rebalance_impl(node_t *node) {
	if(node == NULL) {
		return;
	}
	
	if(abs(node->balance)) > 1) {
		//compute rebalance
	}
	
	rebalance_impl(node->child1);
	rebalance_impl(node->child2);
	
}

void rebalance(tree_t *tree) {
	redepth_impl(GET_PRIV(tree));
}


int avl_destroy(tree_t *tree) {
	//destroy_node function traverses through tree to destroy each node
	destroy_node(GET_PRIV(tree));
	return 0;
}


static node_t *avl_insert_impl(tree_t *tree, node_t *check, void *value, bool *present) {
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
			check->child1 = avl_insert_impl(tree, check->child1, value, present);
			
			if(!present) {
				check->balance += 1;
			}
			break;
		case -1:
			check->child2 = avl_insert_impl(tree, check->child2, value, present);
			
			if(!present) {
				check->balance -= 1;
			}
			break;
		default:
			fprintf(stderr, "Compare function returns invalid value\n");
			break;
	}
	
	return check;
}

int avl_insert(tree_t *tree, void *value) {
	
	bool present = false;
	
	tree->priv = avl_insert_impl(tree, GET_PRIV(tree), value, &present);
	
	if(!present) {
		tree->num_elements += 1;
		return 0;
	}
	
	rebalance(tree);
	
	return 2;
}


static node_t *find_left_leaf(node_t *node) {
	if(node == NULL) {
		return NULL;
	}
	
	if(node->child1 == NULL) {
		return node;
	} else return find_left_leaf(node->child1);
	
}

node_t *avl_remove_impl(tree_t *tree, node_t *check, void *value, bool *present) {
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
				check->child2 = avl_remove_impl(tree, check->child2, check->value, present);
				return check;
			}
			
			break;
		case 1:
			//left child
			check->child1 = avl_remove_impl(tree, check->child1, value, present);
			break;
		case -1:
			//right child
			check->child2 = avl_remove_impl(tree, check->child2, value, present);
			break;
		default:
			fprintf(stderr, "Compare function returns invalid value\n");
			break;
	}
	
	return check;
}

void *avl_remove(tree_t *tree, void *value) {
	
	bool present = false;
	
	tree->priv = avl_remove_impl(tree, GET_PRIV(tree), value, &present);
	
	if(present) {
		tree->num_elements -= 1;
		return value;
	}
	
	return NULL;
}

void *avl_pop(tree_t *tree) {
	if(tree->num_elements == 0) {
		fprintf(stderr, "Cannot pop empty tree\n");
		return NULL;
	}
	
	void *retval = (GET_PRIV(tree))->value;
	
	bool present = false;
	
	avl_remove_impl(tree, GET_PRIV(tree), (GET_PRIV(tree))->value, &present);
	
	tree->num_elements -= 1;
	
	return retval;
}


int avl_depth_impl(node_t *node) {	
	if(node == NULL) {
		return 0;
	}
	
	
	int left = avl_depth_impl(node->child1);
	int right = avl_depth_impl(node->child2);
	
	if(left > right) {
		return left + 1;
	}
	return right + 1;
}

int avl_depth(tree_t *tree) {
	return avl_depth_impl(GET_PRIV(tree));
}


bool avl_present_impl(tree_t *tree, node_t *check, void *value) {
	
	int comp = tree->compare_fp(check->value, value);
	
	switch(comp) {
		case 0:
			return true;
			break;
		case 1:
			if(check->child1 == NULL) {
				return false;
			}
			return avl_present_impl(tree, check->child1, value);
			break;
		case -1:
			return false;
			break;
		default:
			fprintf(stderr, "Compare function returns invalid value\n");
			break;
	}
	
	return avl_present_impl(tree, check->child2, value);
}

bool avl_present(tree_t *tree, void *value) {
	if(tree->num_elements == 0) {
		return false;
	}
	
	return avl_present_impl(tree, GET_PRIV(tree), value);
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

void avl_print(tree_t *tree, transversal_e transversal) {
	//check for valid transversal type
	if(!(valid_tree_type(transversal))) {
		fprintf(stderr, "Invalid transversal in print_tree function\n");
		return;
	}
	
	
	//check for empty tree
	if(GET_PRIV(tree) == NULL) {
		printf("NULL\n");
		return;
	}
	
	
	switch(transversal) {
		case inorder:
			print_tree_inorder(tree, GET_PRIV(tree));
			break;
		case preorder:
			print_tree_preorder(tree, GET_PRIV(tree));
			break;
		case postorder:
			print_tree_postorder(tree, GET_PRIV(tree));
			break;
		default:
			fprintf(stderr, "Invalid transversal in print_tree function\n");
			return;
	}
}



tree_ops_t avl_ops = {
	.create = NULL,
	.destroy = avl_destroy,
	.insert = avl_insert,
	.remove = avl_remove,
	.pop = avl_pop,
	.depth = avl_depth,
	.present = avl_present,
	.print = avl_print
};