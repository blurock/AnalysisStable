/*  FILE     Optimize.cc
**  PACKAGE  Optimize
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "Optimize" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjects.hh"
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
#include "Optimize.hh"

/*S BaseDataOptimizeCostFunction
 */ 
/*F BaseDataOptimizeCostFunction()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataOptimizeCostFunction::BaseDataOptimizeCostFunction()
  : Parameters(NULL),
    OptimizeObject(NULL),
    CurrentCost(NULL),
    IterationCount(0)
{
  Identification = OPTCOST_OPTIMIZE_ID;
  NameTag = OPTCOST_OPTIMIZE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataOptimizeCostFunction(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataOptimizeCostFunction::BaseDataOptimizeCostFunction(const BaseDataOptimizeCostFunction& data)
  : BaseDataOperation(data),
    IterationCount(data.IterationCount)
{
  Parameters = (BaseDataSetOfObjects *) PointerClone(data.Parameters);
  OptimizeObject = PointerClone(data.OptimizeObject);
  CurrentCost = PointerClone(data.CurrentCost);
}
 
/*F ~BaseDataOptimizeCostFunction() . . . . . . . . . . . . . . .  destructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataOptimizeCostFunction::~BaseDataOptimizeCostFunction()
{
  if(Parameters != NULL)
    delete Parameters;
  if(OptimizeObject != NULL)
    delete OptimizeObject;
  if(CurrentCost != NULL)
    delete CurrentCost;
}


/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataOptimizeCostFunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataOptimizeCostFunction::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataOptimizeCostFunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataOptimizeCostFunction::Read(istream& in, DataObjectClass* objc, const String& name)
{
  cout << "Read in OptimizeCostFunction" << endl;
  bool result = BaseDataOperation::Read(in,objc,name);
  
  StreamObjectInput str(in,' ');
  String tag = str.ReadNext();
  if(tag == "CostFunction:")
    {
      cout << "Read in OptimizeCostFunction  1" << endl;
      DataOptimizeCostFunctionClass *costclass = (DataOptimizeCostFunctionClass *) objc;
      cout << "Read in OptimizeCostFunction  2" << endl;
      DataSetOfObjectsClass *parclass = costclass->getParameterClass();
      cout << "Read in OptimizeCostFunction  3" << endl;
      Parameters = (BaseDataSetOfObjects *) parclass->BaseDataObjectExample();
      cout << "Reading in Optimize Parameters of type: '" << parclass->NameTag << "'" << endl;
      Parameters->Read(in,parclass,name);
    }
  else
    {
      cerr << "Expected the tag 'CostFunction:' got '" << tag << "' instead" << endl;
      result = false;
    }
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataOptimizeCostFunction
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataOptimizeCostFunction::print(ostream& out) const
{
  BaseDataOperation::print(out);
  out << endl;
  out << "The Number of Iterations: " << IterationCount << endl;
  PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  out << endl;
  PointerPrint(out,"The Current Object: ","No Object to Optimize",OptimizeObject);
  out << endl;
  PointerPrint(out,"The Current Cost: ","No Cost Calculated",CurrentCost);
  out << endl;
  
   
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataOptimizeCostFunction
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataOptimizeCostFunction::Clone()
{
  BaseDataOptimizeCostFunction *obj = new BaseDataOptimizeCostFunction(*this);
  return obj;
}
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataOptimizeCostFunction
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataOptimizeCostFunction::CopyClone(Identify * obj)
{
  BaseDataOptimizeCostFunction *objfull = (BaseDataOptimizeCostFunction *) obj;
  
  *this = *objfull;
  Parameters = (BaseDataSetOfObjects *) PointerClone(objfull->Parameters);
  OptimizeObject = PointerClone(objfull->OptimizeObject);
  CurrentCost = PointerClone(objfull->CurrentCost);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataOptimizeCostFunction
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataOptimizeCostFunction::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  result = result && PointerEncode(buffer,Parameters);
  result = result && PointerEncode(buffer,OptimizeObject);
  result = result && PointerEncode(buffer,CurrentCost);
  result = result && Encode(buffer,IterationCount);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataOptimizeCostFunction
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataOptimizeCostFunction::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Parameters);
  result = result && PointerDecode(buffer,(BaseDataObject *&) OptimizeObject);
  result = result && PointerDecode(buffer,(BaseDataObject *&) CurrentCost);
  result = result && Decode(buffer,IterationCount);
  return result;
}
/*F InitializeParameters(instances,instclass,run,runclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataOptimizeCostFunction::InitializeParameters(DataOptimizeCostFunctionClass *costclass,
							BaseDataSetOfInstances*,
							DataSetOfInstancesClass*)
{
  if(Parameters != NULL)
    delete Parameters;

  Parameters = ExtractParameters(costclass);
  ResultWithParameters = false;
}
/*F parameters = ExtractParameters()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSetOfObjects *BaseDataOptimizeCostFunction::ExtractParameters(DataOptimizeCostFunctionClass *costclass)
{
  BaseDataSetOfObjects *parameters = NULL;
  if(Parameters != NULL)
    {
      parameters = Parameters;
    }
  else
    {
      cout << "BaseDataOptimizeCostFunction::ExtractParameters: Create a new set of parameters" << endl;
      DataSetOfObjectsClass *objclass = (DataSetOfObjectsClass *) costclass->getParameterClass();
      if(objclass != NULL)
	{
	  parameters = (BaseDataSetOfObjects *) objclass->BaseDataObjectExample();
	}
      else
	{
	  cerr << " ExtractParameters: Cost Function Class not specified" << endl;
	}
    }
  return parameters;
}
/*F InsertParameters(parameters)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataOptimizeCostFunction::InsertParameters(BaseDataSetOfObjects *parameters)
{
  if(Parameters != parameters)
    {
      if(Parameters != NULL)
	delete Parameters;
      Parameters = parameters;
    }
}
/*F object = operator()(instance,instclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataObject *BaseDataOptimizeCostFunction::operator()(DataObjectClass *objclass,
							 BaseDataObject *x,
							 DataObjectClass *xclass)
{
  BaseDataSetOfInstances *instances = (BaseDataSetOfInstances *) x;
  DataSetOfInstancesClass *instancesclass = (DataSetOfInstancesClass *) xclass;

  DataObjectClass *instanceclass = (DataObjectClass *) 
    instancesclass->PointerToAllowedClasses()->GetObjectClass(INSTANCE_INSTANCE_ID);
  ObjectList<String>::iterator name;
  for(name = TrainInstanceNames.begin(); name != TrainInstanceNames.end(); name++)
    {
      BaseDataObject *instance = (BaseDataObject *) instances->GetInstance(*name);
      BaseDataObject *instancecost = operator()(objclass,
						instance,x,
						instanceclass,xclass);
      AccumulateCosts(instancecost);
      delete instancecost;
    }
  return NULL;
}
/*F object = operator()(instance,instclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataObject *BaseDataOptimizeCostFunction::operator()(DataObjectClass *objclass,
							 BaseDataObject *x,
							 BaseDataObject *y,
							 DataObjectClass *xclass,
							 DataObjectClass *yclass)
{
  /*
  DataOptimizeCostFunctionClass *costclass = (DataOptimizeCostFunctionClass *) objclass;
  BaseDataInstance *instance = (BaseDataInstance *) x;
  DataInstanceClass *instanceclass = (DataInstanceClass *) xclass;
  BaseDataSetOfInstances *instances = (BaseDataSetOfInstances *) y;
  DataSetOfInstancesClass *instancesclass = (DataSetOfInstancesClass *) yclass;
  */
  cout << "BaseDataOptimizeCostFunction::operator() -- " << endl;
  BaseDataObject *cost = new BaseDataObject();

  return cost;
}
/*F newcost = AccumulateCosts(cost)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataOptimizeCostFunction::AccumulateCosts(BaseDataObject *cost)
{
}
 
/*F SetOptimizeObject(current)  . . . . . . . . initialize object to optimize
**
**  DESCRIPTION
**    Note that a new copy is not made of object
**
**  REMARKS
**
*/
void BaseDataOptimizeCostFunction::SetOptimizeObject(BaseDataObject *current)
{
  OptimizeObject = (BaseDataObject *) current->Clone();
}
/*F current = GetOptimizeObject()  . . . . . . . . get optimized object
**
**  DESCRIPTION
**    Note that a new copy is not made of object
**
**  REMARKS
**
*/
BaseDataObject *BaseDataOptimizeCostFunction::GetOptimizeObject()
{
  return OptimizeObject;
}
 
