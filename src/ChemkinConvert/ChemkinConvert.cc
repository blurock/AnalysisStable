/*  FILE     ChemkinConvert.cc
**  PACKAGE  ChemkinConvert
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "ChemkinConvert" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 2006 Edward S. Blurock
*/
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "FullReaction.hh"

#include <cantera/Cantera.h>
#include "cantera/kernel/converters/CKReader.h"
#include <cantera/zerodim.h>
#include <cantera/IdealGasMix.h>
#include <time.h>
#include <cantera/kernel/Array.h>
#include <cantera/kernel/plots.h>

#include "ChemkinConvert.hh"

/*S RxnDataReadChemkin
 */ 
/*F RxnDataReadChemkin()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
RxnDataReadChemkin::RxnDataReadChemkin() 
  : chemkinFileNameExtension(DEFAULT_CHEMKIN_EXT),
    thermoFileNameExtension(DEFAULT_THERMO_EXT),
    fileRootNameS(CHEMKINREAD_FILEROOT),
    MoleculeClassS(MOLECULE_CLASS_PARAMETER),
    ReactionClassS(REACTION_CLASS_PARAMETER),
    MechanismClassS(MECHANISM_CLASS_PARAMETER),
    ChemkinClassS(CHEMKIN_CLASS_PARAMETER),
    ReactionRateS(REACTION_RATE_NAME),
    ThirdBodyS(REACTION_THIRDBODY_NAME),
    ReactionRateHiLowS(REACTION_HILOW_NAME),
    ChemkinThermoNameS(THERMO_NAME_PARAMETER),
    ChemkinNameS(CHEMKIN_NAME_PARAMETER),
    ReferenceS(REFERENCE_PARAMETER),
    MoleculeSummaryS(MOLECULE_SUMMARY_PARAMETER)
{
  Identification = CHEMKINCONVERT_READCHEMKIN_ID;
  NameTag = CHEMKINCONVERT_READCHEMKIN_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F RxnDataReadChemkin(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
RxnDataReadChemkin::RxnDataReadChemkin(const RxnDataReadChemkin& data)
  : BaseDataAlgorithmOperation(data),
    chemkinFileNameExtension(data.chemkinFileNameExtension),
    thermoFileNameExtension(data.thermoFileNameExtension),
    fileRootNameS(data.fileRootNameS),
    MoleculeClassS(data.MoleculeClassS),
    ReactionClassS(data.ReactionClassS),
    MechanismClassS(data.MechanismClassS),
    ChemkinClassS(data.ChemkinClassS),
    ReactionRateS(data.ReactionRateS),
    ThirdBodyS(data.ThirdBodyS),
    ReactionRateHiLowS(data.ReactionRateHiLowS),
    ChemkinThermoNameS(data.ChemkinThermoNameS),
    ChemkinNameS(data.ChemkinNameS),
    ReferenceS(data.ReferenceS),
    MoleculeSummaryS(data.MoleculeSummaryS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in RxnDataReadChemkin
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool RxnDataReadChemkin::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in RxnDataReadChemkin
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool RxnDataReadChemkin::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  RxnDataReadChemkin
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& RxnDataReadChemkin::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  out << "RootName:              '" << fileRootNameS << "'" << endl;
  out << "MoleculeClassS:        '" << MoleculeClassS << "'" << endl;
  out << "ReactionClassS:        '" << ReactionClassS << "'" << endl;
  out << "MechanismClassS:       '" << MechanismClassS << "'" << endl;
  out << "ChemkinClassS:         '" << ChemkinClassS << "'" << endl;
  out << "ReactionRateS:         '" << ReactionRateS << "'" << endl;
  out << "ThirdBodyS:            '" << ThirdBodyS << "'" << endl;
  out << "ReactionRateHiLowS:    '" << ReactionRateHiLowS << "'" << endl;
  out << "ChemkinThermoName:     '" << ChemkinThermoNameS << "'" << endl;
  out << "ChemkinName:           '" << ChemkinNameS << "'" << endl;
  out << "ReferenceS:            '" << ReferenceS << "'" << endl;
  out << "MoleculeSummaryS:      '" << MoleculeSummaryS << "'" << endl;

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .RxnDataReadChemkin
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * RxnDataReadChemkin::Clone()
{
  RxnDataReadChemkin *obj = new RxnDataReadChemkin(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .RxnDataReadChemkin
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void RxnDataReadChemkin::CopyClone(Identify * obj)
{
  RxnDataReadChemkin *objfull = (RxnDataReadChemkin *) obj;
  *this = *objfull;
  //Parameter = (RxnData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  RxnDataReadChemkin
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool RxnDataReadChemkin::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  result = result && chemkinFileNameExtension.EncodeThis(buffer);
  result = result && thermoFileNameExtension.EncodeThis(buffer);
  result = result && fileRootNameS.EncodeThis(buffer);
  result = result && MoleculeClassS.EncodeThis(buffer);
  result = result && ReactionClassS.EncodeThis(buffer);
  result = result && MechanismClassS.EncodeThis(buffer);
  result = result && ChemkinClassS.EncodeThis(buffer);
  result = result && ReactionRateS.EncodeThis(buffer);
  result = result && ThirdBodyS.EncodeThis(buffer);
  result = result && ReactionRateHiLowS.EncodeThis(buffer);
  result = result && ChemkinThermoNameS.EncodeThis(buffer);
  result = result && ChemkinNameS.EncodeThis(buffer);
  result = result && ReferenceS.EncodeThis(buffer);
  result = result && MoleculeSummaryS.EncodeThis(buffer);

  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  RxnDataReadChemkin
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool RxnDataReadChemkin::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  result = result && chemkinFileNameExtension.DecodeThis(buffer);
  result = result && thermoFileNameExtension.DecodeThis(buffer);
  result = result && fileRootNameS.DecodeThis(buffer);
  result = result && MoleculeClassS.DecodeThis(buffer);
  result = result && ReactionClassS.DecodeThis(buffer);
  result = result && MechanismClassS.DecodeThis(buffer);
  result = result && ChemkinClassS.DecodeThis(buffer);
  result = result && ReactionRateS.DecodeThis(buffer);
  result = result && ThirdBodyS.DecodeThis(buffer);
  result = result && ReactionRateHiLowS.DecodeThis(buffer);
  result = result && ChemkinThermoNameS.DecodeThis(buffer);
  result = result && ChemkinNameS.DecodeThis(buffer);
  result = result && ReferenceS.DecodeThis(buffer);
  result = result && MoleculeSummaryS.DecodeThis(buffer);

  return result;
}
 
 
/*S RxnReadChemkinClass
 */
