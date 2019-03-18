/*  FILE     NumericObjects.cc
**  PACKAGE  NumericObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "NumericObjects" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
**  Version 1.5
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjects.hh"
#include "NumericObjects.hh"

/*S BaseDataNumeric
*/ 
/*F BaseDataNumeric() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataNumeric::BaseDataNumeric()
{
  Identification = NUMERIC_BASE_ID;
  SetType(NUMERIC_BASE_ID);
  NameTag = NUMERIC_BASE_NAME;
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataNumeric(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataNumeric::BaseDataNumeric(const BaseDataNumeric& data)
  : BaseDataObject(data)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . . .  Read  in BaseDataNumeric
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataNumeric::Read(istream& in, DataObjectClass* objc)
{
  bool result = BaseDataObject::Read(in,objc);
  //cout << "\n Inside BaseDataNumeric \n";
  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . . Read in BaseDataNumeric
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataNumeric::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);

  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . BaseDataNumeric
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataNumeric::print(ostream& out) const
{
  BaseDataObject::print(out);
  //cout << "Numeric Object ";
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . BaseDataNumeric
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataNumeric::Clone()
{
  BaseDataNumeric *obj = new BaseDataNumeric;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . BaseDataNumeric
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataNumeric::CopyClone(Identify *  obj)
{
  BaseDataNumeric *objfull = (BaseDataNumeric *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . BaseDataNumeric
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumeric::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  // The rest: result = result && Encode(buffer,-------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . BaseDataNumeric
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNumeric::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  // The rest: result = result && Decode(buffer,-------);

  return result;
}
/*F ans = operator==(obj) . . . . . . . . . . .  true if logic value the same
**
**  DESCRIPTION
**    obj: The logical object to compare
**    ans: true if the logical value (GetValue()) is the same.
**
**    The types of objects have to be exactly the same;
**
**  REMARKS
**
*/
bool BaseDataNumeric::operator==(BaseDataObject *obj)
{
  bool result = false;
  /*
  cout << "Numeric Compare: Types (";
  cout << obj->GetType() << ", " << GetType() << "), Distance (";
  cout << Distance(obj) << ")" << endl;
  */
  if(obj->GetType() == GetType())
    {
      if(Distance(obj) == 0.0)
        result = true;
    }
  return result;
}
/*F ans = operator>(obj) . . . . . . . . . . .  true if logic value the same
**
**  DESCRIPTION
**    obj: The logical object to compare
**    ans: true if the logical value (GetValue()) is the same.
**
**    The types of objects have to be exactly the same;
**
**  REMARKS
**
*/
bool BaseDataNumeric::operator>(BaseDataObject *obj)
{
  bool result = false;
  if(obj->GetType() == GetType())
    {
      if(Distance(obj) > 0.0)
        result = true;
    }
  else if(obj->GetType() > GetType())
    result = true;
    
  return result;
}
/*F ans = operator<(obj) . . . . . . . . . . .  true if logic value the same
**
**  DESCRIPTION
**    obj: The logical object to compare
**    ans: true if the logical value (GetValue()) is the same.
**
**    The types of objects have to be exactly the same;
**
**  REMARKS
**
*/
bool BaseDataNumeric::operator<(BaseDataObject *obj)
{
  return !(operator>(obj));
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool BaseDataNumeric::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << "(" << objc->NameTag << ") " << NameTag << " = ";  
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool BaseDataNumeric::WriteAsASCII(ostream&, DataObjectClass *)
{
  return true;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool BaseDataNumeric::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  out << "$(" << objc->NameTag << ") " << NameTag << " = $ ";
  out << endl;
  return true;
}


/*S DataNumericClass
 */
/*F DataNumericClass()  . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataNumericClass::DataNumericClass()
  : Width(15)
{
  NameTag = NUMERIC_BASE_NAME;
  Identification = NUMERIC_BASE_ID;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = NUMERIC_BASE_NAME;
} 
/*F DataNumericClass(data)  . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataNumericClass::DataNumericClass(const DataNumericClass& data)
  : DataObjectClass(data),
    Width(data.Width)
  // the rest
{
} 
 
/*F DataNumericClass(id,name,descr) . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataNumericClass::DataNumericClass(const int id, 
                                   const String& name,
                                   const String& descr)
  : DataObjectClass(id,name,descr)
{
  EncodeDecodeClass = name;
  SubClass = COREOBJECTS_BASE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . .  DataNumericClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataNumericClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  out << NameTag << "  ";
      
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . .  DataNumericClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataNumericClass, there is no further information.
**
**  REMARKS
**
*/
bool  DataNumericClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataObjectClass::Read(in,set);

  return result;
}
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . .  DataNumericClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataNumericClass::CopyClone(Identify *  objc)
{
  DataNumericClass *objcfull = (DataNumericClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . .  DataNumericClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataNumericClass::Clone()
{
  DataNumericClass* id = new DataNumericClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . .  DataNumericClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumericClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  result = result && Encode(buffer,Width);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . .  DataNumericClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNumericClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
  result = result && Decode(buffer,Width);

  return result;
}
/*F ans = WriteAsLine(out)  . . . . . . . . . . . . . . . . . DataObjectClass
**
**  DESCRIPTION
**    out: The output stream
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool DataNumericClass::WriteAsLine(ostream& out)
{
  out << NameTag << ": " << Description << endl;
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool DataNumericClass::WriteAsASCII(ostream& out)
{
  return DataObjectClass::WriteAsASCII(out);
}
/*F ans = WriteAsLatex(out) . . . . . . . . . . . . . . . . . DataObjectClass
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool DataNumericClass::WriteAsLatex(ostream& out)
{
  out << endl;
  out << "\\begin{verbatim}" << endl;
  print(out);
  out << endl << "\\{verbatim}" << endl;
  out << "\\\\" << endl;

  return true;
}

/*S BaseDataInteger
 */ 
/*F BaseDataInteger()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataInteger::BaseDataInteger()
{
  Identification = NUMERIC_INTEGER_ID;
  SetType(NUMERIC_INTEGER_ID);
  NameTag = NUMERIC_INTEGER_NAME;
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataInteger(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataInteger::BaseDataInteger(const BaseDataInteger& data)
  : BaseDataNumeric(data),
    Value(data.Value)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataInteger
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataInteger::Read(istream& in, DataObjectClass* objc)
{
  bool result = BaseDataNumeric::Read(in,objc);
  if (result) 
    {
      StreamObjectInput str(in,' ');
      String val = str.ReadNext();
      Value = val.ToInteger();
    }  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataInteger
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataInteger::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataNumeric::Read(in,objc,name);
  if (result) 
    {
      StreamObjectInput str(in,' ');
      String val = str.ReadNext();
      Value = val.ToInteger();
    }
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataInteger
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataInteger::print(ostream& out) const
{
  BaseDataNumeric::print(out);

  out << "Value: " << Value;
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataInteger
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataInteger::Clone()
{
  BaseDataInteger *obj = new BaseDataInteger;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataInteger
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataInteger::CopyClone(Identify * obj)
{
  BaseDataInteger *objfull = (BaseDataInteger *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataInteger
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInteger::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataNumeric::EncodeThis(buffer);
  result = result && Encode(buffer,Value);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataInteger
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInteger::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataNumeric::DecodeThis(buffer);
  result = result && Decode(buffer,Value);

  return result;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool BaseDataInteger::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataNumeric::WriteAsLine(out,objc);
  out << Value << endl;  
  return result;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool BaseDataInteger::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataNumeric::WriteAsASCII(out,objc);
  out << Value << " ";
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool BaseDataInteger::WriteAsLatex(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataNumeric::WriteAsLatex(out,objc);
  out << "$ " << Value;
  out << " $ \\\\" << endl;
  
  return result;
}

/*S DataIntegerClass
 */
/*F DataIntegerClass()  . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataIntegerClass::DataIntegerClass()
{
  NameTag = NUMERIC_INTEGER_NAME;
  Identification = NUMERIC_INTEGER_ID;
  SubClass = NUMERIC_BASE_NAME;
  EncodeDecodeClass = NUMERIC_INTEGER_NAME;
} 
/*F DataIntegerClass(data)  . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataIntegerClass::DataIntegerClass(const DataIntegerClass& data)
  : DataNumericClass(data)
{
} 
 
/*F DataIntegerClass(id,name,descr) . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataIntegerClass::DataIntegerClass(const int id, 
                                   const String& name,
                                   const String& descr)
  : DataNumericClass(id,name,descr)

{
  EncodeDecodeClass = NUMERIC_INTEGER_NAME;
  SubClass = NUMERIC_BASE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . .  DataIntegerClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataIntegerClass::print(ostream& out) const
{
  DataNumericClass::print(out);
  out << " Integer ";
      
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . .  DataIntegerClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataIntegerClass, there is no further information.
**
**  REMARKS
**
*/
bool DataIntegerClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataNumericClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . .  DataIntegerClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataIntegerClass::CopyClone(Identify *  objc)
{
  DataIntegerClass *objcfull = (DataIntegerClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . .  DataIntegerClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataIntegerClass::Clone()
{
  DataIntegerClass* id = new DataIntegerClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . .  DataIntegerClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataIntegerClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataNumericClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . .  DataIntegerClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataIntegerClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataNumericClass::DecodeThis(buffer);
  //  result = result && Decode(buffer,-----);

  return result;
}
/*S BaseDataReal
 */ 
/*F BaseDataReal()  . . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataReal::BaseDataReal()
{
  Identification = NUMERIC_REAL_ID;
  SetType(NUMERIC_REAL_ID);
  NameTag = NUMERIC_REAL_NAME;
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataReal(data)  . . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataReal::BaseDataReal(const BaseDataReal& data)
  : BaseDataNumeric(data),
    Value(data.Value)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . . . . .  Read in BaseDataReal
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataReal::Read(istream& in, DataObjectClass* objc)
{
  bool result = BaseDataNumeric::Read(in,objc);
  if ( result)
    {
      StreamObjectInput str(in,' ');
      String val = str.ReadNext();
      Value = val.ToFloat();
    }  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . . .  Read in BaseDataReal
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataReal::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataNumeric::Read(in,objc,name);
  if (result)
    {
      StreamObjectInput str(in,' ');
      String val = str.ReadNext();
      Value = val.ToFloat();
    }
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . .  BaseDataReal
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataReal::print(ostream& out) const
{
  BaseDataNumeric::print(out);
  out << "Value: " << Value;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .  BaseDataReal
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataReal::Clone()
{
  BaseDataReal *obj = new BaseDataReal;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .  BaseDataReal
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataReal::CopyClone(Identify * obj)
{
  BaseDataReal *objfull = (BaseDataReal *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . .  BaseDataReal
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataReal::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataNumeric::EncodeThis(buffer);
  result = result && Encode(buffer,Value);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . .  BaseDataReal
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataReal::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataNumeric::DecodeThis(buffer);
  result = result && Decode(buffer,Value);

  return result;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool BaseDataReal::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataNumeric::WriteAsLine(out,objc);
  out << Value << endl;  
  return result;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool BaseDataReal::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataNumeric::WriteAsASCII(out,objc);
  out << " " << Value << " ";
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool BaseDataReal::WriteAsLatex(ostream& out, DataObjectClass*objc)
{
  bool result = BaseDataNumeric::WriteAsLatex(out,objc);
  out << "$ " << Value;
  out << " $ \\\\" << endl;
  
  return result;
}

/*S DataRealClass
 */
/*F DataRealClass() . . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataRealClass::DataRealClass()
{
  NameTag = NUMERIC_REAL_NAME;
  Identification = NUMERIC_REAL_ID;
  SubClass = NUMERIC_BASE_NAME;
  EncodeDecodeClass = NUMERIC_REAL_NAME;
} 
/*F DataRealClass(data) . . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataRealClass::DataRealClass(const DataRealClass& data)
  : DataNumericClass(data)
  // the rest
{
} 
 
/*F DataRealClass(id,name,descr)  . . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataRealClass::DataRealClass(const int id, 
                             const String& name,
                             const String& descr)
  : DataNumericClass(id,name,descr)
{
  EncodeDecodeClass = NUMERIC_REAL_NAME;
  SubClass = NUMERIC_BASE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . . DataRealClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataRealClass::print(ostream& out) const
{
  DataNumericClass::print(out);
  out << " Real ";
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . . . . DataRealClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataRealClass, there is no further information.
**
**  REMARKS
**
*/
bool DataRealClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataNumericClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . . DataRealClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataRealClass::CopyClone(Identify *  objc)
{
  DataRealClass *objcfull = (DataRealClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . . DataRealClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataRealClass::Clone()
{
  DataRealClass* id = new DataRealClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . . DataRealClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataRealClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataNumericClass::EncodeThis(buffer);
  //result = result && Encode(buffer,Value);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . . DataRealClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataRealClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataNumericClass::DecodeThis(buffer);
  //result = result && Decode(buffer,Value);

  return result;
}

/*S Utilities
 */
 
/*F AddNumericClasses(set)  . . . . . . . . . .  add to DataSetOfObjectsClass
**
**  DESCRIPTION
**    set: The set of classes of objects to add the numeric classes to
**
**  REMARKS
**
*/
void AddNumericClasses(DataSetOfObjectsClass& set)
{
  String numdescr("Numeric Base Class");
  String intdescr("Integer Class");
  String realdescr("Real Class");
  
  DataNumericClass numclass(NUMERIC_BASE_ID,NUMERIC_BASE_NAME,numdescr);
  DataIntegerClass intclass(NUMERIC_INTEGER_ID,NUMERIC_INTEGER_NAME,intdescr);
  DataRealClass realclass(NUMERIC_REAL_ID,NUMERIC_REAL_NAME,realdescr);
  
  set.AddObjectClass(numclass);
  set.AddObjectClass(intclass);
  set.AddObjectClass(realclass);
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataNumericClass::BaseDataObjectExample()
{ 
  //cout << "Make Numeric Example\n";
  return (BaseDataObject *) new BaseDataNumeric();
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataIntegerClass::BaseDataObjectExample()
{ 
  //cout << "Make Integer Example\n";
  return (BaseDataObject *) new BaseDataInteger();
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataRealClass::BaseDataObjectExample()
{ 
  //cout << "Make Real Example\n";
  return (BaseDataObject *) new BaseDataReal();
}
/*S TopDecode
 */
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . .  DataNumericClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataNumericClass*& obj)
{
  obj = new DataNumericClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . .  DataIntegerClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataIntegerClass*& obj)
{
  obj = new DataIntegerClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . . DataRealClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataRealClass*& obj)
{
  obj = new DataRealClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataNumeric
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataNumeric*& obj)
{
  obj = new BaseDataNumeric;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataInteger
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataInteger*& obj)
{
  obj = new BaseDataInteger;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . .  BaseDataReal
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataReal*& obj)
{
  obj = new BaseDataReal;
  return obj->DecodeThis(buffer);
}
 
/*F InitialSetOfNumericEncodeDecodeRoutines() . . . . . . . . numeric objects
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialSetOfNumericEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataNumericClass,BaseDataNumeric,NUMERIC_BASE_NAME);
  EncodeDecodeRegisterClass(DataIntegerClass,BaseDataInteger,NUMERIC_INTEGER_NAME);
  EncodeDecodeRegisterClass(DataRealClass,BaseDataReal,NUMERIC_REAL_NAME);
}
/*S Operators
 */
 
/*F y = operator+(x)  . . . . . . . . . . . . . . . . . . . . BaseDataNumeric
**
**  DESCRIPTION
**    x: The number to add with
**    y: x added to the instance value
**
**  REMARKS
**
*/
BaseDataObject* BaseDataNumeric::operator+(const BaseDataNumeric* x) const
{
  if(x){}
  
  BaseDataNumeric *y = new BaseDataNumeric();
  return (BaseDataObject *) y;
}
/*F y = operator+(x)  . . . . . . . . . . . . . . . . . . . . BaseDataInteger
**
**  DESCRIPTION
**    x: The number to add with
**    y: x added to the instance value
**
**  REMARKS
**
*/
BaseDataObject* BaseDataInteger::operator+(const BaseDataNumeric* x) const
{
  BaseDataInteger *x1 = (BaseDataInteger *) x;
  BaseDataInteger *y = new BaseDataInteger();
  int ix = x1->GetValue() + GetValue();
  y->SetValue(ix);
  return (BaseDataObject *) y;
}
/*F y = operator+(x)  . . . . . . . . . . . . . . . . . . . . .  BaseDataReal
**
**  DESCRIPTION
**    x: The number to add with
**    y: x added to the instance value
**
**  REMARKS
**
*/
BaseDataObject* BaseDataReal::operator+(const BaseDataNumeric* x) const
{
  BaseDataReal *x1 = (BaseDataReal *) x;
  BaseDataReal *y = new BaseDataReal;
  double dx = x1->GetValue() + GetValue();
  y->SetValue(dx);

  return (BaseDataObject *) y;
}
/*F y = operator-(x)  . . . . . . . . . . . . . . . . . . . . BaseDataNumeric
**
**  DESCRIPTION
**    x: The number to add with
**    y: x subtracted from the instance value
**
**  REMARKS
**
*/
BaseDataObject* BaseDataNumeric::operator-(const BaseDataNumeric* x) const
{
  if(x){}
  BaseDataNumeric *y = new BaseDataNumeric();
  return (BaseDataObject *) y;
}
/*F y = operator-(x)  . . . . . . . . . . . . . . . . . . . . BaseDataInteger
**
**  DESCRIPTION
**    x: The number to add with
**    y: x subtracted from the instance value
**
**  REMARKS
**
*/
BaseDataObject* BaseDataInteger::operator-(const BaseDataNumeric* x) const
{
  BaseDataInteger *x1 = (BaseDataInteger *) x;
  BaseDataInteger *y = new BaseDataInteger();
  int ix = GetValue() - x1->GetValue();
  y->SetValue(ix);
  return (BaseDataObject *) y;
}
/*F y = operator-(x)  . . . . . . . . . . . . . . . . . . . . .  BaseDataReal
**
**  DESCRIPTION
**    x: The number to add with
**    y: x added to the instance value
**
**  REMARKS
**
*/
BaseDataObject* BaseDataReal::operator-(const BaseDataNumeric* x) const
{
  BaseDataReal *x1 = (BaseDataReal *) x;
  BaseDataReal *y = new BaseDataReal;
  double dx = GetValue() - x1->GetValue();
  
  y->SetValue(dx);

  return (BaseDataObject *) y;
}
/*F y = operator*(x)  . . . . . . . . . . . . . . . . . . . . BaseDataNumeric
**
**  DESCRIPTION
**    x: The number to add with
**    y: x multiplied by the instance value
**
**  REMARKS
**
*/
BaseDataObject* BaseDataNumeric::operator*(const BaseDataNumeric* x) const
{
  if(x){}
  BaseDataNumeric *y = new BaseDataNumeric();
  return (BaseDataObject *) y;
}
/*F y = operator*(x)  . . . . . . . . . . . . . . . . . . . . BaseDataInteger
**
**  DESCRIPTION
**    x: The number to add with
**    y: x multiplied by the instance value
**
**  REMARKS
**
*/
BaseDataObject* BaseDataInteger::operator*(const BaseDataNumeric* x) const
{
  BaseDataInteger *x1 = (BaseDataInteger *) x;
  BaseDataInteger *y = new BaseDataInteger();
  int ix = x1->GetValue() * GetValue();
  y->SetValue(ix);
  return (BaseDataObject *) y;
}
/*F y = operator*(x)  . . . . . . . . . . . . . . . . . . . . .  BaseDataReal
**
**  DESCRIPTION
**    x: The number to add with
**    y: x multiplied by the instance value
**
**  REMARKS
**
*/
BaseDataObject* BaseDataReal::operator*(const BaseDataNumeric* x) const
{
  BaseDataReal *x1 = (BaseDataReal *) x;
  BaseDataReal *y = new BaseDataReal;
  double dx = x1->GetValue() * GetValue();
  y->SetValue(dx);

  return (BaseDataObject *) y;
}
/*F y = operator/(x)  . . . . . . . . . . . . . . . . . . . . BaseDataNumeric
**
**  DESCRIPTION
**    x: The number to add with
**    y: instance value divided by x
**
**  REMARKS
**
*/
BaseDataObject* BaseDataNumeric::operator/(const BaseDataNumeric* x) const
{
  if(x){}
  BaseDataNumeric *y = new BaseDataNumeric();
  return (BaseDataObject *) y;
}
/*F y = operator/(x)  . . . . . . . . . . . . . . . . . . . . BaseDataInteger
**
**  DESCRIPTION
**    x: The number to add with
**    y: instance value divided by x
**
**  REMARKS
**
*/
BaseDataObject* BaseDataInteger::operator/(const BaseDataNumeric* x) const
{
  BaseDataInteger *x1 = (BaseDataInteger *) x;
  BaseDataInteger *y = new BaseDataInteger();
  int ix = GetValue() / x1->GetValue();
  y->SetValue(ix);
  return (BaseDataObject *) y;
}
/*F y = operator/(x)  . . . . . . . . . . . . . . . . . . . . .  BaseDataReal
**
**  DESCRIPTION
**    x: The number to add with
**    y: instance value divided by x
**
**  REMARKS
**
*/
BaseDataObject* BaseDataReal::operator/(const BaseDataNumeric* x) const
{
  BaseDataReal *x1 = (BaseDataReal *) x;
  BaseDataReal *y = new BaseDataReal;
  double dx = GetValue() / x1->GetValue();
  y->SetValue(dx);

  return (BaseDataObject *) y;
}
/*F f = GetValue()  . . . . . . . . . . . . . . . . . . . . . .  BaseDataReal
**
**  DESCRIPTION
**    f: The Real number (double) value of the object
**
**  REMARKS
**
*/
double BaseDataReal::GetValue() const
{
  return Value;
}
/*F i = GetValue()  . . . . . . . . . . . . . . . . . . . . . BaseDataInteger
**
**  DESCRIPTION
**    i: The integer value of the object
**
**  REMARKS
**
*/
int BaseDataInteger::GetValue() const
{
  return Value;
}
/*F SetValue(x) . . . . . . . . . . . . . . . . . . . . . . . BaseDataInteger
**
**  DESCRIPTION
**    x: The value to set the Real number object to
**
**  REMARKS
**
*/
void BaseDataInteger::SetValue(const int x)
{
  Value = x;
}
/*F SetValue(x) . . . . . . . . . . . . . . . . . . . . . . . .  BaseDataReal
**
**  DESCRIPTION
**    x: The number to set the Real number to
**
**  REMARKS
**
*/
void BaseDataReal::SetValue(const double x)
{
  Value = x;
}
  
/*S DistanceFunction
 */
 
/*F dist = Distance(x)  . . . . . . . . . . . . . . . . . . . BaseDataNumeric
**
**  DESCRIPTION
**    x,y: The numeric points
**    dist: The distance represented as a double
**
**  REMARKS
**
*/
double BaseDataNumeric::Distance(BaseDataObject* x)
{
  return 0.0;
}
/*F dist = Distance() . . . . . . . . . . . . . . . . . . . . BaseDataNumeric
**
**  DESCRIPTION
**    x: The numeric object
**    dist: The distance from zero (as a double)
**
**  REMARKS
**
*/
double BaseDataNumeric::Distance()
{
  return 0.0;
}
/*F dist = Distance(x)  . . . . . . . . . . . . . . . . . . . BaseDataInteger
**
**  DESCRIPTION
**    x,y: The numeric points
**    dist: The distance represented as a double
**
**  REMARKS
**
*/
double BaseDataInteger::Distance(BaseDataObject* x)
{
  BaseDataInteger *x1 = (BaseDataInteger *) x;
  BaseDataInteger *d = (BaseDataInteger *) operator-(x1);
  double dist = d->GetValue();
  delete d;
  return dist;
}
/*F dist = Distance() . . . . . . . . . . . . . . . . . . . . BaseDataInteger
**
**  DESCRIPTION
**    x: The numeric object
**    dist: The distance from zero (as a double)
**
**  REMARKS
**
*/
double BaseDataInteger::Distance()
{
  double dist = (double) GetValue();
  return dist;
}
/*F dist = Distance(x)  . . . . . . . . . . . . . . . . . . . .  BaseDataReal
**
**  DESCRIPTION
**    x,y: The numeric points
**    dist: The distance represented as a double
**
**  REMARKS
**
*/
double BaseDataReal::Distance(BaseDataObject* x)
{
  BaseDataReal *x1 = (BaseDataReal *) x;
  BaseDataReal *d = (BaseDataReal *) operator-(x1);
  double dist = d->GetValue();
  delete d;
  return dist;
}
/*F dist = Distance() . . . . . . . . . . . . . . . . . . . . .  BaseDataReal
**
**  DESCRIPTION
**    x: The numeric object
**    dist: The distance from zero (as a double)
**
**  REMARKS
**
*/
double BaseDataReal::Distance()
{
  double dist = GetValue();
  return dist;
}
