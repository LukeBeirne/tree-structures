#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdbool.h>


/*
 * struct definitions and typedefs
 */
 
struct tree;
typedef struct tree tree_t;

struct node;
typedef struct node node_t;



/*
 * node struct function definitions
 */

//static function definitions in tree.c



/*
 * tree struct function definitions
 */

tree_t *create_tree();
void destroy_tree(tree_t *a);

void insert_node(tree_t *a, int value);
void remove_node(tree_t *a, int value);

//returns true if input tree is NULL
bool tree_empty(tree_t *a);

int tree_depth(tree_t *a);

//returns false if input tree is NULL
bool tree_node_present(tree_t *a, int value);

//void tree_traversals(tree_t *a, traversal type);
//1, 2, or 3 for traversal type?



/* unused book functions as references

void print_book(book_t *a);

void set_title(book_t *a, char *title);
void set_id(book_t *a, int id);

char *get_title(book_t *a);
int get_id(book_t *a);

void write_book(book_t *a, FILE *fn);
book_t *read_book(FILE *fn);

*/


#endif