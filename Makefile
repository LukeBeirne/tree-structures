CC = gcc
CFLAGS = -g -Wall
LFLAGS = -lm
PROGS = make_tree
all: $(PROGS)

make_tree: make_tree.o tree.o heap.o
	$(CC) $(LFLAGS) -o make_tree make_tree.o tree.o heap.o

make_tree.o: make_tree.c
	$(CC) $(CFLAGS) -c make_tree.c

tree.o: tree.c
	$(CC) $(CFLAGS) -c tree.c
	
heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c
	
clean:
	rm -f $(PROGS) *.o