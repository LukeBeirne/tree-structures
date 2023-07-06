#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tree.h"

#define LEFTCHILD(index) (((index)<<1)+1)
#define RIGHTCHILD(index) (((index)<<1)+2)

#define PARENT(index) (((index)-1)>>1)


/*
 * heap tree function definitions
 */

static void heapify_up(tree_t *tree, int index) {
	int indexval = (tree->heap_array)[index];
	int parentval;
	int tmp;
	
	parentval = (tree->heap_array)[PARENT(index)];
	
	if(parentval < indexval) {
		tmp = parentval;
		(tree->heap_array)[PARENT(index)] = indexval;
		(tree->heap_array)[index] = tmp;
	}
	else 
		return;
	
	
	if(PARENT(index) != 0) {
		heapify_up(tree, PARENT(index));
	}
	
}

static void heapify_down(tree_t *tree, int index) {
	int indexval = (tree->heap_array)[index];
	
	int child1val;
	int child2val;
	
	int tmp;
	
	bool child1exists = false;
	bool child2exists = false;
	
	if((LEFTCHILD(index) < tree->num_elements)) {
		child1exists = true;
		child1val = (tree->heap_array)[LEFTCHILD(index)];
	}
	if(RIGHTCHILD(index) < tree->num_elements) {
		child2exists = true;
		child2val = (tree->heap_array)[RIGHTCHILD(index)];
	}
	
	//if no child exists
	if(!(child1exists || child2exists))
		return;
	
	//if only one child exists
	if(child1exists ^ child2exists) {
		if(child1exists) {
			tmp = child1val;
			(tree->heap_array)[LEFTCHILD(index)] = indexval;
			(tree->heap_array)[index] = tmp;
			heapify_down(tree, LEFTCHILD(index));
		}
		else {
			tmp = child2val;
			(tree->heap_array)[RIGHTCHILD(index)] = indexval;
			(tree->heap_array)[index] = tmp;
			heapify_down(tree, RIGHTCHILD(index));
		}
	}
	
	//both children exist
	else {
		if(child1val > child2val) {
			tmp = child1val;
			(tree->heap_array)[LEFTCHILD(index)] = indexval;
			(tree->heap_array)[index] = tmp;
			heapify_down(tree, LEFTCHILD(index));
		}
		else {
			tmp = child2val;
			(tree->heap_array)[RIGHTCHILD(index)] = indexval;
			(tree->heap_array)[index] = tmp;
			heapify_down(tree, RIGHTCHILD(index));
		}
	}
	
}


tree_t *heap_create(tree_t *tree, int heap_size) {
	tree->heap_array = (int *)malloc(heap_size*sizeof(int));
	tree->heap_size = heap_size;
	return tree;
}

void heap_destroy(tree_t *tree) {
	free(tree->heap_array);
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

void heap_pop(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return;
	}
	
	(tree->heap_array)[0] = (tree->heap_array)[tree->num_elements-1];
	tree->num_elements -= 1;
	heapify_down(tree, 0);
	
}

void heap_remove(tree_t *tree) {
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
 * https://www.geeksforgeeks.org/height-complete-heap-tree-heap-n-nodes/
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


bool heap_present(tree_t *tree, int value) {
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


void heap_print(tree_t *tree) {	
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



tree_ops_t heap_ops = {
	.create = heap_create,
	.destroy = heap_destroy,
	.insert = heap_insert_node,
	.remove = heap_remove,
	.pop = heap_pop,
	.depth = heap_depth,
	.present = heap_present,
	.print = heap_print
};