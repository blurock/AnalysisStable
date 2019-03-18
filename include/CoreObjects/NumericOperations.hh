/*  FILE     NumericOperations.hh
**  PACKAGE  NumericOperations
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "NumericOperations" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_NUMERICOPERATIONS_HH
#define CoreObjects_NUMERICOPERATIONS_HH

#define OPERATION_NUMERIC_ID          OPERATION_ID_BASE + 20
#define OPERATION_NUMPLUS_ID          OPERATION_ID_BASE + 21
#define OPERATION_NUMMINUS_ID         OPERATION_ID_BASE + 22
#define OPERATION_NUMMULT_ID          OPERATION_ID_BASE + 23
#define OPERATION_NUMDIVIDE_ID        OPERATION_ID_BASE + 24
#define OPERATION_LINESEGMENTS_ID     OPERATION_ID_BASE + 25
#define OPERATION_LOGTOREAL_ID        OPERATION_ID_BASE + 26
#define OPERATION_NUMERIC_NAME        "NumericOperation"
#define OPERATION_NUMPLUS_NAME        "NumOpPlus"
#define OPERATION_NUMMINUS_NAME       "NumOpMinus"
#define OPERATION_NUMMULT_NAME        "NumOpMultiply"
#define OPERATION_NUMDIVIDE_NAME      "NumOpDivide"
#define OPERATION_LINESEGMENTS_NAME   "NumericLineSegmentFunction"
#define OPERATION_LOGTOREAL_NAME      "LogicToReal"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "NumericOperationsType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
extern void InitialSetOfNumericOperationEncodeDecodeRoutines();
void AddNumericOperationClasses(DataSetOfObjectsClass& set);

#endif
