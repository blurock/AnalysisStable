/*  FILE     EntropyObjects.hh
**  PACKAGE  EntropyObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "EntropyObjects" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_ENTROPYOBJECTS_HH
#define CoreObjects_ENTROPYOBJECTS_HH

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#ifdef _msdos_stl
#include <iomanip>
using namespace std;
#pragma warning(disable:4786)
#endif
 

#define ENTROPY_ALG_ID       ENTROPY_BASE_ID + 10
#define ENTROPY_ALG_NAME     "EntropyAlgorithm"
#define ENTROPY_SELECT_ID    ENTROPY_BASE_ID + 20
#define ENTROPY_SELECT_NAME     "EntropySelectPredicate"


#define LOG2_INVERSE  1.442695
#define CURRENT_INSTANCELIST     "CurrentInstanceList"
#define ENTROPY_PARAMETERS       "EntropyParameters"
#define SELECTION_DESCRIPTORS    "PartitionList"
#define SELECTION_GOAL           "EntropyGoal"
#define ENTROPY_PARTITION_TABLE  "EntropyPartitionTable"
#define ENTROPY_CONJUNCTION      "EntropyConjunction"
#define ENTROPY_GAIN             "EntropyGain"
#define ENTROPY_MATRIX           "EntropyMatrix"
#define ENTROPY_TOP_PREDICATE    "EntropyTopPredicate"
#define DECISIONTREE_PARAMETERS  "DecisionTreeParameters"
#define LOGIC_DESCRIPTIONS       "LogicDescriptions"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "EntropyObjectsType.hh"

void AddEntropyAlgorithmClasses(DataSetOfObjectsClass& set);
extern void InitialEntropyAlgorithmEncodeDecodeRoutines();

/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/



#endif



