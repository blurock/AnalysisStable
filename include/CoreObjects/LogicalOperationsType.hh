/*  FILE     LogicalOperationsType.hh
**  PACKAGE  LogicalOperations
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "LogicalOperations" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_LOGICALOPERATIONSTYPE_HH
#define CoreObjects_LOGICALOPERATIONSTYPE_HH

/*C BaseDataLogicalOperation  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the LogicalOperation class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataLogicalOperation : public BaseDataOperation
{
public:
  BaseDataLogicalOperation();
  BaseDataLogicalOperation(const BaseDataLogicalOperation& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataLogicalOperationClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataLogicalOperationClass : public DataOperationClass
{
public:
  DataLogicalOperationClass();
  DataLogicalOperationClass(const DataLogicalOperationClass& data);
  DataLogicalOperationClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataLogicalAND  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the LogicalAND class definitions
**
**  REMARKS
**    Inheirits BaseDataLogicalOperation
*/
class BaseDataLogicalAND : public BaseDataLogicalOperation
{
public:
  BaseDataLogicalAND();
  BaseDataLogicalAND(const BaseDataLogicalAND& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataLogicalANDClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataLogicalOperationClass
*/
class DataLogicalANDClass : public DataLogicalOperationClass
{
public:
  DataLogicalANDClass();
  DataLogicalANDClass(const DataLogicalANDClass& data);
  DataLogicalANDClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataLogicalOR  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the LogicalOR class definitions
**
**  REMARKS
**    Inheirits BaseDataLogicalOperation
*/
class BaseDataLogicalOR : public BaseDataLogicalOperation
{
public:
  BaseDataLogicalOR();
  BaseDataLogicalOR(const BaseDataLogicalOR& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataLogicalORClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataLogicalOperationClass
*/
class DataLogicalORClass : public DataLogicalOperationClass
{
public:
  DataLogicalORClass();
  DataLogicalORClass(const DataLogicalORClass& data);
  DataLogicalORClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataLogicalNOT  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the LogicalNOT class definitions
**
**  REMARKS
**    Inheirits BaseDataLogicalOperation
*/
class BaseDataLogicalNOT : public BaseDataLogicalOperation
{
public:
  BaseDataLogicalNOT();
  BaseDataLogicalNOT(const BaseDataLogicalNOT& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataLogicalNOTClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataLogicalOperationClass
*/
class DataLogicalNOTClass : public DataLogicalOperationClass
{
public:
  DataLogicalNOTClass();
  DataLogicalNOTClass(const DataLogicalNOTClass& data);
  DataLogicalNOTClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataNumericPredicate  . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the NumericPredicate class
**
**    The prerequisite for the 'Numeric' classes is the definition of:
**    - Distance(x,y): The distance between two objects
**    - Distance(x): The distance from a zero object
**    These distance functions give a double real number which is used
**    for the evaluation of the predicate function(BaseDataFuncReal1D).
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataNumericPredicate : public BaseDataOperation
{
  BaseDataFuncReal1D* PredicateFunction;
  DataLogicalClass* LogicClass;
  
public:
  BaseDataNumericPredicate();
  BaseDataNumericPredicate(const BaseDataNumericPredicate& data);
  BaseDataNumericPredicate(BaseDataFuncReal1D* func,
                           DataLogicalClass* log);
  ~BaseDataNumericPredicate();
  
  virtual BaseDataObject *operator()(const double x);
  STANDARD_VIRTUAL_OPERATION_METHODS;
  friend class DataNumericPredicateClass;
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataNumericPredicateClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataNumericPredicateClass : public DataOperationClass
{
  DataFuncReal1DClass* PredicateFunction;
  DataLogicalClass* LogicClass;
  
public:
  DataNumericPredicateClass();
  DataNumericPredicateClass(const DataNumericPredicateClass& data);
  DataNumericPredicateClass(const int id, 
                    const String& name,
                    const String& descr);
  friend class BaseDataNumericPredicate;
  STANDARD_VIRTUAL_METHODS_CLASS  
  virtual bool WriteAsLine(ostream&);
  virtual bool WriteAsASCII(ostream&);
  virtual bool WriteAsLatex(ostream&);
  void setPredicateFunction(DataFuncReal1DClass *func);
  void setLogicClass(DataLogicalClass *logclass);
};


/*C BaseDataExactlyEqualPredicate  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ExactlyEqualPredicate class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataExactlyEqualPredicate : public BaseDataOperation
{
  String parameterName;
  BaseDataObject *objectToCompare;
  DataLogicalClass *logicClass;
  
public:
  BaseDataExactlyEqualPredicate();
  BaseDataExactlyEqualPredicate(const BaseDataExactlyEqualPredicate& data);
  BaseDataExactlyEqualPredicate(String parameterName,
				BaseDataObject *objectToCompare,
				DataLogicalClass *lclass);
  void setParameterName(String& name) {
    parameterName = name;
  }
  void setLogicClass(DataLogicalClass *log){
    logicClass = (DataLogicalClass *) log->Clone();
  }
  void setCompareObject(BaseDataObject *obj){
    objectToCompare = (BaseDataObject *) obj->Clone();
  }
  String& getParameterName() {
    return parameterName;
  }
  BaseDataObject *getCompareObject(){
    return objectToCompare;
  }
  DataLogicalClass *getLogicClass(){
    return logicClass;
  }
  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_OPERATION_METHODS;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataExactlyEqualPredicateClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataExactlyEqualPredicateClass : public DataOperationClass
{
public:
  DataObjectClass *objectClass;
  DataLogicalClass *logicClass;
  
  DataExactlyEqualPredicateClass();
  DataExactlyEqualPredicateClass(const DataExactlyEqualPredicateClass& data);
  DataExactlyEqualPredicateClass(const int id, 
                    const String& name,
                    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
  virtual bool WriteAsLine(ostream&);
  virtual bool WriteAsASCII(ostream&);
  virtual bool WriteAsLatex(ostream&);
};
/*C BaseDataMemberOfKeyWord  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the MemberOfKeyWord class definitions
**
**  REMARKS
**    Inheirits BaseDataLogicalOperation
*/
class BaseDataMemberOfKeyWord : public BaseDataLogicalOperation
{
  String parameterName;
  String KeyWord;
public:
  BaseDataMemberOfKeyWord();
  BaseDataMemberOfKeyWord(const BaseDataMemberOfKeyWord& data);
  void setParameterName(String& name) {parameterName = name; }
  void setKeyWord(String& key) {KeyWord = key; }
  String& getParameterName() { return parameterName; }
  String& getKeyWord() { return KeyWord; }
  STANDARD_VIRTUAL_OPERATION_METHODS;
  STANDARD_VIRTUAL_METHODS_OBJECT;
};
/*C DataMemberOfKeyWordClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataLogicalOperationClass
*/
class DataMemberOfKeyWordClass : public DataLogicalOperationClass
{
public:
  DataMemberOfKeyWordClass();
  DataMemberOfKeyWordClass(const DataMemberOfKeyWordClass& data);
  DataMemberOfKeyWordClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataRealToLogic  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the RealToLogic class definitions
**
**  REMARKS
**    Inheirits BaseDataLogicalOperation
*/
class BaseDataRealToLogic : public BaseDataLogicalOperation
{
public:
  BaseDataRealToLogic();
  BaseDataRealToLogic(const BaseDataRealToLogic& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataRealToLogicClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataLogicalOperationClass
*/
class DataRealToLogicClass : public DataLogicalOperationClass
{
public:
  DataRealToLogicClass();
  DataRealToLogicClass(const DataRealToLogicClass& data);
  DataRealToLogicClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataRealPredicate  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the RealPredicate class definitions
**
**  REMARKS
**    Inheirits BaseDataRealFunctionParameterized
*/
class BaseDataRealPredicate : public BaseDataRealFunctionParameterized
{
public:
  BaseDataRealPredicate();
  BaseDataRealPredicate(const BaseDataRealPredicate& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataRealPredicateClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataRealFunctionParameterizedClass
*/
class DataRealPredicateClass : public DataRealFunctionParameterizedClass
{
  DataLogicalClass    *LogicClass;
public:
  DataRealPredicateClass();
  DataRealPredicateClass(const DataRealPredicateClass& data);
  DataRealPredicateClass(const int id, 
		    const String& name,
		    const String& descr);
  DataLogicalClass    *getLogicClass();
  STANDARD_VIRTUAL_METHODS_CLASS
};



/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
