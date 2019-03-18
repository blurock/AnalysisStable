/*  FILE     InstanceAlgorithms.hh
**  PACKAGE  InstanceAlgorithms
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "InstanceAlgorithms" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_INSTANCEALGORITHMS_HH
#define CoreObjects_INSTANCEALGORITHMS_HH

#define INSTALGORITHMS_ATTRIBUTES_ID   INSTALGORITHMS_BASE_ID + 10
#define INSTALGORITHMS_ATTRIBUTES_NAME     "InstanceAttributesAlg"
#define INSTALGORITHMS_INSTANCES_ID    INSTALGORITHMS_BASE_ID + 20
#define INSTALGORITHMS_INSTANCES_NAME      "InstanceInstancesAlg"
#define INSTALGORITHMS_MATRIX_ID       INSTALGORITHMS_BASE_ID + 30
#define INSTALGORITHMS_MATRIX_NAME         "InstanceMatrixAlg"
#define INSTALGORITHMS_READASCII_ID    INSTALGORITHMS_BASE_ID + 40
#define INSTALGORITHMS_READASCII_NAME      "InstanceReadASCIIAlg"
#define INSTALGORITHMS_PREDICATE_ID    INSTALGORITHMS_BASE_ID + 50
#define INSTALGORITHMS_PREDICATE_NAME  "InstancesFromPredicate"

#define INSTALGORITHMS_MATGRPOUTPUT_ID      INSTALGORITHMS_BASE_ID + 60
#define INSTALGORITHMS_MATGRPOUTPUT_NAME    "MatrixGraphOutput"
#define INSTALGORITHMS_MATRIXREAD_ID        INSTALGORITHMS_BASE_ID + 70
#define INSTALGORITHMS_MATRIXREAD_NAME      "ReadMatrix"
#define INSTALGORITHMS_MATRIXINSTANCES_ID   INSTALGORITHMS_BASE_ID + 80
#define INSTALGORITHMS_MATRIXINSTANCES_NAME "MatrixToInstances"

#define MATRIX_OBJECT        "MatrixObject"
#define ROOT_NAME            "RootName"
#define XCOORDINATE_NAME     "Xcoordinate"
#define YCOORDINATES_NAME     "Ycoordinates"

#define REALTYPEFORINSTANCEPARAMETER "RealType"
#define MATRIXREADCLASSPARAMETER     "MatrixReadClass"
#define FILENAMEPARAMETER            "FileName"
#define INDEXPREFIX                  "IndexPrefix"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "InstanceAlgorithmsType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
void AddInstanceAlgorithmsClasses(DataSetOfObjectsClass& set);
extern void InitialInstanceAlgorithmsEncodeDecodeRoutines();

#endif
