play: main.c defs.h board.c board.h tree.c tree.h
	gcc -o play main.c board.c tree.c -Wall

.PHONY: debug
debug: play.debug

play.debug: main.c defs.h board.c board.h tree.c tree.h
	gcc -o play.debug main.c board.c tree.c -Wall -D DEBUG
