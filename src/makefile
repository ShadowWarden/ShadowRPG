obj=object.o controls.o
exec=engine
cfiles=main.cpp object.cpp controls.cpp
maincfile=main.cpp
libpathflags=
libafter=-lGLEW -lglfw -lGL
libbefore=

$(exec): $(obj) $(maincfile)
	g++  $(libpathflags) $(libbefore) -o $(exec) $(maincfile) $(obj) $(libafter)

object.o: object.cpp
	g++ -c object.cpp

controls.o: controls.hpp
	g++ -c controls.cpp

.PHONY: clean
clean:
	rm -f $(obj) $(exec) .*.swp
