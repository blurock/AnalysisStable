/*  FILE     GraphOperations.hh
**  PACKAGE  GraphOperations
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "GraphOperations" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_GRAPHOPERATIONS_HH
#define CoreObjects_GRAPHOPERATIONS_HH

#define GRAPHOP_BASE                  30700

#define GRAPHOP_NODEEDGEOP_ID       GRAPHOP_BASE + 10
#define GRAPHOP_ELEMATCH_ID         GRAPHOP_BASE + 20
#define GRAPHOP_NEIGHBORS_ID        GRAPHOP_BASE + 40
#define GRAPHOP_PAIRS_ID            GRAPHOP_BASE + 50
#define GRAPHOP_PAIR_ID             GRAPHOP_BASE + 60
#define GRAPHOP_GRAPHCOUNTS_ID      GRAPHOP_BASE + 70
#define GRAPHOP_PAIRSOP_ID          GRAPHOP_BASE + 80
#define GRAPHOP_NODEEDGEOP_NAME     "NodeEdgeOperation"
#define GRAPHOP_ELEMATCH_NAME       "GraphElementMatch"
#define GRAPHOP_NEIGHBORS_NAME      "GraphNeighbors"
#define GRAPHOP_PAIRS_NAME          "GraphNodePairs"
#define GRAPHOP_PAIR_NAME           "GraphNodePair"
#define GRAPHOP_GRAPHCOUNTS_NAME    "SimpleGraphCounts"
#define GRAPHOP_PAIRSOP_NAME        "GraphNodePairsOperation"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "GraphOperationsType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
void AddGraphOperationClasses(DataSetOfObjectsClass& set);
void InitialGraphOperationEncodeDecodeRoutines();


#endif
