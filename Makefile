CC=g++

all: hello

hello: ./src/main.cpp ./src/glad.c ./src/shaders.cpp
	$(CC) ./src/main.cpp ./src/glad.c ./src/shaders.cpp -L./lib -lglfw3 -I./include -o gol.exe
clear:
	rm gol.exe