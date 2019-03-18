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
#include "Pairs.hh"
#include "Graph.hh"

#ifdef _unix
template class list<int>;
template class list< BasicPair<Identify,Identify> >;
template class list< BasicPair<int,int> >;
#endif

static void IdentifyGraph();
static void EncodeDecode();
static void IntegerGraph();
static Graph<Identify,Identify> CreateIdentifyGraph();


main ()

{
  IdentifyGraph();

  //     IntegerGraph();
  cout << "==============================================\n";
  EncodeDecode();
  return(0);
}


static void IdentifyGraph()
{
  Graph<Identify,Identify> graph = CreateIdentifyGraph();
     
  GraphOut(cout,graph,true,true);
}

static Graph<Identify,Identify> CreateIdentifyGraph()
{
  Graph<Identify,Identify> graph;
     
  cout << graph;
  cout << "\n";
     
  Identify nid1(11,"node one");
  Identify nid2(12,"node two");
  Identify nid3(13,"node three");
  Identify nid4(14,"node four");
  Identify nid5(15,"node five");
  Identify nid6(16,"node six");
  Identify nid7(17,"node seven");
  Identify nid8(18,"node eight");
  Identify nid9(19,"node nine");

  Identify kid1(21,"key one");
  Identify kid2(22,"key two");
  Identify kid3(23,"key three");
  Identify kid4(24,"key four");
  Identify kid5(25,"key five");
  Identify kid6(26,"key six");
  Identify kid7(27,"key seven");
  Identify kid8(28,"key eight");
  Identify kid9(29,"key nine");
     
  graph.AddNodeToGraph(kid1,nid1);
  graph.AddNodeToGraph(kid2,nid2);
  graph.AddNodeToGraph(kid3,nid3);
  graph.AddNodeToGraph(kid4,nid4);
  graph.AddNodeToGraph(kid5,nid5);
  graph.AddNodeToGraph(kid6,nid6);
  graph.AddNodeToGraph(kid7,nid7);
  graph.AddNodeToGraph(kid8,nid8);
  graph.AddNodeToGraph(kid9,nid9);
     
  //     cout << graph;
  //     cout << "\n";
  graph.AddBondToGraph(kid1,kid2);
  graph.AddBondToGraph(kid2,kid3);
  graph.AddBondToGraph(kid3,kid4);
  graph.AddBondToGraph(kid4,kid1);

  //     cout << graph;
  //     cout << "\n";
  graph.AddBondToGraph(kid1,kid5);
  graph.AddBondToGraph(kid5,kid6);
  graph.AddBondToGraph(kid6,kid7);
  graph.AddBondToGraph(kid7,kid8);
  graph.AddBondToGraph(kid8,kid9);
  graph.AddBondToGraph(kid9,kid6);

  //     cout << graph;
  //     cout << "\n";
  return graph;
}     

static void IntegerGraph()
{
  Graph<int,int> graph;
  ObjectList<int> matchlist;
     
  graph.AddNodeToGraph(11,111);
  graph.AddNodeToGraph(121,222,11);
  graph.AddNodeToGraph(122,222,11);
  graph.AddNodeToGraph(123,222,11);
  graph.AddNodeToGraph(31,333,11);
  graph.AddNodeToGraph(14,444,121);
  graph.AddNodeToGraph(15,555,121);

  graph.RemoveGraphNode(12);

  cout << "------------------------------\n";
  cout << "Output of Graph\n";
  cout << graph;

  cout << "------------------------------\n";
  cout << "Matching 222\n";
  matchlist = graph.NodesMatchingValue(222);
  cout << matchlist;

  cout << "------------------------------\n";
  cout << "The Node List\n";
  ObjectList<int> nodelist = graph.GetSetOfGraphKeys();
  cout << nodelist;
  cout << "------------------------------\n";
     
  PairList<int,int> glist = graph.GraphToPairList();
  cout << glist;
  cout << "\n";

  ObjectList<int> keys = graph.GetSetOfGraphKeys();
  cout << keys;
  cout << "\n";

  ObjectList<int> values = graph.GetSetOfUniqueGraphValues(keys);
  cout << values;
  cout << "\n";

  cout << "\n_____________________\n";
     
  SetOfPairSets<int,int> newsets;

  newsets.SetsOfEquivalentJ(values,glist);
  cout << newsets.size() << "\n";
  newsets.print(cout);
  cout << "\n";
     
  ObjectList<int> key1;
  key1.AddObject(11);
  key1.AddObject(11);
  key1.AddObject(31);
}



static void EncodeDecode()
{
  Graph<int,int> graph;
  ObjectList<int> matchlist;
     
  graph.AddNodeToGraph(11,111);
  graph.AddNodeToGraph(121,222,11);
  graph.AddNodeToGraph(122,222,11);
  graph.AddNodeToGraph(123,222,11);
  graph.AddNodeToGraph(31,333,11);
  graph.AddNodeToGraph(14,444,121);
  graph.AddNodeToGraph(15,555,121);


     
  cout << "-----------------------------------------\n";
  cout << "Encode\n";
  cout << graph;
     
  CommBuffer buffer(COMM_BUFF_ENCODE);
  Encode(buffer,graph);
     
  cout << "-----------------------------------------\n";
  cout << "Decode\n";
  CommBuffer inbuffer(buffer.GetBuffer(),
                      buffer.GetBufferSize());
  Graph<int,int> newgraph;
  Decode(inbuffer,newgraph);
     
  cout << "-----------------------------------------\n";
  cout << newgraph;
}
