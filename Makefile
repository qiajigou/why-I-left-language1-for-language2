PREFIX ?= /usr/local
CC     ?= cc

ifeq ($(shell uname), Cygwin)
BINS    = wuliao.exe
CP      = cp -f
RM      = rm -f
MKDIR   = mkdir -p
else ifeq ($(OS),Windows_NT)
BINS    = wuliao.exe
CP      = copy /Y
RM      = del /Q /S
MKDIR   = mkdir
else
BINS    = wuliao
CP      = cp -f
RM      = rm -f
MKDIR   = mkdir -p
endif

CFLAGS = -std=c99 -Ideps -Wall -g
SRC  = $(wildcard c/*.c)
DEPS = $(wildcard deps/*/*.c)
OBJ = $(DEPS:.c=.o)

all: $(BINS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

install: $(BINS)
	$(MKDIR) $(PREFIX)/bin
	$(foreach c, $(BINS), $(CP) $(c) $(PREFIX)/bin/$(c);)

uninstall:
	$(foreach c, $(BINS), $(RM) $(PREFIX)/bin/$(c);)

test:
	@./test.sh

$(BINS): $(SRC) $(OBJS)
	gcc $(CFLAGS) -o $@ $^
