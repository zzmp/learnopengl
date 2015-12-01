CC=g++
CCFLAGS=-std=c++11 -Wall -ggdb
GLFLAGS=-lGLEW -lglfw3 -framework OpenGL

default: build/hello-window

clean:
	rm -rf build/*

build/hello-window: hello-window.cc build
	$(CC) $(CCFLAGS) $(GLFLAGS) -o $@ $<
