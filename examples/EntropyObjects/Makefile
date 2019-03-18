# FILE     Makefile
# PACKAGE  EntropyObjects
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "EntropyObjects" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/CoreObjects/MakeDef

LDLIBS+=\
  -lEntropyObjects


#V
ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
        -lDecisionTreeAlgorithms\
	-lEntropyObjects\
	-lAlgorithmObjects\
	-lPredicateObjects\
	-lInstanceObjects\
	-lFunctionReal1DObjects\
	-lOperationObjects\
	-lDataObjects\
	-lSelectObjects\
	-lDirectedTreeObjects\
	-lLogicalObjects\
	-lNumericObjects\
	-lCoreDataObjects\
        -lSystem\
        -lONames\
        -lMixedClasses\
        -lMatrix\
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
