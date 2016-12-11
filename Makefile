# GMS Makefile
# This file depends on gcc.

PREFIX   	:= /usr/local 		# PREFIX : Change this to install the program wherever you want.
CC    	   	:= g++			# CC : C++ Compiler.
CFLAGS    	:= -g -std=c++11 	# CFLAGS : C++ Compiler flags.
INCLUDES	:= -I./inc/		# INCLUDES : Directory where to look for files.
MKDIR		:= mkdir		# MKDIR : Make Directory command.
RM 		:= rm 			# RM : Remove Directory command.
TARGET		:= bin/gms		# TARGET : The 'gms' program.

# File to compile
OBJS = src/Bundle.o src/DllLoader.o src/Interpreter.o src/main.o src/Node.o \
    src/NodeContext.o src/NodeFunction.o src/NodeObject.o src/NodeProject.o \
    src/NodeVariable.o src/StdBundle.o src/Utils.o src/WordPeeker.o

# Files rebuildable.
REBUILDABLES = $(OBJS) $(TARGET) 

# The gms program rule.
all: $(TARGET) 
   
$(TARGET): $(OBJS)
	echo Making $(TARGET).
	$(MKDIR) bin
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

# Clean rule.
clean:
	$(RM) -f $(REBUILDABLES)
	$(RM) -d bin

install: $(TARGET)
	install -m 0755 $(TARGET) $(PREFIX)/bin

.PHONY: install

