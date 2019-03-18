/*  FILE     IteratorType.hh
**  PACKAGE  Iterator
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "Iterator" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_ITERATORTYPE_HH
#define CoreObjects_ITERATORTYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
class DataIteratorObjectClass;
class DataIterationSetClass;

/*C BaseDataObjectIterator  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ObjectIterator class definitions
**
**  REMARKS
**    Inheirits BaseDataSetOfObjects
*/
class BaseDataObjectIterator : public BaseDataSetOfObjects
{
  BaseDataKeyWords ObjectNames;
  
public:
  BaseDataObjectIterator();
  BaseDataObjectIterator(const BaseDataObjectIterator& data);

  STANDARD_VIRTUAL_METHODS_OBJECT

  virtual bool initializeIterator(DataIteratorObjectClass *cls);
  virtual BaseDataObject *nextIterator();
  virtual unsigned int numberRemaining();
  virtual BaseDataObject *randomObject(DataIteratorObjectClass *cls);
};
/*C DataObjectIteratorClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataObjectIteratorClass : public DataSetOfObjectsClass {
public:
  BaseDataKeyWords ParameterKeys;

  DataObjectIteratorClass();
  DataObjectIteratorClass(const DataObjectIteratorClass& data);
  DataObjectIteratorClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
  DataSetOfObjectsClass *PointerToAllowedClasses();  
};
/*C BaseDataNumericIterator  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the NumericIterator class definitions
**
**  REMARKS
**    Inheirits BaseDataObjectIterator
*/
class BaseDataNumericIterator : public BaseDataObjectIterator
{
protected:
  BaseDataNumeric *Begin;
  BaseDataNumeric *End;
  BaseDataNumeric *Increment;

  BaseDataNumeric *Current;
public:
  BaseDataNumericIterator();
  BaseDataNumericIterator(const BaseDataNumericIterator& data);
  BaseDataNumericIterator(BaseDataNumeric *B,
			  BaseDataNumeric *E,
			  BaseDataNumeric *I);

  STANDARD_VIRTUAL_METHODS_OBJECT
  virtual bool initializeIterator(DataObjectIteratorClass *cls);
  virtual BaseDataObject *nextIterator();
  virtual unsigned int numberRemaining();
  virtual BaseDataObject *randomObject(DataObjectIteratorClass *cls);
};
/*C DataNumericIteratorClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectIteratorClass
*/
class DataNumericIteratorClass : public DataObjectIteratorClass
{
public:
  DataNumericClass *NumericClass; 

  DataNumericIteratorClass();
  DataNumericIteratorClass(const DataNumericIteratorClass& data);
  DataNumericIteratorClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataRealIterator  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the RealIterator class definitions
**
**  REMARKS
**    Inheirits BaseDataNumericIterator
*/
class BaseDataRealIterator : public BaseDataNumericIterator
{
  double BeginD;
  double EndD;
  double IncrementD;
public:
  BaseDataRealIterator();
  BaseDataRealIterator(const BaseDataRealIterator& data);
  BaseDataRealIterator(double B,double E,double I);

  STANDARD_VIRTUAL_METHODS_OBJECT
  virtual bool initializeIterator(DataObjectIteratorClass *cls);
  virtual BaseDataObject *nextIterator();
  virtual unsigned int numberRemaining();
  virtual BaseDataObject *randomObject(DataObjectIteratorClass *cls);
};
/*C DataRealIteratorClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataNumericIteratorClass
*/
class DataRealIteratorClass : public DataNumericIteratorClass
{
public:
  DataRealIteratorClass();
  DataRealIteratorClass(const DataRealIteratorClass& data);
  DataRealIteratorClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataIterationSet  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the IterationSet class definitions
**
**  REMARKS
**    Inheirits BaseDataSetOfObjects
*/
class BaseDataIterationSet : public BaseDataSetOfObjects
{
  VectorSimple<String> *OrderedNames;
  VectorSimple<String> *CurrentNames;
  BaseDataSetOfObjects *Current;
public:
  BaseDataIterationSet();
  BaseDataIterationSet(const BaseDataIterationSet& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
  bool initialize(DataIterationSetClass *cls);
  BaseDataSetOfObjects *nextIterator(DataIterationSetClass *itercls);
  BaseDataSetOfObjects *getCurrent() { return Current; }
};
/*C DataIterationSetClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataIterationSetClass : public DataSetOfObjectsClass
{
public:
  DataSetOfObjectsClass *CurrentClass;
  DataIterationSetClass();
  DataIterationSetClass(const DataIterationSetClass& data);
  DataIterationSetClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
  DataSetOfObjectsClass *PointerToAllowedClasses();
};







#endif
