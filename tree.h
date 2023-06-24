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
	binary,
	avl,
	heap,
	invalid_tree
} tree_e;

/*
 * struct definitions and typedefs
 */
 
struct tree;
typedef struct tree tree_t;

struct node;
typedef struct node node_t;



/*
 * node struct function declarations
 */

//static function definitions in tree.c

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
 * tree struct function declarations
 */

tree_t *create_tree(tree_e type, compare_func cp_f);
void destroy_tree(tree_t *tree);

//does nothing if inserted value already exists
void insert_node(tree_t *tree, int value);

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
//prints "NULL" if tree is empty and returns
void print_tree(tree_t *tree, transversal_e transversal);


#endif