/*F cost = InitializeCost()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataOptimizeCostFunction::InitializeCost()
{
  if(CurrentCost != NULL)
    delete CurrentCost;
}
 
/*F cost = getCurrentCost()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataObject *BaseDataOptimizeCostFunction::getCurrentCost()
{
  return CurrentCost;
}
  
/*F setCurrentCost(cost)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataOptimizeCostFunction::setCurrentCost(BaseDataObject *cost)
{
  CurrentCost = cost;
}
/*F setCurrentCost(cost)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSetOfObjects *BaseDataOptimizeCostFunction::getParameters()
{
  return Parameters;
}
/*F names = getTrainInstanceNames()
**
**  DESCRIPTION
**     names: The set of instance names
**    
**  REMARKS
**
*/
ObjectList<String>& BaseDataOptimizeCostFunction::getTrainInstanceNames()
{
  return TrainInstanceNames;
}
/*F setTrainInstanceNames(names)
**
**  DESCRIPTION
**     names: The set of instance names
**    
**  REMARKS
**
*/
void BaseDataOptimizeCostFunction::setTrainInstanceNames(ObjectList<String>& names)
{
  TrainInstanceNames = names;
}

/*S DataOptimizeCostFunctionClass
 */
/*F DataOptimizeCostFunctionClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataOptimizeCostFunctionClass::DataOptimizeCostFunctionClass()
  : ParameterClass(NULL)
{
  Identification = OPTCOST_OPTIMIZE_ID;
  NameTag = OPTCOST_OPTIMIZE_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataOptimizeCostFunctionClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataOptimizeCostFunctionClass::DataOptimizeCostFunctionClass(const DataOptimizeCostFunctionClass& data)
  : DataOperationClass(data)
{
  ParameterClass = (DataSetOfObjectsClass *) PointerClone(data.ParameterClass);
} 
/*F DataOptimizeCostFunctionClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataOptimizeCostFunctionClass::DataOptimizeCostFunctionClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOperationClass(id,name,descr),
    ParameterClass(NULL)
{
  SubClass = "Operation";
  EncodeDecodeClass = OPTCOST_OPTIMIZE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataOptimizeCostFunctionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataOptimizeCostFunctionClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  PointerPrint(out,"Optimize Cost Function Class:\n","No Cost Function Class Specified",ParameterClass);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataOptimizeCostFunctionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataOptimizeCostFunctionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataOptimizeCostFunctionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);
  StreamObjectInput str(in,' ');
  String classname = str.ReadNext();
  if(set.PointerToAllowedClasses()->IsInList(classname))
    {
      ParameterClass = (DataSetOfObjectsClass *) set.PointerToAllowedClasses()->GetObjectClass(classname);
    }
  else
    {
      cerr << "Cost Function Class not found: '" << classname << "'" << endl;
    }
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataOptimizeCostFunctionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataOptimizeCostFunctionClass::CopyClone(Identify *  objc)
{
  DataOptimizeCostFunctionClass *objcfull = (DataOptimizeCostFunctionClass *) objc;
  *this = *objcfull;
  ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataOptimizeCostFunctionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataOptimizeCostFunctionClass::Clone()
    {
      DataOptimizeCostFunctionClass* id = new DataOptimizeCostFunctionClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataOptimizeCostFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataOptimizeCostFunctionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,ParameterClass);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataOptimizeCostFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataOptimizeCostFunctionClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) ParameterClass);

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
BaseDataObject * DataOptimizeCostFunctionClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataOptimizeCostFunction();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataOptimizeCostFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataOptimizeCostFunctionClass*& obj)
     {
     obj = new DataOptimizeCostFunctionClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataOptimizeCostFunction
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataOptimizeCostFunction*& obj)
     {
     obj = new BaseDataOptimizeCostFunction;
     return obj->DecodeThis(buffer);
     }
 
/*F pclass = getParameterClass()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataSetOfObjectsClass *DataOptimizeCostFunctionClass::getParameterClass()
{
  return ParameterClass;
}
 
/*F setParameterClass(paramclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void DataOptimizeCostFunctionClass::setParameterClass(DataSetOfObjectsClass *paramclass)
{
  ParameterClass = paramclass;
}
/*S BaseDataRealVectorCostFunction
 */ 
