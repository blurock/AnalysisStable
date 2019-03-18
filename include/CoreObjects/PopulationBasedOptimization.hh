/*  FILE     PopulationBasedOptimization.hh
**  PACKAGE  PopulationBasedOptimization
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "PopulationBasedOptimization" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_POPULATIONBASEDOPTIMIZATION_HH
#define CoreObjects_POPULATIONBASEDOPTIMIZATION_HH

#define POPULATION_OBJECT_ID               POPULATION_BASE + 1
#define POPULATION_OBJECT_NAME             "PopulationObject"
#define POPULATION_POPULATION_ID           POPULATION_BASE + 2
#define POPULATION_POPULATION_NAME        "Population"
#define POPULATION_COST_ID                 POPULATION_BASE + 3
#define POPULATION_COST_NAME              "PopulationCost"
#define POPULATION_GENETICBASE_ID          POPULATION_BASE + 4
#define POPULATION_GENETICBASE_NAME       "GeneticBasedOptimization"
#define POPULATION_GENETICALGORITHM_ID     POPULATION_BASE + 5
#define POPULATION_GENETICALGORITHM_NAME  "GeneticAlgorithm"
#define POPULATION_VECTORPOP_ID            POPULATION_BASE + 6
#define POPULATION_VECTORPOP_NAME          "RealVectorPopulation"
#define POPULATION_BOUNDARIES_ID           POPULATION_BASE + 7
#define POPULATION_BOUNDARIES_NAME         "RealOptimizationBoundaries"
#define POPULATION_EXPRESSION_ID           POPULATION_BASE + 8
#define POPULATION_EXPRESSION_NAME         "PopulationExpressionObject"
#define POPULATION_NUMEXPR_ID              POPULATION_BASE + 9
#define POPULATION_NUMEXPR_NAME            "PopulationNumExprObject"
#define GENETIC_OBJECT_ID                  POPULATION_BASE + 10
#define GENETIC_OBJECT_NAME                "GeneticObject"

#define STANDARD_VIRTUAL_GENETIC_OBJECT_METHODS                           \
virtual bool Mutate(BaseDataObject *obj,                                  \
                    DataGeneticObjectClass *cls);                         \
virtual BaseDataSetOfObjects *CrossOver(BaseDataObject *obj1,             \
		                        BaseDataObject *obj2,             \
		                        BaseDataGeneticObject *genetic,   \
		                        DataGeneticObjectClass *cls);     \
virtual BaseDataObject *GeneticInitializeObject(DataGeneticObjectClass *cls); \
virtual bool GeneticInitialize(DataGeneticObjectClass *cls,               \
                               BaseDataSetOfInstances *insts,             \
                               DataSetOfInstancesClass *instcls);


/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "PopulationBasedOptimizationType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
void AddPopulationClasses(DataSetOfObjectsClass& set);
extern void InitialSetOfPopulationEncodeDecodeRoutines();

#endif
