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

//SearchableObjectListSimple<String,SingleDecodeRoutine> *SetOfEncodeDecodeRoutines;

/*C CoreObjectTest  . . . . . . . . . . . . . . . . . .  test for CoreObjects
**
**  DESCRIPTION
**     
**  REMARKS
**
*/
class SystemTest : public ReactionSystemLevel1
{
public:
  SystemTest(int argc, char *argv[])
    : ReactionSystemLevel1(argc,argv)
    {
    }
  void Initialization()
    {
      SingleSystemCommand command("Default",&DefaultSystemCommand);
      Commands.AddObject(command.getName(),command);
      SingleSystemCommand clist("CommandList",&PrintCommandList);
      Commands.AddObject(clist.getName(),clist);
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
  SystemTest test(argc,argv);
  cout << test << endl;
  test.Initialization();
  cout << "After Initialization" << endl;
  test.Run();
  
  return 0;
}
