/*  FILE     ExpressionTreeType.hh
**  PACKAGE  ExpressionTree
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "ExpressionTree" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_EXPRESSIONTREETYPE_HH
#define CoreObjects_EXPRESSIONTREETYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
class BaseDataExpressionTree;
class DataExpressionTreeClass;

/*C BaseDataExpressionTreeNode  . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ExpressionTreeNode class definitions
**
**  REMARKS
**    Inheirits BaseDataTreeNode
*/
class BaseDataExpressionTreeNode : public BaseDataTreeNode
{
  String Object;
public:
  BaseDataExpressionTreeNode();
  BaseDataExpressionTreeNode(const BaseDataExpressionTreeNode& data);
  virtual BaseDataObject *Evaluate(BaseDataSetOfObjects *set,
				   DataSetOfObjectsClass *setclass,
				   BaseDataExpressionTree *tree,
				   DataExpressionTreeClass *ctree,
				   BaseDataSetOfObjects *attrs,
				   DataSetOfObjectsClass *attrclass);
    
  String& getAttribute();
  void SetAttribute(String& name);
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataExpressionTreeNodeClass . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataTreeNodeClass
*/
class DataExpressionTreeNodeClass : public DataTreeNodeClass
{
public:
  DataExpressionTreeNodeClass();
  DataExpressionTreeNodeClass(const DataExpressionTreeNodeClass& data);
  DataExpressionTreeNodeClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataExpressionTreeObject  . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ExpressionTreeObject class definitions
**
**  REMARKS
**    Inheirits BaseDataExpressionTreeNode
*/
class BaseDataExpressionTreeObject : public BaseDataExpressionTreeNode
{
public:
  BaseDataObject *ObjectObject;

  BaseDataExpressionTreeObject();
  BaseDataExpressionTreeObject(const BaseDataExpressionTreeObject& data);

  virtual BaseDataObject *Evaluate(BaseDataSetOfObjects *set,
				   DataSetOfObjectsClass *setclass,
				   BaseDataExpressionTree *tree,
				   DataExpressionTreeClass *ctree,
				   BaseDataSetOfObjects *attrs,
				   DataSetOfObjectsClass *attrclass);
  bool SetObject(BaseDataObject *obj);
  STANDARD_VIRTUAL_METHODS_OBJECT;
};
/*C DataExpressionTreeObjectClass . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataExpressionTreeNodeClass
*/
class DataExpressionTreeObjectClass : public DataExpressionTreeNodeClass
{
public:
  DataObjectClass *ObjectClass;

