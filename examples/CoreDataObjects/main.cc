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
#include <strstream>

static int SimpleDataObjectClassTest(ReactionSystemBase *level1);
static int SimpleInputDataObjectClassTest(ReactionSystemBase *level1);
static int GenericObjectSet(ReactionSystemBase *level1);
static int SimpleReadStreamTest(ReactionSystemBase *level1);
static int RemoveTest(ReactionSystemBase *level1);
static int MemoryTest(ReactionSystemBase *level1);
extern SearchableObjectListSimple<String,SingleDecodeRoutine> *SetOfEncodeDecodeRoutines;

/*C CoreObjectTest  . . . . . . . . . . . . . . . . . .  test for CoreObjects
**
**  DESCRIPTION
**     
**  REMARKS
**
*/
class CoreObjectTest : public ReactionSystemLevel1
{
public:
  CoreObjectTest(int argc, char *argv[])
    : ReactionSystemLevel1(argc,argv)
    {
    }
  void Initialization()
    {     
      String srd("Read");
      SingleSystemCommand rd(srd,
				"Simple Read Stream Test",
				&SimpleReadStreamTest);
      Commands.AddObject(srd,rd);
      String ssetup("DataObjectClass");
      SingleSystemCommand setup(ssetup,
				"Simple DataObjectClass Test",
				&SimpleDataObjectClassTest);
      Commands.AddObject(ssetup,setup);
      String scinput("InputClassTest");
      SingleSystemCommand cinput(scinput,
				"Simple Input of a set of DataObjectClass's Test",
				&SimpleInputDataObjectClassTest);
      Commands.AddObject(scinput,cinput);
      String sgeneric("GenericDefTest");
      SingleSystemCommand generic(sgeneric,
				"Input of a Generic Set Definition",
				&GenericObjectSet);
      Commands.AddObject(sgeneric,generic);
      String srm("Remove");
      SingleSystemCommand rm(srm,
				"Remove BaseDataSetOfObjects Elements Test",
				&RemoveTest);
      Commands.AddObject(srm,rm);
      String smemtest("Memory");
      SingleSystemCommand memtest(smemtest,
				"BaseDataSetOfObjects Memory alloc Test",
				&MemoryTest);
      Commands.AddObject(smemtest,memtest);
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
  CoreObjectTest test(argc,argv);
  
  test.Initialization();
cout << "After test.init" << endl;
 InitialCoreDataObjectEncodeDecodeRoutines();
  test.Run();
  
  return 0;
}
 
/*F SimpleDataObjectClassTest()
**
**  DESCRIPTION
**    The simpliest of all the ObjectClass tests.  Creates object classes and 
**    puts them into the SetoOfObjectsClass
**
**  REMARKS
**
*/
int SimpleDataObjectClassTest(ReactionSystemBase *)
{
  DataObjectClass objc1(100,"Type1","Test type 1");
  DataObjectClass objc2(200,"Type2","Test type 2");
  
  cout << "Object class (100,type1)\n";
  cout << objc1;
  cout << "Object class (200,type2)\n";
  cout << objc2;
  
  DataSetOfObjectsClass set;
  cout << "--------------------------------\n";
  cout << "Empty\n";
  set.print(cout);
  cout << "--------------------------------\n";

  set.SetUpStandardPrintModes();
  cout << "--------------------------------\n";
  cout << "With Standard PrintModes\n";
  set.print(cout);
  cout << "--------------------------------\n";

  set.AddObjectClass(objc1);
  set.AddObjectClass(objc2);
  
  cout << "--------------------------------\n";
  cout << "With the two types added\n";
  set.print(cout);
  cout << "--------------------------------\n";

  cout << "Retrieve type1 by name\n";
  DataObjectClass *cp1 = set.GetObjectClass("Type1");
  cout << *cp1;
  cout << "Retrieve type2 by id\n";
  DataObjectClass *cp2 = set.GetObjectClass(200);
  cout << *cp2;

  return 0;
}
 
/*F SimpleReadStreamTest(level1)
**
**  DESCRIPTION
**    Read in from a filename (an input parameter) a stream of strings.
**    This is also a test of the use of comments
**
      The standard input file is 'Test.txt'
**  REMARKS
**
*/ 
int SimpleReadStreamTest(ReactionSystemBase *level1)
{
  CoreObjectTest *test = (CoreObjectTest *) level1;
  
  if(test->Inputs.size() < 1)
    {
      cout << "Needs a filename argument (such at 'Test.txt')\n";
      return 1;
    }
  
  String filename = test->Inputs.front();
  cout << "Opening Input File: '" << filename << "'" << endl;

  OpenInputFile file(filename);

  cout << "Defining ObjectInput" << endl;

  StreamObjectInput itest(file.Stream,' ');
  
  cout << "Reading First Argument" << endl;

  String name1 = itest.ReadNext();
  cout << "First: '" << name1 << "'\n";
  
  String name2 = itest.ReadNext();
  cout << "First: '" << name2 << "'\n";
  
  String name3 = itest.ReadNext();
  cout << "First: '" << name3 << "'\n";
  
  return 1;
}
 
/*F SimpleInputDataObjectClassTest(level1)
**
**  DESCRIPTION
**    This sets up an object class and reads in some more classes
**
**  REMARKS
**
*/
int SimpleInputDataObjectClassTest(ReactionSystemBase *level1)
{
  CoreObjectTest *test = (CoreObjectTest *) level1;
  
  if(test->Inputs.size() < 1)
    {
      cout << "Needs a filename argument (such as 'TestClass.txt')\n";
      return 1;
    }
  
  String filename = test->Inputs.front();
  OpenInputFile file(filename);

  DataSetOfObjectsClass set;
  DataObjectClass simple(100,"BaseType","The basis object class type");
  set.AddObjectClass(simple);
  
  cout << "------------------------\n";
  cout << "Before Read\n";
  set.print(cout);
  cout << "------------------------\n";

  set.Read(file.Stream,set);
  cout << "------------------------\n";

  cout << "After Read\n";
  set.print(cout);
  cout << "------------------------\n";
  
  return 1;
}
 
/*F GenericObjectSet(level1)
**
**  DESCRIPTION
**    This reads in a set of classes and a set of objects (based on the class description)
**    
**  REMARKS
**
*/
static int GenericObjectSet(ReactionSystemBase *level1)
{
  CoreObjectTest *test = (CoreObjectTest *) level1;
  
  if(test->Inputs.size() < 1)
    {
      cout << "Needs a filename argument (such as 'GenericDef.txt')\n";
      return 1;
    }
  

  String filename = test->Inputs.front();
  OpenInputFile file(filename);

  DataSetOfObjectsClass setclass;
  DataObjectClass simple(100,"BaseType","The basis object class type");
  setclass.AddObjectClass(simple);

  bool result = setclass.Read(file.Stream,setclass);
  cout << "\n -------------  Print  -----------------\n";
  setclass.print(cout);
  cout << "\n ------------- As Line  -----------------\n";
  setclass.WriteAsLine(cout);
  cout << "\n ------------- As Latex -----------------\n";
  setclass.WriteAsLatex(cout);
  cout << "\n ------------- As ASCII -----------------\n";
  setclass.WriteAsASCII(cout);
  cout << "\n -------------   Done   -----------------\n";
  if(result)
    {
      BaseDataSetOfObjects set;
      
      set.Read(file.Stream,&setclass,setclass.NameTag);
      cout << "---\n";
      
      cout << "\n -------------  Print  -----------------\n";
      set.print(cout);
      cout << "\n ------------- As Line  -----------------\n";
      set.WriteAsLine(cout,&setclass);
      cout << "\n ------------- As Latex -----------------\n";
      set.WriteAsLatex(cout,&setclass);
      cout << "\n ------------- As ASCII -----------------\n";
      set.WriteAsASCII(cout,&setclass);
      cout << "\n -------------   Done   -----------------\n";
    }
  else
    {
      cout << "Read in was unsuccessful\n";
    }
  return 0;
}
 
/*F RemoveTest(level1)
**
**  DESCRIPTION
**    A test of removing objects from an object list
**    The input is:
**    - A filename (such as 'TestClass.txt') 
**    - a set of variable names to remove (such as 'var1' or 'var2')
**
**  REMARKS
**
*/
static int RemoveTest(ReactionSystemBase *level1)
{
  CoreObjectTest *test = (CoreObjectTest *) level1;
  
  if(test->Inputs.size() < 1)
    {
      cout << "Needs a filename argument\n";
      return 1;
    }
  

  String filename = test->Inputs.front();
  test->Inputs.pop_front();
  
  OpenInputFile file(filename);

  cout << "\n1  ------------------------------------------\n";
  DataSetOfObjectsClass setclass;
  //DataObjectClass simple(100,"BaseType","The basis object class type");
  //setclass.AddObjectClass(simple);
  DataObjectClass simple1(101,"BaseType1","The basis object class type");
  setclass.AddObjectClass(simple1);

  cout << "\n2  ------------------------------------------\n";
  bool result = setclass.Read(file.Stream,setclass);
  cout << "\n3  ------------------------------------------\n";
  setclass.print(cout);
  
  if(result)
    {
      BaseDataSetOfObjects set;
      cout << "\n4  ------------------------------------------\n";
      
      set.Read(file.Stream,&setclass,setclass.NameTag);
      cout << "\n------------------------------------------\n";
      set.print(cout);
      cout << "\n------------------------------------------\n";

      while(test->Inputs.size() > 0)
	{
	  String name = test->Inputs.front();
	  test->Inputs.pop_front();
	  cout << "\n------------------------------------------\n";
	  cout << "Remove Object: " << name << endl;
	  set.RemoveObject(name);
	  cout << "\n------------------------------------------\n";
	  set.print(cout);
	  cout << "\n------------------------------------------\n";
	}
      
    }
  else
    {
      cout << "Read in was unsuccessful\n";
    }
  return 0;
}
 
/*C
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class ExtraObjectClass : public BaseDataObject
{
  double x;
  unsigned int y;
 public:
  ExtraObjectClass(unsigned int yy)
    : y(yy)
    {
    }
  virtual ~ExtraObjectClass(){};
};
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int MemoryTest(ReactionSystemBase *level1)
{
  CoreObjectTest *test = (CoreObjectTest *) level1;
  unsigned int i;
  
  if(test->Inputs.size() < 2)
    {
      cout << "repititions: The number of repetitions of cycles\n";
      cout << "runsize: The number of objects to add in list\n";
      return 1;
    }
  
  String repetitionsS = test->Inputs.front();
  test->Inputs.pop_front();
  unsigned int repetitions = repetitionsS.ToInteger();
  String runsizeS = test->Inputs.front();
  test->Inputs.pop_front();
  unsigned int runsize = runsizeS.ToInteger();

  ObjectList<String> names;
  names.ChangeTitle("\nSet of Names\n");
  names.ChangeDelimitor(", ");
  
  for(i=0;i<runsize;i++)
    {
      char *p = new char[100];
      ostrstream ost(p,100);
      ost << "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP" << i << ends;
      String str = p;
      names.AddObject(str);
    }
  String
    bigname("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
  
  unsigned int count = 0;
  for(i=0; i < repetitions;i++)
    {
      cout << ". " << flush;
      
      BaseDataSetOfObjects objlist;
      SearchableObjectListFull<Identify,PntrMixed<Identify,Identify> > srchlist;
      SearchableListOfMixedObjects<Identify,Identify> mixlist;

      for(ObjectList<String>::iterator name=names.begin();
	  name != names.end();
	  name++)
	{
	  /*
	    BaseDataObject obj;
	    obj.NameTag = *name;	  
	    bool ans = objlist.AddObject(&obj);
	    if(!ans)
	    cout << "Add Unsuccessful\n";
	  */
	  
