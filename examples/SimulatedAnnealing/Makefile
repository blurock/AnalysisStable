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
include ../../etc/Basis/MakeDef

LDLIBS+=\
  -lAlgorithmObjects


#V
ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
	-lSimulatedAnnealing\
	-lAlgorithmObjects\
	-lClusterTree\
	-lMenuObjects\
	-lInstanceAlgorithms\
	-lInstanceObjects\
	-lDataObjects\
	-lSelectObjects\
	-lDirectedTreeObjects\
	-lOperationObjects\
	-lFunctionReal1DObjects\
	-lLogicalOperations\
	-lNumericOperations\
	-lParameterizedFunction\
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

