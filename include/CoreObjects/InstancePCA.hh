/*  FILE     InstancePCA.hh
**  PACKAGE  InstancePCA
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "InstancePCA" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_INSTANCEPCA_HH
#define CoreObjects_INSTANCEPCA_HH

#define PCAINSTANCE_PCA_ID        PCAINSTANCE_BASE_ID + 10
#define PCAINSTANCE_PCA_NAME      "InstancePCA"
#define PCAINSTANCE_OBJECT_ID     PCAINSTANCE_BASE_ID + 20
#define PCAINSTANCE_OBJECT_NAME   "InstancePCAObject"
#define PCAINSTANCE_GEN_ID        PCAINSTANCE_BASE_ID + 30
#define PCAINSTANCE_GEN_NAME      "PCAParameterGenerate"

 
/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "InstancePCAType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
void AddBasePCAClasses(DataSetOfObjectsClass& set);
extern void InitialPCAEncodeDecodeRoutines();



#endif
