/*  FILE     ParameterizedFunctionType.hh
**  PACKAGE  ParameterizedFunction
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "ParameterizedFunction" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_PARAMETERIZEDFUNCTIONTYPE_HH
#define CoreObjects_PARAMETERIZEDFUNCTIONTYPE_HH

class DataParameterSetClass;
class DataRealFunctionParameterizedClass;
class BaseDataFuncReal1D;
class DataFuncReal1DClass;
class DataDescriptionExpressionsClass;
/*C BaseDataParameterSet  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ParameterSet class definitions
**
**  REMARKS
**    Inheirits BaseDataSetOfObjects
*/
class BaseDataParameterSet : public BaseDataSetOfObjects
{
  ObjectList<String> ParameterList;
public:
  BaseDataParameterSet();
  BaseDataParameterSet(const BaseDataParameterSet& data);

  virtual bool AddObject(BaseDataObject *obj);
  ObjectList<String>& OrderedListOfParameterNames();
  STANDARD_VIRTUAL_METHODS_OBJECT
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataParameterSetClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataParameterSetClass : public DataSetOfObjectsClass
{
public:
  BaseDataKeyWords ParameterSetKeys;

  DataParameterSetClass();
  DataParameterSetClass(const DataParameterSetClass& data);
  DataParameterSetClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
  DataSetOfObjectsClass *PointerToAllowedClasses();
  };


/*C BaseDataParameterizedFunction  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ParameterizedFunction class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataParameterizedFunction : public BaseDataOperation
{
  BaseDataParameterSet *ParameterSet;
  BaseDataOperation *Operation;
  bool ParametersWithOperation;
public:
  BaseDataParameterizedFunction();
  BaseDataParameterizedFunction(const BaseDataParameterizedFunction& data);
  virtual ~BaseDataParameterizedFunction();
  virtual bool InsertParameterSet();
  virtual bool InsertParameterSet(BaseDataParameterSet *objects);
  virtual bool InsertParameterSet(BaseDataParameterSet *objects, bool value);
  virtual bool InsertParameter(BaseDataObject *obj);
  void InsertParametersWithOperation();
  void DontInsertParametersWithOperation();
  STANDARD_VIRTUAL_OPERATION_METHODS;
  STANDARD_VIRTUAL_METHODS_OBJECT;
  BaseDataOperation *getOperation();
  BaseDataParameterSet *getParameterSet();
  void setParameterSet(BaseDataParameterSet *params);
  void setOperation(BaseDataOperation *op);
};
/*C DataParameterizedFunctionClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataParameterizedFunctionClass : public DataOperationClass
{
  DataParameterSetClass *ParameterClass;
  DataOperationClass *OperationClass;
  DataObjectClass *OutputClass;
public:
  BaseDataKeyWords FunctionKeys;

  DataParameterizedFunctionClass();
  DataParameterizedFunctionClass(const DataParameterizedFunctionClass& data);
  DataParameterizedFunctionClass(const int id, 
		    const String& name,
		    const String& descr);
  DataOperationClass *getOperationClass();  
  DataParameterSetClass *getParameterClass();
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataRealFunctionParameterized  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the RealFunctionParameterized class definitions
**
**  REMARKS
**    Inheirits BaseDataParameterizedFunction
*/
class BaseDataRealFunctionParameterized : public BaseDataOperation
{
  BaseDataFuncReal1D *Operation;
public:
  BaseDataRealFunctionParameterized();
  BaseDataRealFunctionParameterized(const BaseDataRealFunctionParameterized& data);

