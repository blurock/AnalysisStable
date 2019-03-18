/*  FILE     LogicalOperations.hh
**  PACKAGE  LogicalOperations
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "LogicalOperations" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_LOGICALOPERATIONS_HH
#define CoreObjects_LOGICALOPERATIONS_HH


#define LOGICALOP_BASE_ID          LOGICALOP_ID_BASE + 1
#define LOGICALOP_BASE_NAME        "LogicalOperation"
#define LOGICALOP_AND_ID           LOGICALOP_ID_BASE + 2
#define LOGICALOP_AND_NAME         "LogicalAND"
#define LOGICALOP_OR_ID            LOGICALOP_ID_BASE + 3
#define LOGICALOP_OR_NAME          "LogicalOR"
#define LOGICALOP_NOT_ID           LOGICALOP_ID_BASE + 4
#define LOGICALOP_NOT_NAME         "LogicalNOT"
#define LOGICALOP_NUMPRED_ID       LOGICALOP_ID_BASE + 5
#define LOGICALOP_NUMPRED_NAME     "NumericPredicate"
#define LOGICALOP_EXACTEQPRED_ID   LOGICALOP_ID_BASE + 6
#define LOGICALOP_EXACTEQPRED_NAME "ExactlyEqualPredicate"
#define LOGICALOP_REALTOLOGIC_ID   LOGICALOP_ID_BASE + 7
#define LOGICALOP_REALTOLOGIC_NAME "RealToLogic"
#define LOGICALOP_REALPRED_ID      LOGICALOP_ID_BASE + 8
#define LOGICALOP_REALPRED_NAME    "RealPredicate"
#define LOGICALOP_KEYWORDMEMBER_ID      LOGICALOP_ID_BASE + 9
#define LOGICALOP_KEYWORDMEMBER_NAME    "MemberOfKeyWord"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "LogicalOperationsType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
void AddLogicalOperationClasses(DataSetOfObjectsClass& set);
extern void InitialSetOfLogicalOperationEncodeDecodeRoutines();


#endif
