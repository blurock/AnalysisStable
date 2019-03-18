/*  FILE     GeneticOperations.hh
**  PACKAGE  GeneticOperations
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "GeneticOperations" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_GENETICOPERATIONS_HH
#define CoreObjects_GENETICOPERATIONS_HH

#define GENETIC_DISTRIBUTION_ID           GENETIC_BASE + 2
#define GENETIC_DISTRIBUTION_NAME         "GeneticDistribution"
#define GENETIC_STDDEV_ID                 GENETIC_BASE + 3
#define GENETIC_STDDEV_NAME               "GeneticStdDev"
#define GENETIC_INTERVAL_ID               GENETIC_BASE + 4
#define GENETIC_INTERVAL_NAME             "GeneticInterval"
#define GENETIC_CONSTANT_ID               GENETIC_BASE + 6
#define GENETIC_CONSTANT_NAME             "GeneticConstant"
#define GENETIC_SETOFPARAMS_ID            GENETIC_BASE + 5
#define GENETIC_SETOFPARAMS_NAME          "GeneticSetOfParameters"

#define SET_NAME1  "C1"
#define SET_NAME2  "C2"
/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "GeneticOperationsType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
extern void InitialGeneticEncodeDecodeRoutines();
void AddGeneticClasses(DataSetOfObjectsClass& set);
BaseDataSetOfObjects *PairSet(DataObjectClass *popobjectbase);

#endif
