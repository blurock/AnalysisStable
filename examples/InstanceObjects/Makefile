# FILE     Makefile
# PACKAGE  InstanceObjects
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "InstanceObjects" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/CoreObjects/MakeDef

LDLIBS+=\
  -lInstanceObjects


#V
ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
	-lInstanceObjects\
	-lDataObjects\
	-lOperationObjects\
	-lLogicalOperations\
	-lNumericOperations\
	-lFunctionReal1DObjects\
	-lParameterizedFunction\
	-lLogicalObjects\
	-lNumericObjects\
	-lCoreDataObjects\
	-lNonStandard\
        -lSystem\
        -lCommBuffer\
        -lONames\
        -lMixedClasses\
	-lMatrixNumeric\
        -lGraph\
	-lPairs\
	-lVector\
        -lString\
        -lObjects\
        -lm

#F Targets.

all: $(ALL)

otest: $(OBJECTS)
	CompileC++ -o otest $(OBJECTS) $(LIBS)

cleaner::
	$(RM) $(ALL)

