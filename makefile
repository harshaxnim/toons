UNAME_S := $(shell uname -s)

FLAGS = -std=c++11

INCLUDES = -Iinclude

FRAMEWORK = -framework OpenGL

OBJS = src/Controller.cc \
	src/Main.cc \
	src/Model.cc \
	src/View.cc

LIBS  = lib/Allegro5/allegro.dylib \
	lib/Allegro5/main.dylib \
	lib/Allegro5/font.dylib \
	lib/Allegro5/ttf.dylib 

CC = g++

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = runThis

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBS) $(FRAMEWORK) $(INCLUDES) -o $(OBJ_NAME)