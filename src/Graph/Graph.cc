/*  FILE     
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
 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#define TEMPLATE_INSTANTIATION
#include "BasisSystem.hh"
#include "Pairs.hh"
#include "Graph.hh"

 
 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#ifdef _unix
template class GraphNodeOut<Identify,Identify>;
template class GraphBondOut<Identify>;
template class GraphNodeToPair<Identify,Identify>;
template class GetGraphNodeValue<Identify,Identify>;
template class GetGraphNodeKey<Identify,Identify>;
template class RemoveAsParent<Identify,Identify>;
template class RemoveAsSon<Identify,Identify>;
template struct KeyOfMatchingValue<Identify,Identify>;
#endif
template bool Encode(CommBuffer &, GraphNode<Identify, Identify> &);
template bool Decode(CommBuffer &, GraphNode<Identify, Identify> &);
template ostream& operator<<(ostream &, GraphNode<Identify, Identify> const &);