	  /*
	  Identify id(count,*name);
	  PntrMixed<Identify,Identify> *ido = new PntrMixed<Identify,Identify>(id,&id,"Identify");
	  delete ido;
	  */

	  /*
	    BaseDataObject obj;
	    obj.NameTag = *name;
	    Identify id(count,*name);
	    PntrMixed<Identify,Identify> *ido = new PntrMixed<Identify,Identify>(id,&obj,"BaseDataObject");
	    delete ido;
	  */
	  
	  /*
	    BaseDataObject obj;
	    Identify *iobj = &obj;
	    String b("BaseDataObject");
	    obj.NameTag = *name;
	    Identify id(count,*name);
	    PntrMixed<Identify,Identify> *ido = new PntrMixed<Identify,Identify>(id,iobj,b);
	    srchlist.AddObject(id,*ido);
	    delete ido;
	  */
	  
	  /*
	    BaseDataObject obj;
	    obj.NameTag = *name;
	    Identify id(count,*name);
	    mixlist.AddObject(id,&obj,"BaseDataObject");
	  */

	  //BaseDataObject obj;
	  ExtraObjectClass obj(count);
	  obj.NameTag = *name;
	  objlist.AddObject(&obj);

	  count++;
	}
	
	BaseDataObject bobj;
	/*
	  CommBuffer buffer(COMM_BUFF_ENCODE,200000,2000);
	  objlist.EncodeThis(buffer);
	  //  bobj.EncodeThis(buffer);
	  cout << "And now print:" << endl;
	  objlist.print(cout);
	  //cout << "---" << endl;
	  //  ido->print(cout);
	  cout << "\nEnd Info" << endl;  
	  
	  BaseDataObject bobj2;
	  BaseDataSetOfObjects *sObj2 = new BaseDataSetOfObjects();
	  CommBuffer buffer1(buffer.GetBuffer(), buffer.GetBufferSize());
	  
	  sObj2->DecodeThis(buffer1);
	  //  bobj2.DecodeThis(buffer1);
	  cout << "2 And now print:" << endl;
	  sObj2->print(cout);
	  //  bobj2.print(cout);
	  //cout << "---" << endl;
	  //  ido->print(cout);
	  cout << "\nEnd Info" << endl;  
	*/
	//int j = runsize/2;
      char *p = new char[100];
      ostrstream ost(p,100);
      ost << "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP" << i << ends;
      String str = p;
      //BaseDataObject *getobj = objlist.GetObject(str);
//      getobj->print(cout);

      /*
      for(ObjectList<String>::iterator name=names.begin();
	  name != names.end();
	  name++)
	{
	  Identify *id = objlist.GetPointerToProperty(count);
	  if(id->NameTag != *name)
	    cout << "Not the same: " << *name << endl;
	  
	  count++;
	}
	*/
    }
  cout << endl;
  
  return 0;
}

      



