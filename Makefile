CC=g++
CCFLAGS=-std=c++11 -Wall -ggdb
GLFLAGS=-lGLEW -lglfw3 -framework OpenGL

default: build/shaders

clean:
	rm -rf build/*

build/gl.o: gl.cc gl.h
	$(CC) $(CCFLAGS) -c -o $@ $<

build/hello-window: hello-window.cc build/gl.o
	$(CC) $(CCFLAGS) $(GLFLAGS) -o $@ $^

build/hello-triangle: hello-triangle.cc build/gl.o
	$(CC) $(CCFLAGS) $(GLFLAGS) -o $@ $^

build/shaders: shaders.cc build/gl.o
	$(CC) $(CCFLAGS) $(GLFLAGS) -o $@ $^
