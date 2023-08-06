#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tree.h"

#define LEFTCHILD(index) (((index)<<1)+1)
#define RIGHTCHILD(index) (((index)<<1)+2)

#define PARENT(index) (((index)-1)>>1)

#define GET_PRIV(t) \
	(heap_priv_t *)((t)->priv)

typedef struct heap_priv {
	int heap_size;
	void **heap_array;
} heap_priv_t;

/*
 * heap tree function definitions
 */

static void heapify_up(tree_t *tree, int index) {
	void *indexval = (GET_PRIV(tree))->heap_array[index];
	void *parentval;
	void *tmp;
	
	parentval = (GET_PRIV(tree))->heap_array[PARENT(index)];
	
	int comp = tree->compare_fp(parentval, indexval);
	
	if(comp == -1) {
		tmp = parentval;
		(GET_PRIV(tree))->heap_array[PARENT(index)] = indexval;
		(GET_PRIV(tree))->heap_array[index] = tmp;
	}
	else 
		return;
	
	
	if(PARENT(index) != 0) {
		heapify_up(tree, PARENT(index));
	}
	
}

static void heapify_down(tree_t *tree, int index) {
	void *indexval = (GET_PRIV(tree))->heap_array[index];
	
	void *child1val;
	void *child2val;
	
	void *tmp;
	
	bool child1exists = false;
	bool child2exists = false;
	
	if((LEFTCHILD(index) < tree->num_elements)) {
		child1exists = true;
		child1val = (GET_PRIV(tree))->heap_array[LEFTCHILD(index)];
	}
	if(RIGHTCHILD(index) < tree->num_elements) {
		child2exists = true;
		child2val = (GET_PRIV(tree))->heap_array[RIGHTCHILD(index)];
	}
	
	//if no child exists
	if(!(child1exists || child2exists))
		return;
	
	//if only one child exists
	if(child1exists ^ child2exists) {
		if(child1exists) {
			tmp = child1val;
			(GET_PRIV(tree))->heap_array[LEFTCHILD(index)] = indexval;
			(GET_PRIV(tree))->heap_array[index] = tmp;
			heapify_down(tree, LEFTCHILD(index));
		}
		else {
			tmp = child2val;
			(GET_PRIV(tree))->heap_array[RIGHTCHILD(index)] = indexval;
			(GET_PRIV(tree))->heap_array[index] = tmp;
			heapify_down(tree, RIGHTCHILD(index));
		}
	}
	
	//both children exist
	else {
		int comp = tree->compare_fp(child1val, child2val);
		if(comp == 1) {
			tmp = child1val;
			(GET_PRIV(tree))->heap_array[LEFTCHILD(index)] = indexval;
			(GET_PRIV(tree))->heap_array[index] = tmp;
			heapify_down(tree, LEFTCHILD(index));
		}
		else {
			tmp = child2val;
			(GET_PRIV(tree))->heap_array[RIGHTCHILD(index)] = indexval;
			(GET_PRIV(tree))->heap_array[index] = tmp;
			heapify_down(tree, RIGHTCHILD(index));
		}
	}
	
}


tree_t *heap_create(tree_t *tree, int heap_size) {
	tree->priv = (heap_priv_t *)malloc(sizeof(heap_priv_t));
	(GET_PRIV(tree))->heap_size = heap_size;
	(GET_PRIV(tree))->heap_array = (void **)malloc(heap_size*sizeof(void *));
	return tree;
}

int heap_destroy(tree_t *tree) {
	if((GET_PRIV(tree))->heap_array == NULL) {
		fprintf(stderr, "Heap array pointer is NULL\n");
		return 2;
	}
	
	free((GET_PRIV(tree))->heap_array);
	
	return 0;
}


int heap_insert_node(tree_t *tree, void *value) {
	if((GET_PRIV(tree))->heap_array == NULL) {
		fprintf(stderr, "Heap array pointer is NULL\n");
		return 2;
	}
	
	if(tree->num_elements == (GET_PRIV(tree))->heap_size) {
		fprintf(stderr, "Heap at capacity, returning without insert\n");
		return 3;
	}
	
	(GET_PRIV(tree))->heap_array[tree->num_elements] = value;
	
	tree->num_elements += 1;
	
	if(tree->num_elements != 1) {
		heapify_up(tree, tree->num_elements-1);
	}
	
	return 0;	
}

void *heap_pop(tree_t *tree) {
	if(tree == NULL) {
		fprintf(stderr, "Tree pointer is NULL\n");
		return NULL;
	}
	
	void *retval = (GET_PRIV(tree))->heap_array[0];
	
	(GET_PRIV(tree))->heap_array[0] = (GET_PRIV(tree))->heap_array[tree->num_elements-1];
	tree->num_elements -= 1;
	heapify_down(tree, 0);
	
	return retval;
	
}

void *heap_remove(tree_t *tree, void *value) {
	
	void *check;
	for(int i = 0; i < tree->num_elements; i++) {
		check = (GET_PRIV(tree))->heap_array[i];
		if(tree->compare_fp(check, value) == 0) {
			//stuff
		}
	}
	
	if(tree->num_elements > 0) {
		tree->num_elements -= 1;
		return value;
	}
	
	return NULL;
}


/* 
 * depth formula for heap structures using number of elements:
 * https://www.geeksforgeeks.org/height-complete-heap-tree-heap-n-nodes/
 */
int heap_depth(tree_t *tree) {	
	if((GET_PRIV(tree))->heap_array == NULL) {
		fprintf(stderr, "Heap array pointer is NULL\n");
		return 0;
	}
	
	
	if(tree->num_elements == 0) {
		return 0;
	}
	
	return (int)(floor(log2(tree->num_elements))+1);
}


bool heap_present(tree_t *tree, void *value) {
	if((GET_PRIV(tree))->heap_array == NULL) {
		fprintf(stderr, "Heap array pointer is NULL\n");
		return false;
	}
	
	
	void *check;
	for(int i = 0; i < tree->num_elements; i++) {
		check = (GET_PRIV(tree))->heap_array[i];
		if(tree->compare_fp(check, value) == 0) {
			return true;
		}
	}
	
	return false;
}


void heap_print(tree_t *tree, transversal_e transversal) {	
	if((GET_PRIV(tree))->heap_array == NULL) {
		fprintf(stderr, "Heap array pointer is NULL\n");
		return;
	}
	
	
	if(tree->num_elements == 0) {
		printf("NULL\n");
		return;
	}
	
	for(int i = 0; i < tree->num_elements; i++) {
		tree->print_fp((GET_PRIV(tree))->heap_array[i]);
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