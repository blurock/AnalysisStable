/*  FILE     RuleSystemType.hh
**  PACKAGE  RuleSystem
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "RuleSystem" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_RULESYSTEMTYPE_HH
#define CoreObjects_RULESYSTEMTYPE_HH

class DataActionRuleClass;
class DataProductionSystemClass;
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

/*C BaseDataActionRule  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ActionRule class definitions
**
**  REMARKS
**    Inheirits BaseDataParameterizedFunction
*/
class BaseDataActionRule : public BaseDataParameterizedFunction
{
  BaseDataParameterizedFunction *Condition;
  BaseDataParameterSet *Actions;
  double CutOff;
public:
  BaseDataActionRule();
  BaseDataActionRule(const BaseDataActionRule& data);
  ~BaseDataActionRule();

  virtual bool ShouldActionBePerformed(BaseDataLogical *logical);
  bool AddAction(BaseDataParameterizedFunction *action);
  bool RemoveAction(String &action);
  BaseDataParameterizedFunction *getCondition();
  void setCondition(BaseDataParameterizedFunction *condition);

  BaseDataLogical *EvaluateCondition(DataActionRuleClass *cls,
				     BaseDataParameterSet *set,
				     BaseDataInstance *instance,
				     DataParameterSetClass *setclass,
				     DataInstanceClass *instclass);
  bool EvaluateAction(String &name,
		      DataActionRuleClass *cls,
		      BaseDataParameterSet *set,
		      BaseDataInstance *instance,
		      DataParameterSetClass *setclass,
		      DataInstanceClass *instclass);
  bool EvaluateAllActions(DataActionRuleClass *cls,
			  BaseDataParameterSet *set,
			  BaseDataInstance *instance,
			  DataParameterSetClass *setclass,
			  DataInstanceClass *instclass);
  bool InitializeRule(DataActionRuleClass *cls,
		      BaseDataParameterSet *globalparams);
  virtual BaseDataObject *operator()(DataObjectClass *cls,
				     BaseDataObject *x, DataObjectClass *xclass);
  virtual BaseDataObject *operator()(DataObjectClass *cls,
				     BaseDataObject *x, BaseDataObject *y,
				     DataObjectClass *xclass, DataObjectClass *yclass);

