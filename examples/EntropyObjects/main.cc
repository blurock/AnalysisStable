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
#define TEMPLATE_INSTANTIATION
#include "CoreObjects/CoreDataObjects.hh"
#include "CoreObjects/NumericObjects.hh"
#include "CoreObjects/LogicalObjects.hh"
#include "CoreObjects/FunctionReal1DObjects.hh"
#include "CoreObjects/OperationObjects.hh"
#include "CoreObjects/DirectedTreeObjects.hh"
#include "CoreObjects/DataObjects.hh"
#include "CoreObjects/InstanceObjects.hh"
#include "CoreObjects/SelectObjects.hh"
#include "CoreObjects/AlgorithmObjects.hh"
#include "CoreObjects/InstanceAlgorithms.hh"
#include "CoreObjects/PredicateObjects.hh"
#include "CoreObjects/EntropyObjects.hh"

template class list<String>;
template class list<double>;
template class SearchableObjectList<String, int>;
template class SearchableObjectList<String, double>;
template class list<Identify>;
template class list< BasicPair<Identify,Identify> >;
template class list< BasicPair<String,String> >;
/*
template class BasicPair<String,int>;
template class PairList<String,int>;
template operator==(BasicPair<String, int> const &, BasicPair<String, int> const &);
template operator<<(ostream &, BasicPair<String, int> const &);
template Decode(CommBuffer &, BasicPair<String, int> &);
template Encode(CommBuffer &, BasicPair<String, int> &);
template class list<BasicPair<String, int> >;
*/

static int SimpleEntropy(ReactionSystemBase *level1);

class SystemCoreObjectTest : public ReactionSystemLevel1
{
public:
  DataSetOfObjectsClass Standard;
  DataInstanceClass InstanceClasses;


  SystemCoreObjectTest(int argc, char *argv[])
    : ReactionSystemLevel1(argc,argv)
    {
    }
  void Initialization()
    {     
      InitialSetOfNumericEncodeDecodeRoutines();
      InitialSetOfLogicalEncodeDecodeRoutines();
      InitialSetOfOperationEncodeDecodeRoutines();
      InitialSetOfODRealEncodeDecodeRoutines();
      
      AddNumericClasses(Standard);
      AddLogicalClasses(Standard);
      AddFunctionClasses(Standard);
      AddOperationClasses(Standard);
      AddPredicateClasses(Standard);
      AddDataObjectClasses(Standard);
      AddEntropyAlgorithmClasses(Standard);

      SingleSystemCommand entropy("Entropy",
				"Simple Entropy Test",
				&SimpleEntropy);
      Commands.AddObject("Entropy",entropy);
    }
  int Run()
    {  
      cout << "\n==================================\n";
      return Commands.ExecuteCommand(0,0,this);
    }
  int Exit()
    {
      return 0;
    }
  BaseDataSetOfObjects& ReadInData(const String& filename);
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
  test.Run();
}
 
/*F SimpleEntropy(level1) 
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int SimpleEntropy(ReactionSystemBase *level1)
{
  SystemCoreObjectTest *test = (SystemCoreObjectTest *) level1;
  AlgorithmAndInstanceReadIn(test->Inputs,test->Standard);
  
  /*

  if(test->Inputs.size() < 3)
    {
      cout << "instanceclasses: The file name of a set of data types\n";
      cout << "instances: The file name of a set of parameters and data types\n";
      cout << "partition: The name of the partition parameter\n";
      return 1;
    }
  
  BaseDataSetOfInstances instances;
  DataSetOfInstancesClass instanceclasses;
  BaseDataAlgorithmRun run;
  DataAlgorithmRunClass rclass;
  
  String instclassesS = test->Inputs.front();
  test->Inputs.pop_front();
  String instancesS = test->Inputs.front();
  test->Inputs.pop_front();
  String algorithmS = test->Inputs.front();
  test->Inputs.pop_front();
  
  cout << "\n______________________________________________________________________________\n";
  
  OpenInputFile instclassesF(instclassesS);
  bool result = instanceclasses.Read(instclassesF.Stream,test->Standard);
  
  cout << "\n______________________________________________________________________________\n";
  OpenInputFile instancesF(instancesS);
  result = result && instances.Read(instancesF.Stream,&instanceclasses);
  //instances.print(cout);

  cout << "\n______________________________________________________________________________\n";
  cout << "\n";
  cout << "\n====== List of Instances ====\n";
  ObjectList<String> names =  instances.ListOfInstanceNames();
  cout << names;
  cout << "\n====== List of Attributes ====\n";
  ObjectList<String> types;
  cout << instances.ListOfInstanceAttributeNames(names,types,instanceclasses,true);
  cout << "\n====== List of Common Attributes ====\n";
  types.AddObject("Integer");
  cout << instances.ListOfInstanceAttributeNames(names,types,instanceclasses,true);
  cout << "\n";
  cout << "===================================================================\n";
  cout << "                        Entropy Test\n";
  cout << "===================================================================\n";
  
    cout << "Read in Algorihthm Run Class\n";

  OpenInputFile algorithmF(algorithmS);

  rclass.Read(algorithmF.Stream,test->Standard);
  cout << "\n+++++++++++++++++++++++++++++++++++++++\n";
  cout << "The AlgorithmRun Class\n";
  rclass.print(cout);
  cout << "\n=================+++++++++++++++++++++++++++++++++++++++\n";

  
  cout << "Read in Algorihthm Run Class\n";
  run.Read(algorithmF.Stream,&rclass,algorithmS);
  cout << "\n+++++++++++++++++++++++++++++++++++++++\n";
  ObjectList<String> notfound = run.TransferInputParameters(&run,&instances);
  cout << "Parameters not Transfered\n";
  notfound.print(cout);
  cout << "\n";
  
  cout << "The algorithm:\n";
  run.print(cout);
  cout << "\n";
  cout << "\n+++++++++++++++++++++++++++++++++++++++\n";

  run.Run(&instances,&instanceclasses,&rclass);
  cout << "\n";
  */
  
  return 0;
}

