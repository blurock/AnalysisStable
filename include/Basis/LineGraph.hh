/*  FILE     LineGraph.hh
**  PACKAGE  LineGraph
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "LineGraph" package in the Basis environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef Basis_LINEGRAPH_HH
#define Basis_LINEGRAPH_HH

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "LineGraphType.hh"

template <class Type>
ostream& operator<<(ostream& out, const GraphData<Type>& data);

double CalculateEndValue(double hi, double lo, double interval);
double CalculateBeginValue(double lo, double inc);
double CalculateInterval(double hi, double lo);

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "LineGraph.icc"

#ifdef TEMPLATE_INSTANTIATION
#include "LineGraph.itc"
#endif



/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/



#endif
