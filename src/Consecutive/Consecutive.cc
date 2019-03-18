/*  FILE     Consecutive.cc
**  PACKAGE  Consecutive
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "Consecutive" package.
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
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "InstanceAlgorithms.hh"
#include "PredicateObjects.hh"
#include "EvaluationTree.hh"
#include "ClusterTree.hh"
#include "Consecutive.hh"

/*S BaseDataClusterInstanceSets
 */ 
/*F BaseDataClusterInstanceSets()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataClusterInstanceSets::BaseDataClusterInstanceSets()
  : ClusterS(CLUSTER_NAME),
    RootNameS(ROOT_NAME)
{
  Identification = CONSECUTIVE_INSTSET_ID;
  NameTag = CONSECUTIVE_INSTSET_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataClusterInstanceSets(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataClusterInstanceSets::BaseDataClusterInstanceSets(const BaseDataClusterInstanceSets& data)
  : BaseDataAlgorithmOperation(data),
    ClusterS(data.ClusterS),
    RootNameS(data.RootNameS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataClusterInstanceSets
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataClusterInstanceSets::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataClusterInstanceSets
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataClusterInstanceSets::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataClusterInstanceSets
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataClusterInstanceSets::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  out << "ClusterTree       " << ClusterS << endl;
  out << "RootName          " << RootNameS << endl;

  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataClusterInstanceSets
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataClusterInstanceSets::Clone()
{
  BaseDataClusterInstanceSets *obj = new BaseDataClusterInstanceSets(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataClusterInstanceSets
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataClusterInstanceSets::CopyClone(Identify * obj)
{
  BaseDataClusterInstanceSets *objfull = (BaseDataClusterInstanceSets *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataClusterInstanceSets
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataClusterInstanceSets::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && Encode(buffer,ClusterS);
  result = result && Encode(buffer,RootNameS);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataClusterInstanceSets
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataClusterInstanceSets::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && Decode(buffer,ClusterS);
  result = result && Decode(buffer,RootNameS);
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
bool BaseDataClusterInstanceSets::SetUpAlgorithms(BaseDataSetOfInstances *instances,
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
bool BaseDataClusterInstanceSets::CheckInput(BaseDataSetOfInstances *instances,
					     DataSetOfInstancesClass *instancesclass,
					     BaseDataAlgorithmRun *run,
					     DataAlgorithmRunClass *runclass)
{
  bool result = true;

  if(run->ParameterInList(ClusterS)){
    if(run->ParameterInList(RootNameS)) {
    } else {
      cerr << "The root name parameter '" << RootNameS << "' was not in the list of parameters";
      result = false;
    }
  } else {
    cerr << "The cluster tree parameter '" << ClusterS << "' was not in the list of parameters";
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
bool BaseDataClusterInstanceSets::SetUpInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;
  BaseDataString *clustername = (BaseDataString *) run->ParameterValue(ClusterS);
  if(instances->IsInList(clustername->getString()))
    {
      Cluster = (BaseDataClusterTree *) instances->GetObject(clustername->getString());
      RootName = (BaseDataString *) run->ParameterValue(RootNameS);
    }
  else
    {
      cerr << "Cluster Tree '" << clustername->getString() << "' not found in attributes" << endl;
      result = false;
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
bool BaseDataClusterInstanceSets::Calculate(BaseDataSetOfInstances *instances,
					    DataSetOfInstancesClass *instancesclass,
					    BaseDataAlgorithmRun *run,
					    DataAlgorithmRunClass *runclass)
{
  bool result = true;
  BaseDataClusterNode *rootnode = (BaseDataClusterNode *) Cluster->Tree.getRootNode();
  String totalinstancesS(RootName->getString());
  String totalnameS(INSTANCE_NAME_LIST);
  totalinstancesS.AppendToEnd(totalnameS);
  BaseDataKeyWords *elements = getNames(rootnode,totalinstancesS);
  ClusterSetNames = new BaseDataKeyWords();
  ClusterSetNames->NameTag = CLUSTERSETS;

  instances->AddObject(elements);
  delete elements;

  TraverseSons(rootnode,instances);
  instances->AddObject(ClusterSetNames);
  run->AddParameter(ClusterSetNames);

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
bool BaseDataClusterInstanceSets::WriteOutputValues(BaseDataSetOfInstances *instances,
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
bool BaseDataClusterInstanceSets::ConcludeRun(BaseDataSetOfInstances *instances,
					      DataSetOfInstancesClass *instancesclass,
					      BaseDataAlgorithmRun *run,
					      DataAlgorithmRunClass *runclass)
{
  bool result = true;
  delete ClusterSetNames;
//  delete something
  return result;
}
 
/*F keynames = getNames(node) 
**
**  DESCRIPTION
**    node: The node from which to extract the names
**    keynames: The names of the elements
**
**  REMARKS
**
*/
BaseDataKeyWords *BaseDataClusterInstanceSets::getNames(BaseDataClusterNode *node, String& name)
{
  ObjectList<String> names = node->ElementClusterAssignment.ListOfObjectNames();
  BaseDataKeyWords *keynames = new BaseDataKeyWords(names);
  keynames->NameTag = name;

  return keynames;
} 
 
