CC = gcc
SRCS = src/main.c src/gl.c
FLAGS = -Wall -Wextra
LIBS = -lglfw
EXEC = a.out

install:
	$(CC) -o $(EXEC) $(SRCS) $(LIBS) $(FLAGS)