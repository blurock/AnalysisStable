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

static int SimpleReadIn(ReactionSystemBase *level1);
static int SimpleEncodeDecode(ReactionSystemBase *level1);
 
class SystemCoreObjectTest : public ReactionSystemLevel1
{
public:
  DataSetOfObjectsClass Standard;


  SystemCoreObjectTest(int argc, char *argv[])
    : ReactionSystemLevel1(argc,argv)
    {
    }
  void Initialization()
    {     
      InitialSetOfNumericEncodeDecodeRoutines();
      InitialSetOfLogicalEncodeDecodeRoutines();
      InitialSetOfOperationEncodeDecodeRoutines();
      InitialSetOfODRealEncodeDecodeRoutines();
      
      AddNumericClasses(Standard);
      AddLogicalClasses(Standard);
      AddFunctionClasses(Standard);
      AddOperationClasses(Standard);

      SingleSystemCommand readit("Read",
				"Simple Read in Test",
				&SimpleReadIn);
      Commands.AddObject("Read",readit);
      SingleSystemCommand enc("Encode",
				"Simple Encode Decode Test",
				&SimpleEncodeDecode);
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
  BaseDataSetOfObjects& ReadInData(const String& filename);
  void EncodeIt(String& filename, CommBuffer& buf);
  int DecodeIt(CommBuffer& buf);
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
  
  if(test->Inputs.size() < 1)
    {
      cout << "Needs a filename argument\n";
      return 1;
    }
  

  String filename = test->Inputs.front();
  BaseDataSetOfObjects set = (*test).ReadInData(filename);
  set.print(cout);
  cout << "\n";
  

  return 0;
}

 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int SimpleEncodeDecode(ReactionSystemBase *level1)
{
  SystemCoreObjectTest *test = (SystemCoreObjectTest *) level1;
  
  if(test->Inputs.size() < 1)
    {
      cout << "Needs a filename argument\n";
      return 1;
    }
  String filename = test->Inputs.front();

  cout << "\n==========================================================\n";
  cout << "Encode\n";
  
  CommBuffer buf(COMM_BUFF_ENCODE,200000,2000);
  (*test).EncodeIt(filename,buf);
  

  cout << "\n==========================================================\n";
  cout << "Decode\n";

  int ans =  (*test).DecodeIt(buf);
  
  return ans;
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSetOfObjects& SystemCoreObjectTest::ReadInData(const String& filename)
{
  OpenInputFile file(filename);
  
  cout << "-------------------------------------------------\n";
  DataSetOfObjectsClass setclass;
  BaseDataSetOfObjects *set = new BaseDataSetOfObjects;

  setclass.SetDebugLevel(5);
  
  bool result = setclass.Read(file.Stream,Standard);
  cout << "\n -------------  Print  Classes -----------------\n";
  setclass.print(cout);
  cout << "\n ------------- As Line  Classes -----------------\n";
  setclass.WriteAsLine(cout);
  cout << "\n ------------- As Latex Classes -----------------\n";
  setclass.WriteAsLatex(cout);
  cout << "\n ------------- As ASCII Classes -----------------\n";
  setclass.WriteAsASCII(cout);
  cout << "\n -------------   Done   Classes -----------------\n";

  if(result)
    {
      setclass.print(cout);
  
      if(result)
	{
	  cout << "------------ Read In Data -----------------------\n";
	  (*set).Read(file.Stream,&setclass,Standard.NameTag);
  cout << "\n -------------  Print  -----------------\n";
  set->print(cout);
  cout << "\n ------------- As Line  -----------------\n";
  set->WriteAsLine(cout,&setclass);
  cout << "\n ------------- As Latex -----------------\n";
  set->WriteAsLatex(cout,&setclass);
  cout << "\n ------------- As ASCII -----------------\n";
  set->WriteAsASCII(cout,&setclass);
  cout << "\n -------------   Done   -----------------\n";
	}
      else
	{
	  cout << "Read in was unsuccessful\n";
	}
    }
  else
    {
      cerr << "Error in reading classes" << endl;
    }
  
  return *set;
}

  
/*F EncodeIt
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void SystemCoreObjectTest::EncodeIt(String& filename, CommBuffer& buf)
{
  BaseDataSetOfObjects set = ReadInData(filename);
  set.print(cout);
  cout << "\n";
  
  
  CommBuffer buf1(COMM_BUFF_ENCODE,20000,2000);
  Identify iden(1,"One");
  iden.EncodeThis(buf1);
  CommBuffer buf2(buf1.GetBuffer(),
		      buf1.GetBufferSize());
  Identify iden2;
  iden2.DecodeThis(buf2);
  cout << "Identify\n";
  cout << iden2;
  cout << "\n-----------------\n";
  
  set.EncodeThis(buf);
}

/*F DecodeIt
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int SystemCoreObjectTest::DecodeIt(CommBuffer& buf)
{
  
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
  cout << "\n";
  return ans;
  
}
