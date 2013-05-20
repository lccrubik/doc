.PHONY: clean all re run rubik

cflags=-c -Wall -O99 
mods=$(wildcard *.c)
objs=$(patsubst %.c,%.o,$(mods))
final=checker

all: $(final) rubik

rubik:
	make -C ../solver
	ln -f -s ../solver/rubik .

%.o: %.c $(wildcard *.h)
	gcc $(cflags) $<	-o $@

$(final): $(objs) 
	gcc $(objs) -o $(final)

clean:
	rm -f $(objs) $(final) rubik

re: clean all

run: $(final) rubik
	./$(final) 5000
