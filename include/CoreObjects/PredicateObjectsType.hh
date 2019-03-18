/*  FILE     PredicateObjectsType.hh
**  PACKAGE  PredicateObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "PredicateObjects" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_PREDICATEOBJECTSTYPE_HH
#define CoreObjects_PREDICATEOBJECTSTYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
class DataPredicateClass;
class DataDescriptionClass;
class DataLogicSetClass;
class BaseDataLogicDescription;
class DataLogicDescriptionClass;
class DataPartitionClass;
class DataPartitionTableClass;
class DataConjunctionClass;
class DataConjunctionClass;
class DataSetOfLogicDescriptionsClass;
class DataDescriptionExpressionsClass;
/*C BaseDataPredicate . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the Predicate class definitions 
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataPredicate : public BaseDataOperation
{
  String Logic;
  String Parameter;
  BaseDataOperation* Operation;
  
public:
  BaseDataPredicate();
  BaseDataPredicate(const BaseDataPredicate& data);
  BaseDataPredicate(const String& name,
		    const String& var,
		    const String& logic,
		    BaseDataOperation *op);
  ~BaseDataPredicate();
  void setParameters(const String& name,
		     const String& var,
		     const String& logic,
		     BaseDataOperation *op);
  BaseDataPredicate& operator=(BaseDataPredicate& pred);
  
  virtual BaseDataObject *operator()(BaseDataObject* obj,
				     DataObjectClass *objclass);
  virtual BaseDataObject *operator()(BaseDataObject* log,
				     BaseDataObject* obj,
				     DataObjectClass *logclass,
				     DataObjectClass *objclass);
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataPredicateClass  . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataPredicateClass : public DataOperationClass
{
  DataOperationClass *OpClass;
  
public:
  DataPredicateClass();
  DataPredicateClass(const DataPredicateClass& data);
  DataPredicateClass(const int id, 
		    const String& name,
		    const String& descr);
  DataOperationClass *OperationClass();
  STANDARD_VIRTUAL_METHODS_CLASS;
  void setOpClass(DataOperationClass *op);
  virtual bool WriteAsLine(ostream&);
  virtual bool WriteAsASCII(ostream&);
  virtual bool WriteAsLatex(ostream&);
};

/*C BaseDataDescription . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the Description class
**
**  REMARKS
**    Inheirits BaseDataSetOfObjects
*/
class BaseDataDescription : public BaseDataSetOfObjects
{
public:
  BaseDataDescription();
  BaseDataDescription(const BaseDataDescription& data);
  BaseDataDescription(BaseDataSetOfObjects * objects, BaseDataKeyWords& names);
  BaseDataLogicDescription *ComputeLogicDescription(DataDescriptionClass *descrclass,
						    BaseDataSetOfObjects * instance,
						    DataSetOfObjectsClass * instclass);

  bool AddPredicate(BaseDataPredicate *pred);
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataDescriptionClass  . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataDescriptionClass : public DataSetOfObjectsClass
{
  DataLogicDescriptionClass *LogicalDescriptionClass;
public:
  DataDescriptionClass();
  DataDescriptionClass(const DataDescriptionClass& data);
  DataDescriptionClass(const int id, 
		    const String& name,
		    const String& descr);
  DataLogicDescriptionClass *getLogicalDescriptionClass();
  STANDARD_VIRTUAL_METHODS_CLASS;
  virtual DataSetOfObjectsClass *PointerToAllowedClasses();    
};
/*C BaseDataLogicDescription  . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the LogicDescription class
**
**  REMARKS
**    Inheirits BaseDataSetOfObjects
*/
class BaseDataLogicDescription : public BaseDataSetOfObjects
{
public:
  BaseDataLogicDescription();
  BaseDataLogicDescription(const BaseDataLogicDescription& data);

