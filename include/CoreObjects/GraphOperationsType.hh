/*  FILE     GraphOperationsType.hh
**  PACKAGE  GraphOperations
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "GraphOperations" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_GRAPHOPERATIONSTYPE_HH
#define CoreObjects_GRAPHOPERATIONSTYPE_HH

/*C BaseDataGraphNodePair  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the GraphNodePair class definitions
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataGraphNodePair : public BaseDataObject
{
public:
  String Node1S;
  String Node2S;
  BaseDataLogical *Value;

  BaseDataGraphNodePair();
  BaseDataGraphNodePair(const BaseDataGraphNodePair& data);
  void GenerateName();
  virtual bool operator==(BaseDataObject *pair);
  String& GetName1();
  String& GetName2();
  BaseDataLogical *getValue();
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataGraphNodePairClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataGraphNodePairClass : public DataObjectClass
{
  DataLogicalClass *LogicClass;
public:
  DataGraphNodePairClass();
  DataGraphNodePairClass(const DataGraphNodePairClass& data);
  DataGraphNodePairClass(const int id, 
			 const String& name,
			 const String& descr);
  DataLogicalClass *getLogicClass();
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataGraphNodePairs  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the GraphNodePairs class definitions
**
**  REMARKS
**    Inheirits BaseDataSetOfObjects
*/
class BaseDataGraphNodePairs : public BaseDataSetOfObjects
{
  BaseDataLogical *Value;
public:
  BaseDataGraphNodePairs();
  BaseDataGraphNodePairs(const BaseDataGraphNodePairs& data);
  virtual bool AddObject(BaseDataObject *obj);
  BaseDataLogical *getTotalValue();
  STANDARD_VIRTUAL_METHODS_OBJECT;
};
/*C DataGraphNodePairsClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataGraphNodePairsClass : public DataSetOfObjectsClass
{
  DataGraphNodePairClass *NodePairClass;
public:
  DataGraphNodePairsClass();
  DataGraphNodePairsClass(const DataGraphNodePairsClass& data);
  DataGraphNodePairsClass(const int id, 
		    const String& name,
		    const String& descr);
  DataGraphNodePairClass *getNodePairClass();
  DataSetOfObjectsClass *PointerToAllowedClasses();
  STANDARD_VIRTUAL_METHODS_CLASS;
};
/*C BaseDataNodeEdgeOperation  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the NodeEdgeOperation class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataNodeEdgeOperation : public BaseDataOperation
{
  BaseDataOperation *Operation;
  String VariableS;
  bool NodeOperation;
public:
  BaseDataNodeEdgeOperation();
  BaseDataNodeEdgeOperation(const BaseDataNodeEdgeOperation& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataNodeEdgeOperationClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataNodeEdgeOperationClass : public DataOperationClass
{
  DataOperationClass *OperationClass;
public:
  DataNodeEdgeOperationClass();
  DataNodeEdgeOperationClass(const DataNodeEdgeOperationClass& data);
  DataNodeEdgeOperationClass(const int id, 
		    const String& name,
		    const String& descr);
  DataOperationClass *getOperationClass();
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataGraphElementMatch  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the GraphElementMatch class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataGraphElementMatch : public BaseDataOperation
{
  bool NodeMatch;
  String MatchVariableS;
  String DescriptionVariableS;
  BaseDataOperation *Operation;
  double CutOff;
public:
  BaseDataGraphElementMatch();
  BaseDataGraphElementMatch(const BaseDataGraphElementMatch& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataGraphElementMatchClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataGraphElementMatchClass : public DataOperationClass
{
  DataOperationClass *OperationClass;
public:
  DataGraphElementMatchClass();
  DataGraphElementMatchClass(const DataGraphElementMatchClass& data);
  DataGraphElementMatchClass(const int id, 
		    const String& name,
		    const String& descr);
  DataOperationClass *getOperationClass();
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataGraphNeighbors  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the GraphNeighbors class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataGraphNeighbors : public BaseDataOperation
{
  String PairsVariableS;
  String MatchesVariableS;
public:
  BaseDataGraphNeighbors();
  BaseDataGraphNeighbors(const BaseDataGraphNeighbors& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataGraphNeighborsClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataGraphNeighborsClass : public DataOperationClass
{
public:
  DataGraphNeighborsClass();
  DataGraphNeighborsClass(const DataGraphNeighborsClass& data);
  DataGraphNeighborsClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataSimpleGraphCounts  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the SimpleGraphCounts class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataSimpleGraphCounts : public BaseDataOperation
{
  String NodeOperationS;
  bool NodeOperation;
  String NumberOfS;
  String CountRootS;
  String LogicDescriptionS;
  
public:
  BaseDataSimpleGraphCounts();
  BaseDataSimpleGraphCounts(const BaseDataSimpleGraphCounts& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataSimpleGraphCountsClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataSimpleGraphCountsClass : public DataOperationClass
{
public:
  DataSimpleGraphCountsClass();
  DataSimpleGraphCountsClass(const DataSimpleGraphCountsClass& data);
  DataSimpleGraphCountsClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataGraphNodePairsOperation  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the GraphNodePairsOperation class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataGraphNodePairsOperation : public BaseDataOperation
{
  String NumberOfMatchesS;
  String MatchValueS;
public:
  BaseDataGraphNodePairsOperation();
  BaseDataGraphNodePairsOperation(const BaseDataGraphNodePairsOperation& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataGraphNodePairsOperationClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataGraphNodePairsOperationClass : public DataOperationClass
{
public:
  DataGraphNodePairsOperationClass();
  DataGraphNodePairsOperationClass(const DataGraphNodePairsOperationClass& data);
  DataGraphNodePairsOperationClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};




/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
