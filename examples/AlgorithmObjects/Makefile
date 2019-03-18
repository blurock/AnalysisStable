# FILE     Makefile
# PACKAGE  AlgorithmObjects
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "AlgorithmObjects" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/CoreObjects/MakeDef

LDLIBS+=\
  -lAlgorithmObjects


#V
ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
	-lAlgorithmObjects\
	-lClusterTree\
	-lMenuObjects\
	-lInstanceAlgorithms\
	-lInstanceObjects\
	-lDataObjects\
	-lSelectObjects\
	-lDirectedTreeObjects\
	-lLogicalOperations\
	-lNumericOperations\
	-lOperationObjects\
	-lParameterizedFunction\
	-lFunctionReal1DObjects\
	-lLogicalObjects\
	-lNumericObjects\
	-lCoreDataObjects\
	-lNonStandard\
        -lGraph\
	-lPairs\
        -lSystem\
	-lMatrixOut\
	-lMatrixUtilities\
        -lBasicLaTeXTable\
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