/*F RxnReadChemkinClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
RxnReadChemkinClass::RxnReadChemkinClass()
{
  Identification = CHEMKINCONVERT_READCHEMKIN_ID;
  NameTag = CHEMKINCONVERT_READCHEMKIN_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F RxnReadChemkinClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
RxnReadChemkinClass::RxnReadChemkinClass(const RxnReadChemkinClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F RxnReadChemkinClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
RxnReadChemkinClass::RxnReadChemkinClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = "ReadChemkin";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . RxnReadChemkinClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& RxnReadChemkinClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . RxnReadChemkinClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base RxnReadChemkinClass, there is no further information.
**
**  REMARKS
**
*/
bool RxnReadChemkinClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . RxnReadChemkinClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void RxnReadChemkinClass::CopyClone(Identify *  objc)
{
  RxnReadChemkinClass *objcfull = (RxnReadChemkinClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . RxnReadChemkinClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * RxnReadChemkinClass::Clone()
    {
      RxnReadChemkinClass* id = new RxnReadChemkinClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . RxnReadChemkinClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool RxnReadChemkinClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);
  
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . RxnReadChemkinClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool RxnReadChemkinClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
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
BaseDataObject * RxnReadChemkinClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new RxnDataReadChemkin();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . RxnReadChemkinClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, RxnReadChemkinClass*& obj)
     {
     obj = new RxnReadChemkinClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . RxnDataReadChemkin
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, RxnDataReadChemkin*& obj)
     {
     obj = new RxnDataReadChemkin;
     return obj->DecodeThis(buffer);
     }
//EncodeDecodeRegisterClass(RxnReadChemkinClass,RxnDataReadChemkin,_NAME);
//String descr("The Class");
//RxnReadChemkinClass class(_ID,_NAME,descr);
//set.AddObjectClass(class);
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
bool RxnDataReadChemkin::SetUpAlgorithms(BaseDataSetOfInstances *instances,
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
bool RxnDataReadChemkin::CheckInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;
  
  result = result && CheckInputVariable(fileRootNameS," root name of the CHEMKIN file ",run);
  result = result && CheckInputVariable(MoleculeClassS," Molecule Class Name ",run);
  result = result && CheckInputVariable(ReactionClassS," Reaction Class Name ",run);
  result = result && CheckInputVariable(MechanismClassS," Mechanism Class Name ",run);
  result = result && CheckInputVariable(ReactionRateS," Third Body reaction rate class ",run);
  result = result && CheckInputVariable(ThirdBodyS," Third Body reaction rate class ",run);
  result = result && CheckInputVariable(ReactionRateHiLowS," pressure dependent (hi,low) rate class ",run);
  result = result && CheckInputVariable(ChemkinClassS," CHEMKIN class ",run);
  result = result && CheckInputVariable(ChemkinThermoNameS," thermo name in instance ",run);
  result = result && CheckInputVariable(ChemkinNameS," Chemkin Name in instance ",run);
  result = result && CheckInputVariable(ReferenceS," Mechanism Reference ",run);
  result = result && CheckInputVariable(MoleculeSummaryS," Molecule Summary class ",run);

  if(run->AlgorithmSummary.KeyWordInList("SeparateThermo")){
    cout << endl << "Input is CHEMKIN file and a separate THERMO file" << endl;
  } else {
    cout << endl << "THERMO and CHEMKIN information in one file" << endl;
  }
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
bool RxnDataReadChemkin::SetUpInput(BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instancesclass,
				  BaseDataAlgorithmRun *run,
				  DataAlgorithmRunClass *runclass)
{
  bool result = true;

  DataSetOfObjectsClass *classes = instancesclass->PointerToAllowedClasses();

  BaseDataString *scls = (BaseDataString *) run->ParameterValue(MoleculeClassS);
  BaseDataString *rcls = (BaseDataString *) run->ParameterValue(ReactionClassS);
  BaseDataString *mcls = (BaseDataString *) run->ParameterValue(MechanismClassS);

  MoleculeClass = (RxnSimpleMoleculeClass *) classes->GetObjectClass(scls->getString());
  ReactionClass = (RxnReactionClass *) classes->GetObjectClass(rcls->getString());
  MechanismClass = (RxnMechanismClass *)  classes->GetObjectClass(mcls->getString());

  BaseDataString *rate  = (BaseDataString *) run->ParameterValue(ReactionRateS);
  BaseDataString *third = (BaseDataString *) run->ParameterValue(ThirdBodyS);
  BaseDataString *hilow = (BaseDataString *) run->ParameterValue(ReactionRateHiLowS);

  ReactionRateClass      = (RxnReactionRatesClass *) classes->GetObjectClass(rate->getString());
  ThirdBodyClass         = (RxnReactionRatesClass *) classes->GetObjectClass(third->getString());
  ReactionRateHiLowClass = (RxnReactionRatesClass *) classes->GetObjectClass(hilow->getString());

  BaseDataString *ck = (BaseDataString *) run->ParameterValue(ChemkinClassS);
  ChemkinClass = (RxnChemkinThermoClass *) classes->GetObjectClass(ck->getString());
  MolSummaryClass = MechanismClass->getMoleculeSummaryClass();
  
  chemkinFileRoot = (BaseDataString *) run->ParameterValue(fileRootNameS);
  cout << "CHEMKIN file root name: '";
  chemkinFileRoot->print(cout);
  cout << endl;
  chemkinFileName = chemkinFileRoot->getString();
  chemkinFileName.AppendToEnd(chemkinFileNameExtension);
  cout << "CHEMKIN: ";
  chemkinFileName.print(cout);
  cout << endl;
  
  
  BaseDataString *cname = (BaseDataString *) run->ParameterValue(ChemkinNameS);    
  /*
  if(instances->IsInList(cname->getString())) {
    BaseDataString *cnameS = (BaseDataString *) instances->GetObject(cname->getString());
    ChemkinName = cnameS->getString();
  } else {
      cerr << "Chemkin Name parameter not found: '" << cname->getString() << "'" << endl;
      result = false;
  }
  */
  ChemkinName = cname->getString();
  BaseDataString *ctname = (BaseDataString *) run->ParameterValue(ChemkinThermoNameS);    
  /*
  if(instances->IsInList(ctname->getString())) {
    BaseDataString *ctnameS = (BaseDataString *) instances->GetObject(ctname->getString());
      ChemkinThermoName = ctnameS->getString();
  } else {
    cerr << "Chemkin Thermo Name parameter not found: '" << ctname->getString() << "'" << endl;
    result = false;
  }
  */
  ChemkinThermoName = ctname->getString();
    BaseDataString *ms = (BaseDataString *) run->ParameterValue(MoleculeSummaryS);  
    if(instances->IsInList(ms->getString())) {
      MolSummary  = (BaseDataSetOfObjects *) instances->GetObject(ms->getString());
    } else {
      cerr << "No Standard Molecule Summary found in instances: '" << ms->getString()<< "'" << endl;
      cerr << "Continuing" << endl;
      result = false;
    }
    BaseDataString *ref = (BaseDataString *) run->ParameterValue(ReferenceS);
    if(result && instances->IsInList(ref->getString()))
    Reference = (RxnDataLiteratureReference *) instances->GetObject(ref->getString());
    else {
      cerr << "Reference: '" << ref->getString() << "' not found" << endl;
      result = false;
    }
    if(run->AlgorithmSummary.KeyWordInList("SeparateThermo")){
      thermoFileName = chemkinFileRoot->getString();
      thermoFileName.AppendToEnd(thermoFileNameExtension);
      cout << "THERMO: ";
      thermoFileName.print(cout);
      cout << endl;
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
bool RxnDataReadChemkin::Calculate(BaseDataSetOfInstances *instances,
				   DataSetOfInstancesClass *instancesclass,
				   BaseDataAlgorithmRun *run,
				   DataAlgorithmRunClass *runclass) {
  reactionCount = 0;

  SetUpMechanismInInstance(instances);
  ReactionList = new BaseDataKeyWords(0);
  ReactionList->NameTag = REACTION_LIST;
  bool result = true;
  cout << "Start Reading CHEMKIN file" << endl;
  ckr::CKReader reader;
  reader.debug = true;
  
  reader.read(chemkinFileName.c_str(),"","logfile.out");
  BuildMoleculeData(instances,instancesclass,reader.species);
  BuildReactionSet(instances,instancesclass,reader.reactions);

  instances->AddObject(ReactionList);

  //if(run->AlgorithmSummary.KeyWordInList("")){}
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
bool RxnDataReadChemkin::WriteOutputValues(BaseDataSetOfInstances *instances,
					 DataSetOfInstancesClass *instancesclass,
					 BaseDataAlgorithmRun *run,
					 DataAlgorithmRunClass *runclass)
{
  bool result = true;
  
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
bool RxnDataReadChemkin::ConcludeRun(BaseDataSetOfInstances *instances,
				   DataSetOfInstancesClass *instancesclass,
				   BaseDataAlgorithmRun *run,
				   DataAlgorithmRunClass *runclass)
{
  bool result = true;
//  delete something
  return result;
}
/*F MakeNewInstance(name,instances)
**
**  DESCRIPTION
**    name: Name of empty instance to create
**    instances: The set of instances
**
**  REMARKS
**
*/
BaseDataInstance *RxnDataReadChemkin::MakeNewInstance(String name, BaseDataSetOfInstances *instances)
{
  BaseDataInstance *newinstance = new BaseDataInstance;
  newinstance->NameTag = name;
  instances->AddInstance(*newinstance);
  delete newinstance;
  newinstance = (BaseDataInstance *) instances->GetInstance(name);
  return newinstance;
}
/*F SetUpMechanismInInstance(instances)
**
**  DESCRIPTION
**    instances: The set of instances to store mechanism instance
**
**    This sets up the mechanism instance.  The Mechanism slot in the
**    class is set up also (pointer within instance to spare extra Clone()ing
**
**  REMARKS
**
*/
void RxnDataReadChemkin::SetUpMechanismInInstance(BaseDataSetOfInstances *instances)
{
  cout << "Mechanism: " << chemkinFileRoot->getString() << endl;
  
  Mechanism = (RxnDataMechanism *) MechanismClass->BaseDataObjectExample();
  String mechS("Mechanism");
  Mechanism->NameTag = mechS;
  BaseDataInstance *instance = MakeNewInstance(chemkinFileRoot->getString(),instances);

  instance->AddObject(Mechanism);
  delete Mechanism;
  Mechanism = (RxnDataMechanism *) instance->GetObject(mechS);
  Mechanism->setUpMoleculeSummaries(MolSummary);

}

/*F BuildMoleculeData(instances,instanceclasses)
**
**  DESCRIPTION
**    instances: The set of instances to store mechanism instance
**
**  REMARKS
**
*/
void RxnDataReadChemkin::BuildMoleculeData(BaseDataSetOfInstances *instances,
					      DataSetOfInstancesClass *instancesclass,
					      ckr::speciesList specieslist) {
  ckr::speciesList::iterator species;
  BaseDataKeyWords *moleculelist = new BaseDataKeyWords();
  moleculelist->NameTag = MOLECULE_LIST;
  for(species = specieslist.begin();species != specieslist.end();species++) {
    String name = String((*species).name.c_str());
    BaseDataInstance *instance = MakeNewInstance(name,instances);
    RxnDataSimpleMolecule *simple = (RxnDataSimpleMolecule *) MoleculeClass->BaseDataObjectExample();
    RxnDataChemkinThermo *chemkin = (RxnDataChemkinThermo *) ChemkinClass->BaseDataObjectExample();
    RxnDataMoleculeSummary *molsum = (RxnDataMoleculeSummary *) MolSummaryClass->BaseDataObjectExample();

    chemkin->setReference(Reference);
    chemkin->NameTag = ChemkinThermoName;
    molsum->NameTag = name;
    molsum->ThermodynamicInfo = chemkin->NameTag;
    molsum->ShortName = ChemkinName;
    Mechanism->addMoleculeSummary(molsum);
    molsum->NameTag = MOLECULE_SUMMARY_NAME;
    instance->AddObject(molsum);
    simple->NameTag = name;

    Mechanism->addMolecule(simple->NameTag);
    moleculelist->AddKeyWord(simple->NameTag);
    AddAtomProperties(*species,simple);
    TransferThermoData(chemkin,*species);
    StoreChemkinNameInMolecule(chemkin->getSpeciesName(), simple, instance);
    StoreThermoInMolecule(chemkin,simple,instance);
    Mechanism->AddObject(simple);
    simple->NameTag = MoleculeClass->GetNameInInstance();
    instance->AddObject(simple);
  }
  instances->AddObject(moleculelist);
  Mechanism->AddObject(moleculelist);
}
/*F TransferThermoData(chemkin,species)  . . . . . . . . . . . . Reactions
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void RxnDataReadChemkin::TransferThermoData(RxnDataChemkinThermo *chemkin,
			ckr::Species& species) {
  String *name = new String(species.name.c_str());
  chemkin->SpeciesName = *name;
  delete name;
  String *id = new String(species.id.c_str());
  chemkin->Date = *id;
  delete id;
  String *phase = new String(species.phase.c_str());
  chemkin->PhaseDescriptor = *phase;
  delete phase;
  FormFormulaDescriptor(species,&(chemkin->FormulaDescriptor));
  chemkin->AtSymbAndFormula = FillStringToLength(20,chemkin->FormulaDescriptor);
  chemkin->LowerBoundTemp = species.tlow;
  chemkin->UpperBoundTemp = species.thigh;
  chemkin->CommonTemp = species.tmid;
  VectorNumeric *upper = new VectorNumeric(7);
  VectorNumeric *lower = new VectorNumeric(7);
  chemkin->UpperCoeff = *upper;
  chemkin->LowerCoeff = *lower;
  delete upper;
  delete lower;
  for(int i=0;i<7;i++) {
    chemkin->UpperCoeff[i] = species.highCoeffs[i];
    chemkin->LowerCoeff[i] = species.lowCoeffs[i];
  }
}
void RxnDataReadChemkin::FormFormulaDescriptor(ckr::Species& species,String *full) {
  for(map<string, double>::const_iterator atm = species.comp.begin();
      atm != species.comp.end(); atm++) {
    unsigned int num = (unsigned int) floor(atm->second);
    char str[7];
    sprintf(str,"%-2s%3d",atm->first.c_str(),num);
    str[0] = (char) toupper(str[0]);
    str[1] = (char) toupper(str[1]);
    String *form = new String(str);
    full->AppendToEnd(*form);
    delete form;
  }
}
void RxnDataReadChemkin::AddAtomProperties(ckr::Species& species, 
					   RxnDataSimpleMolecule *simple) {
  RxnMoleculeAtomClass *atomclass = 
    (RxnMoleculeAtomClass *) MoleculeClass->NodeClass;
  RxnBasicAtomDataClass *atomdataclass = (RxnBasicAtomDataClass *)
    atomclass->getBasicAtomDataClass();
  RxnDataAtomInformation *atominfo = atomdataclass->getAtomInformation();

    for(map<string, double>::const_iterator atm = species.comp.begin();
      atm != species.comp.end(); atm++) {
      unsigned int num = (unsigned int) floor(atm->second);
      for(unsigned int j=0;j<num;j++) {
	RxnDataMolFileAtom *atom = (RxnDataMolFileAtom *) 
	  atomdataclass->BaseDataObjectExample();
	char str[7];
	sprintf(str,"%s%d",atm->first.c_str(),j);
 	String name(str);
	name.EliminateBlanks();
	atom->NameTag = name;
	String atmS(atm->first.c_str());
	atom->AtomicNumber = atominfo->AtomicNumberFromSymbol(atmS);
	atom->Valence = atom->AtomicNumber * VAL_ATOMIC_NUMBER;
	simple->AddAtomToMolecule(atom);
	delete atom;
	RxnDataMoleculeAtom *a = (RxnDataMoleculeAtom *) simple->getNode(name);
	BaseDataInteger val;
	val.NameTag = STANDARD_VALENCE;
	val.SetValue(atom->Valence);
	a->AddObject(&val);
      }
    }
}
/*F ans = StoreChemkinNameInMolecule(molecule,instance)
**
**  DESCRIPTION
**    molecule: The molecule to store chemkin name
**    instance: THe instance
**    ans: true if successful
**
**  REMARKS
**
*/
bool RxnDataReadChemkin::StoreChemkinNameInMolecule(String& name,
						    RxnDataSimpleMolecule *molecule,
						    BaseDataInstance *instance)
{
  bool result = true;
  BaseDataString *chemkinname = new BaseDataString();
  chemkinname->NameTag = ChemkinName;
  chemkinname->setString(name);
  result = molecule->StoreProperty(chemkinname);
  instance->AddObject(chemkinname);
  delete chemkinname;
  return result;
}
 
/*F ans = StoreThermoInMolecule(chemkin,simple,instance)RxnDataGetGeneratedMechanism
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool RxnDataReadChemkin::StoreThermoInMolecule(RxnDataChemkinThermo *chemkin,
					       RxnDataSimpleMolecule *molecule,
					       BaseDataInstance *instance)
{
  if(molecule->RetrieveProperty(chemkin->NameTag) == NULL)
    {
      molecule->StoreProperty(chemkin);
      instance->AddObject(chemkin);
    }
  else 
    {
      //cerr << "StoreThermoInMolecule: Thermal Value already defined, not stored: '";
      //cerr << molecule->NameTag << "'" << endl;
    }
  return true;
}
/*F rxn = MakeReaction(rxnname,forward,reverse)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void RxnDataReadChemkin::BuildReactionSet(BaseDataSetOfInstances *instances,
						      DataSetOfInstancesClass *instancesclass,
						      vector<ckr::Reaction> reactions) {
  vector<ckr::Reaction>::iterator rxn;
  String f("Forward");
  String b("Reverse");
  for(rxn = reactions.begin();
      rxn != reactions.end();
      rxn++) {
    String *rxnname = determineReactionName(*rxn);
    BaseDataInstance *instance = MakeNewInstance(*rxnname,instances);
    RxnDataReaction *reaction = MakeReaction(*rxnname,instance);
    MakeRates((*rxn),instancesclass,reaction,instance);
    ReactionList->AddKeyWord(*rxnname);
    RxnDataMoleculeSet *Reactants = reaction->getReactants();
    RxnDataMoleculeSet *Products  = reaction->getProducts();
    DataKeySetClass *setclass = (DataKeySetClass *) instancesclass->GetObjectClass("KeySet");
    BaseDataKeySet *reactants = getReactionSpecies((*rxn).reactants,setclass,Reactants,true);
    BaseDataKeySet *products = getReactionSpecies((*rxn).products,setclass,Products,false);
    instance->AddAttribute(reactants);
    instance->AddAttribute(products);
    reaction->NameTag = *rxnname;
    Mechanism->addReaction(reaction);
    Mechanism->addToMechanism(reaction->NameTag,f,b,MechanismClass);
			      
    delete rxnname;
    }
}
/*F rxn = MakeReaction(rxnname,instance)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
RxnDataReaction *RxnDataReadChemkin::MakeReaction(String& rxnname,
						  BaseDataInstance *instance) {
  RxnDataReaction *newrxn = (RxnDataReaction *) ReactionClass->BaseDataObjectExample();
  String name("Reaction");
  newrxn->NameTag = name;
  instance->AddObject(newrxn);

  delete newrxn;
  newrxn = (RxnDataReaction *) instance->GetObject(name);
  RxnDataMoleculeSet *Reactants = new RxnDataMoleculeSet();
  RxnDataMoleculeSet *Products  = new RxnDataMoleculeSet();
   
  newrxn->setReactants(Reactants);
  newrxn->setProducts(Products);
  
  return newrxn;
}
/*F rxn = MakeRates(chemkinrxn)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void RxnDataReadChemkin::MakeRates(ckr::Reaction &chemkinrxn, 
				   DataSetOfObjectsClass *instanceclasses,
				   RxnDataReaction *rxn, 
				   BaseDataInstance *instance) {
  RxnReactionRatesClass *rateclass = (RxnReactionRatesClass *) ReactionRateClass;
  if(chemkinrxn.isFalloffRxn) {
    rateclass = (RxnReactionRatesClass *) ReactionRateHiLowClass;
    String m("(M)");
    BaseDataString str;
    str.NameTag = "ThirdBodyName";
    str.setString(m);
    rxn->AddObject(&str);
  }
  if(chemkinrxn.isThreeBodyRxn) {
    rateclass = (RxnReactionRatesClass *) ThirdBodyClass;
  }
  RxnDataReactionRates *forward;
  RxnDataReactionRates *reverse;
  if(chemkinrxn.isFalloffRxn) {
    forward = formReactionRate(chemkinrxn.kf_aux,rateclass,true);
    reverse = formReactionRate(chemkinrxn.krev,rateclass,false);
    RxnDataReactionRateHiLow *rhilow = (RxnDataReactionRateHiLow *) forward;
    RxnDataReactionRates *high = 
      formReactionRate(chemkinrxn.kf,ReactionRateClass,true);
    rhilow->setHiRate(high);
    FillInThirdBodyCoefficients(forward,reverse,chemkinrxn.e3b);
    FillInFallOffCoefficients(forward,chemkinrxn);
  } else if(chemkinrxn.isThreeBodyRxn) {
    forward = formReactionRate(chemkinrxn.kf,rateclass,true);
    reverse =  formReactionRate(chemkinrxn.krev,rateclass,false);

    FillInThirdBodyCoefficients(forward,reverse,chemkinrxn.e3b);
  } else {
    forward = formReactionRate(chemkinrxn.kf,rateclass,true);
    reverse = formReactionRate(chemkinrxn.krev,rateclass,false);
  }
  if(chemkinrxn.isChemActRxn)
    cout << "chemical activation reaction" << endl;
  
  rxn->AddObject(forward);
  rxn->AddObject(reverse);
  instance->AddAttribute(forward);
  instance->AddAttribute(reverse);
  
  AddReactionSummaryToMechanism(rxn->NameTag,instance,forward,reverse);
}
/*F FillInThirdBodyCoefficients(forward,reverse,third)
**
**  DESCRIPTION
**    forward,reverse: The forward and reverse constants
**    third: the set of collision coefficients
**  REMARKS
**
*/
void RxnDataReadChemkin::FillInThirdBodyCoefficients(RxnDataReactionRates *forward,
						     RxnDataReactionRates *reverse,
						     map<string, double> third) {  
  BaseDataKeyWords *species = new BaseDataKeyWords();
  species->NameTag = REACTION_THIRDBODY_NAME;
  map<string, double>::const_iterator b = third.begin(), 
    e = third.end();
  for (; b != e; ++b) {
    BaseDataReal *coef = new BaseDataReal();
    String name((b->first).c_str());
    species->AddKeyWord(name);
    coef->NameTag = name;
    coef->SetValue(b->second);
    forward->AddObject(coef);
    reverse->AddObject(coef);
    delete coef;
  }
  //forward->AddObject(species);
  reverse->AddObject(species);
  delete species;
}
/*F FillInFallOffCoefficients(rate,chemkinrxn)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void RxnDataReadChemkin::FillInFallOffCoefficients(RxnDataReactionRates *r,
						   ckr::Reaction &chemkinrxn) {
  RxnDataReactionRateHiLow *rate = (RxnDataReactionRateHiLow *) r;
  ckr::vector_fp::iterator bf=chemkinrxn.falloffParameters.begin(),
    ef = chemkinrxn.falloffParameters.end();
  int count = chemkinrxn.falloffParameters.size();
  VectorNumeric vec = VectorNumeric(count);
  int i = 0;
  for(;bf!=ef;bf++) {
    vec[i] = *bf;
    i++;
  }
  rate->setParameters(new BaseDataDoubleVector(vec));
}
/*F 
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void RxnDataReadChemkin::AddReactionSummaryToMechanism(String& rxnname,
				     BaseDataInstance *instance,
				     RxnDataReactionRates *forward,
				     RxnDataReactionRates *reverse) { 
  RxnDataReactionSummary *summary = (RxnDataReactionSummary *)
    MechanismClass->getSummaryClass()->BaseDataObjectExample();
  summary->NameTag = rxnname;
  summary->setReactionName(rxnname);
  summary->setForwardRate(forward->NameTag);
  summary->setReverseRate(reverse->NameTag);
  Mechanism->addReactionSummary(summary);
  summary->NameTag = REACTION_SUMMARY_NAME;
  instance->AddObject(summary);
  delete summary;
}
/*F ans = determineReactionName(species,rxnname)  . . . algorithm
**
**  DESCRIPTION
**    
**    
**  REMARKS
**
*/
String *RxnDataReadChemkin::determineReactionName(ckr::Reaction& rxn) {
  reactionCount++;
  String *name = new String(chemkinFileRoot->getString());
  name->AppendToEnd("_");
  String prefix = Int2String(reactionCount);
  name->AppendToEnd(prefix);
  name->AppendToEnd("_");
  fromReactionSet(rxn.reactants,name);
  name->AppendToEnd("=");
  fromReactionSet(rxn.products,name);
  
  return name;
}
/*F ans = putSpecies(species,rxnname)  . . . algorithm
**
**  DESCRIPTION
**    
**    
**  REMARKS
**
*/
BaseDataKeySet *RxnDataReadChemkin::getReactionSpecies(vector<ckr::RxnSpecies>& species, 
						    DataKeySetClass *setclass, 
						    RxnDataMoleculeSet *mols,
						    bool forward) {
  BaseDataKeySet *set = (BaseDataKeySet *) setclass->BaseDataObjectExample();
  if(forward)
    set->NameTag = "Reactants";
  else
    set->NameTag = "Products";

  vector<ckr::RxnSpecies>::iterator s;
  for(s = species.begin();s != species.end();s++) {
    int count = (int) s->number;
    for(int i=0;i<count;i++) {
      String name(s->name.c_str());
      set->AddKeyWord(name);
      mols->AddMolecule(name);
    }
  }
  return set;
}

/*F ans = putSpecies(species,rxnname)  . . . algorithm
**
**  DESCRIPTION
**    
**    
**  REMARKS
**
*/
void RxnDataReadChemkin::fromReactionSet(vector<ckr::RxnSpecies>& species,
					 String *name) {
  vector<ckr::RxnSpecies>::iterator s;
  bool notfirst = false;
  for(s = species.begin();s != species.end();s++) {
    if(notfirst) 
      name->AppendToEnd("+");
    int count = (int) s->number;
    for(int i=0;i<count;i++) {
      if(i > 0) 
	name->AppendToEnd("+");
      name->AppendToEnd(s->name.c_str());
    }
    notfirst = true;
  }
}
/*F rxnrate = formReactionRate(chemkinrate,forward)  . . . algorithm
**
**  DESCRIPTION
**    
**    
**  REMARKS
**
*/
RxnDataReactionRates *RxnDataReadChemkin::formReactionRate(ckr::RateCoeff &chemkinrate, 
							   RxnReactionRatesClass *rateclass,
							   bool forward) {
  RxnDataReactionRates *rate = (RxnDataReactionRates *) rateclass->BaseDataObjectExample();
  if(forward)
    rate->NameTag = "Forward";
  else
    rate->NameTag = "Reverse";

  BaseDataReal *AReal = new BaseDataReal();
  AReal->SetValue(chemkinrate.A);
  BaseDataReal *nReal = new BaseDataReal();
  nReal->SetValue(chemkinrate.n);
  BaseDataReal *EReal = new BaseDataReal();
  EReal->SetValue(chemkinrate.E);
  rate->setArrhenius(AReal,rateclass);
  rate->setActivationEnergy(EReal,rateclass);
  rate->setTemperatureCoefficient(nReal,rateclass);

  return rate;
}


/*S Utilities
 */


/*F InitializeChemkinConvertDecodeFunctions()  . . . . . . . . . . . . Reactions
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void InitialChemkinConvertDecodeFunctions() {
  EncodeDecodeRegisterClass(RxnReadChemkinClass,RxnDataReadChemkin,CHEMKINCONVERT_READCHEMKIN_NAME);
}
/*F AddChemkinConvertClasses(set) . . . . . . . . . . . .  EquilibriumConst
**
**  DESCRIPTION
**    set: The set of classes to add them to
**
**  REMARKS
**
*/
void AddChemkinConvertClasses(DataSetOfObjectsClass& set) {
  String readdescr("Algorithm: Read in Chemkin File");
  RxnReadChemkinClass readclass(CHEMKINCONVERT_READCHEMKIN_ID, CHEMKINCONVERT_READCHEMKIN_NAME, readdescr);
  set.AddObjectClass(readclass);
}
