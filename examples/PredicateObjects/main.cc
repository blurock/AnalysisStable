/*  FILE     main.cc
**  PACKAGE     REACTION    
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    
**
**  REFERENCES
**
**  COPYRIGHT (C) 1995  REACTION Project / Edward S. Blurock 
*/
 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "DataObjects.hh"
#include "OperationObjects.hh"
#include "InstanceObjects.hh"
#include "PredicateObjects.hh"

static int SimplePredicate(ReactionSystemBase *level1);
static int SimpleDescription(ReactionSystemBase *level1);
static int SimpleConjunction(ReactionSystemBase *level1);
static int PartitionMatrixTest(ReactionSystemBase *level1);

template class list<BasicPair<String, String> >;
//bool operator==(const BasicPair<String,String>& pair1, const BasicPair<String,String>& pair2);
#ifdef _unix
bool operator==(BasicPair<String, String> const &p1, BasicPair<String, String> const &p2)
{
  return ( (p1.I == p2.I) && (p1.J == p2.J));
}
bool operator<(BasicPair<String, String> const &p1, BasicPair<String, String> const &p2)
{
  return ( (p1.I < p2.I) || (p1.J < p2.J));
}
#endif

class SystemCoreObjectTest : public InstanceSystemSave
{
public:

  SystemCoreObjectTest(int argc, char *argv[])
    : InstanceSystemSave(argc,argv)
    {
    }
  void StandardObjectsSetUp()
    {
      InstanceSystem::StandardObjectsSetUp();
      AddPredicateClasses(getStandard());
    }

  void EncodeDecodeObjectsSetUp()
    {
      InstanceSystem::EncodeDecodeObjectsSetUp();
      InitialSetOfDataObjectsEncodeDecodeRoutines();
      InitialSetOfPredicateEncodeDecodeRoutines();
    }
  
