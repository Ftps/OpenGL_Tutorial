TARGET = exe
CC = g++
LIBS = -lm -lGLEW -lGL -lSDL2
HEAD = ./Headers
SRCS = ./Sources
CFLAGS = -Wall -pedantic -O3 -I$(HEAD)
.PHONY: clean

DEPS = $(wildcard $(HEAD)/*.hpp)
OBJS = $(patsubst %.cpp, %.o, $(wildcard $(SRCS)/*.cpp))

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -r $(SRCS)/*.o
	rm -r $(TARGET)
