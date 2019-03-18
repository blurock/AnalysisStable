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
#define TEMPLATE_INSTANTIATION
#include "System.hh"
#include "CommBuffer.hh"
#include "String.hh"
#include "MixedClasses.hh"
#include "Objects.hh"

/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
 */
static void TestPntr();
static SearchableObjectListFull<Identify,PntrMixed<Identify,Identify> >& 
TestPntrHelp(SearchableObjectListFull<Identify,PntrMixed<Identify,Identify> >& plist);
static void PropIdentify();
static void TestByName();
static void TestSimpleDecodeRoutines();

/*C MixedClassSystem  . . . . . . . . . . . . . . . . . . . . .  system class
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class MixedClassSystem : public ReactionSystemLevel1
{
public:
  
  MixedClassSystem(int argc, char *argv[])
    : ReactionSystemLevel1(argc,argv)
    {
    }
  virtual int Run()
    {
      cout << "Begin of Mixed Test\n";
      print(cout);
      cout << "=======================================\n";
      TestPntr();
      PropIdentify();
      TestByName();
      return 0;
    }
  virtual int Exit()
    {
      cout << "End of Mixed Test\n";
      return 0;
    }
};
/*S Main
 */
/*f main()  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int main(int argc, char *argv[])
{
  TestSimpleDecodeRoutines();
  
  MixedClassSystem system(argc,argv);
  system.Run();
  system.Exit();
  SetOfEncodeDecodeRoutines = 
    new SearchableObjectListSimple<String,SingleDecodeRoutine>();
  InitialSetOfMixedEncodeDecodeRoutines(SetOfEncodeDecodeRoutines);
       
  return(0);
}
/*S Test of PropertyTypeByName
 */
