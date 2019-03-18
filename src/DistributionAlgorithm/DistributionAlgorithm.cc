/*  FILE     DistributionAlgorithm.cc
**  PACKAGE  DistributionAlgorithm
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "DistributionAlgorithm" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjects.hh"
#include "Vector.hh"
#include "PrimitiveStats.hh"
#include "MatrixNumeric.hh"
#include "BasicLaTeXTable.hh"
#include "MatrixOut.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "EvaluationTree.hh"
#include "ExpressionTree.hh"
#include "DistributionAlgorithm.hh"

/*S BaseDataAttributeDistribution
 */ 
/*F BaseDataAttributeDistribution() . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataAttributeDistribution::BaseDataAttributeDistribution()
{
  Identification = DISTRIBUTION_ATTR_ID;
  NameTag = DISTRIBUTION_ATTR_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  Distribution = NULL;
} 
/*F BaseDataAttributeDistribution(data) . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataAttributeDistribution::BaseDataAttributeDistribution(const BaseDataAttributeDistribution& data)
  : BaseDataObject(data),
    Distribution(NULL)
{
  if(!(data.Distribution == NULL) )
    {
      Distribution = (PrimitiveStats *) data.Distribution->Clone();
    }
}
/*F BaseDataAttributeDistribution(data) . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataAttributeDistribution::BaseDataAttributeDistribution(VectorNumeric& vec)
{
  Identification = DISTRIBUTION_ATTR_ID;
  NameTag = DISTRIBUTION_ATTR_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  Distribution = new EvenDistributionStats(vec);
  
}
/*F ~BaseDataAttributeDistribution()  . . . . . . .  delete also Distribution
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataAttributeDistribution::~BaseDataAttributeDistribution()
{
  if(Distribution != NULL)
    delete Distribution;
}
/*F Read(in,objc) . . . . . . . . . . . Read in BaseDataAttributeDistribution
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataAttributeDistribution::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . Read in BaseDataAttributeDistribution
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataAttributeDistribution::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);
  StreamObjectInput str(in,' ');
  String tag = str.ReadNext();
  if(tag == "PrimitiveStats:")
    {
      VectorNumeric vec;
      vec.Read(in);
      Distribution = new EvenDistributionStats(vec);
      /*
      String num = str.ReadNext();
      Distribution->Min = num.ToFloat();
      num = str.ReadNext();
      Distribution->Max = num.ToFloat();
      num = str.ReadNext();
      Distribution->Mean = num.ToFloat();
      num = str.ReadNext();
      Distribution->Average = num.ToFloat();
      num = str.ReadNext();
      Distribution->StdDev = num.ToFloat();

      Distribution->Values.Read(in);
      Distribution->SortedValues.Read(in);
      */
    }
  else
    {
      cerr << "Expected the keywork 'PrimitiveStats:' got '" << tag << "'" << endl;
      result = false;
    }

  return result;
}
/*F out1 = print(out) . . . . . . . . . . . . . BaseDataAttributeDistribution
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataAttributeDistribution::print(ostream& out) const
{
  BaseDataObject::print(out);
  if(Distribution == NULL)
    out << "No Distribution Data\n";
  else
    {
      Distribution->print(out);
    }
  
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . BaseDataAttributeDistribution
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataAttributeDistribution::Clone()
{
  BaseDataAttributeDistribution *obj = new BaseDataAttributeDistribution;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . BaseDataAttributeDistribution
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataAttributeDistribution::CopyClone(Identify * obj)
{
  BaseDataAttributeDistribution *objfull = (BaseDataAttributeDistribution *) obj;
  BaseDataObject::CopyClone(obj);
  
  if(objfull->Distribution != NULL)
    {
      Distribution = (PrimitiveStats *) objfull->Distribution->Clone();
    }
  
  else
    Distribution = NULL;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . BaseDataAttributeDistribution
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataAttributeDistribution::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  if(Distribution != 0)
    {
      String name("Distribution");
      result = result && Encode(buffer,name);
      result = result && Distribution->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . BaseDataAttributeDistribution
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool  BaseDataAttributeDistribution::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  String name;
  result = result && Decode(buffer,name);
  if(name == "Distribution")
    {
      Distribution = new EvenDistributionStats;
      Distribution->DecodeThis(buffer);
    }
  
  return result;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . . . . BaseDataAttributeDistribution
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
bool BaseDataAttributeDistribution::WriteAsLine(ostream& out, DataObjectClass *)
{
  out << NameTag << ":";
  Distribution->WriteAsLine(out);
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . . . BaseDataAttributeDistribution
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
bool BaseDataAttributeDistribution::WriteAsASCII(ostream& out, DataObjectClass*)
{
    return Distribution->WriteAsASCII(out);
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
bool BaseDataAttributeDistribution::WriteAsLatex(ostream& out, DataObjectClass*)
{
    return Distribution->WriteAsLatex(out);
}
/*F stats = getStatistics() . . . . . . . . . . BaseDataAttributeDistribution
**
**  DESCRIPTION
**    stats: The statistical information
**
**
**  REMARKS
**
*/
PrimitiveStats *BaseDataAttributeDistribution::getStatistics()
{
    return Distribution;
}

/*S DataAttributeDistributionClass  . . . . . . . . . . . . . . . . . . . .  
 */
/*F DataAttributeDistributionClass()  . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataAttributeDistributionClass::DataAttributeDistributionClass()
{
  Identification = DISTRIBUTION_ATTR_ID;
  NameTag = DISTRIBUTION_ATTR_NAME;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataAttributeDistributionClass(data)  . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataAttributeDistributionClass::DataAttributeDistributionClass(const DataAttributeDistributionClass& data)
  : DataObjectClass(data)
{
} 
 
/*F DataAttributeDistributionClass(id,name,descr) . . . . . . . . constructor
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
DataAttributeDistributionClass::DataAttributeDistributionClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataObjectClass(id,name,descr)
{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = DISTRIBUTION_ATTR_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . .  DataAttributeDistributionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataAttributeDistributionClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . .  DataAttributeDistributionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataAttributeDistributionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataAttributeDistributionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataObjectClass::Read(in,set);
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . .  DataAttributeDistributionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataAttributeDistributionClass::CopyClone(Identify *  objc)
{
  DataAttributeDistributionClass *objcfull = (DataAttributeDistributionClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . .  DataAttributeDistributionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataAttributeDistributionClass::Clone()
    {
      DataAttributeDistributionClass* id = new DataAttributeDistributionClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . .  DataAttributeDistributionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataAttributeDistributionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . .  DataAttributeDistributionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataAttributeDistributionClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataAttributeDistributionClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataAttributeDistribution();
}
/*F ans = TopDecode(buffer,obj) . . . . . . .  DataAttributeDistributionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataAttributeDistributionClass*& obj)
     {
     obj = new DataAttributeDistributionClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . BaseDataAttributeDistribution
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataAttributeDistribution*& obj)
     {
     obj = new BaseDataAttributeDistribution;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataDistributionAlgorithm . . . . . . . . . . . . . . . . . . . . .  
 */ 
