#include "tree.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void print_empty(tree_t *tree) {
	bool empty = tree_empty(tree);
	if(empty) {
		printf("The tree is empty\n");
	}
	else {
		printf("The tree is not empty\n");
	}
}

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
	srand(50);
	
	
	int value = rand() % 100;
	
	tree_t *tree = create_tree(value);
	tree_t *emptytree = create_tree(NULL);
	
	print_empty(tree);
	print_empty(emptytree);
	
	int depth = tree_depth(tree);
	printf("Tree depth is %d\n", depth);
	
	int insertvalue = rand() % 100;
	printf("Inserting value %d into tree\n", insertvalue);
	insert_node(tree, insertvalue);
	
	depth = tree_depth(tree);
	printf("Tree depth is %d\n", depth);
	
	if(tree_node_present(tree, insertvalue)) {
		printf("%d in tree\n", insertvalue);
	}
	else printf("%d not in tree\n", insertvalue);
	
	printf("%d elements in tree\n", tree_get_num_elements(tree));
	
	
	destroy_tree(tree);
	destroy_tree(emptytree);
	
	return(0);
}