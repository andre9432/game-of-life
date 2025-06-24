CC=g++

all: hello

hello: main.cpp shaders.cpp glad.c
	$(CC) main.cpp glad.c -L./lib -lglfw3dll -lshader -I./include -o run.exe
clear:
	rm run.exe