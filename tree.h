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
 * function pointer typedefs
 */
 
typedef void (*traversal_func)(void *);

/* compare func return values:
-1 for first input < second input
0 for equal
1 for first input > second input
*/
typedef int (*compare_func)(void *, void *);



/*
 * struct definitions and typedefs
 */
 
typedef struct node node_t;

typedef struct tree {
	node_t *root;
	tree_e type;
	int num_elements;
	int heap_size;
	int *heap_array;
	compare_func compare_fp;
}tree_t;

/*
 * node struct function declarations
 */

//static function definitions in tree.c



/*
 * tree struct function declarations
 */

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



#endif