/*  FILE     ClusterTree.hh
**  PACKAGE  ClusterTree
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "ClusterTree" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_CLUSTERTREE_HH
#define CoreObjects_CLUSTERTREE_HH

#define CLUSTER_TREE_ID                COBWEBCLUSTER_ID + 10
#define CLUSTER_NODE_ID                COBWEBCLUSTER_ID + 20
#define CLUSTER_TREE_NAME              "ClusterTree"
#define CLUSTER_NODE_NAME              "ClusterNode"

#define CLUSTER_MAX_LEVEL   "MaxLevel"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "ClusterTreeType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
void AddClusterTreeClasses(DataSetOfObjectsClass& set);
extern void ClusterTreeEncodeDecodeRoutines();



#endif