  DataExpressionTreeObjectClass();
  DataExpressionTreeObjectClass(const DataExpressionTreeObjectClass& data);
  DataExpressionTreeObjectClass(const int id, 
		    const String& name,
		    const String& descr);
  DataObjectClass *getObjectClass();
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataExpressionTreeOperation . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ExpressionTreeOperation class definitions
**
**  REMARKS
**    Inheirits BaseDataExpressionTreeNode
*/
class BaseDataExpressionTreeOperation : public BaseDataExpressionTreeNode
{
public:
  BaseDataExpressionTreeOperation();
  BaseDataExpressionTreeOperation(const BaseDataExpressionTreeOperation& data);
  BaseDataObject *Evaluate(BaseDataSetOfObjects *set,
			   DataSetOfObjectsClass *setclass,
			   BaseDataExpressionTree *tree,
			   DataExpressionTreeClass *ctree,
			   BaseDataSetOfObjects *attrs,
			   DataSetOfObjectsClass *attrclass);
  
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataExpressionTreeOperationClass  . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataExpressionTreeNodeClass
*/
class DataExpressionTreeOperationClass : public DataExpressionTreeNodeClass
{
public:
  DataExpressionTreeOperationClass();
  DataExpressionTreeOperationClass(const DataExpressionTreeOperationClass& data);
  DataExpressionTreeOperationClass(const int id, 
				   const String& name,
				   const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataExpressionTree  . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ExpressionTree class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataExpressionTree : public BaseDataOperation
{
  BaseDataDirectedTree Tree;
  ObjectNameClassPairs ParametersClass;
  BaseDataSetOfObjects Parameters;
  unsigned int IDCount;
  String LocalParameterKeyWord;
public:
  BaseDataExpressionTree();
  BaseDataExpressionTree(const BaseDataExpressionTree& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  void Initialisation();
  bool ParameterInList(String& name);
  BaseDataObject *GetParameter(String& name);
  ObjectNameClassPairs& getParameterClasses();
  ObjectList<String> *GetSons(String& nodename);
  bool ChangeParameter(BaseDataObject *parameter);
  bool ReadInExpressionNow(istream& in, DataExpressionTreeClass *ctree);
  bool ReadInExpressionArguments(istream& in,
				 String& rootop,
				 DataExpressionTreeClass *ctree);
  String& AddParameterNode(String& parameter, String& parent);
  String& AddVariableNameNode(String& variable, String& parent);
  String AddOperationNode(BaseDataOperation *oper,
			   String& parent);
  String AddOperationNode(BaseDataOperation *oper);

  String& AddExpressionNode(BaseDataExpressionTreeNode *node);
  String& AddExpressionNode(BaseDataExpressionTreeNode *node,
			   String& parent);
  bool CreateFunctionOrConstantNode(istream& in, String& parent, DataExpressionTreeClass *ctree, bool topnode);
  DataObjectClass *GetConstantTypeNode(String& name);
  String AddConstantObjectNode(istream& in, DataObjectClass *cls, String& parent);
  String AddConstantObjectNode(istream& in, DataObjectClass *cls, String& parent, bool topnode);
  BaseDataExpressionTreeNode *GetNode(String& name);
  BaseDataObject *GetNextNode(ObjectList<String>& sons,
			      BaseDataSetOfObjects *objects,
			      DataSetOfObjectsClass *objclass,
			      DataExpressionTreeClass *ctree,
			      BaseDataSetOfObjects *attrs,
			      DataSetOfObjectsClass *attrclass);
    STANDARD_VIRTUAL_OPERATION_METHODS;
  //virtual BaseDataObject *operator()(BaseDataObject *x, BaseDataObject *y, DataObjectClass *xclass, DataObjectClass *yclass);
  BaseDataObject *DoOperation(String& op, DataExpressionTreeClass *ctree,
			      BaseDataObject *obj);
  BaseDataObject *DoOperation(String& op, DataExpressionTreeClass *ctree,
			      BaseDataObject *obj1,
			      BaseDataObject *obj2);

  
};
/*C DataExpressionTreeClass . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataExpressionTreeClass : public DataOperationClass
{
  BaseDataSetOfObjects Operations;
  ObjectNameClassPairs OperationsClass;
public:
  DataExpressionTreeClass();
  DataExpressionTreeClass(const DataExpressionTreeClass& data);
  DataExpressionTreeClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
  bool AddOperation(BaseDataOperation *op);
  DataSetOfObjectsClass *PointerToAllowedClasses();
  BaseDataOperation *GetOperation(String& name);
  BaseDataOperation *GetFunctionNode(String& name);
  DataObjectClass *GetConstantTypeNode(String& name);
};
/*C BaseDataExpressionAlgorithm  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ExpressionAlgorithm class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataExpressionAlgorithm : public BaseDataAlgorithmOperation
{
  bool Instances;
  String VarsAndExpsS;
  BaseDataKeyWords *VarsAndExps;
  String instanceNameListS;
  BaseDataKeyWords *instanceNameList;
public:
  BaseDataExpressionAlgorithm();
  BaseDataExpressionAlgorithm(const BaseDataExpressionAlgorithm& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
  bool OverAttributes(String& variable,
		      BaseDataExpressionTree *etree,
		      DataExpressionTreeClass *ctree,
		      BaseDataSetOfInstances *instances,
		      DataSetOfInstancesClass *instclasses);
  bool LoopOverInstances(String& variable,
			 BaseDataExpressionTree *etree,
			 DataExpressionTreeClass *ctree,
			 BaseDataSetOfInstances *instances,
			 DataSetOfInstancesClass *instclasses);
};
/*C DataExpressionAlgorithmClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataExpressionAlgorithmClass : public DataAlgorithmOperationClass
{
public:
  DataExpressionAlgorithmClass();
  DataExpressionAlgorithmClass(const DataExpressionAlgorithmClass& data);
  DataExpressionAlgorithmClass(const int id, 
		    const String& name,
		    const String& descr);
  DataSetOfObjectsClass *PointerToAllowedClasses();
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataParameterizedExpression  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ParameterizedExpression class definitions
**
**  REMARKS
**    Inheirits BaseDataParameterizedFunction
*/
class BaseDataParameterizedExpression : public BaseDataParameterizedFunction
{
public:
  BaseDataParameterizedExpression();
  BaseDataParameterizedExpression(const BaseDataParameterizedExpression& data);
  virtual bool InsertParameter(BaseDataObject *obj);
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataParameterizedExpressionClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataParameterizedFunctionClass
*/
class DataParameterizedExpressionClass : public DataParameterizedFunctionClass
{
public:
  DataParameterizedExpressionClass();
  DataParameterizedExpressionClass(const DataParameterizedExpressionClass& data);
  DataParameterizedExpressionClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};


#endif
