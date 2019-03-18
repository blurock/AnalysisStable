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
#include "GeneralGraph.hh"

static int SimpleGraphTest(ReactionSystemBase *level1);
static int GraphTest(ReactionSystemBase *level1);

class GraphObjectTest : public InstanceSystemSave
{
public:

  GraphObjectTest(int argc, char *argv[])
    : InstanceSystemSave(argc,argv)
    {
    }
  void StandardObjectsSetUp()
    {
      InstanceSystem::StandardObjectsSetUp();
      AddGeneralGraphClasses(getStandard());
    }

  void EncodeDecodeObjectsSetUp()
    {
      InstanceSystem::EncodeDecodeObjectsSetUp();
      InitialSetOfGeneralGraphEncodeDecodeRoutines();
    }
  
  void CommandSetUp()
    {
      InstanceSystemSave::CommandSetUp();
      
      SingleSystemCommand simple("Simple",
				"Simple Graph Test",
				&SimpleGraphTest);
      Commands.AddObject("Simple",simple);
      SingleSystemCommand test("Test",
				"Simple Graph Test",
				&GraphTest);
      Commands.AddObject("Test",test);
    }
};


/*F GraphTest . . . . . . . . . . . . . . graph test
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int GraphTest(ReactionSystemBase *level1)
{
  /*
  BaseDataGraph *test = new BaseDataGraph;
  String resultString;
  bool resultBool;
  float resultFloat;

  resultString = test->addNode("node1");
  cout << "\naddNode(node1) returned: " << resultString << "\n";
  resultString = test->addNode("node2");
  cout << "addNode(node2) returned: " << resultString << "\n";
  resultString = test->addNode("node3");
  cout << "addNode(node3) returned: " << resultString << "\n";
  resultString = test->addNode("node4");
  cout << "addNode(node4) returned: " << resultString << "\n";
  resultString = test->addEdge("edge1", "node1", "node2");
  cout << "addEdge(edge1,node1,node2) returned: " << resultString << "\n";
  resultString = test->addEdge("edge2", "node1", "node3");
  cout << "addEdge(edge2,node1,node3) returned: " << resultString << "\n";
  resultString = test->addEdge("edge3", "node2", "node4");
  cout << "addEdge(edge3,node2,node4) returned: " << resultString << "\n";
  // resultBool = test->delNode("node4");
  // cout << "delEdge(node4) returned: " << resultBool << "\n";
  resultFloat = test->graphDistance("node1", "node4");
  cout << "graphDistance(node1, node4) = " << resultFloat << "\n";
  resultFloat = test->graphDistance("node3", "node4");
  cout << "graphDistance(node3, node4) = " << resultFloat << "\n";
  resultFloat = test->graphDistance("node1", "node2");
  cout << "graphDistance(node1, node2) = " << resultFloat << "\n";
  

  cout << "\nprint() returned:\n";
  test->print(cout);
  */
  cout << "\nCalled Test" << endl;
  return 0;
}

/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int main(int argc, char *argv[])
{
  GraphObjectTest test(argc,argv);
  
  test.Initialization();
  test.Run();
  test.Exit();
}

/*F SimpleGraphTest . . . . . . . . . . . . . .  simple single graph test
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int SimpleGraphTest(ReactionSystemBase *level1)
{
  GraphObjectTest *test2 = (GraphObjectTest *) level1;

  if(test2->Inputs.size() < 0)
    {
      cout << "instances: The file name of a set of instances and data types\n";
      cout << "predicate: The file name with a single predicate\n";
      cout << "ptype:     The predicate type\n";
      
      return 1;
    }

  cout << "\nCalled Test" << endl;

  return 0;
}



