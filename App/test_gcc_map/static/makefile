#
# Makefile for test_gcc_map
#

CC = gcc
INCLUDE = -I./
LIBRARY = -L 

SRCS_C := $(wildcard *.c)
OBJECTS_C := $(patsubst %.c, %.o, $(SRCS_C))

TARGET = gcc_create_map_file

all : $(TARGET)

$(TARGET) : $(OBJECTS_C)
	$(CC) -Wl,-Map=test.map -g -O0 -o $(TARGET) $(OBJECTS_C)
	
.c.o:
	$(CC) -g -O0 -c $(INCLUDE) $< -o $@
	
clean :
	rm -rf $(TARGET) $(OBJECTS_C)
