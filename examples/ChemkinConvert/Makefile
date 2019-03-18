# FILE     Makefile
# PACKAGE  Flame
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "Flame" package.
#
# COPYRIGHT (C)  1997 Reaction Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/Cantera/MakeDef


ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
        -lFullReaction\
        -lFullSystem\
        -lChemkinConvert\
        -lFlame\
	-lMechanismGraph\
	-lMechLumping\
	-lMechanism\
	-lRxn\
	-lUtilities\
	-lEquilibriumConst\
        -lThermoProps\
	-lThermoTables\
	-lRxn\
	-lSECharge\
	-lMolecule\
	-lMolBond\
	-lMolAtom\
	-lDbase\
	-lStaticAtom\
	-lMolStats\
	-lConsecutive\
	-lVectorOperations\
	-lGeneticOperations\
	-lPopulationBasedOptimization\
	-lOptimize\
	-lCobwebCluster\
	-lDecisionTreeAlgorithms\
	-lEntropyObjects\
        -lEquivalentClasses\
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
	-lUtilities\
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
        -lSystem\
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
        -lm  -lgdbm\
        -L/usr/local/cantera/build/lib/i686-pc-linux-gnu -L/usr/local/sundials/lib\
        -luser -loneD -lzeroD -ltransport -lcantera -lsundials_cvodes -lsundials_shared -lsundials_nvecserial -lctlapack -lctblas -lctmath -ltpx -lctf2c -lconverters -lctcxx

#F Targets.

all: $(ALL)

otest: $(OBJECTS)
	CompileC++ -g -o otest $(OBJECTS) $(LIBS)

run:
	TestReadChemkin.sh
cleaner::
	$(RM) $(ALL)
