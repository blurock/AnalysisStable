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
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "InstanceAlgorithms.hh"
#include "GoalObjects.hh"

static int SimpleGoalSpec(ReactionSystemBase *level1);
static int SimpleGoalSummary(ReactionSystemBase *level1);
static int SimpleGoalDefs(ReactionSystemBase *level1);

class SystemCoreObjectTest : public GoalSystemSave
{
public:
  SystemCoreObjectTest(int argc, char *argv[])
    : GoalSystemSave(argc,argv)
    {
    }
  void EncodeDecodeObjectsSetUp()
    {
      GoalSystemSave::EncodeDecodeObjectsSetUp();
      InitialInstanceAlgorithmsEncodeDecodeRoutines();
    }
  void StandardObjectsSetUp()
    {
      GoalSystemSave::StandardObjectsSetUp();
      AddInstanceAlgorithmsClasses(getStandard());
    }
  
  void CommandSetUp()
    {
      GoalSystemSave::CommandSetUp();
      
      SingleSystemCommand goalspec("GoalSpec",
				"Simple GoalSpec Test",
				&SimpleGoalSpec);
      Commands.AddObject("GoalSpec",goalspec);

      SingleSystemCommand goalsummary("GoalSummary",
				"Simple GoalSummary Test",
				&SimpleGoalSummary);
      Commands.AddObject("GoalSummary",goalsummary);

      SingleSystemCommand goaldefs("GoalDefs",
				"Simple GoalDefs Test",
				&SimpleGoalDefs);
      Commands.AddObject("GoalDefs",goaldefs);

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
 
/*F ans = SimpleGoalSpec(level1)  . . . . . . . . . . .  simple GoalSpec test
**
**  DESCRIPTION
**    This reads in three goal specs from one file and checks for equality of the
**    first against the second and third
**
**  REMARKS
**
*/
static int SimpleGoalSpec(ReactionSystemBase *level1)
{
  /*  
  SystemCoreObjectTest *test = (SystemCoreObjectTest *) level1;
  if(test->Inputs.size() < 1)
    {
      cout << "Input:\n";
      cout << "Filename: Three GoalSpec Definitions\n";
      
      return 1;
    }
  
  DataGoalSpecClass sclass(0,"Test","A GoalSpec Test");

  String filename = test->Inputs.front();
  test->Inputs.pop_front();
  OpenInputFile file(filename);
  
  cout << "Read in Three GoalSpec instances\n";
  BaseDataGoalSpec gspec1,gspec2,gspec3;
  gspec1.Read(file.Stream,&sclass);
  gspec1.print(cout);
  cout << "\n";
  gspec2.Read(file.Stream,&sclass);
  gspec2.print(cout);
  cout << "\n";
  gspec3.Read(file.Stream,&sclass);
  gspec3.print(cout);
  cout << "\n";
  cout.flush();

  cout << "Compare GoalSpec1 and GoalSpec2\n";
  if(gspec1.operator==(gspec2))
    cout << "Equal\n";
  else
    cout << "Not Equal\n";
  
  cout << "Compare GoalSpec1 and GoalSpec3\n";
  if(gspec1.operator==(gspec3))
    cout << "Equal\n";
  else
    cout << "Not Equal\n";
  
  BaseDataGoalSpec gspec4(gspec1);
  cout << "Copy of GoalSpec1\n";
  gspec4.print(cout);
  cout << "\n";
  */
  return 0;
}
/*F ans = SimpleGoalSummary(level1)  . . . . . . . . . . .  simple GoalSpec test
**
**  DESCRIPTION
**    This reads in three goal specs from one file and checks for equality of the
**    first against the second and third
**
**  REMARKS
**
*/
static int SimpleGoalSummary(ReactionSystemBase *level1)
{
  SystemCoreObjectTest *test = (SystemCoreObjectTest *) level1;
  
  if(test->Inputs.size() < 1)
    {
      cout << "Input:\n";
      cout << "Filename:  GoalSummary Definition\n";
      
      return 1;
    }
  
  DataGoalSummaryClass sclass(0,"Test","A GoalSummary Test");

  String filename = test->Inputs.front();
  test->Inputs.pop_front();
  OpenInputFile file(filename);
  
  cout << "Read in GoalSummary instance\n";
  BaseDataGoalSummary gspec1;
  gspec1.Read(file.Stream,&sclass);
  gspec1.print(cout);
  cout << "\n";
  return 0;
}
/*F ans = SimpleGoalDefs(level1)  . . . . . . . . . . .  simple GoalSpec test
**
**  DESCRIPTION
**    This reads in three goal specs from one file and checks for equality of the
**    first against the second and third
**
**  REMARKS
**
*/
static int SimpleGoalDefs(ReactionSystemBase *level1)
{
  SystemCoreObjectTest *test = (SystemCoreObjectTest *) level1;
  
  if(test->Inputs.size() < 1)
    {
      cout << "Input:\n";
      cout << "Filename:  SetOfGoalDefs Definition\n";
      cout << "Filename:  GoalSpec Specification\n";
      
      return 1;
    }
  
  DataGoalSummaryClass sclass(0,"Test","A GoalSummary Test");
  DataSetOfGoalDefsClass dclass(0,"Test","A GoalSummary Test");
  dclass.GoalSummaryClass = sclass;
  
  String filename = test->Inputs.front();
  test->Inputs.pop_front();
  OpenInputFile file(filename);
  
  String gfilename = test->Inputs.front();
  test->Inputs.pop_front();
  OpenInputFile gfile(gfilename);
  
  cout << "Read in SetOfGoalDefs instance\n";
  BaseDataSetOfGoalDefs gdefs;
  gdefs.Read(file.Stream,&dclass);
  gdefs.print(cout);
  cout << "\n";
  
  cout << "-------- Get Summary ------------------\n";
  BaseDataGoalSpec goalspec;
  goalspec.Read(gfile.Stream,&(sclass.GoalSpecClass));
  
  BaseDataGoalSummary summary = gdefs.GetGoalSummary(goalspec);
  summary.print(cout);

  cout << "-------- Get Prerequisites ------------\n";
  ObjectList<BaseDataGoalSpec> prereqs;
  ObjectList<BaseDataGoalSpec> specs;
  specs.AddObject(goalspec);

  gdefs.GetPrerequisiteListReverse(specs,prereqs);
  prereqs.print(cout);
  cout << "\n";

  return 0;
}
