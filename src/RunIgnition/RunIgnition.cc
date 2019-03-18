/*  FILE     RunIgnition.cc
**  PACKAGE  RunIgnition
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "RunIgnition" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include <cantera/Cantera.h>
#include "cantera/kernel/converters/CKReader.h"
#include <cantera/zerodim.h>
#include <cantera/IdealGasMix.h>
#include <time.h>
#include <cantera/kernel/Array.h>
#include <cantera/kernel/plots.h>
#include <cantera/equilibrium.h>

#include "FullReaction.hh"
#include "Iterator.hh"


#include "ChemkinConvert.hh"
#include "RunIgnition.hh"

/*S RxnDataIgnitionConditions
 */ 
/*F RxnDataIgnitionConditions()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
RxnDataIgnitionConditions::RxnDataIgnitionConditions()
  : Species(NULL),
    Temperature(NULL),
    Pressure(NULL),
    DeltaT(NULL)
{
  Identification = RUNIGNITION_IGNITIONSCONDITIONS_ID;
  NameTag = RUNIGNITION_IGNITIONSCONDITIONS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F RxnDataIgnitionConditions(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
RxnDataIgnitionConditions::RxnDataIgnitionConditions(const RxnDataIgnitionConditions& data)
  : RxnDataRealBasedProperty(data)
{
  Species     = (BaseDataSetOfObjects *) PointerClone(data.Species);
  Temperature = (BaseDataReal *) PointerClone(data.Temperature);
  Pressure    = (BaseDataReal *) PointerClone(data.Pressure);
  DeltaT      = (BaseDataReal *) PointerClone(data.DeltaT);
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in RxnDataIgnitionConditions
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool RxnDataIgnitionConditions::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in RxnDataIgnitionConditions
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
**  This is what a typical input looks like
**    T: 1000.0
**    P: 1.0
**    d: 0.00001
**    Species: 
**    CH4  0.1 
**    O2   0.2
**    N2   0.7
**    END
**    
*/
bool RxnDataIgnitionConditions::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = RxnDataRealBasedProperty::Read(in,objc,name);
  RxnIgnitionConditionsClass *igncndclass 
    = (RxnIgnitionConditionsClass *) objc;

  StreamObjectInput str(in,' ');
  String tLabel = str.ReadNext();
  if(tLabel == "T:") {
    String tS = str.ReadNext();
    double temperature = tS.ToFloat();
    Temperature = (BaseDataReal *) igncndclass->TemperatureClass->BaseDataObjectExample();
    Temperature->SetValue(temperature);
    String pLabel = str.ReadNext();
    if(pLabel == "P:") {
      String pS = str.ReadNext();
      double pressure = pS.ToFloat();
      Pressure = (BaseDataReal *) igncndclass->PressureClass->BaseDataObjectExample();
      Pressure->SetValue(pressure);
      String dLabel = str.ReadNext();
      if(dLabel == "d:") {
	String dS = str.ReadNext();
	double delta = dS.ToFloat();
	DeltaT = (BaseDataReal *) igncndclass->DeltaTClass->BaseDataObjectExample();
	DeltaT->SetValue(delta);
      } else {
	cerr << "Expected 'd:' got '" << dLabel << "'" << endl;
	result = false;
      }
    } else {
      cerr << "Expected 'P:' got '" << pLabel << "'" << endl;
	result = false;
    }
  } else {
    cerr << "Expected 'T:' got '" << tLabel << "'" << endl;
	result = false;
  }
  if(result) {
    String sLabel = str.ReadNext();
    if(sLabel == "Species:") {
      Species = (BaseDataSetOfObjects *) igncndclass->SpeciesClass->BaseDataObjectExample();
      String next = str.ReadNext();
      while(!(next == "END")) {
	BaseDataReal *value = (BaseDataReal *) igncndclass->SpeciesValueClass->BaseDataObjectExample();
	value->NameTag = next;
	String cS = str.ReadNext();
	double c = cS.ToFloat();
	value->SetValue(c);
	Species->AddObject(value);
	delete value;
	next = str.ReadNext();
      }
    }
  }
  return result;
}
 
