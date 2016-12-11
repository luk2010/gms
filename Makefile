# GMS Makefile
# This file depends on gcc. You must have gcc installed and available in your
# command line.

TARGET = bin/gms

# PREFIX : Change this to install the program wherever you want.
PREFIX = /usr/local 

# File to compile
OBJS = src/Bundle.o src/DllLoader.o src/Interpreter.o src/main.o src/Node.o \
    src/NodeContext.o src/NodeFunction.o src/NodeObject.o src/NodeProject.o \
    src/NodeVariable.o src/StdBundle.o src/Utils.o src/WordPeeker.o

# Files rebuildable.
REBUILDABLES = $(OBJS) $(TARGET) 

# The gms program rule.
all: $(TARGET) 
   
$(TARGET): $(OBJS)
	mkdir bin
	g++ -I./inc/ -std=c++11 -g -o $@ $^

%.o: %.cpp
	g++ -I./inc/ -std=c++11 -g -o $@ -c $<

# Clean rule.
clean:
	rm -f $(REBUILDABLES)
	rm -d bin

install: $(TARGET)
	install -m 0755 $(TARGET) $(PREFIX)/bin

.PHONY: install

