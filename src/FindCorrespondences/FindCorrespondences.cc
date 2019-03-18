/*  FILE     FindCorrespondences.cc
**  PACKAGE  FindCorrespondences
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "FindCorrespondences" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) REACTION Project, Edward S. Blurock
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "BasisSystem.hh"
#define TEMPLATE_INSTANTIATION
#include "Pairs.hh"
#include "Graph.hh"
#include "StartPairs.hh"
#include "SubGraph.hh"
#include "FindCorrespondences.hh"

template class ObjectList<int>;
template class ObjectList<PairList<int, int> >;
template class GraphNode<int,int>;
template class SearchableObjectList< int, GraphNode<int,int> >;
template class Graph<int,int>;
template class IsolateCorrespondencesFromGraphInfo<int, int>;
template class FindStartPairs<int,int>;
template class FilterOutSmallerCorrespondences<int>;
template class CheckIfValidBonds<int,int>;
template class GraphSearchSingleIteration<int,int>;
template class SubGraphSearch<int,int>;

