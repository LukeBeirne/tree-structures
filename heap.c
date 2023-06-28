#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"


/*
 * heap tree function definitions
 */

static void heapify(tree_t *tree) {
	
	return;
}

void heap_insert_node(tree_t *tree, int value) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	if(tree->num_elements == tree->heap_size) {
		fprintf(stderr, "Heap at capacity, returning without insert\n");
		return;
	}
	
	(tree->heap_array)[tree->num_elements] = value;
	
	heapify(tree);
	return;
}