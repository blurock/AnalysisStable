# FILE     Makefile
# PACKAGE  VerifyEnvironment
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "VerifyEnvironment" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/CoreObjects/MakeDef

#V
ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
	-lVerifyEnvironment\
	-lExpressionTree\
	-lAlgorithmObjects\
	-lInstanceObjects\
	-lVectorOperations\
	-lPredicateObjects\
	-lMenuObjects\
	-lDataObjects\
	-lSelectObjects\
	-lDirectedTreeObjects\
	-lOperationObjects\
	-lNumericOperations\
	-lParameterizedFunction\
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




#F Targets.

all: $(ALL)

otest: $(OBJECTS)
	CompileC++ -o otest $(OBJECTS) $(LIBS)


cleaner::
	$(RM) $(ALL)
