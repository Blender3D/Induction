all:
	g++ -Wall -O3 -march=native -fopenmp engine.cpp -o engine

run: all
	./engine
	eog image.ppm
