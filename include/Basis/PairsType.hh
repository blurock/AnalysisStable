/*  FILE     PairsType.hh
**  PACKAGE  Pairs
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "Pairs" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 STURM Project, RISC Linz
*/
 
#ifndef STURM_PAIRSTYPE_HH
#define STURM_PAIRSTYPE_HH

/*C BasicPair<T1,T2>  . . . . . . . . . . . . . . . . . .  A pair of elements
**
**  DESCRIPTION
**     The basic pair of objects, I and J
**
**  REMARKS
**
*/
template <class T1, class T2>
class BasicPair
{
public:
  T1 I;
  T2 J;
  // Constructors
       BasicPair(void);
  BasicPair(const T1& i, const T2& j);
  BasicPair(const BasicPair<T1,T2>& p);
  virtual ~BasicPair()
    {
    }
  
  virtual void CopyClone( BasicPair<T1,T2> *pair)
    {
      I = pair->I;
      J = pair->J;
    }
  virtual BasicPair<T1,T2> * Clone()
    {
      BasicPair<T1,T2> *pair = new BasicPair<T1,T2>;
      pair->CopyClone(this);
      return pair;
    }
  virtual ostream& print(ostream& out) const
    {
      out << "(" << I << "," << J << ")";
      return out;
    }
  virtual bool EncodeThis(CommBuffer& buffer)
    {
      bool result = Encode(buffer,I);
      result = result && Encode(buffer,J);
      return result;
    }
  virtual bool DecodeThis(CommBuffer& buffer)
    {
      bool result = Decode(buffer,I);
      result = result && Decode(buffer,J);
      return result;
    }
};            

 
/*C PairList<T1,T2> . . . . . . . . . . . . . . . . . . .  List of BasicPairs
**
**  DESCRIPTION
**     An ObjectList of BasicPairs<T1,T2>.
**     
**  REMARKS
**
*/
template <class T1, class T2>
class PairList : public ObjectList< BasicPair<T1,T2> >
{
public:
     
  // Constructors
  PairList();
  PairList(const int n);
  PairList(const PairList& pairs);
  PairList(const ObjectList<T1> first, const T2& j);
  PairList(const T1& i, const ObjectList<T2> second);
  PairList(const ObjectList<T1>& l1,
           const ObjectList<T2>& l2);

  // Utility Routines
  virtual ObjectList<T1>& VectorOfFirsts(ObjectList<T1>& vec);
  virtual ObjectList<T2>& VectorOfSeconds(ObjectList<T2>& vec);
  virtual void RemoveWithI(const T1& i);
  virtual void OnlyWithI(const T1& i);
  virtual void RemoveWithJ(const T2& j);
  virtual void OnlyWithJ(const T2& j);
};
/*C SetOfPairSets<T1,T2>  . . . . . . . . . . . . . . . .  A list of PairLists
**
**  DESCRIPTION
**     This is a list of PairLists (usually the result of some
**     combinatorial work)
**
**  REMARKS
**
*/
template <class T1, class T2>
class SetOfPairSets : public ObjectList< PairList<T1,T2> >
{
public:
     
  // Constructors
       SetOfPairSets();
  SetOfPairSets(int n);
  SetOfPairSets(const char *title, const char *delim);
  SetOfPairSets(const SetOfPairSets& sets);
  SetOfPairSets(const ObjectList<T1>& set1,
                const ObjectList<T2>& set2);
     
  inline void GenerateSetOfPairSetsWorkOver2(const ObjectList<T1>& set1,
                                             const ObjectList<T2>& set2);
  inline void GenerateSetOfPairSetsWorkOver1(const ObjectList<T1>& set1,
                                             const ObjectList<T2>& set2);
          
  void WithAndWithoutValueI(const PairList<T1,T2>& plist, const T1& value);
  void WithAndWithoutValueJ(const PairList<T1,T2>& plist, const T2& value);
  void IterativeValueI(const PairList<T1,T2>& plist);
  void IterativeValueJ(const PairList<T1,T2>& plist);

