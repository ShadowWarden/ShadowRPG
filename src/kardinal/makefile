obj=main.o parse.o evaluate.o

kardinal: main.o parse.o evaluate.o
	cc -o kardinal $(obj)

evaluate.o: evaluate.c
	cc -c evaluate.c 

main.o: main.c
	cc -c main.c

parse.o: parse.c
	cc -c parse.c

.PHONY: clean
clean:
	rm -f $(obj) kardinal .*.swp
