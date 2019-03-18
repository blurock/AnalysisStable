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
#include "ONames.hh"

void SimpleCheck();
void ReadAndStoreCheck();
void ClassNameCheck();
void InitializeONamePropertyDecodeFunctions();

int main(int argc, char *argv[])
{
  ReactionSystemLevel1 system(argc,argv);
     
  //     SimpleCheck();
  InitializeONamePropertyDecodeFunctions();
  ReadAndStoreCheck();
  //     ClassNameCheck();
  return 0;
  
}

 
/*F SimpleCheck() . . . . . . . . . . . . . . . . . . . . . . . simple checks
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void SimpleCheck()
{
  AlternativeNames names;
     
  names["Test1"] = "Sample1";
  names["Test2"] = "Sample2";
  names["Test3"] = "Sample3";
     
  cout << "\n-----------------------------------------\n";
  cout << names;
  cout << "\n-----------------------------------------\n";
  AlternativeNames *newnames = new AlternativeNames;
  *newnames = names;
  cout << *newnames;
  cout << "\n-----------------------------------------\n";
  CommBuffer buffer(COMM_BUFF_ENCODE);
  Encode(buffer,*newnames);
  delete newnames;
  CommBuffer newbuffer(buffer.GetBuffer(),buffer.GetBufferSize());
  AlternativeNames bnames;
  Decode(newbuffer,bnames);
  cout << bnames;
  bnames["TestAfter1"] = "AfterTest1";
  bnames["TestAfter2"] = "AfterTest2";
  cout << bnames;
  cout << "\n-----------------------------------------\n";
  cout << bnames["TestAfter1"];
  cout << "   ";
  cout << bnames["Test2"];
  cout << "\nUnknown\n";
  cout << bnames["TTTTTTT"];
  cout << "\n-----------------------------------------\n";
}
 

void AddObjectTest(PropertyListByName* plist,
                   Identify *prop1, 
                   const String& name)
{
  Identify* pid = new Identify(0,prop1->NameTag);
  PntrMixed<Identify,Identify> *ido = new PntrMixed<Identify,Identify>(*pid,prop1,name);     
  (*plist)[*pid] = *ido;
}

/*F ReadAndStoreCheck() . . . . . . . . . . . . . . . . . . . . . as property
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void ReadAndStoreCheck()
{
  cout << "ReadAndStoreCheck";
  cout << "\n-----------------------------------------\n";
  StringPropertyFunctions PropertyFunctions;
  PropertyListByName* plist = new PropertyListByName;
  InitONameForPropertyList(plist);
  plist->print(cout);
  /*     
         AlternativeNames names;
         cout << "\n-----------------------------------------\n";
         cout << names;
     
         PropertyTypeByName<AlternativeNames> *prop1
         = new PropertyTypeByName<AlternativeNames>("AlternativeNames",names);
         plist->AddObject(prop1,"AlternativeNames");
     
         cout << "\n-----------------------------------------\n";
         cout << *plist;
     
         cout << "\n-----------------------------------------\n";
         PropertyListByName plist2 = *plist;
         cout << plist2;
     

         ObjectStringClasses classnames;
         cout << "\n-----------------------------------------\n";
         cout << classnames;

         PropertyTypeByName<ObjectStringClasses> *prop2
         = new PropertyTypeByName<ObjectStringClasses>("ObjectStringClasses",classnames);
         plist->AddObject(prop2,"ObjectStringClasses");

         cout << "\n-----------------------------------------\n";
         cout << *plist;
     
         cout << "\n-----------------------------------------\n";
         PropertyListByName plist1 = *plist;
         cout << plist1;
         */     
  cout << "\n-----------------------------------------\n";
  String line1 = "CHEMKIN C4H8";
  String line2 = "CLASS Hydrocarbon";


  AlternativeNamesFromLine(plist,line1);
  AlternativeNamesFromLine(plist,line2);
  plist->print(cout);
  cout << "\n-----------------------------------------\n";
  cout << "Encode/Decode\n";     
  CommBuffer buffer(COMM_BUFF_ENCODE);
  Encode(buffer,*plist);
  delete plist;
  cout << "\n-----------------------------------------\n";
  CommBuffer newbuffer(buffer.GetBuffer(),buffer.GetBufferSize());
  PropertyListByName newlist;
  Decode(newbuffer,newlist);
  cout << "\n-----------------------------------------\n";
  newlist.print(cout);
  cout << "\n-----------------------------------------\n";
  String line3 = "SUPER_CLASS Small_Hydrocarbon";
  AlternativeNamesFromLine(&newlist,line3);
  newlist.print(cout);
  cout << "\n-----------------------------------------\n";
  String altname = GetAlternativeName("CHEMKIN",newlist);
  cout << altname;
  cout << "\n-----------------------------------------\n";

}

/*F ReadAndStoreCheck() . . . . . . . . . . . . . . . . . . . . . as property
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void ClassNameCheck()
{
  cout << "\n-----------------------------------------\n";
  StringPropertyFunctions PropertyFunctions;
  PropertyListByName* plist = new PropertyListByName;
  InitONameForPropertyList(plist);
     
  String line1 = "Hydrocarbon";
  String line2 = "Very Small Atom";

  ObjectStringClassesFromLine(plist,line1);
  ObjectStringClassesFromLine(plist,line2);
  plist->print(cout);
  cout << "\n-----------------------------------------\n";
  CommBuffer buffer(COMM_BUFF_ENCODE);
  Encode(buffer,*plist);
  delete plist;
  CommBuffer newbuffer(buffer.GetBuffer(),buffer.GetBufferSize());
  PropertyListByName newlist;
  Decode(newbuffer,newlist);
  newlist.print(cout);
  cout << "\n-----------------------------------------\n";
  String line3 = "Small_Hydrocarbon";
  ObjectStringClassesFromLine(&newlist,line3);
  newlist.print(cout);
  cout << "\n-----------------------------------------\n";
  bool altname = IsMemberOfClass("Hydrocarbon",newlist);
  if(altname)
    cout << "Is a member of Hydrocarbon";
  else
    cout << "Said it wasn't a member -- but should be";
  cout << "\n-----------------------------------------\n";
}
