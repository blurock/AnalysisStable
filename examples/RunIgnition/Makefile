# FILE     Makefile
# PACKAGE  RunIgnition
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "RunIgnition" package.
#
# COPYRIGHT (C)  1997 Cantera Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/Cantera/MakeDef

ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
        -lRunIgnition\
        -lChemkinConvert\
        -lFlame\
	-lMechanism\
	-lMechanismGraph\
	-lMechLumping\
	-lRxn\
	-lUtilities\
	-lEquilibriumConst\
        -lThermoProps\
	-lThermoTables\
	-lRxn\
	-lSECharge\
	-lMolecule\
	-lFullSystem\
	-lMolBond\
	-lMolAtom\
	-lDbase\
	-lStaticAtom\
	-lMolStats\
        -lBasisSystem\
	-lConsecutive\
	-lVectorOperations\
	-lPopulationBasedOptimization\
	-lGeneticOperations\
	-lOptimize\
	-lCobwebCluster\
	-lClusterTree\
	-lInstancePCA\
	-lPCAAnalysis\
        -lEquivalentClasses\
	-lDecisionTreeAlgorithms\
	-lGraphOperations\
	-lNumericProperties\
	-lEntropyObjects\
        -lDescriptionProbs\
	-lPredicateGen\
	-lPredicateObjects\
	-lDistributionAlgorithm\
	-lEigenValuesOut\
	-lEigenValues\
	-lEigenValuesOut\
	-lPrimitiveStats\
	-lEvaluationTree\
	-lNumericOperations\
	-lParameterizedFunction\
        -lGeneralGraph\
        -lEquivalentClasses\
	-lDescriptionProbs\
	-lInstanceAlgorithms\
	-lGoalObjects\
	-lAlgorithmObjects\
	-lMenuObjects\
	-lDirectedTreeObjects\
	-lSelectObjects\
	-lInstanceObjects\
	-lFunctionReal1DObjects\
	-lDistributionAlgorithm\
	-lExpressionTree\
	-lPredicateGen\
	-lPredicateObjects\
	-lParameterizedFunction\
	-lOperationObjects\
	-lDataObjects\
	-lVectorOperations\
	-lLogicalOperations\
	-lNumericOperations\
	-lIterator\
	-lLogicalObjects\
	-lNumericObjects\
        -lDbase\
	-lCoreDataObjects\
	-lNonStandard\
	-lPrimitiveStats\
        -lGraph\
	-lPairs\
	-lMatrixUtilities\
        -lBasicLaTeXTable\
	-lMatrixNumeric\
	-lMatrixOut\
	-lMatrixUtilities\
        -lBasicLaTeXTable\
	-lMatrixNumeric\
	-lMatrixOut\
	-lVector\
        -lONames\
        -lMixedClasses\
        -lString\
        -lObjects\
        -lCommBuffer\
	-lPredicateObjects\
        -lm  -lgdbm\
        -L/usr/local/cantera/lib -L/usr/local/lib\
        -luser -loneD -lzeroD -ltransport -lkinetics -lthermo -lctnumerics -lctbase  -lctlapack -lctblas -lctmath -ltpx -lctf2c -lconverters -lctcxx -lsundials_cvodes -lsundials_nvecserial

#F Targets.

all: $(ALL)

otest: $(OBJECTS)
	CompileC++ -o otest $(OBJECTS) $(LIBS)

run:
	Test.sh
cleaner::
	$(RM) $(ALL)
