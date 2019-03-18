/*  FILE     EvaluationTree.hh
**  PACKAGE  EvaluationTree
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "EvaluationTree" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_EVALUATIONTREE_HH
#define CoreObjects_EVALUATIONTREE_HH

#define EVALUATIONTREE_TREE_ID   EVALUATIONTREE_ID_BASE + 30
#define EVALUATIONTREE_TREE_NAME "EvaluationTree"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "EvaluationTreeType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
extern void InitialEvaluationTreeEncodeDecodeRoutines();
extern void AddEvaluationTreeClasses(DataSetOfObjectsClass& set);



#endif
