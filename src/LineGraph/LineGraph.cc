/*  File     LineGraph.cc
**  PACKAGE  LineGraph
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "LineGraph" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) REACTION Project, Edward S. Blurock
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "BasisSystem.hh"
#include "LineGraph.hh"
 
 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
template class GraphData<double>;

/*F e = CalculateEndValue(hi,lo,interval) . . . . . . . .  Round up end value
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
double CalculateEndValue(double lo, double hi, double interval)
     {
     double hir;
     
     if(interval != 0.0)
	  {
	  double num = (hi - lo)/interval;
	  if(num != 0.0)
	       {
	       double cnum = ceil(num);
	       hir = lo + interval*cnum;
	       }
	  else
	       hir = hi;
	  }
     else
	  hir = hi;
     
     return (double) hir;
     }
 
/*F b = CalculateBeginValue(lo) . . . . . . . . . . .  Round down begin value
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
double CalculateBeginValue(double lo, double inc)
     {
     double rlo;
     
     if(inc != 0.0)
	  rlo = floor(lo/inc) * inc;
     else
	  rlo = 0.0;
     
     double b = 0;
     
     if(rlo !=  0.0)
	  {
	  double fac = 1.0;
	  
	  if(rlo < 0.0)
	       {
	       rlo = -rlo;
	       fac = -1.0;
	       }
	  
	  double lg10 = log10(rlo);
	  
	  double p = floor(lg10);
	  double lr = lg10 - p;
	  double r = pow(10.0,lr);
	  
	  b = fac * r * pow(10.0,p);
	  }
     else
	  {
	  if(inc == 0)
	       b = lo;
	  }
          
     return b;
     }


 
/*F CalculateInterval(hi,lo)  . . . . . . . . . . . . . . Best interval value
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
double CalculateInterval(double hi, double lo)
     {
     double diff = (double) hi - lo;
     double lg10 = log10(diff);
     double p = floor(lg10);
     double lr = lg10 - p;
     double r = pow(10.0,lr);
     double inc;
     
     if(r < 1.5)
	  {
	  inc = .1;
	  }
     else if(r < 2.5)
	  {
	  inc = .2;
	  }
     else if(r < 4.0)
	  {
	  inc = .25;
	  }
     else 
	  {
	  inc = 1.0;
	  }
     double interval = inc * pow(10.0,p);
     
     return interval;
     }