/*F TraverseSons(node,instances)  . . . . . . . . BaseDataClusterInstanceSets
**
**  DESCRIPTION
**    npde: The node
**    instances: The set of instances
**
**    The element names of the node are stored as an attribute in the set of instances
**    and then the sons are traversed in an recursive call
**
**  REMARKS
**
*/
void BaseDataClusterInstanceSets::TraverseSons(BaseDataClusterNode *node,
					       BaseDataSetOfInstances *instances)
{
  String clusternameS(RootName->getString());
  clusternameS.AppendToEnd(node->NameTag);

  BaseDataKeyWords *elements = getNames(node,clusternameS);
  ClusterSetNames->AddKeyWord(elements->NameTag);

  instances->AddObject(elements);
  ObjectList<String> *sons = Cluster->Tree.GetSons(node->NameTag);
  ObjectList<String>::iterator son;
  for(son = sons->begin(); son != sons->end(); son++)
    {
      BaseDataClusterNode *sonnode = (BaseDataClusterNode *) Cluster->Tree.GetNode(*son);
      TraverseSons(sonnode,instances);
    }
  delete sons;
}
/*S DataClusterInstanceSetsClass
 */
/*F DataClusterInstanceSetsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataClusterInstanceSetsClass::DataClusterInstanceSetsClass()
{
  Identification = CONSECUTIVE_INSTSET_ID;
  NameTag = CONSECUTIVE_INSTSET_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataClusterInstanceSetsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataClusterInstanceSetsClass::DataClusterInstanceSetsClass(const DataClusterInstanceSetsClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataClusterInstanceSetsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataClusterInstanceSetsClass::DataClusterInstanceSetsClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = "ClusterInstanceSets";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataClusterInstanceSetsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataClusterInstanceSetsClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataClusterInstanceSetsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataClusterInstanceSetsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataClusterInstanceSetsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataClusterInstanceSetsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataClusterInstanceSetsClass::CopyClone(Identify *  objc)
{
  DataClusterInstanceSetsClass *objcfull = (DataClusterInstanceSetsClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataClusterInstanceSetsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataClusterInstanceSetsClass::Clone()
    {
      DataClusterInstanceSetsClass* id = new DataClusterInstanceSetsClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataClusterInstanceSetsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataClusterInstanceSetsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataClusterInstanceSetsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataClusterInstanceSetsClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataClusterInstanceSetsClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataClusterInstanceSets();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataClusterInstanceSetsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataClusterInstanceSetsClass*& obj)
     {
     obj = new DataClusterInstanceSetsClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataClusterInstanceSets
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataClusterInstanceSets*& obj)
     {
     obj = new BaseDataClusterInstanceSets;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataConsecutiveSeries
 */ 
