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
#include "platform.hh"
#include "CommBuffer.hh"
#include "String.hh"
#include "Objects.hh"

static void IdentifyTest(void);
static void ObjectListTest();
static void SearchableObjectTest();
static void SearchableObjectRemoveTest();

static void EncodeIt(CommBuffer& outbuffer);
static void DecodeIt(CommBuffer& outbuffer);

static void ObjectListAndIdentifyDecode(CommBuffer& buffer);
static CommBuffer ObjectListAndIdentifyEncode();


int main()
{
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++\n";
  cout << "Identify Test\n";
  IdentifyTest();
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++\n";
  cout << "ObjectListTest\n";
  ObjectListTest();
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++\n";
  cout << "SearchableObjectTest\n";       
  SearchableObjectTest();
       
  cout << flush << "++++++++++++++++++++++++++++++++++++++++++++++++\n";
  cout << "SearchableObjectRemoveTest\n";       
  SearchableObjectRemoveTest();
       
  cout << flush << "++++++++++++++++++++++++++++++++++++++++++++++++\n";
  cout << "Encode Decode Test\n";

  cout << flush << "========================================\n";
  cout << "Encode Test\n";
  CommBuffer outbuffer(COMM_BUFF_ENCODE,1000,2000);
  EncodeIt(outbuffer);
       
  cout << flush << "========================================\n";
  cout << "Decode Test\n";
  DecodeIt(outbuffer);
  cout << flush;
  cout << "========================================\n";
  cout << "Encode Identify and Object list\n";
  CommBuffer buffer = ObjectListAndIdentifyEncode();
  cout << flush;
       
  cout << "========================================\n";
  cout << "Decode Identify and Object list\n";
  ObjectListAndIdentifyDecode(buffer);
       
       
  IdentifyTest();
       
       
  cout << "--------================================\n";

  IdentifyTest();
       
  cout << "++++++++================================\n";
       
  cout << flush;
       
       
       
  return(0);
} 

static void EncodeIt(CommBuffer& outbuffer)
{
  SearchableObjectListSimple<int,String> slist;
  slist.ChangeTitle("Searchable ------------------");
  slist.ChangeDelimitor(", ");
  
  String s1("1bb");
  String s2("1bbxxxxxxxxx");
  String s3("1bbbbbbbbbbbbbb");
  String s4("rrrrrr1bb");
  String s5("222222221bb");

  slist.AddObject(100,s1);
  slist.AddObject(200,s2);
  slist.AddObject(300,s3);
  slist.AddObject(300,s4);
  slist.AddObject(100,s5);
  
  ObjectList<int> olist("Test Case\n",", ");
  olist.AddObject(1);
  olist.AddObject(2);
  olist.AddObject(3);
  olist.AddObject(4);
  olist.AddObject(5);
  
  cout << olist;
  cout << "\n";
  slist.print(cout);
  cout << "\n";
  
  slist.EncodeThis(outbuffer);
  Encode(outbuffer,olist);
}
static void DecodeIt(CommBuffer& outbuffer)
{
  CommBuffer inbuffer(outbuffer.GetBuffer(),
                      outbuffer.GetBufferSize());
  SearchableObjectListSimple<int,String> slist;
  ObjectList<int> olist;
  
  slist.DecodeThis(inbuffer);
  Decode(inbuffer,olist);
  
  slist.print(cout);
  cout << "\n";
  cout << olist;
  cout << "\n";
}


static void SearchableObjectTest()
{
  SearchableObjectListSimple<int,int> slist;
  slist.ChangeTitle("Searchable -- ");
  slist.ChangeDelimitor(", ");
  
  slist[100] = 1000;
  slist[200] = 2000;
  slist[300] = 3000;
  
  slist.print(cout);
  cout << "\n";
  
  cout << "========================================\n";
  cout << "Encode Test\n";
  CommBuffer outbuffer(COMM_BUFF_ENCODE,200,200);
  slist.EncodeThis(outbuffer);
  
  CommBuffer inbuffer(outbuffer.GetBuffer(),
                      outbuffer.GetBufferSize());
  
  SearchableObjectListSimple<int,int> inlist;
  inlist.DecodeThis(inbuffer);
  
  inlist.print(cout);
  cout << "\n";
  
  
}
static void FillInList(SearchableObjectList<Identify,Identify>& slist)
{
  Identify id1(1,"ID1");
  Identify id2(2,"ID111111");
  Identify id3(3,"ID122222222222222");
  Identify id1k(1111,"ID1");
  Identify id2k(2222,"ID111111");
  Identify id3k(3333,"ID122222222222222");
  slist.AddObject(id1k,id1);
  
  slist.AddObject(id2k,id2);
  
  slist.AddObject(id3k,id3);
}

