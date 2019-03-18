/*  FILE     Graphs.h
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
#ifndef GRAPH_H
#define GRAPH_H

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#ifdef _msdos_stl
#include <iostream>
#include <vector>
#include <ALGORITHM>
#include <functional>
// #include <numeric>
using namespace std;
#pragma warning(disable:4786)
#endif


#ifdef _unix
#include "STL.h"
#endif

#include "defines.hh"
#include "GraphType.hh"

/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
template <class KeyType, class T>
bool operator==(GraphNode<KeyType,T>& node1, 
		GraphNode<KeyType,T>& node2);
template <class KeyType, class T>
bool operator==(GraphNode<KeyType,T>& node,
		T& value);
template <class KeyType, class T>
bool operator<(GraphNode<KeyType,T>& node1, 
	       GraphNode<KeyType,T>& node2);
template <class KeyType, class T>
ostream& operator<<(ostream& out, const GraphNode<KeyType,T>& node);
template <class KeyType, class T> 
ostream& operator<<(ostream& out, const Graph<KeyType,T>& graph);     
template <class KeyType, class T>
bool Encode(CommBuffer& buffer, GraphNode<KeyType,T>& graph);
template <class KeyType, class T>
bool Decode(CommBuffer& buffer, GraphNode<KeyType,T>& graph);
template <class KeyType, class T>
bool Encode(CommBuffer& buffer, Graph<KeyType,T>& graph);
template <class KeyType, class T>
bool Decode(CommBuffer& buffer, Graph<KeyType,T>& graph);
template <class KeyType, class T>
void GraphOut(ostream& out,
	      Graph<KeyType,T>& graph,
	      bool printKey,
	      bool printValue);

#include "Graph.icc"
#ifdef TEMPLATE_INSTANTIATION
#include "Graph.itc"
#include "GraphOut.itc"
#endif

#endif
