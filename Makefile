all:
	g++ \
	    -Wextra \
	    -Wall \
	    -std=c++0x \
	    -O3 \
	    -g \
	    -lglut -lGLU -lGL \
	    -fopenmp \
	    -D GUI \
	    -D MULTITHREADING \
	    engine.cpp \
					structures/vector.cpp \
					structures/point.cpp \
					structures/ray.cpp \
					structures/camera.cpp \
					structures/color.cpp \
					structures/image.cpp \
					structures/boundingbox.cpp \
					\
					samplers/sampler.cpp \
			-o engine

run: all
	./engine

jrun:
	./engine
