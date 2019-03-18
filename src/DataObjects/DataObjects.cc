/*  FILE     DataObjects.cc
**  PACKAGE  DataObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "DataObjects" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
** Version 1.5
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "DataObjects.hh"

/*S BaseDataString
 */ 
/*F BaseDataString()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataString::BaseDataString()
{
  Identification = DATAOBJ_STRING_ID;
  NameTag = DATAOBJ_STRING_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataString(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataString::BaseDataString(const BaseDataString& data)
  : BaseDataObject(data),
    Name(data.Name)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataString
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataString::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataString
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataString::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);
  StreamObjectInput str(in,' ');
  Name = str.ReadNext();
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataString
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataString::print(ostream& out) const
{
  BaseDataObject::print(out);
  out << "String: '" << Name << "'" << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataString
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataString::Clone()
{
  BaseDataString *obj = new BaseDataString(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataString
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataString::CopyClone(Identify * obj)
{
  BaseDataString *objfull = (BaseDataString *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataString
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataString::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && Encode(buffer,Name);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataString
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataString::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && Decode(buffer,Name);
  return result;
}
 
/*F string = getString()
**
**  DESCRIPTION
**    string: The string stored
**  REMARKS
**
*/
String& BaseDataString::getString()
{
  return Name;
}
 
/*F setString(s)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataString::setString(String& s)
{
  Name = s;
}
/*F ans = WriteAsLine(out,objc)  . . . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**      String rootname = inputRoot.getText();

*/
bool BaseDataString::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << "String: " << Name << " ";
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool BaseDataString::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataObject::WriteAsASCII(out,objc);
  out << " " << Name << " ";
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool BaseDataString::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  out << " " << Name << " " << "\\\\" << endl;
  return true;
}
/*S DataStringClass
 */
