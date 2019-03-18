/*  FILE     DescriptionProbs.cc
**  PACKAGE  DescriptionProbs
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "DescriptionProbs" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
/*#define DESCRIPTION_DEBUG*/
 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjects.hh"
#include "Vector.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "PredicateObjects.hh"
#include "InstanceAlgorithms.hh"
#include "DescriptionProbs.hh"

/*S Utilities
 */
/*C ProbabilityOfDescription  . . . . .	 description probability for instance
**
**  DESCRIPTION
**    operator()(instanceName):
**    - From the instance i (with instanceName), the value of the description j
**	is given.  The logical value of the description operator is returned.
**	In its usage here, it is considered like a probability.
**
**    The operator for the description is assumed to be:
**      op(Logical*, Instance*,LogicalClass*,InstanceClass*)
**
**  REMARKS
**
*/
class ProbabilityOfDescription
{
  BaseDataSetOfInstances& instances;
  DataInstanceClass* instCls;
  BaseDataOperation *opdescr;
  BaseDataLogical logic;
  DataLogicalClass logclass;
    
public:
  ProbabilityOfDescription(BaseDataOperation *op,
			   BaseDataSetOfInstances& instances,
			   DataSetOfInstancesClass& instsclass)
    : instances(instances),
    opdescr(op)
    {
      instCls = (DataInstanceClass *)
	instsclass.PointerToAllowedClasses()->GetObjectClass(INSTANCE_INSTANCE_NAME);
    }
  double operator()(String& instanceName)
    {
      BaseDataInstance *instance = instances.GetInstance(instanceName);
      opdescr->operator()(&logic,instance,&logclass,instCls);
      double d = logic.GetValue();
      return d;
    }
};
/*C MatrixOfDescriptionProbabilities description probabiltities for instances
**
**  DESCRIPTION
**     operator()(descriptionName,vector):
**     - For each instance, the vector (each element corresponds 
**	 to an instance) of values is filled in (and returned).  This
**       is done through a call to 'ProbabilityOfDescription' call.
**
**  REMARKS
**
*/
class MatrixOfDescriptionProbabilities
{
  BaseDataSetOfInstances& instanceSet;
  DataSetOfInstancesClass& instsclass;
  BaseDataSetOfObjects& descriptions;
  ObjectList<String>& instanceNames;
    
public:
  MatrixOfDescriptionProbabilities(ObjectList<String>& names,
				   BaseDataSetOfObjects& descrs,
				   BaseDataSetOfInstances& instances,
				   DataSetOfInstancesClass& iclss)
    : instanceSet(instances),
    instsclass(iclss),
    descriptions(descrs),
    instanceNames(names)
    {
    }
  VectorNumeric& operator()(String& description,VectorNumeric& values)
    {
      if(descriptions.IsInList(description))
	{
	  BaseDataOperation * opdescr = (BaseDataOperation *) descriptions.GetObject(description);
	  ProbabilityOfDescription calc(opdescr,instanceSet,instsclass);
	  transform(instanceNames.begin(),instanceNames.end(),values.begin(),calc);
	}
      else
	{
	  cerr << "Predicate not in Description list: '" << description << "'" << endl;
	  cerr << "   Values unaffected" << endl;
	}
	
	
      return values;
    }
};
/*F mat = MatrixOfProbsInClusters(instances,instclass)
**
**  DESCRIPTION
**    inames: The names of the instances
**    descrs: The description 
**    instances: The set of instances
**    instsclasses: The set of instance classes
**    
**    A matrix of Probabilities (instances versus description) is set up.
**    The instances are specified by a list of names and the full list
**    of descriptions are used.  This is a help routine.
**
**    This routine calls 'MatrixOfDescriptionProbabilities' operation (through
**    transform) while looping over each description thus filling a row.
**
**  REMARKS
**
*/
MatrixNumeric *MatrixOfProbabilitiesCalc(ObjectList<String>& inames,
					BaseDataSetOfObjects& descrs,
					BaseDataSetOfInstances& instances,
					DataSetOfInstancesClass& instsclass)
{
  ObjectList<String> dnames = descrs.ListOfObjectNames();
  if(instsclass.getDebugLevel() > 2)
    cout << "MatrixOfProbsDescriptionsInClusters: " << dnames.size() << ", " << inames.size() << endl;

  MatrixNumeric matprobs(dnames.size(),inames.size());

  MatrixOfDescriptionProbabilities calc(inames,descrs,instances,instsclass);
  transform(dnames.begin(),dnames.end(),matprobs.begin(),matprobs.begin(),calc);
  MatrixNumeric *trans = new MatrixNumeric(matprobs[0].size(),matprobs.size());
  matprobs.transpose(*trans);
  return trans;
}
/*S BaseDataDescriptionMatrix
 */ 
