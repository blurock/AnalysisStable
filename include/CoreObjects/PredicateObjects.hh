/*  FILE     PredicateObjects.hh
**  PACKAGE  PredicateObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "PredicateObjects" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_PREDICATEOBJECTS_HH
#define CoreObjects_PREDICATEOBJECTS_HH

#define PREDICATE_BASE_ID             PREDICATE_ID_BASE + 1
#define PREDICATE_DESCRIPTION_ID      PREDICATE_ID_BASE + 2
#define PREDICATE_LOGICDESCR_ID       PREDICATE_ID_BASE + 3
#define PREDICATE_PARTITION_ID        PREDICATE_ID_BASE + 4
#define PREDICATE_PARTITIONTABLE_ID   PREDICATE_ID_BASE + 5
#define PREDICATE_CONJUNCTION_ID      PREDICATE_ID_BASE + 6
#define PREDICATE_DISJUNCTION_ID      PREDICATE_ID_BASE + 7
#define PREDICATE_LOGICDESCRSET_ID    PREDICATE_ID_BASE + 8
#define PREDICATE_LOGCOMP_ID          PREDICATE_ID_BASE + 10

#define PREDICATE_BASE_NAME           "Predicate"
#define PREDICATE_DESCRIPTION_NAME    "Description"
#define PREDICATE_LOGICDESCR_NAME     "LogicDescription"
#define PREDICATE_PARTITION_NAME      "Partition"
#define PREDICATE_PARTITIONTABLE_NAME "PartitionTable"
#define PREDICATE_CONJUNCTION_NAME    "Conjunction"
#define PREDICATE_DISJUNCTION_NAME    "Disjunction"
#define PREDICATE_LOGICDESCRSET_NAME  "SetOfLogicDescriptions"
#define PREDICATE_LOGCOMP_NAME        "LogicalDescriptionCompare"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "PredicateObjectsType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
void AddPredicateClasses(DataSetOfObjectsClass& set);
bool CheckPartitionListInSet(BaseDataKeyWords& partlist,
			     BaseDataSetOfObjects *set,
			     DataSetOfObjectsClass *classset,
			     const bool printerror);
bool CheckPredicateListInSet(BaseDataKeyWords& predlist,
			     BaseDataSetOfObjects *set,
			     DataSetOfObjectsClass *classset,
			     const bool printerror);
BaseDataLogicDescription* DetermineLogicInstance(BaseDataLogical *logic,
						 DataLogicalClass *logclass,
						 BaseDataDescription* descr,
						 ObjectList<String>& names,
						 BaseDataSetOfObjects * instance,
						 DataSetOfObjectsClass * instclass);
extern void InitialSetOfPredicateEncodeDecodeRoutines();
void AddPredicateClasses(DataSetOfObjectsClass& set);
#endif



