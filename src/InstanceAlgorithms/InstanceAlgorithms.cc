/*  FILE     InstanceAlgorithms.cc
**  PACKAGE  InstanceAlgorithms
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "InstanceAlgorithms" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
**  Version 1.1
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
#include "InstanceAlgorithms.hh"
#include "BasicLaTeXTable.hh"
#include "MatrixOut.hh"

/*S BaseDataAttributeSetUp
 */ 
/*F BaseDataAttributeSetUp()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataAttributeSetUp::BaseDataAttributeSetUp()
  : instanceNameListS("TotalInstanceNameList"),
    attributeSpecsS("AttributeSpecs"),
    byTypeS("AttributesByType"),
    byType(false),
    byNameS("AttributesByName"),
    byName(false),
    allValuesS("allAttributes"),
    allValues(false),
    attributeNamesS("AttributeNames"),
    allAttributeNamesS("totalAttributeNameList")
{
  Identification = INSTALGORITHMS_ATTRIBUTES_ID;
  NameTag = INSTALGORITHMS_ATTRIBUTES_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataAttributeSetUp(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataAttributeSetUp::BaseDataAttributeSetUp(const BaseDataAttributeSetUp& data)
  : BaseDataAlgorithmOperation(data),
    instanceNameListS(data.instanceNameListS),
    attributeSpecsS(data.attributeSpecsS),
    byTypeS(data.byTypeS),
    byType(data.byType),
    byNameS(data.byNameS),
    byName(data.byName),
    allValuesS(data.allValuesS),
    allValues(data.allValues),
    attributeNamesS(data.attributeNamesS),
    allAttributeNamesS(data.allAttributeNamesS)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataAttributeSetUp
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataAttributeSetUp::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataAttributeSetUp
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataAttributeSetUp::Read(istream& in, DataObjectClass* objc, const String& name)
{
  return BaseDataAlgorithmOperation::Read(in,objc,name);
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataAttributeSetUp
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataAttributeSetUp::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataAttributeSetUp
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataAttributeSetUp::Clone()
{
  BaseDataAttributeSetUp *obj = new BaseDataAttributeSetUp;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataAttributeSetUp
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataAttributeSetUp::CopyClone(Identify * obj)
{
  BaseDataAttributeSetUp *objc = (BaseDataAttributeSetUp *) obj;
  *this = *objc;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataAttributeSetUp
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataAttributeSetUp::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataAttributeSetUp
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataAttributeSetUp::DecodeThis(CommBuffer& buffer)
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
bool BaseDataAttributeSetUp::SetUpAlgorithms(BaseDataSetOfInstances*,
					     DataSetOfInstancesClass*,
					     BaseDataAlgorithmRun* ,
					     DataAlgorithmRunClass*)
{
  return true;
}
/*F ans = CheckInput(instances,instancesclass,run,runclass) . . . . algorithm
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
bool BaseDataAttributeSetUp::CheckInput(BaseDataSetOfInstances*,
					DataSetOfInstancesClass*,
					BaseDataAlgorithmRun* run,
					DataAlgorithmRunClass*)
{
  bool result = true;
  
  if(run->AlgorithmSummary.KeyWordInList(byTypeS))
    byType = true;
  else if(run->AlgorithmSummary.KeyWordInList(byNameS))
    byName = true;
  else if(run->AlgorithmSummary.KeyWordInList(allValuesS))
    allValues = true;
  
  if(run->ParameterInList(instanceNameListS))
    {
	if(!allValues)
	    {
		if(!run->ParameterInList(attributeSpecsS))
		    {
			cerr << "Attribute Specification: '" << attributeSpecsS << "' not found\n";
			result = false; 
		    }
	    }
    }
  else
    {
      cerr << "Instance Name List: '" << instanceNameListS << "' not found\n";
      result = false; 
    }

  return result;
}
/*F ans = SetUpInput(instances,instancesclass,run,runclass) . . . . algorithm
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
bool BaseDataAttributeSetUp::SetUpInput(BaseDataSetOfInstances*,
					DataSetOfInstancesClass*,
					BaseDataAlgorithmRun* run,
					DataAlgorithmRunClass*)
{
  bool result = true;
  
  instanceNameList = (BaseDataKeyWords *) run->ParameterValue(instanceNameListS);

  if(!allValues)
      {
	  attributeSpecs  = (BaseDataKeyWords *) run->ParameterValue(attributeSpecsS);
      }
  if(debugPrint > 0)
    {
	instanceNameList->print(cout);
	cout << endl;
	if(!allValues)
	    {
		attributeSpecs->print(cout);
		cout << endl;
	    }
      cout << "Allowed KeyWords: ";
      cout << byTypeS << ", " << byNameS << ", " << allValuesS << endl;
      
      if(allValues)
	cout << "     All (Common) Parameter Values\n";
      else if(byType)
	cout << "     Specification of Parameter Types\n";
      else if(byName)
	cout << "     Specification of Parameter Names\n";
      else
	cout << "     All Parameters Used\n";
    }
  
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
bool BaseDataAttributeSetUp::Calculate(BaseDataSetOfInstances* instances,
				       DataSetOfInstancesClass* instancesclass,
				       BaseDataAlgorithmRun *,
				       DataAlgorithmRunClass*)
{
  bool result = true;

  ObjectList<String> nlist;
  ObjectList<String> slist;
  ObjectList<String> fullset = instances->ListOfInstanceAttributeNames(instanceNameList->GetKeyWords(),
								       slist,*instancesclass,false);
  if(allValues)
    {
      nlist = instances->ListOfInstanceAttributeNames(instanceNameList->GetKeyWords(),slist,*instancesclass,true);
    }
  else if(byName)
    {
      nlist = instances->ListOfInstanceAttributeNames(instanceNameList->GetKeyWords(),slist,*instancesclass,true);
      cout << "instances->ListOfInstanceAttributeNames" << endl;
      nlist.print(cout);
      cout << endl;

      ObjectList<String> namelist = attributeSpecs->GetKeyWords();
      cout << " attributeSpecs->GetKeyWords();" << endl;
      namelist.print(cout);
      cout << endl;
      nlist.Intersected(namelist);
      cout << "nlist.Intersected(namelist);" << endl;
      nlist.print(cout);
      cout << endl;
    }
  else if(byType)
    {
	ObjectList<String> namelist = attributeSpecs->GetKeyWords();
	nlist = instances->ListOfInstanceAttributeNames(instanceNameList->GetKeyWords(),namelist,*instancesclass,true);
    }
  else
    {
      nlist = instances->ListOfInstanceAttributeNames(instanceNameList->GetKeyWords(),slist,*instancesclass,true);
    }
  attributeNames = new BaseDataKeyWords(nlist);
  attributeNames->NameTag = attributeNamesS;

  allAttributeNames = new BaseDataKeyWords(fullset);
  allAttributeNames->NameTag = allAttributeNamesS;

  instances->PrintMissingAttributeNames(instanceNameList->GetKeyWords(),
					slist,*instancesclass,fullset);
  
  return result;
}
/*F ans = WriteOutputValues(instances,instancesclass,run,runclass)  algorithm
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
bool BaseDataAttributeSetUp::WriteOutputValues(BaseDataSetOfInstances*,
					       DataSetOfInstancesClass*,
					       BaseDataAlgorithmRun* run,
					       DataAlgorithmRunClass*) 
{
  bool result = true;
  if(debugPrint > 0)
    {
      attributeNames->print(cout);
      cout << "\nSelected Attributes Stored under " << attributeNamesS << endl;
    }
  
  run->AddParameter(attributeNames);
  run->AddParameter(allAttributeNames);

  return result;
}
/*F ans = ConcludeRun(instances,instancesclass,run,runclass)  . . . algorithm
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
bool BaseDataAttributeSetUp::ConcludeRun(BaseDataSetOfInstances*,
					 DataSetOfInstancesClass*,
					 BaseDataAlgorithmRun*,
					 DataAlgorithmRunClass* ) 
{
  delete attributeNames;

  return true;
}
/*S DataAttributeSetUpClass
 */
