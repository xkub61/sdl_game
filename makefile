#-*- Makefile -*-

#OBJS specifies which files to compile as part of the project
OBJS = src/*.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = hello_SDL

#This is the target that compiles our executable
all : $(OBJS)
	g++ -c $(OBJS) -std=c++14 -g -I C:\SDL2-w64\include -I source && g++ *.o -L C:\SDL2-w64\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -o $(OBJ_NAME)