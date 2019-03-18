/*  FILE     VectorOperations.hh
**  PACKAGE  VectorOperations
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "VectorOperations" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_VECTOROPERATIONS_HH
#define CoreObjects_VECTOROPERATIONS_HH

#define VECOPERATION_FORM_ID            VECOPERATION_BASE + 1
#define VECOPERATION_FORM_NAME          "FormVector"
#define VECOPERATION_REAL_ID            VECOPERATION_BASE + 2
#define VECOPERATION_REAL_NAME          "VectorParameterizedFunction"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "VectorOperationsType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
extern void InitialVectorOperationsEncodeDecodeRoutines();
void AddVectorOperationClasses(DataSetOfObjectsClass& set);


#endif
