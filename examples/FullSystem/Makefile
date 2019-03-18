# FILE     Makefile
# PACKAGE  FullSystem
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "FullSystem" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


include ../../etc/CoreObjects/MakeDef

#V
ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
	-L/usr/local/lib\
	-lFullSystem\
	-lDbase\
	-lConsecutive\
	-lVectorOperations\
	-lGeneticOperations\
	-lPopulationBasedOptimization\
	-lOptimize\
	-lCobwebCluster\
        -lEquivalentClasses\
	-lDecisionTreeAlgorithms\
	-lEntropyObjects\
        -lDescriptionProbs\
	-lPredicateGen\
	-lPredicateObjects\
	-lDistributionAlgorithm\
	-lPrimitiveStats\
	-lEvaluationTree\
	-lNumericOperations\
	-lParameterizedFunction\
        -lGeneralGraph\
	-lGraphOperations\
	-lClusterTree\
	-lExpressionTree\
	-lNumericProperties\
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
        -lm


#F Targets.

all: $(ALL)

otest: $(OBJECTS)
	CompileC++ -o otest $(OBJECTS) $(LIBS)

cleaner::
	$(RM) $(ALL)
