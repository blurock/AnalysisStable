/*  FILE     CobwebClusterType.hh
**  PACKAGE  CobwebCluster
**  AUTHOR   Edward S. Blurock 
**
**  CONTENT
**    Class definitions for the "CobwebCluster" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_COBWEBCLUSTERTYPE_HH
#define CoreObjects_COBWEBCLUSTERTYPE_HH

class DataCobwebClusterNodeStatsClass;
class DataCobwebClusterTreeCreateClass;
class DataCobwebClusterTreeClass;
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
/*C BaseDataCobwebClusterNodeStats  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the CobwebClusterNodeStats class definitions
**
**  REMARKS
**    Inheirits BaseDataClusterNode
*/
class BaseDataCobwebClusterNodeStats : public BaseDataClusterNode
{
public:
  VectorNumeric *DescriptionProbs;
  VectorNumeric *GoalProbs;
  VectorNumeric *ProbChanges;
  
  BaseDataCobwebClusterNodeStats();
  BaseDataCobwebClusterNodeStats(const BaseDataCobwebClusterNodeStats& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  void OutDescriptionInfo(ostream& out, 
			  DataCobwebClusterNodeStatsClass *nodeclass,
			  double cutoff,
			  String& prefix);
  void OutGoalInfo(ostream& out,
		   DataCobwebClusterNodeStatsClass *nodeclass,
		   String& prefix);
  
  double TestNodePrint(ostream& out,
		       BaseDataSetOfObjects& goals,
		       String& iname,
		       BaseDataInstance *instance,
		       DataInstanceClass *iclass,
		       DataCobwebClusterNodeStatsClass *nodeclass,
		       String& prefix);
  
  virtual ostream& PrintASCIINodeInfo(ostream& out,
				      String& prefix,
				      DataDirectedTreeClass *,
				      DataObjectClass *,
				      BaseDataSetOfInstances&,
				      DataSetOfInstancesClass&);
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataCobwebClusterNodeStatsClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataClusterNodeClass
*/
class DataCobwebClusterNodeStatsClass : public DataClusterNodeClass
{
  
public:
  ObjectList<String> *DescriptorNames;
  ObjectList<String> *GoalNames;

  DataCobwebClusterNodeStatsClass();
  DataCobwebClusterNodeStatsClass(const DataCobwebClusterNodeStatsClass& data);
  DataCobwebClusterNodeStatsClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataCobwebClusterTree  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the CobwebClusterTree class definitions
**
**  REMARKS
**    Inheirits BaseDataClusterTree
*/
class BaseDataCobwebClusterTree : public BaseDataClusterTree
{
protected:
  String SmallestNodeForAssignmentS;
  BaseDataReal *SmallestNodeForAssignmentR;
  double SmallestNodeForAssignment;
  double SmallestNodeSize;

  String testInstanceNamesS;
  BaseDataKeyWords testInstanceNames;
  String trainInstanceNamesS;
  BaseDataKeyWords trainInstanceNames;

  String matrixInstanceNamesS;

  String GroupProbsS;
  String SingleDescriptionS;
  String SingleMembershipS;

  String InGroupMeasureS;
  BaseDataDoubleVector *InGroupMeasure;
  String ExtraGroupMeasureS;
  BaseDataReal *ExtraGroupMeasure;

  BaseDataSetOfObjects Description;
  BaseDataSetOfObjects Goals;
  
  String measureAlgS;
  BaseDataAlgorithmOperation *measureAlg;
  String descriptionAlgS;
  BaseDataAlgorithmOperation *descriptionAlg;

  String cobwebTreeS;

  BaseDataDescriptionMatrix *DescriptionMatrix;
public:
  String AttributeListS;
  BaseDataSetOfInstances *Instances;
  BaseDataAlgorithmRun *Run;
  DataClusterTreeClass *TreeClass;
  DataCobwebClusterNodeStatsClass *NodeClass;

  BaseDataCobwebClusterTree();
  BaseDataCobwebClusterTree(const BaseDataCobwebClusterTree& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;

  String& getTrainListName();
  void setTrainListName(String& name);
  BaseDataAlgorithmOperation *getClusteringMeasure();
  BaseDataAlgorithmOperation *getDescriptionMeasure();
  double AttributeAndNode(BaseDataClusterNode& node);
  BaseDataKeyWords& getTrainInstanceNames();
  bool setTrainInstanceNames(BaseDataKeyWords& namesaskeys);
  BaseDataKeyWords& getTestInstanceNames();
  bool setTestInstanceNames(BaseDataKeyWords& namesaskeys);
  BaseDataSetOfObjects *getDescription();
  bool setDescription(BaseDataKeyWords& description,
		      BaseDataSetOfObjects* set);
  BaseDataSetOfObjects *getGoals();
  bool setGoals(BaseDataKeyWords& goals,
		BaseDataSetOfObjects* set);
  MatrixNumeric MatrixOfProbsInClusters(ObjectList<String>& inames,
					 BaseDataSetOfObjects& descrs,
					 BaseDataSetOfInstances& instances,
					 DataSetOfInstancesClass& instsclass);
  VectorNumeric DetermineMembershipInSons(ObjectList<String>& sons,
					   BaseDataCobwebClusterNodeStats& parent,
					   BaseDataInstance * tobeadded,
					   BaseDataLogical *membership,
					   DataInstanceClass * iclass,
					   MatrixNumeric *descrMatrix);
  DataClusterNodeClass *InitializeNodeClass(DataSetOfObjectsClass* classes);
  String DetermineBestFromNode(BaseDataClusterNode *node,
			       String& name, bool allownewnode, bool sizelimit,
			       DataClusterTreeClass *treeclass);
  bool ComputeClusteringMeasure(String& parentname,
				BaseDataInstance *tobeadded,
				ObjectList<String>& sons,
				DataCobwebClusterTreeClass *treeclass);
  String DetermineBestNode(ObjectList<String>& sons,bool allownewnode, bool sizelimit,
			   DataCobwebClusterTreeClass *treeclass);
  DataClusterTreeClass *SetUpGlobalInformation(BaseDataSetOfInstances* instances,
					       DataSetOfInstancesClass* instancesclasses,
					       BaseDataAlgorithmRun *run,
					       DataAlgorithmRunClass* rclass);
  BaseDataLogical *InitializeMembership();
  bool ComputeInstanceDescriptionMatrixFromParent(BaseDataClusterNode *parent,
						  DataCobwebClusterTreeClass *treeclass);
  bool ComputeInstanceDescriptionMatrix(BaseDataKeyWords *instlist,
					DataCobwebClusterTreeClass *treeclass);
  void InitializeRootNode(DataClusterTreeClass *treeclass);
  String getCobwebTreeName();
  void TransferClusterTree(BaseDataClusterTree *tree);
  virtual bool EvaluateWithCluster(DataCobwebClusterTreeClass *tclass,
				   BaseDataSetOfInstances *instances,
				   DataSetOfInstancesClass *instancesclasses,
				   BaseDataAlgorithmRun *run,
				   DataAlgorithmRunClass *rclass);
  void ResultPrintout(String& name, ObjectList<String> *sons, String& bestname, String& pre);

  virtual bool InitializeIncrementClusterTree(BaseDataSetOfInstances *instances,
					      DataSetOfInstancesClass *instancesclasses,
					      BaseDataAlgorithmRun *run,
					      DataAlgorithmRunClass *rclass);
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);

  bool AssignNValuedClassForNode(BaseDataInstance *instance,
				 String &bestnode, String& postfix,
				 DataCobwebClusterTreeClass *treeclass );
  ObjectList<String> ValidNodesToNValued(BaseDataSetOfInstances *instances,
					 DataCobwebClusterTreeClass *treeclass,
					 DataSetOfObjectsClass *classes);
  bool IsValidNode(BaseDataCobwebClusterNodeStats *nodestat);    
  void LevelValuesForInstance(BaseDataInstance *instance, 
			      BaseDataCobwebClusterNodeStats *parent, 
			      int level, int maxlevel,
			      BaseDataSetOfObjects *levelkeys,
			      DataCobwebClusterTreeClass *treeclass);
  BaseDataSetOfObjects *LevelKeySets(int maxlevel,DataSetOfObjectsClass *classes);
  void SetUpSinglePartitions(DataCobwebClusterTreeClass *treeclass,
			     BaseDataKeyWords *keynames,
			     DataNValuedClass *reference,
			     DataExactlyEqualPredicateClass *compareclass,
			     BaseDataSetOfObjects *instances,
			     DataSetOfObjectsClass *classes);
  void SetUpPartitions(DataCobwebClusterTreeClass *treeclass,
		       BaseDataSetOfObjects *instances,
		       BaseDataSetOfObjects *levelsets,
		       DataSetOfObjectsClass *classes);
};
/*C DataCobwebClusterTreeClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataClusterTreeClass
*/
class DataCobwebClusterTreeClass : public DataClusterTreeClass
{
  DataSetOfObjectsClass PredicateClassInfo;
  DataKeyWordsClass KeyWordClass;
  
public:
  String ClusterAssignmentBaseClassS;
  String ClusterNodeAssignmentClassS;
  DataNValuedClass *ClusterNodeAssignmentClass;
  String ClusterAssignmentName;
  DataSetOfInstancesClass *InstancesClass;
  DataAlgorithmRunClass *RunClass;
  DataSetOfObjectsClass *Classes;
  DataInstanceClass *InstanceClass;

  DataCobwebClusterTreeClass();
  DataCobwebClusterTreeClass(const DataCobwebClusterTreeClass& data);
  DataCobwebClusterTreeClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
  String& getNodeClassName();
  DataSetOfObjectsClass * getPredicateClassInfo();
  DataKeyWordsClass * getKeyWordClass();
  DataSetOfObjectsClass *PointerToAllowedClasses();
  DataNValuedClass *SetUpNValuedClass(ObjectList<String> &validsons,
				      String& baseclassS,
				      String& classnameS,
				      String& parametername,
				      BaseDataSetOfInstances *instances,
				      DataSetOfObjectsClass *classes);

  DataExactlyEqualPredicateClass *CreateComparePredicateClass(DataNValuedClass *reference,
							      DataSetOfObjectsClass *classes);
};
/*C BaseDataCobwebClusterTreeCreate  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the CobwebClusterTreeCreate class definitions
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataCobwebClusterTreeCreate : public BaseDataCobwebClusterTree
{
  String logicTypeS;
  String logicType;
  String trainInstanceNamesS;
  String descriptionNamesS;
  String goalNamesS;
  BaseDataAlgorithmOperation *measureAlg;
  
  MatrixNumeric *descrMatrix;
  MatrixNumeric *goalMatrix;

public:
  unsigned int NodeCount;
  
  BaseDataCobwebClusterTreeCreate();
  BaseDataCobwebClusterTreeCreate(const BaseDataCobwebClusterTreeCreate& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;

  void StartToAddInstanceToClusterTree(String& instname,
				       DataClusterTreeClass *treeclass);
  void AddToNextLevel(BaseDataClusterNode *parent,
		      BaseDataInstance * tobeadded,
		      BaseDataLogical *membership,
		      DataClusterTreeClass *treeclass);
  void AddInstanceToClusterNode(BaseDataClusterNode *parent,
				BaseDataInstance* instance,
				BaseDataLogical *membership,
				DataClusterTreeClass *treeclass);
  String DetermineBestNode(ObjectList<String> sons,
			   DataCobwebClusterTreeCreateClass *treeclass);
  BaseDataCobwebClusterNodeStats *AddInstanceToSons(String& bestnode,
						    BaseDataClusterNode *parent,
						    BaseDataInstance * tobeadded,
						    BaseDataLogical *membership,
						    DataClusterTreeClass *treeclass);
  virtual bool InitializeIncrementClusterTree(BaseDataSetOfInstances *instances,
					      DataSetOfInstancesClass *instancesclasses,
					      BaseDataAlgorithmRun *run,
					      DataAlgorithmRunClass *rclass);
  virtual bool BuildIncrementClusterTree(BaseDataSetOfInstances *instances,
					 DataSetOfInstancesClass *instancesclasses,
					 BaseDataAlgorithmRun *run,
					 DataAlgorithmRunClass *rclass);
};
/*C DataCobwebClusterTreeCreateClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataCobwebClusterTreeCreateClass : public DataCobwebClusterTreeClass
{
public:
  DataCobwebClusterTreeCreateClass();
  DataCobwebClusterTreeCreateClass(const DataCobwebClusterTreeCreateClass& data);
  DataCobwebClusterTreeCreateClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};







/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif




