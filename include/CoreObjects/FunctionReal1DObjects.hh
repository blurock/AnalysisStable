/*  FILE     FunctionReal1DObjects.hh
**  PACKAGE  FunctionReal1DObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "FunctionReal1DObjects" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_FUNCTIONREAL1DOBJECTS_HH
#define CoreObjects_FUNCTIONREAL1DOBJECTS_HH

#define ODREALFUNC_BASE_NAME          "ODReal"
#define ODREALFUNC_CONSTANT_NAME      "ConstantODReal"
#define ODREALFUNC_LINEAR_NAME        "LinearODReal"
#define ODREALFUNC_GAUSSIAN_NAME      "GaussianODReal"
#define ODREALFUNC_PIECEWISE_NAME     "PiecewiseContinuousODReal"
#define ODREALFUNC_PYRAMID_NAME       "PyramidODReal"
#define ODREALFUNC_EXPONENTIAL_NAME   "ExponentialODReal"
#define ODREALFUNC_POWER_NAME         "PowerODReal"
#define ODREALFUNC_BASE_ID            ODREADFUNC_ID_BASE + 10
#define ODREALFUNC_CONSTANT_ID        ODREADFUNC_ID_BASE + 20
#define ODREALFUNC_LINEAR_ID          ODREADFUNC_ID_BASE + 30
#define ODREALFUNC_GAUSSIAN_ID        ODREADFUNC_ID_BASE + 40
#define ODREALFUNC_PIECEWISE_ID       ODREADFUNC_ID_BASE + 50
#define ODREALFUNC_PYRAMID_ID         ODREADFUNC_ID_BASE + 60
#define ODREALFUNC_EXPONENTIAL_ID     ODREADFUNC_ID_BASE + 70
#define ODREALFUNC_POWER_ID           ODREADFUNC_ID_BASE + 80


/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "Vector.hh"
#include "OperationObjects.hh"
#include "ParameterizedFunction.hh"
#include "FunctionReal1DObjectsType.hh"
 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#define HIGHEST_POSSIBLE_REAL     1e+35
#define LOWEST_POSSIBLE_REAL     -1e+35
#define HIGHEST_POSSIBLE_REAL_NAME    "+Infinity"
#define LOWEST_POSSIBLE_REAL_NAME    "-Infinity"

/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
extern void InitialSetOfODRealEncodeDecodeRoutines();
void AddFunctionClasses(DataSetOfObjectsClass& set);
double ConvertNumericString(String& sval);


#endif
