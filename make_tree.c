#include "tree.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	
	/* saving switch case jic input parameters are needed
	while((opt = getopt(argc, argv, "f:n:h")) != -1) {
		switch(opt) {
			case 'f':	
				//filename = strdup(optarg);
				if(strlen(optarg) > 10) {
					fprintf(stderr, "Error: filename is too long\n");
					return(-1);
				}
				strncpy(filename, optarg, 10);
				ffnd = 1;
				break;
			case 'n':
				length = atoi(optarg);
				break;
			case 'h':
				fprintf(stderr, "Usage: ./write_file [-f filename] [-n number]\nfilename: the file to write to\nnumber: the number of books\n");
				return(-1);
			default:
				fprintf(stderr, "Usage: ./write_file [-f filename] [-n number]\nfilename: the file to write to\nnumber: the number of books\n");
				return(-1);
		}
	}
	*/
	
	//random values assigned into tree nodes
	//srand call to ensure random values stay the same
	//srand(50) returns increasing values with 1 repeat
	srand(100);
	int upbound = 100;
	
	int value = rand() % upbound;
	
	
	//creating trees
	printf("Creating tree with %d as root\n", value);
	tree_t *tree = create_tree(value, binary, NULL);
	tree_t *emptytree = create_tree(0, binary, NULL);
	
	//print trees with only root value
	print_tree(tree, inorder);
	print_tree(emptytree, inorder);
	
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
		insert_node(tree, insertvalue);
	}
	
	//print new tree with various orders
	printf("Tree contents inorder:\n");
	print_tree(tree, 0);
	
	printf("Tree contents preorder:\n");
	print_tree(tree, 1);
	
	printf("Tree contents postorder:\n");
	print_tree(tree, 2);
	
	//test new depth
	printf("Tree depth is %d\n", tree_depth(tree));
	
	//test new num elements
	printf("%d elements in tree\n", tree_get_num_elements(tree));
	
	//test node present using last inserted value
	if(tree_node_present(tree, insertvalue)) {
		printf("Value %d present in tree\n", insertvalue);
	}
	else printf("Value %d not present in tree\n", insertvalue);
	
	//test removing value
	int removevalue = 40;
	printf("Removing value %d from tree\n", removevalue);
	remove_node(tree, removevalue);
	
	//re-print tree
	printf("Tree contents inorder:\n");
	print_tree(tree, 0);
	
	printf("Tree contents preorder:\n");
	print_tree(tree, 1);
	
	printf("Tree contents postorder:\n");
	print_tree(tree, 2);
	
	//test new depth
	printf("Tree depth is %d\n", tree_depth(tree));
	
	//test new num elements
	printf("%d elements in tree\n", tree_get_num_elements(tree));
	
	//destroy trees and end
	destroy_tree(tree);
	destroy_tree(emptytree);
	
	return(0);
}