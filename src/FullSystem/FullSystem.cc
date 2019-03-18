/*  FILE     FullSystem.cc
**  PACKAGE  FullSystem
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "FullSystem" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#define TEMPLATE_INSTANTIATION

#include "FullSystem.hh"


/*S FullSystemSave
 */

void AnalysisSystemSave::StandardObjectsSetUp() {
      GoalSystemSave::StandardObjectsSetUp();

      AddBaseAlgorithmClasses(getStandard());
      AddSelectionTreeClasses(getStandard());
      AddDirectedTreeObjects(getStandard());


      AddInstanceAlgorithmsClasses(getStandard());
      AddEntropyAlgorithmClasses(getStandard());
      AddPredicateClasses(getStandard());
      AddPredicateGenAlgorithmClasses(getStandard());
      AddEvaluationTreeClasses(getStandard());
      AddDecisionTreeClasses(getStandard());
      AddCobwebAlgorithmClasses(getStandard());
      AddClusterTreeClasses(getStandard());
      AddBaseExpressionTreeClasses(getStandard());
      AddBaseDistributionClasses(getStandard());
      //AddBasePCAClasses(getStandard());
      AddDescriptionProbsClasses(getStandard());
      AddLogicalOperationClasses(getStandard());
      AddNumericOperationClasses(getStandard());
      AddParameterizedClasses(getStandard());

      AddConsecutiveClasses(getStandard());
      AddVectorOperationClasses(getStandard());

      AddGeneralGraphClasses(getStandard());
      AddGraphOperationClasses(getStandard());

      //AddRuleSystemClasses(getStandard());
      //AddSimAnnAlgorithmsClasses(getStandard());

      AddOptimizeClasses(getStandard());
      AddPopulationClasses(getStandard());
      AddGeneticClasses(getStandard());
      
      //AddBaseVerifyClasses(getStandard());

      AddNumericPropertiesClasses(getStandard());
      AddEquivalenceClassesClasses(getStandard());
      
    }

void AnalysisSystemSave::EncodeDecodeObjectsSetUp()
    {
      GoalSystemSave::EncodeDecodeObjectsSetUp();
      InitialInstanceAlgorithmsEncodeDecodeRoutines();
      InitialEntropyAlgorithmEncodeDecodeRoutines();
      InitialSetOfPredicateEncodeDecodeRoutines();
      InitialPredicateGenEncodeDecodeRoutines();
      InitialEvaluationTreeEncodeDecodeRoutines();
      DecisionTreeEncodeDecodeRoutines();
      ClusterTreeEncodeDecodeRoutines();
      CobwebClusterEncodeDecodeRoutines();
      InitialSetOfExpressionTreeEncodeDecodeRoutines();
      InitialDistributionObjectsEncodeDecodeRoutines();
      InitialPCAEncodeDecodeRoutines();
      InitialDescriptionProbsEncodeDecodeRoutines();
      InitialSetOfNumericOperationEncodeDecodeRoutines();
      InitialSetOfLogicalOperationEncodeDecodeRoutines();
      InitialParameterizedEncodeDecodeRoutines();
      ConsecutiveEncodeDecodeRoutines();
      InitialSetOfGeneralGraphEncodeDecodeRoutines();
      InitialGraphOperationEncodeDecodeRoutines();

      InitialSetOfOptimizeEncodeDecodeRoutines();
      InitialSetOfPopulationEncodeDecodeRoutines();
      InitialGeneticEncodeDecodeRoutines();

      InitialSetOfNumericPropertiesEncodeDecodeRoutines();
      //InitialSimAnnAlgorithmsEncodeDecodeRoutines();

      //InitialSetOfRuleSystemEncodeDecodeRoutines();
      //VerifyEncodeDecodeRoutines();
      InitialVectorOperationsEncodeDecodeRoutines();
      InitialSetOfEquivalenceClassesEncodeDecodeRoutines();

    }

void AnalysisSystemSave::CommandSetUp()
    {
      GoalSystemSave::CommandSetUp();

      String distS("DistributionReport");
      SingleSystemCommand dist(distS,
			     "Create a Distribution Statistics Report",
			     &DistributionReport);
      Commands.AddObject(distS,dist);

      String critS("MakeCriticalPoints");
      SingleSystemCommand crit(critS,
			     "Create a Critical Points File",
			     &CriticalPointList);
      Commands.AddObject(critS,crit);

      String trans("TransferAttributes");
      SingleSystemCommand transfer(trans,
				    "Transfer Attributes",
				    &TransferAttributes);
      Commands.AddObject(trans,transfer);

    }
int AnalysisSystemSave::Run() {
    String done("END");
    if(Inputs.size() == 0) {
      istream& inputstream = cin;
      String inpline;
      bool notDone = true;
      while(notDone) {
	cout << "Reaction::" << endl;
	cerr << "Reaction::" << endl;
	cout.flush();
	cerr.flush();
	inpline.ReadFullLine(inputstream);
	cout << "Command Line: '" << inpline << "'" << endl;
	cerr << "Command Line: '" << inpline << "'" << endl;
	if(!strncmp(inpline.c_str(), done.c_str(),3))
	  notDone = false;
	else {
	  loadInput(inpline);
	  Commands.ExecuteCommand(0,0,this);
	}
      }
    } else {
      Commands.ExecuteCommand(0,0,this);
    }
    return 1;
  }
