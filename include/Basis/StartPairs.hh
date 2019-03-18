/*  FILE     StartPairs.hh
**  PACKAGE  StartPairs
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "StartPairs" package in the Basis environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef Basis_STARTPAIRS_HH
#define Basis_STARTPAIRS_HH

#include "StartPairsType.hh"

/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
template <class T1,class T2>
bool operator<(const EquivalentPairClass<T1,T2>& equiv1,
	       const EquivalentPairClass<T1,T2>& equiv2);
template <class T1,class T2>
bool operator==(const EquivalentPairClass<T1,T2>& equiv1,
		const EquivalentPairClass<T1,T2>& equiv2);
template <class T1,class T2>
ostream& operator<<(ostream& out, const EquivalentPairClass<T1,T2>& equiv);
template <class T1,class T2>
bool Encode(CommBuffer& buffer, EquivalentPairClass<T1,T2>& equiv);
template <class T1,class T2>
bool Decode(CommBuffer& buffer, EquivalentPairClass<T1,T2>& equiv);

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "StartPairs.icc"

#ifdef TEMPLATE_INSTANTIATION
#include "StartPairs.itc"
#endif
 


#endif
