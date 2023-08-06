CC = gcc 
SRCS = src/main.c src/gl.c src/shaderManager.c src/fileManager.c src/windowManager.c
FLAGS = -Wall -Wextra
LIBS = -lglfw -lm
EXEC = a.out

install:
	$(CC) -o $(EXEC) $(SRCS) $(LIBS) $(FLAGS)
