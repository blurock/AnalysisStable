/*  FILE     Consecutive.hh
**  PACKAGE  Consecutive
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "Consecutive" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_CONSECUTIVE_HH
#define CoreObjects_CONSECUTIVE_HH

#define CONSECUTIVE_INSTSET_NAME    "ClusterInstanceSets"
#define CONSECUTIVE_SERIES_NAME     "ConsecutiveSeries"
#define CONSECUTIVE_SERIESSET_NAME  "ConsecutiveSeriesSet"
#define CONSECUTIVE_ALGORITHM_NAME  "Consecutive"
#define CONSECUTIVE_SORT_NAME       "SortElements"
#define CONSECUTIVE_INSTSET_ID      CONSECUTIVE_BASE + 1
#define CONSECUTIVE_SERIES_ID       CONSECUTIVE_BASE + 2
#define CONSECUTIVE_SERIESSET_ID    CONSECUTIVE_BASE + 3
#define CONSECUTIVE_ALGORITHM_ID    CONSECUTIVE_BASE + 4
#define CONSECUTIVE_SORT_ID         CONSECUTIVE_BASE + 5

#define INSTANCE_NAME_LIST "TrainInstanceNameList"
#define CLUSTER_NAME       "ClusterObject"
#define ROOT_NAME          "RootName"
#define CLUSTERSETS        "ClusterSets"
#define CONSECUTIVE        "Consecutive"
#define MAXIMUMGAP         "MaximumGap"
#define SORTPARAMETER      "SortParameter"
#define CONSECUTIVESET     "ConsecutiveSet"
#define MINIMUMELEMENTS    "MinimumNumberOfElements"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "ConsecutiveType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
void AddConsecutiveClasses(DataSetOfObjectsClass& set);
extern void ConsecutiveEncodeDecodeRoutines();

#endif