/*F DataAttributeSetUpClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataAttributeSetUpClass::DataAttributeSetUpClass()
{
  NameTag = INSTALGORITHMS_ATTRIBUTES_NAME;
  Identification = INSTALGORITHMS_ATTRIBUTES_ID;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = INSTALGORITHMS_ATTRIBUTES_NAME;
} 
/*F DataAttributeSetUpClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataAttributeSetUpClass::DataAttributeSetUpClass(const DataAttributeSetUpClass& data)
  : DataAlgorithmOperationClass(data)
     // the rest
{
} 
 
/*F DataAttributeSetUpClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataAttributeSetUpClass::DataAttributeSetUpClass(const int id, 
						 const String& name,
						 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = INSTALGORITHMS_ATTRIBUTES_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataAttributeSetUpClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataAttributeSetUpClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  out << NameTag << "  ";
  // the rest
	   
       return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . . . . . DataAttributeSetUpClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataAttributeSetUpClass, there is no further information.
**
**  REMARKS
**
*/
bool DataAttributeSetUpClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  return DataAlgorithmOperationClass::Read(in,set);
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataAttributeSetUpClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataAttributeSetUpClass::CopyClone(Identify *  objc)
{
  DataAttributeSetUpClass *objcc = (DataAttributeSetUpClass *) objc;
  *this = *objcc;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataAttributeSetUpClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataAttributeSetUpClass::Clone()
{
  DataAttributeSetUpClass* id = new DataAttributeSetUpClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataAttributeSetUpClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataAttributeSetUpClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataAttributeSetUpClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataAttributeSetUpClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataAttributeSetUpClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataAttributeSetUp();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataAttributeSetUpClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataAttributeSetUpClass*& obj)
{
  obj = new DataAttributeSetUpClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataAttributeSetUp
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataAttributeSetUp*& obj)
{
  obj = new BaseDataAttributeSetUp;
  return obj->DecodeThis(buffer);
}

/*S BaseDataInstanceSetUp
 */ 
/*F BaseDataInstanceSetUp() . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataInstanceSetUp::BaseDataInstanceSetUp()
  : instanceNameListS("InstanceNameList"),
    testPercentageS("TestPercentage"),
    totalInstanceNameListS("TotalInstanceNameList"),
    testInstanceNameListS("TestInstanceNameList"),
    trainInstanceNameListS("TrainInstanceNameList")
{
  Identification = INSTALGORITHMS_INSTANCES_ID;
  NameTag = INSTALGORITHMS_INSTANCES_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataInstanceSetUp(data) . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataInstanceSetUp::BaseDataInstanceSetUp(const BaseDataInstanceSetUp& data)
  : BaseDataAlgorithmOperation(data)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . Read in BaseDataInstanceSetUp
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataInstanceSetUp::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . Read in BaseDataInstanceSetUp
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataInstanceSetUp::Read(istream& in, DataObjectClass* objc, const String& name)
{
  return BaseDataAlgorithmOperation::Read(in,objc,name);
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . BaseDataInstanceSetUp
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataInstanceSetUp::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  // The rest of the print objects

       return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . BaseDataInstanceSetUp
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataInstanceSetUp::Clone()
{
  BaseDataInstanceSetUp *obj = new BaseDataInstanceSetUp;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . BaseDataInstanceSetUp
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataInstanceSetUp::CopyClone(Identify * obj)
{
  BaseDataInstanceSetUp *objc = (BaseDataInstanceSetUp *) obj;
  *this = *objc;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . BaseDataInstanceSetUp
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInstanceSetUp::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . BaseDataInstanceSetUp
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInstanceSetUp::DecodeThis(CommBuffer& buffer)
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
bool BaseDataInstanceSetUp::SetUpAlgorithms(BaseDataSetOfInstances*,
					    DataSetOfInstancesClass*,
					    BaseDataAlgorithmRun* ,
					    DataAlgorithmRunClass*)
{
  return true;
}
/*F ans = CheckInput(instances,instancesclass,run,runclass) . . . . algorithm
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
bool BaseDataInstanceSetUp::CheckInput(BaseDataSetOfInstances*,
				       DataSetOfInstancesClass*,
				       BaseDataAlgorithmRun* run,
				       DataAlgorithmRunClass*)
{
  bool result = true;
  if(run->ParameterInList(instanceNameListS))
    {
      if(!run->ParameterInList(testPercentageS))
	{
	  cerr << "Percentage of Test Instances not found: " << testPercentageS << endl;
	  result = false;
	}
    }
  else
    {
      cerr << "Not found: Instance name list parameter: " << instanceNameListS << endl;
      result = false;
    }
  
  return result;
}
/*F ans = SetUpInput(instances,instancesclass,run,runclass) . . . . algorithm
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
bool BaseDataInstanceSetUp::SetUpInput(BaseDataSetOfInstances*,
				       DataSetOfInstancesClass*,
				       BaseDataAlgorithmRun* run,
				       DataAlgorithmRunClass*)
{
  bool result = true;

  instanceNameList = (BaseDataKeyWords *) run->ParameterValue(instanceNameListS);
  testPercentage = (BaseDataNumeric *) run->ParameterValue(testPercentageS);

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
bool BaseDataInstanceSetUp::Calculate(BaseDataSetOfInstances* instances,
				      DataSetOfInstancesClass*,
				      BaseDataAlgorithmRun *,
				      DataAlgorithmRunClass*)
{
  bool result = true;

  ObjectList<String> totalList = instances->ListOfInstanceNames();
  ObjectList<String> inputList = instanceNameList->GetKeyWords();

  if(inputList.size() > 0)
    {
      totalList.Intersected(inputList);
    }
  ObjectList<String> testList;
  ObjectList<String> trainList;

  double ele;
  double r;
  double percent = testPercentage->Distance() / 100.0;
  
  for(ObjectList<String>::iterator name = totalList.begin(); name != totalList.end(); name++)
    {
      r = rand();
      ele = r/RAND_MAX;
      
      if(ele < percent)
	testList.AddObject(*name);
      else
	trainList.AddObject(*name);
    }

  totalInstanceNameList = new BaseDataKeyWords(totalList);
  totalInstanceNameList->NameTag = totalInstanceNameListS;

  testInstanceNameList = new BaseDataKeyWords(testList);
  testInstanceNameList->NameTag = testInstanceNameListS;

  trainInstanceNameList = new BaseDataKeyWords(trainList);
  trainInstanceNameList->NameTag = trainInstanceNameListS;
  
  return result;
}
/*F ans = WriteOutputValues(instances,instancesclass,run,runclass) algorithm 
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
bool BaseDataInstanceSetUp::WriteOutputValues(BaseDataSetOfInstances*,
					      DataSetOfInstancesClass*,
					      BaseDataAlgorithmRun* run,
					      DataAlgorithmRunClass*) 
{
  bool result = true;

  run->AddParameter(totalInstanceNameList);
  run->AddParameter(testInstanceNameList);
  run->AddParameter(trainInstanceNameList);

  return result;
}
/*F ans = ConcludeRun(instances,instancesclass,run,runclass)  . . . algorithm
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
bool BaseDataInstanceSetUp::ConcludeRun(BaseDataSetOfInstances*,
					DataSetOfInstancesClass*,
					BaseDataAlgorithmRun*,
					DataAlgorithmRunClass* ) 
{
  delete totalInstanceNameList;
  delete testInstanceNameList;
  delete trainInstanceNameList;

  return true;
}
/*S DataInstanceSetUpClass
 */
/*F DataInstanceSetUpClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataInstanceSetUpClass::DataInstanceSetUpClass()
{
  NameTag = INSTALGORITHMS_INSTANCES_NAME;
  Identification = INSTALGORITHMS_INSTANCES_ID;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = INSTALGORITHMS_INSTANCES_NAME;
} 
/*F DataInstanceSetUpClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataInstanceSetUpClass::DataInstanceSetUpClass(const DataInstanceSetUpClass& data)
  : DataAlgorithmOperationClass(data)
     // the rest
{
} 
 
/*F DataInstanceSetUpClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataInstanceSetUpClass::DataInstanceSetUpClass(const int id, 
					       const String& name,
					       const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = INSTALGORITHMS_INSTANCES_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataInstanceSetUpClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataInstanceSetUpClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  out << NameTag << "  ";
  // the rest
	   
       return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . . . . . DataInstanceSetUpClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataInstanceSetUpClass, there is no further information.
**
**  REMARKS
**
*/
bool DataInstanceSetUpClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  return DataAlgorithmOperationClass::Read(in,set);
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataInstanceSetUpClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataInstanceSetUpClass::CopyClone(Identify *  objc)
{
  DataInstanceSetUpClass *objcc = (DataInstanceSetUpClass *) objc;
  *this = *objcc;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataInstanceSetUpClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataInstanceSetUpClass::Clone()
{
  DataInstanceSetUpClass* id = new DataInstanceSetUpClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataInstanceSetUpClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataInstanceSetUpClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataInstanceSetUpClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataInstanceSetUpClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataInstanceSetUpClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataInstanceSetUp();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataInstanceSetUpClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataInstanceSetUpClass*& obj)
{
  obj = new DataInstanceSetUpClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataInstanceSetUp
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataInstanceSetUp*& obj)
{
  obj = new BaseDataInstanceSetUp;
  return obj->DecodeThis(buffer);
}

/*S BaseDataMatrixSetUp
 */ 
/*F BaseDataMatrixSetUp()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataMatrixSetUp::BaseDataMatrixSetUp()
  : totalInstanceNameListS("TotalInstanceNameList"),
    attributeNamesS("AttributeNames"),
    matrixObjectS("MatrixObject"),
    rootNameS("RunRootName")
{
  Identification = INSTALGORITHMS_MATRIX_ID;
  NameTag = INSTALGORITHMS_MATRIX_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataMatrixSetUp(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataMatrixSetUp::BaseDataMatrixSetUp(const BaseDataMatrixSetUp& data)
  : BaseDataAlgorithmOperation(data),
  totalInstanceNameListS(data.totalInstanceNameListS),
  attributeNamesS(data.attributeNamesS),
  matrixObjectS(data.matrixObjectS),
  rootNameS(data.rootNameS)  
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataMatrixSetUp
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataMatrixSetUp::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataMatrixSetUp
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataMatrixSetUp::Read(istream& in, DataObjectClass* objc, const String& name)
{
  return BaseDataAlgorithmOperation::Read(in,objc,name);
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataMatrixSetUp
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataMatrixSetUp::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  out << "MatrixSetUp: " << totalInstanceNameListS << ", " << attributeNamesS;
  out << ", " << matrixObjectS << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataMatrixSetUp
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataMatrixSetUp::Clone()
{
  BaseDataMatrixSetUp *obj = new BaseDataMatrixSetUp(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataMatrixSetUp
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataMatrixSetUp::CopyClone(Identify * obj)
{
  BaseDataMatrixSetUp *objc = (BaseDataMatrixSetUp *) obj;
  *this = *objc;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMatrixSetUp
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMatrixSetUp::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && Encode(buffer,totalInstanceNameListS);
  result = result && Encode(buffer,attributeNamesS);
  result = result && Encode(buffer,matrixObjectS);
  result = result && Encode(buffer,rootNameS);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMatrixSetUp
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMatrixSetUp::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && Decode(buffer,totalInstanceNameListS);
  result = result && Decode(buffer,attributeNamesS);
  result = result && Decode(buffer,matrixObjectS);
  result = result && Decode(buffer,rootNameS);
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
bool BaseDataMatrixSetUp::SetUpAlgorithms(BaseDataSetOfInstances*,
					  DataSetOfInstancesClass*,
					  BaseDataAlgorithmRun* ,
					  DataAlgorithmRunClass*)
{
  return true;
}
/*F ans = CheckInput(instances,instancesclass,run,runclass) . . . . algorithm
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
bool BaseDataMatrixSetUp::CheckInput(BaseDataSetOfInstances*,
				     DataSetOfInstancesClass*,
				     BaseDataAlgorithmRun* run,
				     DataAlgorithmRunClass*)
{
  bool result = true;
  
  if(!(run->ParameterInList(totalInstanceNameListS)))
    {
      cerr << "Parameter not found: " << totalInstanceNameListS << endl;
      result = false;
    }
  if(!(run->ParameterInList(attributeNamesS)))
    {
      cerr << "Parameter not found: " << attributeNamesS << endl;
      result = false;
    }
  
  return result;
}
/*F ans = SetUpInput(instances,instancesclass,run,runclass) . . . . algorithm
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
bool BaseDataMatrixSetUp::SetUpInput(BaseDataSetOfInstances*,
				     DataSetOfInstancesClass*,
				     BaseDataAlgorithmRun* run,
				     DataAlgorithmRunClass*)
{
  bool result = true;
  
  totalInstanceNameList = (BaseDataKeyWords *) run->ParameterValue(totalInstanceNameListS);
  attributeNames = (BaseDataKeyWords *) run->ParameterValue(attributeNamesS);
  if(run->ParameterInList(rootNameS))
    {
      BaseDataKeyWords *rootkeys = (BaseDataKeyWords *) run->ParameterValue(rootNameS);
      ObjectList<String> keys = rootkeys->GetKeyWords();
      if(keys.size() > 0)
	matrixObjectS = keys.front();
    }
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
bool BaseDataMatrixSetUp::Calculate(BaseDataSetOfInstances* instances,
				    DataSetOfInstancesClass*,
				    BaseDataAlgorithmRun *,
				    DataAlgorithmRunClass*)
{
  bool result = true;
  ObjectList<String>::iterator in;
  ObjectList<String>::iterator attr;
  ObjectList<String> insts = totalInstanceNameList->GetKeyWords();
  ObjectList<String> attrs = attributeNames->GetKeyWords();
  MatrixNumeric *mat = new MatrixNumeric(insts.size(),attrs.size());
  
  int incount = 0;
  for(in = insts.begin(); in != insts.end(); in++) {
      BaseDataInstance *instance = instances->GetInstance(*in);
      int attcount = 0;
      for(attr = attrs.begin(); attr != attrs.end(); attr++) {
	if(instance->ObjectExists(*attr)) {
	  BaseDataNumeric *param = (BaseDataNumeric *) instance->GetAttributeValue(*attr);
	  
	  double value = param->Distance();
	  (*mat)[incount][attcount] = value;
	  attcount++;
	} else {
	  cerr << "Attribute: " << *attr << " not in instance: " << instance->NameTag << endl;
	}
      }
      incount++;
    }
  matrixObject = new BaseDataInstanceDoubleMatrix(*mat,*totalInstanceNameList,*attributeNames);
  matrixObject->NameTag = matrixObjectS;
  
  delete mat;
  
  return result;
}
/*F ans = WriteOutputValues(instances,instancesclass,run,runclass) algorithm 
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
bool BaseDataMatrixSetUp::WriteOutputValues(BaseDataSetOfInstances*,
					    DataSetOfInstancesClass*,
					    BaseDataAlgorithmRun* run,
					    DataAlgorithmRunClass*) 
{
  bool result = true;
  run->AddParameter(matrixObject);

  return result;
}
/*F ans = ConcludeRun(instances,instancesclass,run,runclass)  . . . algorithm
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
bool BaseDataMatrixSetUp::ConcludeRun(BaseDataSetOfInstances*,
				      DataSetOfInstancesClass*,
				      BaseDataAlgorithmRun*,
				      DataAlgorithmRunClass* ) 
{
  delete matrixObject;
  return true;
}
/*S DataMatrixSetUpClass
 */
/*F DataMatrixSetUpClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataMatrixSetUpClass::DataMatrixSetUpClass()
{
  NameTag = INSTALGORITHMS_MATRIX_NAME;
  Identification = INSTALGORITHMS_MATRIX_ID;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = INSTALGORITHMS_MATRIX_NAME;
} 
/*F DataMatrixSetUpClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataMatrixSetUpClass::DataMatrixSetUpClass(const DataMatrixSetUpClass& data)
  : DataAlgorithmOperationClass(data)
     // the rest
{
} 
 
/*F DataMatrixSetUpClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataMatrixSetUpClass::DataMatrixSetUpClass(const int id, 
					   const String& name,
					   const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = INSTALGORITHMS_MATRIX_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataMatrixSetUpClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataMatrixSetUpClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  out << NameTag << "  ";
  // the rest
	   
       return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . . . . . DataMatrixSetUpClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataMatrixSetUpClass, there is no further information.
**
**  REMARKS
**
*/
bool DataMatrixSetUpClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  return DataAlgorithmOperationClass::Read(in,set);
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataMatrixSetUpClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataMatrixSetUpClass::CopyClone(Identify *  objc)
{
  DataMatrixSetUpClass *objcc = (DataMatrixSetUpClass *) objc;
  *this = *objcc;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataMatrixSetUpClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataMatrixSetUpClass::Clone()
{
  DataMatrixSetUpClass* id = new DataMatrixSetUpClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataMatrixSetUpClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMatrixSetUpClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataMatrixSetUpClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMatrixSetUpClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataMatrixSetUpClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataMatrixSetUp();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataMatrixSetUpClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataMatrixSetUpClass*& obj)
{
  obj = new DataMatrixSetUpClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataMatrixSetUp
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataMatrixSetUp*& obj)
{
  obj = new BaseDataMatrixSetUp;
  return obj->DecodeThis(buffer);
}

/*S BaseDataInstanceASCIIRead
 */ 
/*F BaseDataInstanceASCIIRead()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataInstanceASCIIRead::BaseDataInstanceASCIIRead()
  : instanceReadFilesS("InstanceReadFiles")
{
  Identification = INSTALGORITHMS_READASCII_ID;
  NameTag = INSTALGORITHMS_READASCII_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataInstanceASCIIRead(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataInstanceASCIIRead::BaseDataInstanceASCIIRead(const BaseDataInstanceASCIIRead& data)
  : BaseDataAlgorithmOperation(data)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataInstanceASCIIRead
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataInstanceASCIIRead::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataInstanceASCIIRead
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataInstanceASCIIRead::Read(istream& in, DataObjectClass* objc, const String& name)
{
  return BaseDataAlgorithmOperation::Read(in,objc,name);
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataInstanceASCIIRead
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataInstanceASCIIRead::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  // The rest of the print objects

       return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataInstanceASCIIRead
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataInstanceASCIIRead::Clone()
{
  BaseDataInstanceASCIIRead *obj = new BaseDataInstanceASCIIRead;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataInstanceASCIIRead
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataInstanceASCIIRead::CopyClone(Identify * obj)
{
  BaseDataInstanceASCIIRead *objc = (BaseDataInstanceASCIIRead *) obj;
  *this = *objc;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataInstanceASCIIRead
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInstanceASCIIRead::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataInstanceASCIIRead
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInstanceASCIIRead::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  // The rest: result = result && Decode(buffer,-------);
  // result = result && DecodeThis(buffer);

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
bool BaseDataInstanceASCIIRead::SetUpAlgorithms(BaseDataSetOfInstances*,
						DataSetOfInstancesClass*,
						BaseDataAlgorithmRun* ,
						DataAlgorithmRunClass*)
{
  return true;
}
/*F ans = CheckInput(instances,instancesclass,run,runclass) . . . . algorithm
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
bool BaseDataInstanceASCIIRead::CheckInput(BaseDataSetOfInstances*,
					   DataSetOfInstancesClass*,
					   BaseDataAlgorithmRun* run,
					   DataAlgorithmRunClass*)
{
  bool result = true;
  if(!run->ParameterInList(instanceReadFilesS))
    {
      cerr << "Not found: '" << instanceReadFilesS << endl;
      result = false;
    }
  
  return result;
}
/*F ans = SetUpInput(instances,instancesclass,run,runclass) . . . . algorithm
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
bool BaseDataInstanceASCIIRead::SetUpInput(BaseDataSetOfInstances*,
					   DataSetOfInstancesClass*,
					   BaseDataAlgorithmRun* run,
					   DataAlgorithmRunClass*)
{
  bool result = true;
  instanceReadFiles = (BaseDataKeyWords *) run->ParameterValue(instanceReadFilesS);
  
  return result;
}
 
/*F ans = Calculate(instances,instancesclass,run,runclass)  . . . . alogirhtm
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
bool BaseDataInstanceASCIIRead::Calculate(BaseDataSetOfInstances* instances,
					  DataSetOfInstancesClass* instancesclass,
					  BaseDataAlgorithmRun *,
					  DataAlgorithmRunClass*)
{
  bool result = true;
  ObjectList<String> namelist = instanceReadFiles->GetKeyWords();
  namelist.ChangeTitle("Input file pairs (class and instance files): ");
  cout << namelist;
  cout << endl;
  
  while(namelist.size() > 1 && result)
    {
      String classfileS = namelist.front();
      namelist.pop_front();
      OpenInputFile classfile(classfileS);
      if(classfile.IfOpen())
	{
	  String instfileS = namelist.front();
	  namelist.pop_front();
	  OpenInputFile instfile(instfileS);
	  if(instfile.IfOpen())
	    {
	      DataSetOfInstancesClass objectclass;
	      if(debugPrint > 0)
		cout << endl << "Read Classes: " << classfileS << endl;
	      result = result && objectclass.Read(classfile.Stream,*instancesclass);
	      if(debugPrint > 0)
		cout << endl;
	      if(debugPrint > 0)
		{
		  objectclass.print(cout);
		  cout << endl;
		}
	      if(debugPrint > 0)	      
		cout << endl << "Read Instances: " << instfileS << endl;
	      objectclass.ReadClassPairs     = false;
	      objectclass.ReadAllowedClasses = false;
	      result = result && instances->Read(instfile.Stream,&objectclass,instances->NameTag);
	    }
	  else
	    {
	      cerr << "Instance File not found: " << instfileS << endl;
	      result = false;
	    }
	}
      else
	{
	  cerr << "Class File not found: " << classfileS << endl;
	  result = false;
	}
    }
  
  return result;
}
/*F ans = WriteOutputValues(instances,instancesclass,run,runclass)  algorithm
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
bool BaseDataInstanceASCIIRead::WriteOutputValues(BaseDataSetOfInstances*,
						  DataSetOfInstancesClass*,
						  BaseDataAlgorithmRun*,
						  DataAlgorithmRunClass*) 
{
  bool result = true;
  return result;
}
/*F ans = ConcludeRun(instances,instancesclass,run,runclass)  . . . algorithm
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
bool BaseDataInstanceASCIIRead::ConcludeRun(BaseDataSetOfInstances*,
					    DataSetOfInstancesClass*,
					    BaseDataAlgorithmRun*,
					    DataAlgorithmRunClass* ) 
{
  return true;
}
/*S DataInstanceASCIIReadClass
 */
/*F DataInstanceASCIIReadClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataInstanceASCIIReadClass::DataInstanceASCIIReadClass()
{
  NameTag = INSTALGORITHMS_READASCII_NAME;
  Identification = INSTALGORITHMS_READASCII_ID;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = INSTALGORITHMS_READASCII_NAME;
} 
/*F DataInstanceASCIIReadClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataInstanceASCIIReadClass::DataInstanceASCIIReadClass(const DataInstanceASCIIReadClass& data)
  : DataAlgorithmOperationClass(data)
     // the rest
{
} 
 
/*F DataInstanceASCIIReadClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataInstanceASCIIReadClass::DataInstanceASCIIReadClass(const int id, 
						       const String& name,
						       const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = INSTALGORITHMS_READASCII_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataInstanceASCIIReadClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataInstanceASCIIReadClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  out << NameTag << "  ";
  // the rest
	   
       return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . . . . . DataInstanceASCIIReadClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataInstanceASCIIReadClass, there is no further information.
**
**  REMARKS
**
*/
bool DataInstanceASCIIReadClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  return DataAlgorithmOperationClass::Read(in,set);
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataInstanceASCIIReadClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataInstanceASCIIReadClass::CopyClone(Identify *  objc)
{
  DataInstanceASCIIReadClass *objcc = (DataInstanceASCIIReadClass *) objc;
  *this = *objcc;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataInstanceASCIIReadClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataInstanceASCIIReadClass::Clone()
{
  DataInstanceASCIIReadClass* id = new DataInstanceASCIIReadClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataInstanceASCIIReadClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataInstanceASCIIReadClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataInstanceASCIIReadClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataInstanceASCIIReadClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataInstanceASCIIReadClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataInstanceASCIIRead();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataInstanceASCIIReadClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataInstanceASCIIReadClass*& obj)
{
  obj = new DataInstanceASCIIReadClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataInstanceASCIIRead
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataInstanceASCIIRead*& obj)
{
  obj = new BaseDataInstanceASCIIRead;
  return obj->DecodeThis(buffer);
}
/*S BaseDataInstancesFromPredicate
 */ 
/*F BaseDataInstancesFromPredicate()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataInstancesFromPredicate::BaseDataInstancesFromPredicate()
  : instanceNameListS("InstanceNameList"),
    predicateListS("InstanceListFromPredicates")
{
  Identification = INSTALGORITHMS_PREDICATE_ID;
  NameTag = INSTALGORITHMS_PREDICATE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataInstancesFromPredicate(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataInstancesFromPredicate::BaseDataInstancesFromPredicate(const BaseDataInstancesFromPredicate& data)
  : BaseDataAlgorithmOperation(data),
    instanceNameListS(data.instanceNameListS),
    predicateListS(data.predicateListS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataInstancesFromPredicate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataInstancesFromPredicate::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataInstancesFromPredicate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataInstancesFromPredicate::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataInstancesFromPredicate
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataInstancesFromPredicate::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataInstancesFromPredicate
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataInstancesFromPredicate::Clone()
{
  BaseDataInstancesFromPredicate *obj = new BaseDataInstancesFromPredicate(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataInstancesFromPredicate
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataInstancesFromPredicate::CopyClone(Identify * obj)
{
  BaseDataInstancesFromPredicate *objfull = (BaseDataInstancesFromPredicate *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataInstancesFromPredicate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInstancesFromPredicate::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && Encode(buffer,instanceNameListS);
  result = result && Encode(buffer,predicateListS);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataInstancesFromPredicate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInstancesFromPredicate::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && Decode(buffer,instanceNameListS);
  result = result && Decode(buffer,predicateListS);
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
bool BaseDataInstancesFromPredicate::SetUpAlgorithms(BaseDataSetOfInstances*,
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
bool BaseDataInstancesFromPredicate::CheckInput(BaseDataSetOfInstances*,
						 DataSetOfInstancesClass*,
						 BaseDataAlgorithmRun *run,
						 DataAlgorithmRunClass*)
{
  bool result = true;

  if(run->ParameterInList(instanceNameListS))
    {
      if(run->ParameterInList(predicateListS))
	{
	}
      else
	{
	  cerr << "The list of predicates, '" << predicateListS << "' was not in the list of parameters";
	  result = false;
	}
    }
  else
    {
      cerr << "The list of instance names, '" << instanceNameListS << "' was not in the list of parameters";
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
bool BaseDataInstancesFromPredicate::SetUpInput(BaseDataSetOfInstances* instances,
						 DataSetOfInstancesClass* instancesclass,
						 BaseDataAlgorithmRun *run,
						 DataAlgorithmRunClass* rclass)
{
  bool result = true;

  instanceNameList = (BaseDataKeyWords *) run->ParameterValue(instanceNameListS);
  predicateList = (BaseDataKeyWords *) run->ParameterValue(predicateListS);
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
bool BaseDataInstancesFromPredicate::Calculate(BaseDataSetOfInstances *instances,
						DataSetOfInstancesClass *instclass,
						BaseDataAlgorithmRun *run,
						DataAlgorithmRunClass *runclass)
{
  bool result = true;
  ObjectList<String> inames = instanceNameList->GetKeyWords();
  ObjectList<String> pnames = predicateList->GetKeyWords();
  ObjectList<String>::iterator iname,pname;
  DataSetOfObjectsClass *classes = instclass->PointerToAllowedClasses();

  BaseDataParameterSet *params = new BaseDataParameterSet();
  DataParameterSetClass *paramclass = (DataParameterSetClass *) classes->GetObjectClass(params->GetType());
  DataInstanceClass *instcls = 
    (DataInstanceClass *) classes->GetObjectClass(INSTANCE_INSTANCE_ID);
  double cutoff = 0.5;
  for(pname = pnames.begin();pname != pnames.end();pname++)
    {
      ObjectList<String> truelist;
      if(instances->IsInList(*pname))
	{
	  BaseDataParameterizedFunction *pred = 
	    (BaseDataParameterizedFunction *) instances->GetObject(*pname);
	  unsigned int ptype = pred->GetType();
	  DataParameterizedFunctionClass *predclass = 
	    (DataParameterizedFunctionClass *) classes->GetObjectClass(ptype);
	  for(iname = inames.begin();iname != inames.end();iname++)
	    {
	      if(instances->InstanceInSet(*iname))
		{
		  BaseDataInstance *instance = instances->GetInstance(*iname);
		  BaseDataObject *object = pred->operator()(predclass,instance,params,instcls,paramclass);
		  if(instclass->IsOfClass(*object,LOGICAL_BASE_NAME))
		    {
		      BaseDataLogical *log = (BaseDataLogical *) object;
		      double value = log->GetValue();
		      if(runclass->getDebugLevel() > 1)
			cout << "PredValue: " << value;
		      if(value > cutoff)
			{
			  if(runclass->getDebugLevel() > 1)
			    cout << "      Added " << *iname << endl;
			  truelist.AddObject(*iname);
			}
		      else
			{
			  if(runclass->getDebugLevel() > 1)
			    cout << "  Not Added " << *iname << endl;
			}
		    }
		  else
		    {
		      cerr << "Result of predicate: " << *pname << " not logical" << endl;
		      result = false;
		    }
		}
	      else
		{
		  cerr << "Instance not found: " << *iname << endl;
		  result = false;
		}
	    }
	}
      else
	{
	  cerr << "Predicate not found: " << *pname << endl;
	  result = false;
	}
      String name(instanceNameListS);
      BaseDataKeyWords newlist(truelist);
      if(pname == pnames.begin())
	{
	  newlist.NameTag = name;
	  instances->AddObject(&newlist);
	}
      String delim("_");
      name.AppendToEnd(delim);
      name.AppendToEnd(*pname);
      newlist.NameTag = name;
      instances->AddObject(&newlist);
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
bool BaseDataInstancesFromPredicate::WriteOutputValues(BaseDataSetOfInstances*,
							DataSetOfInstancesClass*,
							BaseDataAlgorithmRun* run,
							DataAlgorithmRunClass*)
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
bool BaseDataInstancesFromPredicate::ConcludeRun(BaseDataSetOfInstances*,
						  DataSetOfInstancesClass*,
						  BaseDataAlgorithmRun*,
						  DataAlgorithmRunClass*)
{
  bool result = true;
//  delete something
  return result;
}
 
 
 
/*S DataInstancesFromPredicateClass
 */
/*F DataInstancesFromPredicateClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataInstancesFromPredicateClass::DataInstancesFromPredicateClass()
{
  Identification = INSTALGORITHMS_PREDICATE_ID;
  NameTag = INSTALGORITHMS_PREDICATE_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataInstancesFromPredicateClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataInstancesFromPredicateClass::DataInstancesFromPredicateClass(const DataInstancesFromPredicateClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataInstancesFromPredicateClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataInstancesFromPredicateClass::DataInstancesFromPredicateClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = INSTALGORITHMS_PREDICATE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataInstancesFromPredicateClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataInstancesFromPredicateClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataInstancesFromPredicateClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataInstancesFromPredicateClass, there is no further information.
**
**  REMARKS
**
*/
bool DataInstancesFromPredicateClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataInstancesFromPredicateClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataInstancesFromPredicateClass::CopyClone(Identify *  objc)
{
  DataInstancesFromPredicateClass *objcfull = (DataInstancesFromPredicateClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataInstancesFromPredicateClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataInstancesFromPredicateClass::Clone()
    {
      DataInstancesFromPredicateClass* id = new DataInstancesFromPredicateClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataInstancesFromPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataInstancesFromPredicateClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataInstancesFromPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataInstancesFromPredicateClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataInstancesFromPredicateClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataInstancesFromPredicate();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataInstancesFromPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataInstancesFromPredicateClass*& obj)
     {
     obj = new DataInstancesFromPredicateClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataInstancesFromPredicate
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataInstancesFromPredicate*& obj)
     {
     obj = new BaseDataInstancesFromPredicate;
     return obj->DecodeThis(buffer);
     }

/*S BaseDataMatrixGraphOutput
 */ 
/*F BaseDataMatrixGraphOutput()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataMatrixGraphOutput::BaseDataMatrixGraphOutput()
  : MatrixObjectS(MATRIX_OBJECT),
  RootNameS(ROOT_NAME),
  XcoordS(XCOORDINATE_NAME),
  YcoordsS(YCOORDINATES_NAME)
{
  Identification = INSTALGORITHMS_MATGRPOUTPUT_ID;
  NameTag = INSTALGORITHMS_MATGRPOUTPUT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataMatrixGraphOutput(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataMatrixGraphOutput::BaseDataMatrixGraphOutput(const BaseDataMatrixGraphOutput& data)
  : BaseDataAlgorithmOperation(data),
  MatrixObjectS(data.MatrixObjectS),
  RootNameS(data.RootNameS),
  XcoordS(data.XcoordS),
  YcoordsS(data.YcoordsS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataMatrixGraphOutput
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataMatrixGraphOutput::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataMatrixGraphOutput
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataMatrixGraphOutput::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataMatrixGraphOutput
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataMatrixGraphOutput::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  out << "Matrix Object Name:         " << MatrixObjectS << endl;
  out << "Root Name:                  " << RootNameS << endl;
  out << "X Coordinate Name:          " << XcoordS << endl;
  out << "Y Coordinate Name:          " << Ycoords << endl;

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataMatrixGraphOutput
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataMatrixGraphOutput::Clone()
{
  BaseDataMatrixGraphOutput *obj = new BaseDataMatrixGraphOutput(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataMatrixGraphOutput
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataMatrixGraphOutput::CopyClone(Identify * obj)
{
  BaseDataMatrixGraphOutput *objfull = (BaseDataMatrixGraphOutput *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMatrixGraphOutput
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMatrixGraphOutput::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && Encode(buffer,MatrixObjectS);
  result = result && Encode(buffer,RootNameS);
  result = result && Encode(buffer,XcoordS);
  result = result && Encode(buffer,YcoordsS);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMatrixGraphOutput
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMatrixGraphOutput::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && Decode(buffer,MatrixObjectS);
  result = result && Decode(buffer,RootNameS);
  result = result && Decode(buffer,XcoordS);
  result = result && Decode(buffer,YcoordsS);

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
bool BaseDataMatrixGraphOutput::SetUpAlgorithms(BaseDataSetOfInstances *instances,
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
bool BaseDataMatrixGraphOutput::CheckInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;

  if(run->ParameterInList(MatrixObjectS))
    {
      if(run->ParameterInList(RootNameS))
	{
	  if(run->ParameterInList(XcoordS))
	    {
	      if(run->ParameterInList(YcoordsS))
		{
		}
	      else
		{
		  cerr << "The list of Y coordinates parameter '" << YcoordsS  << "' was not in the list of parameters";
		  result = false;
		}
	    }
	  else
	    {
	      cerr << "The X coordinate parameter '" << Xcoord << "' was not in the list of parameters";
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
      cerr << "The matrix object parameter '" << MatrixObjectS << "' was not in the list of parameters";
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
bool BaseDataMatrixGraphOutput::SetUpInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;

  MatrixObject = (BaseDataInstanceDoubleMatrix *) run->ParameterValue(MatrixObjectS);
  RootName     = (BaseDataString *) run->ParameterValue(RootNameS);
  Xcoord       = (BaseDataString *) run->ParameterValue(XcoordS);
  Ycoords      = (BaseDataKeyWords *) run->ParameterValue(YcoordsS);
  
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
bool BaseDataMatrixGraphOutput::Calculate(BaseDataSetOfInstances *instances,
				 DataSetOfInstancesClass *instancesclass,
				 BaseDataAlgorithmRun *run,
				 DataAlgorithmRunClass *runclass)
{
  bool result = true;
  //if(run->AlgorithmSummary.KeyWordInList("")){}
  ObjectList<String> ynames = Ycoords->GetKeyWords();
  cout << "List of Y Coordinates: ";
  ynames.print(cout);
  cout << endl;

  cout << "X coordinate: " << endl;
  Xcoord->print(cout);
  cout << endl;
  cout << Xcoord->getString() << endl;

  unsigned int x = MatrixObject->CorrespondingColumn(Xcoord->getString());
  cout << "X coordinate position: " << x << endl;

  ObjectList<double> xcoords;
  unsigned int insize = MatrixObject->getInstanceNames().SizeOf();
  for(unsigned int i=0;i<insize;i++)
      xcoords.AddObject((MatrixObject->CurrentMatrix())[i][x]);
  cout << "X coordinate list:" << endl;
  xcoords.print(cout);
  cout << endl;

  outMatrix = MatrixObject->formReducedMatrix(Ycoords);
  /*
  cout << "Reduced Matrix" << endl;
  outMatrix->print(cout);
  cout << endl;
  */
  cout << "Plotting routine:" << endl;

  //String rName = RootName->getString();
  String rName("Report");
  cout  << rName << endl;

  cout << "outMatrix->size() Size1: " << outMatrix->size() << "(*outMatrix)[0].size()   Size2: " << (*outMatrix)[0].size() << endl;
  cout << "ynames.size(): " << ynames.size() << endl;

  matrixGnuPlotOut(*outMatrix,ynames,ynames.size(),15,rName,xcoords,2);

  cout << "Plotting routine done" << endl;
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
bool BaseDataMatrixGraphOutput::WriteOutputValues(BaseDataSetOfInstances *instances,
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
bool BaseDataMatrixGraphOutput::ConcludeRun(BaseDataSetOfInstances *instances,
				   DataSetOfInstancesClass *instancesclass,
				   BaseDataAlgorithmRun *run,
				   DataAlgorithmRunClass *runclass)
{
  bool result = true;
//  delete something
  return result;
}
 

 
/*S DataMatrixGraphOutputClass
 */
/*F DataMatrixGraphOutputClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataMatrixGraphOutputClass::DataMatrixGraphOutputClass()
{
  Identification = INSTALGORITHMS_MATGRPOUTPUT_ID;
  NameTag = INSTALGORITHMS_MATGRPOUTPUT_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataMatrixGraphOutputClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataMatrixGraphOutputClass::DataMatrixGraphOutputClass(const DataMatrixGraphOutputClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataMatrixGraphOutputClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataMatrixGraphOutputClass::DataMatrixGraphOutputClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = "MatrixGraphOutput";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataMatrixGraphOutputClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataMatrixGraphOutputClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataMatrixGraphOutputClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataMatrixGraphOutputClass, there is no further information.
**
**  REMARKS
**
*/
bool DataMatrixGraphOutputClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataMatrixGraphOutputClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataMatrixGraphOutputClass::CopyClone(Identify *  objc)
{
  DataMatrixGraphOutputClass *objcfull = (DataMatrixGraphOutputClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataMatrixGraphOutputClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataMatrixGraphOutputClass::Clone()
    {
      DataMatrixGraphOutputClass* id = new DataMatrixGraphOutputClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataMatrixGraphOutputClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMatrixGraphOutputClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataMatrixGraphOutputClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMatrixGraphOutputClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataMatrixGraphOutputClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataMatrixGraphOutput();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataMatrixGraphOutputClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataMatrixGraphOutputClass*& obj)
     {
     obj = new DataMatrixGraphOutputClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataMatrixGraphOutput
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataMatrixGraphOutput*& obj)
     {
     obj = new BaseDataMatrixGraphOutput;
     return obj->DecodeThis(buffer);
     }

/*S BaseDataReadMatrix
 */ 
/*F BaseDataReadMatrix()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataReadMatrix::BaseDataReadMatrix()
  : matrixReadClassParameterS(MATRIXREADCLASSPARAMETER),
    indexPrefixParameterS(INDEXPREFIX),
    fileNameParameterS(FILENAMEPARAMETER),
    matrixNameParameterS(MATRIX_OBJECT)
{
  Identification = INSTALGORITHMS_MATRIXREAD_ID;
  NameTag = INSTALGORITHMS_MATRIXREAD_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataReadMatrix(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataReadMatrix::BaseDataReadMatrix(const BaseDataReadMatrix& data)
  : BaseDataAlgorithmOperation(data),
    matrixReadClassParameterS(data.matrixReadClassParameterS),
    indexPrefixParameterS(data.indexPrefixParameterS),
    fileNameParameterS(data.fileNameParameterS),
    matrixNameParameterS(data.matrixNameParameterS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataReadMatrix
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataReadMatrix::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataReadMatrix
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataReadMatrix::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataReadMatrix
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataReadMatrix::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataReadMatrix
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataReadMatrix::Clone()
{
  BaseDataReadMatrix *obj = new BaseDataReadMatrix(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataReadMatrix
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataReadMatrix::CopyClone(Identify * obj)
{
  BaseDataReadMatrix *objfull = (BaseDataReadMatrix *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataReadMatrix
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataReadMatrix::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && Encode(buffer,matrixReadClassParameterS);
  result = result && Encode(buffer,indexPrefixParameterS);
  result = result && Encode(buffer,fileNameParameterS);
  result = result && Encode(buffer,matrixNameParameterS);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataReadMatrix
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataReadMatrix::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && Decode(buffer,matrixReadClassParameterS);
  result = result && Decode(buffer,indexPrefixParameterS);
  result = result && Decode(buffer,fileNameParameterS);
  result = result && Decode(buffer,matrixNameParameterS);

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
bool BaseDataReadMatrix::SetUpAlgorithms(BaseDataSetOfInstances *instances,
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
bool BaseDataReadMatrix::CheckInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;
  result = result && CheckInputVariable(matrixReadClassParameterS,"The Matrix read class",run);
  result = result && CheckInputVariable(indexPrefixParameterS,"The prefix for the indexed variable",run);
  result = result && CheckInputVariable(fileNameParameterS,"The file name of the matrix",run);
  result = result && CheckInputVariable(matrixNameParameterS,"The parameter name of the resulting matrix",run);
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
bool BaseDataReadMatrix::SetUpInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;

  BaseDataString *matrixReadClass = (BaseDataString *) run->ParameterValue(matrixReadClassParameterS);
  BaseDataString *indexPrefix = (BaseDataString *) run->ParameterValue(indexPrefixParameterS);
  BaseDataString *fileName = (BaseDataString *) run->ParameterValue(fileNameParameterS);
  BaseDataString *matrixName = (BaseDataString *) run->ParameterValue(matrixNameParameterS);
  
  MatrixClass = (DataProgressVariableMatrixClass *) 
    instancesclass->GetObjectClass(matrixReadClass->getString());
  Matrix = (BaseDataProgressVariableMatrix *) MatrixClass->BaseDataObjectExample();
  
  indexPrefixS = indexPrefix->getString();
  fileNameS = fileName->getString();
  matrixNameS = matrixName->getString();

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
bool BaseDataReadMatrix::Calculate(BaseDataSetOfInstances *instances,
				 DataSetOfInstancesClass *instancesclass,
				 BaseDataAlgorithmRun *run,
				 DataAlgorithmRunClass *runclass)
{
  bool result = true;
  OpenInputFile file(fileNameS);
  if(file.IfOpen()) {
    Matrix->Read(file.Stream,MatrixClass,indexPrefixS);
    Matrix->NameTag = matrixNameS;
    instances->AddObject(Matrix);
    } else {
    result = false;
    cerr << "Matrix not created" << endl;
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
bool BaseDataReadMatrix::WriteOutputValues(BaseDataSetOfInstances *instances,
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
bool BaseDataReadMatrix::ConcludeRun(BaseDataSetOfInstances *instances,
				   DataSetOfInstancesClass *instancesclass,
				   BaseDataAlgorithmRun *run,
				   DataAlgorithmRunClass *runclass)
{
  bool result = true;
//  delete something
  return result;
}
 

 
/*S DataReadMatrixClass
 */
/*F DataReadMatrixClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataReadMatrixClass::DataReadMatrixClass()
{
  Identification = INSTALGORITHMS_MATRIXREAD_ID;
  NameTag = INSTALGORITHMS_MATRIXREAD_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataReadMatrixClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataReadMatrixClass::DataReadMatrixClass(const DataReadMatrixClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataReadMatrixClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataReadMatrixClass::DataReadMatrixClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = "ReadMatrix";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataReadMatrixClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataReadMatrixClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataReadMatrixClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataReadMatrixClass, there is no further information.
**
**  REMARKS
**
*/
bool DataReadMatrixClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataReadMatrixClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataReadMatrixClass::CopyClone(Identify *  objc)
{
  DataReadMatrixClass *objcfull = (DataReadMatrixClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataReadMatrixClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataReadMatrixClass::Clone()
    {
      DataReadMatrixClass* id = new DataReadMatrixClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataReadMatrixClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataReadMatrixClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataReadMatrixClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataReadMatrixClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataReadMatrixClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataReadMatrix();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataReadMatrixClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataReadMatrixClass*& obj)
     {
     obj = new DataReadMatrixClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataReadMatrix
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataReadMatrix*& obj)
     {
     obj = new BaseDataReadMatrix;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataMatrixToInstances
 */ 
/*F BaseDataMatrixToInstances()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataMatrixToInstances::BaseDataMatrixToInstances()
  : matrixNameParameterS(MATRIX_OBJECT),
    realTypeParameterS(REALTYPEFORINSTANCEPARAMETER)
{
  Identification = INSTALGORITHMS_MATRIXINSTANCES_ID;
  NameTag = INSTALGORITHMS_MATRIXINSTANCES_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataMatrixToInstances(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataMatrixToInstances::BaseDataMatrixToInstances(const BaseDataMatrixToInstances& data)
  : BaseDataAlgorithmOperation(data),
    matrixNameParameterS(data.matrixNameParameterS),
    realTypeParameterS(data.realTypeParameterS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataMatrixToInstances
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataMatrixToInstances::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataMatrixToInstances
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataMatrixToInstances::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataMatrixToInstances
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataMatrixToInstances::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataMatrixToInstances
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataMatrixToInstances::Clone()
{
  BaseDataMatrixToInstances *obj = new BaseDataMatrixToInstances(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataMatrixToInstances
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataMatrixToInstances::CopyClone(Identify * obj)
{
  BaseDataMatrixToInstances *objfull = (BaseDataMatrixToInstances *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMatrixToInstances
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMatrixToInstances::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && Encode(buffer,matrixNameParameterS);
  result = result && Encode(buffer,realTypeParameterS);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMatrixToInstances
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMatrixToInstances::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && Decode(buffer,matrixNameParameterS);
  result = result && Decode(buffer,realTypeParameterS);
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
bool BaseDataMatrixToInstances::SetUpAlgorithms(BaseDataSetOfInstances *instances,
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
bool BaseDataMatrixToInstances::CheckInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;
  result = result && CheckInputVariable(matrixNameParameterS,"The parameter name of the resulting matrix",run);
  result = result && CheckInputVariable(realTypeParameterS,"The type of the real parameter in the instance",run);
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
bool BaseDataMatrixToInstances::SetUpInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;
  BaseDataString *realTypeS  = (BaseDataString *) run->ParameterValue(realTypeParameterS);
  BaseDataString *matrixName = (BaseDataString *) run->ParameterValue(matrixNameParameterS);

  matrixNameS = matrixName->getString();
  realType = (DataRealClass *) instancesclass->GetObjectClass(realTypeS->getString());

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
bool BaseDataMatrixToInstances::Calculate(BaseDataSetOfInstances *instances,
				 DataSetOfInstancesClass *instancesclass,
				 BaseDataAlgorithmRun *run,
				 DataAlgorithmRunClass *runclass)
{
  bool result = true;
  if(instances->IsInList(matrixNameS))
    {
      BaseDataInstanceDoubleMatrix *instmat = 
	(BaseDataInstanceDoubleMatrix *) instances->GetObject(matrixNameS);
      MatrixNumeric &mat = instmat->CurrentMatrix();
      BaseDataKeyWords &namekeys = instmat->getParameterNames();
      BaseDataKeyWords &instkeys = instmat->getInstanceNames();
      ObjectList<String> params = namekeys.GetKeyWords();
      ObjectList<String> insts  = instkeys.GetKeyWords();
      ObjectList<String>::iterator param,inst;
      unsigned int instcount = 0;
      BaseDataReal *number = (BaseDataReal *) realType->BaseDataObjectExample();
      for(inst = insts.begin(); inst != insts.end();inst++)
	{
	  BaseDataInstance *instance = new BaseDataInstance();
	  instance->NameTag = *inst;
	  instances->AddInstance(*instance);
	  delete instance;
	  instance = instances->GetInstance(*inst);
	  
	  unsigned int paramcount = 0;
	  for(param=params.begin();param != params.end();param++)
	    {
	      double val = mat[instcount][paramcount];
	      number->SetValue(val);
	      number->NameTag = *param;
	      instance->AddObject(number);
	      paramcount++;
	    }
	  instcount++;
	}
    } else {
      cerr << "Matrix Object: ':" << matrixNameS << "' not found in Attributes" << endl;
      result = false;
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
bool BaseDataMatrixToInstances::WriteOutputValues(BaseDataSetOfInstances *instances,
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
bool BaseDataMatrixToInstances::ConcludeRun(BaseDataSetOfInstances *instances,
				   DataSetOfInstancesClass *instancesclass,
				   BaseDataAlgorithmRun *run,
				   DataAlgorithmRunClass *runclass)
{
  bool result = true;
//  delete something
  return result;
}
 

 
/*S DataMatrixToInstancesClass
 */
/*F DataMatrixToInstancesClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataMatrixToInstancesClass::DataMatrixToInstancesClass()
{
  Identification = INSTALGORITHMS_MATRIXINSTANCES_ID;
  NameTag = INSTALGORITHMS_MATRIXINSTANCES_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataMatrixToInstancesClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataMatrixToInstancesClass::DataMatrixToInstancesClass(const DataMatrixToInstancesClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataMatrixToInstancesClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataMatrixToInstancesClass::DataMatrixToInstancesClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = "MatrixToInstances";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataMatrixToInstancesClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataMatrixToInstancesClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataMatrixToInstancesClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataMatrixToInstancesClass, there is no further information.
**
**  REMARKS
**
*/
bool DataMatrixToInstancesClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataMatrixToInstancesClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataMatrixToInstancesClass::CopyClone(Identify *  objc)
{
  DataMatrixToInstancesClass *objcfull = (DataMatrixToInstancesClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataMatrixToInstancesClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataMatrixToInstancesClass::Clone()
    {
      DataMatrixToInstancesClass* id = new DataMatrixToInstancesClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataMatrixToInstancesClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMatrixToInstancesClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataMatrixToInstancesClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMatrixToInstancesClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataMatrixToInstancesClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataMatrixToInstances();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataMatrixToInstancesClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataMatrixToInstancesClass*& obj)
     {
     obj = new DataMatrixToInstancesClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataMatrixToInstances
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataMatrixToInstances*& obj)
     {
     obj = new BaseDataMatrixToInstances;
     return obj->DecodeThis(buffer);
     }


/*S Utility
 */ 
/*F AddInstanceAlgorithmsClasses(set) . . . . . . . . . . . . add new classes
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AddInstanceAlgorithmsClasses(DataSetOfObjectsClass& set)
{
  String readdescr("Algorithm: Read in Instances");
  String attrdescr("Algorithm: SetUp Attribute List");
  String instdescr("Algorithm: SetUp Instance List");
  String matrdescr("Algorithm: Build a Matrix");
  String preddescr("Algorithm: Instance List from Predicate");
  String rdmatdescr("Algorithm: Read in a Matrix");
  
  DataInstanceASCIIReadClass readclass(INSTALGORITHMS_READASCII_ID,INSTALGORITHMS_READASCII_NAME,readdescr);
  DataAttributeSetUpClass attrclass(INSTALGORITHMS_ATTRIBUTES_ID,INSTALGORITHMS_ATTRIBUTES_NAME,attrdescr);
  DataInstanceSetUpClass instclass(INSTALGORITHMS_INSTANCES_ID,INSTALGORITHMS_INSTANCES_NAME,instdescr);
  DataMatrixSetUpClass matrclass(INSTALGORITHMS_MATRIX_ID,INSTALGORITHMS_MATRIX_NAME,matrdescr);
  DataInstancesFromPredicateClass predclass(INSTALGORITHMS_PREDICATE_ID,INSTALGORITHMS_PREDICATE_NAME,preddescr);
  DataReadMatrixClass rdmatclass(INSTALGORITHMS_MATRIXREAD_ID,INSTALGORITHMS_MATRIXREAD_NAME,rdmatdescr);
  
  set.AddObjectClass(readclass);
  set.AddObjectClass(attrclass);
  set.AddObjectClass(instclass);
  set.AddObjectClass(matrclass);
  set.AddObjectClass(predclass);
  set.AddObjectClass(rdmatclass);

  String matoutdescr("The Matrix Output Algorithm Class");
  DataMatrixGraphOutputClass matoutclass(INSTALGORITHMS_MATGRPOUTPUT_ID,INSTALGORITHMS_MATGRPOUTPUT_NAME,matoutdescr);
  set.AddObjectClass(matoutclass);
  String m2idescr("Algorithm: Transfer matrix into instances");
  DataMatrixToInstancesClass m2iclass(INSTALGORITHMS_MATRIXINSTANCES_ID,INSTALGORITHMS_MATRIXINSTANCES_NAME,m2idescr);
  set.AddObjectClass(m2iclass);

}
/*F InitialInstanceAlgorithmsEncodeDecodeRoutines() . . .  instance algorithm
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialInstanceAlgorithmsEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataAttributeSetUpClass,BaseDataAttributeSetUp,INSTALGORITHMS_ATTRIBUTES_NAME);
  EncodeDecodeRegisterClass(DataInstanceSetUpClass,BaseDataInstanceSetUp,INSTALGORITHMS_INSTANCES_NAME);
  EncodeDecodeRegisterClass(DataMatrixSetUpClass,BaseDataMatrixSetUp,INSTALGORITHMS_MATRIX_NAME);
  EncodeDecodeRegisterClass(DataInstanceASCIIReadClass,BaseDataInstanceASCIIRead,INSTALGORITHMS_READASCII_NAME);
  EncodeDecodeRegisterClass(DataInstancesFromPredicateClass,BaseDataInstancesFromPredicate,INSTALGORITHMS_PREDICATE_NAME);
  EncodeDecodeRegisterClass(DataMatrixGraphOutputClass,BaseDataMatrixGraphOutput,INSTALGORITHMS_MATGRPOUTPUT_NAME);
  EncodeDecodeRegisterClass(DataReadMatrixClass,BaseDataReadMatrix,INSTALGORITHMS_MATRIXREAD_NAME);
  EncodeDecodeRegisterClass(DataMatrixToInstancesClass,BaseDataMatrixToInstances,INSTALGORITHMS_MATRIXINSTANCES_NAME);
}

