/*  FILE     GeneticOperations.cc
**  PACKAGE  GeneticOperations
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "GeneticOperations" package.
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
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "ExpressionTree.hh"
#include "DistributionAlgorithm.hh"
#include "Optimize.hh"
#include "PopulationBasedOptimization.hh"
#include "GeneticOperations.hh"

/*S BaseDataGeneticDistribution
 */ 
/*F BaseDataGeneticDistribution()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGeneticDistribution::BaseDataGeneticDistribution()
  : DistributionName("Distribution"),
    ParameterName("Parameter"),
    Distribution(NULL)
{
  Identification = GENETIC_DISTRIBUTION_ID;
  NameTag = GENETIC_DISTRIBUTION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataGeneticDistribution(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGeneticDistribution::BaseDataGeneticDistribution(const BaseDataGeneticDistribution& data)
  : BaseDataGeneticObject(data),
    DistributionName(data.DistributionName),
    ParameterName(data.ParameterName)
    
{
  Distribution = (BaseDataAttributeDistribution *) PointerClone(data.Distribution);
}
 
/*F ~BaseDataGeneticDistribution()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGeneticDistribution::~BaseDataGeneticDistribution()
{
  if(Distribution != NULL)
    delete Distribution;
}


/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataGeneticDistribution
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataGeneticDistribution::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataGeneticDistribution
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataGeneticDistribution::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataGeneticObject::Read(in,objc,name);
  StreamObjectInput str(in,' ');
  ParameterName = str.ReadNext();
  DistributionName = str.ReadNext();
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataGeneticDistribution
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGeneticDistribution::print(ostream& out) const
{
  BaseDataGeneticObject::print(out);
  out << endl << "Parameter: '" << ParameterName << "' with Distribution: '" << DistributionName << "'" << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataGeneticDistribution
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGeneticDistribution::Clone()
{
  BaseDataGeneticDistribution *obj = new BaseDataGeneticDistribution(*this);
  return obj;
}
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataGeneticDistribution
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGeneticDistribution::CopyClone(Identify * obj)
{
  BaseDataGeneticDistribution *objfull = (BaseDataGeneticDistribution *) obj;
  *this = *objfull;
  BaseDataGeneticObject::CopyClone(obj);
  Distribution = (BaseDataAttributeDistribution *) PointerClone(objfull->Distribution);
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGeneticDistribution
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticDistribution::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataGeneticObject::EncodeThis(buffer);
  result = result && ParameterName.EncodeThis(buffer);
  result = result && DistributionName.EncodeThis(buffer);
  result = result && PointerEncode(buffer,(BaseDataObject *&) Distribution);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGeneticDistribution
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticDistribution::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataGeneticObject::DecodeThis(buffer);
  result = result && ParameterName.DecodeThis(buffer);
  result = result && DistributionName.DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Distribution);
  return result;
}
/*F ans = Mutate(cls,obj,objcls) . . . . . . . . . mutate object
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
bool BaseDataGeneticDistribution::Mutate(BaseDataObject *obj,
					 DataGeneticObjectClass *cls)
{
  bool result = true;
  BaseDataReal *num = (BaseDataReal *) obj;
  double rndm = ((double) random()) / ((double) RAND_MAX);
  double value = num->GetValue();
  double percent = value*0.10;
  double generated = value - percent + 2.0*percent*rndm;
  num->SetValue(generated);
  num->NameTag = ParameterName;
  
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
BaseDataSetOfObjects *BaseDataGeneticDistribution::CrossOver(BaseDataObject *obj1,
							     BaseDataObject *obj2,
							     BaseDataGeneticObject *genetic,
							     DataGeneticObjectClass *cls)
{
  BaseDataSetOfObjects *set;
  BaseDataReal *num1 = (BaseDataReal *) obj1;
  BaseDataReal *num2 = (BaseDataReal *) obj2;
  
  DataRealClass *numcls = (DataRealClass *) cls->getObjectClass();
  if(numcls != NULL)
    {
      BaseDataReal *newnum1 = (BaseDataReal *) numcls->BaseDataObjectExample();
      BaseDataReal *newnum2 = (BaseDataReal *) numcls->BaseDataObjectExample();

      double rndm1 = ((double) random()) / ((double) RAND_MAX);
      double rndm2 = ((double) random()) / ((double) RAND_MAX);
      
      double o1 = num1->GetValue();
      double o2 = num2->GetValue();
      double d1 = o1 + (o2 - o1)*rndm1;
      double d2 = o1 + (o2 - o1)*rndm2;

      newnum1->SetValue(d1);
      newnum2->SetValue(d2);
      newnum1->NameTag = "C1";
      newnum2->NameTag = "C2";

      set = new BaseDataSetOfObjects();
      set->AddObject(newnum1);
      set->AddObject(newnum2);
      delete newnum1;
      delete newnum2;
    }
  else
    {
      cerr << "Numeric Class within Genetic not set" << endl;
    }
  return set;
}
/*F ans = GeneticInitializeObject(cls,popobj,popobjcls) . . . initialize the object
**
**  DESCRIPTION
**    cls: The genetic object class
**    popobj: The population object to add new object
**    popobjcls: The population object class
**    ans: True if successful
**    
**  REMARKS
**
*/
BaseDataObject *BaseDataGeneticDistribution::GeneticInitializeObject(DataGeneticObjectClass *cls)
{
  BaseDataReal *num = (BaseDataReal *) BaseDataGeneticObject::GeneticInitializeObject(cls);
  double generated = GenerateDoubleValueFromDistribution();
  num->SetValue(generated);
  num->NameTag = ParameterName;
  return (BaseDataObject *) num;
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
bool BaseDataGeneticDistribution::GeneticInitialize(DataGeneticObjectClass *cls,
						    BaseDataSetOfInstances *insts,
						    DataSetOfInstancesClass *instcls)
{
  bool result = true;
  if(insts->IsInList(DistributionName))
    {
      Distribution = (BaseDataAttributeDistribution *) insts->GetObject(DistributionName)->Clone();
    }
  else
    {
      cerr << "Distribution '" << DistributionName << "' not found for Genetic Object" << endl;
      result = false;
    }
  return result;
}
 
/*F val = GenerateDoubleValueFromDistribution() . . . . . . . . . .  generate
**
**  DESCRIPTION
**    val: The generated value from the list of sorted values
**
**  REMARKS
**
*/
double BaseDataGeneticDistribution::GenerateDoubleValueFromDistribution()
{
  double value;
  if(Distribution != NULL)
    {
      double rndm = ((double) random()) / ((double) RAND_MAX);
      double rndm2 = ((double) random()) / ((double) RAND_MAX);
      unsigned int ilower;
      unsigned int iupper;
      
      unsigned int ivecsize = Distribution->getStatistics()->SortedValues.size();
      double vecsize = ivecsize;
      unsigned int icnt = (unsigned int) (rndm*(vecsize-2.0) + 0.5);
      if(icnt > 0)
	ilower = icnt - 1;
      else
	ilower = 0;
      if(icnt+1 < ivecsize)
	iupper = icnt+1;
      else
	iupper = ivecsize - 1;
      double min = Distribution->getStatistics()->SortedValues[ilower];
      double max = Distribution->getStatistics()->SortedValues[iupper];
      value = min + (max-min)*rndm2;
    }
  else
    {
      cerr << "Distribution not set, returning 0.0 as generated value" << endl;
      value = 0.0;
    }
  return value;
}
/*S DataGeneticDistributionClass
 */
/*F DataGeneticDistributionClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGeneticDistributionClass::DataGeneticDistributionClass()
{
  Identification = GENETIC_DISTRIBUTION_ID;
  NameTag = GENETIC_DISTRIBUTION_NAME;
  SubClass = GENETIC_OBJECT_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataGeneticDistributionClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGeneticDistributionClass::DataGeneticDistributionClass(const DataGeneticDistributionClass& data)
  : DataGeneticObjectClass(data)
{
} 
 
/*F DataGeneticDistributionClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataGeneticDistributionClass::DataGeneticDistributionClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataGeneticObjectClass(id,name,descr)
{
  SubClass = GENETIC_OBJECT_NAME;
  EncodeDecodeClass = GENETIC_DISTRIBUTION_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataGeneticDistributionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGeneticDistributionClass::print(ostream& out) const
{
  DataGeneticObjectClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataGeneticDistributionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGeneticDistributionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGeneticDistributionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataGeneticObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataGeneticDistributionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGeneticDistributionClass::CopyClone(Identify *  objc)
{
  DataGeneticDistributionClass *objcfull = (DataGeneticDistributionClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataGeneticDistributionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGeneticDistributionClass::Clone()
    {
      DataGeneticDistributionClass* id = new DataGeneticDistributionClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataGeneticDistributionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGeneticDistributionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataGeneticObjectClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataGeneticDistributionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGeneticDistributionClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataGeneticObjectClass::DecodeThis(buffer);
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
BaseDataObject * DataGeneticDistributionClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataGeneticDistribution();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGeneticDistributionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGeneticDistributionClass*& obj)
     {
     obj = new DataGeneticDistributionClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataGeneticDistribution
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGeneticDistribution*& obj)
     {
     obj = new BaseDataGeneticDistribution;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataGeneticStdDev
 */ 
/*F BaseDataGeneticStdDev()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGeneticStdDev::BaseDataGeneticStdDev()
{
  Identification = GENETIC_STDDEV_ID;
  NameTag = GENETIC_STDDEV_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataGeneticStdDev(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGeneticStdDev::BaseDataGeneticStdDev(const BaseDataGeneticStdDev& data)
  : BaseDataGeneticDistribution(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataGeneticStdDev
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataGeneticStdDev::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataGeneticStdDev
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataGeneticStdDev::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataGeneticDistribution::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataGeneticStdDev
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGeneticStdDev::print(ostream& out) const
{
  BaseDataGeneticDistribution::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataGeneticStdDev
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGeneticStdDev::Clone()
{
  BaseDataGeneticStdDev *obj = new BaseDataGeneticStdDev;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataGeneticStdDev
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGeneticStdDev::CopyClone(Identify * obj)
{
  BaseDataGeneticStdDev *objfull = (BaseDataGeneticStdDev *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGeneticStdDev
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticStdDev::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataGeneticDistribution::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGeneticStdDev
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticStdDev::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataGeneticDistribution::DecodeThis(buffer);
  // The rest

  return result;
}
/*S DataGeneticStdDevClass
 */
/*F DataGeneticStdDevClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGeneticStdDevClass::DataGeneticStdDevClass()
{
  Identification = GENETIC_STDDEV_ID;
  NameTag = GENETIC_STDDEV_NAME;
  SubClass = GENETIC_OBJECT_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataGeneticStdDevClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGeneticStdDevClass::DataGeneticStdDevClass(const DataGeneticStdDevClass& data)
  : DataGeneticDistributionClass(data)
{
} 
 
/*F DataGeneticStdDevClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataGeneticStdDevClass::DataGeneticStdDevClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataGeneticDistributionClass(id,name,descr)
{
  SubClass = GENETIC_OBJECT_NAME;
  EncodeDecodeClass = GENETIC_STDDEV_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataGeneticStdDevClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGeneticStdDevClass::print(ostream& out) const
{
  DataGeneticDistributionClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataGeneticStdDevClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGeneticStdDevClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGeneticStdDevClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataGeneticDistributionClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataGeneticStdDevClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGeneticStdDevClass::CopyClone(Identify *  objc)
{
  DataGeneticStdDevClass *objcfull = (DataGeneticStdDevClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataGeneticStdDevClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGeneticStdDevClass::Clone()
    {
      DataGeneticStdDevClass* id = new DataGeneticStdDevClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataGeneticStdDevClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGeneticStdDevClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataGeneticDistributionClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataGeneticStdDevClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGeneticStdDevClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataGeneticDistributionClass::DecodeThis(buffer);
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
BaseDataObject * DataGeneticStdDevClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataGeneticStdDev();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGeneticStdDevClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGeneticStdDevClass*& obj)
     {
     obj = new DataGeneticStdDevClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataGeneticStdDev
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGeneticStdDev*& obj)
     {
     obj = new BaseDataGeneticStdDev;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataGeneticInterval
 */ 
/*F BaseDataGeneticInterval()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGeneticInterval::BaseDataGeneticInterval()
{
  Identification = GENETIC_INTERVAL_ID;
  NameTag = GENETIC_INTERVAL_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataGeneticInterval(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGeneticInterval::BaseDataGeneticInterval(const BaseDataGeneticInterval& data)
  : BaseDataGeneticDistribution(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataGeneticInterval
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataGeneticInterval::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataGeneticInterval
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataGeneticInterval::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataGeneticDistribution::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataGeneticInterval
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGeneticInterval::print(ostream& out) const
{
  BaseDataGeneticDistribution::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataGeneticInterval
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGeneticInterval::Clone()
{
  BaseDataGeneticInterval *obj = new BaseDataGeneticInterval;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataGeneticInterval
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGeneticInterval::CopyClone(Identify * obj)
{
  BaseDataGeneticInterval *objfull = (BaseDataGeneticInterval *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGeneticInterval
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticInterval::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataGeneticDistribution::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGeneticInterval
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticInterval::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataGeneticDistribution::DecodeThis(buffer);
  // The rest

  return result;
}
/*S DataGeneticIntervalClass
 */
/*F DataGeneticIntervalClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGeneticIntervalClass::DataGeneticIntervalClass()
{
  Identification = GENETIC_INTERVAL_ID;
  NameTag = GENETIC_INTERVAL_NAME;
  SubClass = GENETIC_OBJECT_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataGeneticIntervalClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGeneticIntervalClass::DataGeneticIntervalClass(const DataGeneticIntervalClass& data)
  : DataGeneticDistributionClass(data)
{
} 
 
/*F DataGeneticIntervalClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataGeneticIntervalClass::DataGeneticIntervalClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataGeneticDistributionClass(id,name,descr)
{
  SubClass = GENETIC_OBJECT_NAME;
  EncodeDecodeClass = GENETIC_INTERVAL_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataGeneticIntervalClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGeneticIntervalClass::print(ostream& out) const
{
  DataGeneticDistributionClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataGeneticIntervalClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGeneticIntervalClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGeneticIntervalClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataGeneticDistributionClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataGeneticIntervalClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGeneticIntervalClass::CopyClone(Identify *  objc)
{
  DataGeneticIntervalClass *objcfull = (DataGeneticIntervalClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataGeneticIntervalClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGeneticIntervalClass::Clone()
    {
      DataGeneticIntervalClass* id = new DataGeneticIntervalClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataGeneticIntervalClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGeneticIntervalClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataGeneticDistributionClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataGeneticIntervalClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGeneticIntervalClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataGeneticDistributionClass::DecodeThis(buffer);
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
BaseDataObject * DataGeneticIntervalClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataGeneticInterval();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGeneticIntervalClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGeneticIntervalClass*& obj)
     {
     obj = new DataGeneticIntervalClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataGeneticInterval
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGeneticInterval*& obj)
     {
     obj = new BaseDataGeneticInterval;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataGeneticConstant
 */ 
/*F BaseDataGeneticConstant()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGeneticConstant::BaseDataGeneticConstant()
{
  Identification = GENETIC_CONSTANT_ID;
  NameTag = GENETIC_CONSTANT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataGeneticConstant(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGeneticConstant::BaseDataGeneticConstant(const BaseDataGeneticConstant& data)
  : BaseDataGeneticObject(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataGeneticConstant
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataGeneticConstant::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataGeneticConstant
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataGeneticConstant::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataGeneticObject::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataGeneticConstant
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGeneticConstant::print(ostream& out) const
{
  BaseDataGeneticObject::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataGeneticConstant
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGeneticConstant::Clone()
{
  BaseDataGeneticConstant *obj = new BaseDataGeneticConstant;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataGeneticConstant
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGeneticConstant::CopyClone(Identify * obj)
{
  BaseDataGeneticConstant *objfull = (BaseDataGeneticConstant *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGeneticConstant
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticConstant::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataGeneticObject::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGeneticConstant
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticConstant::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataGeneticObject::DecodeThis(buffer);
  // The rest

  return result;
}
/*S DataGeneticConstantClass
 */
/*F DataGeneticConstantClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGeneticConstantClass::DataGeneticConstantClass()
{
  Identification = GENETIC_CONSTANT_ID;
  NameTag = GENETIC_CONSTANT_NAME;
  SubClass = GENETIC_OBJECT_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataGeneticConstantClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGeneticConstantClass::DataGeneticConstantClass(const DataGeneticConstantClass& data)
  : DataGeneticObjectClass(data)
{
} 
 
/*F DataGeneticConstantClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataGeneticConstantClass::DataGeneticConstantClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataGeneticObjectClass(id,name,descr)
{
  SubClass = GENETIC_OBJECT_NAME;
  EncodeDecodeClass = GENETIC_CONSTANT_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataGeneticConstantClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGeneticConstantClass::print(ostream& out) const
{
  DataGeneticObjectClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataGeneticConstantClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGeneticConstantClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGeneticConstantClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataGeneticObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataGeneticConstantClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGeneticConstantClass::CopyClone(Identify *  objc)
{
  DataGeneticConstantClass *objcfull = (DataGeneticConstantClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataGeneticConstantClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGeneticConstantClass::Clone()
    {
      DataGeneticConstantClass* id = new DataGeneticConstantClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataGeneticConstantClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGeneticConstantClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataGeneticObjectClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataGeneticConstantClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGeneticConstantClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataGeneticObjectClass::DecodeThis(buffer);
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
BaseDataObject * DataGeneticConstantClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataGeneticConstant();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGeneticConstantClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGeneticConstantClass*& obj)
     {
     obj = new DataGeneticConstantClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataGeneticConstant
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGeneticConstant*& obj)
     {
     obj = new BaseDataGeneticConstant;
     return obj->DecodeThis(buffer);
     }

/*S BaseDataGeneticSetOfParameters
 */ 
/*F BaseDataGeneticSetOfParameters()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGeneticSetOfParameters::BaseDataGeneticSetOfParameters()
  : GeneticObjects(NULL)
{
  Identification = GENETIC_SETOFPARAMS_ID;
  NameTag = GENETIC_SETOFPARAMS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataGeneticSetOfParameters(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGeneticSetOfParameters::BaseDataGeneticSetOfParameters(const BaseDataGeneticSetOfParameters& data)
  : BaseDataGeneticObject(data)
{
  GeneticObjects = (BaseDataSetOfObjects *) PointerClone(data.GeneticObjects);
}
/*F BaseDataGeneticSetOfParameters()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGeneticSetOfParameters::~BaseDataGeneticSetOfParameters()
{
  if(GeneticObjects != NULL)
    delete GeneticObjects;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataGeneticSetOfParameters
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataGeneticSetOfParameters::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataGeneticSetOfParameters
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataGeneticSetOfParameters::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataGeneticObject::Read(in,objc,name);
  StreamObjectInput str(in,' ');
  String key = str.ReadNext();
  if(key == "GeneticParameters:")
    {
      DataGeneticSetOfParametersClass *genclass = (DataGeneticSetOfParametersClass *) objc;
      GeneticObjects = new BaseDataSetOfObjects();
      genclass->PointerToAllowedClasses()->SetDebugLevel(2);
      cout << "BaseDataGeneticSetOfParameters::Read" << endl;
      result = result && ReadInClassNamePairsAndSetOfObjects(in,NameTag,
							     GeneticObjects,
							     genclass->PointerToAllowedClasses());
    }
  else
    {
      cerr << "Expected 'GeneticParameters:' got '" << key << "'" << endl;
      result = false;
    }
      return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataGeneticSetOfParameters
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGeneticSetOfParameters::print(ostream& out) const
{
  BaseDataGeneticObject::print(out);
  PointerPrint(out,"Genetic Objects:","No Genetic Objects Defined",GeneticObjects);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataGeneticSetOfParameters
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGeneticSetOfParameters::Clone()
{
  BaseDataGeneticSetOfParameters *obj = new BaseDataGeneticSetOfParameters(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataGeneticSetOfParameters
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGeneticSetOfParameters::CopyClone(Identify * obj)
{
  BaseDataGeneticSetOfParameters *objfull = (BaseDataGeneticSetOfParameters *) obj;  
  *this = *objfull;
  BaseDataGeneticObject::CopyClone(obj);
  GeneticObjects = (BaseDataSetOfObjects *) PointerClone(objfull->GeneticObjects);
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGeneticSetOfParameters
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticSetOfParameters::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataGeneticObject::EncodeThis(buffer);
  result = result && PointerEncode(buffer,(BaseDataObject *&) GeneticObjects);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGeneticSetOfParameters
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGeneticSetOfParameters::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataGeneticObject::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) GeneticObjects);
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
bool BaseDataGeneticSetOfParameters::Mutate(BaseDataObject *obj,
					    DataGeneticObjectClass *cls)
{
  BaseDataSetOfObjects *set = (BaseDataSetOfObjects *) obj;
  DataGeneticSetOfParametersClass *genparcls = (DataGeneticSetOfParametersClass *) cls;
  bool result = true;
  ObjectList<String> varnames = GeneticObjects->ListOfObjectNames();
  ObjectList<String>::iterator varname = varnames.begin();
  double rndm = ((double) random()) / ((double) RAND_MAX);
  double rsize = (double) varnames.size();
  double inc = 1.0 / rsize + .0000001;
  double total = inc;
  while(total < rndm)
    {
      varname++;
      total += inc;
    }
  BaseDataGeneticObject *genobj = GetGeneticParameter(*varname);
  BaseDataObject *parobj = set->GetObject(*varname);
  DataGeneticObjectClass *gencls = genparcls->GetGeneticClass(genobj->GetType());
  genobj->Mutate(parobj,gencls);
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
BaseDataSetOfObjects *BaseDataGeneticSetOfParameters::CrossOver(BaseDataObject *objb1,
								BaseDataObject *objb2,
								BaseDataGeneticObject *genetic,
								DataGeneticObjectClass *cls)
{
  DataGeneticSetOfParametersClass *geneticclass = (DataGeneticSetOfParametersClass *) cls;
  BaseDataSetOfObjects *obj1 = (BaseDataSetOfObjects *) objb1;
  BaseDataSetOfObjects *obj2 = (BaseDataSetOfObjects *) objb2;

  DataObjectClass *popobjectbase = cls->getObjectClass();
  BaseDataSetOfObjects *set = PairSet(popobjectbase);

  BaseDataSetOfObjects *newobj1 = (BaseDataSetOfObjects *) set->GetObject(SET_NAME1);
  BaseDataSetOfObjects *newobj2 = (BaseDataSetOfObjects *) set->GetObject(SET_NAME2);
  ObjectList<String> varnames = obj1->ListOfObjectNames();
  ObjectList<String>::iterator varname = varnames.begin();

  double rndm = ((double) random()) / ((double) RAND_MAX);
  double vsize = (double) varnames.size() - 1.0;
  double pick = rndm*vsize + 1.0;
  double sum = 1.0;

  while(sum < pick)
    {
      BaseDataObject *lobj = obj1->GetObject(*varname);
      BaseDataObject *robj = obj2->GetObject(*varname);
      newobj1->AddObject(lobj);
      newobj2->AddObject(robj);
      sum += 1.0;
      varname++;
    }
  bool notcrossed = true;
  while(varname != varnames.end())
    {
      BaseDataObject *lobj = obj1->GetObject(*varname);
      BaseDataObject *robj = obj2->GetObject(*varname);
      if(notcrossed)
	{
	  
	  BaseDataGeneticObject *gobj = GetGeneticParameter(lobj->NameTag);
	  if(gobj != NULL)
	    {
	      DataGeneticObjectClass *gencls = (DataGeneticObjectClass *) geneticclass->GetGeneticClass(gobj->GetType());
	      BaseDataSetOfObjects *cset = gobj->CrossOver(lobj,robj,gobj,gencls);
	      BaseDataObject *lcobj = cset->GetObject(SET_NAME1);
	      BaseDataObject *rcobj = cset->GetObject(SET_NAME2);
	      rcobj->NameTag = *varname;
	      lcobj->NameTag = *varname;
	      newobj2->AddObject(rcobj);
	      newobj1->AddObject(lcobj);
	      delete cset;
	    }
	  else
	    {
	      cerr << "Aborting CrossOver of element in Parameter Set" << endl;
	      newobj2->AddObject(robj);
	      newobj1->AddObject(lobj);
	    }
	  notcrossed = false;
	}
      else
	{
	  newobj2->AddObject(robj);
	  newobj1->AddObject(lobj);
	}
      varname++;
    }
  return set;
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
BaseDataObject *BaseDataGeneticSetOfParameters::GeneticInitializeObject(DataGeneticObjectClass *cls)
{
  BaseDataParameterSet *set = (BaseDataParameterSet *) BaseDataGeneticObject::GeneticInitializeObject(cls);
  DataGeneticSetOfParametersClass *parsclass = (DataGeneticSetOfParametersClass *) cls;
  ObjectList<String> names = GeneticObjects->ListOfObjectNames();
  ObjectList<String>::iterator name;
  DataSetOfObjectsClass *setclass = parsclass->PointerToAllowedClasses();
  for(name=names.begin(); name != names.end();name++)
    {
      BaseDataGeneticObject *obj = (BaseDataGeneticObject *) GeneticObjects->GetObject(*name);
      unsigned int ptype = obj->GetType();
      DataGeneticObjectClass *objcls = (DataGeneticObjectClass *) setclass->GetObjectClass(ptype);
      BaseDataObject *newobj = obj->GeneticInitializeObject(objcls);
      set->AddObject(newobj);
      delete newobj;
    }
  return set;
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
bool BaseDataGeneticSetOfParameters::GeneticInitialize(DataGeneticObjectClass *cls,
						       BaseDataSetOfInstances *insts,
						       DataSetOfInstancesClass *instcls)
{
  if(instcls->getDebugLevel() > 2)
    cout << "BaseDataGeneticSetOfParameters::GeneticInitialize" << endl;
  DataGeneticSetOfParametersClass *parclass = (DataGeneticSetOfParametersClass *) cls;
  bool result = true;
  ObjectList<String> names = GeneticObjects->ListOfObjectNames();
  ObjectList<String>::iterator name;
  DataSetOfObjectsClass *parsetclass = (DataSetOfObjectsClass *) parclass->getObjectClass();
  DataSetOfObjectsClass *setclass = parsetclass->PointerToAllowedClasses();
  for(name=names.begin(); result && name != names.end();name++)
    {
      if(instcls->getDebugLevel() > 2)
	cout << "GeneticInitialize: '" << *name << "'" << endl;
      BaseDataGeneticObject *obj = (BaseDataGeneticObject *) GeneticObjects->GetObject(*name);
      unsigned int ptype = obj->GetType();
      DataGeneticObjectClass *objcls = (DataGeneticObjectClass *) setclass->GetObjectClass(ptype);
      result = result && obj->GeneticInitialize(objcls,insts,instcls);
    }
  return result;
}
 
/*F gen = GetGeneticParameter(name) . . . . . . .  get genetic info for param
**
**  DESCRIPTION
**    gen: Genetic information for the parameter 'name'
**
**  REMARKS
**
*/
BaseDataGeneticObject *BaseDataGeneticSetOfParameters::GetGeneticParameter(String& name)
{
  BaseDataGeneticObject *obj;
  if(GeneticObjects->IsInList(name))
      obj = (BaseDataGeneticObject *) GeneticObjects->GetObject(name);
  else
    {
      cerr << "Genetic Parameter '" << name << "' not found in Parameters" << endl;
      ObjectList<String> names = GeneticObjects->ListOfObjectNames();
      if(names.size() == 0)
	cerr << "No Objects in Genetic Objects" << endl;
      else
	{
	  names.print(cerr);
	  cerr << endl;
	  obj = NULL;
	}
    }
  return obj;
}
/*S DataGeneticSetOfParametersClass
 */
/*F DataGeneticSetOfParametersClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGeneticSetOfParametersClass::DataGeneticSetOfParametersClass()
  : GeneticObjectsClass(NULL)
{
  Identification = GENETIC_SETOFPARAMS_ID;
  NameTag = GENETIC_SETOFPARAMS_NAME;
  SubClass = "GeneticObject";
  EncodeDecodeClass = NameTag;
} 
/*F DataGeneticSetOfParametersClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGeneticSetOfParametersClass::DataGeneticSetOfParametersClass(const DataGeneticSetOfParametersClass& data)
  : DataGeneticObjectClass(data)
{
  GeneticObjectsClass = (DataSetOfObjectsClass *) PointerClone(data.GeneticObjectsClass);
}  
/*F DataGeneticSetOfParametersClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataGeneticSetOfParametersClass::DataGeneticSetOfParametersClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataGeneticObjectClass(id,name,descr),
    GeneticObjectsClass(NULL)
{
  SubClass = "GeneticObject";
  EncodeDecodeClass = GENETIC_SETOFPARAMS_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataGeneticSetOfParametersClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGeneticSetOfParametersClass::print(ostream& out) const
{
  DataGeneticObjectClass::print(out);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataGeneticSetOfParametersClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGeneticSetOfParametersClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGeneticSetOfParametersClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataGeneticObjectClass::Read(in,set);
  return result;
} 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataGeneticSetOfParametersClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGeneticSetOfParametersClass::CopyClone(Identify *  objc)
{
  DataGeneticSetOfParametersClass *objcfull = (DataGeneticSetOfParametersClass *) objc;
  *this = *objcfull;
  DataGeneticObjectClass::CopyClone(objc);
  GeneticObjectsClass = (DataSetOfObjectsClass *) PointerClone(GeneticObjectsClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataGeneticSetOfParametersClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGeneticSetOfParametersClass::Clone()
    {
      DataGeneticSetOfParametersClass* id = new DataGeneticSetOfParametersClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataGeneticSetOfParametersClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGeneticSetOfParametersClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataGeneticObjectClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,(DataObjectClass *&) GeneticObjectsClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataGeneticSetOfParametersClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGeneticSetOfParametersClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataGeneticObjectClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) GeneticObjectsClass);
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
BaseDataObject * DataGeneticSetOfParametersClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataGeneticSetOfParameters();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGeneticSetOfParametersClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGeneticSetOfParametersClass*& obj)
     {
     obj = new DataGeneticSetOfParametersClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataGeneticSetOfParameters
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGeneticSetOfParameters*& obj)
     {
     obj = new BaseDataGeneticSetOfParameters;
     return obj->DecodeThis(buffer);
     }
 
/*F classes = PointerToAllowedClasses() . . . . . . . .  total set of classes
**
**  DESCRIPTION
**    classes: The full set of classes
**
**  REMARKS
**
*/
DataSetOfObjectsClass *DataGeneticSetOfParametersClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}
 
