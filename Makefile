CC=g++
LIBS=-lGL -lGLEW -lglfw -lm

utils: ./src/utils/u_read.c ./src/utils/u_strcpy.c
	$(CC) -c ./src/utils/u_read.c -o ./bin/u_read.o
	$(CC) -c ./src/utils/u_strcpy.c -o ./bin/u_strcpy.o

shaders: ./src/opengl/shaders.c
	$(CC) -c ./src/opengl/shaders.c -o ./bin/shaders.o

window: ./src/opengl/window.c
	$(CC) -c ./src/opengl/window.c -o ./bin/window.o

main: ./src/main.c
	$(CC) -c ./src/main.c -o ./bin/main.o

all: main window shaders utils
	$(CC) \
		./bin/main.o \
		./bin/window.o \
		./bin/shaders.o \
		./bin/u_read.o \
		./bin/u_strcpy.o \
		$(LIBS) -o SEngine

run: all
	./SEngine

clear:
	rm -rf ./bin/*.o



