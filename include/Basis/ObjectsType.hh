/*  FILE     ObjectsType.hh
**  PACKAGE  Objects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "Objects" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 STURM Project, RISC Linz
*/
 
#ifndef BASIS_OBJECTSTYPE_HH
#define BASIS_OBJECTSTYPE_HH

/*C Identify  . . . . . . . . . . . . . . . . . . . . . . . . . . id and name
**
**  DESCRIPTION
**    The basic class with  a name and an id:
**    - NameTag is the String name
**    - Identification is the int id.
**
**  REMARKS
**
*/
class Identify
{
public:
  INDEX Identification;
  String NameTag;
  inline Identify();
  inline Identify(const INDEX id, const String& name);
  inline Identify(const INDEX id);
  inline Identify(const String name);
  inline Identify(const Identify& id);

  virtual void CopyClone(Identify* id)
    {
      Identification = id->Identification;
      NameTag = id->NameTag;
    }
  virtual Identify* Clone()
    {
      Identify* id = new Identify(Identification,NameTag);
      return id;
    }
  virtual ostream& print(ostream& out) const
    {
      out << "[";
      out << Identification;
      out << ',';
      out << NameTag;
      out << ']';
      return out;
    }
  virtual bool EncodeThis(CommBuffer& buffer)
    {
      bool result = Encode(buffer, Identification);
      result = result && Encode(buffer,NameTag);
      return result;
    }
  virtual bool DecodeThis(CommBuffer& buffer)
    {
      bool result = Decode(buffer, Identification);
      result = result && Decode(buffer,NameTag);
      return result;
    }
  virtual ~Identify(){}
};
 
 
/*C EncodeObjectList  . . . . . . . . . . . . . . . . Encode the class object
**
**  DESCRIPTION
**
**  REMARKS
**
*/
template <class T> 
class EncodeObjectList
{
  bool result;
     
public:
  EncodeObjectList()
    : result(true)
    {
    }
     
               
  CommBuffer& operator()(CommBuffer& buffer, T& object)
    {
      result = result && Encode(buffer,object);
      return buffer;
    }
};
/*C DecodeObjectList  . . . . . . . . . . . . . . . . .  decodes class object
**
**  DESCRIPTION
**     This is set up with the buffer
**
**  REMARKS
**
*/
template <class T>
class DecodeObjectList
{
     
  CommBuffer& Buffer;
  bool result;
     
public:
  DecodeObjectList(CommBuffer& buffer)
    : Buffer(buffer), result(true)
    {
    }
  bool Successful()
    {
      return result;
    }
     
  T operator()()
    {
      T* object = new T;
      result = result && Decode(Buffer,*object);
      return *object;
    }
};
/*C Objectlist<T> . . . . . . . . . . . . . . . . . . . .  class of vector<T>
**
**  DESCRIPTION
**     This is the class of a list (set) of objects.  It is based on the 
**     STL vector class.  Whenever a list or set of objects are needed
**     within the REACTION system, this class should be used.  Standard
**     operations of listing, removing, adding, etc. are included in this class.
**
**  REMARKS
**     Based on STL list class for now
**
*/
template <class T>
class ObjectList : public list< T >
{
  String Title;
  String Delimitor;
     
public:     
     
  // Constructors
       inline ObjectList();
  inline ObjectList(const String& title, const String& delimitor);
  inline ObjectList(const char *title, const char *delimitor);
  inline ObjectList(const int n);
  inline ObjectList(const ObjectList<T>& olist);
  virtual ~ObjectList(){}

  virtual void CopyClone(ObjectList<T> *object)
    {
      Title = object->Title;
      Delimitor = object->Delimitor;
      copy(object->begin(),
           object->end(),
           back_insert_iterator< ObjectList<T> >(*this));
    }
     
  virtual ObjectList<T> * Clone()
    {
      ObjectList<T> *newobject = new ObjectList<T>;
      newobject->CopyClone(this);
      return newobject;
    }
  virtual ostream& print(ostream& out) const
    {
      String temp;
      temp = (String) Delimitor;
          
      ostream_iterator< T > iter(out,(char *) temp.c_str());
          
      out << Title;
      copy((*this).begin(),(*this).end(),iter);
          
      return out;
    }
  virtual bool EncodeThis(CommBuffer& buffer)
    {
      int siz = (*this).size();
          
      bool result = Encode(buffer,Title);
      result = result && Encode(buffer,Delimitor);
          
      result = result && Encode(buffer,siz);
      typename ObjectList<T>::iterator iter;
      for(iter = (*this).begin();
          !(iter == (*this).end());
          iter++)
        {
          result = result && Encode(buffer,*iter);
        }
      return result;
    }
          
