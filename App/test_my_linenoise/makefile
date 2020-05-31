#
# Makefile for test_my_linenoise
#

CC = gcc
INCLUDE = -I./
LIBRARY = -L 

SRCS_C := $(wildcard *.c)
OBJECTS_C := $(patsubst %.c, %.o, $(SRCS_C))

TARGET = test_my_linenoise

all : $(TARGET)

$(TARGET) : $(OBJECTS_C)
	$(CC) -g -O0 -o $(TARGET) $(OBJECTS_C)
	
.c.o:
	$(CC) -g -O0 -c $(INCLUDE) $< -o $@
	
clean :
	rm -rf $(TARGET) $(OBJECTS_C)
