/*  FILE     LogicalObjectsType.hh
**  PACKAGE  LogicalObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "LogicalObjects" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
class DataNValuedClass;

#ifndef CoreObjects_LOGICALOBJECTSTYPE_HH
#define CoreObjects_LOGICALOBJECTSTYPE_HH

class DataLogicalClass;

/*C BaseDataObject  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the Logical class
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataLogical : public BaseDataObject
{
  double Value;
  
public:
  BaseDataLogical();
  BaseDataLogical(const BaseDataLogical& data);

  virtual void AND(const BaseDataLogical& val);
  virtual void OR(const BaseDataLogical& val);
  virtual void NOT();
  virtual double GetValue() const;
  virtual void SetValue(const double val);
  virtual void SetAbsoluteTrue();
  virtual void SetAbsoluteFalse();

  STANDARD_VIRTUAL_METHODS_OBJECT;
  
  virtual bool operator==(BaseDataObject *obj);
  virtual bool WriteAsLine(ostream &out, DataObjectClass *cls);
  virtual bool WriteAsASCII(ostream &out, DataObjectClass *cls);
  virtual bool WriteAsLatex(ostream &out, DataObjectClass  *cls);
};
/*C DataLogicalClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataLogicalClass : public DataObjectClass
{
public:
  DataLogicalClass();
  DataLogicalClass(const DataLogicalClass& data);
  DataLogicalClass(const int id, 
                    const String& name,
                    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
  virtual bool WriteAsLine(ostream& out);
  virtual bool WriteAsASCII(ostream& out);
  virtual bool WriteAsLatex(ostream& out);
};

/*C BaseDataNValued  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the NValued class definitions with the following 
**    virtual functions:
**    - Read(stream,objc): Read from ASCII stream (using objc for additional format info)
**    - Read(stream,objc,name): Read from ASCII stream (if the name of the object already known)
**    - Write(stream,objc): Write with formatting details
**    - Clone(),CopyClone(obj): Clone a copy
**    - EncodeThis(buffer),DecodeThis(buffer): Encode and Decode routines
**    - print(out): Standard default output routine
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataNValued : public BaseDataLogical
{
public:
  BaseDataNValued();
  BaseDataNValued(const BaseDataNValued& data);
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream& out, DataObjectClass *cls);
  virtual bool WriteAsASCII(ostream& out, DataObjectClass *cls);
  virtual bool WriteAsLatex(ostream& out, DataObjectClass  *cls);
};
/*C DataNValuedClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataNValuedClass : public DataLogicalClass
{
  
public:
  SearchableObjectListSimpleStringdouble NameValueCorrs;
  DataNValuedClass();
  DataNValuedClass(const DataNValuedClass& data);
  DataNValuedClass(const int id, 
                    const String& name,
                    const String& descr);

  String& FindNearestLogicalValue(const double val);
  bool IsValidName(String& name);

  STANDARD_VIRTUAL_METHODS_CLASS;
  virtual bool WriteAsLine(ostream& out);
  virtual bool WriteAsASCII(ostream& out);
  virtual bool WriteAsLatex(ostream& out);
};
 


/*C BaseDataContinuous  . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the Continuous class
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataContinuous : public BaseDataLogical
{
public:
  BaseDataContinuous();
  BaseDataContinuous(const BaseDataContinuous& data);
  STANDARD_VIRTUAL_METHODS_OBJECT
  virtual bool WriteAsLine(ostream &out, DataObjectClass *cls);
  virtual bool WriteAsASCII(ostream &out, DataObjectClass *cls);
  virtual bool WriteAsLatex(ostream &out, DataObjectClass  *cls);
};
/*C DataContinuousClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataContinuousClass : public DataLogicalClass
{

public:
  DataContinuousClass();
  DataContinuousClass(const DataContinuousClass& data);
  DataContinuousClass(const int id, 
                    const String& name,
                    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
 
#endif

