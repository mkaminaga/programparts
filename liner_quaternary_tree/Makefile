# makefile
# date 2018-04-15
# Copyright 2017 Mamoru Kaminaga
TARGET = main.out
SRC = main.cc liner_quaternary_tree.cc
OBJDIR = build
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRC:.cc=.o)))

GCC = g++
INCLUDE =
CFLAGS = -std=c++0x -g -Wall -O2 -DUNICODE -DDEBUG
LIBS = -lrt -lstdc++
LDFLAGS =

$(TARGET): $(OBJS)
	$(GCC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS)

$(OBJDIR)/%.o: %.cc
	mkdir -p $(OBJDIR)
	$(GCC) $(CFLAGS) $(INCLUDE) -o $@ -c $^
