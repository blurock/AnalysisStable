/*  FILE     ClusterTreeType.hh
**  PACKAGE  ClusterTree
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "ClusterTree" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_CLUSTERTREETYPE_HH
#define CoreObjects_CLUSTERTREETYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
class DataClusterTreeClass;

/*C BaseDataCobwebClusterNode  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the CobwebClusterNode class definitions
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataClusterNode : public BaseDataTreeNode
{
  unsigned int Level;
  double InstanceCount;
public:
  BaseDataSetOfObjects ElementClusterAssignment;
  
  BaseDataClusterNode();
  BaseDataClusterNode(const BaseDataClusterNode& data);
  
  STANDARD_VIRTUAL_METHODS_OBJECT;
    
  BaseDataLogical * ElementInCluster(String& name);
  void AssignElementToCluster(String& name, BaseDataLogical *assignment);
  double NumberOfElementsInCluster();
  double ExtentInCluster(String& name);
  VectorNumeric *ExtentInCluster(ObjectList<String>& instnames);
  MatrixNumeric *ExtentInClusterAsMatrix(ObjectList<String>& instnames);
  double ProbabilityOfElement(String& name);
  void setInstanceCount(double count);
  double getInstanceCount();
  ObjectList<String> InstancesOnNode();
  void setLevel(unsigned int level);
  unsigned int getLevel();

  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataCobwebClusterNodeClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataClusterNodeClass : public DataTreeNodeClass
{
  DataLogicalClass LogicClass;
  
public:
  DataClusterNodeClass();
  DataClusterNodeClass(const DataClusterNodeClass& data);
  DataClusterNodeClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
  DataLogicalClass *getLogicClass();
  DataSetOfObjectsClass *PointerToAllowedClasses();
};

/*C BaseDataClusterTree  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ClusterTree class definitions
**
**  REMARKS
**    Inheirits BaseDataEvaluationTree
*/
class BaseDataClusterTree : public BaseDataEvaluationTree
{
  String maxLevelS;
  unsigned int maxLevel;

  String LogicType;
  double Count;
public:
  BaseDataClusterTree();
  BaseDataClusterTree(const BaseDataClusterTree& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
  MatrixNumeric CalculateInstancesOnSubNodes(String& parent,
					     ObjectList<String>& instancenames); 
  void InitializeRootNode(DataClusterTreeClass *treeclass);
  DataClusterNodeClass *InitializeNodeClass(DataSetOfObjectsClass* classes);
  BaseDataLogical *InitializeMembership();
  void AddInstanceToClusterNode(BaseDataClusterNode* node,
				BaseDataInstance* instance,
				BaseDataLogical *membership);
  BaseDataClusterNode *AddEmptyNode(BaseDataClusterNode *parent,
				    DataClusterNodeClass *nodeclass,
				    BaseDataInstance *instance,
				    BaseDataLogical *membership);
  BaseDataLogical *InitializeMembership(DataSetOfObjectsClass *classes);
  void setInstanceCount(double count);
  double getInstanceCount();
  String getLogicType();
  void TransferClusterTree(BaseDataClusterTree *tree);
  unsigned int getMaxLevel();

  virtual bool SetUpInput(BaseDataSetOfInstances* instances,
			  DataSetOfInstancesClass* instancesclass,
			  BaseDataAlgorithmRun* run,
			  DataAlgorithmRunClass* rclass);
  virtual bool CheckInput(BaseDataSetOfInstances*,
			  DataSetOfInstancesClass*,
			  BaseDataAlgorithmRun* run,
			  DataAlgorithmRunClass*);  
  bool InitializeIncrementClusterTree(BaseDataSetOfInstances *instances,
				      DataSetOfInstancesClass *instancesclasses,
				      BaseDataAlgorithmRun *run,
				      DataAlgorithmRunClass *rclass);
};
/*C DataClusterTreeClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataEvaluationTreeClass
*/
class DataClusterTreeClass : public DataEvaluationTreeClass
{
  String NodeClassS;
  DataClusterNodeClass *NodeClass;
public:
  DataClusterTreeClass();
  DataClusterTreeClass(const DataClusterTreeClass& data);
  DataClusterTreeClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;

  String& getNodeClassName();
  void setNodeClassName(String& name);

  DataClusterNodeClass *getNodeClass();
  void setNodeClass(DataClusterNodeClass *nodeclass);
  DataSetOfObjectsClass *PointerToAllowedClasses();
};


#endif
