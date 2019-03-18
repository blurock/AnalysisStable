# FILE     Makefile
# PACKAGE  DistributionAlgorithm
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "DistributionAlgorithm" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/CoreObjects/MakeDef

LDLIBS+=\
  -lDistributionAlgorithm


#V
ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
	-lDistributionAlgorithm\
	-lExpressionTree\
	-lPrimitiveStats\
	-lAlgorithmObjects\
	-lInstanceAlgorithms\
	-lMenuObjects\
	-lInstanceObjects\
	-lDataObjects\
	-lSelectObjects\
	-lDirectedTreeObjects\
	-lOperationObjects\
	-lFunctionReal1DObjects\
	-lLogicalOperations\
	-lLogicalObjects\
	-lNumericOperations\
	-lNumericObjects\
	-lParameterizedFunction\
	-lCoreDataObjects\
	-lNonStandard\
        -lGraph\
	-lPairs\
        -lSystem\
	-lMatrixNumeric\
	-lMatrixOut\
	-lMatrixUtilities\
	-lBasicLaTeXTable\
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