/*F cls = GetGeneticClass(type) . . . . . . . . . . .  get genetic class info
**
**  DESCRIPTION
**    type: The type id of the class
**
**  REMARKS
**
*/
DataGeneticObjectClass *DataGeneticSetOfParametersClass::GetGeneticClass(unsigned int type)
{
  DataSetOfObjectsClass *classset = PointerToAllowedClasses();
  return (DataGeneticObjectClass *) classset->GetObjectClass(type);
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
extern void InitialGeneticEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataGeneticDistributionClass,BaseDataGeneticDistribution,GENETIC_DISTRIBUTION_NAME);
  EncodeDecodeRegisterClass(DataGeneticStdDevClass,BaseDataGeneticStdDev,GENETIC_STDDEV_NAME);
  EncodeDecodeRegisterClass(DataGeneticIntervalClass,BaseDataGeneticInterval,GENETIC_INTERVAL_NAME);
  EncodeDecodeRegisterClass(DataGeneticConstantClass,BaseDataGeneticConstant,GENETIC_CONSTANT_NAME);
  EncodeDecodeRegisterClass(DataGeneticSetOfParametersClass,BaseDataGeneticSetOfParameters,GENETIC_SETOFPARAMS_NAME);
}
 
/*F AddPopulationClasses(set)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AddGeneticClasses(DataSetOfObjectsClass& set)
{
  String distrdescr("Genetic Numeric Distribution Class");
  String stddevdescr("Genetic Numeric Standard Deviation Class");
  String intervaldescr("Genetic Numeric Interval Class");
  String constantdescr("Genetic Numeric Constant Class");
  String setdescr("Genetic Set of Objects Class");
  
  DataGeneticDistributionClass        distrclass(GENETIC_DISTRIBUTION_ID,GENETIC_DISTRIBUTION_NAME,distrdescr);
  DataGeneticStdDevClass              stddevclass(GENETIC_STDDEV_ID,GENETIC_STDDEV_NAME,stddevdescr);
  DataGeneticIntervalClass            intervalclass(GENETIC_INTERVAL_ID,GENETIC_INTERVAL_NAME,intervaldescr);
  DataGeneticConstantClass            constantclass(GENETIC_CONSTANT_ID,GENETIC_CONSTANT_NAME,constantdescr);
  DataGeneticSetOfParametersClass     setclass(GENETIC_SETOFPARAMS_ID,GENETIC_SETOFPARAMS_NAME,setdescr);

  set.AddObjectClass(distrclass);
  set.AddObjectClass(stddevclass);
  set.AddObjectClass(intervalclass);
  set.AddObjectClass(constantclass);
  set.AddObjectClass(setclass);
}
 
/*F set = PairSet(popobjectbase)  . . . . . . . . . .  initialize two objects
**
**  DESCRIPTION
**    popobjectbase: The example object
**    set: The resulting pair of objects
**
**  REMARKS
**
*/
BaseDataSetOfObjects *PairSet(DataObjectClass *popobjectbase)
{
  BaseDataSetOfObjects *set = new BaseDataSetOfObjects();
  BaseDataSetOfObjects *newobj1  = (BaseDataSetOfObjects *) popobjectbase->BaseDataObjectExample();
  BaseDataSetOfObjects *newobj2 = (BaseDataSetOfObjects *) popobjectbase->BaseDataObjectExample();
  newobj1->NameTag = SET_NAME1;
  newobj2->NameTag = SET_NAME2;
  set->AddObject(newobj1);
  set->AddObject(newobj2);
  delete newobj1;
  delete newobj2;
  return set;
}
