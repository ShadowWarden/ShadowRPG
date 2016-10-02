obj=main.o parse.o

kardinal: main.o parse.o
	cc -o kardinal main.o parse.o

main.o: main.c
	cc -c main.c

parse.o: parse.c
	cc -c parse.c

.PHONY: clean
clean:
	rm -f $(obj) kardinal
