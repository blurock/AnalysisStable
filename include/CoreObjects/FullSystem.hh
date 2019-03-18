/*  FILE     FullSystem.hh
**  PACKAGE  FullSystem
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "FullSystem" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_FULLSYSTEM_HH
#define CoreObjects_FULLSYSTEM_HH

#pragma interface
 
 
/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/

#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "NumericOperations.hh"
#include "LogicalOperations.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "InstanceAlgorithms.hh"
#include "PredicateObjects.hh"
#include "PredicateGen.hh"
#include "EntropyObjects.hh"
#include "EvaluationTree.hh"
#include "DecisionTreeAlgorithms.hh"
#include "GoalObjects.hh"
#include "PrimitiveStats.hh"
#include "ExpressionTree.hh"
#include "ParameterizedFunction.hh"
#include "DistributionAlgorithm.hh"
#include "MatrixUtilities.hh"
#include "BasicLaTeXTable.hh"
#include "EigenValuesOut.hh"
#include "EigenValues.hh"
#include "PCAAnalysis.hh"
#include "InstancePCA.hh"
#include "DescriptionProbs.hh"
#include "NumericProperties.hh"
#include "ClusterTree.hh"
#include "CobwebCluster.hh"
#include "RuleSystem.hh"
#include "Optimize.hh"
#include "PopulationBasedOptimization.hh"
#include "ParameterizedFunction.hh"
#include "GeneticOperations.hh"
#include "VectorOperations.hh"
#include "VerifyEnvironment.hh"
#include "Consecutive.hh"
#include "GeneralGraph.hh"
#include "GraphOperations.hh"
#include "EquivalentClasses.hh"

#include "FullSystemType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/

int DistributionReport(ReactionSystemBase *sys);
int CriticalPointList(ReactionSystemBase *sys);
int TransferAttributes(ReactionSystemBase* sys);

#endif
