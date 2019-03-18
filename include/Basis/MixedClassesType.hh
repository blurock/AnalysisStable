/*  FILE     MixedClassesType.hh
**  PACKAGE  MixedClasses
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "MixedClasses" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 STURM Project, RISC Linz
*/
 
#ifndef STURM_MIXEDCLASSESTYPE_HH
#define STURM_MIXEDCLASSESTYPE_HH

/*C PntrMixed<ObjectID,BaseClass> . . . . . . . . . . . . . . . pointer class
**
**  DESCRIPTION
**     This class holds ObjectID (the key to find the object)
**     the pointer to the BaseClass (the object to be stored).
**     It is this class that is in the list of objects.
**
**  REMARKS
**
*/
template <class ObjectID, class BaseClass>
class PntrMixed
     {
 public:
     BaseClass* Pntr;
     ObjectID ID;
     String StructureName;
     
     PntrMixed();
     PntrMixed(const ObjectID& id, BaseClass* object,
	       const String& name);
     PntrMixed(const PntrMixed& mixed);
     virtual ~PntrMixed();
     virtual ostream& print(ostream& out) const;
     virtual bool EncodeThis(CommBuffer& buffer);
     virtual bool DecodeThis(CommBuffer& buffer);
     
     inline void ChangeID(const ObjectID& id);
     inline void CopyClone(const PntrMixed* pntr);
     inline PntrMixed* Clone() const;
     };
/*C SearchableListOfMixedObjects  . . . . . . . . . . . . the list of objects
**
**  DESCRIPTION
**     This is a class of SearchableObjectList with the template ObjectID
**     as the key to access and PntrMixed as the object.  The PntrMixed
**     has the pointer to mixed object to be stored.
**
**     The following are the basic access routines:
**     - AddObject adds the object to the list
**     - RemoveObject takes the object away
**     - GetPointerToObject gives a pointer to the object being stored
**
**     The object being stored has to inheirit the template class BaseClass
**
**  REMARKS
**
*/
template <class ObjectID, class BaseClass>
class SearchableListOfMixedObjects 
: public SearchableObjectListFull< ObjectID, PntrMixed< ObjectID, BaseClass > >
{
public:
  
  inline SearchableListOfMixedObjects();
  inline bool AddObject(const ObjectID& id, 
			BaseClass* object,
			const String& name);
  inline BaseClass* GetPointerToObject(const ObjectID &id);
  inline void RemoveObject(const ObjectID &id);
};
/*C PropertyTypeIdentify<T> . . . . . . . . . . . . . . .  Access by Identify
**
**  DESCRIPTION
**     This class is a standard class holding the object to be stored.  
**     It is a subclass of Identify, which will be used for access.  It
**     is this class that will be held as a pointer in the PntrMixed class
**
**  REMARKS
**
*/
template <class T>
class PropertyType : public Identify
     {
 public:
     
     T Object;
     inline PropertyType();     
     inline PropertyType(const PropertyType& prop);
     inline PropertyType(const String& name, 
			 T& object);
     inline PropertyType(const int id, T& object);     
       //virtual void CopyClone(PropertyType<T> *prop)
       virtual void CopyClone(Identify *iden)
	  {
	    PropertyType<T> *prop = (PropertyType<T> *) iden;
	  Identification = prop->Identification;
	  NameTag = prop->NameTag;
	  Object = prop->Object;
	  }
     virtual Identify * Clone()
	  {
	  PropertyType<T>* prop = new PropertyType<T>;
	  prop->CopyClone(this);
	  return prop;
	  }
     virtual ostream& print(ostream& out) const
	  {
	  out << (Identify) *this;
	  out << " -- ";
	  out << Object;
	  out << "\n";
	  return out;
	  }
     virtual bool EncodeThis(CommBuffer& buffer)
	  {
	  bool result = Encode(buffer,this->Identification);
	  result = result && Encode(buffer,this->NameTag);
	  result = result && Encode(buffer,Object);
	  return result;
	  }
     virtual bool DecodeThis(CommBuffer& buffer)
	  {
	  bool result = Decode(buffer,this->Identification);
	  result = result && Decode(buffer,this->NameTag);
	  result = result && Decode(buffer,Object);
	  return result;
	  }
	  
     };
/*C PropertyTypeByID<T> . . . . . . . . . . . . . . . . Access by Property ID
**
**  DESCRIPTION
**     The PropertyType class can only be accessed by a numeric id.  
**     The NameTag defaults to the empty string.  As in PropertyType, 
**     this class inherits Identify and it stores the object of type T.
**
**  REMARKS
**
*/
template <class T>
class PropertyTypeByID : public Identify
     {
 public:
     
     T Object;
     inline PropertyTypeByID();
     inline PropertyTypeByID(const PropertyTypeByID& prop);
     inline PropertyTypeByID(const int id, T& object); 
     virtual void CopyClone(Identify *iden);
	//error C2555: overriding virtual function differs... 
     virtual Identify * Clone();
     virtual ostream& print(ostream& out) const
	  {
	  out << Identification;
	  out << " -- ";
	  out << Object;
	  out << "\n";
	  return out;
	  }
     virtual bool EncodeThis(CommBuffer& buffer)
	  {
	  bool result = Encode(buffer,Identification);
	  result = result && Encode(buffer,Object);
	  return result;
	  }
     virtual bool DecodeThis(CommBuffer& buffer)
	  {
	  bool result = Decode(buffer,Identification);
	  result = result && Decode(buffer,Object);
	  return result;
	  }
     };
