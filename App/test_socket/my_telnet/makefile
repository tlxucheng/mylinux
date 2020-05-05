#
# Makefile for telnet_server_echo
#

CC = gcc
INCLUDE = -I./
LIBRARY = -L./ -lpthread

SRCS_C := $(wildcard *.c)
OBJECTS_C := $(patsubst %.c, %.o, $(SRCS_C))

TARGET = telnet_server_echo

all : $(TARGET)

$(TARGET) : $(OBJECTS_C)
	$(CC) -g -O0 -o $(TARGET) $(OBJECTS_C) $(LIBRARY)
	
.c.o:
	$(CC) -g -O0 -c $(INCLUDE) $< -o $@
	
clean :
	rm -rf $(TARGET) $(OBJECTS_C)
