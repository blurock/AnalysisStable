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
#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "DataObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "InstanceObjects.hh"
#include "DirectedTreeObjects.hh"
#include "InstanceObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "InstanceAlgorithms.hh"

static int SimpleReadIn(ReactionSystemBase *level1);
static int ExecuteAlgorithm(ReactionSystemBase *level1);

class SystemCoreObjectTest : public AlgorithmSystemSave
{
public:
  SystemCoreObjectTest(int argc, char *argv[])
    : AlgorithmSystemSave(argc,argv)
    {
    }
  void CommandSetUp()
    {
      AlgorithmSystemSave::CommandSetUp();
      SingleSystemCommand readit("InstanceRead",
				"Simple Read in Test",
				&SimpleReadIn);
      Commands.AddObject("InstanceRead",readit);
      SingleSystemCommand alg("RunAlg",
			      "Run Simple Algorithm",
			      &ExecuteAlgorithm);
      Commands.AddObject("RunAlg",alg);
    }
  void EncodeDecodeObjectsSetUp()
    {
      InstanceSystem::EncodeDecodeObjectsSetUp();
      InitialSetOfDirectedTreesEncodeDecodeRoutines();
      InitialSetOfSelectionTreeEncodeDecodeRoutines();
      InitialSetOfAlgorithmObjectsEncodeDecodeRoutines();
      InitialInstanceAlgorithmsEncodeDecodeRoutines();
    }
  void StandardObjectsSetUp()
    {
      InstanceSystem::StandardObjectsSetUp();
      AddBaseAlgorithmClasses(getStandard());
      AddSelectionTreeClasses(getStandard());
      AddDirectedTreeObjects(getStandard());
      AddInstanceAlgorithmsClasses(getStandard());
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
  test.Run();
  test.Exit();
}
 
/*F ans = SimpleReadIn(level1)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int SimpleReadIn(ReactionSystemBase *level1)
{
  SystemCoreObjectTest *test = (SystemCoreObjectTest *) level1;
  return AlgorithmAndInstanceMultipleAlgorithms(test->Inputs,test->getStandard());
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int ExecuteAlgorithm(ReactionSystemBase *level1)
{
  InstanceSystemSave *test = (InstanceSystemSave *) level1;
  int result = SYSTEM_NORMAL_RETURN;
  
  if(test->Inputs.size() < 1)
    {
      cout << "Input:\n";
      cout << "     The name of the algorithm\n";
      exit(1);
    }
  String algS = test->GetNextInput();
  String algR = test->GetNextInput();
  
  if(test->Instances.IsInList(algS))
     {
       BaseDataAlgorithmRun *run = (BaseDataAlgorithmRun *) test->Instances.GetObject(algS);
       unsigned int type = run->GetType();
       cout << "\nAlgorithmRun------------------------------------------------------------------------\n";
       run->print(cout);
       cout << "\nAlgorithmRun------------------------------------------------------------------------\n";
       
       DataAlgorithmRunClass *rclass = (DataAlgorithmRunClass *) test->InstanceClasses.GetObjectClass(type);
       cout << "\nAlgorithmRunClass-------------------------------------------------------------------\n";
       run->print(cout);
       cout << "\nAlgorithmRunClass-------------------------------------------------------------------\n";
       
       ObjectList<String> notfound = run->TransferInputParameters(run,&(test->Instances));
       cout << "\nAlgorithmRun Parameters -----------------------------------------------------------\n";
       run->PrintParameters(cout);
       cout << "\nAlgorithmRun Parameters -----------------------------------------------------------\n";
       cout << "\n------Not found--------------------------------------------------------------------\n";
       notfound.print(cout);
       cout << "\n----- Not found -------------------------------------------------------------------\n";
       cout << "Now To Run: " << algR << endl;
       
       bool res = run->Run(algR,&(test->Instances),&(test->InstanceClasses),rclass);
       cout << "\nFinished Run-----------------------------------------------------------------------\n";
       
       if(!res) 
	 result = SYSTEM_ERROR_RETURN;
     }
  else
    {
      cerr << "Algorithm not found: '" << algS << "'" << endl;
      result = SYSTEM_ERROR_RETURN;
    }
  cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
  test->Instances.print(cout);
  cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
  
  return result;
  
}