/*F BaseDataRealVectorCostFunction()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataRealVectorCostFunction::BaseDataRealVectorCostFunction()
{
  Identification = OPTCOST_VECTOR_ID;
  NameTag = OPTCOST_VECTOR_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataRealVectorCostFunction(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataRealVectorCostFunction::BaseDataRealVectorCostFunction(const BaseDataRealVectorCostFunction& data)
  : BaseDataOptimizeCostFunction(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataRealVectorCostFunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataRealVectorCostFunction::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataRealVectorCostFunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataRealVectorCostFunction::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOptimizeCostFunction::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataRealVectorCostFunction
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataRealVectorCostFunction::print(ostream& out) const
{
  BaseDataOptimizeCostFunction::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataRealVectorCostFunction
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataRealVectorCostFunction::Clone()
{
  BaseDataRealVectorCostFunction *obj = new BaseDataRealVectorCostFunction(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataRealVectorCostFunction
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataRealVectorCostFunction::CopyClone(Identify * obj)
{
  BaseDataRealVectorCostFunction *objfull = (BaseDataRealVectorCostFunction *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataRealVectorCostFunction
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataRealVectorCostFunction::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOptimizeCostFunction::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataRealVectorCostFunction
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataRealVectorCostFunction::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOptimizeCostFunction::DecodeThis(buffer);
  // The rest

  return result;
}
 
 
/*S DataRealVectorCostFunctionClass
 */
/*F DataRealVectorCostFunctionClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataRealVectorCostFunctionClass::DataRealVectorCostFunctionClass()
{
  Identification = OPTCOST_VECTOR_ID;
  NameTag = OPTCOST_VECTOR_NAME;
  SubClass = "OptimizeCostFunction";
  EncodeDecodeClass = NameTag;
} 
/*F DataRealVectorCostFunctionClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataRealVectorCostFunctionClass::DataRealVectorCostFunctionClass(const DataRealVectorCostFunctionClass& data)
  : DataOptimizeCostFunctionClass(data)
{
} 
 
/*F DataRealVectorCostFunctionClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataRealVectorCostFunctionClass::DataRealVectorCostFunctionClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOptimizeCostFunctionClass(id,name,descr)
{
  SubClass = OPTCOST_OPTIMIZE_NAME;
  EncodeDecodeClass = OPTCOST_VECTOR_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataRealVectorCostFunctionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataRealVectorCostFunctionClass::print(ostream& out) const
{
  DataOptimizeCostFunctionClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataRealVectorCostFunctionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataRealVectorCostFunctionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataRealVectorCostFunctionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOptimizeCostFunctionClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataRealVectorCostFunctionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataRealVectorCostFunctionClass::CopyClone(Identify *  objc)
{
  DataRealVectorCostFunctionClass *objcfull = (DataRealVectorCostFunctionClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataRealVectorCostFunctionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataRealVectorCostFunctionClass::Clone()
    {
      DataRealVectorCostFunctionClass* id = new DataRealVectorCostFunctionClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataRealVectorCostFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataRealVectorCostFunctionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOptimizeCostFunctionClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataRealVectorCostFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataRealVectorCostFunctionClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOptimizeCostFunctionClass::DecodeThis(buffer);
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
BaseDataObject * DataRealVectorCostFunctionClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataRealVectorCostFunction();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataRealVectorCostFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataRealVectorCostFunctionClass*& obj)
     {
     obj = new DataRealVectorCostFunctionClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataRealVectorCostFunction
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataRealVectorCostFunction*& obj)
     {
     obj = new BaseDataRealVectorCostFunction;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataOptimizeOperation
 */ 
