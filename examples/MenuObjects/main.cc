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

int SimpleMenuTest(ReactionSystemBase *sys);
int SimpleClassTest(ReactionSystemBase *sys);
int SimpleTextTest(ReactionSystemBase *sys);
int WindowClassPrint(ReactionSystemBase *sys);
int WindowInstAttrPrint(ReactionSystemBase *sys);
int WindowClassHierarchy(ReactionSystemBase *sys);
int MenuObjectTest(ReactionSystemBase *sys);

class InstanceSystemMenuTest : public InstanceSystemMenu
{
public:
  InstanceSystemMenuTest(int argc, char *argv[])
    : InstanceSystemMenu(argc,argv)
    {
	cout << "constructor" << endl;
    }
  void EncodeDecodeObjectsSetUp()
    {
      InstanceSystemSave::EncodeDecodeObjectsSetUp();
    }
  void StandardObjectsSetUp()
    {
      InstanceSystemSave::StandardObjectsSetUp();
    }
  
  void CommandSetUp()
    {
	InstanceSystemMenu::CommandSetUp();

	SingleSystemCommand txt("WindowText",
				"Text Test",
				&SimpleTextTest);
	Commands.AddObject("WindowText",txt);
	
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
  cout << "main -1" << endl;
  InstanceSystemMenuTest test(argc,argv);
  
  cout << "main 0" << endl;
  test.Initialization();
  cout << "main 1" << endl;
  test.Run();
  cout << "main 1" << endl;
  test.Exit();
  cout << "main 1" << endl;
}
/*F ans = SimpleTextTest(sys)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int SimpleTextTest(ReactionSystemBase *sys)
{
  int ans = SYSTEM_NORMAL_RETURN;
  
  BaseDataMenuWindow window;
  DataMenuWindowClass windowclass;
  BaseDataMenuText txt;
  String line1("The cat in the hat\n");
  String line2("The dog in the hat\n");
  String line3("The cat in the barrel\n");
  String line4("The mouse in the bucket\n");
  String text;
  text.AppendToEnd(line1);
  text.AppendToEnd(line2);
  text.AppendToEnd(line3);
  text.AppendToEnd(line4);
  txt.setText(text);

  window.setMenuObject(&txt);

  window.Write(cout,&windowclass);

  return ans;
}

  
  
