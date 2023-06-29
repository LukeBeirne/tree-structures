#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
	
	if(tree->heap_array == NULL) {
		fprintf(stderr, "Heap array pointer is NULL\n");
		return;
	}
	
	if(tree->num_elements == tree->heap_size) {
		fprintf(stderr, "Heap at capacity, returning without insert\n");
		return;
	}
	
	(tree->heap_array)[tree->num_elements] = value;
	
	tree->num_elements += 1;
	
	heapify(tree);
	return;
}

/* 
 * depth formula for heap structures using number of elements:
 * https://www.geeksforgeeks.org/height-complete-binary-tree-heap-n-nodes/
 */
int heap_depth(tree_t *tree) {	
	if(tree->heap_array == NULL) {
		fprintf(stderr, "Heap array pointer is NULL\n");
		return 0;
	}
	
	
	if(tree->num_elements == 0) {
		return 0;
	}
	
	return (int)(floor(log2(tree->num_elements))+1);
}

void print_heap(tree_t *tree) {	
	if(tree->heap_array == NULL) {
		fprintf(stderr, "Heap array pointer is NULL\n");
		return;
	}
	
	
	if(tree->num_elements == 0) {
		printf("NULL\n");
		return;
	}
	
	for(int i = 0; i < tree->num_elements; i++) {
		printf("%d\n", (tree->heap_array)[i]);
	}
}