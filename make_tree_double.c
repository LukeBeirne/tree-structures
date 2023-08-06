#include "tree.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
 * static function definitions
 */

static int compare_double(void *val1, void *val2) {
	double *value1 = (double *)val1;
	double *value2 = (double *)val2;
	
	if(*value1 == *value2) {
		return 0;
	}
	
	else if(*value1 < *value2) {
		return -1;
	}
	
	return 1;
}

static void print_double(void *value) {
	double *val = (double *)value;
	printf("%f\n", *val);
}



int main(int argc, char *argv[]) {
	
	//random values assigned into tree nodes
	//srand call to ensure random values stay the same
	//srand(50) returns increasing values with 1 repeat
	srand(100);
	int upbound = 100;
	
	double value = rand() % upbound;
	
	
	
	/*
	 *
	 * BINARY TREE TESTING *******************************************************
	 *
	 */
	printf("--------BINARY TREE TESTING--------\n");
	
	
	
	//creating trees
	printf("Creating tree with %f as root\n", value);
	tree_t *tree = create_tree(binary, compare_double, print_double, 0);
	tree_t *emptytree = create_tree(binary, compare_double, print_double, 0);
	
	//insert root into tree
	tree_insert_node(tree, &value);
	
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
	if(tree_node_present(tree, &value)) {
		printf("Value %f present in tree\n", value);
	}
	else printf("Value %f not present in tree\n", value);
	
	//insert values
	double insertvalue1 = rand() % upbound;
	printf("Inserting value %f into tree\n", insertvalue1);
	tree_insert_node(tree, &insertvalue1);
	
	double insertvalue2 = rand() % upbound;
	printf("Inserting value %f into tree\n", insertvalue2);
	tree_insert_node(tree, &insertvalue2);
	
	double insertvalue3 = rand() % upbound;
	printf("Inserting value %f into tree\n", insertvalue3);
	tree_insert_node(tree, &insertvalue3);
	
	double insertvalue4 = rand() % upbound;
	printf("Inserting value %f into tree\n", insertvalue4);
	tree_insert_node(tree, &insertvalue4);
	
	double insertvalue5 = rand() % upbound;
	printf("Inserting value %f into tree\n", insertvalue5);
	tree_insert_node(tree, &insertvalue5);
	
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
	if(tree_node_present(tree, &insertvalue5)) {
		printf("Value %f present in tree\n", insertvalue5);
	} 
	else {
		printf("Value %f not present in tree\n", insertvalue5);
	}
	
	double testval = 101;
	if(tree_node_present(tree, &testval)) {
		printf("Value %f present in tree\n", testval);
	}
	else {
		printf("Value %f not present in tree\n", testval);
	}
	
	//test removing value
	double removevalue = 40;
	printf("Removing value %f from tree\n", removevalue);
	tree_remove_node(tree, &removevalue);
	
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
	double rootvalue = 10;
	printf("Creating heap with %f as root\n", rootvalue);
	tree_t *heaptree = create_tree(heap, compare_double, print_double, 10);
	tree_t *emptyheap = create_tree(heap, compare_double, print_double, 10);
	
	//insert root into tree
	tree_insert_node(heaptree, &rootvalue);
	
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
	if(tree_node_present(heaptree, &rootvalue)) {
		printf("Value %f present in heap\n", rootvalue);
	}
	else printf("Value %f not present in heap\n", rootvalue);
	
	//insert values
	double insertvalue6 = rand() % upbound;
	printf("Inserting value %f into tree\n", insertvalue6);
	tree_insert_node(heaptree, &insertvalue6);
	
	double insertvalue7 = rand() % upbound;
	printf("Inserting value %f into tree\n", insertvalue7);
	tree_insert_node(tree, &insertvalue7);
	
	double insertvalue8 = rand() % upbound;
	printf("Inserting value %f into tree\n", insertvalue8);
	tree_insert_node(heaptree, &insertvalue8);
	
	double insertvalue9 = rand() % upbound;
	printf("Inserting value %f into tree\n", insertvalue9);
	tree_insert_node(heaptree, &insertvalue9);
	
	double insertvalue10 = rand() % upbound;
	printf("Inserting value %f into tree\n", insertvalue10);
	tree_insert_node(heaptree, &insertvalue10);
	
	//print new heap
	printf("Heap contents:\n");
	tree_print(heaptree, inorder);
	
	//test new depth
	printf("Heap depth is %d\n", tree_depth(heaptree));
	
	//test new num elements
	printf("%d elements in heap\n", tree_get_num_elements(heaptree));
	
	//test node present using last inserted value
	if(tree_node_present(heaptree, &insertvalue10)) {
		printf("Value %f present in heap\n", insertvalue10);
	}
	else printf("Value %f not present in heap\n", insertvalue10);
	
	//test removing last element
	removevalue = 10;
	printf("Removing value %f from heap\n", removevalue);
	tree_remove_node(heaptree, &removevalue);
	
	//print new heap
	printf("Heap contents after removing last inserted value:\n");
	tree_print(heaptree, inorder);
	
	//test new num elements
	printf("%d elements in heap\n", tree_get_num_elements(heaptree));
	
	//test removing root value
	removevalue = 81;
	printf("Removing value %f from heap\n", removevalue);
	tree_remove_node(heaptree, &removevalue);
	
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
	
	
	/*
	 *
	 * AVL TREE TESTING *******************************************************
	 *
	 */
	printf("--------AVL TREE TESTING--------\n");
	
	
	
	//creating trees
	printf("Creating tree with %f as root\n", value);
	tree_t *avltree = create_tree(avl, compare_double, print_double, 0);
	tree_t *emptyavltree = create_tree(avl, compare_double, print_double, 0);
	
	//insert root into tree
	tree_insert_node(avltree, &value);
	
	//print trees with only root value
	tree_print(avltree, inorder);
	tree_print(emptyavltree, inorder);
	
	//test emptiness
	if(tree_empty(avltree)) {
		printf("The tree is empty\n");
	}
	else {
		printf("The tree is not empty\n");
	}
	
	if(tree_empty(emptyavltree)) {
		printf("The tree is empty\n");
	}
	else {
		printf("The tree is not empty\n");
	}
	
	//test depth
	printf("Tree depth is %d\n", tree_depth(avltree));
	printf("Empty tree depth is %d\n", tree_depth(emptyavltree));
	
	//test num elements
	printf("%d elements in tree\n", tree_get_num_elements(avltree));
	printf("%d elements in empty tree\n", tree_get_num_elements(emptyavltree));
	
	//test node present using root value
	if(tree_node_present(avltree, &value)) {
		printf("Value %f present in tree\n", value);
	}
	else printf("Value %f not present in tree\n", value);
	
	//insert values
	double insertvalue11 = rand() % upbound;
	printf("Inserting value %f into tree\n", insertvalue11);
	tree_insert_node(avltree, &insertvalue11);
	
	double insertvalue12 = rand() % upbound;
	printf("Inserting value %f into tree\n", insertvalue12);
	tree_insert_node(avltree, &insertvalue12);
	
	double insertvalue13 = rand() % upbound;
	printf("Inserting value %f into tree\n", insertvalue13);
	tree_insert_node(avltree, &insertvalue13);
	
	double insertvalue14 = rand() % upbound;
	printf("Inserting value %f into tree\n", insertvalue14);
	tree_insert_node(avltree, &insertvalue14);
	
	double insertvalue15 = rand() % upbound;
	printf("Inserting value %f into tree\n", insertvalue15);
	tree_insert_node(avltree, &insertvalue15);
	
	//print new tree with various orders
	printf("Tree contents inorder:\n");
	tree_print(avltree, inorder);
	
	printf("Tree contents preorder:\n");
	tree_print(avltree, preorder);
	
	printf("Tree contents postorder:\n");
	tree_print(avltree, postorder);
	
	//test new depth
	printf("Tree depth is %d\n", tree_depth(avltree));
	
	//test new num elements
	printf("%d elements in tree\n", tree_get_num_elements(avltree));
	
	//test node present using last inserted value
	if(tree_node_present(avltree, &insertvalue15)) {
		printf("Value %f present in tree\n", insertvalue15);
	} 
	else {
		printf("Value %f not present in tree\n", insertvalue15);
	}
	
	if(tree_node_present(avltree, &testval)) {
		printf("Value %f present in tree\n", testval);
	}
	else {
		printf("Value %f not present in tree\n", testval);
	}
	
	//test removing value
	removevalue = 40;
	printf("Removing value %f from tree\n", removevalue);
	tree_remove_node(avltree, &removevalue);
	
	//re-print tree
	printf("Tree contents inorder:\n");
	tree_print(avltree, inorder);
	
	printf("Tree contents preorder:\n");
	tree_print(avltree, preorder);
	
	printf("Tree contents postorder:\n");
	tree_print(avltree, postorder);
	
	//test new depth
	printf("Tree depth is %d\n", tree_depth(avltree));
	
	//test new num elements
	printf("%d elements in tree\n", tree_get_num_elements(avltree));
	
	//destroy binary trees
	destroy_tree(avltree);
	destroy_tree(emptyavltree);
	
	return(0);
}