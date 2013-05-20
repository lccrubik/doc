.PHONY: clean all re run

cflags=-c -Wall -Wextra -O99 -pedantic -std=c99
mods=$(wildcard *.c)
objs=$(patsubst %.c,%.o,$(mods))
final=rubik
CC=gcc

all: $(final)

%.o: %.c *.h
	$(CC) $(cflags) $<	-o $@

$(final): $(objs)
	$(CC) $(objs) -o $(final)

clean:
	rm -f $(objs) $(final)

re: clean all
