/*  FILE     CoreDataObjects.cc
**  PACKAGE  CoreDataObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "CoreDataObjects" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
**  Version 1.5
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#define TEMPLATE_INSTANTIATION
#include "CoreDataObjects.hh"


/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
String DefaultSetOfDataObjectClasses("Standard");
String RootClassName("DataObjectClass");
String PlaceHoldersKeyWord("PlaceHolders");
String NoClassNamePairsKeyWord("NoClassNamePairsKeyWord");
String NoReadKeyWord("NoRead");
String ReadAsTripletKeyWord("ReadAsTriplet");


DataSetOfObjectsClass *StandardAllowedClasses;
String ClassNamePairsKeyWord("ClassNamePairs:");

/*S BaseDataSetOfObjects
 */ 
/*F BaseDataSetOfObjects()  . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSetOfObjects::BaseDataSetOfObjects()
  : AssignedID(true)
{
  Identification = COREOBJECTS_SET_ID;
  NameTag = COREOBJECTS_SET_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  Initialisation();
} 
/*F Initialisation()  . . . . . . . . . . . . . . . . . . . . . .  initialize
**
**  DESCRIPTION
**    Performs the initialisation: 
**    - Title and Delimitor changes
**
**  REMARKS
**
*/
void BaseDataSetOfObjects::Initialisation()
{
  IDcount = 0;
  
  Objects.ChangeTitle("---------------------The set of Data Objects---------------------\n");
  Objects.ChangeDelimitor("\n");
  Objects.ChangeOutputFlag(SEARCHABLE_OBJECT);
  IDCorrs.ChangeTitle("Name, Class integer ID Correspondences\n");
  IDCorrs.ChangeDelimitor("\n");
  IDCorrs.ChangeOutputFlag(SEARCHABLE_BOTH);
}
/*F BaseDataSetOfObjects(data)  . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataSetOfObjects::BaseDataSetOfObjects(const BaseDataSetOfObjects& data)
  : BaseDataObject(data),
    Objects(data.Objects),
    IDCorrs(data.IDCorrs),
    IDcount(data.IDcount),
    AssignedID(data.AssignedID)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . .  Read in BaseDataSetOfObjects
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataSetOfObjects::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  bool result = Read(in,objc,NameTag);
  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . .  Read in BaseDataSetOfObjects
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**    The Read proceeds as follows:
**    - Read in the Name/Class pairs if there are none in the class
**    - Read in the corresponding data
**
**    The set of allowed classes is given in 'BaseSetOfObjectsClass'
**    The set of objects is not initialised, so this can be used
**    to repeatedly add new objects.
**
**  REMARKS
**
*/
bool BaseDataSetOfObjects::Read(istream& in, DataObjectClass* objc, const String& name)
{
  BaseDataObject::Read(in,objc,name);
  DataSetOfObjectsClass *nobjc = (DataSetOfObjectsClass *) objc;
  bool result = true;
  
  ObjectNameClassPairs objtypes;
  objtypes = nobjc->ObjectTypes;
  
  if(objc->getDebugLevel() > 0)
    cout << "Read in Object\n";
  
  ObjectNameClassPairs::const_iterator iter;
  for(iter=objtypes.begin();
      !(iter == objtypes.end()) && result;
      iter++)
    {
      if(IDCorrs.IsInList((*iter).I))
        {
          if(objc->getDebugLevel() > 0)
            cout << "Replacing: " << (*iter).I << endl;
        }
      
      if(objc->getDebugLevel() > 0)
        cout << "Read Object "<< (*iter).J << "\n";
      
      DataObjectClass *c = (DataObjectClass *) 
	nobjc->PointerToAllowedClasses()->GetObjectClass((*iter).J);
      c->SetDebugLevel(objc->getDebugLevel());
      if(c->Identification != 0)
        {
          if(objc->getDebugLevel() > 0)
            {
              cout << "The Class\n";
              c->print(cout);
              cout << "\n";
            }
          
          BaseDataObject *o = c->BaseDataObjectExample();

	  o->SetType(c->Identification);
          o->Identification = IDcount;
          o->NameTag = (*iter).I;
          IDcount++;
          result = o->Read(in,c,(*iter).I);
          if(result)
	    result = AddObject(o);
          delete o;
        }
      else
        {
          cerr << "Object Type: " << (*iter).J << " Not found in List of Allowed Classes\n";
          nobjc->PointerToAllowedClasses()->ListOfClassNames().print(cerr);
          cerr << "\n";
          result = false;
	  cout << "Error Read: " << result << endl;
        }
    }

  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . .  BaseDataSetOfObjects
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataSetOfObjects::print(ostream& out) const
{
  BaseDataObject::print(out);
  out << "\nBegin: ";
  Objects.print(out);
  out << "\nEnd:   " << Objects.Title << endl;
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . .  BaseDataSetOfObjects
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataSetOfObjects::Clone()
{
  BaseDataSetOfObjects *obj = new BaseDataSetOfObjects;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . .  BaseDataSetOfObjects
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataSetOfObjects::CopyClone(Identify *obj)
{
  BaseDataSetOfObjects *objfull = (BaseDataSetOfObjects *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . .  BaseDataSetOfObjects
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSetOfObjects::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && Objects.EncodeThis(buffer);
  result = result && IDCorrs.EncodeThis(buffer);
  result = result && Encode(buffer,IDcount);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . .  BaseDataSetOfObjects
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSetOfObjects::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && Objects.DecodeThis(buffer);
  result = result && IDCorrs.DecodeThis(buffer);
  result = result && Decode(buffer,IDcount);
  return result;
}
 
/*F obj = GetObject(id) . . . . . . . . . . . . . .  get object given name
**
**  DESCRIPTION
**    id: The name of the object to retrieve
**    obj: The retrieved object
**    
**  REMARKS
**
*/
BaseDataObject *BaseDataSetOfObjects::GetObject(const unsigned int id)
{
  Identify id1(id);
  return (BaseDataObject *) Objects.GetPointerToObject(id1);
}
 
/*F obj = GetObject(name) . . . . . . . . . . . . . .  get object, given name
**
**  DESCRIPTION
**    name: The name of the object to retrieve
**    obj: The retrieved object
**    
**  REMARKS
**
*/
BaseDataObject *BaseDataSetOfObjects::GetObject(const String& name)
{
  unsigned int id = IDCorrs[name];
  return GetObject(id);
}
 
/*F ans = IsInList(name)  . . . . . . . . . . . . . Is the object in the list
**
**  DESCRIPTION
**    name: The object name
**    ans: True if in the list of objects
**    
**  REMARKS
**
*/
bool BaseDataSetOfObjects::IsInList(const String& name)
{
  return IDCorrs.IsInList(name);
}
 
/*F names = ListOfObjectNames() . . . . . . . . . get names of all attributes
**
**  DESCRIPTION
**    names: The names of the Objects in the list
**
**  REMARKS
**
*/
ObjectList<String> BaseDataSetOfObjects::ListOfObjectNames()
{
  ObjectList<int> empty;
  return ListOfObjectNames(empty);
}

/*F names = ListOfObjectNames(tlist)  . . . . . . get names of all attributes
**
**  DESCRIPTION
**    tlist: List of IDs (see below)
**    names: The list of attribute types
**
**    This retrieves the attribute names corresponding to the list of IDs given.
**    If the list of IDs is empty, then the entire list of attributes is returned.
**
**  REMARKS
**
*/
ObjectList<String> BaseDataSetOfObjects::ListOfObjectNames(ObjectList<int>& tlist)
{
  ObjectList<String> names;
  names.ChangeTitle("List Of Object Names:   ");
  names.ChangeDelimitor(" ");
  bool selectattributes = true;
  if(tlist.size() == 0)
    selectattributes = false;
  ObjectList<int>::iterator t;
  NameIDCorrespondences::iterator iter;
  for(iter=IDCorrs.begin();
      iter != IDCorrs.end();
      iter++)
    {
      if(selectattributes)
        {
          int typ = GetObject((*iter).first)->GetType();
          t = find(tlist.begin(),tlist.end(),typ);
          if(t != tlist.end())
            {
              names.AddObject((*iter).first);
            }
        }
      else
        {
          names.AddObject((*iter).first);
        }
      
    }
  return names;
}
/*F ans = AddObject(obj)  . . . . . . . . . . . . . add attribute to instance
**
**  DESCRIPTION
**    obj: The object to add
**    ans: true if successful
**
**    The object  adds a cloned version of the object
**    The Identification is also changed to an internal number
**
**  REMARKS
**
*/
bool BaseDataSetOfObjects::AddObject(BaseDataObject *obj)
{
  bool added = true;
  bool inlist = IDCorrs.IsInList(obj->NameTag);
  if(inlist)
    {
      obj->Identification = IDCorrs[obj->NameTag];
      String *n = new String(obj->NameTag);
      BaseDataSetOfObjects::RemoveObject(*n);
      delete n;
    }
  else
    {
      if(AssignedID)
	obj->Identification = NextIdentification();
    }
  
  IDCorrs[obj->NameTag] = obj->Identification;
  Identify id1(obj->Identification);
  added = added && Objects.AddObject(id1,obj,obj->EncodeDecodeClass);
  return added;
}
/*F nums = NamesToIDs(names)  . . . . . . .  translate class names to numbers
**
**  DESCRIPTION
**    names: The classes as names
**    nums: The classes as integers
**
**  REMARKS
**
*/
ObjectList<int>& BaseDataSetOfObjects::NamesToIDs(const ObjectList<String>& names)
{
  ObjectList<int> *nums = new ObjectList<int>;
  for(ObjectList<String>::const_iterator iter = names.begin();
      iter != names.end();
      iter++)
    {
      if(IDCorrs.IsInList(*iter))
        nums->AddObject(IDCorrs[(*iter)]);
      else
        {
          cout << "Name not found: ";
          cout << *iter;
          cout << "\n";
        }
    }
  return *nums;
}
/*C SetLoopOfAddObjects . . . . . . . . . . . . . . .  add object to ClassSet
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class SetLoopOfAddObjects
{
  BaseDataSetOfObjects *ObjectSet;
  BaseDataSetOfObjects *SetToAdd;
  
public:
  unsigned int NewAdded;
  
  SetLoopOfAddObjects(BaseDataSetOfObjects *set, BaseDataSetOfObjects *addset)
    : ObjectSet(set),
      SetToAdd(addset),
      NewAdded(0)
    {
    }
  void operator()(pair< const String, int >& data)
    {
      BaseDataObject *prop = SetToAdd->GetObject(data.second);
      if(!ObjectSet->IsInList(data.first) )
        {
          ObjectSet->AddObject(prop);
          NewAdded++;
        }
    }
};
/*F added = MergeSetOfObjects(objects)  . . . . . . . .  merge in new objects
**
**  DESCRIPTION
**    objects: The objects to be merged in
**    added: The number of new objects added.
**
**  REMARKS
**
*/
unsigned int BaseDataSetOfObjects::MergeSetOfObjects(BaseDataSetOfObjects *objects)
{
  SetLoopOfAddObjects addobj(this,objects);
  for_each(objects->IDCorrs.begin(),
	   objects->IDCorrs.end(),
	   addobj);
  return addobj.NewAdded;
}
 
/*F ans = NextIdentification()  . . . . . . . . . . . . . . . . . . . next ID
**
**  DESCRIPTION
**    ans: The next ID for the added objects
**
**  REMARKS
**
*/
unsigned int BaseDataSetOfObjects::NextIdentification()
{
  IDcount++;
  return IDcount;
}
/*F ans = RemoveObject(name)  . . . . . . . . . . . . . . . . . . . .  remove
**
**  DESCRIPTION
**    name: The name of the object
**    ans: The next ID for the added objects
**
**  REMARKS
**
*/
bool BaseDataSetOfObjects::RemoveObject(String& name)
{
  bool removed = true;
  
  bool inlist = IDCorrs.IsInList(name);
  if(inlist)
    {
      Objects.RemoveObject(IDCorrs[name]);
      IDCorrs.RemoveObject(name);
    }
  else
    {
      removed = false;
    }
  return removed;
} 
/*F setTitle(title) . . . . . . . . . . . . . . . . . . . . . .  change title
**
**  DESCRIPTION
**    title: The title of the set of objects
**
**  REMARKS
**
*/
void BaseDataSetOfObjects::setTitle(String& title)
{
  Objects.ChangeTitle(title);
}
/*F setDelimitor(delimitor) . . . . . . . . . . . . . . . .  change delimitor
**
**  DESCRIPTION
**    delimitor: The delimitor between the objects in the list
**
**  REMARKS
**
*/
void BaseDataSetOfObjects::setDelimitor(String& delimitor)
{
  Objects.ChangeDelimitor(delimitor);
}
 
/*F NoIDAssignment()  . . . . . . . . . . . . . . . . .  BaseDataSetOfObjects
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataSetOfObjects::NoIDAssignment()
{
  AssignedID = false;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . .  BaseDataSetOfObjects
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
bool BaseDataSetOfObjects::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << "(" << objc->NameTag << ") " << NameTag << " with a size of " << Objects.size() << endl;
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
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
bool BaseDataSetOfObjects::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  DataSetOfObjectsClass *objclass = (DataSetOfObjectsClass *) objc;
  bool result = true;
  DataObjectClass *cls;
  BaseDataObject *obj;

  ObjectNameClassPairs pairs = objclass->getNameClassPairs();
  ObjectNameClassPairs::iterator pair;
  unsigned int icount= 0;
  for(pair=pairs.begin(); pair != pairs.end() && result ; pair++)
    {
      String name = (*pair).I;
      obj = GetObject(name);
      cls = objclass->PointerToAllowedClasses()->GetObjectClass(obj->GetType());
      if(icount % 10 == 0 && icount != 0)
	out << endl;
      obj->WriteAsASCII(out,cls);
      icount++;
    }
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . .  BaseDataSetOfObjects
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
bool BaseDataSetOfObjects::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  DataSetOfObjectsClass *objclass = (DataSetOfObjectsClass *) objc;
  bool result = true;
  DataObjectClass *cls;
  BaseDataObject *obj;
  ObjectList<String> names = ListOfObjectNames();
  ObjectList<String>::iterator name;

  /*
  out << "\\begin{description}" << endl;
  for(name=names.begin(); name != names.end() && result ; name++)
    {
      obj = GetObject(*name);
      cls = objclass->GetObjectClass(obj->GetType());
      out << "   \\item[ " << *name << "] ";
      cls->WriteAsLine(out);
      out << endl;
    }
  out << "\\end{description}" << endl;
  */

  for(name=names.begin(); name != names.end() && result ; name++)
    {
      obj = GetObject(*name);
      cls = objclass->GetObjectClass(obj->GetType());
      obj->WriteAsLatex(out,cls);
    }

  return true;
}
bool BaseDataSetOfObjects::ReadAsTriplet(istream& in, DataSetOfObjectsClass *set) {
  bool result = true;
  String endstring("END");
  DataSetOfObjectsClass *classes = set->PointerToAllowedClasses();
  StreamObjectInput str(in,' ');
  String classtype = str.ReadNext();
  while(!(classtype == endstring) && result) {
    cout << "Reading Type: '" << classtype << "'" << endl;
    if(classes->IsInList(classtype)) {
      DataObjectClass *cls = classes->GetObjectClass(classtype);
      BaseDataObject *obj = cls->BaseDataObjectExample();
      obj->SetType(cls->Identification);
      cout << "READING" << endl;
      obj->Read(in,cls);
      cout << "Adding" << endl;
      result = result && AddObject(obj);
    } else {
      cerr << "Class Not found: '" << classtype << "'" << endl;
      result = false;
    }
    classtype = str.ReadNext();
  }
  cout << "Done" << endl;
  return result;
}
/*S DataSetOfObjectsClass
 */
/*F DataSetOfObjectsClass() . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataSetOfObjectsClass::DataSetOfObjectsClass()
{
  Initialisation();
  NameTag = COREOBJECTS_SET_NAME;
  Identification = COREOBJECTS_SET_ID;
} 
/*F DataSetOfObjectsClass(data) . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataSetOfObjectsClass::DataSetOfObjectsClass(const DataSetOfObjectsClass& data)
  : DataObjectClass(data),
    AllowedClasses(data.AllowedClasses),
    ObjectTypes(data.ObjectTypes),
    PrintMode(data.PrintMode),
    ClassPrintMode(data.ClassPrintMode),
    ClassEndDelimitor(data.ClassEndDelimitor),
    AvailablePrintModes(data.AvailablePrintModes),
    ReadClassPairs(data.ReadClassPairs),
    ReadAllowedClasses(data.ReadAllowedClasses)
{
} 
 
/*F DataSetOfObjectsClass(id,name,descr)  . . . . . . . . . . . . constructor
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
DataSetOfObjectsClass::DataSetOfObjectsClass(const int id, 
                                             const String& name,
                                             const String& descr)
  : DataObjectClass(id,name,descr)
{
  Initialisation();
}
 
/*F Initialisation()  . . . . . . . . .  Initialize the DataSetOfObjectsClass
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void DataSetOfObjectsClass::Initialisation()
{
  IDCount = 90000;
  AllowedClasses.NoIDAssignment();
  
  ReadClassPairs = true;
  ReadAllowedClasses = true;
  
  SubClass = "Object";
  EncodeDecodeClass = "SetOfObjects";

  PrintMode = 0;
  ClassPrintMode = 0;
  ClassEndDelimitor = DefaultEndDelimitor;

  ObjectTypes.ChangeDelimitor("\n");
  ObjectTypes.ChangeTitle(" ---- Set Of Object-Class Pairs --- ");
  
  String title(" --------------- Set Of Instance Classes ----------------- ");
  
  AllowedClasses.setTitle(title);
  AvailablePrintModes.ChangeTitle("Available Print Modes\n");
  AvailablePrintModes.ChangeDelimitor("\n");
  AvailablePrintModes.ChangeOutputFlag(SEARCHABLE_BOTH);
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . DataSetOfObjectsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataSetOfObjectsClass::print(ostream& out) const
{
  DataObjectClass::print(out);

  ObjectTypes.print(out);

  AvailablePrintModes.print(out);

  AllowedClasses.print(out);
  
  
  return out;
}
/*F ans = Read(in,set)  . . . . . . . . . . . . . . . . DataSetOfObjectsClass
**
**  DESCRIPTION
**    set: The set of classes
**    in: The input buffer
**    ans: true if successful
**
**    This performs the following tasks:
**    - The SetOfDataObjectClasses is merged with input set
**    - The new classes are read in
**    - The current set of ObjectTypes are erased.
**    - Read in Name-Class pairs into Objecttypes (ends with 'END')
**
**  REMARKS
**
*/
bool  DataSetOfObjectsClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = true;

  MergeSetOfObjectClasses(set);
  if(ReadAllowedClasses)
    result = result && ReadInAttributeTypes(in);

  result = result && ReadInClassNamePairs(in);
  return result;
}
/*F ReInitializeObjectNames() . . . . . . . . . . . . . . . . . . DataSetOfObjectsClass
**
**  DESCRIPTION
**    Reinitializes ObjectTypes and ObjectNames by erasing
**    their contents.
**
**  REMARKS
**
*/
void DataSetOfObjectsClass::ReInitializeObjectNames() {
  ObjectTypes.erase(ObjectTypes.begin(),ObjectTypes.end());
  ObjectTypes.ClassNames.erase(ObjectTypes.ClassNames.begin(),
			       ObjectTypes.ClassNames.end());
  ObjectTypes.ObjectNames.erase(ObjectTypes.ObjectNames.begin(),
				ObjectTypes.ObjectNames.end());
}

/*F ReadInClassNamePairs(in) . . . . . . . . . . . . . . . . . . DataSetOfObjectsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
bool DataSetOfObjectsClass::ReadInClassNamePairs(istream& in) {
  bool result = false;
  ReInitializeObjectNames();
  if(ReadClassPairs)
    {
      if(CheckReadKeyWord(in,ClassNamePairsKeyWord))
        result = ObjectTypes.Read(in);
      else
	result = false;
    }
  return result;
}
/*F ReadInClassNamePairsWithoutKey(in) . . . . . . . . . . . . . . . . . . DataSetOfObjectsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
bool DataSetOfObjectsClass::ReadInClassNamePairsWithoutKeyWord(istream& in) {
  bool result = false;
  ReInitializeObjectNames();
  if(ReadClassPairs)
    {
      result = ObjectTypes.Read(in);
    }
  return result;
}

/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . DataSetOfObjectsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataSetOfObjectsClass::CopyClone(Identify *objc)
{
  DataSetOfObjectsClass *objcfull = (DataSetOfObjectsClass *) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . DataSetOfObjectsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataSetOfObjectsClass::Clone()
{
  DataSetOfObjectsClass* id = new DataSetOfObjectsClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . DataSetOfObjectsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**    The AllowedClasses are not encoded or decoded
**
**  REMARKS
**
*/
bool DataSetOfObjectsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  result = result && AllowedClasses.EncodeThis(buffer);
  result = result && ObjectTypes.EncodeThis(buffer);
  result = result && Encode(buffer,IDCount);
  result = result && Encode(buffer,PrintMode);
  result = result && Encode(buffer,ClassPrintMode);
  result = result && Encode(buffer,ClassEndDelimitor);
  result = result && AvailablePrintModes.EncodeThis(buffer);
  result = result && BoolEncode(buffer,ReadClassPairs);
  result = result && BoolEncode(buffer,ReadAllowedClasses);
  
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . DataSetOfObjectsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**    The AllowedClasses are not encoded or decoded
**
**  REMARKS
**
*/
bool DataSetOfObjectsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
  result = result && AllowedClasses.DecodeThis(buffer);
  result = result && ObjectTypes.DecodeThis(buffer);
  result = result && Decode(buffer,IDCount);
  result = result && Decode(buffer,PrintMode);
  result = result && Decode(buffer,ClassPrintMode);
  result = result && Decode(buffer,ClassEndDelimitor);
  result = result && AvailablePrintModes.DecodeThis(buffer);
  result = result && BoolDecode(buffer,ReadClassPairs);
  result = result && BoolDecode(buffer,ReadAllowedClasses);

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
BaseDataObject * DataSetOfObjectsClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataSetOfObjects();
}
 
/*F ReadInAttributeTypes(in)  . . . . . . . . . . read in new attribute types
**
**  DESCRIPTION
**    in: The input stream
**
**  REMARKS
**
*/
bool DataSetOfObjectsClass::ReadInAttributeTypes(istream& in)
{
  bool result = true;
  setIDCount(PointerToAllowedClasses()->getIDCount());
  
  StreamObjectInput str(in,' ');
  String spec = str.ReadNext();
  if(spec == "ObjectClasses:")
    {
      spec = str.ReadNext();
      while(spec == "DataType:" && result)
        {
          DataObjectClass inputc;
          inputc.ReadDataObjectClass(in);

          bool inlist = PointerToAllowedClasses()->IsInList(inputc.NameTag);
          if(inlist)
            {
              if(getDebugLevel() > 1)
                {
                  cout << "DataType: Derived from ";
                  cout << inputc.NameTag;
                  cout << "\n";
                }
	      DataObjectClass *clsorig = (DataObjectClass *)
		PointerToAllowedClasses()->GetObjectClass(inputc.NameTag);
	      DataObjectClass *cp = (DataObjectClass *) clsorig->Clone();
	      cp->SetDebugLevel(getDebugLevel());
	      
	      cp->Identification = IDCount;
	      IDCount++;
	      
	      cp->SubClass = inputc.NameTag;
	      cp->Description = inputc.Description;
	      cp->NameTag = str.ReadNext();
	      
	      result = result && cp->Read(in,*this);
	      PointerToAllowedClasses()->AddObjectClass(*cp);
	      if(getDebugLevel() > 1)
		{
		  cout << "Begin: ------------ Data Type Added: --------------------\n";
		  cp->print(cout);
		  cout << "\nEnd:   ------------ Data Type Added: --------------------\n";
		  
		}
            }
          else
            {
              cerr << "Object '";
              cerr << inputc.NameTag;
              cerr << "' not found in standard list of classes\n";
	      cerr << "Set of Class Names available" << endl;
	      cerr << "Pointers: " << StandardAllowedClasses << "  " << PointerToAllowedClasses() << endl;
	      PointerToAllowedClasses()->ListOfClassNames().print(cerr);
	      cerr << "\n";
              result = false;
            }

          spec = str.ReadNext();
        }
      if(!(spec == "END"))
        {
          cerr << "Expected END or 'DataType:' and got ";
          cerr << spec;
          cerr << "\n";
          result = false;
        }
    }
  else
    {
      cout << "Expected 'ObjectClasses:' got ";
      unsigned int x = spec.c_str()[spec.size()-1];
      unsigned int x1 = spec.c_str()[spec.size()-2];
      unsigned int x2 = spec.c_str()[spec.size()-3];
      cout << "'" << spec << "' " << spec.size() << " '" << x << "'"<< " '" << x1 << "'"<< " '" << x2 << "'";
      cout << "\n";
      result = false;
    }
  PointerToAllowedClasses()->setIDCount(getIDCount());

  return result;
}
/*F mode = GetPrintMode() . . . . . . . . . . .  print mode of CoreDataObject
**
**  DESCRIPTION
**    mode: The mode of printing of the CoreDataObject:
**
**  REMARKS
**
*/
unsigned int DataSetOfObjectsClass::GetPrintMode() const
{
  return PrintMode;
}
/*F mode = GetClassPrintMode()  . . .  print mode of class description itself
**
**  DESCRIPTION
**    mode: The mode of printing of the CoreDataObject class description
**
**  REMARKS
**
*/
unsigned int DataSetOfObjectsClass::GetClassPrintMode() const
{
  return ClassPrintMode;
}
/*F SetPrintMode(mode)  . . . . . . . .  set print mode of the CoreDataObject
**
**  DESCRIPTION
**    mode: The print mode to set for the CoreDataObject
**
**    The routine uses the string mode representation and sets the
**    corresponding integer mode.  If the mode is not
**    in the AvailablePrintModes, then the mode remains unchanged.
**
**    This mode is used as the objects are being printed.
**
**  REMARKS
**
*/
bool DataSetOfObjectsClass::SetPrintMode(const String& mode)
{
  bool ans = true;
  
  if(AvailablePrintModes.IsInList(mode))
    PrintMode = AvailablePrintModes[mode];
  else
    {
      cout << mode << " is not a valid print mode\n";
      ans = false;
    }
  return ans;
}
/*F SetClassPrintMode(mode) . . .  set print mode of class description itself
**
**  DESCRIPTION
**    mode: The print mode to set for the CoreDataObject 
**          class description itself 
**
**    The routine uses the string mode representation and sets the
**    corresponding integer mode.  If the mode is not
**    in the AvailablePrintModes, then the mode remains unchanged.      
**
**  REMARKS
**
*/
bool DataSetOfObjectsClass::SetClassPrintMode(const String& mode)
{
  bool ans = true;
  
  if(AvailablePrintModes.IsInList(mode))
    ClassPrintMode = AvailablePrintModes.IDfromName(mode);
  else
    {
      cout << mode << " is not a valid print mode\n";
      ans = false;
    }
  return ans;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . DataSetOfObjectsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataSetOfObjectsClass*& obj)
{
  obj = new DataSetOfObjectsClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . .  BaseDataSetOfObjects
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataSetOfObjects*& obj)
{
  obj = new BaseDataSetOfObjects;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataObjectClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataObjectClass*& obj)
{
  obj = new DataObjectClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataObject*& obj)
{
  obj = new BaseDataObject;
  return obj->DecodeThis(buffer);
}

/*F ans = IsInList(name)  . . . . . . . . . . . . . . . . . . . class exists?
**
**  DESCRIPTION
**    name: The name of the class
**    ans: True if the class is in the list of allowed classes
**
**  REMARKS
**
*/
bool DataSetOfObjectsClass::IsInList(const String& name)
{
  return AllowedClasses.IsInList(name);
}
 
/*F names = ListOfClassNames()  . . . . . . . . . . . . DataSetOfObjectsClass
**
**  DESCRIPTION
**    names: The set of class names
**
**  REMARKS
**
*/
ObjectList<String> DataSetOfObjectsClass::ListOfClassNames()
{
  return AllowedClasses.ListOfObjectNames();
}

/*F ans = ReplaceObjectTypes(pairs) . . . . . . . .  replace class-name pairs
**
**  DESCRIPTION
**    pairs: Class-Name pairs
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSetOfObjectsClass::ReplaceObjectTypes(const ObjectNameClassPairs& pairs)
{
  ObjectTypes = pairs;
  return true;
} 
/*F level = DebugLevel()  . . . . . . . . . . .  return the debug print level
**
**  DESCRIPTION
**    level: The debug print level
**
**    The levels are:
**    - DEBUG_LEVEL_0: No Debug Printing
**    - DEBUG_LEVEL_1: Some essential printing
**    - DEBUG_LEVEL_2: Can be very detailed
**
**  REMARKS
**
*/
unsigned int DataSetOfObjectsClass::DebugLevel()
{
  return PrintMode/1000;
}
 
/*F id = getIDCount() . . . . . . . . . . . . . . .  Get the current ID count
**
**  DESCRIPTION
**    id: The ID count
**
**    This retrieves the IDCount so it can be transfered to another class structure.
**
**  REMARKS
**
*/
unsigned int DataSetOfObjectsClass::getIDCount()
{
  return IDCount;
}
/*F setIDCount(idcount) . . . . . . . . . . . . . .  set the current ID count
**
**  DESCRIPTION
**    idcount: set the ID count
**
**    This set the IDCount so it can be transfered to another class structure.
**
**  REMARKS
**
*/
void DataSetOfObjectsClass::setIDCount(unsigned int idcount)
{
  IDCount = idcount;
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
bool DataSetOfObjectsClass::WriteAsLine(ostream& out)
{
  ObjectList<String> names = ListOfClassNames();
  out << "(" << NameTag << ") " << " with a size of " << names.size() << endl;
  return true;
}
/*F ans = WriteAsASCII(out) . . . . . . . . . . . . . . DataSetOfObjectsClass
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
bool DataSetOfObjectsClass::WriteAsASCII(ostream& out)
{
  bool result = true;
  DataObjectClass *cls;
  ObjectList<String> names = AllowedClasses.ListOfObjectNames();
  ObjectList<String>::iterator name;
  out << "ObjectClasses:" << endl;
  for(name=names.begin(); name != names.end() && result; name++)
    {
      cls = this->GetObjectClass(*name);
      result = cls->WriteAsASCII(out);
    }
  out << "END" << endl;
  ObjectTypes.WriteAsASCII(out);
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . DataSetOfObjectsClass
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
bool DataSetOfObjectsClass::WriteAsLatex(ostream& out)
{
  bool result = true;
  DataObjectClass *cls;
  ObjectList<String> names = AllowedClasses.ListOfObjectNames();
  ObjectList<String>::iterator name;

  out << "\\begin{description}" << endl;
  for(name=names.begin(); name != names.end() && result ; name++)
    {
      cls = GetObjectClass(*name);
      out << "\\item " << cls->WriteAsLine(out) << endl;
    }
  out << "\\end{description}" << endl;

  for(name=names.begin(); name != names.end() && result ; name++)
    {
      cls = GetObjectClass(*name);
      cls->WriteAsLatex(out);
    }

  return true;
}

/*F types = getNameClassPairs() . . . . . . . . . . . . DataSetOfObjectsClass
**
**  DESCRIPTION
**    types: the class name pairs
**
**  REMARKS
**
*/
ObjectNameClassPairs& DataSetOfObjectsClass::getNameClassPairs()
{
  return ObjectTypes;
}
/*S BaseDataObject
 */ 
/*F BaseDataObject()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataObject::BaseDataObject()
{
  NameTag = COREOBJECTS_BASE_NAME;
  Identification = COREOBJECTS_BASE_ID;
  DataType = COREOBJECTS_BASE_ID;
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataObject(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataObject::BaseDataObject(const BaseDataObject& data)
  : Identify(data),
    DataType(data.DataType),
    EncodeDecodeClass(data.EncodeDecodeClass)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataObject
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataObject::Read(istream& in, DataObjectClass* objc)
{
  if((*objc).Identification){}
  
  StreamObjectInput inobject(in,' ');
  NameTag = inobject.ReadNext();
  
  return true;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataObject
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataObject::Read(istream& in, DataObjectClass* objc, const String& name)
{
  if((*objc).Identification){}
  if(name.size() <= 1)
    {
      StreamObjectInput inobject(in,' ');
      NameTag = inobject.ReadNext();
    }
  
  return true;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataObject::print(ostream& out) const
{
  out << "Name(" << Identification << "): " << NameTag << "  ";
  out << "(" << DataType << ")  ";
  
  if(NameTag != EncodeDecodeClass)
    {
      cout << "[Encode: ";
      cout << EncodeDecodeClass << "]  ";
    }
  
  return out;
}

 
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .  clone a copy
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataObject::Clone()
{
  BaseDataObject *obj = new BaseDataObject(*this);

  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .  copy a clone
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataObject::CopyClone(Identify *obj)
{
  BaseDataObject *objo = (BaseDataObject *) obj;
  
  *this = *objo;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataObject::EncodeThis(CommBuffer& buffer)
{
  bool result = Identify::EncodeThis(buffer);
  result = result && Encode(buffer,DataType);
  result = result && Encode(buffer,EncodeDecodeClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataObject::DecodeThis(CommBuffer& buffer)
{
  bool result = Identify::DecodeThis(buffer);
  result = result && Decode(buffer,DataType);
  result = result && Decode(buffer,EncodeDecodeClass);
  return result;
}
 
/*F ans = operator==(obj) . . . . . . . . . . . . . . . . .  virtual equality
**
**  DESCRIPTION
**    obj: The object to compare with
**    ans: True if equal (default case is if the names are equal)
**
**  REMARKS
**
*/
bool BaseDataObject::operator==(BaseDataObject *obj)
{
  return NameTag == obj->NameTag;
}
/*F ans = operator<(obj) . . . . . . . . . . . . . . . . .  virtual equality
**
**  DESCRIPTION
**    obj: The object to compare with
**    ans: True if equal (default case is if the names are equal)
**
**  REMARKS
**
*/
bool BaseDataObject::operator<(BaseDataObject *obj)
{
  return NameTag < obj->NameTag;
}
/*F ans = operator>(obj) . . . . . . . . . . . . . . . . .  virtual equality
**
**  DESCRIPTION
**    obj: The object to compare with
**    ans: True if equal (default case is if the names are equal)
**
**  REMARKS
**
*/
bool BaseDataObject::operator>(BaseDataObject *obj)
{
  return !(operator<(obj));
}
/*F ans = Write(out,objc) . . . . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object according to the mode in the object class
**
**  REMARKS
**
*/
bool BaseDataObject::Write(ostream& out, DataObjectClass *objc)
{
  bool result = true;
  unsigned int mode = objc->getPrintMode();
  switch(mode)
    {
    case CORE_PRINT_ID_QUIET:
      break;
    case CORE_PRINT_ID_LINE:
      result = WriteAsLine(out,objc);
      break;
    case CORE_PRINT_ID_WRITE:
      result = WriteAsASCII(out,objc);
      break;
    case CORE_PRINT_ID_DETAILED:
      print(out);
      break;
    case CORE_PRINT_ID_LATEX:
      result = WriteAsLatex(out,objc);
      break;
    default:
      break;
    }
  return result;
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
bool BaseDataObject::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << "(" << objc->NameTag << ") " << NameTag << endl;
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
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
bool BaseDataObject::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  return true;
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
bool BaseDataObject::WriteAsLatex(ostream& out, DataObjectClass* cls)
{
  out << endl;
  out << "\\begin{verbatim}" << endl;
  print(out);
  out << endl << "\\item{verbatim}" << endl;
  out << "\\\\" << endl;

  return true;
}
/*F SetType(type) . . . . . . . . . . . . . . . . . . . . . .  get class type
**
**  DESCRIPTION
**    type: The object class type
**
**  REMARKS
**    This is only accessable by friends of the class
**    (it will be managed by the CoreObjectClass)
**
*/
void BaseDataObject::SetType(unsigned int type)
{
  DataType = type;
}
/*F t = GetType() . . . . . . . . . . . . . . . . . . . . . .  get class type
**
**  DESCRIPTION
**    t: The object class type
**
**  REMARKS
**    This is only accessable by friends of the class
**    (it will be managed by the CoreObjectClass)
**
*/
unsigned int BaseDataObject::GetType() const
{
  return DataType;
}

/*S DataObjectClass
 */
/*C DataObjectClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataObjectClass::DataObjectClass()
  : PrintMode(CORE_PRINT_ID_DETAILED),
    ClassPrintMode(CORE_PRINT_ID_DETAILED),
    Description("Base Object Class")
{
  NameTag = COREOBJECTS_BASE_NAME;
  Identification = COREOBJECTS_BASE_ID;
  SubClass = "Root";
  EncodeDecodeClass = NameTag;
} 
/*F DataObjectClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataObjectClass::DataObjectClass(const DataObjectClass& data)
  : BaseDataObject(data),
    PrintMode(data.PrintMode),
    ClassPrintMode(data.ClassPrintMode),
    SubClass(data.SubClass),
    Description(data.Description)
    
{
} 
 
/*F DataObjectClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**    The default print modes are set to detailed.
**
**  REMARKS
**
*/
DataObjectClass::DataObjectClass(const int id, 
                                 const String& name,
                                 const String& descr)
  : PrintMode(CORE_PRINT_ID_DETAILED),
    ClassPrintMode(CORE_PRINT_ID_DETAILED),
    Description(descr)
{
  NameTag = name;
  Identification = id;
  
  SubClass = "Identify";
  EncodeDecodeClass = "Object";
}
 
/*F in1 = ReadDataObjectClass(in) . . . . . . . . . . . . . . DataObjectClass
**
**  DESCRIPTION
**    in,in1: The input stream
**
**    One line is read in and the name and the description
**    (separated by a blank) are read in.  This is used to 
**    read in the base.
**
**  REMARKS
**
*/
istream& DataObjectClass::ReadDataObjectClass(istream& in)
{
  Description.ReadFullLine(in);
  
  Description.IsolateNextWord(NameTag,' ');
  Description.EliminateLeadingBlanks();
  return in;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataObjectClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataObjectClass::print(ostream& out) const
{
  out << "DataType: ";
  Identify::print(out);
  out << "  P(" << PrintMode << " " << ClassPrintMode << ") ";
  if(SubClass.size() > 1)
    out << " SubClass: " << SubClass << " ";
  else
    out << " SubClass: DataObjectClass  ";
  if(EncodeDecodeClass != NameTag)
    out << "{EncodeClass: " << EncodeDecodeClass << "}  ";
  out << "(";
  out << Description << ") ";
  
  return out;
}
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . . . DataObjectClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard object classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataObjectClass, there is no further information.
**
**  REMARKS
**
*/
bool DataObjectClass::Read(istream& in, DataSetOfObjectsClass& cls)
{
  return true;
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
BaseDataObject * DataObjectClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataObject();
  return obj;
}
  
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataObjectClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataObjectClass::CopyClone(Identify* objc)
{
  DataObjectClass *obj = (DataObjectClass *) objc;
  
  *this = *obj;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataObjectClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataObjectClass::Clone()
{
  DataObjectClass* id = new DataObjectClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataObjectClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataObjectClass::EncodeThis(CommBuffer& buffer)
{
  bool result = Identify::EncodeThis(buffer);
  result = result && Encode(buffer,PrintMode);
  result = result && Encode(buffer,ClassPrintMode);
  result = result && SubClass.EncodeThis(buffer);
  result = result && EncodeDecodeClass.EncodeThis(buffer);
  result = result && Description.EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataObjectClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataObjectClass::DecodeThis(CommBuffer& buffer)
{
  bool result = Identify::DecodeThis(buffer);
  result = result && Decode(buffer,PrintMode);
  result = result && Decode(buffer,ClassPrintMode);
  result = result && SubClass.DecodeThis(buffer);
  result = result && EncodeDecodeClass.DecodeThis(buffer);
  result = result && Description.DecodeThis(buffer);
  return result;
}
/*F level = getDebugLevel() . . . . . . . . . . . . get the debug level (0-4)
**
**  DESCRIPTION
**    level: The debug level of the object
**
**  REMARKS
**
*/
unsigned int DataObjectClass::getDebugLevel()
{
  unsigned int s1 = PrintMode/DEBUG_LEVEL_MULT;
  unsigned int s2 = s1 / 10;
  unsigned int debuglevel = s1 - s2*10;
  return debuglevel;
}
 
/*F SetDebugLevel(debug)  . . . . . . . . . . . . . . . . . . . set the level
**
**  DESCRIPTION
**    debug: The debug level
**
**  REMARKS
**
*/
void DataObjectClass::SetDebugLevel(const unsigned int debug)
{
  unsigned int debuglevel = getDebugLevel();
  unsigned int s1 = PrintMode - debuglevel * DEBUG_LEVEL_MULT;
  PrintMode = s1 + debug * DEBUG_LEVEL_MULT;
}
/*F mode = getPrintMode()
**
**  DESCRIPTION
**    mode: The print mode
**
**  REMARKS
**
*/
unsigned int DataObjectClass::getPrintMode()
{
  unsigned int s1 = PrintMode/CORE_PRINT_BASE;
  unsigned int s2 = s1 / 100;
  unsigned int mode = s1 - s2*100;
  return mode;
}
 
/*F SetPrintMode(mode)  . . . . . . . . . . . . . . . . . . . .  set the mode
**
**  DESCRIPTION
**    mode: The print mode
**
**  REMARKS
**
*/
void DataObjectClass::SetPrintMode(const unsigned int mode)
{
  unsigned int oldmode = getPrintMode();
  unsigned int s1 = PrintMode - oldmode * CORE_PRINT_BASE;
  PrintMode = s1 + mode * CORE_PRINT_BASE;
}
/*F mode = getClassPrintMode()  . . . . . . . . . .  how the class is printed
**
**  DESCRIPTION
**    mode: The print mode
**
**  REMARKS
**
*/
unsigned int DataObjectClass::getClassPrintMode()
{
  unsigned int s1 = ClassPrintMode/CORE_PRINT_BASE;
  unsigned int s2 = s1 / 100;
  unsigned int mode = s1 - s2*100;
  return mode;
}
 
/*F SetClassPrintMode(mode) . . . . . . . . . . . . . . . . . .  set the mode
**
**  DESCRIPTION
**    mode: The print mode
**
**  REMARKS
**
*/
void DataObjectClass::SetClassPrintMode(const unsigned int mode)
{
  unsigned int oldmode = getClassPrintMode();
  unsigned int s1 = ClassPrintMode - oldmode * CORE_PRINT_BASE;
  ClassPrintMode = s1 + mode * CORE_PRINT_BASE;
}

/*F AddAvailablePrintMode(id,mode)  . . . . . . . . add mode to list of modes
**
**  DESCRIPTION
**    id: The interger identification of the mode (used internally)
**    mode: The string description of the mode.
**
**    If the mode is already in the list, then this would overwrite it.
**
**  REMARKS
**
*/
void DataSetOfObjectsClass::AddAvailablePrintMode(const int id,const String& mode)
{
  AvailablePrintModes[mode] = id;
} 
/*F SetUpStandardPrintModes() . . . . . . . . . . . . .  short,long and latex
**
**  DESCRIPTION
**    This sets up the standard available print modes: the name-id 
**    correspondences.
**
**  REMARKS
**
*/
void DataSetOfObjectsClass::SetUpStandardPrintModes()
{

  AddAvailablePrintMode(CORE_PRINT_ID_QUIET,CORE_PRINT_NAME_QUIET);
  AddAvailablePrintMode(CORE_PRINT_ID_LINE,CORE_PRINT_NAME_LINE);
  AddAvailablePrintMode(CORE_PRINT_ID_DETAILED,CORE_PRINT_NAME_DETAILED);
  AddAvailablePrintMode(CORE_PRINT_ID_LATEX,CORE_PRINT_NAME_LATEX);

  AddAvailablePrintMode(DEBUG_LEVEL_0,DEBUG_LEVEL0_NAME);
  AddAvailablePrintMode(DEBUG_LEVEL_1,DEBUG_LEVEL1_NAME);
  AddAvailablePrintMode(DEBUG_LEVEL_2,DEBUG_LEVEL2_NAME);
  AddAvailablePrintMode(DEBUG_LEVEL_3,DEBUG_LEVEL3_NAME);
  AddAvailablePrintMode(DEBUG_LEVEL_4,DEBUG_LEVEL4_NAME);
}
 
/*F mode = GetPrintMode(modename) . . . . . . . . . . .  mode id from keyword
**
**  DESCRIPTION
**    modename: The keyword for the print mode
**    mode: the id
**
**  REMARKS
**
*/
unsigned int DataSetOfObjectsClass::GetPrintMode(const String modename)
{
  unsigned int mode;
  
  if(AvailablePrintModes.IsInList(modename))
    {
      mode = AvailablePrintModes.IDfromName(modename);
    }
  else
    {
      cerr << "Print Mode Name Not found: " << modename << " returning zero\n";
      mode = 0;
    }
  return mode;
}
 
/*F ans = IsOfClass(object,subclass)  . . . . true if object of type subclass
**
**  DESCRIPTION
**    object: The object
**    subclass: The subclass name
**    ans: true if object is of type subclass
**
**  REMARKS
**
*/
bool DataSetOfObjectsClass::IsOfClass(BaseDataObject& object,const String& subclass)
{
  bool result = false;
  unsigned int type = object.GetType();
  DataObjectClass *cls = GetObjectClass(type);
  if(cls != NULL)
    {
      result = IsOfClass(cls->NameTag,subclass);
    }
  else
    {
      cerr << "Class of Type: " << type << " not found (from object: '" << object.NameTag << "')" << endl;
      result = false;
    }

  return result;
}

/*F ans = IsOfClass(reference,subclass) .  true if reference of type subclass
**
**  DESCRIPTION
**    reference: The reference class
**    subclass: The subclass
**    ans: true if reference is of type subclass
**
**  REMARKS
**
*/
bool DataSetOfObjectsClass::IsOfClass(const String& reference, const String& subclass)
{
  bool result = false;
  if(reference == subclass)
    {
      result = true;
    }
  else if(!(reference == COREOBJECTS_BASE_NAME))
    {
      if(IsInList(reference))
	{
	  DataObjectClass *cls = GetObjectClass(reference);
	  result = IsOfClass(cls->SubClass,subclass);
	}
      else
	{
	  cerr << "Class not in list of Classes: '" << reference << "'" << endl;
	  result = false;
	}
    }
  return result;
}

/*C SetLoopOfPrintModes . . . . . . . . . . . . . . . .  set class print mode
**
**  DESCRIPTION
**    This class sets the print mode of a DataObjectClass.  The
**    constructor has two arguments:
**    - DataObjectPrint: true if the object is to be printed and false
**      if the class itself is to be printed
**    - PrintMode: The actual print mode to set to
**
**  REMARKS
**
*/
class SetLoopOfPrintModes
{
  int Mode;
  bool DataObjectPrint;
  DataSetOfObjectsClass& ClassSet;
  
public:
  SetLoopOfPrintModes(DataSetOfObjectsClass& set,bool printobject, const int mode)
    : Mode(mode),
      DataObjectPrint(printobject),
      ClassSet(set)
    {
    }
  void operator()(const String& name)
    {
      DataObjectClass *prop = 
        (DataObjectClass *) ClassSet.GetObjectClass(name);

      if(DataObjectPrint)
        prop->SetPrintMode(Mode);
      else
        prop->SetClassPrintMode(Mode);
    }
};
 
/*F SetPrintModeOfPresentClasses(printobject,mode)  . . . . .  set print mode
**
**  DESCRIPTION
**    printobject: true if object, false if class is to be printed
**    mode: The print mode to set the corresponding object to
**
**  REMARKS
**
*/
void DataSetOfObjectsClass::SetPrintModeOfPresentClasses(bool printobject, const int mode)
{
  SetLoopOfPrintModes pmode(*this,printobject,mode);
  ObjectList<int> types;
  ObjectList<String> names = AllowedClasses.ListOfObjectNames(types);
  
  for_each(names.begin(),
	   names.end(),
	   pmode);
}
 

/*F c = GetObjectClass(id)  . . . . . . get the class information from the ID
**
**  DESCRIPTION
**    id: The identification
**    c: The data class description
**
**    This retrieves the data class information
**
**  REMARKS
**
*/
DataObjectClass * DataSetOfObjectsClass::GetObjectClass(const unsigned int id)
{
  return (DataObjectClass *) AllowedClasses.GetObject(id);
}
/*F c = GetObjectClass(name)  . . . . . . get class information from the name
**
**  DESCRIPTION
**    name: The name of the class information
**    c: The object class information
**
**  REMARKS
**
*/
DataObjectClass * DataSetOfObjectsClass::GetObjectClass(const String& name)
{
  return (DataObjectClass *) AllowedClasses.GetObject(name);
}
/*F ans = AddClassObject(c) . . . . . . . . . . . . . adds class info to list
**
**  DESCRIPTION
**    c: The object class information
**
**    The information is added to the list. 
**
**  REMARKS
**    The list is a PropertyListByID.  The object is converted by 
**    InfoAsPropertyByID.
**
*/
bool DataSetOfObjectsClass::AddObjectClass(DataObjectClass& c)
{
  return AllowedClasses.AddObject(&c);
}
/*F added = MergeSetOfObjectClasses(classes)  . . . . .  merge in new classes
**
**  DESCRIPTION
**    classes: The classes to be merged in
**    added: The number of new classes added.
**
**  REMARKS
**
*/
unsigned int DataSetOfObjectsClass::MergeSetOfObjectClasses(DataSetOfObjectsClass& classes)
{
  unsigned int ret = 0;
  DataSetOfObjectsClass *set = PointerToAllowedClasses();
  if(set != &classes)
    {
      cout << "Merge Classes  " << NameTag << "  "  << classes.NameTag << endl;
      if(set != NULL)
	ret = set->AllowedClasses.MergeSetOfObjects(&classes.AllowedClasses);
    }
  return ret;
}
/*F ChangeEndDelimitor(name)  . . . . . . . . . . . .  DataSetOfObjectsClass
**
**  DESCRIPTION
**    name: The new Delimitor (no spaces allowed)
**
**  REMARKS
**
*/
void DataSetOfObjectsClass::ChangeEndDelimitor(const String& delim)
{
  ClassEndDelimitor = delim;
}
/*F objc = CloneClassFromName(name) . . . . . . . . . . get instance of class
**
**  DESCRIPTION
**    name: The name of the object class
**    objc: The object class
**
**  REMARKS
**
*/
Identify *
DataSetOfObjectsClass::CloneClassFromName(String& name)
{
  DataObjectClass * c = PointerToAllowedClasses()->GetObjectClass(name);
  Identify *final = NULL;

  if(c == NULL || c->NameTag != name)
    {
      cerr << "Class to Clone not found: '" << name << "'" << endl;
    }
  else
    {
      final = c->Clone();
    }
  return final;
}
/*F nums = TranslateClassNames(names) . . .  translate class names to numbers
**
**  DESCRIPTION
**    names: The classes as names
**    nums: The classes as integers
**
**  REMARKS
**
*/
ObjectList<int>& DataSetOfObjectsClass::TranslateClassNames(const ObjectList<String>& names)
{
  return AllowedClasses.NamesToIDs(names);
}
 
/*F classes = PointerToAllowedClasses() . . . . . . . . DataSetOfObjectsClass
**
**  DESCRIPTION
**    classes: The set of classes
**
**    This in the default case points to itself (this).  
**    It is meant for the case where the set of standard objects
**    is some external (possibly global) object.
**
**  REMARKS
**
*/
DataSetOfObjectsClass *DataSetOfObjectsClass::PointerToAllowedClasses()
{
  return this;
}
/*F ans = WriteAsLine(out)  . . . . . . . . . . . . . . . . . DataObjectClass
**
**  DESCRIPTION
**    out: The output stream
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool DataObjectClass::WriteAsLine(ostream& out)
{
  out << NameTag << ": " << Description << endl;
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . . DataObjectClass
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
bool DataObjectClass::WriteAsASCII(ostream& out)
{
  out << "DataType: " << endl;
  out << SubClass << " " << Description << endl;
  out << NameTag << endl;

  return true;
}
/*F ans = WriteAsLatex(out) . . . . . . . . . . . . . . . . . DataObjectClass
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
bool DataObjectClass::WriteAsLatex(ostream& out)
{
  out << endl;
  out << "\\begin{verbatim}" << endl;
  print(out);
  out << endl << "\\{verbatim}" << endl;
  out << "\\\\" << endl;

  return true;
}

/*S BasicPointerUtilities
 */
/*F ans = BoolEncode(buffer,b)  . . . . . . . . . . . . . . .  boolean encode
**
**  DESCRIPTION
**    buffer: The buffer
**    b: The boolean to encode
**    ans: true if successful
**
**  REMARKS
**
*/
bool BoolEncode(CommBuffer& buffer, bool b)
{
  int ans = 0;
  if(b)
    ans = 1;
  return Encode(buffer,ans);
}
 
/*F ans = BoolDecode(buffer,bval) . . . . . . . . . . . . . .  boolean decode
**
**  DESCRIPTION
**    buffer: The buffer
**    b: The boolean to decode
**    ans: true if successful
**    
**  REMARKS
**
*/
bool BoolDecode(CommBuffer& buffer, bool& bval)
{
  int val;
  bool ans = Decode(buffer,val);
  if(ans)
    {
      if(val == 1)
        bval = true;
      else
        bval = false;
    }
  
  return ans;
}
/*F newobj = PointerClone(obj)  . . . . . . . . . . . .  clone pointer object
**
**  DESCRIPTION
**    obj: Object to be cloned
**    newobj: The new cloned object
**
**  REMARKS
**
*/
BaseDataObject *PointerClone(BaseDataObject *obj)
{
  BaseDataObject *newobj;
  
  if(obj != 0)
    newobj = (BaseDataObject *) obj->Clone();
  else
    newobj = 0;
  return newobj;
}
/*F ans = PointerEncode(buffer,obj)  . . . . . . . . . . . . . encode pointer object
**
**  DESCRIPTION
**    buffer: The buffer
**    obj: The pointer of the object to be decoded
**    ans: True if successful
**    
**  REMARKS
**
*/
bool PointerEncode(CommBuffer &buffer, BaseDataObject *obj)
{
  bool result = true;
  if(obj != NULL)
    {
      result = result && Encode(buffer,obj->EncodeDecodeClass);
      result = result && obj->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);
  return result;
} 
/*F ans = PointerDecode(buffer, obj)  . . . . . . . . . decode pointer object
**
**  DESCRIPTION
**    buffer: The buffer
**    obj: The pointer of the object to be decoded
**    ans: True if successful
**
**  REMARKS
**
*/
bool PointerDecode(CommBuffer &buffer, BaseDataObject *&obj)
{
  bool result = true;

  String name;
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    DecodeFromName(result,buffer,name,(Identify *&) obj);

  return result;
}
 
/*F ans = PointerObjectRead(in,obj,cls,notdefined)  .  read an object pointer
**
**  DESCRIPTION
**    in: The input stream
**    obj: The object to read in
**    cls: The class of the object to read in
**    notdefined: The message to print when not defined
**    ans: True if unsuccessful
**
**  REMARKS
**
*/
bool PointerObjectRead(istream& in, BaseDataObject *&obj,DataObjectClass *cls, String& notdefined)
{
  bool result = true;
  if(cls != NULL)
    {
      obj = cls->BaseDataObjectExample();
      result = obj->Read(in,cls,cls->NameTag);
    }
  else
    {
      cerr << notdefined << endl;
      result = false;
    }
  return result;
} 
/*F PointerPrint(out,title,noobject,obj)  . . . . . . .  print pointer object
**
**  DESCRIPTION
**    out: The output stream
**    title: The title of the object
**    noobject: To be printed if the object is not there
**    obj: The pointer to the object
**
**  REMARKS
**
*/
void PointerPrint(ostream& out, const String& title, const String& noobject, BaseDataObject *obj)
{
  out << title;
  if(obj != 0)
    obj->print(out);
  else
    out << noobject;
}
 

/*F ans = PointerClassRead(in,obj,classtype,set,notdefined) read a class pointer
**
**  DESCRIPTION
**    in: The input stream
**    obj: The class to read in
**    classtype: The name of the base class of the class to be read in
**    set: The set of allowed classes
**    notdefined: The name to use in error messages
**    ans: True if unsuccessful
**
**  REMARKS
**
*/
bool PointerClassRead(istream& in,DataObjectClass *&obj,
		      const String& classtype,
		      DataSetOfObjectsClass &set, 
		      const String& notdefined)
{
  bool result = true;
  StreamObjectInput str(in,' ');

  String baseS = str.ReadNext();
  if(set.IsOfClass(baseS,classtype))
    {
      if(set.PointerToAllowedClasses()->IsInList(baseS))
	{
	  obj = (DataSetOfObjectsClass *) set.PointerToAllowedClasses()->GetObjectClass(baseS)->Clone();
	}
      else
	{
	  cerr << "Not found is set of classes: '" << notdefined << "'" << endl;
	  result = false;
	}
    }
  else
    {
      cerr << "Specified Class: '" << baseS << "' not a derived class of '" << classtype << "'" << endl;
      result = false;
    }

  return result;
}
/*S BasicUtilities
 */
 
/*F initializeNames(obj,classname)  . . . . . . .  name and encode and decode
**
**  DESCRIPTION
**    obj: The object to initialize
**    classname: The classname to initialize the EncodeDecodeClass to
**
**  REMARKS
**
*/
void initializeNames(BaseDataObject *obj, String& classname)
{
  obj->NameTag = classname;
  obj->EncodeDecodeClass.AppendToEnd(classname);
}
/*F newclasses = SetOfDerivedClasses(classes,baseclasses) .  from baseclasses
**
**  DESCRIPTION
**    classes: The complete set of class objects
**    baseclasses: The names of the base classes
**    newclasses: The names of the derived classes
**
**  REMARKS
**
*/
ObjectList<String> *SetOfDerivedClasses(DataSetOfObjectsClass *classes, ObjectList<String>& baseclasses)
{
    ObjectList<String> *newclasses = new ObjectList<String>;
    
    ObjectList<String> classnames = classes->ListOfClassNames();
    ObjectList<String>::iterator base,derived;
    for(base = baseclasses.begin(); base != baseclasses.end(); base++)
	{
	    if(classes->IsInList(*base))
		{
		    for(derived = classnames.begin(); derived != classnames.end(); derived++)
			{
			    if(!(*derived == *base))
				{
				    if(classes->IsOfClass(*derived,*base))
					{
					    newclasses->AddObjectIfNotThere(*derived);
					}
				}
			}
		}
	    else
		cerr << "The Class: " << *base << " is not in the list" << endl;
	}
    cout << "=========================================================\n";

    ObjectList<String> inter(*newclasses);
    inter.print(cout);
    cout << endl;
    inter.Intersected(baseclasses);
    inter.print(cout);
    cout << endl;
    newclasses->Remove(inter);
    newclasses->print(cout);
    cout << endl;

    return newclasses;
}
 
/*F WriteSetOfClasses(name,out,classes)
**
**  DESCRIPTION
**    names: The names of the classes to write out
**    out: The output stream
**    classes: The set of classes
**
**  REMARKS
**
*/
void WriteSetOfClasses(ObjectList<String>& names, 
		       ostream& out,
		       DataSetOfObjectsClass& classes)
{
    out << "ObjectClasses:" << endl;
    ObjectList<String>::iterator name;
    for(name = names.begin();
	name != names.end();
	name++)
	{
	    DataObjectClass *objc = classes.GetObjectClass(*name);
	    objc->WriteAsASCII(out);
	    out << endl;
	}
    out << "END" << endl;
}
/*F SetUpClassNamePairs(objects,classes)  . . . . . .  class name pairs setup
**
**  DESCRIPTION
**    objects: The set of objects
**    classes: The set of classes
**
**    This routine sets up the entire set of ClassNamePairs 
**    corresponding to the set of objects within the set of classes
**
**  REMARKS
**
*/
void SetUpClassNamePairs(BaseDataSetOfObjects *objects,
			 DataSetOfObjectsClass *classes)
{
  ObjectList<String> names = objects->ListOfObjectNames();
  ObjectList<String>::iterator name;
  ObjectNameClassPairs namepairs;
  for(name = names.begin(); name != names.end(); name++)
    {
      BaseDataObject *obj = objects->GetObject(*name);
      DataObjectClass *objc = classes->GetObjectClass(obj->GetType());
      namepairs.AddObject(obj->NameTag,objc->NameTag);
    }
  classes->ReplaceObjectTypes(namepairs);
}
/*F AddCoreDataObjectClasses(set) . . . . . . . . . . . . .  register objects
**
**  DESCRIPTION
**    set: The set in which to register classes
**
**  REMARKS
**
*/
void AddCoreDataObjectClasses(DataSetOfObjectsClass& set)
{
  String objdescr("Base Object");
  String setdescr("Base Set of Objects");
  
  DataObjectClass objclass(COREOBJECTS_BASE_ID,COREOBJECTS_BASE_NAME,objdescr);
  DataSetOfObjectsClass setclass(COREOBJECTS_SET_ID,COREOBJECTS_SET_NAME,setdescr);
  
  set.AddObjectClass(objclass);
  set.AddObjectClass(setclass);
}
 
/*F InitialCoreDataObjectEncodeDecodeRoutines() . . . . . . . .  core objects
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void InitialCoreDataObjectEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataObjectClass,BaseDataObject,COREOBJECTS_BASE_NAME);
  EncodeDecodeRegisterClass(DataSetOfObjectsClass,BaseDataSetOfObjects,COREOBJECTS_SET_NAME);
}
/*F ReadInClassNamePairsAndSetOfObjects(in,name,set,oclassses)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool ReadInClassNamePairsAndSetOfObjects(istream& in,
					 String &name,
					 BaseDataSetOfObjects *set,
					 DataSetOfObjectsClass *oclasses)
{
  bool result = true;
  ObjectNameClassPairs namepairs;
  result = result && namepairs.Read(in);
  if(oclasses->getDebugLevel() > 1)
    {
      cout << "Class Name Pairs: " << endl;
      namepairs.print(cout);
      cout << endl;
    }
  oclasses->ReplaceObjectTypes(namepairs);
  result = result && set->Read(in,oclasses,name);

  return result;
}
/*F ans = CheckReadKeyWord(in,key)  . . . . . . . . . . . check input keyword
**
**  DESCRIPTION
**    in: The input stream
**    key: The key to check for
**    ans: True if the key is the next word
**
**  REMARKS
**
*/
bool CheckReadKeyWord(istream& in, String &key)
{
  bool result = true;
  StreamObjectInput str(in,' ');
  String keyword = str.ReadNext();
  if(keyword != key)
    {
      cerr << "Expected '" << key << "' got instead '" << keyword << "'" << endl;
      result = false;
    }
  return result;
}
/*F ans = DecodeFromName(result,buffer,name,str)  . . . . . .  pointer decode
**
**  DESCRIPTION
**    result: true if Decode has been successful 
**    buffer: The buffer to decode from
**    name: The name of the structure
**    str: The pointer to the structure
**    ans: true if successful
**
**  REMARKS
**
*/
bool DecodeFromName(bool result, CommBuffer& buffer, String& name, Identify *&str)
{
  if(result)
    {
      if(name != NoStructure)
        {
          bool (*rout)(CommBuffer&,Identify*&) 
            = (bool (*)(CommBuffer&,Identify*&)) 
            (*SetOfEncodeDecodeRoutines)[name].Routine;
          if(rout != 0)
            {
              result = result && rout(buffer,str);
	      if(!result)
		cerr << "Decode Failed with: '" << name << "'" << endl;
            }
          else
            {
              cerr << "DecodeFromName: Structure not found in SetOfEncodeDecodeRoutines\n";
              cerr << "Structure: " << name << "\n";
              result = false;
            }
        }
    }
  
  return result;
}
 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
 */
