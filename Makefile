CC = gcc
CFLAGS = -Wall -g
DEPS = c/dict.h c/fs.h c/format.h
OBJ = c/wuliao.o c/dict.o c/fs.o c/format.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

wuliao: $(OBJ)
	gcc $(CFLAGS) -o $@ $^
