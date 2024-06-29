CC = gcc
CFLAGS = -Wall -Wextra

.PHONY: all clean

all: ./program

TARGET = main

./program: $(TARGET).o AVL/arvoreAvl.o RedBlack/RedBlack.o BTree/BTree.o
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET).o: $(TARGET).c AVL/arvoreAvl.h RedBlack/RedBlack.h BTree/BTree.h
	$(CC) $(CFLAGS) -c $<

arvore_avl.o: AVL/arvoreAvl.c AVL/arvoreAvl.h
	$(CC) $(CFLAGS) -c $<

RedBlack.o: RedBlack/RedBlack.c RedBlack/RedBlack.h
	$(CC) $(CFLAGS) -c $<

BTree.o: BTree/BTree.c BTree/BTree.h
	$(CC) $(CFLAGS) -c $<