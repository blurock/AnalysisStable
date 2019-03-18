/*  FILE     NumericObjectsType.hh
**  PACKAGE  NumericObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "NumericObjects" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_NUMERICOBJECTSTYPE_HH
#define CoreObjects_NUMERICOBJECTSTYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

 
class DataNumericClass;


/*C BaseDataNumeric  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the Numeric class definitions
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataNumeric : public BaseDataObject
{
public:
  BaseDataNumeric();
  BaseDataNumeric(const BaseDataNumeric& data);

  virtual BaseDataObject* operator+(const BaseDataNumeric* x) const;
  virtual BaseDataObject* operator-(const BaseDataNumeric* x) const;
  virtual BaseDataObject* operator*(const BaseDataNumeric* x) const;
  virtual BaseDataObject* operator/(const BaseDataNumeric* x) const;

  virtual double Distance();
  virtual double Distance(BaseDataObject* x);
  virtual bool operator==(BaseDataObject *obj);
  virtual bool operator>(BaseDataObject *obj);
  virtual bool operator<(BaseDataObject *obj);
  
  STANDARD_VIRTUAL_METHODS_OBJECT;

  virtual bool WriteAsLine(ostream& out, DataObjectClass *obj);
  virtual bool WriteAsASCII(ostream& out, DataObjectClass *obj);
  virtual bool WriteAsLatex(ostream& out, DataObjectClass  *obj);
};
/*C DataNumericClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataNumericClass : public DataObjectClass
{
  unsigned int Width;
public:
  DataNumericClass();
  DataNumericClass(const DataNumericClass& data);
  DataNumericClass(const int id, 
		   const String& name,
		   const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;

  virtual bool WriteAsLine(ostream& out);
  virtual bool WriteAsASCII(ostream& out);
  virtual bool WriteAsLatex(ostream& out);
};
 
class DataIntegerClass;

/*C BaseDataObject  . . . . . . . . . . . . . . . . . . . . . . . . . .	 data
**
**  DESCRIPTION
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataInteger : public BaseDataNumeric
{
  int Value;
public:
  BaseDataInteger();
  BaseDataInteger(const BaseDataInteger& data);

  virtual int GetValue() const;
  virtual void SetValue(const int x);
  
  virtual BaseDataObject* operator+(const BaseDataNumeric* x) const;
  virtual BaseDataObject* operator-(const BaseDataNumeric* x) const;
  virtual BaseDataObject* operator*(const BaseDataNumeric* x) const;
  virtual BaseDataObject* operator/(const BaseDataNumeric* x) const;

  virtual double Distance();
  virtual double Distance(BaseDataObject* x);

  STANDARD_VIRTUAL_METHODS_OBJECT;

  virtual bool WriteAsLine(ostream& out, DataObjectClass *obj);
  virtual bool WriteAsASCII(ostream& out, DataObjectClass *obj);
  virtual bool WriteAsLatex(ostream& out, DataObjectClass  *obj);

};
/*C DataIntegerClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataIntegerClass : public DataNumericClass
{
  
public:
  DataIntegerClass();
  DataIntegerClass(const DataIntegerClass& data);
  DataIntegerClass(const int id, 
		   const String& name,
		   const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
};
 
class DataRealClass;

/*C BaseDataObject  . . . . . . . . . . . . . . . . . . . . . . . . . .	 data
**
**  DESCRIPTION
**    This is the Real class definitions
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataReal : public BaseDataNumeric
{
  double Value;
  
public:
  BaseDataReal();
  BaseDataReal(const BaseDataReal& data);

  virtual double GetValue() const;
  virtual void SetValue(const double x);

  virtual BaseDataObject* operator+(const BaseDataNumeric* x) const;
  virtual BaseDataObject* operator-(const BaseDataNumeric* x) const;
  virtual BaseDataObject* operator*(const BaseDataNumeric* x) const;
  virtual BaseDataObject* operator/(const BaseDataNumeric* x) const;

  virtual double Distance();
  virtual double Distance(BaseDataObject* x);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream& out, DataObjectClass *objc);
  virtual bool WriteAsASCII(ostream& out, DataObjectClass *objc);
  virtual bool WriteAsLatex(ostream& out, DataObjectClass  *objc);

};
/*C DataRealClass . . . . . . . . . . . . . . .	 the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataRealClass : public DataNumericClass
{
public:
  DataRealClass();
  DataRealClass(const DataRealClass& data);
  DataRealClass(const int id, 
		const String& name,
		const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
};

#endif
