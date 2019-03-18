/*  FILE     GraphSearch_INT.cc
**  PACKAGE     REACTION    
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    
**
**  REFERENCES
**
**  COPYRIGHT (C) 1995  REACTION Project / Edward S. Blurock 
*/
#define TEMPLATE_INSTANTIATION
#include "BasisSystem.hh"
#include "Pairs.hh"
#include "Graph.hh"
#include "SubGraph.hh"

#define GRAPHSEARCH_KEYTYPE int
#define GRAPHSEARCH_T int
template class ObjectList<int>;
template class FormNextNode<GRAPHSEARCH_KEYTYPE,GRAPHSEARCH_T>;
template class Graph<GRAPHSEARCH_KEYTYPE,GRAPHSEARCH_T>;
template class GraphSearch<GRAPHSEARCH_KEYTYPE,GRAPHSEARCH_T>;
template class GraphSearchInfo<GRAPHSEARCH_KEYTYPE,GRAPHSEARCH_T>;

#undef GRAPHSEARCH_KEYTYPE
#undef GRAPHSEARCH_T
