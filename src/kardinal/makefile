obj=main.o parse.o evaluate.o state.o variable.o

kardinal: main.o parse.o evaluate.o state.o variable.o
	cc -Wall -o kardinal -O3 $(obj)

state.o: state.c
	cc -c state.c

evaluate.o: evaluate.c
	cc -c evaluate.c 

main.o: main.c
	cc -c main.c

parse.o: parse.c
	cc -c parse.c

variable.o : variable.c
	cc -c variable.c

.PHONY: debug
debug: main.o parse.o evaluate.o state.o variable.o
	cc -g -o kardinal $(obj)

.PHONY: clean
clean:
	rm -f $(obj) kardinal .*.swp
