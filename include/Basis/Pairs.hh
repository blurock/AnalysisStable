/*  FILE     Pairs.hh
**  PACKAGE  Pairs
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Definitions for the "Pairs" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 Reaction, Edward S. Blurock
*/

#ifndef PAIRS_HH
#define PAIRS_HH
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#ifdef _msdos_stl
// #include "relation.hh"
#include <iostream>
#include <vector>
// #include <algorithm>
#include <functional>
#include <list>
using namespace std;
#pragma warning(disable:4786)
#endif


#ifdef _unix
#include "STL.h"
#endif

#include "defines.hh"
#include "PairsType.hh"
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
template <class T1, class T2>
bool operator==(const BasicPair<T1,T2>& pair1, const BasicPair<T1,T2>& pair2);
template <class T1, class T2>
bool operator<(const BasicPair<T1,T2>& pair1, const BasicPair<T1,T2>& pair2);
template <class T1, class T2>
ostream& operator<<(ostream& out, const BasicPair<T1,T2>& p);
template <class T1, class T2>
istream& operator>>(istream& in, const BasicPair<T1,T2>& p);
template <class T1, class T2>
bool Encode(CommBuffer& buffer, BasicPair<T1,T2>& p);
template <class T1, class T2>
bool Decode(CommBuffer& buffer, BasicPair<T1,T2>& p);
 
template <class T>
bool operator==(const SymmetricPair<T>& pair1, const SymmetricPair<T>& pair2);
template <class T>
bool operator<(const SymmetricPair<T>& pair1, const SymmetricPair<T>& pair2);
template <class T>
bool operator>(const SymmetricPair<T>& pair1, const SymmetricPair<T>& pair2);
template <class T>
ostream& operator<<(ostream& out, const SymmetricPair<T>& p);
template <class T>
istream& operator>>(istream& in, const SymmetricPair<T>& p);
template <class T1>
bool Encode(CommBuffer& buffer, SymmetricPair<T1>& p);
template <class T1>
bool Decode(CommBuffer& buffer, SymmetricPair<T1>& p);
 
template <class T1, class T2>
istream& operator>>(istream& in, const PairList<T1,T2>& p);
template <class T1, class T2>
ostream& operator<<(ostream& out, const PairList<T1,T2>& p);
template <class T1, class T2>
bool operator<(const PairList<T1,T2>& l1, const PairList<T1,T2>& l2);
template <class T1, class T2>
bool Encode(CommBuffer& buffer, PairList<T1,T2>& p);
template <class T1, class T2>
bool Decode(CommBuffer& buffer, PairList<T1,T2>& p);
template <class T1>
bool Encode(CommBuffer& buffer, SymmetricPairList<T1>& p);
template <class T1>
bool Decode(CommBuffer& buffer, SymmetricPairList<T1>& p);

template <class T1, class T2>
bool operator==(const SetOfPairSets<T1,T2>& s1, const SetOfPairSets<T1,T2>& s2);
template <class T1, class T2>
bool operator<(const SetOfPairSets<T1,T2>& s1, const SetOfPairSets<T1,T2>& s2);
template <class T1, class T2>
SymmetricSetOfPairSets<T1> CombineEquivalentJ(SetOfPairSets<T1,T2>& set1,
					      SetOfPairSets<T1,T2>& set2);
template <class T1, class T2>
SymmetricSetOfPairSets<T1> CombineEquivalentJ(SetOfPairSets<T1,T2>& set1,
					      SetOfPairSets<T1,T2>& set2);

template <class T>
bool operator==(const SymmetricSetOfPairSets<T>& s1, const SymmetricSetOfPairSets<T>& s2);
template <class T>
bool operator<(const SymmetricSetOfPairSets<T>& s1, const SymmetricSetOfPairSets<T>& s2);
template <class T1, class T2>
bool operator==(const PairList<T1,T2>& l1, const PairList<T1,T2>& l2);
template <class T>
ostream& operator<<(ostream& out, const SymmetricSetOfPairSets<T>& set);
template <class T>
istream& operator>>(istream& in, SymmetricSetOfPairSets<T>& set);
template <class T1, class T2>
bool Encode(CommBuffer& buffer, SetOfPairSets<T1,T2>& p);
template <class T1, class T2>
bool Decode(CommBuffer& buffer, SetOfPairSets<T1,T2>& p);
template <class T1>
bool Encode(CommBuffer& buffer, SymmetricSetOfPairSets<T1>& p);
template <class T1>
bool Decode(CommBuffer& buffer, SymmetricSetOfPairSets<T1>& p);

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "BasicPair.icc"
#include "PairList.icc"
#include "SetOfPairSets.icc"
#include "PairTranslate.icc"
#include "SymmetricPair.icc"
#include "SymmetricPairList.icc"
#include "SymmetricSetOfPairsSets.icc"

#ifdef TEMPLATE_INSTANTIATION
#include "BasicPair.itc"
#include "PairList.itc"
#include "SymmetricPairs.itc"
#include "PairsEncodeDecode.itc"
#endif

#endif
