obj=main.o map.o character.o move.o inst.o

../main: main.o map.o character.o move.o inst.o
	cc -o ../../genesis main.o map.o character.o move.o inst.o -lncurses

main.o: main.c
	cc -c main.c

map.o: map.c
	cc -c map.c

character.o: character.c
	cc -c character.c

move.o: move.c
	cc -c move.c

inst.o: inst.c
	cc -c inst.c

.PHONY: clean
clean:
	rm -f $(obj) ../../genesis .*.swp
