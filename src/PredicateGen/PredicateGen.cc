/*  FILE     PredicateGen.cc
**  PACKAGE  PredicateGen
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "PredicateGen" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
**  Version 1.1
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#ifdef _unix
//#include <strstream.h"
#endif

#include "CoreDataObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "LogicalOperations.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "PredicateObjects.hh"
#include "PredicateGen.hh"
#include "PrimitiveStats.hh"
#include "EvaluationTree.hh"
#include "ExpressionTree.hh"
#include "DistributionAlgorithm.hh"
//#define DEBUG_LEVEL1

/*S BaseDataCriticalPoints
 */ 
/*F BaseDataCriticalPoints()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataCriticalPoints::BaseDataCriticalPoints()
{
  Identification = PREDGEN_CRITICAL_ID;
  NameTag = PREDGEN_CRITICAL_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

  Points.ChangeTitle("Critical Points and Widths\n");
  Points.ChangeDelimitor(" ");
  
} 
/*F BaseDataCriticalPoints(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataCriticalPoints::BaseDataCriticalPoints(const BaseDataCriticalPoints& data)
  : BaseDataObject(data),
    Parameter(data.Parameter),
    Points(data.Points)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataCriticalPoints
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataCriticalPoints::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static bool TranslateDoublePair(String& str, SymmetricPair<double>* p)
{
  bool result = true;
  String bS;
  String iS;
  String jS;
  str.IsolateNextWord(bS,'[');
  str.IsolateNextWord(iS,',');
  str.IsolateNextWord(jS,']');
  double fi = iS.ToFloat();
  double fj = jS.ToFloat();
  SymmetricPair<double> p1(fi,fj);
  p->I = p1.I;
  p->J = p1.J;
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataCriticalPoints
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataCriticalPoints::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);
  StreamObjectInput strinp(in,' ');
  String key = strinp.ReadNext();
  if(key == "CriticalPoints:")
    {
      SymmetricPair<double> *p = new SymmetricPair<double>;
      
      Parameter = strinp.ReadNext();

      String next = strinp.ReadNext();
      while(!(next == "END") && result)
	{
	  result = result && TranslateDoublePair(next,p);
	  Points.AddObject(*p);
	  next = strinp.ReadNext();
	}
      delete p;
    }
  else
    {
      cerr << "Expecting 'CriticalPoint:', recieved ";
      cerr << key << endl;
      result = false;
    }
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataCriticalPoints
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataCriticalPoints::print(ostream& out) const
{
  BaseDataObject::print(out);

  out << "Critical Points For Parameter: ";
  out << Parameter << endl;
  Points.print(out);

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataCriticalPoints
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataCriticalPoints::Clone()
{
  BaseDataCriticalPoints *obj = new BaseDataCriticalPoints;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataCriticalPoints
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataCriticalPoints::CopyClone(Identify *obj)
{
  BaseDataCriticalPoints *objfull = (BaseDataCriticalPoints *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataCriticalPoints
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataCriticalPoints::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && Points.EncodeThis(buffer); 
  result = result && Encode(buffer,Parameter);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataCriticalPoints
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataCriticalPoints::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && Points.DecodeThis(buffer);
  result = result && Decode(buffer,Parameter);

  return result;
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
SymmetricPairList<double> *BaseDataCriticalPoints::PointerToPoints()
{
  return &Points;
}



 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
String& BaseDataCriticalPoints::getParameterName()
{
  return Parameter;
}

/*S DataCriticalPointsClass
 */
/*F DataCriticalPointsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataCriticalPointsClass::DataCriticalPointsClass()
{
  Identification = PREDGEN_CRITICAL_ID;
  NameTag = PREDGEN_CRITICAL_NAME;
  SubClass = "Object";
  EncodeDecodeClass = NameTag;
} 
/*F DataCriticalPointsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataCriticalPointsClass::DataCriticalPointsClass(const DataCriticalPointsClass& data)
  : DataObjectClass(data)
{
} 
 
/*F DataCriticalPointsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataCriticalPointsClass::DataCriticalPointsClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataObjectClass(id,name,descr)
{
  SubClass = "Object";
  EncodeDecodeClass = PREDGEN_CRITICAL_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataCriticalPointsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataCriticalPointsClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataCriticalPointsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataCriticalPointsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataCriticalPointsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  return DataObjectClass::Read(in,set);
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataCriticalPointsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataCriticalPointsClass::CopyClone(Identify* objc)
{
  DataCriticalPointsClass *objcfull = (DataCriticalPointsClass *) objc;
  *this = *objcfull;
}

/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataCriticalPointsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataCriticalPointsClass::Clone()
    {
      DataCriticalPointsClass* id = new DataCriticalPointsClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataCriticalPointsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataCriticalPointsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataCriticalPointsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataCriticalPointsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
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
BaseDataObject * DataCriticalPointsClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataCriticalPoints();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataCriticalPointsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataCriticalPointsClass*& obj)
     {
     obj = new DataCriticalPointsClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataCriticalPoints
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataCriticalPoints*& obj)
     {
     obj = new BaseDataCriticalPoints;
     return obj->DecodeThis(buffer);
     }

/*S BaseDataReadCriticalPoints
 */ 
