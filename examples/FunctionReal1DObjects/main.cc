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

static int SimpleLogical(ReactionSystemBase *level1);
static int SimpleLogicalEncodeDecode(ReactionSystemBase *level1);
 
class SystemObjectTest : public ReactionSystemLevel1
{
public:
  BaseDataSetOfObjects *Set;
  DataSetOfObjectsClass Stand;
  
  SystemObjectTest(int argc, char *argv[])
    : ReactionSystemLevel1(argc,argv)
    {
    }
  void Initialization()
    {     
      AddNumericClasses(Stand);
      AddLogicalClasses(Stand);
      AddFunctionClasses(Stand);

      InitialSetOfNumericEncodeDecodeRoutines();
      InitialSetOfLogicalEncodeDecodeRoutines();
      InitialSetOfODRealEncodeDecodeRoutines();
      
      SingleSystemCommand setup("Simple",
				"Simple LogicalObjectClass Test",
				&SimpleLogical);
      Commands.AddObject("Simple",setup);
      SingleSystemCommand enc("Encode",
				"Simple Encode Decode Test",
				&SimpleLogicalEncodeDecode);
      Commands.AddObject("Encode",enc);
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
  void ReadInData(const String& filename);
  
};

/*F ReadInData(const String& filename)  . . . . . . . . . .  SystemObjectTest
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void SystemObjectTest::ReadInData(const String& filename)
{
  OpenInputFile file(filename);
  
  cout << "-------------------------------------------------\n";
  DataSetOfObjectsClass setclass;
  
  bool result = setclass.Read(file.Stream,Stand);
  setclass.print(cout);
  cout << "\n -------------  Print  Classes -----------------\n";
  setclass.print(cout);
  cout << "\n ------------- As Line  Classes -----------------\n";
  setclass.WriteAsLine(cout);
  cout << "\n ------------- As Latex Classes -----------------\n";
  setclass.WriteAsLatex(cout);
  cout << "\n ------------- As ASCII Classes -----------------\n";
  setclass.WriteAsASCII(cout);
  cout << "\n -------------   Done   Classes -----------------\n";

  
  Set = new BaseDataSetOfObjects;
  if(result)
    {
      cout << "------------ Read In Data -----------------------\n";
      (*Set).Read(file.Stream,&setclass,Stand.NameTag);
  cout << "\n -------------  Print  -----------------\n";
  Set->print(cout);
  cout << "\n ------------- As Line  -----------------\n";
  Set->WriteAsLine(cout,&setclass);
  cout << "\n ------------- As Latex -----------------\n";
  Set->WriteAsLatex(cout,&setclass);
  cout << "\n ------------- As ASCII -----------------\n";
  Set->WriteAsASCII(cout,&setclass);
  cout << "\n -------------   Done   -----------------\n";
    }
  else
    {
      cout << "Read in was unsuccessful\n";
    }
}

int main(int argc, char *argv[])
{
  SystemObjectTest test(argc,argv);
  
  test.Initialization();
  test.Run();
}

static int SimpleLogical(ReactionSystemBase *level1)
{
  SystemObjectTest *test = (SystemObjectTest *) level1;
  
  if(test->Inputs.size() < 1)
    {
      cout << "Needs a filename argument\n";
      return 1;
    }
  

  String filename = test->Inputs.front();
  (*test).ReadInData(filename);
  (*test).Set->print(cout);

  return 0;
}

static int SimpleLogicalEncodeDecode(ReactionSystemBase *level1)
{
  SystemObjectTest *test = (SystemObjectTest *) level1;
  
  if(test->Inputs.size() < 1)
    {
      cout << "Needs a filename argument\n";
      return 1;
    }
  String filename = test->Inputs.front();

  (*test).ReadInData(filename);
  (*test).Set->print(cout);
  
  CommBuffer buf(COMM_BUFF_ENCODE,200000,2000);
  test->Set->EncodeThis(buf);
  CommBuffer inbuffer(buf.GetBuffer(),
		      buf.GetBufferSize());
  BaseDataSetOfObjects newset;
  bool result = newset.DecodeThis(inbuffer);
  
  int ans = 0;
  
  if(!result)
    {
      cout << "Decode Failed\n";
      ans = 1;
    }

  cout << newset;

  return ans;
}
 

  
