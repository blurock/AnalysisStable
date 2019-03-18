# FILE     Makefile
# PACKAGE  MixedClasses
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "MixedClasses" package.
#
# COPYRIGHT (C)  1997 Basis Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/Basis/MakeDef

#V
ALL= otest

OBJECTS = main.o

LIBS = 	\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
        -lMixedClasses\
        -lSystem\
        -lCommBuffer\
        -lObjects\
        -lMixedClasses\
        -lString\
        -lm

#F Targets.

all: $(ALL)

otest: $(OBJECTS)
	CompileC++ -o otest $(OBJECTS) $(LIBS)

cleaner::
	$(RM) $(ALL)