/*F BaseDataReadCriticalPoints()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataReadCriticalPoints::BaseDataReadCriticalPoints()
  : InputfileNamesS(CRITICALPOINTS_FILENAME),
    InputrootNameS(CRITICALPOINTS_ROOTNAME),
    OutputPointListS(CRITICALPOINTS_POINTLIST),
    OutputCriticalPointsS(CRITICALPOINTS_CRITICALPOINTS)
{
  Identification = PREDGEN_READ_ID;
  NameTag = PREDGEN_READ_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataReadCriticalPoints(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataReadCriticalPoints::BaseDataReadCriticalPoints(const BaseDataReadCriticalPoints& data)
  : BaseDataAlgorithmOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataReadCriticalPoints
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataReadCriticalPoints::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataReadCriticalPoints
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataReadCriticalPoints::Read(istream& in, DataObjectClass* objc, const String& name)
{
  return BaseDataAlgorithmOperation::Read(in,objc,name);
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataReadCriticalPoints
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataReadCriticalPoints::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataReadCriticalPoints
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataReadCriticalPoints::Clone()
{
  BaseDataReadCriticalPoints *obj = new BaseDataReadCriticalPoints;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataReadCriticalPoints
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataReadCriticalPoints::CopyClone(Identify *obj)
{
  BaseDataReadCriticalPoints *objfull = (BaseDataReadCriticalPoints *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataReadCriticalPoints
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataReadCriticalPoints::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataReadCriticalPoints
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataReadCriticalPoints::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
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
bool BaseDataReadCriticalPoints::SetUpAlgorithms(BaseDataSetOfInstances*,
						 DataSetOfInstancesClass*,
						 BaseDataAlgorithmRun* ,
						DataAlgorithmRunClass*)
{
  return true;
}
/*F ans = SetUpInput(instances,instancesclass,run,runclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataReadCriticalPoints::SetUpInput(BaseDataSetOfInstances* instances,
					  DataSetOfInstancesClass* instancesclass,
					  BaseDataAlgorithmRun* run,
					  DataAlgorithmRunClass* runclass)
{
  bool result = this->CheckInput(instances,instancesclass,run,runclass);
  if(result)
    {
      rootNameK = (BaseDataKeyWords *) run->ParameterValue(InputrootNameS);
      ObjectList<String> names = rootNameK->GetKeyWords();
      rootName = names.front();

      fileNamesK = (BaseDataKeyWords *) run->ParameterValue(InputfileNamesS);
      
#ifdef DEBUG_LEVEL1
      cout << "The Root Name: " << rootName << "\n";
#endif
      
    }
  
  return result;
}
 
/*F ans = WriteOutputValues(instances,instancesclass,run,runclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataReadCriticalPoints::WriteOutputValues(BaseDataSetOfInstances*,
						 DataSetOfInstancesClass*,
						 BaseDataAlgorithmRun* run,
						 DataAlgorithmRunClass*) 
{
  PointList->NameTag = OutputPointListS;
  bool result = run->AddParameter(PointList);

  return result;
}
/*F ans = ConcludeRun(instances,instancesclass,run,runclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataReadCriticalPoints::ConcludeRun(BaseDataSetOfInstances*,
					   DataSetOfInstancesClass*,
					   BaseDataAlgorithmRun*,
					   DataAlgorithmRunClass* ) 
{
  delete PointList;
  
  return true;
}
/*F ans = CheckInput(instances,instancesclass,run,runclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataReadCriticalPoints::CheckInput(BaseDataSetOfInstances*,
					  DataSetOfInstancesClass*,
					  BaseDataAlgorithmRun* run,
					  DataAlgorithmRunClass*)
{
  bool result = true;
  
  if(run->ParameterInList(InputrootNameS))
    {
      rootNameK = (BaseDataKeyWords *) run->ParameterValue(InputrootNameS);
      ObjectList<String> names = rootNameK->GetKeyWords();
      
      if(names.size() == 0)
	{
	  result = false;
	  cerr << "Empty Conjunction Class\n";
	}
    }
  else
    {
      cerr << "Parameter for root name: " << InputrootNameS << " not found\n";
      result = false;
    }
  
  return result;
}
/*F ans = Calculate(instances,instancesclass,run,runclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataReadCriticalPoints::Calculate(BaseDataSetOfInstances* instances,
					 DataSetOfInstancesClass*,
					 BaseDataAlgorithmRun *,
					 DataAlgorithmRunClass*)
{
  bool result = true;
  
  PointList = new BaseDataKeyWords;
  DataCriticalPointsClass critclass;
  
  ObjectList<String> filenames = fileNamesK->GetKeyWords();
  while(result && filenames.size() > 0)
    {
      cout << "Filename: " << filenames << endl;
      String filename = filenames.front();
      filenames.pop_front();
      OpenInputFile file(filename);
      StreamObjectInput strinp(file.Stream,' ');
      
      String name = strinp.ReadNext();
      cout << "Name: " << name << endl;
      while(!(name == "END") && result)
	{
	  Points = new BaseDataCriticalPoints;
	  result = Points->Read(file.Stream,&critclass,name);
	  if(result)
	    {
	      PointList->AddKeyWord(name);
	      Points->NameTag = name;
	      result = instances->AddObject(Points);
	      name = strinp.ReadNext();
	    }
	  delete Points;
	}
    }
  
  return true;
}

/*S DataReadCriticalPointsClass
 */
/*F DataReadCriticalPointsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataReadCriticalPointsClass::DataReadCriticalPointsClass()
{
  Identification = PREDGEN_READ_ID;
  NameTag = PREDGEN_READ_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataReadCriticalPointsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataReadCriticalPointsClass::DataReadCriticalPointsClass(const DataReadCriticalPointsClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataReadCriticalPointsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataReadCriticalPointsClass::DataReadCriticalPointsClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = PREDGEN_READ_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataReadCriticalPointsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataReadCriticalPointsClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataReadCriticalPointsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataReadCriticalPointsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataReadCriticalPointsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  return DataAlgorithmOperationClass::Read(in,set);
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataReadCriticalPointsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataReadCriticalPointsClass::CopyClone(Identify* objc)
{
  DataReadCriticalPointsClass *objcfull = (DataReadCriticalPointsClass *) objc;
  *this = *objcfull;
}

/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataReadCriticalPointsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataReadCriticalPointsClass::Clone()
    {
      DataReadCriticalPointsClass* id = new DataReadCriticalPointsClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataReadCriticalPointsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataReadCriticalPointsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataReadCriticalPointsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataReadCriticalPointsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataReadCriticalPointsClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataReadCriticalPoints();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataReadCriticalPointsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataReadCriticalPointsClass*& obj)
     {
     obj = new DataReadCriticalPointsClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataReadCriticalPoints
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataReadCriticalPoints*& obj)
     {
     obj = new BaseDataReadCriticalPoints;
     return obj->DecodeThis(buffer);
     }

/*S BaseDataPatternsFromCriticalPoints
 */ 
