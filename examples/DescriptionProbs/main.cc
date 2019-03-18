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
#include "PredicateObjects.hh"
#include "DescriptionProbs.hh"
 
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
      AddDescriptionProbsClasses(getStandard());
      AddPredicateClasses(getStandard());
      AddDataObjectClasses(getStandard());
    }
  virtual void EncodeDecodeObjectsSetUp()
    {
      AlgorithmSystemSave::EncodeDecodeObjectsSetUp();
      InitialInstanceAlgorithmsEncodeDecodeRoutines();
      InitialDescriptionProbsEncodeDecodeRoutines();
      InitialSetOfPredicateEncodeDecodeRoutines();
      InitialSetOfDataObjectsEncodeDecodeRoutines();
    }
  void CommandSetUp()
    {     
      AlgorithmSystemSave::CommandSetUp();
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
