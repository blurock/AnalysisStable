/*  FILE     DescriptionProbs.hh
**  PACKAGE  DescriptionProbs
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "DescriptionProbs" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_DESCRIPTIONPROBS_HH
#define CoreObjects_DESCRIPTIONPROBS_HH

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "DescriptionProbsType.hh"

#define DESCRIPTIONPROBS_BASE        25000

#define DESCRIPTIONPROBS_MAT_NAME        "DescriptionMatrix"
#define DESCRIPTIONPROBS_MAT_ID          DESCRIPTIONPROBS_BASE + 10
#define DESCRIPTIONPROBS_MEMBERSHIP_NAME "DetermineMembershipByTrying"
#define DESCRIPTIONPROBS_MEMBERSHIP_ID   DESCRIPTIONPROBS_BASE + 20
#define DESCRIPTIONPROBS_SETUP_NAME      "DescriptionMatrixSetUp"
#define DESCRIPTIONPROBS_SETUP_ID        DESCRIPTIONPROBS_BASE + 30
#define DESCRIPTIONPROBS_COBWEB_NAME      "CobwebBestGroup"
#define DESCRIPTIONPROBS_COBWEB_ID        DESCRIPTIONPROBS_BASE + 40

#define COBWEB_BEST_GROUP_GROUPPROBS  "GroupProbs"
#define COBWEB_BEST_GROUP_SINGLE      "SingleDescription"
#define COBWEB_BEST_GROUP_MEMBERSHIP  "SingleMembership"
#define COBWEB_BEST_GROUP_DESCR       "DescriptionMatrix"
#define COBWEB_BEST_GROUP_INGROUP     "InGroupMeasure"
#define COBWEB_BEST_GROUP_EXTRAGROUP  "ExtraGroupMeasure"

#define DESCRIPTION_MATRIX_NAME  "DescriptionMatrix"
/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
extern void InitialDescriptionProbsEncodeDecodeRoutines();
void AddDescriptionProbsClasses(DataSetOfObjectsClass& set);
MatrixNumeric *MatrixOfProbabilitiesCalc(ObjectList<String>& inames,
					BaseDataSetOfObjects& descrs,
					BaseDataSetOfInstances& instances,
					DataSetOfInstancesClass& instsclass);

#endif
