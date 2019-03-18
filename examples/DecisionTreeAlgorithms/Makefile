# FILE     Makefile
# PACKAGE  DecisionTreeAlgorithms
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "DecisionTreeAlgorithms" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/CoreObjects/MakeDef

LDLIBS+=\
  -lDecisionTreeAlgorithms


#V
ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
	-lDecisionTreeAlgorithms\
	-lEntropyObjects\
        -lPopulationBasedOptimization\
	-lGeneticOperations\
        -lOptimize\
	-lRuleSystem\
	-lInstanceAlgorithms\
	-lInstanceObjects\
	-lNumericOperations\
	-lGoalObjects\
	-lPredicateGen\
	-lPredicateObjects\
	-lLogicalOperations\
	-lFunctionReal1DObjects\
	-lParameterizedFunction\
	-lDistributionAlgorithm\
	-lPrimitiveStats\
	-lAlgorithmObjects\
        -lExpressionTree\
	-lEvaluationTree\
	-lClusterTree\
	-lMenuObjects\
	-lDataObjects\
	-lSelectObjects\
	-lDirectedTreeObjects\
	-lOperationObjects\
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
