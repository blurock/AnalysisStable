/*  File     main.cc
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
#include "PredicateGen.hh"
#include "PredicateObjects.hh"
#include "RuleSystem.hh"
#include "Optimize.hh"
#include "PopulationBasedOptimization.hh"
#include "ParameterizedFunction.hh"
#include "GeneticOperations.hh"
#include "VectorOperations.hh"
#include "EvaluationTree.hh"
#include "EntropyObjects.hh"
#include "DecisionTreeAlgorithms.hh"
#include "GoalObjects.hh"

extern void InitialEntropyAlgorithmEncodeDecodeRoutines();
//template class list<BasicPair<Identify,Identify> >;
//template class list<BasicPair<String,String> >;
//template class list<BasicPair<double,double> >;

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
      InitialDistributionObjectsEncodeDecodeRoutines();
      InitialSetOfExpressionTreeEncodeDecodeRoutines();
      InitialSetOfNumericOperationEncodeDecodeRoutines();
      InitialSetOfLogicalOperationEncodeDecodeRoutines();
      InitialParameterizedEncodeDecodeRoutines();
      InitialSetOfPredicateEncodeDecodeRoutines();
      InitialSetOfRuleSystemEncodeDecodeRoutines();

      InitialPredicateGenEncodeDecodeRoutines();
      InitialSetOfOptimizeEncodeDecodeRoutines();
      InitialSetOfPopulationEncodeDecodeRoutines();
      //InitialGeneticEncodeDecodeRoutines();
      InitialEntropyAlgorithmEncodeDecodeRoutines();
      DecisionTreeEncodeDecodeRoutines();
    }
  void StandardObjectsSetUp()
    {
      GoalSystemSave::StandardObjectsSetUp();
      AddInstanceAlgorithmsClasses(getStandard());
      AddBaseDistributionClasses(getStandard());
      AddBaseExpressionTreeClasses(getStandard());
      AddNumericOperationClasses(getStandard());
      AddParameterizedClasses(getStandard());
      AddLogicalOperationClasses(getStandard());
      AddParameterizedClasses(getStandard());
      AddPredicateClasses(getStandard());
      AddRuleSystemClasses(getStandard());

      AddPredicateGenAlgorithmClasses(getStandard());
      AddOptimizeClasses(getStandard());
      AddPopulationClasses(getStandard());
      //AddGeneticClasses(getStandard());
      AddEntropyAlgorithmClasses(getStandard());
      AddDecisionTreeClasses(getStandard());
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

  return 0;
  
}
