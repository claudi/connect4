SOURCES = $(wildcard $(SRCDIR)*.c)
DEPENDS	= $(wildcard $(SRCDIR)*.h)
OBJECTS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SOURCES:.c=.o))

SRCDIR = src/
OBJDIR = obj/

CFLAGS = -Wall -pedantic -Werror -O3

play: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)%.o: $(SRCDIR)%.c $(DEPENDS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) play play.debug

.PHONY: debug
debug: play.debug

play.debug: CFLAGS += -D DEBUG -g
play.debug: $(SOURCES) $(DEPENDS)
	$(CC) $(CFLAGS) -o $@ $(SOURCES)
