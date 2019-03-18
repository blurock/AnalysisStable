#define TEMPLATE_INSTANTIATION
#include "Basis/System.hh"
#include "Basis/Pairs.hh"
#include "Basis/Graph.hh"
#include "Basis/StartPairs.hh"
#include "Basis/SubGraph.hh"
#include "Basis/FindCorrespondences.hh"
#include "Basis/MixedClasses.hh"

#ifdef _unix
template class ObjectList<int>;
template class FormNextNode<int,int>;
template class Graph<int,int>;
template class GraphSearch<int,int>;
template class GraphSearchInfo<int,int>;

#endif

class GraphTest : public ReactionSystemBase
     {
     String Test;
 public:
     
     GraphTest(int argc, char *argv[]) 
	  : ReactionSystemBase(argc,argv),
	  Test("General")
	  {
	  if(argc > 1)
	       Test = argv[1];
	  }
     virtual int Run()
	  {
	  cout << "Test: " << Test;
	  cout << "\n";
	  
	  if(Test == "General")
	       {
	       Graph<int,int> graph;
	       graph.AddNodeToGraph(1,10);
	       graph.AddNodeToGraph(2,10,1);
	       graph.AddNodeToGraph(3,20,1);
	       graph.AddNodeToGraph(4,20,1);
	       graph.AddNodeToGraph(6,20,2);
	       graph.AddNodeToGraph(7,20,2);

	       
	       cout << "\n--------------------------------------------\n";
	       cout << graph;
	       cout << "==============================================\n";     
	       Graph<int,int> graph1 = graph;
	       Graph<int,int> graph2 = graph;
	       graph1.AddNodeToGraph(8,30,2);
	       graph2.AddNodeToGraph(5,40,1);

	       cout << "\n==============================================\n";     
	       cout << "Start Pairs\n";
	       FindStartPairs<int,int> start(graph1,graph2);
	       cout << "\n==============================================\n";     
	       start.GetStartPairList().print(cout);

	       cout << "\n==============================================\n";     
	       FindSubGraphCorrespondences<int,int> corrs(graph1,graph2);
	       cout << "\nBasic Correspondences\n";
	       cout << corrs.Correspondences;
	       cout << "\n==============================================\n";     
	       cout << "Filter out non-complete\n";
	       corrs.FilterOutSmallCorrespondences();
	       cout << corrs.Correspondences;
	       cout << "\n==============================================\n";     
	       cout << "Filter out not enough bonds\n";
	       corrs.FilterIfNotEnoughBonds();
	       cout << corrs.Correspondences;
	       cout << "\n==============================================\n";     	       
	       }
	  return 0;
	  }
     };

int main(int argc, char *argv[])
     {
     GraphTest test(argc,argv);
     test.Run();
     
     return(0);
     }

