CC=g++
LIBS=-lGL -lGLEW -lglfw -lm

utils: ./src/utils/u_read.c ./src/utils/u_pointers.c ./src/utils/u_array.c
	$(CC) -c ./src/utils/u_read.c -o ./bin/u_read.o
	$(CC) -c ./src/utils/u_pointers.c -o ./bin/u_pointers.o
	$(CC) -c ./src/utils/u_array.c -o ./bin/u_array.o

math: ./src/math/matrix.h ./src/math/vector.h
	$(CC) -c ./src/math/matrix.c -o ./bin/matrix.o
	$(CC) -c ./src/math/vector.c -o ./bin/vector.o

shaders: ./src/opengl/shaders.c
	$(CC) -c ./src/opengl/shaders.c -o ./bin/shaders.o

scene: ./src/opengl/scene.c
	$(CC) -c ./src/opengl/scene.c -o ./bin/scene.o

main: ./src/main.c
	$(CC) -c ./src/main.c -o ./bin/main.o

all: main scene shaders utils math
	clear && \
	$(CC) \
		./bin/main.o \
		./bin/scene.o \
		./bin/shaders.o \
		./bin/u_read.o \
		./bin/u_pointers.o \
		./bin/u_array.o \
		./bin/matrix.o \
		./bin/vector.o \
		$(LIBS) -o SEngine

run: all
	./SEngine

clear:
	rm -rf ./bin/*.o



