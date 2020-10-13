SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -pedantic -Werror -O3

play: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJECTS) play play.debug

.PHONY: debug
debug: play.debug

play.debug: CFLAGS += -D DEBUG -g
play.debug: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(SOURCES)