/*C PropertyTypeByName<T> . . . . . . . . . . . . . . Access by Property Name
**
**  DESCRIPTION
**
**  REMARKS
**
*/
template <class T>
class PropertyTypeByName : public Identify
     {
 public:
     
     T Object;
     inline PropertyTypeByName();
     inline PropertyTypeByName(const PropertyTypeByName& prop);
     inline PropertyTypeByName(const String& name, T object) ;
     inline PropertyTypeByName(const char* name, T object);     
       //virtual void CopyClone(PropertyTypeByName *prop)  
       virtual void CopyClone(Identify *iden) {
	    PropertyTypeByName<T> *prop = (PropertyTypeByName *) iden;
	  Identification = 0;
	  NameTag = prop->NameTag;
	  Object = prop->Object;
	  }
	  
     virtual Identify * Clone()
	  {
//	  cout << "PropertyTypeByName  ";
//	  cout << Object << "\n";
	  
	  PropertyTypeByName<T>* prop = new PropertyTypeByName<T>();
	  prop->CopyClone(this);
	  return prop;
	  }
     virtual ostream& print(ostream& out) const
	  {
	  out << "-----  ";
	  
	  out << NameTag;
	  out << "  -----\n";
	  out << Object;
	  out << "\n";
	  return out;
	  }
     virtual bool EncodeThis(CommBuffer& buffer)
	  {
//	  cout << "Encode: PropertyTypeByName\n";
	  bool result = Encode(buffer,NameTag);
	  result = result && Encode(buffer,Object);
	  return result;
	  }
     virtual bool DecodeThis(CommBuffer& buffer)
	  {
//	  cout << "Decode: PropertyTypeByName\n";
	  bool result = Decode(buffer,NameTag);
	  result = result && Decode(buffer,Object);
	  return result;
	  }
     };
/*C PropertyListByIdentify  . . . . . . . . . . . . . .  using Identify class
**
**  DESCRIPTION
**     This is a property list in which the object and the key inherit
**     the identity class.  It is meant to be used in conjuction with 
**     the PropertyType classes listed (PropertyType, PropertyTypeByID and
**     PropertyTypeByName).
**
**     The RemoveObject and GetPointerToObject are inherited.  Only
**     AddObject is a special case of this class
**
**  REMARKS
**
*/
class PropertyListByIdentify 
: public SearchableListOfMixedObjects<Identify,Identify>
     {
 public:
     inline PropertyListByIdentify();     
     inline bool AddObject(Identify* object,const String& name);
     };
/*C PropertyListByName  . . . . . . . . . . . . . . . .  using Identify class
**
**  DESCRIPTION
**    The object to be stored inherits Identify, but the list here only
**    uses the name portion to access them.  The main use should be in
**    conjunction with the PropertyTypeByName class
**
**  REMARKS
**
*/
class PropertyListByName 
: public SearchableListOfMixedObjects<Identify,Identify>
     {
 public:
     inline PropertyListByName(); 
     inline Identify* GetPointerToProperty(const String& name);
     inline bool AddObject(Identify* object,const String& name);
     };
/*C PropertyListByID  . . . . . . . . . . . . . . . . .  using Identify class
**
**  DESCRIPTION
**    The object to be stored inherits Identify, but the list here only
**    uses the id portion to access them.  The main use should be in
**    conjunction with the PropertyTypeByID class
**
**  REMARKS
**
*/
class PropertyListByID
: public SearchableListOfMixedObjects<Identify,Identify>
     {
 public:
     inline PropertyListByID();
     inline bool AddObject(Identify* object, const String& name);
     inline Identify* GetPointerToProperty(const int id);     
     };
 
/*C SingleDecodeRoutine
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class SingleDecodeRoutine
     {
 public:
     
     String StructureName;
     bool (*Routine)(CommBuffer&,Identify*&);
     
     SingleDecodeRoutine()
	  : StructureName(""),
	    Routine(0)
	  {
	  }
     
     SingleDecodeRoutine(const String& name,
			 bool (*&routine)(CommBuffer&,Identify*&))
	  : StructureName(name),Routine(routine)
	       {
	       }
     SingleDecodeRoutine(const SingleDecodeRoutine& decode)
	  : StructureName(decode.StructureName),Routine(decode.Routine)
	       {
	       }
     ostream& print(ostream& out) const
	  {
	  out << StructureName;
	  return out;
	  }
     
	       
     bool operator==(const SingleDecodeRoutine& decode)
	  {
	  return decode.StructureName == StructureName;
	  }
     };

#endif
