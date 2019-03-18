/*  FILE     Iterator.hh
**  PACKAGE  Iterator
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "Iterator" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_ITERATOR_HH
#define CoreObjects_ITERATOR_HH

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "IteratorType.hh"

#define ITERATOR_OBJECT_ID      ITERATOR_BASE_ID + 10
#define ITERATOR_NUMERIC_ID     ITERATOR_BASE_ID + 20
#define ITERATOR_REAL_ID        ITERATOR_BASE_ID + 30
#define ITERATOR_SET_ID         ITERATOR_BASE_ID + 40

#define ITERATOR_OBJECT_NAME      "ObjectIterator"
#define ITERATOR_NUMERIC_NAME     "NumericIterator"
#define ITERATOR_REAL_NAME        "RealIterator"
#define ITERATOR_SET_NAME         "IterationSet"

#define NUMERIC_ITERATOR_KEYWORD "NumericIterator:"
#define REAL_ITERATOR_KEYWORD    "RealIterator:"
#define TOP_ITERATOR_KEYWORD     "IterationSet:"
#define ITERATOR_KEYWORD         "Iterator:"

/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/

extern void InitialIteratorEncodeDecodeRoutines();
void AddIteratorClasses(DataSetOfObjectsClass& set);
bool ReadSetOfObjects(istream& in,
		      BaseDataSetOfObjects * set,
		      DataSetOfObjectsClass* setclass, 
		      const String& name,
		      BaseDataKeyWords keys);


#endif