  ObjectList<double>& LogicValues();
  bool AddLogicInstanceSet(BaseDataLogical *logic,
			   DataLogicalClass *logclass,
			   BaseDataSetOfInstances* instances,
			   DataSetOfInstancesClass* instsclass,
			   ObjectList<String>& descrnames,
			   BaseDataSetOfObjects * instance,
			   DataSetOfObjectsClass * instclass);
  bool AddLogicInstanceSet(BaseDataLogical *logic,
			   DataLogicalClass *logclass,
			   BaseDataDescription *description,
			   DataDescriptionClass *descrclass,
			   BaseDataSetOfObjects * instance,
			   DataSetOfObjectsClass * instclass);
  
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataLogicDescriptionClass . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataLogicDescriptionClass : public DataSetOfObjectsClass
{
  DataLogicalClass *LogicClass;
public:
  DataLogicDescriptionClass();
  DataLogicDescriptionClass(const DataLogicDescriptionClass& data);
  DataLogicDescriptionClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
  DataLogicalClass *getLogicClass();
  virtual DataSetOfObjectsClass *PointerToAllowedClasses();  
};

/*C BaseDataSetOfLogicDescriptions  . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the SetOfLogicDescriptions class definitions
**
**  REMARKS
**    Inheirits BaseDataSetOfObjects
*/
class BaseDataSetOfLogicDescriptions : public BaseDataSetOfObjects
{
public:
  BaseDataSetOfLogicDescriptions();
  BaseDataSetOfLogicDescriptions(const BaseDataSetOfLogicDescriptions& data);

