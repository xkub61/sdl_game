#-*- Makefile -*-

#OBJS specifies which files to compile as part of the project
OBJS = src/*.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = hello_SDL

#This is the target that compiles our executable
debug : $(OBJS)
	g++ -c $(OBJS) -std=c++14 -g -I C:\SDL2-w64\include -I source && g++ *.o -L C:\SDL2-w64\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o $(OBJ_NAME)

#(-lSDL2_ttf) foi retirada aps o "-lSDL2_image"
#-w -Wl,-subsystem,windows
build : $(OBJS)
	g++ -c $(OBJS) -std=c++14 -I C:\SDL2-w64\include -I source && g++ *.o -w -Wl,-subsystem,windows -L C:\SDL2-w64\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o Platformer
