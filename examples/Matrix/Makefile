# FILE     Makefile
# PACKAGE  Matrix
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "Matrix" package.
#
# COPYRIGHT (C)  1997 Basis Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/Basis/MakeDef

LDLIBS+=\
  -lMatrix


#V

ALL= otest

OBJECTS = main.o

LIBS = 	\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
        -lMatrix\
        -lMixedClasses\
        -lString\
        -lObjects\
        -lCommBuffer\
        -lSystem\
        -lMixedClasses\
        -lm



#F Targets.

all: $(ALL)

otest: $(OBJECTS)
	CompileC++ -o otest $(OBJECTS) $(LIBS)


cleaner::
	$(RM) $(ALL)