  void SetsOfEquivalentI(const ObjectList<T1>& ilist, const PairList<T1,T2>& plist);
  void SetsOfEquivalentJ(const ObjectList<T2>& ilist, const PairList<T1,T2>& plist);
  void Sort();
  bool operator==(const SetOfPairSets<T1,T2>& set)
    {
      return (ObjectList< PairList<T1,T2> >) (*this) ==
        (ObjectList< PairList<T1,T2> >) set;
    }

};

 
/*C SymmetricPair . . . . . . . . . . . . . . . . BasicPair with same element
**
**  DESCRIPTION
**     This is the mirror class of BasicPair in which
**     the pair types are the same
**
**  REMARKS
**
*/
template <class T>
class SymmetricPair : public BasicPair<T,T>
{
public:
     
  SymmetricPair(void);
  SymmetricPair(const T& i, const T& j);
  SymmetricPair(const SymmetricPair<T>& p);
};
/*C SymmetricPairList . . . . . . . . . . . . . . . .  List of SymmetricPairs
**
**  DESCRIPTION
**     This is the mirror class of PairList
**     in which the pair types are the same
**
**  REMARKS
**
*/
template <class T>
class SymmetricPairList : public PairList<T,T>
{
public:
     
  SymmetricPairList(void);
  SymmetricPairList(const int n);
  SymmetricPairList(const SymmetricPairList& pairs);
  SymmetricPairList(const SymmetricPairList* pairs);
  SymmetricPairList(const PairList<T,T>& pairs);
  SymmetricPairList(const T& i, const ObjectList<T> second);
  SymmetricPairList(const ObjectList<T> first, const T& j);
  SymmetricPairList(const ObjectList<T> first,
                           const ObjectList<T> second);
     
  virtual ObjectList<T>& VectorOfBoth(ObjectList<T>& vec);
  virtual void RemoveWithI(const T& i);
  virtual void RemoveWithJ(const T& j);
  virtual void RemoveWithIAndJ(const T& ij);
};
 
/*C SymmetricSetOfPairSets  . . . . . . . . . . . . List of SymmetricPairList
**
**  DESCRIPTION
**      List of Symmetric Pair Lists.  Mainly used in the 
**      generation of permutation of lists
**
**  REMARKS
**
*/
template <class T>
class SymmetricSetOfPairSets : public SetOfPairSets<T,T>
{
public:

  SymmetricSetOfPairSets();
  SymmetricSetOfPairSets(int n);
  SymmetricSetOfPairSets(const char *title, const char *delim);
  SymmetricSetOfPairSets(const SymmetricSetOfPairSets& sets);
  SymmetricSetOfPairSets(const ObjectList<T>& set1,
                                const ObjectList<T>& set2);
};
 
/*C TranslateItoJ . . . . . . . . . . . . . . . . . . . . . Translation Pairs
**
**  DESCRIPTION
**      A translation from I (T1) to J (T2) in the form of a
**      PairList is given.  The operator takes as an
**      argument a T1 and finds the corresponding T2 element
**      (it is assumed that one would not ask for elements not
**      there)
**
**  REMARKS
**     Inheirits SearchableObjectList
**
*/
template <class T1, class T2>
class TranslatePairItoJ : public SearchableObjectListSimple<T1,T2>
{
public:
     
  TranslatePairItoJ();
  TranslatePairItoJ(const TranslatePairItoJ<T1,T2>& translate);
  TranslatePairItoJ(const PairList<T1,T2>& translate);
  T2 operator()(const T1& i);
};
/*C TranslateJtoI . . . . . . . . . . . . . . . . . . . . . Translation Pairs
**
**  DESCRIPTION
**      A translation from J (T2) to I (T1) in the form of a
**      PairList<T1,T2> is given.  The operator takes as an
**      argument a T1 and finds the corresponding T2 element
**      (it is assumed that one would not ask for elements not
**      there)
**
**  REMARKS
**      Inheirits SearchableObjectList<T1,T2>
**
*/
template <class T1, class T2>
class TranslatePairJtoI : public SearchableObjectListSimple<T2,T1>
{
public:
     
