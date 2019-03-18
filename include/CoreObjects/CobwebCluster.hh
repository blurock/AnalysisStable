/*  FILE     CobwebCluster.hh
**  PACKAGE  CobwebCluster
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "CobwebCluster" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_COBWEBCLUSTER_HH
#define CoreObjects_COBWEBCLUSTER_HH

 
/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#ifdef _msdos_stl
#include <iomanip>
using namespace std;
#pragma warning(disable:4786)
#endif
 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#define COBWEB_LOGIC_TYPE  "LogicType"
#define COBWEB_DESCRIPTION "PredicateList"
#define COBWEB_GOALS       "GoalNameList"
#define COBWEB_TRAININGSET "TrainInstanceNameList"
#define COBWEB_TESTSET     "TestInstanceNameList"
#define COBWEB_ADD_INSTANCE_ALONE "AddInstanceAloneToNode"
#define CLUSTER_SMALLEST_ASSIGNED  "SmallestNodeForAssignment"

#define COBWEBCLUSTER_NODESTATS_ID     COBWEBCLUSTER_ID + 30
#define COBWEBCLUSTER_BASETREE_ID      COBWEBCLUSTER_ID + 40
#define COBWEBCLUSTER_TREECREATE_ID    COBWEBCLUSTER_ID + 50

#define COBWEBCLUSTER_NODESTATS_NAME   "CobwebClusterNodeStats"
#define COBWEBCLUSTER_BASETREE_NAME    "CobwebClusterTree"
#define COBWEBCLUSTER_TREECREATE_NAME  "CobwebClusterTreeCreate"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "CobwebClusterType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
void AddCobwebAlgorithmClasses(DataSetOfObjectsClass& set);
extern void CobwebClusterEncodeDecodeRoutines();



#endif
