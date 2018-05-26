obj=object.o
exec=engine
cfiles=main.cpp object.cpp
maincfile=main.cpp
libpathflags=
libbefore=-lGLEW -lglfw -lGL
libafter=-lSOIL

$(exec): $(obj) $(maincfile)
	g++  $(libpathflags) $(libbefore) -o $(exec) $(maincfile) $(obj) $(libafter)

object.o: object.cpp
	g++ -c object.cpp

.PHONY: clean
clean:
	rm -f $(obj) $(exec) .*.swp
