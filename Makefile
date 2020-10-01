play: main.c defs.h board.c board.h tree.c tree.h
	gcc -o play main.c board.c tree.c -Wall