  virtual bool DecodeThis(CommBuffer& buffer)
    {
      int size = 0;
          
      bool result = Decode(buffer,Title);
      result = result && Decode(buffer,Delimitor);
      result = result && Decode(buffer,size);
      for(int iter = 0;
          iter != size;
          iter++)
        {
          T* object = new T;
          result = result && Decode(buffer,*object);
          (*this).AddObject(*object);
        }
      return result;
    }
  // Utility Operations
       inline void ChangeTitle(const String& title);
  inline void ChangeDelimitor(const String& title);
  // Modifying Functions
       inline void AddObject(const T& newobject);
  inline void RemoveObject(const T& newobject);
  inline void Remove(const ObjectList<T>& toremove);
  inline void Unique(void);
  inline void Sort(void);
  inline void AddObjectIfNotThere(const T& newobject);
  inline void AddOnlyUniqueObjects(const ObjectList<T>& olist);
  inline void Intersected(const ObjectList<T>& intersect);
};     
     
/*C SearchableObjectList  . . . . . . . . . . . . . . . . . . Searchable List
**
**  DESCRIPTION
**      A list of objects where the referencing
**      is done through a key.
**
**  REMARKS
**    Based on the STL map< KeyType,T,less<KeyType> >
**
*/
template <class KeyType, class T>
class SearchableObjectList : public map< KeyType,T,less<KeyType> >
{
public:     
  String Title;
  String Delimitor;
  unsigned int OutputFlag;
     
  SearchableObjectList();
  SearchableObjectList(const SearchableObjectList<KeyType,T>& slist);
  virtual ~SearchableObjectList()
    {
    }
  inline void ChangeOutputFlag(const unsigned int flag);
  inline void ChangeDelimitor(const String& delim);
  inline void ChangeTitle(const String& title);
     
  virtual void CopyClone(SearchableObjectList<KeyType,T> *slist)
    {
      *this = *slist;
    }
  virtual SearchableObjectList<KeyType,T> *Clone()
    {
      SearchableObjectList<KeyType,T> *newlist 
        = new SearchableObjectList<KeyType,T>(*this);
      return newlist;
    }
     
  bool AddObject(const KeyType &key,
                 T &value);
  void RemoveObject(const KeyType& key);
     
};
 
/*C
**
**  DESCRIPTION
**
**  REMARKS
**
*/
template <class KeyType, class T>
class SearchableObjectListSimple : public SearchableObjectList<KeyType,T>
{
public:
  SearchableObjectListSimple();
  SearchableObjectListSimple(const SearchableObjectListSimple<KeyType,T>& slist);
  virtual ~SearchableObjectListSimple()
    {
    }
     
  virtual bool EncodeThis(CommBuffer& buffer);
  virtual bool DecodeThis(CommBuffer& buffer);
     
  virtual ostream& print(ostream& out) const
    {
      typename map< KeyType,T,less<KeyType> >::const_iterator iter;
      out << (*this).Title;
      
      for(iter = (*this).begin(); iter != (*this).end(); iter++)
        {
          switch((*this).OutputFlag)
            {
            case SEARCHABLE_KEYWORD:
              out << (*iter).first;
              break;
            case SEARCHABLE_OBJECT:
              out << (*iter).second;
              break;
            case SEARCHABLE_BOTH:
              out << "[" << (*iter).first << "] = ";
              out << (*iter).second;
              break;
            }
          out << (*this).Delimitor;
        }
      return out;
    }
};
 
/*C
**
**  DESCRIPTION
**
**  REMARKS
**
*/
template <class KeyType, class T>
class SearchableObjectListFull : public SearchableObjectList<KeyType,T>
{
public:  
  SearchableObjectListFull();
  SearchableObjectListFull(const SearchableObjectListFull<KeyType,T>& slist);
  virtual ~SearchableObjectListFull()
    {
    }
     
  virtual bool EncodeThis(CommBuffer& buffer);
  virtual bool DecodeThis(CommBuffer& buffer);
     
  virtual ostream& print(ostream& out) const
    {
      typename map< KeyType,T,less<KeyType> >::const_iterator iter;
      out << (*this).Title;
      
      for(iter = (*this).begin(); iter != (*this).end(); iter++)
        {
          switch((*this).OutputFlag)
            {
            case SEARCHABLE_KEYWORD:
              (*iter).first.print(out);
              break;
            case SEARCHABLE_OBJECT:
              (*iter).second.print(out);
              break;
            case SEARCHABLE_BOTH:
              out << "[";
	      (*iter).first.print(out);
	      out << "] = ";
              (*iter).second.print(out);
              break;
            }
          out << (*this).Delimitor;
        }
      return out;
    }
};

class ObjectListString : public ObjectList<String> {  
public:
  ObjectListString(const String& title, const String& delimitor)
    : ObjectList<String>(title,delimitor) {}
  ObjectListString(const char *title, const char *delimitor) 
    : ObjectList<String>(title,delimitor) {}
  ObjectListString(const int n) 
    : ObjectList<String>(n) {}
  ObjectListString(const ObjectList<String>& olist)
    : ObjectList<String>(olist) {}
      
};

 
#endif

