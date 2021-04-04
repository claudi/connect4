SRCDIR = src/
OBJDIR = obj/
EXECUTS = play play.debug play.profile play.headless

SOURCES = $(wildcard $(SRCDIR)*.c)
DEPENDS	= $(wildcard $(SRCDIR)*.h)
OBJECTS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SOURCES:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Wshadow -std=c11 -pedantic -Werror -Ofast
LFLAGS = `sdl2-config --cflags` -lSDL2
CDEBUGFLAGS = -D DEBUG -ggdb -g3 -O0
CHEADLESSFLAGS = -D HEADLESS -D START_DEPTH=6
CPROFILEFLAGS = -pg

play: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.c $(DEPENDS)
	$(CC) $(CFLAGS) -c $< -o $@

release.tar.gz: $(SOURCES) $(DEPENDS) Makefile
	tar -czvf $@ $^

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(EXECUTS) release.tar.gz *.out

.PHONY: all
all: $(EXECUTS)

.PHONY: debug
debug: play.debug

play.debug: $(SOURCES) $(DEPENDS)
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -o $@ $(SOURCES) $(LFLAGS)

.PHONY: headless
headless: play.headless

play.headless: $(SOURCES) $(DEPENDS)
	$(CC) $(CFLAGS) $(CHEADLESSFLAGS) -o $@ $(SOURCES)

.PHONY: profile
profile: play.profile

play.profile: $(SOURCES) $(DEPENDS)
	$(CC) $(CFLAGS) $(CPROFILEFLAGS) -o $@ $(SOURCES) $(LFLAGS)

.PHONY: lint
lint: lint.out
lint.out: $(SOURCES) $(DEPENDS)
	splint -booltype Bool -boolfalse FALSE -booltrue TRUE $^ > $@

.PHONY: check
check: check.out
check.out: $(SOURCES) $(DEPENDS)
	cppcheck --std=c11 --enable=all --suppress=missingIncludeSystem $^ &> $@

