#
# File:   Makefile for assignment 4 - Image processing
# Author: Sponono
# 
# Created on 04 May 2017, 09:22
#

# Define all variables here

CC = g++
CCFLAGS = -Wextra -pedantic -std=c++11
SOURCES = $(wildcard src/*.cpp)
SOURCES_TEST = $(wildcard tests/*.cpp)
OBJ = $(SOURCES:src/%.cpp=bin/%.o)
OBJ_TEST = $(filter-out bin/main.o, $(OBJ)) $(SOURCES_TEST:tests/%.cpp=bin/%.o)
LIBS = -lm
INC = -I headers
INC_TEST = -I lib/catch/inc


#---------------------------------------------------------------------------------
.PHONY: all
all: imageops
imageops: $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) -o imageops $(LIBS)

#---------------------------------------------------------------------------------
.PHONY: test
test:imageopstest
imageopstest: $(OBJ_TEST)
	$(CC) $(CCFLAGS) $(OBJ_TEST) -o imageopstest $(LIBS)
#---------------------------------------------------------------------------------
bin/%.o: src/%.cpp
	$(CC) $(CCFLAGS) -c $< $(INC) -o $@

bin/%.o: tests/%.cpp
	$(CC) $(CCFLAGS) -c $< $(INC_TEST) -o $@
#---------------------------------------------------------------------------------
.PHONY: clean
clean:
	rm -f bin/*.o 
	rm  ./imageops ./imageopstest
