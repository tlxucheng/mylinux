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
	$(CPP) -g -o $(TARGET) $(OBJECTS_CPP) $(OBJECTS_C)
	
.c.o:
	$(CC) -g -c $(INCLUDE) $< -o $@
	
.cpp.o:
	$(CPP) -g -c $(INCLUDE) $< -o $@
	
clean :
	rm -rf $(TARGET) $(OBJECTS_C)
	rm -rf $(TARGET) $(OBJECTS_CPP)