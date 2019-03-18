/*  FILE     OperationObjectsType.hh
**  PACKAGE  OperationObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "OperationObjects" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_OPERATIONOBJECTSTYPE_HH
#define CoreObjects_OPERATIONOBJECTSTYPE_HH

 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
class DataOperationClass;
class DataNumericPredicateClass;

/*C BaseDataObject  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the Operation class 
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataOperation : public BaseDataObject
{
public:
  BaseDataOperation();
  BaseDataOperation(const BaseDataOperation& data);

  BaseDataObject* operator()(const String& x, BaseDataSetOfObjects& set,
                             const String& xclass, DataSetOfObjectsClass& setclass);
  BaseDataObject* operator()(const String& x, const String& y,
                             BaseDataSetOfObjects& set,
                             const String& xclass, const String& yclass,
                             DataSetOfObjectsClass& setclass);
  
  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_OPERATION_METHODS;
  virtual bool WriteAsLine(ostream& o, DataObjectClass *cls);
  virtual bool WriteAsASCII(ostream& o, DataObjectClass *cls);
  virtual bool WriteAsLatex(ostream& o, DataObjectClass  *cls);
};
/*C DataOperationClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**    This is the base function about a data type:
**       Identification: The numerical value of the type
**       NameTag: The ASCII name of the type
**       Description: The text description of the class
**
**  REMARKS
**
*/
class DataOperationClass : public DataObjectClass
{
public:
  DataOperationClass();
  DataOperationClass(const DataOperationClass& data);
  DataOperationClass(const int id, 
                    const String& name,
                    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
  virtual bool WriteAsLine(ostream& o);
  virtual bool WriteAsASCII(ostream& o);
  virtual bool WriteAsLatex(ostream& o);
};




#endif
