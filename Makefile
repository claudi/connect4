SRCDIR = src/
OBJDIR = obj/
EXECUTS = play play.debug play.profile

SOURCES = $(wildcard $(SRCDIR)*.c)
DEPENDS	= $(wildcard $(SRCDIR)*.h)
OBJECTS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SOURCES:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Wshadow -Wconversion -std=c11 -pedantic -Werror -Ofast -lm
CDEBUGFLAGS = -D DEBUG -ggdb -g
CPROFILEFLAGS = -pg

play: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)%.o: $(SRCDIR)%.c $(DEPENDS)
	$(CC) $(CFLAGS) -c $< -o $@

release.tar.gz: $(SOURCES) $(DEPENDS) Makefile
	tar -czvf $@ $^

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXECUTS) release.tar.gz *.out

.PHONY: all
all: $(EXECUTS)

.PHONY: debug
debug: play.debug

play.debug: $(SOURCES) $(DEPENDS)
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -o $@ $(SOURCES)

.PHONY: profile
profile: play.profile

play.profile: $(SOURCS) $(DEPENDS)
	$(CC) $(CFLAGS) $(CPROFILEFLAGS) -o $@ $(SOURCES)

.PHONY: lint
lint: lint.out
lint.out:
	splint src/*.c > lint.out

