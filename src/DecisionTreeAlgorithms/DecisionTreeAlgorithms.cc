/*  FILE     DecisionTreeAlgorithms.cc
**  PACKAGE  DecisionTreeAlgorithms
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "DecisionTreeAlgorithms" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
**  Version 1.0
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#define TEMPLATE_INSTANTIATION
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
#include "EntropyObjects.hh"
#include "EvaluationTree.hh"
#include "DecisionTreeAlgorithms.hh"

//template class PairList<Identify,Identify>;
//template class GraphNode<Identify,Identify>;
//template class SearchableObjectListSimple<Identify, GraphNode<Identify,Identify> >;
//template class Graph<Identify,Identify>;

/*S BaseDataDecisionTree
 */ 
/*F BaseDataDecisionTree()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDecisionTree::BaseDataDecisionTree()
  : instanceNamesS("TrainInstanceNameList"),
    decisionTreeS("DecisionTree")
{
  Identification = TREE_DECISION_ID;
  NameTag = TREE_DECISION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataDecisionTree(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDecisionTree::BaseDataDecisionTree(const BaseDataDecisionTree& data)
  : BaseDataEvaluationTree(data),
    instanceNamesS(data.instanceNamesS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataDecisionTree
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataDecisionTree::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataDecisionTree
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataDecisionTree::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result= true;
  //bool result = BaseDataEvaluationTree::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataDecisionTree
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataDecisionTree::print(ostream& out) const
{
  BaseDataEvaluationTree::print(out);
  // The rest

       return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataDecisionTree
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataDecisionTree::Clone()
{
  BaseDataDecisionTree *obj = new BaseDataDecisionTree;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataDecisionTree
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataDecisionTree::CopyClone(Identify * obj)
{
  BaseDataDecisionTree *objfull = (BaseDataDecisionTree *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDecisionTree
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDecisionTree::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataEvaluationTree::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDecisionTree
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDecisionTree::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataEvaluationTree::DecodeThis(buffer);
  // The rest

       return result;
}
 
 
/*F out = PrintDecisionASCIITree(out)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
ostream& BaseDataDecisionTree::PrintASCIIDecisionTree(ostream& out)
{
  out << "------------- Decision Tree ---------------------------\n";
  BaseDataDecisionTreeNodeStats* node = (BaseDataDecisionTreeNodeStats*)
    Tree.GetNode("Root");

  PrintDecisionSubTree(out,node,0);
  return out;
}
 
/*F PrintDecisionASCIISubTree(out,node,level)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/                            
ostream& BaseDataDecisionTree::PrintDecisionSubTree(ostream& out,
                                                    BaseDataDecisionTreeNodeStats* node,
                                                    unsigned int level)
{  
  PrintLevelPrefix(out,level);
  PrintLevelNodeInfo(out,node);
  ObjectList<String> *names = Tree.GetSons(node->NameTag);
  ObjectList<String>::iterator name;
  unsigned int newlevel = level + 1;
  
  for(name = names->begin();
      name != names->end();
      name++)
    {
      BaseDataDecisionTreeNodeStats* son = (BaseDataDecisionTreeNodeStats*)
        Tree.GetNode(*name);
      PrintDecisionSubTree(out,son,newlevel);
    }
  delete names;
  return out;
  
}
 
/*F out = PrintLevelNodeInfo(out,node)  . . . . . . . tree print help routine
**
**  DESCRIPTION
**    out: 
**    node:
**
**  REMARKS
**
*/
ostream& BaseDataDecisionTree::PrintLevelNodeInfo(ostream& out,
                                                  BaseDataDecisionTreeNodeStats* node)
{
  ObjectList<double> goalstats = node->GoalStatistics();
  out << setw(6) << node->GetNumberOfObjects() << " ";
  out << " [";
  for(ObjectList<double>::iterator g=goalstats.begin();
      g != goalstats.end();
      g++)
    {
      if(g != goalstats.begin())
        {
          out << ", ";
        }
      double nelements = node->GetNumberOfObjects() * (*g) * 100;
      unsigned int n = (unsigned int) nelements;
      double nele = (double) n/100;
      
      out << setw(10) << nele;
    }
  out << " ] ";
  out << node->NameTag;
  out << endl;

  return out;
}
/*F out = PrintLevelPrefix(out,level) . . . . . . . . tree print help routine
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
ostream& BaseDataDecisionTree::PrintLevelPrefix(ostream& out, unsigned int level)
{
  for(unsigned int i=0;
      i < level;
      i++)
    {
      out << "     ";
    }
  out << ": ";
  out << setw(5) << level << " ";
  return out;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . .  BaseDataDecisionTree
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
bool BaseDataDecisionTree::WriteAsLine(ostream& out, DataObjectClass *objc)
{
    bool result = BaseDataEvaluationTree::WriteAsLine(out,objc);
    return result;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . .  BaseDataDecisionTree
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
bool BaseDataDecisionTree::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
    bool result = BaseDataEvaluationTree::WriteAsASCII(out,objc);
    return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . .  BaseDataDecisionTree
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
bool BaseDataDecisionTree::WriteAsLatex(ostream& out, DataObjectClass*objc)
{
    bool result = BaseDataEvaluationTree::WriteAsLatex(out,objc);
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
bool BaseDataDecisionTree::SetUpAlgorithms(BaseDataSetOfInstances *instances,
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
bool BaseDataDecisionTree::CheckInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;
  result = result && CheckInputVariable(instanceNamesS,"The set of test instances",run);
  result = result && CheckInputVariable(decisionTreeS,"The Decision Tree",run);
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
bool BaseDataDecisionTree::SetUpInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;

  instanceNames = (BaseDataKeyWords *) run->ParameterValue(instanceNamesS);
  decisionTree = (BaseDataDecisionTree *) run->ParameterValue(decisionTreeS);
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
bool BaseDataDecisionTree::Calculate(BaseDataSetOfInstances *instances,
				 DataSetOfInstancesClass *instancesclass,
				 BaseDataAlgorithmRun *run,
				 DataAlgorithmRunClass *runclass)
{
  bool result = decisionTree->EvaluateDecisionTree(instances,instancesclass,instanceNames);
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
bool BaseDataDecisionTree::WriteOutputValues(BaseDataSetOfInstances *instances,
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
bool BaseDataDecisionTree::ConcludeRun(BaseDataSetOfInstances *instances,
				   DataSetOfInstancesClass *instancesclass,
				   BaseDataAlgorithmRun *run,
				   DataAlgorithmRunClass *runclass)
{
  bool result = true;
//  delete something
  return result;
}
/*F ans = EvaluateTree(instances,instancesclass,run,runclass)  . . . . algorithm
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
bool BaseDataDecisionTree::EvaluateDecisionTree(BaseDataSetOfInstances *instances,
						DataSetOfInstancesClass *instancesclass,
						BaseDataKeyWords *instancenames)
{
  bool result = true;

  ObjectList<String> *set = Tree.FindLeafNodes();
  ObjectList<String>::iterator nodename;


  for(nodename = (*set).begin(); !(nodename == (*set).end()); nodename++) {
    cout << "Decision Tree (Node): " << *nodename << endl;
    BaseDataDecisionTreeNodeStats *node = (BaseDataDecisionTreeNodeStats *) Tree.GetNode(*nodename);
    BaseDataConjunction *conj = node->PointerToConjunction();
    String contclassS("Continuous");
    DataContinuousClass *contclass = (DataContinuousClass *) instancesclass->PointerToAllowedClasses()->GetObjectClass(contclassS);
    BaseDataContinuous *cont = (BaseDataContinuous *) contclass->BaseDataObjectExample();
    ObjectList<String> instnames = instancenames->GetKeyWords();
    ObjectList<String>::iterator name;
    for(name = instnames.begin(); name != instnames.end(); name++) {
      BaseDataInstance *instance = (BaseDataInstance *) instances->GetInstance(*name);
      DataInstanceClass *instanceclass = (DataInstanceClass *) 
	instancesclass->PointerToAllowedClasses()->GetObjectClass(instance->GetType());
      cont->SetValue(1.0);
      BaseDataContinuous *log = (BaseDataContinuous *) conj->operator()(cont,instance, contclass,instanceclass);
      if(log->GetValue() > 0.0001) 
	cout << *name << ":    " << log->GetValue() << endl;
    }
  }
  return result;
}



/*S DataDecisionTreeClass
 */
