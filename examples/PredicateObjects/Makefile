# FILE     Makefile
# PACKAGE  PredicateObjects
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "PredicateObjects" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/CoreObjects/MakeDef

LDLIBS+=\
  -lPredicateObjects


#V
ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
	-lPredicateObjects\
	-lParameterizedFunction\
	-lInstanceObjects\
	-lFunctionReal1DObjects\
	-lParameterizedFunction\
	-lOperationObjects\
	-lDataObjects\
	-lLogicalOperations\
	-lNumericOperations\
	-lLogicalObjects\
	-lNumericObjects\
	-lCoreDataObjects\
        -lGraph\
	-lPairs\
        -lSystem\
	-lMatrixNumeric\
	-lVector\
        -lONames\
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