/*F out1 = StandardASCIIOut(out) . . . . . . . . . . . . . . . .  RxnDataIgnitionConditions
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
**  This is what a typical input looks like
**    T: 1000.0
**    P: 1.0
**    d: 0.00001
**    Species: 
**    CH4  0.1 
**    O2   0.2
**    N2   0.7
**    END
*/
ostream& RxnDataIgnitionConditions::StandardASCIIOut(ostream& out) const {
  out << " T: " << Temperature->GetValue() << endl;
  out << " P: " << Pressure->GetValue() << endl;
  out << " d: " << DeltaT->GetValue() << endl;
  out << " Species:" << endl;
  if(Species != NULL) {
    ObjectList<String> names = Species->ListOfObjectNames();
    ObjectList<String>::iterator name;
    for(name = names.begin(); name != names.end(); name++) {
      BaseDataReal *value = (BaseDataReal *) Species->GetObject(*name);
      out << *name << " " << value->GetValue() << endl;
    }
    out << "END" << endl;
  }
  return out;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  RxnDataIgnitionConditions
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& RxnDataIgnitionConditions::print(ostream& out) const {
  RxnDataRealBasedProperty::print(out);
  StandardASCIIOut(out);
  return out;
}
/*F ans = WriteAsLine(out,cls) . . . . . . . . . . . . . . . . . . . .  RxnDataIgnitionConditions
**  DESCRIPTION
**    out: The output buffer
**    cls: object class
**    ans: true if successful
**
**  REMARKS
**
*/
bool RxnDataIgnitionConditions::WriteAsLine(ostream& out, DataObjectClass *objc) {
  out << " T: " << Temperature->GetValue();
  out << " P: " << Pressure->GetValue();
  out << " d: " << DeltaT->GetValue();
  out << " Species:";
  if(Species != NULL) {
    ObjectList<String> names = Species->ListOfObjectNames();
    ObjectList<String>::iterator name;
    for(name = names.begin(); name != names.end(); name++) {
      BaseDataReal *value = (BaseDataReal *) Species->GetObject(*name);
      out << *name << " " << value->GetValue() << " ";
    }
    out << "END" << endl;
  }
  return out;

}
/*F ans = WriteAsASCII(out,cls) . . . . . . . . . . . . . . . . . . . .  RxnDataIgnitionConditions
**  DESCRIPTION
**    out: The output buffer
**    cls: object class
**    ans: true if successful
**
**  REMARKS
**
*/
bool RxnDataIgnitionConditions::WriteAsASCII(ostream& out, DataObjectClass *objc) {
  out << " T: " << Temperature->GetValue() << endl;
  out << " P: " << Pressure->GetValue() << endl;
  out << " d: " << DeltaT->GetValue() << endl;
  out << " Species:" << endl;
  if(Species != NULL) {
    ObjectList<String> names = Species->ListOfObjectNames();
    ObjectList<String>::iterator name;
    for(name = names.begin(); name != names.end(); name++) {
      BaseDataReal *value = (BaseDataReal *) Species->GetObject(*name);
      out << *name << " " << value->GetValue() << endl;
    }
    out << "END" << endl;
  }
  return out;
}
/*F ans = WriteAsLatex(out,cls) . . . . . . . . . . . . . . . . . . . .  RxnDataIgnitionConditions
**  DESCRIPTION
**    out: The output buffer
**    cls: object class
**    ans: true if successful
**
**  REMARKS
**
*/
bool RxnDataIgnitionConditions::WriteAsLatex(ostream& out, DataObjectClass  *objc) {
  out << "\\begin{description}" << endl;
  out << "\\item[Temperature] " << Temperature->GetValue() << endl;
  out << "\\item[Pressure] " << Pressure->GetValue() << endl;
  out << "\\item[Time Step] " << DeltaT->GetValue() << endl;
  out << "\\item[Species]" << endl;
  if(Species != NULL) {
    out << "     \\begin{description}" << endl;
    ObjectList<String> names = Species->ListOfObjectNames();
    ObjectList<String>::iterator name;
    for(name = names.begin(); name != names.end(); name++) {
      BaseDataReal *value = (BaseDataReal *) Species->GetObject(*name);
      out << "       \\item[" << *name << "] " << value->GetValue() << endl;
    }
    out << "     \\end{description}" << endl;
    out << "\\end{description}" << endl;
  }
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .RxnDataIgnitionConditions
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * RxnDataIgnitionConditions::Clone()
{
  RxnDataIgnitionConditions *obj = new RxnDataIgnitionConditions(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .RxnDataIgnitionConditions
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void RxnDataIgnitionConditions::CopyClone(Identify * obj)
{
  RxnDataIgnitionConditions *objfull = (RxnDataIgnitionConditions *) obj;
  *this = *objfull;
  Species     = (BaseDataSetOfObjects *) PointerClone(objfull->Species);
  Temperature = (BaseDataReal *) PointerClone(objfull->Temperature);
  Pressure    = (BaseDataReal *) PointerClone(objfull->Pressure);
  DeltaT      = (BaseDataReal *) PointerClone(objfull->DeltaT);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  RxnDataIgnitionConditions
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool RxnDataIgnitionConditions::EncodeThis(CommBuffer& buffer)
{
  bool result = RxnDataRealBasedProperty::EncodeThis(buffer);
  result = result && PointerEncode(buffer,Species);
  result = result && PointerEncode(buffer,Temperature);
  result = result && PointerEncode(buffer,Pressure);
  result = result && PointerEncode(buffer,DeltaT);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  RxnDataIgnitionConditions
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool RxnDataIgnitionConditions::DecodeThis(CommBuffer& buffer)
{
  bool result = RxnDataRealBasedProperty::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Species);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Temperature);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Pressure);
  result = result && PointerDecode(buffer,(BaseDataObject *&) DeltaT);
  return result;
}
/*S RxnIgnitionConditionsClass
 */
/*F RxnIgnitionConditionsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
RxnIgnitionConditionsClass::RxnIgnitionConditionsClass()
  : SpeciesClass(NULL),
SpeciesValueClass(NULL),
    TemperatureClass(NULL),
    PressureClass(NULL),
    DeltaTClass(NULL)
{
  Identification = RUNIGNITION_IGNITIONSCONDITIONS_ID;
  NameTag = RUNIGNITION_IGNITIONSCONDITIONS_NAME;
  SubClass = "RealBasedProperty";
  EncodeDecodeClass = NameTag;
} 
/*F RxnIgnitionConditionsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
RxnIgnitionConditionsClass::RxnIgnitionConditionsClass(const RxnIgnitionConditionsClass& data)
  : RxnRealBasedPropertyClass(data),
    SpeciesClass(data.SpeciesClass),
    SpeciesValueClass(data.SpeciesValueClass),
    TemperatureClass(data.TemperatureClass),
    PressureClass(data.PressureClass),
    DeltaTClass(data.DeltaTClass)
{
} 
 
/*F RxnIgnitionConditionsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
RxnIgnitionConditionsClass::RxnIgnitionConditionsClass(const int id, 
				 const String& name,
				 const String& descr)
  : RxnRealBasedPropertyClass(id,name,descr),
    SpeciesClass(NULL),
    SpeciesValueClass(NULL),
    TemperatureClass(NULL),
    PressureClass(NULL),
    DeltaTClass(NULL)
{
  SubClass = "RealBasedProperty";
  EncodeDecodeClass = "IgnitionConditions";
}

/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . RxnIgnitionConditionsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& RxnIgnitionConditionsClass::print(ostream& out) const
{
  RxnRealBasedPropertyClass::print(out);
  PointerPrint(out,"  The Set of Species Class: "," No Class Defined ",SpeciesClass);
  PointerPrint(out,"  The Species Value Class: "," No Class Defined ",SpeciesValueClass);
  PointerPrint(out,"  The Temperature Class: "," No Class Defined ",TemperatureClass);
  PointerPrint(out,"  The Pressure Class: "," No Class Defined ",PressureClass);
  PointerPrint(out,"  The Time Step Class: "," No Class Defined ",DeltaTClass);
  return out;
}

/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . RxnIgnitionConditionsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base RxnIgnitionConditionsClass, there is no further information.
**
**  REMARKS
**
*/
bool RxnIgnitionConditionsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = RxnRealBasedPropertyClass::Read(in,set);
  result = result && PointerClassRead(in,(DataObjectClass *&) SpeciesClass,
				      COREOBJECTS_SET_NAME,
				      set," No Set of Species Values Class ");
  
  result = result && PointerClassRead(in,(DataObjectClass *&) SpeciesValueClass,
				      NUMERIC_REAL_NAME,
				      set," No Species Value Class ");
  
  result = result && PointerClassRead(in,(DataObjectClass *&) TemperatureClass,
				      NUMERIC_REAL_NAME,
				      set," No Temperature Class ");
  
  result = result && PointerClassRead(in,(DataObjectClass *&) PressureClass,
				      NUMERIC_REAL_NAME,
				      set," No Pressure Class ");
  
  result = result && PointerClassRead(in,(DataObjectClass *&) DeltaTClass,
				      NUMERIC_REAL_NAME,
				      set," No Time Step Class ");
  
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . RxnIgnitionConditionsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void RxnIgnitionConditionsClass::CopyClone(Identify *  objc)
{
  RxnIgnitionConditionsClass *objcfull = (RxnIgnitionConditionsClass *) objc;
  *this = *objcfull;
  SpeciesClass     = (DataSetOfObjectsClass *) PointerClone(objcfull->SpeciesClass);
  SpeciesValueClass     = (DataRealClass *) PointerClone(objcfull->SpeciesValueClass);
  TemperatureClass = (DataRealClass *) PointerClone(objcfull->TemperatureClass);
  PressureClass    = (DataRealClass *) PointerClone(objcfull->PressureClass);
  DeltaTClass      = (DataRealClass *) PointerClone(objcfull->DeltaTClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . RxnIgnitionConditionsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * RxnIgnitionConditionsClass::Clone()
{
  RxnIgnitionConditionsClass* id = new RxnIgnitionConditionsClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . RxnIgnitionConditionsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool RxnIgnitionConditionsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = RxnRealBasedPropertyClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,SpeciesClass);
  result = result && PointerEncode(buffer,SpeciesValueClass);
  result = result && PointerEncode(buffer,TemperatureClass);
  result = result && PointerEncode(buffer,PressureClass);
  result = result && PointerEncode(buffer,DeltaTClass);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . RxnIgnitionConditionsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool RxnIgnitionConditionsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = RxnRealBasedPropertyClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) SpeciesClass);
  result = result && PointerDecode(buffer,(BaseDataObject *&) SpeciesValueClass);
  result = result && PointerDecode(buffer,(BaseDataObject *&) TemperatureClass);
  result = result && PointerDecode(buffer,(BaseDataObject *&) PressureClass);
  result = result && PointerDecode(buffer,(BaseDataObject *&) DeltaTClass);

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
BaseDataObject * RxnIgnitionConditionsClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new RxnDataIgnitionConditions();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . RxnIgnitionConditionsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, RxnIgnitionConditionsClass*& obj)
     {
     obj = new RxnIgnitionConditionsClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . RxnDataIgnitionConditions
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, RxnDataIgnitionConditions*& obj)
     {
     obj = new RxnDataIgnitionConditions;
     return obj->DecodeThis(buffer);
     }

/*S RxnDataRunIgnition
 */ 
/*F RxnDataRunIgnition()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
RxnDataRunIgnition::RxnDataRunIgnition()
  :RootNameS(CHEMKINREAD_FILEROOT),
   ConditionsS(CONDITIONS_ATTRIBUTE),
   FinalTimeS(FINALTIME_ATTRIBUTE),
   OutputNameS(OUTPUTMATRIX_ATTRIBUTE),
   GasState(NULL)
{
  Identification = RUNIGNITION_RUNIGNITION_ID;
  NameTag = RUNIGNITION_RUNIGNITION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  SpeciesNames       = NULL;
  IndexNames         = NULL;
  MassFractions      = NULL;
  NetProductionRates = NULL;
  ForwardRates       = NULL;
  ReverseRates       = NULL;
  TimeStepProperties = NULL;
 } 
/*F RxnDataRunIgnition(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
RxnDataRunIgnition::RxnDataRunIgnition(const RxnDataRunIgnition& data)
  : BaseDataAlgorithmOperation(data),
    RootNameS(data.RootNameS),
    ConditionsS(data.ConditionsS),
    FinalTimeS(data.FinalTimeS),
    OutputNameS(data.OutputNameS),
    GasState(NULL)
{
  SpeciesNames       = NULL;
  IndexNames         = NULL;
  MassFractions      = NULL;
  NetProductionRates = NULL;
  ForwardRates       = NULL;
  ReverseRates       = NULL;
  TimeStepProperties = NULL;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in RxnDataRunIgnition
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool RxnDataRunIgnition::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in RxnDataRunIgnition
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool RxnDataRunIgnition::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  RxnDataRunIgnition
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& RxnDataRunIgnition::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .RxnDataRunIgnition
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * RxnDataRunIgnition::Clone()
{
  RxnDataRunIgnition *obj = new RxnDataRunIgnition(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .RxnDataRunIgnition
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void RxnDataRunIgnition::CopyClone(Identify * obj)
{
  RxnDataRunIgnition *objfull = (RxnDataRunIgnition *) obj;
  *this = *objfull;
  //Parameter = (RxnData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  RxnDataRunIgnition
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool RxnDataRunIgnition::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && Encode(buffer,RootNameS);
  result = result && Encode(buffer,ConditionsS);
  result = result && Encode(buffer,FinalTimeS);
  result = result && Encode(buffer,OutputNameS);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  RxnDataRunIgnition
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool RxnDataRunIgnition::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  // The rest
  result = result && Decode(buffer,RootNameS);
  result = result && Decode(buffer,ConditionsS);
  result = result && Decode(buffer,FinalTimeS);
  result = result && Decode(buffer,OutputNameS);

  return result;
}
 
/*S RxnRunIgnitionClass
 */
/*F RxnRunIgnitionClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
RxnRunIgnitionClass::RxnRunIgnitionClass()
{
  Identification = RUNIGNITION_RUNIGNITION_ID;
  NameTag = RUNIGNITION_RUNIGNITION_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F RxnRunIgnitionClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
RxnRunIgnitionClass::RxnRunIgnitionClass(const RxnRunIgnitionClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F RxnRunIgnitionClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
RxnRunIgnitionClass::RxnRunIgnitionClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = "RunIgnition";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . RxnRunIgnitionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& RxnRunIgnitionClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . RxnRunIgnitionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base RxnRunIgnitionClass, there is no further information.
**
**  REMARKS
**
*/
bool RxnRunIgnitionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . RxnRunIgnitionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void RxnRunIgnitionClass::CopyClone(Identify *  objc)
{
  RxnRunIgnitionClass *objcfull = (RxnRunIgnitionClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . RxnRunIgnitionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * RxnRunIgnitionClass::Clone()
    {
      RxnRunIgnitionClass* id = new RxnRunIgnitionClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . RxnRunIgnitionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool RxnRunIgnitionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . RxnRunIgnitionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool RxnRunIgnitionClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);

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
BaseDataObject * RxnRunIgnitionClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new RxnDataRunIgnition();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . RxnRunIgnitionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, RxnRunIgnitionClass*& obj)
     {
     obj = new RxnRunIgnitionClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . RxnDataRunIgnition
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, RxnDataRunIgnition*& obj)
     {
     obj = new RxnDataRunIgnition;
     return obj->DecodeThis(buffer);
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
bool RxnDataRunIgnition::SetUpAlgorithms(BaseDataSetOfInstances *instances,
				       DataSetOfInstancesClass *instancesclass,
				       BaseDataAlgorithmRun *run,
				       DataAlgorithmRunClass *runclass)
{
  return true;
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
bool RxnDataRunIgnition::CheckInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;
  result = result && CheckInputVariable(RootNameS,"The root name attribute name",run);
  result = result && CheckInputVariable(ConditionsS,"The attribute with the run conditions",run);
  result = result && CheckInputVariable(FinalTimeS,"The attribute with the end time",run);
  result = result && CheckInputVariable(OutputNameS,"The attribute with the name of the output matrix",run);

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
bool RxnDataRunIgnition::SetUpInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;

  BaseDataString *RootNameDS       = (BaseDataString *) run->ParameterValue(RootNameS);
  BaseDataReal *FinalTimeDS        = (BaseDataReal *) run->ParameterValue(FinalTimeS);
  BaseDataString *OutputNameDS = (BaseDataString *) run->ParameterValue(OutputNameS);
  Conditions = (RxnDataIgnitionConditions *) run->ParameterValue(ConditionsS);
  RootName = RootNameDS->getString();
  finalTime = FinalTimeDS->GetValue();
  OutputAttribute = OutputNameDS->getString();

  double deltaTime = Conditions->DeltaT->GetValue();
  double nIntervalsD = finalTime / deltaTime + 0.5;
  numberOfIntervals  = (unsigned int) floor(nIntervalsD);

  inputFileName = RootName;
  inputFileName.AppendToEnd(STANDARD_CANTERA_EXTENSION);

  if(run->AlgorithmSummary.KeyWordInList("ExtraOutput")){
    cout << "Number of Intervals: " << numberOfIntervals << endl;
    cout << "Time Step:           " << deltaTime << endl;
    cout << "Input File: " << inputFileName << endl;
  }
  return result;
}
/*F str = formSpeciesFromConditions() . . . . algorithm
**
**  DESCRIPTION
**    str: The string with the species
**    
**  REMARKS
**
** The string is of the form
**   H2:2.0, O2:1.0, N2:4.0
*/
vector_fp *RxnDataRunIgnition::formSpeciesFromConditions(BaseDataAlgorithmRun *run) {
  ObjectList<String> names = Conditions->Species->ListOfObjectNames();
  ObjectList<String>::iterator name;
  int nspecies = GasState->nSpecies();
  vector_fp *molfractions = new vector_fp(nspecies,0.0);
  for(name = names.begin(); name != names.end(); name++) {
    BaseDataReal *value = (BaseDataReal *) Conditions->Species->GetObject(*name);
    int i = 0;
    int index = -1;
    //cout << (*name).c_str() << ": " << GasState->speciesIndex((*name).c_str()) << endl;
    while(i<nspecies && index < 0) {
      if(strcmp((*name).c_str(),GasState->speciesName(i).c_str()) == 0) {
	index = i;
      }
      i++;
    }
    if(index < 0) {
      cerr << "Species '" << (*name).c_str() << "' has not been found " << endl;
    } else {
      if(run->AlgorithmSummary.KeyWordInList("ExtraOutput")){
	cout << (*name).c_str() << "(" << index << "): " << value->GetValue() << endl;
      }
      (*molfractions)[index] = value->GetValue();
    }
  }
  return molfractions;
}


/*F ignitionTimeInitialize() . . . . algorithm
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void RxnDataRunIgnition::ignitionTimeInitialize() {
  
  tlast = GasState->temperature();
  dTmax = 0.0;
  timeTMax = 0.0;
  OHindex = -1;
  try {
    string ohname("OH");
    OHindex = GasState->speciesIndex(ohname);
  } catch(CanteraError) {
  }
    
  OHMax = 0.0;
}
/*F ignitionTimeStep(time,dt,temperature) . . . . algorithm
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void RxnDataRunIgnition::ignitionTimeCheck(double time, 
					  double dt, 
					  double temperature) {
  double dTdt = (temperature - tlast)/dt;
  if(dTmax < dTdt) {
    timeTMax = time;
    dTmax = dTdt;
  }
  tlast = temperature;

  if(OHindex >=0 ) {
    double OHvalue = GasState->moleFraction(OHindex);
    if(OHMax < OHvalue) {
      OHMax = OHvalue;
      timeOHMax = time;
    }
  }
}
/*F ignitionTimeFinalize() . . . . algorithm
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void RxnDataRunIgnition::ignitionTimeFinalize(ostream& out) {
  out << "Ignition Delay Time:" << endl;
  out << "       time(ms) max(dT/dt):  " << timeTMax * 1000.0 << endl;
  if(OHindex >= 0) 
    out << "       time(ms) max(OH):     " << timeOHMax * 1000.0 << endl;
  out << endl;
}
/*F runMatrixInitialize() . . . . algorithm
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void RxnDataRunIgnition::runMatrixInitialize(int numruns, BaseDataAlgorithmRun *run) {
  int nspecies = GasState->nSpecies();
  SpeciesNames = new BaseDataKeySet();
  for(int i=0;i<nspecies;i++) {
    String name = String(GasState->speciesName(i).c_str());
    SpeciesNames->AddKeyWord(name);
  }
  IndexNames = new BaseDataKeySet();
  if(run->AlgorithmSummary.KeyWordInList(MOLFRACTIONS_ATTRIBUTE)){
    //MassFractions = new MatrixNumeric(numruns,nspecies+1);
    MassFractions = new MatrixNumeric();
  } else {
    MassFractions = NULL;
  }
  if(run->AlgorithmSummary.KeyWordInList(RATES_NET)){
    //NetProductionRates = new MatrixNumeric(numruns,nspecies+1);
    NetProductionRates = new MatrixNumeric();
  } else {
    NetProductionRates = NULL;
  }
  if(run->AlgorithmSummary.KeyWordInList(RATES_FORWARD)){
    //ForwardRates = new MatrixNumeric(numruns,nspecies+1);
    ForwardRates = new MatrixNumeric();
  } else {
    ForwardRates = NULL;
  }
  if(run->AlgorithmSummary.KeyWordInList(RATES_REVERSE)){
    //ReverseRates = new MatrixNumeric(numruns,nspecies+1);
    ReverseRates = new MatrixNumeric();
  } else {
    ReverseRates = NULL;
  }
  if(run->AlgorithmSummary.KeyWordInList(TIMESTEP_PROPERTIES)) {
    //TimeStepProperties = new MatrixNumeric(numruns,15);
    TimeStepProperties = new MatrixNumeric();
  } else {
    TimeStepProperties = NULL;
  }
}
/*
void transferToMatrix(vector_fp& temp, MatrixNumeric& mat, int i) {
  copy(temp.begin(),temp.end(),mat[i].begin()+1);
}
*/
void RxnDataRunIgnition::transferToMatrix(double *temp, unsigned int dim, double time, MatrixNumeric *mat) {
  //copy(temp.begin(),temp.end(),mat[i].begin()+1);
  unsigned int dimp1 = dim + 1;
  VectorNumeric *tempv = new VectorNumeric(dim+1);
  VectorNumeric::iterator t = tempv->begin();
  *t++ = time;
  for(unsigned int i=1;i < dimp1;i++) {
    *t++ = *temp++;
  }
  mat->push_back(*tempv);
  delete tempv;
}

/*F runMatrixTimeStepInfo() . . . . algorithm
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void RxnDataRunIgnition::runMatrixTimeStepInfo(int i) {
  char cname[20];
  sprintf(cname,"%12.9f",CurrentTime);
  IndexNames->AddKeyWord(cname);
  unsigned int nspecies = GasState->nSpecies();
  double *temp = (double *) calloc(nspecies, sizeof(double));
  if(MassFractions != NULL) {
    GasState->getMoleFractions(temp);
    transferToMatrix(temp,nspecies,CurrentTime,MassFractions);
  }
  if(NetProductionRates != NULL) {
     GasState->getNetProductionRates(temp);
      transferToMatrix(temp,nspecies,CurrentTime,NetProductionRates);
  }
  if(ForwardRates != NULL) {
    GasState->getCreationRates(temp);
     transferToMatrix(temp,nspecies,CurrentTime,ForwardRates);
  }
  if(ReverseRates != NULL) {
    GasState->getDestructionRates(temp);
     transferToMatrix(temp,nspecies,CurrentTime,ReverseRates);
  }
  delete temp;
  if(TimeStepProperties != NULL) {
    double index = (double) i;
    VectorNumeric temp(15);
    temp[0] = index;
    temp[1] = CurrentTime;
    temp[2] = (double) GasState->temperature();
    temp[3] = GasState->density();
    temp[4] = GasState->pressure();
    temp[5] = GasState->enthalpy_mole(); // molar enthalpy [J/kmol]
    temp[6] = GasState->entropy_mole();
    temp[7] = GasState->gibbs_mole();
    temp[8] = GasState->cp_mole();
    temp[9] = GasState->cv_mole();
    temp[10] = GasState->enthalpy_mass(); // specific enthalpy [J/kg]
    temp[11] = GasState->entropy_mass();
    temp[12] = GasState->gibbs_mass();
    temp[13] = GasState->cp_mass();
    temp[14] = GasState->cv_mass();
    (*TimeStepProperties).push_back(temp);
  }
}
/*F runMatrixFinalize() . . . . algorithm
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void RxnDataRunIgnition::excelOutMatrix(BaseDataInstanceDoubleMatrix *mat,
					BaseDataAlgorithmRun *run) {
  String name(OutputAttribute);
  name.AppendToEnd("-");
  name.AppendToEnd(mat->NameTag);

  OpenOutputFile *file = new OpenOutputFile(name,"csv");
  file->Stream << RootName << " " << mat->NameTag << " ," << endl;
  BaseDataKeyWords names = mat->getParameterNames();
  ObjectListString n = names.GetKeyWords();
  ObjectListString::iterator iter;
  for(iter = n.begin();iter != n.end();iter++) {
    file->Stream << *iter << ",";
  }
  file->Stream << endl;
  MatrixNumeric nummat = mat->CurrentMatrix();
  //int dim1 = nummat.size();
  int dim1 = Iterations - 1;
  int dim2 = nummat[0].size();
  for(int i=0;i<dim1;i++) {
    for(int j=0;j < dim2;j++) {
      file->Stream << nummat[i][j] << ",";
    }
    file->Stream << endl;
  }
}
/*F runMatrixFinalize() . . . . algorithm
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void RxnDataRunIgnition::saveMatrix(const char n[], BaseDataKeyWords *columns,
				    MatrixNumeric *mat,
				    BaseDataAlgorithmRun *run) {
  String name(n);
  BaseDataInstanceDoubleMatrix *instmat = 
    new BaseDataInstanceDoubleMatrix(*mat,*IndexNames,*columns);
  instmat->NameTag = name;
  Conditions->AddObject(instmat);
  if(run->AlgorithmSummary.KeyWordInList("Excel")){  
    excelOutMatrix(instmat,run);
  }
  delete instmat;
}
/*F runMatrixFinalize() . . . . algorithm
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void RxnDataRunIgnition::runMatrixFinalize(BaseDataAlgorithmRun *run) {
  if(MassFractions != NULL) {
    saveMatrix(MOLFRACTIONS_ATTRIBUTE,SpeciesNames,MassFractions,run);
    delete MassFractions;
    MassFractions = NULL;
  }
  if(NetProductionRates != NULL) {
    saveMatrix(RATES_NET,SpeciesNames,NetProductionRates,run);
    delete NetProductionRates;
    NetProductionRates = NULL;
  }
  if(ForwardRates != NULL) {
    saveMatrix(RATES_FORWARD,SpeciesNames,ForwardRates,run);
    delete ForwardRates;
    ForwardRates = NULL;
  }
  if(ReverseRates != NULL) {
    saveMatrix(RATES_REVERSE,SpeciesNames,ReverseRates,run);
    delete ReverseRates;
    ReverseRates = NULL;
  }
  if(TimeStepProperties != NULL) {
    BaseDataKeySet *set = new BaseDataKeySet();
    set->AddKeyWord("Index");
    set->AddKeyWord("Time(s)");
    set->AddKeyWord("T(K)");
    set->AddKeyWord("Density");
    set->AddKeyWord("P");
    set->AddKeyWord("Enthalpy(J/kmol)");
    set->AddKeyWord("Entropy(J/kmol)");
    set->AddKeyWord("Gibbs(J/kmol)");
    set->AddKeyWord("CP(J/kmol)");
    set->AddKeyWord("CV(J/kmol)");
    set->AddKeyWord("Enthalpy(J/kg)");
    set->AddKeyWord("Entropy(J/kg)");
    set->AddKeyWord("Gibbs(J/kg)");
    set->AddKeyWord("CP(J/kg)");
    set->AddKeyWord("CV(J/kg)");
    saveMatrix(TIMESTEP_PROPERTIES,set,TimeStepProperties,run);
    delete TimeStepProperties;
    TimeStepProperties = NULL;
  }  
}
/*F ans = SetUpInput(instances,instancesclass,run,runclass) . . . . algorithm
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int RxnDataRunIgnition::kinetics(BaseDataAlgorithmRun *run) {
  try {
  if(run->AlgorithmSummary.KeyWordInList("ExtraOutput")){
    cout << "Constant-pressure Adiabatic Ignition" << endl;
    cout << "Beginning at T = " <<  Conditions->Temperature->GetValue() << "K" << endl;
    cout << "Pressure = " << Conditions->Pressure->GetValue() << endl;
    cout << "Begin Setup" << endl;
  }

  clock_t t0 = clock();        // save end time
  // create an ideal gas mixture
  if(GasState == NULL) {
    if(run->AlgorithmSummary.KeyWordInList("ExtraOutput")){
      cout << "IdealGasMix GasState set up: '" <<  inputFileName.c_str() << "', '" << RootName.c_str() << "'" << endl;
    }
    GasState = new IdealGasMix(inputFileName.c_str(),RootName.c_str());
  } else {
    if(run->AlgorithmSummary.KeyWordInList("ExtraOutput")){
      cout << "Previous IdealGasMix GasState used" << endl;
    }
  }
  // set the state

  vector_fp *molfractions = formSpeciesFromConditions(run);
  /*
  GasState->setState_TPX(Conditions->Temperature->GetValue(), 
			 Conditions->Pressure->GetValue(), 
			 molfractions->begin());
  doublereal tol = 1e-8;
  Cantera::thermo_t *th = GasState;
  equilibrate(*th,"TP",0,tol,400,400,0);
  printf("Equilibrium Temperature: %10.4f\n",GasState->temperature());
  */
  GasState->setState_TPX(Conditions->Temperature->GetValue(), 
			 Conditions->Pressure->GetValue(),
			 (doublereal *) &(*(molfractions->begin())));

  int nsp = GasState->nSpecies();
  // create a reactor
  Reactor r;
  // create a reservoir to represent the environment
  Reservoir env;
  
  // 'insert' the gas into the reactor and environment.  Note
  // that it is ok to insert the same gas object into multiple
  // reactors or reservoirs. All this means is that this object
  // will be used to evaluate thermodynamic or kinetic
  // quantities needed.
  r.insert(*GasState);
  env.insert(*GasState);
  
  //r.addHomogenRxnSens(0);
  
  // create a wall between the reactor and the environment
  Wall w;
  w.install(r,env);
  
  // The wall "expansion rate coefficient" controls how fast it
  // moves in response to a pressure difference. Set it to a
  // large value to approach the constant-pressure limit, so
  // that the wall moves to counteract even small pressure
  // differences
  w.setExpansionRateCoeff(1.e9);
  
  // set the wall to have unit area (arbitrary)
  w.setArea(1.0);
  
  // create a container object to run the simulation
  // and add the reactor to it
  ReactorNet sim;
  sim.setTolerances(1.0e-6,1.0e-10);
  sim.addReactor(&r);
  
  clock_t t1 = clock();        // save start time
  doublereal tmsetup = 1.0*(t1 - t0)/CLOCKS_PER_SEC;
  if(run->AlgorithmSummary.KeyWordInList("ExtraOutput")){
    cout << "Setup Time: " << tmsetup << endl;
  }
  // Time step setup
  double tm;
  double dt = Conditions->DeltaT->GetValue();
  int nsteps = (int) numberOfIntervals;
  vector_fp temp(GasState->nSpecies());
  vector_fp last(GasState->nSpecies());
  vector_fp temp2(GasState->nSpecies());
  
  for(int i=0;i<GasState->nSpecies();i++) 
    last[i] = 0.0;

  // create a 2D array to hold the output variables,
  // and store the values for the initial state
  Array2D soln(nsp+4, 1);
  saveSoln(0, 0.0, *GasState, soln);
  int e0 = 0;
  ignitionTimeInitialize();
  runMatrixInitialize(nsteps,run);
  // main loop
  CurrentTime = 0.0;
  Iterations = 1;
  CurrentTime = sim.step(1.0e-3);
  cout << "After First Step: " << CurrentTime << endl;

  //  try {
    while(CurrentTime < finalTime) {
      clock_t t3 = clock();        // save start time
      if(Iterations > 1)
	e0 = sim.integrator().nEvals();
      
      CurrentTime += dt;
      if(run->AlgorithmSummary.KeyWordInList("ShowTimeSteps")){
	cout << 
	  "time =     " << CurrentTime << " s, dt=" << dt << endl;
      }
      //doublereal dtr = dt;
      //sim.setMaxStep(dtr);
      //double currentTemperature = GasState->temperature();
      sim.advance(CurrentTime);
      //cout << "Time STEP: "  << CurrentTime1 - CurrentTime << endl;
      clock_t t4 = clock();        // save start time
      int e1 = sim.integrator().nEvals();

      
      /*
      if((e1-e0) > 20 && dt > 5e-8) {
	dt = dt/2.0;
      }
      if((e1-e0) < 10) {
	dt = dt*2.0;
      }
      */
      ignitionTimeCheck(CurrentTime,dt,GasState->temperature());
      runMatrixTimeStepInfo(Iterations-1);
      
      if(run->AlgorithmSummary.KeyWordInList("ShowTimeSteps")){
	double tsteptime = 1.0*(t4 - t3)/CLOCKS_PER_SEC;
	cout << 
	  "T=         " << GasState->temperature() << "K " <<
	  "(time=     " << tsteptime << ", dt=" << dt << ") " <<
	  "evals:     " << (e1-e0) <<
	  endl;
      }
      GasState->getNetProductionRates(&(*(temp.begin())));
      double sum2 = 0.0;
      double top = 0.0;
      int topi;
      for(int i=0;i<GasState->nSpecies();i++) {
	if(temp[i]*temp[i] > top) {
	  top = temp[i]*temp[i];
	  topi = i;
	}
	sum2 += temp[i]*temp[i];
      }
      double sum = sqrt(sum2);

      GasState->getCreationRates(&(*(temp.begin())));
      double sumC2 = 0.0;
      for(int i=0;i<GasState->nSpecies();i++) {
	sumC2 += temp[i]*temp[i];
      }
      double sumC = sqrt(sumC2);

      printf("Net Change: %10.4e  %5d %10.4e  %10.4e %10.4e \n",top, topi,sumC, sum,sum*dt);
      /*
      if(sum*dt < 1e-5)
	dt = dt*2.0;
      if(sum*dt > 1e-3)
	dt = dt/2.0;
      if( dt > 1e-3)
      */
      if(sum*dt < 1e-9 && top < 1e-9 && Iterations > 30 && 
	 Conditions->Temperature->GetValue() + 500.0 < GasState->temperature()) {
	printf("Equilibrium Reached: %10.4e \n",sum);
	CurrentTime = finalTime;
      }

      saveSoln(tm, *GasState, soln);
      Iterations++;
    }
    clock_t t2 = clock();        // save end time
    if(run->AlgorithmSummary.KeyWordInList("ExtraOutput")){
      ignitionTimeFinalize(cout);
    }
    runMatrixFinalize(run);
    
    // Excel spreadsheet
    string plotTitle = "kinetics example 1: constant-pressure ignition";
    if(run->AlgorithmSummary.KeyWordInList("Excel")){
      String csv(OutputAttribute);
      csv.AppendToEnd(".csv");
      plotSoln(csv.c_str(), "XL", plotTitle, *GasState, soln);
    }
    
    
    // print final temperature and timing data
    totalRuntime = 1.0*(t2 - t1)/CLOCKS_PER_SEC;
    finalTemperature = r.temperature();
    numberEvaluations = sim.integrator().nEvals();
    numberEquations = sim.integrator().nEquations();
  } catch(CanteraError) {
    showErrors(cerr);
    return 1;
  }

    return 0;
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
bool RxnDataRunIgnition::Calculate(BaseDataSetOfInstances *instances,
				 DataSetOfInstancesClass *instancesclass,
				 BaseDataAlgorithmRun *run,
				 DataAlgorithmRunClass *runclass)
{
  bool result = true;
  kinetics(run);
  return result;
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
bool RxnDataRunIgnition::WriteOutputValues(BaseDataSetOfInstances *instances,
					 DataSetOfInstancesClass *instancesclass,
					 BaseDataAlgorithmRun *run,
					 DataAlgorithmRunClass *runclass)
{
  bool result = true;
  
  if(run->AlgorithmSummary.KeyWordInList("ExtraOutput")){
    cout << " Tfinal =          " << finalTemperature << endl;
    cout << " time =            " << totalRuntime << endl;    
    cout << " Iterations:       " << Iterations << endl;
    cout << " Evaluations:      " << numberEvaluations << endl;
    cout << " time per eval:    " << totalRuntime/numberEvaluations 
         << endl << endl;
  }
    String timeTMaxS(TIMETMAX_ATTRIBUTE);
    SaveRealValue(timeTMax,timeTMaxS);
    String timeOHMaxS(TIMEOHMAX_ATTRIBUTE);
    SaveRealValue(timeOHMax,timeOHMaxS);
    String totalRuntimeS(TOTALRUNTIME_ATTRIBUTE);
    SaveRealValue(totalRuntime,totalRuntimeS);
    String finalTemperatureS(FINALTEMPERATURE_ATTRIBUTE);
    SaveRealValue(finalTemperature,finalTemperatureS);
    String numberEvaluationsS(NUMBEREVALUATIONS_ATTRIBUTE);
    SaveIntegerValue(numberEvaluations,numberEvaluationsS);
    String numberEquationsS(NUMBEREQUATIONS_ATTRIBUTE);
    SaveIntegerValue(numberEquations,numberEquationsS);

    Conditions->NameTag = OutputAttribute;
    instances->AddObject(Conditions);
    Conditions->NameTag = ConditionsS;

  return result;
}


/*F ans = SetRealValue(value,name)  . . . algorithm
**
**  DESCRIPTION
**    value: The value
**    name: The name of the parameter
**    
**  REMARKS
**
*/
void RxnDataRunIgnition::SaveRealValue(double value, String& name) {
  BaseDataReal *R = new BaseDataReal();
  R->NameTag = name;
  R->SetValue(value);
  Conditions->AddObject(R);
  delete R;
}
/*F ans = SetRealValue(value,name)  . . . algorithm
**
**  DESCRIPTION
**    value: The value
**    name: The name of the parameter
**    
**  REMARKS
**
*/
void RxnDataRunIgnition::SaveIntegerValue(int value, String& name) {
  BaseDataInteger *R = new BaseDataInteger();
  R->NameTag = name;
  R->SetValue(value);
  Conditions->AddObject(R);
  delete R;
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
bool RxnDataRunIgnition::ConcludeRun(BaseDataSetOfInstances *instances,
				   DataSetOfInstancesClass *instancesclass,
				   BaseDataAlgorithmRun *run,
				   DataAlgorithmRunClass *runclass)
{
  bool result = true;
//  delete something
  return result;
}
/*F ans = Jacobian()  . . . algorithm
**
**  DESCRIPTION
**    value: The value
**    name: The name of the parameter
**    
**  REMARKS
**
bool RxnDataRunIgnition::Jacobian() {
  int nsp = GasState->nSpecies();
  Array2D ref = new Array2D(nsp,1);
  Array2D temp = new Array2D(*ref);
  gas.getMoleFractions(ref);
  for(int i=0;i<nsp;i++) {
  }

}
*/
/*S BaseDataRunSetOfConditions
 */ 
/*F BaseDataRunSetOfConditions()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataRunSetOfConditions::BaseDataRunSetOfConditions() 
  : RootNameS(CHEMKINREAD_FILEROOT),
    IterationSetS(ITERATIONSET_ATTRIBUTE),
    ConditionsS(CONDITIONS_ATTRIBUTE),
    OutputNameS(OUTPUTMATRIX_ATTRIBUTE),
    PressureAttribute(PRESSURE_ATTRIBUTE),
    TemperatureAttribute(TEMPERATURE_ATTRIBUTE),
    DeltaTAttribute(DELTAT_ATTRIBUTE),
    SpeciesAttribute(SPECIES_ATTRIBUTE)
{

  Identification = RUNIGNITION_RUNSETOFCONDITIONS_ID;
  NameTag = RUNIGNITION_RUNSETOFCONDITIONS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataRunSetOfConditions(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataRunSetOfConditions::BaseDataRunSetOfConditions(const BaseDataRunSetOfConditions& data)
  : BaseDataAlgorithmOperation(data),
    RootNameS(data.RootNameS),
    IterationSetS(data.IterationSetS),
    ConditionsS(data.ConditionsS),
    OutputNameS(data.OutputNameS),
    PressureAttribute(data.PressureAttribute),
    TemperatureAttribute(data.TemperatureAttribute),
    DeltaTAttribute(data.DeltaTAttribute),
    SpeciesAttribute(data.SpeciesAttribute)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataRunSetOfConditions
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataRunSetOfConditions::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataRunSetOfConditions
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataRunSetOfConditions::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataRunSetOfConditions
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataRunSetOfConditions::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataRunSetOfConditions
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataRunSetOfConditions::Clone()
{
  BaseDataRunSetOfConditions *obj = new BaseDataRunSetOfConditions(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataRunSetOfConditions
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataRunSetOfConditions::CopyClone(Identify * obj)
{
  BaseDataRunSetOfConditions *objfull = (BaseDataRunSetOfConditions *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataRunSetOfConditions
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataRunSetOfConditions::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && IterationSetS.EncodeThis(buffer);
  result = result && RootNameS.EncodeThis(buffer);
  result = result && ConditionsS.EncodeThis(buffer);
  result = result && OutputNameS.EncodeThis(buffer);
  result = result && SpeciesAttribute.EncodeThis(buffer);
  result = result && TemperatureAttribute.EncodeThis(buffer);
  result = result && PressureAttribute.EncodeThis(buffer);
  result = result && DeltaTAttribute.EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataRunSetOfConditions
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataRunSetOfConditions::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && IterationSetS.DecodeThis(buffer);
  result = result && RootNameS.DecodeThis(buffer);
  result = result && ConditionsS.DecodeThis(buffer);
  result = result && OutputNameS.DecodeThis(buffer);
  result = result && SpeciesAttribute.DecodeThis(buffer);
  result = result && TemperatureAttribute.DecodeThis(buffer);
  result = result && PressureAttribute.DecodeThis(buffer);
  result = result && DeltaTAttribute.DecodeThis(buffer);
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
bool BaseDataRunSetOfConditions::SetUpAlgorithms(BaseDataSetOfInstances *instances,
				       DataSetOfInstancesClass *instancesclass,
				       BaseDataAlgorithmRun *run,
				       DataAlgorithmRunClass *runclass)
{
  if(runclass->getDebugLevel() > 2)
    {
      cout << "List of Algorithms" << endl;
      run->GetListOfSubAlgorithms().print(cout);
      cout << endl;
    }
  ObjectList<String> algnames = run->GetListOfSubAlgorithms();
  algnames.pop_front();

  String CalculationName  = algnames.front();
  Calculation = (RxnDataRunIgnition *) run->GetSubAlgorithm(CalculationName);
  if(runclass->getDebugLevel() > 2)
    {
      cout << "\nCalculation: " << CalculationName << endl;
      Calculation->print(cout);
      cout << endl;
    }
  
  return true;
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
bool BaseDataRunSetOfConditions::CheckInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;
  result = result && CheckInputVariable(IterationSetS,"The set of interation conditions",run);
  result = result && CheckInputVariable(RootNameS,"The root name",run);
  result = result && CheckInputVariable(ConditionsS,"The base set of conditions",run);
  result = result && CheckInputVariable(OutputNameS,"The name of the output variable",run);
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
bool BaseDataRunSetOfConditions::SetUpInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;
  IterationSet = (BaseDataIterationSet *) run->ParameterValue(IterationSetS);
  BaseDataString *rootname = (BaseDataString *) run->ParameterValue(RootNameS);
  RootName = rootname->getString();
  Conditions = (RxnDataIgnitionConditions *) run->ParameterValue(ConditionsS);
  OutputAttribute = (BaseDataString *) run->ParameterValue(OutputNameS);

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
bool BaseDataRunSetOfConditions::Calculate(BaseDataSetOfInstances *instances,
				 DataSetOfInstancesClass *instancesclass,
				 BaseDataAlgorithmRun *run,
				 DataAlgorithmRunClass *runclass)
{
  int type = IterationSet->GetType();
  DataSetOfObjectsClass *classes = instancesclass->PointerToAllowedClasses();
  DataIterationSetClass *iterationclass = (DataIterationSetClass *) classes->GetObjectClass(type);
  bool result = IterationSet->initialize(iterationclass);
  BaseDataSetOfObjects *current = IterationSet->getCurrent();
  ConditionNames = new BaseDataKeySet();
  ConditionNames->NameTag = CONDITIONNAMES_ATTRIBUTE;

  if(run->AlgorithmSummary.KeyWordInList("FileSummary")){
    String name(RootName);
    name.AppendToEnd("-SetSummary");
    fileSummary = new OpenOutputFile(name,"csv");
    fileSummary->Stream << "Constant-pressure Adiabatic Ignition" << endl;

    fileSummary->Stream << "T[K]" << ","
			<< "P" << ",";
    ObjectListString sp = Conditions->Species->ListOfObjectNames();
    ObjectListString::iterator iter;
    for(iter=sp.begin();iter != sp.end();iter++) {
      fileSummary->Stream << *iter << ",";
    }
    fileSummary->Stream << "Tend" << ","
			<< "TimeTMax" << ","
			<< "TotalTime" << "," 
			<< "Evaluations"
			<< endl;
  }
  bool notdone = true;
  while(notdone) {
    if(current->IsInList(TemperatureAttribute)) {
      if(Conditions->Temperature != NULL) {
	delete Conditions->Temperature;
	Conditions->Temperature = NULL;
      }
      Conditions->Temperature = (BaseDataReal *) 
	current->GetObject(TemperatureAttribute)->Clone();
    }

    if(current->IsInList(PressureAttribute)) {
      if(Conditions->Pressure != NULL) {
	delete Conditions->Pressure;
	Conditions->Pressure = NULL;
      }
      Conditions->Pressure = (BaseDataReal *) 
	current->GetObject(PressureAttribute)->Clone();
    }
    if(current->IsInList(SpeciesAttribute)) {
      if(Conditions->Species != NULL) {
	delete Conditions->Species;
      }
      Conditions->Species = (BaseDataSetOfObjects *) 
	current->GetObject(SpeciesAttribute)->Clone();
    }
    String name(RootName);
    name.AppendToEnd("-");
    name.AppendToEnd(current->NameTag);
    OutputAttribute->setString(name);
    ConditionNames->AddKeyWord(OutputAttribute->getString());

    result = result && Calculation->operator()(instances,instancesclass,
						run,runclass);
    if(run->AlgorithmSummary.KeyWordInList("FileSummary")){
      fileSummary->Stream << Conditions->Temperature->GetValue() << ","
			  << Conditions->Pressure->GetValue() << ",";
      ObjectListString sp = Conditions->Species->ListOfObjectNames();
      ObjectListString::iterator iter;
      for(iter=sp.begin();iter != sp.end();iter++) {
	BaseDataReal *r = (BaseDataReal *) Conditions->Species->GetObject(*iter);
	fileSummary->Stream << r->GetValue() << ",";
      }
      fileSummary->Stream << Calculation->finalTemperature << ","
			  << Calculation->timeTMax << ","
			  << Calculation->totalRuntime << "," 
			  << Calculation->numberEvaluations
			  << endl;
    }    
    current = IterationSet->nextIterator(iterationclass);
    if(current == NULL) 
      notdone = false;
  }
  return result;
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
bool BaseDataRunSetOfConditions::WriteOutputValues(BaseDataSetOfInstances *instances,
					 DataSetOfInstancesClass *instancesclass,
					 BaseDataAlgorithmRun *run,
					 DataAlgorithmRunClass *runclass)
{
  bool result = true;
  
  ConditionNames->print(cout);
  cout << endl;
  instances->AddObject(ConditionNames);
  delete ConditionNames;

//  run->AddParameter(ctree);

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
bool BaseDataRunSetOfConditions::ConcludeRun(BaseDataSetOfInstances *instances,
				   DataSetOfInstancesClass *instancesclass,
				   BaseDataAlgorithmRun *run,
				   DataAlgorithmRunClass *runclass)
{
  bool result = true;
  return result;
}
/*S DataRunSetOfConditionsClass
 */
/*F DataRunSetOfConditionsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataRunSetOfConditionsClass::DataRunSetOfConditionsClass()
  :ConditionsClass(NULL) {
  Identification = RUNIGNITION_RUNSETOFCONDITIONS_ID;
  NameTag = RUNIGNITION_RUNSETOFCONDITIONS_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataRunSetOfConditionsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataRunSetOfConditionsClass::DataRunSetOfConditionsClass(const DataRunSetOfConditionsClass& data)
  : DataAlgorithmOperationClass(data) {
  ConditionsClass = (RxnIgnitionConditionsClass *) PointerClone(data.ConditionsClass);
} 
 
/*F DataRunSetOfConditionsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataRunSetOfConditionsClass::DataRunSetOfConditionsClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr),
    ConditionsClass(NULL)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = "RunSetOfConditions";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataRunSetOfConditionsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataRunSetOfConditionsClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  PointerPrint(out," Conditions Class "," No Class Defined ",ConditionsClass);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataRunSetOfConditionsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataRunSetOfConditionsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataRunSetOfConditionsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  result = result && PointerClassRead(in,(DataObjectClass *&) ConditionsClass,
				      RUNIGNITION_IGNITIONSCONDITIONS_NAME,
				      set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataRunSetOfConditionsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataRunSetOfConditionsClass::CopyClone(Identify *  objc)
{
  DataRunSetOfConditionsClass *objcfull = (DataRunSetOfConditionsClass *) objc;
  *this = *objcfull;
  ConditionsClass = (RxnIgnitionConditionsClass *) PointerClone(objcfull->ConditionsClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataRunSetOfConditionsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataRunSetOfConditionsClass::Clone()
    {
      DataRunSetOfConditionsClass* id = new DataRunSetOfConditionsClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataRunSetOfConditionsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataRunSetOfConditionsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,(BaseDataObject *&) ConditionsClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataRunSetOfConditionsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataRunSetOfConditionsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) ConditionsClass);
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
BaseDataObject * DataRunSetOfConditionsClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataRunSetOfConditions();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataRunSetOfConditionsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataRunSetOfConditionsClass*& obj)
     {
     obj = new DataRunSetOfConditionsClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataRunSetOfConditions
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataRunSetOfConditions*& obj)
     {
     obj = new BaseDataRunSetOfConditions;
     return obj->DecodeThis(buffer);
     }



/*S Utilities
 */

// Save the temperature, density, pressure, and mole fractions at one
// time
template<class G, class A>
void saveSoln(int i, double time, const G& gas, A& soln) {  
    soln(0,i) = time;
    soln(1,i) = gas.temperature();
    soln(2,i) = gas.density();
    soln(3,i) = gas.pressure();
    gas.getMoleFractions(&soln(4,i));
}

template<class G, class A>
void saveSoln(double time, const G& gas, A& soln) {  
    soln.resize(static_cast<int>(soln.nRows()), 
		static_cast<int>(soln.nColumns()) + 1);
    int back = static_cast<int>(soln.nColumns()) - 1;
    soln(0,back) = time;
    soln(1,back) = gas.temperature();
    soln(2,back) = gas.density();
    soln(3,back) = gas.pressure();
    int nsp = gas.nSpecies();
    for (int k = 0; k < nsp; k++) 
        soln(4+k,back) = gas.moleFraction(k);
}

template<class G, class V>
void makeDataLabels(const G& gas, V& names) {
    int nsp = gas.nSpecies();
    names.resize(nsp + 4);
    names[0] = "time (s)";
    names[1]  = "Temperature (K)";
    names[2]  = "Density (kg/m3)";
    names[3]  = "Pressure (Pa)";
    int k;
    for (k = 0; k < nsp; k++) names[4+k] = gas.speciesName(k);
}

template<class G, class A>
void plotSoln(string fname, string fmt, string title, const G& gas, const A& soln) {
    vector<string> names;
    makeDataLabels(gas, names);
    writePlotFile(fname, fmt, title, names, soln);
}


/*F InitializeRunIgnitionDecodeFunctions()  . . . . . . . . . . . . Reactions
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void InitialRunIgnitionDecodeFunctions() {
  EncodeDecodeRegisterClass(RxnRunIgnitionClass,RxnDataRunIgnition,RUNIGNITION_RUNIGNITION_NAME);
  EncodeDecodeRegisterClass(RxnIgnitionConditionsClass,RxnDataIgnitionConditions,RUNIGNITION_IGNITIONSCONDITIONS_NAME);
  EncodeDecodeRegisterClass(DataRunSetOfConditionsClass,BaseDataRunSetOfConditions,RUNIGNITION_RUNSETOFCONDITIONS_NAME);
}
/*F AddRunIgnitionClasses(set) . . . . . . . . . . . .  EquilibriumConst
**
**  DESCRIPTION
**    set: The set of classes to add them to
**
**  REMARKS
**
*/
void AddRunIgnitionClasses(DataSetOfObjectsClass& set) {
  String descr("Algorithm: Run a single ignition job with Cantera");
  RxnRunIgnitionClass runclass(RUNIGNITION_RUNIGNITION_ID,RUNIGNITION_RUNIGNITION_NAME,descr);
  set.AddObjectClass(runclass);

  String cnddescr("The Ignition Run Conditions Class");
  RxnIgnitionConditionsClass cndclass(RUNIGNITION_IGNITIONSCONDITIONS_ID,RUNIGNITION_IGNITIONSCONDITIONS_NAME,descr);
  set.AddObjectClass(cndclass);

  String runsetdescr("Run a set of conditions");
  DataRunSetOfConditionsClass runsetclass(RUNIGNITION_RUNSETOFCONDITIONS_ID,RUNIGNITION_RUNSETOFCONDITIONS_NAME,runsetdescr);
  set.AddObjectClass(runsetclass);
}
