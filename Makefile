CC = gcc
CFLAGS = -g -Wall
LFLAGS = -lm

PROGS = make_tree_int make_tree_double

OBJS_DIR = ./objs
OBJ1 = $(OBJS_DIR)/make_tree_int.o
OBJ2 = $(OBJS_DIR)/make_tree_double.o
OBJ3 = $(OBJS_DIR)/binary.o
OBJ4 = $(OBJS_DIR)/heap.o
OBJ5= $(OBJS_DIR)/avl.o
OBJS = $(OBJ3) $(OBJ4) $(OBJ5)


all: $(PROGS)

make_tree_int: $(OBJS) $(OBJS_DIR)/make_tree_int.o
	$(CC) -o make_tree_int $(OBJS) $(OBJS_DIR)/make_tree_int.o $(LFLAGS)

make_tree_double: $(OBJS) $(OBJS_DIR)/make_tree_double.o
	$(CC) -o make_tree_double $(OBJS) $(OBJS_DIR)/make_tree_double.o $(LFLAGS)

$(OBJ1): make_tree_int.c
	$(CC) $(CFLAGS) -c make_tree_int.c
	mv *.o $(OBJS_DIR)

$(OBJ2): make_tree_double.c
	$(CC) $(CFLAGS) -c make_tree_double.c
	mv *.o $(OBJS_DIR)

$(OBJ3): binary.c
	$(CC) $(CFLAGS) -c binary.c
	mv *.o $(OBJS_DIR)

$(OBJ4): heap.c
	$(CC) $(CFLAGS) -c heap.c
	mv *.o $(OBJS_DIR)

$(OBJ5): avl.c
	$(CC) $(CFLAGS) -c avl.c
	mv *.o $(OBJS_DIR)

clean:
	rm -f $(PROGS) $(OBJS_DIR)/*.o