/*F BaseDataDescriptionMatrix()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDescriptionMatrix::BaseDataDescriptionMatrix()
{
  Identification = DESCRIPTIONPROBS_MAT_ID;
  NameTag = DESCRIPTIONPROBS_MAT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataDescriptionMatrix(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDescriptionMatrix::BaseDataDescriptionMatrix(const BaseDataDescriptionMatrix& data)
  : BaseDataInstanceDoubleMatrix(data)
{
}
/*F BaseDataDescriptionMatrix(mat,insts,attrs)  . . . . . . . . .  initialize
**
**  DESCRIPTION
**    mat: The description matrix
**    insts: The set of instance names
**    attrs: The set of attribute names
**
**  REMARKS
**
*/
BaseDataDescriptionMatrix::BaseDataDescriptionMatrix(MatrixNumeric& mat,
						     BaseDataKeySet& insts,
						     BaseDataKeySet& attrs)
  : BaseDataInstanceDoubleMatrix(mat,insts,attrs)
{
}
/*F BaseDataDescriptionMatrix(mat,insts,attrs)  . . . . . . . . .  initialize
**
**  DESCRIPTION
**    mat: The description matrix
**    insts: The set of instance names
**    attrs: The set of attribute names
**
**  REMARKS
**
*/
BaseDataDescriptionMatrix::BaseDataDescriptionMatrix(MatrixNumeric& mat,
						     BaseDataKeyWords& insts,
						     BaseDataKeyWords& attrs)
  : BaseDataInstanceDoubleMatrix(mat,insts,attrs)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataDescriptionMatrix
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataDescriptionMatrix::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataDescriptionMatrix
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataDescriptionMatrix::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataInstanceDoubleMatrix::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataDescriptionMatrix
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataDescriptionMatrix::print(ostream& out) const
{
  BaseDataInstanceDoubleMatrix::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataDescriptionMatrix
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataDescriptionMatrix::Clone()
{
  BaseDataDescriptionMatrix *obj = new BaseDataDescriptionMatrix;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataDescriptionMatrix
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataDescriptionMatrix::CopyClone(Identify * obj)
{
  BaseDataDescriptionMatrix *objfull = (BaseDataDescriptionMatrix *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDescriptionMatrix
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDescriptionMatrix::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataInstanceDoubleMatrix::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDescriptionMatrix
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDescriptionMatrix::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataInstanceDoubleMatrix::DecodeThis(buffer);
  return result;
}
 
 
/*S DataDescriptionMatrixClass
 */
/*F DataDescriptionMatrixClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDescriptionMatrixClass::DataDescriptionMatrixClass()
{
  Identification = DESCRIPTIONPROBS_MAT_ID;
  NameTag = DESCRIPTIONPROBS_MAT_NAME;
  SubClass = "InstanceDoubleMatrix";
  EncodeDecodeClass = NameTag;
} 
/*F DataDescriptionMatrixClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataDescriptionMatrixClass::DataDescriptionMatrixClass(const DataDescriptionMatrixClass& data)
  : DataInstanceDoubleMatrixClass(data)
{
} 
 
/*F DataDescriptionMatrixClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataDescriptionMatrixClass::DataDescriptionMatrixClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataInstanceDoubleMatrixClass(id,name,descr)
{
  SubClass = "InstanceDoubleMatrix";
  EncodeDecodeClass = DESCRIPTIONPROBS_MAT_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataDescriptionMatrixClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataDescriptionMatrixClass::print(ostream& out) const
{
  DataInstanceDoubleMatrixClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataDescriptionMatrixClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataDescriptionMatrixClass, there is no further information.
**
**  REMARKS
**
*/
bool DataDescriptionMatrixClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataInstanceDoubleMatrixClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataDescriptionMatrixClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataDescriptionMatrixClass::CopyClone(Identify *  objc)
{
  DataDescriptionMatrixClass *objcfull = (DataDescriptionMatrixClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataDescriptionMatrixClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataDescriptionMatrixClass::Clone()
    {
      DataDescriptionMatrixClass* id = new DataDescriptionMatrixClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataDescriptionMatrixClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDescriptionMatrixClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataInstanceDoubleMatrixClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataDescriptionMatrixClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDescriptionMatrixClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataInstanceDoubleMatrixClass::DecodeThis(buffer);
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
BaseDataObject * DataDescriptionMatrixClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataDescriptionMatrix();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataDescriptionMatrixClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataDescriptionMatrixClass*& obj)
     {
     obj = new DataDescriptionMatrixClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataDescriptionMatrix
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataDescriptionMatrix*& obj)
     {
     obj = new BaseDataDescriptionMatrix;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataDescriptionMatrixSetUp
 */ 
/*F BaseDataDescriptionMatrixSetUp()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDescriptionMatrixSetUp::BaseDataDescriptionMatrixSetUp()
  : descrObjectS(DESCRIPTION_MATRIX_NAME)
{
  Identification = DESCRIPTIONPROBS_SETUP_ID;
  NameTag = DESCRIPTIONPROBS_SETUP_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataDescriptionMatrixSetUp(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDescriptionMatrixSetUp::BaseDataDescriptionMatrixSetUp(const BaseDataDescriptionMatrixSetUp& data)
  : BaseDataMatrixSetUp(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataDescriptionMatrixSetUp
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataDescriptionMatrixSetUp::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataDescriptionMatrixSetUp
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataDescriptionMatrixSetUp::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataMatrixSetUp::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataDescriptionMatrixSetUp
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataDescriptionMatrixSetUp::print(ostream& out) const
{
  BaseDataMatrixSetUp::print(out);
  cout << "DescriptionMatrixSetUp:  " << descrObjectS << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataDescriptionMatrixSetUp
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataDescriptionMatrixSetUp::Clone()
{
  BaseDataDescriptionMatrixSetUp *obj = new BaseDataDescriptionMatrixSetUp;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataDescriptionMatrixSetUp
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataDescriptionMatrixSetUp::CopyClone(Identify * obj)
{
  BaseDataDescriptionMatrixSetUp *objfull = (BaseDataDescriptionMatrixSetUp *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDescriptionMatrixSetUp
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDescriptionMatrixSetUp::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMatrixSetUp::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDescriptionMatrixSetUp
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDescriptionMatrixSetUp::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMatrixSetUp::DecodeThis(buffer);
  return result;
}
/*F ans = Calculate(instances,instancesclass,run,runclass)  . . . . algorithm
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
bool BaseDataDescriptionMatrixSetUp::Calculate(BaseDataSetOfInstances* instances,
					       DataSetOfInstancesClass*instsclass,
					       BaseDataAlgorithmRun *,
					       DataAlgorithmRunClass*)
{
  bool result = true;
  ObjectList<String> insts = totalInstanceNameList->GetKeyWords();
  ObjectList<String> attrs = attributeNames->GetKeyWords();
  ObjectList<String>::iterator attr;

  BaseDataSetOfObjects descriptions;
  for(attr = attrs.begin();
      attr != attrs.end();
      attr++) {
      if(instances->IsInList(*attr)) {
	BaseDataObject *descr = instances->GetObject(*attr);
	descriptions.AddObject(descr);
      } else {
	cerr << "Predicate: '" << *attr << "' not found in Attributes" << endl;
	result = false;
      }
    }
  
  if(result) {
    //cout << "MatrixOfProbabilitiesCalc 1" << endl;
    BaseDataKeyWords akeys(descriptions.ListOfObjectNames());

    MatrixNumeric *mat = MatrixOfProbabilitiesCalc(insts,descriptions,*instances,*instsclass);
    matrixObject = new BaseDataDescriptionMatrix(*mat,*totalInstanceNameList,akeys);
    delete mat;
    matrixObject->NameTag = descrObjectS;
    instances->AddObject(matrixObject);
    //cout << "MatrixOfProbabilitiesCalc 2" << endl;
  }
  return result;
}

 
/*S DataDescriptionMatrixSetUpClass
 */
/*F DataDescriptionMatrixSetUpClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDescriptionMatrixSetUpClass::DataDescriptionMatrixSetUpClass()
{
  Identification = DESCRIPTIONPROBS_SETUP_ID;
  NameTag = DESCRIPTIONPROBS_SETUP_NAME;
  SubClass = "MatrixSetUp";
  EncodeDecodeClass = NameTag;
} 
/*F DataDescriptionMatrixSetUpClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataDescriptionMatrixSetUpClass::DataDescriptionMatrixSetUpClass(const DataDescriptionMatrixSetUpClass& data)
  : DataMatrixSetUpClass(data)
{
} 
 
/*F DataDescriptionMatrixSetUpClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataDescriptionMatrixSetUpClass::DataDescriptionMatrixSetUpClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataMatrixSetUpClass(id,name,descr)
{
  SubClass = "MatrixSetUp";
  EncodeDecodeClass = DESCRIPTIONPROBS_SETUP_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataDescriptionMatrixSetUpClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataDescriptionMatrixSetUpClass::print(ostream& out) const
{
  out << "\nDataDescriptionMatrixSetUpClass\n";
  DataMatrixSetUpClass::print(out);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataDescriptionMatrixSetUpClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataDescriptionMatrixSetUpClass, there is no further information.
**
**  REMARKS
**
*/
bool DataDescriptionMatrixSetUpClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataMatrixSetUpClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataDescriptionMatrixSetUpClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataDescriptionMatrixSetUpClass::CopyClone(Identify *  objc)
{
  DataDescriptionMatrixSetUpClass *objcfull = (DataDescriptionMatrixSetUpClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataDescriptionMatrixSetUpClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataDescriptionMatrixSetUpClass::Clone()
    {
      DataDescriptionMatrixSetUpClass* id = new DataDescriptionMatrixSetUpClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataDescriptionMatrixSetUpClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDescriptionMatrixSetUpClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataMatrixSetUpClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataDescriptionMatrixSetUpClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDescriptionMatrixSetUpClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataMatrixSetUpClass::DecodeThis(buffer);
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
BaseDataObject * DataDescriptionMatrixSetUpClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataDescriptionMatrixSetUp();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataDescriptionMatrixSetUpClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataDescriptionMatrixSetUpClass*& obj)
     {
     obj = new DataDescriptionMatrixSetUpClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataDescriptionMatrixSetUp
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataDescriptionMatrixSetUp*& obj)
     {
     obj = new BaseDataDescriptionMatrixSetUp;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataDetermineMembershipByTrying
 */ 
/*F BaseDataDetermineMembershipByTrying()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDetermineMembershipByTrying::BaseDataDetermineMembershipByTrying()
  : BelongsInGroupMeasure(NULL),
    nodeInGroup(NULL),
    nodeNotInGroup(NULL),
    instanceCountOnGroup(NULL),
    descriptionOverAllGroups(NULL)
    
{
  Identification = DESCRIPTIONPROBS_MEMBERSHIP_ID;
  NameTag = DESCRIPTIONPROBS_MEMBERSHIP_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataDetermineMembershipByTrying(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDetermineMembershipByTrying::BaseDataDetermineMembershipByTrying(const BaseDataDetermineMembershipByTrying& data)
  : BaseDataDescriptionMatrix(data),
    BelongsInGroupMeasure(NULL),
    nodeInGroup(NULL),
    nodeNotInGroup(NULL),
    instanceCountOnGroup(NULL),
    descriptionOverAllGroups(NULL)
{
}
/*F BaseDataDetermineMembershipByTrying(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDetermineMembershipByTrying::BaseDataDetermineMembershipByTrying(const BaseDataDescriptionMatrix& data)
  : BaseDataDescriptionMatrix(data),
    BelongsInGroupMeasure(NULL),
    nodeInGroup(NULL),
    nodeNotInGroup(NULL),
    instanceCountOnGroup(NULL),
    descriptionOverAllGroups(NULL)
{
}
/*F ~BaseDataDetermineMembershipByTrying()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDetermineMembershipByTrying::~BaseDataDetermineMembershipByTrying()
{
  if(BelongsInGroupMeasure != NULL)
    delete BelongsInGroupMeasure;
  if(nodeInGroup != NULL)
    delete nodeInGroup;
  if(nodeNotInGroup != NULL)
    delete nodeNotInGroup;
  if(instanceCountOnGroup != NULL)
    delete instanceCountOnGroup;
  if(descriptionOverAllGroups != NULL)
    delete descriptionOverAllGroups;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataDetermineMembershipByTrying
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataDetermineMembershipByTrying::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataDetermineMembershipByTrying
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataDetermineMembershipByTrying::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataDescriptionMatrix::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataDetermineMembershipByTrying
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataDetermineMembershipByTrying::print(ostream& out) const
{
  out << "\n====================================================\n";
  out << "DescriptionMatrix\n";
  BaseDataDescriptionMatrix::print(out);
  out << "\n====================================================\n";
  out << "NewInstanceProbabilities\n";
  NewInstanceDescrProbabilities.print(out);
  out << "\n====================================================\n";
  out << "GroupDescriptionProbabilities\n";
  GroupDescrProbabilities.print(out);
  out << "\n====================================================\n";
  out << "Counts: (Groups, Descriptions, Instance) = (";
  out << numGroups << " " << numDescriptions << " " << totalNumberOfInstances << ")";
  if(instanceCountOnGroup != NULL)
    {
      out << "\n====================================================\n";
      out << "Instance Count on each group\n";
      instanceCountOnGroup->print(out);
    }
  if(descriptionOverAllGroups != NULL)
    {
      out << "\n====================================================\n";
      out << "Description probabilities over all Groups\n";
      descriptionOverAllGroups->print(out);
    }
  if(nodeInGroup != NULL)
    {
      out << "\n====================================================\n";
      out << "Preprocessing: Node in group\n";
      nodeInGroup->print(out);
    }
  if(nodeNotInGroup != NULL)
    {
      out << "\n====================================================\n";
      out << "Preprocessing: Node not in group\n";
      nodeNotInGroup->print(out);
    }
  if(totalDescriptionProbs != NULL)
    {
      out << "\n====================================================\n";
      out << "Total Description Probabilities Squared\n";
      totalDescriptionProbs->print(out);
      out << endl << "Total Sum Squared: " << totalDescriptionProbSquared << endl;
    }
  if(BelongsInGroupMeasure != NULL)
    {
      out << "\n====================================================\n";
      out << "Measures for groups\n";
      BelongsInGroupMeasure->print(out);
      out << "\nMeasure if isolated group: " << BelongsInExtraGroupMeasure << endl;
    }
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataDetermineMembershipByTrying
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataDetermineMembershipByTrying::Clone()
{
  BaseDataDetermineMembershipByTrying *obj = new BaseDataDetermineMembershipByTrying;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataDetermineMembershipByTrying
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataDetermineMembershipByTrying::CopyClone(Identify * obj)
{
  BaseDataDetermineMembershipByTrying *objfull = (BaseDataDetermineMembershipByTrying *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDetermineMembershipByTrying
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDetermineMembershipByTrying::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataDescriptionMatrix::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDetermineMembershipByTrying
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDetermineMembershipByTrying::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataDescriptionMatrix::DecodeThis(buffer);
  // The rest

  return result;
}
 
/*F setGroupProbabilities(probs)  . . . . BaseDataDetermineMembershipByTrying
**
**  DESCRIPTION
**    probs: description probabilities (groups versus descriptions) 
**
**  REMARKS
**
*/
void BaseDataDetermineMembershipByTrying::setGroupProbabilities(MatrixNumeric& probs)
{
  GroupInstanceProbabilities = probs;
}
 
/*F setNewInstance(newinstanceprobs)  . BaseDataDetermineMembershipByTrying::
**
**  DESCRIPTION
**    newinstanceprobs: Description probabilities for a single instance
**
**  REMARKS
**
*/
void BaseDataDetermineMembershipByTrying::setNewInstance(VectorNumeric& newinstanceprobs,
							 double membership)
{
  NewInstanceDescrProbabilities = newinstanceprobs;
  newInstanceMembership = membership;
}
 
/*F measure = getBelongsInGroupMeasurePointer() BaseDataDetermineMembershipByTrying
**
**  DESCRIPTION
**    measure: A vector (over the groups) of measures of how the instance fits in group
**
**  REMARKS
**
*/
VectorNumeric *BaseDataDetermineMembershipByTrying::getBelongsInGroupMeasurePointer()
{
  return BelongsInGroupMeasure;
}
 
/*F extragrp = getBelongsInExtraGroupMeasure()BaseDataDetermineMembershipByTrying
**
**  DESCRIPTION
**    extragrp: The measure when the extra
**
**  REMARKS
**
*/ 
double BaseDataDetermineMembershipByTrying::getBelongsInExtraGroupMeasure()
{
  return BelongsInExtraGroupMeasure;
}
 
/*F TotalDescriptionOverAllGroups() . . . . . . . . .  total description prob
**
**  DESCRIPTION
**   descriptionOverAllGroups: The matrix of node versus description probabilities
**    NewInstanceDescrProbabilities: description probs for new instance
**
**   descriptionOverAllGroups: P(D) (summed over all the nodes of this level)
**
**   The description probabilities are summed over all nodes 
**   and the new instance to give the total probability
**   of the description at this level.
**
**  REMARKS
**
*/
void BaseDataDetermineMembershipByTrying::TotalDescriptionOverAllSons()
{
  descriptionOverAllGroups = new VectorNumeric(numDescriptions);
  for(unsigned int description=0; description<numDescriptions;description++)
    {
      (*descriptionOverAllGroups)[description] = NewInstanceDescrProbabilities[description] * newInstanceMembership;
      for(unsigned int node = 0;node < numGroups; node++)
	{
	  (*descriptionOverAllGroups)[description] += GroupDescrProbabilities[node][description];
	}
    }
}
/*F best = getBestGroup() . . . . . . . . BaseDataDetermineMembershipByTrying
**
**  DESCRIPTION
**    best: The best node (-1 if should be alone)
**
**  REMARKS
**
*/
int BaseDataDetermineMembershipByTrying::getBestGroup()
{
  int node = -1;
  double best = BelongsInExtraGroupMeasure;
  for(unsigned int i=0; i < numGroups; i++)
    {
      if(best < (*BelongsInGroupMeasure)[i])
	{
	  best = (*BelongsInGroupMeasure)[i];
	  node = i;
	}
    }
  return node;
}
 
/*F counts = GroupInstanceCount()
**
**  DESCRIPTION
**    GroupDescrProbabilities: The matrix of counts (groups versus description)
**    instanceCountOnGroup: The vector of instance counts
**
**    This calculates the sum over all descriptions
**
**  REMARKS
**
*/
void BaseDataDetermineMembershipByTrying::GroupInstanceCount()
{
  instanceCountOnGroup = new VectorNumeric(numGroups);
  unsigned int num = GroupInstanceProbabilities[0].size();
  for(unsigned int icount = 0;icount < numGroups;icount++)
    {
      (*instanceCountOnGroup)[icount] = 0.0;
      for(unsigned int jcount = 0;jcount < num;jcount++)
	{
	  (*instanceCountOnGroup)[icount] += GroupInstanceProbabilities[icount][jcount];
	}
    }
}
/*F TotalNumberOfInstances()  . . . . . . BaseDataDetermineMembershipByTrying
**
**  DESCRIPTION
**    Compute 'totalNumberOfInstances'
**
**  REMARKS
**
*/
void BaseDataDetermineMembershipByTrying::TotalNumberOfInstances()
{
  totalNumberOfInstances = newInstanceMembership;
  for(unsigned int node = 0;node < numGroups; node++)
    {
      totalNumberOfInstances += (*instanceCountOnGroup)[node];
    }
  //totalNumberOfInstances = CurrentMatrix().size() +  newInstanceMembership;
}
/*F GroupMeasuresPreprocessing()  . . . . BaseDataDetermineMembershipByTrying
**
**  DESCRIPTION
**      nodeprobwith: The probability that an instance is on this node 
**                    (calculated with extra instance) - P(node)
**      nodeprobwithout: The probability that an instance is on this node 
**                    (calculated without extra instance) P(node)
**      nodeInGroup, nodeNotInGroup: The partial measures with the new instance
**                                 added to the group and not added are calculated.
**
**      A loop is made over all descriptions:
**	- nodewith,nodewithout: Probability of description on node P(D|C)
**      - topprobdescr: The probability that description over all groups P(D)
**      - Sum: P(node)*( P(D|C)^2 ) - ( P(D)^2 )
**
**  REMARKS
**
*/
void BaseDataDetermineMembershipByTrying::GroupMeasuresPreprocessing()
{
  double extraprob = newInstanceMembership/totalNumberOfInstances;
  for(unsigned int node = 0;node < numGroups; node++)
    {
      (*nodeInGroup)[node] = 0.0;
      (*nodeNotInGroup)[node] = 0.0;

      double nodeprobwith = ((*instanceCountOnGroup)[node] + newInstanceMembership)/totalNumberOfInstances;
      double nodeprobwithout = ((*instanceCountOnGroup)[node])/totalNumberOfInstances;

      BelongsInExtraGroupMeasure = 0.0;
      #ifdef DESCRIPTION_DEBUG
      cout << "Node Loop: " << node << endl;
      cout << "Probability of Node: (with and without) " << nodeprobwith << " " << nodeprobwithout << endl;
      #endif
      
      for(unsigned int description=0; description<numDescriptions;description++)
	{
	  double nodewithout = GroupDescrProbabilities[node][description]/(*instanceCountOnGroup)[node];
	  double nodewith    = GroupDescrProbabilities[node][description] 
	    + NewInstanceDescrProbabilities[description]*newInstanceMembership;
	  nodewith /= ((*instanceCountOnGroup)[node] + newInstanceMembership);

	  (*nodeNotInGroup)[node] += nodeprobwithout*nodewithout*nodewithout;
	  (*nodeInGroup)[node] += nodeprobwith*nodewith*nodewith;
	  
	  double descr = NewInstanceDescrProbabilities[description]*newInstanceMembership;
	  BelongsInExtraGroupMeasure += extraprob*descr*descr;
          #ifdef DESCRIPTION_DEBUG
	  cout << "Description Loop:" << description << endl;
	  cout << "Probabilitiy of Description on Node (with and without) " << " " << nodewith << " " << nodewithout << endl;
	  #endif
	}
    }
}

/*F ComputeTotalDescriptionProbs()
**
**  DESCRIPTION
**    
**    totalDescriptionProbs:  Allocated and computed for each node.
**         Uses descriptionOverAllGroups vector
**      totalDescriptionProbSquared: computed in ComputeTotalDescriptionProbs()
**         used in ComputeAsOnACluster(), ComputeAsExtraCluster()
**  REMARKS
**
*/
void BaseDataDetermineMembershipByTrying::ComputeTotalDescriptionProbs()
{
  totalDescriptionProbs = new VectorNumeric(numDescriptions);
  totalDescriptionProbSquared = 0.0;

  for(unsigned int description=0; description<numDescriptions;description++)
    {
      (*totalDescriptionProbs)[description] = (*descriptionOverAllGroups)[description]/totalNumberOfInstances;
      totalDescriptionProbSquared += (*totalDescriptionProbs)[description]*(*totalDescriptionProbs)[description];
    }
}
  
/*F ComputeAsOnACluster()
**
**  DESCRIPTION
**    nodemeasure: The summed probabilties
**    nodemeasurewith: Probablility on each node (with instance added)
**    nodemeasurewithout: Probability on each node (without instance)
**
**    
**  REMARKS
**
*/
void BaseDataDetermineMembershipByTrying::ComputeAsOnACluster()
{
  double fnumnodes = (double) numGroups;
  
  double total = 0.0;
  for(unsigned int node1=0;node1 < numGroups; node1++)
    {
      total += (*nodeNotInGroup)[node1];
    }
  total = total - totalDescriptionProbSquared;
  for(unsigned int node=0;node < numGroups; node++)
    {
      (*BelongsInGroupMeasure)[node] = total + ((*nodeInGroup)[node] - (*nodeNotInGroup)[node]);
      (*BelongsInGroupMeasure)[node] /= fnumnodes;
    }
}
/*F ComputeAsExtraCluster()
**
**  DESCRIPTION
**    NewInstanceDescrProbabilities:	 The instance description
**    fnumnodes: The number of nodes as a double
**
**    This sums the node measures of those 'without' the extra instance
**    and adds to it the sum of the descriptions
**
**  REMARKS
**
*/
void BaseDataDetermineMembershipByTrying::ComputeAsExtraCluster()
{
  #ifdef DESCRIPTION_DEBUG
  cout << "ComputeAsExtraCluster()" << endl;
  cout << "BelongsInExtraGroupMeasure: " << BelongsInExtraGroupMeasure << endl;
  #endif

  plus<double> p;
  double without 
    = accumulate((*nodeNotInGroup).begin(),(*nodeNotInGroup).end(),0.0,p);
  double fnumnodes     = (double) numGroups;
  without = without - totalDescriptionProbSquared;
  BelongsInExtraGroupMeasure += without;
  BelongsInExtraGroupMeasure /= (fnumnodes+newInstanceMembership);
  #ifdef DESCRIPTION_DEBUG
  cout << "BelongsInExtraGroupMeasure, without: " << BelongsInExtraGroupMeasure << ", " << without << endl;
  #endif
}
/*F CalculateNewInstanceMembership()
**
**  DESCRIPTION
**    The measures for determining the best node on 
**    which to put the instance are calculated:
**    - BelongsInGroupMeasure: The measure if instance is in the
**                             corresponding group
**    - BelongsInExtraGroupMeasure: The measure if the instance
**                             is in a group by itself.
**    These must be deallocated when they are put into the 
**      output parameters.
**    
**    totalDescriptionProbs:  Allocated in ComputeTotalDescriptionProbs()
**         and filled in.  Uses descriptionOverAllGroups
**     totalDescriptionProbSquared: computed in ComputeTotalDescriptionProbs()
**         used in ComputeAsOnACluster(), ComputeAsExtraCluster()
**  REMARKS
**
*/
void BaseDataDetermineMembershipByTrying::CalculateNewInstanceMembership()
{
  GroupDescrProbabilities = GroupInstanceProbabilities * CurrentMatrix();
  numGroups = GroupDescrProbabilities.size();
  numDescriptions = GroupDescrProbabilities[0].size();
  // Allocates descriptionOverAllGroups
  TotalDescriptionOverAllSons();
  // Allocates instanceCountOnGroup
  GroupInstanceCount();
  TotalNumberOfInstances();
  // fills in 
  nodeInGroup = new VectorNumeric(numGroups);
  nodeNotInGroup = new VectorNumeric(numGroups);
  GroupMeasuresPreprocessing();
  // Creates
  ComputeTotalDescriptionProbs();  
  BelongsInGroupMeasure = new VectorNumeric(numGroups);
  // fills in BelongsInGroupMeasure vector for each node
  ComputeAsOnACluster();
  // fills in BelongsInExtraGroupMeasure
  ComputeAsExtraCluster();
  // Deallocate intermediate quantities
  delete nodeInGroup;
  nodeInGroup = NULL;
  delete nodeNotInGroup;
  nodeNotInGroup = NULL;
  //delete GroupDescrProbabilities;
  //GroupDescrProbabilities = NULL;
  delete descriptionOverAllGroups;
  descriptionOverAllGroups = NULL;
  delete instanceCountOnGroup;
  instanceCountOnGroup = NULL;
}

/*S DataDetermineMembershipByTryingClass
 */
/*F DataDetermineMembershipByTryingClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDetermineMembershipByTryingClass::DataDetermineMembershipByTryingClass()
{
  Identification = DESCRIPTIONPROBS_MEMBERSHIP_ID;
  NameTag = DESCRIPTIONPROBS_MEMBERSHIP_NAME;
  SubClass = "DescriptionMatrix";
  EncodeDecodeClass = NameTag;
} 
/*F DataDetermineMembershipByTryingClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataDetermineMembershipByTryingClass::DataDetermineMembershipByTryingClass(const DataDetermineMembershipByTryingClass& data)
  : DataDescriptionMatrixClass(data)
{
} 
/*F DataDetermineMembershipByTryingClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataDetermineMembershipByTryingClass::DataDetermineMembershipByTryingClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataDescriptionMatrixClass(id,name,descr)
{
  SubClass = "DescriptionMatrix";
  EncodeDecodeClass = DESCRIPTIONPROBS_MEMBERSHIP_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataDetermineMembershipByTryingClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataDetermineMembershipByTryingClass::print(ostream& out) const
{
  DataDescriptionMatrixClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataDetermineMembershipByTryingClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataDetermineMembershipByTryingClass, there is no further information.
**
**  REMARKS
**
*/
bool DataDetermineMembershipByTryingClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataDescriptionMatrixClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataDetermineMembershipByTryingClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataDetermineMembershipByTryingClass::CopyClone(Identify *  objc)
{
  DataDetermineMembershipByTryingClass *objcfull = (DataDetermineMembershipByTryingClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataDetermineMembershipByTryingClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataDetermineMembershipByTryingClass::Clone()
    {
      DataDetermineMembershipByTryingClass* id = new DataDetermineMembershipByTryingClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataDetermineMembershipByTryingClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDetermineMembershipByTryingClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataDescriptionMatrixClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataDetermineMembershipByTryingClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDetermineMembershipByTryingClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataDescriptionMatrixClass::DecodeThis(buffer);
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
BaseDataObject * DataDetermineMembershipByTryingClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataDetermineMembershipByTrying();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataDetermineMembershipByTryingClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataDetermineMembershipByTryingClass*& obj)
     {
     obj = new DataDetermineMembershipByTryingClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataDetermineMembershipByTrying
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataDetermineMembershipByTrying*& obj)
     {
     obj = new BaseDataDetermineMembershipByTrying;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataCobwebBestGroup
 */ 
/*F BaseDataCobwebBestGroup()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataCobwebBestGroup::BaseDataCobwebBestGroup()
  : InstanceDescrProbsS(COBWEB_BEST_GROUP_DESCR),
    GroupProbsS(COBWEB_BEST_GROUP_GROUPPROBS),
    SingleDescriptionS(COBWEB_BEST_GROUP_SINGLE),
    SingleMembershipS(COBWEB_BEST_GROUP_MEMBERSHIP),
    InGroupMeasureS(COBWEB_BEST_GROUP_INGROUP),
    ExtraGroupMeasureS(COBWEB_BEST_GROUP_EXTRAGROUP)
{
  Identification = DESCRIPTIONPROBS_COBWEB_ID;
  NameTag = DESCRIPTIONPROBS_COBWEB_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataCobwebBestGroup(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataCobwebBestGroup::BaseDataCobwebBestGroup(const BaseDataCobwebBestGroup& data)
  : BaseDataAlgorithmOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataCobwebBestGroup
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataCobwebBestGroup::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataCobwebBestGroup
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataCobwebBestGroup::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataCobwebBestGroup
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataCobwebBestGroup::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataCobwebBestGroup
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataCobwebBestGroup::Clone()
{
  BaseDataCobwebBestGroup *obj = new BaseDataCobwebBestGroup;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataCobwebBestGroup
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataCobwebBestGroup::CopyClone(Identify * obj)
{
  BaseDataCobwebBestGroup *objfull = (BaseDataCobwebBestGroup *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataCobwebBestGroup
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataCobwebBestGroup::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataCobwebBestGroup
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataCobwebBestGroup::DecodeThis(CommBuffer& buffer)
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
bool BaseDataCobwebBestGroup::SetUpAlgorithms(BaseDataSetOfInstances*,
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
bool BaseDataCobwebBestGroup::CheckInput(BaseDataSetOfInstances*,
						 DataSetOfInstancesClass*,
						 BaseDataAlgorithmRun *run,
						 DataAlgorithmRunClass*)
{
  bool result = true;

  if(run->ParameterInList(InstanceDescrProbsS))
    {
      if(run->ParameterInList(GroupProbsS))
	{
	  if(run->ParameterInList(SingleDescriptionS))
	    {
	      if(!run->ParameterInList(SingleMembershipS))
		{
		  cerr << "The parameter '" << SingleMembershipS << "' was not in the list of parameters" << endl;
		  result = false;
		}
	    }
	  else
	    {
	      cerr << "The parameter '" << SingleDescriptionS << "' was not in the list of parameters" << endl;
	      result = false;
	    }
	}
      else
	{
	  cerr << "The parameter '" << GroupProbsS << "' was not in the list of parameters" << endl;
	  result = false;
	}
    }
  else
    {
      cerr << "The parameter '" << InstanceDescrProbsS << "' was not in the list of parameters" << endl;
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
bool BaseDataCobwebBestGroup::SetUpInput(BaseDataSetOfInstances* instances,
						 DataSetOfInstancesClass* instancesclass,
						 BaseDataAlgorithmRun *run,
						 DataAlgorithmRunClass* rclass)
{
  bool result = true;

  InstanceDescrProbs = (BaseDataDescriptionMatrix *) run->ParameterValue(InstanceDescrProbsS);
  GroupProbs  = (BaseDataInstanceDoubleMatrix *) run->ParameterValue(GroupProbsS);
  SingleDescription = (BaseDataInstanceDoubleVector *) run->ParameterValue(SingleDescriptionS);
  SingleMembership = (BaseDataReal *) run->ParameterValue(SingleMembershipS);
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
bool BaseDataCobwebBestGroup::Calculate(BaseDataSetOfInstances*,
						DataSetOfInstancesClass*,
						BaseDataAlgorithmRun*,
						DataAlgorithmRunClass *run)
{
  bool result = true;
  Calc = new BaseDataDetermineMembershipByTrying(*InstanceDescrProbs);
  Calc->setGroupProbabilities(GroupProbs->CurrentMatrix());
  Calc->setNewInstance(SingleDescription->CurrentVector(),SingleMembership->GetValue());
  Calc->CalculateNewInstanceMembership();

  if(run->getDebugLevel() > 2)
    Calc->print(cout);

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
bool BaseDataCobwebBestGroup::WriteOutputValues(BaseDataSetOfInstances*,
						DataSetOfInstancesClass*,
						BaseDataAlgorithmRun* run,
						DataAlgorithmRunClass*)
{
  bool result = true;

  BaseDataDoubleVector vec(*(Calc->getBelongsInGroupMeasurePointer()));
  vec.NameTag = InGroupMeasureS;

  BaseDataReal extra;
  extra.SetValue(Calc->getBelongsInExtraGroupMeasure());
  extra.NameTag = ExtraGroupMeasureS;
  
  run->AddParameter(&vec);
  run->AddParameter(&extra);
  
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
bool BaseDataCobwebBestGroup::ConcludeRun(BaseDataSetOfInstances*,
						  DataSetOfInstancesClass*,
						  BaseDataAlgorithmRun*,
						  DataAlgorithmRunClass*)
{
  bool result = true;
  delete Calc;
  return result;
}
 

 
/*S DataCobwebBestGroupClass
 */
/*F DataCobwebBestGroupClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataCobwebBestGroupClass::DataCobwebBestGroupClass()
{
  Identification = DESCRIPTIONPROBS_COBWEB_ID;
  NameTag = DESCRIPTIONPROBS_COBWEB_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataCobwebBestGroupClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataCobwebBestGroupClass::DataCobwebBestGroupClass(const DataCobwebBestGroupClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataCobwebBestGroupClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataCobwebBestGroupClass::DataCobwebBestGroupClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = DESCRIPTIONPROBS_COBWEB_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataCobwebBestGroupClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataCobwebBestGroupClass::print(ostream& out) const
{
  out << "\nDataCobwebBestGroupClass\n";
  DataAlgorithmOperationClass::print(out);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataCobwebBestGroupClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataCobwebBestGroupClass, there is no further information.
**
**  REMARKS
**
*/
bool DataCobwebBestGroupClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataCobwebBestGroupClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataCobwebBestGroupClass::CopyClone(Identify *  objc)
{
  DataCobwebBestGroupClass *objcfull = (DataCobwebBestGroupClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataCobwebBestGroupClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataCobwebBestGroupClass::Clone()
    {
      DataCobwebBestGroupClass* id = new DataCobwebBestGroupClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataCobwebBestGroupClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataCobwebBestGroupClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataCobwebBestGroupClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataCobwebBestGroupClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataCobwebBestGroupClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataCobwebBestGroup();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataCobwebBestGroupClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataCobwebBestGroupClass*& obj)
     {
     obj = new DataCobwebBestGroupClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataCobwebBestGroup
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataCobwebBestGroup*& obj)
     {
     obj = new BaseDataCobwebBestGroup;
     return obj->DecodeThis(buffer);
     }


/*S Utilities
 */
/*F AddDescriptionProbsClasses(set) . . . . . . . .  basic algorithm data types
**
**  DESCRIPTION
**    set: The set of data types
**
**  REMARKS
**
*/
void AddDescriptionProbsClasses(DataSetOfObjectsClass& set)
{
  String matdescr("Description Probability Matrix Class");
  String setupdescr("Description Probability Set up");
  String cobwebdescr("Group Selection By Cobweb Measure");

  DataDescriptionMatrixClass matclass(DESCRIPTIONPROBS_MAT_ID,DESCRIPTIONPROBS_MAT_NAME,matdescr);
  DataDescriptionMatrixSetUpClass setupclass(DESCRIPTIONPROBS_SETUP_ID,DESCRIPTIONPROBS_SETUP_NAME,setupdescr);
  DataCobwebBestGroupClass cobwebclass(DESCRIPTIONPROBS_COBWEB_ID,DESCRIPTIONPROBS_COBWEB_NAME,cobwebdescr);
  
  set.AddObjectClass(matclass);
  set.AddObjectClass(setupclass);
  set.AddObjectClass(cobwebclass);
}
/*F InitialDescriptionProbsEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialDescriptionProbsEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataDescriptionMatrixClass,BaseDataDescriptionMatrix,DESCRIPTIONPROBS_MAT_NAME);
  EncodeDecodeRegisterClass(DataDescriptionMatrixSetUpClass,BaseDataDescriptionMatrixSetUp,DESCRIPTIONPROBS_SETUP_NAME);
  EncodeDecodeRegisterClass(DataCobwebBestGroupClass,BaseDataCobwebBestGroup,DESCRIPTIONPROBS_COBWEB_NAME);
//  bool (*toproutine)(CommBuffer&,Identify*&);
//
//  bool (*rout1)(CommBuffer&,DataDescriptionMatrixClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout1;
//  SingleDecodeRoutine p1(DESCRIPTIONPROBS_MAT_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p1.StructureName] = p1;
//
//  bool (*rout2)(CommBuffer&,DataDescriptionMatrixSetUpClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout2;
//  SingleDecodeRoutine p2(DESCRIPTIONPROBS_SETUP_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p2.StructureName] = p2;
//
//  bool (*rout3)(CommBuffer&,DataCobwebBestGroupClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout3;
//  SingleDecodeRoutine p3(DESCRIPTIONPROBS_COBWEB_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p3.StructureName] = p3;
//
//  String s1("Object.");
//  String s11(DESCRIPTIONPROBS_MAT_NAME);
//  s1.AppendToEnd(s11);
//  bool (*rout11)(CommBuffer&,BaseDataDescriptionMatrix*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout11;
//  SingleDecodeRoutine p11(s1,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p11.StructureName] = p11;
//
//  String s2("Object.");
//  String s22(DESCRIPTIONPROBS_SETUP_NAME);
//  s2.AppendToEnd(s22);
//  bool (*rout22)(CommBuffer&,BaseDataDescriptionMatrixSetUp*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout22;
//  SingleDecodeRoutine p22(s2,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p22.StructureName] = p22;
//
//  String s3("Object.");
//  String s33(DESCRIPTIONPROBS_COBWEB_NAME);
//  s3.AppendToEnd(s33);
//  bool (*rout33)(CommBuffer&,BaseDataCobwebBestGroup*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout33;
//  SingleDecodeRoutine p33(s3,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p33.StructureName] = p33;

}
