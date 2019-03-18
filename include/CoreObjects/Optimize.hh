/*  FILE     Optimize.hh
**  PACKAGE  Optimize
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "Optimize" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_OPTIMIZE_HH
#define CoreObjects_OPTIMIZE_HH

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "OptimizeType.hh"

#define OPTCOST_OPTIMIZE_NAME        "OptimizeCostFunction"
#define OPTCOST_OPTIMIZE_ID          OPTIMIZE_BASE + 1
#define OPTCOST_VECTOR_NAME          "RealVectorCostFunction"
#define OPTCOST_VECTOR_ID            OPTIMIZE_BASE + 2

#define OPTIMIZE_OPERATION_NAME            "OptimizeOperation"
#define OPTIMIZE_OPERATION_ID              OPTIMIZE_BASE + 3
#define OPTIMIZE_REAL_NAME                 "RealOptimizeOperation"
#define OPTIMIZE_REAL_ID                   OPTIMIZE_BASE + 4
#define OPTIMIZE_SIMPLEITERATION_NAME      "SimpleIterativeOptimize"
#define OPTIMIZE_SIMPLEITERATION_ID        OPTIMIZE_BASE + 5

/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
extern void InitialSetOfOptimizeEncodeDecodeRoutines();
void AddOptimizeClasses(DataSetOfObjectsClass& set);


#endif
