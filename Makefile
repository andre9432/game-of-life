CC=g++

all: hello

hello: main.cpp glad.c
	$(CC) main.cpp glad.c shaders.cpp -L./lib -lglfw3 -I./include -o gol.exe
clear:
	rm gol.exe