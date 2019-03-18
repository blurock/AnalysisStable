/*  FILE     PairTranslate_INT.cc
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
#include <utility>


#ifdef _unix
template class BasicPair<Identify,Identify>;
template class list<BasicPair<Identify, Identify> >;

template class list<BasicPair<String, String> >;
template class list<BasicPair<double, double> >;

template class PairList<Identify,Identify>;
template class SetOfPairSets<Identify,Identify>;
template class SymmetricPair<Identify>;
template class SymmetricPairList<Identify>;
template class SymmetricSetOfPairSets<Identify>;

#endif

template bool Encode(CommBuffer&, PairList<Identify,Identify>&);
template bool Decode(CommBuffer&, PairList<Identify,Identify>&);
template bool operator==(PairList<Identify, Identify> const &, PairList<Identify, Identify> const &);
template bool operator<(PairList<Identify, Identify> const &, PairList<Identify, Identify> const &);
template ostream& operator<<(ostream &, PairList<Identify, Identify> const &);
template bool Encode(CommBuffer &, BasicPair<double, double> &);
template bool Decode(CommBuffer &, BasicPair<double, double> &);
template ostream& operator<<(ostream &, BasicPair<double, double> const &);
template bool Encode(CommBuffer &, BasicPair<Identify, Identify> &);
template bool Decode(CommBuffer &, BasicPair<Identify, Identify> &);
template ostream& operator<<(ostream &, BasicPair<Identify, Identify> const &);



template bool Encode(CommBuffer &, PairList<int, int> &);
template bool Decode(CommBuffer &, PairList<int, int> &);

template bool operator==(PairList<int, int> const &, PairList<int, int> const &);
template bool operator<(PairList<int, int> const &, PairList<int, int> const &);
template bool operator==(BasicPair<int, int> const &, BasicPair<int, int> const &);

template bool operator<(BasicPair<int, int> const &, BasicPair<int, int> const &);

template ostream& operator<<(ostream &, PairList<int, int> const &);
