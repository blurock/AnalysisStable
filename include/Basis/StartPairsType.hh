/*  FILE     StartPairsType.hh
**  PACKAGE  StartPairs
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "StartPairs" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 Basis Project, RISC Linz
*/
 
#ifndef Basis_STARTPAIRSTYPE_HH
#define Basis_STARTPAIRSTYPE_HH

/*C GroupEquivalentJWork  . . . . . . . . . . . . . . . . . . . . only with J
**
**  DESCRIPTION
**     The class is initialized with a given pair list.  Each call
**     to the operator() with a J value will return those
**     pairs (in a PairList) which have that value of J.
**
**  REMARKS
**
*/
template <class T1,class T2>
class GroupEquivalentJWork
     {
 public:
     
     PairList<T1,T2> Pairs;
     
     GroupEquivalentJWork();
     GroupEquivalentJWork(GroupEquivalentJWork<T1,T2>& work);
     GroupEquivalentJWork(PairList<T1,T2> pairs);
     PairList<T1,T2> operator()(T1& j);
     };
/*C GraphPairInfo . . . . . . . . . . . . . . . . . . information about Graph
**
**  DESCRIPTION
**     Information about the graph for graph search
**     - NodeList is the list of indicies
**     - ValueList is the corresponding list of node values
**     - GraphPairs is the index-value pairs
**
**  REMARKS
**
*/
template <class KeyType,class T>
class GraphPairInfo
{
public:
  
  Graph<KeyType,T> Graph1;
  ObjectList< KeyType > NodeList;
  ObjectList< T > ValueList;
  PairList<KeyType,T> GraphPairs;
  
  GraphPairInfo();
  GraphPairInfo(const GraphPairInfo& inf1);
  GraphPairInfo(const Graph<KeyType,T>& gr1);
  GraphPairInfo(const Graph<KeyType,T>& gr, const ObjectList< KeyType >& nlist);
  void SetUp();
};

 
/*C EquivalentPairClass . . . . . . . . . . . . . . . . . . . paired elements
**
**  DESCRIPTION
**    Two pairlists, each with equivalent J values, are grouped by this 
**    class.  The I elements are isolated into two lists (Elements1 and 
**    Elements2).  The SizeScore is the product of the sizes of these
**    lists.  The ClassValue is the common J value of all.
**
**    The purpose of this class is to take derived pair lists,
**    where the first element is the index and the second element
**    is the value, and to pair those with the same value.  
**   
**  REMARKS
**
*/
template <class T1,class T2>
class EquivalentPairClass
{
public:
  
  T2 ClassValue;
  int SizeScore;
  ObjectList<T1> Elements1;
  ObjectList<T1> Elements2;
  
  EquivalentPairClass();
  EquivalentPairClass(const EquivalentPairClass<T1,T2>& equiv);
  EquivalentPairClass(PairList<T1,T2> element1,
		      PairList<T1,T2> element2);
  virtual ~EquivalentPairClass()
    {
    }
  
     virtual void CopyClone(EquivalentPairClass<T1,T2> *equiv)
	  {
	  *this = *equiv;
	  }
     virtual EquivalentPairClass<T1,T2> * Clone()
	  {
	  EquivalentPairClass<T1,T2> *equiv = new EquivalentPairClass<T1,T2>;
	  equiv->CopyClone(this);
	  return equiv;
	  }
     virtual ostream& print(ostream& out) const
	  {
	  out << "EquivalentPairClass[" << ClassValue;
	  out << "," << SizeScore << "]\n";
	  out << Elements1 << "\n";
	  out << Elements2 << "\n";
	  return out;
	  }
     virtual bool EncodeThis(CommBuffer& buffer)
	  {
	  bool result = Encode(buffer,ClassValue);
	  result = result && Encode(buffer,SizeScore);
	  result = result && Elements1.EncodeThis(buffer);
	  result = result && Elements2.EncodeThis(buffer);
	  return result;
	  }
     virtual bool DecodeThis(CommBuffer& buffer)
	  {
	  bool result = Decode(buffer,ClassValue);
	  result = result && Decode(buffer,SizeScore);
	  result = result && Elements1.DecodeThis(buffer);
	  result = result && Elements2.DecodeThis(buffer);
	  return result;
	  }
     };
 
/*C CreateEquivalentPairClass . . . . . . . . . .  set up EquivalentPairClass
**
**  DESCRIPTION
**    The operator() procedure takes two pair lists (with equivalent J
**    values) and creates the EquivalentPairClass class.
**
**  REMARKS
**
*/
template <class T1,class T2>
class CreateEquivalentPairClass 
     {
 public:
     EquivalentPairClass<T1,T2> 
	  operator()(const PairList<T1,T2> element1,
		     const PairList<T1,T2> element2);
     };
/*C FindStartPairs  . . . . . . . . . . . . . . . . . . . . . . . start pairs
**
**  DESCRIPTION
**     The start pairs, given two graphs (and node lists if desired),
**     for use in subgraph search are found.  The computations
**     are made upon the class constuction and the pair list
**     is given with GetStartPairList()
**
**  REMARKS
**
*/
template <class KeyType,class T>
class FindStartPairs 
     {
 public:
     
     GraphPairInfo<KeyType,T> Info1;
     GraphPairInfo<KeyType,T> Info2;

     ObjectList< EquivalentPairClass<KeyType,T> > EquivalentElements;

     FindStartPairs();
     FindStartPairs(const FindStartPairs& findstart);
     FindStartPairs(const Graph<KeyType,T>& graph1,
		    const Graph<KeyType,T>& graph2);
     FindStartPairs(const Graph<KeyType,T>& graph1,
		    const ObjectList< KeyType > nodelist1,
		    const Graph<KeyType,T>& graph2,
		    const ObjectList< KeyType > nodelist2);
     void SetUp();
     SymmetricSetOfPairSets<KeyType> GetStartPairListFull();
     SymmetricPairList<KeyType> GetStartPairList();
     };
 

#endif
