/*  FILE     FunctionReal1DObjects.cc
**  PACKAGE  FunctionReal1DObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "FunctionReal1DObjects" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
**  Version 1.5
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjects.hh"
#include "Vector.hh"
#include "OperationObjects.hh"
#include "ParameterizedFunction.hh"
#include "FunctionReal1DObjects.hh"

/*S BaseDataFuncReal1D
 */ 
/*F BaseDataFuncReal1D()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataFuncReal1D::BaseDataFuncReal1D()
  : LowerBound(LOWEST_POSSIBLE_REAL),
    UpperBound(HIGHEST_POSSIBLE_REAL),
    IncludeLower(true),
    IncludeUpper(true)
{
  Identification = ODREALFUNC_BASE_ID;
  NameTag = ODREALFUNC_BASE_NAME;
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataFuncReal1D(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataFuncReal1D::BaseDataFuncReal1D(const BaseDataFuncReal1D& data)
  : BaseDataObject(data),
    LowerBound(data.LowerBound),
    UpperBound(data.UpperBound),
    IncludeLower(data.IncludeLower),
    IncludeUpper(data.IncludeUpper)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataFuncReal1D
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**    The expected input for this class is:
**    - That from BaseDataObject
**    - UpperBound (a number or '+Infinity')
**    - Inclusive? ('T' or 'F')
**    - LowerBound (a numer or '-Infintity')
**    - Inclusive? ('T' or 'F')
**
**  REMARKS
**
*/
bool BaseDataFuncReal1D::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataFuncReal1D
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**    The expected input for this class is:
**    - That from BaseDataObject
**    - UpperBound (a number or '+Infinity')
**    - Inclusive? ('T' or 'F')
**    - LowerBound (a numer or '-Infintity')
**    - Inclusive? ('T' or 'F')
**
**  REMARKS
**
*/
bool BaseDataFuncReal1D::Read(istream& in, DataObjectClass* objc, const String& name)
{
  BaseDataObject::Read(in,objc,name);
  bool result = true;
  
  StreamObjectInput str(in,' ');
  String key = str.ReadNext();
  if(key == ODREALFUNC_BASE_NAME)
    {
      String lower  = str.ReadNext();
      String ilower = str.ReadNext();
      String upper  = str.ReadNext();
      String iupper = str.ReadNext();
      
      if(objc->getDebugLevel() > 1)
        {
          cout << "Read Intervals\n";
          cout << lower << ", ";
          cout << upper << ", ";
          cout << ilower << ", ";
          cout << iupper << "\n";
        }
      UpperBound = ConvertNumericString(upper);
      LowerBound = ConvertNumericString(lower);
      
      if(objc->getDebugLevel() > 1)
        {
          cout << LowerBound << ", " << UpperBound << "\n";
        }
      
      if(iupper == "T")
        IncludeUpper = true;
      else
        IncludeUpper = false;
      if(ilower == "T")
        IncludeLower = true;
      else
        IncludeLower = false;
    }
  else
    {
      cerr << "Expecting '" << ODREALFUNC_BASE_NAME << "' got '" << key << endl;
      result = false;
    }
  
      
  return result;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataFuncReal1D
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataFuncReal1D::print(ostream& out) const
{
  BaseDataObject::print(out);
  cout << "Function: ";
  WriteBounds(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataFuncReal1D
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataFuncReal1D::Clone()
{
  BaseDataFuncReal1D *obj = new BaseDataFuncReal1D;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataFuncReal1D
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataFuncReal1D::CopyClone(Identify * obj)
{
  BaseDataFuncReal1D *objfull = (BaseDataFuncReal1D *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataFuncReal1D
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataFuncReal1D::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && Encode(buffer,LowerBound);
  result = result && Encode(buffer,UpperBound);
  int val;
  if(IncludeLower)
    val = 1;
  else
    val = 0;
  result = result && Encode(buffer,val);
  if(IncludeUpper)
    val = 1;
  else
    val = 0;
  result = result && Encode(buffer,val);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataFuncReal1D
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataFuncReal1D::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && Decode(buffer,LowerBound);
  result = result && Decode(buffer,UpperBound);
  int val = 0;
  result = result && Decode(buffer,val);
  if(val == 1)
    IncludeLower = true;
  else
    IncludeLower = false;
  result = result && Decode(buffer,val);
  if(val == 1)
    IncludeUpper = true;
  else
    IncludeUpper = false;

  return result;
}
/*F WriteBounds(out)  . . . . . . . . . . . . . . . . . . . .  BaseDataFuncReal1D
**
**  DESCRIPTION
**    Simply writes the bound in a normal way
**
**  REMARKS
**
*/
void BaseDataFuncReal1D::WriteBounds(ostream& out) const
{
  if(IncludeLower)
    out << "[";
  else
    out << "(";
  if(LowerBound > LOWEST_POSSIBLE_REAL)
    out << "-Infinity,";
  else
    out << LowerBound << ",";
  if(LowerBound < HIGHEST_POSSIBLE_REAL)
    out << "+Infinity";
  else
    out << UpperBound;
  if(IncludeUpper)
    out << "]  ";
  else
    out << ")  ";
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
bool BaseDataFuncReal1D::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << "(" << objc->NameTag << ") " << NameTag;
  out << "  with Bounds: ";
  WriteBounds(out);
  out << " = ";

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
bool BaseDataFuncReal1D::WriteAsASCII(ostream& out, DataObjectClass*)
{
  out << " " << ODREALFUNC_BASE_NAME << " ";
  if(LowerBound > LOWEST_POSSIBLE_REAL)
    out << LowerBound << " ";
  else
    out << "-Infinity ";
  if(IncludeLower)
    out << "T ";
  else
    out << "F ";
  if(LowerBound < HIGHEST_POSSIBLE_REAL)
    out << UpperBound << " ";
  else
    out << "+Infinity ";
  if(IncludeUpper)
    out << "T ";
  else
    out << "F ";
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
bool BaseDataFuncReal1D::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  out << "$(" << objc->NameTag << ") " << NameTag;
  out << "  with Bounds: ";
  WriteBounds(out);
  out << " = $ ";
  return true;
}
VectorNumeric *BaseDataFuncReal1D::NumericVectorFromParameters(BaseDataParameterSet *parameters,
							       DataParameterSetClass *parclass)
{
  bool result = true;
  ObjectList<String> names = parameters->OrderedListOfParameterNames();
  DataSetOfObjectsClass *set = parclass->PointerToAllowedClasses();
  VectorNumeric *vec = new VectorNumeric(names.size());
  unsigned int pos = 0;
  ObjectList<String>::iterator name = names.begin();
  while(result && name != names.end())
    {
      BaseDataObject *obj = parameters->GetObject(*name);
      DataObjectClass *objcls = set->GetObjectClass(obj->GetType());
      if(set->IsOfClass(objcls->NameTag,NUMERIC_BASE_NAME))
	{
	  BaseDataReal *num = (BaseDataReal *) obj;
	  (*vec)[pos] = num->Distance();
	  name++;
	  pos++;
	}
      else
	{
	  cerr << "Error in parameter set, parameter not a number: '" << obj->NameTag << "'" << endl;
	  delete vec;
	  vec = NULL;
	  result = false;
	}
    }
  return vec;
}
/*S DataFuncReal1DClass
 */
/*F DataFuncReal1DClass() . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataFuncReal1DClass::DataFuncReal1DClass()
{
} 
/*F DataFuncReal1DClass(data) . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataFuncReal1DClass::DataFuncReal1DClass(const DataFuncReal1DClass& data)
  : DataObjectClass(data)
  // the rest
{
} 
 
/*F DataFuncReal1DClass(id,name,descr)  . . . . . . . . . . . . . constructor
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
DataFuncReal1DClass::DataFuncReal1DClass(const int id, 
					 const String& name,
					 const String& descr)
  : DataObjectClass(id,name,descr)
{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = ODREALFUNC_BASE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . DataFuncReal1DClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataFuncReal1DClass::print(ostream& out) const
{
  DataObjectClass::print(out);
           
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . DataFuncReal1DClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataFuncReal1DClass, there is no further information.
**
**  REMARKS
**
*/
bool DataFuncReal1DClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . DataFuncReal1DClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataFuncReal1DClass::CopyClone(Identify *  objc)
{
  DataFuncReal1DClass *objcfull = (DataFuncReal1DClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . DataFuncReal1DClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataFuncReal1DClass::Clone()
{
  DataFuncReal1DClass* id = new DataFuncReal1DClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . DataFuncReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataFuncReal1DClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . DataFuncReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataFuncReal1DClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
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
BaseDataObject * DataFuncReal1DClass::BaseDataObjectExample()
{ 
  //cout << "Make FuncReal1D Example\n";
  return (BaseDataObject *) new BaseDataFuncReal1D();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . DataFuncReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataFuncReal1DClass*& obj)
{
  obj = new DataFuncReal1DClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . .  BaseDataFuncReal1D
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataFuncReal1D*& obj)
{
  obj = new BaseDataFuncReal1D;
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
bool DataFuncReal1DClass::WriteAsLine(ostream& out)
{
  return DataObjectClass::WriteAsLine(out);
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
bool DataFuncReal1DClass::WriteAsASCII(ostream& out)
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
bool DataFuncReal1DClass::WriteAsLatex(ostream& out)
{
  return DataObjectClass::WriteAsLatex(out);
}


/*S BaseDataConstantReal1D
 */ 
/*F BaseDataConstantReal1D()  . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataConstantReal1D::BaseDataConstantReal1D()
{
  Identification = ODREALFUNC_CONSTANT_ID;
  NameTag = ODREALFUNC_CONSTANT_NAME;
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataConstantReal1D(data)  . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataConstantReal1D::BaseDataConstantReal1D(const BaseDataConstantReal1D& data)
  : BaseDataFuncReal1D(data),
    ConstantValue(data.ConstantValue)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . .  Read in BaseDataConstantReal1D
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataConstantReal1D::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput strin(in,' ');
  NameTag = strin.ReadNext();

  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . .  Read in BaseDataConstantReal1D
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataConstantReal1D::Read(istream& in, DataObjectClass* objc, const String& name)
{
  BaseDataFuncReal1D::Read(in,objc,name);
  bool result = true;
  
  StreamObjectInput strin(in,' ');
  String key = strin.ReadNext();
  
  if(key == ODREALFUNC_CONSTANT_NAME)
    {
      String cval = strin.ReadNext();
      ConstantValue = ConvertNumericString(cval);
    }
  else
    {
      cerr << "Expecting '" << ODREALFUNC_CONSTANT_NAME << "' got '" << key << endl;
      result = false;
    }
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . .  BaseDataConstantReal1D
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataConstantReal1D::print(ostream& out) const
{
  BaseDataFuncReal1D::print(out);

  cout << "Constant Value: " << ConstantValue << " ";
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . .  BaseDataConstantReal1D
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataConstantReal1D::Clone()
{
  BaseDataConstantReal1D *obj = new BaseDataConstantReal1D;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . .  BaseDataConstantReal1D
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataConstantReal1D::CopyClone(Identify * obj)
{
  BaseDataConstantReal1D *objfull = (BaseDataConstantReal1D *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . .  BaseDataConstantReal1D
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataConstantReal1D::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataFuncReal1D::EncodeThis(buffer);
  result = result && Encode(buffer,ConstantValue);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . .  BaseDataConstantReal1D
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataConstantReal1D::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataFuncReal1D::DecodeThis(buffer);
  result = result && Decode(buffer,ConstantValue);

  return result;
}
 
/*F ans = operator()(x) . . . . . . . . . . . . . . .  BaseDataConstantRead1D
**
**  DESCRIPTION
**    x: The argument to the function
**    ans: The constant value
**
**  REMARKS
**
*/
double BaseDataConstantReal1D::operator()(const double x)
{
  return ConstantValue;
}
/*F ans = operator()(x) . . . . . . . . . . . . . . .  BaseDataConstantRead1D
**
**  DESCRIPTION
**    x: The argument to the function
**    ans: The constant value
**
**  REMARKS
**
*/
double BaseDataConstantReal1D::operator()(const double x, 
					  BaseDataParameterSet *parameters,
					  DataParameterSetClass *parclass)
{
  return ConstantValue;
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
bool BaseDataConstantReal1D::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataFuncReal1D::WriteAsLine(out,objc);
  out << ConstantValue << endl;

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
bool BaseDataConstantReal1D::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataFuncReal1D::WriteAsASCII(out,objc);
  out << " " << ODREALFUNC_CONSTANT_NAME;
  out << " " << ConstantValue << endl;

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
bool BaseDataConstantReal1D::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataFuncReal1D::WriteAsLatex(out,objc);
  out << " $" << ConstantValue << "$ " << endl;

  return result;
}

/*S DataConstantReal1DClass
 */
/*F DataConstantReal1DClass() . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataConstantReal1DClass::DataConstantReal1DClass()
{
} 
/*F DataConstantReal1DClass(data) . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataConstantReal1DClass::DataConstantReal1DClass(const DataConstantReal1DClass& data)
  : DataFuncReal1DClass(data)
  // the rest
{
} 
 
/*F DataConstantReal1DClass(id,name,descr)  . . . . . . . . . . . constructor
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
DataConstantReal1DClass::DataConstantReal1DClass(const int id, 
						 const String& name,
						 const String& descr)
  : DataFuncReal1DClass(id,name,descr)
{
  SubClass = ODREALFUNC_BASE_NAME;
  EncodeDecodeClass = ODREALFUNC_CONSTANT_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . DataConstantReal1DClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataConstantReal1DClass::print(ostream& out) const
{
  DataFuncReal1DClass::print(out);
  out << NameTag << "  ";
  // the rest
           
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . DataConstantReal1DClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataConstantReal1DClass, there is no further information.
**
**  REMARKS
**
*/
bool DataConstantReal1DClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataFuncReal1DClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . DataConstantReal1DClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataConstantReal1DClass::CopyClone(Identify * objc)
{
  DataConstantReal1DClass *objcfull = (DataConstantReal1DClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . DataConstantReal1DClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataConstantReal1DClass::Clone()
{
  DataConstantReal1DClass* id = new DataConstantReal1DClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . DataConstantReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataConstantReal1DClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataFuncReal1DClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . DataConstantReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataConstantReal1DClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataFuncReal1DClass::DecodeThis(buffer);
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
BaseDataObject * DataConstantReal1DClass::BaseDataObjectExample()
{ 
  //cout << "Make ConstantReal1D Example\n";
  return (BaseDataObject *) new BaseDataConstantReal1D();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . DataConstantReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataConstantReal1DClass*& obj)
{
  obj = new DataConstantReal1DClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . .  BaseDataConstantReal1D
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataConstantReal1D*& obj)
{
  obj = new BaseDataConstantReal1D;
  return obj->DecodeThis(buffer);
}
/*S BaseDataLinearReal1D
 */ 
/*F BaseDataLinearReal1D()  . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataLinearReal1D::BaseDataLinearReal1D()
{
  Identification = ODREALFUNC_LINEAR_ID;
  NameTag = ODREALFUNC_LINEAR_NAME;
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataLinearReal1D(data)  . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataLinearReal1D::BaseDataLinearReal1D(const BaseDataLinearReal1D& data)
  : BaseDataFuncReal1D(data),
    Pointx(data.Pointx),
    Pointy(data.Pointy),
    Directionx(data.Directionx),
    Directiony(data.Directiony)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . .  Read in BaseDataLinearReal1D
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**    The input expected is:
**    - A fixed x point
**    - A fixed y point
**    - An x Direction
**    - A y Direction
**
**  REMARKS
**
*/
bool BaseDataLinearReal1D::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput strin(in,' ');
  NameTag = strin.ReadNext();
  
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . .  Read in BaseDataLinearReal1D
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**    The input expected is:
**    - A fixed x point
**    - A fixed y point
**    - An x Direction
**    - A y Direction
**
**  REMARKS
**
*/
bool BaseDataLinearReal1D::Read(istream& in, DataObjectClass* objc, const String& name)
{
  BaseDataFuncReal1D::Read(in,objc,name);
  bool result = true;
  
  StreamObjectInput strin(in,' ');

  String key = strin.ReadNext();
  if(key == ODREALFUNC_LINEAR_NAME)
    {
      String pxval = strin.ReadNext();
      String pyval = strin.ReadNext();
      String dxval = strin.ReadNext();
      String dyval = strin.ReadNext();
  
      Pointx = pxval.ToFloat();
      Pointy = pyval.ToFloat();
      Directionx = dxval.ToFloat();
      Directiony = dyval.ToFloat();
    }
  else
    {
      cerr << "Expected '" << ODREALFUNC_LINEAR_NAME << "' got '" << key << endl;
      result = false;
    }
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . .  BaseDataLinearReal1D
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataLinearReal1D::print(ostream& out) const
{
  BaseDataFuncReal1D::print(out);

  cout << "Line From Point: ";
  cout << "(" << Pointx << "," << Pointy << ")";
  cout << " in Direction: ";
  cout << "(" << Directionx << "," << Directiony << ")";
  cout << "  ";

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . .  BaseDataLinearReal1D
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataLinearReal1D::Clone()
{
  BaseDataLinearReal1D *obj = new BaseDataLinearReal1D;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . .  BaseDataLinearReal1D
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataLinearReal1D::CopyClone(Identify * obj)
{
  BaseDataLinearReal1D *objfull = (BaseDataLinearReal1D *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . .  BaseDataLinearReal1D
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLinearReal1D::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataFuncReal1D::EncodeThis(buffer);
  result = result && Encode(buffer,Pointx);
  result = result && Encode(buffer,Pointy);
  result = result && Encode(buffer,Directionx);
  result = result && Encode(buffer,Directiony);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . .  BaseDataLinearReal1D
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLinearReal1D::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataFuncReal1D::DecodeThis(buffer);
  result = result && Decode(buffer,Pointx);
  result = result && Decode(buffer,Pointy);
  result = result && Decode(buffer,Directionx);
  result = result && Decode(buffer,Directiony);

  return result;
}
 
/*F ans = operator()(x) . . . . . . . . . . . . . . . . . . . Linear function
**
**  DESCRIPTION
**    x: The value at which to compute the function
**    ans: The y value of the linear function
**
**  REMARKS
**
*/
double BaseDataLinearReal1D::operator()(const double x)
{
  return (x - Pointx)*Directiony/Directionx + Pointy;
}
/*F ans = operator()(x) . . . . . . . . . . . . . . .  BaseDataRealLinear1D
**
**  DESCRIPTION
**    x: The argument to the function
**    ans: The constant value
**
**  REMARKS
**
*/
double BaseDataLinearReal1D::operator()(const double x, 
					BaseDataParameterSet *parameters,
					DataParameterSetClass *parclass)
{
  VectorNumeric *vec = NumericVectorFromParameters(parameters,parclass);
  if(vec->size() == 4)
    {
      Pointx = (*vec)[0];
      Pointx = (*vec)[1];
      Directionx = (*vec)[2];
      Directiony = (*vec)[3];

    }
  else
    {
      cerr << "Parameter set size not correct for linear function (expected 4): " << vec->size() << endl;
    }
  return operator()(x);
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
bool BaseDataLinearReal1D::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataFuncReal1D::WriteAsLine(out,objc);
  out << " (" << Pointx << "," << Pointy << ") ";
  out << "with direction " << "(" << Directionx << "," << Directiony << ")" << endl;

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
bool BaseDataLinearReal1D::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataFuncReal1D::WriteAsASCII(out,objc);
  out << " " << ODREALFUNC_LINEAR_NAME;
  out << " " << Pointx;
  out << " " << Pointy;
  out << " " << Directionx;
  out << " " << Directiony;
  out << endl;

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
bool BaseDataLinearReal1D::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataFuncReal1D::WriteAsLatex(out,objc);
  out << " $(" << Pointx << "," << Pointy << ") ";
  out << "with direction " << "(" << Directionx << "," << Directiony << ")$" << endl;

  return result;
}

/*S DataLinearReal1DClass
 */
/*F DataLinearReal1DClass() . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataLinearReal1DClass::DataLinearReal1DClass()
{
} 
/*F DataLinearReal1DClass(data) . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataLinearReal1DClass::DataLinearReal1DClass(const DataLinearReal1DClass& data)
  : DataFuncReal1DClass(data)
  // the rest
{
} 
 
/*F DataLinearReal1DClass(id,name,descr)  . . . . . . . . . . . . constructor
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
DataLinearReal1DClass::DataLinearReal1DClass(const int id, 
					     const String& name,
					     const String& descr)
  : DataFuncReal1DClass(id,name,descr)
{
  SubClass = ODREALFUNC_BASE_NAME;
  EncodeDecodeClass = ODREALFUNC_LINEAR_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . DataLinearReal1DClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataLinearReal1DClass::print(ostream& out) const
{
  DataFuncReal1DClass::print(out);
  out << NameTag << "  ";
  // the rest
           
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . DataLinearReal1DClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataLinearReal1DClass, there is no further information.
**
**  REMARKS
**
*/
bool DataLinearReal1DClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataFuncReal1DClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . DataLinearReal1DClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataLinearReal1DClass::CopyClone(Identify * objc)
{
  DataLinearReal1DClass *objcfull = (DataLinearReal1DClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . DataLinearReal1DClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataLinearReal1DClass::Clone()
{
  DataLinearReal1DClass* id = new DataLinearReal1DClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . DataLinearReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLinearReal1DClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataFuncReal1DClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . DataLinearReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLinearReal1DClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataFuncReal1DClass::DecodeThis(buffer);
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
BaseDataObject * DataLinearReal1DClass::BaseDataObjectExample()
{ 
  //cout << "Make LinearReal1D Example\n";
  return (BaseDataObject *) new BaseDataLinearReal1D();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . DataLinearReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataLinearReal1DClass*& obj)
{
  obj = new DataLinearReal1DClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . .  BaseDataLinearReal1D
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataLinearReal1D*& obj)
{
  obj = new BaseDataLinearReal1D;
  return obj->DecodeThis(buffer);
}
/*S BaseDataGaussianReal1D
 */ 
/*F BaseDataGaussianReal1D()  . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGaussianReal1D::BaseDataGaussianReal1D()
{
  Identification = ODREALFUNC_GAUSSIAN_ID;
  NameTag = ODREALFUNC_GAUSSIAN_NAME;
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataGaussianReal1D(data)  . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGaussianReal1D::BaseDataGaussianReal1D(const BaseDataGaussianReal1D& data)
  : BaseDataFuncReal1D(data),
    Constant(data.Constant),
    ExponentMult(data.ExponentMult),
    ExponentOffset(data.ExponentOffset)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . .  Read in BaseDataGaussianReal1D
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**    The input is as follows:
**    - The name of the function
**    - The constant in front of the exponential
**    - The multiplicative constant in the exponent
**    - The offset on the exponent
**
**  REMARKS
**
*/
bool BaseDataGaussianReal1D::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput strin(in,' ');
  NameTag = strin.ReadNext();

  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . .  Read in BaseDataGaussianReal1D
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**    The input is as follows:
**    - The constant in front of the exponential
**    - The multiplicative constant in the exponent
**    - The offset on the exponent
**
**  REMARKS
**
*/
bool BaseDataGaussianReal1D::Read(istream& in, DataObjectClass* objc, const String& name)
{
  BaseDataFuncReal1D::Read(in,objc,name);
  bool result = true;
  
  StreamObjectInput strin(in,' ');

  String key = strin.ReadNext();
  if(key == ODREALFUNC_GAUSSIAN_NAME)
    {
      String cval = strin.ReadNext();
      Constant = cval.ToFloat();
      cval = strin.ReadNext();
      ExponentMult = cval.ToFloat();
      cval = strin.ReadNext();
      ExponentOffset = cval.ToFloat();
    }
  else
    {
      cerr << "Expecting '" << ODREALFUNC_GAUSSIAN_NAME << "' got '" << key << endl;
      result = false;
    }
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . .  BaseDataGaussianReal1D
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGaussianReal1D::print(ostream& out) const
{
  BaseDataFuncReal1D::print(out);
  
  cout << "The Gaussian: ";
  cout << Constant;
  cout << " * Exp( ";
  cout << ExponentMult;
  cout << "*(x-";
  cout << ExponentOffset;
  cout << ") ) ";

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . .  BaseDataGaussianReal1D
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGaussianReal1D::Clone()
{
  BaseDataGaussianReal1D *obj = new BaseDataGaussianReal1D;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . .  BaseDataGaussianReal1D
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGaussianReal1D::CopyClone(Identify * obj)
{
  BaseDataGaussianReal1D *objfull = (BaseDataGaussianReal1D *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . .  BaseDataGaussianReal1D
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGaussianReal1D::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataFuncReal1D::EncodeThis(buffer);
  result = result && Encode(buffer,Constant);
  result = result && Encode(buffer,ExponentMult);
  result = result && Encode(buffer,ExponentOffset);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . .  BaseDataGaussianReal1D
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGaussianReal1D::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataFuncReal1D::DecodeThis(buffer);
  result = result && Decode(buffer,Constant);
  result = result && Decode(buffer,ExponentMult);
  result = result && Decode(buffer,ExponentOffset);

  return result;
}
/*F ans = operator()(x) . . . . . . . . . . . . . . . . . . . Linear function
**
**  DESCRIPTION
**    x: The given x value
**    ans: The y value of the exponential
**
**  REMARKS
**
*/
double BaseDataGaussianReal1D::operator()(const double x)
{
  double diff = (x-ExponentOffset);
  double e = -ExponentMult*diff*diff;
  return Constant * exp(e);  
}
/*F ans = operator()(x) . . . . . . . . . . . . . . .  BaseDataRealGaussian1D
**
**  DESCRIPTION
**    x: The argument to the function
**    ans: The constant value
**
**  REMARKS
**
*/
double BaseDataGaussianReal1D::operator()(const double x, 
					  BaseDataParameterSet *parameters,
					  DataParameterSetClass *parclass)
{
  VectorNumeric *vec = NumericVectorFromParameters(parameters,parclass);
  if(vec->size() == 3)
    {
      Constant = (*vec)[0];
      ExponentMult = (*vec)[1];
      ExponentOffset = (*vec)[2];
    }
  else
    {
      cerr << "Parameter set size not correct for Gaussian (expected 3): " << vec->size() << endl;
    }
  return operator()(x);
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
bool BaseDataGaussianReal1D::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataFuncReal1D::WriteAsLine(out,objc);
  out << " " << Constant << "*E^(" << ExponentMult << "*( x - " << ExponentOffset << "))" << endl;
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
bool BaseDataGaussianReal1D::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataFuncReal1D::WriteAsASCII(out,objc);
  out << " " << ODREALFUNC_GAUSSIAN_NAME;
  out << " " << Constant;
  out << " " << ExponentMult;
  out << " " << ExponentOffset;
  out << endl;

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
bool BaseDataGaussianReal1D::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataFuncReal1D::WriteAsLatex(out,objc);
  out << "$ " << Constant << "*E^(" << ExponentMult << "*( x - " << ExponentOffset << "))$" << endl;
  return result;
}
/*S DataGaussianReal1DClass
 */
/*F DataGaussianReal1DClass() . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGaussianReal1DClass::DataGaussianReal1DClass()
{
} 
/*F DataGaussianReal1DClass(data) . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGaussianReal1DClass::DataGaussianReal1DClass(const DataGaussianReal1DClass& data)
  : DataFuncReal1DClass(data)
  // the rest
{
} 
 
/*F DataGaussianReal1DClass(id,name,descr)  . . . . . . . . . . . constructor
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
DataGaussianReal1DClass::DataGaussianReal1DClass(const int id, 
						 const String& name,
						 const String& descr)
  : DataFuncReal1DClass(id,name,descr)
{
  SubClass = ODREALFUNC_BASE_NAME;
  EncodeDecodeClass = ODREALFUNC_GAUSSIAN_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . DataGaussianReal1DClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGaussianReal1DClass::print(ostream& out) const
{
  DataFuncReal1DClass::print(out);
  out << NameTag << "  ";
  // the rest
           
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . DataGaussianReal1DClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGaussianReal1DClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGaussianReal1DClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataFuncReal1DClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . DataGaussianReal1DClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGaussianReal1DClass::CopyClone(Identify *  objc)
{
  DataGaussianReal1DClass *objcfull = (DataGaussianReal1DClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . DataGaussianReal1DClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGaussianReal1DClass::Clone()
{
  DataGaussianReal1DClass* id = new DataGaussianReal1DClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . DataGaussianReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGaussianReal1DClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataFuncReal1DClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . DataGaussianReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGaussianReal1DClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataFuncReal1DClass::DecodeThis(buffer);
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
BaseDataObject * DataGaussianReal1DClass::BaseDataObjectExample()
{ 
  //cout << "Make GaussianReal1D Example\n";
  return (BaseDataObject *) new BaseDataGaussianReal1D();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . DataGaussianReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGaussianReal1DClass*& obj)
{
  obj = new DataGaussianReal1DClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . .  BaseDataGaussianReal1D
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGaussianReal1D*& obj)
{
  obj = new BaseDataGaussianReal1D;
  return obj->DecodeThis(buffer);
}

/*S BaseDataPyramidFunction
 */ 
/*F BaseDataPyramidFunction() . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataPyramidFunction::BaseDataPyramidFunction()
{
  Identification = ODREALFUNC_PYRAMID_ID;
  NameTag = ODREALFUNC_PYRAMID_NAME;
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataPyramidFunction(data) . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataPyramidFunction::BaseDataPyramidFunction(const BaseDataPyramidFunction& data)
  : BaseDataFuncReal1D(data),
    InitialHeight(data.InitialHeight),
    PointHeight(data.PointHeight),
    FinalHeight(data.FinalHeight),
    Xbegin(data.Xbegin),
    Xpoint(data.Xpoint),
    Xend(data.Xend)
{
  Identification = ODREALFUNC_PYRAMID_ID;
  String tag = ODREALFUNC_PYRAMID_NAME;
  String name("Object.");
  name.AppendToEnd(tag);
  EncodeDecodeClass = name;
}
 
 
/*F BaseDataPyramidFunction(name,initial,point,final,xbeg,xpnt,xend) 
**
**  DESCRIPTION
**    name: The name of the function
**    initial,point,final: The corresponding y values
**    xbeg,xpnt,xend: The corresponding x values
**
**  REMARKS
**
*/
BaseDataPyramidFunction::BaseDataPyramidFunction(const String& name,
                                                 const double initial,const double point,const double final,
                                                 const double xbeg, const double xpnt, const double
                                                 xend)
  : InitialHeight(initial),
    PointHeight(point),
    FinalHeight(final),
    Xbegin(xbeg),
    Xpoint(xpnt),
    Xend(xend)
{
  Identification = ODREALFUNC_PYRAMID_ID;
  String tag = ODREALFUNC_PYRAMID_NAME;
  String obj("Object.");
  obj.AppendToEnd(tag);
  EncodeDecodeClass = obj;
  NameTag = name;
}


/*F Read(in,objc) . . . . . . . . . . . . . . Read in BaseDataPyramidFunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataPyramidFunction::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput strin(in,' ');
  NameTag = strin.ReadNext();
  
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . Read in BaseDataPyramidFunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataPyramidFunction::Read(istream& in, DataObjectClass* objc, const String& name)
{
  BaseDataFuncReal1D::Read(in,objc,name);
  bool result = true;
  
  StreamObjectInput strin(in,' ');
  String key = strin.ReadNext();
  if(key == ODREALFUNC_PYRAMID_NAME)
    {
      String iheight = strin.ReadNext();
      InitialHeight = iheight.ToFloat();
      String pheight = strin.ReadNext();
      PointHeight = pheight.ToFloat();
      String fheight = strin.ReadNext();
      FinalHeight = fheight.ToFloat();
      String xbegin = strin.ReadNext();
      Xbegin = xbegin.ToFloat();
      String xpoint = strin.ReadNext();
      Xpoint = xpoint.ToFloat();
      String xend = strin.ReadNext();
      Xend = xend.ToFloat();
    }
  else
    {
      cerr << "Expecting '" << ODREALFUNC_PYRAMID_NAME << "' got '" << key << endl;
      result = false;
    }
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . BaseDataPyramidFunction
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataPyramidFunction::print(ostream& out) const
{
  BaseDataFuncReal1D::print(out);
  
  PrintLine(out);
  out << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . BaseDataPyramidFunction
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataPyramidFunction::Clone()
{
  BaseDataPyramidFunction *obj = new BaseDataPyramidFunction;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . BaseDataPyramidFunction
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataPyramidFunction::CopyClone(Identify * obj)
{
  BaseDataPyramidFunction *objfull = (BaseDataPyramidFunction *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . BaseDataPyramidFunction
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPyramidFunction::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataFuncReal1D::EncodeThis(buffer);
  result = result && Encode(buffer,InitialHeight);
  result = result && Encode(buffer,PointHeight);
  result = result && Encode(buffer,FinalHeight);
  result = result && Encode(buffer,Xbegin);
  result = result && Encode(buffer,Xpoint);
  result = result && Encode(buffer,Xend);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . BaseDataPyramidFunction
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPyramidFunction::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataFuncReal1D::DecodeThis(buffer);
  result = result && Decode(buffer,InitialHeight);
  result = result && Decode(buffer,PointHeight);
  result = result && Decode(buffer,FinalHeight);
  result = result && Decode(buffer,Xbegin);
  result = result && Decode(buffer,Xpoint);
  result = result && Decode(buffer,Xend);

  return result;
}
 
/*F ans = FindPointValue(x1,y1,x2,y2,x) . . . . . . . BaseDataPyramidFunction
**
**  DESCRIPTION
**    x1,y1: The first point
**    x2,y2: The second point
**    x: The desired x value
**    ans: The y on the line
**
**    Given the line created by the two points, find the corresponding y 
**    value to the given x value
**
**  REMARKS
**
*/
double BaseDataPyramidFunction::FindPointValue(const double x1,const double y1,
                                               const double x2, const double y2,
                                               const double x)
{
  return y1 + (x-x1)*(y2-y1)/(x2-x1);
}
 
/*F ans = operator()(x) . . . . . . . . . . . . . . . BaseDataPyramidFunction
**
**  DESCRIPTION
**    x: The given x value
**    ans: The value of the pyramid function
**
**  REMARKS
**
*/
double BaseDataPyramidFunction::operator()(const double x)
{
  double y;
  if(x < Xbegin)
    y = InitialHeight;
  else if(x > Xend)
    y = FinalHeight;
  else if(x == Xpoint)
    y = PointHeight;
  else if(x < Xpoint)
    y = FindPointValue(Xbegin,InitialHeight,Xpoint,PointHeight,x);
  else
    y = FindPointValue(Xpoint,PointHeight,Xend,FinalHeight,x);
  return y;
}
/*F ans = operator()(x) . . . . . . . . . . . . . . .  BaseDataRealPyramid1D
**
**  DESCRIPTION
**    x: The argument to the function
**    ans: The constant value
**
**  REMARKS
**
*/
double BaseDataPyramidFunction::operator()(const double x, 
					   BaseDataParameterSet *parameters,
					   DataParameterSetClass *parclass)
{
  VectorNumeric *vec = NumericVectorFromParameters(parameters,parclass);
  if(vec->size() == 6)
    {
      InitialHeight = (*vec)[0];
      PointHeight = (*vec)[1];
      FinalHeight = (*vec)[2];
      Xbegin = (*vec)[3];
      Xpoint = (*vec)[4];
      Xend = (*vec)[5];
    }
  else
    {
      cerr << "Parameter set size not correct for Pyramid (expected 6): " << vec->size() << endl;
    }

  return operator()(x);
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
bool BaseDataPyramidFunction::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataFuncReal1D::WriteAsLine(out,objc);
  PrintLine(out);
  out << endl;
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
bool BaseDataPyramidFunction::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataFuncReal1D::WriteAsASCII(out,objc);
  out << " " << ODREALFUNC_PYRAMID_NAME;
  out << " " << InitialHeight;
  out << " " << PointHeight;
  out << " " << FinalHeight;
  out << " " << Xbegin;
  out << " " << Xpoint;
  out << " " << Xend;
  out << endl;

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
bool BaseDataPyramidFunction::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataFuncReal1D::WriteAsLatex(out,objc);
  out << "$ ";
  PrintLine(out);
  out << " $" << endl;
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
void BaseDataPyramidFunction::PrintLine(ostream& out) const 
{
  if(Xbegin == Xend)
    {
      out << "Stepping From ";
      out << InitialHeight;
      out << " to ";
      out << FinalHeight;
      out << " (at X= ";
      out << Xbegin;
      out << " with value ";
      out << PointHeight;
      out << ")  ";
    }
  else if(Xbegin == Xpoint || Xend == Xpoint)
    {
      if(InitialHeight > FinalHeight)
        out << "Decending From ";
      else 
        out << "Ascending From ";
      out << InitialHeight;
      out << " (at X= ";
      out << Xbegin;
      
      out << ") to ";
      out << FinalHeight;
      out << " (at X= ";
      out << Xend;
      out << ")  ";
    }
  else
    {
      if(InitialHeight > PointHeight)
        out << "Decending From ";
      else 
        out << "Ascending From ";
      out << InitialHeight;
      out << " (at X= ";
      out << Xbegin;
      
      out << ") to ";
      out << PointHeight;
      out << " (at X= ";
      out << Xpoint;
      out << ")  and then ";
      if(PointHeight > FinalHeight)
        out << "Decending to ";
      else 
        out << "Ascending to ";
      out << FinalHeight;
      out << " (at X= ";
      out << Xend;
      out << ")";
    }
}
/*S DataPyramidFunctionClass
 */
/*F DataPyramidFunctionClass()  . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataPyramidFunctionClass::DataPyramidFunctionClass()
{
  SubClass = ODREALFUNC_BASE_NAME;
  EncodeDecodeClass = ODREALFUNC_PYRAMID_NAME;
} 
/*F DataPyramidFunctionClass(data)  . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataPyramidFunctionClass::DataPyramidFunctionClass(const DataPyramidFunctionClass& data)
  : DataFuncReal1DClass(data)
  // the rest
{
} 
 
/*F DataPyramidFunctionClass(id,name,descr) . . . . . . . . . . . constructor
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
DataPyramidFunctionClass::DataPyramidFunctionClass(const int id, 
						   const String& name,
						   const String& descr)
  : DataFuncReal1DClass(id,name,descr)
{
  SubClass = ODREALFUNC_BASE_NAME;
  EncodeDecodeClass = ODREALFUNC_PYRAMID_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . .  DataPyramidFunctionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataPyramidFunctionClass::print(ostream& out) const
{
  DataFuncReal1DClass::print(out);
  out << NameTag << "  ";
  // the rest
           
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . .  DataPyramidFunctionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataPyramidFunctionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataPyramidFunctionClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataFuncReal1DClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . .  DataPyramidFunctionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataPyramidFunctionClass::CopyClone(Identify *  objc)
{
  DataPyramidFunctionClass *objcfull = (DataPyramidFunctionClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . .  DataPyramidFunctionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataPyramidFunctionClass::Clone()
{
  DataPyramidFunctionClass* id = new DataPyramidFunctionClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . .  DataPyramidFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPyramidFunctionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataFuncReal1DClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . .  DataPyramidFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPyramidFunctionClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataFuncReal1DClass::DecodeThis(buffer);
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
BaseDataObject * DataPyramidFunctionClass::BaseDataObjectExample()
{ 
  //cout << "Make PyramidFunction Example\n";
  return (BaseDataObject *) new BaseDataPyramidFunction();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . .  DataPyramidFunctionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataPyramidFunctionClass*& obj)
{
  obj = new DataPyramidFunctionClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . BaseDataPyramidFunction
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataPyramidFunction*& obj)
{
  obj = new BaseDataPyramidFunction;
  return obj->DecodeThis(buffer);
}
/*S BaseDataExponentialReal1D
 */ 
/*F BaseDataExponentialReal1D()  . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataExponentialReal1D::BaseDataExponentialReal1D()
  : Constant(0.0),
    ExponentMult(0.0)
{
  Identification = ODREALFUNC_EXPONENTIAL_ID;
  NameTag = ODREALFUNC_EXPONENTIAL_NAME;
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataExponentialReal1D(data)  . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataExponentialReal1D::BaseDataExponentialReal1D(const BaseDataExponentialReal1D& data)
  : BaseDataFuncReal1D(data),
    Constant(data.Constant),
    ExponentMult(data.ExponentMult)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . .  Read in BaseDataExponentialReal1D
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**    The input is as follows:
**    - The name of the function
**    - The constant in front of the exponential
**    - The multiplicative constant in the exponent
**    - The offset on the exponent
**
**  REMARKS
**
*/
bool BaseDataExponentialReal1D::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput strin(in,' ');
  NameTag = strin.ReadNext();

  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . .  Read in BaseDataExponentialReal1D
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**    The input is as follows:
**    - The constant in front of the exponential
**    - The multiplicative constant in the exponent
**    - The offset on the exponent
**
**  REMARKS
**
*/
bool BaseDataExponentialReal1D::Read(istream& in, DataObjectClass* objc, const String& name)
{
  BaseDataFuncReal1D::Read(in,objc,name);
  bool result = true;
  
  StreamObjectInput strin(in,' ');

  String key = strin.ReadNext();
  if(key == ODREALFUNC_EXPONENTIAL_NAME)
    {
      String cval = strin.ReadNext();
      Constant = cval.ToFloat();
      cval = strin.ReadNext();
      ExponentMult = cval.ToFloat();
    }
  else
    {
      cerr << "Expecting '" << ODREALFUNC_EXPONENTIAL_NAME << "' got '" << key << endl;
      result = false;
    }
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . .  BaseDataExponentialReal1D
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataExponentialReal1D::print(ostream& out) const
{
  BaseDataFuncReal1D::print(out);
  
  out << "The Exponential: ";
  out << Constant;
  out << " * Exp( ";
  out << ExponentMult;
  out << " * x)";

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . .  BaseDataExponentialReal1D
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataExponentialReal1D::Clone()
{
  BaseDataExponentialReal1D *obj = new BaseDataExponentialReal1D(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . .  BaseDataExponentialReal1D
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataExponentialReal1D::CopyClone(Identify * obj)
{
  BaseDataExponentialReal1D *objfull = (BaseDataExponentialReal1D *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . .  BaseDataExponentialReal1D
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExponentialReal1D::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataFuncReal1D::EncodeThis(buffer);
  result = result && Encode(buffer,Constant);
  result = result && Encode(buffer,ExponentMult);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . .  BaseDataExponentialReal1D
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExponentialReal1D::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataFuncReal1D::DecodeThis(buffer);
  result = result && Decode(buffer,Constant);
  result = result && Decode(buffer,ExponentMult);
  return result;
}
/*F ans = operator()(x) . . . . . . . . . . . . . . . . . . . Linear function
**
**  DESCRIPTION
**    x: The given x value
**    ans: The y value of the exponential
**
**  REMARKS
**
*/
double BaseDataExponentialReal1D::operator()(const double x)
{
  double e = -ExponentMult*x;
  return Constant * exp(e);  
}
/*F ans = operator()(x) . . . . . . . . . . . . . . .  BaseDataRealExponential1D
**
**  DESCRIPTION
**    x: The argument to the function
**    ans: The constant value
**
**  REMARKS
**
*/
double BaseDataExponentialReal1D::operator()(const double x, 
					  BaseDataParameterSet *parameters,
					  DataParameterSetClass *parclass)
{
  VectorNumeric *vec = NumericVectorFromParameters(parameters,parclass);
  if(vec->size() == 2)
    {
      Constant = (*vec)[0];
      ExponentMult = (*vec)[1];
    }
  else
    {
      cerr << "Parameter set size not correct for Exponential (expected 3): " << vec->size() << endl;
    }
  return operator()(x);
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
bool BaseDataExponentialReal1D::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataFuncReal1D::WriteAsLine(out,objc);
  out << " " << Constant << "*Exp^(" << ExponentMult << "* x )" << endl;
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
bool BaseDataExponentialReal1D::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataFuncReal1D::WriteAsASCII(out,objc);
  out << " " << ODREALFUNC_EXPONENTIAL_NAME;
  out << " " << Constant;
  out << " " << ExponentMult;
  out << endl;
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
bool BaseDataExponentialReal1D::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataFuncReal1D::WriteAsLatex(out,objc);
  out << "$ " << Constant << "*E^(" << ExponentMult << "*( x ))$" << endl;
  return result;
}
/*S DataExponentialReal1DClass
 */
/*F DataExponentialReal1DClass() . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataExponentialReal1DClass::DataExponentialReal1DClass()
{
} 
/*F DataExponentialReal1DClass(data) . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataExponentialReal1DClass::DataExponentialReal1DClass(const DataExponentialReal1DClass& data)
  : DataFuncReal1DClass(data)
  // the rest
{
} 
 
/*F DataExponentialReal1DClass(id,name,descr)  . . . . . . . . . . . constructor
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
DataExponentialReal1DClass::DataExponentialReal1DClass(const int id, 
						 const String& name,
						 const String& descr)
  : DataFuncReal1DClass(id,name,descr)
{
  SubClass = ODREALFUNC_BASE_NAME;
  EncodeDecodeClass = ODREALFUNC_EXPONENTIAL_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . DataExponentialReal1DClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataExponentialReal1DClass::print(ostream& out) const
{
  DataFuncReal1DClass::print(out);
  out << NameTag << "  ";
  // the rest
           
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . DataExponentialReal1DClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataExponentialReal1DClass, there is no further information.
**
**  REMARKS
**
*/
bool DataExponentialReal1DClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataFuncReal1DClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . DataExponentialReal1DClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataExponentialReal1DClass::CopyClone(Identify *  objc)
{
  DataExponentialReal1DClass *objcfull = (DataExponentialReal1DClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . DataExponentialReal1DClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataExponentialReal1DClass::Clone()
{
  DataExponentialReal1DClass* id = new DataExponentialReal1DClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . DataExponentialReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataExponentialReal1DClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataFuncReal1DClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . DataExponentialReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataExponentialReal1DClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataFuncReal1DClass::DecodeThis(buffer);
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
BaseDataObject * DataExponentialReal1DClass::BaseDataObjectExample()
{ 
  //cout << "Make ExponentialReal1D Example\n";
  return (BaseDataObject *) new BaseDataExponentialReal1D();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . DataExponentialReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataExponentialReal1DClass*& obj)
{
  obj = new DataExponentialReal1DClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . .  BaseDataExponentialReal1D
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataExponentialReal1D*& obj)
{
  obj = new BaseDataExponentialReal1D;
  return obj->DecodeThis(buffer);
}
/*S BaseDataPowerReal1D
 */ 
/*F BaseDataPowerReal1D()  . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataPowerReal1D::BaseDataPowerReal1D()
  : Exponent(0.0)
{
  Identification = ODREALFUNC_POWER_ID;
  NameTag = ODREALFUNC_POWER_NAME;
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataPowerReal1D(data)  . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataPowerReal1D::BaseDataPowerReal1D(const BaseDataPowerReal1D& data)
  : BaseDataFuncReal1D(data),
    Exponent(data.Exponent)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . .  Read in BaseDataPowerReal1D
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**    The input is as follows:
**    - The name of the function
**    - The constant in front of the exponential
**    - The multiplicative constant in the exponent
**    - The offset on the exponent
**
**  REMARKS
**
*/
bool BaseDataPowerReal1D::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput strin(in,' ');
  NameTag = strin.ReadNext();

  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . .  Read in BaseDataPowerReal1D
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**    The input is as follows:
**    - The constant in front of the exponential
**    - The multiplicative constant in the exponent
**    - The offset on the exponent
**
**  REMARKS
**
*/
bool BaseDataPowerReal1D::Read(istream& in, DataObjectClass* objc, const String& name)
{
  BaseDataFuncReal1D::Read(in,objc,name);
  bool result = true;
  
  StreamObjectInput strin(in,' ');

  String key = strin.ReadNext();
  if(key == ODREALFUNC_POWER_NAME)
    {
      String cval = strin.ReadNext();
      Exponent = cval.ToFloat();
    }
  else
    {
      cerr << "Expecting '" << ODREALFUNC_POWER_NAME << "' got '" << key << endl;
      result = false;
    }
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . .  BaseDataPowerReal1D
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataPowerReal1D::print(ostream& out) const
{
  BaseDataFuncReal1D::print(out);
  
  out << "The Power: ";
  out << " x ^ ( ";
  out << Exponent;
  out << " )";

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . .  BaseDataPowerReal1D
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataPowerReal1D::Clone()
{
  BaseDataPowerReal1D *obj = new BaseDataPowerReal1D(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . .  BaseDataPowerReal1D
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataPowerReal1D::CopyClone(Identify * obj)
{
  BaseDataPowerReal1D *objfull = (BaseDataPowerReal1D *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . .  BaseDataPowerReal1D
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPowerReal1D::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataFuncReal1D::EncodeThis(buffer);
  result = result && Encode(buffer,Exponent);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . .  BaseDataPowerReal1D
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPowerReal1D::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataFuncReal1D::DecodeThis(buffer);
  result = result && Decode(buffer,Exponent);
  return result;
}
/*F ans = operator()(x) . . . . . . . . . . . . . . . . . . . Linear function
**
**  DESCRIPTION
**    x: The given x value
**    ans: The y value of the exponential
**
**  REMARKS
**
*/
double BaseDataPowerReal1D::operator()(const double x)
{
  return pow(x,Exponent);
}
/*F ans = operator()(x) . . . . . . . . . . . . . . .  BaseDataRealPower1D
**
**  DESCRIPTION
**    x: The argument to the function
**    ans: The constant value
**
**  REMARKS
**
*/
double BaseDataPowerReal1D::operator()(const double x, 
					  BaseDataParameterSet *parameters,
					  DataParameterSetClass *parclass)
{
  VectorNumeric *vec = NumericVectorFromParameters(parameters,parclass);
  if(vec->size() == 1)
    {
      Exponent = (*vec)[0];
    }
  else
    {
      cerr << "Parameter set size not correct for Power (expected 3): " << vec->size() << endl;
    }
  return operator()(x);
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
bool BaseDataPowerReal1D::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataFuncReal1D::WriteAsLine(out,objc);
  out << "x^( " << Exponent << " )" << endl;
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
bool BaseDataPowerReal1D::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataFuncReal1D::WriteAsASCII(out,objc);
  out << " " << ODREALFUNC_POWER_NAME;
  out << " " << Exponent;
  out << endl;
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
bool BaseDataPowerReal1D::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataFuncReal1D::WriteAsLatex(out,objc);
  out << "$ x^(" << Exponent << ")$" << endl;
  return result;
}
/*S DataPowerReal1DClass
 */
/*F DataPowerReal1DClass() . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataPowerReal1DClass::DataPowerReal1DClass()
{
} 
/*F DataPowerReal1DClass(data) . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataPowerReal1DClass::DataPowerReal1DClass(const DataPowerReal1DClass& data)
  : DataFuncReal1DClass(data)
  // the rest
{
} 
 
/*F DataPowerReal1DClass(id,name,descr)  . . . . . . . . . . . constructor
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
DataPowerReal1DClass::DataPowerReal1DClass(const int id, 
						 const String& name,
						 const String& descr)
  : DataFuncReal1DClass(id,name,descr)
{
  SubClass = ODREALFUNC_BASE_NAME;
  EncodeDecodeClass = ODREALFUNC_POWER_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . DataPowerReal1DClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataPowerReal1DClass::print(ostream& out) const
{
  DataFuncReal1DClass::print(out);
  out << NameTag << "  ";
  // the rest
           
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . DataPowerReal1DClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataPowerReal1DClass, there is no further information.
**
**  REMARKS
**
*/
bool DataPowerReal1DClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataFuncReal1DClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . DataPowerReal1DClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataPowerReal1DClass::CopyClone(Identify *  objc)
{
  DataPowerReal1DClass *objcfull = (DataPowerReal1DClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . DataPowerReal1DClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataPowerReal1DClass::Clone()
{
  DataPowerReal1DClass* id = new DataPowerReal1DClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . DataPowerReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPowerReal1DClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataFuncReal1DClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . DataPowerReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPowerReal1DClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataFuncReal1DClass::DecodeThis(buffer);
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
BaseDataObject * DataPowerReal1DClass::BaseDataObjectExample()
{ 
  //cout << "Make PowerReal1D Example\n";
  return (BaseDataObject *) new BaseDataPowerReal1D();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . DataPowerReal1DClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataPowerReal1DClass*& obj)
{
  obj = new DataPowerReal1DClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . .  BaseDataPowerReal1D
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataPowerReal1D*& obj)
{
  obj = new BaseDataPowerReal1D;
  return obj->DecodeThis(buffer);
}
/*S Utilities
 */
 
/*F ans = ConvertNumericString(sval)  . . . . . . . . . . .  string to double
**
**  DESCRIPTION
**    sval: The number as string
**    ans: The numeric value
**
**    This routine converts the string using 'ToFloat' 
**    unless the string is equal to '+Infintiy' or 
**    '-Infinity'
** 
**  REMARKS
**
*/
double ConvertNumericString(String& sval)
{
  double ans;
  
  if(sval == HIGHEST_POSSIBLE_REAL_NAME)
    ans = HIGHEST_POSSIBLE_REAL;
  else if(sval == LOWEST_POSSIBLE_REAL_NAME)
    ans = LOWEST_POSSIBLE_REAL;
  else
    ans = sval.ToFloat();
  return ans;
}

/*F InitialSetOfLogicalEncodeDecodeRoutines() . . . . . . . . . . . . logical
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialSetOfODRealEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataFuncReal1DClass,BaseDataFuncReal1D,ODREALFUNC_BASE_NAME);
  EncodeDecodeRegisterClass(DataConstantReal1DClass,BaseDataConstantReal1D,ODREALFUNC_CONSTANT_NAME);
  EncodeDecodeRegisterClass(DataLinearReal1DClass,BaseDataLinearReal1D,ODREALFUNC_LINEAR_NAME);
  EncodeDecodeRegisterClass(DataGaussianReal1DClass,BaseDataGaussianReal1D,ODREALFUNC_GAUSSIAN_NAME);
  EncodeDecodeRegisterClass(DataPyramidFunctionClass,BaseDataPyramidFunction,ODREALFUNC_PYRAMID_NAME);
  EncodeDecodeRegisterClass(DataExponentialReal1DClass,BaseDataExponentialReal1D,ODREALFUNC_EXPONENTIAL_NAME);
  EncodeDecodeRegisterClass(DataPowerReal1DClass,BaseDataPowerReal1D,ODREALFUNC_POWER_NAME);
}
/*F AddFunctionClasses(set)  . . . . . . . . . . add to DataSetOfObjectsClass
**
**  DESCRIPTION
**    set: The set of classes of objects to add the numeric classes to
**
**  REMARKS
**
*/
void AddFunctionClasses(DataSetOfObjectsClass& set)
{
  String funcdescr("One Dimensional Function Class");
  String constdescr("Constant Function");
  String lindescr("Linear Function");
  String gaussdescr("Gaussian Function");
  String pyramiddescr("Pyramid Function");
  String expdescr("Exponential Function");
  String powerdescr("Power Function");
  
  DataFuncReal1DClass funcclass(ODREALFUNC_BASE_ID,ODREALFUNC_BASE_NAME,funcdescr);
  DataConstantReal1DClass constclass(ODREALFUNC_CONSTANT_ID,ODREALFUNC_CONSTANT_NAME,constdescr);
  DataLinearReal1DClass linclass(ODREALFUNC_LINEAR_ID,ODREALFUNC_LINEAR_NAME,lindescr);
  DataGaussianReal1DClass gaussclass(ODREALFUNC_GAUSSIAN_ID,ODREALFUNC_GAUSSIAN_NAME,gaussdescr);
  DataPyramidFunctionClass pyramidclass(ODREALFUNC_PYRAMID_ID,ODREALFUNC_PYRAMID_NAME,pyramiddescr);
  DataExponentialReal1DClass expclass(ODREALFUNC_EXPONENTIAL_ID,ODREALFUNC_EXPONENTIAL_NAME,expdescr);
  DataPowerReal1DClass powerclass(ODREALFUNC_POWER_ID,ODREALFUNC_POWER_NAME,powerdescr);

  set.AddObjectClass(funcclass);
  set.AddObjectClass(constclass);
  set.AddObjectClass(linclass);
  set.AddObjectClass(gaussclass);
  set.AddObjectClass(pyramidclass);
  set.AddObjectClass(expclass);
  set.AddObjectClass(powerclass);
  
}
