all: car

car: car.cpp mfuentes.cpp jramos3.cpp 
	g++ car.cpp mfuentes.cpp jramos3.cpp -Wall -lX11 -lGL -lGLU -lm ./libggfonts.a -ocar

clean:
	rm -f car
	rm -f *.o