/*F BaseDataDistributionAlgorithm() . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDistributionAlgorithm::BaseDataDistributionAlgorithm()
  : imatrixS("MatrixObject"),
    rootnameS("RootName"),
    distributionNamesS("Distributions")
{
  Identification = DISTRIBUTION_ALG_ID;
  NameTag = DISTRIBUTION_ALG_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataDistributionAlgorithm(data) . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDistributionAlgorithm::BaseDataDistributionAlgorithm(const BaseDataDistributionAlgorithm& data)
  : BaseDataAlgorithmOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . Read in BaseDataDistributionAlgorithm
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataDistributionAlgorithm::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . Read in BaseDataDistributionAlgorithm
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataDistributionAlgorithm::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . BaseDataDistributionAlgorithm
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataDistributionAlgorithm::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . BaseDataDistributionAlgorithm
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataDistributionAlgorithm::Clone()
{
  BaseDataDistributionAlgorithm *obj = new BaseDataDistributionAlgorithm;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . BaseDataDistributionAlgorithm
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataDistributionAlgorithm::CopyClone(Identify * obj)
{
  BaseDataDistributionAlgorithm *objfull = (BaseDataDistributionAlgorithm *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . BaseDataDistributionAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDistributionAlgorithm::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . BaseDataDistributionAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDistributionAlgorithm::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
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
bool BaseDataDistributionAlgorithm::SetUpAlgorithms(BaseDataSetOfInstances*,
						      DataSetOfInstancesClass*,
						      BaseDataAlgorithmRun* ,
						      DataAlgorithmRunClass*)
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
bool BaseDataDistributionAlgorithm::CheckInput(BaseDataSetOfInstances*,
					       DataSetOfInstancesClass*,
						 BaseDataAlgorithmRun* run,
						 DataAlgorithmRunClass*)
{
  bool result = true;

  if(run->ParameterInList(imatrixS))
    {
      if(!run->ParameterInList(rootnameS))
	{
	  cerr << "The parameter '" << imatrixS << "' was not in the list of parameters";
	  result = false;
	}
    }
  else
    {
      cerr << "The parameter '" << rootnameS << "' was not in the list of parameters";
      result = false;
    }

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
bool BaseDataDistributionAlgorithm::SetUpInput(BaseDataSetOfInstances*,
					       DataSetOfInstancesClass*,
					       BaseDataAlgorithmRun* run,
					       DataAlgorithmRunClass*)
{
  bool result = true;

  imatrix = (BaseDataInstanceDoubleMatrix *) run->ParameterValue(imatrixS);
  BaseDataString *root = (BaseDataString *) run->ParameterValue(rootnameS);
  rootname = root->getString();
  
  distributionNames = new BaseDataKeyWords;
  distributionNames->NameTag = distributionNamesS;
  
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
bool BaseDataDistributionAlgorithm::Calculate(BaseDataSetOfInstances* instances,
					      DataSetOfInstancesClass*,
					      BaseDataAlgorithmRun*,
					      DataAlgorithmRunClass*)
{
  cout << "DistributionAlgorithm:\n";
  
  bool result = true;
  MatrixNumeric mat = imatrix->CurrentMatrix();
  ObjectList<String> names = imatrix->getParameterNames().GetKeyWords();
  ObjectList<String>::iterator name = names.begin();
  
  for(unsigned int i=0;i < names.size();i++)
    {
      cout << endl << i << endl;
      String dname(rootname);
      dname.AppendToEnd(*name);
      cout << endl << dname << endl;
      VectorNumeric vec = mat.getMatrixColumn(i);

      BaseDataAttributeDistribution *dist = new BaseDataAttributeDistribution(vec);
      PrimitiveStats *stats = dist->getStatistics();
      stats->NameTag = *name;
      dist->NameTag = dname;
      dist->print(cout);
      cout << endl;
      
      instances->AddObject(dist);
      distributionNames->AddKeyWord(dname);
      
      name++;
    }

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
bool BaseDataDistributionAlgorithm::WriteOutputValues(BaseDataSetOfInstances*,
							DataSetOfInstancesClass*,
							BaseDataAlgorithmRun* run,
							DataAlgorithmRunClass*)
{
  bool result = true;
  
  run->AddParameter(distributionNames);

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
bool BaseDataDistributionAlgorithm::ConcludeRun(BaseDataSetOfInstances*,
						  DataSetOfInstancesClass*,
						  BaseDataAlgorithmRun*,
						  DataAlgorithmRunClass*)
{
  bool result = true;
  //delete distributionNames;
  //delete imatrix;
  
  return result;
}
 

/*S DataDistributionAlgorithmClass
 */
