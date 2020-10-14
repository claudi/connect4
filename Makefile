SOURCES = $(wildcard *.c)
DEPENDS	= $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -pedantic -Werror -O3

play: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(DEPENDS)
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f $(OBJECTS) play play.debug

.PHONY: debug
debug: play.debug

play.debug: CFLAGS += -D DEBUG -g
play.debug: $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $(SOURCES)
