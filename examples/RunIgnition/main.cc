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
using namespace std;
#define TEMPLATE_INSTANTIATION

#include <cantera/Cantera.h>
#include "cantera/kernel/converters/CKReader.h"
#include <cantera/IdealGasMix.h>

#include "FullReaction.hh"
#include "Iterator.hh"
#include "ChemkinConvert.hh"
#include "RunIgnition.hh"


class RunIgnitionTest : public MechanismSystemBase
{
public:
  RunIgnitionTest(int argc, char *argv[])
    : MechanismSystemBase(argc,argv)
    {
    }
  virtual void StandardObjectsSetUp()
    {
      MechanismSystemBase::StandardObjectsSetUp();

      AddRunIgnitionClasses(getStandard());
      AddIteratorClasses(getStandard());
       AddChemkinConvertClasses(getStandard());
    }
  virtual void EncodeDecodeObjectsSetUp()
    {
      MechanismSystemBase::EncodeDecodeObjectsSetUp();

      InitialRunIgnitionDecodeFunctions();
      InitialIteratorEncodeDecodeRoutines();
      InitialChemkinConvertDecodeFunctions();
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
  RunIgnitionTest test(argc,argv);
  
  test.Initialization();
  test.Run();
  return test.Exit();
}