  STANDARD_VIRTUAL_OPERATION_METHODS;
  STANDARD_VIRTUAL_METHODS_OBJECT;
};
/*C DataRealFunctionParameterizedClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataParameterizedFunctionClass
*/
class DataRealFunctionParameterizedClass : public DataOperationClass
{
  DataFuncReal1DClass *OperationClass;
public:
  DataRealFunctionParameterizedClass();
  DataRealFunctionParameterizedClass(const DataRealFunctionParameterizedClass& data);
  DataRealFunctionParameterizedClass(const int id, 
		    const String& name,
		    const String& descr);
  DataFuncReal1DClass *getOperationClass();
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataParameterSetOperation  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ParameterSetOperation class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataParameterSetOperation : public BaseDataOperation
{
  unsigned int ParameterCount;
public:
  BaseDataParameterSetOperation();
  BaseDataParameterSetOperation(const BaseDataParameterSetOperation& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataParameterSetOperationClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataParameterSetOperationClass : public DataOperationClass
{
public:
  DataParameterSetOperationClass();
  DataParameterSetOperationClass(const DataParameterSetOperationClass& data);
  DataParameterSetOperationClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataParameterExtract  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ParameterExtract class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataParameterExtract : public BaseDataOperation
{
public:
  BaseDataParameterExtract();
  BaseDataParameterExtract(const BaseDataParameterExtract& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataParameterExtractClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataParameterExtractClass : public DataOperationClass
{
public:
  DataParameterExtractClass();
  DataParameterExtractClass(const DataParameterExtractClass& data);
  DataParameterExtractClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataDescriptionExpressions  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the DescriptionExpressions class definitions
**
**  REMARKS
**    Inheirits BaseDataParameterSet
*/
class BaseDataDescriptionExpressions : public BaseDataParameterizedFunction
{
  BaseDataParameterSet *Expressions;
  bool PostOperation;
public:
  BaseDataDescriptionExpressions();
  BaseDataDescriptionExpressions(const BaseDataDescriptionExpressions& data);
  BaseDataSetOfObjects *ComputeDescription(DataDescriptionExpressionsClass *descrclass,
					   BaseDataSetOfObjects * instance,
					   DataSetOfObjectsClass * instclass);
  BaseDataSetOfObjects *ComputeDescription(BaseDataSetOfObjects * instance,
					   DataSetOfObjectsClass * instclass);
  //bool InsertParameterSet(BaseDataParameterSet *objects);
  //bool InsertParameterSet();
  bool InsertParameter(BaseDataObject *object);
  STANDARD_VIRTUAL_OPERATION_METHODS;
  STANDARD_VIRTUAL_METHODS_OBJECT;
};
/*C DataDescriptionExpressionsClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataParameterSetClass
*/
class DataDescriptionExpressionsClass : public DataParameterizedFunctionClass
{
  DataParameterSetClass *ExpressionsClass;
  DataSetOfObjectsClass *ResultSetClass;
  DataObjectClass *BaseClass;
public:
  DataDescriptionExpressionsClass();
  DataDescriptionExpressionsClass(const DataDescriptionExpressionsClass& data);
  DataDescriptionExpressionsClass(const int id, 
		    const String& name,
		    const String& descr);
  DataParameterSetClass *getExpressionsClass();
  DataSetOfObjectsClass *getResultSetClass();
  DataObjectClass *getBaseClass();
  STANDARD_VIRTUAL_METHODS_CLASS;
};
/*C BaseDataDescriptionOperation  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the DescriptionOperation class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataDoOperation : public BaseDataOperation
{
public:
  BaseDataDoOperation();
  BaseDataDoOperation(const BaseDataDoOperation& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataDescriptionOperationClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataDoOperationClass : public DataOperationClass
{
public:
  DataDoOperationClass();
  DataDoOperationClass(const DataDoOperationClass& data);
  DataDoOperationClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataParametersInFunction  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ParametersInFunction class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataParametersInFunction : public BaseDataOperation
{
public:
  BaseDataParametersInFunction();
  BaseDataParametersInFunction(const BaseDataParametersInFunction& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataParametersInFunctionClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataParametersInFunctionClass : public DataOperationClass
{
public:
  DataParametersInFunctionClass();
  DataParametersInFunctionClass(const DataParametersInFunctionClass& data);
  DataParametersInFunctionClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};


/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