/*f plist = TestPntrHelp(plist) . . . . . . . . Add PropertyTypeByName<double>
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
SearchableObjectListFull<Identify,PntrMixed<Identify,Identify> >& 
TestPntrHelp(SearchableObjectListFull<Identify,PntrMixed<Identify,Identify> >& plist)
{
  cout << flush;
  cout << " ========== The list with nothing added\n";
  plist.print(cout);
  PropertyTypeByName<double>* flt1 = new PropertyTypeByName<double>("One Floating Number",1.1111);

  Identify *id1 = new Identify(0,flt1->NameTag);
  cout << "\n2--------------------------\n";
  PntrMixed<Identify,Identify> *pntr1 = 
    new PntrMixed<Identify,Identify>(*id1,flt1,"ByName-Float");
  cout << "========== [0,One Floating Number]\n";
  id1->print(cout);
  cout << "\n";
  cout << "========== 2 times One Floating Number and 1.1111\n";
  flt1->print(cout);
  cout << "\n";
  pntr1->Pntr->print(cout);
  cout << "\n3--------------------------\n";     
  plist.AddObject(*id1,*pntr1);
  PntrMixed<Identify,Identify> pntr2 = plist[*id1];
  pntr2.print(cout);
  cout << "\n4--------------------------\n";     
  cout << plist.size() << endl;
       
  cout << flush;
  cout << " ========== The list with the floating point added\n";
  plist.print(cout);
  cout << flush << "\n";
  return(plist);
}

/*f TestPntr()  . . . . . . .  Short PntrMixed test with SearchableObjectList
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static void TestPntr()
{
  cout << "\nTestPntr 0--------------------------\n";     
       
  SearchableObjectListFull<Identify,PntrMixed<Identify,Identify> > plist;
       
  cout << "\nTestPntr 1--------------------------\n";     
  plist = TestPntrHelp(plist);
  cout << "\nTestPntr 4--------------------------\n";     
  Identify id1(0,"One Floating Number");
  PntrMixed<Identify,Identify> pout1 = plist[id1];
  cout << "\nTestPntr 5--------------------------\n";     
  cout << " ========= After retrieving floating point (the ID)\n";
  cout << pout1.ID;
  cout << "\nTestPntr 6--------------------------\n";     
  PropertyTypeByName<double>* ans1 = (PropertyTypeByName<double>*) pout1.Pntr;
  cout << " ========= After retrieving floating point (the structure)\n";
  cout << *ans1;
  cout << "\n";
  pout1.print(cout);
  cout << "\nTestPntr 7--------------------------\n";     
  cout << " ========= The list again\n";
  plist.print(cout);
  cout << "\nTestPntr 8--------------------------\n";
  CommBuffer buf(COMM_BUFF_ENCODE,20000,20000);
  bool ans = plist.EncodeThis(buf);
  if(ans)
    cout << "Encoding Successful\n";
  else
    cout << "Encoding Not-Successful\n";
       
  CommBuffer inbuffer(buf.GetBuffer(),
                      buf.GetBufferSize());
  SearchableObjectListFull<Identify,PntrMixed<Identify,Identify> > newplist;
  ans = newplist.DecodeThis(inbuffer);     
  if(ans)
    cout << "Decoding Successful\n";
  else
    cout << "Decoding Not-Successful\n";
       
  cout << "\nTestPntr 9--------------------------\n";     
  newplist.print(cout);
  cout << "\nTestPntr 10--------------------------\n";
  PntrMixed<Identify,Identify> pout2 = newplist[id1];
  cout << "\nTestPntr 11--------------------------\n";     
  cout << pout2.ID;
  cout << "\nTestPntr 12--------------------------\n";     
  PropertyTypeByName<double>* ans2 = (PropertyTypeByName<double>*) pout2.Pntr;
  cout << *ans2;
}
/*f plist TestWriteByName(plist)  . . . . . . . . . add to PropertyListByName
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
PropertyListByName& TestWriteByName(PropertyListByName& plist)
{
  cout << "\n--------------------------\n";     
  PropertyTypeByName<double>* flt1 = new PropertyTypeByName<double>("One Floating Number",1.1111);
  PropertyTypeByName<double> temp("Two Float",2.22);
  PropertyTypeByName<double>* flt2 = new PropertyTypeByName<double>(temp);
  PropertyTypeByName<int>* i1 = new PropertyTypeByName<int>("One Int",111);
  PropertyTypeByName<int>* i2 = new PropertyTypeByName<int>("Two Int",2222);
  cout << "\n--------------------------\n";     

  plist.AddObject(flt1,"Test1");
  plist.AddObject(flt2,"Test1");
  plist.AddObject(i1,"Test2");
  plist.AddObject(i2,"Test2");

  return(plist);
}
/*f TestRetrieveByName(plist) . . . . . . . . . . . . . .  PropertyListByName
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static void TestRetrieveByName(PropertyListByName& plist)
{
  PropertyTypeByName<double>* ans1 = (PropertyTypeByName<double>*) 
    plist.GetPointerToProperty("Two Float");
  cout << ans1->Object;
  cout << "\n";
  cout << (Identify) *ans1;

  cout << "\n=================================================================\n";
  PropertyTypeByName<double>* ans2 = (PropertyTypeByName<double>*) 
    plist.GetPointerToProperty("One Floating Number");
  cout << ans2->Object;
  cout << "\n";
  cout << (Identify) *ans2;

  cout << "\n=================================================================\n";
  PropertyTypeByName<int>* ans3 = (PropertyTypeByName<int>*) 
    plist.GetPointerToProperty("One Int");
  cout << ans3->Object;
  cout << "\n";
  cout << (Identify) *ans3;

  cout << "\n=================================================================\n";
  PropertyTypeByName<int>* ans4 = (PropertyTypeByName<int>*) 
    plist.GetPointerToProperty("Two Int");
  cout << ans4->Object;
  cout << "\n";
  cout << (Identify) *ans4;
  cout << "\n=================================================================\n";
}
 
/*f TestByName()  . . . . . . . . . . . . . . . . . . . .  PropertyListByName
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static void TestByName()
{
  PropertyListByName plist;
  cout << "\n--------------------------\n";     
  plist = TestWriteByName(plist);
  cout << "\n--------------------------\n";     
  cout << "\n=================================================================\n";
  TestRetrieveByName(plist);
}

/*f TestPntrMixedWithIdentify(id2,id11)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static void TestPntrMixedWithIdentify(const Identify& id2,
                                      Identify *id11)
{
  cout << "PntrMixed Test\n";
  PntrMixed<Identify,Identify> pm1;
  cout << "Empty -- ";
  pm1.print(cout);
  cout << "\n";

  cout << "Identify,Identify (id2,id11)\n";
  PntrMixed<Identify,Identify> pm2(id2,id11,"Test");
  pm2.print(cout);
  cout << "\n";
     
  cout << "Copied filled\n";
  PntrMixed<Identify,Identify> pm3 = pm2;
  pm3.print(cout);
  cout << "\n Copied empty\n";
  PntrMixed<Identify,Identify> pm4 = pm1;
  pm4.print(cout);
  cout << "\n--------------------------\n";     
}
/*C Mix1  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  test 1
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class Mix1 : public Identify
{
public:
     
  int A;
  int B;

  Mix1() 
    {
      A = 99999;
      B = 99999;
    }

  Mix1(const Mix1& mix) 
    : Identify(mix), A(mix.A), B(mix.B)
    {
    }
  Mix1(const Identify& id,const int a, const int b)
    : Identify(id), A(a),B(b)
    {
    }
  Identify* Clone()
    {
      Mix1 *mix = new Mix1();
      mix->CopyClone(this);
            
      return mix;
    }
  void CopyClone(Identify* mix)
    {
      Mix1 *mixcp = (Mix1 *) mix;
      *this = *mixcp;
    }

  ostream& print(ostream& out) const
    {
      out << "[" << A << "," << B << "]\n";
      return out;
    }
};
 
/*C Mix2  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  test 2
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class Mix2 : public Identify
{
public:
     
  int A;
  int B;
  int C;
     
  Mix2() 
    {
    }
  Mix2(const Mix2& mix) 
    : Identify(mix), A(mix.A), B(mix.B), C(mix.C)
    {
    }
  Mix2(const Identify& id,const int a, const int b, const int c)
    : Identify(id), A(a),B(b),C(c)
    {
    }
     
  Identify* Clone()
    {
      Mix2 *mix = new Mix2();
      mix->CopyClone(this);
            
      return mix;
    }
  void CopyClone(Identify* mix)
    {
      Mix2 *mixcp = (Mix2 *) mix;
            
      *this = *mixcp;
    }
  ostream& print(ostream& out) const
    {
      out << "[" << A << "," << B << "," << C << "]\n";
      return out;
    }
     
};
 
 
/*f PutInMix(mix)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static PropertyListByIdentify& PutInMix(PropertyListByIdentify& mix)
{
  Identify id1(1,"One");
  Identify id2(2,"Two");
  Identify id3(3,"Three");
  Identify id4(4,"Four");

  Mix1 mix11(id1,111,1111);
  Mix1 mix12(id2,222,2222);
  Mix2 mix23(id3,333,3333,33333);
  Mix2 mix24(id4,444,4444,44444);
     
  cout << "--------------------------\n";     
  cout << "Put in Mix1 object\n";
  cout << mix11;
  mix.AddObject(&mix11,"Mix1");
     
  cout << "--------------------------\n";     
  cout << "Put in Mix2 object\n";
  mix23.print(cout);
  mix.AddObject(&mix23,"Mix2");
  cout << "--------------------------\n";     
  cout << "Put in Mix1 object\n";
  mix12.print(cout);
  mix.AddObject(&mix12,"Mix1");
  cout << "--------------------------\n";     
  cout << "Put in Mix2 object\n";
  mix24.print(cout);
  mix.AddObject(&mix24,"Mix2");

  cout << "\n--------------------------\n";
  cout << "The Retrieved Mix1 -- 1\n";
  Mix1* mix111b = (Mix1*) mix.GetPointerToObject(id1);
  mix111b->print(cout);
  cout << "\n Leaving PutInMix\n\n";

  cout << "\n--------------------------\n";
  cout << "The list with the four objects\n";
  mix.print(cout);
     
  return(mix);
}
/*f PropIdentify()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static void PropIdentify()
{
  Identify id1(1,"One");
     
  cout << "--------------------------\n";     
  cout << "Short Identity Test\n";
     
  Identify* id11 = new Identify(id1.Identification,id1.NameTag);
  cout << "\n";
  cout << *id11;
  Identify id12 = *id11;
  Identify* id13 = new Identify(id11->Identification,id11->NameTag);
  //     delete id11;
  Identify id2(2,"Two");
  Identify id3(3,"Three");
  cout << "\n";
  cout << id12;
  cout << "\n";
  cout << *id13;
  delete id13;
  Identify id4(4,"Four");
  cout << id12;
  cout << "\n--------------------------\n";     
  TestPntrMixedWithIdentify(id2,id11);
  cout << "\n--------------------------\n";     
     
  PropertyListByIdentify mix;
  PutInMix(mix);
     
  cout << "\n--------------------------\n";
  cout << "The Retrieved Mix1 -- 1\n";
  Mix1* mix111b = (Mix1*) mix.GetPointerToObject(id1);
  cout << *mix111b;

  cout << "\n--------------------------\n";
  cout << "The Retrieved Mix1 -- 2\n";
  Mix1* mix121 = (Mix1*) mix.GetPointerToObject(id2);
  cout << *mix121;

  cout << "\n--------------------------\n";
  cout << "The Retrieved Mix2 -- 3\n";
  Mix2* mix231 = (Mix2*) mix.GetPointerToObject(id3);
  cout << *mix231;

  cout << "\n--------------------------\n";
  cout << "The Retrieved Mix2 -- 4\n";
  Mix2* mix241 = (Mix2*) mix.GetPointerToObject(id4);
  cout << *mix241;
}


 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/


 
/*C Dummy
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DummyClass : public Identify
{
public:
     
  int Object;
  DummyClass(const int id, const String name, const int obj)
    : Identify(id,name),Object(obj)
    {
    }
};

 
/*F TestProg  . . . . . . . . . . . . . . . . . . . . . . . . . .  DummyClass
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool TestProg(CommBuffer&,DummyClass& id)
{
  cout << "For Property Type\n";
     
  cout << id.Identification;
  cout << "\n";
  cout << id.NameTag;
  cout << "\n";
  cout << id.Object;
  cout << "\n";

  return true;
}
 
/*F TestProg  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . int
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool TestProg(CommBuffer&, int i)
{
  cout << "For Integer\n";
  cout << i;
  cout << "\n";
  return true;
}
 
/*F TestSimpleDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static void TestSimpleDecodeRoutines()
{
  SearchableObjectList<String,SingleDecodeRoutine> Routines;
  bool (*r1)(CommBuffer&,DummyClass&) = TestProg;
  bool (*r2)(CommBuffer&,int) = TestProg;
  SingleDecodeRoutine p1("Identify",r1);
  SingleDecodeRoutine p2("int",     r2);
  Routines.AddObject(p1.StructureName,p1);
  Routines.AddObject(p2.StructureName,p2);
  Routines.AddObject(p2.StructureName,p2);
  Routines.AddObject(p2.StructureName,p2);
  cout << "Size of Routines -- " << Routines.size() << "\n";
     

  CommBuffer buf(COMM_BUFF_ENCODE,200,200);

  DummyClass id(1,"XXXX",2222);
     
  bool (*rout1)(CommBuffer&,Identify&) = (bool (*)(CommBuffer&,Identify&))  Routines["Identify"].Routine;
  rout1(buf,id);
  bool (*rout2)(CommBuffer&,int)       = (bool (*)(CommBuffer&,int)) Routines["int"].Routine; 
  int ii = 2;
  rout2(buf,ii);
}




