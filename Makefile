SRCDIR = src/
OBJDIR = obj/
EXECUTS = play play.debug play.profile

SOURCES = $(wildcard $(SRCDIR)*.c)
DEPENDS	= $(wildcard $(SRCDIR)*.h)
OBJECTS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SOURCES:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic -Werror -Ofast -lm

play: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)%.o: $(SRCDIR)%.c $(DEPENDS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXECUTS)

.PHONY: all
all: $(EXECUTS)

.PHONY: debug
debug: play.debug

play.debug: CFLAGS += -D DEBUG -ggdb
play.debug: $(SOURCES) $(DEPENDS)
	$(CC) $(CFLAGS) -o $@ $(SOURCES)

.PHONY: profile
profile: play.profile

play.profile: CFLAGS += -pg
play.profile: $(SOURCS) $(DEPENDS)
	$(CC) $(CFLAGS) -o $@ $(SOURCES)
