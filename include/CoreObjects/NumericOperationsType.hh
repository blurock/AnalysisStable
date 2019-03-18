/*  FILE     NumericOperationsType.hh
**  PACKAGE  NumericOperations
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "NumericOperations" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_NUMERICOPERATIONSTYPE_HH
#define CoreObjects_NUMERICOPERATIONSTYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
/*C BaseDataNumericOperation  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the NumericOperation class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataNumericOperation : public BaseDataOperation
{
public:
  BaseDataNumericOperation();
  BaseDataNumericOperation(const BaseDataNumericOperation& data);

  virtual   BaseDataObject* operator()(BaseDataObject* x, DataObjectClass* xclass);
  virtual   BaseDataObject* operator()(BaseDataObject* x, BaseDataObject* y,
                                       DataObjectClass* xclass, DataObjectClass* yclass);
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataNumericOperationClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataNumericOperationClass : public DataOperationClass
{
public:
  DataNumericOperationClass();
  DataNumericOperationClass(const DataNumericOperationClass& data);
  DataNumericOperationClass(const int id, 
		    const String& name,
		    const String& descr); 
  STANDARD_VIRTUAL_METHODS_CLASS;
};

/*C BaseDataNumOpPlus  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the NumOpPlus class definitions
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataNumOpPlus : public BaseDataOperation
{
public:
  BaseDataNumOpPlus();
  BaseDataNumOpPlus(const BaseDataNumOpPlus& data);

  virtual   BaseDataObject* operator()(BaseDataObject* x, DataObjectClass* xclass);
  virtual   BaseDataObject* operator()(BaseDataObject* x, BaseDataObject* y,
                                       DataObjectClass* xclass, DataObjectClass* yclass);
  STANDARD_VIRTUAL_METHODS_OBJECT  
};
/*C DataNumOpPlusClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataNumOpPlusClass : public DataOperationClass
{
public:
  DataNumOpPlusClass();
  DataNumOpPlusClass(const DataNumOpPlusClass& data);
  DataNumOpPlusClass(const int id, 
                    const String& name,
                    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataNumOpMinus  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the NumOpMinus class definitions
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataNumOpMinus : public BaseDataOperation
{
public:
  BaseDataNumOpMinus();
  BaseDataNumOpMinus(const BaseDataNumOpMinus& data);

  virtual   BaseDataObject* operator()(BaseDataObject* x, DataObjectClass* xclass);
  virtual   BaseDataObject* operator()(BaseDataObject* x, BaseDataObject* y,
                                       DataObjectClass* xclass, DataObjectClass* yclass);
  STANDARD_VIRTUAL_METHODS_OBJECT  
};
/*C DataNumOpMinusClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataNumOpMinusClass : public DataOperationClass
{
public:
  DataNumOpMinusClass();
  DataNumOpMinusClass(const DataNumOpMinusClass& data);
  DataNumOpMinusClass(const int id, 
                    const String& name,
                    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataNumOpMultiply  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the NumOpMultiply class definitions
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataNumOpMultiply : public BaseDataOperation
{
public:
  BaseDataNumOpMultiply();
  BaseDataNumOpMultiply(const BaseDataNumOpMultiply& data);

  virtual   BaseDataObject* operator()(BaseDataObject* x, DataObjectClass* xclass);
  virtual   BaseDataObject* operator()(BaseDataObject* x, BaseDataObject* y,
                                       DataObjectClass* xclass, DataObjectClass* yclass);
  STANDARD_VIRTUAL_METHODS_OBJECT  
};
/*C DataNumOpMultiplyClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataNumOpMultiplyClass : public DataOperationClass
{
public:
  DataNumOpMultiplyClass();
  DataNumOpMultiplyClass(const DataNumOpMultiplyClass& data);
  DataNumOpMultiplyClass(const int id, 
                    const String& name,
                    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataNumOpDivide  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the NumOpDivide class definitions
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataNumOpDivide : public BaseDataOperation
{
public:
  BaseDataNumOpDivide();
  BaseDataNumOpDivide(const BaseDataNumOpDivide& data);

  virtual   BaseDataObject* operator()(BaseDataObject* x, DataObjectClass* xclass);
  virtual   BaseDataObject* operator()(BaseDataObject* x, BaseDataObject* y,
                                       DataObjectClass* xclass, DataObjectClass* yclass);
  STANDARD_VIRTUAL_METHODS_OBJECT  
};
/*C DataNumOpDivideClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataNumOpDivideClass : public DataOperationClass
{
public:
  DataNumOpDivideClass();
  DataNumOpDivideClass(const DataNumOpDivideClass& data);
  DataNumOpDivideClass(const int id, 
                    const String& name,
                    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataNumericLineSegmentFunction  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the NumericLineSegmentFunction class definitions
**
**  REMARKS
**    Inheirits BaseDataNumericOperation
*/
class BaseDataNumericLineSegmentFunction : public BaseDataNumericOperation
{
public:
  BaseDataNumericLineSegmentFunction();
  BaseDataNumericLineSegmentFunction(const BaseDataNumericLineSegmentFunction& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataNumericLineSegmentFunctionClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataNumericOperationClass
*/
class DataNumericLineSegmentFunctionClass : public DataNumericOperationClass
{
public:
  DataNumericLineSegmentFunctionClass();
  DataNumericLineSegmentFunctionClass(const DataNumericLineSegmentFunctionClass& data);
  DataNumericLineSegmentFunctionClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataLogicToReal  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the LogicToReal class definitions
**
**  REMARKS
**    Inheirits BaseDataNumericOperation
*/
class BaseDataLogicToReal : public BaseDataNumericOperation
{
public:
  BaseDataLogicToReal();
  BaseDataLogicToReal(const BaseDataLogicToReal& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_OPERATION_METHODS;

};
/*C DataLogicToRealClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataNumericOperationClass
*/
class DataLogicToRealClass : public DataNumericOperationClass
{
public:
  DataLogicToRealClass();
  DataLogicToRealClass(const DataLogicToRealClass& data);
  DataLogicToRealClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

#endif