  bool AddLogicalObjects(BaseDataLogical *logic,
			 DataLogicalClass *logclass,
			 DataDescriptionClass* descrclass,
			 BaseDataSetOfInstances* instances,
			 DataSetOfInstancesClass* instsclass,
			 ObjectList<String>& instnames,
			 ObjectList<String>& descrnames);
  bool AddLogicalObject(BaseDataLogical *logic,
			DataLogicalClass *logclass,
			BaseDataSetOfInstances* instances,
			DataSetOfInstancesClass* instsclass,
			ObjectList<String>& descrnames,
			DataDescriptionClass*,
			BaseDataInstance* instance,
			DataInstanceClass* instclass);
  BaseDataLogical *GetLogicValue(const String& instance, const String& predicate);
  
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataSetOfLogicDescriptionsClass . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataSetOfLogicDescriptionsClass : public DataSetOfObjectsClass
{
  DataLogicDescriptionClass LogicDescription;
  
public:
  DataSetOfLogicDescriptionsClass();
  DataSetOfLogicDescriptionsClass(const DataSetOfLogicDescriptionsClass& data);
  DataSetOfLogicDescriptionsClass(const int id, 
		    const String& name,
		    const String& descr);
  DataLogicDescriptionClass *getLogicDescription();
  
  STANDARD_VIRTUAL_METHODS_CLASS;
  virtual DataSetOfObjectsClass *PointerToAllowedClasses();  
};

/*C BaseDataConjunction . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the Conjunction class
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataConjunction : public BaseDataOperation
{
  BaseDataDescription LogicalOperations;
  
public:
  BaseDataConjunction();
  BaseDataConjunction(const BaseDataConjunction& data);
  BaseDataConjunction(const BaseDataDescription& data);
  BaseDataConjunction* CreateConjunction(BaseDataSetOfObjects* set, BaseDataKeyWords* conjkeys);
  
  virtual BaseDataObject *operator()(BaseDataObject* log,
				     BaseDataObject* obj,
				     DataObjectClass *logclass,
				     DataObjectClass *objclass);
  double NumberOfElements(ObjectList<String>& instnames,
			  BaseDataLogical* logical,
			  DataLogicalClass* logclass,
			  BaseDataSetOfLogicDescriptions& ldescrs,
			  DataSetOfLogicDescriptionsClass& ldescrsclass);
  
  bool AddPredicate(BaseDataPredicate *pred);
  BaseDataKeyWords& KeyWordsFromConjunction();
  
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataConjunctionClass  . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataConjunctionClass : public DataOperationClass
{
  DataDescriptionClass LogicalOperationsClass;
  
public:
  DataConjunctionClass();
  DataConjunctionClass(const DataConjunctionClass& data);
  DataConjunctionClass(const int id, 
		    const String& name,
		    const String& descr);

  DataDescriptionClass *LogicalOperationsClassPointer();

  STANDARD_VIRTUAL_METHODS_CLASS;
};

/*C BaseDataDisjunction . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the Disjunction class
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataDisjunction : public BaseDataOperation
{
  BaseDataDescription LogicalOperations;
  
public:
  BaseDataDisjunction();
  BaseDataDisjunction(const BaseDataDisjunction& data);
  BaseDataDisjunction(const BaseDataDescription& data);
  BaseDataDisjunction* CreateDisjunction(BaseDataSetOfObjects* set, 
					 BaseDataKeyWords* conjkeys);
  bool AddPredicate(BaseDataPredicate *pred);
  virtual BaseDataObject *operator()(BaseDataObject* log,
				     BaseDataObject* obj,
				     DataObjectClass *logclass,
				     DataObjectClass *objclass);
  double NumberOfElements(BaseDataLogical *log,
			  BaseDataSetOfInstances *instances,
			  DataLogicalClass *lclass,
			  DataSetOfInstancesClass *instclass,
			  ObjectList<String>& instnames);
  BaseDataKeyWords& KeyWordsFromDisjunction();
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataDisjunctionClass  . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataDisjunctionClass : public DataOperationClass
{
  DataDescriptionClass LogicalOperationsClass;
  
public:
  DataDisjunctionClass();
  DataDisjunctionClass(const DataDisjunctionClass& data);
  DataDisjunctionClass(const int id, 
		       const String& name,
		       const String& descr);

  DataDescriptionClass *LogicalOperationsClassPointer();
  STANDARD_VIRTUAL_METHODS_CLASS;
  BaseDataObject *operator()(BaseDataObject* log,
			     BaseDataObject* obj,
			     DataObjectClass *lclass,
			     DataObjectClass *objclass);

};
/*C BaseDataPartition . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the Partition class
**
**  REMARKS
**    Inheirits BaseDataLogicDescription
*/
class BaseDataPartition : public BaseDataKeyWords
{
public:
  BaseDataPartition();
  BaseDataPartition(const BaseDataPartition& data);
  BaseDataPartition(const BaseDataKeyWords& data);
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataPartitionClass  . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataLogicDescriptionClass
*/
class DataPartitionClass : public DataKeyWordsClass
{
public:
  DataPartitionClass();
  DataPartitionClass(const DataPartitionClass& data);
  DataPartitionClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataPartitionTable  . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the PartitionTable class
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataPartitionTable : public BaseDataObject
{
  BaseDataPartition Columns;
  BaseDataPartition Rows;
public:
  BaseDataPartitionTable();
  BaseDataPartitionTable(const BaseDataPartitionTable& data);
  BaseDataPartitionTable(BaseDataKeyWords& columns,
			 BaseDataKeyWords& rows);  
  BaseDataPartitionTable(BaseDataSetOfObjects* instances,
			 String& partition);
  void AddLogicalObjects(BaseDataSetOfInstances *instances,
			 DataSetOfInstancesClass *instclass,
			 ObjectList<String>& instnames);
  void CalculateFromLogDesc(MatrixNumeric* mat,
			    BaseDataLogical *result,
			    const String& instance,
			    BaseDataSetOfLogicDescriptions& descr,
			    BaseDataLogical *condition,
			    bool addin);
  MatrixNumeric *CalculatePartitionMatrixFromSet(BaseDataSetOfLogicDescriptions& descr,
						 BaseDataSetOfInstances* instances,
						 DataSetOfInstancesClass* instclass,
						 DataSetOfLogicDescriptionsClass&,
						 BaseDataConjunction *conj,
						 DataConjunctionClass *,
						 ObjectList<String>& instnames);
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);  
};
/*C DataPartitionTableClass . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataPartitionTableClass : public DataObjectClass
{
  DataPartitionClass Classes;
  ObjectNameClassPairs ColumnPairs;
  
public:
  DataPartitionTableClass();
  DataPartitionTableClass(const DataPartitionTableClass& data);
  DataPartitionTableClass(const int id, 
		    const String& name,
		    const String& descr);

  DataPartitionClass * ClassDescriptions();  
  ObjectNameClassPairs * GetColumnPairs();
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataLogicalDescriptionCompare  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the LogicalDescriptionCompare class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataLogicalDescriptionCompare : public BaseDataOperation
{
  bool ANDElement;
  bool ORSet;

public:
  BaseDataLogicalDescriptionCompare();
  BaseDataLogicalDescriptionCompare(const BaseDataLogicalDescriptionCompare& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_OPERATION_METHODS;
BaseDataLogical *CompareLogicalDescriptions(BaseDataLogicDescription *descr1,
					    BaseDataLogicDescription *descr2,
					    DataLogicDescriptionClass *logdclass1,
					    DataLogicDescriptionClass *logdclass2);

};
/*C DataLogicalDescriptionCompareClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataLogicalDescriptionCompareClass : public DataOperationClass
{
public:
  DataLogicalDescriptionCompareClass();
  DataLogicalDescriptionCompareClass(const DataLogicalDescriptionCompareClass& data);
  DataLogicalDescriptionCompareClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

#endif



