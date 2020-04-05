#
# Makefile for sigsegv
#

CC = gcc
INCLUDE = -I./
LIBRARY = -L 
LDLIBS:=-ldl
LDFLAGS:=-rdynamic

SRCS_C := $(wildcard *.c)
OBJECTS_C := $(patsubst %.c, %.o, $(SRCS_C))

TARGET = sigsegv

all : $(TARGET)

$(TARGET) : $(OBJECTS_C)
	$(CC) -g -O0 -o $(TARGET) $(OBJECTS_C) $(LDLIBS) $(LDFLAGS)
	
.c.o:
	$(CC) -g -O0 -c $(INCLUDE) $< -o $@
	
clean :
	rm -rf $(TARGET) $(OBJECTS_C)
