/*  FILE     PopulationBasedOptimization.cc
**  PACKAGE  PopulationBasedOptimization
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "PopulationBasedOptimization" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
//#define random() rand()
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#define TEMPLATE_INSTANTIATION
#include "CoreDataObjects.hh"
#include "Vector.hh"
#include "PrimitiveStats.hh"
#include "MatrixNumeric.hh"
#include "BasicLaTeXTable.hh"
#include "MatrixOut.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "MenuObjects.hh"
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "ExpressionTree.hh"
#include "DistributionAlgorithm.hh"
#include "Optimize.hh"
#include "PopulationBasedOptimization.hh"
#include "ParameterizedFunction.hh"

/*S BaseDataGeneticObject
 */ 
/*F BaseDataGeneticObject()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGeneticObject::BaseDataGeneticObject()
{
  Identification = GENETIC_OBJECT_ID;
  NameTag = GENETIC_OBJECT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataGeneticObject(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGeneticObject::BaseDataGeneticObject(const BaseDataGeneticObject& data)
  : BaseDataOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataGeneticObject
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataGeneticObject::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataGeneticObject
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataGeneticObject::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataGeneticObject
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGeneticObject::print(ostream& out) const
{
  BaseDataOperation::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataGeneticObject
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGeneticObject::Clone()
{
  BaseDataGeneticObject *obj = new BaseDataGeneticObject;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataGeneticObject
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGeneticObject::CopyClone(Identify * obj)
{
  BaseDataGeneticObject *objfull = (BaseDataGeneticObject *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGeneticObject
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticObject::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGeneticObject
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticObject::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  // The rest

  return result;
}
 
/*F ans = Mutate(cls,obj,objcls,set,setclass) . . . . . . . . . mutate object
**
**  DESCRIPTION
**    cls: The genetic object class
**    obj: The object to mutate
**    objcls: The object class
**    set: The set of objects
**    setclass: The set of objects class
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticObject::Mutate(BaseDataObject *obj,
				   DataGeneticObjectClass *cls)
{
  bool result = true;
  return result;
}
/*F ans = CrossOver(cls,obj,objcls,set,setclass)  .  cross over within object
**
**  DESCRIPTION
**    cls: The genetic object class
**    obj: The object to cross over
**    objcls: The object class
**    set: The set of objects
**    setclass: The set of objects class
**    ans: True if successful
**    
**  REMARKS
**
*/
BaseDataSetOfObjects *BaseDataGeneticObject::CrossOver(BaseDataObject *obj1,
						       BaseDataObject *obj2,
						       BaseDataGeneticObject *genetic,
						       DataGeneticObjectClass *cls)
{
  return NULL;
}
/*F ans = GeneticInitializeObject(cls,obj,objcls) . . . initialize the object
**
**  DESCRIPTION
**    cls: The genetic object class
**    obj: The object to mutate
**    objcls: The object class
**    ans: True if successful
**    
**  REMARKS
**
*/
BaseDataObject *BaseDataGeneticObject::GeneticInitializeObject(DataGeneticObjectClass *cls)
{
  BaseDataObject *obj = NULL;
  DataObjectClass *objcls = NULL;
  if(cls != NULL)
    {
      objcls = cls->getObjectClass();
      if(objcls != NULL)
	{
	  obj = objcls->BaseDataObjectExample();
	}
      else
	{
	  cerr << "Genetic Object class not defined, returning NULL for object" << endl;
	}
    }
  else
    {
      cerr << "Genetic Class not defined, returning NULL for object" << endl;
    }
  return obj;
}
/*F ans = GeneticInitialize(cls,insts,instcls)  . . . . . . . . .  initialize
**
**  DESCRIPTION
**    cls: The genetic object class
**    insts: The set of instances
**    instclass: The set of instances class
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticObject::GeneticInitialize(DataGeneticObjectClass *cls,
					      BaseDataSetOfInstances *insts,
					      DataSetOfInstancesClass *instcls)
{
  bool result = true;
  return result;
}

/*S DataGeneticObjectClass
 */
/*F DataGeneticObjectClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGeneticObjectClass::DataGeneticObjectClass()
  : ObjectClass(NULL)
{
  Identification = GENETIC_OBJECT_ID;
  NameTag = GENETIC_OBJECT_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataGeneticObjectClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGeneticObjectClass::DataGeneticObjectClass(const DataGeneticObjectClass& data)
  : DataOperationClass(data)
{
  ObjectClass = (DataObjectClass *) PointerClone(data.ObjectClass);
} 
 
/*F DataGeneticObjectClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataGeneticObjectClass::DataGeneticObjectClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOperationClass(id,name,descr),
    ObjectClass(NULL)
{
  SubClass = "Operation";
  EncodeDecodeClass = GENETIC_OBJECT_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataGeneticObjectClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGeneticObjectClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  PointerPrint(out,"The Object Class:","No Object defined",ObjectClass);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataGeneticObjectClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGeneticObjectClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGeneticObjectClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);

  StreamObjectInput str(in,' ');
  String baseS = str.ReadNext();
  if(set.PointerToAllowedClasses()->IsInList(baseS))
    {
      ObjectClass = (DataObjectClass *) set.PointerToAllowedClasses()->GetObjectClass(baseS)->Clone();
    }
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataGeneticObjectClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGeneticObjectClass::CopyClone(Identify *  objc)
{
  DataGeneticObjectClass *objcfull = (DataGeneticObjectClass *) objc;
  *this = *objcfull;
  ObjectClass = (DataObjectClass *) PointerClone(objcfull->ObjectClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataGeneticObjectClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGeneticObjectClass::Clone()
{
  DataGeneticObjectClass* id = new DataGeneticObjectClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataGeneticObjectClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGeneticObjectClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,(BaseDataObject *&) ObjectClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataGeneticObjectClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGeneticObjectClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) ObjectClass);
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
BaseDataObject * DataGeneticObjectClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataGeneticObject();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGeneticObjectClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGeneticObjectClass*& obj)
     {
     obj = new DataGeneticObjectClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataGeneticObject
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGeneticObject*& obj)
     {
     obj = new BaseDataGeneticObject;
     return obj->DecodeThis(buffer);
     }
/*F cls = getObjectClass()  . . . . . . . . . . . . . . . . . .  object class
**
**  DESCRIPTION
**    cls: The object class of the genetic object to be manipulated
**
**  REMARKS
**
*/
DataObjectClass *DataGeneticObjectClass::getObjectClass()
{
  return ObjectClass;
}
/*S BaseDataPopulationObject
 */ 
