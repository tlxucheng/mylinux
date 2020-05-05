#
# Makefile for telnet_server_echo
#

CC = gcc
LD = ld
INCLUDE = -I./
LIBRARY = -L./

SRCS_C := $(wildcard *.c)
OBJECTS_C := $(patsubst %.c, %.o, $(SRCS_C))

TARGET = libcaculate.so

all : $(TARGET)

$(TARGET) : $(OBJECTS_C)
	$(LD) -fPIC -shared -o $(TARGET) $(OBJECTS_C) $(LIBRARY)
	
.c.o:
	$(CC) -g -O0 -c $(INCLUDE) $< -o $@
	
clean :
	rm -rf $(TARGET) $(OBJECTS_C)
