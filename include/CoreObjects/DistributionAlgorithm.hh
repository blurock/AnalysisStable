/*  FILE     DistributionAlgorithm.hh
**  PACKAGE  DistributionAlgorithm
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "DistributionAlgorithm" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_DISTRIBUTIONALGORITHM_HH
#define CoreObjects_DISTRIBUTIONALGORITHM_HH

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "DistributionAlgorithmType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#define DISTRIBUTION_ATTR_NAME         "AttributeDistribution"
#define DISTRIBUTION_ALG_NAME          "DistributionAlgorithm"
#define DISTRIBUTION_NORMALIZE_NAME    "NormalizeOperation"
#define DISTRIBUTION_SIMPLENORM_NAME   "SimpleNormalizeOperation"
#define DISTRIBUTION_NORMOP_NAME       "SimpleNormalize"
#define DISTRIBUTION_DISTTONORM_NAME   "NormalizeOpFromDistribution"

#define DISTRIBUTION_ATTR_ID          DISTRIBUTION_BASE_ID + 1
#define DISTRIBUTION_ALG_ID           DISTRIBUTION_BASE_ID + 2
#define DISTRIBUTION_NORMALIZE_ID     DISTRIBUTION_BASE_ID + 3
#define DISTRIBUTION_SIMPLENORM_ID    DISTRIBUTION_BASE_ID + 4
#define DISTRIBUTION_NORMOP_ID        DISTRIBUTION_BASE_ID + 5
#define DISTRIBUTION_DISTTONORM_ID    DISTRIBUTION_BASE_ID + 6

void AddBaseDistributionClasses(DataSetOfObjectsClass& set);
extern void InitialDistributionObjectsEncodeDecodeRoutines();

#endif
