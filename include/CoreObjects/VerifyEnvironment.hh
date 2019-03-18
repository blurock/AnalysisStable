/*  FILE     VerifyEnvironment.hh
**  PACKAGE  VerifyEnvironment
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "VerifyEnvironment" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_VERIFYENVIRONMENT_HH
#define CoreObjects_VERIFYENVIRONMENT_HH

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "VerifyEnvironmentType.hh"


#define VERIFY_OPERATION_ID         VERIFY_ENVIRONMENT_BASE + 1
#define VERIFY_ERROR_ID             VERIFY_ENVIRONMENT_BASE + 2
#define VERIFY_ALGORITHM_ID         VERIFY_ENVIRONMENT_BASE + 3
#define VERIFY_OPERATION_NAME       "VerifyOperation"
#define VERIFY_ERROR_NAME           "VerifyErrorOperation"
#define VERIFY_ALGORITHM_NAME       "VerifyErrorAlgorithm"

/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
void AddBaseVerifyClasses(DataSetOfObjectsClass& set);
extern void VerifyEncodeDecodeRoutines();

#endif
