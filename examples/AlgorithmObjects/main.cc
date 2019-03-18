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
#include "OperationObjects.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "MenuObjects.hh"
#include "DirectedTreeObjects.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "InstanceAlgorithms.hh"

static int AlgorithmReadIn(ReactionSystemBase *level1);
static int SimpleSetUp(ReactionSystemBase *level1);
 
class SystemCoreObjectTest : public AlgorithmSystemSave
{
public:
  SystemCoreObjectTest(int argc, char *argv[])
    : AlgorithmSystemSave(argc,argv)
    {
    }
  virtual void StandardObjectsSetUp()
    {
      AlgorithmSystemSave::StandardObjectsSetUp();
      AddInstanceAlgorithmsClasses(getStandard());
    }
  virtual void EncodeDecodeObjectsSetUp()
    {
      AlgorithmSystemSave::EncodeDecodeObjectsSetUp();
      InitialInstanceAlgorithmsEncodeDecodeRoutines();
    }
  void CommandSetUp()
    {     
      AlgorithmSystemSave::CommandSetUp();

      SingleSystemCommand readit("TestRead",
				"Simple Read in Test",
				&AlgorithmReadIn);
      Commands.AddObject("TestRead",readit);
      SingleSystemCommand sumit("Summary",
				"Summary to Run Test",
				&SimpleSetUp);
      Commands.AddObject("Summary",sumit);
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
 
/*F ans = AlgorithmReadIn(level1)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int AlgorithmReadIn(ReactionSystemBase *level1)
{
  SystemCoreObjectTest *test = (SystemCoreObjectTest *) level1;
  AlgorithmAndInstanceReadIn(test->Inputs,test->getStandard());
  
  return 1;
}

/*F ans = SimpleSetUp(level1)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int SimpleSetUp(ReactionSystemBase *level1)
{
  SystemCoreObjectTest *test = (SystemCoreObjectTest *) level1;
  if(test->Inputs.size() < 3)
    {
      cout << "Input:\n";
      cout << "Filename: GoalRunClass Definition\n";
      cout << "Filename: AlgorithmSummary Definition\n";
      cout << "Filename: Initial set of instances\n";
      
      return 1;
    }
  
  String gfilename = test->Inputs.front();
  test->Inputs.pop_front();
  OpenInputFile gfile(gfilename);

  String filename = test->Inputs.front();
  test->Inputs.pop_front();
  OpenInputFile file(filename);

  String instfilename = test->Inputs.front();
  test->Inputs.pop_front();
  OpenInputFile instfile(instfilename);

  cout << "Read in Instances (and Class, of course)";
  BaseDataSetOfInstances instances;
  DataSetOfInstancesClass instancesclass;
  instancesclass.Read(instfile.Stream,test->getStandard());
  instances.Read(instfile.Stream,&instancesclass,test->getStandard().NameTag);
  instances.print(cout);
  cout.flush();
  
  DataAlgorithmRunClass rclass(0,"Test","A Test Run of an Algorithm");

  cout << "Read in AlgorithmRun Class\n";
  rclass.Read(gfile.Stream,test->getStandard());
  cout << "\n+++++++++++++++++++++++++++++++++++++++\n";
  cout << "The AlgorithmRun Class\n";
  rclass.print(cout);
  cout << "\n=================+++++++++++++++++++++++++++++++++++++++\n";

  BaseDataAlgorithmSummary summary;
  
  cout << "Read in Algorihthm Summary Class\n";
  summary.Read(file.Stream,&rclass,filename);
  cout << "\n+++++++++++++++++++++++++++++++++++++++\n";
  BaseDataAlgorithmRun run;
  run.Instantiate(&summary,&rclass);
  
  cout << "The algorithm:\n";
  run.print(cout);
  cout << "\n";
  cout << "\n+++++++++++++++++++++++++++++++++++++++\n";
  run.Run(&instances,&instancesclass,&rclass);
  cout << "\n";
  
  return 0;
}
