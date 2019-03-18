/*  FILE     VectorOperationsType.hh
**  PACKAGE  VectorOperations
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "VectorOperations" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_VECTOROPERATIONSTYPE_HH
#define CoreObjects_VECTOROPERATIONSTYPE_HH

/*C BaseDataFormVector  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the FormVector class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataFormVector : public BaseDataOperation
{
  unsigned int CurrentPosition;
public:
  BaseDataFormVector();
  BaseDataFormVector(const BaseDataFormVector& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataFormVectorClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataFormVectorClass : public DataOperationClass
{
public:
  DataFormVectorClass();
  DataFormVectorClass(const DataFormVectorClass& data);
  DataFormVectorClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataVectorParameterizedFunction  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the VectorParameterizedFunction class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataVectorParameterizedFunction : public BaseDataOperation
{
public:
  BaseDataVectorParameterizedFunction();
  BaseDataVectorParameterizedFunction(const BaseDataVectorParameterizedFunction& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataVectorParameterizedFunctionClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataVectorParameterizedFunctionClass : public DataOperationClass
{
public:
  DataVectorParameterizedFunctionClass();
  DataVectorParameterizedFunctionClass(const DataVectorParameterizedFunctionClass& data);
  DataVectorParameterizedFunctionClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};


/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
