all:
	g++ -Wall -O3 engine.cpp -o engine

run: all
	./engine
	ristretto image.ppm