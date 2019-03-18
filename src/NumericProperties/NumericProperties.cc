/*  FILE     NumericProperties.cc
**  PACKAGE  NumericProperties
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "NumericProperties" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "LogicalOperations.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "NumericOperations.hh"
#include "MenuObjects.hh"
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "InstanceAlgorithms.hh"
#include "NumericProperties.hh"
#include "MatrixUtilities.hh"

/*S BaseDataMatrixPlots
 */ 
/*F BaseDataMatrixPlots()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataMatrixPlots::BaseDataMatrixPlots()
{
  Identification = NUMERICPROPS_MATPLOT_ID;
  NameTag = NUMERICPROPS_MATPLOT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataMatrixPlots(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataMatrixPlots::BaseDataMatrixPlots(const BaseDataMatrixPlots& data)
  : BaseDataInstanceDoubleMatrix(data),
  Xcoords(data.Xcoords),
  Ycoords(data.Ycoords)
{
}
 
/*F BaseDataMatrixPlots(mat,x,y)  . . . . . . . . . . . . BaseDataMatrixPlots
**
**  DESCRIPTION
**    mat: The matrix on which the plots are based
**    x: The set of x coordinates
**    y: The set of y coordinates
**
**  REMARKS
**
*/
BaseDataMatrixPlots::BaseDataMatrixPlots(const BaseDataInstanceDoubleMatrix &mat,
					 const BaseDataKeyWords& x,
					 const BaseDataKeyWords& y)
  : BaseDataInstanceDoubleMatrix(mat),
  Xcoords(x),
  Ycoords(y)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataMatrixPlots
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataMatrixPlots::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataMatrixPlots
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataMatrixPlots::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataInstanceDoubleMatrix::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataMatrixPlots
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataMatrixPlots::print(ostream& out) const
{
  BaseDataInstanceDoubleMatrix::print(out);
  out << "The X coordinates: ";
  Xcoords.print(out);
  out << endl << "The Y coordinates: ";
  Ycoords.print(out);
  out << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataMatrixPlots
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataMatrixPlots::Clone()
{
  BaseDataMatrixPlots *obj = new BaseDataMatrixPlots(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataMatrixPlots
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataMatrixPlots::CopyClone(Identify * obj)
{
  BaseDataMatrixPlots *objfull = (BaseDataMatrixPlots *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMatrixPlots
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMatrixPlots::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataInstanceDoubleMatrix::EncodeThis(buffer);
  result = result && Encode(buffer,Xcoords);
  result = result && Encode(buffer,Ycoords);
  //result = result && ---.EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataMatrixPlots
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataMatrixPlots::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataInstanceDoubleMatrix::DecodeThis(buffer);
  result = result && Decode(buffer,Xcoords);
  result = result && Decode(buffer,Ycoords);
  return result;
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataKeyWords& BaseDataMatrixPlots::getXcoords()
{
  return Xcoords;
}
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataKeyWords& BaseDataMatrixPlots::getYcoords()
{
  return Ycoords;
}
/*S DataMatrixPlotsClass
 */
/*F DataMatrixPlotsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataMatrixPlotsClass::DataMatrixPlotsClass()
{
  Identification = NUMERICPROPS_MATPLOT_ID;
  NameTag = NUMERICPROPS_MATPLOT_NAME;
  SubClass = "InstanceDoubleMatrix";
  EncodeDecodeClass = NameTag;
} 
/*F DataMatrixPlotsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataMatrixPlotsClass::DataMatrixPlotsClass(const DataMatrixPlotsClass& data)
  : DataInstanceDoubleMatrixClass(data)
{
} 
 
/*F DataMatrixPlotsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataMatrixPlotsClass::DataMatrixPlotsClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataInstanceDoubleMatrixClass(id,name,descr)
{
  SubClass = "InstanceDoubleMatrix";
  EncodeDecodeClass = "MatrixPlots";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataMatrixPlotsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataMatrixPlotsClass::print(ostream& out) const
{
  DataInstanceDoubleMatrixClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataMatrixPlotsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataMatrixPlotsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataMatrixPlotsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataInstanceDoubleMatrixClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataMatrixPlotsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataMatrixPlotsClass::CopyClone(Identify *  objc)
{
  DataMatrixPlotsClass *objcfull = (DataMatrixPlotsClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataMatrixPlotsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataMatrixPlotsClass::Clone()
    {
      DataMatrixPlotsClass* id = new DataMatrixPlotsClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataMatrixPlotsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMatrixPlotsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataInstanceDoubleMatrixClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataMatrixPlotsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataMatrixPlotsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataInstanceDoubleMatrixClass::DecodeThis(buffer);
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
BaseDataObject * DataMatrixPlotsClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataMatrixPlots();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataMatrixPlotsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataMatrixPlotsClass*& obj)
     {
     obj = new DataMatrixPlotsClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataMatrixPlots
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataMatrixPlots*& obj)
     {
     obj = new BaseDataMatrixPlots;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataPolynomialPlotProperties
 */ 
/*F BaseDataPolynomialPlotProperties()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataPolynomialPlotProperties::BaseDataPolynomialPlotProperties()
{
  Identification = NUMERICPROPS_POLYPROPS_ID;
  NameTag = NUMERICPROPS_POLYPROPS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataPolynomialPlotProperties(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataPolynomialPlotProperties::BaseDataPolynomialPlotProperties(const BaseDataPolynomialPlotProperties& data)
  : BaseDataInstanceDoubleMatrix(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataPolynomialPlotProperties
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataPolynomialPlotProperties::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataPolynomialPlotProperties
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataPolynomialPlotProperties::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataInstanceDoubleMatrix::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataPolynomialPlotProperties
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataPolynomialPlotProperties::print(ostream& out) const
{
  BaseDataInstanceDoubleMatrix::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataPolynomialPlotProperties
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataPolynomialPlotProperties::Clone()
{
  BaseDataPolynomialPlotProperties *obj = new BaseDataPolynomialPlotProperties(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataPolynomialPlotProperties
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataPolynomialPlotProperties::CopyClone(Identify * obj)
{
  BaseDataPolynomialPlotProperties *objfull = (BaseDataPolynomialPlotProperties *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPolynomialPlotProperties
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPolynomialPlotProperties::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataInstanceDoubleMatrix::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPolynomialPlotProperties
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPolynomialPlotProperties::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataInstanceDoubleMatrix::DecodeThis(buffer);
  return result;
}
/*S DataPolynomialPlotPropertiesClass
 */
/*F DataPolynomialPlotPropertiesClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataPolynomialPlotPropertiesClass::DataPolynomialPlotPropertiesClass()
{
  Identification = NUMERICPROPS_POLYPROPS_ID;
  NameTag = NUMERICPROPS_POLYPROPS_NAME;
  SubClass = "InstanceDoubleMatrix";
  EncodeDecodeClass = NameTag;
} 
/*F DataPolynomialPlotPropertiesClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataPolynomialPlotPropertiesClass::DataPolynomialPlotPropertiesClass(const DataPolynomialPlotPropertiesClass& data)
  : DataInstanceDoubleMatrixClass(data)
{
} 
 
/*F DataPolynomialPlotPropertiesClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataPolynomialPlotPropertiesClass::DataPolynomialPlotPropertiesClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataInstanceDoubleMatrixClass(id,name,descr)
{
  SubClass = "InstanceDoubleMatrix";
  EncodeDecodeClass = "PolynomialPlotProperties";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataPolynomialPlotPropertiesClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataPolynomialPlotPropertiesClass::print(ostream& out) const
{
  DataInstanceDoubleMatrixClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataPolynomialPlotPropertiesClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataPolynomialPlotPropertiesClass, there is no further information.
**
**  REMARKS
**
*/
bool DataPolynomialPlotPropertiesClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataInstanceDoubleMatrixClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataPolynomialPlotPropertiesClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataPolynomialPlotPropertiesClass::CopyClone(Identify *  objc)
{
  DataPolynomialPlotPropertiesClass *objcfull = (DataPolynomialPlotPropertiesClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataPolynomialPlotPropertiesClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataPolynomialPlotPropertiesClass::Clone()
    {
      DataPolynomialPlotPropertiesClass* id = new DataPolynomialPlotPropertiesClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataPolynomialPlotPropertiesClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPolynomialPlotPropertiesClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataInstanceDoubleMatrixClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataPolynomialPlotPropertiesClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPolynomialPlotPropertiesClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataInstanceDoubleMatrixClass::DecodeThis(buffer);
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
BaseDataObject * DataPolynomialPlotPropertiesClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataPolynomialPlotProperties();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataPolynomialPlotPropertiesClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataPolynomialPlotPropertiesClass*& obj)
     {
     obj = new DataPolynomialPlotPropertiesClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataPolynomialPlotProperties
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataPolynomialPlotProperties*& obj)
     {
     obj = new BaseDataPolynomialPlotProperties;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataCalculateNumericProperties
 */ 
/*F BaseDataCalculateNumericProperties()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataCalculateNumericProperties::BaseDataCalculateNumericProperties()
  : LowerPowerS("LowerPower"),
    UpperPowerS("UpperPower"),
    XcoordsS("XParameters"),
    YcoordsS("YParameters"),
    PlotsS("Plots"),
    AttributeNamesS("AttributeNames"),
    NumDerivativesS("NumberOfDerivatives"),
    NumericZeroValueS("NumericZeroValue")
{
  Identification = NUMERICPROPS_CALCULATE_ID;
  NameTag = NUMERICPROPS_CALCULATE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataCalculateNumericProperties(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataCalculateNumericProperties::BaseDataCalculateNumericProperties(const BaseDataCalculateNumericProperties& data)
  : BaseDataMatrixSetUp(data),
    LowerPowerS(data.LowerPowerS),
    UpperPowerS(data.UpperPowerS),
    XcoordsS(data.XcoordsS),
    YcoordsS(data.YcoordsS),
    PlotsS(data.PlotsS),
    AttributeNamesS(data.AttributeNamesS),
    NumDerivativesS(data.NumDerivativesS),
    NumericZeroValueS(data.NumericZeroValueS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataCalculateNumericProperties
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataCalculateNumericProperties::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataCalculateNumericProperties
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataCalculateNumericProperties::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataMatrixSetUp::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataCalculateNumericProperties
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataCalculateNumericProperties::print(ostream& out) const
{
  BaseDataMatrixSetUp::print(out);
  out << "Lowest: " << LowerPowerS << "  Highest: " << UpperPowerS << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataCalculateNumericProperties
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataCalculateNumericProperties::Clone()
{
  BaseDataCalculateNumericProperties *obj = new BaseDataCalculateNumericProperties(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataCalculateNumericProperties
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataCalculateNumericProperties::CopyClone(Identify * obj)
{
  BaseDataCalculateNumericProperties *objfull = (BaseDataCalculateNumericProperties *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataCalculateNumericProperties
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataCalculateNumericProperties::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMatrixSetUp::EncodeThis(buffer);
  result = result && Encode(buffer,LowerPowerS);
  result = result && Encode(buffer,UpperPowerS);
  result = result && Encode(buffer,XcoordsS);
  result = result && Encode(buffer,YcoordsS);
  result = result && Encode(buffer,PlotsS);
  result = result && Encode(buffer,AttributeNamesS);
  
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataCalculateNumericProperties
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataCalculateNumericProperties::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataMatrixSetUp::DecodeThis(buffer);
  result = result && Decode(buffer,LowerPowerS);
  result = result && Decode(buffer,UpperPowerS);
  result = result && Decode(buffer,XcoordsS);
  result = result && Decode(buffer,YcoordsS);
  result = result && Decode(buffer,PlotsS);
  result = result && Decode(buffer,AttributeNamesS);
  return result;
}
/*F ans = SetUpAlgorithms(instances,instancesclass,run,runclass)  . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataCalculateNumericProperties::SetUpAlgorithms(BaseDataSetOfInstances *instances,
							 DataSetOfInstancesClass *instancesclass,
							 BaseDataAlgorithmRun *run,
							 DataAlgorithmRunClass *runclass)
{
  return BaseDataMatrixSetUp::SetUpAlgorithms(instances,instancesclass,run,runclass);
}
/*F ans = CheckInput(instances,instancesclass,run,runclass) . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**
**  REMARKS
**
*/
bool BaseDataCalculateNumericProperties::CheckInput(BaseDataSetOfInstances *instances,
						    DataSetOfInstancesClass *instancesclass,
						    BaseDataAlgorithmRun *run,
						    DataAlgorithmRunClass *runclass)
{
  bool result = BaseDataMatrixSetUp::CheckInput(instances,instancesclass,run,runclass);
  result = result && CheckInputVariable(LowerPowerS,"lowest polynomical power",run);
  result = result && CheckInputVariable(UpperPowerS,"highest polynomial power",run);
  result = result && CheckInputVariable(XcoordsS,"set of X coordinates",run);
  result = result && CheckInputVariable(YcoordsS,"set of Y coordinates",run);
  return result;
}
/*F ans = SetUpInput(instances,instancesclass,run,runclass) . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataCalculateNumericProperties::SetUpInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = BaseDataMatrixSetUp::SetUpInput(instances,instancesclass,run,runclass);

  LowerPower = (BaseDataInteger *) run->ParameterValue(LowerPowerS);
  UpperPower = (BaseDataInteger *) run->ParameterValue(UpperPowerS);
  Xcoords = (BaseDataKeyWords *) run->ParameterValue(XcoordsS);
  Ycoords = (BaseDataKeyWords *) run->ParameterValue(YcoordsS);

  Lower = LowerPower->GetValue();
  Upper = UpperPower->GetValue();
  if(Lower > Upper)
    {
      cerr << "Lowest Power, " << Lower << " less than highest power, " << Upper << endl;
      result = false;
    }
  if(instances->IsInList(NumDerivativesS)) {
    NumDerivatives = (BaseDataInteger *) instances->GetObject(NumDerivativesS);
    numderiv = NumDerivatives->GetValue() + 1;
    cout << "Number Of Derivatives: " << numderiv - 1 << endl;
  } else {
    numderiv = 3;
    cout << "Default Number Of Derivatives: " << numderiv - 1 << endl;
    cout << "(can be set with '" << NumDerivativesS << "'" << endl;
  }
  if(instances->IsInList(NumericZeroValueS)) {
    NumericZeroValue = (BaseDataReal *) instances->GetObject(NumericZeroValueS);
    Zero = NumericZeroValue->GetValue();
    cout << "Numeric Zero set to: " << Zero << endl;
  } else {
    Zero = 1e-10;
    cout << "Default Numeric Zero set to: " << Zero << endl;
    cout << "(Can be set with '" << NumericZeroValueS << "'" << endl;
  }
  return result;
}
/*F ans = Calculate(instances,instancesclass,run,runclass)  . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataCalculateNumericProperties::Calculate(BaseDataSetOfInstances *instances,
						   DataSetOfInstancesClass *instancesclass,
						   BaseDataAlgorithmRun *run,
						   DataAlgorithmRunClass *runclass)
{
  bool result = BaseDataMatrixSetUp::Calculate(instances,instancesclass,run,runclass);
  BaseDataInstanceDoubleMatrix mat = *matrixObject;
  Plots = new BaseDataMatrixPlots(mat,*Xcoords,*Ycoords);
  AttributeNames = new BaseDataKeyWords();
  AttributeNames->NameTag = AttributeNamesS;

  matderivatives = NULL;

  Plots->NameTag = PlotsS;
  ObjectList<String> attributes = Plots->getXcoords().GetKeyWords();
  ObjectList<String>::iterator attrname;

  cout << "========================================================" << endl;
  cout << "========================================================" << endl;
  Plots->CurrentMatrix().print(cout);
  cout << "========================================================" << endl;
  cout << "========================================================" << endl;
  for(attrname = attributes.begin(); attrname != attributes.end(); attrname++)
    {
      AttributeNames->AddKeyWord(*attrname);
      CalculatePlotInfoForXParameter(*attrname,instances);
    }
  return result;
}
 
/*F ans = CalculatePlotInfoForXParameter(xname)
**
**  DESCRIPTION
**    xname: The x parameter name
**    ans: true if successfull
**  REMARKS
**
*/
bool BaseDataCalculateNumericProperties::CalculatePlotInfoForXParameter(String& xname,
									BaseDataSetOfInstances *instances)
{
  cout << "BaseDataCalculateNumericProperties::CalculatePlotInfoForXParameter" << endl;
  cout << "X Attribute: " << xname << endl;
  bool result = true;
  ObjectList<String> attributes = Plots->getYcoords().GetKeyWords();
  ObjectList<String>::iterator attrname;
  for(attrname = attributes.begin(); attrname != attributes.end(); attrname++)
    {
      result = result && CalculatePlotInfoForXandYParameters(xname,*attrname);
      WriteInstanceValues(xname,*attrname,instances);
    }
  return result;
}
/*F ans = CalculatePlotInfoForXandYParameter(xname,yname)
**
**  DESCRIPTION
**    xname: The x parameter name
**    yname: The y parameter name
**    ans: true if successfull
**  REMARKS
**
*/
bool BaseDataCalculateNumericProperties::CalculatePlotInfoForXandYParameters(String& xname,String& yname)
{
  bool result = true;

  MatrixNumeric mat = Plots->CurrentMatrix();
  unsigned int xpos = Plots->CorrespondingColumn(xname);
  unsigned int ypos = Plots->CorrespondingColumn(yname);
  double diff = (double) Upper - Lower;
  unsigned int range = (unsigned int) floor(diff/2.0 + 0.5);
  
  cout << "X,Y: " << xname << " " << yname << " " << xpos << " " << ypos << endl;
  cout << "Y(0,1,2,3,4): " 
       <<  mat[0][ypos] << ", "
       <<  mat[1][ypos] << ", "
       <<  mat[2][ypos] << ", "
       <<  mat[3][ypos] << endl;
  cout << "X(0,1,2,3,4): " 
       <<  mat[0][xpos] << ", "
       <<  mat[1][xpos] << ", "
       <<  mat[2][xpos] << ", "
       <<  mat[3][xpos] << endl;
  unsigned int numinstances = mat.size();
  
  if(matderivatives != NULL)
    delete matderivatives;
  matderivatives = new MatrixNumeric(numinstances,numderiv);
  for(unsigned int ipnts = 0; ipnts < numinstances;ipnts++)
    (*matderivatives)[ipnts][0] = mat[ipnts][ypos];

  double max = fabs(mat[0][xpos]);
  for(unsigned int ipnts = 0; ipnts < numinstances;ipnts++) {
    if(fabs(mat[ipnts][0]) > max)
      max = fabs(mat[ipnts][0]);
  }
  for(unsigned int ideriv = 1; ideriv < numderiv; ideriv++)
    {
      for(unsigned int i=0; i<numinstances;i++)
	{
	  result = result && ValuesForInstance(mat,max,numinstances,ideriv,range,i,xpos,ypos);
	}
    }
  cout << "The Derivatives" << endl;
  (*matderivatives).print(cout);
  cout << endl;
  return result;
}  
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataCalculateNumericProperties::ValuesForInstance(MatrixNumeric& mat, 
							   double max,
							   unsigned int numinstance, unsigned int ideriv,
							   unsigned int range, unsigned int icenter, 
							   unsigned int xpos, unsigned int ypos)
{
  bool result = true;
  unsigned int numinstances = mat.size();
  unsigned int lderiv = ideriv - 1;
  //cout << ideriv << ", " << icenter << ", " << numinstances << ", " << Zero << endl;
  if(icenter == 0) {
    if(fabs((*matderivatives)[1][lderiv]) < Zero &&
       fabs((*matderivatives)[0][lderiv]) < Zero) {
      (*matderivatives)[icenter][ideriv] = 0.0;
    } else {
      double xdiff = (mat[1][xpos] - mat[0][xpos])/max;
      double ydiff = (*matderivatives)[1][lderiv] - (*matderivatives)[0][lderiv];
      if(fabs(xdiff) > Zero)
	(*matderivatives)[icenter][ideriv] = ydiff/xdiff;
      else
	(*matderivatives)[icenter][ideriv] = 0.0;
    }
  }
  else if(icenter + 1 >= numinstances) {
    if(fabs((*matderivatives)[icenter][lderiv]) < Zero &&
       fabs((*matderivatives)[icenter-1][lderiv]) < Zero) {
      (*matderivatives)[icenter][ideriv] = 0.0;
    } else {
      double xdiff = (mat[icenter][xpos] - mat[icenter-1][xpos])/max;
      double ydiff = (*matderivatives)[icenter][lderiv] - (*matderivatives)[icenter-1][lderiv];
      if(fabs(ydiff) > Zero)
	(*matderivatives)[icenter][ideriv] = ydiff/xdiff;
      else 
	(*matderivatives)[icenter][ideriv] = 0.0;
    }
  } else {
    //cout << icenter << ", " << lderiv << ", " << max << endl;
    //cout << mat[icenter-1][xpos] << ", " << mat[icenter][xpos] << ", " << mat[icenter+1][xpos] << endl;
    if(fabs((*matderivatives)[icenter][lderiv])    < Zero &&
       fabs((*matderivatives)[icenter+1][lderiv]) < Zero &&
       fabs((*matderivatives)[icenter-1][lderiv]) < Zero ) {
      (*matderivatives)[icenter][ideriv] = 0.0;
    } else {
      double xdiff1 = (mat[icenter][xpos] - mat[icenter+1][xpos])/max;
      double xdiff2 = (mat[icenter][xpos] - mat[icenter-1][xpos])/max;
      double ydiff1 = (*matderivatives)[icenter][lderiv] - (*matderivatives)[icenter+1][lderiv];
      double ydiff2 = (*matderivatives)[icenter][lderiv] - (*matderivatives)[icenter-1][lderiv];
      /*
	cout << "NonZero: "
	<< (*matderivatives)[icenter-1 ][lderiv] << ", "
	<< (*matderivatives)[icenter   ][lderiv] << ", "
	<< (*matderivatives)[icenter+1 ][lderiv] << endl;
	cout << xdiff1 << ", " << xdiff2 << ", " << ydiff1 << ", " << ydiff2 << endl;
      */
      if(fabs(ydiff1) > Zero && fabs(ydiff2) > Zero)
	(*matderivatives)[icenter][ideriv] = ( ydiff1/xdiff1 + ydiff2/xdiff2 )/2.0;
      else
	(*matderivatives)[icenter][ideriv] = 0.0;
      //cout << "mat[" << icenter << ", " << ideriv << "] = " << (*matderivatives)[icenter][ideriv] << endl;
      }
  }
  if(fabs( (*matderivatives)[icenter][ideriv] ) < Zero) {
  (*matderivatives)[icenter][ideriv] = 0.0;
  }
  /*
  cout << icenter << "\t" << ideriv << "\t" << mat[icenter][xpos] << "\t";
  cout << (*matderivatives)[icenter][lderiv] << "\t" << (*matderivatives)[icenter][ideriv] << endl;
  unsigned int ibegin;
  int ib = icenter - range;
  unsigned int iend   = icenter + range;
  if(ib < 0)
    {
      ib = 0;
      iend   = 2*range;
    }
  if(iend >= mat.size())
    {
      iend = mat.size() - 1;
      ib = mat.size() - 2*range - 1;
    }
  if(ib < 0)
    ibegin = 0;
  else
    ibegin = ib;
  unsigned int fullrange = iend-ibegin;
  cout << "ValuesForInstance: " << icenter << "\t" << range << "\t" << fullrange << "\t" << ibegin << "\t" << iend << endl;
  double lpower = Lower;
  double upower = lpower + fullrange;
  MatrixNumeric *ps = FormMatrixOfPowers(mat,ibegin,iend,lpower,upower,xpos);
  cout << "------------------------------------------------------------------" << endl;
  ps->print(cout);
  cout << "------------------------------------------------------------------" << endl;
  VectorNumeric *yvalues = new VectorNumeric(fullrange);
  VectorNumeric *ryvalues = new VectorNumeric(fullrange);
  cout << "Real        ";
  for(unsigned int i=0; i<fullrange; i++)
    {
      (*yvalues)[i] = mat[ibegin+i][ypos];
      (*ryvalues)[i] = mat[ibegin+i][ypos];
      
      cout << mat[ibegin+i][ypos] << "\t";
    }
  cout << endl;
  MatrixUtilities mutil;
  mutil.gauss_jordan(*ps,*yvalues,fullrange);
  VectorNumeric coefs(fullrange);
  //VectorNumeric coefs = SolveLinearSystemOfEquations(*ps,*yvalues);
  cout << "Coefficients: " << endl;
  for(unsigned int jj=0;jj<fullrange;jj++)
    cout << (*yvalues)[jj] << "\t";
  cout << endl;
  MatrixNumeric *pscopy = FormMatrixOfPowers(mat,ibegin,iend,lpower,upower,xpos);
  cout << "Calculated  ";
  double total = 0.0;
  for(unsigned int ii=0; ii<fullrange;ii++)
    {
      double sum = 0.0;
      coefs[ii] = (*yvalues)[ii];
      for(unsigned int jj=0;jj<fullrange;jj++)
	{
	  sum += (*pscopy)[ii][jj] * (*yvalues)[jj];
	}
      cout << sum << "\t";
      total += fabs(sum-(*ryvalues)[ii]);
    }
  cout << endl;
  cout << total << "\t";
  cout << mat[icenter][ypos] << "\t" << mat[icenter][xpos] << "\t";
  CalculateDerivatives(mat[icenter][xpos]/12.0,icenter,lpower,coefs);

  delete ps;
  delete yvalues;
  */
  return result;
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataCalculateNumericProperties::WriteInstanceValues(String& xattr, String& yattr,
							     BaseDataSetOfInstances *instances)
{
  String basename(xattr);
  String delim("_");
  basename.AppendToEnd(delim);
  basename.AppendToEnd(yattr);
  
  for(unsigned int ideriv = 1;ideriv < numderiv; ideriv++) {
      String dname("Derivative");
      if(ideriv == 1)
	{
	  dname.AppendToEnd("1st_");
	  dname.AppendToEnd(basename);
	}
      else if(ideriv == 2)
	{
	  dname.AppendToEnd("2nd_");
	  dname.AppendToEnd(basename);	  
	}
      else if(ideriv == 3)
	{
	  dname.AppendToEnd("3rd_");
	  dname.AppendToEnd(basename);	  
	}
      else
	{
	  String n = Int2String(ideriv);
	  String d("th_");
	  dname.AppendToEnd(n);
	  dname.AppendToEnd(d);
	  dname.AppendToEnd(basename);
	}
      AttributeNames->AddKeyWord(dname);
      BaseDataReal *r = new BaseDataReal();
      r->NameTag = dname;
      WriteToInstance(ideriv,instances,r);
    }
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataCalculateNumericProperties::WriteToInstance(unsigned int ideriv,
							 BaseDataSetOfInstances *instances, 
							 BaseDataReal *r)
{
  ObjectList<String> instnames = Plots->getInstanceNames().GetKeyWords();
  ObjectList<String>::iterator name;
  unsigned int ipos = 0;
  for(name=instnames.begin();name != instnames.end();name++)
    {
      BaseDataInstance *instance = instances->GetInstance(*name);
      r->SetValue((*matderivatives)[ipos][ideriv]);
      instance->AddObject(r);
      ipos++;
    }
}
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
MatrixNumeric* BaseDataCalculateNumericProperties::FormMatrixOfPowers(MatrixNumeric& mat,
								     unsigned int ibegin, unsigned int iend,
								     double lpower, double upower,
								     unsigned int xpos)
{
  unsigned int isize = iend-ibegin;
  MatrixNumeric *answer = new MatrixNumeric(isize,isize);
  unsigned int i = 0;
  for(unsigned int j=ibegin; j < iend;j++)
    {
      double x = mat[j][xpos]/12.0;
      unsigned int k = 0;
      for(double p = lpower ; p < upower;p+=1.0)
	{
	  (*answer)[i][k] = pow(x,p);
	  k++;
	}
      i++;
    }
  return answer;
}
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataCalculateNumericProperties::CalculateDerivatives(double x,unsigned int icenter,
							      double lower,
							      VectorNumeric& coefs)
{
  unsigned int isize = coefs.size();
  VectorNumeric *fpowers = new VectorNumeric(isize);
  VectorNumeric *fcoeffs = new VectorNumeric(isize);
  for(unsigned int i=0;i<isize;i++)
    {
      (*fpowers)[i] = i;
      (*fcoeffs)[i] = coefs[i];
    }
  for(unsigned int ideriv=0;ideriv<numderiv;ideriv++)
    {
      double sum = 0.0;
      for(unsigned int ipowers=0;ipowers<isize;ipowers++)
	{
	  double p = ipowers;
	  sum += (*fcoeffs)[ipowers]*pow(x,p);
	}
      (*matderivatives)[icenter][ideriv] = sum;
      if(ideriv == 0)
	cout << sum << endl;
      for(unsigned int jpowers=0;jpowers<isize;jpowers++)
	{
	  (*fcoeffs)[jpowers] = (*fpowers)[jpowers]*(*fcoeffs)[jpowers];
	  (*fpowers)[jpowers] -= 1.0;
	}
    }
}
/*F ans = WriteOutputValues(instances,instancesclass,run,runclass)  algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataCalculateNumericProperties::WriteOutputValues(BaseDataSetOfInstances *instances,
					 DataSetOfInstancesClass *instancesclass,
					 BaseDataAlgorithmRun *run,
					 DataAlgorithmRunClass *runclass)
{
  bool result = BaseDataMatrixSetUp::WriteOutputValues(instances,instancesclass,run,runclass);
  // There is a problem with the copy constructor of MatrixNumeric
  run->AddParameter(Plots);
  run->AddParameter(AttributeNames);
  return result;
}
/*F ans = ConcludeRun(instances,instancesclass,run,runclass)  . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataCalculateNumericProperties::ConcludeRun(BaseDataSetOfInstances *instances,
				   DataSetOfInstancesClass *instancesclass,
				   BaseDataAlgorithmRun *run,
				   DataAlgorithmRunClass *runclass)
{
  bool result = BaseDataMatrixSetUp::ConcludeRun(instances,instancesclass,run,runclass);
  //delete Plots;
  delete AttributeNames;
  return result;
}
 
/*S DataCalculateNumericPropertiesClass
 */
/*F DataCalculateNumericPropertiesClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataCalculateNumericPropertiesClass::DataCalculateNumericPropertiesClass()
{
  Identification = NUMERICPROPS_CALCULATE_ID;
  NameTag = NUMERICPROPS_CALCULATE_NAME;
  SubClass = "MatrixSetUp";
  EncodeDecodeClass = NameTag;
} 
/*F DataCalculateNumericPropertiesClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataCalculateNumericPropertiesClass::DataCalculateNumericPropertiesClass(const DataCalculateNumericPropertiesClass& data)
  : DataMatrixSetUpClass(data)
{
} 
 
/*F DataCalculateNumericPropertiesClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataCalculateNumericPropertiesClass::DataCalculateNumericPropertiesClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataMatrixSetUpClass(id,name,descr)
{
  SubClass = "MatrixSetUp";
  EncodeDecodeClass = "CalculateNumericProperties";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataCalculateNumericPropertiesClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataCalculateNumericPropertiesClass::print(ostream& out) const
{
  DataMatrixSetUpClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataCalculateNumericPropertiesClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataCalculateNumericPropertiesClass, there is no further information.
**
**  REMARKS
**
*/
bool DataCalculateNumericPropertiesClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataMatrixSetUpClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataCalculateNumericPropertiesClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataCalculateNumericPropertiesClass::CopyClone(Identify *  objc)
{
  DataCalculateNumericPropertiesClass *objcfull = (DataCalculateNumericPropertiesClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataCalculateNumericPropertiesClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataCalculateNumericPropertiesClass::Clone()
    {
      DataCalculateNumericPropertiesClass* id = new DataCalculateNumericPropertiesClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataCalculateNumericPropertiesClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataCalculateNumericPropertiesClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataMatrixSetUpClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataCalculateNumericPropertiesClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataCalculateNumericPropertiesClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataMatrixSetUpClass::DecodeThis(buffer);
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
BaseDataObject * DataCalculateNumericPropertiesClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataCalculateNumericProperties();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataCalculateNumericPropertiesClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataCalculateNumericPropertiesClass*& obj)
     {
     obj = new DataCalculateNumericPropertiesClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataCalculateNumericProperties
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataCalculateNumericProperties*& obj)
     {
     obj = new BaseDataCalculateNumericProperties;
     return obj->DecodeThis(buffer);
     }
/*S Utilities
 */
/*F AddNumericPropertiesClasses(set)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AddNumericPropertiesClasses(DataSetOfObjectsClass& set)
{
  String plotdescr("The Matrix Plot Class");
  DataMatrixPlotsClass plotclass(NUMERICPROPS_MATPLOT_ID,NUMERICPROPS_MATPLOT_NAME,plotdescr);
  set.AddObjectClass(plotclass);

  String polydescr("The Class");
  DataPolynomialPlotPropertiesClass polyclass(NUMERICPROPS_POLYPROPS_ID,NUMERICPROPS_POLYPROPS_NAME,polydescr);
  set.AddObjectClass(polyclass);

  String calculatedescr("The Class");
  DataCalculateNumericPropertiesClass calculateclass(NUMERICPROPS_CALCULATE_ID,NUMERICPROPS_CALCULATE_NAME,calculatedescr);
  set.AddObjectClass(calculateclass);
}
/*F InitialSetOfNumericPropertiesEncodeDecodeRoutines() . . . . . . . . . . TopDecode
**
**  DESCRIPTION
**    Initialise 'TopDecode' functions in SetOfEncodeDecodeRoutines
**
**  REMARKS
**
*/
extern void InitialSetOfNumericPropertiesEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataMatrixPlotsClass,BaseDataMatrixPlots,NUMERICPROPS_MATPLOT_NAME);
  EncodeDecodeRegisterClass(DataPolynomialPlotPropertiesClass,BaseDataPolynomialPlotProperties,NUMERICPROPS_POLYPROPS_NAME);
  EncodeDecodeRegisterClass(DataCalculateNumericPropertiesClass,BaseDataCalculateNumericProperties,NUMERICPROPS_CALCULATE_NAME);
}