/*F BaseDataOptimizeOperation()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataOptimizeOperation::BaseDataOptimizeOperation()
  : OptimizationCostS("OptimizationCost"),
    OptimizationCost(NULL),
    TrainInstanceNamesS("TrainInstanceNameList"),
    MaximumIterationCountS("MaximumNumberOfIterations"),
    OptimizeObjectS("OptimizeObject"),
    OptimizeObject(NULL),
    FinalResultS("OptimizedObject")
{
  Identification = OPTIMIZE_OPERATION_ID;
  NameTag = OPTIMIZE_OPERATION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataOptimizeOperation(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataOptimizeOperation::BaseDataOptimizeOperation(const BaseDataOptimizeOperation& data)
  : BaseDataAlgorithmOperation(data),
    OptimizationCostS(data.OptimizationCostS),
    TrainInstanceNamesS(data.TrainInstanceNamesS),
    MaximumIterationCountS(data.MaximumIterationCountS),
    OptimizeObjectS(data.OptimizeObjectS),
    FinalResultS(data.FinalResultS)
{
  OptimizationCost = (BaseDataOptimizeCostFunction *) PointerClone(data.OptimizationCost);
  OptimizeObject = (BaseDataObject *) PointerClone(data.OptimizeObject);
}
 
/*F ~BaseDataOptimizeOperation() . . . . . . . . . . . . . . . . .  destructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataOptimizeOperation::~BaseDataOptimizeOperation()
{
  if(OptimizationCost != NULL)
    delete OptimizationCost;
  if(OptimizeObject != NULL)
    delete OptimizeObject;
}

/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataOptimizeOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataOptimizeOperation::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataOptimizeOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataOptimizeOperation::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataOptimizeOperation
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataOptimizeOperation::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataOptimizeOperation
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataOptimizeOperation::Clone()
{
  BaseDataOptimizeOperation *obj = new BaseDataOptimizeOperation(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataOptimizeOperation
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataOptimizeOperation::CopyClone(Identify * obj)
{
  BaseDataOptimizeOperation *objfull = (BaseDataOptimizeOperation *) obj;
  *this = *objfull;
  OptimizationCost = (BaseDataOptimizeCostFunction *) PointerClone(objfull->OptimizationCost);
  OptimizeObject = (BaseDataObject *) PointerClone(objfull->OptimizeObject);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataOptimizeOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataOptimizeOperation::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataOptimizeOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataOptimizeOperation::DecodeThis(CommBuffer& buffer)
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
bool BaseDataOptimizeOperation::SetUpAlgorithms(BaseDataSetOfInstances*,
						      DataSetOfInstancesClass*,
						      BaseDataAlgorithmRun *run,
						      DataAlgorithmRunClass *rclass)
{
  bool result = true;
  return result;
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
bool BaseDataOptimizeOperation::CheckInput(BaseDataSetOfInstances*,
						 DataSetOfInstancesClass*,
						 BaseDataAlgorithmRun *run,
						 DataAlgorithmRunClass*)
{
  bool result = true;

  if(run->ParameterInList(TrainInstanceNamesS))
    {
      if(run->ParameterInList(OptimizeObjectS))
	{
	  if(run->ParameterInList(MaximumIterationCountS))
	    {
	      if(run->ParameterInList(OptimizationCostS))
		{
		}
	      else
		{
		  cerr << "The parameter '" << OptimizationCostS << "' was not in the list of parameters";
		  result = false;
		}
	    }
	  else
	    {
	      cerr << "The parameter '" << MaximumIterationCountS << "' was not in the list of parameters";
	      result = false;
	    }
	}
      else
	{
	  cerr << "The parameter '" << OptimizeObjectS << "' was not in the list of parameters";
	  result = false;
	}
    }
  else
    {
      cerr << "The parameter '" << TrainInstanceNamesS << "' was not in the list of parameters";
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
bool BaseDataOptimizeOperation::SetUpInput(BaseDataSetOfInstances*,
					   DataSetOfInstancesClass*,
					   BaseDataAlgorithmRun *run,
					   DataAlgorithmRunClass *rclass)
{
  bool result = true;

  BaseDataKeyWords *tlist = (BaseDataKeyWords *) run->ParameterValue(TrainInstanceNamesS);
  TrainInstanceNames = tlist->GetKeyWords();

  OptimizationCost = (BaseDataOptimizeCostFunction *) run->ParameterValue(OptimizationCostS)->Clone();
  OptimizationCost->setTrainInstanceNames(TrainInstanceNames);

  BaseDataInteger *count = (BaseDataInteger *) run->ParameterValue(MaximumIterationCountS);
  OptimizationCost->MaximumIterationCount = count->GetValue();

  OptimizeObject = (BaseDataObject *) run->ParameterValue(OptimizeObjectS)->Clone();
  if(rclass->getDebugLevel() > 3)
    {
      cout << "Input Parameters" << endl;
      OptimizeObject->print(cout);
      cout << endl;
    }

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
bool BaseDataOptimizeOperation::Calculate(BaseDataSetOfInstances *instances,
					  DataSetOfInstancesClass *instsclass,
					  BaseDataAlgorithmRun *run,
					  DataAlgorithmRunClass *rclass)
{
  bool result = true;
  instsclass->SetDebugLevel(rclass->getDebugLevel());
  if(rclass->getDebugLevel() > 1)
    cout << "Start Optimization" << endl;
  
  int costtype = OptimizationCost->GetType();
  DataOptimizeCostFunctionClass *costclass = 
    (DataOptimizeCostFunctionClass *) instsclass->PointerToAllowedClasses()->GetObjectClass(costtype);

  InitializeOptimization(costclass,instances,instsclass);
  result = UpdateCurrentCosts(costclass,instances,instsclass);
  BaseDataSetOfObjects *parameters;
  while(result && OptimizationNotDone())
    {
      if(rclass->getDebugLevel() > 0)
	{
	  cout << "IterationCount: " << OptimizationCost->IterationCount;
	  cout << " out of a maximum of " << OptimizationCost->MaximumIterationCount << endl;
	}
      OptimizationCost->IterationCount++;

      parameters = OptimizationCost->ExtractParameters(costclass);
      DataSetOfObjectsClass *popclass = costclass->getParameterClass();
      result = PerformSingleIteration(parameters,popclass,instances,instsclass);
      OptimizationCost->InsertParameters(parameters);
      if(rclass->getDebugLevel() > 2)
	{
	  cout << "begin: ----- Current Set Of Parameters ---------" << endl;
	  OptimizationCost->ExtractParameters(costclass)->print(cout);
	  cout << endl << "end:   ----- Current Set Of Parameters ---------" << endl;
	}
      if(result)
	result = UpdateCurrentCosts(costclass,instances,instsclass);

    }
  if(rclass->getDebugLevel() > 1)
    cout << "Optimization Finished" << endl;

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
bool BaseDataOptimizeOperation::WriteOutputValues(BaseDataSetOfInstances*,
							DataSetOfInstancesClass*,
							BaseDataAlgorithmRun* run,
							DataAlgorithmRunClass*)
{
  bool result = true;
  OptimizationCost->NameTag = FinalResultS;

  run->AddParameter(OptimizationCost);

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
bool BaseDataOptimizeOperation::ConcludeRun(BaseDataSetOfInstances *instances,
					    DataSetOfInstancesClass*,
					    BaseDataAlgorithmRun*,
					    DataAlgorithmRunClass*)
{
  bool result = true;
  return result;
}
 
/*F InitializeOptimization(instances,instsclass) .  all structures
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataOptimizeOperation::InitializeOptimization(DataOptimizeCostFunctionClass *costclass,
						       BaseDataSetOfInstances *instances,
						       DataSetOfInstancesClass *instsclass)
{
  bool result = true;
  OptimizationCost->SetOptimizeObject(OptimizeObject);
  InitializeObjectToOptimize(OptimizationCost,costclass,instances,instsclass);
  OptimizationCost->InitializeParameters(costclass,instances,instsclass);
  return result;
}
 
/*F OptimizationNotDone() . . . . . . . . . . . . . . . . true if not not yet
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataOptimizeOperation::OptimizationNotDone()
{
  bool result = true;

  if(OptimizationCost->IterationCount > OptimizationCost->MaximumIterationCount)
    result = false;
  return result;
}
 
/*F PerformSingleIteration(intances,instsclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataOptimizeOperation::PerformSingleIteration(BaseDataSetOfObjects *parameters,
						       DataSetOfObjectsClass *parclass,
						       BaseDataSetOfInstances *instances,
						       DataSetOfInstancesClass *)
{
  bool result = true;
  return result;
}
 
/*F ans = UpdateCurrentCosts(costclass,instances,instsclass)
**
**  DESCRIPTION
**   
**  REMARKS
**
*/
bool BaseDataOptimizeOperation::UpdateCurrentCosts(DataOptimizeCostFunctionClass *costclass,
						   BaseDataSetOfInstances *instances,
						   DataSetOfInstancesClass *instsclass)
{
  bool result = true;
  OptimizationCost->InitializeCost();
  BaseDataObject obj;
  DataObjectClass objclass;
  OptimizationCost->operator()(costclass,&obj,instances,&objclass,instsclass);

  return result;
}
/*F InitializeObjectToOptimize(cost,cclass,inst,instclass)
**
**  DESCRIPTION
**    inst: The set of instances
**    instclass: The set of instances class
**    run: The run algorithm
**    runclass: The run algorithm class
**
**  REMARKS
**
*/
void BaseDataOptimizeOperation::InitializeObjectToOptimize(BaseDataOptimizeCostFunction *cost,
							   DataOptimizeCostFunctionClass *cclass,
							   BaseDataSetOfInstances*,
							   DataSetOfInstancesClass*)
{
}
/*F costfunc = getCurrentCostFunction()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataOptimizeCostFunction *BaseDataOptimizeOperation::getCurrentCostFunction()
{
  return OptimizationCost;
}
 
/*F obj = getOptimizeObject()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataObject *BaseDataOptimizeOperation::getOptimizeObject()
{
  return OptimizeObject;
}
 
/*F getOptimizeObject(obj)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataOptimizeOperation::getOptimizeObject(BaseDataObject *obj)
{
  OptimizeObject = obj;
}
/*S DataOptimizeOperationClass
 */
