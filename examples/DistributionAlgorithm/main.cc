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
#include "Vector.hh"
#include "MatrixNumeric.hh"
#include "PrimitiveStats.hh"
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
#include "InstanceAlgorithms.hh"
#include "ExpressionTree.hh"
#include "DistributionAlgorithm.hh"

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
      InitialInstanceAlgorithmsEncodeDecodeRoutines();
      InitialDistributionObjectsEncodeDecodeRoutines();
      InitialParameterizedEncodeDecodeRoutines();
    }
    void StandardObjectsSetUp()
    {
      AlgorithmSystemSave::StandardObjectsSetUp();
      AddBaseExpressionTreeClasses(getStandard());
      AddLogicalOperationClasses(getStandard());
      AddNumericOperationClasses(getStandard());
      AddInstanceAlgorithmsClasses(getStandard());
      AddBaseDistributionClasses(getStandard());
      AddParameterizedClasses(getStandard());
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
