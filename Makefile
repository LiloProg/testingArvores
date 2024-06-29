CC = gcc
CFLAGS = -Wall -Wextra

.PHONY: all clean

all: ./program

TARGET = main

./program: $(TARGET).o AVL/arvoreAvl.o RedBlack/RedBlack.o BTree/BTree.o
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET).o: $(TARGET).c AVL/arvoreAvl.h RedBlack/RedBlack.h BTree/BTree.h
	$(CC) $(CFLAGS) -c $<

AVL/arvoreAvl.o: AVL/arvoreAvl.c AVL/arvoreAvl.h
	$(CC) $(CFLAGS) -c $< -o $@

RedBlack/RedBlack.o: RedBlack/RedBlack.c RedBlack/RedBlack.h
	$(CC) $(CFLAGS) -c $< -o $@

BTree/BTree.o: BTree/BTree.c BTree/BTree.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET).o AVL/arvoreAvl.o RedBlack/RedBlack.o BTree/BTree.o ./program