  void CommandSetUp()
    {
      InstanceSystemSave::CommandSetUp();
      
      SingleSystemCommand pred("Predicate",
				"Simple Predicate Test",
				&SimplePredicate);
      Commands.AddObject("Predicate",pred);
      SingleSystemCommand descr("Description",
				"Simple Description Test",
				&SimpleDescription);
      Commands.AddObject("Description",descr);
      SingleSystemCommand conj("Conjunction",
				"Simple Conjunction Test",
				&SimpleConjunction);
      Commands.AddObject("Conjunction",conj);
      SingleSystemCommand fulltable("FullTable",
				"Partition Table Test with a set of Instances",
				&PartitionMatrixTest);
      Commands.AddObject("FullTable",fulltable);
    }
};
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int main(int argc, char *argv[])
{
  SystemCoreObjectTest test(argc,argv);
  
  test.Initialization();
  StandardAllowedClasses = &(test.InstanceClasses);
  test.Run();
  test.Exit();
}
/*F SimplePredicate . . . . . . . . . . . . . .  simple single predicate test
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int SimplePredicate(ReactionSystemBase *level1)
{
  SystemCoreObjectTest *test = (SystemCoreObjectTest *) level1;
  
  if(test->Inputs.size() < 3)
    {
      cout << "instances: The file name of a set of instances and data types\n";
      cout << "predicate: The file name with a single predicate\n";
      cout << "ptype:     The predicate type\n";
      
      return 1;
    }

  String instancesf = test->Inputs.front();
  test->Inputs.pop_front();
  String predicatef = test->Inputs.front();
  test->Inputs.pop_front();
  String ptype = test->Inputs.front();
  test->Inputs.pop_front();
  
  OpenInputFile file(instancesf);
  bool result = (*test).InstanceClasses.Read(file.Stream,(*test).getStandard());
  BaseDataInstance *instance = new BaseDataInstance;
  if(result)
    {
      cout << "------------ Read In Data -----------------------\n";
      (*instance).Read(file.Stream,&(*test).InstanceClasses,(*test).getStandard().NameTag);
    }
  else
    {
      cout << "Read in was unsuccessful\n";
    }

  OpenInputFile pfile(predicatef);

  BaseDataPredicate predicate;
  DataPredicateClass *predclass = (DataPredicateClass *) (*test).InstanceClasses.GetObjectClass(ptype);
  
  
  result = result && predicate.Read(pfile.Stream,(DataObjectClass *) predclass);
  if(result)
    {
      cout << "\n-------------- The Predicate ---------------------------------\n";
      predicate.print(cout);
      cout << "\n--------------------------------------------------------------\n";

      BaseDataLogical logic;
      DataLogicalClass logclass;
      
      BaseDataObject *logobj = predicate.operator()(&logic,instance,&logclass,&(*test).InstanceClasses);
      cout << "\n-------------- The Logical Answer ----------------------------\n";
      (*logobj).print(cout);
      cout << "\n--------------------------------------------------------------\n";
      
    }
  else
    {
      cout << "\n Read In Unsuccessful\n";
    }
  
  return 0;
}
/*F SimpleDescription . . . . . . . . . . . . . .  simple description test
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int SimpleDescription(ReactionSystemBase *level1)
{
  SystemCoreObjectTest *test = (SystemCoreObjectTest *) level1;
  
  if(test->Inputs.size() < 3)
    {
      cout << "instances: The file name of a set of instances and data types\n";
      cout << "descriptionclass: The file name with the description classes\n";
      cout << "description: The file name with the description\n";
      
      return 1;
    }

  String instancesf = test->Inputs.front();
  test->Inputs.pop_front();
  String descrclassf = test->Inputs.front();
  test->Inputs.pop_front();
  String descrf = test->Inputs.front();
  test->Inputs.pop_front();
  
  OpenInputFile file(instancesf);
  bool result = (*test).InstanceClasses.Read(file.Stream,(*test).getStandard());
  BaseDataInstance *instance = new BaseDataInstance;
  if(result)
    {
      cout << "------------ Read In Data -----------------------\n";
      (*instance).Read(file.Stream,&(*test).InstanceClasses,(*test).getStandard().NameTag);
    }
  else
    {
      cout << "Read in was unsuccessful\n";
    }

  cout << "\n===============================================================================\n";
  cout << "                   Description Test\n";
  cout << "===============================================================================\n";
  
  OpenInputFile dcfile(descrclassf);

  BaseDataPredicate predicate;
  DataDescriptionClass descrclass;
  result = result && descrclass.Read(dcfile.Stream,(*test).getStandard());
  
  cout << "\n===============================================================================\n";
  if(result)
    {
      cout << "Description Class\n";
      descrclass.print(cout);
    }
  else
    {
      cout << "Description Class Read in Error\n";
    }
  cout << "\n===============================================================================\n";
  BaseDataDescription description;
  OpenInputFile dfile(descrf);
  result = result && description.Read(dfile.Stream,(DataObjectClass *) &descrclass);
  if(result)
    {
      cout << "\n-------------- The Description ---------------------------------\n";
      description.print(cout);
      cout << "\n--------------------------------------------------------------\n";
      BaseDataLogical logic;
      DataLogicalClass logclass;
      ObjectList<String> names = description.ListOfObjectNames();
      
      BaseDataLogicDescription ldescr;
      
      ldescr.AddLogicInstanceSet(&logic,&logclass,&(*test).Instances,&(*test).InstanceClasses,
				 names,instance,&(*test).InstanceClasses);
      cout << "\n-------------- The Logic Description ------------------------------\n";
      ldescr.print(cout);
      cout << "\n-------------------------------------------------------------------\n";
      ObjectList<double> values = ldescr.LogicValues();
      values.print(cout);
      cout << "\n";
      
    }
  else
    {
      cout << "\n Read In Unsuccessful\n";
    }
  
  return 0;
}
/*F SimpleConjunction . . . . . . . . . . . . . .  simple conjunction test
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int SimpleConjunction(ReactionSystemBase *level1)
{
  SystemCoreObjectTest *test = (SystemCoreObjectTest *) level1;
  
  if(test->Inputs.size() < 3)
    {
      cout << "instances: The file name of a set of instances and data types\n";
      cout << "descriptionclass: The file name with the description classes\n";
      cout << "description: The file name with the description\n";
      
      return 1;
    }

  String instancesf = test->Inputs.front();
  test->Inputs.pop_front();
  String descrclassf = test->Inputs.front();
  test->Inputs.pop_front();
  String descrf = test->Inputs.front();
  test->Inputs.pop_front();
  
  OpenInputFile file(instancesf);
  bool result = (*test).InstanceClasses.Read(file.Stream,(*test).getStandard());
  BaseDataInstance *instance = new BaseDataInstance;
  if(result)
    {
      cout << "------------ Read In Data -----------------------\n";
      (*instance).Read(file.Stream,&(*test).InstanceClasses,(*test).getStandard().NameTag);
    }
  else
    {
      cout << "Read in was unsuccessful\n";
    }

  cout << "\n===============================================================================\n";
  cout << "                   Conjunction Test\n";
  cout << "===============================================================================\n";
  
  OpenInputFile dcfile(descrclassf);

  BaseDataPredicate predicate;
  DataDescriptionClass descrclass;
  result = result && descrclass.Read(dcfile.Stream,(*test).getStandard());
  
  cout << "\n===============================================================================\n";
  if(result)
    {
      cout << "Description Class\n";
      descrclass.print(cout);
    }
  else
    {
      cout << "Description Class Read in Error\n";
    }
  cout << "\n===============================================================================\n";
  BaseDataDescription description;
  OpenInputFile dfile(descrf);
  result = result && description.Read(dfile.Stream,(DataObjectClass *) &descrclass);
  if(result)
    {
      cout << "\n-------------- The Description ---------------------------------\n";
      description.print(cout);
      cout << "\n--------------------------------------------------------------\n";
      BaseDataConjunction conj(description);
      
      BaseDataLogical logic;
      DataLogicalClass logclass;
      
      conj.operator()(&logic,instance,
		      &logclass,&(*test).InstanceClasses);
      cout << "\n-------------- The Logic Description ------------------------------\n";
      logic.print(cout);
      cout << "\n-------------------------------------------------------------------\n";
    }
  else
    {
      cout << "\n Read In Unsuccessful\n";
    }
  
  return 0;
}
/*F SimpleEntropy(level1) 
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int PartitionMatrixTest(ReactionSystemBase *level1)
{
  SystemCoreObjectTest *test = (SystemCoreObjectTest *) level1;
  
  if(test->Inputs.size() < 3)
    {
      cout << "instanceclasses: The file name of a set of data types\n";
      cout << "instances: The file name of a set of parameters and data types\n";
      cout << "partition: The name of the partition parameter\n";
      cout << "conjunction: The name of the conjunction parameter\n";
      cout << "debug level: [optional] \n";
      
      cout << "For example:  FullTable InstanceClass.txt Instances.txt PartitionTable.Var3.Var1 Conjunction\n";
      
      return 1;
    }
  
  BaseDataSetOfInstances instances;
  DataSetOfInstancesClass instanceclasses;
  
  String instclassesS = test->Inputs.front();
  test->Inputs.pop_front();
  String instancesS = test->Inputs.front();
  test->Inputs.pop_front();
  String partitionS = test->Inputs.front();
  test->Inputs.pop_front();
  String conjunctionS = test->Inputs.front();
  test->Inputs.pop_front();
  String DebugLevelS = test->Inputs.front();
  test->Inputs.pop_front();
  unsigned int debuglevel = DebugLevelS.ToInteger();
  
  
  cout << "\n______________________________________________________________________________\n";
  
  OpenInputFile instclassesF(instclassesS);
  bool result = instanceclasses.Read(instclassesF.Stream,test->getStandard());
  instanceclasses.SetDebugLevel(debuglevel);
  
  cout << "\n______________________________________________________________________________\n";
  OpenInputFile instancesF(instancesS);
  result = result && instances.Read(instancesF.Stream,&instanceclasses);
  instances.print(cout);

  cout << "\n______________________________________________________________________________\n";
  cout << "\n";
  cout << "\n====== List of Instances ====\n";
  ObjectList<String> names =  instances.ListOfInstanceNames();
  names.print(cout);
  cout << "\n====== List of Attributes ====\n";
  ObjectList<String> types;
  cout << instances.ListOfInstanceAttributeNames(names,types,instanceclasses,true);
  cout << "\n====== List of Common Attributes ====\n";
  types.AddObject("Integer");
  cout << instances.ListOfInstanceAttributeNames(names,types,instanceclasses,true);
  cout << "\n";
  cout << "\n===============================================================================\n";
  cout << "                   Partition Table Test\n";
  cout << "===============================================================================\n";
  
  BaseDataPartitionTable table(&instances,partitionS);
  if(result)
    {
      cout << "\n-------------- The Partition Table ---------------------------------\n";
      table.print(cout);
      cout << "\n--------------------------------------------------------------\n";
      if(instances.IsInList(conjunctionS))
	{
	  BaseDataKeyWords *keys = (BaseDataKeyWords *) instances.GetObject(conjunctionS);
	  
	  BaseDataDescription descr(&instances,*keys);
	  DataDescriptionClass descrclass;
	  
	  BaseDataConjunction conj(descr);
	  DataConjunctionClass conjclass;
	  //*(conjclass.LogicalOperationsClassPointer()) = (*test).InstanceClasses;
	  
	  BaseDataLogical logic;
	  DataLogicalClass logclass;
	  
	  ObjectList<int> predtypes;
	  predtypes.AddObject(PREDICATE_BASE_ID);
	  ObjectList<String> descrnames = (*test).Instances.ListOfObjectNames(predtypes);
	  cout << "List of Predicates: ";
	  descrnames.print(cout);
	  cout << endl;
	  
	  BaseDataSetOfLogicDescriptions ldescrs;
	  DataSetOfLogicDescriptionsClass ldescrsclass;
	  
	  ldescrs.AddLogicalObjects(&logic,&logclass,&descrclass,
				    &(*test).Instances,&(*test).InstanceClasses,
				    names,descrnames);

	  cout << "\n---------------- Conjunction  ---------------------------\n";
	  conj.print(cout);
	  cout << "\n---------------- Partition Matrix ---------------------------\n";
	  ObjectList<String> names = instances.ListOfInstanceNames();
	  MatrixNumeric *mat = table.CalculatePartitionMatrixFromSet(ldescrs,
								     &instances,
								     &instanceclasses,
								     ldescrsclass,
								     &conj,
								     &conjclass,
								     names);
	  cout << "\n--------------------------------------------------------------\n";
	  mat->print(cout);
	  cout << "\n--------------------------------------------------------------\n";
	}
      else
	{
	  cout << "\n No Conjunction '";
	  cout << conjunctionS;
	  cout << endl;
	}
    }
  else
    {
      cout << "\n Read In Unsuccessful\n";
    }
  
  return 0;
}
 
