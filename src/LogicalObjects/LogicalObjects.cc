/*  FILE     LogicalObjects.cc
**  PACKAGE  LogicalObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "LogicalObjects" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
**  Version 1.5
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjects.hh"
#include "LogicalObjects.hh"

/*S BaseDataLogical
 */ 
/*F BaseDataLogical() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataLogical::BaseDataLogical()
{
  Identification = LOGICAL_BASE_ID;
  NameTag = LOGICAL_BASE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataLogical(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataLogical::BaseDataLogical(const BaseDataLogical& data)
  : BaseDataObject(data),
    Value(data.Value)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . . . . Read in BaseDataLogical
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**    Note that 'Value' is not read-in in this routine.
**    This is left for the classes that inherit this class.
**
**  REMARKS
**
*/
bool BaseDataLogical::Read(istream& in, DataObjectClass* objc)
{
  bool result = BaseDataLogical::Read(in,objc);
  // The rest of the read objects
  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . . Read in BaseDataLogical
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataLogical::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);
  // The rest of the read objects
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . BaseDataLogical
**
**  DESCRIPTION
**    out,out1: The output buffer
** 
**    The output of the Value is reserved for the 
**    classes that inherit this one.
**
**  REMARKS
**
*/
ostream& BaseDataLogical::print(ostream& out) const
{
  BaseDataObject::print(out);
  double val = GetValue();
  cout << "Value: ";
  cout << val;
  cout << "  ";
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . BaseDataLogical
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataLogical::Clone()
{
  BaseDataLogical *obj = new BaseDataLogical;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . BaseDataLogical
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataLogical::CopyClone(Identify * obj)
{
  BaseDataLogical *objfull = (BaseDataLogical *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . BaseDataLogical
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLogical::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && Encode(buffer,Value);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . BaseDataLogical
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLogical::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  if(!result)
    cout << "Failed\n";
  result = result && Decode(buffer,Value);
  if(!result)
    cout << "Failed\n";
  
  return result;
}
 
/*F AND(val)  . . . . . . . . . . . . . . . . . . . . . . . . BaseDataLogical
**
**  DESCRIPTION
**    val: The first boolean 
**    and: The AND(val,Value) as min(val,Value)
**    
**  REMARKS
**
*/
void BaseDataLogical::AND(const BaseDataLogical& val)
{
  Value = val.Value * Value;
}
/*F OR(val) . . . . . . . . . . . . . . . . . . . . . . . . . BaseDataLogical
**
**  DESCRIPTION
**    val: The first boolean 
**    and: The OR(val,Value) as max(val,Value)
**    
**  REMARKS
**
*/
void BaseDataLogical::OR(const BaseDataLogical& val)
{
    Value = Value + val.Value -  Value * val.Value;
}
/*F NOT() . . . . . . . . . . . . . . . . . . . . . . . . . . BaseDataLogical
**
**  DESCRIPTION
**    val: The first boolean 
**    and: The OR(val,Value) as max(val,Value)
**    
**  REMARKS
**
*/
void BaseDataLogical::NOT()
{
  Value = 1.0 - Value;
}
 
/*F val = GetValue()  . . . . . . . . . . . . . . . . . . . . BaseDataLogical
**
**  DESCRIPTION
**    val: The logical value
**
**  REMARKS
**
*/
double BaseDataLogical::GetValue() const
{
  double val = Value;
  if(val > 1.0)
    val = 1.0;
  if(val < 0.0) 
    val = 0.0;
  
  return Value;
}
/*F GetValue(val) . . . . . . . . . . . . . . . . . . . . . . BaseDataLogical
**
**  DESCRIPTION
**    val: The logical value
**
**    The value returned is forced to be between 0.0 and 1.0
**
**  REMARKS
**
*/
void BaseDataLogical::SetValue(const double valorig)
{
  double val = valorig;
  
  if(val > 1.0)
    val = 1.0;
  if(val < 0.0) 
    val = 0.0;
  
  Value = val;
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
bool BaseDataLogical::operator==(BaseDataObject *obj)
{
  bool result = false;
  if(obj->GetType() == GetType())
    {
      BaseDataLogical *objfull = (BaseDataLogical *) obj;
      double diff = objfull->GetValue() - GetValue();
      if(diff*diff < .0000001)
        result = true;
    }
  else
    {
      cerr << "Comparing Different Logical Types: " << obj->GetType() << " " << GetType() << endl;
    }
  return result;
}
 
/*F SetAbsoluteTrue()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataLogical::SetAbsoluteTrue()
{
  Value = 1.0;
}
/*F SetAbsoluteTrue()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataLogical::SetAbsoluteFalse()
{
  Value = 0.0;
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
bool BaseDataLogical::WriteAsLine(ostream& out, DataObjectClass *objc)
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
bool BaseDataLogical::WriteAsASCII(ostream&, DataObjectClass*)
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
bool BaseDataLogical::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  out << "$(" << objc->NameTag << ") " << NameTag << " = $ ";
  out << endl;
  return true;
}

/*S DataLogicalClass
 */
/*F DataLogicalClass()  . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataLogicalClass::DataLogicalClass()
{
  Identification = LOGICAL_BASE_ID;
  NameTag = LOGICAL_BASE_NAME;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataLogicalClass(data)  . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataLogicalClass::DataLogicalClass(const DataLogicalClass& data)
  : DataObjectClass(data)
  // the rest
{
} 
 
/*F DataLogicalClass(id,name,descr) . . . . . . . . . . . . . . . constructor
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
DataLogicalClass::DataLogicalClass(const int id, 
                                   const String& name,
                                   const String& descr)
  : DataObjectClass(id,name,descr)

{
  EncodeDecodeClass = name;
  SubClass = COREOBJECTS_BASE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . .  DataLogicalClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataLogicalClass::print(ostream& out) const
{
  DataObjectClass::print(out);
           
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . .  DataLogicalClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataLogicalClass, there is no further information.
**
**  REMARKS
**
*/
bool DataLogicalClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . .  DataLogicalClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataLogicalClass::CopyClone(Identify *  objc)
{
  DataLogicalClass *objcfull = (DataLogicalClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . .  DataLogicalClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataLogicalClass::Clone()
{
  DataLogicalClass* id = new DataLogicalClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . .  DataLogicalClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLogicalClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . .  DataLogicalClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLogicalClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
  //  result = result && Decode(buffer,-----);

  return result;
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
BaseDataObject * DataLogicalClass::BaseDataObjectExample()
{ 
  //cout << "Make Logical Example\n";
  return (BaseDataObject *) new BaseDataLogical();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . .  DataLogicalClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataLogicalClass*& obj)
{
  obj = new DataLogicalClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataLogical
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataLogical*& obj)
{
  obj = new BaseDataLogical;
  return obj->DecodeThis(buffer);
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
bool DataLogicalClass::WriteAsLine(ostream& out)
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
bool DataLogicalClass::WriteAsASCII(ostream& out)
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
bool DataLogicalClass::WriteAsLatex(ostream& out)
{
  out << endl;
  out << "\\begin{verbatim}" << endl;
  print(out);
  out << endl << "\\{verbatim}" << endl;
  out << "\\\\" << endl;

  return true;
}
/*S BaseDataNValued
 */ 
/*F BaseDataNValued() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataNValued::BaseDataNValued()
{
  Identification = LOGICAL_NVALUED_ID;
  NameTag = LOGICAL_NVALUED_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataNValued(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataNValued::BaseDataNValued(const BaseDataNValued& data)
  : BaseDataLogical(data)
{
}
 
/*F ans = IsValidName(name) . . . . . . . .  look in list of name-value corrs
**
**  DESCRIPTION
**    name: Name to find
**    ans: true if in list
**
**  REMARKS
**
*/
bool DataNValuedClass::IsValidName(String& name)
{
  bool ans = true;
  
  //  SearchableObjectList<String,int>::iterator ele = NameValueCorrs.find(name);
  //  SearchableObjectList<String,int>::iterator elee = NameValueCorrs.end();
  if(NameValueCorrs.find(name) == NameValueCorrs.end())
    ans = false;
  return ans;
}

  
/*F Read(in,objc) . . . . . . . . . . . . . . . . . . Read in BaseDataNValued
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataNValued::Read(istream& in, DataObjectClass* objc)
{
  DataNValuedClass *objn = (DataNValuedClass *) objc;
  bool result = BaseDataLogical::Read(in,objc);
  
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  String val = str.ReadNext();
  
  if(objn->IsValidName(val))
    SetValue(objn->NameValueCorrs[val]);
  else 
    {
      cerr << "Truth Value not Found for '";
      cerr << NameTag << "' : '" << val << "' Value not changed\n";
      result = false;
    }
  
  return false;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . . Read in BaseDataNValued
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataNValued::Read(istream& in, DataObjectClass* objc, const String& name)
{
  DataNValuedClass *objn = (DataNValuedClass *) objc;
  bool result = BaseDataLogical::Read(in,objc,name);

  StreamObjectInput str(in,' ');

  String val = str.ReadNext();
  if(objn->IsValidName(val))
    SetValue(objn->NameValueCorrs[val]);
  else 
    {
      cerr << "Truth Value '" << val << "' not Found for '";
      cerr << name;
      cerr << "   Value set to lowest value\n";
      result = false;
    }
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . BaseDataNValued
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataNValued::print(ostream& out) const
{
  BaseDataLogical::print(out);
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . BaseDataNValued
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataNValued::Clone()
{
  BaseDataNValued *obj = new BaseDataNValued;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . BaseDataNValued
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataNValued::CopyClone(Identify * obj)
{
  BaseDataNValued *objfull = (BaseDataNValued *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . BaseDataNValued
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNValued::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataLogical::EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . BaseDataNValued
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataNValued::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataLogical::DecodeThis(buffer);

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
bool BaseDataNValued::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataLogical::WriteAsLine(out,objc);
  DataNValuedClass *lclass = (DataNValuedClass *) objc;
  out << lclass->FindNearestLogicalValue(GetValue()) << endl;  
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
bool BaseDataNValued::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataLogical::WriteAsASCII(out,objc);
  DataNValuedClass *lclass = (DataNValuedClass *) objc;
  out << lclass->FindNearestLogicalValue(GetValue()) << " " << endl;  
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
bool BaseDataNValued::WriteAsLatex(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataLogical::WriteAsLatex(out,objc);
  DataNValuedClass *lclass = (DataNValuedClass *) objc;
  out << " " << lclass->FindNearestLogicalValue(GetValue()) << " " << endl;  
  out << "\\\\" << endl;
  
  return result;
}

/*S DataNValuedClass
 */
/*F DataNValuedClass()  . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataNValuedClass::DataNValuedClass()
{
  Identification = LOGICAL_NVALUED_ID;
  NameTag = LOGICAL_NVALUED_NAME;
  SubClass = LOGICAL_BASE_NAME;
  EncodeDecodeClass = NameTag;

  NameValueCorrs.ChangeTitle("Logical Name-Value Correspondences\n");
  
} 
/*F DataNValuedClass(data)  . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataNValuedClass::DataNValuedClass(const DataNValuedClass& data)
  : DataLogicalClass(data),
    NameValueCorrs(data.NameValueCorrs)
{
} 
 
/*F DataNValuedClass(id,name,descr) . . . . . . . . . . . . . . . constructor
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
DataNValuedClass::DataNValuedClass(const int id, 
                                   const String& name,
                                   const String& descr)
  : DataLogicalClass(id,name,descr)
{
  EncodeDecodeClass = name;
  SubClass = LOGICAL_BASE_NAME;

  NameValueCorrs.ChangeTitle("Logical Name-Value Correspondences\n");
  NameValueCorrs.ChangeDelimitor("  ");
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . .  DataNValuedClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataNValuedClass::print(ostream& out) const
{
  DataLogicalClass::print(out);
  unsigned int s = NameValueCorrs.size();
  out << s << "-Valued Logic: ";
  NameValueCorrs.print(out);
  if(NameValueCorrs.size() == 0)
    out << "No Elements";

  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . .  DataNValuedClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataNValuedClass, there is no further information.
**
**  REMARKS
**
*/
bool DataNValuedClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataLogicalClass::Read(in,set);

  StreamObjectInput str(in,' ');
  String name = str.ReadNext();

  while(!(name == "END"))
    {
      String value = str.ReadNext();
      double val = value.ToFloat();
      if(val > 1.0) 
        val = 1.0;
      if(val < 0.0)
        val = 0.0;
      
      NameValueCorrs[name] = val;
      name = str.ReadNext();
      
    }
  
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . .  DataNValuedClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataNValuedClass::CopyClone(Identify *  objc)
{
  DataNValuedClass *objcfull = (DataNValuedClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . .  DataNValuedClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataNValuedClass::Clone()
{
  DataNValuedClass* id = new DataNValuedClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . .  DataNValuedClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNValuedClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataLogicalClass::EncodeThis(buffer);
  result = result && NameValueCorrs.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . .  DataNValuedClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataNValuedClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataLogicalClass::DecodeThis(buffer);
  result = result && NameValueCorrs.DecodeThis(buffer);

  return result;
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
BaseDataObject * DataNValuedClass::BaseDataObjectExample()
{ 
  BaseDataNValued *obj = new BaseDataNValued();
  obj->NameTag = NameTag;
  obj->SetType(Identification);
  return (BaseDataObject *) obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . .  DataNValuedClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataNValuedClass*& obj)
{
  obj = new DataNValuedClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataNValued
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataNValued*& obj)
{
  obj = new BaseDataNValued;
  return obj->DecodeThis(buffer);
}
 
/*F name = FindNearestLogicalValue(val) . . . . .  find the name of the value
**
**  DESCRIPTION
**    val: The 'logical' value
**    name: The descrete name which is closest to the value
**
**  REMARKS
**
*/
String& DataNValuedClass::FindNearestLogicalValue(const double val)
{
  double v;
  double nearest = 1000.0;
  String *name = new String("Not Found");
  double diff;
  SearchableObjectList<String,double>::iterator iter;
  for(iter=NameValueCorrs.begin();
      iter != NameValueCorrs.end();
      iter++)
    {
      v = (*iter).second;
      if(v > val)
        diff = v - val;
      else
        diff = val - v;
      if(diff < nearest)
        {
          *name = (*iter).first;
          nearest = diff;
        }
    }
  return *name;
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
bool DataNValuedClass::WriteAsLine(ostream& out)
{
  return DataLogicalClass::WriteAsLine(out);
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
bool DataNValuedClass::WriteAsASCII(ostream& out)
{
  bool result = DataLogicalClass::WriteAsASCII(out);

  SearchableObjectList<String,double>::iterator iter;
  for(iter=NameValueCorrs.begin();
      iter != NameValueCorrs.end();
      iter++)
    {
      out << " " << (*iter).first << " " << (*iter).second << " ";
    }
  out << "  END";
  out << endl;
  
  return result;
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
bool DataNValuedClass::WriteAsLatex(ostream& out)
{
  out << "\\begin{tabular}[|l|l|]\\hline" << endl;
  
  SearchableObjectList<String,double>::iterator iter;
  for(iter=NameValueCorrs.begin();
      iter != NameValueCorrs.end();
      iter++)
    {
      out << (*iter).first << " & " << (*iter).second << " \\hline" << endl;
    }
  out << "\\end{tabular}" << endl;

  return true;
}

/*S BaseDataContinuous
 */ 
/*F BaseDataContinuous()  . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataContinuous::BaseDataContinuous()
{
  Identification = LOGICAL_CONTINUOUS_ID;
  NameTag = LOGICAL_CONTINUOUS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataContinuous(data)  . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataContinuous::BaseDataContinuous(const BaseDataContinuous& data)
  : BaseDataLogical(data)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . .  Read in BaseDataContinuous
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataContinuous::Read(istream& in, DataObjectClass* objc)
{
  bool result = BaseDataLogical::Read(in,objc);
  
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  String val = str.ReadNext();
  SetValue(val.ToFloat());
  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . .  Read in BaseDataContinuous
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataContinuous::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataLogical::Read(in,objc,name);

  StreamObjectInput str(in,' ');

  String val = str.ReadNext();
  SetValue(val.ToFloat());
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . .  BaseDataContinuous
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataContinuous::print(ostream& out) const
{
  BaseDataLogical::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . .  BaseDataContinuous
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataContinuous::Clone()
{
  BaseDataContinuous *obj = new BaseDataContinuous;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . .  BaseDataContinuous
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataContinuous::CopyClone(Identify * obj)
{
  BaseDataContinuous *objfull = (BaseDataContinuous *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . .  BaseDataContinuous
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataContinuous::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataLogical::EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . .  BaseDataContinuous
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataContinuous::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataLogical::DecodeThis(buffer);

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
bool BaseDataContinuous::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataLogical::WriteAsLine(out,objc);
  out << GetValue() << endl;  
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
bool BaseDataContinuous::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataLogical::WriteAsASCII(out,objc);
  out << GetValue() << " ";
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
bool BaseDataContinuous::WriteAsLatex(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataLogical::WriteAsLatex(out,objc);
  out << "$ " << GetValue();
  out << " $ \\\\" << endl;
  
  return result;
}

/*S DataContinuousClass
 */
/*F DataContinuousClass() . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataContinuousClass::DataContinuousClass()
{
  Identification = LOGICAL_CONTINUOUS_ID;
  NameTag = LOGICAL_CONTINUOUS_NAME;
  SubClass = LOGICAL_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataContinuousClass(data) . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataContinuousClass::DataContinuousClass(const DataContinuousClass& data)
  : DataLogicalClass(data)
{
} 
 
/*F DataContinuousClass(id,name,descr)  . . . . . . . . . . . . . constructor
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
DataContinuousClass::DataContinuousClass(const int id, 
                                         const String& name,
                                         const String& descr)
  : DataLogicalClass(id,name,descr)
{
  EncodeDecodeClass = name;
  SubClass = LOGICAL_BASE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . DataContinuousClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataContinuousClass::print(ostream& out) const
{
  DataLogicalClass::print(out);
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . DataContinuousClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataContinuousClass, there is no further information.
**
**  REMARKS
**
*/
bool DataContinuousClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataLogicalClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . DataContinuousClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataContinuousClass::CopyClone(Identify *  objc)
{
  DataContinuousClass *objcfull = (DataContinuousClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . DataContinuousClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataContinuousClass::Clone()
{
  DataContinuousClass* id = new DataContinuousClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . DataContinuousClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataContinuousClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataLogicalClass::EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . DataContinuousClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataContinuousClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataLogicalClass::DecodeThis(buffer);

  return result;
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
BaseDataObject * DataContinuousClass::BaseDataObjectExample()
{ 
  //cout << "Make Continuous Example\n";
  return (BaseDataObject *) new BaseDataContinuous();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . DataContinuousClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataContinuousClass*& obj)
{
  obj = new DataContinuousClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . .  BaseDataContinuous
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataContinuous*& obj)
{
  obj = new BaseDataContinuous;
  return obj->DecodeThis(buffer);
}
/*S Utitilies
 */
 
/*F InitialSetOfLogicalEncodeDecodeRoutines() . . . . . . . . set of routines
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialSetOfLogicalEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataLogicalClass,BaseDataLogical,LOGICAL_BASE_NAME);
  EncodeDecodeRegisterClass(DataNValuedClass,BaseDataNValued,LOGICAL_NVALUED_NAME);
  EncodeDecodeRegisterClass(DataContinuousClass,BaseDataContinuous,LOGICAL_CONTINUOUS_NAME);


//  bool (*toproutine)(CommBuffer&,Identify*&);
//
//  bool (*rout1)(CommBuffer&,BaseDataLogical*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout1;
//  SingleDecodeRoutine p1("Object.Logical",toproutine);
//  (*SetOfEncodeDecodeRoutines)[p1.StructureName] = p1;
//
//  bool (*rout2)(CommBuffer&,BaseDataNValued*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout2;
//  SingleDecodeRoutine p2("Object.NValued",toproutine);
//  (*SetOfEncodeDecodeRoutines)[p2.StructureName] = p2;
//
//  bool (*rout3)(CommBuffer&,DataLogicalClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout3;
//  SingleDecodeRoutine p3("Logical",toproutine);
//  (*SetOfEncodeDecodeRoutines)[p3.StructureName] = p3;
//
//  bool (*rout4)(CommBuffer&,DataNValuedClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout4;
//  SingleDecodeRoutine p4("NValued",toproutine);
//  (*SetOfEncodeDecodeRoutines)[p4.StructureName] = p4;
//
//  bool (*rout5)(CommBuffer&,BaseDataContinuous*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout5;
//  SingleDecodeRoutine p5("Object.Continuous",toproutine);
//  (*SetOfEncodeDecodeRoutines)[p5.StructureName] = p5;
//
//  bool (*rout6)(CommBuffer&,DataContinuousClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout6;
//  SingleDecodeRoutine p6("Continuous",toproutine);
//  (*SetOfEncodeDecodeRoutines)[p6.StructureName] = p6;
}
/*F AddLogicalClasses(set)  . . . . . . . . . .  add to DataSetOfObjectsClass
**
**  DESCRIPTION
**    set: The set of classes of objects to add the numeric classes to
**
**  REMARKS
**
*/
void AddLogicalClasses(DataSetOfObjectsClass& set)
{
  String logdescr("Logical Base Class");
  String nvaldescr("N-Valued Class");
  String contdescr("Continuous Class");
  
  DataLogicalClass logclass(LOGICAL_BASE_ID,LOGICAL_BASE_NAME,logdescr);
  DataNValuedClass nvalclass(LOGICAL_NVALUED_ID,LOGICAL_NVALUED_NAME,nvaldescr);
  DataContinuousClass contclass(LOGICAL_CONTINUOUS_ID,LOGICAL_CONTINUOUS_NAME,contdescr);
  
  set.AddObjectClass(logclass);
  set.AddObjectClass(nvalclass);
  set.AddObjectClass(contclass);
}