/*F BaseDataPatternsFromCriticalPoints()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataPatternsFromCriticalPoints::BaseDataPatternsFromCriticalPoints()
  : InputpredicateTypesS(PARTFROMPOINTS_TYPES),
    InputcriticalPointListS(CRITICALPOINTS_POINTLIST),
    OutputlistOfPredicatesS(PARTFROMPOINTS_PREDICATES),
    OutputlistOfPartitionsS(PARTFROMPOINTS_PARTITIONS)
{
  Identification = PREDGEN_PARTITIONS_ID;
  NameTag = PREDGEN_PARTITIONS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataPatternsFromCriticalPoints(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataPatternsFromCriticalPoints::BaseDataPatternsFromCriticalPoints(const BaseDataPatternsFromCriticalPoints& data)
  : BaseDataAlgorithmOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataPatternsFromCriticalPoints
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataPatternsFromCriticalPoints::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataPatternsFromCriticalPoints
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataPatternsFromCriticalPoints::Read(istream& in, DataObjectClass* objc, const String& name)
{
  return BaseDataAlgorithmOperation::Read(in,objc,name);
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataPatternsFromCriticalPoints
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataPatternsFromCriticalPoints::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);

  out << endl << "Algorithm(";
  out << InputpredicateTypesS << ", ";
  out << InputcriticalPointListS << ") = (";
  out << OutputlistOfPredicatesS << ", ";
  out << OutputlistOfPartitionsS << ")";
  out << endl;
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataPatternsFromCriticalPoints
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataPatternsFromCriticalPoints::Clone()
{
  BaseDataPatternsFromCriticalPoints *obj = new BaseDataPatternsFromCriticalPoints;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataPatternsFromCriticalPoints
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataPatternsFromCriticalPoints::CopyClone(Identify *obj)
{
  BaseDataPatternsFromCriticalPoints *objfull = (BaseDataPatternsFromCriticalPoints *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPatternsFromCriticalPoints
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPatternsFromCriticalPoints::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPatternsFromCriticalPoints
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPatternsFromCriticalPoints::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  return result;
}
/*F name = MakePredicate(run,ybeg,ypnt,yfin,xbeg,xpnt,xfin,typename,name)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static String& MakePredicate(BaseDataSetOfObjects *set,
			     DataPredicateClass *predclass,
			     unsigned int debuglevel,
			     double ybeg, double ypnt, double yfin,
			     double xbeg ,double xpnt, double xfin,
			     String& tname,
			     String& name,
			     String& pname)
{
  char *p = new char[500];
  //ostrstream ost(p,500);
  stringstream ost;
  ost << name << tname << (xbeg+xfin)/2.0 << ends;
  String *predname = new String(ost.str().c_str());
  if(debuglevel > 1)
    {
      cout << "----------------------\n";
      cout << "Predicate: '" << *predname << "' created for center: " << xpnt;
      cout << " and type: '" << tname << "'" << endl;
    }
  BaseDataPyramidFunction *func  = new BaseDataPyramidFunction(*predname,
							       ybeg,ypnt,yfin,
							       xbeg,xpnt,xfin);
  DataContinuousClass *cont = new DataContinuousClass;
  BaseDataNumericPredicate *pred = new BaseDataNumericPredicate(func,cont);
  pred->NameTag = *predname;
  String logicS("Continuous");

  BaseDataPredicate *vpred = (BaseDataPredicate *) predclass->BaseDataObjectExample();
  vpred->setParameters(*predname,pname,logicS,pred);
  vpred->SetType(predclass->Identification);

  if(debuglevel > 2)
    {
      cout << "Predicate: ";
      vpred->print(cout);
      cout << endl;
    }
  set->AddObject(vpred);
  delete p;
  delete vpred;
  delete func;
  delete cont;
  
  return *predname;
}
/*F name = MakePredicateEqual(run,center,width,name)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static String& MakePredicateEqual(BaseDataSetOfObjects *set,
				  DataPredicateClass *predclass,
				  unsigned int debuglevel,
				  double center,
				  double width,
				  String& name,
				  String& pname)
{
  String tname(".EQ.");
  
  return MakePredicate(set,predclass,debuglevel,
		       0.0,1.0,0.0,
		       center-width,center,center+width,
		       tname,
		       name,pname);
}
/*F name = MakePredicateNotEqual(run,center,width,name)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static String& MakePredicateNotEqual(BaseDataSetOfObjects *set,
				     DataPredicateClass *predclass,
				     unsigned int debuglevel,
				     double center,
				     double width,
				     String& name, String& pname)
{
  String tname(".NE.");
  
  return MakePredicate(set,predclass,debuglevel,
		       1.0,0.0,1.0,
		       center-width,center,center+width,
		       tname,
		       name,pname);
  
}
/*F name = MakePredicateLessThan(run,center,width,name)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static String& MakePredicateLessThan(BaseDataSetOfObjects *set,
				     DataPredicateClass *predclass,
				     unsigned int debuglevel,
				     double center,
				     double width,
				     String& name, String& pname)
{
  String tname(".LT.");
  
  return MakePredicate(set,predclass,debuglevel,
		       1.0,1.0,0.0,
		       center-width,center-width,center+width,
		       tname,
		       name,pname);
  
}
/*F name = MakePredicateGreaterThan(run,center,width,name)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static String& MakePredicateGreaterThan(BaseDataSetOfObjects *set,
					DataPredicateClass *predclass,
					unsigned int debuglevel,
					double center,
					double width,
					String& name,
					String& pname)
{
  String tname(".GT.");
  
  return MakePredicate(set,predclass,debuglevel,
		       0.0,1.0,1.0,
		       center-width,center+width,center+width,
		       tname,
		       name,pname);
  
}
/*F ans = MakePartitionOfType(run,predlist,center,width,type,name)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static bool MakePartitionOfType(BaseDataSetOfObjects *set,
				DataPredicateClass *predclass,
				unsigned int debuglevel,
				BaseDataKeyWords *predlist,
				BaseDataKeyWords *partlist,
				double center,
				double width,
				String& type,
				String& name,
				String& pname)
{
  bool result = true;

  BaseDataKeyWords partition;
  //char *p = new char[500];
  //ostrstream ost(p,500);
  stringstream ost;
  ost << name << "." << center << ends;
  //String *partname = new String(p);
  String *partname = new String(ost.str().c_str());
  //delete p;
  
  if(debuglevel > 1)
    {
      cout << "Partition: " << *partname << " created for center: " << center << endl;
      cout << "           for type: '" << type << "'\n";
    }
  
  partition.NameTag = *partname;
  
  if(type == "LTGT")
    {
      String name1 = MakePredicateLessThan(set,predclass,debuglevel,center,width,name,pname);
      String name2 = MakePredicateGreaterThan(set,predclass,debuglevel,center,width,name,pname);
      predlist->AddKeyWord(name1);
      predlist->AddKeyWord(name2);
      
      partition.AddKeyWord(name1);
      partition.AddKeyWord(name2);
    }
  else if(type =="EQNE")
    {
      String name1 = MakePredicateEqual(set,predclass,debuglevel,center,width,name,pname);
      String name2 = MakePredicateNotEqual(set,predclass,debuglevel,center,width,name,pname);
      predlist->AddKeyWord(name1);
      predlist->AddKeyWord(name2);

      partition.AddKeyWord(name1);
      partition.AddKeyWord(name2);
    }
  else if(type =="LTEQGT")
    {
      double center1 = center - width/2;
      double center3 = center + width/2;
      double width2 = width/2.0;
      
      String name1 = MakePredicateLessThan(set,predclass,debuglevel,center1,width2,name,pname);
      String name2 = MakePredicateEqual(set,predclass,debuglevel,center,width,name,pname);
      String name3 = MakePredicateGreaterThan(set,predclass,debuglevel,center3,width2,name,pname);
      predlist->AddKeyWord(name1);
      predlist->AddKeyWord(name2);
      predlist->AddKeyWord(name3);

      partition.AddKeyWord(name1);
      partition.AddKeyWord(name2);
      partition.AddKeyWord(name3);
    }
  else if(type =="LTEQEQGT")
    {
      double width2 = width/2.0;
      double center1 = center - width;
      double center2 = center - width2;
      double center4 = center + width2;
      double center5 = center + width;
      String name1 = MakePredicateLessThan(set,predclass,debuglevel,center1,width2,name,pname);
      String name2 = MakePredicateEqual(set,predclass,debuglevel,center2,width2,name,pname);
      String name3 = MakePredicateEqual(set,predclass,debuglevel,center,width2,name,pname);
      String name4 = MakePredicateEqual(set,predclass,debuglevel,center4,width2,name,pname);
      String name5 = MakePredicateGreaterThan(set,predclass,debuglevel,center5,width2,name,pname);
      predlist->AddKeyWord(name1);
      predlist->AddKeyWord(name2);
      predlist->AddKeyWord(name3);
      predlist->AddKeyWord(name4);
      predlist->AddKeyWord(name5);

      partition.AddKeyWord(name1);
      partition.AddKeyWord(name2);
      partition.AddKeyWord(name3);
      partition.AddKeyWord(name4);
      partition.AddKeyWord(name5);
    }
  else
    {
      cerr << "Non-Valid Partition Type: ";
      cerr << type;
      cerr << endl;
      
      result = false;
    }
  if(result)
    {
      partlist->AddKeyWord(*partname);
      set->AddObject(&partition);
    }
  delete partname;
  
  return result;
}
			      
/*F MakePredicateFromCriticalPoints(run,points,type,name)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static bool MakePartitionFromCriticalPoints(BaseDataSetOfObjects *set,
					    DataPredicateClass *predclass,
					    unsigned int debuglevel,
					    BaseDataKeyWords *predlist,
					    BaseDataKeyWords *partlist,
					    BaseDataCriticalPoints *critpoints,
					    String& type,
					    String& name,
					    String& pname)
{
  bool result = true;
  
  SymmetricPairList<double>::iterator pnt;
  SymmetricPairList<double> *points = critpoints->PointerToPoints();
  
  for(pnt=points->begin();
      pnt != points->end() && result;
      pnt++)
    {
      double center = (*pnt).I;
      double width = (*pnt).J;
      
      result = result && MakePartitionOfType(set,predclass,debuglevel,predlist,partlist,center,width,type,name,pname);
    }
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
bool BaseDataPatternsFromCriticalPoints::SetUpAlgorithms(BaseDataSetOfInstances*,
						 DataSetOfInstancesClass*,
						 BaseDataAlgorithmRun* ,
						DataAlgorithmRunClass*)
{
  return true;
}
/*F ans = CheckInput(instances,instancesclass,run,runclass)
**
**  DESCRIPTION
**    instances:     The set of instances
**    instancesclass: The instance classes
**    run:            The algorithm run class
**    runclass:       The class of algorithm run
**    
**  REMARKS
**
*/
bool BaseDataPatternsFromCriticalPoints::CheckInput(BaseDataSetOfInstances*,
					  DataSetOfInstancesClass*,
					  BaseDataAlgorithmRun* run,
					  DataAlgorithmRunClass*)
{
  bool result = true;
  
    if(!run->ParameterInList(InputpredicateTypesS))
      {
	cerr << "Parameter with predicate types: " << InputpredicateTypesS << " not found\n";
	result = false;
      }
    if(!run->ParameterInList(InputcriticalPointListS))
      {
	cerr << "Parameter with list of critical points: " << InputcriticalPointListS << " not found\n";
	result = false;
      }
  
  return result;
}
/*F ans = SetUpInput(instances,instancesclass,run,runclass) . . . . . . setup
**
**  DESCRIPTION
**    instances:     The set of instances
**    instancesclass: The instance classes
**    run:            The algorithm run class
**    runclass:       The class of algorithm run
**
**  REMARKS
**
*/
bool BaseDataPatternsFromCriticalPoints::SetUpInput(BaseDataSetOfInstances*,
					  DataSetOfInstancesClass*,
					  BaseDataAlgorithmRun* run,
					  DataAlgorithmRunClass*)
{
  bool result = true;
  
  predicateTypes = (BaseDataKeyWords *) run->ParameterValue(InputpredicateTypesS);
  criticalPointList = (BaseDataKeyWords *) run->ParameterValue(InputcriticalPointListS);
  
#ifdef DEBUG_LEVEL1
  cout << endl << "Input SetUp" << endl;
  cout << "The predicate types to create: ";
  predicateTypes->print(cout);
  cout << endl;
  cout << "The set of critical points: ";
  criticalPointList->print(cout);
  cout <<  endl;
#endif
  
  return result;
}
 
