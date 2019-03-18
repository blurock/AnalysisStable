/*  FILE     
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
#include "System.hh"
#include "ONames.hh"
#include "CommBuffer.hh"
#include "String.hh"
#include "MixedClasses.hh"
#include "Objects.hh"
#include "Pairs.hh"
#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "DataObjects.hh"

int KeyWordTest(ReactionSystemBase *);

/*C CoreObjectTest  . . . . . . . . . . . . . . . . . .  test for CoreObjects
**
**  DESCRIPTION
**     
**  REMARKS
**
*/
class CoreObjectTest : public ReactionSystemLevel1
{
public:
  CoreObjectTest(int argc, char *argv[])
    : ReactionSystemLevel1(argc,argv)
    {
    }
  void Initialization()
    {     
      String srd("KeyWordTest");
      SingleSystemCommand rd(srd,
			     "Simple KeyWord Test",
			     &KeyWordTest);
      Commands.AddObject(srd,rd);
    }
  int Run()
    {  
      cout << "\n==================================\n";
      return Commands.ExecuteCommand(0,0,this);
    }
  int Exit()
    {
      return 0;
    }
};
 
/*F main(argc,argv) . . . . . . . . . . . . . . . . . . . .  the main program
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int main(int argc, char *argv[])
{
  CoreObjectTest test(argc,argv);
  
  test.Initialization();
  cout << "After test.init" << endl;
  //InitialCoreDataObjectEncodeDecodeRoutines();
  test.Run();
  
  return 0;
}
 
/*F KeyWordTest()
**
**  DESCRIPTION
**    The simpliest of all the ObjectClass tests.  Creates object classes and 
**    puts them into the SetoOfObjectsClass
**
**  REMARKS
**
*/
int KeyWordTest(ReactionSystemBase *level1) {
  CoreObjectTest *kwtest = (CoreObjectTest *) level1;

  BaseDataSetOfObjects olist;
  unsigned int runsize = 1000;
  for(unsigned int i=0;i<runsize;i++)
    {
      String str = Int2String(i);
      BaseDataObject obj;
      obj.NameTag = str;
      olist.AddObject(&obj);
    }
  String test("---------------------------------------");
  unsigned int count = 0;
  while(true) {
    count++;
    if((count % 1000) ==  0) cout << "." << endl;
    String test1 = test;
    ObjectList<String> distnames = olist.ListOfObjectNames();
    BaseDataKeyWords skeys(distnames);
  }

  return 0;
}
