play: main.c defs.h masks.c masks.h board.c board.h tree.c tree.h minimax.c minimax.h heuristic.c heuristic.h
	gcc -o play main.c masks.c board.c tree.c heuristic.c minimax.c -Wall

.PHONY: debug
debug: play.debug

play.debug: main.c defs.h board.c board.h tree.c tree.h
	gcc -o play.debug main.c masks.c board.c tree.c heuristic.c minimax.c -Wall -D DEBUG

.PHONY: all
all: play debug
