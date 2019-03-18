/*  FILE     StartPairs.cc
**  PACKAGE  StartPairs
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "StartPairs" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) REACTION Project, Edward S. Blurock
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#define TEMPLATE_INSTANTIATION
#include "BasisSystem.hh"
#include "Pairs.hh"
#include "Graph.hh"
#include "StartPairs.hh"

#define STARTPAIRS_T1 int
#define STARTPAIRS_T2 int
#define STARTPAIRS_KEYTYPE int
#define STARTPAIRS_T int
//#include "BasisSrc/StartPairs/StartPairs.irq"


template class BasicPair<int,int>;
template class list< BasicPair<int,int> >;
template class ObjectList< BasicPair<int,int> >;
template class PairList<int,int>;
//template class Graph<int,int>;

template class GroupEquivalentJWork<STARTPAIRS_T1,STARTPAIRS_T2>;
template class GraphPairInfo<STARTPAIRS_KEYTYPE,STARTPAIRS_T>;
template class EquivalentPairClass<STARTPAIRS_T1,STARTPAIRS_T2>;
template class CreateEquivalentPairClass <STARTPAIRS_T1,STARTPAIRS_T2>;
template class FindStartPairs<STARTPAIRS_KEYTYPE,STARTPAIRS_T>;

#undef STARTPAIRS_T 
#undef STARTPAIRS_KEYTYPE

//template bool operator<<(ostream &, ObjectList<EquivalentPairClass<int, int> > const &);
template bool Decode(CommBuffer &, EquivalentPairClass<int, int> &);
template bool Encode(CommBuffer &, EquivalentPairClass<int, int> &);