  TranslatePairJtoI();
  TranslatePairJtoI(const TranslatePairJtoI<T1,T2>& translate);
  TranslatePairJtoI(const PairList<T1,T2>& translate);
  T1 operator()(const T2& j);
  BasicPair<T1,T2> operator()(const BasicPair<T1,T2>& p);
     
};

 
/*C PairTranslatePairItoJ<T>  . . . . . . . . . . . . . . . . Translate Pairs
**
**  DESCRIPTION
**    A translation from I to J (both of type T) in the form of a
**    SymmetricPairList<T> is given.  The operator is used to translate
**    a SymmetricPair<T> by substituting the I and J of the SymmetricPair
**    by their translation.
**
**  REMARKS
**    Inheirits TranslatePairItoJ<T,T>
**
*/
template <class T>
class PairTranslatePairItoJ : public TranslatePairItoJ<T,T>
{
public:
     
  PairTranslatePairItoJ();
  PairTranslatePairItoJ(const PairTranslatePairItoJ<T>& translate);
  PairTranslatePairItoJ(const SymmetricPairList<T>& translate);
     
  SymmetricPair<T> operator()(const BasicPair<T,T>& spair);
};
/*C PairTranslatePairJtoI<T>  . . . . . . . . . . . . . . . . Translate Pairs
**
**  DESCRIPTION
**    A translation from J to I (both of type T) in the form of a
**    SymmetricPairList<T> is given.  The operator() is used to translate
**    a SymmetricPair<T> by substituting the I and J of the SymmetricPair
**    by their translation.
**
**  REMARKS
**
*/
template <class T>
class PairTranslatePairJtoI : public TranslatePairJtoI<T,T>
{
public:
     
  PairTranslatePairJtoI();
  PairTranslatePairJtoI(const PairTranslatePairJtoI<T>& translate);
  PairTranslatePairJtoI(const SymmetricPairList<T>& translate);
     
  SymmetricPair<T> operator()(const BasicPair<T,T>& spair);
};

 
/*C PairTranslatePairListItoJ<T>  . . . . . . . . . . . .  Translate PairList
**
**  DESCRIPTION
**    A translation from I to J (both of type T) in the form of a
**    SymmetricPairList<T> is given.  The operator() is used to translate
**    a SymmetricPairList<T> by substituting the I and J of each SymmetricPair
**    by their translation.
**
**  REMARKS
**
*/
template <class T>
class PairTranslatePairListItoJ
{
  PairTranslatePairItoJ<T>  Translate;
public:
     
  PairTranslatePairListItoJ();
  PairTranslatePairListItoJ(const PairTranslatePairListItoJ<T>& translate);
  PairTranslatePairListItoJ(const SymmetricPairList<T>& translate);
     
  SymmetricPairList<T> operator()(const SymmetricPairList<T>& spairlist);
};

 
/*C PairTranslatePairListJtoI<T>  . . . . . . . . . . . .  Translate PairList
**
**  DESCRIPTION
**    A translation from J to I (both of type T) in the form of a
**    SymmetricPairList<T> is given.  The operator() is used to translate
**    a SymmetricPairList<T> by substituting the I and J of each SymmetricPair
**    by their translation.
**
**  REMARKS
**
*/
template <class T>
class PairTranslatePairListJtoI
{
  PairTranslatePairJtoI<T>  Translate;
public:
     
  PairTranslatePairListJtoI();
  PairTranslatePairListJtoI(const PairTranslatePairListJtoI<T>& translate);
  PairTranslatePairListJtoI(const SymmetricPairList<T>& translate);
     
  SymmetricPairList<T> operator()(const SymmetricPairList<T>& spairlist);
};
 
 


#endif