void AnalysisSystemSave::loadInput(String line) {
    String word;
    while(Inputs.size() > 0) {
      word = GetNextInput();
      cout << "Extra: '" << word << "'" << endl;
    }

    while(!line.IsEmpty()) {
      line.IsolateNextWord(word,' ');
      Inputs.AddObject(word);
    }
}
int DistributionReport(ReactionSystemBase *sys)
{
  AnalysisSystemSave *flametest = (AnalysisSystemSave *) sys;

  String reportname = sys->GetNextInput();
  String dists      = sys->GetNextInput();

  String tex("tex");
  OpenOutputDataFile reportout(reportname,tex);
  reportout.Stream << "\\section{Distribution of Data}" << endl;

  String gnu("gnu");
  OpenOutputDataFile gnuout(reportname,gnu);
  gnuout.Stream << "set grid" << endl;
  gnuout.Stream << "set data style boxes" << endl;
  gnuout.Stream << "set terminal postscript eps monochrome solid" << endl;

  String postfix("dat");

  BaseDataKeyWords *keys = (BaseDataKeyWords *) flametest->Instances.GetObject(dists);
  cout << "The keywords: " << endl;
  keys->print(cout);
  cout << endl;

  ObjectList<String> names = keys->GetKeyWords();
  ObjectList<String>::iterator name;
  for(name = names.begin(); name != names.end(); name++)
    {
      cout << "Distribution: " << *name << endl;
      if(flametest->Instances.IsInList(*name))
	{
	  OpenOutputDataFile distout(*name,postfix);

	  BaseDataAttributeDistribution *distribution = (BaseDataAttributeDistribution *) flametest->Instances.GetObject(*name);
	  EvenDistributionStats *stats = (EvenDistributionStats *) distribution->getStatistics();
	  double val = stats->Min;
	  for(VectorNumeric::const_iterator count = stats->Counts.begin() ; 
	      count != stats->Counts.end();
	      count++)
	    {
	      distout.Stream << setw(20) << val << "  ";
	      distout.Stream << setw(20) << *count << endl;
	      val += stats->IntervalSize;
	    }
	  
	  gnuout.Stream << "set output '" << *name << ".eps" << "'" << endl;
	  gnuout.Stream << "plot '" << *name << "." << postfix << "'" << endl;

	  reportout.Stream << "\\begin{figure}[htb]" << endl;
	  reportout.Stream << "    \\begin{center}" << endl;
	  reportout.Stream << "      \\standardeps{" << *name << "}" << endl;
	  reportout.Stream << "      \\caption{Distribution from " << *name << "}" << endl;
	  reportout.Stream << "      \\label{fig:" << *name << "}" << endl;
	  reportout.Stream << "    \\end{center}" << endl;
	  reportout.Stream << "\\end{figure}" << endl;
	  reportout.Stream << "\\clearpage" << endl;
	}
      else
	{
	  cerr << "Distribution: '" << *name << "' not found in Attributes" << endl;
	}
    }
  return 0;
}

int CriticalPointList(ReactionSystemBase *sys)
{
  AnalysisSystemSave *flametest = (AnalysisSystemSave *) sys;

  String critpointsname = sys->GetNextInput();
  String dists      = sys->GetNextInput();
  String listtype       = sys->GetNextInput();

  String dat("dat");
  OpenOutputDataFile critpointout(critpointsname,dat);

  BaseDataKeyWords *keys = (BaseDataKeyWords *) flametest->Instances.GetObject(dists);

  ObjectList<String> names = keys->GetKeyWords();
  ObjectList<String>::iterator name;
  for(name = names.begin(); name != names.end(); name++)
    {
      cout << "Distribution: " << *name << endl;
      if(flametest->Instances.IsInList(*name))
	{
	  BaseDataAttributeDistribution *distribution = (BaseDataAttributeDistribution *) flametest->Instances.GetObject(*name);
	  EvenDistributionStats *stats = (EvenDistributionStats *) distribution->getStatistics();
	  double val = stats->Min;
	  critpointout.Stream << *name << endl;
	  critpointout.Stream << "CriticalPoints: " << stats->NameTag << "   ";
	  if(listtype == "DistributionPartitions")
	    {
	      for(VectorNumeric::const_iterator count = stats->Counts.begin() ; 
		  count != stats->Counts.end();
		  count++)
		{
		  critpointout.Stream << "[" << val << "," << stats->IntervalSize << "]  ";
		  val += stats->IntervalSize;
		}
	    }
	  else
	    {
	      critpointout.Stream << "[" << stats->Min + stats->IntervalSize << "," << stats->IntervalSize << "]  ";
	      critpointout.Stream << "[" << stats->Average << "," << stats->StdDev << "]  ";
	    }
	  critpointout.Stream << "END" << endl;
	}
      else
	{
	  cerr << "Distribution: '" << *name << "' not found in Attributes" << endl;
	}
    }
  critpointout.Stream << "END" << endl;

  return 0;
}
/*F ans = TransferAttributes(system)
**
**  DESCRIPTION
**    system: The system structure
**    ans: Zero if successful
**
**  REMARKS
**
*/
int TransferAttributes(ReactionSystemBase* sys)
{
  InstanceSystem* system = (InstanceSystem *) sys;
  
  int result = SYSTEM_NORMAL_RETURN;
  BaseDataSetOfInstances instances = system->Instances;
  cout << "Number of Inputs: " << system->Inputs.size() << endl;
  while(system->Inputs.size() > 1)
    {
      String source = system->GetNextInput();
      String destination = system->GetNextInput();
      cout << "Transfer: '" << source << "' to  '" << destination << "'" << endl;
      if(system->Instances.IsInList(source))
	{
	  BaseDataObject *obj = (BaseDataObject *) system->Instances.GetObject(source)->Clone();
	  obj->NameTag = destination;
	  system->Instances.AddObject(obj);
	}
      else
	{
	  cerr << "Source Attribute Not found: '" << source << "'" << endl;
	  result = SYSTEM_ERROR_RETURN;
	}
    }
  return result;
}
