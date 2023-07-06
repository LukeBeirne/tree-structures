#ifndef TREE_H
#define TREE_H
#include <stdio.h>
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
 * struct definitions and typedefs
 */
 
typedef struct node node_t;


/* compare func return values:
-1 for first input < second input
0 for equal
1 for first input > second input
*/
typedef int (*compare_func)(void *, void *);

typedef struct tree {
	node_t *root;
	tree_e type;
	int num_elements;
	int heap_size;
	int *heap_array;
	compare_func compare_fp;
	tree_ops_t *ops;
}tree_t;

extern tree_ops_t heap_ops;
extern tree_ops_t binary_ops;
extern tree_ops_t avl_ops;



/*
 * function pointer typedefs
 */
 
typedef void (*traversal_func)(void *);

typedef tree_t *(*create_op)(void *, void *);
typedef void (*destroy_op)(void *);
typedef void (*insert_op)(void *, void *);
typedef void (*remove_op)(void *, void *);
typedef void (*pop_op)(void *);
typedef int (*depth_op)(void *);
typedef bool (*present_op)(void *, void *);
typedef void (*print_op)(void *, void *);



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



/*
 * generic tree functions
 */

tree_t *create_tree(tree_e type, compare_func c_func, int heap_size) {
	tree_t *tree = (tree_t *)calloc(1, sizeof(tree_t));
	tree->compare_fp = c_func;
	tree->type = type;
	
	switch(type) {
		case binary:
			tree->ops = binary_ops;
			break;
			//return tree->ops->create(tree);
		case heap:
			tree->ops = heap_ops;
			return tree->ops->create(tree, heap_size);
		case avl:
			tree->ops = avl_ops;
			break;
			//return tree->ops->create(tree);
		default: //invalid tree type
			fprintf(stderr, "Invalid tree type\n");
			return NULL;
	}
	return tree;
}

void destroy_tree(tree_t *tree) {
	tree->ops->destroy;
	
	free(tree);
}

//returns true if input tree is NULL
bool empty(tree_t *tree) {
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
int get_num_elements(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	return tree->num_elements;
}

/*
 * static inline tree struct function declarations
 */

//heap_size is used to mark the number of elements in a heap tree
//the size value is ignored for all non-heap tree types
static inline tree_t *create_tree(tree_t *tree, compare_func cp_f, int heap_size) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	return tree->ops->create(tree, fp_f, heap_size);
}

static inline void destroy_tree(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	tree->ops->destroy(tree);
}

//for non-heap trees it does nothing if inserted value already exists
static inline void insert_node(tree_t *tree, int value) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	tree->ops->insert(tree, value);
}

//does nothing if value to be removed does not exist
static inline void remove_node(tree_t *tree, int value) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	tree->ops->remove(tree, value);
}

static inline void pop(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	tree->ops->pop(tree);
}

//returns 0 if input tree is NULL
static inline int depth(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	return tree->ops->depth(tree);
}

//returns false if input tree is NULL
static inline bool present(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	return tree->ops->present(tree);
}

//transversal value is ignored for heap trees
//prints "NULL" if input tree is empty
static inline void print(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	tree->ops->print(tree);
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