# FILE     Makefile
# PACKAGE  MenuObjects
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "MenuObjects" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/CoreObjects/MakeDef

LDLIBS+=\
  -lMenuObjects


#V
ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
	-lMenuObjects\
	-lInstancePCA\
        -lGoalObjects\
	-lAlgorithmObjects\
	-lInstanceAlgorithms\
	-lInstanceObjects\
	-lDataObjects\
	-lSelectObjects\
	-lDirectedTreeObjects\
	-lOperationObjects\
	-lParameterizedFunction\
	-lFunctionReal1DObjects\
	-lLogicalObjects\
	-lLogicalOperations\
	-lNumericObjects\
	-lCoreDataObjects\
	-lNonStandard\
        -lPCAAnalysis\
        -lEigenValues\
        -lEigenValuesOut\
	-lNumericObjects\
	-lCoreDataObjects\
        -lSystem\
        -lCommBuffer\
        -lONames\
        -lMixedClasses\
	-lMatrixNumeric\
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

