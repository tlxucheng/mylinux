#
# Makefile for ccp project
#
CPP = g++ -std=c++11
INCLUDE = -I./
LIBRARY = -L 

SRCS_CPP := $(wildcard *.cpp)
OBJECTS_CPP := $(patsubst %.cpp, %.o, $(SRCS_CPP))

TARGET = ccm_template

all : $(TARGET)

$(TARGET) : $(OBJECTS_CPP)
	$(CPP) -g -O0 -o $(TARGET) $(OBJECTS_CPP)
	
.cpp.o:
	$(CPP) -g -O0 -c $(INCLUDE) $< -o $@
	
clean :
	rm -rf $(TARGET) $(OBJECTS_CPP)