static void SearchableObjectRemoveTest()
{
  SearchableObjectListFull<Identify,Identify> slist;
  slist.ChangeTitle("Searchable -- ");
  slist.ChangeDelimitor(", ");
  
  Identify id1k(1111,"ID1");
  Identify id2k(2222,"ID111111");
  Identify id3k(3333,"ID122222222222222");
  
  FillInList(slist);
  
  slist.print(cout);
  cout << "\n";
  
  cout << "========================================\n";
  cout << "Remove Test\n";
  
  slist.RemoveObject(id2k);
  slist.print(cout);
  cout << "\n";
  Identify id1kcopy(id1k);
  cout << "\n========================================\n";
  slist.RemoveObject(id1k);
  slist.print(cout);
  cout << "\n";
  Identify id2(321,"ID1234567890");
  slist.AddObject(id2k,id2);
  cout << "\n========================================\n";
  slist.print(cout);
  cout << "\n";
  slist.RemoveObject(id3k);
  slist.print(cout);
  cout << "\n";
  
}

static void ObjectListTest()
{
  
  ObjectList<int> list("Test Case\n",", ");
  list.AddObject(1);
  list.AddObject(2);
  list.AddObject(3);
  list.AddObject(4);
  list.AddObject(5);

  cout << list;
  cout << "\n";
     
  cout << "========================================\n";
  cout << "Encode Test\n";
  CommBuffer outbuffer(COMM_BUFF_ENCODE,200,200);
  Encode(outbuffer,list);

  CommBuffer inbuffer(outbuffer.GetBuffer(),
                      outbuffer.GetBufferSize());
  ObjectList<int> newlist;
  Decode(inbuffer,newlist);
  cout << newlist;
  cout << "\n";
  cout << "========================================\n";
}     

static void IdentifyTest(void)
{
  Identify iden1;
  cout << "Empty Identify\n";
  cout << iden1;
  cout << "\n";
     
  String onehundred("One Hundred");
  Identify iden2(100,onehundred);
  cout << "Identify with number and string\n";
  cout << iden2;
  cout << "\n";

  Identify iden3(200);
  cout << "Identify with just number\n";
  cout << iden3;
  cout << "\n";
     
  Identify iden4("Four Hundred");
  cout << "Identify with just string\n";
  cout << iden4;
  cout << "\n";
     
  Identify iden5(iden2);
  cout << "Identify copied (100,One Hundred)\n";
  cout << iden5;
  cout << "\n";
     
  cout << "========================================\n";
  cout << "Encode Test\n";
  CommBuffer outbuffer(COMM_BUFF_ENCODE,2000,2000);
  Encode(outbuffer,iden1);
  Encode(outbuffer,iden2);
  Encode(outbuffer,iden3);
  Encode(outbuffer,iden4);
     
  CommBuffer inbuffer(outbuffer.GetBuffer(),
                      outbuffer.GetBufferSize());

  Identify iden1a,iden2a,iden3a,iden4a;
  Decode(inbuffer,iden1a);
  cout << iden1a;
  cout << flush << "\n";
  Decode(inbuffer,iden2a);
  cout << iden2a;
  cout << flush << "\n";
  Decode(inbuffer,iden3a);
  cout << iden3a;
  cout << flush << "\n";
  Decode(inbuffer,iden4a);
  cout << iden4a;
  cout << flush << "\n";
  cout << "========================================\n";
     
}

static CommBuffer ObjectListAndIdentifyEncode()
{

  CommBuffer *buffer = new CommBuffer(COMM_BUFF_ENCODE,2000,2000);

        
  Identify id(1000,"The cat in the hat");
  ObjectList<double> lst;
     
  double flt = 0.0;
  for(int i=0;i<600;i++)
    {
      lst.AddObject(flt);
      flt++;
    }
  lst.ChangeTitle("--------This is the Title-------------------------------------\n");
     
     
  Encode(*buffer,id);
  Encode(*buffer,lst);
  Encode(*buffer,lst);
     
  return *buffer;
}

static void ObjectListAndIdentifyDecode(CommBuffer& buffer)
{
  Identify id;
  ObjectList<double> lst1,lst2,lst3;
     
  CommBuffer inbuffer(buffer.GetBuffer(),
                      buffer.GetBufferSize());
  Decode(inbuffer,id);
  Decode(inbuffer,lst1);
  Decode(inbuffer,lst2);
     
  cout << id;
  cout << "\n";
  cout << lst1;
  cout << "\n";
  cout << lst2;
     
}