/*F DataDistributionAlgorithmClass()  . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDistributionAlgorithmClass::DataDistributionAlgorithmClass()
{
  Identification = DISTRIBUTION_ALG_ID;
  NameTag = DISTRIBUTION_ALG_NAME;
  SubClass = ALGORITHM_OPERATION_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataDistributionAlgorithmClass(data)  . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataDistributionAlgorithmClass::DataDistributionAlgorithmClass(const DataDistributionAlgorithmClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataDistributionAlgorithmClass(id,name,descr) . . . . . . . . constructor
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
DataDistributionAlgorithmClass::DataDistributionAlgorithmClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = ALGORITHM_OPERATION_NAME;
  EncodeDecodeClass = DISTRIBUTION_ALG_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . .  DataDistributionAlgorithmClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataDistributionAlgorithmClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . .  DataDistributionAlgorithmClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataDistributionAlgorithmClass, there is no further information.
**
**  REMARKS
**
*/
bool DataDistributionAlgorithmClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . .  DataDistributionAlgorithmClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataDistributionAlgorithmClass::CopyClone(Identify *  objc)
{
  DataDistributionAlgorithmClass *objcfull = (DataDistributionAlgorithmClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . .  DataDistributionAlgorithmClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataDistributionAlgorithmClass::Clone()
    {
      DataDistributionAlgorithmClass* id = new DataDistributionAlgorithmClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . .  DataDistributionAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDistributionAlgorithmClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . .  DataDistributionAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDistributionAlgorithmClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataDistributionAlgorithmClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataDistributionAlgorithm();
}
/*F ans = TopDecode(buffer,obj) . . . . . . .  DataDistributionAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataDistributionAlgorithmClass*& obj)
     {
     obj = new DataDistributionAlgorithmClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . BaseDataDistributionAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataDistributionAlgorithm*& obj)
     {
     obj = new BaseDataDistributionAlgorithm;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataNormalizeOperation
 */ 
/*F BaseDataNormalizeOperation()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataNormalizeOperation::BaseDataNormalizeOperation()
{
  Identification = DISTRIBUTION_NORMALIZE_ID;
  NameTag = DISTRIBUTION_NORMALIZE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataNormalizeOperation(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataNormalizeOperation::BaseDataNormalizeOperation(const BaseDataNormalizeOperation& data)
  : BaseDataParameterizedFunction(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataNormalizeOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataNormalizeOperation::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataNormalizeOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataNormalizeOperation::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataParameterizedFunction::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataNormalizeOperation
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataNormalizeOperation::print(ostream& out) const
{
  BaseDataParameterizedFunction::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataNormalizeOperation
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataNormalizeOperation::Clone()
{
  BaseDataNormalizeOperation *obj = new BaseDataNormalizeOperation(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataNormalizeOperation
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataNormalizeOperation::CopyClone(Identify * obj)
{
  BaseDataNormalizeOperation *objfull = (BaseDataNormalizeOperation *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataNormalizeOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNormalizeOperation::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataParameterizedFunction::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataNormalizeOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNormalizeOperation::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataParameterizedFunction::DecodeThis(buffer);
  // The rest

  return result;
}
/*F obj = operator()(x,y,xclass,yclass) . . . . . . . . . . BaseDataNormalizeOperation
**
**  DESCRIPTION
**    x,y: The objects to be operated on
**    xclass,yclass: The object classes
**    obj: The result
**
**    This is a two-dimensional call.  An object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNormalizeOperation::operator()(BaseDataObject *x, BaseDataObject *y,
						       DataObjectClass *xc, DataObjectClass *yc)
{
  return operator()(x,xc);
}
/*F obj = operator()(x,xclass)  . . . . . . . . . . . . . . BaseDataNormalizeOperation
**
**  DESCRIPTION
**    x: The object to be operated on
**    xclass: The class of the object
**    obj: The result
**
**    This is a one-dimensional call.  An object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNormalizeOperation::operator()(BaseDataObject *x,
					     DataObjectClass *xc)
{
  InsertParameterSet();
  BaseDataObject *obj = getOperation()->operator()(x,xc);
  return obj;
}
/*F obj = operator()(cls,x,y,xclass,yclass) . . . . . . . . . . BaseDataNormalizeOperation
**
**  DESCRIPTION
**    x,y: The objects to be operated on
**    xclass,yclass: The object classes
**    obj: The result
**
**    This is a two-dimensional call.  An object is created.
**    The cls is used (among other things) to check the input types
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNormalizeOperation::operator()(DataObjectClass *cls,
						  BaseDataObject *x, BaseDataObject *y,
						  DataObjectClass *xc, DataObjectClass *yc)
                                              
{
  /*
    DataSetOfObjectsClass *set = (BaseDataSetOfObjects *) cls->PointerToAllowedClasses();
    bool result = true;
    result = result && set->IsOfClass(xc,_NAME);
    result = result && set->IsOfClass(yc,_NAME);
    result = result && (x->GetType() == xc->GetType());
    result = result && (y->GetType() == yc->GetType());
  */
  return operator()(x,y,xc,yc);
}
/*F obj = operator()(cls,x,xclass)  . . . . . . . . . . . . . . BaseDataNormalizeOperation
**
**  DESCRIPTION
**    cls: The class of the operation
**    x: The object to be operated on
**    xclass: The class of the object
**    obj: The result
**
**    This is a dummy one-dimensional call.  An empty object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataNormalizeOperation::operator()(DataObjectClass *cls,
						  BaseDataObject *x,
						  DataObjectClass *xclass)
{
  /*
    DataSetOfObjectsClass *set = (BaseDataSetOfObjects *) cls->PointerToAllowedClasses();
    bool result = true;
    result = result && set->IsOfClass(xc,_NAME);
    result = result && (x->GetType() == xc->GetType());
  */
  return operator()(x,xclass);
}

 
/*S DataNormalizeOperationClass
 */
