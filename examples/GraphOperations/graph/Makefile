# FILE     Makefile
# PACKAGE  ExpressionTree
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "ExpressionTree" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../../..; pwd)


#I
include ../../../etc/CoreObjects/MakeDef


#V
ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
	-lVectorOperations\
	-lPredicateObjects\
	-lParameterizedFunction\
	-lNumericOperations\
        -lGeneralGraph\
	-lGraphOperations\
	-lExpressionTree\
	-lNumericProperties\
	-lMenuObjects\
	-lUtilities\
        -lGoalObjects\
	-lAlgorithmObjects\
	-lInstanceAlgorithms\
	-lInstanceObjects\
	-lDataObjects\
	-lSelectObjects\
	-lDirectedTreeObjects\
	-lOperationObjects\
	-lFunctionReal1DObjects\
	-lLogicalObjects\
	-lLogicalOperations\
	-lNumericObjects\
	-lCoreDataObjects\
	-lNonStandard\
        -lPCAAnalysis\
        -lEigenValues\
        -lEigenValuesOut\
        -lGraph\
	-lPairs\
        -lSystem\
	-lMatrixUtilities\
	-lMatrixNumeric\
	-lMatrixOut\
        -lBasicLaTeXTable\
	-lVector\
        -lONames\
        -lMixedClasses\
        -lString\
        -lObjects\
        -lCommBuffer\
        -lm  -lgdbm

#F Targets.

all: $(ALL)

otest: $(OBJECTS)
	CompileC++ -o otest $(OBJECTS) $(LIBS)


cleaner::
	$(RM) $(ALL)
