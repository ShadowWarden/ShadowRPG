obj=main.o parse.o evaluate.o variable.o logical.o relational.o general.o etc.o

flags=-lreadline

kardinal: $(obj)
	cc  -g -Wall -o kardinal -O3 $(obj) $(flags)

evaluate.o: evaluate.c
	cc  -g -Wall -c evaluate.c 

main.o: main.c
	cc  -g -Wall -c main.c

parse.o: parse.c
	cc  -g -Wall -c parse.c

variable.o: variable.c
	cc  -g -Wall -c variable.c

logical.o: logical.c
	cc  -g -Wall -c logical.c

relational.o: relational.c
	cc -g -Wall -c relational.c

general.o: general.c
	cc -g -Wall -c general.c

etc.o: etc.c
	cc -g  -Wall -c etc.c

.PHONY: debug
debug: $(obj)
	cc -Wall -g -o kardinal $(obj)

.PHONY: clean
clean:
	rm -f $(obj) kardinal .*.swp
