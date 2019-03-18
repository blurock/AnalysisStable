/*  FILE     MenuObjects.cc
**  PACKAGE  MenuObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "MenuObjects" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#define TEMPLATE_INSTANTIATION
#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "MenuObjects.hh"

/*S BaseDataMenuBaseObject
 */ 
/*F BaseDataMenuBaseObject()  . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataMenuBaseObject::BaseDataMenuBaseObject()
{
  Identification = MENUOBJECTS_BASEOBJECT_ID;
  NameTag = MENUOBJECTS_BASEOBJECT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataMenuBaseObject(data)  . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataMenuBaseObject::BaseDataMenuBaseObject(const BaseDataMenuBaseObject& data)
  : BaseDataObject(data),
    Command(data.Command),
    KeyWord(data.KeyWord)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . .  Read in BaseDataMenuBaseObject
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataMenuBaseObject::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . .  Read in BaseDataMenuBaseObject
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataMenuBaseObject::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);

  StreamObjectInput str(in,' ');
  Command = str.ReadNext();
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataMenuBaseObject::print(ostream& out) const
{
  BaseDataObject::print(out);
  cout << "Command: " << Command << endl;

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataMenuBaseObject::Clone()
{
  BaseDataMenuBaseObject *obj = new BaseDataMenuBaseObject;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataMenuBaseObject::CopyClone(Identify * obj)
{
  BaseDataMenuBaseObject *objfull = (BaseDataMenuBaseObject *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMenuBaseObject::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && Encode(buffer,Command);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMenuBaseObject::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && Decode(buffer,Command);

  return result;
}
/*F  command = getCommand() . . . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    command: The current command
**
**  REMARKS
**
*/
String BaseDataMenuBaseObject::getCommand()
{
  return Command;
}
/*F setCommand(command) . . . . . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    command: Set current command
**
**  REMARKS
**
*/
void BaseDataMenuBaseObject::setCommand(String command)
{
  Command = command;
}
/*F  keyword = getKeyWord() . . . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    keyword: The current keyword of the object
**
**  REMARKS
**
*/
String BaseDataMenuBaseObject::getKeyWord()
{
  return KeyWord;
}
/*F setKeyWord(keyword) . . . . . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    keyword: Set current object keyword
**
**  REMARKS
**
*/
void BaseDataMenuBaseObject::setKeyWord(String keyword)
{
  KeyWord = keyword;
}
/*F ans = Write(out,objc) . . . . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The menu class
**
**  REMARKS
**
*/
bool BaseDataMenuBaseObject::Write(ostream& out, DataObjectClass *objc)
{
  out << KeyWord << endl;
  if(Command.size() > 1)
    {
      out << "command=" << Command << endl;
      out << "activeCommunication=TRUE" << endl;
    }

  return true;
}
/*S DataMenuBaseObjectClass
 */
