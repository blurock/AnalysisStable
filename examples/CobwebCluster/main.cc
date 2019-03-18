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
#include "PredicateObjects.hh"
#include "PredicateGen.hh"
#include "NumericOperations.hh"
#include "LogicalOperations.hh"

#include "EvaluationTree.hh"
#include "GoalObjects.hh"
#include "DescriptionProbs.hh"
#include "ClusterTree.hh"
#include "CobwebCluster.hh"

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
      InitialSetOfPredicateEncodeDecodeRoutines();
      InitialPredicateGenEncodeDecodeRoutines();
      InitialEvaluationTreeEncodeDecodeRoutines();
      ClusterTreeEncodeDecodeRoutines();
      CobwebClusterEncodeDecodeRoutines();
      InitialDescriptionProbsEncodeDecodeRoutines();
    }
  void StandardObjectsSetUp()
    {
      GoalSystemSave::StandardObjectsSetUp();
      AddInstanceAlgorithmsClasses(getStandard());
      AddPredicateClasses(getStandard());
      AddPredicateGenAlgorithmClasses(getStandard());
      AddEvaluationTreeClasses(getStandard());
      AddClusterTreeClasses(getStandard());
      AddCobwebAlgorithmClasses(getStandard());
      AddDescriptionProbsClasses(getStandard());
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