/*F DataStringClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataStringClass::DataStringClass()
{
  Identification = DATAOBJ_STRING_ID;
  NameTag = DATAOBJ_STRING_NAME;
  SubClass = "Object";
  EncodeDecodeClass = NameTag;
} 
/*F DataStringClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataStringClass::DataStringClass(const DataStringClass& data)
  : DataObjectClass(data)
{
} 
 
/*F DataStringClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataStringClass::DataStringClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataObjectClass(id,name,descr)
{
  SubClass = "Object";
  EncodeDecodeClass = DATAOBJ_STRING_NAME;
} 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataStringClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataStringClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataStringClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataStringClass, there is no further information.
**
**  REMARKS
**
*/
bool DataStringClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataObjectClass::Read(in,set);
  return result;
} 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataStringClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataStringClass::CopyClone(Identify *  objc)
{
  DataStringClass *objcfull = (DataStringClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataStringClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataStringClass::Clone()
{
  DataStringClass* id = new DataStringClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataStringClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataStringClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataStringClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataStringClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataStringClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataString();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataStringClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataStringClass*& obj)
     {
     obj = new DataStringClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataString
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataString*& obj)
     {
     obj = new BaseDataString;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataKeySet
 */ 
/*F BaseDataKeySet()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataKeySet::BaseDataKeySet()
{
  Identification = DATAOBJ_KEYSET_ID;
  NameTag = DATAOBJ_KEYSET_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataKeySet(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataKeySet::BaseDataKeySet(const BaseDataKeySet& data)
  : BaseDataKeyWords(data)
{
}
/*F BaseDataKeySet(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataKeySet::BaseDataKeySet(const BaseDataKeyWords& data)
  : BaseDataKeyWords(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataKeySet
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataKeySet::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataKeySet
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataKeySet::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);
  StreamObjectInput str(in,' ');
  String key = str.ReadNext();
  while(!(key == "END"))
    {
      AddKeyWord(key);
      key = str.ReadNext();
    }
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataKeySet
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataKeySet::print(ostream& out) const
{
  BaseDataKeyWords::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataKeySet
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataKeySet::Clone()
{
  BaseDataKeySet *obj = new BaseDataKeySet(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataKeySet
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataKeySet::CopyClone(Identify * obj)
{
  BaseDataKeySet *objfull = (BaseDataKeySet *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataKeySet
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataKeySet::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataKeyWords::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataKeySet
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataKeySet::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataKeyWords::DecodeThis(buffer);
  return result;
}
/*F ans = AddKeyWord(key) . . . . . . . . . . . . . . . . . . add key to list
**
**  DESCRIPTION
**    key: The keyword
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataKeySet::AddKeyWord(const String& key)
{
  bool ans = true;
  KeyWords.AddObject(key);
  return ans;
}
/*S DataKeySetClass
 */
/*F DataKeySetClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataKeySetClass::DataKeySetClass()
{
  Identification = DATAOBJ_KEYSET_ID;
  NameTag = DATAOBJ_KEYSET_NAME;
  SubClass = "KeyWords";
  EncodeDecodeClass = NameTag;
} 
/*F DataKeySetClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataKeySetClass::DataKeySetClass(const DataKeySetClass& data)
  : DataKeyWordsClass(data)
{
} 
 
/*F DataKeySetClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataKeySetClass::DataKeySetClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataKeyWordsClass(id,name,descr)
{
  SubClass = "KeyWords";
  EncodeDecodeClass = DATAOBJ_KEYSET_NAME;
}

/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataKeySetClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataKeySetClass::print(ostream& out) const
{
  DataKeyWordsClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataKeySetClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataKeySetClass, there is no further information.
**
**  REMARKS
**
*/
bool DataKeySetClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataKeyWordsClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataKeySetClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataKeySetClass::CopyClone(Identify *  objc)
{
  DataKeySetClass *objcfull = (DataKeySetClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataKeySetClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataKeySetClass::Clone()
    {
      DataKeySetClass* id = new DataKeySetClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataKeySetClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataKeySetClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataKeyWordsClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataKeySetClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataKeySetClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataKeyWordsClass::DecodeThis(buffer);
  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataKeySetClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataKeySet();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataKeySetClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataKeySetClass*& obj)
     {
     obj = new DataKeySetClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataKeySet
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataKeySet*& obj)
     {
     obj = new BaseDataKeySet;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataKeyWords
 */ 
/*F BaseDataKeyWords()  . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataKeyWords::BaseDataKeyWords()
  : KeyWords("---KeyWords---   "," ")
{
  Identification = DATAOBJ_KEYWORDS_ID;
  NameTag = DATAOBJ_KEYWORDS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataKeyWords(data)  . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataKeyWords::BaseDataKeyWords(const BaseDataKeyWords& data)
  : BaseDataObject(data),
    KeyWords(data.KeyWords)
{
}
BaseDataKeyWords::BaseDataKeyWords(const ObjectListString& data)
  : KeyWords(data)
{
  NameTag = DATAOBJ_KEYWORDS_NAME;
  Identification = DATAOBJ_KEYWORDS_ID;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . .  Read in BaseDataKeyWords
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataKeyWords::Read(istream& in, DataObjectClass* objc)
{
  bool result = true;
  
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  result = result && Read(in,objc,NameTag);
  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . .  Read in BaseDataKeyWords
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**    This reads in a set of keys separated by a blank
**    until END appears
**
**  REMARKS
**
*/
bool BaseDataKeyWords::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);
  StreamObjectInput str(in,' ');
  String key = str.ReadNext();
  while(!(key == "END"))
    {
      AddKeyWord(key);
      key = str.ReadNext();
    }
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . .  BaseDataKeyWords
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataKeyWords::print(ostream& out) const
{
  BaseDataObject::print(out);
  if(KeyWords.size() > 5)
    out << endl;
  ObjectList<String>::const_iterator key;
  unsigned int count = 0;
  for(key = KeyWords.begin(); key != KeyWords.end(); key++)
    {
      if((count % 5 == 0) && key != KeyWords.begin())
	{
	  out << endl;
	}
      out << *key << " ";
      count++;
    }
  out << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . .  BaseDataKeyWords
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataKeyWords::Clone()
{
  BaseDataKeyWords *obj = new BaseDataKeyWords;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . .  BaseDataKeyWords
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataKeyWords::CopyClone(Identify * obj)
{
  BaseDataKeyWords *objfull = (BaseDataKeyWords *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . .  BaseDataKeyWords
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataKeyWords::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && KeyWords.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . .  BaseDataKeyWords
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataKeyWords::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && KeyWords.DecodeThis(buffer);

  return result;
}
 
/*F ans = AddKeyWord(key) . . . . . . . . . . . . . . . . . . add key to list
**
**  DESCRIPTION
**    key: The keyword
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataKeyWords::AddKeyWord(const String& key)
{
  bool ans = true;
  
  if(KeyWordInList(key))
    {
      cout << "Key Already in List:";
      cout << key;
      cout << "\n";
      ans = false;
    }
  else
    KeyWords.AddObject(key);
  return ans;
}
/*F ans = RemoveKeyWord(key)  . . . . . . . . . . . . .  remove key from list
**
**  DESCRIPTION
**    key: The keyword
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataKeyWords::RemoveKeyWord(const String& key)
{
  bool ans = true;
  
  if(KeyWordInList(key))
    {
      KeyWords.RemoveObject(key);
    }
  else
    {
      cout << "Key Not in List:";
      cout << key;
      cout << "\n";
      ans = false;
    }
  return ans;
}
/*F ans = AddKeyWords(keys) . . . . . . . . . . . . . . . . . . add key to list
**
**  DESCRIPTION
**    key: The keyword
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataKeyWords::AddKeyWords(BaseDataKeyWords &keys)
{
  bool ans = true;
  ObjectListString names = keys.GetKeyWords();
  ObjectListString::iterator name;
  for(name = names.begin();name != names.end();name++) {
    ans = ans && AddKeyWord(*name);
  }
  return ans;
}
/*F ans = KeyWordInList(key)  . . . . . . . . . . . . . . . . is key in list?
**
**  DESCRIPTION
**    key: The keyword
**    ans: True if key is in list
**
**  REMARKS
**
*/
bool BaseDataKeyWords::KeyWordInList(const String& key)
{
  bool ans = true;
  ObjectList<String>::iterator pos;
  pos = find(KeyWords.begin(),KeyWords.end(),key);
  if(pos == KeyWords.end())
    ans = false;
  return ans;
}
/*F ans = ContainedIn(list)  . . . . . . . . . . . . . . . . is key in list?
**
**  DESCRIPTION
**    list: The list of keywords
**    ans: true if all the keywords are found in the list
**
**  REMARKS
**
*/
bool BaseDataKeyWords::ContainedIn(BaseDataKeyWords& list)
{
  bool ans = true;
  for(ObjectList<String>::iterator iter=KeyWords.begin();
      iter != KeyWords.end() && ans;
      iter++) {
    ans = ans && list.KeyWordInList(*iter);
    }
  return ans;
}
 
/*F name = BuildCategoryName()  . . . . . . . . . . . . . build from KeyWords
**
**  DESCRIPTION
**    name: The resulting name
**
**  REMARKS
**
*/
String& BaseDataKeyWords::BuildCategoryName()
{
  String *name = new String;
  String delim("#");
  
  for(ObjectList<String>::iterator iter=KeyWords.begin();
      iter != KeyWords.end();
      iter++)
    {
      if(iter != KeyWords.begin())
        name->AppendToEnd(delim);
      name->AppendToEnd(*iter);
    }
  return *name;
}
/*F keys = GetKeyWords()  . . . . . . . . . . . . . . . . . . . . .  get keys
**
**  DESCRIPTION
**    keys: The list of keywords
**
**  REMARKS
**
*/
ObjectListString& BaseDataKeyWords::GetKeyWords()
{
  return KeyWords;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool BaseDataKeyWords::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << "(" << objc->NameTag << ") " << NameTag << " = ";  
  return true;
}
/*F ans = WriteKeys(out,objc) . . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
void BaseDataKeyWords::WriteKeys(ostream& out)
{
  unsigned int icount = 0;
  ObjectList<String>::iterator key;
  for(key=KeyWords.begin();key != KeyWords.end();key++)
    {
      out << " " << *key;
      if(icount % 10 == 0 && icount != 0)
        out << endl;
    }
  out << " END" << endl;
}
/*F ans = WriteKeys(out)  . . . . . . . . . . . . . . . . .  BaseDataKeyWords
**
**  DESCRIPTION
**    out: The output stream
**
**  REMARKS
**
*/
bool BaseDataKeyWords::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataObject::WriteAsASCII(out,objc);
  WriteKeys(out);
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool BaseDataKeyWords::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  out << "$(" << objc->NameTag << ") " << NameTag << " = $ ";
  out << endl;
  WriteKeys(out);
  return true;
}
 
/*F key = NextKey()
**
**  DESCRIPTION
**    next: The next parameter key (it is taken out of the keys)
**
**  REMARKS
**
*/
String BaseDataKeyWords::NextKey()
{
  String name;
  if(KeyWords.size() > 0)
    {
      name = KeyWords.front();
      KeyWords.pop_front();
    }
  return name;
}
 
/*F size = SizeOf()
**
**  DESCRIPTION
**   size
**  REMARKS
**
*/
unsigned int BaseDataKeyWords::SizeOf()
{
  return KeyWords.size();
}

/*S DataKeyWordsClass
 */
/*F DataKeyWordsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataKeyWordsClass::DataKeyWordsClass()
{
  NameTag = DATAOBJ_KEYWORDS_NAME;
  Identification = DATAOBJ_KEYWORDS_ID;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = DATAOBJ_KEYWORDS_NAME;
} 
/*F DataKeyWordsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataKeyWordsClass::DataKeyWordsClass(const DataKeyWordsClass& data)
  : DataObjectClass(data)
  // the rest
{
} 
 
/*F DataKeyWordsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataKeyWordsClass::DataKeyWordsClass(const int id, 
                                     const String& name,
                                     const String& descr)
  : DataObjectClass(id,name,descr)
{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = DATAOBJ_KEYWORDS_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataKeyWordsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataKeyWordsClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  out << NameTag << "  ";
  // the rest
           
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . . . . . DataKeyWordsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataKeyWordsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataKeyWordsClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataKeyWordsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataKeyWordsClass::CopyClone(Identify *  objc)
{
  DataKeyWordsClass* objcfull = (DataKeyWordsClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataKeyWordsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataKeyWordsClass::Clone()
{
  DataKeyWordsClass* id = new DataKeyWordsClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataKeyWordsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataKeyWordsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  // The rest: result = result && Encode(buffer,-------);
  // result = result && EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataKeyWordsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataKeyWordsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
  // The rest: result = result && Decode(buffer,-------);
  // result = result && DecodeThis(buffer);

  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataKeyWordsClass::BaseDataObjectExample()
{ 
  BaseDataKeyWords *obj = new BaseDataKeyWords();
  obj->SetType(Identification);
  return (BaseDataObject *) obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataKeyWordsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataKeyWordsClass*& obj)
{
  obj = new DataKeyWordsClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataKeyWords
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataKeyWords*& obj)
{
  obj = new BaseDataKeyWords;
  bool result = obj->DecodeThis(buffer);
  return result;
}
/*S BaseDataPair
 */ 
/*F BaseDataPair()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataPair::BaseDataPair()
  : I(NULL),
    J(NULL)
{
  Identification = DATAOBJ_PAIR_ID;
  NameTag = DATAOBJ_PAIR_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataPair(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataPair::BaseDataPair(const BaseDataPair& data)
  : BaseDataObject(data)
{
  I = PointerClone(data.I);
  J = PointerClone(data.J);
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataPair
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataPair::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataPair
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataPair::Read(istream& in, DataObjectClass* objc, const String& name)
{
  DataPairClass *pairclass = (DataPairClass *) objc;
  bool result = BaseDataObject::Read(in,objc,name);
  if(pairclass->getIClass() != NULL &&
     pairclass->getJClass() != NULL)
    {
      I = pairclass->getIClass()->BaseDataObjectExample();
      J = pairclass->getJClass()->BaseDataObjectExample();
      result = result && I->Read(in,pairclass->getIClass());
      result = result && J->Read(in,pairclass->getJClass());
    }
  else
    {
      cerr << "No Pair Class object defined" << endl;
      result = false;
    }
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataPair
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataPair::print(ostream& out) const
{
  BaseDataObject::print(out);
  PointerPrint(out,"\nThe First Pair : ","No I Defined",I);
  PointerPrint(out,"\nThe Second Pair: ","No J Defined",J);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataPair
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataPair::Clone()
{
  BaseDataPair *obj = new BaseDataPair(*this);
  return obj;
}
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataPair
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataPair::CopyClone(Identify * obj)
{
  BaseDataPair *objfull = (BaseDataPair *) obj;
  *this = *objfull;
  I = PointerClone(objfull->I);
  J = PointerClone(objfull->J);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPair
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPair::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && PointerEncode(buffer,I);
  result = result && PointerEncode(buffer,J);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPair
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPair::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && PointerDecode(buffer,I);
  result = result && PointerDecode(buffer,J);
  return result;
}
 
/*F obj = getI()  . . . . . . . . . . . . . . . .  get the first of the pair
**
**  DESCRIPTION
**    obj: The First object of the pair
**
**  REMARKS
**
*/
BaseDataObject *BaseDataPair::getI()
{
  return I;
}
/*F obj = getI()  . . . . . . . . . . . . . . . .  get the first of the pair
**
**  DESCRIPTION
**    obj: The First object of the pair
**
**  REMARKS
**
*/
BaseDataObject *BaseDataPair::getJ()
{
  return J;
}
/*F ans = setI(obj)  . . . . . . . . . . . . . . . .  get the first of the pair
**
**  DESCRIPTION
**    obj: The First object of the pair
**
**  REMARKS
**
*/
void BaseDataPair::setI(BaseDataObject *obj)
{
  I = (BaseDataObject *) obj->Clone();
}
/*F obj = getI()  . . . . . . . . . . . . . . . .  get the first of the pair
**
**  DESCRIPTION
**    obj: The First object of the pair
**
**  REMARKS
**
*/
void BaseDataPair::setJ(BaseDataObject *obj)
{
  J = (BaseDataObject *) obj->Clone();
}
/*S DataPairClass
 */
/*F DataPairClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataPairClass::DataPairClass()
  : IClass(NULL),
    JClass(NULL)
{
  Identification = DATAOBJ_PAIR_ID;
  NameTag = DATAOBJ_PAIR_NAME;
  SubClass = "Object";
  EncodeDecodeClass = NameTag;
} 
/*F DataPairClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataPairClass::DataPairClass(const DataPairClass& data)
  : DataObjectClass(data)
{
  IClass = (DataObjectClass *) PointerClone(data.IClass);
  JClass = (DataObjectClass *) PointerClone(data.JClass);
} 
/*F DataPairClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataPairClass::DataPairClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataObjectClass(id,name,descr),
    IClass(NULL),
    JClass(NULL)
{
  SubClass = "Object";
  EncodeDecodeClass = DATAOBJ_PAIR_NAME;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataPairClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataPairClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  PointerPrint(out,"  The I Class: "," No Class Defined ",IClass);
  PointerPrint(out,"  The J Class: "," No Class Defined ",JClass);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataPairClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataPairClass, there is no further information.
**
**  REMARKS
**
*/
bool DataPairClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataObjectClass::Read(in,set);
  result = result && PointerClassRead(in,(DataObjectClass *&) IClass,
				      COREOBJECTS_BASE_NAME,
				      set," No Class ");
  result = result && PointerClassRead(in,(DataObjectClass *&) JClass,
				      COREOBJECTS_BASE_NAME,
				      set," No Class ");
  return result;
} 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataPairClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataPairClass::CopyClone(Identify *  objc)
{
  DataPairClass *objcfull = (DataPairClass *) objc;
  *this = *objcfull;
  IClass = (DataObjectClass *) PointerClone(objcfull->IClass);
  JClass = (DataObjectClass *) PointerClone(objcfull->JClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataPairClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataPairClass::Clone()
    {
      DataPairClass* id = new DataPairClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataPairClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPairClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,IClass);
  result = result && PointerEncode(buffer,JClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataPairClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPairClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) IClass);
  result = result && PointerDecode(buffer,(BaseDataObject *&) JClass);
  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataPairClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataPair();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataPairClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataPairClass*& obj)
     {
     obj = new DataPairClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataPair
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataPair*& obj)
     {
     obj = new BaseDataPair;
     return obj->DecodeThis(buffer);
     }
 
/*F iclass = getIClass()  . . . . . . . . . . . . . . . . . . . DataPairClass
**
**  DESCRIPTION
**    iclass: The class of the first of the pair
**
**  REMARKS
**
*/
DataObjectClass *DataPairClass::getIClass()
{
  return IClass;
}
 
/*F jclass = getJClass()  . . . . . . . . . . . . . . . . . . . DataPairClass
**
**  DESCRIPTION
**    jclass: the second class
**
**  REMARKS
**
*/
DataObjectClass *DataPairClass::getJClass()
{
  return JClass;
}
/*S BaseDataDoubleMatrix
 */ 
/*F BaseDataDoubleMatrix()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDoubleMatrix::BaseDataDoubleMatrix()
{
  Identification = DATAOBJ_MATRIX_ID;
  NameTag = DATAOBJ_MATRIX_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataDoubleMatrix(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDoubleMatrix::BaseDataDoubleMatrix(const BaseDataDoubleMatrix& data)
  : BaseDataNumeric(data),
    Mat(data.Mat)
{
}
/*F BaseDataDoubleMatrix(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDoubleMatrix::BaseDataDoubleMatrix(const MatrixNumeric& mat)
  : Mat(mat)
{
  Identification = DATAOBJ_MATRIX_ID;
  NameTag = DATAOBJ_MATRIX_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataDoubleMatrix
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataDoubleMatrix::Read(istream& in, DataObjectClass* objc)
{
  bool result = true;
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  result = result && Read(in,objc,NameTag);
  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataDoubleMatrix
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**    First the two dimensions are read in: rows, columns (integers).  The the matrix values
**    (doubles).
**
**  REMARKS
**
*/
bool BaseDataDoubleMatrix::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = true;
  result = result && BaseDataNumeric::Read(in,objc,name);
  StreamObjectInput str(in,' ');

  result = result && Mat.Read(in);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataDoubleMatrix
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataDoubleMatrix::print(ostream& out) const
{
  BaseDataNumeric::print(out);
  out << "\n";
  
  for (unsigned int i=0; i<Mat.size(); i++)
    {
      for (unsigned int j=0; j<Mat[0].size(); j++)
        out << Mat[i][j] << " ";
      out << "\n";
    }
  //  Mat.print(out);
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataDoubleMatrix
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataDoubleMatrix::Clone()
{
  BaseDataDoubleMatrix *obj = new BaseDataDoubleMatrix;
  obj->CopyClone(this);
  return obj;
}
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataDoubleMatrix
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataDoubleMatrix::CopyClone(Identify * obj)
{
  BaseDataDoubleMatrix *objfull = (BaseDataDoubleMatrix *) obj;
  
  BaseDataNumeric::CopyClone(objfull);

  unsigned int i;
  unsigned int matsize = objfull->Mat.size();
  for( i=0; i< Mat.size(); i++)
    {
      Mat[i].erase(Mat[i].begin(),Mat[i].end());
    }
  
  Mat.erase(Mat.begin(),Mat.end());
  for( i=0; i<matsize; i++)
    {
      Mat.push_back((objfull->Mat)[i]);
    }
}

/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDoubleMatrix
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDoubleMatrix::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataNumeric::EncodeThis(buffer);
  result = result && Mat.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDoubleMatrix
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDoubleMatrix::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataNumeric::DecodeThis(buffer);
  result = result && Mat.DecodeThis(buffer);

  return result;
}
 
/*F mat = CurrentMatrix() . . . . . . . . . . . . . . . . . . . .  the matrix
**
**  DESCRIPTION
**    mat: The matrix within the class
**
**  REMARKS
**
*/
MatrixNumeric& BaseDataDoubleMatrix::CurrentMatrix()
{
  return Mat;
}
/*F ans = WriteAsLine(out,objc)  . . . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool BaseDataDoubleMatrix::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << "(" << objc->NameTag << ") " << NameTag << " = ";  
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool BaseDataDoubleMatrix::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataObject::WriteAsASCII(out,objc);
  
  VectorNumeric row = Mat.getMatrixRow(0);
  out << Mat.size() << " " << row.size() << endl;
  for(unsigned int i=0; i < Mat.size(); i++)
    {
      row = Mat.getMatrixRow(i);
      for(unsigned int j=0; j < row.size() ; j++)
        {
          out << row[j] << " ";
        }
      out << endl;
    }
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool BaseDataDoubleMatrix::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  out << "$(" << objc->NameTag << ") " << NameTag << " = $ ";
  out << endl;
  for(unsigned int i=0; i < Mat.size(); i++)
    {
      VectorNumeric row = Mat.getMatrixRow(i);
      for(unsigned int j=0; j < row.size() ; j++)
        {
          out << row[j] << " ";
        }
      out << "\\\\" << endl;;
    }
  return true;
}

/*S DataDoubleMatrixClass
 */
/*F DataDoubleMatrixClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDoubleMatrixClass::DataDoubleMatrixClass()
{
  NameTag = DATAOBJ_MATRIX_NAME;
  Identification = DATAOBJ_MATRIX_ID;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = DATAOBJ_MATRIX_NAME;
} 
/*F DataDoubleMatrixClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataDoubleMatrixClass::DataDoubleMatrixClass(const DataDoubleMatrixClass& data)
  : DataNumericClass(data)
  // the rest
{
} 
 
/*F DataDoubleMatrixClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataDoubleMatrixClass::DataDoubleMatrixClass(const int id, 
                                             const String& name,
                                             const String& descr)
  : DataNumericClass(id,name,descr)
{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = DATAOBJ_MATRIX_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataDoubleMatrixClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataDoubleMatrixClass::print(ostream& out) const
{
  DataNumericClass::print(out);
  out << NameTag << "  ";
  // the rest
           
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . . . . . DataDoubleMatrixClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataDoubleMatrixClass, there is no further information.
**
**  REMARKS
**
*/
bool DataDoubleMatrixClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataNumericClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataDoubleMatrixClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataDoubleMatrixClass::CopyClone(Identify *  objc)
{
  DataDoubleMatrixClass *objcfull = (DataDoubleMatrixClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataDoubleMatrixClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataDoubleMatrixClass::Clone()
{
  DataDoubleMatrixClass* id = new DataDoubleMatrixClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataDoubleMatrixClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDoubleMatrixClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataNumericClass::EncodeThis(buffer);
  // The rest: result = result && Encode(buffer,-------);
  // result = result && EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataDoubleMatrixClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDoubleMatrixClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataNumericClass::DecodeThis(buffer);
  // The rest: result = result && Decode(buffer,-------);
  // result = result && DecodeThis(buffer);

  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataDoubleMatrixClass::BaseDataObjectExample()
{ 
  //cout << "Make DoubleMatrix Example\n";
  return (BaseDataObject *) new BaseDataDoubleMatrix();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataDoubleMatrixClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataDoubleMatrixClass*& obj)
{
  obj = new DataDoubleMatrixClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataDoubleMatrix
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataDoubleMatrix*& obj)
{
  obj = new BaseDataDoubleMatrix;
  return obj->DecodeThis(buffer);
}
/*S BaseDataDoubleVector
 */ 
/*F BaseDataDoubleVector()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDoubleVector::BaseDataDoubleVector()
{
  Identification = DATAOBJ_VECTOR_ID;
  NameTag = DATAOBJ_VECTOR_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataDoubleVector(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDoubleVector::BaseDataDoubleVector(const BaseDataDoubleVector& data)
  : BaseDataObject(data),
    Vect(data.Vect)
{
}
 
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDoubleVector::BaseDataDoubleVector(const VectorNumeric& data)
  : Vect(data)
{
  Identification = DATAOBJ_VECTOR_ID;
  NameTag = DATAOBJ_VECTOR_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataDoubleVector
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataDoubleVector::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  bool result = Read(in,objc,NameTag);
  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataDoubleVector
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataDoubleVector::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);
  StreamObjectInput str(in,' ');
  
  result = result && Vect.Read(in);

  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataDoubleVector
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataDoubleVector::print(ostream& out) const
{
  BaseDataObject::print(out);
  out << "Vector: ";
  Vect.print(out);
  cout << "\n";
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataDoubleVector
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataDoubleVector::Clone()
{
  BaseDataDoubleVector *obj = new BaseDataDoubleVector;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataDoubleVector
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataDoubleVector::CopyClone(Identify * obj)
{
  BaseDataDoubleVector *objfull = (BaseDataDoubleVector *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDoubleVector
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDoubleVector::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && Vect.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDoubleVector
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDoubleVector::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && Vect.DecodeThis(buffer);

  return result;
}
/*F ans = WriteAsLine(out,objc)  . . . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool BaseDataDoubleVector::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << "(" << objc->NameTag << ") " << NameTag << " = ";  
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool BaseDataDoubleVector::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataObject::WriteAsASCII(out,objc);
  
  cout << Vect.size() << endl;
  for(unsigned int j=0; j < Vect.size() ; j++)
    {
      out << Vect[j] << " ";
    }
  out << endl;
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool BaseDataDoubleVector::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  out << "$(" << objc->NameTag << ") " << NameTag << " = $ ";
  for(unsigned int j=0; j < Vect.size() ; j++)
    {
      out << Vect[j] << " ";
    }
  out << endl;
  return true;
}

/*S DataDoubleVectorClass
 */
/*F DataDoubleVectorClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDoubleVectorClass::DataDoubleVectorClass()
{
  NameTag = DATAOBJ_VECTOR_NAME;
  Identification = DATAOBJ_VECTOR_ID;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = DATAOBJ_VECTOR_NAME;
} 
/*F DataDoubleVectorClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataDoubleVectorClass::DataDoubleVectorClass(const DataDoubleVectorClass& data)
  : DataObjectClass(data)
{
} 
 
/*F DataDoubleVectorClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataDoubleVectorClass::DataDoubleVectorClass(const int id, 
                                             const String& name,
                                             const String& descr)
  : DataObjectClass(id,name,descr)
{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = DATAOBJ_VECTOR_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataDoubleVectorClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataDoubleVectorClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  out << NameTag << "  ";
  // the rest
           
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . . . . . DataDoubleVectorClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataDoubleVectorClass, there is no further information.
**
**  REMARKS
**
*/
bool DataDoubleVectorClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataDoubleVectorClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataDoubleVectorClass::CopyClone(Identify *  objc)
{
  DataDoubleVectorClass *objcfull = (DataDoubleVectorClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataDoubleVectorClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataDoubleVectorClass::Clone()
{
  DataDoubleVectorClass* id = new DataDoubleVectorClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataDoubleVectorClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDoubleVectorClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  // The rest: result = result && Encode(buffer,-------);
  // result = result && EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataDoubleVectorClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDoubleVectorClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);

  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataDoubleVectorClass::BaseDataObjectExample()
{ 
  //cout << "Make DoubleVector Example\n";
  return (BaseDataObject *) new BaseDataDoubleVector();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataDoubleVectorClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataDoubleVectorClass*& obj)
{
  obj = new DataDoubleVectorClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataDoubleVector
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataDoubleVector*& obj)
{
  obj = new BaseDataDoubleVector;
  return obj->DecodeThis(buffer);
}
 
/*F vect = CurrentVector()  . . . . . . . . . . . . . .  BaseDataDoubleVector
**
**  DESCRIPTION
**    vect: The current
**
**  REMARKS
**
*/
VectorNumeric& BaseDataDoubleVector::CurrentVector()
{
  return Vect;
}

/*S Utilities
 */
/*F AddBasicAlgorithmClasses(set) . . . . . . . .  basic algorithm data types
**
**  DESCRIPTION
**    set: The set of data types
**
**  REMARKS
**
*/
void AddDataObjectClasses(DataSetOfObjectsClass& set)
{
  String keydescr("List of KeyWords");
  String matdescr("Matrix of doubles");
  String vecdescr("Vector of doubles");
  String strdescr("The String Class");
  String keysetdescr("The set of Keys Class");
  String pairdescr("Pair of Objects");
  
  DataKeyWordsClass keyclass(DATAOBJ_KEYWORDS_ID,DATAOBJ_KEYWORDS_NAME,keydescr);
  DataDoubleMatrixClass matclass(DATAOBJ_MATRIX_ID,DATAOBJ_MATRIX_NAME,matdescr);
  DataDoubleVectorClass vecclass(DATAOBJ_VECTOR_ID,DATAOBJ_VECTOR_NAME,vecdescr);
  DataStringClass strclass(DATAOBJ_STRING_ID,DATAOBJ_STRING_NAME,strdescr);
  DataKeySetClass keysetclass(DATAOBJ_KEYSET_ID,DATAOBJ_KEYSET_NAME,keysetdescr);
  DataPairClass pairclass(DATAOBJ_PAIR_ID,DATAOBJ_PAIR_NAME,pairdescr);
  
  set.AddObjectClass(keyclass);
  set.AddObjectClass(matclass);
  set.AddObjectClass(vecclass);
  set.AddObjectClass(strclass);
  set.AddObjectClass(keysetclass);
  set.AddObjectClass(pairclass);
}
/*F InitialSetOfDataObjectsEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialSetOfDataObjectsEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataKeyWordsClass,BaseDataKeyWords,DATAOBJ_KEYWORDS_NAME);
  EncodeDecodeRegisterClass(DataDoubleVectorClass,BaseDataDoubleVector,DATAOBJ_VECTOR_NAME);
  EncodeDecodeRegisterClass(DataDoubleMatrixClass,BaseDataDoubleMatrix,DATAOBJ_MATRIX_NAME);
  EncodeDecodeRegisterClass(DataStringClass,BaseDataString,DATAOBJ_STRING_NAME);
  EncodeDecodeRegisterClass(DataKeySetClass,BaseDataKeySet,DATAOBJ_KEYSET_NAME);
  EncodeDecodeRegisterClass(DataPairClass,BaseDataPair,DATAOBJ_PAIR_NAME);
}