/*F DataNormalizeOperationClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataNormalizeOperationClass::DataNormalizeOperationClass()
{
  Identification = DISTRIBUTION_NORMALIZE_ID;
  NameTag = DISTRIBUTION_NORMALIZE_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataNormalizeOperationClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataNormalizeOperationClass::DataNormalizeOperationClass(const DataNormalizeOperationClass& data)
  : DataParameterizedFunctionClass(data)
{
} 
 
/*F DataNormalizeOperationClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataNormalizeOperationClass::DataNormalizeOperationClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataParameterizedFunctionClass(id,name,descr)
{
  SubClass = "Operation";
  EncodeDecodeClass = DISTRIBUTION_NORMALIZE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataNormalizeOperationClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataNormalizeOperationClass::print(ostream& out) const
{
  DataParameterizedFunctionClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataNormalizeOperationClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataNormalizeOperationClass, there is no further information.
**
**  REMARKS
**
*/
bool DataNormalizeOperationClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataParameterizedFunctionClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataNormalizeOperationClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataNormalizeOperationClass::CopyClone(Identify *  objc)
{
  DataNormalizeOperationClass *objcfull = (DataNormalizeOperationClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataNormalizeOperationClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataNormalizeOperationClass::Clone()
    {
      DataNormalizeOperationClass* id = new DataNormalizeOperationClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataNormalizeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNormalizeOperationClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataParameterizedFunctionClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataNormalizeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNormalizeOperationClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataParameterizedFunctionClass::DecodeThis(buffer);
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
BaseDataObject * DataNormalizeOperationClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataNormalizeOperation();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataNormalizeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataNormalizeOperationClass*& obj)
     {
     obj = new DataNormalizeOperationClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataNormalizeOperation
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataNormalizeOperation*& obj)
     {
     obj = new BaseDataNormalizeOperation;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataSimpleNormalizeOperation
 */ 
/*F BaseDataSimpleNormalizeOperation()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSimpleNormalizeOperation::BaseDataSimpleNormalizeOperation()
{
  Identification = DISTRIBUTION_SIMPLENORM_ID;
  NameTag = DISTRIBUTION_SIMPLENORM_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  InsertParametersWithOperation();
} 
/*F BaseDataSimpleNormalizeOperation(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataSimpleNormalizeOperation::BaseDataSimpleNormalizeOperation(const BaseDataSimpleNormalizeOperation& data)
  : BaseDataNormalizeOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataSimpleNormalizeOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataSimpleNormalizeOperation::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataSimpleNormalizeOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataSimpleNormalizeOperation::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataNormalizeOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataSimpleNormalizeOperation
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataSimpleNormalizeOperation::print(ostream& out) const
{
  BaseDataNormalizeOperation::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataSimpleNormalizeOperation
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataSimpleNormalizeOperation::Clone()
{
  BaseDataSimpleNormalizeOperation *obj = new BaseDataSimpleNormalizeOperation(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataSimpleNormalizeOperation
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataSimpleNormalizeOperation::CopyClone(Identify * obj)
{
  BaseDataSimpleNormalizeOperation *objfull = (BaseDataSimpleNormalizeOperation *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSimpleNormalizeOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSimpleNormalizeOperation::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataNormalizeOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSimpleNormalizeOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSimpleNormalizeOperation::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataNormalizeOperation::DecodeThis(buffer);
  // The rest

  return result;
}
/*F obj = InsertParameterSet()  . . . . . . . . . . . . . . BaseDataSimpleNormalize
**
**  DESCRIPTION
**   x: The argument to operate on
**
**  REMARKS
**
*/
bool BaseDataSimpleNormalizeOperation::InsertParameterSet()
{
  //cout << "BaseDataSimpleNormalizeOperation::InsertParameterSet()" << endl;
  
  BaseDataParameterSet *paramset = getParameterSet();
  ObjectList<String> *parameters = paramset->OrderedListOfParameterNames().Clone();
  String offsetS = parameters->front();
  parameters->pop_front();
  String scaleS  = parameters->front();
  parameters->pop_front();
  BaseDataObject *OffSetobj = paramset->GetObject(offsetS);
  BaseDataObject *Scaleobj  = paramset->GetObject(scaleS);
  // should do some checking at this point.....if Numeric objects
  BaseDataSimpleNormalize *simple = (BaseDataSimpleNormalize *) getOperation();
  simple->setOffSet((BaseDataNumeric *) OffSetobj);
  simple->setScale((BaseDataNumeric *) Scaleobj);
  delete parameters;
  return true;
}
/*S DataSimpleNormalizeOperationClass
 */
/*F DataSimpleNormalizeOperationClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataSimpleNormalizeOperationClass::DataSimpleNormalizeOperationClass()
{
  Identification = DISTRIBUTION_SIMPLENORM_ID;
  NameTag = DISTRIBUTION_SIMPLENORM_NAME;
  SubClass = "NormalizeOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataSimpleNormalizeOperationClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataSimpleNormalizeOperationClass::DataSimpleNormalizeOperationClass(const DataSimpleNormalizeOperationClass& data)
  : DataNormalizeOperationClass(data)
{
} 
 
/*F DataSimpleNormalizeOperationClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataSimpleNormalizeOperationClass::DataSimpleNormalizeOperationClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataNormalizeOperationClass(id,name,descr)
{
  SubClass = "NormalizeOperation";
  EncodeDecodeClass = DISTRIBUTION_SIMPLENORM_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataSimpleNormalizeOperationClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataSimpleNormalizeOperationClass::print(ostream& out) const
{
  DataNormalizeOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataSimpleNormalizeOperationClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataSimpleNormalizeOperationClass, there is no further information.
**
**  REMARKS
**
*/
bool DataSimpleNormalizeOperationClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataNormalizeOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataSimpleNormalizeOperationClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataSimpleNormalizeOperationClass::CopyClone(Identify *  objc)
{
  DataSimpleNormalizeOperationClass *objcfull = (DataSimpleNormalizeOperationClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataSimpleNormalizeOperationClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataSimpleNormalizeOperationClass::Clone()
    {
      DataSimpleNormalizeOperationClass* id = new DataSimpleNormalizeOperationClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataSimpleNormalizeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSimpleNormalizeOperationClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataNormalizeOperationClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataSimpleNormalizeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSimpleNormalizeOperationClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataNormalizeOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataSimpleNormalizeOperationClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataSimpleNormalizeOperation();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataSimpleNormalizeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataSimpleNormalizeOperationClass*& obj)
     {
     obj = new DataSimpleNormalizeOperationClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataSimpleNormalizeOperation
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataSimpleNormalizeOperation*& obj)
     {
     obj = new BaseDataSimpleNormalizeOperation;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataSimpleNormalize
 */ 
/*F BaseDataSimpleNormalize() . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSimpleNormalize::BaseDataSimpleNormalize()
  : OffSet(NULL),
  Scale(NULL)
{
  Identification = DISTRIBUTION_NORMOP_ID;
  NameTag = DISTRIBUTION_NORMOP_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataSimpleNormalize(data) . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataSimpleNormalize::BaseDataSimpleNormalize(const BaseDataSimpleNormalize& data)
  : BaseDataOperation(data)
{
  OffSet = (BaseDataNumeric *) PointerClone(data.OffSet);
  Scale = (BaseDataNumeric *) PointerClone(data.Scale);
}
/*F Read(in,objc) . . . . . . . . . . . . . . Read in BaseDataSimpleNormalize
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataSimpleNormalize::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . Read in BaseDataSimpleNormalize
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataSimpleNormalize::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  DataSimpleNormalizeClass *objcfull = (DataSimpleNormalizeClass *) objc;
  String notdefined("Factors not defined");

  result = result && PointerObjectRead(in,(BaseDataObject *&) OffSet,objcfull->getOffSetClass(),notdefined);
  result = result && PointerObjectRead(in,(BaseDataObject *&) Scale,objcfull->getScaleClass(),notdefined);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . BaseDataSimpleNormalize
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataSimpleNormalize::print(ostream& out) const
{
  BaseDataOperation::print(out);
  PointerPrint(out,"\nThe OffSet Factor (is added): ","No Factor",OffSet);
  PointerPrint(out,"\nThe Scale Factor (is multiplied): ","No Factor",Scale);
  out << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . BaseDataSimpleNormalize
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataSimpleNormalize::Clone()
{
  BaseDataSimpleNormalize *obj = new BaseDataSimpleNormalize(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . BaseDataSimpleNormalize
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataSimpleNormalize::CopyClone(Identify * obj)
{
  BaseDataSimpleNormalize *objfull = (BaseDataSimpleNormalize *) obj;
  *this = *objfull;
  OffSet = (BaseDataNumeric *) PointerClone(objfull->OffSet);
  Scale = (BaseDataNumeric *) PointerClone(objfull->Scale);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . BaseDataSimpleNormalize
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSimpleNormalize::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  result = result && PointerEncode(buffer,Scale);
  result = result && PointerEncode(buffer,OffSet);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . BaseDataSimpleNormalize
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSimpleNormalize::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Scale);
  result = result && PointerDecode(buffer,(BaseDataObject *&) OffSet);
  return result;
}
/*F obj = operator()(x,y,xclass,yclass) . . . . . . . BaseDataSimpleNormalize
**
**  DESCRIPTION
**    x,y: The objects to be operated on
**    xclass,yclass: The object classes
**    obj: The result
**
**    This is a two-dimensional call.  An object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataSimpleNormalize::operator()(BaseDataObject *x, BaseDataObject *y,
					     DataObjectClass *xc, DataObjectClass *yc)
{
  cout << "BaseDataSimpleNormalize::operator() - 2" << endl;
  return operator()(x,xc);
}
/*F obj = operator()(x,xclass)  . . . . . . . . . . . BaseDataSimpleNormalize
**
**  DESCRIPTION
**    x: The object to be operated on
**    xclass: The class of the object
**    obj: The result
**
**    This is a one-dimensional call.  An object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataSimpleNormalize::operator()(BaseDataObject *x,
						    DataObjectClass *xc)
{
  BaseDataObject *answer = CalculateSimpleNormalization(x);
  //cout << "BaseDataSimpleNormalize::operator() - 1" << endl;
  return answer;
}
/*F obj = operator()(cls,x,y,xclass,yclass) . . . . . BaseDataSimpleNormalize
**
**  DESCRIPTION
**    x,y: The objects to be operated on
**    xclass,yclass: The object classes
**    obj: The result
**
**    This is a two-dimensional call.  An object is created.
**    The cls is used (among other things) to check the input types
**
**  REMARKS
**
*/
BaseDataObject *BaseDataSimpleNormalize::operator()(DataObjectClass *cls,
						  BaseDataObject *x, BaseDataObject *y,
						  DataObjectClass *xc, DataObjectClass *yc)
                                              
{
  cout << "BaseDataSimpleNormalize::operator() - 2C" << endl;

  return operator()(x,y,xc,yc);
}
/*F obj = operator()(cls,x,xclass)  . . . . . . . . . BaseDataSimpleNormalize
**
**  DESCRIPTION
**    cls: The class of the operation
**    x: The object to be operated on
**    xclass: The class of the object
**    obj: The result
**
**    This is a dummy one-dimensional call.  An empty object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataSimpleNormalize::operator()(DataObjectClass *cls,
						    BaseDataObject *x,
						    DataObjectClass *xclass)
{
    cout << "BaseDataSimpleNormalize::operator() - 1C" << endl;

  //DataSimpleNormalizeClass *normcls = (DataSimpleNormalizeClass *) cls;
  //DataSetOfObjectsClass *set = (BaseDataSetOfObjects *) normcls->PointerToAllowedClasses();
  BaseDataObject *answer = NULL;
  //if(set->IsOfClass(*x,NUMERIC_BASE_NAME))
  //{
  answer = CalculateSimpleNormalization(x);
  //}
  return answer;
}
/*F obj = CalculateSimpleNormalization(x) .  BaseDataSimpleNormalizeOperation
**
**  DESCRIPTION
**   x: The argument to operate on
**
**  REMARKS
**
*/
BaseDataObject *BaseDataSimpleNormalize::CalculateSimpleNormalization(BaseDataObject *x)
{
  //print(cout);
  //cout << endl;
  //x->print(cout);
  //cout << endl;
  BaseDataNumeric *centered = (BaseDataNumeric *) OffSet->operator+((BaseDataNumeric *) x);
  BaseDataObject *answer = Scale->operator*(centered);
  delete centered;
  //answer->print(cout);
  //cout << endl;
  return answer;
}
/*F num =  getOffSet(); . . . . . . . . . . . . . . . BaseDataSimpleNormalize
**
**  DESCRIPTION
**   num: The offset parameter to insert
**
**  REMARKS
**
*/
BaseDataNumeric *BaseDataSimpleNormalize::getOffSet()
{
  return OffSet;
}
/*F num =  getScale();  . . . . . . . . . . . . . . . BaseDataSimpleNormalize
**
**  DESCRIPTION
**   num: The scaling parameter to insert
**
**  REMARKS
**
*/
BaseDataNumeric *BaseDataSimpleNormalize::getScale()
{
  return Scale;
}
/*F setOffSet(num); . . . . . . . . . . . . . . . . . BaseDataSimpleNormalize
**
**  DESCRIPTION
**   num: The offset parameter to insert
**
**  REMARKS
**
*/
void BaseDataSimpleNormalize::setOffSet(BaseDataNumeric *offset)
{
  if(OffSet != NULL)
    delete OffSet;
  OffSet = (BaseDataNumeric *) offset->Clone();
}
/*F num =  setScale(num); . . . . . . . . . . . . . . BaseDataSimpleNormalize
**
**  DESCRIPTION
**   num: The scaling parameter to insert
**
**  REMARKS
**
*/
void BaseDataSimpleNormalize::setScale(BaseDataNumeric *scale)
{
  if(Scale != NULL)
    delete Scale;
  Scale = (BaseDataNumeric *) scale->Clone();
} 
/*S DataSimpleNormalizeClass
 */
/*F DataSimpleNormalizeClass()  . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataSimpleNormalizeClass::DataSimpleNormalizeClass()
  : OffSetClass(NULL),
  ScaleClass(NULL)
{
  Identification = DISTRIBUTION_NORMOP_ID;
  NameTag = DISTRIBUTION_NORMOP_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataSimpleNormalizeClass(data)  . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataSimpleNormalizeClass::DataSimpleNormalizeClass(const DataSimpleNormalizeClass& data)
  : DataOperationClass(data)
{
  OffSetClass = (DataNumericClass *) PointerClone(data.OffSetClass);
  ScaleClass = (DataNumericClass *) PointerClone(data.ScaleClass);
} 
 
/*F DataSimpleNormalizeClass(id,name,descr) . . . . . . . . . . . constructor
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
DataSimpleNormalizeClass::DataSimpleNormalizeClass(const int id, 
						   const String& name,
						   const String& descr)
  : DataOperationClass(id,name,descr),
  OffSetClass(NULL),
  ScaleClass(NULL)

{
  SubClass = "Operation";
  EncodeDecodeClass = "SimpleNormalize";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataSimpleNormalizeClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataSimpleNormalizeClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  PointerPrint(out,"  The OffSetClass: "," No Class Defined ",OffSetClass);
  PointerPrint(out,"  The ScaleClass: "," No Class Defined ",ScaleClass);
  return out;
}
/*F in1 = Read(in)  . . . . . . . . . . . . . . . .  DataSimpleNormalizeClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataSimpleNormalizeClass, there is no further information.
**
**  REMARKS
**
*/
bool DataSimpleNormalizeClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);
  result = result && PointerClassRead(in,(DataObjectClass *&) OffSetClass,
				      NUMERIC_BASE_NAME,
				      set," No Class ");
  result = result && PointerClassRead(in,(DataObjectClass *&) ScaleClass,
				      NUMERIC_BASE_NAME,
				      set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . .  DataSimpleNormalizeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataSimpleNormalizeClass::CopyClone(Identify *  objc)
{
  DataSimpleNormalizeClass *objcfull = (DataSimpleNormalizeClass *) objc;
  *this = *objcfull;
  OffSetClass = (DataNumericClass *) PointerClone(objcfull->OffSetClass);
  ScaleClass = (DataNumericClass *) PointerClone(objcfull->ScaleClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . .  DataSimpleNormalizeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataSimpleNormalizeClass::Clone()
    {
      DataSimpleNormalizeClass* id = new DataSimpleNormalizeClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . .  DataSimpleNormalizeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSimpleNormalizeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,OffSetClass);
  result = result && PointerEncode(buffer,ScaleClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . .  DataSimpleNormalizeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSimpleNormalizeClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) OffSetClass);
  result = result && PointerDecode(buffer,(BaseDataObject *&) ScaleClass);
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
BaseDataObject * DataSimpleNormalizeClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataSimpleNormalize();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . .  DataSimpleNormalizeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataSimpleNormalizeClass*& obj)
     {
     obj = new DataSimpleNormalizeClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . BaseDataSimpleNormalize
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataSimpleNormalize*& obj)
     {
     obj = new BaseDataSimpleNormalize;
     return obj->DecodeThis(buffer);
     }
 
/*F scale = getOffSetClass()  . . . . . . . . . . .  DataSimpleNormalizeClass
**
**  DESCRIPTION
**    scale: The scale factor for the normalization
**
**  REMARKS
**
*/
DataNumericClass *DataSimpleNormalizeClass::getOffSetClass()
{
  return OffSetClass;
}
/*F offset = getScaleClass()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataNumericClass *DataSimpleNormalizeClass::getScaleClass()
{
  return ScaleClass;
}
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void DataSimpleNormalizeClass::setOffSetClass(DataNumericClass *offsetcls)
{
  if(OffSetClass != NULL)
    delete OffSetClass;
  OffSetClass = (DataNumericClass *) offsetcls->Clone();
}
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void DataSimpleNormalizeClass::setScaleClass(DataNumericClass *scalecls)
{
  if(ScaleClass != NULL)
    delete ScaleClass;
  ScaleClass = (DataNumericClass *) scalecls->Clone();
}
/*S BaseDataNormalizeOpFromDistribution
 */ 
/*F BaseDataNormalizeOpFromDistribution() . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataNormalizeOpFromDistribution::BaseDataNormalizeOpFromDistribution()
  : DistributionListS("Distributions"),
  RootNameS("OperationRoot"),
  OperationClassS("OperationClass"),
  ExpressionTreeClassS("ExpressionTreeClass"),
  OpListS("OperationList")
{
  Identification = DISTRIBUTION_DISTTONORM_ID;
  NameTag = DISTRIBUTION_DISTTONORM_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataNormalizeOpFromDistribution(data) . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataNormalizeOpFromDistribution::BaseDataNormalizeOpFromDistribution(const BaseDataNormalizeOpFromDistribution& data)
  : BaseDataAlgorithmOperation(data),
  DistributionListS(data.DistributionListS),
  RootNameS(data.RootNameS),
  OperationClassS(data.OperationClassS),
  ExpressionTreeClassS(data.ExpressionTreeClassS),
  OpListS(data.OpListS)
{
}
/*F Read(in,objc) . . . . . . . . Read in BaseDataNormalizeOpFromDistribution
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataNormalizeOpFromDistribution::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . Read in BaseDataNormalizeOpFromDistribution
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataNormalizeOpFromDistribution::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . BaseDataNormalizeOpFromDistribution
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataNormalizeOpFromDistribution::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . BaseDataNormalizeOpFromDistribution
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataNormalizeOpFromDistribution::Clone()
{
  BaseDataNormalizeOpFromDistribution *obj = new BaseDataNormalizeOpFromDistribution(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . BaseDataNormalizeOpFromDistribution
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataNormalizeOpFromDistribution::CopyClone(Identify * obj)
{
  BaseDataNormalizeOpFromDistribution *objfull = (BaseDataNormalizeOpFromDistribution *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . BaseDataNormalizeOpFromDistribution
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNormalizeOpFromDistribution::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && Encode(buffer,DistributionListS);
  result = result && Encode(buffer,RootNameS);
  result = result && Encode(buffer,OperationClassS);
  result = result && Encode(buffer,ExpressionTreeClassS);
  result = result && Encode(buffer,OpListS);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . BaseDataNormalizeOpFromDistribution
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNormalizeOpFromDistribution::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && Decode(buffer,DistributionListS);
  result = result && Decode(buffer,RootNameS);
  result = result && Decode(buffer,OperationClassS);
  result = result && Decode(buffer,ExpressionTreeClassS);
  result = result && Decode(buffer,OpListS);
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
bool BaseDataNormalizeOpFromDistribution::SetUpAlgorithms(BaseDataSetOfInstances *instances,
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
bool BaseDataNormalizeOpFromDistribution::CheckInput(BaseDataSetOfInstances *instances,
						     DataSetOfInstancesClass *instancesclass,
						     BaseDataAlgorithmRun *run,
						     DataAlgorithmRunClass *runclass)
{
  bool result = true;

  if(run->ParameterInList(DistributionListS))
    {
      if(run->ParameterInList(RootNameS))
	{
	  if(run->ParameterInList(OperationClassS))
	    {
	      if(run->ParameterInList(ExpressionTreeClassS))
		{
		}
	      else
		{
		  cerr << "The expression class  parameter '" << ExpressionTreeClassS << "' was not in the list of parameters";
		  result = false;
		}
	    }
	  else
	    {
	      cerr << "The operation class  parameter '" << OperationClassS << "' was not in the list of parameters";
	      result = false;
	    }
	}
      else
	{
	  cerr << "The root name parameter '" << RootNameS << "' was not in the list of parameters";
	  result = false;
	}
    }
  else
    {
      cerr << "The distribution parameter '" << DistributionListS << "' was not in the list of parameters";
      result = false;
    }

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
bool BaseDataNormalizeOpFromDistribution::SetUpInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;

  RootName = (BaseDataString *) run->ParameterValue(RootNameS);
  DistributionList = (BaseDataKeyWords *) run->ParameterValue(DistributionListS)->Clone();
  BaseDataString *OperationClass = (BaseDataString *) run->ParameterValue(OperationClassS)->Clone();
  BaseDataString *ExpressionTreeClass = (BaseDataString *) run->ParameterValue(ExpressionTreeClassS)->Clone();
  Expressions = (DataExpressionTreeClass *) 
    instancesclass->PointerToAllowedClasses()->GetObjectClass(ExpressionTreeClass->getString());
  ParameterizedOperationClass = (DataNormalizeOperationClass *)
    instancesclass->PointerToAllowedClasses()->GetObjectClass(OperationClass->getString());
  cout << endl << "----------------------------------------------------------" << endl;
  ParameterizedOperationClass->print(cout);
  NormOpClass = (DataSimpleNormalizeClass *) ParameterizedOperationClass->getOperationClass();
  cout << endl << "----------------------------------------------------------" << endl;
  NormOpClass->print(cout);
  ParamsClass = (DataParameterSetClass *) ParameterizedOperationClass->getParameterClass();
  cout << endl << "----------------------------------------------------------" << endl;
  ParamsClass->print(cout);
  OpList = new BaseDataKeyWords();
  OpList->NameTag = OpListS;
  cout << endl << "----------------------------------------------------------" << endl;

  
  
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
bool BaseDataNormalizeOpFromDistribution::Calculate(BaseDataSetOfInstances *instances,
						    DataSetOfInstancesClass *instancesclass,
						    BaseDataAlgorithmRun *run,
						    DataAlgorithmRunClass *runclass)
{
  bool result = true;
  double scale,offset;

  while(DistributionList->SizeOf() > 0) {
      String name = DistributionList->NextKey();
      if(instances->IsInList(name)) {
	  BaseDataAttributeDistribution *dist = (BaseDataAttributeDistribution *) instances->GetObject(name);
	  PrimitiveStats *stats = dist->getStatistics();
	  String *opname = new String(RootName->getString());
	  opname->AppendToEnd(stats->NameTag);
	  
	  bool nodeviation = NoDeviationCheck(stats);

	  cout << "Operation Name: " << *opname << endl;
	  if(!nodeviation)  {
	      scale = SetScaleFactor(stats,run);
	      offset = SetOffSetFactor(stats,run);
	  } else {
	    scale = 1.0;
	    offset = 0.0;
	  }
	      cout << "OffSet: " << offset << "   Scale: " << scale << endl;
	      BaseDataReal *scaleobj = new BaseDataReal();
	      BaseDataReal *offsetobj = new BaseDataReal();
	      scaleobj->NameTag = "Scale";
	      offsetobj->NameTag = "OffSet";
	      scaleobj->SetValue(scale);
	      offsetobj->SetValue(offset);
	      cout << "-------------------------" << endl;
	      BaseDataSimpleNormalize *normop = (BaseDataSimpleNormalize *)
		NormOpClass->BaseDataObjectExample();
	      cout << "-------------------------" << endl;
	      BaseDataSimpleNormalizeOperation *paramnormop = (BaseDataSimpleNormalizeOperation *)
		ParameterizedOperationClass->BaseDataObjectExample();
	      cout << "-------------------------" << endl;
	      BaseDataParameterSet *paramset = (BaseDataParameterSet *)
		ParamsClass->BaseDataObjectExample();
	      cout << "-------------------------" << endl;
	      
	      paramnormop->setOperation(normop);
	      paramset->AddObject(offsetobj);	
	      paramset->AddObject(scaleobj);
	      paramnormop->setParameterSet(paramset);
	      paramnormop->NameTag = *opname;
	      
	      OpList->AddKeyWord(*opname);
	      Expressions->AddOperation(paramnormop);
	      cout << "-------------------------" << endl;
	      paramnormop->print(cout);
	      cout << endl;

	      delete scaleobj;
	      delete offsetobj;
	      delete normop;
	      delete paramnormop;
	      delete paramset;
	  }
    }
  return result;
} 
/*F ans = NoDeviationCheck(stats) . . . . BaseDataNormalizeOpFromDistribution
**
**  DESCRIPTION
**    stats: The primitive stats
**
**  REMARKS
**
*/
bool BaseDataNormalizeOpFromDistribution::NoDeviationCheck(PrimitiveStats *stats)
{
  double width = stats->Max - stats->Min;
  bool nodev = true;
  if(width > 1e-30) {
    nodev = false;
    cout << "No Deviation: " << stats->NameTag << " Max=" << stats->Max << "  Min=" << stats->Min << endl;
  }
  return nodev;
}
/*F scale = SetScaleFactor(stats,run) . . BaseDataNormalizeOpFromDistribution
**
**  DESCRIPTION
**    stats: The primitive statistics
**    run: The run info
**  REMARKS
**
*/
double BaseDataNormalizeOpFromDistribution::SetOffSetFactor(PrimitiveStats *stats,BaseDataAlgorithmRun *run)
{
  double offset;
  if(run->AlgorithmSummary.KeyWordInList("MeanOffSet"))
    {
      offset = -(stats->Mean);
    } 
  else if(run->AlgorithmSummary.KeyWordInList("AverageOffSet"))
    {
      offset = -(stats->Average);
    }
  else if(run->AlgorithmSummary.KeyWordInList("ZeroPreserving"))
    {
      offset = 0.0;
    }
  else if(run->AlgorithmSummary.KeyWordInList("MinimumIsZero"))
    {
      offset = -(stats->Min);
    }
  else
    {
      offset = 0.0;
    }
  
  return offset;
}
/*F scale = SetScaleFactor(stats,run) . . BaseDataNormalizeOpFromDistribution
**
**  DESCRIPTION
**    stats: The primitive statistics
**    run: The info
**  REMARKS
**
*/
double BaseDataNormalizeOpFromDistribution::SetScaleFactor(PrimitiveStats *stats,BaseDataAlgorithmRun *run)
{
  double scale;
  double width = stats->Max - stats->Min;
  if(run->AlgorithmSummary.KeyWordInList("ZeroPreserving"))
    {
      if(fabs(stats->Min) > fabs(stats->Max))
	scale = 1.0/(fabs(stats->Min));
      else
	scale = 1.0/(fabs(stats->Max));
    }
  else if(run->AlgorithmSummary.KeyWordInList("WidthScale"))
    {
      scale = 1.0/width;
    }
  else
    {
      scale = 1.0;
    }
  return scale;
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
bool BaseDataNormalizeOpFromDistribution::WriteOutputValues(BaseDataSetOfInstances *instances,
					 DataSetOfInstancesClass *instancesclass,
					 BaseDataAlgorithmRun *run,
					 DataAlgorithmRunClass *runclass)
{
  bool result = true;
  instances->AddObject(OpList);
  
  run->AddParameter(OpList);
  
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
bool BaseDataNormalizeOpFromDistribution::ConcludeRun(BaseDataSetOfInstances *instances,
				   DataSetOfInstancesClass *instancesclass,
				   BaseDataAlgorithmRun *run,
				   DataAlgorithmRunClass *runclass)
{
  bool result = true;
  delete OpList;
  return result;
} 
/*S DataNormalizeOpFromDistributionClass
 */
/*F DataNormalizeOpFromDistributionClass()  . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataNormalizeOpFromDistributionClass::DataNormalizeOpFromDistributionClass()
{
  Identification = DISTRIBUTION_DISTTONORM_ID;
  NameTag = DISTRIBUTION_DISTTONORM_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataNormalizeOpFromDistributionClass(data)  . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataNormalizeOpFromDistributionClass::DataNormalizeOpFromDistributionClass(const DataNormalizeOpFromDistributionClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataNormalizeOpFromDistributionClass(id,name,descr) . . . . . constructor
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
DataNormalizeOpFromDistributionClass::DataNormalizeOpFromDistributionClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = "NormalizeOpFromDistribution";
}
 
/*F out1 = print(out) . . . . . . . . .  DataNormalizeOpFromDistributionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataNormalizeOpFromDistributionClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . .  DataNormalizeOpFromDistributionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataNormalizeOpFromDistributionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataNormalizeOpFromDistributionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . .  DataNormalizeOpFromDistributionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataNormalizeOpFromDistributionClass::CopyClone(Identify *  objc)
{
  DataNormalizeOpFromDistributionClass *objcfull = (DataNormalizeOpFromDistributionClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . .  DataNormalizeOpFromDistributionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataNormalizeOpFromDistributionClass::Clone()
    {
      DataNormalizeOpFromDistributionClass* id = new DataNormalizeOpFromDistributionClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . .  DataNormalizeOpFromDistributionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNormalizeOpFromDistributionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . .  DataNormalizeOpFromDistributionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNormalizeOpFromDistributionClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataNormalizeOpFromDistributionClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataNormalizeOpFromDistribution();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . .  DataNormalizeOpFromDistributionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataNormalizeOpFromDistributionClass*& obj)
     {
     obj = new DataNormalizeOpFromDistributionClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . BaseDataNormalizeOpFromDistribution
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataNormalizeOpFromDistribution*& obj)
     {
     obj = new BaseDataNormalizeOpFromDistribution;
     return obj->DecodeThis(buffer);
     }
/*S Utility . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
 */
/*F InitialSetOfAlgorithmObjectsEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialDistributionObjectsEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataAttributeDistributionClass,BaseDataAttributeDistribution,DISTRIBUTION_ATTR_NAME);
  EncodeDecodeRegisterClass(DataDistributionAlgorithmClass,BaseDataDistributionAlgorithm,DISTRIBUTION_ALG_NAME);
  EncodeDecodeRegisterClass(DataNormalizeOperationClass,BaseDataNormalizeOperation,DISTRIBUTION_NORMALIZE_NAME);
  EncodeDecodeRegisterClass(DataSimpleNormalizeOperationClass,BaseDataSimpleNormalizeOperation,DISTRIBUTION_SIMPLENORM_NAME);
  EncodeDecodeRegisterClass(DataNormalizeOpFromDistributionClass,BaseDataNormalizeOpFromDistribution,DISTRIBUTION_DISTTONORM_NAME);
  EncodeDecodeRegisterClass(DataSimpleNormalizeClass,BaseDataSimpleNormalize,DISTRIBUTION_NORMOP_NAME);
}
/*F AddBaseDistributionClasses()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AddBaseDistributionClasses(DataSetOfObjectsClass& set)
{
  String attrdist("Distribution Attribute Class");
  String distalg("Distribution Algorithm");
  String normbasedescr("The Parameterized Normalization Base Class");
  String simplenormdescr("The Simple Parameterized Normalization Class");
  String normdistdescr("The Normalization Operation From Distribution Class");
  String asopdescr("The Simple Normalization as an Operation Class");
  
  DataAttributeDistributionClass attrclass(DISTRIBUTION_ATTR_ID,
			     DISTRIBUTION_ATTR_NAME,
			     attrdist); 
  DataDistributionAlgorithmClass distalgclass(DISTRIBUTION_ALG_ID,DISTRIBUTION_ALG_NAME,distalg);
  DataNormalizeOperationClass normbaseclass(DISTRIBUTION_NORMALIZE_ID,DISTRIBUTION_NORMALIZE_NAME,normbasedescr);
  DataSimpleNormalizeOperationClass simplenormclass(DISTRIBUTION_SIMPLENORM_ID,DISTRIBUTION_SIMPLENORM_NAME,simplenormdescr);
  DataNormalizeOpFromDistributionClass normdistclass(DISTRIBUTION_DISTTONORM_ID,DISTRIBUTION_DISTTONORM_NAME,normdistdescr);
  DataSimpleNormalizeClass asopclass(DISTRIBUTION_NORMOP_ID,DISTRIBUTION_NORMOP_NAME,asopdescr);
  
  set.AddObjectClass(attrclass);
  set.AddObjectClass(distalgclass);
  set.AddObjectClass(normbaseclass);
  set.AddObjectClass(simplenormclass);
  set.AddObjectClass(normdistclass);
  set.AddObjectClass(asopclass);
}
