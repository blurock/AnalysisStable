# FILE     Makefile
# PACKAGE  CommBuffer
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "CommBuffer" package.
#
# COPYRIGHT (C)  1997 Basis Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/Basis/MakeDef

LDLIBS+=\
  -lCommBuffer


#V

#F Targets.

ALL = otest

all: $(ALL)

LIBS = 	\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
        -lCommBuffer\
        -lm

OBJECTS = main.o

otest: $(OBJECTS)
	CompileC++ -o otest $(OBJECTS) $(LIBS)


cleaner::
	$(RM) $(ALL)
