# FILE     Makefile
# PACKAGE  CobwebCluster
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "CobwebCluster" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/CoreObjects/MakeDef

ALL = otest
OBJECTS = main.o

LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
	-lCobwebCluster\
	-lClusterTree\
        -lDescriptionProbs\
	-lEvaluationTree\
        -lPredicateGen\
	-lEntropyObjects\
	-lAlgorithmObjects\
	-lInstanceAlgorithms\
	-lPredicateObjects\
        -lMenuObjects\
	-lInstanceObjects\
	-lLogicalOperations\
	-lNumericOperations\
	-lParameterizedFunction\
	-lGoalObjects\
	-lFunctionReal1DObjects\
	-lOperationObjects\
	-lDataObjects\
	-lSelectObjects\
	-lDirectedTreeObjects\
	-lLogicalObjects\
	-lNumericObjects\
	-lCoreDataObjects\
	-lGraph\
	-lPairs\
        -lSystem\
        -lONames\
        -lMixedClasses\
        -lMatrixNumeric\
        -lVector\
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
