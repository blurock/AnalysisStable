/*  FILE     ExpressionTree.hh
**  PACKAGE  ExpressionTree
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "ExpressionTree" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_EXPRESSIONTREE_HH
#define CoreObjects_EXPRESSIONTREE_HH

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "ExpressionTreeType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#define EXPRESSIONTREE_NODE_ID        EXPRESSIONTREE_ID_BASE + 10
#define EXPRESSIONTREE_ALG_ID         EXPRESSIONTREE_ID_BASE + 20
#define EXPRESSIONTREE_OBJECT_ID      EXPRESSIONTREE_ID_BASE + 30
#define EXPRESSIONTREE_TREE_ID        EXPRESSIONTREE_ID_BASE + 40
#define EXPRESSIONTREE_ALGOP_ID       EXPRESSIONTREE_ID_BASE + 50
#define EXPRESSIONTREE_PARAM_ID       EXPRESSIONTREE_ID_BASE + 60
#define EXPRESSIONTREE_NODE_NAME     "ExpressionTreeNode"
#define EXPRESSIONTREE_ALG_NAME      "ExpressionTreeAlgorithm"
#define EXPRESSIONTREE_OBJECT_NAME   "ExpressionTreeObject"
#define EXPRESSIONTREE_TREE_NAME     "ExpressionTree"
#define EXPRESSIONTREE_ALGOP_NAME    "ExpressionAlgorithm"
#define EXPRESSIONTREE_PARAM_NAME    "ParameterizedExpression"

void AddBaseExpressionTreeClasses(DataSetOfObjectsClass& set);
extern void InitialSetOfExpressionTreeEncodeDecodeRoutines();

#define LOCAL_PARAMETER_KEYWORD "LocalExpressionKeyWords:"

#endif


