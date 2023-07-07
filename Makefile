CC = gcc
CFLAGS = -g -Wall
LFLAGS = -lm

PROGS = make_tree

OBJS_DIR = ./objs
OBJ1 = $(OBJS_DIR)/make_tree.o
OBJ2 = $(OBJS_DIR)/binary.o
OBJ3 = $(OBJS_DIR)/heap.o
OBJ4= $(OBJS_DIR)/avl.o
OBJS = $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)


all: $(PROGS)

make_tree: $(OBJS)
	$(CC) -o make_tree $(OBJS) $(LFLAGS)

$(OBJ1): make_tree.c
	$(CC) $(CFLAGS) -c make_tree.c
	mv *.o $(OBJS_DIR)

$(OBJ2): binary.c
	$(CC) $(CFLAGS) -c binary.c
	mv *.o $(OBJS_DIR)

$(OBJ3): heap.c
	$(CC) $(CFLAGS) -c heap.c
	mv *.o $(OBJS_DIR)

$(OBJ4): avl.c
	$(CC) $(CFLAGS) -c avl.c
	mv *.o $(OBJS_DIR)

clean:
	rm -f $(PROGS) $(OBJS_DIR)/*.o