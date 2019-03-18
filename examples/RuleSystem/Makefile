# FILE     Makefile
# PACKAGE  RuleSystem
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "RuleSystem" package.
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
	-lRuleSystem\
	-lNumericOperations\
	-lParameterizedFunction\
	-lPredicateObjects\
	-lDistributionAlgorithm\
	-lPrimitiveStats\
	-lAlgorithmObjects\
        -lExpressionTree\
	-lClusterTree\
	-lMenuObjects\
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
	-lNonStandard\
	-lCoreDataObjects\
        -lGraph\
	-lPairs\
	-lMatrixUtilities\
	-lMatrixNumeric\
	-lMatrixOut\
        -lBasicLaTeXTable\
	-lVector\
        -lONames\
	-lBasisSystem\
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
