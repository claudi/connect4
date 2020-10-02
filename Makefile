play: main.c defs.h board.c board.h tree.c tree.h minimax.c minimax.h
	gcc -o play main.c board.c tree.c minimax.c -Wall
