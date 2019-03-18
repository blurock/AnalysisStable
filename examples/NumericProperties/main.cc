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
#include "NumericProperties.hh"
#include "ExpressionTree.hh"
#include "PrimitiveStats.hh"
#include "DistributionAlgorithm.hh"

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
    }
  void EncodeDecodeObjectsSetUp()
    {
      AlgorithmSystemSave::EncodeDecodeObjectsSetUp();
      InitialSetOfDirectedTreesEncodeDecodeRoutines();
      InitialSetOfSelectionTreeEncodeDecodeRoutines();
      InitialSetOfAlgorithmObjectsEncodeDecodeRoutines();
      InitialInstanceAlgorithmsEncodeDecodeRoutines();
      InitialSetOfNumericPropertiesEncodeDecodeRoutines();
      InitialDistributionObjectsEncodeDecodeRoutines();
      InitialSetOfExpressionTreeEncodeDecodeRoutines();
      InitialParameterizedEncodeDecodeRoutines();
    }
  void StandardObjectsSetUp()
    {
      AlgorithmSystemSave::StandardObjectsSetUp();
      AddBaseAlgorithmClasses(getStandard());
      AddSelectionTreeClasses(getStandard());
      AddDirectedTreeObjects(getStandard());
      AddInstanceAlgorithmsClasses(getStandard());
      AddNumericPropertiesClasses(getStandard());
      AddBaseExpressionTreeClasses(getStandard());
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
