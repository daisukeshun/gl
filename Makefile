CC=g++
LIBS=-lGL -lGLEW -lglfw -lm

types: ./src/types/m_types.c
	$(CC) -c ./src/types/m_types.c -o ./bin/m_types.o

utils: ./src/utils/u_read.c ./src/utils/u_pointers.c 
	$(CC) -c ./src/utils/u_read.c -o ./bin/u_read.o
	$(CC) -c ./src/utils/u_pointers.c -o ./bin/u_pointers.o

math: ./src/math/matrix.h ./src/math/vertex.h
	$(CC) -c ./src/math/matrix.c -o ./bin/matrix.o
	$(CC) -c ./src/math/vertex.c -o ./bin/vertex.o

shaders: ./src/opengl/shaders.c
	$(CC) -c ./src/opengl/shaders.c -o ./bin/shaders.o

scene: ./src/opengl/scene.c
	$(CC) -c ./src/opengl/scene.c -o ./bin/scene.o

main: ./src/main.c
	$(CC) -c ./src/main.c -o ./bin/main.o

all: main scene shaders utils math types
	clear && \
	$(CC) \
		./bin/main.o \
		./bin/scene.o \
		./bin/shaders.o \
		./bin/u_read.o \
		./bin/u_pointers.o \
		./bin/matrix.o \
		./bin/vertex.o \
		./bin/m_types.o \
		$(LIBS) -o SEngine

run: all
	./SEngine

clear:
	rm -rf ./bin/*.o