/*F DataDecisionTreeClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDecisionTreeClass::DataDecisionTreeClass()
{
  Identification = TREE_DECISION_ID;
  NameTag = TREE_DECISION_NAME;
  SubClass = "EvaluationTree";
  EncodeDecodeClass = NameTag;
} 
/*F DataDecisionTreeClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataDecisionTreeClass::DataDecisionTreeClass(const DataDecisionTreeClass& data)
  : DataEvaluationTreeClass(data)
{
} 
 
/*F DataDecisionTreeClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataDecisionTreeClass::DataDecisionTreeClass(const int id, 
                                             const String& name,
                                             const String& descr)
  : DataEvaluationTreeClass(id,name,descr)
{
  SubClass = "EvaluationTree";
  EncodeDecodeClass = TREE_DECISION_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataDecisionTreeClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataDecisionTreeClass::print(ostream& out) const
{
  DataEvaluationTreeClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataDecisionTreeClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataDecisionTreeClass, there is no further information.
**
**  REMARKS
**
*/
bool DataDecisionTreeClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataEvaluationTreeClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataDecisionTreeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataDecisionTreeClass::CopyClone(Identify *  objc)
{
  DataDecisionTreeClass *objcfull = (DataDecisionTreeClass *) objc;
  *this = *objcfull;
}

/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataDecisionTreeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataDecisionTreeClass::Clone()
{
  DataDecisionTreeClass* id = new DataDecisionTreeClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataDecisionTreeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDecisionTreeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataEvaluationTreeClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataDecisionTreeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDecisionTreeClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataEvaluationTreeClass::DecodeThis(buffer);
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
BaseDataObject * DataDecisionTreeClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataDecisionTree();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataDecisionTreeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataDecisionTreeClass*& obj)
{
  obj = new DataDecisionTreeClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataDecisionTree
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataDecisionTree*& obj)
{
  obj = new BaseDataDecisionTree;
  return obj->DecodeThis(buffer);
}

/*S BaseDataDecisionTreeCreate
 */ 
/*F BaseDataDecisionTreeCreate()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDecisionTreeCreate::BaseDataDecisionTreeCreate()
  : selectionDescriptorsS(SELECTION_DESCRIPTORS),
    selectionGoalsS(SELECTION_GOAL)
{
  Identification = TREE_CREATE_ID;
  NameTag = TREE_CREATE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataDecisionTreeCreate(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDecisionTreeCreate::BaseDataDecisionTreeCreate(const BaseDataDecisionTreeCreate& data)
  : BaseDataDecisionTree(data),
    selectionDescriptorsS(data.selectionDescriptorsS),
    selectionGoalsS(data.selectionGoalsS),
    EntropyCalculationName(data.EntropyCalculationName),
    EntropyCalc(data.EntropyCalc),
    ChooseEntropyName(data.ChooseEntropyName),
    ChooseEntropy(data.ChooseEntropy),
    FilterName(data.FilterName),
    Filter(data.Filter),
    OpenNodes(data.OpenNodes)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataDecisionTreeCreate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataDecisionTreeCreate::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataDecisionTreeCreate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataDecisionTreeCreate::Read(istream& , DataObjectClass* , const String& )
{
  return true;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataDecisionTreeCreate
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataDecisionTreeCreate::print(ostream& out) const
{
  BaseDataDecisionTree::print(out);
  out << "\nBegin:-----------------------";
  out << " BaseDataDecisionTreeCreate: " << NameTag;
  out << "-----------------------" << endl;
  
  out << "DecisionTree Create:\n";
  out << "Entropy Calculation Routine: " << EntropyCalculationName << endl;
  out << "Choose Predicate from Entropy Routine: " << ChooseEntropyName << endl;
  out << "Filter Nodes Routine: " << FilterName << endl;

  out << "Input Parameters: [ ";

  out << instanceNamesS << "','";
  out << selectionDescriptorsS << "','";
  out << selectionGoalsS << "]" << endl;
  
  out << "List of Open Nodes:\n";
  OpenNodesNames.print(out);
  out << endl;
  
  out << "\nEnd:  -----------------------";
  out << " BaseDataDecisionTreeCreate: " << NameTag;
  out << "-----------------------" << endl;
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataDecisionTreeCreate
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataDecisionTreeCreate::Clone()
{
  BaseDataDecisionTreeCreate *obj = new BaseDataDecisionTreeCreate;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataDecisionTreeCreate
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataDecisionTreeCreate::CopyClone(Identify * obj)
{
  BaseDataDecisionTreeCreate *objfull = (BaseDataDecisionTreeCreate *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDecisionTreeCreate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDecisionTreeCreate::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataDecisionTree::EncodeThis(buffer);
  result = result && Encode(buffer,selectionDescriptorsS);
  result = result && Encode(buffer,EntropyCalculationName);
  result = result && Encode(buffer,ChooseEntropyName);
  result = result && Encode(buffer,FilterName);
  result = result && OpenNodes.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDecisionTreeCreate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDecisionTreeCreate::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataDecisionTree::DecodeThis(buffer);
  result = result && Decode(buffer,selectionDescriptorsS);
  result = result && Decode(buffer,EntropyCalculationName);
  result = result && Decode(buffer,ChooseEntropyName);
  result = result && Decode(buffer,FilterName);
  result = result && OpenNodes.DecodeThis(buffer);

  return result;
}
 
 
/*F ans = SetUpAlgorihtms(run)  . . . . . . . . . . . . check parameter input
**
**  DESCRIPTION
**    run: Algorithm information
**
**  REMARKS
**
*/
bool BaseDataDecisionTreeCreate::SetUpAlgorithms(BaseDataSetOfInstances*,
                                                 DataSetOfInstancesClass*,
                                                 BaseDataAlgorithmRun* run,
                                                 DataAlgorithmRunClass* rclass)
{
  bool result = true;
  if(rclass->getDebugLevel() > 2)
    {
      cout << "List of Algorithms" << endl;
      run->GetListOfSubAlgorithms().print(cout);
      cout << endl;
    }
  ObjectList<String> algnames = run->GetListOfSubAlgorithms();
  algnames.pop_front();

  ChooseEntropyName  = algnames.front();
  algnames.pop_front();
  String EntropyCalculationName  = algnames.front();
  algnames.pop_front();
  FilterName  = algnames.front();
  algnames.pop_front();

  EntropyCalc = run->GetSubAlgorithm(EntropyCalculationName);
  ChooseEntropy = (BaseDataEntropySelectPredicate *) run->GetSubAlgorithm(ChooseEntropyName);
  Filter = run->GetSubAlgorithm(FilterName);

  ChooseEntropy->SetEntropyAlgorithm(EntropyCalc);

  if(rclass->getDebugLevel() > 2)
    {
      run->GetListOfSubAlgorithms().print(cout);
      cout << "\nEntropy Calculate: " << EntropyCalculationName << endl;
      EntropyCalc->print(cout);
      cout << "\nChoose by Entropy: " << ChooseEntropyName << endl;
      ChooseEntropy->print(cout);
      cout << "\nFilter: " << FilterName << endl;
      Filter->print(cout);
      cout << endl;
    }

  return result;
}
/*F ans = InitialiseCreate()  . . . . . . . . . . . . .  initialise open list
**
**  DESCRIPTION
**    ans: true if successful
**  
**  REMARKS
**
*/
bool BaseDataDecisionTreeCreate::InitialiseCreate(ObjectList<String>& names,
                                                  BaseDataSetOfLogicDescriptions& ldescrs,
                                                  DataSetOfLogicDescriptionsClass& ldescrsclass,
						  DataSetOfInstancesClass* instclasses)
{
  BaseDataConjunction conj;

  BaseDataDecisionTreeNodeStats node(conj);
  
  node.NameTag = "Root";
  Tree.SetRootNode(node.NameTag);
  node.Parent = node.NameTag;
  node.SetNumberOfObjects(names,ldescrs,ldescrsclass,instclasses);
  
  bool result = AddNodeToOpenList(node);
  
  return result;
}
/*F ans = AddNodeToOpenList(node) . . . . . . . . . . . . .  add to open list
**
**  DESCRIPTION
**    ans: true if successful
**  
**  REMARKS
**
*/
bool BaseDataDecisionTreeCreate::AddNodeToOpenList(BaseDataDecisionTreeNodeStats& node)
{
  node.Identification = OpenNodes.NextIdentification();
  OpenNodes.AddObject(&node);
  OpenNodesNames.AddObject(node.NameTag);

  return true;
}
/*F ans = OpenNotEmpty()  . . . . . . . . . . . . . . . . . . .  not done yet
**
**  DESCRIPTION
**    ans: true if not empty
**
**  REMARKS
**
*/
bool BaseDataDecisionTreeCreate::OpenNotEmpty()
{
  return OpenNodesNames.size() != 0;
}
 
