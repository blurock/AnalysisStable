# FILE     Makefile
# PACKAGE  String
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "String" package.
#
# COPYRIGHT (C)  REACTION Project, 1996 Edward S. Blurock

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/Basis/MakeDef


#V

#F Targets.

ALL= otest

all: $(ALL)

LIBS = 	\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
        -lString\
        -lCommBuffer\
        -lm

OBJECTS = main.o

otest: $(OBJECTS)
	CompileC++ -o otest $(OBJECTS) $(LIBS)

cleaner::
	$(RM) $(ALL)


