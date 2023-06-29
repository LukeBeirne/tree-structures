#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tree.h"


/*
 * heap tree function definitions
 */

static void heapify_up(tree_t *tree, int index) {
	int indexval = (tree->heap_array)[index];
	int parentindex;
	int parentval;
	int tmp;
	
	if(index % 2 == 0) {
		parentindex = (index-2)/2;
		parentval = (tree->heap_array)[parentindex];
		
		if(parentval < indexval) {
			tmp = parentval;
			(tree->heap_array)[parentindex] = indexval;
			(tree->heap_array)[index] = tmp;
		}
		else return;
	}
	else {
		parentindex = (index-1)/2;
		parentval = (tree->heap_array)[parentindex];
		
		if(parentval < indexval) {
			tmp = parentval;
			(tree->heap_array)[parentindex] = indexval;
			(tree->heap_array)[index] = tmp;
		}
		else return;
	}
	
	if(parentindex != 0) {
		heapify_up(tree, parentindex);
	}
	
}

static void heapify_down(tree_t *tree, int index) {
	//case for child1
	if((2*index)+1 > tree->num_elements) {
		return;
	}
	
	int indexval = (tree->heap_array)[index];
	
	int childindex = (2*index)+1;
	int childval = (tree->heap_array)[childindex];
	
	int tmp;
	
	if(childval > indexval) {
		tmp = childval;
		(tree->heap_array)[childindex] = indexval;
		(tree->heap_array)[index] = tmp;
		heapify_down(tree, childindex);
		return;
	}
	
	
	//case for child2
	if((2*index)+2 > tree->num_elements) {
		return;
	}
	
	childindex = (2*index)+2;
	childval = (tree->heap_array)[childindex];
	
	if(childval > indexval) {
		tmp = childval;
		(tree->heap_array)[childindex] = indexval;
		(tree->heap_array)[index] = tmp;
		heapify_down(tree, childindex);
		return;
	}	
	
}


void heap_insert_node(tree_t *tree, int value) {
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
	
	if(tree->num_elements != 1) {
		heapify_up(tree, tree->num_elements-1);
	}
	
}


void heap_remove_root(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	(tree->heap_array)[0] = (tree->heap_array)[tree->num_elements-1];
	tree->num_elements -= 1;
	heapify_down(tree, 0);
	
}

void heap_remove_last(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	
	if(tree->num_elements > 0) {
		tree->num_elements -= 1;
	}
	
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


bool heap_tree_node_present(tree_t *tree, int value) {
	if(tree->heap_array == NULL) {
		fprintf(stderr, "Heap array pointer is NULL\n");
		return false;
	}
	
	
	for(int i = 0; i < tree->num_elements; i++) {
		if((tree->heap_array)[i] == value) {
			return true;
		}
	}
	
	return false;
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