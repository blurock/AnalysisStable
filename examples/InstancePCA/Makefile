# FILE     Makefile
# PACKAGE  InstancePCA
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
  -lInstancePCA


#V
ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
	-lInstancePCA\
	-lPrimitiveStats\
	-lAlgorithmObjects\
	-lInstanceAlgorithms\
	-lInstanceObjects\
	-lDataObjects\
	-lSelectObjects\
	-lDirectedTreeObjects\
	-lOperationObjects\
	-lFunctionReal1DObjects\
	-lLogicalObjects\
	-lNumericObjects\
	-lCoreDataObjects\
	-lPCAAnalysis\
	-lEigenValues\
	-lEigenValuesOut\
	-lMatrixUtilities\
	-lBasicLaTeXTable\
	-lMatrixNumeric\
        -lGraph\
	-lPairs\
        -lSystem\
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
