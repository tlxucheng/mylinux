#
# Makefile for main
#

CC = gcc
INCLUDE = -I./
LIBRARY = -L./ -ldl

SRCS_C := $(wildcard *.c)
OBJECTS_C := $(patsubst %.c, %.o, $(SRCS_C))

TARGET = main

all : $(TARGET)

$(TARGET) : $(OBJECTS_C)
	$(CC) -g -O0  -rdynamic -o $(TARGET) $(OBJECTS_C) $(LIBRARY)
	
.c.o:
	$(CC) -g -O0 -c $(INCLUDE) $< -o $@
	
clean :
	rm -rf $(TARGET) $(OBJECTS_C)
