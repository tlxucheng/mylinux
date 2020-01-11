#
# Makefile for my_sipp
#

CC = gcc
CPP = g++
INCLUDE = -I./
LIBRARY = -L 

SRCS_C := $(wildcard *.c)
SRCS_CPP := $(wildcard *.cpp)
OBJECTS_C := $(patsubst %.c, %.o, $(SRCS_C))
OBJECTS_CPP := $(patsubst %.cpp, %.o, $(SRCS_CPP))

TARGET = my_sipp

all : $(TARGET)

$(TARGET) : $(OBJECTS_CPP) $(OBJECTS_C)
	$(CPP) -g -O0 -o $(TARGET) $(OBJECTS_CPP) $(OBJECTS_C)
	
.c.o:
	$(CC) -g -O0 -c $(INCLUDE) $< -o $@
	
.cpp.o:
	$(CPP) -g -O0 -c $(INCLUDE) $< -o $@
	
clean :
	rm -rf $(TARGET) $(OBJECTS_C)
	rm -rf $(TARGET) $(OBJECTS_CPP)