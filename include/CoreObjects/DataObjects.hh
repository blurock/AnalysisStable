/*  FILE     DataObjects.hh
**  PACKAGE  DataObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "DataObjects" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_DATAOBJECTS_HH
#define CoreObjects_DATAOBJECTS_HH


/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "Vector.hh"
#include "MatrixNumeric.hh"
#include "DataObjectsType.hh"

#define DATAOBJ_KEYWORDS_ID        DATAOBJECTS_ID_BASE + 1
#define DATAOBJ_MATRIX_ID          DATAOBJECTS_ID_BASE + 2
#define DATAOBJ_VECTOR_ID          DATAOBJECTS_ID_BASE + 3
#define DATAOBJ_STRING_ID          DATAOBJECTS_ID_BASE + 4
#define DATAOBJ_KEYSET_ID          DATAOBJECTS_ID_BASE + 5
#define DATAOBJ_PAIR_ID            DATAOBJECTS_ID_BASE + 6

#define DATAOBJ_KEYWORDS_NAME      "KeyWords"
#define DATAOBJ_MATRIX_NAME        "Matrix"
#define DATAOBJ_VECTOR_NAME        "Vector"
#define DATAOBJ_STRING_NAME        "String"
#define DATAOBJ_KEYSET_NAME        "KeySet"
#define DATAOBJ_PAIR_NAME          "Pair"

/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
void AddDataObjectClasses(DataSetOfObjectsClass& set);
extern void InitialSetOfDataObjectsEncodeDecodeRoutines();

#endif
