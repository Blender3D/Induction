all:
	g++ -Wall -O3 engine.cpp -o engine

run: all
	./engine
	eog image.ppm
