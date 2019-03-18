/*  FILE     DecisionTreeAlgorithms.hh
**  PACKAGE  DecisionTreeAlgorithms
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "DecisionTreeAlgorithms" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_DECISIONTREEALGORITHMS_HH
#define CoreObjects_DECISIONTREEALGORITHMS_HH
 
/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#ifdef _msdos_stl
#include <iomanip>
using namespace std;
#pragma warning(disable:4786)
#endif
 
 
#define TREE_DECISION_ID         TREE_DECISION_BASE_ID + 10
#define TREE_DECISION_NAME       "DecisionTree"
#define TREE_CREATE_ID           TREE_DECISION_BASE_ID + 20
#define TREE_CREATE_NAME         "DecisionTreeCreate"
#define TREE_NODESPEC_ID         TREE_DECISION_BASE_ID + 30
#define TREE_NODESPEC_NAME       "DecisionTreeNodeSpec"
#define TREE_NODESTATS_ID        TREE_DECISION_BASE_ID + 40
#define TREE_NODESTATS_NAME      "DecisionTreeNodeStats"
#define TREE_DECTREEFILTER_ID    TREE_DECISION_BASE_ID + 50
#define TREE_DECTREEFILTER_NAME  "FilterDecisionTreeNode"
#define DECISION_TREE               "DecisionTree"
#define MINIMUM_NUMBER_INSTANCES    "DecisionTreeMinimumInstances"
#define MAXIMUM_PARTITION_PERCENT   "DecisionTreePartitionPercent"
#define MINIMUM_ENTROPY_VALUE       "DecisionTreeMinimumEntropy"
#define MAXIMUM_NUMBER_NODES        "DecisionTreeMaximumNodes"
#define DECISION_TREE_FILTER_ANSWER "DecisionTreeFilterAnswer"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "DecisionTreeAlgorithmsType.hh"

/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
void AddDecisionTreeClasses(DataSetOfObjectsClass& set);
extern void DecisionTreeEncodeDecodeRoutines();

#endif
