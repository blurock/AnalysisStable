# FILE     Makefile
# PACKAGE  GeneralGraph
# AUTHOR   Mario Drobics
#
# CONTENT
#   Makefile for example programs of the "GeneralGraph" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/CoreObjects/MakeDef

ALL=otest 

OBJECTS = main.o 

LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
        -lGeneralGraph\
	-lInstanceObjects\
	-lDataObjects\
	-lOperationObjects\
	-lFunctionReal1DObjects\
	-lParameterizedFunction\
	-lDirectedTreeObjects\
	-lLogicalOperations\
	-lNumericOperations\
	-lLogicalObjects\
	-lNumericObjects\
	-lCoreDataObjects\
        -lSystem\
	-lPairs\
        -lONames\
        -lMixedClasses\
        -lMatrixNumeric\
	-lVector\
        -lString\
        -lObjects\
        -lCommBuffer\
        -lm

all: $(ALL)

otest: $(OBJECTS)
	CompileC++ -o otest $(OBJECTS) $(LIBS)

cleaner::
	$(RM) $(ALL)
