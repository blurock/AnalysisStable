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
 
#define TEMPLATE_INSTANTIATION
#include "System.hh"
#include "Pairs.hh"

static void TestBasicPair();
static void TestSymmetricPair();
static void TestPairList();
static void EncodeDecodeBasicPairs();
static void EncodeDecodeSymmetricPairs();



int main()
     {
     TestBasicPair();
     TestSymmetricPair();
     TestPairList();
     EncodeDecodeBasicPairs();
     EncodeDecodeSymmetricPairs();
	return 0;

     }

static void EncodeDecodeBasicPairs()
     {
     cout << "=================================\n";
     cout << "Encode Decode\n";
     
     PairList<int,int> plist;
     BasicPair<int,int> p1(1,1);
     BasicPair<int,int> p2(2,1);
     BasicPair<int,int> p3(3,1);
     plist.AddObject(p1);
     plist.AddObject(p2);
     plist.AddObject(p3);


     cout << "=================================\n";
     cout << "Simple BasicPair\n";
     
     CommBuffer buffer0(COMM_BUFF_ENCODE,2000,2000);
     bool result = Encode(buffer0,p2);
     cout << "Result of Encode: " << result << " " << buffer0.GetBufferSize() << "\n";
     
     cout << "---------------------------------\n";
     cout << "Decode\n";
     CommBuffer inbuffer0(buffer0.GetBuffer(),
			 buffer0.GetBufferSize());
     BasicPair<int,int> newp1;
     result = Decode(inbuffer0,newp1);
     cout << "Result of Decode: " << result << "\n";
     newp1.print(cout);
     cout << "\n";

     cout << "=================================\n";
     cout << "Encode PairList\n";
     
     plist.print(cout);

     cout << "\n";
     
     CommBuffer buffer(COMM_BUFF_ENCODE,200,200);
     result = Encode(buffer,plist);
     cout << "Result of Encode: " << result << " " << buffer.GetBufferSize() << "\n";
     
     cout << "---------------------------------\n";
     cout << "Decode\n";
     CommBuffer inbuffer(buffer.GetBuffer(),
			 buffer.GetBufferSize());
     PairList<int,int> newplist;
     result = Decode(inbuffer,newplist);
     cout << "Result of Decode: " << result << "\n";
     newplist.print(cout);
     cout << "\n";
     }     

static void EncodeDecodeSymmetricPairs()
     {
     cout << "=================================\n";
     cout << "Encode Decode\n";
     
     SymmetricPairList<int> plist;
     SymmetricPair<int> p1(1,1);
     SymmetricPair<int> p2(2,1);
     SymmetricPair<int> p3(3,1);
     plist.AddObject(p1);
     plist.AddObject(p2);
     plist.AddObject(p3);

     cout << "---------------------------------\n";
     cout << "Encode\n";
     
//     cout << plist;
plist.print(cout);

     cout << "\n";
     
     CommBuffer buffer(COMM_BUFF_ENCODE,200,200);
     Encode(buffer,plist);

     cout << "---------------------------------\n";
     cout << "Decode\n";
     CommBuffer inbuffer(buffer.GetBuffer(),
			 buffer.GetBufferSize());
     SymmetricPairList<int> newplist;
     Decode(inbuffer,newplist);
     newplist.print(cout);
     newplist.print(cout);
     
//     cout << newplist;
     cout << "\n";
     }     

static void TestBasicPair()
     {
     cout << "\n   Test Basic Pair \n";
     cout << "\n--------------------------\n";
     BasicPair<int,int> bp1;
     cout << bp1;
     cout << "\n--------------------------\n";
     BasicPair<int,int> bp2(1,2);
     cout << bp2;
     cout << "\n--------------------------\n";
     BasicPair<int,int> bp3(bp2);
     cout << bp3;
     }
static void TestPairList()
     {
     cout << "\n   Test Pair List \n";
     cout << "\n--------------------------\n";
     PairList<int,int> p;
     cout << p;
     cout << "\n--------------------------\n";
     BasicPair<int,int> a1(3,2);
     p.AddObject(a1);
     cout << p;
     cout << "\n--------------------------\n";
     BasicPair<int,int> a2(3,1);
     p.AddObject(a2);
     cout << p;
     cout << "\n--------------------------\n";
     BasicPair<int,int> a3(2,2);
     p.AddObject(a3);
     cout << p;
     
     cout << "\n--------------------------\n";
     p.Sort();
     cout << p;
     cout << "\n--------------------------\n";
      
     }



static void TestSymmetricPair()
     {
     cout << "\n   Test Symmetric Pair\n";
     
     cout << "--------------------------\n";
     SymmetricPair<int> a;
     cout << a;
     cout << "--------------------------\n";
     SymmetricPair<int> b(1,2);
     cout << b;
     cout << "--------------------------\n";
     SymmetricPair<int> c(b);
     cout << c;
     
     cout << "--------------------------\n";
     }
     
