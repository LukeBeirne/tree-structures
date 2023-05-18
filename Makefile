CC = gcc
CFLAGS = -g -Wall
LFLAGS = -lm
PROGS = make_tree
all: $(PROGS)

make_tree: make_tree.o tree.o
	$(CC) $(LFLAGS) -o make_tree make_tree.o tree.o
	
tree.o: tree.c
	$(CC) $(CFLAGS) -c tree.c
	
make_tree.o: make_tree.c
	$(CC) $(CFLAGS) -c make_tree.c
	
clean:
	rm -f $(PROGS) *.o