/*F ans = Calculate(instances,instancesclass,run,runclass)
**
**  DESCRIPTION
**    instances:     The set of instances
**    instancesclass: The instance classes
**    run:            The algorithm run class
**    runclass:       The class of algorithm run
**
**  REMARKS
**
*/
bool BaseDataPatternsFromCriticalPoints::Calculate(BaseDataSetOfInstances* instances,
						   DataSetOfInstancesClass* instsclass,
						   BaseDataAlgorithmRun *,
						   DataAlgorithmRunClass* )
{
  
  bool result = true;
  ObjectList<String> types = predicateTypes->GetKeyWords();
  String dot(".");;
  
  listOfPredicates = new BaseDataKeyWords;
  listOfPartitions = new BaseDataKeyWords;
  unsigned int debuglevel = instsclass->getDebugLevel();
  
  DataSetOfObjectsClass *classes = instsclass->PointerToAllowedClasses();
  unsigned int newid = classes->getIDCount();
  DataNumericPredicateClass *npredcls = new DataNumericPredicateClass(newid,PREDGEN_CRITICAL_NUMERICPREDICATE,
								     "Numeric Predicate for the Generated Predicates");
  npredcls->SubClass = LOGICALOP_NUMPRED_NAME;
  newid++;
  classes->setIDCount(newid);

  DataContinuousClass *contlogic = (DataContinuousClass *) classes->GetObjectClass(LOGICAL_CONTINUOUS_ID);
  DataPyramidFunctionClass *func = (DataPyramidFunctionClass *) classes->GetObjectClass(ODREALFUNC_PYRAMID_NAME);
  npredcls->setPredicateFunction(func);
  npredcls->setLogicClass(contlogic);

  classes->AddObjectClass(*npredcls);



  newid = classes->getIDCount();
  DataPredicateClass *predclass = new DataPredicateClass(newid,PREDGEN_CRITICAL_FUZZYPREDICATE,
							 "Fuzzy Predicate for Generated Predicates");
  newid++;
  classes->setIDCount(newid);
  predclass->setOpClass(npredcls);
  predclass->SubClass = PREDICATE_BASE_NAME;

  classes->AddObjectClass(*predclass);
  
  while(types.size() > 0 && result)
    {
      String type = types.front();
      types.pop_front();
      
      ObjectList<String> points = criticalPointList->GetKeyWords();
      while(points.size() > 0 && result)
	{
	  String set = points.front();
	  points.pop_front();
	  if(instances->IsInList(set))
	    {
	      BaseDataCriticalPoints *critpoints 
		= (BaseDataCriticalPoints *) instances->GetObject(set);
	      String partitionname = String(set);
	      partitionname.AppendToEnd(dot);
	      partitionname.AppendToEnd(type);
	      if(debuglevel > 1)
		{
		  cout << "==========================================\n";
		  cout << partitionname << endl;
		  critpoints->print(cout);
		  cout << endl;
		  cout << "==========================================\n";
		}
	      String pname = critpoints->getParameterName();
	      
	      result = result && MakePartitionFromCriticalPoints(instances,predclass,
								 debuglevel,listOfPredicates,listOfPartitions,
								 critpoints,type,partitionname,pname);
	    }
	  else
	    {
	      cerr << "Set of Critical Points: " << set << " not found";
	    }
	  
	}
    }
  
  return result;
}
/*F ans = WriteOutputValues(instances,instancesclass,run,runclass)  . output 
**
**  DESCRIPTION
**    instances:     The set of instances
**    instancesclass: The instance classes
**    run:            The algorithm run class
**    runclass:       The class of algorithm run
**    
**  REMARKS
**
*/
bool BaseDataPatternsFromCriticalPoints::WriteOutputValues(BaseDataSetOfInstances *instances,
						 DataSetOfInstancesClass*,
						 BaseDataAlgorithmRun* run,
						 DataAlgorithmRunClass*) 
{
  bool result = true;
  cout << "Write out '"<< OutputlistOfPredicatesS << "'" << endl;
  if(listOfPredicates != NULL) {
      listOfPredicates->NameTag = OutputlistOfPredicatesS;
      result = result && run->AddParameter(listOfPredicates);

      /*
      if(instances->IsInList(OutputlistOfPredicatesS))
	{
	  BaseDataKeyWords *old = (BaseDataKeyWords *) instances->GetObject(OutputlistOfPredicatesS);
	  ObjectList<String> oldkeys = old->GetKeyWords();
	  ObjectList<String> newkeys = listOfPredicates->GetKeyWords();
	  ObjectList<String> combined(oldkeys);
	  combined.AddOnlyUniqueObjects(newkeys);
	  BaseDataKeyWords *newcombined = new BaseDataKeyWords(combined);
	  newcombined->NameTag = OutputlistOfPredicatesS;
	  result = result && run->AddParameter(newcombined);
	  delete newcombined;
	}
      else
	{
	}
      */
    }
  cout << "Write out '"<< OutputlistOfPartitionsS << "'" << endl;
  if(listOfPartitions != NULL) {
    listOfPartitions->NameTag = OutputlistOfPartitionsS;
    result = result && run->AddParameter(listOfPartitions);

    /*
      if(instances->IsInList(OutputlistOfPartitionsS))
	{
	  BaseDataKeyWords *old = (BaseDataKeyWords *) instances->GetObject(OutputlistOfPartitionsS);
	  ObjectList<String> oldkeys = old->GetKeyWords();
	  ObjectList<String> newkeys = listOfPartitions->GetKeyWords();
	  ObjectList<String> combined(oldkeys);
	  combined.AddOnlyUniqueObjects(newkeys);
	  BaseDataKeyWords *newcombined = new BaseDataKeyWords(combined);
	  newcombined->NameTag = OutputlistOfPartitionsS;
	  result = result && run->AddParameter(newcombined);
	  delete newcombined;
	}
      else
	{
	  listOfPartitions->NameTag = OutputlistOfPartitionsS;
	  result = result && run->AddParameter(listOfPartitions);
	}
    */
    }
  
  return result;
}
/*F ans = ConcludeRun(instances,instancesclass,run,runclass)
**
**  DESCRIPTION
**    instances:     The set of instances
**    instancesclass: The instance classes
**    run:            The algorithm run class
**    runclass:       The class of algorithm run
**    
**  REMARKS
**
*/
bool BaseDataPatternsFromCriticalPoints::ConcludeRun(BaseDataSetOfInstances*,
					   DataSetOfInstancesClass*,
					   BaseDataAlgorithmRun*,
					   DataAlgorithmRunClass* ) 
{
  delete listOfPredicates;
  delete listOfPartitions;
  
  return true;
}
 
 

