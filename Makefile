CC=g++
CCFLAGS=-std=c++11 -Wall -ggdb
GLFLAGS=-lGLEW -lglfw3 -framework OpenGL

default: build/hello-window

clean:
	rm -rf build/*

build/gl.o: gl.cc
	$(CC) $(CCFLAGS) -c -o $@ $^

build/hello-window: hello-window.cc build/gl.o
	$(CC) $(CCFLAGS) $(GLFLAGS) -o $@ $^
