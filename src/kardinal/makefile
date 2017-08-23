obj=main.o parse.o evaluate.o variable.o logical.o relational.o general.o arithmetic.o etc.o

cfiles=main.c parse.c evaluate.c variable.c logical.c relational.c general.c arithmetic.c etc.c

flags=

kardinal: $(obj)
	cc -Wall -o kardinal -O3 $(obj)

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

arithmetic.o: arithmetic.c
	cc -Wall -c arithmetic.c

etc.o: etc.c
	cc -Wall -c etc.c

.PHONY: debug
debug: $(obj)
	cc -Wall -g -o kardinal $(obj)

.PHONY: windows
windows: $(cfiles)
	i686-w64-mingw32-gcc -Wall $(cfiles) -o kardinal.exe



.PHONY: clean
clean:
	rm -f $(obj) kardinal .*.swp
