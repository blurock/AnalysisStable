/*  FILE     InstanceObjects.cc
**  PACKAGE  InstanceObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "InstanceObjects" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
**  Version 1.5
*/
 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "LogicalOperations.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "NumericOperations.hh"

#ifndef _unix
extern "C" {
#include "CReadWrite.h"
}
#endif

/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

String InstanceEncodeDecodeClass("Instance");
String SetOfInstancesEncodeDecodeClass("SetOfInstances");
static int WriteDataInfo(ReactionSystemBase *sys);
static int SummaryOfDataInfo(ReactionSystemBase *sys);
static int PrintDataInfo(ReactionSystemBase *sys);
static int LatexDataInfo(ReactionSystemBase *sys);
/*S BaseDataInstance
 */ 
/*F BaseDataInstance()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataInstance::BaseDataInstance()
{
  Identification = INSTANCE_INSTANCE_ID;
  NameTag = INSTANCE_INSTANCE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  String title(" ----------------------- Set of Attributes  ----------------------- \n");
  setTitle(title);
} 
/*F BaseDataInstance(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataInstance::BaseDataInstance(const BaseDataInstance& data)
  : BaseDataSetOfObjects(data),
    Description(data.Description)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataInstance
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataInstance::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput objin(in,' ');
  NameTag = objin.ReadNext();
  bool result = Read(in,objc,NameTag);
  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataInstance
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataInstance::Read(istream& in, DataObjectClass* objc, const String& name)
{
  return BaseDataSetOfObjects::Read(in,objc,name);
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataInstance
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataInstance::print(ostream& out) const
{
  out << "========= Instance =========\n";
  out << Description;
  out << "\n";
  
  BaseDataSetOfObjects::print(out);

  return out;
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
bool BaseDataInstance::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  return BaseDataSetOfObjects::WriteAsLine(out,objc);
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
bool BaseDataInstance::WriteAsASCII(ostream& out, DataObjectClass*objc)
{
  DataInstanceClass *instclass = (DataInstanceClass *) objc;
  ObjectNameClassPairs pairs;
  ObjectList<String> names = ListOfObjectNames();
  ObjectList<String>::iterator name;
  BaseDataObject  *obj;
  DataObjectClass *objclass;
  for(name=names.begin(); !(name == names.end()); name++)
    {
      obj = GetObject(*name);
      objclass = instclass->PointerToAllowedClasses()->GetObjectClass(obj->GetType());
      pairs.AddObject(obj->NameTag,objclass->NameTag);
    }
  out << "\n%%% ClassNamePairs   --------------------------------\n";
  out << "ClassNamePairs:" << endl;
  pairs.print(cout);
  instclass->ReplaceObjectTypes(pairs);
  out << "\n%%% Instance Objects --------------------------------\n";
  return BaseDataSetOfObjects::WriteAsASCII(out,instclass);
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
bool BaseDataInstance::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  WriteAsLine(out,objc);
  return BaseDataSetOfObjects::WriteAsASCII(out,objc);
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataInstance
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataInstance::Clone()
{
  BaseDataInstance *obj = new BaseDataInstance(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataInstance
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataInstance::CopyClone(Identify * obj)
{
  BaseDataInstance *objfull = (BaseDataInstance *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataInstance
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInstance::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::EncodeThis(buffer);
  result = result && Encode(buffer,Description);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataInstance
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInstance::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::DecodeThis(buffer);
  result = result && Decode(buffer,Description);

  return result;
}
/*F obj = GetAttributeValue(name) . . . . . . . . . . .  get object from name
**
**  DESCRIPTION
**    name: The name of the object to retrieve
**    obj: The retrieved object
**
**  REMARKS
**
*/
BaseDataObject *BaseDataInstance::GetAttributeValue(const String& name)
{
  return GetObject(name);
}
/*F ans = ObjectExists(name)  . . . . . . . . . . . Is the object in the list
**
**  DESCRIPTION
**    name: The object name
**    ans: True if in the list of objects
**
**  REMARKS
**
*/
bool BaseDataInstance::ObjectExists(const String& name)
{
  return IsInList(name);
}
/*F names = ListOfAttributeNames(tlist) . . . . . get names of all attributes
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
ObjectList<String> BaseDataInstance::ListOfAttributeNames(ObjectList<int>& tlist)
{
  return ListOfObjectNames(tlist);
}
 
/*F ans = AddAttribute(obj) . . . . . . . . add attribute to instance
**
**  DESCRIPTION
**    obj: The object to add
**    classes: The set of allowed classes (object must be one of these types)
**
**  REMARKS
**
*/
bool BaseDataInstance::AddAttribute(BaseDataObject *obj)
{
  return AddObject(obj);
}
/*F ans = RemoveAttribute(obj) . . . . . . . . add attribute to instance
**
**  DESCRIPTION
**    obj: The object to add
**    classes: The set of allowed classes (object must be one of these types)
**
**  REMARKS
**
*/
bool BaseDataInstance::RemoveAttribute(String& name)
{
  return RemoveObject(name);
}
/*S DataInstanceClass
 */
/*F DataInstanceClass() . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataInstanceClass::DataInstanceClass()
{
  Identification = INSTANCE_INSTANCE_ID;
  NameTag = INSTANCE_INSTANCE_NAME;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataInstanceClass(data) . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataInstanceClass::DataInstanceClass(const DataInstanceClass& data)
  : DataSetOfObjectsClass(data)
{
} 
 
/*F DataInstanceClass(id,name,descr)  . . . . . . . . . . . . . . constructor
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
DataInstanceClass::DataInstanceClass(const int id, 
                                     const String& name,
                                     const String& descr)
  : DataSetOfObjectsClass(id,name,descr)
{
  SubClass = COREOBJECTS_SET_NAME;
  EncodeDecodeClass = INSTANCE_INSTANCE_NAME;
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
BaseDataObject * DataInstanceClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataInstance();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . DataInstanceClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataInstanceClass*& obj)
{
  obj = new DataInstanceClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . .  BaseDataInstance
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataInstance*& obj)
{
  obj = new BaseDataInstance;
  return obj->DecodeThis(buffer);
}
/*F objc = PointerToAllowedClasses()  . . . .  the allowed set of class types
**
**  DESCRIPTION
**    objc: The pointer to the allowed classes
**  REMARKS
**
*/
DataSetOfObjectsClass*  DataInstanceClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}


/*S BaseDataSetOfInstances
 */ 
