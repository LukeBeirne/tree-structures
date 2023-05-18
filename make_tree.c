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
	node_t *root = create_node(value);
	
	tree_t *tree = create_tree(root);
	
	destroy_tree(tree);
	destroy_node(root);
	
	return(0);
}