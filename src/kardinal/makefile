obj=main.o parse.o evaluate.o state.o

kardinal: main.o parse.o evaluate.o state.o
	cc -o kardinal $(obj)

state.o: state.c
	cc -c state.c

evaluate.o: evaluate.c
	cc -c evaluate.c 

main.o: main.c
	cc -c main.c

parse.o: parse.c
	cc -c parse.c

.PHONY: clean
clean:
	rm -f $(obj) kardinal .*.swp
