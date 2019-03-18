/*  FILE     SelectObjects.hh
**  PACKAGE  SelectObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "SelectObjects" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_SELECTOBJECTS_HH
#define CoreObjects_SELECTOBJECTS_HH

#define SELECTION_SELECTIONS_ID         SELECTION_BASE_ID + 10
#define SELECTION_TREE_ID               SELECTION_BASE_ID + 20
#define SELECTION_SELECTIONS_NAME       "Selections"
#define SELECTION_TREE_NAME             "SelectionTree"
#define SELECTION_CATEGORY_OFFSET       SELECTION_BASE_ID + 100

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "SelectObjectsType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
extern void InitialSetOfSelectionTreeEncodeDecodeRoutines();
void AddSelectionTreeClasses(DataSetOfObjectsClass& set);

#endif
