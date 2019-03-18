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

static int SimpleReadIn(ReactionSystemBase *level1);
 
class SystemCoreObjectTest : public InstanceSystemSave
{
public:
  SystemCoreObjectTest(int argc, char *argv[])
    : InstanceSystemSave(argc,argv)
    {
    }
  void CommandSetUp()
    {     
      InstanceSystemSave::CommandSetUp();

      SingleSystemCommand readit("Test",
				"Simple Selection Tree Test",
				&SimpleReadIn);
      Commands.AddObject("Test",readit);
    }
  void EncodeDecodeObjectsSetUp()
    {
      InstanceSystem::EncodeDecodeObjectsSetUp();
      InitialSetOfDirectedTreesEncodeDecodeRoutines();
      InitialSetOfSelectionTreeEncodeDecodeRoutines();
    }
  void StandardObjectsSetUp()
    {
      InstanceSystem::StandardObjectsSetUp();
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
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int SimpleReadIn(ReactionSystemBase *level1)
{
  SystemCoreObjectTest *test = (SystemCoreObjectTest *) level1;
  
  if(test->Inputs.size() < 2)
    {
      cout << "Input:\n";
      cout << "A filename argument\n";
      cout << "A Category Name (start point)\n";
      cout << "A Full Node Name\n";
      cout << "For Example: Test.inp Initial#Numbers Initial#Numbers#IntegerChoice#Two\n";
      
      return 1;
    }
  
  DataSelectionTreeClass tclass;
  String filename = test->Inputs.front();
  test->Inputs.pop_front();
  
  OpenInputFile file(filename);
  BaseDataSelectionTree tree;
  
  tree.Read(file.Stream,&tclass,filename);
  
  tree.print(cout);
  cout << "\n";
  String node = test->Inputs.front();
  test->Inputs.pop_front();
  ObjectList<String> sel = tree.GetChoices(node);
  cout << "The Selected Nodes\n";
  sel.print(cout);
  cout << "\n";

  cout << "The selection to be made from input\n";
  BaseDataObject *selection = tree.GetNextSelection(file.Stream,node);
  selection->print(cout);
  cout << "\n";
  BaseDataSelections selections = tree.GetSelections(file.Stream,sel);
  cout << "Actual Read in Selections\n";
  selections.print(cout);
  cout << "\n";
  
  cout << "Selection made from full category name\n";
  String category = test->Inputs.front();
  test->Inputs.pop_front();
  cout << category;
  cout << "\n";
  BaseDataObject *selname = tree.GetSelection(category);
  selname->print(cout);
  cout << "\n----------------------------------\n";
  return 0;
}





