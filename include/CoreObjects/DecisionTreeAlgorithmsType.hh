/*  FILE     DecisionTreeAlgorithmsType.hh
**  PACKAGE  DecisionTreeAlgorithms
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "DecisionTreeAlgorithms" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_DECISIONTREEALGORITHMSTYPE_HH
#define CoreObjects_DECISIONTREEALGORITHMSTYPE_HH

 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
class DataDecisionTreeClass;
class DataDecisionTreeCreateClass;
class DataDecisionTreeNodeSpecClass;
class DataDecisionTreeNodeStatsClass;

/*C BaseDataDecisionTreeNodeSpec  . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the DecisionTreeNodeSpec class definitions
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataDecisionTreeNodeSpec : public BaseDataTreeNode
{
  BaseDataConjunction Conjunction;
  BaseDataKeyWords    Partition;
  
public:
  String Parent;
  
  BaseDataDecisionTreeNodeSpec();
  BaseDataDecisionTreeNodeSpec(const BaseDataDecisionTreeNodeSpec& data);
  BaseDataDecisionTreeNodeSpec(const BaseDataConjunction& data);
  virtual ~BaseDataDecisionTreeNodeSpec(){};

  void InsertPartition(BaseDataKeyWords *partition);
  BaseDataConjunction *PointerToConjunction();
  BaseDataKeyWords *PointerToPartition();

  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);

};
/*C DataDecisionTreeNodeSpecClass . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataDecisionTreeNodeSpecClass : public DataTreeNodeClass
{
  DataConjunctionClass ConjunctionClass;
  DataPartitionClass   PartitionClass;
  
public:
  DataDecisionTreeNodeSpecClass();
  DataDecisionTreeNodeSpecClass(const DataDecisionTreeNodeSpecClass& data);
  DataDecisionTreeNodeSpecClass(const int id, 
		    const String& name,
		    const String& descr);
  DataConjunctionClass *PointerToConjunctionClass();
  DataPartitionClass *PointerToPartitionClass();
  
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataDecisionTreeNodeStats . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the DecisionTreeNodeStats class definitions
**
**  REMARKS
**    Inheirits BaseDataDecisionTreeNodeSpec
*/
class BaseDataDecisionTreeNodeStats : public BaseDataDecisionTreeNodeSpec
{
  BaseDataDoubleMatrix PartitionMatrix;
  double               NumberOfObjects;
  double               Gain;
  ObjectList<double>   GoalStats;
  
public:
  BaseDataDecisionTreeNodeStats();
  BaseDataDecisionTreeNodeStats(const BaseDataDecisionTreeNodeStats& data);
  BaseDataDecisionTreeNodeStats(const BaseDataConjunction& data);
  virtual ~BaseDataDecisionTreeNodeStats(){};
  
  bool InsertElements(BaseDataReal *gainobject,
		      BaseDataDoubleMatrix *mat,
		      BaseDataKeyWords *partition);
  void SetNumberOfObjects(ObjectList<String>& names,
			  BaseDataSetOfLogicDescriptions& ldescrs,
			  DataSetOfLogicDescriptionsClass& ldescrsclass,
			  DataSetOfInstancesClass* instclasses);
  
  ObjectList<double>& GoalStatistics();
  MatrixNumeric& GetCurrentMatrix();
  double GetNumberOfObjects() { return NumberOfObjects;}
  double GetGain() { return Gain; }
  ObjectList<double> *PointerToGoalStats() { return &GoalStats; }

  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataDecisionTreeNodeStatsClass  . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataDecisionTreeNodeSpecClass
*/
class DataDecisionTreeNodeStatsClass : public DataDecisionTreeNodeSpecClass
{
  DataDoubleMatrixClass PartitionMatrixClass;
  
public:
  DataDecisionTreeNodeStatsClass();
  DataDecisionTreeNodeStatsClass(const DataDecisionTreeNodeStatsClass& data);
  DataDecisionTreeNodeStatsClass(const int id, 
		    const String& name,
		    const String& descr);
  DataDoubleMatrixClass *PointerToPartitionMatrixClass();
  
  STANDARD_VIRTUAL_METHODS_CLASS
};


/*C BaseDataDecisionTree  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the DecisionTree class definitions
**
**  REMARKS
**    Inheirits BaseDataEvaluationTree
*/
class BaseDataDecisionTree : public BaseDataEvaluationTree
{
public:
  String instanceNamesS;
  BaseDataKeyWords *instanceNames;
  String decisionTreeS;
  BaseDataDecisionTree *decisionTree;

  BaseDataDecisionTree();
  BaseDataDecisionTree(const BaseDataDecisionTree& data);
  virtual ~BaseDataDecisionTree(){};