/*F BaseDataSetOfInstances()  . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSetOfInstances::BaseDataSetOfInstances()
{
  Identification = INSTANCE_SETOFINSTANCES_ID;
  NameTag = INSTANCE_SETOFINSTANCES_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  String title(" ------------------------- Set of Attributes  ------------------------- \n");
  setTitle(title);
  String ititle(" ------------------------- Set of Instances  ------------------------- \n");
  Instances.setTitle(ititle);
} 
/*F BaseDataSetOfInstances(data)  . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataSetOfInstances::BaseDataSetOfInstances(const BaseDataSetOfInstances& data)
  : BaseDataSetOfObjects(data),
    Description(data.Description),
    Instances(data.Instances)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . .  Read in BaseDataSetOfInstances
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataSetOfInstances::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput objin(in,' ');
  NameTag = objin.ReadNext();
  
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . .  Read in BaseDataSetOfInstances
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataSetOfInstances::Read(istream& in, DataObjectClass* objc, const String& name)
{
  DataSetOfInstancesClass *nobjc = (DataSetOfInstancesClass *) objc;
  bool result = true;
  Description.ReadFullLine(in);
  if(objc->getDebugLevel() > 0)
    {
      cout << "The Set description: ";
      cout << Description;
      cout << "\n+++++++++++++++++++Read In Set Attributes++++++++++++++++++++\n";
    }
  StreamObjectInput str(in,' ');

  String spec = str.ReadNext();
  if(!(spec == "Attributes:"))
    {
      cout << "Expected 'Attributes:' got ";
      cout << spec;
      result = false;
    }
  if(result)
    {
      result = BaseDataSetOfObjects::Read(in,objc,name);
      if(objc->getDebugLevel() > 0)
        cout << "Read In Instances Attributes\n";

      spec = str.ReadNext();
      while(spec == "Instance:" && result)
        {
          BaseDataInstance *instance;
          String id = str.ReadNext();
          String name = str.ReadNext();
          if(Instances.IsInList(name))
            {
              instance = (BaseDataInstance *) Instances.GetObject(name);
              if(objc->getDebugLevel() > 0)
                cout << "New Values for " << name << endl;
              String descr;
              descr.ReadFullLine(in);
              result = instance->Read(in,nobjc->PointerToInstanceClass(),instance->NameTag);
            }
          else
            {
              instance = new BaseDataInstance;
              if(objc->getDebugLevel() > 0)
                cout << "New Instance: " << name << endl;
              instance->Identification = id.ToInteger();
              instance->NameTag = name;   
              instance->Description.ReadFullLine(in);
              result = instance->Read(in,nobjc->PointerToInstanceClass(),instance->NameTag);
              Instances.AddObject(instance);
              delete instance;
            }
          spec = str.ReadNext();
        }
      if(!(spec == "END"))
        {
          cout << "Expected 'Instance:' or END and got ";
          cout << spec;
          result = false;
        }
    }
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . .  BaseDataSetOfInstances
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataSetOfInstances::print(ostream& out) const
{
  out << "\n-------------------------------------------------------------------\n";
  out << "\n---------------------- Set Of Instances --------------------------\n";
  out << "\n-------------------------------------------------------------------\n";
  out << Description;
  out << "\n";
  out << "\n------------------- The Set Attributes ----------------------------\n";
  
  BaseDataSetOfObjects::print(out);
  out << "\n------------------- The set of Instances --------------------------\n";
  
  Instances.print(out);
  out << "\n-------------------------------------------------------------------\n";
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . .  BaseDataSetOfInstances
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataSetOfInstances::Clone()
{
  BaseDataSetOfInstances *obj = new BaseDataSetOfInstances(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . .  BaseDataSetOfInstances
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataSetOfInstances::CopyClone(Identify * obj)
{
  BaseDataSetOfInstances *objfull = (BaseDataSetOfInstances *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . .  BaseDataSetOfInstances
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSetOfInstances::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::EncodeThis(buffer);
  result = result && Encode(buffer,Description);
  result = result && Instances.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . .  BaseDataSetOfInstances
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSetOfInstances::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::DecodeThis(buffer);
  if(!result)
    cout << "\nUnsuccessful Decode of Set of Instances Attributes\n";
  result = result && Decode(buffer,Description);
  if(!result)
    cout << "\nUnsuccessful Decode of Description (or last Attribute)\n";
  result = result && Instances.DecodeThis(buffer);
  if(!result)
    cout << "\nUnsuccessful Decode of Set of Instances \n";

  return result;
}
/*F ans = AddInstance(instance) . . . . . . . . . . . . . add instance to set
**
**  DESCRIPTION
**    instance:  Instance to be added
**    ans: true if added
**
**    Instances of the same name are not added (returning false)
**
**  REMARKS
**
*/
bool BaseDataSetOfInstances::AddInstance(BaseDataInstance& object)
{
  return Instances.AddObject(&object);
}
/*F ans = RemoveInstance(name) . . . . . . . . . . . . . removes instance from set
**
**  DESCRIPTION
**    name:  Name of Instance to be removed
**    ans: true if removed
**
**
**  REMARKS
**
*/
bool BaseDataSetOfInstances::RemoveInstance(String& name)
{
  return Instances.RemoveObject(name);
}
/*F names = ListOfInstanceNames() . . . . . . . .  get names of all instances
**
**  DESCRIPTION
**    names: The list of instance names
**
**  REMARKS
**
*/
ObjectList<String> BaseDataSetOfInstances::ListOfInstanceNames()
{
  ObjectList<int> tlist;
  return Instances.ListOfObjectNames(tlist);
}
/*F ans = InstanceInSet(name) . . . . . . . . . . . . . .  is instance there?
**
**  DESCRIPTION
**    name: The name of the instance
**    ans: True if in list
**
**  REMARKS
**
*/
bool BaseDataSetOfInstances::InstanceInSet(const String& name)
{
  return Instances.IsInList(name);
}
/*F obj = GetInstance(name) . . . . . . . . . . . . .  get instance from name
**
**  DESCRIPTION
**    name: The name of the instance
**    obj: The instance
**
**  REMARKS
**
*/
BaseDataInstance *BaseDataSetOfInstances::GetInstance(const String& name)
{
  return (BaseDataInstance *) Instances.GetObject(name);
}
/*F attrs = ListOfInstanceAttributeNames(instances,tlist,commontoall) attribute names of all instances
**
**  DESCRIPTION
**    instances: A list of instance names
**    tlist: A list of attribute types (if empty, then all types)
**    attrs: The list of attribute names
**
**  REMARKS
**
*/
ObjectList<String>& BaseDataSetOfInstances::ListOfInstanceAttributeNames(ObjectList<String>& instances,
                                                                         ObjectList<String>& tlist,
                                                                         DataSetOfInstancesClass& setclasses,
                                                                         bool commontoall)
{
  ObjectList<String> *names;
  BaseDataInstance *instance;
  
  ObjectList<int> classnums = setclasses.TranslateInstanceAttributeClassNames(tlist);
  ObjectList<String>::iterator iterstart = instances.begin();
  ObjectList<String>::iterator iter;
  if(instances.size() > 0)
    {
      instance = GetInstance(*iterstart);
      names = new ObjectList<String>(instance->ListOfAttributeNames(classnums));
      iterstart++;
      names->ChangeTitle("List Of Instance Attribute Names\n");
      names->ChangeDelimitor(" ");
      if(instances.size() > 1)
        {
          for(iter=iterstart;
              !(iter == instances.end());
              iter++)
            {
              instance = GetInstance(*iter);
              ObjectList<String> instnames = instance->ListOfAttributeNames(classnums);
              if(commontoall)
                names->Intersected(instnames);
              else
                names->AddOnlyUniqueObjects(instnames);
            }
        }
    }
  else
    names = new ObjectList<String>;

  return *names;
}
/*F PrintMissingAttributeNames(instances,tlist,commontoall) print missing for each instance
**
**  DESCRIPTION
**    instances: A list of instance names
**    tlist: A list of attribute types (if empty, then all types)
**    attrs: The list of attribute names
**
**  REMARKS
**
*/
void BaseDataSetOfInstances::PrintMissingAttributeNames(ObjectList<String>& instances,
                                                        ObjectList<String>& tlist,
                                                        DataSetOfInstancesClass& setclasses,
                                                        ObjectList<String>& fullset)
{
  BaseDataInstance *instance;
  
  ObjectList<int> classnums = setclasses.TranslateInstanceAttributeClassNames(tlist);
  ObjectList<String>::iterator iterstart = instances.begin();
  ObjectList<String>::iterator iter;
  if(instances.size() > 0)
    {
      instance = GetInstance(*iterstart);
      
      iterstart++;
      if(instances.size() > 1)
        {
          for(iter=iterstart;
              !(iter == instances.end());
              iter++)
            {
              instance = GetInstance(*iter);
              ObjectList<String> instnames = instance->ListOfAttributeNames(classnums);
              
              ObjectList<String> names(fullset);
              names.Remove(instnames);
              if(names.size() > 0)
                {
                  cerr << "Instance: '" << instance->NameTag << "' Missing: " << names.size() << " Attributes" << endl;
		  names.print(cerr);
		  cerr << endl;
		  cerr << "From full of instance names:" << endl;
		  instnames.print(cerr);
		  cerr << endl;
		  cerr << "Class Selection"<< endl;
		  classnums.print(cout);
		  cerr << endl;
		  cerr << "Full set of names" << endl;
		  fullset.print(cerr);
		  cerr << endl;
                }
              
            }
        }
    }
}
/*F names = ListOfSetAttributeNames(tlist)  . . . . . . .  list of attributes
**
**  DESCRIPTION
**    tlist: List of attribute types to pick out
**    names: The list of attribute names
**
**  REMARKS
**
*/
ObjectList<String> BaseDataSetOfInstances::ListOfSetAttributeNames(ObjectList<int>& tlist)
{
  return ListOfObjectNames(tlist);
}
/*S DataSetOfInstancesClass
 */
/*F DataSetOfInstancesClass() . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataSetOfInstancesClass::DataSetOfInstancesClass()
{
  Identification = INSTANCE_SETOFINSTANCES_ID;
  NameTag = INSTANCE_SETOFINSTANCES_NAME;
  SubClass = COREOBJECTS_SET_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataSetOfInstancesClass(data) . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataSetOfInstancesClass::DataSetOfInstancesClass(const DataSetOfInstancesClass& data)
  : DataSetOfObjectsClass(data),
    AllowedInstanceClasses(data.AllowedInstanceClasses)
{
} 
 
/*F DataSetOfInstancesClass(id,name,descr)  . . . . . . . . . . . constructor
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
DataSetOfInstancesClass::DataSetOfInstancesClass(const int id, 
                                                 const String& name,
                                                 const String& descr)
  : DataSetOfObjectsClass(id,name,descr)
{
  SubClass = COREOBJECTS_SET_NAME;
  EncodeDecodeClass = INSTANCE_SETOFINSTANCES_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . DataSetOfInstancesClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataSetOfInstancesClass::print(ostream& out) const
{
  DataSetOfObjectsClass::print(out);
  //AllowedInstanceClasses.print(out);
  
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . DataSetOfInstancesClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataSetOfInstancesClass, there is no further information.
**
**  REMARKS
**
*/
bool DataSetOfInstancesClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  if(set.getDebugLevel() > 0)
    cout << "Read In Set Attribute Classes\n";
  bool result = DataSetOfObjectsClass::Read(in,set);
  PointerToAllowedClasses()->MergeSetOfObjectClasses(*this);
  
  if(set.getDebugLevel() > 0)
    cout << "Read In Instance Attribute Classes\n";
  result = result && AllowedInstanceClasses.Read(in,set);
  //PointerToAllowedClasses()->MergeSetOfObjectClasses(AllowedInstanceClasses);
  if(set.getDebugLevel() > 0)
    cout << "Done: Read In Classes\n";
  
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . DataSetOfInstancesClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataSetOfInstancesClass::CopyClone(Identify *  objc)
{
  DataSetOfInstancesClass* objcfull = (DataSetOfInstancesClass*) objc;
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . DataSetOfInstancesClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataSetOfInstancesClass::Clone()
{
  DataSetOfInstancesClass* id = new DataSetOfInstancesClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . DataSetOfInstancesClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSetOfInstancesClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::EncodeThis(buffer);
  result = result && AllowedInstanceClasses.EncodeThis(buffer);
  
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . DataSetOfInstancesClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSetOfInstancesClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::DecodeThis(buffer);
  result = result && AllowedInstanceClasses.DecodeThis(buffer);
  
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
BaseDataObject * DataSetOfInstancesClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataSetOfInstances();
}
 
/*F objc = PointerToAllowedClasses()  . . . .  the allowed set of class types
**
**  DESCRIPTION
**    objc: The pointer to the allowed classes
**  REMARKS
**
*/
DataSetOfObjectsClass*  DataSetOfInstancesClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}

/*F tlist = TranslateInstanceAttributeClassNames(names) . . . . . . Class IDs
**
**  DESCRIPTION
**    names: The list of class names
**    tlist: The class IDs
**
**    This translates the list of class names from the set of instances to
**    their corresponding class IDs.
**
**  REMARKS
**
*/
ObjectList<int>& DataSetOfInstancesClass::TranslateInstanceAttributeClassNames(const ObjectList<String>& names)
{
  return PointerToAllowedClasses()->TranslateClassNames(names);
}
/*F tlist = TranslateInstanceAttributeClassNames(names) . . . . . . Class IDs
**
**  DESCRIPTION
**    names: The list of class names
**    tlist: The class IDs
**
**    This translates the list of class names from the set attributes to
**    their corresponding class IDs.
**
**  REMARKS
**
*/
ObjectList<int>& DataSetOfInstancesClass::TranslateSetAttributeClassNames(const ObjectList<String>& names)
{
  return TranslateClassNames(names);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . DataSetOfInstancesClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataSetOfInstancesClass*& obj)
{
  obj = new DataSetOfInstancesClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . .  BaseDataSetOfInstances
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataSetOfInstances*& obj)
{
  obj = new BaseDataSetOfInstances;
  return obj->DecodeThis(buffer);
}
 
/*F pntr = PointerToInstanceClass() . . . . . . . . classes for each instance
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataInstanceClass *DataSetOfInstancesClass::PointerToInstanceClass()
{
  return &AllowedInstanceClasses;
}

 
/*S BaseDataInstanceDoubleMatrix
 */ 
