CC=g++ -g
FREETYPE = ./freetype2
CPPFLAGS = -I${FREETYPE}/include
CFLAGS = -Wall $(DEBUG)
CXXFLAGS = $(CFLAGS)
LDIR = ../lib
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
LDFLAGS=-lrt -lm -pthread -L ./ -lGLEW -lglfw3 -ldl -lglut -lGLU -lGl -lfreetype -lpng -lz
foo: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.C

