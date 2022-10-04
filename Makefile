all: car

car: car.cpp ichavez.cpp  mfuentes.cpp jramos3.cpp sdenney.cpp jquinonez.cpp jquinonez.h
	g++ car.cpp ichavez.cpp mfuentes.cpp jramos3.cpp sdenney.cpp jquinonez.cpp -Wall -lX11 -lGL -lGLU -lm ./libggfonts.a -ocar

clean:
	rm -f car
	rm -f *.o

