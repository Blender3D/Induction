all:
	g++ -Wall -O3 -lglut -lGLU -lGL -fopenmp engine.cpp -o engine

run: all
	./engine
	eog image.ppm
