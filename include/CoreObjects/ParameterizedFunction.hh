/*  FILE     ParameterizedFunction.hh
**  PACKAGE  ParameterizedFunction
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "ParameterizedFunction" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
#include "DataObjects.hh"

#ifndef CoreObjects_PARAMETERIZEDFUNCTION_HH
#define CoreObjects_PARAMETERIZEDFUNCTION_HH

#define PARAMETERIZED_SET_ID            PARAMETERIZED_BASE + 1
#define PARAMETERIZED_SET_NAME          "ParameterSet"
#define PARAMETERIZED_FUNCTION_ID       PARAMETERIZED_BASE + 2
#define PARAMETERIZED_FUNCTION_NAME     "ParameterizedFunction"
#define PARAMETERIZED_EXPRESSION_ID     PARAMETERIZED_BASE + 3
#define PARAMETERIZED_EXPRESSION_NAME   "ParameterizedExpression"
#define PARAMETERIZED_SETOP_ID          PARAMETERIZED_BASE + 4
#define PARAMETERIZED_SETOP_NAME        "ParameterSetOperation"
#define PARAMETERIZED_REALFUNC_ID       PARAMETERIZED_BASE + 5
#define PARAMETERIZED_REALFUNC_NAME     "RealFunctionParameterized"
#define PARAMETERIZED_EXTRACT_ID        PARAMETERIZED_BASE + 6
#define PARAMETERIZED_EXTRACT_NAME      "ParameterExtract"
#define PARAMETERIZED_EXPDESCR_ID       PARAMETERIZED_BASE + 7
#define PARAMETERIZED_EXPDESCR_NAME     "DescriptionExpressions"
#define PARAMETERIZED_DESCROP_ID        PARAMETERIZED_BASE + 8
#define PARAMETERIZED_DESCROP_NAME      "DoOperation"
#define PARAMETERIZED_PINFUNC_ID        PARAMETERIZED_BASE + 9
#define PARAMETERIZED_PINFUNC_NAME      "ParametersInFunction"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "ParameterizedFunctionType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
extern void InitialParameterizedEncodeDecodeRoutines();
void AddParameterizedClasses(DataSetOfObjectsClass& set);


#endif
