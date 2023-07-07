#include "tree.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	
	//random values assigned into tree nodes
	//srand call to ensure random values stay the same
	//srand(50) returns increasing values with 1 repeat
	srand(100);
	int upbound = 100;
	
	int value = rand() % upbound;
	
	
	
	/*
	 *
	 * BINARY TREE TESTING *******************************************************
	 *
	 */
	printf("--------BINARY TREE TESTING--------\n");
	
	
	
	//creating trees
	printf("Creating tree with %d as root\n", value);
	tree_t *tree = create_tree(binary, NULL, 0);
	tree_t *emptytree = create_tree(binary, NULL, 0);
	
	//insert root into tree
	tree_insert_node(tree, value);
	
	//print trees with only root value
	tree_print(tree, inorder);
	tree_print(emptytree, inorder);
	
	//test emptiness
	if(tree_empty(tree)) {
		printf("The tree is empty\n");
	}
	else {
		printf("The tree is not empty\n");
	}
	
	if(tree_empty(emptytree)) {
		printf("The tree is empty\n");
	}
	else {
		printf("The tree is not empty\n");
	}
	
	//test depth
	printf("Tree depth is %d\n", tree_depth(tree));
	printf("Empty tree depth is %d\n", tree_depth(emptytree));
	
	//test num elements
	printf("%d elements in tree\n", tree_get_num_elements(tree));
	printf("%d elements in empty tree\n", tree_get_num_elements(emptytree));
	
	//test node present using root value
	if(tree_node_present(tree, value)) {
		printf("Value %d present in tree\n", value);
	}
	else printf("Value %d not present in tree\n", value);
	
	//insert values
	int insertvalue;
	for(int i = 0; i < 5; i++) {
		insertvalue = rand() % upbound;
		printf("Inserting value %d into tree\n", insertvalue);
		tree_insert_node(tree, insertvalue);
	}
	
	//print new tree with various orders
	printf("Tree contents inorder:\n");
	tree_print(tree, inorder);
	
	printf("Tree contents preorder:\n");
	tree_print(tree, preorder);
	
	printf("Tree contents postorder:\n");
	tree_print(tree, postorder);
	
	//test new depth
	printf("Tree depth is %d\n", tree_depth(tree));
	
	//test new num elements
	printf("%d elements in tree\n", tree_get_num_elements(tree));
	
	//test node present using last inserted value
	if(tree_node_present(tree, insertvalue)) {
		printf("Value %d present in tree\n", insertvalue);
	} 
	else {
		printf("Value %d not present in tree\n", insertvalue);
	}
	
	if(tree_node_present(tree, 101)) {
		printf("Value %d present in tree\n", 101);
	}
	else {
		printf("Value %d not present in tree\n", 101);
	}
	
	//test removing value
	int removevalue = 40;
	printf("Removing value %d from tree\n", removevalue);
	tree_remove_node(tree, removevalue);
	
	//re-print tree
	printf("Tree contents inorder:\n");
	tree_print(tree, inorder);
	
	printf("Tree contents preorder:\n");
	tree_print(tree, preorder);
	
	printf("Tree contents postorder:\n");
	tree_print(tree, postorder);
	
	//test new depth
	printf("Tree depth is %d\n", tree_depth(tree));
	
	//test new num elements
	printf("%d elements in tree\n", tree_get_num_elements(tree));
	
	//destroy binary trees
	destroy_tree(tree);
	destroy_tree(emptytree);
	
	
	/*
	 *
	 * HEAP TREE TESTING *******************************************************
	 *
	 */
	printf("\n--------HEAP TREE TESTING--------\n");
	
	
	
	//creating trees
	int rootvalue = 10;
	tree_t *heaptree = create_tree(heap, NULL, 10);
	tree_t *emptyheap = create_tree(heap, NULL, 10);
	
	//insert root into tree
	tree_insert_node(heaptree, rootvalue);
	
	//print trees with only root value
	tree_print(heaptree, inorder);
	tree_print(emptyheap, inorder);
	
	//test emptiness
	if(tree_empty(heaptree)) {
		printf("The heap is empty\n");
	}
	else {
		printf("The heap is not empty\n");
	}
	
	if(tree_empty(emptyheap)) {
		printf("The heap is empty\n");
	}
	else {
		printf("The heap is not empty\n");
	}
	
	//test depth
	printf("Heap depth is %d\n", tree_depth(heaptree));
	printf("Empty heap depth is %d\n", tree_depth(emptyheap));
	
	//test num elements
	printf("%d elements in heap\n", tree_get_num_elements(heaptree));
	printf("%d elements in empty heap\n", tree_get_num_elements(emptyheap));
	
	//test node present using root value
	if(tree_node_present(heaptree, rootvalue)) {
		printf("Value %d present in heap\n", rootvalue);
	}
	else printf("Value %d not present in heap\n", rootvalue);
	
	//insert values
	for(int i = 0; i < 5; i++) {
		insertvalue = rand() % upbound;
		printf("Inserting value %d into heap\n", insertvalue);
		tree_insert_node(heaptree, insertvalue);
	}
	
	//print new heap
	printf("Heap contents:\n");
	tree_print(heaptree, inorder);
	
	//test new depth
	printf("Heap depth is %d\n", tree_depth(heaptree));
	
	//test new num elements
	printf("%d elements in heap\n", tree_get_num_elements(heaptree));
	
	//test node present using last inserted value
	if(tree_node_present(heaptree, insertvalue)) {
		printf("Value %d present in heap\n", insertvalue);
	}
	else printf("Value %d not present in heap\n", insertvalue);
	
	//test removing last element
	removevalue = 10;
	printf("Removing value %d from heap\n", removevalue);
	tree_remove_node(heaptree, removevalue);
	
	//print new heap
	printf("Heap contents after removing last inserted value:\n");
	tree_print(heaptree, inorder);
	
	//test new num elements
	printf("%d elements in heap\n", tree_get_num_elements(heaptree));
	
	//test removing root value
	removevalue = 81;
	printf("Removing value %d from heap\n", removevalue);
	tree_remove_node(heaptree, removevalue);
	
	//print new heap
	printf("Heap contents after removing root value:\n");
	tree_print(heaptree, inorder);
	
	//test new num elements
	printf("%d elements in heap\n", tree_get_num_elements(heaptree));
	
	//test new depth
	printf("Heap depth is %d\n", tree_depth(heaptree));
	
	
	//destroy heap trees
	destroy_tree(heaptree);
	destroy_tree(emptyheap);
	
	return(0);
}