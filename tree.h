#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef enum transversal {
	inorder,
	preorder,
	postorder,
	invalid_transversal
} transversal_e;

typedef enum tree_type {
	binary = 1,
	heap,
	avl,
	invalid_tree
} tree_e;



/*
 * function pointer typedefs
 */
 
typedef void (*traversal_func)(void *);

/* compare func return values:
-1 for first input < second input
0 for equal
1 for first input > second input
*/
typedef void (*print_func)(void *);
typedef int (*compare_func)(void *, void *);

typedef struct tree tree_t;


typedef tree_t *(*create_op)(tree_t *, int);
typedef int (*destroy_op)(tree_t *);
typedef int (*insert_op)(tree_t *, void *);
typedef void *(*remove_op)(tree_t *, void *);
typedef void *(*pop_op)(tree_t *);
typedef int (*depth_op)(tree_t *);
typedef bool (*present_op)(tree_t *, void *);
typedef void (*print_op)(tree_t *, transversal_e);



/*
 * struct definitions and typedefs
 */
 
typedef struct node node_t;

typedef struct tree_ops {
	create_op create;
	destroy_op destroy;
	insert_op insert;
	remove_op remove;
	pop_op pop;
	depth_op depth;
	present_op present;
	print_op print;
}tree_ops_t;

struct tree {
	void *priv;
	tree_e type;
	size_t type_size;
	int num_elements;
	compare_func compare_fp;
	print_func print_fp;
	tree_ops_t *ops;
};

extern tree_ops_t heap_ops;
extern tree_ops_t binary_ops;
extern tree_ops_t avl_ops;



/*
 * generic tree functions
 */

//heap_size is used to mark the number of elements in a heap tree
//the size value is ignored for all non-heap tree types
static inline tree_t *create_tree(tree_e type, compare_func c_func, print_func p_func, int heap_size) {
	tree_t *tree = (tree_t *)calloc(1, sizeof(tree_t));
	tree->type = type;
	tree->compare_fp = c_func;
	tree->print_fp = p_func;
	
	switch(type) {
		case binary:
			tree->ops = &binary_ops;
			break;
			//return tree->ops->create(tree);
		case heap:
			tree->ops = &heap_ops;
			return tree->ops->create(tree, heap_size);
		case avl:
			tree->ops = &avl_ops;
			break;
			//return tree->ops->create(tree);
		default: //invalid tree type
			fprintf(stderr, "Invalid tree type\n");
			return NULL;
	}
	return tree;
}

//returns 2 for NULL heap_array pointer
static inline int destroy_tree(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return 1;
	}
	
	
	int retval = tree->ops->destroy(tree);
	
	free(tree);
	
	return retval;
}

//returns true if input tree is NULL
static inline bool tree_empty(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return true;
	}
	
	if(tree->num_elements == 0) {
		return true;
	}
	return false;
}

//returns 0 if input tree is NULL
static inline int tree_get_num_elements(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return 0;
	}
	
	return tree->num_elements;
}



/*
 * static inline tree struct function declarations
 */

//for non-heap trees it does nothing if inserted value already exists
//returns 2 for NULL heap_array pointer OR if value is already present
//returns 3 for heap_array at capacity
static inline int tree_insert_node(tree_t *tree, void *value) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return 1;
	}
	
	return tree->ops->insert(tree, value);
}

//does nothing if value to be removed does not exist
//returns removed value if it is present
//returns NULL if removed value is not present
static inline void *tree_remove_node(tree_t *tree, void *value) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return NULL;
	}
	
	return tree->ops->remove(tree, value);
}

//returns popped value if it is present
//returns NULL if removed value is not present
static inline void *tree_pop(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return NULL;
	}
	
	return tree->ops->pop(tree);
}

//returns 0 if input tree is NULL
static inline int tree_depth(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return 0;
	}
	
	return tree->ops->depth(tree);
}

//returns false if input tree is NULL
static inline bool tree_node_present(tree_t *tree, void *value) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return false;
	}
	
	return tree->ops->present(tree, value);
}

//transversal value is ignored for heap trees
//prints "NULL" if input tree is empty
static inline void tree_print(tree_t *tree, transversal_e transversal) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	tree->ops->print(tree, transversal);
}



/* OLD CODE FOR REFERENCE

 * 
 * tree struct function declarations
 *

//heap_size is used to mark the number of elements in a heap tree
//the size value is ignored for all non-heap tree types
tree_t *create_tree(tree_e type, compare_func cp_f, int heap_size);
void destroy_tree(tree_t *tree);

//for non-heap trees it does nothing if inserted value already exists
void insert_node(tree_t *tree, int value);

//does nothing if value to be removed does not exist
void remove_node(tree_t *tree, int value);

//returns true if input tree is NULL
bool tree_empty(tree_t *tree);

//returns 0 if input tree is NULL
int tree_depth(tree_t *tree);

//returns 0 if input tree is NULL
int tree_get_num_elements(tree_t *tree);

//returns false if input tree is NULL
bool tree_node_present(tree_t *tree, int value);

//inorder = 0, preorder = 1, postorder = 2, invalid = 3
//transversal value is ignored for heap trees
//prints "NULL" if tree is empty and returns
void print_tree(tree_t *tree, transversal_e transversal);

*/

#endif