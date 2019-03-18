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
#include "FullReaction.hh"

#include <cantera/Cantera.h>
#include "cantera/kernel/converters/CKReader.h"
#include "ChemkinConvert.hh"

class ChemkinConvertTest : public ReactionSystemSave
{
public:
  ChemkinConvertTest(int argc, char *argv[])
    : ReactionSystemSave(argc,argv)
    {
    }
  virtual void StandardObjectsSetUp()
    {
      ReactionSystemSave::StandardObjectsSetUp();

      AddChemkinConvertClasses(getStandard());
      
    }
  virtual void EncodeDecodeObjectsSetUp()
    {
      ReactionSystemSave::EncodeDecodeObjectsSetUp();

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
  ChemkinConvertTest test(argc,argv);
  
  test.Initialization();
  test.Run();
  return test.Exit();
}
