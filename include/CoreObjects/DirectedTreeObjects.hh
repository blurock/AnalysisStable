/*  FILE     DirectedTreeObjects.hh
**  PACKAGE  DirectedTreeObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "DirectedTreeObjects" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_DIRECTEDTREEOBJECTS_HH
#define CoreObjects_DIRECTEDTREEOBJECTS_HH

 
/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "Pairs.hh"
#include "Graph.hh"
#include "DirectedTreeObjectsType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#define DIRECTEDTREE_NODE_ID         DIRECTEDTREE_ID_BASE + 10
#define DIRECTEDTREE_NODE_NAME       "TreeNode"
#define DIRECTEDTREE_BASE_ID         DIRECTEDTREE_ID_BASE + 20
#define DIRECTEDTREE_BASE_NAME       "DirectedTree"

extern void InitialSetOfDirectedTreesEncodeDecodeRoutines();
void AddDirectedTreeObjects(DataSetOfObjectsClass& set);

#endif
