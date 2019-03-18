/*  FILE     FindCorrespondencesType.hh
**  PACKAGE  FindCorrespondences
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "FindCorrespondences" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 Basis Project, RISC Linz
*/
 
#ifndef Basis_FINDCORRESPONDENCESTYPE_HH
#define Basis_FINDCORRESPONDENCESTYPE_HH

/*C CheckIfValidBonds . . . . . . . . . . . . . . . . . check correspondences
**
**  DESCRIPTION
**     For two given graphs, the bond lists are set up.  The
**     operator() procedure takes a single correspondence
**     list, translates the bonds indicies and sees whether
**     the exact same set of bonds are present.
**
**  REMARKS
**
*/
template <class KeyType, class T>
class CheckIfValidBonds
     {
     SymmetricPairList< KeyType > Bonds1;
     SymmetricPairList< KeyType > Bonds2;
 public:     
     CheckIfValidBonds();
     CheckIfValidBonds(const CheckIfValidBonds<KeyType,T>& valid);
     CheckIfValidBonds(const Graph<KeyType,T>& graph1,
		       const Graph<KeyType,T>& graph2);
     bool operator()(const SymmetricPairList<KeyType>& plist);
     };
  
/*C IsolateCorrespondencesFromGraphInfo . . . . . . . . . get correspondences
**
**  DESCRIPTION
**
**  REMARKS
**
*/
template <class KeyType, class T>
class IsolateCorrespondencesFromGraphInfo
     {
 public:
     SymmetricPairList<KeyType> operator()(const GraphSearchInfo<KeyType,T>& info);
     };
/*C FilterOutSmallerCorrespondences . . . . . . . . .  filter correspondences
**
**  DESCRIPTION
**
**  REMARKS
**
*/
template <class KeyType>
class FilterOutSmallerCorrespondences
     {
     unsigned int ProperSize;
 public:
     FilterOutSmallerCorrespondences(int n);
     bool operator()(const SymmetricPairList<KeyType>& plist);
     };

/*C FindSubGraphCorrespondences
**
**  DESCRIPTION
**
**  REMARKS
**
*/
template <class KeyType, class T>
class FindSubGraphCorrespondences
     {
     FindStartPairs<KeyType,T> Starts;
     SubGraphSearch<KeyType,T> Search;
     FilterOutSmallerCorrespondences<KeyType> EnoughCheck;
     CheckIfValidBonds<KeyType,T> BondCheck;
     
 public:
     SymmetricSetOfPairSets<KeyType> Correspondences;
     FindSubGraphCorrespondences(const FindSubGraphCorrespondences<KeyType,T>& corr);
     FindSubGraphCorrespondences(const Graph<KeyType,T>& graph1,
				 const Graph<KeyType,T>& graph2);
     void FindBasicCorrespondences();
     void FilterOutSmallCorrespondences();
     void FilterIfNotEnoughBonds();
     
     };


#endif
