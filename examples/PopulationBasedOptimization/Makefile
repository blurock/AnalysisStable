# FILE     Makefile
# PACKAGE  PopulationBasedOptimization
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "PopulationBasedOptimization" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/CoreObjects/MakeDef

ALL=otest
OBJECTS=main.o
LIBS+=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
        -lPopulationBasedOptimization\
	-lGeneticOperations\
        -lExpressionTree\
	-lDistributionAlgorithm\
	-lPrimitiveStats\
	-lInstanceAlgorithms\
        -lOptimize\
	-lAlgorithmObjects\
	-lInstanceObjects\
	-lParameterizedFunction\
	-lPredicateObjects\
	-lMenuObjects\
	-lDataObjects\
	-lSelectObjects\
	-lDirectedTreeObjects\
	-lOperationObjects\
	-lNumericOperations\
	-lLogicalOperations\
	-lFunctionReal1DObjects\
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


#V
all: $(ALL)

otest: $(OBJECTS)
	CompileC++ -o otest $(OBJECTS) $(LIBS)

#F Targets.

all: $(ALL)


cleaner::
	$(RM) $(ALL)
