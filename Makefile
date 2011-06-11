all:
	g++ -Wall -O3 -fopenmp engine.cpp -o engine

run: all
	./engine
	eog image.ppm