/*F BaseDataConsecutiveSeries()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataConsecutiveSeries::BaseDataConsecutiveSeries()
  : NumberOfElements(0)
{
  Identification = CONSECUTIVE_SERIES_ID;
  NameTag = CONSECUTIVE_SERIES_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  
  GapList.NameTag = "GapList";
} 
/*F BaseDataConsecutiveSeries(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataConsecutiveSeries::BaseDataConsecutiveSeries(const BaseDataConsecutiveSeries& data)
  : BaseDataSetOfObjects(data),
    Top(data.Top),
    Bottom(data.Bottom),
    GapList(data.GapList),
    NumberOfElements(data.NumberOfElements)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataConsecutiveSeries
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataConsecutiveSeries::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataConsecutiveSeries
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataConsecutiveSeries::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataSetOfObjects::Read(in,objc,name);  
  StreamObjectInput str(in,' ');
  Top = str.ReadNext();
  Bottom = str.ReadNext();
  DataKeyWordsClass keyclass;
  String gapname("GapList");
  GapList.Read(in,&keyclass,gapname);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataConsecutiveSeries
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataConsecutiveSeries::print(ostream& out) const
{
  BaseDataSetOfObjects::print(out);
  out << "Number of Elements In Matched Set: " << NumberOfElements << endl;
  Bottom.print(out);
  out << endl;
  Top.print(out);
  out << endl;
  GapList.print(out);
  out << endl;

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataConsecutiveSeries
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataConsecutiveSeries::Clone()
{
  BaseDataConsecutiveSeries *obj = new BaseDataConsecutiveSeries(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataConsecutiveSeries
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataConsecutiveSeries::CopyClone(Identify * obj)
{
  BaseDataConsecutiveSeries *objfull = (BaseDataConsecutiveSeries *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataConsecutiveSeries
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataConsecutiveSeries::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::EncodeThis(buffer);
  result = result && Encode(buffer,NumberOfElements);
  result = result && Encode(buffer,Top);
  result = result && Encode(buffer,Bottom);
  result = result && GapList.EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataConsecutiveSeries
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataConsecutiveSeries::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::DecodeThis(buffer);
  result = result && Decode(buffer,NumberOfElements);
  result = result && Decode(buffer,Top);
  result = result && Decode(buffer,Bottom);
  result = result && GapList.DecodeThis(buffer);
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
bool BaseDataConsecutiveSeries::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << NameTag << "   Top: " << Top << " Bottom: " << Bottom;
  out << "  Elements: " << NumberOfElements << " Gaps: " << GapList.SizeOf() << " ";
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
bool BaseDataConsecutiveSeries::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  out << NameTag << "   Top: " << Top << " Bottom: " << Bottom << endl;
  out << "      Elements: " << NumberOfElements << " Gaps: " << GapList.SizeOf() << " ";
  out << endl;
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
bool BaseDataConsecutiveSeries::WriteAsLatex(ostream& out, DataObjectClass* cls)
{
  out << NameTag << " & " << Top << " & " << Bottom;
  out << "  & " << NumberOfElements << " & " << GapList.SizeOf() << "\\\\\\hline ";
  out << endl;
  return true;
}

/*S DataConsecutiveSeriesClass
 */
/*F DataConsecutiveSeriesClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataConsecutiveSeriesClass::DataConsecutiveSeriesClass()
{
  Identification = CONSECUTIVE_SERIES_ID;
  NameTag = CONSECUTIVE_SERIES_NAME;
  SubClass = "SetOfObjects";
  EncodeDecodeClass = NameTag;
} 
/*F DataConsecutiveSeriesClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataConsecutiveSeriesClass::DataConsecutiveSeriesClass(const DataConsecutiveSeriesClass& data)
  : DataSetOfObjectsClass(data)
{
} 
 
/*F DataConsecutiveSeriesClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataConsecutiveSeriesClass::DataConsecutiveSeriesClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataSetOfObjectsClass(id,name,descr)
{
  SubClass = "SetOfObjects";
  EncodeDecodeClass = "ConsecutiveSeries";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataConsecutiveSeriesClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataConsecutiveSeriesClass::print(ostream& out) const
{
  DataSetOfObjectsClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataConsecutiveSeriesClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataConsecutiveSeriesClass, there is no further information.
**
**  REMARKS
**
*/
bool DataConsecutiveSeriesClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataSetOfObjectsClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataConsecutiveSeriesClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataConsecutiveSeriesClass::CopyClone(Identify *  objc)
{
  DataConsecutiveSeriesClass *objcfull = (DataConsecutiveSeriesClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataConsecutiveSeriesClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataConsecutiveSeriesClass::Clone()
    {
      DataConsecutiveSeriesClass* id = new DataConsecutiveSeriesClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataConsecutiveSeriesClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataConsecutiveSeriesClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataConsecutiveSeriesClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataConsecutiveSeriesClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::DecodeThis(buffer);
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
BaseDataObject * DataConsecutiveSeriesClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataConsecutiveSeries();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataConsecutiveSeriesClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataConsecutiveSeriesClass*& obj)
     {
     obj = new DataConsecutiveSeriesClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataConsecutiveSeries
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataConsecutiveSeries*& obj)
     {
     obj = new BaseDataConsecutiveSeries;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataConsecutiveSeriesSet
 */ 
/*F BaseDataConsecutiveSeriesSet()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataConsecutiveSeriesSet::BaseDataConsecutiveSeriesSet()
{
  Identification = CONSECUTIVE_SERIESSET_ID;
  NameTag = CONSECUTIVE_SERIESSET_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataConsecutiveSeriesSet(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataConsecutiveSeriesSet::BaseDataConsecutiveSeriesSet(const BaseDataConsecutiveSeriesSet& data)
  : BaseDataSetOfObjects(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataConsecutiveSeriesSet
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataConsecutiveSeriesSet::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataConsecutiveSeriesSet
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataConsecutiveSeriesSet::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataSetOfObjects::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataConsecutiveSeriesSet
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataConsecutiveSeriesSet::print(ostream& out) const
{
  BaseDataSetOfObjects::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataConsecutiveSeriesSet
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataConsecutiveSeriesSet::Clone()
{
  BaseDataConsecutiveSeriesSet *obj = new BaseDataConsecutiveSeriesSet(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataConsecutiveSeriesSet
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataConsecutiveSeriesSet::CopyClone(Identify * obj)
{
  BaseDataConsecutiveSeriesSet *objfull = (BaseDataConsecutiveSeriesSet *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataConsecutiveSeriesSet
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataConsecutiveSeriesSet::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataConsecutiveSeriesSet
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataConsecutiveSeriesSet::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::DecodeThis(buffer);
  // The rest

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
bool BaseDataConsecutiveSeriesSet::WriteAsLine(ostream& out, DataObjectClass *objc)
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
bool BaseDataConsecutiveSeriesSet::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  DataConsecutiveSeriesSetClass *seriesclass = (DataConsecutiveSeriesSetClass *) objc;
  DataSetOfObjectsClass *classes = seriesclass->PointerToAllowedClasses();
  out << "Consecutive Sets:" << endl;
  ObjectList<String> names = ListOfObjectNames();
  for(ObjectList<String>::iterator name = names.begin();
      name != names.end();
      name++)
    {
      BaseDataConsecutiveSeriesSet *obj = (BaseDataConsecutiveSeriesSet *) GetObject(*name);
      DataConsecutiveSeriesSetClass *objclass = (DataConsecutiveSeriesSetClass *) classes->GetObjectClass(obj->GetType());
      obj->WriteAsASCII(out,objclass);
      out << endl;
    }
  out << "END" << endl;
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
bool BaseDataConsecutiveSeriesSet::WriteAsLatex(ostream& out, DataObjectClass* cls)
{
  DataConsecutiveSeriesSetClass *seriesclass = (DataConsecutiveSeriesSetClass *) cls;
  DataSetOfObjectsClass *classes = seriesclass->PointerToAllowedClasses();
  out << "\\begin{tabular}{|l|l|l|c|c|}\\\\hline" << endl;
  out << "Name   & Top & Bottom & Elements & Gaps \\\\\\hline" << endl;

  ObjectList<String> names = ListOfObjectNames();
  for(ObjectList<String>::iterator name = names.begin();
      name != names.end();
      name++)
    {
      BaseDataConsecutiveSeriesSet *obj = (BaseDataConsecutiveSeriesSet *) GetObject(*name);
      DataConsecutiveSeriesSetClass *objclass = (DataConsecutiveSeriesSetClass *) classes->GetObjectClass(obj->GetType());
      obj->WriteAsLatex(out,objclass);
      out << endl;
    }
  out << "\\end{tabular}" << endl;
  return true;
}

/*S DataConsecutiveSeriesSetClass
 */
/*F DataConsecutiveSeriesSetClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataConsecutiveSeriesSetClass::DataConsecutiveSeriesSetClass()
{
  Identification = CONSECUTIVE_SERIESSET_ID;
  NameTag = CONSECUTIVE_SERIESSET_NAME;
  SubClass = "SetOfObjects";
  EncodeDecodeClass = NameTag;
} 
/*F DataConsecutiveSeriesSetClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataConsecutiveSeriesSetClass::DataConsecutiveSeriesSetClass(const DataConsecutiveSeriesSetClass& data)
  : DataSetOfObjectsClass(data)
{
} 
 
/*F DataConsecutiveSeriesSetClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataConsecutiveSeriesSetClass::DataConsecutiveSeriesSetClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataSetOfObjectsClass(id,name,descr)
{
  SubClass = "SetOfObjects";
  EncodeDecodeClass = "ConsecutiveSeriesSet";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataConsecutiveSeriesSetClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataConsecutiveSeriesSetClass::print(ostream& out) const
{
  DataSetOfObjectsClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataConsecutiveSeriesSetClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataConsecutiveSeriesSetClass, there is no further information.
**
**  REMARKS
**
*/
bool DataConsecutiveSeriesSetClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataSetOfObjectsClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataConsecutiveSeriesSetClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataConsecutiveSeriesSetClass::CopyClone(Identify *  objc)
{
  DataConsecutiveSeriesSetClass *objcfull = (DataConsecutiveSeriesSetClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataConsecutiveSeriesSetClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataConsecutiveSeriesSetClass::Clone()
    {
      DataConsecutiveSeriesSetClass* id = new DataConsecutiveSeriesSetClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataConsecutiveSeriesSetClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataConsecutiveSeriesSetClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataConsecutiveSeriesSetClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataConsecutiveSeriesSetClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::DecodeThis(buffer);
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
BaseDataObject * DataConsecutiveSeriesSetClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataConsecutiveSeriesSet();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataConsecutiveSeriesSetClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataConsecutiveSeriesSetClass*& obj)
     {
     obj = new DataConsecutiveSeriesSetClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataConsecutiveSeriesSet
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataConsecutiveSeriesSet*& obj)
     {
     obj = new BaseDataConsecutiveSeriesSet;
     return obj->DecodeThis(buffer);
     }
/*F objc = PointerToAllowedClasses()  . . . .  the allowed set of class types
**
**  DESCRIPTION
**    objc: The pointer to the allowed classes
**  REMARKS
**
*/
DataSetOfObjectsClass*  DataConsecutiveSeriesSetClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}

/*S BaseDataConsecutive
 */ 
/*F BaseDataConsecutive()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataConsecutive::BaseDataConsecutive()
  : RootNameS(CONSECUTIVE),
    InstanceNameListS(INSTANCE_NAME_LIST),
    ClusterSetsS(CLUSTERSETS),
    MaximumGapS(MAXIMUMGAP),
    MinimumS(MINIMUMELEMENTS)
{
  Identification = CONSECUTIVE_ALGORITHM_ID;
  NameTag = CONSECUTIVE_ALGORITHM_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataConsecutive(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataConsecutive::BaseDataConsecutive(const BaseDataConsecutive& data)
  : BaseDataAlgorithmOperation(data),
    RootNameS(data.RootNameS),
    InstanceNameListS(data.InstanceNameListS),
    ClusterSetsS(data.ClusterSetsS),
    MaximumGapS(data.MaximumGapS),
    MinimumS(data.MinimumS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataConsecutive
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataConsecutive::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataConsecutive
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataConsecutive::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataConsecutive
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataConsecutive::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  out << "RootName:          " << RootNameS << endl;
  out << "InstanceNameList:  " << InstanceNameListS << endl;
  out << "ClusterSet:        " << ClusterSetsS << endl;
  out << "MaximumGap:        " << MaximumGapS << endl;
  out << "Minimum            " << MinimumS << endl;

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataConsecutive
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataConsecutive::Clone()
{
  BaseDataConsecutive *obj = new BaseDataConsecutive(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataConsecutive
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataConsecutive::CopyClone(Identify * obj)
{
  BaseDataConsecutive *objfull = (BaseDataConsecutive *) obj;
  *this = *objfull;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataConsecutive
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataConsecutive::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && Encode(buffer,RootNameS);
  result = result && Encode(buffer,InstanceNameListS);
  result = result && Encode(buffer,ClusterSetsS);
  result = result && Encode(buffer,MaximumGapS);
  result = result && Encode(buffer,MinimumS);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataConsecutive
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataConsecutive::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && Decode(buffer,RootNameS);
  result = result && Decode(buffer,InstanceNameListS);
  result = result && Decode(buffer,ClusterSetsS);
  result = result && Decode(buffer,MaximumGapS);
  result = result && Decode(buffer,MinimumS);
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
bool BaseDataConsecutive::SetUpAlgorithms(BaseDataSetOfInstances *instances,
				       DataSetOfInstancesClass *instancesclass,
				       BaseDataAlgorithmRun *run,
				       DataAlgorithmRunClass *runclass)
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
bool BaseDataConsecutive::CheckInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;

  if(run->ParameterInList(InstanceNameListS))
    {
      if(run->ParameterInList(ClusterSetsS))
	{
	  if(run->ParameterInList(MaximumGapS))
	    {
	      if(run->ParameterInList(MinimumS))
		{
		}
	      else
		{
		  cerr << "The minimum cluster parameter '" << MinimumS << "' was not in the list of parameters";
		  result = false;
	    }
	    }
	  else
	    {
	      cerr << "The maximum gap parameter '" << MaximumGapS << "' was not in the list of parameters";
	      result = false;
	    }
	}
      else
	{
	  cerr << "The cluster set list parameter '" << ClusterSetsS << "' was not in the list of parameters";
	  result = false;
	}
    }
  else
    {
      cerr << "The total instance name list parameter '" << InstanceNameListS << "' was not in the list of parameters";
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
bool BaseDataConsecutive::SetUpInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;
  
  InstanceNameList = (BaseDataKeyWords *) run->ParameterValue(InstanceNameListS);
  ClusterSets      = (BaseDataKeyWords *) run->ParameterValue(ClusterSetsS);
  MaximumGap       = (BaseDataInteger *)  run->ParameterValue(MaximumGapS);
  Minimum          = (BaseDataInteger *)  run->ParameterValue(MinimumS);
  maximumGap = MaximumGap->GetValue();
  minimum = Minimum->GetValue();

  cout << "Minimum Number of Elements: " << minimum << endl;

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
bool BaseDataConsecutive::Calculate(BaseDataSetOfInstances *instances,
				 DataSetOfInstancesClass *instancesclass,
				 BaseDataAlgorithmRun *run,
				 DataAlgorithmRunClass *runclass)
{
  bool result = true;
  //if(run->AlgorithmSummary.KeyWordInList("")){}

  ConsecutiveSets = (BaseDataConsecutiveSeriesSet *) new BaseDataConsecutiveSeriesSet();
  BaseDataKeyWords *clustersets = (BaseDataKeyWords *) ClusterSets->Clone();
  unsigned int subseries;
  while(clustersets->SizeOf())
    {
      subseries = 0;
      String cluster = clustersets->NextKey();
      BaseDataKeyWords *nodenames = (BaseDataKeyWords *) instances->GetObject(cluster);
      ObjectList<String> names = InstanceNameList->GetKeyWords();
      ObjectList<String>::iterator firstname = names.begin();
      while(firstname != names.end() && !(nodenames->KeyWordInList(*firstname))) 
	firstname++;
      BaseDataConsecutiveSeries *series = new BaseDataConsecutiveSeries();
      series->Bottom = *firstname;
      series->Top = *firstname;
      unsigned int gap = 0;
      ObjectList<String> *gaplist = new ObjectList<String>();
      for(ObjectList<String>::iterator name = firstname; name != names.end(); name++)
	{
	  if(!nodenames->KeyWordInList(*name))
	    {
	      gap++;
	      gaplist->AddObject(*name);
	    }
	  else if(gap > 0)
	    {
	      series->NumberOfElements++;
	      series->Top = *name;
	      for(ObjectList<String>::iterator gapname = gaplist->begin(); 
		  gapname != gaplist->end(); gapname++)
		{
		  series->GapList.AddKeyWord(*gapname);
		}
	      delete gaplist;
	      gaplist = new ObjectList<String>();
	      gap = 0;
	    }
	  else
	    {
	      series->NumberOfElements++;
	      series->Top = *name;
	    }
	  if(gap > maximumGap)
	    {
	      delete gaplist;
	      gaplist = new ObjectList<String>();
	      gap = 0;
	      subseries++;
	      if(series->NumberOfElements > minimum)
		{
		  AddNameTagToSeries(series,cluster,subseries);
		  ConsecutiveSets->AddObject(series);
		}
	      else
		{
		}
	      while(name != names.end() &&  !(nodenames->KeyWordInList(*name)))
		name++;
	      if(name != names.end())
		{
		  if(!(name == names.end()))
		    {
		      delete series;
		      series = new BaseDataConsecutiveSeries();
		      series->Bottom = *name;
		      series->Top = *name;
		    }
		}
	      else
		{
		  name--;
		}
	    }
	}
      if(series->NumberOfElements == 0)
	series->NumberOfElements = 1;

      if(series->NumberOfElements > minimum)
	{
	  AddNameTagToSeries(series,cluster,subseries);
	  ConsecutiveSets->AddObject(series);
	}
      else
	{
	}
      delete series;
    }

  return result;
}
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataConsecutive::AddNameTagToSeries(BaseDataConsecutiveSeries *series,
					     String& cluster, unsigned int subseries)
{
  series->NameTag = cluster;
  if(subseries > 0)
    {
      String prefix("-");
      String num = PositveIntegerToString(subseries,prefix,3);
      series->NameTag.AppendToEnd(num);
    }
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
bool BaseDataConsecutive::WriteOutputValues(BaseDataSetOfInstances *instances,
					 DataSetOfInstancesClass *instancesclass,
					 BaseDataAlgorithmRun *run,
					 DataAlgorithmRunClass *runclass)
{
  bool result = true;
  ConsecutiveSets->NameTag = CONSECUTIVESET;
  run->AddParameter(ConsecutiveSets);
  instances->AddObject(ConsecutiveSets);
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
bool BaseDataConsecutive::ConcludeRun(BaseDataSetOfInstances *instances,
				   DataSetOfInstancesClass *instancesclass,
				   BaseDataAlgorithmRun *run,
				   DataAlgorithmRunClass *runclass)
{
  bool result = true;
//  delete something
  return result;
}
/*S DataConsecutiveClass
 */
/*F DataConsecutiveClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataConsecutiveClass::DataConsecutiveClass()
{
  Identification = CONSECUTIVE_ALGORITHM_ID;
  NameTag = CONSECUTIVE_ALGORITHM_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataConsecutiveClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataConsecutiveClass::DataConsecutiveClass(const DataConsecutiveClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataConsecutiveClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataConsecutiveClass::DataConsecutiveClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = "Consecutive";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataConsecutiveClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataConsecutiveClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataConsecutiveClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataConsecutiveClass, there is no further information.
**
**  REMARKS
**
*/
bool DataConsecutiveClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataConsecutiveClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataConsecutiveClass::CopyClone(Identify *  objc)
{
  DataConsecutiveClass *objcfull = (DataConsecutiveClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataConsecutiveClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataConsecutiveClass::Clone()
    {
      DataConsecutiveClass* id = new DataConsecutiveClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataConsecutiveClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataConsecutiveClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataConsecutiveClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataConsecutiveClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataConsecutiveClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataConsecutive();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataConsecutiveClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataConsecutiveClass*& obj)
     {
     obj = new DataConsecutiveClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataConsecutive
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataConsecutive*& obj)
     {
     obj = new BaseDataConsecutive;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataSortElements
 */ 
/*F BaseDataSortElements()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSortElements::BaseDataSortElements()
  : InstanceNameListS(INSTANCE_NAME_LIST),
    SortParameterS(SORTPARAMETER)
{
  Identification = CONSECUTIVE_SORT_ID;
  NameTag = CONSECUTIVE_SORT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataSortElements(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataSortElements::BaseDataSortElements(const BaseDataSortElements& data)
  : BaseDataAlgorithmOperation(data),
    InstanceNameListS(data.InstanceNameListS),
    SortParameterS(data.SortParameterS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataSortElements
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataSortElements::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataSortElements
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataSortElements::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataSortElements
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataSortElements::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  out << "InstanceNameList:     " << InstanceNameListS << endl;
  out << "SortParameter:        " << SortParameterS << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataSortElements
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataSortElements::Clone()
{
  BaseDataSortElements *obj = new BaseDataSortElements(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataSortElements
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataSortElements::CopyClone(Identify * obj)
{
  BaseDataSortElements *objfull = (BaseDataSortElements *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSortElements
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSortElements::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && Encode(buffer,InstanceNameListS);
  result = result && Encode(buffer,SortParameterS);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSortElements
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSortElements::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && Decode(buffer,InstanceNameListS);
  result = result && Decode(buffer,SortParameterS);
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
bool BaseDataSortElements::SetUpAlgorithms(BaseDataSetOfInstances *instances,
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
bool BaseDataSortElements::CheckInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;

  if(run->ParameterInList(InstanceNameListS))
    {
      if(run->ParameterInList(SortParameterS))
	{
	}
      else
	{
	  cerr << "The sort parameter name in '" << SortParameterS << "' was not in the list of parameters";
	  result = false;
	}
    }
  else
    {
      cerr << "The instance names parameter '" << InstanceNameListS << "' was not in the list of parameters";
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
bool BaseDataSortElements::SetUpInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;

  InstanceNameList = (BaseDataKeyWords *) run->ParameterValue(InstanceNameListS);
  SortParameter    = (BaseDataString *) run->ParameterValue(SortParameterS);

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
bool BaseDataSortElements::Calculate(BaseDataSetOfInstances *instances,
				     DataSetOfInstancesClass *instancesclass,
				     BaseDataAlgorithmRun *run,
				     DataAlgorithmRunClass *runclass)
{
  bool result = true;
  String sortparam = SortParameter->getString();

  //if(run->AlgorithmSummary.KeyWordInList("")){}

  ObjectList<String> names = InstanceNameList->GetKeyWords();
  ObjectList<String> sorted;
  ObjectList<String>::iterator orig, newlistname;
  for(orig=names.begin();orig != names.end(); orig++)
    {
      BaseDataInstance *nextinstance = instances->GetInstance(*orig);
      BaseDataObject *nextobj = nextinstance->GetObject(sortparam);
      newlistname = sorted.begin();
      bool found = newlistname != sorted.end();
      while(found)
	{
	  if(instances->InstanceInSet(*newlistname)) {
	    BaseDataInstance *compinstance = instances->GetInstance(*newlistname);
	    if(compinstance->IsInList(sortparam)) {
	      BaseDataObject *compobj = compinstance->GetObject(sortparam);
	      if(compobj->operator>(nextobj))
		found = false;
	      if(found)
		newlistname++;
	    } else {
	      cerr << "In Instance: '" << *newlistname << "' sort parameter '" << sortparam << "' not found" << endl;
	    }
	  } else {
	    cerr << "Instance: '" << *newlistname << "' not in instances" << endl;
	  }
	    found = found && (newlistname != sorted.end());
	}
      sorted.insert(newlistname,*orig);
    }
  Sorted = new BaseDataKeyWords(sorted);
  Sorted->NameTag = INSTANCE_NAME_LIST;
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
bool BaseDataSortElements::WriteOutputValues(BaseDataSetOfInstances *instances,
					     DataSetOfInstancesClass *instancesclass,
					     BaseDataAlgorithmRun *run,
					     DataAlgorithmRunClass *runclass)
{
  bool result = true;
  instances->AddObject(Sorted);
  run->AddParameter(Sorted);

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
bool BaseDataSortElements::ConcludeRun(BaseDataSetOfInstances *instances,
				   DataSetOfInstancesClass *instancesclass,
				   BaseDataAlgorithmRun *run,
				   DataAlgorithmRunClass *runclass)
{
  bool result = true;
//  delete something
  return result;
}
 
 
 
/*S DataSortElementsClass
 */
/*F DataSortElementsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataSortElementsClass::DataSortElementsClass()
{
  Identification = CONSECUTIVE_SORT_ID;
  NameTag = CONSECUTIVE_SORT_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataSortElementsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataSortElementsClass::DataSortElementsClass(const DataSortElementsClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataSortElementsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataSortElementsClass::DataSortElementsClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = "SortElements";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataSortElementsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataSortElementsClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataSortElementsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataSortElementsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataSortElementsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataSortElementsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataSortElementsClass::CopyClone(Identify *  objc)
{
  DataSortElementsClass *objcfull = (DataSortElementsClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataSortElementsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataSortElementsClass::Clone()
    {
      DataSortElementsClass* id = new DataSortElementsClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataSortElementsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSortElementsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataSortElementsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSortElementsClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataSortElementsClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataSortElements();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataSortElementsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataSortElementsClass*& obj)
     {
     obj = new DataSortElementsClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataSortElements
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataSortElements*& obj)
     {
     obj = new BaseDataSortElements;
     return obj->DecodeThis(buffer);
     }
/*S Utilities
 */
/*F CobwebClusterEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void ConsecutiveEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataClusterInstanceSetsClass,BaseDataClusterInstanceSets,CONSECUTIVE_INSTSET_NAME);
  EncodeDecodeRegisterClass(DataConsecutiveClass,BaseDataConsecutive,CONSECUTIVE_ALGORITHM_NAME);
  EncodeDecodeRegisterClass(DataConsecutiveSeriesSetClass,BaseDataConsecutiveSeriesSet,CONSECUTIVE_SERIESSET_NAME);
  EncodeDecodeRegisterClass(DataConsecutiveSeriesClass,BaseDataConsecutiveSeries,CONSECUTIVE_SERIES_NAME);
  EncodeDecodeRegisterClass(DataSortElementsClass,BaseDataSortElements,CONSECUTIVE_SORT_NAME);
}
/*F AddClusterTreeClasses(set) . . . . . . . .  basic algorithm data types
**
**  DESCRIPTION
**    set: The set of data types
**
**  REMARKS
**
*/
void AddConsecutiveClasses(DataSetOfObjectsClass& set)
{
  String condescr("The Create Instance Sets Class");
  DataClusterInstanceSetsClass conclass(CONSECUTIVE_INSTSET_ID,CONSECUTIVE_INSTSET_NAME,condescr);
  set.AddObjectClass(conclass);

  String algdescr("The Find Consecutive Series Class");
  DataConsecutiveClass algclass(CONSECUTIVE_ALGORITHM_ID,CONSECUTIVE_ALGORITHM_NAME,algdescr);
  set.AddObjectClass(algclass);

  String setdescr("The Sets of Consecutive SeriesClass");
  DataConsecutiveSeriesSetClass setclass(CONSECUTIVE_SERIESSET_ID,CONSECUTIVE_SERIESSET_NAME,setdescr);
  set.AddObjectClass(setclass);
  
  String seriesdescr("The Consecutive Series Class");
  DataConsecutiveSeriesClass seriesclass(CONSECUTIVE_SERIES_ID,CONSECUTIVE_SERIES_NAME,seriesdescr);
  set.AddObjectClass(seriesclass);

  String sortdescr("The Sort Instance Class");
  DataSortElementsClass sortclass(CONSECUTIVE_SORT_ID,CONSECUTIVE_SORT_NAME,sortdescr);
  set.AddObjectClass(sortclass);
}