/*F BaseDataPopulationObject()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataPopulationObject::BaseDataPopulationObject()
  : Value(0.0),
    ValueObject(NULL)
{
  Identification = POPULATION_OBJECT_ID;
  NameTag = POPULATION_OBJECT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataPopulationObject(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataPopulationObject::BaseDataPopulationObject(const BaseDataPopulationObject& data)
  : BaseDataObject(data),
    Value(data.Value)
{
  ValueObject = PointerClone(data.ValueObject);
}
/*F ~BaseDataPopulationObject() . . . . . . . . . . . . . . . . .  destructor
**
**  DESCRIPTION
**    The 'Expression' pointer is deleted
**
**  REMARKS
**
*/
BaseDataPopulationObject::~BaseDataPopulationObject()
{
  if(ValueObject != NULL)
    delete ValueObject;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataPopulationObject
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataPopulationObject::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataPopulationObject
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataPopulationObject::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);
  return result;
} 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataPopulationObject
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataPopulationObject::print(ostream& out) const
{
  BaseDataObject::print(out);
  out << "Heuristic Value: " << Value << endl;
  PointerPrint(out,"PopulationObject: ", "Population Object not defined yet",ValueObject);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataPopulationObject
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataPopulationObject::Clone()
{
  BaseDataPopulationObject *obj = new BaseDataPopulationObject(*this);
  return obj;
} 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataPopulationObject
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataPopulationObject::CopyClone(Identify * obj)
{
  BaseDataPopulationObject *objfull = (BaseDataPopulationObject *) obj;
  *this = *objfull;
  BaseDataObject::CopyClone(obj);
  ValueObject = PointerClone(objfull->ValueObject);
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPopulationObject
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPopulationObject::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && Encode(buffer,Value);
  result = result && PointerEncode(buffer,(BaseDataObject *&) ValueObject);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPopulationObject
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPopulationObject::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && Decode(buffer,Value);
  result = result && PointerDecode(buffer,(BaseDataObject *&) ValueObject);

  return result;
}
/*F AddValueObject(obj,objclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataPopulationObject::AddValueObject(BaseDataObject *obj, 
					      DataPopulationObjectClass *objclass)
{
  bool result = true;
  if(ValueObject != NULL)
    delete ValueObject;
  ValueObject = (BaseDataObject *) obj->Clone();
  return result;
} 
/*F obj = getValueObject() 
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataObject *BaseDataPopulationObject::getValueObject()
{
  return ValueObject;
}
/*F AssignValue(value)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataPopulationObject::AssignValue(double value)
{
  Value = value;
}
/*F value = GetValue()  . . . . . . . . . . . . . . . . . get heuristic value
**
**  DESCRIPTION
**    value: The heuristic value of the population object
**
**  REMARKS
**
*/
double BaseDataPopulationObject::GetValue()
{
  return Value;
}
/*F ans = AddInstanceValue(obj,set)
**
**  DESCRIPTION
**    obj: The result of the parameterized operation
**    set: The set of allowed classes
**
**  REMARKS
**
bool BaseDataPopulationObject::AddInstanceValue(BaseDataObject *obj,
						DataSetOfObjectsClass *set)
{
  bool result = true;
  if(set->IsOfClass(*obj,NUMERIC_BASE_NAME))
    {
      BaseDataNumeric *num = (BaseDataNumeric *) obj;
      double value = num->Distance();
      InstanceValue = value;
    }
  else if(set->IsOfClass(*obj,LOGICAL_BASE_NAME))
    {
      BaseDataLogical *num = (BaseDataLogical *) obj;
      double value = num->GetValue();
      InstanceValue = value;
    }
  else
    {
      cerr << "Result of Expression is not a number (value remains unchanged):" << endl;
      obj->print(cerr);
      cerr << endl;
      cerr << "-------- Object Returned as NULL -------------" << endl;
      delete obj;
      obj = NULL;
      result = false;
    }

  return result;
}
*/
bool BaseDataPopulationObject::AddInstanceValue(BaseDataReal *num)
{
  Value += num->GetValue();
  InstanceValue = num->GetValue();
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . .  BaseDataPopulationObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the population object
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool BaseDataPopulationObject::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  //DataPopulationObjectClass *popobjclass = (DataPopulationObjectClass *) objc;
  //DataObjectClass *objcls = popobjclass->getBaseObjectClass();
  out << "%% Population Object" << endl;
  out << Value << "  " << endl;
  //bool result = ValueObject->WriteAsASCII(out,objcls);
  bool result = true;
  ValueObject->print(out);
  out << endl;
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
bool BaseDataPopulationObject::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  DataPopulationObjectClass *objclass = (DataPopulationObjectClass *) objc;
  DataObjectClass *objcls = objclass->getBaseObjectClass();
  out << "Population Object: ";
  out << Value << " \\\\ ";
  bool result = ValueObject->WriteAsASCII(out,objcls);
  return result;
}
/*F ans = WriteAsLine(out,objc)  . . . . . . . . . . .  BaseDataSetOfObjects
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object on a single line
**
**  REMARKS
**
*/
bool BaseDataPopulationObject::WriteAsLine(ostream& out, DataObjectClass* objc)
{
  DataPopulationObjectClass *objclass = (DataPopulationObjectClass *) objc;
  DataObjectClass *objcls = objclass->getBaseObjectClass();
  out << Value << " --> ";
  bool result = ValueObject->WriteAsLine(out,objcls);
  return result;
}
/*S DataPopulationObjectClass
 */
/*F DataPopulationObjectClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataPopulationObjectClass::DataPopulationObjectClass()
  : BaseObjectClass(NULL)
{
  Identification = POPULATION_OBJECT_ID;
  NameTag = POPULATION_OBJECT_NAME;
  SubClass = "SetOfObjects";
  EncodeDecodeClass = NameTag;
  
} 
/*F DataPopulationObjectClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataPopulationObjectClass::DataPopulationObjectClass(const DataPopulationObjectClass& data)
  : DataObjectClass(data)
{
  BaseObjectClass = (DataObjectClass *) PointerClone((DataObjectClass *) data.BaseObjectClass);
} 
/*F DataPopulationObjectClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataPopulationObjectClass::DataPopulationObjectClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataObjectClass(id,name,descr),
    BaseObjectClass(NULL)
{
  SubClass = "SetOfObjects";
  EncodeDecodeClass = POPULATION_OBJECT_NAME;
} 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataPopulationObjectClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataPopulationObjectClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  out << endl;
  PointerPrint(out,"BaseObjectClass:", "No Base Object Class Specified\n",BaseObjectClass);
  out << endl;
  return out;
}
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataPopulationObjectClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataPopulationObjectClass, there is no further information.
**
**  REMARKS
**
*/
bool DataPopulationObjectClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  return DataObjectClass::Read(in,set);
}
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataPopulationObjectClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataPopulationObjectClass::CopyClone(Identify *  objc)
{
  DataPopulationObjectClass *objcfull = (DataPopulationObjectClass *) objc;
  *this = *objcfull;
  BaseDataObject::CopyClone(objc);
  BaseObjectClass = (DataObjectClass *) PointerClone((DataObjectClass *) objcfull->BaseObjectClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataPopulationObjectClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataPopulationObjectClass::Clone()
{
  DataPopulationObjectClass* id = new DataPopulationObjectClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataPopulationObjectClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPopulationObjectClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,BaseObjectClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataPopulationObjectClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPopulationObjectClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) BaseObjectClass);
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
BaseDataObject * DataPopulationObjectClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataPopulationObject();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataPopulationObjectClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataPopulationObjectClass*& obj)
     {
     obj = new DataPopulationObjectClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataPopulationObject
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataPopulationObject*& obj)
     {
     obj = new BaseDataPopulationObject;
     return obj->DecodeThis(buffer);
     }
/*F setBaseObjectClass(objclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void DataPopulationObjectClass::setBaseObjectClass(DataObjectClass *objclass)
{
  BaseObjectClass = objclass;
}
/*F objclass = getBaseObjectClass(objclass)
**
**  DESCRIPTION
**    objclass: The object class
**
**  REMARKS
**
*/
DataObjectClass *DataPopulationObjectClass::getBaseObjectClass()
{
  return BaseObjectClass;
}
/*F baseobj = BasePopulationObject()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataObject *DataPopulationObjectClass::BasePopulationObject()
{
  BaseDataObject *obj;
  if(BaseObjectClass == NULL)
    {
      cerr << "In '" << NameTag << "' the BasePopulationObject class is not defined" << endl;
      obj = (BaseDataObject *) new BaseDataPopulationObject();
    }
  else    
    obj = BaseObjectClass->BaseDataObjectExample();
  return obj;
}
/*S BaseDataPopulation
 */ 
