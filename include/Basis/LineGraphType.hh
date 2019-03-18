/*  FILE     LineGraphType.hh
**  PACKAGE  LineGraph
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "LineGraph" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 Basis Project, RISC Linz
*/
 
#ifndef Basis_LINEGRAPHTYPE_HH
#define Basis_LINEGRAPHTYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
/*C GraphData . . . . . . . . . . . . . . . . . . . data to draw a line graph
**
**  DESCRIPTION
**
**  REMARKS
**
*/
template <class Type>
class GraphData
     {
     ObjectList<Type> Sorted;
     
     Type HiValue;
     Type LoValue;
     
     Type Begin;
     Type End;
     Type Increment;
     
     
 public:
     ObjectList<Type> Original;

     GraphData();
     GraphData(const GraphData<Type>& data);
     
     ostream& print(ostream& out) const;
     GraphData<Type>& operator()(GraphData<Type>& data, const Type point);

     void AddObject(const Type point);
     void MaxMinSort();
     void CalcBeginEndInterval();
     
     ostream& CalcAndShowGraphData(ostream& out);
     
     };


#endif
