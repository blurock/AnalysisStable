/*  FILE     SubGraph.hh
**  PACKAGE  SubGraph
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "SubGraph" package in the Basis environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef Basis_SUBGRAPH_HH
#define Basis_SUBGRAPH_HH

#ifdef _unix
//#pragma interface
#endif
 
/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "SubGraphType.hh"

template <class KeyType, class T>
ostream& operator<<(ostream& out, 
		    const GraphSearchInfo<KeyType,T>& info);
template <class KeyType, class T>
istream& operator>>(istream& in, 
				     GraphSearchInfo<KeyType,T>& info);
template <class KeyType, class T>
bool operator==(const GraphSearchInfo<KeyType,T>& info1,
		const GraphSearchInfo<KeyType,T>& info2);
template <class KeyType, class T>
bool operator<(const GraphSearchInfo<KeyType,T>& info1, 
	       const GraphSearchInfo<KeyType,T>& info2);
template <class KeyType, class T>
bool Encode(CommBuffer& buffer, GraphSearchInfo<KeyType,T>& graphinfo);
template <class KeyType, class T>
bool Decode(CommBuffer& buffer, GraphSearchInfo<KeyType,T>& graphinfo);

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#include "SubGraph.icc"

#ifdef TEMPLATE_INSTANTIATION
#include "SubGraph.itc"
#endif




/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/



#endif
