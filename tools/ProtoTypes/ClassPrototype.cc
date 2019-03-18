/*S BaseData=Object=
 */ 
/*F BaseData=Object=()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseData=Object=::BaseData=Object=()
{
  Identification = _ID;
  NameTag = _NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseData=Object=(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseData=Object=::BaseData=Object=(const BaseData=Object=& data)
  : BaseData=SubClass=(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseData=Object=
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseData=Object=::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseData=Object=
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseData=Object=::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseData=SubClass=::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseData=Object=
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseData=Object=::print(ostream& out) const
{
  BaseData=SubClass=::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseData=Object=
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseData=Object=::Clone()
{
  BaseData=Object= *obj = new BaseData=Object=(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseData=Object=
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseData=Object=::CopyClone(Identify * obj)
{
  BaseData=Object= *objfull = (BaseData=Object= *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseData=Object=
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseData=Object=::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseData=SubClass=::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseData=Object=
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseData=Object=::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseData=SubClass=::DecodeThis(buffer);
  // The rest

  return result;
}
 
 
/*S Data=Object=Class
 */
/*F Data=Object=Class() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
Data=Object=Class::Data=Object=Class()
{
  Identification = _ID;
  NameTag = _NAME;
  SubClass = "=SubClass=";
  EncodeDecodeClass = NameTag;
} 
/*F Data=Object=Class(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
Data=Object=Class::Data=Object=Class(const Data=Object=Class& data)
  : Data=SubClass=Class(data)
{
} 
 
/*F Data=Object=Class(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
Data=Object=Class::Data=Object=Class(const int id, 
				 const String& name,
				 const String& descr)
  : Data=SubClass=Class(id,name,descr)
{
  SubClass = "=SubClass=";
  EncodeDecodeClass = "=Object=";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . Data=Object=Class
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& Data=Object=Class::print(ostream& out) const
{
  Data=SubClass=Class::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . Data=Object=Class
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base Data=Object=Class, there is no further information.
**
**  REMARKS
**
*/
bool Data=Object=Class::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = Data=SubClass=Class::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . Data=Object=Class
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void Data=Object=Class::CopyClone(Identify *  objc)
{
  Data=Object=Class *objcfull = (Data=Object=Class *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . Data=Object=Class
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * Data=Object=Class::Clone()
    {
      Data=Object=Class* id = new Data=Object=Class(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . Data=Object=Class
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool Data=Object=Class::EncodeThis(CommBuffer& buffer)
{
  bool result = Data=SubClass=Class::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . Data=Object=Class
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool Data=Object=Class::DecodeThis(CommBuffer& buffer)
{
  bool result = Data=SubClass=Class::DecodeThis(buffer);
  //result = result && PointerDecode(buffer,(BaseDataObject *&) Class);
  //result = result && Decode(buffer,-----);

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
BaseDataObject * Data=Object=Class::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseData=Object=();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . Data=Object=Class
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, Data=Object=Class*& obj)
     {
     obj = new Data=Object=Class;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseData=Object=
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseData=Object=*& obj)
     {
     obj = new BaseData=Object=;
     return obj->DecodeThis(buffer);
     }
//EncodeDecodeRegisterClass(Data=Object=Class,BaseData=Object=,_NAME);
//String descr("The Class");
//Data=Object=Class class(_ID,_NAME,descr);
//set.AddObjectClass(class);