/*F BaseDataInstanceDoubleMatrix()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataInstanceDoubleMatrix::BaseDataInstanceDoubleMatrix()
{
  Identification = INSTANCE_MATRIX_ID;
  NameTag = INSTANCE_MATRIX_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataInstanceDoubleMatrix(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataInstanceDoubleMatrix::BaseDataInstanceDoubleMatrix(const BaseDataInstanceDoubleMatrix& data)
  : BaseDataDoubleMatrix(data),
    Parameters(data.Parameters),
    Instances(data.Instances)
{
  /*
  Identification = INSTANCE_MATRIX_ID;
  NameTag = INSTANCE_MATRIX_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  */
}
 
/*F BaseDataInstanceDoubleMatrix(mat,instances,parameters)  . . . constructor
**
**  DESCRIPTION
**    mat: The matrix
**    instances: The names of the instances
**    parameters: The names of the parameters
**
**  REMARKS
**
*/
BaseDataInstanceDoubleMatrix::BaseDataInstanceDoubleMatrix(const MatrixNumeric& mat,
                                                           const BaseDataKeySet& instances,
                                                           const BaseDataKeySet& parameters)
  : BaseDataDoubleMatrix(mat),
    Parameters(parameters),
    Instances(instances)
{
  Identification = INSTANCE_MATRIX_ID;
  NameTag = INSTANCE_MATRIX_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
}
/*F BaseDataInstanceDoubleMatrix(mat,instances,parameters)  . . . constructor
**
**  DESCRIPTION
**    mat: The matrix
**    instances: The names of the instances
**    parameters: The names of the parameters
**
**  REMARKS
**
*/
BaseDataInstanceDoubleMatrix::BaseDataInstanceDoubleMatrix(const MatrixNumeric& mat,
                                                           const BaseDataKeyWords& instances,
                                                           const BaseDataKeyWords& parameters)
  : BaseDataDoubleMatrix(mat),
    Parameters(parameters),
    Instances(instances)
{
  Identification = INSTANCE_MATRIX_ID;
  NameTag = INSTANCE_MATRIX_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataInstanceDoubleMatrix
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataInstanceDoubleMatrix::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  
  
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataInstanceDoubleMatrix
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataInstanceDoubleMatrix::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataDoubleMatrix::Read(in,objc,name);
  result = result && Instances.Read(in,objc,name);
  result = result && Parameters.Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataInstanceDoubleMatrix
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataInstanceDoubleMatrix::print(ostream& out) const
{
  BaseDataDoubleMatrix::print(out);
  Instances.print(out);
  Parameters.print(out);
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataInstanceDoubleMatrix
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataInstanceDoubleMatrix::Clone()
{
  BaseDataInstanceDoubleMatrix *obj = new BaseDataInstanceDoubleMatrix(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataInstanceDoubleMatrix
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataInstanceDoubleMatrix::CopyClone(Identify * obj)
{
  BaseDataInstanceDoubleMatrix *objfull = (BaseDataInstanceDoubleMatrix *) obj;
  BaseDataDoubleMatrix::CopyClone(objfull);
  Parameters.CopyClone(&(objfull->Parameters));
  Instances.CopyClone(&(objfull->Instances));
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataInstanceDoubleMatrix
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInstanceDoubleMatrix::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataDoubleMatrix::EncodeThis(buffer);
  result = result && Parameters.EncodeThis(buffer);
  result = result && Instances.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataInstanceDoubleMatrix
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInstanceDoubleMatrix::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataDoubleMatrix::DecodeThis(buffer);
  result = result && Parameters.DecodeThis(buffer); 
  result = result && Instances.DecodeThis(buffer);
  return result;
}
/*F names = getInstanceNames()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataKeySet& BaseDataInstanceDoubleMatrix::getInstanceNames()
{
  return Instances;
}
/*F names = getInstanceNames()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataKeySet& BaseDataInstanceDoubleMatrix::getParameterNames()
{
  return Parameters;
}
 
/*F colnum = CorrespondingColumn(colname) . . .  BaseDataInstanceDoubleMatrix
**
**  DESCRIPTION
**    colname: The name of the matrix column
**    colnum: The corresponding column number
**
**  REMARKS
**
*/
unsigned int BaseDataInstanceDoubleMatrix::CorrespondingColumn(String& colname)
{
  ObjectList<String> params = Parameters.GetKeyWords();
  ObjectList<String>::iterator name = params.begin();
  unsigned int colnum = 0;
  while(!(*name == colname) && name != params.end())
    {
      name++;
      colnum++;
    }
  if(name == params.end()) {
    cerr << "Parameter: " << colname << " not found in Matrix" << endl;
    colnum = TOO_BIG_ROW_NUMBER;
  }

  return colnum;
}
/*F column = getColumn(colname) . . .  BaseDataInstanceDoubleMatrix
**
**  DESCRIPTION
**    colname: The name of the matrix column
**    column: The corresponding column
**
**  REMARKS
**
*/
BaseDataInstanceDoubleVector *BaseDataInstanceDoubleMatrix::getColumn(String& colname) 
{
  BaseDataInstanceDoubleVector *instvec = NULL;
  unsigned int colnum = CorrespondingColumn(colname);
  if(colnum != TOO_BIG_ROW_NUMBER) {
    VectorNumeric vec = CurrentMatrix().getMatrixColumn(colnum);
    instvec = new BaseDataInstanceDoubleVector(vec,getInstanceNames());
    instvec->NameTag = colname;
  }
  return instvec;
}
/*F colnum = CorrespondingColumn(colname) . . .  BaseDataInstanceDoubleMatrix
**
**  DESCRIPTION
**    colname: The name of the matrix column
**    colnum: The corresponding column number
**
**  REMARKS
**
*/
unsigned int BaseDataInstanceDoubleMatrix::CorrespondingRow(String& rowname)
{
  ObjectList<String> insts = Instances.GetKeyWords();
  ObjectList<String>::iterator name = insts.begin();
  unsigned int rownum = 0;
  while(!(*name == rowname) && name != insts.end())
    {
      name++;
      rownum++;
    }
  if(name == insts.end()) {
    cerr << "Parameter: " << rowname << " not found in Matrix" << endl;
    rownum = TOO_BIG_ROW_NUMBER;
  }
  return rownum;
}
/*F column = getColumn(colname) . . .  BaseDataInstanceDoubleMatrix
**
**  DESCRIPTION
**    colname: The name of the matrix column
**    column: The corresponding column
**
**  REMARKS
**
*/
BaseDataInstanceDoubleVector *BaseDataInstanceDoubleMatrix::getRow(String& rowname) 
{
  BaseDataInstanceDoubleVector *instvec = NULL;
  unsigned int rownum = CorrespondingRow(rowname);
  if(rownum != TOO_BIG_ROW_NUMBER) {
    VectorNumeric vec = CurrentMatrix().getMatrixRow(rownum);
    instvec = new BaseDataInstanceDoubleVector(vec,getParameterNames());
    instvec->NameTag = rowname;
  }
  return instvec;
}
/*F mat = formReducedMatrix(parameters) . . . .  BaseDataInstanceDoubleMatrix
**
**  DESCRIPTION
**    parameters: The set of parameters to use for new matrix
**    mat: The new matrix
**
**  REMARKS
**
*/
MatrixNumeric *BaseDataInstanceDoubleMatrix::formReducedMatrix(BaseDataKeyWords *parameters)
{
  unsigned int intsize = Instances.SizeOf();

  MatrixNumeric *mat = new MatrixNumeric(intsize,parameters->SizeOf());
  unsigned int pcount = 0;
  BaseDataKeyWords *params = (BaseDataKeyWords *) parameters->Clone();
  while(params->SizeOf() >0)
    {
      String name = params->NextKey();
      cout << "Parameter: " << name << endl;
      unsigned int p = CorrespondingColumn(name);
      if(p < Parameters.SizeOf())
	{
	  for(unsigned int i=0;i<intsize;i++)
	    {
	      (*mat)[i][pcount] = (CurrentMatrix())[i][p];
	    }
	}
      else
	{
	  cerr << "Parameter '" << name << "' not found in matrix" << endl;
	}
      pcount++;
    }
  return mat;
}
/*F mat = formReducedMatrix(parameters) . . . .  BaseDataInstanceDoubleMatrix
**
**  DESCRIPTION
**    parameters: The set of parameters to use for new matrix
**    mat: The new matrix
**
**  REMARKS
**
*/
BaseDataInstanceDoubleMatrix *BaseDataInstanceDoubleMatrix::isolateColumnsByParameterName(BaseDataKeyWords *parameters)
{
  unsigned int intsize = Instances.SizeOf();

  MatrixNumeric *mat = new MatrixNumeric(intsize,parameters->SizeOf());
  unsigned int pcount = 0;
  BaseDataKeyWords *params = (BaseDataKeyWords *) parameters->Clone();
  while(params->SizeOf() >0)
    {
      String name = params->NextKey();
      cout << "Parameter: " << name << endl;
      unsigned int p = CorrespondingColumn(name);
      if(p < Parameters.SizeOf())
	{
	  for(unsigned int i=0;i<intsize;i++)
	    {
	      (*mat)[i][pcount] = (CurrentMatrix())[i][p];
	    }
	}
      else
	{
	  cerr << "Parameter '" << name << "' not found in matrix" << endl;
	}
      pcount++;
    }
  BaseDataKeySet set(*parameters);
  BaseDataInstanceDoubleMatrix *instmat = new BaseDataInstanceDoubleMatrix(*mat,Instances,set);
  instmat->NameTag = NameTag;
  delete mat;
  return instmat;
}
/*F mat = isolateRowsByName(parameters) . . . .  BaseDataInstanceDoubleMatrix
**
**  DESCRIPTION
**    rownames: The set of row names to use for new matrix
**    mat: The new matrix
**
**  REMARKS
**
*/
BaseDataInstanceDoubleMatrix *BaseDataInstanceDoubleMatrix::isolateRowsByInstanceName(BaseDataKeyWords *rownames)
{
  unsigned int intsize = Parameters.SizeOf();

  MatrixNumeric *mat = new MatrixNumeric(rownames->SizeOf(),intsize);
  unsigned int pcount = 0;
  BaseDataKeyWords *names = (BaseDataKeyWords *) rownames->Clone();
  while(names->SizeOf() >0)
    {
      String name = names->NextKey();
      unsigned int p = CorrespondingRow(name);
      if(p < Instances.SizeOf())
	{
	  for(unsigned int i=0;i<intsize;i++)
	    {
	      (*mat)[pcount][i] = (CurrentMatrix())[p][i];
	    }
	}
      else
	{
	  cerr << "Row Name '" << name << "' not found in matrix" << endl;
	}
      pcount++;
    }
  BaseDataKeySet set(*rownames);
  BaseDataInstanceDoubleMatrix *instmat = new BaseDataInstanceDoubleMatrix(*mat,set,Parameters);
  instmat->NameTag = NameTag;
  delete mat;
  return instmat;
}

/*S DataInstanceDoubleMatrixClass
 */
/*F DataInstanceDoubleMatrixClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataInstanceDoubleMatrixClass::DataInstanceDoubleMatrixClass()
{
  NameTag = INSTANCE_MATRIX_NAME;
  Identification = INSTANCE_MATRIX_ID;
  SubClass = DATAOBJ_MATRIX_NAME;
  EncodeDecodeClass = INSTANCE_MATRIX_NAME;
} 
/*F DataInstanceDoubleMatrixClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataInstanceDoubleMatrixClass::DataInstanceDoubleMatrixClass(const DataInstanceDoubleMatrixClass& data)
  : DataDoubleMatrixClass(data)
{
} 
 
/*F DataInstanceDoubleMatrixClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataInstanceDoubleMatrixClass::DataInstanceDoubleMatrixClass(const int id, 
                                                             const String& name,
                                                             const String& descr)
  : DataDoubleMatrixClass(id,name,descr)
{
  SubClass = DATAOBJ_MATRIX_NAME;
  EncodeDecodeClass = INSTANCE_MATRIX_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataInstanceDoubleMatrixClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataInstanceDoubleMatrixClass::print(ostream& out) const
{
  DataDoubleMatrixClass::print(out);
  out << NameTag << "  ";
  // the rest
           
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . . . . . DataInstanceDoubleMatrixClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataInstanceDoubleMatrixClass, there is no further information.
**
**  REMARKS
**
*/
bool DataInstanceDoubleMatrixClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataDoubleMatrixClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataInstanceDoubleMatrixClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataInstanceDoubleMatrixClass::CopyClone(Identify *  objc)
{
  DataInstanceDoubleMatrixClass* objcfull = (DataInstanceDoubleMatrixClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataInstanceDoubleMatrixClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataInstanceDoubleMatrixClass::Clone()
{
  DataInstanceDoubleMatrixClass* id = new DataInstanceDoubleMatrixClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataInstanceDoubleMatrixClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataInstanceDoubleMatrixClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataDoubleMatrixClass::EncodeThis(buffer);
  // The rest: result = result && Encode(buffer,-------);
  // result = result && EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataInstanceDoubleMatrixClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataInstanceDoubleMatrixClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataDoubleMatrixClass::DecodeThis(buffer);
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
BaseDataObject * DataInstanceDoubleMatrixClass::BaseDataObjectExample()
{ 
  //cout << "Make InstanceDoubleMatrix Example\n";
  return (BaseDataObject *) new BaseDataInstanceDoubleMatrix();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataInstanceDoubleMatrixClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataInstanceDoubleMatrixClass*& obj)
{
  obj = new DataInstanceDoubleMatrixClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataInstanceDoubleMatrix
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataInstanceDoubleMatrix*& obj)
{
  cout << "InstanceDoubleMatrix\n";
  obj = new BaseDataInstanceDoubleMatrix;
  return obj->DecodeThis(buffer);
}

/*S BaseDataInstanceDoubleVector
 */ 
/*F BaseDataInstanceDoubleVector()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataInstanceDoubleVector::BaseDataInstanceDoubleVector()
{
  Identification = INSTANCE_VECTOR_ID;
  NameTag = INSTANCE_VECTOR_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataInstanceDoubleVector(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataInstanceDoubleVector::BaseDataInstanceDoubleVector(const BaseDataInstanceDoubleVector& data)
  : BaseDataDoubleVector(data),
    Parameters(data.Parameters)
{
}
/*F BaseDataInstanceDoubleVector(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    vec: The vector
**    keys: The parameter names
**
**  REMARKS
**
*/
BaseDataInstanceDoubleVector::BaseDataInstanceDoubleVector(VectorNumeric& vec, BaseDataKeySet& keys)
  : BaseDataDoubleVector(vec),
    Parameters(keys)
{
  Identification = INSTANCE_VECTOR_ID;
  NameTag = INSTANCE_VECTOR_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
}
/*F BaseDataInstanceDoubleVector(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    vec: The vector
**    keys: The parameter names
**
**  REMARKS
**
*/
BaseDataInstanceDoubleVector::BaseDataInstanceDoubleVector(VectorNumeric& vec, BaseDataKeyWords& keys)
  : BaseDataDoubleVector(vec),
    Parameters(keys)
{
  Identification = INSTANCE_VECTOR_ID;
  NameTag = INSTANCE_VECTOR_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
}

/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataInstanceDoubleVector
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataInstanceDoubleVector::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataInstanceDoubleVector
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataInstanceDoubleVector::Read(istream& in, DataObjectClass* objc, const String& name)
{
  BaseDataDoubleVector::Read(in,objc,name);
  
  return Parameters.Read(in,objc,name);
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataInstanceDoubleVector
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataInstanceDoubleVector::print(ostream& out) const
{
  BaseDataDoubleVector::print(out);
  Parameters.print(out);

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataInstanceDoubleVector
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataInstanceDoubleVector::Clone()
{
  BaseDataInstanceDoubleVector *obj = new BaseDataInstanceDoubleVector(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataInstanceDoubleVector
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataInstanceDoubleVector::CopyClone(Identify * obj)
{
  BaseDataInstanceDoubleVector *objfull = (BaseDataInstanceDoubleVector *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataInstanceDoubleVector
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInstanceDoubleVector::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataDoubleVector::EncodeThis(buffer);
  result = result && Parameters.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataInstanceDoubleVector
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInstanceDoubleVector::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataDoubleVector::DecodeThis(buffer);
  result = result && Parameters.DecodeThis(buffer);

  return result;
}
/*F ans = AddElement(name,value)  . . .. . . . . . . . . . . .  BaseDataInstanceDoubleVector
**
**  DESCRIPTION
**    name: The name of the element
**    value: The double value of the element
**
**  REMARKS
**
*/
void BaseDataInstanceDoubleVector::AddElement(String& name, double value)
{
  Parameters.AddKeyWord(name);
  CurrentVector().push_back(value);
}
/*S DataInstanceDoubleVectorClass
 */
/*F DataInstanceDoubleVectorClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataInstanceDoubleVectorClass::DataInstanceDoubleVectorClass()
{
  NameTag = INSTANCE_VECTOR_NAME;
  Identification = INSTANCE_VECTOR_ID;
  SubClass = DATAOBJ_VECTOR_NAME;
  EncodeDecodeClass = INSTANCE_VECTOR_NAME;
} 
/*F DataInstanceDoubleVectorClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataInstanceDoubleVectorClass::DataInstanceDoubleVectorClass(const DataInstanceDoubleVectorClass& data)
  : DataDoubleVectorClass(data)
{
} 
 
/*F DataInstanceDoubleVectorClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataInstanceDoubleVectorClass::DataInstanceDoubleVectorClass(const int id, 
                                                             const String& name,
                                                             const String& descr)
  : DataDoubleVectorClass(id,name,descr)
{
  SubClass = DATAOBJ_VECTOR_NAME;
  EncodeDecodeClass = INSTANCE_VECTOR_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataInstanceDoubleVectorClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataInstanceDoubleVectorClass::print(ostream& out) const
{
  DataDoubleVectorClass::print(out);
  out << NameTag << "  ";
  // the rest
           
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . . . . . DataInstanceDoubleVectorClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataInstanceDoubleVectorClass, there is no further information.
**
**  REMARKS
**
*/
bool DataInstanceDoubleVectorClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataDoubleVectorClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataInstanceDoubleVectorClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataInstanceDoubleVectorClass::CopyClone(Identify *  objc)
{
  DataInstanceDoubleVectorClass* objcfull = (DataInstanceDoubleVectorClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataInstanceDoubleVectorClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataInstanceDoubleVectorClass::Clone()
{
  DataInstanceDoubleVectorClass* id = new DataInstanceDoubleVectorClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataInstanceDoubleVectorClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataInstanceDoubleVectorClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataDoubleVectorClass::EncodeThis(buffer);
  // The rest: result = result && Encode(buffer,-------);
  // result = result && EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataInstanceDoubleVectorClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataInstanceDoubleVectorClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataDoubleVectorClass::DecodeThis(buffer);
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
BaseDataObject * DataInstanceDoubleVectorClass::BaseDataObjectExample()
{ 
  //cout << "Make InstanceDoubleVector Example\n";
  return (BaseDataObject *) new BaseDataInstanceDoubleVector();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataInstanceDoubleVectorClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataInstanceDoubleVectorClass*& obj)
{
  obj = new DataInstanceDoubleVectorClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataInstanceDoubleVector
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataInstanceDoubleVector*& obj)
{
  obj = new BaseDataInstanceDoubleVector;
  return obj->DecodeThis(buffer);
}
/*S BaseDataProgressVariableMatrix
 */ 
/*F BaseDataProgressVariableMatrix()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataProgressVariableMatrix::BaseDataProgressVariableMatrix()
{
  Identification = INSTANCE_PROGRESSMATRIX_ID;
  NameTag = INSTANCE_PROGRESSMATRIX_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataProgressVariableMatrix(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataProgressVariableMatrix::BaseDataProgressVariableMatrix(const BaseDataProgressVariableMatrix& data)
  : BaseDataInstanceDoubleMatrix(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataProgressVariableMatrix
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataProgressVariableMatrix::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataProgressVariableMatrix
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataProgressVariableMatrix::Read(istream& in, DataObjectClass* objc, const String& name)
{
  //  bool result = BaseDataInstanceDoubleMatrix::Read(in,objc,name);
  bool result = true;
  DataProgressVariableMatrixClass *flameclass = (DataProgressVariableMatrixClass *) objc;
  String nameline;
  nameline.ReadFullLine(in);
  cout << nameline << endl;
  String baseName(name);
  String paren("]");
  String beginParen("[");
  char delimitor = '\t';

  unsigned int nameindex = 0;
  unsigned int count = 0;
  BaseDataKeySet &parameters = getParameterNames();
  while(!nameline.IsEmpty())
    {
      String param;
      nameline.IsolateNextWord(param,delimitor);
      param.EliminateBlanks();
      cout << "Read:  '" << param << "' (" << param.size() << ") - (" << nameline.size() << ")" << endl;
      if(param == flameclass->ProgressVariable) {
	nameindex = count;
	cout << "Progress Variable: " << nameindex;
      }
      parameters.AddKeyWord(param);
      nameline.EliminateLeadingBlanks();
      count++;
    }
  unsigned int dim2 = parameters.GetKeyWords().size();
  cout << "Read in Data for " << dim2 << " variables" << endl;

  StreamObjectInput file(in, delimitor);
  String oneset;
  oneset.ReadFullLine(in);
  oneset.EliminateLeadingBlanks();
  double currentVal;
  MatrixNumeric &mat = CurrentMatrix();
  count = 0;
  BaseDataKeyWords &instances = getInstanceNames();
  String word;
  //*** stringstream change    int siz = 100;
  //*** stringstream change    char* ch = new char[siz];

  while(!oneset.IsEmpty())
    {
      VectorNumeric line;
      //line.AddObject(timeval);

      oneset.EliminateLeadingBlanks();
      for (unsigned int j=0; j<dim2; j++)
	{
	  oneset.IsolateNextWord(word,delimitor);
	  oneset.EliminateLeadingBlanks();
	  currentVal = word.ToFloat();
	  line.AddObject(currentVal);
	}

      String name(baseName);
      String cntS = Int2String(count);
      name.AppendToEnd(cntS);
      name.AppendToEnd(beginParen);
      oneset.IsolateNextWord(word,delimitor);
      word.EliminateBlanks();
      double timeval = line[nameindex];
      stringstream ostrstr;
      //ostrstr.setf(ios::fixed,ios::floatfield);
      ostrstr.setf(ios::fixed);
      
      ostrstr << setprecision(6) << timeval << '\0';
      name.AppendToEnd(ostrstr.str().c_str());
      name.AppendToEnd(paren);

      instances.AddKeyWord(name);

      mat.AddObject(line);
      oneset.ReadFullLine(in);
      oneset.EliminateLeadingBlanks();
      count++;
    }

  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataProgressVariableMatrix
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataProgressVariableMatrix::print(ostream& out) const
{
  BaseDataInstanceDoubleMatrix::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataProgressVariableMatrix
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataProgressVariableMatrix::Clone()
{
  BaseDataProgressVariableMatrix *obj = new BaseDataProgressVariableMatrix(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataProgressVariableMatrix
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataProgressVariableMatrix::CopyClone(Identify * obj)
{
  BaseDataProgressVariableMatrix *objfull = (BaseDataProgressVariableMatrix *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataProgressVariableMatrix
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataProgressVariableMatrix::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataInstanceDoubleMatrix::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataProgressVariableMatrix
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataProgressVariableMatrix::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataInstanceDoubleMatrix::DecodeThis(buffer);
  // The rest

  return result;
}
 
/*S DataProgressVariableMatrixClass
 */
/*F DataProgressVariableMatrixClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataProgressVariableMatrixClass::DataProgressVariableMatrixClass()
{
  Identification = INSTANCE_PROGRESSMATRIX_ID;
  NameTag = INSTANCE_PROGRESSMATRIX_NAME;
  SubClass = "InstanceDoubleMatrix";
  EncodeDecodeClass = NameTag;
  Initialize();
} 
/*F DataProgressVariableMatrixClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataProgressVariableMatrixClass::DataProgressVariableMatrixClass(const DataProgressVariableMatrixClass& data)
  : DataInstanceDoubleMatrixClass(data),
    InstanceBaseName(data.InstanceBaseName),
    ProgressVariable(data.ProgressVariable)
{
} 
 
/*F DataProgressVariableMatrixClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataProgressVariableMatrixClass::DataProgressVariableMatrixClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataInstanceDoubleMatrixClass(id,name,descr)
{
  SubClass = "InstanceDoubleMatrix";
  EncodeDecodeClass = "ProgressVariableMatrix";
  Initialize();
}
 
/*F Initialize()  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
void DataProgressVariableMatrixClass::Initialize() {
  InstanceBaseName = "Index";
  ProgressVariable = "Index";
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataProgressVariableMatrixClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataProgressVariableMatrixClass::print(ostream& out) const
{
  DataInstanceDoubleMatrixClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataProgressVariableMatrixClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataProgressVariableMatrixClass, there is no further information.
**
**  REMARKS
**
*/
bool DataProgressVariableMatrixClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataInstanceDoubleMatrixClass::Read(in,set);

  StreamObjectInput str(in,' ');
  InstanceBaseName = str.ReadNext();
  ProgressVariable = str.ReadNext();
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataProgressVariableMatrixClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataProgressVariableMatrixClass::CopyClone(Identify *  objc)
{
  DataProgressVariableMatrixClass *objcfull = (DataProgressVariableMatrixClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataProgressVariableMatrixClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataProgressVariableMatrixClass::Clone()
    {
      DataProgressVariableMatrixClass* id = new DataProgressVariableMatrixClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataProgressVariableMatrixClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataProgressVariableMatrixClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataInstanceDoubleMatrixClass::EncodeThis(buffer);
  result = result && Encode(buffer,InstanceBaseName);
  result = result && Encode(buffer,ProgressVariable);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataProgressVariableMatrixClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataProgressVariableMatrixClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataInstanceDoubleMatrixClass::DecodeThis(buffer);
  result = result && Decode(buffer,InstanceBaseName);
  result = result && Decode(buffer,ProgressVariable);
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
BaseDataObject * DataProgressVariableMatrixClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataProgressVariableMatrix();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataProgressVariableMatrixClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataProgressVariableMatrixClass*& obj)
     {
     obj = new DataProgressVariableMatrixClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataProgressVariableMatrix
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataProgressVariableMatrix*& obj)
     {
     obj = new BaseDataProgressVariableMatrix;
     return obj->DecodeThis(buffer);
     }
//EncodeDecodeRegisterClass(DataProgressVariableMatrixClass,BaseDataProgressVariableMatrix,_NAME);
//String descr("The Class");
//DataProgressVariableMatrixClass class(_ID,_NAME,descr);
//set.AddObjectClass(class);






/*S SystemInstance
 */
 
/*F Run() . . . . . . . . . . . . . . . . . . . . . . . . . .  InstanceSystem
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int InstanceSystem::Run()
{
  return Commands.ExecuteCommand(0,0,this);
}
/*F Exit()  . . . . . . . . . . . . . . . . . . . . . . . . .  InstanceSystem
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int InstanceSystem::Exit()
{
  return 0;
}

/*F EncodeDecodeObjectsSetUp()  . . . . . . . . . . . . . . .  InstanceSystem
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void InstanceSystem::EncodeDecodeObjectsSetUp()
{
  InitialSetOfNumericEncodeDecodeRoutines();
  InitialCoreDataObjectEncodeDecodeRoutines();
  InitialSetOfLogicalEncodeDecodeRoutines();
  InitialSetOfOperationEncodeDecodeRoutines();
  InitialSetOfODRealEncodeDecodeRoutines();
  InitialSetOfDataObjectsEncodeDecodeRoutines();
  InitialSetOfInstanceEncodeDecodeRoutines();
  InitialSetOfLogicalOperationEncodeDecodeRoutines();
  InitialSetOfNumericOperationEncodeDecodeRoutines();
}
/*F StandardObjectsSetUp()  . . . . . . . . . . . . . . . . .  InstanceSystem
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void InstanceSystem::StandardObjectsSetUp()
{
  AddFunctionClasses(Standard);
  AddCoreDataObjectClasses(Standard);
  AddNumericClasses(Standard);
  AddLogicalClasses(Standard);
  AddOperationClasses(Standard);
  AddDataObjectClasses(Standard);
  AddInstanceClasses(Standard);
  AddLogicalOperationClasses(Standard);
  AddNumericOperationClasses(Standard);
}
/*F CommandSetUp()  . . . . . . . . . . . . . . . . . . . . .  InstanceSystem
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void InstanceSystem::CommandSetUp()
{
  SingleSystemCommand clonetest("CloneDelete",
                                "Repetitive Clone-Delete Test",
                                &InstanceCloneDeleteTest);
  Commands.AddObject(clonetest.getName(),clonetest);
  SingleSystemCommand readtest("Read",
                               "Instance Read in Test",
                               &InstanceReadTest);
  Commands.AddObject(readtest.getName(),readtest);
  SingleSystemCommand encodedecode("EncodeDecode",
                                   "Instance Read/Encode/Decode Test",
                                   &InstanceEncodeDecodeTest);
  Commands.AddObject(encodedecode.getName(),encodedecode);
}
/*F Initialization()  . . . . . . . . . . . . . . . . . . . . .  InstanceSystem
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void InstanceSystem::Initialization()
{
  EncodeDecodeObjectsSetUp();
  StandardObjectsSetUp();
  StandardAllowedClasses = &InstanceClasses;
  InstanceClasses.MergeSetOfObjectClasses(getStandard());
  CommandSetUp();
}
/*F FileReadIn()  . . . . . . . . . . . . . . . . . . . . . read in file test
**
**  DESCRIPTION
**    The input 
**    - class filename
**    - filename
**    - maindebug
**
**  REMARKS
**
*/
int InstanceSystem::FileReadIn()
{
  if(Inputs.size() < 3)
    {
      cerr << "Class Filename\n";
      cerr << "Filename\n";
      cerr << "Debug Level:\n";

      return 1;
    }
  String classfilename = GetNextInput();
  String filename = GetNextInput();
  String debuglevelS = GetNextInput();
  int maindebug = debuglevelS.ToInteger();
  InstanceClasses.SetDebugLevel(maindebug);
  
  bool result = ReadInInstancesAndClass(classfilename,filename,
                                        Instances,InstanceClasses,
                                        *StandardAllowedClasses,maindebug);
  int final = 0;
  
  if(!result)
    final = 1;
  
  
  return final;
}
/*F EncodeTest()  . . . . . . . . . . . . . . . . . . . . . read in file test
**
**  DESCRIPTION
**    The input 
**    - class filename
**    - filename
**    - maindebug
**
**  REMARKS
**
*/
int InstanceSystem::EncodeTest()
{
  if(Inputs.size() < 3)
    {
      cerr << "Class Filename\n";
      cerr << "Filename\n";
      cerr << "Debug Level:\n";

      return 1;
    }
  String classfilename = GetNextInput();
  String filename = GetNextInput();
  String debuglevelS = GetNextInput();
  int maindebug = debuglevelS.ToInteger();
  
  bool result = ReadInInstancesAndClass(classfilename,filename,
                                        Instances,InstanceClasses,
                                        *StandardAllowedClasses,maindebug);
  if(result)
    {
      cout << "=================================================\n";
      cout << "           Encode Instances\n";
      cout << "=================================================\n";
      CommBuffer buffer(COMM_BUFF_ENCODE,200000,2000);
      result = result && Instances.EncodeThis(buffer);
      if(result)
        {
          BaseDataSetOfInstances instances;
          
          cout << "=================================================\n";
          cout << "           Decode Instances\n";
          cout << "=================================================\n";
          result = result && instances.DecodeThis(buffer);
          cout << "-------------------------------------------------\n";
          instances.print(cout);
        }
    }
  
  int final = 0;
  
  if(!result)
    final = 1;
  
  
  return final;
}
/*F CloneDeleteTest() . . . . . . . . . . . . . . . . . . . read in file test
**
**  DESCRIPTION
**    The input 
**    - class filename
**    - filename
**    - maindebug
**
**  REMARKS
**
*/
int InstanceSystem::CloneDeleteTest()
{
  if(Inputs.size() < 3)
    {
      cerr << "Class Filename\n";
      cerr << "Filename\n";
      cerr << "Number of Repeats\n";
      cerr << "Debug Level:\n";

      return 1;
    }
  String classfilename = GetNextInput();
  String filename = GetNextInput();
  String repeatsS = GetNextInput();
  unsigned int repeats = repeatsS.ToInteger();
  String debuglevelS = GetNextInput();
  int maindebug = debuglevelS.ToInteger();
  
  //cout << "=========================================================\n";
  //cout << "            Read In Instances And Class\n";
  //cout << "=========================================================\n";
  
  bool result = ReadInInstancesAndClass(classfilename,filename,
                                        Instances,InstanceClasses,
                                        *StandardAllowedClasses,maindebug);
  //cout << "=========================================================\n";
  //Instances.print(cout);
  //cout << "=========================================================\n";

  BaseDataSetOfInstances *instances;
  
  if(result)
    {
      for(unsigned int i=0;i < repeats; i++)
        {
          instances = new BaseDataSetOfInstances;
          instances->CopyClone(&Instances);
          delete instances;
        }
    }
  int final = 0;  
  if(!result)
    final = 1;

  return final;
}
 
/*F getStandard() . . . . . . . . . . . . . . . . . . . . . .  InstanceSystem
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataSetOfObjectsClass& InstanceSystem::getStandard()
{
  return Standard;
}
/*S InstanceSystemSave
 */
 
/*F Initialization()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void InstanceSystemSave::Initialization()
{
  InstanceSystem::Initialization();
  Successful = RestartObjectInitialization();  
}
/*F Exit()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int InstanceSystemSave::Exit()
{
  bool result = RestartObjectExit();
  
  int ans = 0;
  if(!result)
    ans = 1;
  return ans;
}
 
/*F CommandSetUp()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void InstanceSystemSave::CommandSetUp()
{
  InstanceSystem::CommandSetUp();
  SingleSystemCommand prt("Print",
                          "Print Attributes and Instance Attributes",
                          &PrintDataInfo);
  Commands.AddObject(prt.getName(),prt);
  SingleSystemCommand sum("Summary",
                          "Print Attributes and Instance Attributes",
                          &SummaryOfDataInfo);
  Commands.AddObject(sum.getName(),sum);
  SingleSystemCommand wrt("Write",
                          "Print Attributes and Instance Attributes",
                          &WriteDataInfo);
  Commands.AddObject(wrt.getName(),wrt);
  SingleSystemCommand lat("LaTeX",
                          "Print Attributes and Instance Attributes",
                          &LatexDataInfo);
  Commands.AddObject(lat.getName(),lat);
}
/*F RestartObjectExit()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool InstanceSystemSave::RestartObjectExit()
{
  bool result = true;
  if(SaveIt)
    {
      bool result = true;
      if(IncrementVersion)
        Version++;
      unsigned int  ver = Version;
      String version = Int2String(ver);
      String writename(RootName);
      writename.AppendToEnd(Delimitor);
      writename.AppendToEnd(version);

 
      CommBuffer buffer(COMM_BUFF_ENCODE,200000,2000);
      result = result && EncodeSavedObjects(buffer);
      
#ifdef _unix
  result = result && WriteCPP(writename, &buffer);
#else
  result = result && WriteC(writename, &buffer);
#endif
    }
  return result;
}

 
/*F RestartObjectInitialization()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool InstanceSystemSave::RestartObjectInitialization()
{
  bool result = true;
  if(Inputs.size() >= 3)
    {
      SysCommand = GetNextInput();
      RootName = GetNextInput();
      VersionS = GetNextInput();

      Version = VersionS.ToInteger();
      result = result && SetUpCommand();
      if(result)
        {
          if(ReadIt)
            {
              result = result && ReadInVersion();
            }
        }
    }
  else
    {
      cerr << "System Information Needed:\n";
      cerr << "   Run Command:\n";
      cerr << "      Experiment: Read a restart file\n";
      cerr << "         Initial: Write a restart file\n";
      cerr << "         Operate: Read restart and write next\n";
      cerr << "   Run Root Name\n";
      cerr << "   Version: The version number of run";
      cerr << "            The next versionn is written out\n";
      cerr << endl;
      
      result = false;
    }
  return result;
}
/*F SetUpCommand()
**
**  DESCRIPTION
**    Set up the command flags
**
**    The commands are:
**        Experiment: Just read the information
**        Operate:    Read and write a new version
**        Initial:    Initialize a version
**        Change:     Read in version and write to same file
**
**  REMARKS
**
*/
bool InstanceSystemSave::SetUpCommand()
{
  bool result = true;

  if(SysCommand == "Experiment")
    ReadIt = true;
  else if(SysCommand == "Operate")
    {
      ReadIt = true;
      SaveIt = true;
    }
  else if(SysCommand == "Initial")
    {
      ReadIt = false;
      SaveIt = true;
    }
  else if(SysCommand == "Change")
    {
      ReadIt = true;
      SaveIt = true;
      IncrementVersion = false;
    }
  else
    {
      cerr << "Command not found: ";
      cerr << SysCommand << endl;
      result = false;
    }
  if(result)
    {
      /*
      if(ReadIt)
        cout << "Will Read Restart File\n";
      else
        cout << "No Restart File Read\n";
      
      if(SaveIt)
        cout << "Write New Restart File (after run)\n";
      else
        cout << "No Output Restart File will be written\n";
      */
    }

  return result;
}
/*F ReadInVersion()
**
**  DESCRIPTION
**    Read in the current version information
**
**  REMARKS
**
*/
bool InstanceSystemSave::ReadInVersion()
{
  String readname("saves/");
  readname.AppendToEnd(RootName);
  readname.AppendToEnd(Delimitor);
  readname.AppendToEnd(VersionS);
  
  CommBuffer *buffer;
#ifdef _unix
  bool success = ReadCPP(readname, buffer);
#else
  bool success = ReadC(readname, buffer);
#endif

  DecodeSavedObjects(*buffer);
  getStandard().setIDCount(InstanceClasses.getIDCount());
  getStandard().MergeSetOfObjectClasses(InstanceClasses);

  return success;
}
/*F ans = ReadCPP() 
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool InstanceSystemSave::ReadCPP(String &readname,
                                 CommBuffer *&buffer) 
{
    RestartFile = new OpenInputDataFile(getDataRootDirectory(),
					readname,
					"save");
    bool success = true;                                 
    if(RestartFile->IfOpen())
	{
	    unsigned int bufsize;
	    
	    RestartFile->Stream >> bufsize;
	    char *buf = new char[bufsize];
	    RestartFile->Stream.read(buf,bufsize);
	    buffer = new CommBuffer(buf,bufsize);
	    return true;
	}
    else
	{
	    cerr << "Restart file not found: '" << readname;
	    cerr << "' in directory '" << getDataRootDirectory() << "'" << endl;
	    success = false;
	}
    return success;
}
/*F ReadC()  . . . . . . . . . . . 
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool InstanceSystemSave::ReadC(String &readname, 
                               CommBuffer *&buffer)
{
#ifndef _unix
  FileName saveName(getDataRootDirectory(), readname, "save");
cout << "FileName " << saveName.FullName << endl;
  int iii=0;

  char * buf = readFromFile(saveName.FullName.chars(), 
                            &iii);
cout << saveName.FullName << "   " << iii << endl;
  buffer = new CommBuffer(buf, iii);
#endif
  return true;
}
/*F ans = EncodeSavedObjects(buffer) 
**
**  DESCRIPTION
**    buffer: Buffer inn which to encode the objects
**    ans: true if successful
**
**    This is the routine to save the essential information
**    associated with a run.  The encoded buffer will
**    be written to a file by another routine.  The
**    complimentary routine is DecodeSavedObjects.
**
**  REMARKS
**
*/
bool InstanceSystemSave::EncodeSavedObjects(CommBuffer& buffer)
{
  bool result = Instances.EncodeThis(buffer);
  result = result && InstanceClasses.EncodeThis(buffer);
  if(!result)
    cerr << "Error in Reading Instances and Instance Classes\n";
  return result;
}
/*F ans = DecodeSavedObjects(buffer) 
**
**  DESCRIPTION
**    buffer: Buffer inn which to decode the objects
**    ans: true if successful
**
**    This is the routine to extract the essential information
**    associated with a run.  The decoded buffer has
**    been read from a file by another routine.  The
**    complimentary routine is EncodeSavedObjects.
**
**  REMARKS
**
*/
bool InstanceSystemSave::DecodeSavedObjects(CommBuffer& buffer)
{
  bool result = Instances.DecodeThis(buffer);
  if(!result)
    cerr << "Error in Decoding Instances\n";
  else
    {
      result = result && InstanceClasses.DecodeThis(buffer);
      if(!result)
        cerr << "Error in Decoding Instance Classes\n";
    }
  
  return result;
}
/*F BaseDataObjectOut(ptype,obj,out,system)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void InstanceSystemSave::BaseDataObjectOut(String& ptype, 
					   BaseDataObject *obj, 
					   ostream& out)
{
  int itype = obj->GetType();
  DataObjectClass *objc = InstanceClasses.PointerToAllowedClasses()->GetObjectClass(itype);
    
  if(ptype == "Print")
    {
      obj->print(out);
    }
  else if(ptype == "Write")
    {
      obj->WriteAsASCII(out,objc);
    }
  else if(ptype == "Line")
    {
      obj->WriteAsLine(out,objc);
    }
  else if(ptype == "LaTeX")
    {
      obj->WriteAsLatex(out,objc);
    }
  out << " ";
}
/*F PrintListOfNames(ptype,obj,out,system)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void InstanceSystemSave::PrintListOfNames(String& ptype, 
					  String& prefix,
					  ostream& out,
					  ObjectList<String>& names)
{
  names.ChangeDelimitor("\n");
  names.ChangeTitle("");
  out << "---------------- List of ";
  out << prefix;
  out << "----------------" << endl;
  names.print(out);
  out << "---------------- List of ";
  out << prefix;
  out << "----------------" << endl;
}

/*S Utilities
 */
 
/*F ReadInInstancesAndClass(icfilename,ifilename,instances,instancesclass,standard,mainbug)
**
**  DESCRIPTION
**    icfilename: The instance class information filename
**    ifilename: The instance objects filename
**    instances: The instances
**    instanceclass: The instance class names
**    standard: The original class information
**    mainbug: The debug level
**
**  REMARKS
**
*/
bool ReadInInstancesAndClass(String& icfilename,
                             String& ifilename,
                             BaseDataSetOfInstances& instances,
                             DataSetOfInstancesClass& instancesclass,
                             DataSetOfObjectsClass& Standard,
                             unsigned int maindebug)
{
  bool result = true;
  
  OpenInputFile icfile(icfilename);
  OpenInputFile ifile(ifilename);
  if(icfile.IfOpen())
    {
      if(!(ifile.IfOpen()))
        {
          cerr << "Instance file not found: " << ifilename << endl;
          result = false;
        }
    }
  else
    {
      cerr << "InstanceClass file not found: " << icfilename << endl;
      result = false;
    }
  
          
  if(result && maindebug > 0)
    cout << "============ Read in Instance Classes (debug level > 0) ================\n";
  Standard.SetDebugLevel(maindebug);
  
  result = result && instancesclass.Read(icfile.Stream,Standard);
  
  if(result)
    {
      if(maindebug > 2)
        {
          cout << "Begin=====  Print Out Current Set of Instance Classes (debug level > 2) ==================Begin\n";
          instancesclass.print(cout);
          cout << "End=======  Print Out Current Set of Instance Classes (debug level > 2) ====================End\n";
          cout << endl;
        }
      if(maindebug > 0)
        cout << "============== Read in Instances (debug level > 0) ==================\n";
      instancesclass.SetDebugLevel(maindebug);
      instancesclass.PointerToAllowedClasses()->SetDebugLevel(maindebug);
      result = result && instances.Read(ifile.Stream,&instancesclass,Standard.NameTag);
      if(result)
        {
          if(maindebug > 1)
            {
              cout << "Begin=====  Print Out Current Set of Instances (debug level 1) ==================Begin\n";
              instances.print(cout);
              cout << "End=======  Print Out Current Set of Instances (debug level 1) ====================End\n";
              cout << endl;
            }
        }
      else
        {
          cerr << "Error in reading instances\n";
        }
    }
  else 
    {
      cerr << "Error in reading instance classes\n";
    }
  return result;
}
/*F InstanceEncodeTest(classfilename,filename,standard,buf)
**
**  DESCRIPTION
**    classfilename: The class structure filename
**    filename: The instance filename
**    standard: The standard class objects
**    buf: The buffer
**
**  REMARKS
**
*/
bool InstanceEncodeTest(String& classfilename, String& filename, 
                        DataSetOfObjectsClass& standard,
                        CommBuffer& buf)
{
  BaseDataSetOfInstances instances;
  DataSetOfInstancesClass instsclass;
  
  bool result = ReadInInstancesAndClass(classfilename,filename,
                                        instances,instsclass,
                                        standard,0);
  result = result && instances.EncodeThis(buf);
  return result;
}
/*F InstanceDecodeTest(buf)
**
**  DESCRIPTION
**    buf: The buffer
**
**  REMARKS
**
*/
bool InstanceDecodeTest(CommBuffer& buf)
{
  
  CommBuffer inbuffer(buf.GetBuffer(),
                      buf.GetBufferSize());
  BaseDataSetOfInstances instances;
  
  bool result = instances.DecodeThis(inbuffer);
  
  int ans = 0;
  
  if(!result)
    {
      cerr << "Decode Failed\n";
      ans = 1;
    }
  else
    {
      cout << "Begin========================= Decoded Instances ============================Begin\n";
      instances.print(cout);
      cout << "End  ========================= Decoded Instances ============================  End\n";
      cout << "\n";
    }
  return result;
}
/*F ans = InstanceReadTest(system)
**
**  DESCRIPTION
**    system: The system structure
**    ans: Zero if successful
**
**  REMARKS
**
*/
int InstanceReadTest(ReactionSystemBase* sys)
{
  InstanceSystem* system = (InstanceSystem *) sys;

  return system->FileReadIn();
}
/*F ans = InstanceCloneDeleteTest(system)
**
**  DESCRIPTION
**    system: The system structure
**    ans: Zero if successful
**
**  REMARKS
**
*/
int InstanceCloneDeleteTest(ReactionSystemBase* sys)
{
  InstanceSystem* system = (InstanceSystem *) sys;
  
  return system->CloneDeleteTest();
}
/*F ans = InstanceEncodeDecodeTest(system)  . . . . . . .  encode/decode test
**
**  DESCRIPTION
**    system: The system command structure
**    ans: zero if successful
**
**  REMARKS
**
*/
int InstanceEncodeDecodeTest(ReactionSystemBase* sys)
{
  InstanceSystem* system = (InstanceSystem *) sys;

  if(system->Inputs.size() < 2)
    {
      cerr << "Class Filename\n";
      cerr << "Filename\n";
      return 1;
    }
  String classfilename = system->GetNextInput();
  String filename = system->GetNextInput();
  
  cout << "\n==========================================================\n";
  cout << "Encode\n";  
  CommBuffer buf(COMM_BUFF_ENCODE,200000,2000);
  bool result = InstanceEncodeTest(classfilename,filename,
                                   system->getStandard(),buf);
  cout << "\n==========================================================\n";
  cout << "Decode\n";
  result = result && InstanceDecodeTest(buf);

  int ans = 0;
  if(!result)
    ans = 1;
  
  return ans;
}
 
/*F AddInstanceClasses(set)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AddInstanceClasses(DataSetOfObjectsClass& set)
{
  String instdescr("The Instance Class");
  String setinstdescr("Set Of Instances Class");
  String matrixdescr("Matrix Instance Class");
  String vectordescr("Vector Instance Class");
  String pairdescr("Pair of Strings");

  DataInstanceClass instclass(INSTANCE_INSTANCE_ID,INSTANCE_INSTANCE_NAME,instdescr);
  DataSetOfInstancesClass setinstclass(INSTANCE_SETOFINSTANCES_ID,INSTANCE_SETOFINSTANCES_NAME,setinstdescr);
  DataInstanceDoubleMatrixClass matrixclass(INSTANCE_MATRIX_ID,INSTANCE_MATRIX_NAME,matrixdescr);
  DataInstanceDoubleVectorClass vectorclass(INSTANCE_VECTOR_ID,INSTANCE_VECTOR_NAME,vectordescr);
  DataProgressVariableMatrixClass prgmatclass(INSTANCE_PROGRESSMATRIX_ID,INSTANCE_PROGRESSMATRIX_NAME,pairdescr);

  set.AddObjectClass(instclass);
  set.AddObjectClass(setinstclass);
  set.AddObjectClass(matrixclass);
  set.AddObjectClass(vectorclass);
  set.AddObjectClass(prgmatclass);
}
/*F InitialSetOfInstanceEncodeDecodeRoutines() . . . . . . . . . . TopDecode
**
**  DESCRIPTION
**    Initialise 'TopDecode' functions in SetOfEncodeDecodeRoutines
**
**  REMARKS
**
*/
extern void InitialSetOfInstanceEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataInstanceClass,BaseDataInstance,INSTANCE_INSTANCE_NAME);
  EncodeDecodeRegisterClass(DataSetOfInstancesClass,BaseDataSetOfInstances,INSTANCE_SETOFINSTANCES_NAME);
  EncodeDecodeRegisterClass(DataInstanceDoubleMatrixClass,BaseDataInstanceDoubleMatrix,INSTANCE_MATRIX_NAME);
  EncodeDecodeRegisterClass(DataInstanceDoubleVectorClass,BaseDataInstanceDoubleVector,INSTANCE_VECTOR_NAME);
  EncodeDecodeRegisterClass(DataProgressVariableMatrixClass,BaseDataProgressVariableMatrix,INSTANCE_PROGRESSMATRIX_NAME);
}
 
/*F WriteCPP() . . . . . . . . . . . . . . . 
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool InstanceSystemSave::WriteCPP(String& writename,
                                  CommBuffer* buffer) {
    String dir(getDataRootDirectory());
    String sav("/saves");
    dir.AppendToEnd(sav);
  SaveFile = new OpenOutputDataFile(dir,
                                    writename,
                                    "save");
  bool result = true;
  if(SaveFile->Stream == NULL)
    {
      cerr << "Save File could not be opened: '";
      cerr << writename << "' in directory: ";
      cerr << getDataRootDirectory() << endl;
      result = false;
    }

  unsigned int bufsize = buffer->GetBufferSize();
  SaveFile->Stream << bufsize;
  char *buf = buffer->GetBuffer();
  SaveFile->Stream.write(buf,bufsize);
  SaveFile->Stream.flush();
  
  return result;
}
/*F WriteC() . . . . . . . . . . . . . . . 
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool InstanceSystemSave::WriteC(String& writename,
                                CommBuffer* buffer) {
#ifndef _unix
    String fl("saves/");
    String sav(writename);
    fl.AppendToEnd(sav);
  FileName saveNextName(getDataRootDirectory(),
                        fl,
                        "save");

  cout << "Exit: '" << saveNextName.FullName << "' written\n";
  writeToFile(saveNextName.FullName.chars(), 
              buffer->GetBuffer(), 
              buffer->GetBufferSize());
#endif
  return true;
}
/*F ans = PrintSetOfInstancesAttribute(out,name,instances,instclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int PrintSetOfInstancesAttribute(ostream& out,
                                 String& ptype,
                                 String& name,
                                 BaseDataSetOfInstances& instances,
                                 DataSetOfInstancesClass& instsclass,
                                 InstanceSystemSave *system)
{
  BaseDataObject *obj = instances.GetObject(name);
  if(ptype == "Print")
    {
      String prefix("Data Set Attribute: '");
      prefix.AppendToEnd(name);
      String s1("'\n");
      prefix.AppendToEnd(s1);
      out << prefix;
    }
  system->BaseDataObjectOut(ptype,obj,out);
  if(ptype == "Print")
    {
      String suffix("\n");
      out << suffix;
    }
  return SYSTEM_NORMAL_RETURN;
}
 
/*F ans = PrintEntireInstance(out,name,instances,class)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int PrintEntireInstance(ostream& out,
                        String& ptype,
                        String& name,
                        BaseDataSetOfInstances& instances,
                        DataSetOfInstancesClass&,
                        InstanceSystemSave *system)
{
  String border("\n==============================================================\n");

  int ans = SYSTEM_NORMAL_RETURN;
  if(instances.InstanceInSet(name))
    {
      BaseDataInstance *inst = instances.GetInstance(name);
      if(ptype == "Print")
        {
          out << border;
          out << "Data Set Instance: '" << name << "'" << endl;
        }
      system->BaseDataObjectOut(ptype,inst,out);
      if(ptype == "Print")
        {
          out << border;
        }
    }
  else
    {
      out << border;
      out << "Instance not found: '" << name << "'" << endl;
      ans = SYSTEM_ERROR_RETURN;
    }
  return ans;
}
 
/*F ans = PrintInstanceAttribute(out,instance,attribute,instances,instsclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int PrintInstanceAttribute(ostream& out,
                           String& ptype,
                           String& instance,
                           String& attribute,
                           BaseDataSetOfInstances& instances,
                           DataSetOfInstancesClass& instsclass,
                           InstanceSystemSave *system)
{
  String border("\n==============================================================\n");
  String prefix(border);  
  String p1("Instance: '");
  String p2("' attribute: '");
  String p3("\n");

  prefix.AppendToEnd(p1);
  prefix.AppendToEnd(instance);
  prefix.AppendToEnd(p2);
  prefix.AppendToEnd(attribute);
  prefix.AppendToEnd(p3);
  
  String suffix("\n");
  
  int ans = SYSTEM_NORMAL_RETURN;
  if(instances.InstanceInSet(instance))
    {
      BaseDataInstance *inst = instances.GetInstance(instance);
      BaseDataObject *obj = inst->GetObject(attribute);
      if(ptype == "Print")
        out << prefix;
      system->BaseDataObjectOut(ptype,obj,out);
      if(ptype == "Print")
        out << suffix;
    }
  else
    {
      out << border;
      out << "Instance not found: '" << attribute << "'" << endl;
      ans = SYSTEM_ERROR_RETURN;
    }
  return ans;
}
/*F PrintSingleInstanceInformation(ptype,instance,out,system)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static void PrintSingleInstanceInformation(String& ptype, String& instance, 
					   ostream& out, InstanceSystemSave *system)
{
  if(system->Inputs.size() > 0)
    {
      String attribute = system->GetNextInput();
      if(attribute == "All")
	{
	  PrintEntireInstance(out,ptype,instance,
				    system->Instances,
				    system->InstanceClasses,
				    system);
	}
      else
	{
	  PrintInstanceAttribute(out,
				       ptype,
				       instance,attribute,
				       system->Instances,
				       system->InstanceClasses,
				       system);
	}
    }
  else
    {
      if(system->Instances.InstanceInSet(instance))
	{
	  BaseDataInstance *inst = system->Instances.GetInstance(instance);
	  ObjectList<String> names = inst->ListOfObjectNames();
	  String prefix("Instance ");
	  prefix.AppendToEnd(instance);
	  system->PrintListOfNames(ptype,prefix,out,names);
	}
      else
	{
	  out << "Instance not found: '" << instance << "'" << endl;
	}
    }
}
/*F PrintInstanceInformation(ptype,out,system)
**
**  DESCRIPTION
**    ptype: The type of printing
**    out: The output stream
**    system: The system information
**
**  REMARKS
**
*/
static void PrintInstanceInformation(String& ptype,ostream& out, InstanceSystemSave *system)
{
  if(system->Inputs.size() > 0)
    {
      String instance = system->GetNextInput();
      if(instance == "All")
	{
	  out << "All Instances  =================== All =====================" << endl;
	  out << "Attributes:" << endl;
	  BaseDataKeyWords attributes;
	  while(system->Inputs.size() > 0)
	    {
	      String aname = system->GetNextInput();
	      attributes.AddKeyWord(aname);
	    }
	  ObjectList<String> anames = attributes.GetKeyWords();
	  ObjectList<String>::iterator attr;

	  ObjectList<String> names = system->Instances.ListOfInstanceNames();
	  ObjectList<String>::iterator name;
	  for(name = names.begin(); !(name == names.end());name++)
	    {
	      BaseDataInstance *inst = system->Instances.GetInstance(*name);
	      out << "Instance: " << inst->Identification << " " << inst->NameTag << " ";
	      out << inst->Description << endl;
	      for(attr = anames.begin(); attr != anames.end();attr++)
		{
		  BaseDataObject *obj = inst->GetObject(*attr);
		  system->BaseDataObjectOut(ptype,obj,out);
		}
	      out << endl;
	    }
	  out << "END" << endl;
	}
      else
	{
	  PrintSingleInstanceInformation(ptype,instance,out,system);
	}
    }
  else
    {
      ObjectList<String> names = system->Instances.ListOfInstanceNames();
      String prefix("Instance");
      system->PrintListOfNames(ptype,prefix,out,names);
    }
}
/*F PrintAttributeInformation(ptype,out,system)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void PrintAttributeInformation(String ptype, ostream& out, InstanceSystemSave *system)
{
  if(system->Inputs.size() > 0)
    {
      String attribute = system->GetNextInput();
      if(attribute == "All")
	{
	  ObjectList<int> empty;
	  ObjectList<String> names = system->Instances.ListOfSetAttributeNames(empty);
	  ObjectList<String>::iterator name;
	  out << "\n------------------------ List of Attributes ------------------------\n";
	  system->Instances.BaseDataSetOfObjects::print(cout);
	  for(name = names.begin();!(name == names.end());name++)
	    {
	      cout << "Object: '" << *name << "' size=" << (*name).size() << endl;
	      BaseDataObject *inst = system->Instances.GetObject(*name);
	      system->BaseDataObjectOut(ptype,inst,out);
	    }
	  out << "\n------------------------ List of Attributes ------------------------\n";
	}
      else
	{
	  while(!(attribute == "END"))
	    {
	      if(system->Instances.IsInList(attribute))
		{
		  BaseDataObject *attr = system->Instances.GetObject(attribute);
		  system->BaseDataObjectOut(ptype,attr,out);
		}
	      else
		{
		  cerr << "Attribute: '" << attribute << "' not found" << endl;
		}
	      if(system->Inputs.size() > 0)
		attribute = system->GetNextInput();
	      else
		attribute = "END";
	    }
	}
    }
  else
    {
      ObjectList<int> empty;
      ObjectList<String> names = system->Instances.ListOfSetAttributeNames(empty);
      String prefix("Attribute");
      system->PrintListOfNames(ptype,prefix,out,names);
    }
}
/*F PrintClassInformation(ptype,out,system)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static void PrintClassInformation(String& ptype, ostream& out, InstanceSystemSave *system)
{
  if(system->Inputs.size() > 0)
    {
      String name = system->GetNextInput();
      if(name == "All")
	{
	  ObjectList<String> names = system->InstanceClasses.ListOfClassNames();
	  ObjectList<String>::iterator name;
	  out << "\n------------------------ List of Classes ------------------------\n";
	  for(name = names.begin();!(name == names.end());name++)
	    {
	      BaseDataObject *inst = system->InstanceClasses.PointerToAllowedClasses()->GetObjectClass(*name);
	      system->BaseDataObjectOut(ptype,inst,out);
	    }
	  out << "\n------------------------ List of Classes ------------------------\n";
	}
      else
	{
	  while(!(name == "END"))
	    {
	      if(system->InstanceClasses.IsInList(name))
		{
		  BaseDataObject *attr = system->InstanceClasses.PointerToAllowedClasses()->GetObjectClass(name);
		  system->BaseDataObjectOut(ptype,attr,out);
		}
	      else
		{
		  cerr << "Class: '" << name << "' not found" << endl;
		}
	      if(system->Inputs.size() > 0)
		name = system->GetNextInput();
	      else
		name = "END";
	    }
        }
    }
  else
    {
      ObjectList<String> names = system->InstanceClasses.ListOfClassNames();
      String prefix("Class");
      system->PrintListOfNames(ptype,prefix,out,names);
    }
}
 
/*F DataInformationOut(ptype,out,sys)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int DataInformationOut(String ptype, ostream& out, ReactionSystemBase *sys)
{
  InstanceSystemSave *system = (InstanceSystemSave *) sys;
  int ans = SYSTEM_NORMAL_RETURN;
  
  if(sys->Inputs.size() < 1)
    {
      cerr << "Print Instance Info:\n";
      cerr << " Input:\n";
      cerr << "     Print: What is to be printed (Attribute, Instance, Class)\n";
      cerr << "     [Name1,Name2]:\n";
      cerr << "          If no name, then all is printed\n";
      cerr << "          The names tell which attribute and instance is to be printed\n";
      cerr << "   otherwise:\n";
      cerr << "     Names [type]\n";
      cerr << "          type is Class, Instance or Attribute\n";
      exit(1);
    }

  String prt = system->GetNextInput();
  if(prt == "Instance")
    {
      PrintInstanceInformation(ptype,out,system);
    }
  else if(prt == "Attribute")
    {
      PrintAttributeInformation(ptype,out,system);
    }
  else if(prt == "Class")
    {
      PrintClassInformation(ptype,out,system);
    }
  else 
    {
      cerr << "Expected 'Instance' 'Attribute' or 'Class'\n";
      ans = SYSTEM_ERROR_RETURN;
    }
  return ans;  
}
/*F ans = PrintDataInfo(sys)
**
**  DESCRIPTION
**    sys: System information
**  REMARKS
**
*/
static int PrintDataInfo(ReactionSystemBase *sys)
{
  return DataInformationOut("Print",cout,sys);
}
/*F ans = SummaryOfDataInfo(sys)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int SummaryOfDataInfo(ReactionSystemBase *sys)
{
  return DataInformationOut("Line",cout,sys);
}
/*F ans = WriteDataInfo(sys)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int WriteDataInfo(ReactionSystemBase *sys)
{
  return DataInformationOut("Write",cout,sys);
}
/*F ans = LatexDataInfo(sys)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int LatexDataInfo(ReactionSystemBase *sys)
{
  return DataInformationOut("LaTeX",cout,sys);
}
