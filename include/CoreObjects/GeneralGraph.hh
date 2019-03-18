/*  FILE     GeneralGraph.hh
**  PACKAGE  GeneralGraph
**  AUTHOR   Mario Drobics
**
**  CONTENT
**    Prototypes for the "GeneralGraph" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_GENERALGRAPH_HH
#define CoreObjects_GENERALGRAPH_HH

#define GENERALGRAPH_BASE_ID 40000
#define SOMGENERAL_BASE_ID 40100
#define SOMFIX_BASE_ID 40300
#define SOMDYNAMIC_BASE_ID 40500
#define SOMUTILITIES_BASE_ID 40700

#define GENERALGRAPH_GRAPH_ID GENERALGRAPH_BASE_ID + 10
#define GENERALGRAPH_GRAPH_NAME "Graph"
#define GENERALGRAPH_NODE_ID GENERALGRAPH_BASE_ID + 20
#define GENERALGRAPH_NODE_NAME "Node"
#define GENERALGRAPH_EDGE_ID GENERALGRAPH_BASE_ID + 30
#define GENERALGRAPH_EDGE_NAME "Edge"
#define GENERALGRAPH_NEURALMAP_ID GENERALGRAPH_BASE_ID + 40
#define GENERALGRAPH_NEURALMAP_NAME "NeuralMap"
#define GENERALGRAPH_MAPNODE_ID GENERALGRAPH_BASE_ID + 50
#define GENERALGRAPH_MAPNODE_NAME "MapNode"
#define GENERALGRAPH_NEURALGRID_ID GENERALGRAPH_BASE_ID + 60
#define GENERALGRAPH_NEURALGRID_NAME "NeuralGrid"


/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "GeneralGraphType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/

extern void InitialSetOfGeneralGraphEncodeDecodeRoutines();
void AddGeneralGraphClasses(DataSetOfObjectsClass& set);


#endif
