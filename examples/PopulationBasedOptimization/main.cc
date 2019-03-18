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
#include "Optimize.hh"
#include "PopulationBasedOptimization.hh"
#include "ParameterizedFunction.hh"
#include "GeneticOperations.hh"
#include "PredicateObjects.hh"

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
      AddOptimizeClasses(getStandard());
      AddPopulationClasses(getStandard());
      AddGeneticClasses(getStandard());
      AddBaseExpressionTreeClasses(getStandard());

      AddBaseDistributionClasses(getStandard());
      AddLogicalOperationClasses(getStandard());
      AddNumericOperationClasses(getStandard());
      AddParameterizedClasses(getStandard());
      AddPredicateClasses(getStandard());
    }
  virtual void EncodeDecodeObjectsSetUp()
    {
      AlgorithmSystemSave::EncodeDecodeObjectsSetUp();
      InitialInstanceAlgorithmsEncodeDecodeRoutines();
      InitialSetOfOptimizeEncodeDecodeRoutines();
      InitialSetOfPopulationEncodeDecodeRoutines();
      InitialGeneticEncodeDecodeRoutines();
      InitialSetOfExpressionTreeEncodeDecodeRoutines();
      InitialDistributionObjectsEncodeDecodeRoutines();
      InitialSetOfLogicalOperationEncodeDecodeRoutines();
      InitialSetOfNumericOperationEncodeDecodeRoutines();
      InitialParameterizedEncodeDecodeRoutines();
      InitialSetOfPredicateEncodeDecodeRoutines();
    }
  void CommandSetUp()
    {
      AlgorithmSystemSave::CommandSetUp();
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
  SystemCoreObjectTest test(argc,argv);
  
  cout << "Initialze" << endl;
  test.Initialization();
  cout << "Run" << endl;
  test.Run();
  cout << "Exit" << endl;
  return test.Exit();
}
 