/*S DataPatternsFromCriticalPointsClass
 */
/*F DataPatternsFromCriticalPointsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataPatternsFromCriticalPointsClass::DataPatternsFromCriticalPointsClass()
{
  Identification = PREDGEN_PARTITIONS_ID;
  NameTag = PREDGEN_PARTITIONS_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataPatternsFromCriticalPointsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataPatternsFromCriticalPointsClass::DataPatternsFromCriticalPointsClass(const DataPatternsFromCriticalPointsClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataPatternsFromCriticalPointsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataPatternsFromCriticalPointsClass::DataPatternsFromCriticalPointsClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = PREDGEN_PARTITIONS_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataPatternsFromCriticalPointsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataPatternsFromCriticalPointsClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataPatternsFromCriticalPointsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataPatternsFromCriticalPointsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataPatternsFromCriticalPointsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  return DataAlgorithmOperationClass::Read(in,set);
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataPatternsFromCriticalPointsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataPatternsFromCriticalPointsClass::CopyClone(Identify* objc)
{
  DataPatternsFromCriticalPointsClass *objcfull = (DataPatternsFromCriticalPointsClass *) objc;
  *this = *objcfull;
}

/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataPatternsFromCriticalPointsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataPatternsFromCriticalPointsClass::Clone()
    {
      DataPatternsFromCriticalPointsClass* id = new DataPatternsFromCriticalPointsClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataPatternsFromCriticalPointsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPatternsFromCriticalPointsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataPatternsFromCriticalPointsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPatternsFromCriticalPointsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataPatternsFromCriticalPointsClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataPatternsFromCriticalPoints();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataPatternsFromCriticalPointsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataPatternsFromCriticalPointsClass*& obj)
     {
     obj = new DataPatternsFromCriticalPointsClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataPatternsFromCriticalPoints
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataPatternsFromCriticalPoints*& obj)
     {
     obj = new BaseDataPatternsFromCriticalPoints;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataPredicatesFromDistribution
 */ 
/*F BaseDataPredicatesFromDistribution()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataPredicatesFromDistribution::BaseDataPredicatesFromDistribution()
  : DistributionNamesS("VariablesInInstance"),
    RootNameS("RootName"),
    PredicateS(PREDICATE_OBJECT)
{
  Identification = PREDGEN_FROMDISTRIBUTION_ID;
  NameTag = PREDGEN_FROMDISTRIBUTION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataPredicatesFromDistribution(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataPredicatesFromDistribution::BaseDataPredicatesFromDistribution(const BaseDataPredicatesFromDistribution& data)
  : BaseDataAlgorithmOperation(data),
    DistributionNamesS(data.DistributionNamesS),
    RootNameS(data.RootNameS),
    PredicateS(data.PredicateS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataPredicatesFromDistribution
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataPredicatesFromDistribution::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataPredicatesFromDistribution
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataPredicatesFromDistribution::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataPredicatesFromDistribution
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataPredicatesFromDistribution::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  out << "Predicate From Distribution" << endl;
  out << "Input: RootName:         '" << RootNameS << "'" << endl;
  out << "       Distribution:     '" << DistributionNamesS << "'" << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataPredicatesFromDistribution
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataPredicatesFromDistribution::Clone()
{
  BaseDataPredicatesFromDistribution *obj = new BaseDataPredicatesFromDistribution(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataPredicatesFromDistribution
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataPredicatesFromDistribution::CopyClone(Identify * obj)
{
  BaseDataPredicatesFromDistribution *objfull = (BaseDataPredicatesFromDistribution *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPredicatesFromDistribution
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPredicatesFromDistribution::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && DistributionNamesS.EncodeThis(buffer);
  result = result && RootNameS.EncodeThis(buffer);
  result = result && PredicateS.EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPredicatesFromDistribution
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPredicatesFromDistribution::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && DistributionNamesS.DecodeThis(buffer);
  result = result && RootNameS.DecodeThis(buffer);
  result = result && PredicateS.DecodeThis(buffer);
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
bool BaseDataPredicatesFromDistribution::SetUpAlgorithms(BaseDataSetOfInstances *instances,
				       DataSetOfInstancesClass *instancesclass,
				       BaseDataAlgorithmRun *run,
				       DataAlgorithmRunClass *runclass)
{
  return true;
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
bool BaseDataPredicatesFromDistribution::CheckInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;
  result = result && CheckInputVariable(DistributionNamesS,"List of Distributions",run);
  result = result && CheckInputVariable(RootNameS,"Root Name for output predicates",run);
  result = result && CheckInputVariable(PredicateS,"Predicate Object Base for generated predicates",run);
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
bool BaseDataPredicatesFromDistribution::SetUpInput(BaseDataSetOfInstances *instances,
						    DataSetOfInstancesClass *instancesclass,
						    BaseDataAlgorithmRun *run,
						    DataAlgorithmRunClass *runclass)
{
  bool result = true;

  DistributionNames = (BaseDataKeyWords *) run->ParameterValue(DistributionNamesS);
  RootNameString = (BaseDataString *) run->ParameterValue(RootNameS);
  RootName = RootNameString->getString();
  Predicate = (BaseDataOperation *) run->ParameterValue(PredicateS);
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
bool BaseDataPredicatesFromDistribution::Calculate(BaseDataSetOfInstances *instances,
						   DataSetOfInstancesClass *instancesclass,
						   BaseDataAlgorithmRun *run,
						   DataAlgorithmRunClass *runclass)
{
  bool result = true;
  //if(run->AlgorithmSummary.KeyWordInList("")){}
  
  BaseDataInteger val;
  BaseDataKeyWords predicates;
  predicates.NameTag = "AttributeNames";
  ObjectList<String> distributions = DistributionNames->GetKeyWords();
  for(ObjectList<String>::iterator name = distributions.begin(); 
      name != distributions.end();
      name++) {
    String distname(RootName);
    distname.AppendToEnd(*name);
    if(instances->IsInList(distname)) {
      BaseDataAttributeDistribution *dist = (BaseDataAttributeDistribution *) instances->GetObject(distname);
      PrimitiveStats *Distribution = dist->getStatistics();
      VectorNumeric Values = Distribution->SortedValues;
      int lastvalue = -1;
      for(VectorNumeric::iterator n = Values.begin(); n != Values.end();n++) {
	int in = (int) *n;
	if(*n > 0 && in != lastvalue) {
	  BaseDataExactlyEqualPredicate *pred = (BaseDataExactlyEqualPredicate *) Predicate->Clone();
	  val.SetValue((int) floor(*n));
	  pred->setCompareObject(&val);
	  pred->setParameterName(*name);
	  pred->NameTag = "Predicate_";
	  pred->NameTag.AppendToEnd(*name);
	  pred->NameTag.AppendToEnd("_");
	  String num = Int2String(in);
	  pred->NameTag.AppendToEnd(num);
	  instances->AddObject(pred);
	  predicates.AddKeyWord(pred->NameTag);
	  lastvalue = in;
	}
      }
    } else {
      cerr << "Distribution: '" << distname << "' for variable '" << *name << "' not found" << endl;
    }
  }
  instances->AddObject(&predicates);
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
bool BaseDataPredicatesFromDistribution::WriteOutputValues(BaseDataSetOfInstances *instances,
							   DataSetOfInstancesClass *instancesclass,
							   BaseDataAlgorithmRun *run,
							   DataAlgorithmRunClass *runclass)
{
  bool result = true;
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
bool BaseDataPredicatesFromDistribution::ConcludeRun(BaseDataSetOfInstances *instances,
				   DataSetOfInstancesClass *instancesclass,
				   BaseDataAlgorithmRun *run,
				   DataAlgorithmRunClass *runclass)
{
  bool result = true;
//  delete something
  return result;
}
 

 
/*S DataPredicatesFromDistributionClass
 */
/*F DataPredicatesFromDistributionClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataPredicatesFromDistributionClass::DataPredicatesFromDistributionClass()
{
  Identification = PREDGEN_FROMDISTRIBUTION_ID;
  NameTag = PREDGEN_FROMDISTRIBUTION_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataPredicatesFromDistributionClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataPredicatesFromDistributionClass::DataPredicatesFromDistributionClass(const DataPredicatesFromDistributionClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataPredicatesFromDistributionClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataPredicatesFromDistributionClass::DataPredicatesFromDistributionClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = "PredicatesFromDistribution";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataPredicatesFromDistributionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataPredicatesFromDistributionClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataPredicatesFromDistributionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataPredicatesFromDistributionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataPredicatesFromDistributionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataPredicatesFromDistributionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataPredicatesFromDistributionClass::CopyClone(Identify *  objc)
{
  DataPredicatesFromDistributionClass *objcfull = (DataPredicatesFromDistributionClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataPredicatesFromDistributionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataPredicatesFromDistributionClass::Clone()
    {
      DataPredicatesFromDistributionClass* id = new DataPredicatesFromDistributionClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataPredicatesFromDistributionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPredicatesFromDistributionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataPredicatesFromDistributionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPredicatesFromDistributionClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
  //result = result && PointerDecode(buffer,(BaseDataObject *&) Class);
  //result = result && Decode(buffer,-----);

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
BaseDataObject * DataPredicatesFromDistributionClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataPredicatesFromDistribution();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataPredicatesFromDistributionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataPredicatesFromDistributionClass*& obj)
     {
     obj = new DataPredicatesFromDistributionClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataPredicatesFromDistribution
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataPredicatesFromDistribution*& obj)
     {
     obj = new BaseDataPredicatesFromDistribution;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataPredicatesFromKeyWords
 */ 
/*F BaseDataPredicatesFromKeyWords()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataPredicatesFromKeyWords::BaseDataPredicatesFromKeyWords()
  : KeyWordListS(KEYWORD_LIST),
    ParameterListS("ParameterList"),
    RootNameS("RootName"),
    PredicateS(PREDICATE_OBJECT)
{
  Identification = PREDGEN_FROMKEYWORDS_ID;
  NameTag = PREDGEN_FROMKEYWORDS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataPredicatesFromKeyWords(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataPredicatesFromKeyWords::BaseDataPredicatesFromKeyWords(const BaseDataPredicatesFromKeyWords& data)
  : BaseDataAlgorithmOperation(data),
    KeyWordListS(data.KeyWordListS),
    ParameterListS(data.ParameterListS),
    RootNameS(data.RootNameS),
    PredicateS(data.PredicateS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataPredicatesFromKeyWords
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataPredicatesFromKeyWords::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataPredicatesFromKeyWords
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataPredicatesFromKeyWords::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataPredicatesFromKeyWords
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataPredicatesFromKeyWords::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataPredicatesFromKeyWords
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataPredicatesFromKeyWords::Clone()
{
  BaseDataPredicatesFromKeyWords *obj = new BaseDataPredicatesFromKeyWords(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataPredicatesFromKeyWords
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataPredicatesFromKeyWords::CopyClone(Identify * obj)
{
  BaseDataPredicatesFromKeyWords *objfull = (BaseDataPredicatesFromKeyWords *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPredicatesFromKeyWords
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPredicatesFromKeyWords::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && Encode(buffer, KeyWordListS);
  result = result && Encode(buffer,ParameterListS);
  result = result && Encode(buffer,RootNameS);
  result = result && Encode(buffer,PredicateS);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPredicatesFromKeyWords
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPredicatesFromKeyWords::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && Decode(buffer,KeyWordListS);
  result = result && Decode(buffer,ParameterListS);
  result = result && Decode(buffer,RootNameS);
  result = result && Decode(buffer,PredicateS);
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
bool BaseDataPredicatesFromKeyWords::SetUpAlgorithms(BaseDataSetOfInstances *instances,
						     DataSetOfInstancesClass *instancesclass,
						     BaseDataAlgorithmRun *run,
						     DataAlgorithmRunClass *runclass)
{
  return true;
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
bool BaseDataPredicatesFromKeyWords::CheckInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;
  result = result && CheckInputVariable(KeyWordListS,"The list of keywords from which to form predicates",run);
  result = result && CheckInputVariable(RootNameS,"Root name of predicates",run);
  result = result && CheckInputVariable(PredicateS,"The basis predicate",run);
  result = result && CheckInputVariable(ParameterListS,"The list of keyword parameter variables",run);
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
bool BaseDataPredicatesFromKeyWords::SetUpInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;

  KeyWordList = (BaseDataKeyWords *) run->ParameterValue(KeyWordListS)->Clone();
  ParameterList = (BaseDataKeyWords *) run->ParameterValue(ParameterListS);
  RootNameString = (BaseDataString *) run->ParameterValue(RootNameS);
  RootName = RootNameString->getString();
  Predicate = (BaseDataOperation *) run->ParameterValue(PredicateS);
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
bool BaseDataPredicatesFromKeyWords::Calculate(BaseDataSetOfInstances *instances,
					       DataSetOfInstancesClass *instancesclass,
					       BaseDataAlgorithmRun *run,
					       DataAlgorithmRunClass *runclass)
{
  bool result = true;
  //if(run->AlgorithmSummary.KeyWordInList("")){}
  BaseDataKeyWords predicates;
  predicates.NameTag = "AttributeNames";
  while(KeyWordList->SizeOf() > 0) {
    String name = KeyWordList->NextKey();
    ObjectList<String> parnames = ParameterList->GetKeyWords();
    ObjectList<String>::iterator parname;
    for(parname = parnames.begin();parname != parnames.end();parname++) {
      BaseDataMemberOfKeyWord *pred = (BaseDataMemberOfKeyWord *) Predicate->Clone();
      pred->setKeyWord(name);
      pred->setParameterName(*parname);
      pred->NameTag = RootName;
      pred->NameTag.AppendToEnd("_");
      pred->NameTag.AppendToEnd(name);
      pred->NameTag.AppendToEnd("_");
      pred->NameTag.AppendToEnd(*parname);
      instances->AddObject(pred);
      predicates.AddKeyWord(pred->NameTag);
    }
  }
  predicates.print(cout);

  instances->AddObject(&predicates);
  return result;


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
bool BaseDataPredicatesFromKeyWords::WriteOutputValues(BaseDataSetOfInstances *instances,
					 DataSetOfInstancesClass *instancesclass,
					 BaseDataAlgorithmRun *run,
					 DataAlgorithmRunClass *runclass)
{
  bool result = true;
  
//  run->AddParameter(ctree);

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
bool BaseDataPredicatesFromKeyWords::ConcludeRun(BaseDataSetOfInstances *instances,
				   DataSetOfInstancesClass *instancesclass,
				   BaseDataAlgorithmRun *run,
				   DataAlgorithmRunClass *runclass)
{
  bool result = true;
//  delete something
  return result;
}
 

 
/*S DataPredicatesFromKeyWordsClass
 */
/*F DataPredicatesFromKeyWordsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataPredicatesFromKeyWordsClass::DataPredicatesFromKeyWordsClass()
{
  Identification = PREDGEN_FROMKEYWORDS_ID;
  NameTag = PREDGEN_FROMKEYWORDS_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataPredicatesFromKeyWordsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataPredicatesFromKeyWordsClass::DataPredicatesFromKeyWordsClass(const DataPredicatesFromKeyWordsClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataPredicatesFromKeyWordsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataPredicatesFromKeyWordsClass::DataPredicatesFromKeyWordsClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = "PredicatesFromKeyWords";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataPredicatesFromKeyWordsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataPredicatesFromKeyWordsClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataPredicatesFromKeyWordsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataPredicatesFromKeyWordsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataPredicatesFromKeyWordsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataPredicatesFromKeyWordsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataPredicatesFromKeyWordsClass::CopyClone(Identify *  objc)
{
  DataPredicatesFromKeyWordsClass *objcfull = (DataPredicatesFromKeyWordsClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataPredicatesFromKeyWordsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataPredicatesFromKeyWordsClass::Clone()
    {
      DataPredicatesFromKeyWordsClass* id = new DataPredicatesFromKeyWordsClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataPredicatesFromKeyWordsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPredicatesFromKeyWordsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataPredicatesFromKeyWordsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPredicatesFromKeyWordsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
  //result = result && PointerDecode(buffer,(BaseDataObject *&) Class);
  //result = result && Decode(buffer,-----);

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
BaseDataObject * DataPredicatesFromKeyWordsClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataPredicatesFromKeyWords();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataPredicatesFromKeyWordsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataPredicatesFromKeyWordsClass*& obj)
     {
     obj = new DataPredicatesFromKeyWordsClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataPredicatesFromKeyWords
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataPredicatesFromKeyWords*& obj)
     {
     obj = new BaseDataPredicatesFromKeyWords;
     return obj->DecodeThis(buffer);
     }

/*S Utilities
 */
/*F InitialPredicateGenEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialPredicateGenEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataCriticalPointsClass,BaseDataCriticalPoints,PREDGEN_CRITICAL_NAME);
  EncodeDecodeRegisterClass(DataReadCriticalPointsClass,BaseDataReadCriticalPoints,PREDGEN_READ_NAME);
  EncodeDecodeRegisterClass(DataPatternsFromCriticalPointsClass,BaseDataPatternsFromCriticalPoints,PREDGEN_PARTITIONS_NAME);
  EncodeDecodeRegisterClass(DataPredicatesFromDistributionClass,BaseDataPredicatesFromDistribution,PREDGEN_FROMDISTRIBUTION_NAME);
  EncodeDecodeRegisterClass(DataPredicatesFromKeyWordsClass,BaseDataPredicatesFromKeyWords,PREDGEN_FROMKEYWORDS_NAME);
}
/*F AddPredicateGenAlgorithmClasses(set) . . . . . . . .  basic algorithm data types
**
**  DESCRIPTION
**    set: The set of data types
**
**  REMARKS
**
*/
void AddPredicateGenAlgorithmClasses(DataSetOfObjectsClass& set)
{
  String critpnts("Set of Critical Points");
  String critread("Read Set of Critical Points");
  String critpart("From Critical Points create Partitions and predicates");
  String predgendescr("The Predicates from Distribution Class");
  String predkeydescr("The Predicates from keywords Class");
  
  DataCriticalPointsClass critpntclass(PREDGEN_CRITICAL_ID,
				       PREDGEN_CRITICAL_NAME,
				       critpnts);
  DataReadCriticalPointsClass critsetclass(PREDGEN_READ_ID,
					   PREDGEN_READ_NAME,
					   critread);
  DataPatternsFromCriticalPointsClass partsetclass(PREDGEN_PARTITIONS_ID,
						  PREDGEN_PARTITIONS_NAME,
						  critpart);
  DataPredicatesFromDistributionClass predgenclass(PREDGEN_FROMDISTRIBUTION_ID,PREDGEN_FROMDISTRIBUTION_NAME,predgendescr);
  DataPredicatesFromKeyWordsClass predkeyclass(PREDGEN_FROMKEYWORDS_ID,PREDGEN_FROMKEYWORDS_NAME,predkeydescr);
  
  set.AddObjectClass(critpntclass);
  set.AddObjectClass(critsetclass);
  set.AddObjectClass(partsetclass);
  set.AddObjectClass(predgenclass);
  set.AddObjectClass(predkeyclass);
}