/*F ans = NextNode()  . . . . . . . . . . . . . . . . . . . .  next open node
**
**  DESCRIPTION
**    ans: true if successful
**
**  REMARKS
**
*/
BaseDataDecisionTreeNodeStats *BaseDataDecisionTreeCreate::NextNode()
{
  BaseDataDecisionTreeNodeStats *stcopy;

  BaseDataDecisionTreeNodeStats *stats;
  cout << "Begin: ------- Open Nodes ---------" << endl;
  OpenNodesNames.print(cout);
  cout << endl << "End:  ------- Open Nodes ---------" << endl;
  String name = OpenNodesNames.front();

  OpenNodesNames.pop_front();
  if(OpenNodes.IsInList(name))
    {
      stats = (BaseDataDecisionTreeNodeStats *)
	OpenNodes.GetObject(name);
      stcopy = (BaseDataDecisionTreeNodeStats *) stats->Clone();
      OpenNodes.RemoveObject(name);
    }
  else
    {
      cerr << "Predicate Repeated for Node: '" << name << "' not used" << endl;
      stcopy = NULL;
    }

  return stcopy;
}
 
/*F NodeEntropyCalculate(node,instances,instancesclass,run,runclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataDecisionTreeCreate::NodeEntropyCalculate(BaseDataDecisionTreeNodeStats *node,
                                                      BaseDataSetOfInstances* instances,
                                                      DataSetOfInstancesClass* instancesclass,
                                                      BaseDataAlgorithmRun* run,
                                                      DataAlgorithmRunClass *runclass)
{
  bool result = true;
  
  BaseDataConjunction *conj = node->PointerToConjunction();
  String conjS(ENTROPY_CONJUNCTION);
  BaseDataKeyWords conjkeys = conj->KeyWordsFromConjunction();
  conjkeys.NameTag = conjS;

  if(runclass->getDebugLevel() > 2)
    {
      cout << "The Conjunction in 'NodeEntropyCalculate':" << "'" << conj << "'" << endl;
      conj->print(cout);
      cout << endl;
      cout << "The parameter:\n";
      conjkeys.print(cout);
      cout << endl;
    }
  
  result = result && run->AddParameter(&conjkeys);
  if(ChooseEntropy != NULL)
    {
      if(runclass->getDebugLevel() > 3)
	{
	  cout << "Call Choose Entropy" << endl;
	}
      result = result && ChooseEntropy->operator()(instances,instancesclass,run,runclass);
      if(runclass->getDebugLevel() > 3)
	{
	  cout << "Back From Choose Entropy" << endl;
	}
      
      String gainname(ENTROPY_GAIN);
      BaseDataReal *gainobject = (BaseDataReal *) run->ParameterValue(gainname);
      if(runclass->getDebugLevel() > 3)
	cout << "Node Gain: " << gainobject->GetValue() << endl;
      String matname(ENTROPY_MATRIX);
      BaseDataDoubleMatrix *matobject = (BaseDataDoubleMatrix *) run->ParameterValue(matname);
      
      String topname(ENTROPY_TOP_PREDICATE);
      BaseDataKeyWords *top = (BaseDataKeyWords *) run->ParameterValue(topname);
      ObjectList<String> chosen = top->GetKeyWords();
      String selected = chosen.front();
      BaseDataKeyWords *partition = (BaseDataKeyWords *) instances->GetObject(selected);
      node->InsertElements(gainobject,matobject,partition);
    }
  else
    {
      cerr << "Choose by Entropy Routine not found\n";
      result = false;
    }
  
  return result;
}
 
 
/*F ans = DecideToExpandNode()  . . . . . . . . . . . . . call filter routine
**
**  DESCRIPTION
**    ans: 
**
**  REMARKS
**
*/
bool BaseDataDecisionTreeCreate::DecideToExpandNode(BaseDataSetOfInstances *instances,
						    DataSetOfInstancesClass *instancesclass,
						    BaseDataAlgorithmRun *run,
						    DataAlgorithmRunClass *runclass)
{
  bool result = true;
  cout << "Call Filter Routine to decide if to expand node" << endl;
  cout << "\nFilter: " << FilterName << endl;
  Filter->print(cout);
  cout << endl;
  result = result && Filter->operator()(instances,instancesclass,run,runclass);
  if(run->ParameterInList(DECISION_TREE_FILTER_ANSWER)) {
    BaseDataContinuous *logical = (BaseDataContinuous *) run->ParameterValue(DECISION_TREE_FILTER_ANSWER);
    if(runclass->getDebugLevel() > 3)
      cout << "BaseDataDecisionTreeCreate::DecideToExpandNode  Answer from Filter: " << logical->GetValue() << endl;
    if(logical->GetValue() > 0.5)
      result = true;
    else
      result = false;
  } else {
    cout << "No filter answer, do not filter" << endl;
    result = true;
  } 
  /*
    double num = node->GetNumberOfObjects();
  if(node->NameTag == "Root")
    result = true;
  else if(num <= 2.0)
    result = false;
  else
    {
      result = true;
      ObjectList<double> *goalstats = node->PointerToGoalStats();
      for(ObjectList<double>::iterator p=goalstats->begin();
          p != goalstats->end();
          p++)
        {
          if((*p) > .90)
            result = false;
        }
    }
  */
  return result;
}
/*F ans = ExpandNextNode(nodeobj,instances,..)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataDecisionTreeCreate::ExpandNextNode(BaseDataTreeNode *nodeobj,
                                                DataTreeNodeClass *,
                                                BaseDataSetOfInstances* instances,
                                                DataSetOfInstancesClass* instclasses,
                                                BaseDataSetOfLogicDescriptions& ldescrs,
                                                DataSetOfLogicDescriptionsClass& ldescrsclass,
                                                BaseDataAlgorithmRun*,
                                                DataAlgorithmRunClass *rclass)
{
  if(rclass->getDebugLevel() > 1)
    cout << "ExpandNextNode: Start" << endl;
  
  BaseDataDecisionTreeNodeStats *node = (BaseDataDecisionTreeNodeStats *) nodeobj;
  if(rclass->getDebugLevel() > 3)
      node->print(cout);
  
  String par = "#";
  unsigned int count = 0;
  BaseDataConjunction *conjbase = node->PointerToConjunction();
  

  ObjectList<String> instnames = instanceNames->GetKeyWords();
  BaseDataKeyWords *partition = node->PointerToPartition();
  ObjectList<String> names = partition->GetKeyWords();

  ObjectList<String>::iterator name;
  
  cout << "Adding Nodes to Open List" << endl;
  names.print(cout);
  cout << endl;
  for(name = names.begin();
      name != names.end();
      name++)
    {
      unsigned int nodecount = Tree.getNodeCount() + 1;
      cout << "Node: " << nodecount;
      String nodecountS = Int2String(nodecount);
      String nodename("Node");
      nodename.AppendToEnd(nodecountS);
      nodename.AppendToEnd(par);
      nodename.AppendToEnd(*name);

      if(rclass->getDebugLevel() > 2)
	cout << "ExpandNextNode: Loop: " << *name << endl;

      BaseDataPredicate *pred = (BaseDataPredicate *) instances->GetObject(*name);
      if(rclass->getDebugLevel() > 3)
	{
	  cout << "The Predicate:\n";
	  pred->print(cout);
	  cout << endl;
	}
      BaseDataConjunction conj;
      conj.CopyClone(conjbase);
      conj.AddPredicate(pred);
      
      BaseDataDecisionTreeNodeStats newnode(conj);
      //newnode.NameTag = *name;
      newnode.NameTag = nodename;
      newnode.Parent = node->NameTag;
      newnode.SetNumberOfObjects(instnames,ldescrs,ldescrsclass,instclasses);
      count++;
      cout << "Add Node to Open List: " << *name << endl;
      AddNodeToOpenList(newnode);
    }
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
bool BaseDataDecisionTreeCreate::CheckInput(BaseDataSetOfInstances*,
                                            DataSetOfInstancesClass*,
                                            BaseDataAlgorithmRun* run,
                                            DataAlgorithmRunClass*)
{
  bool result = true;
  
  if(run->ParameterInList(instanceNamesS))
    {
      if(run->ParameterInList(selectionDescriptorsS))
        {
          if(!(run->ParameterInList(selectionGoalsS)))
            {
              cerr << "Selection Goals parameter: " << selectionGoalsS << " not found" << endl;
              result = false;
            }
        }
      else
        {
          cerr << "Selection Descriptor parameter: " << selectionDescriptorsS << " not found" << endl;
          result = false;
        }
      
    }
  else
    {
      cerr << "Train Instances List: " << instanceNamesS << " not found" << endl;
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
bool BaseDataDecisionTreeCreate::SetUpInput(BaseDataSetOfInstances* instances,
                                            DataSetOfInstancesClass* instclass,
                                            BaseDataAlgorithmRun* run,
                                            DataAlgorithmRunClass* rclass)
{
  bool result = true;
  
  instanceNames = (BaseDataKeyWords *) run->ParameterValue(instanceNamesS);
  selectionDescriptors = (BaseDataKeyWords *) run->ParameterValue(selectionDescriptorsS);
  selectionGoals = (BaseDataKeyWords *) run->ParameterValue(selectionGoalsS);
  ObjectList<String> logicDescriptorsNames;
  
  ObjectList<String> partnames = selectionDescriptors->GetKeyWords();
  ObjectList<String> goalpnames = selectionGoals->GetKeyWords();
  partnames.AddOnlyUniqueObjects(goalpnames);
  
  if(rclass->getDebugLevel() > 1)
    {
      cout << "List of Partitions Variable: " << selectionDescriptorsS << endl;
      selectionDescriptors->print(cout);
    }
  ObjectList<String>::iterator partname,descrname;
  for(partname = partnames.begin(); 
      partname != partnames.end() && result;
      partname++)
    {
      if(rclass->getDebugLevel() > 3)
	  cout << "Partition Variable: " << *partname << endl;
      if(instances->IsInList(*partname))
        {
          BaseDataKeyWords *descr = (BaseDataKeyWords *) instances->GetObject(*partname);
	  if(rclass->getDebugLevel() > 3)
	    {
	      cout << "Partition Set of Predicates: " << endl;
	      descr->print(cout);
	      cout << endl;
	    }
          
          ObjectList<String> descrnames = descr->GetKeyWords();
          for(descrname = descrnames.begin(); 
              descrname != descrnames.end() && result;
              descrname++)
            {
	      if(rclass->getDebugLevel() > 3)
		cout << "Predicate Variable: " << *descrname << endl;
              if(instances->IsInList(*descrname))
                {
                  logicDescriptorsNames.AddObject(*descrname);
                }
              else
                {
                  cerr << "Predicate Description: '" << *descrname << "' not found" << endl;
                  result = false;
                }
            }
        }
      else
        {
          cerr << "Partition: '" << *partname << "' not found" << endl;
          result = false;
        }
    }
  if(rclass->getDebugLevel() > 1)
    {
      cout << "List of Predicates: " << endl;
      logicDescriptorsNames.print(cout);
      cout << endl;
    }
  if(rclass->getDebugLevel() > 2)
    {
      cout << "List of Instances: " << endl;
      instanceNames->print(cout);
      cout << endl;
    }
  BaseDataLogical logic;
  DataLogicalClass logclass;
  DataDescriptionClass descrclass;
  if(rclass->getDebugLevel() > 2)
    {
      cout << "AddLogicalObjects\n";
    }
  logicDescriptions = new BaseDataSetOfLogicDescriptions;
  logicDescriptions->NameTag = LOGIC_DESCRIPTIONS;
  result = result && run->AddParameter(logicDescriptions);
  delete logicDescriptions;
  logicDescriptions = (BaseDataSetOfLogicDescriptions *) run->ParameterValue(LOGIC_DESCRIPTIONS);

  result = result && logicDescriptions->AddLogicalObjects(&logic,&logclass,
                                                          &descrclass,
                                                          instances,instclass,
                                                          instanceNames->GetKeyWords(),logicDescriptorsNames);
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
bool BaseDataDecisionTreeCreate::Calculate(BaseDataSetOfInstances* instances,
                                           DataSetOfInstancesClass* instancesclass,
                                           BaseDataAlgorithmRun *run,
                                           DataAlgorithmRunClass* runclass)
{
  bool result = true;
  NameTag = "DecisionTree";

  DataSetOfLogicDescriptionsClass ldescrsclass;
  
  result = result && InitialiseCreate(instanceNames->GetKeyWords(),
                                      *logicDescriptions,ldescrsclass,
				      instancesclass);
  
  BaseDataKeyWords *current = new BaseDataKeyWords(*instanceNames);
  current->NameTag = CURRENT_INSTANCELIST;
  result = result && run->AddParameter(current);
  
  if(runclass->getDebugLevel() > 2)
    {
      cout << "Instances used for Generation:" << endl;
      current->print(cout);
    }
  DataDecisionTreeNodeStatsClass *nodeclass;
  
  while(result && OpenNotEmpty())
    {
      if(runclass->getDebugLevel() > 0)
	  cout << "Find Next Node" << endl;
      node = NextNode();
      if(node != NULL)
        {
	  nodeclass = (DataDecisionTreeNodeStatsClass *)
	    instancesclass->PointerToAllowedClasses()->GetObjectClass(node->GetType());
	  if(runclass->getDebugLevel() > 0)
	    cout << "==================== Work on node: '" << node->NameTag << "'" << endl;
	  
          Tree.AddNode(node);
	  String name(node->NameTag);
	  delete node;
	  node = (BaseDataDecisionTreeNodeStats *) Tree.GetNode(name);
          result = result && NodeEntropyCalculate(node,instances,instancesclass,run,runclass);
          if(node->Parent != node->NameTag)
            Tree.AddConnection(node->Parent,node->NameTag);
          
	  result = result && run->AddParameter(this);
	  if(runclass->getDebugLevel() > 4)
	    cout << "DecideToExpandNode" << endl;
          if(DecideToExpandNode(instances,instancesclass,run,runclass))
            result = result && ExpandNextNode(node,nodeclass,instances,instancesclass,
                                              *logicDescriptions,ldescrsclass,
                                              run,runclass);
	  else if(runclass->getDebugLevel() > 0)
	    cout << "Don't Expand Node" << endl;

	  if(runclass->getDebugLevel() > 0)
	    {
	      cout << "==================== The Decision Tree:" << endl;
	      PrintASCIIDecisionTree(cout);
	      cout << endl;
	    }
        }
    }
  if(runclass->getDebugLevel() > 0)
    {
      cout << "==================== The Final Decision Tree:" << endl;
      PrintASCIIDecisionTree(cout);
      cout << endl;
    }
  
  return true;
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
bool BaseDataDecisionTreeCreate::WriteOutputValues(BaseDataSetOfInstances*,
                                                   DataSetOfInstancesClass*,
                                                   BaseDataAlgorithmRun* run,
                                                   DataAlgorithmRunClass*) 
{
  bool result = true;

  BaseDataDecisionTree *dtree = new BaseDataDecisionTree(*this);
  dtree->NameTag = "DecisionTree";
  dtree->EncodeDecodeClass = "Object.DecisionTree";
  dtree->SetType(TREE_DECISION_ID);
  result = result && run->AddParameter(dtree);
  
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
bool BaseDataDecisionTreeCreate::ConcludeRun(BaseDataSetOfInstances*,
                                             DataSetOfInstancesClass*,
                                             BaseDataAlgorithmRun*,
                                             DataAlgorithmRunClass* ) 
{
  return true;
}

 
/*F node = getCurrentNode()
**
**  DESCRIPTION
**    node: The current node being expanded
**
**  REMARKS
**
*/
BaseDataDecisionTreeNodeStats *BaseDataDecisionTreeCreate::getCurrentNode()
{
  return node;
}
 