  ostream& PrintASCIIDecisionTree(ostream& out);
  ostream& PrintDecisionSubTree(ostream& out,
				BaseDataDecisionTreeNodeStats* node,
				unsigned int level);
  ostream& PrintLevelNodeInfo(ostream& out,
			      BaseDataDecisionTreeNodeStats* node);
  ostream& PrintLevelPrefix(ostream& out, unsigned int level);
  bool EvaluateDecisionTree(BaseDataSetOfInstances *instances,
			    DataSetOfInstancesClass *instancesclass,
			    BaseDataKeyWords *instancenames);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataDecisionTreeClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataEvaluationTreeClass
*/
class DataDecisionTreeClass : public DataEvaluationTreeClass
{
public:
  DataDecisionTreeClass();
  DataDecisionTreeClass(const DataDecisionTreeClass& data);
  DataDecisionTreeClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataDecisionTreeCreate  . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the DecisionTreeCreate class definitions
**
**  REMARKS
**    Inheirits BaseDataDecisionTree
*/
class BaseDataDecisionTreeCreate : public BaseDataDecisionTree
{
  String selectionDescriptorsS;
  BaseDataKeyWords *selectionDescriptors;
  String selectionGoalsS;
  BaseDataKeyWords *selectionGoals;

  BaseDataSetOfLogicDescriptions *logicDescriptions;

  String EntropyCalculationName;
  BaseDataAlgorithmOperation *EntropyCalc;
  String ChooseEntropyName;
  //BaseDataAlgorithmOperation *ChooseEntropy;
  BaseDataEntropySelectPredicate *ChooseEntropy;
  String FilterName;
  BaseDataAlgorithmOperation *Filter;
  BaseDataSetOfObjects OpenNodes;
  ObjectList<String> OpenNodesNames;
  
  BaseDataDecisionTreeNodeStats *node;

public:
  BaseDataDecisionTreeCreate();
  BaseDataDecisionTreeCreate(const BaseDataDecisionTreeCreate& data);
  virtual ~BaseDataDecisionTreeCreate(){};

  bool InitialiseCreate(ObjectList<String>& names,
			BaseDataSetOfLogicDescriptions& ldescrs,
			DataSetOfLogicDescriptionsClass& ldescrsclass,
			DataSetOfInstancesClass* instclasses);

  bool DecideToExpandNode(BaseDataSetOfInstances *instances,
			  DataSetOfInstancesClass *instancesclass,
			  BaseDataAlgorithmRun *run,
			  DataAlgorithmRunClass *runclass);
  bool OpenNotEmpty();
  BaseDataDecisionTreeNodeStats *NextNode();
  bool NodeEntropyCalculate(BaseDataDecisionTreeNodeStats *node,
			    BaseDataSetOfInstances* instances,
			    DataSetOfInstancesClass* instancesclass,
			    BaseDataAlgorithmRun* run,
			    DataAlgorithmRunClass *runclass);
  
  bool AddNodeToOpenList(BaseDataDecisionTreeNodeStats& node);
  bool ExpandNextNode(BaseDataTreeNode *nodeobj,
		      DataTreeNodeClass *,
		      BaseDataSetOfInstances* instances,
		      DataSetOfInstancesClass* instclass,
		      BaseDataSetOfLogicDescriptions& ldescrs,
		      DataSetOfLogicDescriptionsClass& ldescrsclass,
		      BaseDataAlgorithmRun*,
		      DataAlgorithmRunClass *);
  BaseDataDecisionTreeNodeStats *getCurrentNode();

  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataDecisionTreeCreateClass . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataDecisionTreeClass
*/
class DataDecisionTreeCreateClass : public DataDecisionTreeClass
{
  DataAlgorithmOperationClass AlgorithmOperationClass;
  
public:
  DataDecisionTreeCreateClass();
  DataDecisionTreeCreateClass(const DataDecisionTreeCreateClass& data);
  DataDecisionTreeCreateClass(const int id, 
		    const String& name,
		    const String& descr);
  DataSetOfObjectsClass *PointerToOpenNodesClass();
  DataAlgorithmOperationClass *PointerToAlgorithmOperationClass();
  
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataFilterDecisionTreeNode  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the FilterDecisionTreeNode class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataFilterDecisionTreeNode : public BaseDataAlgorithmOperation
{
  String DecisionTreeS;
  BaseDataDecisionTreeCreate *DecisionTree;
  String MinimumNumberOfInstancesS;
  double MinimumNumberOfInstances;
  String MaximumPartitionPercentS;
  double MaximumPartitionPercent;
  String MinimumEntropyValueS;
  double MinimumEntropyValue;
  String MaximumNumberOfNodesS;
  unsigned int MaximumNumberOfNodes;

  BaseDataContinuous *Answer;
public:
  BaseDataFilterDecisionTreeNode();
  BaseDataFilterDecisionTreeNode(const BaseDataFilterDecisionTreeNode& data);
  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
};
/*C DataFilterDecisionTreeNodeClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataFilterDecisionTreeNodeClass : public DataAlgorithmOperationClass
{
public:
  DataFilterDecisionTreeNodeClass();
  DataFilterDecisionTreeNodeClass(const DataFilterDecisionTreeNodeClass& data);
  DataFilterDecisionTreeNodeClass(const int id, 
				  const String& name,
				  const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