/*F DataMenuBaseObjectClass() . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataMenuBaseObjectClass::DataMenuBaseObjectClass()
{
  Identification = MENUOBJECTS_BASEOBJECT_ID;
  NameTag = MENUOBJECTS_BASEOBJECT_NAME;
  SubClass = "Object";
  EncodeDecodeClass = NameTag;
} 
/*F DataMenuBaseObjectClass(data) . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataMenuBaseObjectClass::DataMenuBaseObjectClass(const DataMenuBaseObjectClass& data)
  : DataObjectClass(data)
{
} 
 
/*F DataMenuBaseObjectClass(id,name,descr)  . . . . . . . . . . . constructor
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
DataMenuBaseObjectClass::DataMenuBaseObjectClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataObjectClass(id,name,descr)
{
  SubClass = "Object";
  EncodeDecodeClass = MENUOBJECTS_BASEOBJECT_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . DataMenuBaseObjectClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataMenuBaseObjectClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . DataMenuBaseObjectClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataMenuBaseObjectClass, there is no further information.
**
**  REMARKS
**
*/
bool DataMenuBaseObjectClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . DataMenuBaseObjectClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataMenuBaseObjectClass::CopyClone(Identify *  objc)
{
  DataMenuBaseObjectClass *objcfull = (DataMenuBaseObjectClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . DataMenuBaseObjectClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataMenuBaseObjectClass::Clone()
    {
      DataMenuBaseObjectClass* id = new DataMenuBaseObjectClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . DataMenuBaseObjectClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMenuBaseObjectClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . DataMenuBaseObjectClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMenuBaseObjectClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataMenuBaseObjectClass::BaseDataObjectExample()
{ 
  //cout << "Make MenuBaseObject Example\n";
  return (BaseDataObject *) new BaseDataMenuBaseObject();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . DataMenuBaseObjectClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataMenuBaseObjectClass*& obj)
     {
     obj = new DataMenuBaseObjectClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataMenuBaseObject*& obj)
     {
     obj = new BaseDataMenuBaseObject;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataMenuText
 */ 
/*F BaseDataMenuText()  . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataMenuText::BaseDataMenuText()
{
  Identification = MENUOBJECTS_MENUTEXT_ID;
  NameTag = MENUOBJECTS_MENUTEXT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

  setKeyWord("TEXT");
} 
/*F BaseDataMenuText(data)  . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataMenuText::BaseDataMenuText(const BaseDataMenuText& data)
  : BaseDataMenuBaseObject(data),
    Text(data.Text)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . .  Read in BaseDataMenuText
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataMenuText::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . .  Read in BaseDataMenuText
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataMenuText::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataMenuBaseObject::Read(in,objc,name);
  
  String str;
  String d("\n");
  str.ReadFullLine(in);
  while(!(str == "END"))
    {
      Text.AppendToEnd(str);
      Text.AppendToEnd(d);
    }

  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . .  BaseDataMenuText
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataMenuText::print(ostream& out) const
{
  BaseDataMenuBaseObject::print(out);
  Text.print(out);

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . .  BaseDataMenuText
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataMenuText::Clone()
{
  BaseDataMenuText *obj = new BaseDataMenuText;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . .  BaseDataMenuText
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataMenuText::CopyClone(Identify * obj)
{
  BaseDataMenuText *objfull = (BaseDataMenuText *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . .  BaseDataMenuText
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMenuText::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMenuBaseObject::EncodeThis(buffer);
  result = result && Encode(buffer,Text);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . .  BaseDataMenuText
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMenuText::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMenuBaseObject::DecodeThis(buffer);
  result = result && Decode(buffer,Text);

  return result;
}
/*F  command = getText()  . . . . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    text: The current text
**
**  REMARKS
**
*/
String BaseDataMenuText::getText()
{
  return Text;
}
/*F setText(text) . . . . . . . . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    command: Set current command
**
**  REMARKS
**
*/
void BaseDataMenuText::setText(String text)
{
  Text = text;
}
/*F ans = Write(out,objc) . . . . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The menu class
**
**  REMARKS
**
*/
bool BaseDataMenuText::Write(ostream& out, DataObjectClass *objc)
{
  BaseDataMenuBaseObject::Write(out,objc);
  out << Text << endl;
  out << "END" << getKeyWord() << endl;

  return true;
}

/*S DataMenuTextClass
 */
/*F DataMenuTextClass() . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataMenuTextClass::DataMenuTextClass()
{
  Identification = MENUOBJECTS_MENUTEXT_ID;
  NameTag = MENUOBJECTS_MENUTEXT_NAME;
  SubClass = MENUOBJECTS_BASEOBJECT_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataMenuTextClass(data) . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataMenuTextClass::DataMenuTextClass(const DataMenuTextClass& data)
  : DataMenuBaseObjectClass(data)
{
} 
 
/*F DataMenuTextClass(id,name,descr)  . . . . . . . . . . . . . . constructor
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
DataMenuTextClass::DataMenuTextClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataMenuBaseObjectClass(id,name,descr)
{
  SubClass = MENUOBJECTS_BASEOBJECT_NAME;
  EncodeDecodeClass = MENUOBJECTS_MENUTEXT_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . DataMenuTextClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataMenuTextClass::print(ostream& out) const
{
  DataMenuBaseObjectClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . DataMenuTextClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataMenuTextClass, there is no further information.
**
**  REMARKS
**
*/
bool DataMenuTextClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataMenuBaseObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . DataMenuTextClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataMenuTextClass::CopyClone(Identify *  objc)
{
  DataMenuTextClass *objcfull = (DataMenuTextClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . DataMenuTextClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataMenuTextClass::Clone()
    {
      DataMenuTextClass* id = new DataMenuTextClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . DataMenuTextClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMenuTextClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataMenuBaseObjectClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . DataMenuTextClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMenuTextClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataMenuBaseObjectClass::DecodeThis(buffer);
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
BaseDataObject * DataMenuTextClass::BaseDataObjectExample()
{ 
  //cout << "Make MenuText Example\n";
  return (BaseDataObject *) new BaseDataMenuText();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . DataMenuTextClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataMenuTextClass*& obj)
     {
     obj = new DataMenuTextClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . .  BaseDataMenuText
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataMenuText*& obj)
     {
     obj = new BaseDataMenuText;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataMenuTextChoice
 */ 
/*F BaseDataMenuTextChoice()  . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataMenuTextChoice::BaseDataMenuTextChoice()
{
  Identification = MENUOBJECTS_MENUTEXTCHOICE_ID;
  NameTag = MENUOBJECTS_MENUTEXTCHOICE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

  setKeyWord("TEXTCHOICE");
  String delimitor("\n");
  Choice.ChangeDelimitor(delimitor);
} 
/*F BaseDataMenuTextChoice(data)  . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataMenuTextChoice::BaseDataMenuTextChoice(const BaseDataMenuTextChoice& data)
  : BaseDataMenuBaseObject(data),
    Choice(data.Choice)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . .  Read in BaseDataMenuTextChoice
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataMenuTextChoice::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . .  Read in BaseDataMenuTextChoice
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataMenuTextChoice::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataMenuBaseObject::Read(in,objc,name);
  StreamObjectInput str(in,' ');
  String n = str.ReadNext();
  while(!(n == "END"))
    {
      Choice.AddObject(name);
      n = str.ReadNext();
    }

  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . .  BaseDataMenuTextChoice
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataMenuTextChoice::print(ostream& out) const
{
  BaseDataMenuBaseObject::print(out);
  out << "Choice: " << Choice << endl;

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . .  BaseDataMenuTextChoice
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataMenuTextChoice::Clone()
{
  BaseDataMenuTextChoice *obj = new BaseDataMenuTextChoice;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . .  BaseDataMenuTextChoice
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataMenuTextChoice::CopyClone(Identify * obj)
{
  BaseDataMenuTextChoice *objfull = (BaseDataMenuTextChoice *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . .  BaseDataMenuTextChoice
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMenuTextChoice::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMenuBaseObject::EncodeThis(buffer);
  result = result && Encode(buffer,Choice);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . .  BaseDataMenuTextChoice
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMenuTextChoice::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMenuBaseObject::DecodeThis(buffer);
  result = result && Decode(buffer,Choice);

  return result;
}
/*F  choice = getChoice() . . . . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    choice: The current choice
**
**  REMARKS
**
*/
ObjectList<String>& BaseDataMenuTextChoice::getChoice()
{
  return Choice;
}
/*F setChoice(choice) . . . . . . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    choice: Set current choice text
**
**  REMARKS
**
*/
void BaseDataMenuTextChoice::setChoice(ObjectList<String>& choice)
{
  Choice = choice;
}
/*F addChoice(choice) . . . . . . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    choice: Set current choice text
**
**  REMARKS
**
*/
void BaseDataMenuTextChoice::addChoice(String& choice)
{
  Choice.AddObject(choice);
}
/*F ans = Write(out,objc) . . . . . . . . . . . . . .  BaseDataMenuBaseObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The menu class
**
**  REMARKS
**
*/
bool BaseDataMenuTextChoice::Write(ostream& out, DataObjectClass *objc)
{
  BaseDataMenuBaseObject::Write(out,objc);
  out << Choice << endl;
  out << "END" << getKeyWord() << endl;

  return true;
}

/*S DataMenuTextChoiceClass
 */
/*F DataMenuTextChoiceClass() . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataMenuTextChoiceClass::DataMenuTextChoiceClass()
{
  Identification = MENUOBJECTS_MENUTEXTCHOICE_ID;
  NameTag = MENUOBJECTS_MENUTEXTCHOICE_NAME;
  SubClass = MENUOBJECTS_MENUTEXTCHOICE_NAME;
  EncodeDecodeClass = NameTag;

} 
/*F DataMenuTextChoiceClass(data) . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataMenuTextChoiceClass::DataMenuTextChoiceClass(const DataMenuTextChoiceClass& data)
  : DataMenuBaseObjectClass(data)
{
} 
 
/*F DataMenuTextChoiceClass(id,name,descr)  . . . . . . . . . . . constructor
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
DataMenuTextChoiceClass::DataMenuTextChoiceClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataMenuBaseObjectClass(id,name,descr)
{
  SubClass = MENUOBJECTS_BASEOBJECT_NAME;
  EncodeDecodeClass = MENUOBJECTS_MENUTEXTCHOICE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . DataMenuTextChoiceClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataMenuTextChoiceClass::print(ostream& out) const
{
  DataMenuBaseObjectClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . DataMenuTextChoiceClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataMenuTextChoiceClass, there is no further information.
**
**  REMARKS
**
*/
bool DataMenuTextChoiceClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataMenuBaseObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . DataMenuTextChoiceClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataMenuTextChoiceClass::CopyClone(Identify *  objc)
{
  DataMenuTextChoiceClass *objcfull = (DataMenuTextChoiceClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . DataMenuTextChoiceClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataMenuTextChoiceClass::Clone()
    {
      DataMenuTextChoiceClass* id = new DataMenuTextChoiceClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . DataMenuTextChoiceClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMenuTextChoiceClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataMenuBaseObjectClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . DataMenuTextChoiceClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMenuTextChoiceClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataMenuBaseObjectClass::DecodeThis(buffer);
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
BaseDataObject * DataMenuTextChoiceClass::BaseDataObjectExample()
{ 
  //cout << "Make MenuTextChoice Example\n";
  return (BaseDataObject *) new BaseDataMenuTextChoice();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . DataMenuTextChoiceClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataMenuTextChoiceClass*& obj)
     {
     obj = new DataMenuTextChoiceClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . .  BaseDataMenuTextChoice
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataMenuTextChoice*& obj)
     {
     obj = new BaseDataMenuTextChoice;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataMenuComposite
 */ 
/*F BaseDataMenuComposite() . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataMenuComposite::BaseDataMenuComposite()
  : Object(NULL),
    Gridx("RELATIVE"),
    Gridy("RELATIVE"),
    Gridwidth("1"),
    Gridheight("1"),
    Weightx(0),
    Weighty(0),
    Anchor("CENTER"),
    Fill("NONE")
{
  Identification = MENUOBJECTS_MENUCOMPOSITE_ID;
  NameTag = MENUOBJECTS_MENUCOMPOSITE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

  setKeyWord("COMPOSITE");
} 
/*F BaseDataMenuComposite(data) . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataMenuComposite::BaseDataMenuComposite(const BaseDataMenuComposite& data)
  : BaseDataMenuBaseObject(data),
    Gridx(data.Gridx),
    Gridy(data.Gridy),
    Gridwidth(data.Gridwidth),
    Gridheight(data.Gridheight),
    Weightx(data.Weightx),
    Weighty(data.Weighty),
    Anchor(data.Anchor),
    Fill(data.Fill)
{
  Object = (BaseDataMenuBaseObject *) 
    PointerClone(data.Object);
}
/*F Read(in,objc) . . . . . . . . . . . . . . . Read in BaseDataMenuComposite
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataMenuComposite::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . Read in BaseDataMenuComposite
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataMenuComposite::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataMenuBaseObject::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . BaseDataMenuComposite
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataMenuComposite::print(ostream& out) const
{
  BaseDataMenuBaseObject::print(out);
  
  printParameters(out);
  PointerPrint(out,"Composite Object","No Composite Object",
	       (BaseDataObject *) Object);

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . BaseDataMenuComposite
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataMenuComposite::Clone()
{
  BaseDataMenuComposite *obj = new BaseDataMenuComposite;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . BaseDataMenuComposite
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataMenuComposite::CopyClone(Identify * obj)
{
  BaseDataMenuComposite *objfull = (BaseDataMenuComposite *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . BaseDataMenuComposite
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMenuComposite::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMenuBaseObject::EncodeThis(buffer);
  if(Object != NULL)
    {
      result = result && Encode(buffer,Object->EncodeDecodeClass);
      result = result && Object->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . BaseDataMenuComposite
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMenuComposite::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMenuBaseObject::DecodeThis(buffer);
  String name;
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    DecodeFromName(result,buffer,name,(Identify *&) Object);

  return result;
}
/*F setGrid(gridx,gridy,gridwidth,gridheight) . . . . . BaseDataMenuComposite
**
**  DESCRIPTION
**    gridx,gridy: The grid coordinates
**    gridwidth,gridheight: The grid dimensions
**
**  REMARKS
**
*/
void BaseDataMenuComposite::setGrid(String& gridx, String& gridy,
				    String& gridwidth, String& gridheight)
{
  Gridx = gridx;
  Gridy = gridy;
  Gridwidth = gridwidth;
  Gridheight = gridheight;
}
/*F setHeight(weightx,weighty)  . . . . . . . . . . . . BaseDataMenuComposite
**
**  DESCRIPTION
**    weightx,weighty: The weights
**
**  REMARKS
**
*/
void BaseDataMenuComposite::setWeight(unsigned int weightx, 
				      unsigned int weighty)
{
  Weightx = weightx;
  Weighty = weighty;
}
/*F setFill(fill) . . . . . . . . . . . . . . . . . . . BaseDataMenuComposite
**
**  DESCRIPTION
**    fill: Set the fill 
**
**  REMARKS
**
*/
void BaseDataMenuComposite::setFill(String& fill)
{
  Fill = fill;
}
/*F setAnchor(anchor) . . . . . . . . . . . . . . . . . BaseDataMenuComposite
**
**  DESCRIPTION
**    anchor: The anchor
**
**  REMARKS
**
*/
void BaseDataMenuComposite::setAnchor(String& anchor)
{
  Anchor = anchor;
}
/*F printParameters(out)  . . . . . . . . . . . . . . . BaseDataMenuComposite
**
**  DESCRIPTION
**    out: The output stream
**
**  REMARKS
**
*/
void BaseDataMenuComposite::printParameters(ostream& out) const
{
  out << "gridx = " << Gridx << endl;
  out << "gridy = " << Gridy << endl;
  out << "gridwidth = " << Gridwidth << endl;
  out << "gridheight = "<< Gridheight << endl;
}
/*F ans = Write(out,objc) . . . . . . . . . . . . . . . BaseDataMenuComposite
**
**  DESCRIPTION
**    out: The output stream
**    objc: The object class
**    ans: true if successful
**
**  REMARKS
**
*/
bool BaseDataMenuComposite::Write(ostream& out, DataObjectClass *objc)
{
  BaseDataMenuBaseObject::Write(out,objc);
  printParameters(out);
  DataMenuBaseObjectClass objclass;
  bool result = Object->Write(out,&objclass);
  if(result)
    out << "END" << getKeyWord() << endl;
  return result;
}
/*F setObject(obj)  . . . . . . . . . . . . . . . . . . BaseDataMenuComposite
**
**  DESCRIPTION
**    obj: The object
**
**  REMARKS
**
*/
void BaseDataMenuComposite::setObject(BaseDataMenuBaseObject *obj)
{
  if(Object != NULL)
    {
      delete Object;
    }
  Object->CopyClone(obj);
}
/*F obj = setObject() . . . . . . . . . . . . . . . . . BaseDataMenuComposite
**
**  DESCRIPTION
**     obj: The object
**
**  REMARKS
**
*/
BaseDataMenuBaseObject *BaseDataMenuComposite::getObject()
{
  return Object;
}
/*S DataMenuCompositeClass
 */
/*F DataMenuCompositeClass()  . . . . . . . . . . . . . BaseDataMenuComposite
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataMenuCompositeClass::DataMenuCompositeClass()
{
  Identification = MENUOBJECTS_MENUCOMPOSITE_ID;
  NameTag = MENUOBJECTS_MENUCOMPOSITE_NAME;
  SubClass = MENUOBJECTS_BASEOBJECT_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataMenuCompositeClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataMenuCompositeClass::DataMenuCompositeClass(const DataMenuCompositeClass& data)
  : DataMenuBaseObjectClass(data)
{
} 
 
/*F DataMenuCompositeClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataMenuCompositeClass::DataMenuCompositeClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataMenuBaseObjectClass(id,name,descr)
{
  SubClass = MENUOBJECTS_BASEOBJECT_NAME;
  EncodeDecodeClass = MENUOBJECTS_MENUCOMPOSITE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataMenuCompositeClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataMenuCompositeClass::print(ostream& out) const
{
  DataMenuBaseObjectClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataMenuCompositeClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataMenuCompositeClass, there is no further information.
**
**  REMARKS
**
*/
bool DataMenuCompositeClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataMenuBaseObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataMenuCompositeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataMenuCompositeClass::CopyClone(Identify *  objc)
{
  DataMenuCompositeClass *objcfull = (DataMenuCompositeClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataMenuCompositeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataMenuCompositeClass::Clone()
    {
      DataMenuCompositeClass* id = new DataMenuCompositeClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataMenuCompositeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMenuCompositeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataMenuBaseObjectClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataMenuCompositeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMenuCompositeClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataMenuBaseObjectClass::DecodeThis(buffer);
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
BaseDataObject * DataMenuCompositeClass::BaseDataObjectExample()
{ 
  //cout << "Make MenuComposite Example\n";
  return (BaseDataObject *) new BaseDataMenuComposite();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataMenuCompositeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataMenuCompositeClass*& obj)
     {
     obj = new DataMenuCompositeClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataMenuComposite
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataMenuComposite*& obj)
     {
     obj = new BaseDataMenuComposite;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataMenuComposition
 */ 
/*F BaseDataMenuComposition()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataMenuComposition::BaseDataMenuComposition()
{
  Identification = MENUOBJECTS_MENUCOMPOSITION_ID;
  NameTag = MENUOBJECTS_MENUCOMPOSITION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

  setKeyWord("COMPOSITION");
} 
/*F BaseDataMenuComposition(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataMenuComposition::BaseDataMenuComposition(const BaseDataMenuComposition& data)
  : BaseDataMenuBaseObject(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataMenuComposition
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataMenuComposition::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataMenuComposition
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataMenuComposition::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataMenuBaseObject::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataMenuComposition
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataMenuComposition::print(ostream& out) const
{
  BaseDataMenuBaseObject::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataMenuComposition
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataMenuComposition::Clone()
{
  BaseDataMenuComposition *obj = new BaseDataMenuComposition;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataMenuComposition
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataMenuComposition::CopyClone(Identify * obj)
{
  BaseDataMenuComposition *objfull = (BaseDataMenuComposition *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMenuComposition
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMenuComposition::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMenuBaseObject::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMenuComposition
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMenuComposition::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMenuBaseObject::DecodeThis(buffer);
  // The rest

  return result;
}
/*F ans = Write(out,objc) . . . . . . . . . . . . . . . BaseDataMenuComposition
**
**  DESCRIPTION
**    out: The output stream
**    objc: The object class
**    ans: true if successful
**
**  REMARKS
**
*/
bool BaseDataMenuComposition::Write(ostream& out, DataObjectClass *objc)
{
  return BaseDataMenuBaseObject::Write(out,objc);
}
 
/*S DataMenuCompositionClass
 */
/*F DataMenuCompositionClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataMenuCompositionClass::DataMenuCompositionClass()
{
  Identification = MENUOBJECTS_MENUCOMPOSITION_ID;
  NameTag = MENUOBJECTS_MENUCOMPOSITION_NAME;
  SubClass = MENUOBJECTS_BASEOBJECT_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataMenuCompositionClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataMenuCompositionClass::DataMenuCompositionClass(const DataMenuCompositionClass& data)
  : DataMenuBaseObjectClass(data)
{
} 
 
/*F DataMenuCompositionClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataMenuCompositionClass::DataMenuCompositionClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataMenuBaseObjectClass(id,name,descr)
{
  SubClass = MENUOBJECTS_BASEOBJECT_NAME;
  EncodeDecodeClass = MENUOBJECTS_MENUCOMPOSITION_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataMenuCompositionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataMenuCompositionClass::print(ostream& out) const
{
  DataMenuBaseObjectClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataMenuCompositionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataMenuCompositionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataMenuCompositionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataMenuBaseObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataMenuCompositionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataMenuCompositionClass::CopyClone(Identify *  objc)
{
  DataMenuCompositionClass *objcfull = (DataMenuCompositionClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataMenuCompositionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataMenuCompositionClass::Clone()
    {
      DataMenuCompositionClass* id = new DataMenuCompositionClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataMenuCompositionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMenuCompositionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataMenuBaseObjectClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataMenuCompositionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMenuCompositionClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataMenuBaseObjectClass::DecodeThis(buffer);
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
BaseDataObject * DataMenuCompositionClass::BaseDataObjectExample()
{ 
  //cout << "Make MenuComposition Example\n";
  return (BaseDataObject *) new BaseDataMenuComposition();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataMenuCompositionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataMenuCompositionClass*& obj)
     {
     obj = new DataMenuCompositionClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataMenuComposition
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataMenuComposition*& obj)
     {
     obj = new BaseDataMenuComposition;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataMenuWindow
 */ 
/*F BaseDataMenuWindow()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataMenuWindow::BaseDataMenuWindow()
  : MenuObject(NULL)
{
  Identification = MENUOBJECTS_MENUCOMPOSITION_ID;
  NameTag = MENUOBJECTS_MENUCOMPOSITION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

  //setKeyWord("WINDOW");
} 
/*F BaseDataMenuWindow(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataMenuWindow::BaseDataMenuWindow(const BaseDataMenuWindow& data)
  : BaseDataMenuBaseObject(data)
{
  MenuObject = (BaseDataMenuBaseObject *) 
    PointerClone(data.MenuObject);
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataMenuWindow
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataMenuWindow::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataMenuWindow
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataMenuWindow::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataMenuBaseObject::Read(in,objc,name);
  BaseDataMenuWindow objclass;

  MenuObject->Read(in,(DataObjectClass *) &objclass,name);

  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataMenuWindow
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataMenuWindow::print(ostream& out) const
{
  BaseDataMenuBaseObject::print(out);
  PointerPrint(out,"Window Object","No Window Object",
	       (BaseDataObject *) MenuObject);

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataMenuWindow
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataMenuWindow::Clone()
{
  BaseDataMenuWindow *obj = new BaseDataMenuWindow;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataMenuWindow
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataMenuWindow::CopyClone(Identify * obj)
{
  BaseDataMenuWindow *objfull = (BaseDataMenuWindow *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMenuWindow
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMenuWindow::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMenuBaseObject::EncodeThis(buffer);
  if(MenuObject != NULL)
    {
      result = result && Encode(buffer,MenuObject->EncodeDecodeClass);
      result = result && MenuObject->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMenuWindow
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMenuWindow::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMenuBaseObject::DecodeThis(buffer);
  String name;
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    DecodeFromName(result,buffer,name,(Identify *&) MenuObject);

  return result;
}
/*F obj = getMenuObject() . . . . . . . . . . . . . . . .  BaseDataMenuWindow
**
**  DESCRIPTION
**    obj: The object
**
**  REMARKS
**
*/
BaseDataMenuBaseObject *BaseDataMenuWindow::getMenuObject()
{
  return MenuObject;
}
/*F   . . . . . . . . . . . . . . . .  BaseDataMenuWindow
**
**  DESCRIPTION
**
**  REMARKS
**
*/
void BaseDataMenuWindow::setMenuObject(BaseDataMenuBaseObject *obj)
{
  MenuObject = (BaseDataMenuBaseObject *) 
    PointerClone(obj);
}

/*F   . . . . . . . . . . . . . . . .  BaseDataMenuWindow
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool BaseDataMenuWindow::Write(ostream& out, DataObjectClass *objc)
{
  out << "SERVERSENDDATA" << endl;
  BaseDataMenuBaseObject::Write(out,objc);
  bool result = MenuObject->Write(out,objc);
  //if(result)
  //out << "END" << getKeyWord() << endl;
  out << "END" << endl;
  out << "ENDSERVERSENDDATA" << endl;
  
  return result;
}
/*S DataMenuWindowClass
 */
/*F DataMenuWindowClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataMenuWindowClass::DataMenuWindowClass()
{
  Identification = MENUOBJECTS_MENUCOMPOSITION_ID;
  NameTag = MENUOBJECTS_MENUCOMPOSITION_NAME;
  SubClass = "MenuBaseObject";
  EncodeDecodeClass = NameTag;
} 
/*F DataMenuWindowClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataMenuWindowClass::DataMenuWindowClass(const DataMenuWindowClass& data)
  : DataMenuBaseObjectClass(data)
{
} 
 
/*F DataMenuWindowClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataMenuWindowClass::DataMenuWindowClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataMenuBaseObjectClass(id,name,descr)
{
  SubClass = "MenuBaseObject";
  EncodeDecodeClass = MENUOBJECTS_MENUCOMPOSITION_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataMenuWindowClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataMenuWindowClass::print(ostream& out) const
{
  DataMenuBaseObjectClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataMenuWindowClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataMenuWindowClass, there is no further information.
**
**  REMARKS
**
*/
bool DataMenuWindowClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataMenuBaseObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataMenuWindowClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataMenuWindowClass::CopyClone(Identify *  objc)
{
  DataMenuWindowClass *objcfull = (DataMenuWindowClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataMenuWindowClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataMenuWindowClass::Clone()
    {
      DataMenuWindowClass* id = new DataMenuWindowClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataMenuWindowClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMenuWindowClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataMenuBaseObjectClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataMenuWindowClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMenuWindowClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataMenuBaseObjectClass::DecodeThis(buffer);
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
BaseDataObject * DataMenuWindowClass::BaseDataObjectExample()
{ 
  //cout << "Make MenuWindow Example\n";
  return (BaseDataObject *) new BaseDataMenuWindow();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataMenuWindowClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataMenuWindowClass*& obj)
     {
     obj = new DataMenuWindowClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataMenuWindow
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataMenuWindow*& obj)
     {
     obj = new BaseDataMenuWindow;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataMenuCoreObject
 */ 
/*F BaseDataMenuCoreObject()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataMenuCoreObject::BaseDataMenuCoreObject()
  : Object(NULL),
    ClassObject(true)
{
  Identification = MENUOBJECTS_COREOBJECT_ID;
  NameTag = MENUOBJECTS_COREOBJECT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  
  setKeyWord("COREOBJECT");
} 
/*F BaseDataMenuCoreObject(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataMenuCoreObject::BaseDataMenuCoreObject(const BaseDataMenuCoreObject& data)
  : BaseDataMenuBaseObject(data)
{
  Object = (BaseDataMenuBaseObject *) 
    PointerClone(data.Object);  
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataMenuCoreObject
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataMenuCoreObject::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataMenuCoreObject
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataMenuCoreObject::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataMenuBaseObject::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataMenuCoreObject
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataMenuCoreObject::print(ostream& out) const
{
  BaseDataMenuBaseObject::print(out);

  PointerPrint(out,"Core Data Object","No Object",
	       (BaseDataObject *) Object);

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataMenuCoreObject
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataMenuCoreObject::Clone()
{
  BaseDataMenuCoreObject *obj = new BaseDataMenuCoreObject;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataMenuCoreObject
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataMenuCoreObject::CopyClone(Identify * obj)
{
  BaseDataMenuCoreObject *objfull = (BaseDataMenuCoreObject *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMenuCoreObject
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMenuCoreObject::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMenuBaseObject::EncodeThis(buffer);
  if(Object != NULL)
    {
      result = result && Encode(buffer,Object->EncodeDecodeClass);
      result = result && Object->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMenuCoreObject
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMenuCoreObject::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMenuBaseObject::DecodeThis(buffer);
  String name;
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    DecodeFromName(result,buffer,name,(Identify *&) Object);

  return result;
}
/*F ans = Write(out,objc) . . . . . . . . . . . . . .  BaseDataMenuCoreObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The object class
**    ans: true if successful
**
**  REMARKS
**
*/
bool BaseDataMenuCoreObject::Write(ostream& out, DataObjectClass *objc)
{
  BaseDataMenuBaseObject::Write(out,objc);
  DataMenuCoreObjectClass *objclass = (DataMenuCoreObjectClass *) objc;
  bool result = true;
  DataSetOfObjectsClass *allowed = objclass->PointerToAllowedClasses();
  DataObjectClass *cls;

  if(ClassObject)
    {
      cls = (DataObjectClass *) Object;
    }
  else
    {
      cls = allowed->GetObjectClass(Object->GetType());
    }
  if(ClassObject)
      {
	  out << "Class" << endl;
	  out << cls->SubClass << endl;
	  out << "coreText" << endl;
	  result = result && cls->WriteAsASCII(out);
	  out << endl;
	  out << "coreEndOfText" << endl;
      }
  else
      {
	  out << "Attribute" << endl;
	  out << cls->NameTag << endl;
	  out << Object->NameTag << endl;
	  out << "coreText" << endl;
	  result = result && Object->WriteAsASCII(out,cls);
	  out << endl;
	  out << "coreEndOfText" << endl;
      }
  if(result)
      out << "END" << getKeyWord() << endl;
  return result;
}
/*F setAsClassObject(obj) . . . . . . . . . . . . . .  BaseDataMenuCoreObject
**
**  DESCRIPTION
**    obj: The object
**
**  REMARKS
**
*/
void BaseDataMenuCoreObject::setAsClassObject(DataObjectClass *obj)
{
  if(Object != NULL)
    {
      delete Object;
    }
  Object = (BaseDataObject *) obj->Clone();
  ClassObject = true;
}
/*F setAttributeObject(obj) . . . . . . . . . . . . .  BaseDataMenuCoreObject
**
**  DESCRIPTION
**    obj: The object
**
**  REMARKS
**
*/
void BaseDataMenuCoreObject::setAsAttributeObject(BaseDataObject *obj)
{
  if(Object != NULL)
    {
      delete Object;
    }
  Object = (BaseDataObject *) obj->Clone();
  ClassObject = false;
}
/*F obj = getObject() . . . . . . . . . . . . . . . .  BaseDataMenuCoreObject
**
**  DESCRIPTION
**     obj: The object
**
**  REMARKS
**
*/
BaseDataObject *BaseDataMenuCoreObject::getObject()
{
  return Object;
}
/*S DataMenuCoreObjectClass
 */
/*F DataMenuCoreObjectClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataMenuCoreObjectClass::DataMenuCoreObjectClass()
{
  Identification = MENUOBJECTS_COREOBJECT_ID;
  NameTag = MENUOBJECTS_COREOBJECT_NAME;
  SubClass = "MenuBaseObject";
  EncodeDecodeClass = NameTag;
} 
/*F DataMenuCoreObjectClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataMenuCoreObjectClass::DataMenuCoreObjectClass(const DataMenuCoreObjectClass& data)
  : DataMenuBaseObjectClass(data)
{
} 
 
/*F DataMenuCoreObjectClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataMenuCoreObjectClass::DataMenuCoreObjectClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataMenuBaseObjectClass(id,name,descr)
{
  SubClass = "MenuBaseObject";
  EncodeDecodeClass = MENUOBJECTS_COREOBJECT_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataMenuCoreObjectClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataMenuCoreObjectClass::print(ostream& out) const
{
  DataMenuBaseObjectClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataMenuCoreObjectClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataMenuCoreObjectClass, there is no further information.
**
**  REMARKS
**
*/
bool DataMenuCoreObjectClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataMenuBaseObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataMenuCoreObjectClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataMenuCoreObjectClass::CopyClone(Identify *  objc)
{
  DataMenuCoreObjectClass *objcfull = (DataMenuCoreObjectClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataMenuCoreObjectClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataMenuCoreObjectClass::Clone()
    {
      DataMenuCoreObjectClass* id = new DataMenuCoreObjectClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataMenuCoreObjectClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMenuCoreObjectClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataMenuBaseObjectClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataMenuCoreObjectClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMenuCoreObjectClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataMenuBaseObjectClass::DecodeThis(buffer);
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
BaseDataObject * DataMenuCoreObjectClass::BaseDataObjectExample()
{ 
  //cout << "Make MenuCoreObject Example\n";
  return (BaseDataObject *) new BaseDataMenuCoreObject();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataMenuCoreObjectClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataMenuCoreObjectClass*& obj)
     {
     obj = new DataMenuCoreObjectClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataMenuCoreObject
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataMenuCoreObject*& obj)
     {
     obj = new BaseDataMenuCoreObject;
     return obj->DecodeThis(buffer);
     }
/*F classes = PointerToAllowedClasses() . . . . . . .  BaseDataMenuCoreObject
**
**  DESCRIPTION
**    classes: The allowed classes
**
**  REMARKS
**
*/
DataSetOfObjectsClass *DataMenuCoreObjectClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}
/*F ans = registerClass(classname,graphicsname); . . . . . . .  BaseDataMenuCoreObject
**
**  DESCRIPTION
**    classes: The allowed classes
**
**  REMARKS
**
*/
bool DataMenuCoreObjectClass::registerClass(String& classname)
{
  return Registry.AddKeyWord(classname);
}
/*F ans = isInList(classname) . . . . . . . . . . . .  BaseDataMenuCoreObject
**
**  DESCRIPTION
**    classname: The name of the class
**
**  REMARKS
**
*/
bool DataMenuCoreObjectClass::isInList(String& classname)
{
  return Registry.KeyWordInList(classname);
}
/*S Utilities
 */
/*F choice = NamesToMenuTextChoice(names,command) . . create a MenuTextChoice
**
**  DESCRIPTION
**     names: The list of names
**     command: The command
**
**  REMARKS
**
*/
BaseDataMenuTextChoice& NamesToMenuTextChoice(ObjectList<String>& names,
					      String& command)
{
  
  ObjectList<String> names1;
  ObjectList<String>::iterator str;
  for(str=names.begin();
      str != names.end();
      str++)
    {
      String name(" ");
      name.AppendToEnd(*str);
      names1.AddObject(name);
    }
  names1.ChangeDelimitor("\n");

  BaseDataMenuTextChoice *menu = new BaseDataMenuTextChoice;
  menu->setChoice(names1);
  menu->setCommand(command);

  return *menu;
}

/*S BaseDataMenuDirectedTreeObject
 */ 
/*F BaseDataMenuDirectedTreeObject()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataMenuDirectedTreeObject::BaseDataMenuDirectedTreeObject()
{
  Identification = MENUOBJECTS_DIRECTEDTREE_ID;
  NameTag = MENUOBJECTS_DIRECTEDTREE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

  Nodes.ChangeTitle("Nodes of Tree");
  Bonds.ChangeTitle("Bonds of Tree");
  Nodes.ChangeDelimitor("   ");
  Bonds.ChangeDelimitor("   ");
  setKeyWord("DIRECTEDGRAPH");
} 
/*F BaseDataMenuDirectedTreeObject(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataMenuDirectedTreeObject::BaseDataMenuDirectedTreeObject(const BaseDataMenuDirectedTreeObject& data)
  : BaseDataMenuBaseObject(data),
    Nodes(data.Nodes),
    Bonds(data.Bonds)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataMenuDirectedTreeObject
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataMenuDirectedTreeObject::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataMenuDirectedTreeObject
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataMenuDirectedTreeObject::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataMenuBaseObject::Read(in,objc,name);
  StreamObjectInput str(in,' ');
  String nodename = str.ReadNext();
  String son;
  while(!(nodename == "END"))
    {
      Nodes.AddObject(nodename);
      nodename = str.ReadNext();
    }

  nodename = str.ReadNext();
  while(!(nodename == "END"))
    {
      nodename = str.ReadNext();
      son = str.ReadNext();
      if(son == "END")
	{
	  nodename = son;
	  result = false;
	}
      else
	{
	  SymmetricPair<String> pair(nodename,son);
	  Bonds.AddObject(pair);
	  nodename = str.ReadNext();
	}
    }
  
  return result;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataMenuDirectedTreeObject
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataMenuDirectedTreeObject::print(ostream& out) const
{
  BaseDataMenuBaseObject::print(out);
  Nodes.print(out);
  out << endl;
  Bonds.print(out);
  out << endl;

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataMenuDirectedTreeObject
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataMenuDirectedTreeObject::Clone()
{
  BaseDataMenuDirectedTreeObject *obj = new BaseDataMenuDirectedTreeObject;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataMenuDirectedTreeObject
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataMenuDirectedTreeObject::CopyClone(Identify * obj)
{
  BaseDataMenuDirectedTreeObject *objfull = (BaseDataMenuDirectedTreeObject *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMenuDirectedTreeObject
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMenuDirectedTreeObject::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMenuBaseObject::EncodeThis(buffer);
  result = result && Nodes.EncodeThis(buffer);
  result = result && Bonds.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMenuDirectedTreeObject
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMenuDirectedTreeObject::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMenuBaseObject::DecodeThis(buffer);
  result = result && Nodes.DecodeThis(buffer);
  result = result && Bonds.DecodeThis(buffer);

  return result;
}
/*F nodes = getNodes()  . . . . . . . . . . . . . . . .  BaseDataMenuDirectedTreeObject
**
**  DESCRIPTION
**    nodes: The node names
**
**  REMARKS
**
*/
ObjectList<String>& BaseDataMenuDirectedTreeObject::getNodes()
{
  return Nodes;
}
/*F bonds = getBonds()  . . . . . . . . . . . . . . . .  BaseDataMenuDirectedTreeObject
**
**  DESCRIPTION
**    bonds: The bond names
**  REMARKS
**
*/
SymmetricPairList<String>& BaseDataMenuDirectedTreeObject::getBonds()
{
  return Bonds;
}
/*F AddNode(name)  . . . . . . . . . . . . . . . .  BaseDataMenuDirectedTreeObject
**
**  DESCRIPTION
**    name: The name of the node to add
**
**  REMARKS
**
*/
void BaseDataMenuDirectedTreeObject::AddNode(const String& node)
{
  Nodes.AddObject(node);
}
/*F AddBond(parent,son)  . . . . . . . . . . . . . . . .  BaseDataMenuDirectedTreeObject
**
**  DESCRIPTION
**    parent: The name of the parent node to add to bond
**    son: The name of the son node to add to bond
**
**  REMARKS
**
*/
void BaseDataMenuDirectedTreeObject::AddBond(const String& parent, const String& son)
{
  SymmetricPair<String> pair(parent,son);
  Bonds.AddObject(pair);
}
/*F SetRootNode(name) . . . . . . . . . . . .  BaseDataMenuDirectedTreeObject
**
**  DESCRIPTION
**    name: The name of the root node
**
**  REMARKS
**
*/
void BaseDataMenuDirectedTreeObject::SetRootNode(String& name)
{
  RootNode = name;
}
/*F name = GetRootNode()  . . . . . . . . . .  BaseDataMenuDirectedTreeObject
**
**  DESCRIPTION
**    name: The name of the root node
**
**  REMARKS
**
*/
String BaseDataMenuDirectedTreeObject::GetRootNode()
{
  return RootNode;
}

/*F ans = Write(out,objc) . . . . . . . . . .  BaseDataMenuDirectedTreeObject
**
**  DESCRIPTION
**  out: The output stream
**  objc: The class of the object to write
**  ans: true if successful
**
**  REMARKS 
**
*/
bool BaseDataMenuDirectedTreeObject::Write(ostream& out, DataObjectClass *objc)
{
  bool result = BaseDataMenuBaseObject::Write(out,objc);

  out << RootNode << endl;

  ObjectList<String>::iterator name;
  for(name = Nodes.begin();name != Nodes.end();name++)
    {
      out << *name << endl;
    }
  out << "END" << endl;
  SymmetricPairList<String>::iterator pair;
  for(pair = Bonds.begin();pair != Bonds.end();pair++)
    {
      out << (*pair).J << " " << (*pair).I << endl;
    }
  out << "END" << endl;
  out << "END" << getKeyWord() << endl;
  return result;
}

 
/*S DataMenuDirectedTreeObjectClass
 */
/*F DataMenuDirectedTreeObjectClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataMenuDirectedTreeObjectClass::DataMenuDirectedTreeObjectClass()
{
  Identification = MENUOBJECTS_DIRECTEDTREE_ID;
  NameTag = MENUOBJECTS_DIRECTEDTREE_NAME;
  SubClass = "MenuBaseObject";
  EncodeDecodeClass = NameTag;
} 
/*F DataMenuDirectedTreeObjectClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataMenuDirectedTreeObjectClass::DataMenuDirectedTreeObjectClass(const DataMenuDirectedTreeObjectClass& data)
  : DataMenuBaseObjectClass(data)
{
} 
 
/*F DataMenuDirectedTreeObjectClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataMenuDirectedTreeObjectClass::DataMenuDirectedTreeObjectClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataMenuBaseObjectClass(id,name,descr)
{
  SubClass = "MenuBaseObject";
  EncodeDecodeClass = MENUOBJECTS_DIRECTEDTREE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataMenuDirectedTreeObjectClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataMenuDirectedTreeObjectClass::print(ostream& out) const
{
  DataMenuBaseObjectClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataMenuDirectedTreeObjectClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataMenuDirectedTreeObjectClass, there is no further information.
**
**  REMARKS
**
*/
bool DataMenuDirectedTreeObjectClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataMenuBaseObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataMenuDirectedTreeObjectClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataMenuDirectedTreeObjectClass::CopyClone(Identify *  objc)
{
  DataMenuDirectedTreeObjectClass *objcfull = (DataMenuDirectedTreeObjectClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataMenuDirectedTreeObjectClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataMenuDirectedTreeObjectClass::Clone()
    {
      DataMenuDirectedTreeObjectClass* id = new DataMenuDirectedTreeObjectClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataMenuDirectedTreeObjectClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMenuDirectedTreeObjectClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataMenuBaseObjectClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataMenuDirectedTreeObjectClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMenuDirectedTreeObjectClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataMenuBaseObjectClass::DecodeThis(buffer);
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
BaseDataObject * DataMenuDirectedTreeObjectClass::BaseDataObjectExample()
{ 
  //cout << "Make MenuDirectedTreeObject Example\n";
  return (BaseDataObject *) new BaseDataMenuDirectedTreeObject();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataMenuDirectedTreeObjectClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataMenuDirectedTreeObjectClass*& obj)
     {
     obj = new DataMenuDirectedTreeObjectClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataMenuDirectedTreeObject
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataMenuDirectedTreeObject*& obj)
     {
     obj = new BaseDataMenuDirectedTreeObject;
     return obj->DecodeThis(buffer);
     }
/*S InstanceSystemMenu
 */
/*S Utility
 */
 
/*F MenuAttributeList(ptype,out,system)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void MenuAttributeList(String& ptype, ostream& out, InstanceSystemMenu *system)
{
  BaseDataMenuWindow window;
  DataMenuWindowClass windowclass;
  String run(system->getSysMenuCommand());
  String com(" WindowInstanceAttribute ");
  run.AppendToEnd(com);

  ObjectList<String> names = system->Instances.ListOfInstanceNames();
  BaseDataMenuTextChoice menu = NamesToMenuTextChoice(names,run);
  window.setMenuObject(&menu);
  window.Write(cout,&windowclass);
}
 
/*F MenuInstanceList(ptype,out,sys)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void InstanceSystemMenu::PrintListOfNames(String& ptype, String& prefix,
					  ostream& out,
					  ObjectList<String>& names)
{
  BaseDataMenuWindow window;
  DataMenuWindowClass windowclass;
  
  String com(getSysMenuCommand());
  String blank(" ");
  String level = Int2String(getVersion());
  String exp(" Experiment ");
  String run(com);
  run.AppendToEnd(exp);
  run.AppendToEnd(blank);
  run.AppendToEnd(getRootName());
  run.AppendToEnd(blank);
  run.AppendToEnd(level);
  run.AppendToEnd(blank);
  run.AppendToEnd(ptype);
  run.AppendToEnd(blank);
  run.AppendToEnd(prefix);

  BaseDataMenuTextChoice menu = NamesToMenuTextChoice(names,run);
  window.setMenuObject(&menu);
  window.Write(out,&windowclass);
}

/*F BaseDataObjectOut(ptype,attr,out)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void InstanceSystemMenu::BaseDataObjectOut(String& ptype,
					   BaseDataObject *attr,
					   ostream& out)
{
  if(ptype == "WindowObject")
    {
      DataSetOfObjectsClass standard = getStandard();
      DataObjectClass *objclass = standard.GetObjectClass(attr->GetType());
      BaseDataMenuCoreObject obj;
      
      BaseDataMenuWindow window;
      //DataMenuWindowClass windowclass;
      
      obj.setAsAttributeObject(attr);
      
      window.setMenuObject(&obj);
      window.Write(out,objclass);
    }
  else
    InstanceSystemSave::BaseDataObjectOut(ptype,attr,out);
}
/*F ans = MenuChoiceClassesTextChoice(sys)
**
**  DESCRIPTION
**    From the list of classes make a TextChoice 
**
**  REMARKS
**
*/
int MenuChoiceClassesTextChoice(ReactionSystemBase *sys)
{
  InstanceSystemMenu *system = (InstanceSystemMenu *) sys;
  int ans = SYSTEM_NORMAL_RETURN;
  
  BaseDataMenuWindow window;
  DataMenuWindowClass windowclass;
  
  DataSetOfObjectsClass standard = system->getStandard();
  ObjectList<String> clist1 = standard.ListOfClassNames();
  ObjectList<String> clist;
  ObjectList<String>::iterator str;
  for(str=clist1.begin();
      str != clist1.end();
      str++)
    {
      String name(" ");
      name.AppendToEnd(*str);
      clist.AddObject(name);
    }
  clist.ChangeDelimitor("\n");

  BaseDataMenuTextChoice menu;
  menu.setChoice(clist);
  String comm(system->getSysMenuCommand());
  String comm1(" xxx WindowClassPrint");
  comm.AppendToEnd(comm1);
  menu.setCommand(comm);

  window.setMenuObject(&menu);
  window.Write(cout,&windowclass);

  return ans;
}
/*F ans = MenuChoiceClassCoreObject(sys)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int MenuChoiceClassCoreObject(ReactionSystemBase *sys)
{
  InstanceSystemMenu *system = (InstanceSystemMenu *) sys;
  int ans = SYSTEM_NORMAL_RETURN;

  if(system->Inputs.size() < 1)
    {
      cout << "Input:\n";
      cout << "Name of the Class to print \n";
      
      return 1;
    }
  
  String name = system->Inputs.front();
  system->Inputs.pop_front();
  
  BaseDataMenuWindow window;
  DataMenuWindowClass windowclass;
  
  DataSetOfObjectsClass standard = system->getStandard();
  DataObjectClass *objclass = standard.GetObjectClass(name);

  BaseDataMenuCoreObject obj;
  DataMenuCoreObjectClass oclass;

  obj.setAsClassObject(objclass);
  window.setMenuObject(&obj);
  window.Write(cout,&oclass);
  
  return ans;
}
/*F ans = MenuChoiceClassHierarchy(sys)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int MenuChoiceClassHierarchy(ReactionSystemBase *sys)
{
  InstanceSystemMenu *system = (InstanceSystemMenu *) sys;
  int ans = SYSTEM_NORMAL_RETURN;


  BaseDataMenuWindow window;
  DataMenuWindowClass windowclass;
  String run(system->getSysMenuCommand());
  String com(" xxx WindowObject Class ");
  run.AppendToEnd(com);

  DataSetOfObjectsClass standard = system->getStandard();
  ObjectList<String> names = standard.ListOfClassNames();
  
  BaseDataMenuDirectedTreeObject tree;
  DataMenuDirectedTreeObjectClass treeclass;
  tree.setCommand(run);
  String object("Object");
  tree.SetRootNode(object);
  tree.AddNode(object);
  ObjectList<String>::iterator str;
  for(str=names.begin();
      str != names.end();
      str++)
    {
      DataObjectClass *objc = standard.GetObjectClass(*str);
      String name(objc->NameTag);
      tree.AddNode(name);
      tree.AddBond(name,objc->SubClass);
    }
  window.setMenuObject(&tree);
  window.Write(cout,&treeclass);
  
  return ans;
}
/*F ans = MenuChoiceAttributeCoreObject(sys)  . . . . . . . . . . . . .  menu
**
**  DESCRIPTION
**    This routine takes zero or more arguments:
**    - No arguments:   choice of instances
**    - Instance Name:  choice of attributes
**    - Attribute Name: print out the instance CoreObject
**  REMARKS
**
*/
int MenuChoiceCoreObject(ReactionSystemBase *sys)
{
  return DataInformationOut("WindowObject",cout,sys);
}
/*F ans = WriteOutNewDerivedClasses(sys)  . . . . . . . . . . . . . . .  menu
**
**  DESCRIPTION
**    This command writes out in the current 'saves' directory
**    a file (to read) with the total set of new derived classes.
**    The list of current class names is given in the file:
**       - saves/Root.new.names
**    and the new classes are written to the file:
**       - saves/Root.new.classes
**
**  REMARKS
**
*/
int WriteOutNewDerivedClasses(ReactionSystemBase *sys)
{
  InstanceSystemMenu *system = (InstanceSystemMenu *) sys;
  int ans = SYSTEM_NORMAL_RETURN;
  cout << "WriteOutNewDerivedClasses: " << system->getRootName() << endl;
  String dir("./saves");
  String ext("new.names");
  OpenInputFile namesfile(dir,system->getRootName(),ext);
  if(namesfile.IfOpen())
    {
      ObjectList<String> names;
      StreamObjectInput inp(namesfile.Stream,' ');
      String name = inp.ReadNext();
      while(!(name == "END"))
	{
	  cout << "Read: " << name << endl;
	  names.AddObject(name);
	  name = inp.ReadNext();
	}
      cout << "Read in Names" << endl;
      names.print(cout);
      cout << endl;
      ObjectList<String> *newnames = SetOfDerivedClasses(system->InstanceClasses.PointerToAllowedClasses(),
							 names);
      cout << "The set of new derived names" << endl;
      newnames->print(cout);
      cout << endl;
      String ext2("new.classes");
      OpenOutputFile outclasses(dir,system->getRootName(),ext2);
      if(outclasses.IfOpen())
	{
	  WriteSetOfClasses(*newnames,outclasses.Stream,system->InstanceClasses);
	}
      else
	ans = SYSTEM_ERROR_RETURN;
	  
      delete newnames;
    }
  else
    {
      ans = SYSTEM_ERROR_RETURN;
      cerr << "List of names not found: saves/" << system->getRootName() << ".new.names"  << endl;
    }
  
  return ans;
}
/*F CommandSetUp()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void InstanceSystemMenu::CommandSetUp()
{
  InstanceSystemSave::CommandSetUp();
  
  SingleSystemCommand classtree("WindowObject",
				"Print Attribute or Class to Window",
				&MenuChoiceCoreObject);
  Commands.AddObject(classtree.getName(),classtree);
  
  SingleSystemCommand menuobjtst("ClassTree",
				 "Print Class Hierarchy to a Window",
				 &MenuChoiceClassHierarchy);
  Commands.AddObject(menuobjtst.getName(),menuobjtst);

  SingleSystemCommand newclasses("NewClasses",
				 "Print Out all the new classes",
				 &WriteOutNewDerivedClasses);
  Commands.AddObject(newclasses.getName(),newclasses);

}
