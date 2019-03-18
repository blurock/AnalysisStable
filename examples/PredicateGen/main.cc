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
#include "PredicateGen.hh"
#include "GoalObjects.hh"

#ifdef _unix
static int SimpleCriticalPointsTest(ReactionSystemBase *);

template class list< BasicPair<String,String> >;
template class list<BasicPair<Identify, Identify> >;

template class list<BasicPair<double, double> >;
bool operator==(BasicPair<String, String> const &p1, BasicPair<String, String> const &p2)
{
  return ( (p1.I == p2.I) && (p1.J == p2.J));
}
bool operator<(BasicPair<String, String> const &p1, BasicPair<String, String> const &p2)
{
  return ( (p1.I < p2.I) || (p1.J < p2.J));
}
#endif

/*C CoreObjectTest  . . . . . . . . . . . . . . . . . .  test for CoreObjects
**
**  DESCRIPTION
**     
**  REMARKS
**
*/
class PredicateGenTest : public GoalSystemSave
{
public:
  DataSetOfObjectsClass Standard;

  PredicateGenTest(int argc, char *argv[])
    : GoalSystemSave(argc,argv)
    {
    }
  void EncodeDecodeObjectsSetUp()
    {
      GoalSystemSave::EncodeDecodeObjectsSetUp();

      InitialInstanceAlgorithmsEncodeDecodeRoutines();
      InitialPredicateGenEncodeDecodeRoutines();
    }
  void StandardObjectsSetUp()
    {
      GoalSystemSave::StandardObjectsSetUp();

      AddInstanceAlgorithmsClasses(getStandard());
      AddPredicateGenAlgorithmClasses(Standard);
    }
  
  void CommandSetUp()
    {
      GoalSystemSave::CommandSetUp();
      
      SingleSystemCommand crit("CriticalPoints",
			       "Critical Points Test",
			       &SimpleCriticalPointsTest);
      Commands.AddObject("CriticalPoints",crit);
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
  PredicateGenTest test(argc,argv);
  
  test.Initialization();
  test.Run();
  test.Exit();
}
 
/*F SimplePredicateGenTest()
**
**  DESCRIPTION
**
**  REMARKS
**
*/
int SimpleCriticalPointsTest(ReactionSystemBase *level1)
{
  PredicateGenTest *predtest = (PredicateGenTest *) level1;
  
  if(predtest->Inputs.size() < 1)
    {
      cout << "Needs a filename argument (such at 'Test.txt')\n";
      return 1;
    }
  
  String filename = predtest->Inputs.front();
  OpenInputFile file(filename);

  BaseDataCriticalPoints points;
  DataCriticalPointsClass pointsclass;
  
  cout << "Read in points\n";
  points.Read(file.Stream,&pointsclass);

  cout << "\nThe Result\n";
  points.print(cout);
  cout << endl;
  
  return 0;
}
