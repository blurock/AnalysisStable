/*  FILE     PredicateGen.hh
**  PACKAGE  PredicateGen
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "PredicateGen" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_PREDICATEGEN_HH
#define CoreObjects_PREDICATEGEN_HH

#define PREDGEN_CRITICAL_ID              PREDGEN_ID_BASE + 10
#define PREDGEN_CRITICAL_NAME            "CriticalPoints"
#define PREDGEN_READ_ID                  PREDGEN_ID_BASE + 20
#define PREDGEN_READ_NAME                "ReadCriticalPoints"
#define PREDGEN_PARTITIONS_ID             PREDGEN_ID_BASE + 30
#define PREDGEN_PARTITIONS_NAME          "PartitionsFromCriticalPoints"
#define PREDGEN_FROMDISTRIBUTION_ID       PREDGEN_ID_BASE + 40
#define PREDGEN_FROMDISTRIBUTION_NAME    "PredicatesFromDistribution"
#define PREDGEN_FROMKEYWORDS_ID           PREDGEN_ID_BASE + 50
#define PREDGEN_FROMKEYWORDS_NAME        "PredicatesFromKeyWords"

#define PREDGEN_CRITICAL_NUMERICPREDICATE "CriticalPointNumericPredicate"
#define PREDGEN_CRITICAL_FUZZYPREDICATE   "CriticalPointsFuzzyPredicate"

#define CRITICALPOINTS_FILENAME           "CriticalPointsFileName"
#define CRITICALPOINTS_ROOTNAME           "CriticalPointsRootName"
#define CRITICALPOINTS_POINTLIST          "CriticalPointsList"
#define CRITICALPOINTS_CRITICALPOINTS     "CriticalPoints"

#define PARTFROMPOINTS_TYPES              "PartitionTypesFromPoints"
#define PARTFROMPOINTS_PREDICATES         "PredicateList"
#define PARTFROMPOINTS_PARTITIONS         "PartitionList"

#define KEYWORD_LIST                      "KeyWordList"
#define PREDICATE_OBJECT                  "PredicateObject"


/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "PredicateGenType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
extern void AddPredicateGenAlgorithmClasses(DataSetOfObjectsClass& set);
extern void InitialPredicateGenEncodeDecodeRoutines();

#endif
