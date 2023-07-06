CC = gcc
CFLAGS = -g -Wall
LFLAGS = -lm
PROGS = make_tree
OBJS = make_tree.o tree.o binary.o heap.o avl.o
all: $(PROGS)

make_tree: $(OBJS)
	$(CC) -o make_tree $(OBJS) $(LFLAGS)

make_tree.o: make_tree.c
	$(CC) $(CFLAGS) -c make_tree.c

tree.o: tree.c
	$(CC) $(CFLAGS) -c tree.c

binary.o: binary.c
	$(CC) $(CFLAGS) -c binary.c

heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c

avl.o: avl.c
	$(CC) $(CFLAGS) -c avl.c

clean:
	rm -f $(PROGS) *.o