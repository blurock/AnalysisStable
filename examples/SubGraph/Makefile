# FILE     Makefile
# PACKAGE  SubGraph
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "SubGraph" package.
#
# COPYRIGHT (C)  REACTION Project, 1996 Edward S. Blurock

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/Basis/MakeDef


#V
ALL=otest 

OBJECTS = main.o 

LIBS = 	\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
        -lFindCorrespondences\
        -lSubGraph\
        -lStartPairs\
         -lGraph\
        -lPairs\
        -lSystem\
        -lMixedClasses\
        -lString\
        -lObjects\
        -lCommBuffer\
        -lm

#F Targets.

all: $(ALL)

otest: $(OBJECTS)
	CompileC++ -o otest $(OBJECTS) $(LIBS)

cleaner::
	$(RM) $(ALL)




