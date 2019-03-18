/*  FILE     NumericProperties.hh
**  PACKAGE  NumericProperties
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "NumericProperties" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_NUMERICPROPERTIES_HH
#define CoreObjects_NUMERICPROPERTIES_HH

#define NUMERICPROPS_MATPLOT_ID         NUMERICPROPS_BASE + 1
#define NUMERICPROPS_POLYPROPS_ID       NUMERICPROPS_BASE + 2
#define NUMERICPROPS_CALCULATE_ID       NUMERICPROPS_BASE + 3

#define NUMERICPROPS_MATPLOT_NAME       "MatrixPlots"
#define NUMERICPROPS_POLYPROPS_NAME     "PolynomialPlotProperties"
#define NUMERICPROPS_CALCULATE_NAME     "CalculateNumericProperties"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "NumericPropertiesType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
extern void InitialSetOfNumericPropertiesEncodeDecodeRoutines();
void AddNumericPropertiesClasses(DataSetOfObjectsClass& set);

#endif
