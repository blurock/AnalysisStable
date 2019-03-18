/*  FILE     EquivalentClasses.hh
**  PACKAGE  EquivalentClasses
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "EquivalentClasses" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_EQUIVALENTCLASSES_HH
#define CoreObjects_EQUIVALENTCLASSES_HH

#define EQUIVALENTSETS_DEGREE_ID          EQUIVALENTSETS_BASE + 1
#define EQUIVALENTSETS_DEGREE_NAME       "DegreeOfEquivalence"
#define EQUIVALENTSETS_EQUIVALENT_ID      EQUIVALENTSETS_BASE + 2
#define EQUIVALENTSETS_EQUIVALENT_NAME   "EquivalentSet"
#define EQUIVALENTSETS_SET_ID             EQUIVALENTSETS_BASE + 3
#define EQUIVALENTSETS_SET_NAME          "SetOfEquivalentSets"
#define EQUIVALENTSETS_SIMPEQUIVALG_ID             EQUIVALENTSETS_BASE + 4
#define EQUIVALENTSETS_SIMPEQUIVALG_NAME          "SimpleEquivalentSetAlgorithm"
#define EQUIVALENTSETS_NUMDEGREE_ID          EQUIVALENTSETS_BASE + 5
#define EQUIVALENTSETS_NUMDEGREE_NAME       "DegreeOfEquivalenceNumeric"
#define EQUIVALENTSETS_ADDCLASSTOKEYS_ID          EQUIVALENTSETS_BASE + 6
#define EQUIVALENTSETS_ADDCLASSTOKEYS_NAME       "AddEquivalentNameToKeyWords"

#define EQUIVALENT_SET_NAME      "EquivalentSets"
#define EQUIVALENT_NUMERICCUTOFF "CutOffCriteria"
#define EQUIVALENT_SINGLETONS    "FilterOutSingletons"
#define EQUIVALENT_REPLACE_KEY   "ReplaceKey"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "EquivalentClassesType.hh"



/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
BaseDataSetOfObjects *SetUpCorrespondences(BaseDataSetOfEquivalentSets *sets);
BaseDataKeyWords *TranslateKeyWords(BaseDataKeyWords *keys, BaseDataSetOfObjects *translations);
void ReplaceWithTranslatedKeyWords(BaseDataKeySet *keys, BaseDataSetOfObjects *translations);
void AddEquivalenceClassesClasses(DataSetOfObjectsClass& set);
void InitialSetOfEquivalenceClassesEncodeDecodeRoutines();


#endif
