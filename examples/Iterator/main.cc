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
#include "LogicalOperations.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "Iterator.hh"

class IteratorTest : public InstanceSystemSave
{
public:
  IteratorTest(int argc, char *argv[])
    : InstanceSystemSave(argc,argv)
    {
    }

  virtual void Initialization() {

      InitialIteratorEncodeDecodeRoutines();
      AddIteratorClasses(getStandard());
    InstanceSystemSave::Initialization();
    }
  virtual int Run() {
    String done("END");
    if(Inputs.size() == 0) {
      istream& inputstream = cin;
      String inpline;
      bool notDone = true;
      while(notDone) {
	cout << "Reaction::" << endl;
	cerr << "Reaction::" << endl;
	cout.flush();
	cerr.flush();
	inpline.ReadFullLine(inputstream);
	cout << "Command Line: '" << inpline << "'" << endl;
	cerr << "Command Line: '" << inpline << "'" << endl;
	if(!strncmp(inpline.c_str(), done.c_str(),3))
	  notDone = false;
	else {
	  loadInput(inpline);
	  Commands.ExecuteCommand(0,0,this);
	}
      }
    } else {
      Commands.ExecuteCommand(0,0,this);
    }
    return 1;
  }
  void loadInput(String line) {
    String word;
    while(Inputs.size() > 0) {
      word = GetNextInput();
      cout << "Extra: '" << word << "'" << endl;
    }

    while(!line.IsEmpty()) {
      line.IsolateNextWord(word,' ');
      Inputs.AddObject(word);
    }
}


};

int main(int argc, char *argv[])
{
  IteratorTest test(argc,argv);
  
  test.Initialization();
  test.Run();
  test.Exit();
}