/*F BaseDataPopulation()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataPopulation::BaseDataPopulation()
  : GeneticObject(NULL),
    PopulationSize(0),
    PopulationObjectNameRoot("Object"),
    popCount(0),
    SortedObjects(NULL),
    TotalSum(0.0),
    MinimumCost(0.0),
    MaximumCost(0.0)
{
  Identification = POPULATION_POPULATION_ID;
  NameTag = POPULATION_POPULATION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  
  String pop(" ---- The Set of Population Objects ---- \n");
  setTitle(pop);
  String delim("\n");
  setDelimitor(delim);
} 
/*F BaseDataPopulation(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataPopulation::BaseDataPopulation(const BaseDataPopulation& data)
  : BaseDataSetOfObjects(data),
    PopulationSize(data.PopulationSize),
    PopulationObjectNameRoot(data.PopulationObjectNameRoot),
    popCount(data.popCount),
    SortedObjects(data.SortedObjects),
    TotalSum(data.TotalSum),
    MinimumCost(data.MinimumCost),
    MaximumCost(data.MaximumCost)    
{
  GeneticObject = (BaseDataGeneticObject *) PointerClone(data.GeneticObject);
  if(data.SortedObjects != NULL)
    SortedObjects = data.SortedObjects->Clone();
  else
    SortedObjects = NULL;
}
/*F BaseDataPopulation()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataPopulation::~BaseDataPopulation()
{
  if(GeneticObject != NULL)
    delete GeneticObject;
  if(SortedObjects != NULL)
    delete SortedObjects;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataPopulation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataPopulation::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataPopulation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**    Read expects:
**    - The set of population objects are not read in
**    - 'Population:' as keyword
**    - population size as integer
**
**  REMARKS
**
*/
bool BaseDataPopulation::Read(istream& in, DataObjectClass* objc, const String& name)
{
  DataPopulationClass *popclass = (DataPopulationClass *) objc;
  bool result = true;
  StreamObjectInput str(in,' ');
  String key = str.ReadNext();
  if(key == "Genetic:")
    {
      DataGeneticObjectClass *genclass = popclass->getGeneticClass();
      if(genclass != NULL)
	{
	  GeneticObject = (BaseDataGeneticObject *) genclass->BaseDataObjectExample();
	  GeneticObject->Read(in,genclass,name);
	  
	  key = str.ReadNext();
	  if(key == "Population:")
	    {
	      String popsizeS = str.ReadNext();
	      PopulationSize = popsizeS.ToInteger();
	    }
	  else
	    {
	      cerr << "Expected 'Population:' found '" << key << "'" << endl;
	      result = false;
	    }
	}
      else
	{
	  cerr << "Genetic Class not define yet: Genetic Object not read in" << endl;
	  result = false;
	}
    }
  else
    {
      result = false;
      cerr << "Expected 'Genetic:' got '" << key << "'" << endl;
    }
  return result;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataPopulation
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataPopulation::print(ostream& out) const
{
  BaseDataSetOfObjects::print(out);
  out << "Standard Size of Population: " << PopulationSize << endl;
  out << "Current Heuristic: " << TotalSum;
  out << "   Min: " << MinimumCost << "   Max: " << MaximumCost;
  out << "   Diff: " << MaximumCost - MinimumCost;
  double popsize = (double) PopulationSize;
  out << "  Ave: " << (MaximumCost - MinimumCost) / popsize << endl;

  if(SortedObjects != NULL)
    SortedObjects->print(out);

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataPopulation
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataPopulation::Clone()
{
  BaseDataPopulation *obj = new BaseDataPopulation(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataPopulation
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataPopulation::CopyClone(Identify * obj)
{
  BaseDataPopulation *objfull = (BaseDataPopulation *) obj;
  
  *this = *objfull;
  if(objfull->SortedObjects != NULL)
    SortedObjects = objfull->SortedObjects->Clone();
  GeneticObject = (BaseDataGeneticObject *) PointerClone(objfull->GeneticObject);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPopulation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPopulation::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::EncodeThis(buffer);
  result = result && Encode(buffer,PopulationSize);
  result = result && Encode(buffer,TotalSum);
  result = result && Encode(buffer,PopulationObjectNameRoot);
  result = result && PointerEncode(buffer,(BaseDataObject *&) GeneticObject);
  //result = result && SortedObjects->EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPopulation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPopulation::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::DecodeThis(buffer);
  result = result && Decode(buffer,PopulationSize);
  result = result && Decode(buffer,TotalSum);
  result = result && Decode(buffer,PopulationObjectNameRoot);
  result = result && PointerDecode(buffer,(BaseDataObject *&) GeneticObject);
  //result = result && SortedObjects->DecodeThis(buffer);

  return result;
} 
/*F ans = GenerateInitialPopulation(popobjectbase,popclass)  BaseDataPopulation
**
**  DESCRIPTION
**    instances: The set of instances
**    instsclass: The instances class
**
**  REMARKS
**
*/
bool BaseDataPopulation::GenerateInitialPopulation(BaseDataPopulationObject *popobjectbase,
						   DataPopulationClass *popclass)
{
  bool result = true;
  DataPopulationObjectClass *popobjectclass = popclass->getPopulationObjectClass();
  BaseDataPopulationObject *popobject;
  unsigned int popsize = getPopulationSize();
  for(unsigned int i=0;i<popsize;i++)
    {
      AddPopulationObject(popobjectbase);
      String popobjname = popobjectbase->NameTag;
      popobject = (BaseDataPopulationObject *) GetObject(popobjname);
      BaseDataObject *obj = GeneticObject->GeneticInitializeObject(popclass->getGeneticClass());
      popobject->AddValueObject(obj,popobjectclass);
      popobject->AssignValue( ((double) random()) / ((double) RAND_MAX) );
    }
  return result;
}
/*F AddPopulationObject(obj) Add object to population
**
**  DESCRIPTION
**    obj: The population element
**
**  REMARKS
**
*/
void BaseDataPopulation::AddPopulationObject(BaseDataObject *obj)
{
  String *name = GenerateNextPopulationObjectName(); 
  obj->NameTag = *name;
  delete name;
  AddObject(obj);
}
/*F setPopulationSize(popsize)  . . . . . . . . . . . . . . . . . . . . . set
**
**  DESCRIPTION
**    popsize: The normal size of the population (used for filtering and initialization)
**
**  REMARKS
**
*/
void BaseDataPopulation::setPopulationSize(unsigned int popsize)
{
  PopulationSize = popsize;
}
/*F popsize = getPopulationSize() . . . . . . . . . . . . . . . . . . . . get
**
**  DESCRIPTION
**    popsize: The current population normal size
**
**  REMARKS
**
*/
unsigned int BaseDataPopulation::getPopulationSize()
{
  return PopulationSize;
}
/*F name = GeneratePopulationObjectName(i)  . . . . . generic population name
**
**  DESCRIPTION
**    name: The generated name (using the PopulationObjectNameRoot)
**
**  REMARKS
**
*/
String *BaseDataPopulation::GenerateNextPopulationObjectName()
{ 
  String z("0");
  String countS = Int2String(popCount);
  String *popobjectname = new String(PopulationObjectNameRoot);
  if(popCount < 100)
    popobjectname->AppendToEnd(z);
  if(popCount < 10)
    popobjectname->AppendToEnd(z);
  popobjectname->AppendToEnd(countS);

  popCount++;
  return popobjectname;
}
/*F AssignPopulationValue(value,name)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataPopulation::AssignPopulationValue(double value, String& name)
{
  bool result = true;
  if(IsInList(name))
    {
      BaseDataPopulationObject *obj = (BaseDataPopulationObject *) GetObject(name);
      obj->AssignValue(value);
    }
  else
    {
      cerr << "Population object '" << name << "' not found, no value assigned" << endl;
      result = false;
    }
  return result;
}
/*F InitializePopulationInformation(base,instances,instsclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataPopulation::InitializePopulationInformation(BaseDataObject *obj,
							 BaseDataSetOfInstances *insts, 
							 DataSetOfInstancesClass *instcls)
{
  DataSetOfObjectsClass *setclasses = instcls->PointerToAllowedClasses();
  DataGeneticObjectClass *genclass = (DataGeneticObjectClass *) setclasses->GetObjectClass(GeneticObject->GetType());
  GeneticObject->GeneticInitialize(genclass,insts,instcls);
}
 
/*F SortPopulation()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataPopulation::SortPopulation()
{
  PairList<double,String> tosort;
  ObjectList<String> names = ListOfObjectNames();
  BasicPair<double,String> *p = new BasicPair<double,String>;

  ObjectList<String>::iterator name;
  for(name = names.begin(); name != names.end();name++)
    {
      BaseDataPopulationObject *obj = (BaseDataPopulationObject *) GetObject(*name);
      p->I = -obj->GetValue();
      p->J = *name;
      tosort.AddObject(*p);
    }
  tosort.sort();
  if(SortedObjects != NULL)
    delete SortedObjects;
  SortedObjects = new ObjectList<String>;
  tosort.VectorOfSeconds(*SortedObjects);
  delete p;
}
/*F sum = UpdateTotalPopulationValueSum() . . . . . . .  update total pop sum
**
**  DESCRIPTION
**    sum: The sum of all the values in the population
**
**    This sum is used for the selection of single object (based on
**    probability) from the data base.
**
**  REMARKS
**
*/
double BaseDataPopulation::UpdateTotalPopulationValueSum()
{
  ObjectList<String> names = ListOfObjectNames();
  ObjectList<String>::iterator name;
  double value;
  MinimumCost = RAND_MAX;
  MaximumCost = -RAND_MAX;
  TotalSum = 0.0;
  for(name=names.begin();
      name != names.end();
      name++)
    {
      BaseDataPopulationObject *obj = (BaseDataPopulationObject *) GetObject(*name);
      value= obj->GetValue();
      TotalSum += value;
      if(value < MinimumCost)
	MinimumCost = value;
      if(value > MaximumCost)
	MaximumCost = value;
    }
  return TotalSum;
}
/*F names = getSortedObjects()
**
**  DESCRIPTION
**    names: The names of the population ordered in terms of their values
**
**  REMARKS
**
*/
ObjectList<String> *BaseDataPopulation::getSortedObjects()
{
  return SortedObjects;
}
 
/*F TransferEssentialData(pop)  . . . . . . . . . . . . . . . . copy from pop
**
**  DESCRIPTION
**    pop: The original population from which to copy the essential information
**   
**  REMARKS
**
*/
void BaseDataPopulation::TransferEssentialData(BaseDataPopulation *pop)
{
  PopulationSize = pop->getPopulationSize();
  PopulationObjectNameRoot = pop->PopulationObjectNameRoot;
  GeneticObject = (BaseDataGeneticObject *) PointerClone(pop->getGeneticObject());
}
/*F obj = getGeneticObject()  . . . . . .  base genetic object for population
**
**  DESCRIPTION
**    obj: The base genetic object on which the population is based.
**
**  REMARKS
**
*/
BaseDataGeneticObject *BaseDataPopulation::getGeneticObject()
{
  return GeneticObject;
}
/*F sum = getTotalSum()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
double BaseDataPopulation::getTotalSum()
{
  return TotalSum;
}
/*S DataPopulationClass
 */
/*F DataPopulationClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataPopulationClass::DataPopulationClass()
  : ObjectClass(NULL),
    GeneticClass(NULL)
{
  Identification = POPULATION_POPULATION_ID;
  NameTag = POPULATION_POPULATION_NAME;
  SubClass = "SetOfObjects";
  EncodeDecodeClass = NameTag;
} 
/*F DataPopulationClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataPopulationClass::DataPopulationClass(const DataPopulationClass& data)
  : DataSetOfObjectsClass(data)
{
  ObjectClass = (DataPopulationObjectClass *) PointerClone((DataObjectClass *) data.ObjectClass);
  GeneticClass = (DataGeneticObjectClass *) PointerClone((DataObjectClass *) data.GeneticClass);
} 
 
/*F DataPopulationClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataPopulationClass::DataPopulationClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataSetOfObjectsClass(id,name,descr),
    ObjectClass(NULL),
    GeneticClass(NULL)
{
  SubClass = "SetOfObjects";
  EncodeDecodeClass = POPULATION_POPULATION_NAME;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataPopulationClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataPopulationClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  out << endl;
  out << "------------- with PopulationObject:" << endl;
  PointerPrint(out,"PopulationObject:", "No Object Defined\n", ObjectClass);
  PointerPrint(out,"GeneticObject:", "No Genetic Object Defined\n", GeneticClass);
  out << endl;
  
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataPopulationClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataPopulationClass, there is no further information.
**
**  REMARKS
**
*/
bool DataPopulationClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  //bool result = DataSetOfObjectsClass::Read(in,set);
  bool result = true;
  StreamObjectInput str(in,' ');
  String baseS = str.ReadNext();
  if(set.PointerToAllowedClasses()->IsInList(baseS))
    {
      ObjectClass = (DataPopulationObjectClass *) set.PointerToAllowedClasses()->GetObjectClass(baseS)->Clone();
      baseS = str.ReadNext();
      if(set.PointerToAllowedClasses()->IsInList(baseS))
	{
	  GeneticClass = (DataGeneticObjectClass *) set.PointerToAllowedClasses()->GetObjectClass(baseS)->Clone();
	}
      else
	{
	  cerr << "Genetic Object Base Data type not found: '" << baseS << "'" << endl;
	  result = false;
	}
    }
  else
    {
      cerr << "Population Object Base Data type not found: '" << baseS << "'" << endl;
      result = false;
    }
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataPopulationClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataPopulationClass::CopyClone(Identify *  objc)
{
  DataPopulationClass *objcfull = (DataPopulationClass *) objc;
  *this = *objcfull;
  ObjectClass = (DataPopulationObjectClass *) PointerClone((DataObjectClass *) objcfull->ObjectClass);
  GeneticClass = (DataGeneticObjectClass *) PointerClone((DataObjectClass *) objcfull->GeneticClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataPopulationClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataPopulationClass::Clone()
{
  DataPopulationClass* id = new DataPopulationClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataPopulationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPopulationClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,(BaseDataObject *&) ObjectClass);
  result = result && PointerEncode(buffer,(BaseDataObject *&) GeneticClass);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataPopulationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPopulationClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) ObjectClass);
  result = result && PointerDecode(buffer,(BaseDataObject *&) GeneticClass);
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
BaseDataObject * DataPopulationClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataPopulation();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataPopulationClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataPopulationClass*& obj)
     {
     obj = new DataPopulationClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataPopulation
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataPopulation*& obj)
     {
     obj = new BaseDataPopulation;
     return obj->DecodeThis(buffer);
     }
 
/*F setPopulationObjectClass(objclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void DataPopulationClass::setPopulationObjectClass(DataPopulationObjectClass *objclass)
{
  ObjectClass = objclass;
}
 
/*F objclass = getPopulationObjectClass()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataPopulationObjectClass *DataPopulationClass::getPopulationObjectClass()
{
  return ObjectClass;
}
 
/*F cls = getGeneticClass() . . . . . . . . . . . . . . . . base genetic info
**
**  DESCRIPTION
**    cls: The base genetic information for the population class
**
**  REMARKS
**
*/
DataGeneticObjectClass *DataPopulationClass::getGeneticClass()
{
  return GeneticClass;
}

/*S BaseDataPopulationCost
 */ 
/*F BaseDataPopulationCost()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataPopulationCost::BaseDataPopulationCost()
  : Expression(NULL)
{
  Identification = POPULATION_COST_ID;
  NameTag = POPULATION_COST_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataPopulationCost(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataPopulationCost::BaseDataPopulationCost(const BaseDataPopulationCost& data)
  : BaseDataOptimizeCostFunction(data)
{
  Expression = (BaseDataParameterizedFunction *) PointerClone((BaseDataObject *) data.Expression);
}
/*F ~BaseDataPopulationObject() . . . . . . . . . . . . . . . . .  destructor
**
**  DESCRIPTION
**    The 'Expression' pointer is deleted
**
**  REMARKS
**
*/
BaseDataPopulationCost::~BaseDataPopulationCost()
{
  if(Expression != NULL)
    delete Expression;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataPopulationCost
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataPopulationCost::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataPopulationCost
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataPopulationCost::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOptimizeCostFunction::Read(in,objc,name);
  DataPopulationCostClass *cexp = (DataPopulationCostClass *) objc;
  DataOperationClass *cop = cexp->getExpressionClass();
  Expression = (BaseDataParameterizedFunction *) cop->BaseDataObjectExample();

  Expression->SetType(cop->Identification);
  result = result && Expression->Read(in,cop,name);

  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataPopulationCost
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataPopulationCost::print(ostream& out) const
{
  BaseDataOptimizeCostFunction::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataPopulationCost
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataPopulationCost::Clone()
{
  BaseDataPopulationCost *obj = new BaseDataPopulationCost(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataPopulationCost
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataPopulationCost::CopyClone(Identify * obj)
{
  BaseDataPopulationCost *objfull = (BaseDataPopulationCost *) obj;
  *this = *objfull;
  BaseDataOptimizeCostFunction::CopyClone(obj);
  Expression = (BaseDataParameterizedFunction *) PointerClone((DataObjectClass *) objfull->Expression);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPopulationCost
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPopulationCost::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOptimizeCostFunction::EncodeThis(buffer);
  result = result && PointerEncode(buffer,(BaseDataObject *&) Expression);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPopulationCost
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPopulationCost::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOptimizeCostFunction::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Expression);
  return result;
}
/*F InitializeParameters(costclass,run,runclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataPopulationCost::InitializeParameters(DataOptimizeCostFunctionClass *costclass,
						  BaseDataSetOfInstances*,
						  DataSetOfInstancesClass *instsclass)
{
}
/*F object = operator()(instance,instclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataObject *BaseDataPopulationCost::operator()(DataObjectClass *objclass,
						   BaseDataObject *x,
						   DataObjectClass *xclass)
{
  bool bans = true;
  DataOptimizeCostFunctionClass *costclass = (DataOptimizeCostFunctionClass *) objclass;
  BaseDataInstance *instance = (BaseDataInstance *) x;
  DataInstanceClass *instclass = (DataInstanceClass *) xclass;

  DataPopulationCostClass *pcostclass = (DataPopulationCostClass *) costclass;
  BaseDataObject *ans;
  BaseDataParameterizedFunction *pfunc = (BaseDataParameterizedFunction *) getExpression();
  BaseDataPopulation *pop = (BaseDataPopulation *) getParameters();
  ObjectList<String> names = pop->ListOfObjectNames();
  ObjectList<String>::iterator name;
  BaseDataReal *anscost = new BaseDataReal();
  for(name = names.begin(); name != names.end() && bans; name++)
    {
      BaseDataPopulationObject *popobj = (BaseDataPopulationObject *) pop->GetObject(*name);
      ans = pfunc->operator()((DataObjectClass *) pcostclass->getExpressionClass(),
			      popobj->getValueObject(),
			      (BaseDataObject *) instance,
			      (DataObjectClass *) instclass->PointerToAllowedClasses(),
			      (DataObjectClass *) instclass);
      AdjustCosts(anscost,ans,instclass->PointerToAllowedClasses());
      bans = popobj->AddInstanceValue(anscost);
      AccumulateCosts(anscost);
      delete ans;
    }
  delete anscost;
  return NULL;
}
/*F object = operator()(instance,instclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataObject *BaseDataPopulationCost::operator()(DataObjectClass *objclass,
						   BaseDataObject *x,
						   BaseDataObject *y,
						   DataObjectClass *xclass,
						   DataObjectClass *yclass)
{
  bool bans = true;
  DataOptimizeCostFunctionClass *costclass = (DataOptimizeCostFunctionClass *) objclass;
  BaseDataSetOfInstances *instances = (BaseDataSetOfInstances *) y;
  DataSetOfInstancesClass *instancesclass = (DataSetOfInstancesClass *) yclass;
  
  DataPopulationCostClass *pcostclass = (DataPopulationCostClass *) costclass;
  BaseDataObject *ans;
  BaseDataParameterizedFunction *pfunc = (BaseDataParameterizedFunction *) getExpression();
  BaseDataPopulation *pop = (BaseDataPopulation *) getParameters();
  BaseDataReal *anscost = new BaseDataReal();
  
  ObjectList<String> names = pop->ListOfObjectNames();
  ObjectList<String>::iterator instname;
  ObjectList<String>::iterator name;
  for(name = names.begin(); name != names.end() && bans; name++)
    {
      BaseDataPopulationObject *popobj = (BaseDataPopulationObject *) pop->GetObject(*name);
      pfunc->InsertParameterSet((BaseDataParameterSet *) popobj->getValueObject());
      pfunc->DontInsertParametersWithOperation();
      for(instname = getTrainInstanceNames().begin(); instname != getTrainInstanceNames().end(); instname++)
	{
	  BaseDataObject *instance = (BaseDataObject *) instances->GetInstance(*instname);      
	  cout << "RepeatInstance alot" << endl;
	  for(unsigned int i=0;i<1000000;i++)
	    {
	      ans = pfunc->operator()((DataObjectClass *) pcostclass->getExpressionClass(),
				      popobj->getValueObject(),
				      (BaseDataObject *) instance,
				      (DataObjectClass *) instancesclass->PointerToAllowedClasses(),
				      (DataObjectClass *) instancesclass);
	      delete ans;
	    }
	  ans = pfunc->operator()((DataObjectClass *) pcostclass->getExpressionClass(),
				  popobj->getValueObject(),
				  (BaseDataObject *) instance,
				  (DataObjectClass *) instancesclass->PointerToAllowedClasses(),
				  (DataObjectClass *) instancesclass);
	  AdjustCosts(anscost,ans,instancesclass->PointerToAllowedClasses());
	  bans = popobj->AddInstanceValue(anscost);
	  AccumulateCosts(anscost);
	  delete ans;
	  pfunc->InsertParametersWithOperation();
	}
    }
  delete anscost;
  return NULL;
}
/*F exp = getExpression() . . . . . . . . . . . . . get pointer to expression
**
**  DESCRIPTION
**    exp: The pointer to the expression
**
**  REMARKS
**
*/
BaseDataParameterizedFunction *BaseDataPopulationCost::getExpression()
{
  return Expression;
}
/*F AdjustCosts(value,obj)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataPopulationCost::AdjustCosts(BaseDataReal *value, BaseDataObject *obj, DataSetOfObjectsClass *set)
{
  double v;
  if(set->IsOfClass(*obj,NUMERIC_BASE_NAME))
    {
      BaseDataNumeric *num = (BaseDataNumeric *) obj;
      v = num->Distance();
    }
  else if(set->IsOfClass(*obj,LOGICAL_BASE_NAME))
    {
      BaseDataLogical *num = (BaseDataLogical *) obj;
      v = num->GetValue();
    }
  else
    {
      cerr << "Result of Expression is not a number (value remains unchanged):" << endl;
      obj->print(cerr);
      cerr << endl;
      cerr << "-------- Object Returned as NULL -------------" << endl;
      v = 0.0;
    }
  /*
  double vadjusted = 100000;
  if(v > .00001)
    vadjusted = 1.0 / v;
  value->SetValue(vadjusted);  
  */
  value->SetValue(v);
}
/*F newcost = AccumulateCosts(cost)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataPopulationCost::AccumulateCosts(BaseDataObject *cost)
{
  BaseDataReal *rcost = (BaseDataReal *) cost;
  BaseDataReal *val = (BaseDataReal *) getCurrentCost();
  val->SetValue(val->GetValue() + rcost->GetValue());
}
/*F newcost = InitializeCost(cost)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataPopulationCost::InitializeCost()
{
  BaseDataReal *value = new BaseDataReal();
  value->SetValue(0.0);
  setCurrentCost(value);
  BaseDataPopulation *pop = (BaseDataPopulation *) getParameters();
 
  ObjectList<String> names = pop->ListOfObjectNames();
  ObjectList<String>::iterator name;
  for(name = names.begin(); name != names.end(); name++)
    {
      BaseDataPopulationObject *obj = (BaseDataPopulationObject *) pop->GetObject(*name);
      obj->AssignValue(0.0);
    }
}
 
/*S DataPopulationCostClass
 */
/*F DataPopulationCostClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataPopulationCostClass::DataPopulationCostClass()
  : ExpressionClass(NULL)
{
  Identification = POPULATION_COST_ID;
  NameTag = POPULATION_COST_NAME;
  SubClass = "OptimizeCostFunction";
  EncodeDecodeClass = NameTag;
} 
/*F DataPopulationCostClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataPopulationCostClass::DataPopulationCostClass(const DataPopulationCostClass& data)
  : DataOptimizeCostFunctionClass(data)
{
  //PopulationClass = (DataPopulationClass *) PointerClone(data.PopulationClass);
  ExpressionClass = (DataParameterizedFunctionClass *) PointerClone((DataObjectClass *) data.ExpressionClass);
  
} 
/*F DataPopulationCostClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataPopulationCostClass::DataPopulationCostClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOptimizeCostFunctionClass(id,name,descr),
    ExpressionClass(NULL)
{
  SubClass = "OptimizeCostFunction";
  EncodeDecodeClass = "PopulationCost";
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataPopulationCostClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataPopulationCostClass::print(ostream& out) const
{
  DataOptimizeCostFunctionClass::print(out);
  PointerPrint(out,"ExpressionClass:", "No Expression Class Specified\n",ExpressionClass);
  out << endl;
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataPopulationCostClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataPopulationCostClass, there is no further information.
**
**  REMARKS
**
*/
bool DataPopulationCostClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  StreamObjectInput str(in,' ');
  bool result = DataOptimizeCostFunctionClass::Read(in,set);
  String TreeClassS = str.ReadNext();
  if(set.PointerToAllowedClasses()->IsInList(TreeClassS))
    {
      DataObjectClass *oclass = set.PointerToAllowedClasses()->GetObjectClass(TreeClassS);
      ExpressionClass = (DataParameterizedFunctionClass *) oclass->Clone();
    }
  else
    {
      cerr << "Tree Expression Data type not found: '" << TreeClassS << "'" << endl;
      result = false;
    }
  /*
    if(set.PointerToAllowedClasses()->IsInList(name))
    {
    PopulationClass = (DataPopulationClass *) set.PointerToAllowedClasses()->GetObjectClass(name);
    }
    else
    {
    cerr << "Population class type not found: '" << name << "'" << endl;
    result = false;
    }
  */
  return result;
}
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataPopulationCostClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataPopulationCostClass::CopyClone(Identify *  objc)
{
  DataPopulationCostClass *objcfull = (DataPopulationCostClass *) objc;
  *this = *objcfull;
  ExpressionClass = (DataParameterizedFunctionClass *) PointerClone((DataObjectClass *) objcfull->ExpressionClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataPopulationCostClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataPopulationCostClass::Clone()
{
  DataPopulationCostClass* id = new DataPopulationCostClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataPopulationCostClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPopulationCostClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOptimizeCostFunctionClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,(BaseDataObject *&) ExpressionClass);
  //result = result && PointerEncode(buffer,(BaseDataObject *&) PopulationClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataPopulationCostClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPopulationCostClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOptimizeCostFunctionClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) ExpressionClass);
  //result = result && PointerDecode(buffer,(BaseDataObject *&) PopulationClass);
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
BaseDataObject * DataPopulationCostClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataPopulationCost();
  obj->SetType(Identification);
  return obj;
}
/*F exp = getExpression() . . . . . . . . . . . . . get pointer to expression
**
**  DESCRIPTION
**    exp: The pointer to the expression
**
**  REMARKS
**
*/
DataParameterizedFunctionClass *DataPopulationCostClass::getExpressionClass()
{
  return ExpressionClass;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataPopulationCostClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataPopulationCostClass*& obj)
     {
     obj = new DataPopulationCostClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataPopulationCost
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataPopulationCost*& obj)
     {
     obj = new BaseDataPopulationCost;
     return obj->DecodeThis(buffer);
     }

/*S BaseDataGeneticBasedOptimization
 */ 
/*F BaseDataGeneticBasedOptimization()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGeneticBasedOptimization::BaseDataGeneticBasedOptimization()
  : CostFunctionS("CostFunction"),
    PopulationS("Population")
{
  Identification = POPULATION_GENETICBASE_ID;
  NameTag = POPULATION_GENETICBASE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataGeneticBasedOptimization(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGeneticBasedOptimization::BaseDataGeneticBasedOptimization(const BaseDataGeneticBasedOptimization& data)
  : BaseDataOptimizeOperation(data)
{
}
 
/*F ~BaseDataGeneticBasedOptimization()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGeneticBasedOptimization::~BaseDataGeneticBasedOptimization()
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataGeneticBasedOptimization
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataGeneticBasedOptimization::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataGeneticBasedOptimization
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataGeneticBasedOptimization::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOptimizeOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataGeneticBasedOptimization
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGeneticBasedOptimization::print(ostream& out) const
{
  BaseDataOptimizeOperation::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataGeneticBasedOptimization
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGeneticBasedOptimization::Clone()
{
  BaseDataGeneticBasedOptimization *obj = new BaseDataGeneticBasedOptimization(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataGeneticBasedOptimization
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGeneticBasedOptimization::CopyClone(Identify * obj)
{
  BaseDataGeneticBasedOptimization *objfull = (BaseDataGeneticBasedOptimization *) obj;
  *this = *objfull;
  BaseDataOptimizeOperation::CopyClone(obj);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGeneticBasedOptimization
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticBasedOptimization::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOptimizeOperation::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGeneticBasedOptimization
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticBasedOptimization::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOptimizeOperation::DecodeThis(buffer);
  return result;
}
/*F ans = SetUpAlgorithms(instances,instancesclass,run,runclass)  . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataGeneticBasedOptimization::SetUpAlgorithms(BaseDataSetOfInstances *insts,
						      DataSetOfInstancesClass *instsclass,
						      BaseDataAlgorithmRun *run,
						      DataAlgorithmRunClass *runclass)
{
  return BaseDataOptimizeOperation::SetUpAlgorithms(insts,instsclass,run,runclass);
}
/*F ans = CheckInput(instances,instancesclass,run,runclass) . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**
**  REMARKS
**
*/
bool BaseDataGeneticBasedOptimization::CheckInput(BaseDataSetOfInstances *insts,
						  DataSetOfInstancesClass *instsclass,
						  BaseDataAlgorithmRun *run,
						  DataAlgorithmRunClass *runclass)
{
  bool result = BaseDataOptimizeOperation::CheckInput(insts,instsclass,run,runclass);
  return result;
}
/*F ans = SetUpInput(instances,instancesclass,run,runclass) . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataGeneticBasedOptimization::SetUpInput(BaseDataSetOfInstances* instances,
						 DataSetOfInstancesClass* instancesclass,
						 BaseDataAlgorithmRun *run,
						 DataAlgorithmRunClass* rclass)
{
  bool result = BaseDataOptimizeOperation::SetUpInput(instances,instancesclass,run,rclass);
  return result;
}
/*F ans = Calculate(instances,instancesclass,run,runclass)  . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataGeneticBasedOptimization::Calculate(BaseDataSetOfInstances *insts,
						 DataSetOfInstancesClass *instsclass,
						 BaseDataAlgorithmRun *run,
						 DataAlgorithmRunClass *runclass)
{
  BaseDataOptimizeCostFunction *costfunction = getCurrentCostFunction();
  instsclass->SetDebugLevel(runclass->getDebugLevel());
  if(instsclass->getDebugLevel() > 3)
    {
      cout << " ------------------ CostFunction: -------------------- " << endl;
      costfunction->print(cout);
      cout << endl;
      cout << " ------------------ CostFunction: -------------------- " << endl;
    }
  bool result =  BaseDataOptimizeOperation::Calculate(insts,instsclass,run,runclass);
  return result;
}
/*F ans = WriteOutputValues(instances,instancesclass,run,runclass)  algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataGeneticBasedOptimization::WriteOutputValues(BaseDataSetOfInstances *insts,
							 DataSetOfInstancesClass *instsclass,
							 BaseDataAlgorithmRun *run,
							 DataAlgorithmRunClass *runclass)
{
  bool result = BaseDataOptimizeOperation::WriteOutputValues(insts,instsclass,run,runclass);
  return result;
}
/*F ans = ConcludeRun(instances,instancesclass,run,runclass)  . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataGeneticBasedOptimization::ConcludeRun(BaseDataSetOfInstances *insts,
						   DataSetOfInstancesClass *instsclass,
						   BaseDataAlgorithmRun *run,
						   DataAlgorithmRunClass *runclass)
{
  bool result = BaseDataOptimizeOperation::ConcludeRun(insts,instsclass,run,runclass);
  return result;
}
 
/*F InitializeObjectToOptimize(cost,cclass,insts,instsclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataGeneticBasedOptimization::InitializeObjectToOptimize(BaseDataOptimizeCostFunction *cost,
								  DataOptimizeCostFunctionClass *cclass,
								  BaseDataSetOfInstances*,
								  DataSetOfInstancesClass*)
{
}
/*F PerformSingleIteration(intances,instsclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataGeneticBasedOptimization::PerformSingleIteration(BaseDataSetOfObjects *parameters,
							      DataSetOfObjectsClass *parclass,
							      BaseDataSetOfInstances *instances,
							      DataSetOfInstancesClass *instsclass)
{
  bool result = true;
  BaseDataPopulation *pop = (BaseDataPopulation *) parameters;
  DataPopulationClass *popclass = (DataPopulationClass *) parclass;
  BaseDataPopulationCost *optcost = (BaseDataPopulationCost *) getCurrentCostFunction();
  BaseDataPopulationObject *popobjectbase = (BaseDataPopulationObject *) optcost->GetOptimizeObject();

  unsigned int pairsize = pop->getPopulationSize()/2;
  unsigned int cnt;
  if(instsclass->getDebugLevel() > 3)
    {
      cout << "begin: BaseDataGeneticBasedOptimization::PerformSingleIteration -- Population before crossover" << endl;
      pop->print(cout);
      cout << endl << "end:   BaseDataGeneticBasedOptimization::PerformSingleIteration -- Population before crossover" << endl;
    }
  unsigned int poptype = pop->GetType();
  DataPopulationObjectClass *objclass = 
    (DataPopulationObjectClass *) instsclass->PointerToAllowedClasses()->GetObjectClass(poptype);

  pop->UpdateTotalPopulationValueSum();
  for(cnt = 0;cnt < pairsize; cnt++)
    {
      String left  = SelectObjectFromPopulation(pop);
      String right = SelectObjectFromPopulation(pop);
      if(instsclass->getDebugLevel() > 2)
	cout << "Selected ['" << left << "', '" << right << "']" << endl;
      AddCrossOverObjects(popobjectbase,objclass,
			  pop,popclass,
			  left,right);
    }

  double dpopsize = ((double) pop->getPopulationSize())*0.1;
  int mutatecount = (int) dpopsize;
  if(instsclass->getDebugLevel() > 2)
    cout << "Number of Mutants: " << mutatecount << endl;
  for(cnt = 0;cnt < (unsigned int) mutatecount; cnt++)
    {
      String mutant  = SelectObjectFromPopulation(pop);
      if(instsclass->getDebugLevel() > 3)
	cout << "Mutant '" << mutant << "'" << endl;
      MutateObject(pop,popclass,mutant);
    }
  if(instsclass->getDebugLevel() > 3)
    {
      cout << "begin: BaseDataGeneticBasedOptimization::PerformSingleIteration -- Population" << endl;
      pop->print(cout);
      cout << "end:   BaseDataGeneticBasedOptimization::PerformSingleIteration -- Population" << endl;
    }
  pop->SortPopulation();
  return result;
}
 
/*F name = SelectObjectFromPopulation(pop)
**
**  DESCRIPTION
**    pop: The population
**    name: The selected object from the population
**
**    This routine uses the weights (value) of the population objects
**    to randomly select an object
**
**  REMARKS
**
*/
String& BaseDataGeneticBasedOptimization::SelectObjectFromPopulation(BaseDataPopulation *pop)
{
  double rndm = ((double) random()) / ((double) RAND_MAX);
  double totalvalue = pop->getTotalSum();

  double offset;
  double normit;
  
  double diff = pop->MaximumCost - pop->MinimumCost;
  if(diff > 0.000001)
    {
      offset = pop->MinimumCost;
      normit = diff;
    }
  else
    {
      offset = pop->MinimumCost - 1.0;
      normit = 1.0;
    }
  offset -= 1.0;

  ObjectList<String>::iterator name = pop->getSortedObjects()->begin();
  BaseDataPopulationObject *obj = (BaseDataPopulationObject *) pop->GetObject(*name);
  double totalsize = pop->getSortedObjects()->size();
  
  double top = ( totalvalue - totalsize * offset ) / normit * rndm;
  unsigned count = 0;
  double sum = ( obj->GetValue() - offset ) / normit;
  while( sum <  top )
    {
      name++;
      count++;
      if(count < totalsize)
	obj = (BaseDataPopulationObject *) pop->GetObject(*name);
      else
	{
	  cerr << "SelectObjectFromPopulation: Exceeded list of names" << endl;
	  cerr << obj->NameTag << " Sum,Top: " << sum << " " << top << endl;
	  name--;
	  obj = (BaseDataPopulationObject *) pop->GetObject(*name);
	  sum = top;
	}
      sum += ( obj->GetValue() - offset ) / normit;
    }
  return obj->NameTag;
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataGeneticBasedOptimization::MutateObject(BaseDataPopulation *pop, 
						    DataPopulationClass *popclass,
						    String& mutant)
{
  BaseDataPopulationObject *popobj  = (BaseDataPopulationObject *) pop->GetObject(mutant);
  BaseDataObject *obj = popobj->getValueObject();
  BaseDataGeneticObject *genetic = pop->getGeneticObject();
  DataGeneticObjectClass *gencls = popclass->getGeneticClass();
  bool result = genetic->Mutate(obj,gencls);
  return result;
}
/*F ans = AddCrossOverObjects(popobjectbase,objclass,pop,left,right)
**
**  DESCRIPTION
**    popobjectbase: The basic population object
**    objclass: The class of the population object
**    pop: The total population
**    left,right: The names of the right and left crossoverobjects
**
**    From the ordered list of parameters, a simple crossover operation
**    is performed to create two new population objects.  These objects
**    are then added to the population.
**
**  REMARKS
**
*/
bool BaseDataGeneticBasedOptimization::AddCrossOverObjects(BaseDataPopulationObject *popobjectbase,
							   DataPopulationObjectClass *objclass,
							   BaseDataPopulation *pop, 
							   DataPopulationClass *popclass,
							   String& left, String& right)
{
  bool result = true;
  BaseDataPopulationObject *leftobj  = (BaseDataPopulationObject *) pop->GetObject(left);
  BaseDataPopulationObject *rightobj = (BaseDataPopulationObject *) pop->GetObject(right);
  BaseDataPopulationObject *newleftobj  = (BaseDataPopulationObject *) popobjectbase->Clone();
  BaseDataPopulationObject *newrightobj = (BaseDataPopulationObject *) popobjectbase->Clone();

  BaseDataGeneticObject *genetic = pop->getGeneticObject();
  DataGeneticObjectClass *gencls = popclass->getGeneticClass();

  BaseDataSetOfObjects *pair = genetic->CrossOver(leftobj->getValueObject(),
						  rightobj->getValueObject(),
						  genetic,gencls);
  ObjectList<String> names = pair->ListOfObjectNames();
  if(names.size() == 2)
    {
      String cross1 = names.front();
      names.pop_front();
      String cross2 = names.front();
      BaseDataObject *crossobj1 = pair->GetObject(cross1);
      BaseDataObject *crossobj2 = pair->GetObject(cross2);
      crossobj1->NameTag = leftobj->getValueObject()->NameTag;
      crossobj2->NameTag = rightobj->getValueObject()->NameTag;
      newleftobj->AddValueObject(crossobj1,objclass);
      newrightobj->AddValueObject(crossobj2,objclass);
    }
  else
    {
      cerr << "Error in Cross-Over, no new objects generated" << endl;
    }
  delete pair;

  pop->AddPopulationObject(newleftobj);
  pop->AddPopulationObject(newrightobj);
  delete newleftobj;
  delete newrightobj;

  return result;
}
/*F ans = UpdateCurrentCosts(instances,instsclass)
**
**  DESCRIPTION
**   
**  RE
**
*/
bool BaseDataGeneticBasedOptimization::UpdateCurrentCosts(DataOptimizeCostFunctionClass *costclass,
							  BaseDataSetOfInstances *instances,
							  DataSetOfInstancesClass *instsclass)
{
  bool result = BaseDataOptimizeOperation::UpdateCurrentCosts(costclass,instances,instsclass);

  BaseDataOptimizeCostFunction *costfunc = getCurrentCostFunction();
  BaseDataPopulation *pop = (BaseDataPopulation *) costfunc->ExtractParameters(costclass);
  pop->SortPopulation();
  pop->UpdateTotalPopulationValueSum();
  unsigned int psize = pop->getPopulationSize();
  unsigned int ptype = pop->GetType();
  DataPopulationClass *popclass = 
    (DataPopulationClass *) instsclass->PointerToAllowedClasses()->GetObjectClass(ptype);
  DataPopulationObjectClass *popobjclass = popclass->getPopulationObjectClass();

  BaseDataReal *val = (BaseDataReal *) costfunc->getCurrentCost();
  if(instsclass->getDebugLevel() > 0)
    {
      cout << "Current Heuristic Total: " << val->GetValue() << endl;
      cout << "   Min: " << pop->MinimumCost << "   Max: " << pop->MaximumCost;
      cout << "   Diff: " << pop->MaximumCost - pop->MinimumCost;
      double popsize = (double) psize;
      cout << "  Ave: " << (pop->MaximumCost - pop->MinimumCost) / popsize << endl;
    }

  if(instsclass->getDebugLevel() > 1)
    {
      cout << "Begin: -------------- The Best Elements -----------------------" << endl;
      ObjectList<String> *names = pop->getSortedObjects();
      ObjectList<String>::iterator name;
      unsigned int top = 0;
      for(name = names->begin(); name != names->end(); name++)
	{
	  BaseDataPopulationObject *obj = (BaseDataPopulationObject *) pop->GetObject(*name);
	  if(top < 3)
	    {
	      obj->WriteAsASCII(cout,(DataObjectClass *) popobjclass);
	      cout << endl;
	    }
	  top++;
	}      
      cout << "End: -------------- The Best Elements -----------------------" << endl;
    }
  BaseDataPopulation *newpop = (BaseDataPopulation *) popclass->BaseDataObjectExample();
  newpop->TransferEssentialData(pop);
  for(unsigned int i=0; i<psize ;i++)
    {
      String name = SelectObjectFromPopulation(pop);

      if(pop->IsInList(name))
	{
	  BaseDataPopulationObject *obj = (BaseDataPopulationObject *) pop->GetObject(name);
	  newpop->AddPopulationObject(obj);
	}
      else
	{
	  cerr << "Strange Error, Selected Name that is not in the population" << endl;
	  pop->print(cerr);
	  cerr << endl;
	}
    }
  newpop->SortPopulation();
  costfunc->InsertParameters(newpop);
  return result;
}
/*S DataGeneticBasedOptimizationClass
 */
/*F DataGeneticBasedOptimizationClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGeneticBasedOptimizationClass::DataGeneticBasedOptimizationClass()
{
  Identification = POPULATION_GENETICBASE_ID;
  NameTag = POPULATION_GENETICBASE_NAME;
  SubClass = "OptimizeOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataGeneticBasedOptimizationClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGeneticBasedOptimizationClass::DataGeneticBasedOptimizationClass(const DataGeneticBasedOptimizationClass& data)
  : DataOptimizeOperationClass(data)
{
} 
 
/*F DataGeneticBasedOptimizationClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataGeneticBasedOptimizationClass::DataGeneticBasedOptimizationClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOptimizeOperationClass(id,name,descr)
{
  SubClass = "OptimizeOperation";
  EncodeDecodeClass = "GeneticBasedOptimization";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataGeneticBasedOptimizationClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGeneticBasedOptimizationClass::print(ostream& out) const
{
  DataOptimizeOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataGeneticBasedOptimizationClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGeneticBasedOptimizationClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGeneticBasedOptimizationClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOptimizeOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataGeneticBasedOptimizationClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGeneticBasedOptimizationClass::CopyClone(Identify *  objc)
{
  DataGeneticBasedOptimizationClass *objcfull = (DataGeneticBasedOptimizationClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataGeneticBasedOptimizationClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGeneticBasedOptimizationClass::Clone()
    {
      DataGeneticBasedOptimizationClass* id = new DataGeneticBasedOptimizationClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataGeneticBasedOptimizationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGeneticBasedOptimizationClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOptimizeOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataGeneticBasedOptimizationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGeneticBasedOptimizationClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOptimizeOperationClass::DecodeThis(buffer);
//  result = result && Decode(buffer,-----);

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
BaseDataObject * DataGeneticBasedOptimizationClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataGeneticBasedOptimization();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGeneticBasedOptimizationClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGeneticBasedOptimizationClass*& obj)
     {
     obj = new DataGeneticBasedOptimizationClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataGeneticBasedOptimization
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGeneticBasedOptimization*& obj)
     {
     obj = new BaseDataGeneticBasedOptimization;
     return obj->DecodeThis(buffer);
     }

/*S BaseDataGeneticAlgorithm
 */ 
/*F BaseDataGeneticAlgorithm()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGeneticAlgorithm::BaseDataGeneticAlgorithm()
{
  Identification = POPULATION_GENETICALGORITHM_ID;
  NameTag = POPULATION_GENETICALGORITHM_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataGeneticAlgorithm(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGeneticAlgorithm::BaseDataGeneticAlgorithm(const BaseDataGeneticAlgorithm& data)
  : BaseDataGeneticBasedOptimization(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataGeneticAlgorithm
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataGeneticAlgorithm::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataGeneticAlgorithm
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataGeneticAlgorithm::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataGeneticBasedOptimization::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataGeneticAlgorithm
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGeneticAlgorithm::print(ostream& out) const
{
  BaseDataGeneticBasedOptimization::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataGeneticAlgorithm
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGeneticAlgorithm::Clone()
{
  BaseDataGeneticAlgorithm *obj = new BaseDataGeneticAlgorithm(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataGeneticAlgorithm
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGeneticAlgorithm::CopyClone(Identify * obj)
{
  BaseDataGeneticAlgorithm *objfull = (BaseDataGeneticAlgorithm *) obj;
  *this = *objfull;
  BaseDataGeneticBasedOptimization::CopyClone(obj);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGeneticAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticAlgorithm::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataGeneticBasedOptimization::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGeneticAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticAlgorithm::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataGeneticBasedOptimization::DecodeThis(buffer);
  // The rest

  return result;
}
/*F ans = SetUpAlgorithms(instances,instancesclass,run,runclass)  . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataGeneticAlgorithm::SetUpAlgorithms(BaseDataSetOfInstances *insts,
					       DataSetOfInstancesClass *instsclass,
					       BaseDataAlgorithmRun *run,
					       DataAlgorithmRunClass *runclass)
{
  return BaseDataGeneticBasedOptimization::SetUpAlgorithms(insts,instsclass,run,runclass);
;
}
/*F ans = CheckInput(instances,instancesclass,run,runclass) . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**
**  REMARKS
**
*/
bool BaseDataGeneticAlgorithm::CheckInput(BaseDataSetOfInstances *insts,
					  DataSetOfInstancesClass *instsclass,
					  BaseDataAlgorithmRun *run,
					  DataAlgorithmRunClass *runclass)
{
  bool result = BaseDataGeneticBasedOptimization::SetUpAlgorithms(insts,instsclass,run,runclass);
  return result;
}
/*F ans = SetUpInput(instances,instancesclass,run,runclass) . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataGeneticAlgorithm::SetUpInput(BaseDataSetOfInstances *insts,
					  DataSetOfInstancesClass *instsclass,
					  BaseDataAlgorithmRun *run,
					  DataAlgorithmRunClass *runclass)
{
  bool result = BaseDataGeneticBasedOptimization::SetUpInput(insts,instsclass,run,runclass);
  return result;
}
/*F ans = Calculate(instances,instancesclass,run,runclass)  . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataGeneticAlgorithm::Calculate(BaseDataSetOfInstances *insts,
						DataSetOfInstancesClass *instsclass,
						BaseDataAlgorithmRun *run,
						DataAlgorithmRunClass *runclass)
{
  bool result = BaseDataGeneticBasedOptimization::Calculate(insts,instsclass,run,runclass);
  return result;
}
/*F ans = WriteOutputValues(instances,instancesclass,run,runclass)  algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataGeneticAlgorithm::WriteOutputValues(BaseDataSetOfInstances*,
							DataSetOfInstancesClass *instsclass,
							BaseDataAlgorithmRun* run,
							DataAlgorithmRunClass*)
{
  bool result = true;
  BaseDataOptimizeCostFunction *cost = (BaseDataOptimizeCostFunction *) getCurrentCostFunction();
  int costtype = cost->GetType();
  DataOptimizeCostFunctionClass *costclass = 
    (DataOptimizeCostFunctionClass *) instsclass->PointerToAllowedClasses()->GetObjectClass(costtype);
  BaseDataPopulation *pop = (BaseDataPopulation *) cost->ExtractParameters(costclass);
  ObjectList<String>::iterator name = pop->getSortedObjects()->begin();
  BaseDataObject *obj = (BaseDataObject *) pop->GetObject(*name)->Clone();
  obj->NameTag = FinalResultS;
  run->AddParameter(obj);
  if(instsclass->getDebugLevel() > 0)
    {
      cout << "Best Optimized Result:" << endl;
      obj->print(cout);
      cout << endl;
    }
  delete obj;
  return result;
}
/*F ans = ConcludeRun(instances,instancesclass,run,runclass)  . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataGeneticAlgorithm::ConcludeRun(BaseDataSetOfInstances*,
						  DataSetOfInstancesClass*,
						  BaseDataAlgorithmRun*,
						  DataAlgorithmRunClass*)
{
  bool result = true;
  return result;
}
/*F InitializeObjectToOptimize(cost,cclass,insts,instsclass)
**
**  DESCRIPTION
**    cost: The population cost function
**    cclass: The corresponding cost class
**    insts: The set of instances
**    instsclass: The instances class
**
**    This intializes the population (the object to optimize) through:
**    - InitializePopulationInformation
**    - GenerateInitialPopulation
**    - SortPopulation
**
**  REMARKS
**
*/
void BaseDataGeneticAlgorithm::InitializeObjectToOptimize(BaseDataOptimizeCostFunction *cost,
							  DataOptimizeCostFunctionClass *cclass,
							  BaseDataSetOfInstances *insts,
							  DataSetOfInstancesClass *instsclass)
{
  BaseDataPopulationCost *optcost = (BaseDataPopulationCost *) cost;
  DataPopulationCostClass *costclass = (DataPopulationCostClass *) cclass;
  BaseDataPopulationObject *baseobj = (BaseDataPopulationObject *) optcost->GetOptimizeObject();
  BaseDataPopulation *pop = (BaseDataPopulation *) optcost->ExtractParameters(costclass);
  DataPopulationClass *popclass = (DataPopulationClass *) costclass->getParameterClass();
  if(pop != NULL)
    {
      pop->InitializePopulationInformation(getOptimizeObject(),insts,instsclass);
      pop->GenerateInitialPopulation(baseobj,popclass);
      pop->SortPopulation();
    }
  else
    {
      cerr << "Population not set up yet" << endl;
    }
}
/*S DataGeneticAlgorithmClass
 */
/*F DataGeneticAlgorithmClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGeneticAlgorithmClass::DataGeneticAlgorithmClass()
{
  Identification = POPULATION_GENETICALGORITHM_ID;
  NameTag = POPULATION_GENETICALGORITHM_NAME;
  SubClass = "GeneticBasedOptimization";
  EncodeDecodeClass = NameTag;
} 
/*F DataGeneticAlgorithmClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGeneticAlgorithmClass::DataGeneticAlgorithmClass(const DataGeneticAlgorithmClass& data)
  : DataGeneticBasedOptimizationClass(data)
{
} 
 
/*F DataGeneticAlgorithmClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataGeneticAlgorithmClass::DataGeneticAlgorithmClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataGeneticBasedOptimizationClass(id,name,descr)
{
  SubClass = "GeneticBasedOptimization";
  EncodeDecodeClass = "GeneticAlgorithm";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataGeneticAlgorithmClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGeneticAlgorithmClass::print(ostream& out) const
{
  DataGeneticBasedOptimizationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataGeneticAlgorithmClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGeneticAlgorithmClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGeneticAlgorithmClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataGeneticBasedOptimizationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataGeneticAlgorithmClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGeneticAlgorithmClass::CopyClone(Identify *  objc)
{
  DataGeneticAlgorithmClass *objcfull = (DataGeneticAlgorithmClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataGeneticAlgorithmClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGeneticAlgorithmClass::Clone()
    {
      DataGeneticAlgorithmClass* id = new DataGeneticAlgorithmClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataGeneticAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGeneticAlgorithmClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataGeneticBasedOptimizationClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataGeneticAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGeneticAlgorithmClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataGeneticBasedOptimizationClass::DecodeThis(buffer);
//  result = result && Decode(buffer,-----);

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
BaseDataObject * DataGeneticAlgorithmClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataGeneticAlgorithm();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGeneticAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGeneticAlgorithmClass*& obj)
     {
     obj = new DataGeneticAlgorithmClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataGeneticAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGeneticAlgorithm*& obj)
     {
     obj = new BaseDataGeneticAlgorithm;
     return obj->DecodeThis(buffer);
     }

/*S Utilities
 */
/*F InitialSetOfPopulationEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialSetOfPopulationEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataGeneticObjectClass,BaseDataGeneticObject,GENETIC_OBJECT_NAME);
  EncodeDecodeRegisterClass(DataPopulationObjectClass,BaseDataPopulationObject,POPULATION_OBJECT_NAME);
  EncodeDecodeRegisterClass(DataPopulationClass,BaseDataPopulation,POPULATION_POPULATION_NAME);
  EncodeDecodeRegisterClass(DataPopulationCostClass,BaseDataPopulationCost,POPULATION_COST_NAME);
  EncodeDecodeRegisterClass(DataGeneticBasedOptimizationClass,BaseDataGeneticBasedOptimization,POPULATION_GENETICBASE_NAME);
  EncodeDecodeRegisterClass(DataGeneticAlgorithmClass,BaseDataGeneticAlgorithm,POPULATION_GENETICALGORITHM_NAME);

}
 
/*F AddPopulationClasses(set)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AddPopulationClasses(DataSetOfObjectsClass& set)
{
  String geneticdescr("Single Population Object");
  String objdescr("Single Population Object");
  String popdescr("Population of Objects");
  String costdescr("Population of Objects");
  String genbaseddescr("Population of Objects");
  String genalgdescr("Population of Objects");
  
  DataGeneticObjectClass                 geneticclass(GENETIC_OBJECT_ID,GENETIC_OBJECT_NAME,geneticdescr);
  DataPopulationObjectClass              objclass(POPULATION_OBJECT_ID,POPULATION_OBJECT_NAME,objdescr);
  DataPopulationClass          popclass(POPULATION_POPULATION_ID,POPULATION_POPULATION_NAME,popdescr);
  DataPopulationCostClass     costclass(POPULATION_COST_ID,POPULATION_COST_NAME,costdescr);
  DataGeneticBasedOptimizationClass   genbasedclass(POPULATION_GENETICBASE_ID,POPULATION_GENETICBASE_NAME,genbaseddescr);
  DataGeneticAlgorithmClass genalgclass(POPULATION_GENETICALGORITHM_ID,POPULATION_GENETICALGORITHM_NAME,genalgdescr);

  set.AddObjectClass(geneticclass);
  set.AddObjectClass(objclass);
  set.AddObjectClass(popclass);
  set.AddObjectClass(costclass);
  set.AddObjectClass(genbasedclass);
  set.AddObjectClass(genalgclass);
}
