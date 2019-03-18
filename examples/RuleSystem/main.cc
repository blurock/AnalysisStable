/*  FILE     main.cc
**  PACKAGE     ANALYSIS
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
#include "Vector.hh"
#include "PrimitiveStats.hh"
#include "MatrixNumeric.hh"
#include "BasicLaTeXTable.hh"
#include "MatrixOut.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "LogicalOperations.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "MenuObjects.hh"
#include "DirectedTreeObjects.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "ExpressionTree.hh"
#include "InstanceAlgorithms.hh"
#include "DistributionAlgorithm.hh"
#include "NumericOperations.hh"
#include "ParameterizedFunction.hh"
#include "PredicateObjects.hh"
#include "RuleSystem.hh"

int TransferAttributes(ReactionSystemBase* sys);

class RuleSystemTest : public AlgorithmSystemSave
{
public:
  RuleSystemTest(int argc, char *argv[])
    : AlgorithmSystemSave(argc,argv)
    {
    }
  virtual void StandardObjectsSetUp()
    {
      AlgorithmSystemSave::StandardObjectsSetUp();
      AddInstanceAlgorithmsClasses(getStandard());
      AddBaseDistributionClasses(getStandard());
      AddBaseExpressionTreeClasses(getStandard());
      AddNumericOperationClasses(getStandard());
      AddParameterizedClasses(getStandard());
      AddLogicalOperationClasses(getStandard());
      AddParameterizedClasses(getStandard());
      AddPredicateClasses(getStandard());
      AddRuleSystemClasses(getStandard());
    }
  virtual void EncodeDecodeObjectsSetUp()
    {
      AlgorithmSystemSave::EncodeDecodeObjectsSetUp();
      InitialInstanceAlgorithmsEncodeDecodeRoutines();
      InitialDistributionObjectsEncodeDecodeRoutines();
      InitialSetOfExpressionTreeEncodeDecodeRoutines();
      InitialSetOfNumericOperationEncodeDecodeRoutines();
      InitialSetOfLogicalOperationEncodeDecodeRoutines();
      InitialParameterizedEncodeDecodeRoutines();
      InitialSetOfPredicateEncodeDecodeRoutines();
      InitialSetOfRuleSystemEncodeDecodeRoutines();
    }
  void CommandSetUp()
    {
      AlgorithmSystemSave::CommandSetUp();
      String trans("TransferAttributes");
      SingleSystemCommand transfer(trans,
				    "Transfer Attributes",
				    &TransferAttributes);
      Commands.AddObject(trans,transfer);
    }
  int Run() {
    String done("END");
    if(Inputs.size() == 0) {
      istream& inputstream = cin;
      String inpline;
      bool notDone = true;
      while(notDone) {
	cout << "Reaction::" << endl;
	cerr << "Reaction::" << endl;
	cout.flush();
	cerr.flush();
	inpline.ReadFullLine(inputstream);
	cout << "Command Line: '" << inpline << "'" << endl;
	cerr << "Command Line: '" << inpline << "'" << endl;
	if(!strncmp(inpline.c_str(), done.c_str(),3))
	  notDone = false;
	else {
	  loadInput(inpline);
	  Commands.ExecuteCommand(0,0,this);
	}
      }
    } else {
      Commands.ExecuteCommand(0,0,this);
    }
    return 1;
  }
  void loadInput(String line) {
    String word;
    while(Inputs.size() > 0) {
      word = GetNextInput();
      cout << "Extra: '" << word << "'" << endl;
    }

    while(!line.IsEmpty()) {
      line.IsolateNextWord(word,' ');
      Inputs.AddObject(word);
    }
  }
};
/*F main(argc,argv)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int main(int argc, char *argv[])
{
  RuleSystemTest test(argc,argv);
  
  cout << "Initialize" << endl;
  test.Initialization();
  cout << "Run" << endl;
  test.Run();
  cout << "Exit" << endl;
  return test.Exit();
}
 
/*F ans = TransferAttributes(system)
**
**  DESCRIPTION
**    system: The system structure
**    ans: Zero if successful
**
**  REMARKS
**
*/
int TransferAttributes(ReactionSystemBase* sys)
{
  InstanceSystem* system = (InstanceSystem *) sys;
  
  int result = SYSTEM_NORMAL_RETURN;
  BaseDataSetOfInstances instances = system->Instances;
  cout << "Number of Inputs: " << system->Inputs.size() << endl;
  while(system->Inputs.size() > 1)
    {
      String source = system->GetNextInput();
      String destination = system->GetNextInput();
      cout << "Transfer: '" << source << "' to  '" << destination << "'" << endl;
      if(system->Instances.IsInList(source))
	{
	  BaseDataObject *obj = system->Instances.GetObject(source);
	  obj->NameTag = destination;
	  system->Instances.AddObject(obj);
	}
      else
	{
	  cerr << "Source Attribute Not found: '" << source << "'" << endl;
	  result = SYSTEM_ERROR_RETURN;
	}
    }
  return result;
}
