CC = gcc
CFLAGS = -g -Wall
LFLAGS = -lm
PROGS = make_tree
OBJS = make_tree.o tree.o binary.o heap.o
all: $(PROGS)

make_tree: make_tree.o tree.o binary.o heap.o
	$(CC) -o make_tree $(OBJS) $(LFLAGS)

make_tree.o: make_tree.c
	$(CC) $(CFLAGS) -c make_tree.c

tree.o: tree.c
	$(CC) $(CFLAGS) -c tree.c

binary.o: binary.c
	$(CC) $(CFLAGS) -c binary.c

heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c

clean:
	rm -f $(PROGS) *.o