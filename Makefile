CC=g++
LIBS=-lGL -lGLEW -lglfw -lm

physics: ./src/physics/collision.c
	$(CC) -c ./src/physics/collision.c -o ./bin/physics.o

entity: ./src/entity/entity.c
	$(CC) -c ./src/entity/entity.c -o ./bin/entity.o

utils: ./src/utils/u_read.c ./src/utils/u_strcpy.c
	$(CC) -c ./src/utils/u_read.c -o ./bin/u_read.o
	$(CC) -c ./src/utils/u_strcpy.c -o ./bin/u_strcpy.o

camera: ./src/camera/camera.c
	$(CC) -c ./src/camera/camera.c -o ./bin/camera.o

shaders: ./src/opengl/shaders.c
	$(CC) -c ./src/opengl/shaders.c -o ./bin/shaders.o

scene: ./src/opengl/scene.c
	$(CC) -c ./src/opengl/scene.c -o ./bin/scene.o

main: ./src/main.c
	$(CC) -c ./src/main.c -o ./bin/main.o

all: main scene shaders utils camera entity physics
	clear && \
	$(CC) \
		./bin/main.o \
		./bin/scene.o \
		./bin/shaders.o \
		./bin/u_read.o \
		./bin/u_strcpy.o \
		./bin/camera.o \
		./bin/entity.o \
		./bin/physics.o \
		$(LIBS) -o SEngine

run: all
	./SEngine

clear:
	rm -rf ./bin/*.o



