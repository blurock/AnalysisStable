/*  FILE     LogicalObjects.hh
**  PACKAGE  LogicalObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "LogicalObjects" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_LOGICALOBJECTS_HH
#define CoreObjects_LOGICALOBJECTS_HH

#define LOGICAL_BASE_ID            LOGICAL_ID_BASE + 10
#define LOGICAL_NVALUED_ID         LOGICAL_ID_BASE + 20
#define LOGICAL_CONTINUOUS_ID      LOGICAL_ID_BASE + 30
#define LOGICAL_BASE_NAME          "Logical"
#define LOGICAL_NVALUED_NAME       "NValued"
#define LOGICAL_CONTINUOUS_NAME    "Continuous"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "LogicalObjectsType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
void AddLogicalClasses(DataSetOfObjectsClass& set);
extern void InitialSetOfLogicalEncodeDecodeRoutines();
#endif
