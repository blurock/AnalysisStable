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
#include "NumericOperations.hh"
#include "LogicalOperations.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "DirectedTreeObjects.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "PrimitiveStats.hh"
#include "DistributionAlgorithm.hh"
#include "ExpressionTree.hh"
#include "ParameterizedFunction.hh"
#include "PredicateObjects.hh"
#include "VectorOperations.hh"
#include "GraphOperations.hh"
#include "GeneralGraph.hh"
#include "RuleSystem.hh"

static int ExpressionReadIn(ReactionSystemBase *level1);

 
class SystemCoreObjectTest : public AlgorithmSystemSave
{
public:
  SystemCoreObjectTest(int argc, char *argv[])
    : AlgorithmSystemSave(argc,argv)
    {
    }
  void EncodeDecodeObjectsSetUp()
    {
      AlgorithmSystemSave::EncodeDecodeObjectsSetUp();
      InitialSetOfExpressionTreeEncodeDecodeRoutines();
      InitialSetOfNumericOperationEncodeDecodeRoutines();
      InitialSetOfLogicalOperationEncodeDecodeRoutines();
      InitialDistributionObjectsEncodeDecodeRoutines();
      InitialParameterizedEncodeDecodeRoutines();
      InitialSetOfPredicateEncodeDecodeRoutines();
      InitialVectorOperationsEncodeDecodeRoutines();
      InitialGraphOperationEncodeDecodeRoutines();
      InitialSetOfGeneralGraphEncodeDecodeRoutines();
      InitialSetOfRuleSystemEncodeDecodeRoutines();
    }
    void StandardObjectsSetUp()
    {
      AlgorithmSystemSave::StandardObjectsSetUp();
      AddBaseExpressionTreeClasses(getStandard());
      AddLogicalOperationClasses(getStandard());
      AddBaseDistributionClasses(getStandard());
      AddNumericOperationClasses(getStandard());
      AddParameterizedClasses(getStandard());
      AddPredicateClasses(getStandard());
      AddVectorOperationClasses(getStandard());
      AddGraphOperationClasses(getStandard());
      AddGeneralGraphClasses(getStandard());
      AddRuleSystemClasses(getStandard());
    }
    
  void CommandSetUp()
    {     
      AlgorithmSystemSave::CommandSetUp();

      SingleSystemCommand readit("TestRead",
				"Simple Read in Test",
				&ExpressionReadIn);
      Commands.AddObject("TestRead",readit);
    }
};
/*F main(argc,argv) . . . . . . . . . . . . . . . . . . . . . . . . . .  main
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
/*F ans = AlgorithmReadIn(level1)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int ExpressionReadIn(ReactionSystemBase *level1)
{
  SystemCoreObjectTest *test = (SystemCoreObjectTest *) level1;

  if(test->Inputs.size() < 1)
    {
      cout << "Input:\n";
      cout << "Filename: Expression Class\n";
      cout << "Filename: Expression \n";
      
      return 1;
    }

  String algorithmClassS = test->Inputs.front();
  test->Inputs.pop_front();
  String algorithmS = test->Inputs.front();
  test->Inputs.pop_front();

  
  BaseDataExpressionTree tree;
  DataExpressionTreeClass *ctree = (DataExpressionTreeClass *)
    test->InstanceClasses.PointerToAllowedClasses()->GetObjectClass(EXPRESSIONTREE_TREE_NAME);
  
  
  OpenInputFile inclass(algorithmClassS);
  OpenInputFile inexp(algorithmS);

  cout << "-------------------------------------------" << endl;
  cout << "        Read in Tree Class" << endl;
  cout << "-------------------------------------------" << endl;
  ctree->Read(inclass.Stream,*(test->InstanceClasses.PointerToAllowedClasses()));
  cout << endl << "-------------------------------------------" << endl;
  ctree->print(cout);
  DataExpressionTreeClass *ctree1 = (DataExpressionTreeClass *)
    test->InstanceClasses.PointerToAllowedClasses()->GetObjectClass(EXPRESSIONTREE_TREE_NAME);
  cout << endl << "=============================================" << endl;
  ctree1->print(cout);
  cout << endl << "=============================================" << endl;
  
  
  cout << "-------------------------------------------" << endl;
  cout << "        Read in Tree" << endl;
  cout << "-------------------------------------------" << endl;
  tree.Read(inexp.Stream,ctree);
  cout << endl << "-------------------------------------------" << endl;
  tree.print(cout);
  cout << "\n-------------------------------------------" << endl;
  cout << "        Value of Tree" << endl;
  cout << "-------------------------------------------" << endl;
  BaseDataObject *ans = tree.operator()(&(test->Instances),&(test->InstanceClasses));
  cout << "\n-------------------------------------------" << endl;
  ans->print(cout);
  cout << endl;
  
  return 1;
}