  STANDARD_VIRTUAL_METHODS_OBJECT;
};
/*C DataActionRuleClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataParameterizedFunctionClass
*/
class DataActionRuleClass : public DataParameterizedFunctionClass
{
  DataParameterizedFunctionClass *ConditionClass;
  DataParameterSetClass *ActionClass;

public:
  DataActionRuleClass();
  DataActionRuleClass(const DataActionRuleClass& data);
  DataActionRuleClass(const int id, 
		    const String& name,
		    const String& descr);
  DataParameterizedFunctionClass *getConditionClass();
  DataParameterSetClass *getActionClass();
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataExecuteActionRule  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ExecuteActionRule class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmObject
*/
class BaseDataExecuteActionRule : public BaseDataAlgorithmOperation
{
  String actionRuleS;
  BaseDataActionRule *actionRule;
  String TrainInstanceNamesS;
  BaseDataKeyWords *TrainInstanceNames;
  String MaxNodesS;
  BaseDataInteger *MaxNodes;
public:
  BaseDataExecuteActionRule();
  BaseDataExecuteActionRule(const BaseDataExecuteActionRule& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
};
/*C DataExecuteActionRuleClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmObjectClass
*/
class DataExecuteActionRuleClass : public DataAlgorithmOperationClass
{
public:
  DataExecuteActionRuleClass();
  DataExecuteActionRuleClass(const DataExecuteActionRuleClass& data);
  DataExecuteActionRuleClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataSetOfRules  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the SetOfRules class definitions
**
**  REMARKS
**    Inheirits BaseDataParameterSet
*/
class BaseDataSetOfRules : public BaseDataParameterSet
{
public:
  BaseDataSetOfRules();
  BaseDataSetOfRules(const BaseDataSetOfRules& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataSetOfRulesClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataParameterSetClass
*/
class DataSetOfRulesClass : public DataParameterSetClass
{
public:
  DataSetOfRulesClass();
  DataSetOfRulesClass(const DataSetOfRulesClass& data);
  DataSetOfRulesClass(const int id, 
		    const String& name,
		    const String& descr);
  DataSetOfObjectsClass*  PointerToAllowedClasses();
  STANDARD_VIRTUAL_METHODS_CLASS;
};
/*C BaseDataProductionSystemNode  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ProductionSystemNode class definitions
**
**  REMARKS
**    Inheirits BaseDataTreeNode
*/
class BaseDataProductionSystemNode : public BaseDataTreeNode
{
  BaseDataInstance *Data;
  double HeuristicValue;
  double Level;
public:
  double LogicCost;
  String RuleUsed;
  BaseDataSetOfObjects *RuleConditionValues;

  BaseDataProductionSystemNode();
  BaseDataProductionSystemNode(const BaseDataProductionSystemNode& data);
  ~BaseDataProductionSystemNode();
  bool InitializeDataOnNode(BaseDataInstance *instance);
  double GetHeuristicValue();
  void SetHeuristicValue(double value);
  double GetLevel();
  BaseDataInstance *GetData();
  void SetLevel(double value);
  bool CalculateTreeCost(String& parent, BaseDataDirectedTree *tree);
  
  STANDARD_VIRTUAL_METHODS_OBJECT
  virtual ostream& PrintASCIINodeInfo(ostream& out,
				      String& prefix,
				      DataDirectedTreeClass *,
				      DataObjectClass *,
				      BaseDataSetOfInstances&,
				      DataSetOfInstancesClass&);

};
/*C DataProductionSystemNodeClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataTreeNodeClass
*/
class DataProductionSystemNodeClass : public DataTreeNodeClass
{
  DataInstanceClass *DataClass;
public:
  DataProductionSystemNodeClass();
  DataProductionSystemNodeClass(const DataProductionSystemNodeClass& data);
  DataProductionSystemNodeClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataProductionSystem  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ProductionSystem class definitions
**
**  REMARKS
**    Inheirits BaseDataSetOfObjects
*/
class BaseDataProductionSystem : public BaseDataParameterizedExpression
{
  BaseDataSetOfRules *Rules;
  //BaseDataParameterizedFunction *GoalStateCondition;
  BaseDataDirectedTree *Tree;
  ObjectList<String> OpenNodes;
  ObjectList<String> GoalNodes;
  BaseDataSetOfObjects *Costs;
  String CostParameter;
  String GeneratedNodesS;
  String GeneratedNodeS;
  BaseDataKeyWords GoalResultNames;
public:
  unsigned int MaximumNumberOfGoals;
  unsigned int MaximumNumberOfNodes;
  bool BreadthFirst;
  bool DepthFirst;
  bool HeuristicSearch;

  BaseDataProductionSystem();
  BaseDataProductionSystem(const BaseDataProductionSystem& data);
  ~BaseDataProductionSystem();

  bool SystemInitialization(DataProductionSystemClass *prodclass,
			    BaseDataSetOfObjects *instance);
  bool SetUpRootNode(DataProductionSystemClass *prodclass,
		     BaseDataInstance *instance);
  bool RunProductionSystem(DataProductionSystemClass *prodclass,
			   BaseDataInstance *instance);
  bool AddToOpenOrGoalList(DataProductionSystemClass *prodclass,
			   BaseDataProductionSystemNode *node,
			   BaseDataProductionSystemNode *parent);
  bool IsAGoalNode(DataProductionSystemClass *prodclass,
		   BaseDataProductionSystemNode *node);
  bool SetHeuristicValueOnNode(BaseDataProductionSystemNode *newnode,
			       BaseDataProductionSystemNode *parent);
  bool OpenNodesNotEmpty();
  String ChooseNextOpenNode();
  bool ExpandNode(DataProductionSystemClass *prodclass,
		  BaseDataProductionSystemNode *node);
  bool ExpandGeneratedNodes(DataProductionSystemClass *prodclass,
			   BaseDataProductionSystemNode *node);
  bool EvaluateRuleConditions(DataProductionSystemClass *prodclass,
			      BaseDataProductionSystemNode *node);
  BaseDataProductionSystemNode *SetUpNewNode(DataProductionSystemClass *prodclass,
					     BaseDataProductionSystemNode *original);
  bool ApplyRuleToNode(DataProductionSystemClass *prodclass,
		       String& rulename,
		       BaseDataProductionSystemNode *node);
  void PrintSearchTree(ostream& out,
		       DataProductionSystemClass *prodclass,
		       BaseDataSetOfInstances *instances,
		       DataSetOfInstancesClass *instsclass);
  BaseDataParameterSet *ExtractProductionSystemParameters();
  STANDARD_VIRTUAL_METHODS_OBJECT
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataProductionSystemClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataProductionSystemClass : public DataParameterizedExpressionClass
{
  DataSetOfRulesClass *RulesClass;
  DataParameterizedFunctionClass *GoalStateConditionClass;
  DataProductionSystemNodeClass *NodeClass;
  DataDirectedTreeClass *TreeClass;
public:
  DataProductionSystemClass();
  DataProductionSystemClass(const DataProductionSystemClass& data);
  DataProductionSystemClass(const int id, 
		    const String& name,
		    const String& descr);
  DataSetOfRulesClass *getRulesClass();
  DataParameterizedFunctionClass *getGoalStateConditionClass();
  DataProductionSystemNodeClass *getNodeClass();
  DataDirectedTreeClass *getTreeClass();
  DataSetOfObjectsClass*  PointerToAllowedClasses();
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataProductionSystemSearch  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ProductionSystemSearch class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataProductionSystemSearch : public BaseDataAlgorithmOperation
{
  String ProductionSystemS;
  BaseDataProductionSystem *ProductionSystem;
  String TrainInstanceNamesS;
  BaseDataKeyWords *TrainInstanceNameKeys;
  ObjectList<String> TrainInstanceNames;
  String MaxNodesS;
  BaseDataInteger *MaxNodes;
public:
  BaseDataProductionSystemSearch();
  BaseDataProductionSystemSearch(const BaseDataProductionSystemSearch& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
};
/*C DataProductionSystemSearchClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataProductionSystemSearchClass : public DataAlgorithmOperationClass
{
public:
  DataProductionSystemSearchClass();
  DataProductionSystemSearchClass(const DataProductionSystemSearchClass& data);
  DataProductionSystemSearchClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataParameterizedProductionRun  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ParameterizedProductionRun class definitions
**
**  REMARKS
**    Inheirits BaseDataParameterizedFunction
*/
class BaseDataParameterizedProductionRun : public BaseDataParameterizedFunction
{
public:
  BaseDataParameterizedProductionRun();
  BaseDataParameterizedProductionRun(const BaseDataParameterizedProductionRun& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataParameterizedProductionRunClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataParameterizedFunctionClass
*/
class DataParameterizedProductionRunClass : public DataParameterizedFunctionClass
{
public:
  DataParameterizedProductionRunClass();
  DataParameterizedProductionRunClass(const DataParameterizedProductionRunClass& data);
  DataParameterizedProductionRunClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};


#endif
