#
# Makefile for jsonla
#

CC = g++
INCLUDE = -I./
LIBRARY = -L 

SRCS_CC := $(wildcard *.cc)
OBJECTS_CC := $(patsubst %.cc, %.o, $(SRCS_CC))

TARGET = jsonla_main

all : $(TARGET)

$(TARGET) : $(OBJECTS_CC)
	$(CC) -g -O0 -o $(TARGET) $(OBJECTS_CC)
	
.cc.o:
	$(CC) -g -O0 -c $(INCLUDE) $< -o $@
	
clean :
	rm -rf $(TARGET) $(OBJECTS_CC)
