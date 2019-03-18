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

static int TestTree(ReactionSystemBase *level1);

class SystemCoreObjectTest : public InstanceSystemMenu
{
public:
  SystemCoreObjectTest(int argc, char *argv[])
    : InstanceSystemMenu(argc,argv)
    {
    }
  void CommandSetUp()
    {
      InstanceSystemMenu::CommandSetUp();
      SingleSystemCommand test("TreeTest",
			      "Test Tree",
			      &TestTree);
      Commands.AddObject("TestTree",test);
    }
  void EncodeDecodeObjectsSetUp()
    {
      InstanceSystemMenu::EncodeDecodeObjectsSetUp();
      InitialSetOfDirectedTreesEncodeDecodeRoutines();
    }
  void StandardObjectsSetUp()
    {
      InstanceSystemMenu::StandardObjectsSetUp();
      AddDirectedTreeObjects(getStandard());
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
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int TestTree(ReactionSystemBase *level1)
{
  bool ans = true;
  SystemCoreObjectTest *test = (SystemCoreObjectTest *) level1;
  
  BaseDataDirectedTree tree;
  tree.Identification = 1000;
  tree.NameTag = "AnExampleTree";
  
  if(test->Inputs.size() < 1)
    {
      cout << "Needs (Assumes that objects read in previous run):\n";
      cout << "------ Root Node\n";
      cout << "------ (Optional) List of connecting nodes\n";
      
      return 1;
    }
  String var;
  
  String root = test->GetNextInput();
  if(test->Instances.IsInList(root))
    {
      BaseDataObject *obj = test->Instances.GetObject(root);
      tree.AddNode(obj);
      tree.SetRootNode(root);

      cout << "-------------- Tree at the Begining ---------------------\n";
      tree.print(cout);
      cout << "\n";

      while(test->Inputs.size() >0)
	{
	  var = test->GetNextInput();
	  if(test->Instances.IsInList(root))
	    {
	      BaseDataObject *obj = test->Instances.GetObject(var);
	      cout << "Add Node To Tree: ";
	      cout << var;
	      cout << "\n";
	      obj->print(cout);
	      cout << "\n";
      
	      tree.AddNode(obj);
	      tree.AddConnection(root,var);
	      cout << "--------------- After Adding Node ----------------------\n";
	      tree.print(cout);
	      cout << "\n";
	    }
	  else
	    {
	      cerr << "Object: '" << var << "' not found" << endl;
	    }
	}
    }
  else
    {
      cerr << "Root node not found: '" << root << "'" << endl;
    }

  cout << "\n=============== Final Tree ===========================\n";
  tree.print(cout);
  cout << "\n";

  cout << "\n=============== Store Tree in ===========================\n";
  test->Instances.AddObject(&tree);
  
  cout << "\n=============== Sons of Root =====================\n";
  cout << tree.GetSons(root);
  
  cout << "\n===============  GetParent   =====================\n";
  cout << "The parent of ";
  cout << var;
  cout << " is ";
  cout << tree.GetParent(var);
  
  cout << "\n=============== Remove Last Connection =====================\n";
  tree.RemoveConnection(root,var);
  tree.print(cout);
  cout << "\n";
  
  cout << "\n===============    Remove Last Node    =====================\n";
  tree.RemoveNode(var);
  tree.print(cout);
  cout << "\n";
  
  return ans;
}