/*F DataOptimizeOperationClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataOptimizeOperationClass::DataOptimizeOperationClass()
{
  Identification = OPTIMIZE_OPERATION_ID;
  NameTag = OPTIMIZE_OPERATION_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataOptimizeOperationClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataOptimizeOperationClass::DataOptimizeOperationClass(const DataOptimizeOperationClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataOptimizeOperationClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataOptimizeOperationClass::DataOptimizeOperationClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = "OptimizeOperation";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataOptimizeOperationClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataOptimizeOperationClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataOptimizeOperationClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataOptimizeOperationClass, there is no further information.
**
**  REMARKS
**
*/
bool DataOptimizeOperationClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataOptimizeOperationClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataOptimizeOperationClass::CopyClone(Identify *  objc)
{
  DataOptimizeOperationClass *objcfull = (DataOptimizeOperationClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataOptimizeOperationClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataOptimizeOperationClass::Clone()
{
  DataOptimizeOperationClass* id = new DataOptimizeOperationClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataOptimizeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataOptimizeOperationClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataOptimizeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataOptimizeOperationClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataOptimizeOperationClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataOptimizeOperation();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataOptimizeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataOptimizeOperationClass*& obj)
     {
     obj = new DataOptimizeOperationClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataOptimizeOperation
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataOptimizeOperation*& obj)
     {
     obj = new BaseDataOptimizeOperation;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataRealOptimizeOperation
 */ 
/*F BaseDataRealOptimizeOperation()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataRealOptimizeOperation::BaseDataRealOptimizeOperation()
{
  Identification = OPTIMIZE_REAL_ID;
  NameTag = OPTIMIZE_REAL_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataRealOptimizeOperation(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataRealOptimizeOperation::BaseDataRealOptimizeOperation(const BaseDataRealOptimizeOperation& data)
  : BaseDataOptimizeOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataRealOptimizeOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataRealOptimizeOperation::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataRealOptimizeOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataRealOptimizeOperation::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOptimizeOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataRealOptimizeOperation
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataRealOptimizeOperation::print(ostream& out) const
{
  BaseDataOptimizeOperation::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataRealOptimizeOperation
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataRealOptimizeOperation::Clone()
{
  BaseDataRealOptimizeOperation *obj = new BaseDataRealOptimizeOperation(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataRealOptimizeOperation
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataRealOptimizeOperation::CopyClone(Identify * obj)
{
  BaseDataRealOptimizeOperation *objfull = (BaseDataRealOptimizeOperation *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataRealOptimizeOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataRealOptimizeOperation::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOptimizeOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataRealOptimizeOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataRealOptimizeOperation::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOptimizeOperation::DecodeThis(buffer);
  // The rest

  return result;
}
 
 
/*S DataRealOptimizeOperationClass
 */
/*F DataRealOptimizeOperationClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataRealOptimizeOperationClass::DataRealOptimizeOperationClass()
{
  Identification = OPTIMIZE_REAL_ID;
  NameTag = OPTIMIZE_REAL_NAME;
  SubClass = "OptimizeOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataRealOptimizeOperationClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataRealOptimizeOperationClass::DataRealOptimizeOperationClass(const DataRealOptimizeOperationClass& data)
  : DataOptimizeOperationClass(data)
{
} 
 
/*F DataRealOptimizeOperationClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataRealOptimizeOperationClass::DataRealOptimizeOperationClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataOptimizeOperationClass(id,name,descr)
{
  SubClass = "OptimizeOperation";
  EncodeDecodeClass = "RealOptimizeOperation";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataRealOptimizeOperationClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataRealOptimizeOperationClass::print(ostream& out) const
{
  DataOptimizeOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataRealOptimizeOperationClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataRealOptimizeOperationClass, there is no further information.
**
**  REMARKS
**
*/
bool DataRealOptimizeOperationClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOptimizeOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataRealOptimizeOperationClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataRealOptimizeOperationClass::CopyClone(Identify *  objc)
{
  DataRealOptimizeOperationClass *objcfull = (DataRealOptimizeOperationClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataRealOptimizeOperationClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataRealOptimizeOperationClass::Clone()
    {
      DataRealOptimizeOperationClass* id = new DataRealOptimizeOperationClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataRealOptimizeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataRealOptimizeOperationClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOptimizeOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataRealOptimizeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataRealOptimizeOperationClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataRealOptimizeOperationClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataRealOptimizeOperation();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataRealOptimizeOperationClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataRealOptimizeOperationClass*& obj)
     {
     obj = new DataRealOptimizeOperationClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataRealOptimizeOperation
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataRealOptimizeOperation*& obj)
     {
     obj = new BaseDataRealOptimizeOperation;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataSimpleIterativeOptimize
 */ 
/*F BaseDataSimpleIterativeOptimize()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSimpleIterativeOptimize::BaseDataSimpleIterativeOptimize()
{
  Identification = OPTIMIZE_SIMPLEITERATION_ID;
  NameTag = OPTIMIZE_SIMPLEITERATION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataSimpleIterativeOptimize(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataSimpleIterativeOptimize::BaseDataSimpleIterativeOptimize(const BaseDataSimpleIterativeOptimize& data)
  : BaseDataRealOptimizeOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataSimpleIterativeOptimize
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataSimpleIterativeOptimize::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataSimpleIterativeOptimize
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataSimpleIterativeOptimize::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataRealOptimizeOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataSimpleIterativeOptimize
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataSimpleIterativeOptimize::print(ostream& out) const
{
  BaseDataRealOptimizeOperation::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataSimpleIterativeOptimize
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataSimpleIterativeOptimize::Clone()
{
  BaseDataSimpleIterativeOptimize *obj = new BaseDataSimpleIterativeOptimize(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataSimpleIterativeOptimize
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataSimpleIterativeOptimize::CopyClone(Identify * obj)
{
  BaseDataSimpleIterativeOptimize *objfull = (BaseDataSimpleIterativeOptimize *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSimpleIterativeOptimize
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSimpleIterativeOptimize::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataRealOptimizeOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSimpleIterativeOptimize
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSimpleIterativeOptimize::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataRealOptimizeOperation::DecodeThis(buffer);
  // The rest

  return result;
}
 
 
/*S DataSimpleIterativeOptimizeClass
 */
/*F DataSimpleIterativeOptimizeClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataSimpleIterativeOptimizeClass::DataSimpleIterativeOptimizeClass()
{
  Identification = OPTIMIZE_SIMPLEITERATION_ID;
  NameTag = OPTIMIZE_SIMPLEITERATION_NAME;
  SubClass = "RealOptimizeOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataSimpleIterativeOptimizeClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataSimpleIterativeOptimizeClass::DataSimpleIterativeOptimizeClass(const DataSimpleIterativeOptimizeClass& data)
  : DataRealOptimizeOperationClass(data)
{
} 
 
/*F DataSimpleIterativeOptimizeClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataSimpleIterativeOptimizeClass::DataSimpleIterativeOptimizeClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataRealOptimizeOperationClass(id,name,descr)
{
  SubClass = "RealOptimizeOperation";
  EncodeDecodeClass = "SimpleIterativeOptimize";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataSimpleIterativeOptimizeClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataSimpleIterativeOptimizeClass::print(ostream& out) const
{
  DataRealOptimizeOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataSimpleIterativeOptimizeClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataSimpleIterativeOptimizeClass, there is no further information.
**
**  REMARKS
**
*/
bool DataSimpleIterativeOptimizeClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataRealOptimizeOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataSimpleIterativeOptimizeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataSimpleIterativeOptimizeClass::CopyClone(Identify *  objc)
{
  DataSimpleIterativeOptimizeClass *objcfull = (DataSimpleIterativeOptimizeClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataSimpleIterativeOptimizeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataSimpleIterativeOptimizeClass::Clone()
    {
      DataSimpleIterativeOptimizeClass* id = new DataSimpleIterativeOptimizeClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataSimpleIterativeOptimizeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSimpleIterativeOptimizeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataRealOptimizeOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataSimpleIterativeOptimizeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSimpleIterativeOptimizeClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataRealOptimizeOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataSimpleIterativeOptimizeClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataSimpleIterativeOptimize();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataSimpleIterativeOptimizeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataSimpleIterativeOptimizeClass*& obj)
     {
     obj = new DataSimpleIterativeOptimizeClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataSimpleIterativeOptimize
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataSimpleIterativeOptimize*& obj)
     {
     obj = new BaseDataSimpleIterativeOptimize;
     return obj->DecodeThis(buffer);
     }
/*S Utilities
 */

/*F InitialSetOfOptimizeEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialSetOfOptimizeEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataOptimizeCostFunctionClass,BaseDataOptimizeCostFunction,OPTCOST_OPTIMIZE_NAME);
  EncodeDecodeRegisterClass(DataRealVectorCostFunctionClass,BaseDataRealVectorCostFunction,OPTCOST_VECTOR_NAME);

  EncodeDecodeRegisterClass(DataOptimizeOperationClass,BaseDataOptimizeOperation,OPTIMIZE_OPERATION_NAME);
  EncodeDecodeRegisterClass(DataRealOptimizeOperationClass,BaseDataRealOptimizeOperation,OPTIMIZE_REAL_NAME);
  EncodeDecodeRegisterClass(DataSimpleIterativeOptimizeClass,BaseDataSimpleIterativeOptimize,OPTIMIZE_SIMPLEITERATION_NAME);
}
 
/*F AddOptimizeClasses(set)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AddOptimizeClasses(DataSetOfObjectsClass& set)
{
  String costdescr("The Base Optimize Cost Function");
  String vecdescr("The Real Vector Optimization Cost Function");
  String opdescr("The Base Optimize Class");
  String readdescr("Optimization of Real Parameter Sets");
  String iterdescr("Simple Iterative Optimization of Parameter Sets");
  
  DataOptimizeCostFunctionClass costclass(OPTCOST_OPTIMIZE_ID,OPTCOST_OPTIMIZE_NAME,costdescr);
  DataRealVectorCostFunctionClass vecclass(OPTCOST_VECTOR_ID,OPTCOST_VECTOR_NAME,vecdescr);
  DataOptimizeOperationClass opclass(OPTIMIZE_OPERATION_ID,OPTIMIZE_OPERATION_NAME,opdescr);
  DataRealOptimizeOperationClass readclass(OPTIMIZE_REAL_ID,OPTIMIZE_REAL_NAME,readdescr);
  DataSimpleIterativeOptimizeClass iterclass(OPTIMIZE_SIMPLEITERATION_ID,OPTIMIZE_SIMPLEITERATION_NAME,iterdescr);

  set.AddObjectClass(costclass);
  set.AddObjectClass(vecclass);
  set.AddObjectClass(opclass);
  set.AddObjectClass(readclass);
  set.AddObjectClass(iterclass);
}
