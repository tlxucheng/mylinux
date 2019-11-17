#
# Makefile for my_sipp
#

CC = gcc
INCLUDE = -I./
LIBRARY = -L 

SRCS := $(wildcard *.c)
#SRCS_CPP := $(wildcar *.cpp)
#OBJECTS := $(patsubst %.c, patsubst %.cpp, %.o, $(SRCS_C), $(SRCS_CPP))
OBJECTS := $(patsubst %.c, %.o, $(SRCS))

TARGET = my_sipp

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)
	
.c.cpp.o:
	$(cc) -c $(INCLUDE) $< -o $@
	
clean :
	rm -rf $(TARGET) $(OBJECTS)