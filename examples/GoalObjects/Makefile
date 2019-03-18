# FILE     Makefile
# PACKAGE  GoalObjects
# AUTHOR   Edward s. Blurock
#
# CONTENT
#   Makefile for example programs of the "GoalObjects" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/CoreObjects/MakeDef

LDLIBS+=\
  -lGoalObjects


#V
ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
	-lGoalObjects\
	-lInstanceAlgorithms\
	-lAlgorithmObjects\
	-lInstanceObjects\
	-lDataObjects\
	-lSelectObjects\
	-lDirectedTreeObjects\
	-lOperationObjects\
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
