# FILE     Makefile
# PACKAGE  InstanceAlgorithms
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "InstanceAlgorithms" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/CoreObjects/MakeDef

LDLIBS+=\
  -lInstanceAlgorithms


#V
ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
	-lDistributionAlgorithm\
	-lExpressionTree\
	-lNumericProperties\
	-lPrimitiveStats\
	-lInstanceAlgorithms\
	-lAlgorithmObjects\
	-lInstanceObjects\
	-lMenuObjects\
	-lDataObjects\
	-lSelectObjects\
	-lFunctionReal1DObjects\
	-lParameterizedFunction\
	-lDirectedTreeObjects\
	-lNumericOperations\
	-lLogicalOperations\
	-lOperationObjects\
	-lLogicalObjects\
	-lNumericObjects\
	-lCoreDataObjects\
	-lNonStandard\
        -lMatrixUtilities\
        -lMatrixNumeric\
	-lMatrixOut\
	-lBasicLaTeXTable\
	-lVector\
        -lSystem\
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
