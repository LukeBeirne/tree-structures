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
	int value = 18;
	
	tree_t *tree = create_tree(value);
	
	bool empty = tree_empty(tree);
	if(empty) {
		printf("The tree is empty\n");
	}
	else {
		printf("The tree is not empty\n");
	}
	
	int depth = tree_depth(tree);
	printf("Tree depth is %d\n", depth);
	
	int insertvalue = 17;
	printf("Inserting value %d into tree...\n", insertvalue);
	insert_node(tree, insertvalue);
	
	depth = tree_depth(tree);
	printf("Tree depth is %d\n", depth);
	
	
	destroy_tree(tree);
	
	return(0);
}