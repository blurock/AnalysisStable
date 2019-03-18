/*  FILE     NumericObjects.hh
**  PACKAGE  NumericObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "NumericObjects" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_NUMERICOBJECTS_HH
#define CoreObjects_NUMERICOBJECTS_HH
 
#define NUMERIC_BASE_ID            NUMERIC_ID_BASE + 10
#define NUMERIC_INTEGER_ID         NUMERIC_ID_BASE + 20
#define NUMERIC_REAL_ID            NUMERIC_ID_BASE + 30

#define NUMERIC_BASE_NAME          "Numeric"
#define NUMERIC_INTEGER_NAME       "Integer"
#define NUMERIC_REAL_NAME          "Real"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "NumericObjectsType.hh"

/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
void AddNumericClasses(DataSetOfObjectsClass& set);
extern void InitialSetOfNumericEncodeDecodeRoutines();
double Distance(BaseDataNumeric *x, BaseDataNumeric *y);
double Distance(BaseDataNumeric *x);

#endif
