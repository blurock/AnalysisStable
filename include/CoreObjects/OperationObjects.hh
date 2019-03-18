/*  FILE     OperationObjects.hh
**  PACKAGE  OperationObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "OperationObjects" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_OPERATIONOBJECTS_HH
#define CoreObjects_OPERATIONOBJECTS_HH


#define OPERATION_BASE_ID             OPERATION_ID_BASE + 10
#define OPERATION_BASE_NAME           "Operation"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"

#define STANDARD_VIRTUAL_OPERATION_METHODS                                             \
virtual BaseDataObject *operator()(BaseDataObject *x, DataObjectClass *xclass);        \
virtual BaseDataObject *operator()(BaseDataObject *x, BaseDataObject *y,               \
				   DataObjectClass *xclass, DataObjectClass *yclass);  \
virtual BaseDataObject *operator()(DataObjectClass *cls,                               \
				   BaseDataObject *x, DataObjectClass *xclass);        \
virtual BaseDataObject *operator()(DataObjectClass *cls,                               \
				   BaseDataObject *x, BaseDataObject *y,               \
				   DataObjectClass *xclass, DataObjectClass *yclass);

#include "OperationObjectsType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/

void AddOperationClasses(DataSetOfObjectsClass& set);
extern void InitialSetOfOperationEncodeDecodeRoutines();




#endif
