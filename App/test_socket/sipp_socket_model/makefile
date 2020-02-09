#
# Makefile for sipp_socket_model
#

CC = gcc
INCLUDE = -I./
LIBRARY = -L 

SRCS_C := $(wildcard *.c)
OBJECTS_C := $(patsubst %.c, %.o, $(SRCS_C))

TARGET = sipp_socket_model

all : $(TARGET)

$(TARGET) : $(OBJECTS_C)
	$(CC) -g -O0 -o $(TARGET) $(OBJECTS_C)
	
.c.o:
	$(CC) -g -O0 -c $(INCLUDE) $< -o $@
	
clean :
	rm -rf $(TARGET) $(OBJECTS_C)
