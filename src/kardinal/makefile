obj=main.o parse.o evaluate.o state.o variable.o logical.o relational.o general.o

kardinal: $(obj)
	cc -Wall -o kardinal -O3 $(obj)

state.o: state.c
	cc -Wall -c state.c

evaluate.o: evaluate.c
	cc -Wall -c evaluate.c 

main.o: main.c
	cc -Wall -c main.c

parse.o: parse.c
	cc -Wall -c parse.c

variable.o: variable.c
	cc -Wall -c variable.c

logical.o: logical.c
	cc -Wall -c logical.c

relational.o: relational.c
	cc -Wall -c relational.c

general.o: general.c
	cc -Wall -c general.c


.PHONY: debug
debug: main.o parse.o evaluate.o state.o variable.o logical.o relational.o
	cc -Wall -g -o kardinal $(obj)

.PHONY: clean
clean:
	rm -f $(obj) kardinal .*.swp
