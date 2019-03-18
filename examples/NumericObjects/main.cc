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

static int SimpleNumeric(ReactionSystemBase *level1);
static int SimpleNumericEncodeDecode(ReactionSystemBase *level1);
static BaseDataSetOfObjects& ReadInData(const String& filename);
static void EncodeIt(String& filename, CommBuffer& buf);
static int DecodeIt(CommBuffer& buf);
 
class NumericObjectTest : public ReactionSystemLevel1
{
public:
  NumericObjectTest(int argc, char *argv[])
    : ReactionSystemLevel1(argc,argv)
    {
    }
  void Initialization()
    {     
      InitialSetOfNumericEncodeDecodeRoutines();
      
      SingleSystemCommand setup("Simple",
				"Simple NumericObjectClass Test",
				&SimpleNumeric);
      Commands.AddObject("Simple",setup);
      SingleSystemCommand enc("Encode",
				"Simple Encode Decode Test",
				&SimpleNumericEncodeDecode);
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
};

int main(int argc, char *argv[])
{
  NumericObjectTest test(argc,argv);
  
  test.Initialization();
  test.Run();
}

static int SimpleNumeric(ReactionSystemBase *level1)
{
  NumericObjectTest *test = (NumericObjectTest *) level1;
  
  if(test->Inputs.size() < 1)
    {
      cout << "Needs a filename argument\n";
      return 1;
    }
  

  String filename = test->Inputs.front();
  BaseDataSetOfObjects set = ReadInData(filename);
  cout << "\n -------------  Print  -----------------\n";
  set.print(cout);
  cout << "\n -------------   Done   -----------------\n";
  
  return 0;
}

static int SimpleNumericEncodeDecode(ReactionSystemBase *level1)
{
  NumericObjectTest *test = (NumericObjectTest *) level1;
  
  if(test->Inputs.size() < 1)
    {
      cout << "Needs a filename argument\n";
      return 1;
    }
  String filename = test->Inputs.front();
  CommBuffer buf(COMM_BUFF_ENCODE,200000,2000);

  EncodeIt(filename,buf);
  int ans = DecodeIt(buf);
  return ans;
}
 
/*F EncodeIt
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static void EncodeIt(String& filename, CommBuffer& buf)
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
static int DecodeIt(CommBuffer& buf)
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

  
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static BaseDataSetOfObjects& ReadInData(const String& filename)
{
  OpenInputFile file(filename);
  DataSetOfObjectsClass setclass;

  DataSetOfObjectsClass stand;
  AddNumericClasses(stand);
  cout << "-------------------------------------------------\n";
  bool result = setclass.Read(file.Stream,stand);

  cout << "\n -------------  Print  Classes -----------------\n";
  setclass.print(cout);
  cout << "\n ------------- As Line  Classes -----------------\n";
  setclass.WriteAsLine(cout);
  cout << "\n ------------- As Latex Classes -----------------\n";
  setclass.WriteAsLatex(cout);
  cout << "\n ------------- As ASCII Classes -----------------\n";
  setclass.WriteAsASCII(cout);
  cout << "\n -------------   Done   Classes -----------------\n";

  BaseDataSetOfObjects *set = new BaseDataSetOfObjects;

  if(result)
    {
      cout << "------------ Read In Data -----------------------\n";
      (*set).Read(file.Stream,&setclass,set->NameTag);
    }
  else
    {
      cout << "Read in was unsuccessful\n";
    }

  cout << "\n -------------  Print  -----------------\n";
  set->print(cout);
  cout << "\n ------------- As Line  -----------------\n";
  set->WriteAsLine(cout,&setclass);
  cout << "\n ------------- As Latex -----------------\n";
  set->WriteAsLatex(cout,&setclass);
  cout << "\n ------------- As ASCII -----------------\n";
  set->WriteAsASCII(cout,&setclass);
  cout << "\n -------------   Done   -----------------\n";

  return *set;
}

  