/*S DataDecisionTreeCreateClass
 */
/*F DataDecisionTreeCreateClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDecisionTreeCreateClass::DataDecisionTreeCreateClass()
{
  Identification = TREE_CREATE_ID;
  NameTag = TREE_CREATE_NAME;
  SubClass = "DecisionTree";
  EncodeDecodeClass = NameTag;
} 
/*F DataDecisionTreeCreateClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataDecisionTreeCreateClass::DataDecisionTreeCreateClass(const DataDecisionTreeCreateClass& data)
  : DataDecisionTreeClass(data),
    AlgorithmOperationClass(data.AlgorithmOperationClass)
{
} 
 
/*F DataDecisionTreeCreateClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataDecisionTreeCreateClass::DataDecisionTreeCreateClass(const int id, 
                                                         const String& name,
                                                         const String& descr)
  : DataDecisionTreeClass(id,name,descr)
{
  SubClass = "DecisionTree";
  EncodeDecodeClass = TREE_CREATE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataDecisionTreeCreateClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataDecisionTreeCreateClass::print(ostream& out) const
{
  out << "\nBegin:-----------------------";
  out << " DataDecisionTreeCreateClass: " << NameTag;
  out << "-----------------------" << endl;
  
  DataDecisionTreeClass::print(out);
       
  out << "\nEnd  :-----------------------";
  out << " DataDecisionTreeCreateClass: " << NameTag;
  out << "-----------------------" << endl;
  
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataDecisionTreeCreateClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataDecisionTreeCreateClass, there is no further information.
**
**  REMARKS
**
*/
bool DataDecisionTreeCreateClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataDecisionTreeClass::Read(in,set);
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataDecisionTreeCreateClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataDecisionTreeCreateClass::CopyClone(Identify *  objc)
{
  DataDecisionTreeCreateClass *objcfull = (DataDecisionTreeCreateClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataDecisionTreeCreateClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataDecisionTreeCreateClass::Clone()
{
  DataDecisionTreeCreateClass* id = new DataDecisionTreeCreateClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataDecisionTreeCreateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDecisionTreeCreateClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataDecisionTreeClass::EncodeThis(buffer);
  result = result && AlgorithmOperationClass.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataDecisionTreeCreateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDecisionTreeCreateClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataDecisionTreeClass::DecodeThis(buffer);
  result = result && AlgorithmOperationClass.DecodeThis(buffer);

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
BaseDataObject * DataDecisionTreeCreateClass::BaseDataObjectExample()
{ 
  //cout << "Make DecisionTreeCreate Example\n";
  return (BaseDataObject *) new BaseDataDecisionTreeCreate();
}
 
/*F pntr = PointerToAlgorithmOperationClass() . . . . . . . . pointer to info
**
**  DESCRIPTION
**    pntr: pointer
**
**  REMARKS
**
*/
DataAlgorithmOperationClass *DataDecisionTreeCreateClass::PointerToAlgorithmOperationClass()
{
  return &AlgorithmOperationClass;
}
/*F pntr = PointerToOpenNodesClass() . . . . . . . . pointer to info
**
**  DESCRIPTION
**    pntr: pointer
**
**  REMARKS
**
*/
DataSetOfObjectsClass *DataDecisionTreeCreateClass::PointerToOpenNodesClass()
{
  return StandardAllowedClasses;
}

/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataDecisionTreeCreateClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataDecisionTreeCreateClass*& obj)
{
  obj = new DataDecisionTreeCreateClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataDecisionTreeCreate
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataDecisionTreeCreate*& obj)
{
  obj = new BaseDataDecisionTreeCreate;
  bool result = obj->DecodeThis(buffer);
  return result;
}

/*S BaseDataDecisionTreeNodeSpec
 */ 
/*F BaseDataDecisionTreeNodeSpec()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDecisionTreeNodeSpec::BaseDataDecisionTreeNodeSpec()
{
  Identification = TREE_NODESPEC_ID;
  NameTag = TREE_NODESPEC_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataDecisionTreeNodeSpec(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDecisionTreeNodeSpec::BaseDataDecisionTreeNodeSpec(const BaseDataDecisionTreeNodeSpec& data)
  : BaseDataTreeNode(data),
    Conjunction(data.Conjunction),
    Partition(data.Partition)
{
}
/*F BaseDataDecisionTreeNodeStats(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: the conjunction
**
**  REMARKS
**
*/
BaseDataDecisionTreeNodeSpec::BaseDataDecisionTreeNodeSpec(const BaseDataConjunction& data)
  : Conjunction(data)
{
  Identification = TREE_NODESPEC_ID;
  NameTag = TREE_NODESPEC_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataDecisionTreeNodeSpec
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataDecisionTreeNodeSpec::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataDecisionTreeNodeSpec
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataDecisionTreeNodeSpec::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataTreeNode::Read(in,objc,name);
  DataDecisionTreeNodeSpecClass *nodeclass = (DataDecisionTreeNodeSpecClass *) objc;
  
  result = result && Conjunction.Read(in,nodeclass->PointerToConjunctionClass(),name);
  result = result && Partition.Read(in,nodeclass->PointerToPartitionClass(),name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataDecisionTreeNodeSpec
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataDecisionTreeNodeSpec::print(ostream& out) const
{
  BaseDataTreeNode::print(out);
  out << "Decision Tree Node Specification: \n";
  out << "Conjunction: ";
  Conjunction.print(out);
  out << endl << "Partition: ";
  Partition.print(out);
  out << endl;
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataDecisionTreeNodeSpec
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataDecisionTreeNodeSpec::Clone()
{
  BaseDataDecisionTreeNodeSpec *obj = new BaseDataDecisionTreeNodeSpec;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataDecisionTreeNodeSpec
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataDecisionTreeNodeSpec::CopyClone(Identify * obj)
{
  BaseDataDecisionTreeNodeSpec *objfull = (BaseDataDecisionTreeNodeSpec *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDecisionTreeNodeSpec
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDecisionTreeNodeSpec::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataTreeNode::EncodeThis(buffer);
  result = result && Conjunction.EncodeThis(buffer);
  result = result && Partition.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDecisionTreeNodeSpec
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDecisionTreeNodeSpec::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataTreeNode::DecodeThis(buffer);
  result = result && Conjunction.DecodeThis(buffer);
  result = result && Partition.DecodeThis(buffer);

  return result;
}
 
 
/*F conj = PointerToConjunction() . . . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataConjunction *BaseDataDecisionTreeNodeSpec::PointerToConjunction()
{
  return &Conjunction;
}
/*F partition = PointerToPartition()  . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataKeyWords *BaseDataDecisionTreeNodeSpec::PointerToPartition()
{
  return &Partition;
}
/*F InsertPartition(partition)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataDecisionTreeNodeSpec::InsertPartition(BaseDataKeyWords *partition)
{
  BaseDataKeyWords *part = (BaseDataKeyWords *) partition->Clone();
  Partition.CopyClone(part);
}
/*F ans = WriteAsLine(out,objc) . . . . . . . .  BaseDataDecisionTreeNodeSpec
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
bool BaseDataDecisionTreeNodeSpec::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataTreeNode::WriteAsLine(out,objc);
  return result;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . .  BaseDataDecisionTreeNodeSpec
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
bool BaseDataDecisionTreeNodeSpec::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  DataDecisionTreeNodeSpecClass *oclass = (DataDecisionTreeNodeSpecClass *) objc;
  bool result = Conjunction.WriteAsASCII(out,oclass->PointerToConjunctionClass());
  result = result && Partition.WriteAsASCII(out,oclass->PointerToPartitionClass());
  result = result && BaseDataTreeNode::WriteAsASCII(out,objc);
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . .  BaseDataDecisionTreeNodeSpec
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
bool BaseDataDecisionTreeNodeSpec::WriteAsLatex(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataTreeNode::WriteAsLatex(out,objc);
  return result;
}

/*S DataDecisionTreeNodeSpecClass
 */
/*F DataDecisionTreeNodeSpecClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDecisionTreeNodeSpecClass::DataDecisionTreeNodeSpecClass()
{
  Identification = TREE_NODESPEC_ID;
  NameTag = TREE_NODESPEC_NAME;
  SubClass = "TreeNode";
  EncodeDecodeClass = NameTag;
} 
/*F DataDecisionTreeNodeSpecClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataDecisionTreeNodeSpecClass::DataDecisionTreeNodeSpecClass(const DataDecisionTreeNodeSpecClass& data)
  : DataTreeNodeClass(data),
    ConjunctionClass(data.ConjunctionClass),
    PartitionClass(data.PartitionClass)
{
} 
 
/*F DataDecisionTreeNodeSpecClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataDecisionTreeNodeSpecClass::DataDecisionTreeNodeSpecClass(const int id, 
                                                             const String& name,
                                                             const String& descr)
  : DataTreeNodeClass(id,name,descr)
{
  SubClass = "TreeNode";
  EncodeDecodeClass = TREE_NODESPEC_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataDecisionTreeNodeSpecClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataDecisionTreeNodeSpecClass::print(ostream& out) const
{
  DataTreeNodeClass::print(out);
  out << "\n     ";
  ConjunctionClass.print(out);
  out << "\n     ";
  PartitionClass.print(out);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataDecisionTreeNodeSpecClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataDecisionTreeNodeSpecClass, there is no further information.
**
**  REMARKS
**
*/
bool DataDecisionTreeNodeSpecClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataTreeNodeClass::Read(in,set);
  result = result && ConjunctionClass.Read(in,set);
  result = result && PartitionClass.Read(in,set);
  
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataDecisionTreeNodeSpecClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataDecisionTreeNodeSpecClass::CopyClone(Identify *  objc)
{
  DataDecisionTreeNodeSpecClass *objcfull = (DataDecisionTreeNodeSpecClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataDecisionTreeNodeSpecClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataDecisionTreeNodeSpecClass::Clone()
{
  DataDecisionTreeNodeSpecClass* id = new DataDecisionTreeNodeSpecClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataDecisionTreeNodeSpecClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDecisionTreeNodeSpecClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataTreeNodeClass::EncodeThis(buffer);
  result = result && ConjunctionClass.EncodeThis(buffer);
  result = result && PartitionClass.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataDecisionTreeNodeSpecClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDecisionTreeNodeSpecClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataTreeNodeClass::DecodeThis(buffer);
  result = result && ConjunctionClass.DecodeThis(buffer);
  result = result && PartitionClass.DecodeThis(buffer);

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
BaseDataObject * DataDecisionTreeNodeSpecClass::BaseDataObjectExample()
{ 
  //cout << "Make DecisionTreeNodeSpec Example\n";
  return (BaseDataObject *) new BaseDataDecisionTreeNodeSpec();
}
 
/*F pntr = PointerToConjunctionClass()  . . . . . . . . . . .  the class info
**
**  DESCRIPTION
**    pntr: Pointer
**
**  REMARKS
**
*/
DataConjunctionClass *DataDecisionTreeNodeSpecClass::PointerToConjunctionClass()
{
  return &ConjunctionClass;
}
/*F pntr = PointerToPartitionClass()  . . . . . . . . . . .  the class info
**
**  DESCRIPTION
**    pntr: Pointer
**
**  REMARKS
**
*/
DataPartitionClass *DataDecisionTreeNodeSpecClass::PointerToPartitionClass()
{
  return &PartitionClass;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataDecisionTreeNodeSpecClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataDecisionTreeNodeSpecClass*& obj)
{
  obj = new DataDecisionTreeNodeSpecClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataDecisionTreeNodeSpec
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataDecisionTreeNodeSpec*& obj)
{
  obj = new BaseDataDecisionTreeNodeSpec;
  return obj->DecodeThis(buffer);
}

/*S BaseDataDecisionTreeNodeStats
 */ 
/*F BaseDataDecisionTreeNodeStats()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDecisionTreeNodeStats::BaseDataDecisionTreeNodeStats()
{
  Identification = TREE_NODESTATS_ID;
  NameTag = TREE_NODESTATS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataDecisionTreeNodeStats(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDecisionTreeNodeStats::BaseDataDecisionTreeNodeStats(const BaseDataDecisionTreeNodeStats& data)
  : BaseDataDecisionTreeNodeSpec(data),
    PartitionMatrix(data.PartitionMatrix),
    NumberOfObjects(data.NumberOfObjects),
    Gain(data.Gain),
    GoalStats(data.GoalStats)
{
}
/*F BaseDataDecisionTreeNodeStats(conj)  . . . . . . . . . . . . . . . . . from conjunction
**
**  DESCRIPTION
**    conj: The initial Conjunction
**
**  REMARKS
**
*/
BaseDataDecisionTreeNodeStats::BaseDataDecisionTreeNodeStats(const BaseDataConjunction& conj)
  : BaseDataDecisionTreeNodeSpec(conj)
{
  Identification = TREE_NODESTATS_ID;
  NameTag = TREE_NODESTATS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataDecisionTreeNodeStats
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataDecisionTreeNodeStats::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataDecisionTreeNodeStats
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataDecisionTreeNodeStats::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataDecisionTreeNodeSpec::Read(in,objc,name);
  DataDecisionTreeNodeStatsClass *nodeclass = (DataDecisionTreeNodeStatsClass *) objc;
  
  result = result && PartitionMatrix.Read(in,nodeclass->PointerToPartitionMatrixClass(),name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataDecisionTreeNodeStats
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataDecisionTreeNodeStats::print(ostream& out) const
{
  BaseDataDecisionTreeNodeSpec::print(out);
  out << "Decision Tree Node Statistics (";
  out << NumberOfObjects << " Virtual Objects): Gain: ";
  out << Gain;
  out << endl;
  PartitionMatrix.print(out);
  out << "\nGoal Statistics:";
  GoalStats.print(out);
  out << endl;
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataDecisionTreeNodeStats
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataDecisionTreeNodeStats::Clone()
{
  BaseDataDecisionTreeNodeStats *obj = new BaseDataDecisionTreeNodeStats;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataDecisionTreeNodeStats
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataDecisionTreeNodeStats::CopyClone(Identify * obj)
{
  BaseDataDecisionTreeNodeStats *objfull = (BaseDataDecisionTreeNodeStats *) obj;
  
  *this = *objfull;
  PartitionMatrix.CopyClone(&objfull->PartitionMatrix);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDecisionTreeNodeStats
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDecisionTreeNodeStats::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataDecisionTreeNodeSpec::EncodeThis(buffer);
  result = result && PartitionMatrix.EncodeThis(buffer);
  result = result && GoalStats.EncodeThis(buffer);
  result = result && Encode(buffer,Gain);
  result = result && Encode(buffer,NumberOfObjects);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataDecisionTreeNodeStats
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDecisionTreeNodeStats::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataDecisionTreeNodeSpec::DecodeThis(buffer);
  result = result && PartitionMatrix.DecodeThis(buffer);
  result = result && GoalStats.DecodeThis(buffer);
  result = result && Decode(buffer,Gain);
  result = result && Decode(buffer,NumberOfObjects);

  return result;
}
 
 
/*F ans = InsertElements(gainobject,mat,partition)
**
**  DESCRIPTION
**    gainobject: The gain of the partition
**    mat: The partition matrix
**    partition: The partition
**
**  REMARKS
**
*/
bool BaseDataDecisionTreeNodeStats::InsertElements(BaseDataReal *gainobject,
                                                   BaseDataDoubleMatrix *mat,
                                                   BaseDataKeyWords *partition)
{
  Gain = gainobject->GetValue();
  InsertPartition(partition);
  PartitionMatrix.CopyClone(mat);
  GoalStats = GoalStatistics();
  
  return true;
}
 
 
/*F GoalStatistics()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
ObjectList<double>& BaseDataDecisionTreeNodeStats::GoalStatistics()
{
  ObjectList<double> *goalstats = new ObjectList<double>;
  MatrixNumeric mat = this->GetCurrentMatrix();
  unsigned int size1 = mat.size();
  unsigned int size2 = mat[0].size();
  
  for(unsigned int j=0; j < size2 ;j++) {
    double value = 0.0;
      for(unsigned int i=0; i < size1; i++) {
	value += mat[i][j];
      }
      goalstats->AddObject(value);
  }
  return *goalstats;
}

/*F GetCurrentMatrix()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
MatrixNumeric& BaseDataDecisionTreeNodeStats::GetCurrentMatrix()
{
  return PartitionMatrix.CurrentMatrix();
}

/*F SetNumberOfElements(instances,instclass)  . .  number of virtual elements
**
**  DESCRIPTION
**    instances: 
**    instclass: 
**
**  REMARKS
**
*/
void BaseDataDecisionTreeNodeStats::SetNumberOfObjects(ObjectList<String>& names,
                                                       BaseDataSetOfLogicDescriptions& ldescrs,
                                                       DataSetOfLogicDescriptionsClass& ldescrsclass,
						       DataSetOfInstancesClass* instclasses)
{
  BaseDataConjunction *conj = PointerToConjunction();
  DataLogicalClass *logclass = (DataLogicalClass *) 
    instclasses->PointerToAllowedClasses()->GetObjectClass(LOGICAL_BASE_NAME);
  BaseDataLogical *logic = 
    (BaseDataLogical *) logclass->BaseDataObjectExample();
  
  NumberOfObjects = conj->NumberOfElements(names,logic,logclass,ldescrs,ldescrsclass);
  delete logic;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . BaseDataDecisionTreeNodeStats
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
bool BaseDataDecisionTreeNodeStats::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataDecisionTreeNodeSpec::WriteAsLine(out,objc);
  return result;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . BaseDataDecisionTreeNodeStats
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
bool BaseDataDecisionTreeNodeStats::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  out << "TreeNodeSpec:" << endl;
  bool result = BaseDataDecisionTreeNodeSpec::WriteAsASCII(out,objc);
  out << NumberOfObjects << " " << Gain << endl;
  result = result && PartitionMatrix.WriteAsASCII(out,objc);
  ObjectList<double>::iterator num;
  for(num = GoalStats.begin(); num != GoalStats.end();num++)
    {
      out << *num << " ";
    }
  out << " END" << endl;
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . BaseDataDecisionTreeNodeStats
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
bool BaseDataDecisionTreeNodeStats::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataDecisionTreeNodeSpec::WriteAsLatex(out,objc);
  return result;
}

/*S DataDecisionTreeNodeStatsClass
 */
/*F DataDecisionTreeNodeStatsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDecisionTreeNodeStatsClass::DataDecisionTreeNodeStatsClass()
{
  Identification = TREE_NODESTATS_ID;
  NameTag = TREE_NODESTATS_NAME;
  SubClass = "DecisionTreeNodeSpec";
  EncodeDecodeClass = NameTag;
} 
/*F DataDecisionTreeNodeStatsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataDecisionTreeNodeStatsClass::DataDecisionTreeNodeStatsClass(const DataDecisionTreeNodeStatsClass& data)
  : DataDecisionTreeNodeSpecClass(data),
    PartitionMatrixClass(data.PartitionMatrixClass)
{
} 
 
/*F DataDecisionTreeNodeStatsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataDecisionTreeNodeStatsClass::DataDecisionTreeNodeStatsClass(const int id, 
                                                               const String& name,
                                                               const String& descr)
  : DataDecisionTreeNodeSpecClass(id,name,descr)
{
  SubClass = "DecisionTreeNodeSpec";
  EncodeDecodeClass = TREE_NODESTATS_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataDecisionTreeNodeStatsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataDecisionTreeNodeStatsClass::print(ostream& out) const
{
  DataDecisionTreeNodeSpecClass::print(out);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataDecisionTreeNodeStatsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataDecisionTreeNodeStatsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataDecisionTreeNodeStatsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataDecisionTreeNodeSpecClass::Read(in,set);
  result = result && PartitionMatrixClass.Read(in,set);
  
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataDecisionTreeNodeStatsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataDecisionTreeNodeStatsClass::CopyClone(Identify *  objc)
{
  DataDecisionTreeNodeStatsClass *objcfull = (DataDecisionTreeNodeStatsClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataDecisionTreeNodeStatsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataDecisionTreeNodeStatsClass::Clone()
{
  DataDecisionTreeNodeStatsClass* id = new DataDecisionTreeNodeStatsClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataDecisionTreeNodeStatsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDecisionTreeNodeStatsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataDecisionTreeNodeSpecClass::EncodeThis(buffer);
  result = result && PartitionMatrixClass.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataDecisionTreeNodeStatsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDecisionTreeNodeStatsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataDecisionTreeNodeSpecClass::DecodeThis(buffer);
  result = result && PartitionMatrixClass.DecodeThis(buffer);

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
BaseDataObject * DataDecisionTreeNodeStatsClass::BaseDataObjectExample()
{ 
  //cout << "Make DecisionTreeNodeStats Example\n";
  return (BaseDataObject *) new BaseDataDecisionTreeNodeStats();
}
/*F pntr = PointerToPartitionMatrixClass()  . . . . . . . . . . .  class info
**
**  DESCRIPTION
**    pntr: The pointer
**
**  REMARKS
**
*/
DataDoubleMatrixClass *DataDecisionTreeNodeStatsClass::PointerToPartitionMatrixClass()
{
  return &PartitionMatrixClass;
}

/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataDecisionTreeNodeStatsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataDecisionTreeNodeStatsClass*& obj)
{
  obj = new DataDecisionTreeNodeStatsClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataDecisionTreeNodeStats
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataDecisionTreeNodeStats*& obj)
{
  obj = new BaseDataDecisionTreeNodeStats;
  return obj->DecodeThis(buffer);
}
/*S BaseDataFilterDecisionTreeNode
 */ 
/*F BaseDataFilterDecisionTreeNode()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataFilterDecisionTreeNode::BaseDataFilterDecisionTreeNode()
  : DecisionTreeS(DECISION_TREE),
    MinimumNumberOfInstancesS(MINIMUM_NUMBER_INSTANCES),
    MaximumPartitionPercentS(MAXIMUM_PARTITION_PERCENT),
    MinimumEntropyValueS(MINIMUM_ENTROPY_VALUE),
    MaximumNumberOfNodesS(MAXIMUM_NUMBER_NODES)
{
  Identification = TREE_DECTREEFILTER_ID;
  NameTag = TREE_DECTREEFILTER_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataFilterDecisionTreeNode(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataFilterDecisionTreeNode::BaseDataFilterDecisionTreeNode(const BaseDataFilterDecisionTreeNode& data)
  : BaseDataAlgorithmOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataFilterDecisionTreeNode
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataFilterDecisionTreeNode::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataFilterDecisionTreeNode
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataFilterDecisionTreeNode::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataFilterDecisionTreeNode
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataFilterDecisionTreeNode::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  out << "Minimum Number of Instances: " << MinimumNumberOfInstances << endl;
  out << "MaximumPartitionPercent:     " << MaximumPartitionPercent << endl;
  out << "MinimumEntropyValue:         " << MinimumEntropyValue << endl;
  out << "MaximumNumberOfNodes:        " << MaximumNumberOfNodes << endl;

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataFilterDecisionTreeNode
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataFilterDecisionTreeNode::Clone()
{
  BaseDataFilterDecisionTreeNode *obj = new BaseDataFilterDecisionTreeNode;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataFilterDecisionTreeNode
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataFilterDecisionTreeNode::CopyClone(Identify * obj)
{
  BaseDataFilterDecisionTreeNode *objfull = (BaseDataFilterDecisionTreeNode *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataFilterDecisionTreeNode
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataFilterDecisionTreeNode::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataFilterDecisionTreeNode
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataFilterDecisionTreeNode::DecodeThis(CommBuffer& buffer)
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
bool BaseDataFilterDecisionTreeNode::SetUpAlgorithms(BaseDataSetOfInstances*,
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
bool BaseDataFilterDecisionTreeNode::CheckInput(BaseDataSetOfInstances*,
						 DataSetOfInstancesClass*,
						 BaseDataAlgorithmRun *run,
						 DataAlgorithmRunClass*)
{
  bool result = true;

  if(run->ParameterInList(DecisionTreeS))
    {
      if(run->ParameterInList(MinimumNumberOfInstancesS))
	{
	  if(run->ParameterInList(MaximumPartitionPercentS))
	    {
	      if(run->ParameterInList(MinimumEntropyValueS))
		{
		  if(!run->ParameterInList(MaximumNumberOfNodesS))
		    {
		      cerr << "The parameter '" << MaximumNumberOfNodesS << "' was not in the list of parameters";
		      result = false;
		    }
		}
	      else
		{
		  cerr << "The parameter '" << MinimumEntropyValueS << "' was not in the list of parameters";
		  result = false;
		}
	    }
	  else
	    {
	      cerr << "The parameter '" << MaximumPartitionPercentS << "' was not in the list of parameters";
	      result = false;
	    }
	}
      else
	{
	  cerr << "The parameter '" << MinimumNumberOfInstancesS << "' was not in the list of parameters";
	  result = false;
	}
    }
  else
    {
      cerr << "The parameter '" << DecisionTreeS << "' was not in the list of parameters";
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
bool BaseDataFilterDecisionTreeNode::SetUpInput(BaseDataSetOfInstances* instances,
						 DataSetOfInstancesClass* instancesclass,
						 BaseDataAlgorithmRun *run,
						 DataAlgorithmRunClass* rclass)
{
  bool result = true;
  DecisionTree = (BaseDataDecisionTreeCreate *) run->ParameterValue(DecisionTreeS);
  BaseDataInteger *numinst = (BaseDataInteger *) run->ParameterValue(MinimumNumberOfInstancesS);
  MinimumNumberOfInstances = numinst->GetValue();
  if(MinimumNumberOfInstances < 1)
    MinimumNumberOfInstances = 1.0;
  BaseDataReal *num = (BaseDataReal *) run->ParameterValue(MaximumPartitionPercentS);
  MaximumPartitionPercent = num->GetValue();
  num = (BaseDataReal *) run->ParameterValue(MinimumEntropyValueS);
  MinimumEntropyValue = num->GetValue();
  BaseDataInteger *i = (BaseDataInteger *) run->ParameterValue(MaximumNumberOfNodesS);
  MaximumNumberOfNodes = i->GetValue();
  if(rclass->getDebugLevel() > 1)
    {
      cout << "Minimum Number of Instances:       " << MinimumNumberOfInstances << endl;
      cout << "Maximum Partition Percent on Node: " <<  MaximumPartitionPercent << endl;
      cout << "MinimumEntropyValue:               " << MinimumEntropyValue << endl;
      cout << "Maximum Number Of Nodes in Tree    " << MaximumNumberOfNodes << endl;
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
bool BaseDataFilterDecisionTreeNode::Calculate(BaseDataSetOfInstances*,
					       DataSetOfInstancesClass*,
					       BaseDataAlgorithmRun*,
					       DataAlgorithmRunClass *runclass)
{
  cout << "Start Filter: " << runclass->getDebugLevel() << endl;
  if(runclass->getDebugLevel() > 4)
    cout << "BaseDataFilterDecisionTreeNode::Calculate" << endl;

  BaseDataDecisionTreeNodeStats *node = DecisionTree->getCurrentNode();
  bool result = true;
  if(DecisionTree->Tree.getNodeCount() > MaximumNumberOfNodes) {
      result = false;
      if(runclass->getDebugLevel() > 4)
	cout << " Maximum number of nodes exceeded: " << DecisionTree->Tree.getNodeCount() << endl;
    }  else {
      if(runclass->getDebugLevel() > 4)
	cout << "Filtering Node: " << node->NameTag << endl;

      double num = node->GetNumberOfObjects();

      if(node->NameTag == DecisionTree->Tree.getRootNodeName())
	result = true;
      else if(num <= MinimumNumberOfInstances)
	{
	  result = false;
	  if(runclass->getDebugLevel() > 4)
	    cout << "Under the number of instances (" << MinimumNumberOfInstances << ") " << num << endl;
	}
      else
	{
	  double value = node->GetGain();
	  if(value < MinimumEntropyValue) {
	    result = false;
	    if(runclass->getDebugLevel() > 4)
	      cout << "Entropy Value (" << MinimumEntropyValue  << ")  " << value << endl;
	  } else {
	    result = true;
	    ObjectList<double> *goalstats = node->PointerToGoalStats();
	    for(ObjectList<double>::iterator p=goalstats->begin();
		p != goalstats->end();
		p++)
	      {
		if((*p) > MaximumPartitionPercent)
		  {
		    result = false;
		    if(runclass->getDebugLevel() > 4)
		      cout << "Partition percent (" << MaximumPartitionPercent << ") exceeded " << *p << endl;
		  }
	      }
	  }
	}
    }
  cout << "Set Answer: " << result << endl;
  Answer = new BaseDataContinuous();
  Answer->NameTag = DECISION_TREE_FILTER_ANSWER;

  if(result)
    {
      if(runclass->getDebugLevel() > 3)
	cout << "Filter Answer: True   " << node->NameTag << endl;
      Answer->SetValue(1.0);
    }
  else
    {
      if(runclass->getDebugLevel() > 3)
	cout << "Filter Answer: False  "  << node->NameTag << endl;
      Answer->SetValue(0.0);
    }
  return true;
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
bool BaseDataFilterDecisionTreeNode::WriteOutputValues(BaseDataSetOfInstances*,
							DataSetOfInstancesClass*,
							BaseDataAlgorithmRun* run,
							DataAlgorithmRunClass*)
{
  bool result = true;
  
  run->AddParameter(Answer);

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
bool BaseDataFilterDecisionTreeNode::ConcludeRun(BaseDataSetOfInstances*,
						  DataSetOfInstancesClass*,
						  BaseDataAlgorithmRun*,
						  DataAlgorithmRunClass*)
{
  bool result = true;
  delete Answer;
  return result;
}
 
/*S DataFilterDecisionTreeNodeClass
 */
/*F DataFilterDecisionTreeNodeClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataFilterDecisionTreeNodeClass::DataFilterDecisionTreeNodeClass()
{
  Identification = TREE_DECTREEFILTER_ID;
  NameTag = TREE_DECTREEFILTER_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataFilterDecisionTreeNodeClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataFilterDecisionTreeNodeClass::DataFilterDecisionTreeNodeClass(const DataFilterDecisionTreeNodeClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataFilterDecisionTreeNodeClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataFilterDecisionTreeNodeClass::DataFilterDecisionTreeNodeClass(const int id, 
								 const String& name,
								 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = TREE_DECTREEFILTER_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataFilterDecisionTreeNodeClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataFilterDecisionTreeNodeClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataFilterDecisionTreeNodeClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataFilterDecisionTreeNodeClass, there is no further information.
**
**  REMARKS
**
*/
bool DataFilterDecisionTreeNodeClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataFilterDecisionTreeNodeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataFilterDecisionTreeNodeClass::CopyClone(Identify *  objc)
{
  DataFilterDecisionTreeNodeClass *objcfull = (DataFilterDecisionTreeNodeClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataFilterDecisionTreeNodeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataFilterDecisionTreeNodeClass::Clone()
    {
      DataFilterDecisionTreeNodeClass* id = new DataFilterDecisionTreeNodeClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataFilterDecisionTreeNodeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataFilterDecisionTreeNodeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataFilterDecisionTreeNodeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataFilterDecisionTreeNodeClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataFilterDecisionTreeNodeClass::BaseDataObjectExample()
{ 
  //cout << "Make FilterDecisionTreeNode Example\n";
  return (BaseDataObject *) new BaseDataFilterDecisionTreeNode();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataFilterDecisionTreeNodeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataFilterDecisionTreeNodeClass*& obj)
     {
     obj = new DataFilterDecisionTreeNodeClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataFilterDecisionTreeNode
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataFilterDecisionTreeNode*& obj)
     {
     obj = new BaseDataFilterDecisionTreeNode;
     return obj->DecodeThis(buffer);
     }


/*S Utility
 */
/*F AddEntropyAlgorithmClasses(set) . . . . . . . .  basic algorithm data types
**
**  DESCRIPTION
**    set: The set of data types
**
**  REMARKS
**
*/
void AddDecisionTreeClasses(DataSetOfObjectsClass& set)
{
  String dnodetree("Decision Tree Node");
  String dnodestats("Decision Tree Node Statistics");
  String decisiontree("Decision Tree");
  String computetree("Compute Decision Tree");
  String filter("Decision Tree Filter Routine");
  
  DataDecisionTreeNodeSpecClass dnodeclass(TREE_NODESPEC_ID,
                                           TREE_NODESPEC_NAME,
                                           dnodetree);
  DataDecisionTreeNodeStatsClass statsclass(TREE_NODESTATS_ID,
                                            TREE_NODESTATS_NAME,
                                            dnodestats);
  DataDecisionTreeClass treeclass(TREE_DECISION_ID,
                                  TREE_DECISION_NAME,
                                  decisiontree);
  DataDecisionTreeCreateClass createclass(TREE_CREATE_ID,
                                          TREE_CREATE_NAME,
                                          computetree);
  DataFilterDecisionTreeNodeClass filterclass(TREE_DECTREEFILTER_ID,
                                          TREE_DECTREEFILTER_NAME,
                                          filter);
  
  set.AddObjectClass(dnodeclass);
  set.AddObjectClass(statsclass);
  set.AddObjectClass(treeclass);
  set.AddObjectClass(createclass);
  set.AddObjectClass(filterclass);
}
extern void DecisionTreeEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataDecisionTreeNodeSpecClass,BaseDataDecisionTreeNodeSpec,TREE_NODESPEC_NAME);
  EncodeDecodeRegisterClass(DataDecisionTreeNodeStatsClass,BaseDataDecisionTreeNodeStats,TREE_NODESTATS_NAME);
  EncodeDecodeRegisterClass(DataDecisionTreeClass,BaseDataDecisionTree,TREE_DECISION_NAME);
  EncodeDecodeRegisterClass(DataDecisionTreeCreateClass,BaseDataDecisionTreeCreate,TREE_CREATE_NAME);
  EncodeDecodeRegisterClass(DataFilterDecisionTreeNodeClass,BaseDataFilterDecisionTreeNode,TREE_DECTREEFILTER_NAME);

//  bool (*toproutine)(CommBuffer&,Identify*&);
//
//  bool (*rout1)(CommBuffer&,DataDecisionTreeNodeSpecClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout1;
//  SingleDecodeRoutine p1(TREE_NODESPEC_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p1.StructureName] = p1;
//
//  bool (*rout2)(CommBuffer&,DataDecisionTreeNodeStatsClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout2;
//  SingleDecodeRoutine p2(TREE_NODESTATS_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p2.StructureName] = p2;
//
//  bool (*rout3)(CommBuffer&,DataDecisionTreeClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout3;
//  SingleDecodeRoutine p3(TREE_DECISION_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p3.StructureName] = p3;
//
//  bool (*rout4)(CommBuffer&,DataDecisionTreeCreateClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout4;
//  SingleDecodeRoutine p4(TREE_CREATE_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p4.StructureName] = p4;
//
//  bool (*rout5)(CommBuffer&,DataFilterDecisionTreeNodeClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout5;
//  SingleDecodeRoutine p5(TREE_DECTREEFILTER_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p5.StructureName] = p5;
//
//  String s11("Object.");
//  String s111(TREE_NODESPEC_NAME);
//  s11.AppendToEnd(s111);
//  bool (*rout11)(CommBuffer&,BaseDataDecisionTreeNodeSpec*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout11;
//  SingleDecodeRoutine p11(s11,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p11.StructureName] = p11;
//  
//  String s21("Object.");
//  String s211(TREE_NODESTATS_NAME);
//  s21.AppendToEnd(s211);
//  bool (*rout21)(CommBuffer&,BaseDataDecisionTreeNodeStats*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout21;
//  SingleDecodeRoutine p21(s21,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p21.StructureName] = p21;
//  
//  String s31("Object.");
//  String s311(TREE_DECISION_NAME);
//  s31.AppendToEnd(s311);
//  bool (*rout31)(CommBuffer&,BaseDataDecisionTree*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout31;
//  SingleDecodeRoutine p31(s31,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p31.StructureName] = p31;
//  
//  String s41("Object.");
//  String s411(TREE_CREATE_NAME);
//  s41.AppendToEnd(s411);
//  bool (*rout41)(CommBuffer&,BaseDataDecisionTreeCreate*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout41;
//  SingleDecodeRoutine p41(s41,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p41.StructureName] = p41;
//  
//  String s51("Object.");
//  String s511(TREE_DECTREEFILTER_NAME);
//  s51.AppendToEnd(s511);
//  bool (*rout51)(CommBuffer&,BaseDataFilterDecisionTreeNode*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout51;
//  SingleDecodeRoutine p51(s51,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p51.StructureName] = p51;
}
