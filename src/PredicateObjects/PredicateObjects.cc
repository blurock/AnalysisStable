/*  FILE     PredicateObjects.cc
**  PACKAGE  PredicateObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "PredicateObjects" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
**  Version 1.1
*/
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "PredicateObjects.hh"

/*S Utilities
 */
/*F AddPredicateClasses(set)  . . . . . . . . .  add to DataSetOfObjectsClass
**
**  DESCRIPTION
**    set: The set of classes of objects to add the numeric classes to
**
**  REMARKS
**
*/
void AddPredicateClasses(DataSetOfObjectsClass& set)
{
  DataPredicateClass cls;
  
  String preddescr("The Parameter Predication");
  String descrdescr("Predicate Description");
  String ldescrdescr("Logic Description");
  String ldescrsdescr("Set of Logic Descriptions");
  String conjdescr("Predicate Conjunction");
  String disjdescr("Predicate Disjunction");
  String partdescr("Parition");
  String tabledescr("Partition Table");
  String lcompdescr("The logical Description Operation");
  
  DataPredicateClass predclass(PREDICATE_BASE_ID,PREDICATE_BASE_NAME,preddescr);
  DataDescriptionClass descrclass(PREDICATE_DESCRIPTION_ID,PREDICATE_DESCRIPTION_NAME,descrdescr);
  DataLogicDescriptionClass ldescrclass(PREDICATE_LOGICDESCR_ID,PREDICATE_LOGICDESCR_NAME,ldescrdescr);
  DataSetOfLogicDescriptionsClass ldescrsclass(PREDICATE_LOGICDESCRSET_ID,PREDICATE_LOGICDESCRSET_NAME,ldescrsdescr);
  DataConjunctionClass conjclass(PREDICATE_CONJUNCTION_ID,PREDICATE_CONJUNCTION_NAME,conjdescr);
  DataDisjunctionClass disjclass(PREDICATE_DISJUNCTION_ID,PREDICATE_DISJUNCTION_NAME,disjdescr);
  DataPartitionClass partclass(PREDICATE_PARTITION_ID,PREDICATE_PARTITION_NAME,partdescr);
  DataPartitionTableClass tableclass(PREDICATE_PARTITIONTABLE_ID,PREDICATE_PARTITIONTABLE_NAME,tabledescr);
  DataLogicalDescriptionCompareClass lcompclass(PREDICATE_LOGCOMP_ID,PREDICATE_LOGCOMP_NAME,lcompdescr);
  
  set.AddObjectClass(predclass);
  set.AddObjectClass(descrclass);
  set.AddObjectClass(ldescrclass);
  set.AddObjectClass(ldescrsclass);
  set.AddObjectClass(conjclass);
  set.AddObjectClass(disjclass);
  set.AddObjectClass(partclass);
  set.AddObjectClass(tableclass);
  set.AddObjectClass(lcompclass);
}
 
/*C CheckPredicateList
**
**  DESCRIPTION
**     The provides an operator()(name) which
**     looks up the predicate and checks for validity
**
**     The member 'Success' is true if after looping through all the 
**     names, all the predicates where valid
**
**     The members are:
**     - setOfObjects: The pointer to the list where the predicates are to be found
**     - classSet: The class information associated with the set
**     - Success: true if all the names tested are valid
**     - notFound: The list of names which were not found
**     - wrongType: The list of names which were not of the type predicate
**     - className: The root class name of 'Predicate'
**
**
**  REMARKS
**
*/
class CheckPredicateList
{
  BaseDataSetOfObjects *setOfObjects;
  DataSetOfObjectsClass *classSet;
  bool printError;
  
public:
  bool Success;
  ObjectList<String> notFound;
  ObjectList<String> wrongType;
  String className;
  
  CheckPredicateList(BaseDataSetOfObjects *set,
                     DataSetOfObjectsClass *classset,
                     bool printerror)
    : setOfObjects(set),
      classSet(classset),
      printError(printerror),
      Success(true),
      className(PREDICATE_BASE_NAME)
    {
    }

  void operator()(const String& name)
    {
      if(setOfObjects->IsInList(name))
        {
          BaseDataObject *obj = setOfObjects->GetObject(name);
          if(!classSet->IsOfClass(*obj,className))
            {
              wrongType.AddObject(name);
              if(printError)
                {
                  cerr << "Predicate:" << name << " not of type: " << className << endl;
                }
              Success = false;
            }
        }
      else
        {
          notFound.AddObject(name);
          if(printError)
            {
              cerr << "Predicate: " << name << " not found";
            }
          
          Success = false;
        }
    }
  
};
/*F ans = CheckPredicateListInSet(predlist,set,classset,printerror)
**
**  DESCRIPTION
**    predlist: The predicate list
**    set: The set of objects where the predicates are to be found
**    classset: The class of the set of objects
**    printerror: true if the error message is to be printed
**    ans: true if all are valid
**
**  REMARKS
**
*/
bool CheckPredicateListInSet(BaseDataKeyWords& predlist,
                             BaseDataSetOfObjects *set,
                             DataSetOfObjectsClass *classset,
                             const bool printerror)
{
  CheckPredicateList check(set,classset,printerror);
  ObjectList<String> names = predlist.GetKeyWords();
  for_each(names.begin(),names.end(),check);
  
  return check.Success;
}
 
/*C CheckPartitionList
**
**  DESCRIPTION
**     The provides an operator()(name) which
**     looks up the partitions and checks for their validity
**
**     The member 'Success' is true if after looping through all the 
**     names, all the partitions (and their corresponding predicates) where valid
**
**     The members are:
**     - setOfObjects: The pointer to the list where the predicates are to be found
**     - classSet: The class information associated with the set
**     - Success: true if all the names tested are valid
**     - keyName: The root class name of 'KeyWords'
**
**
**  REMARKS
**
*/
class CheckPartitionList
{
  BaseDataSetOfObjects *setOfObjects;
  DataSetOfObjectsClass *classSet;
  CheckPredicateList checkList;
  bool printError;
  
public:
  bool Success;
  String keyName;
  
  CheckPartitionList(BaseDataSetOfObjects *set,
                     DataSetOfObjectsClass *classset,
                     bool printerror)
    : setOfObjects(set),
      classSet(classset),
      checkList(set,classset,printerror),
      printError(printerror),
      Success(true),
      keyName("KeyWords")
    {
    }

  void operator()(const String& name)
    {
      if(setOfObjects->IsInList(name))
        {
          BaseDataObject *obj = setOfObjects->GetObject(name);
          if(classSet->IsOfClass(*obj,keyName))
            {
              BaseDataKeyWords *keys = (BaseDataKeyWords *) obj;
              ObjectList<String> names = keys->GetKeyWords();
              for_each(names.begin(),names.end(),checkList);
              Success = checkList.Success && Success;
            }
          else
            {
              if(printError)
                {
                  cerr << "Partition Predicate List:" << name << " not of type: " << keyName << endl;
                }
              Success = false;
            }
        }
      else
        {
          if(printError)
            {
              cerr << "Predicate: " << name << " not found";
            }
          
          Success = false;
        }
    }
};
/*F ans = CheckPartitionListInSet(partlist,set,classset,printerror)
**
**  DESCRIPTION
**    partlist: The partition list
**    classset: The class of the set of objects
**    printerror: true if the error message is to be printed
**    ans: true if all are valid
**    
**  REMARKS
**
*/
bool CheckPartitionListInSet(BaseDataKeyWords& partlist,
                             BaseDataSetOfObjects *set,
                             DataSetOfObjectsClass *classset,
                             const bool printerror)
{
  ObjectList<String> names = partlist.GetKeyWords();
  CheckPartitionList check(set,classset,printerror);
  for_each(names.begin(),names.end(),check);
  return check.Success;
}
/*F ans = WriteAsASCIIOutFullSetOfObjects(out,objects,oclasses)
**
**  DESCRIPTION
**    out: The output stream
**    objects: The set of objects to write out
**    oclasses: The set of object classes
**    ans: True if successful
**
**    This routine is meant to be a special case of the WriteAsASCII
**    of the SetOfObjects class.  The normal one uses the current
**    state of the name-class pairs to write out the objects.  This
**    routine generates a full set of name class pairs.
**
**  REMARKS
**
*/
bool WriteAsASCIIOutFullSetOfObjects(ostream& out,
				     BaseDataSetOfObjects& objects,
				     DataSetOfObjectsClass& oclasses)
{
  bool result = true;
  DataSetOfObjectsClass *classes = oclasses.PointerToAllowedClasses();
  SetUpClassNamePairs(&objects,classes);
  classes->getNameClassPairs().WriteAsASCII(out);

  result = result && objects.BaseDataSetOfObjects::WriteAsASCII(out,(DataObjectClass *) classes);
  return result;
}
/*F ans = WriteAsLatexOutFullSetOfObjects(out,objects,oclasses)
**
**  DESCRIPTION
**    out: The output stream
**    objects: The set of objects to write out
**    oclasses: The set of object classes
**    ans: True if successful
**
**    This routine is meant to be a special case of the WriteAsLatex
**    of the SetOfObjects class.  The normal one uses the current
**    state of the name-class pairs to write out the objects.  This
**    routine generates a full set of name class pairs.
**
**  REMARKS
**
*/
bool WriteAsLatexOutFullSetOfObjects(ostream& out,
				     BaseDataSetOfObjects& objects,
				     DataSetOfObjectsClass& oclasses)
{
  bool result = true;
  DataSetOfObjectsClass *classes = oclasses.PointerToAllowedClasses();
  SetUpClassNamePairs(&objects,classes);
  classes->getNameClassPairs().WriteAsASCII(out);
  result = result && objects.WriteAsLatex(out,(DataObjectClass *) classes);
  return result;
}
/*S BaseDataPredicate
 */ 
/*F BaseDataPredicate() . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataPredicate::BaseDataPredicate()
  : Operation(NULL)
{
  Identification = PREDICATE_BASE_ID;
  NameTag = PREDICATE_BASE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataPredicate(data) . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataPredicate::BaseDataPredicate(const BaseDataPredicate& data)
  : BaseDataOperation(data),
    Logic(data.Logic),
    Parameter(data.Parameter)
{
  Operation = (BaseDataOperation *) PointerClone((BaseDataOperation *) data.Operation);
}
 
/*F BaseDataPredicate(name,logic,var,op)  . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    name: Name of the tag
**    logic: The logic of the predicate output
**    var: The variable parameter (from instances)
**    op: The operation of the predicate
**
**  REMARKS
**
*/
BaseDataPredicate::BaseDataPredicate(const String& name,
                                     const String& logic,       
                                     const String& var,
                                     BaseDataOperation *op)
  : BaseDataOperation(),
    Logic(logic),
    Parameter(var)
{
  Identification = PREDICATE_BASE_ID;
  SetType(Identification);

  String pred = PREDICATE_BASE_NAME;
  String obj("Object.");
  obj.AppendToEnd(pred);
  EncodeDecodeClass = obj;

  NameTag = name;
  Operation = (BaseDataOperation *) PointerClone(op);

}
 
/*F BaseDataPredicate~()  . . . . . . . . . . . . . . . . . . . .  destructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataPredicate::~BaseDataPredicate()
{
  if(Operation != NULL)
    delete Operation;
  Operation = NULL;
}
/*F prednew = operator=(pred) . . . . . . . . . . . . . . . BaseDataPredicate
**
**  DESCRIPTION
**    pred: The predicate to copy from
** 
**  REMARKS
**
*/
BaseDataPredicate& BaseDataPredicate::operator=(BaseDataPredicate& pred)
{
  if(&pred == this) return *this;
  CopyClone(&pred);
  return *this;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . Read in BaseDataPredicate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataPredicate::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . Read in BaseDataPredicate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**    The form of the input is:
**    - The tag 'Predicate:'
**    - The Parameter name
**    - The logic class name
**    - The predicate operation
**
**  REMARKS
**
*/
bool BaseDataPredicate::Read(istream& in, DataObjectClass* objc, const String& name)
{
  BaseDataOperation::Read(in,objc,name);
  DataPredicateClass *predclass = (DataPredicateClass *) objc;
  bool result = true;
  
  if(objc->getDebugLevel() > 0)
    {
      cout << "Read In Predicate with Parameter\n";
    }
  
  StreamObjectInput strinp(in,' ');
  String tag = strinp.ReadNext();
  if(tag == "Predicate:")
    {
      if(objc->getDebugLevel() > 0)
        {
          cout << "Read in Parameter and Logic\n";
        }
      
      Parameter = strinp.ReadNext();
      Logic = strinp.ReadNext();
      DataOperationClass * opclass = predclass->OperationClass();
      if(objc->getDebugLevel() > 0)
	{
	  cout << "\nOperationClass\n";   
	  opclass->print(cout);
	  cout << "\n==================\n";
	}
      Operation = (BaseDataOperation *) opclass->BaseDataObjectExample();
      
      if(Operation != NULL)
	{
	  result = result && Operation->Read(in,opclass,name);
	}
      else
	{
	  cerr << "Operation not Found: " << opclass->NameTag << endl;
	  result = false;
	}
    }
  else
    {
      cerr << "\n'Predicate:' expected '";
      cerr << tag;
      cerr << "' found.";
      
      result = false;
    }
  
  return result;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . . . . BaseDataPredicate
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
bool BaseDataPredicate::WriteAsLine(ostream& out, DataObjectClass *)
{
  if(Operation != NULL)
    {
      out << "Predicate: " << Logic << " = ";
      out << Operation->NameTag << "(" << Parameter << ")" << endl;
    }
  else
    {
      out << "No Operation Defined" << endl;
    }
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . BaseDataPredicate
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
bool BaseDataPredicate::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  DataPredicateClass *predclass = (DataPredicateClass *) objc;
  DataOperationClass * opclass = predclass->OperationClass();
  bool result = BaseDataOperation::WriteAsASCII(out,objc);
  out << "Predicate: " << Parameter;
  out << " " << Logic << endl;
  if(Operation != NULL)
    {
      result = result && Operation->WriteAsASCII(out,opclass);
    }
  out << endl;
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . . BaseDataPredicate
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
bool BaseDataPredicate::WriteAsLatex(ostream& out, DataObjectClass *objc)
{
  DataPredicateClass *predclass = (DataPredicateClass *) objc;
  DataOperationClass * opclass = predclass->OperationClass();
  bool result = BaseDataOperation::WriteAsLatex(out,objc);
  out << endl << endl << "Predicate: " << Parameter;
  out << " " << Logic << "\\\\" << endl;
  if(Operation != NULL)
    {
      result = result && Operation->WriteAsLatex(out,opclass);
    }
  out << "\\\\" << endl;
  return result;
}

/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . BaseDataPredicate
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataPredicate::print(ostream& out) const
{
  BaseDataOperation::print(out);
  out << "\n         Predicate Parameter: ";
  out << Parameter;
  out << "     With Logic: ";
  out << Logic;
  out << "\n";
  out << "     Operation: -----------------------\n     ";
  if(Operation != 0)
    Operation->print(out);
  else
    out << "No Operation Specified\n";
  out << "\n     Operation: -----------------------\n";
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . BaseDataPredicate
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataPredicate::Clone()
{
  BaseDataPredicate *obj = new BaseDataPredicate;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . BaseDataPredicate
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataPredicate::CopyClone(Identify * obj)
{
  BaseDataPredicate *objfull = (BaseDataPredicate *) obj;
  
  BaseDataOperation::CopyClone(obj);
  Logic = objfull->Logic;
  Parameter = objfull->Parameter;  
  Operation = (BaseDataOperation *) PointerClone(objfull->Operation);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . BaseDataPredicate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPredicate::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  result = result && Logic.EncodeThis(buffer);
  result = result && Encode(buffer,Parameter);
  if(Operation != 0)
    {
      result = result && Encode(buffer,Operation->EncodeDecodeClass);
      result = result && Operation->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);
  
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . BaseDataPredicate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPredicate::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  result = result && Logic.DecodeThis(buffer);
  result = result && Decode(buffer,Parameter);
  String name;
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    DecodeFromName(result,buffer,name,(Identify *&) Operation);

  return result;
}
/*F value = operator()(instance,instclass)  .  predicate value given instance
**
**  DESCRIPTION
**
**  REMARKS
**
*/
BaseDataObject *BaseDataPredicate::operator()(BaseDataObject* obj,
                                              DataObjectClass *objclass)
{
  BaseDataContinuous *logobj = new BaseDataContinuous();
  logobj->SetValue(1.0);
  DataContinuousClass *logclass = new DataContinuousClass();
  Operation->operator()(logobj,obj,logclass,objclass);
  delete logclass;
  return logobj;
}
/*F value = operator()(instance,instclass)  .  predicate value given instance
**
**  DESCRIPTION
**    instance: The particular instance
**    instclass: The instance classes
**    value: The value of the predicate
**
**    This routine sets up the call to the logic evaluateLogicValue:
**    - Parameter object from name in predicate
**    - Class types of object and predicate
**    - evaluate
**
**    From the operator, the BaseDataObject is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataPredicate::operator()(BaseDataObject *log,
                                              BaseDataObject* obj,
                                              DataObjectClass *logclass,
                                              DataObjectClass *objclass)
{
  BaseDataLogical *value = (BaseDataLogical *) log;
  BaseDataSetOfObjects* instance = (BaseDataSetOfObjects *) obj;
  DataSetOfObjectsClass *instclass = (DataSetOfObjectsClass *) objclass;
  
  if(instance->IsInList(Parameter))
    {
      BaseDataObject *object = instance->GetObject(Parameter);
      unsigned int objtype = object->GetType();
      DataSetOfObjectsClass *oclasses = instclass->PointerToAllowedClasses();
      
      DataObjectClass *oclass = (DataObjectClass *) oclasses->GetObjectClass(objtype);
      value->SetValue(1.0);
      Operation->operator()(value,object,logclass,oclass);
      value->NameTag = NameTag;
      String l(".Logic");
      value->NameTag.AppendToEnd(l);
    }
  else
    {
      cerr << "Parameter: '" << Parameter << "' for Predicate: '" << NameTag << "' not found\n";
      cerr << "in Instance: '" << instance->NameTag << "'" << endl;
      
      cerr << "           Returning Logical value of zero\n";

      ObjectList<String> pnames = instance->ListOfObjectNames();
      cerr << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
      instance->print(cerr);
      cerr << endl;
      cerr << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
      value->SetValue(0.0);
    }
  
  return value;
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataPredicate::setParameters(const String& name,
				      const String& var,
				      const String& logic,
				      BaseDataOperation *op)
{
  NameTag = name;
  Parameter = var;
  Logic = logic;
  Operation = (BaseDataOperation *) PointerClone(op);
}


/*S DataPredicateClass
 */
/*F DataPredicateClass()  . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataPredicateClass::DataPredicateClass()
  : OpClass(0)
{
  Identification = PREDICATE_BASE_ID;
  NameTag = PREDICATE_BASE_NAME;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataPredicateClass(data)  . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataPredicateClass::DataPredicateClass(const DataPredicateClass& data)
  : DataOperationClass(data)
{
  OpClass = (DataOperationClass *) PointerClone((DataOperationClass *) data.OpClass);
} 
 
/*F DataPredicateClass(id,name,descr) . . . . . . . . . . . . . . constructor
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
DataPredicateClass::DataPredicateClass(const int id, 
                                       const String& name,
                                       const String& descr)
  : DataOperationClass(id,name,descr),
    OpClass(0)
{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = PREDICATE_BASE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . .  DataPredicateClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataPredicateClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  out << "\n------Begin: Operation Class of Predicate -----\n";
  if(OpClass != 0)
    OpClass->print(out);
  out << "\n------End: Operation class of Predicate -----\n";
  
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . .  DataPredicateClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataPredicateClass, there is no further information.
**
**  REMARKS
**
*/
bool DataPredicateClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  if(getDebugLevel() > 0)
    {
      cout << "Read in PredicateClass\n";
    }
  
  bool result = DataOperationClass::Read(in,set);
  StreamObjectInput strinp(in,' ');
  String logic = strinp.ReadNext();
  
  OpClass = (DataOperationClass *) set.CloneClassFromName(logic);
  
  if(getDebugLevel() > 0)
    {
      cout << "----------------------------------------\n";
      cout << "Logic Class: ";
      cout << logic;
      cout << "\n";
      OpClass->print(cout);
      
      cout << "----------------------------------------\n";
    }
  
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . .  DataPredicateClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataPredicateClass::CopyClone(Identify *  objc)
{
  DataPredicateClass *objcfull = (DataPredicateClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . .  DataPredicateClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataPredicateClass::Clone()
{
  DataPredicateClass* id = new DataPredicateClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . .  DataPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPredicateClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  if(OpClass != 0)
    {
      result = result && Encode(buffer,OpClass->EncodeDecodeClass);
      result = result && OpClass->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);
  
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . .  DataPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPredicateClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
  String name;
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    DecodeFromName(result,buffer,name,(Identify *&) OpClass);

  return result;
}
  
/*F opclass = OperationClass()  . . . . . . . . .  pointer to operation class
**
**  DESCRIPTION
**    opclass: pointer to the operation class
**
**  REMARKS
**
*/
DataOperationClass * DataPredicateClass::OperationClass()
{
  return (DataOperationClass *) OpClass;
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
BaseDataObject * DataPredicateClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataPredicate();
}
/*F ans = WriteAsLine(out)  . . . . . . . . . . . . . . .  DataPredicateClass
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
bool DataPredicateClass::WriteAsLine(ostream& out)
{
    return DataOperationClass::WriteAsLine(out);
}
/*F ans = WriteAsASCII(out) . . . . . . . . . . . . . . .  DataPredicateClass
**
**  DESCRIPTION
**    out: The output stream
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool DataPredicateClass::WriteAsASCII(ostream& out)
{
    bool result = DataOperationClass::WriteAsASCII(out);
    if(OpClass != NULL)
	{
	    out << OpClass->NameTag << endl;
	}
    else
	{
	    out << "NoOperationClass";
	}
    return result;
}
/*F ans = WriteAsLatex(out) . . . . . . . . . . . . . . .  DataPredicateClass
**
**  DESCRIPTION
**    out: The output stream
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool DataPredicateClass::WriteAsLatex(ostream& out)
{
    return DataOperationClass::WriteAsLatex(out);
}

/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . .  DataPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataPredicateClass*& obj)
{
  obj = new DataPredicateClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . BaseDataPredicate
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataPredicate*& obj)
{
  obj = new BaseDataPredicate;
  return obj->DecodeThis(buffer);
}
 
/*F setOpClass(op)  . . . . . . . . . . . . . . . . . . .  DataPredicateClass
**
**  DESCRIPTION
**    op: The operation class
**
**  REMARKS
**
*/
void DataPredicateClass::setOpClass(DataOperationClass *op)
{
  if(OpClass != NULL)
    delete OpClass;
  OpClass = (DataOperationClass *) op->Clone();
}

/*S BaseDataDescription
 */ 
/*F BaseDataDescription() . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDescription::BaseDataDescription()
{
  Identification = PREDICATE_DESCRIPTION_ID;
  NameTag = PREDICATE_DESCRIPTION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataDescription(data) . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDescription::BaseDataDescription(const BaseDataDescription& data)
  : BaseDataSetOfObjects(data)
{
}
/*F BaseDataDescription(instances,keys) . . . . . .  description from names
**
**  DESCRIPTION
**    instances: The list of instances and attributes
**    keys: The list of names
**
**  REMARKS
**
*/
BaseDataDescription::BaseDataDescription(BaseDataSetOfObjects *objects, BaseDataKeyWords& keys)
{
  Identification = PREDICATE_DESCRIPTION_ID;
  NameTag = PREDICATE_DESCRIPTION_NAME;
  SetType(Identification);
  String tname("Object.");
  tname.AppendToEnd(NameTag);
  EncodeDecodeClass = tname;

  //ChangeTitle("-------------- Set Of Predicate Descriptions ----------------\n");
  //ChangeDelimitor("\n");
  
  ObjectList<String> names = keys.GetKeyWords();
  ObjectList<String>::iterator name;
  for(name = names.begin();
      name != names.end();
      name++)
    {
      BaseDataPredicate *predicate = (BaseDataPredicate *) objects->GetObject(*name);
      AddPredicate(predicate);
    }
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . Read in BaseDataDescription
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataDescription::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . Read in BaseDataDescription
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataDescription::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = true;
  DataSetOfObjectsClass *oclasses = (DataSetOfObjectsClass *) objc;
  StreamObjectInput str(in,' ');

  String key = str.ReadNext();
  if(key == "Description:")
    {
      ObjectNameClassPairs namepairs;
      result = result && namepairs.Read(in);
      //if(objc->getDebugLevel() > 0)
      if(true)
	{
	  cout << "Read in Descriptions\n";
	  namepairs.print(cout);
	  cout << endl;
	}
      oclasses->ReplaceObjectTypes(namepairs);
      result = result && BaseDataSetOfObjects::Read(in,objc,name);
    }
  else
    {
      cerr << "Expected 'Description:', got '" << key << "'" << endl;
      result = false;
    }

  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . BaseDataDescription
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataDescription::print(ostream& out) const
{
  out << "\nBegin: --------- Set of Descriptions--------- \n";
  BaseDataSetOfObjects::print(out);
  out << "\nEnd:   --------- Set of Descriptions--------- \n";
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . BaseDataDescription
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataDescription::Clone()
{
  BaseDataDescription *obj = new BaseDataDescription;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . BaseDataDescription
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataDescription::CopyClone(Identify * obj)
{
  BaseDataDescription *objfull = (BaseDataDescription *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . BaseDataDescription
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDescription::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . BaseDataDescription
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDescription::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::DecodeThis(buffer);
  return result;
}
 
/*F ans = AddPredicate(pred)  . . . . . . . . . . . . . . . . Add a predicate
**
**  DESCRIPTION
**    pred: The predicate
**    ans: true if successful
**
**  REMARKS
**
*/
bool BaseDataDescription::AddPredicate(BaseDataPredicate *pred)
{
  return AddObject((BaseDataObject *) pred);
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . . . BaseDataDescription
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
bool BaseDataDescription::WriteAsLine(ostream& out, DataObjectClass *objc)
{
    return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . BaseDataDescription
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
bool BaseDataDescription::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  DataSetOfObjectsClass *oclasses = (DataSetOfObjectsClass *) objc;
  out << "Description:"<< endl;
  return WriteAsASCIIOutFullSetOfObjects(out,*this,*oclasses);
  
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . BaseDataDescription
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
bool BaseDataDescription::WriteAsLatex(ostream& out, DataObjectClass *objc)
{
  DataSetOfObjectsClass *oclasses = (DataSetOfObjectsClass *) objc;
  return WriteAsLatexOutFullSetOfObjects(out,*this,*oclasses);
}
/*F ldescr = ComputeLogicDescription(ldclass,logclass,descrclass,instance,instclass) . . . . logic results
**
**  DESCRIPTION
**    ldclass: The logical description class
**    logclass: The logic class
**    descrclass: The corresponding description class
**    instance: The instance parameters
**    instclass: The paramater classes
**    
**    In this context, the LogicDescription represents the values of the predicate
**    for a specific instance (SetOfObjects). The name of the logical values
**    in the name of the set of objects.
**
**  REMARKS
**
*/
BaseDataLogicDescription *BaseDataDescription::ComputeLogicDescription(DataDescriptionClass *descrclass,
								       BaseDataSetOfObjects * instance,
								       DataSetOfObjectsClass * instclass)
{
  DataLogicDescriptionClass *ldclass = descrclass->getLogicalDescriptionClass();
  DataLogicalClass *logclass = ldclass->getLogicClass();

  BaseDataLogicDescription *logdescr = (BaseDataLogicDescription *) ldclass->BaseDataObjectExample();
  logdescr->NameTag = instance->NameTag;
  BaseDataLogical *logic = (BaseDataLogical *) logclass->BaseDataObjectExample();
  logdescr->AddLogicInstanceSet(logic,logclass,this,descrclass,instance,instclass);
  delete logic;
  return logdescr;
}

/*S DataDescriptionClass
 */
/*F DataDescriptionClass()  . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDescriptionClass::DataDescriptionClass()
  : LogicalDescriptionClass(NULL)
{
  Identification = PREDICATE_DESCRIPTION_ID;
  NameTag = PREDICATE_DESCRIPTION_NAME;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataDescriptionClass(data)  . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataDescriptionClass::DataDescriptionClass(const DataDescriptionClass& data)
  : DataSetOfObjectsClass(data)
{
  LogicalDescriptionClass = (DataLogicDescriptionClass *) PointerClone(data.LogicalDescriptionClass);
} 
/*F DataDescriptionClass(id,name,descr) . . . . . . . . . . . . . constructor
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
DataDescriptionClass::DataDescriptionClass(const int id, 
                                           const String& name,
                                           const String& descr)
  : DataSetOfObjectsClass(id,name,descr),
    LogicalDescriptionClass(NULL)
{
  SubClass = COREOBJECTS_SET_NAME;
  EncodeDecodeClass = PREDICATE_DESCRIPTION_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . .  DataDescriptionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataDescriptionClass::print(ostream& out) const
{
  out << "Begin:  ----------------- Set of descriptions class --------------------\n";
  //DataSetOfObjectsClass::print(out);
  out << "Would have print out the set of classes\n";
  out << "End  :  ----------------- Set of descriptions class --------------------\n";
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . .  DataDescriptionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataDescriptionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataDescriptionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = true;
  result = result && PointerClassRead(in,(DataObjectClass *&) LogicalDescriptionClass,
				      PREDICATE_LOGICDESCR_NAME,
				      set,"Logical Description not found");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . .  DataDescriptionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataDescriptionClass::CopyClone(Identify *  objc)
{
  DataDescriptionClass *objcfull = (DataDescriptionClass*) objc;      
  *this = *objcfull;
  LogicalDescriptionClass = (DataLogicDescriptionClass *) PointerClone(objcfull->LogicalDescriptionClass);
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . .  DataDescriptionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataDescriptionClass::Clone()
{
  DataDescriptionClass* id = new DataDescriptionClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . .  DataDescriptionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDescriptionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,(BaseDataObject *&) LogicalDescriptionClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . .  DataDescriptionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDescriptionClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) LogicalDescriptionClass);
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
BaseDataObject * DataDescriptionClass::BaseDataObjectExample()
{ 
  BaseDataDescription *obj = new BaseDataDescription();
  obj->SetType(Identification);
  return (BaseDataObject *) obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . .  DataDescriptionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataDescriptionClass*& obj)
{
  obj = new DataDescriptionClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . BaseDataDescription
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataDescription*& obj)
{
  obj = new BaseDataDescription;
  return obj->DecodeThis(buffer);
}
/*F classes = PointerToAllowedClasses()
**
**  DESCRIPTION
**  This returns the standard set of allowed classes.
**
**  REMARKS
**
*/
DataSetOfObjectsClass *DataDescriptionClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}
 
/*F ldclass = getLogicalDescriptionClass()
**
**  DESCRIPTION
**    ldclass: The logical description class
**
**  REMARKS
**
*/
DataLogicDescriptionClass *DataDescriptionClass::getLogicalDescriptionClass()
{
  return LogicalDescriptionClass;
}
/*S BaseDataLogicDescription
 */ 
/*F BaseDataLogicDescription()  . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataLogicDescription::BaseDataLogicDescription()
{
  Identification = PREDICATE_LOGICDESCR_ID;
  NameTag = PREDICATE_LOGICDESCR_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataLogicDescription(data)  . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataLogicDescription::BaseDataLogicDescription(const BaseDataLogicDescription& data)
  : BaseDataSetOfObjects(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . .  Read in BaseDataLogicDescription
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataLogicDescription::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . .  Read in BaseDataLogicDescription
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataLogicDescription::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = true;
  String key("LogicDescription:");
  CheckReadKeyWord(in,key);
  ObjectNameClassPairs namepairs;
  DataSetOfObjectsClass *setclass = (DataSetOfObjectsClass *) objc;
  result = result && namepairs.Read(in);
  setclass->ReplaceObjectTypes(namepairs);
  result = result && BaseDataSetOfObjects::Read(in,objc,name);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . .  BaseDataLogicDescription
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataLogicDescription::print(ostream& out) const
{
  out << "Begin:  ----------------- Set of logical descriptions --------------------\n";
  BaseDataSetOfObjects::print(out);
  out << "End  :  ----------------- Set of logical descriptions --------------------\n";
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . .  BaseDataLogicDescription
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataLogicDescription::Clone()
{
  BaseDataLogicDescription *obj = new BaseDataLogicDescription;
  obj->CopyClone(this);
  return obj;
} 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . .  BaseDataLogicDescription
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataLogicDescription::CopyClone(Identify * obj)
{
  BaseDataLogicDescription *objfull = (BaseDataLogicDescription *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . .  BaseDataLogicDescription
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLogicDescription::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . .  BaseDataLogicDescription
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLogicDescription::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::DecodeThis(buffer);

  return result;
} 
/*F values = LogicValues()  . . . . . . . . . . . set continuous logic values
**
**  DESCRIPTION
**    values: The list of double logic values
**
**  REMARKS
**
*/
ObjectList<double>& BaseDataLogicDescription::LogicValues()
{
  ObjectList<double> *list = new ObjectList<double>;
  BaseDataLogical *logic;
  
  ObjectList<String> names = ListOfObjectNames();
  ObjectList<String>::iterator name;
  for(name = names.begin();name != names.end();name++)
    {
      logic = (BaseDataLogical *) GetObject(*name);
      double ans = logic->GetValue();
      list->AddObject(ans);
    }
  return *list;
}
/*F ldescr = AddLogicInstanceSet(logic,logclass,descr,descrnames,instance,instclass) . . . . logic results
**
**  DESCRIPTION
**    logic: A dummy logic object
**    logclass: The logic class
**    descr: The corresponding description
**    descrnames: The set of description names to insert
**    instance: The instance parameters
**    instclass: The paramater classes
**    ldescr: logic description
**    
**    The use of 'logic' is to eliminate the need for creating and deleting a logical
**    object.  The operation of the predicate just modifies the logical value within 
**    the object.
**
**    In this context, the LogicDescription represents the values of the predicate
**    for a specific instance.  Hence, the description name and the instance name
**    must correspond
**
**  REMARKS
**
*/
bool BaseDataLogicDescription::AddLogicInstanceSet(BaseDataLogical *logic,
                                                   DataLogicalClass *logclass,
                                                   BaseDataSetOfInstances* instances,
                                                   DataSetOfInstancesClass*,
                                                   ObjectList<String>& descrnames,
                                                   BaseDataSetOfObjects * instance,
                                                   DataSetOfObjectsClass * instclass)
{
  bool result = true;
  if(instance->NameTag == NameTag)
    {
      ObjectList<String>::iterator name;
      for(name = descrnames.begin();
          name != descrnames.end() && result;
          name++)
        {
          BaseDataPredicate *obj = (BaseDataPredicate *) instances->GetObject(*name);
	  logic->SetValue(1.0);
          obj->operator()(logic,instance,logclass,instclass);
          logic->NameTag = *name;
          result = result && AddObject(logic);

          if(!result)
            cerr << "Didn't Add Logic Value to logical description\n";
        }
    }
  else 
    {
      cerr << "LogicDescription name '" << NameTag;
      cerr << "' does not match instance name '" << instance->NameTag << endl;
      result = false;
    }
  return result;
}
/*F ldescr = AddLogicInstanceSet(logic,logclass,descr,descrnames,instance,instclass) . . . . logic results
**
**  DESCRIPTION
**    logic: A dummy logic object
**    logclass: The logic class
**    descr: The corresponding description
**    descrnames: The set of description names to insert
**    instance: The instance parameters
**    instclass: The paramater classes
**    ldescr: logic description
**    
**    The use of 'logic' is to eliminate the need for creating and deleting a logical
**    object.  The operation of the predicate just modifies the logical value within 
**    the object.
**
**    In this context, the LogicDescription represents the values of the predicate
**    for a specific instance.  Hence, the description name and the instance name
**    must correspond
**
**  REMARKS
**
*/
bool BaseDataLogicDescription::AddLogicInstanceSet(BaseDataLogical *logic,
                                                   DataLogicalClass *logclass,
                                                   BaseDataDescription *description,
                                                   DataDescriptionClass *descrclass,
                                                   BaseDataSetOfObjects * instance,
                                                   DataSetOfObjectsClass * instclass)
{
  bool result = true;
  ObjectList<String> descrnames = description->ListOfObjectNames();
  ObjectList<String>::iterator name;
  for(name = descrnames.begin();
      name != descrnames.end() && result;
      name++)
    {
      BaseDataPredicate *obj = (BaseDataPredicate *) description->GetObject(*name);
      logic->SetValue(1.0);
      obj->operator()(logic,instance,logclass,instclass);
      logic->NameTag = *name;
      result = result && AddObject(logic);
      if(!result)
	cerr << "Didn't Add Logic Value to logical description\n";
    }
  return result;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . .  BaseDataLogicDescription
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
bool BaseDataLogicDescription::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << "SetOfLogicalDescriptions: ";
  return BaseDataSetOfObjects::WriteAsLine(out,objc);
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . .  BaseDataLogicDescription
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
bool BaseDataLogicDescription::WriteAsASCII(ostream& out, DataObjectClass *objc)
{ 
  DataSetOfObjectsClass *oclasses = (DataSetOfObjectsClass *) objc;
  return WriteAsASCIIOutFullSetOfObjects(out,*this,*oclasses);
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . .  BaseDataLogicDescription
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
bool BaseDataLogicDescription::WriteAsLatex(ostream& out, DataObjectClass *objc)
{
  DataSetOfObjectsClass *oclasses = (DataSetOfObjectsClass *) objc;
  return WriteAsLatexOutFullSetOfObjects(out,*this,*oclasses);
}

/*S DataLogicDescriptionClass
 */
/*F DataLogicDescriptionClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataLogicDescriptionClass::DataLogicDescriptionClass()
  : LogicClass(NULL)
{
  Identification = PREDICATE_LOGICDESCR_ID;
  NameTag = PREDICATE_LOGICDESCR_NAME;
  SubClass = COREOBJECTS_SET_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataLogicDescriptionClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataLogicDescriptionClass::DataLogicDescriptionClass(const DataLogicDescriptionClass& data)
  : DataSetOfObjectsClass(data)
{
  LogicClass = (DataLogicalClass *) PointerClone(data.LogicClass);
} 
 
/*F DataLogicDescriptionClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataLogicDescriptionClass::DataLogicDescriptionClass(const int id, 
                                                     const String& name,
                                                     const String& descr)
  : DataSetOfObjectsClass(id,name,descr),
    LogicClass(NULL)
{
  SubClass = COREOBJECTS_SET_NAME;
  EncodeDecodeClass = PREDICATE_LOGICDESCR_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataLogicDescriptionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataLogicDescriptionClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  PointerPrint(out,"The Logic Class: ","No Logic Class Defined",LogicClass);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataLogicDescriptionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataLogicDescriptionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataLogicDescriptionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = true;
  result = result && PointerClassRead(in,(DataObjectClass *&) LogicClass,
				     LOGICAL_BASE_NAME,
				     set,"Logic Class for logical description");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataLogicDescriptionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataLogicDescriptionClass::CopyClone(Identify *  objc)
{
  DataLogicDescriptionClass *objcfull = (DataLogicDescriptionClass*) objc;
  *this = *objcfull;
  LogicClass = (DataLogicalClass *) PointerClone(objcfull->LogicClass);
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataLogicDescriptionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataLogicDescriptionClass::Clone()
{
  DataLogicDescriptionClass* id = new DataLogicDescriptionClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataLogicDescriptionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLogicDescriptionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,LogicClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataLogicDescriptionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLogicDescriptionClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) LogicClass);

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
BaseDataObject * DataLogicDescriptionClass::BaseDataObjectExample()
{ 
  BaseDataLogicDescription *obj = new BaseDataLogicDescription();
  obj->SetType(Identification);
  return (BaseDataObject *) obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataLogicDescriptionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataLogicDescriptionClass*& obj)
{
  obj = new DataLogicDescriptionClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataLogicDescription
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataLogicDescription*& obj)
{
  obj = new BaseDataLogicDescription;
  return obj->DecodeThis(buffer);
}
/*F classes = PointerToAllowedClasses()
**
**  DESCRIPTION
**  This returns the standard set of allowed classes.
**
**  REMARKS
**
*/
DataSetOfObjectsClass *DataLogicDescriptionClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataLogicalClass *DataLogicDescriptionClass::getLogicClass()
{
  return LogicClass;
}

/*S BaseDataPartition
 */ 
/*F BaseDataPartition()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataPartition::BaseDataPartition()
{
  Identification = PREDICATE_PARTITION_ID;
  NameTag = PREDICATE_PARTITION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataPartition(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataPartition::BaseDataPartition(const BaseDataPartition& data)
  : BaseDataKeyWords(data)
{
}
/*F BaseDataPartition(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataPartition::BaseDataPartition(const BaseDataKeyWords& data)
  : BaseDataKeyWords(data)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataPartition
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataPartition::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataPartition
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataPartition::Read(istream& in, DataObjectClass* objc, const String& name)
{
  return BaseDataKeyWords::Read(in,objc,name);
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataPartition
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataPartition::print(ostream& out) const
{
  BaseDataKeyWords::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataPartition
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataPartition::Clone()
{
  BaseDataPartition *obj = new BaseDataPartition;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataPartition
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataPartition::CopyClone(Identify * obj)
{
  BaseDataPartition *objfull = (BaseDataPartition *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPartition
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPartition::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataKeyWords::EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataPartition
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPartition::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataKeyWords::DecodeThis(buffer);

  return result;
}
 
/*S DataPartitionClass
 */
/*F DataPartitionClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataPartitionClass::DataPartitionClass()
{
  Identification = PREDICATE_PARTITION_ID;
  NameTag = PREDICATE_PARTITION_NAME;
  SubClass = PREDICATE_DESCRIPTION_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataPartitionClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataPartitionClass::DataPartitionClass(const DataPartitionClass& data)
  : DataKeyWordsClass(data)
{
} 
 
/*F DataPartitionClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataPartitionClass::DataPartitionClass(const int id, 
                                       const String& name,
                                       const String& descr)
  : DataKeyWordsClass(id,name,descr)
{
  SubClass = PREDICATE_DESCRIPTION_NAME;
  EncodeDecodeClass = PREDICATE_PARTITION_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataPartitionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataPartitionClass::print(ostream& out) const
{
  DataKeyWordsClass::print(out);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataPartitionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataPartitionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataPartitionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  return DataKeyWordsClass::Read(in,set);
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataPartitionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataPartitionClass::CopyClone(Identify *  objc)
{
  DataPartitionClass *objcfull = (DataPartitionClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataPartitionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataPartitionClass::Clone()
{
  DataPartitionClass* id = new DataPartitionClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataPartitionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPartitionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataKeyWordsClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataPartitionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPartitionClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataKeyWordsClass::DecodeThis(buffer);
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
BaseDataObject * DataPartitionClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataPartition();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataPartitionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataPartitionClass*& obj)
{
  obj = new DataPartitionClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataPartition
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataPartition*& obj)
{
  obj = new BaseDataPartition;
  return obj->DecodeThis(buffer);
}

/*S BaseDataPartitionTable
 */ 
/*F BaseDataPartitionTable()  . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataPartitionTable::BaseDataPartitionTable()
{
  Identification = PREDICATE_PARTITIONTABLE_ID;
  NameTag = PREDICATE_PARTITIONTABLE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataPartitionTable(data)  . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataPartitionTable::BaseDataPartitionTable(const BaseDataPartitionTable& data)
  : BaseDataObject(data),
    Columns(data.Columns),
    Rows(data.Rows)
{
}
 
/*F BaseDataPartitionTable(columns,rows)  . . . . . . . . .  table from names
**
**  DESCRIPTION
**    columns: The set of predicate names of the columns
**    rows: The set of predicate names of the rows
**
**  REMARKS
**
*/
BaseDataPartitionTable::BaseDataPartitionTable(BaseDataKeyWords& columns,
                                               BaseDataKeyWords& rows)
  : Columns(columns),
    Rows(rows)
{
  Identification = PREDICATE_PARTITIONTABLE_ID;
  NameTag = PREDICATE_PARTITIONTABLE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
}
/*F BaseDataPartitionTable(partitionpair) . . . . . . . . .  table from names
**
**  DESCRIPTION
**    description: The set of predicates
**    columns: The set of predicate names of the columns
**    rows: The set of predicate names of the rows
**
**  REMARKS
**
*/
BaseDataPartitionTable::BaseDataPartitionTable(BaseDataSetOfObjects* instances,
                                               String& partition)
{
  Identification = PREDICATE_PARTITIONTABLE_ID;
  NameTag = PREDICATE_PARTITIONTABLE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  bool result = instances->IsInList(partition);
  if(result)
    {
      BaseDataKeyWords *pkeys = (BaseDataKeyWords *) instances->GetObject(partition);
      ObjectList<String> pstrings = pkeys->GetKeyWords();
      if(pstrings.size() == 2)
        {
          String rows = pstrings.front();
          pstrings.pop_front();
          String columns = pstrings.front();
          result = result && instances->IsInList(rows);
          result = result && instances->IsInList(columns);
          if(result)
            {
              BaseDataKeyWords *r = (BaseDataKeyWords *) instances->GetObject(rows);
              BaseDataKeyWords *c = (BaseDataKeyWords *) instances->GetObject(columns);
              this->CopyClone(new BaseDataPartitionTable(*r,*c));
            }
          else
            {
              cerr << "At least one partition not found: :";
              cerr << rows;
              cerr << " ";
              cerr << columns;
              cerr << "\n";
            }
        }
      else
        {
          cerr << "Partition Table specification has ";
          cerr << pstrings.size();
          cerr << " elements instead of 2 (";
          cerr << pstrings;
          cerr << " )\n";
        }
    }
  else
    {
      cerr << "PartitionTable Specification not found in instances attributes: ";
      cerr << partition;
      cerr << "\n";
    }
  
}
/*F Read(in,objc) . . . . . . . . . . . . . .  Read in BaseDataPartitionTable
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataPartitionTable::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . .  Read in BaseDataPartitionTable
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataPartitionTable::Read(istream& in, DataObjectClass* objc, const String& name)
{
  DataPartitionTableClass *cdescr = (DataPartitionTableClass *) objc;
  
  bool result = BaseDataObject::Read(in,objc,name);
  StreamObjectInput str(in,' ');

  DataPartitionClass *classdescr = cdescr->ClassDescriptions();
  
  String tag = str.ReadNext();
  if(tag == "PartitionTable-Rows:")
    {
      Rows.NameTag = "Rows";
      result = result && Rows.Read(in,classdescr,Rows.NameTag);
      tag = str.ReadNext();
      if(tag == "PartitionTable-Columns:")
        {
	  Columns.NameTag = "Columns";
          result = result && Columns.Read(in,classdescr,Columns.NameTag);
        }
      else
        {
          cerr << "Expected: 'PartitionTable-Columns:' found ";
          cerr << tag;
          cerr << "\n";
          result = false;
        }
    }
  else
    {
      cerr << "Expected: 'PartitionTable-Rows:' found ";
      cerr << tag;
      cerr << "\n";
      result = false;
    }
       
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . .  BaseDataPartitionTable
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataPartitionTable::print(ostream& out) const
{
  BaseDataObject::print(out);
  out << endl << "Rows         ";
  Rows.print(out);
  out << endl << "Columns      ";
  Columns.print(out);
  out << endl;

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . .  BaseDataPartitionTable
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataPartitionTable::Clone()
{
  BaseDataPartitionTable *obj = new BaseDataPartitionTable;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . .  BaseDataPartitionTable
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataPartitionTable::CopyClone(Identify * obj)
{
  BaseDataPartitionTable *objfull = (BaseDataPartitionTable *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . .  BaseDataPartitionTable
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPartitionTable::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && Rows.EncodeThis(buffer);
  result = result && Columns.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . .  BaseDataPartitionTable
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPartitionTable::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && Rows.DecodeThis(buffer);
  result = result && Columns.DecodeThis(buffer);

  return result;
}
//#define DEBUG_LEVEL3 
/*F CalculateFromLogDesc(mat,result,instance,descr,condition,addin)
**
**  DESCRIPTION
**    mat:  The matrix to be filled in (mat[row,col])
**    result:  The logic value of the result
**    instance:  The instance name
**    descr:     The set descriptions for the instances and predicates
**    condition: The preconditions (AND to the result)
**    addin:     true if the result should be added into the matrix, otherwise the value is set
**
**    The matrix of the partition table is set up by ANDing the rows and columns
**
**    The used version of this routine (especially since it is filling a
**    matrix of doubles, is to use the multiply for the AND.
**    A commented out version uses the AND.  The other 'earlier' version
**    is a more inefficient version.
**
**  REMARKS
**
*/
void BaseDataPartitionTable::CalculateFromLogDesc(MatrixNumeric* mat,
                                                  BaseDataLogical *result,
                                                  const String& instance,
                                                  BaseDataSetOfLogicDescriptions& descr,
                                                  BaseDataLogical *condition,
                                                  bool addin)
{
  //unsigned int r=0;
  //unsigned int c=0;
  
  ObjectList<int> empty;
  ObjectList<String> rownames = Rows.GetKeyWords();
  ObjectList<String> colnames = Columns.GetKeyWords();
  ObjectList<String>::const_iterator row,column;
  
  unsigned int colsize = colnames.size();
  unsigned int rowsize = rownames.size();
  double columnvalues[colsize];
  double rowvalues[rowsize];

  BaseDataLogical *intermediate = (BaseDataLogical *) result->Clone();

  double condvalue = condition->GetValue();
  unsigned int count = 0;
  for(row = rownames.begin(); !(row == rownames.end()); row++) {
    BaseDataLogical *rlogic = descr.GetLogicValue(instance,*row);
    result->SetValue(condvalue);
    result->AND(*rlogic);
    rowvalues[count++] = result->GetValue();
  }
  count = 0;
  for(column = colnames.begin(); !(column == colnames.end()); column++)
    columnvalues[count++] = descr.GetLogicValue(instance,*column)->GetValue();

  if(addin) {
    for(unsigned int irow = 0; irow < rowsize; irow++) {
      for(unsigned int icol = 0; icol < colsize;icol++) {
	(*mat)[irow][icol] += rowvalues[irow]*columnvalues[icol];
      }
    }
  } else {
    for(unsigned int irow = 0; irow < rowsize; irow++) {
      for(unsigned int icol = 0; icol < colsize; icol++) {
	(*mat)[irow][icol]  = rowvalues[irow]*columnvalues[icol];
      }
    }
  }
  delete intermediate;
  /**
     This is using AND (the proper way) to do the interactions
     Of course it is slower
  for(int irow = 0; irow < rowsize; irow++) {
    for(int icol = 0; icol < colsize;irow++) {
      result->SetValue(rowvalues[irow]);
      intermediate->SetValue(columnvalues[icol]);
      result->AND(intermediate);
          if(addin)
            (*mat)[r][c] += result->GetValue();
          else
            (*mat)[r][c] = result->GetValue();
    }
  }
  */

  /*
  for(row = rownames.begin();
      !(row == rownames.end());
      row++)
    {
      BaseDataLogical *rlogic = descr.GetLogicValue(instance,*row);
      c = 0;
      for(column = colnames.begin();
          !(column == colnames.end());
          column++)
        {
          BaseDataLogical *clogic = (BaseDataLogical *) descr.GetLogicValue(instance,*column);
          result->SetValue(condition->GetValue());
          result->AND(*rlogic);
          result->AND(*clogic);
          
          if(addin)
            (*mat)[r][c] += result->GetValue();
          else
            (*mat)[r][c] = result->GetValue();
          c++;
        }
      r++;
    }
  */
}
/*F mat = CalculatePartitionMatrixFromSet(instance,instclass,condition,condclass) 
**
**  DESCRIPTION
**    instance: The instance
**    instclass: The instance class
**    condition: The precondition logic 
**    condclass: The precondition logic class
**
**  REMARKS
**
*/
MatrixNumeric *BaseDataPartitionTable::CalculatePartitionMatrixFromSet(BaseDataSetOfLogicDescriptions& ldescrs,
                                                                       BaseDataSetOfInstances*,
                                                                       DataSetOfInstancesClass* instclasses,
                                                                       DataSetOfLogicDescriptionsClass& ldescrsclass,
                                                                       BaseDataConjunction *conj,
                                                                       DataConjunctionClass *,
                                                                       ObjectList<String>& instnames)
{
  ObjectList<String> rownames = Rows.GetKeyWords();
  ObjectList<String> colnames = Columns.GetKeyWords();
  BaseDataLogical *result = new BaseDataLogical;
  
  unsigned int rowsize = rownames.size();
  unsigned int colsize = colnames.size();
  
  MatrixNumeric *mat = new MatrixNumeric(rowsize,colsize);

  DataLogicalClass *condclass = (DataLogicalClass *) 
    instclasses->PointerToAllowedClasses()->GetObjectClass(LOGICAL_BASE_NAME);
  
  BaseDataLogical *condition = 
    (BaseDataLogical *) condclass->BaseDataObjectExample();
  
  ObjectList<String>::iterator name;
  bool notfirst = false;

  BaseDataKeyWords ckeys = conj->KeyWordsFromConjunction();
  ObjectList<String> cnames = ckeys.GetKeyWords();
  BaseDataLogical *logic;
  double count = 0.0;
  for(name = instnames.begin();name != instnames.end();name++)
    {
      condition->SetValue(1.0);
      for(ObjectList<String>::iterator cname = cnames.begin(); cname != cnames.end();cname++)
	{
	  logic = ldescrs.GetLogicValue(*name,*cname);
	  if(logic != NULL)
	    {
	      condition->AND(*logic);
	    }
	  else
	    condition->SetValue(0.0);
	}
      CalculateFromLogDesc(mat,result,*name,ldescrs,condition,notfirst);
      count++;
      notfirst = true;
    }

  double n = 0.0;
  for(unsigned int i=0;i != rowsize;i++)
    for(unsigned int j=0;j != colsize;j++)
      n += (*mat)[i][j];
  if(n > .0001)
    {
      double inv = 1.0/n;
      for(unsigned int i=0;i != rowsize;i++)
        for(unsigned int j=0;j != colsize;j++)
          (*mat)[i][j] *= inv;
    }
  return mat;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . .  BaseDataPartitionTable
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
bool BaseDataPartitionTable::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << "PartitionTable: " << NameTag << " ";
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . .  BaseDataPartitionTable
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
bool BaseDataPartitionTable::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  bool result = true;
  out << "PartitionTable-Rows:" << endl;
  result = result && Columns.WriteAsASCII(out,objc);
  out << "PartitionTable-Columns:" << endl;
  result = result && Rows.WriteAsASCII(out,objc);
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . .  BaseDataPartitionTable
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
bool BaseDataPartitionTable::WriteAsLatex(ostream& out, DataObjectClass *objc)
{
  bool result = true;
  result = result && Columns.WriteAsLatex(out,objc);
  result = result && Rows.WriteAsLatex(out,objc);
  return result;
}

/*S DataPartitionTableClass
 */
/*F DataPartitionTableClass() . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataPartitionTableClass::DataPartitionTableClass()
{
  Identification = PREDICATE_PARTITIONTABLE_ID;
  NameTag = PREDICATE_PARTITIONTABLE_NAME;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataPartitionTableClass(data) . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataPartitionTableClass::DataPartitionTableClass(const DataPartitionTableClass& data)
  : DataObjectClass(data),
    Classes(data.Classes)
{
} 
 
/*F DataPartitionTableClass(id,name,descr)  . . . . . . . . . . . constructor
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
DataPartitionTableClass::DataPartitionTableClass(const int id, 
                                                 const String& name,
                                                 const String& descr)
  : DataObjectClass(id,name,descr)
{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = PREDICATE_PARTITIONTABLE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . DataPartitionTableClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataPartitionTableClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  out << "Begin: ------------ The Class Descriptions of Partition Table Class -------------\n";
  Classes.print(out);
  out << "End  : ------------ The Class Descriptions of Partition Table Class-------------\n";
       
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . DataPartitionTableClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataPartitionTableClass, there is no further information.
**
**  REMARKS
**
*/
bool DataPartitionTableClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataObjectClass::Read(in,set);
  result = result && Classes.Read(in,set);
  result = result && ColumnPairs.Read(in);
  
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . DataPartitionTableClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataPartitionTableClass::CopyClone(Identify *  objc)
{
  DataPartitionTableClass *objcfull = (DataPartitionTableClass*) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . DataPartitionTableClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataPartitionTableClass::Clone()
{
  DataPartitionTableClass* id = new DataPartitionTableClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . DataPartitionTableClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPartitionTableClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  result = result && Classes.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . DataPartitionTableClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPartitionTableClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
  result = result && Classes.DecodeThis(buffer);

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
BaseDataObject * DataPartitionTableClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataPartitionTable();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . DataPartitionTableClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataPartitionTableClass*& obj)
{
  obj = new DataPartitionTableClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . .  BaseDataPartitionTable
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataPartitionTable*& obj)
{
  obj = new BaseDataPartitionTable;
  return obj->DecodeThis(buffer);
}
 
/*F cdescr = ClassDescriptions()  . . . . . . . . . . . .  pointer to classes
**
**  DESCRIPTION
**    cdescr: The class descriptions
**
**  REMARKS
**
*/
DataPartitionClass * DataPartitionTableClass::ClassDescriptions()
{
  return &Classes;
} 
/*F colpairs = GetColumnPairs() . . . . . . . . . . . . . . . get ColumnPairs
**
**  DESCRIPTION
**    colpairs: The set of ObjectNamePairs
**
**  REMARKS
**
*/
ObjectNameClassPairs* DataPartitionTableClass::GetColumnPairs()
{
  return &ColumnPairs;
}
/*S BaseDataConjunction
 */ 
/*F BaseDataConjunction() . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataConjunction::BaseDataConjunction()
{
  Identification = PREDICATE_CONJUNCTION_ID;
  NameTag = PREDICATE_CONJUNCTION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataConjunction(data) . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataConjunction::BaseDataConjunction(const BaseDataConjunction& data)
  : BaseDataOperation(data),
    LogicalOperations(data.LogicalOperations)
{
}
/*F BaseDataConjunction(descr)  . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    descr: The description
**
**  REMARKS
**
*/
BaseDataConjunction::BaseDataConjunction(const BaseDataDescription& descr)
  : LogicalOperations(descr)
{
  Identification = PREDICATE_CONJUNCTION_ID;
  NameTag = PREDICATE_CONJUNCTION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  NameTag = descr.NameTag;
  Identification = descr.Identification;
}
 
/*F conj = CreateConjunction(set,conjkeys)  . . . . . . . BaseDataConjunction
**
**  DESCRIPTION
**    set: The source of the predicates
**    conjkeys: The set of names 
**    conj: The created conjunction
**
**  REMARKS
**
*/
BaseDataConjunction* BaseDataConjunction::CreateConjunction(BaseDataSetOfObjects* set, BaseDataKeyWords* conjkeys)
{
  BaseDataDescription descr(set,*conjkeys);
#ifdef DEBUG_LEVEL1
  cout << "Conjunction Description\n";
  descr.print(cout);
#endif
  
  BaseDataConjunction *conj = new BaseDataConjunction(descr);
#ifdef DEBUG_LEVEL1
  cout << "Conjunction\n";
  conj->print(cout);
#endif
  return conj;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . Read in BaseDataConjunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataConjunction::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput inpstr(in,' ');
  NameTag = inpstr.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . Read in BaseDataConjunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataConjunction::Read(istream& in, DataObjectClass* objc, const String& name)
{
  DataConjunctionClass *cnjclass = (DataConjunctionClass *) objc;
  
  bool result = BaseDataOperation::Read(in,objc,name);
  StreamObjectInput strinput(in,' ');
  
  String tag = strinput.ReadNext();
  if(result && tag == "ConjunctionPredicates:")
    {
      result = result && LogicalOperations.Read(in,cnjclass->LogicalOperationsClassPointer(),name);
    }
  else
    {
      cerr << "Expected 'DisjunctionPredicates:', got '" << tag << "'" << endl;
      result = false;
    }
  
  return result;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . BaseDataConjunction
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataConjunction::print(ostream& out) const
{
  BaseDataOperation::print(out);
  out << "\nBegin:   The Set of Logical Operations for Conjuction:\n";
  LogicalOperations.print(out);
  out << "\nEnd:     The Set of Logical Operations for Conjuction:\n";
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . BaseDataConjunction
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataConjunction::Clone()
{
  BaseDataConjunction *obj = new BaseDataConjunction;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . BaseDataConjunction
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataConjunction::CopyClone(Identify * obj)
{
  BaseDataConjunction *objfull = (BaseDataConjunction *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . BaseDataConjunction
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataConjunction::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  result = result && LogicalOperations.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . BaseDataConjunction
**
**  Description
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataConjunction::DecodeThis(CommBuffer& buffer)
{
  bool result = true;
  result = result && BaseDataOperation::DecodeThis(buffer);
  if(!result)
    cerr << "BaseDataConjunction::DecodeThis SubClass failed\n";
  result = result && LogicalOperations.DecodeThis(buffer);
  if(!result)
    cerr << "BaseDataConjunction::DecodeThis Operations failed\n";

  return result;
}
 
/*F ans = AddPredicate(pred)  . . . . . . . . . . . . . .  add to conjunction
**
**  DESCRIPTION
**    pred: The predicate
**    ans: true if successful
**    
**  REMARKS
**
*/
bool BaseDataConjunction::AddPredicate(BaseDataPredicate *pred)
{
  return LogicalOperations.AddPredicate(pred);
}
/*F num = NumberOfElements(instnames,logical,logclass,ldescrs,ldescrsclass)
**
**  DESCRIPTION
**     instnames: The list of names from Logical descriptions
**     logical: The type of logic
**     logclass: The logical class
**     ldescrs: The set of descriptions
**     ldescrsclass: The class of logical descriptions
**
**     For each instance, the logical description is retrieved 
**     from the set of logical descriptions and then the 
**     operation of this description is used to determine
**     to what extent this element fits the description.
**
**  REMARKS
**
*/
double BaseDataConjunction::NumberOfElements(ObjectList<String>& instnames,
                                             BaseDataLogical* logical,
                                             DataLogicalClass* logclass,
                                             BaseDataSetOfLogicDescriptions& ldescrs,
                                             DataSetOfLogicDescriptionsClass& ldescrsclass)
{
  BaseDataLogical *logic;
  ObjectList<String> cnames = LogicalOperations.ListOfObjectNames();

  ObjectList<String>::iterator iname,cname;
  double n = 0.0;
  for(iname = instnames.begin();
      iname != instnames.end();
      iname++)
    {
      logical->SetValue(1.0);
      for(cname = cnames.begin(); cname != cnames.end();cname++)
	{
	  logic = ldescrs.GetLogicValue(*iname,*cname);
	  if(logic != NULL)
	    {
	      logical->AND(*logic);
	    }
	  else
	    logical->SetValue(0.0);
	}
      n += logical->GetValue();
    }
  return n;
}
 
/*F keywords = KeyWordsFromConjunction()  . . . . . . . . BaseDataConjunction
**
**  DESCRIPTION
**    keywords: The names of the predicates used in the conjunction
**
**  REMARKS
**
*/
BaseDataKeyWords& BaseDataConjunction::KeyWordsFromConjunction()
{
  ObjectList<String> keys = LogicalOperations.ListOfObjectNames();
  BaseDataKeyWords *conjkeys = new BaseDataKeyWords(keys);
  return *conjkeys;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . . . BaseDataConjunction
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
bool BaseDataConjunction::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << "Conjunction: " << LogicalOperations.WriteAsLine(out,objc) << " ";
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . BaseDataConjunction
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
bool BaseDataConjunction::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  DataConjunctionClass *lclass = (DataConjunctionClass *) objc;
  out << "ConjunctionPredicates: " << endl;
  bool result = LogicalOperations.WriteAsASCII(out,lclass->LogicalOperationsClassPointer());
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . BaseDataConjunction
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
bool BaseDataConjunction::WriteAsLatex(ostream& out, DataObjectClass *objc)
{
  DataConjunctionClass *lclass = (DataConjunctionClass *) objc;
  bool result = LogicalOperations.WriteAsLatex(out,lclass->LogicalOperationsClassPointer());
  return result;
}
/*F obj = operator()(log,obj,lclass,objclass) . . . conjunction from instance
**
**  DESCRIPTION
**    log: The logical object
**    obj: The instance
**    lclass: The logical class
**    objclass: The instance class
**
**  REMARKS
**
*/
BaseDataObject *BaseDataConjunction::operator()(BaseDataObject* log,
                                                BaseDataObject* obj,
                                                DataObjectClass *lclass,
                                                DataObjectClass *objclass)
{
  BaseDataLogical *logical = (BaseDataLogical *) log;
  DataLogicalClass *logclass = (DataLogicalClass *) lclass;
  DataInstanceClass *instclass = (DataInstanceClass *) objclass;
  BaseDataInstance *instance = (BaseDataInstance *) obj;
  
  BaseDataLogical *logic = (BaseDataLogical *) lclass->BaseDataObjectExample();
  ObjectList<String> names = LogicalOperations.ListOfObjectNames();
  
  ObjectList<String>::iterator name;
  for(name = names.begin();
      name != names.end();
      name++) {
    BaseDataPredicate *op = (BaseDataPredicate *) LogicalOperations.GetObject(*name);
    op->operator()(logic,instance,logclass,instclass);
    logical->AND(*logic);
  }
  delete logic;
  return (BaseDataObject *) logical;
}

/*S DataConjunctionClass
 */
/*F DataConjunctionClass()  . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataConjunctionClass::DataConjunctionClass()
{
  Identification = PREDICATE_CONJUNCTION_ID;
  NameTag = PREDICATE_CONJUNCTION_NAME;
  SubClass = OPERATION_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataConjunctionClass(obj) . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataConjunctionClass::DataConjunctionClass(const DataConjunctionClass& obj)
  : DataOperationClass(obj),
    LogicalOperationsClass(obj.LogicalOperationsClass)
{
} 
/*F DataConjunctionClass(id,name,descr) . . . . . . . . . . . . . constructor
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
DataConjunctionClass::DataConjunctionClass(const int id, 
                                           const String& name,
                                           const String& descr)
  : DataOperationClass(id,name,descr)
{
  SubClass = OPERATION_BASE_NAME;
  EncodeDecodeClass = PREDICATE_CONJUNCTION_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . .  DataConjunctionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataConjunctionClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  out << "The Operation Classes:\n";
  LogicalOperationsClass.print(out);
  
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . .  DataConjunctionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataConjunctionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataConjunctionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);
  result = result && LogicalOperationsClass.Read(in,set);
  
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . .  DataConjunctionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataConjunctionClass::CopyClone(Identify *  objc)
{
  DataConjunctionClass *objcfull = (DataConjunctionClass *) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . .  DataConjunctionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataConjunctionClass::Clone()
{
  DataConjunctionClass* id = new DataConjunctionClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . .  DataConjunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataConjunctionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  result = result && LogicalOperationsClass.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . .  DataConjunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataConjunctionClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
  result = result && LogicalOperationsClass.DecodeThis(buffer);

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
BaseDataObject * DataConjunctionClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataConjunction();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . .  DataConjunctionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataConjunctionClass*& obj)
{
  obj = new DataConjunctionClass;
  return obj->DecodeThis(buffer);
}
 
/*F descrclass = LogicalOperationsClassPointer()  . . . pointer to class info
**
**  DESCRIPTION
**    descrclass: The class information
**
**  REMARKS
**
*/
DataDescriptionClass *DataConjunctionClass::LogicalOperationsClassPointer()
{
  return &LogicalOperationsClass;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . BaseDataConjunction
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataConjunction*& obj)
{
  obj = new BaseDataConjunction;
  return obj->DecodeThis(buffer);
}

/*S BaseDataDisjunction
 */ 
/*F BaseDataDisjunction() . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataDisjunction::BaseDataDisjunction()
{
  Identification = PREDICATE_DISJUNCTION_ID;
  NameTag = PREDICATE_DISJUNCTION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataDisjunction(data) . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDisjunction::BaseDataDisjunction(const BaseDataDisjunction& data)
  : BaseDataOperation(data),
    LogicalOperations(data.LogicalOperations)
{
}
/*F BaseDataDisjunction(data) . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataDisjunction::BaseDataDisjunction(const BaseDataDescription& data)
  : LogicalOperations(data)
{
  Identification = PREDICATE_DISJUNCTION_ID;
  NameTag = PREDICATE_DISJUNCTION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

  NameTag = data.NameTag;
  Identification = data.Identification;
}
 
/*F disj = CreateDisjunction(set,disjkeys)  . . . . . . . BaseDataDisjunction
**
**  DESCRIPTION
**    set: The set of objects from which the predicates
**    conjkeys: The set of predicates to choose
**    disj: The created disjunction
**
**  REMARKS
**
*/
BaseDataDisjunction* BaseDataDisjunction::CreateDisjunction(BaseDataSetOfObjects* set, BaseDataKeyWords* disjkeys)
{
  BaseDataDescription descr(set,*disjkeys);
#ifdef DEBUG_LEVEL1
  cout << "Disjunction Description\n";
  descr.print(cout);
#endif
  
  BaseDataDisjunction *disj = new BaseDataDisjunction(descr);
#ifdef DEBUG_LEVEL1
  cout << "Disjunction\n";
  disj->print(cout);
#endif
  return disj;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . Read in BaseDataDisjunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataDisjunction::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput inpstr(in,' ');
  NameTag = inpstr.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . Read in BaseDataDisjunction
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataDisjunction::Read(istream& in, DataObjectClass* objc, const String& name)
{
  DataDisjunctionClass *cnjclass = (DataDisjunctionClass *) objc;
  bool result = BaseDataOperation::Read(in,objc,name);
  StreamObjectInput strinput(in,' ');
  
  String tag = strinput.ReadNext();
  if(result && tag == "DisjunctionPredicates:")
    {
      result = result && LogicalOperations.Read(in,cnjclass->LogicalOperationsClassPointer(),name);
    }
  else
    {
      cerr << "Expected 'DisjunctionPredicates:', got '" << tag << "'" << endl;
      result = false;
    }
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . BaseDataDisjunction
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataDisjunction::print(ostream& out) const
{
  BaseDataOperation::print(out);
  out << "The Set of Logical Operations for Disjunction:";
  LogicalOperations.print(out);
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . BaseDataDisjunction
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataDisjunction::Clone()
{
  BaseDataDisjunction *obj = new BaseDataDisjunction;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . BaseDataDisjunction
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataDisjunction::CopyClone(Identify * obj)
{
  BaseDataDisjunction *objfull = (BaseDataDisjunction *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . BaseDataDisjunction
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDisjunction::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  result = result && LogicalOperations.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . BaseDataDisjunction
**
**  Description
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataDisjunction::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  result = result && LogicalOperations.DecodeThis(buffer);

  return result;
}
 
/*F ans = AddPredicate(pred)  . . . . . . . . . . . . . .  add to conjunction
**
**  DESCRIPTION
**    pred: The predicate
**    ans: true if successful
**    
**  REMARKS
**
*/
bool BaseDataDisjunction::AddPredicate(BaseDataPredicate *pred)
{
  return LogicalOperations.AddPredicate(pred);
}
/*F obj = operator()(obj,objclass)  . . . . compute conjunction from instance
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataObject *BaseDataDisjunction::operator()(BaseDataObject* log,
                                                BaseDataObject* obj,
                                                DataObjectClass *lclass,
                                                DataObjectClass *objclass)
{
  BaseDataLogical *logical = (BaseDataLogical *) log;
  DataLogicalClass *logclass = (DataLogicalClass *) lclass;
  DataInstanceClass *instclass = (DataInstanceClass *) objclass;
  BaseDataInstance *instance = (BaseDataInstance *) obj;
  
  BaseDataLogical *logic = (BaseDataLogical *) logical->Clone();
  ObjectList<String> names = LogicalOperations.ListOfObjectNames();
  
  ObjectList<String>::iterator name;
  for(name = names.begin();
      name != names.end();
      name++)
    {
      BaseDataPredicate *op = (BaseDataPredicate *) LogicalOperations.GetObject(*name);
      op->operator()(logic,instance,logclass,instclass);
      logical->OR(*logic);
    }
  //delete logic;
  
  return (BaseDataObject *) logical;
}
/*F num = NumberOfElements(log,instances,lclass,instclass,instnames)
**
**  DESCRIPTION
**    instances: The instances
**    instclass: The instance class
**
**  REMARKS
**
*/
double BaseDataDisjunction::NumberOfElements(BaseDataLogical *log,
                                             BaseDataSetOfInstances *instances,
                                             DataLogicalClass *lclass,
                                             DataSetOfInstancesClass *instclass,
                                             ObjectList<String>& instnames)

{
  BaseDataLogical *logical = log;
  DataLogicalClass *logclass = lclass;
  DataInstanceClass *iclass = (DataInstanceClass *) instclass;

  ObjectList<String> names = LogicalOperations.ListOfObjectNames();

  ObjectList<String>::iterator name;
  double n = 0.0;
  for(name = instnames.begin();
      name != instnames.end();
      name++)
    {
      BaseDataInstance *instance = 
        (BaseDataInstance *) instances->GetInstance(*name);
      logical->SetValue(1.0);
      this->operator()(logical,instance,logclass,iclass);
      n += logical->GetValue();
    }
  return n;
}
/*F keys = KeyWordsFromDisjunction()  . . . . . . . . . . BaseDataDisjunction
**
**  DESCRIPTION
**    keys: The list of names logical objects 
**
**  REMARKS
**
*/
BaseDataKeyWords& BaseDataDisjunction::KeyWordsFromDisjunction()
{
  ObjectList<int> empty;
  ObjectList<String> keys = LogicalOperations.ListOfObjectNames(empty);
  BaseDataKeyWords *conjkeys = new BaseDataKeyWords(keys);
  return *conjkeys;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . . . BaseDataDisjunction
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
bool BaseDataDisjunction::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << "Disjunction:" << LogicalOperations.WriteAsLine(out,objc) << " ";
    return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . BaseDataDisjunction
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
bool BaseDataDisjunction::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  DataDisjunctionClass *lclass = (DataDisjunctionClass *) objc;
  out << "DisjunctionPredicates: " << endl;
  bool result = LogicalOperations.WriteAsASCII(out,lclass->LogicalOperationsClassPointer());
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . BaseDataDisjunction
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
bool BaseDataDisjunction::WriteAsLatex(ostream& out, DataObjectClass *objc)
{
  DataDisjunctionClass *lclass = (DataDisjunctionClass *) objc;
  bool result = LogicalOperations.WriteAsLatex(out,lclass->LogicalOperationsClassPointer());
  return result;
}

/*S DataDisjunctionClass
 */
/*F DataDisjunctionClass()  . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDisjunctionClass::DataDisjunctionClass()
{
  Identification = PREDICATE_DISJUNCTION_ID;
  NameTag = PREDICATE_DISJUNCTION_NAME;
  SubClass = OPERATION_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataDisjunctionClass(obj) . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataDisjunctionClass::DataDisjunctionClass(const DataDisjunctionClass& obj)
  : DataOperationClass(obj),
    LogicalOperationsClass(obj.LogicalOperationsClass)
{
} 
/*F DataDisjunctionClass(id,name,descr) . . . . . . . . . . . . . constructor
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
DataDisjunctionClass::DataDisjunctionClass(const int id, 
                                           const String& name,
                                           const String& descr)
  : DataOperationClass(id,name,descr)
{
  SubClass = OPERATION_BASE_NAME;
  EncodeDecodeClass = PREDICATE_DISJUNCTION_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . .  DataDisjunctionClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataDisjunctionClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  out << "The Operation Classes:\n";
  LogicalOperationsClass.print(out);
  
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . .  DataDisjunctionClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataDisjunctionClass, there is no further information.
**
**  REMARKS
**
*/
bool DataDisjunctionClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);
  result = result && LogicalOperationsClass.Read(in,set);
  
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . .  DataDisjunctionClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataDisjunctionClass::CopyClone(Identify *  objc)
{
  DataDisjunctionClass *objcfull = (DataDisjunctionClass *) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . .  DataDisjunctionClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataDisjunctionClass::Clone()
{
  DataDisjunctionClass* id = new DataDisjunctionClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . .  DataDisjunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDisjunctionClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  result = result && LogicalOperationsClass.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . .  DataDisjunctionClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataDisjunctionClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
  result = result && LogicalOperationsClass.DecodeThis(buffer);

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
BaseDataObject * DataDisjunctionClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataDisjunction();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . .  DataDisjunctionClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataDisjunctionClass*& obj)
{
  obj = new DataDisjunctionClass;
  return obj->DecodeThis(buffer);
}
 
/*F descrclass = LogicalOperationsClassPointer()  . . . pointer to class info
**
**  DESCRIPTION
**    descrclass: The class information
**
**  REMARKS
**
*/
DataDescriptionClass *DataDisjunctionClass::LogicalOperationsClassPointer()
{
  return &LogicalOperationsClass;
}

/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . BaseDataDisjunction
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataDisjunction*& obj)
{
  obj = new BaseDataDisjunction;
  return obj->DecodeThis(buffer);
}

/*S BaseDataSetOfLogicDescriptions
 */ 
/*F BaseDataSetOfLogicDescriptions()  . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSetOfLogicDescriptions::BaseDataSetOfLogicDescriptions()
{
  Identification = PREDICATE_LOGICDESCRSET_ID;
  NameTag = PREDICATE_LOGICDESCRSET_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataSetOfLogicDescriptions(data)  . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataSetOfLogicDescriptions::BaseDataSetOfLogicDescriptions(const BaseDataSetOfLogicDescriptions& data)
  : BaseDataSetOfObjects(data)
{
}
/*F Read(in,objc) . . . . . . . . . .  Read in BaseDataSetOfLogicDescriptions
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataSetOfLogicDescriptions::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . .  Read in BaseDataSetOfLogicDescriptions
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataSetOfLogicDescriptions::Read(istream& in, DataObjectClass* objc, const String& name)
{
  DataSetOfObjectsClass *oclasses = (DataSetOfObjectsClass *) objc;
  bool result = true;
  ObjectNameClassPairs namepairs;
  result = result && namepairs.Read(in);
  oclasses->ReplaceObjectTypes(namepairs);
  return BaseDataSetOfObjects::Read(in,objc,name);
}
 
/*F out1 = print(out) . . . . . . . . . . . .  BaseDataSetOfLogicDescriptions
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataSetOfLogicDescriptions::print(ostream& out) const
{
  BaseDataSetOfObjects::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . .  BaseDataSetOfLogicDescriptions
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataSetOfLogicDescriptions::Clone()
{
  BaseDataSetOfLogicDescriptions *obj = new BaseDataSetOfLogicDescriptions;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . .  BaseDataSetOfLogicDescriptions
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataSetOfLogicDescriptions::CopyClone(Identify * obj)
{
  BaseDataSetOfLogicDescriptions *objfull = (BaseDataSetOfLogicDescriptions *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . .  BaseDataSetOfLogicDescriptions
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSetOfLogicDescriptions::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . .  BaseDataSetOfLogicDescriptions
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSetOfLogicDescriptions::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataSetOfObjects::DecodeThis(buffer);
  return result;
}
/*F ans = AddLogicalObjects(logic,logclass,description,descrclass,instances,instsnames,descrnames)
**
**  DESCRIPTION
**    logic,logclass: The logic and the logic class to make up description
**    description: The description predicates
**    descrclass: The class
**    instances: The instance for which to apply the predicate
**    instsclass: The instance class
**    instnames: The set of instance names to be added
**    descrnames: The set of predicate names from description
**    ans: true if successful
**
**    The name of the instance is the name of the description
**
**  REMARKS
**
*/
bool BaseDataSetOfLogicDescriptions::AddLogicalObjects(BaseDataLogical *logic,
                                                       DataLogicalClass *logclass,
                                                       DataDescriptionClass* descrclass,
                                                       BaseDataSetOfInstances* instances,
                                                       DataSetOfInstancesClass* instsclass,
                                                       ObjectList<String>& instnames,
                                                       ObjectList<String>& descrnames)
{
  bool result = true;

  DataInstanceClass *instclass = (DataInstanceClass *)
    instsclass->PointerToAllowedClasses()->GetObjectClass(INSTANCE_INSTANCE_NAME);
  
  ObjectList<String>::iterator name;
  for(name = instnames.begin();
      name != instnames.end() && result;
      name++)
    {
      BaseDataInstance *instance = 
        (BaseDataInstance *) instances->GetInstance(*name);
      result = result && AddLogicalObject(logic,logclass,
                                          instances,instsclass,
                                          descrnames,descrclass,instance,instclass);
    }
  return result;
}
/*F ans = AddLogicalObject(logic,logclass,description,descrclass,instance,instclass)
**
**  DESCRIPTION
**    logic: This is a dummy logic object to be modified and added (see SetLogicInstance)
**    logclass: The logical class
**    description: The description predicates
**    descrnames: The set of predicates in the description to be added
**    descrclass: The class
**    instance: The instance for which to apply the predicate
**    instclass: The instance class
**    ans: true if successful
**
**    The name of the instance is the name of the description.  If the description already exists
**    then the values are added, otherwise a new description (with the name of the instance) is
**    created.
**
**  REMARKS
**
*/
bool BaseDataSetOfLogicDescriptions::AddLogicalObject(BaseDataLogical *logic,
                                                      DataLogicalClass *logclass,
                                                      BaseDataSetOfInstances* instances,
                                                      DataSetOfInstancesClass* instsclass,
                                                      ObjectList<String>& descrnames,
                                                      DataDescriptionClass*,
                                                      BaseDataInstance* instance,
                                                      DataInstanceClass* instclass)
{
  bool result = true;
  BaseDataLogicDescription *ld;
  
  ld = new BaseDataLogicDescription;
  ld->NameTag = instance->NameTag;
  result = result && AddObject(ld);
  
  delete ld;

  ld = (BaseDataLogicDescription *) GetObject(instance->NameTag);

  result = result && ld->AddLogicInstanceSet(logic,logclass,
                                             instances,instsclass,descrnames,
                                             instance,instclass);
  return result;
}
 
/*F ans = GetLogicValue(instance,predicate)
**
**  DESCRIPTION
**    instance: The name of the instance
**    predicate: The name of the predicate
**    ans: The logical value
**
**    Note that the logical value is not a copy (it is a pointer in the list)
**
**  REMARKS
**
*/
BaseDataLogical *BaseDataSetOfLogicDescriptions::GetLogicValue(const String& instance, 
                                                               const String& predicate)
{
  BaseDataLogical *logic = NULL;
  
  if(IsInList(instance)) {
      BaseDataLogicDescription *descr = (BaseDataLogicDescription *) GetObject(instance);
      if(descr->IsInList(predicate)) {
          logic = (BaseDataLogical *) descr->GetObject(predicate);
        } else {
          cerr << "Description '" << predicate;
          cerr << "' not found in descriptions for '" << instance <<  "'" << endl;
        }
    } else {
      cerr << "Descriptions not found for instance: '" << instance << "'" << endl;
    }
  return logic;
}
/*F ans = WriteAsLine(out,objc) . . . . . . .  BaseDataSetOfLogicDescriptions
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
bool BaseDataSetOfLogicDescriptions::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  out << "SetOfLogicalDescriptions: ";
  return BaseDataSetOfObjects::WriteAsLine(out,objc);
}
/*F ans = WriteAsASCII(out,objc)  . . . . . .  BaseDataSetOfLogicDescriptions
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
bool BaseDataSetOfLogicDescriptions::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  DataSetOfObjectsClass *oclasses = (DataSetOfObjectsClass *) objc;
  return WriteAsASCIIOutFullSetOfObjects(out,*this,*oclasses);
}
/*F ans = WriteAsLatex(out,objc)  . . . . . .  BaseDataSetOfLogicDescriptions
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
bool BaseDataSetOfLogicDescriptions::WriteAsLatex(ostream& out, DataObjectClass *objc)
{
  DataSetOfObjectsClass *oclasses = (DataSetOfObjectsClass *) objc;
  return WriteAsLatexOutFullSetOfObjects(out,*this,*oclasses);
}
/*S DataSetOfLogicDescriptionsClass
 */
/*F DataSetOfLogicDescriptionsClass() . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataSetOfLogicDescriptionsClass::DataSetOfLogicDescriptionsClass()
{
  Identification = PREDICATE_LOGICDESCRSET_ID;
  NameTag = PREDICATE_LOGICDESCRSET_NAME;
  SubClass = COREOBJECTS_SET_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataSetOfLogicDescriptionsClass(data) . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataSetOfLogicDescriptionsClass::DataSetOfLogicDescriptionsClass(const DataSetOfLogicDescriptionsClass& data)
  : DataSetOfObjectsClass(data)
{
} 
 
/*F DataSetOfLogicDescriptionsClass(id,name,descr)  . . . . . . . constructor
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
DataSetOfLogicDescriptionsClass::DataSetOfLogicDescriptionsClass(const int id, 
                                                                 const String& name,
                                                                 const String& descr)
  : DataSetOfObjectsClass(id,name,descr)
{
  SubClass = COREOBJECTS_SET_NAME;
  EncodeDecodeClass = PREDICATE_LOGICDESCRSET_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . DataSetOfLogicDescriptionsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataSetOfLogicDescriptionsClass::print(ostream& out) const
{
  //DataSetOfObjectsClass::print(out);
  out << "Would have print out the set of classes\n";

  // the rest
       
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . DataSetOfLogicDescriptionsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataSetOfLogicDescriptionsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataSetOfLogicDescriptionsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  return DataSetOfObjectsClass::Read(in,set);
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . DataSetOfLogicDescriptionsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataSetOfLogicDescriptionsClass::CopyClone(Identify *  objc)
{
  DataSetOfLogicDescriptionsClass *objcfull = (DataSetOfLogicDescriptionsClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . DataSetOfLogicDescriptionsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataSetOfLogicDescriptionsClass::Clone()
{
  DataSetOfLogicDescriptionsClass* id = new DataSetOfLogicDescriptionsClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . DataSetOfLogicDescriptionsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSetOfLogicDescriptionsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . DataSetOfLogicDescriptionsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSetOfLogicDescriptionsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataSetOfObjectsClass::DecodeThis(buffer);
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
BaseDataObject * DataSetOfLogicDescriptionsClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataSetOfLogicDescriptions();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . DataSetOfLogicDescriptionsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataSetOfLogicDescriptionsClass*& obj)
{
  obj = new DataSetOfLogicDescriptionsClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . .  BaseDataSetOfLogicDescriptions
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataSetOfLogicDescriptions*& obj)
{
  obj = new BaseDataSetOfLogicDescriptions;
  return obj->DecodeThis(buffer);
}
/*F descrclass = getLogicDescription() 
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
DataLogicDescriptionClass *DataSetOfLogicDescriptionsClass::getLogicDescription()
{
  return &LogicDescription;
}
/*F classes = PointerToAllowedClasses()
**
**  DESCRIPTION
**  points to standard allowed classes
**
**  REMARKS
**
*/
DataSetOfObjectsClass *DataSetOfLogicDescriptionsClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}
/*S BaseDataLogicalDescriptionCompare
 */ 
/*F BaseDataLogicalDescriptionCompare()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataLogicalDescriptionCompare::BaseDataLogicalDescriptionCompare()
  : ANDElement(true),
    ORSet(true)
{
  Identification = PREDICATE_LOGCOMP_ID;
  NameTag = PREDICATE_LOGCOMP_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataLogicalDescriptionCompare(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataLogicalDescriptionCompare::BaseDataLogicalDescriptionCompare(const BaseDataLogicalDescriptionCompare& data)
  : BaseDataOperation(data),
    ANDElement(true),
    ORSet(true)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataLogicalDescriptionCompare
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataLogicalDescriptionCompare::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataLogicalDescriptionCompare
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataLogicalDescriptionCompare::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataLogicalDescriptionCompare
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataLogicalDescriptionCompare::print(ostream& out) const
{
  BaseDataOperation::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataLogicalDescriptionCompare
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataLogicalDescriptionCompare::Clone()
{
  BaseDataLogicalDescriptionCompare *obj = new BaseDataLogicalDescriptionCompare(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataLogicalDescriptionCompare
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataLogicalDescriptionCompare::CopyClone(Identify * obj)
{
  BaseDataLogicalDescriptionCompare *objfull = (BaseDataLogicalDescriptionCompare *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataLogicalDescriptionCompare
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLogicalDescriptionCompare::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);
  result = result && BoolEncode(buffer,ANDElement);
  result = result && BoolEncode(buffer,ORSet);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataLogicalDescriptionCompare
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataLogicalDescriptionCompare::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);
  result = result && BoolDecode(buffer,ANDElement);
  result = result && BoolDecode(buffer,ORSet);
  return result;
}
/*F obj = operator()(x,y,xclass,yclass) . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    x,y: The objects to be operated on
**    xclass,yclass: The object classes
**    obj: The result
**
**    This is a dummy two-dimensional call.  An empty object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataLogicalDescriptionCompare::operator()(BaseDataObject *x, BaseDataObject *y,
							      DataObjectClass *xc, DataObjectClass *yc)
                                              
{
  BaseDataLogicDescription *logdescription1 = (BaseDataLogicDescription *) x;
  BaseDataLogicDescription *logdescription2 = (BaseDataLogicDescription *) y;
  DataLogicDescriptionClass *logdclass1 = (DataLogicDescriptionClass *) xc;
  DataLogicDescriptionClass *logdclass2 = (DataLogicDescriptionClass *) yc;

  return CompareLogicalDescriptions(logdescription1,logdescription2,
				    logdclass1,logdclass2);
}
/*F obj = operator()(x,xclass)  . . . . . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    x: The object to be operated on
**    xclass: The class of the object
**    obj: The result
**
**    This is a dummy one-dimensional call.  An empty object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataLogicalDescriptionCompare::operator()(BaseDataObject *x,
							      DataObjectClass *xc)
{
  return (BaseDataObject *) x->Clone();
}
/*F obj = operator()(cls,x,y,xclass,yclass) . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    x,y: The objects to be operated on
**    xclass,yclass: The object classes
**    obj: The result
**
**    This is a dummy two-dimensional call.  An empty object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataLogicalDescriptionCompare::operator()(DataObjectClass *cls,
							      BaseDataObject *x, BaseDataObject *y,
							      DataObjectClass *xc, DataObjectClass *yc)
                                              
{
  BaseDataLogicDescription *logdescription1 = (BaseDataLogicDescription *) x;
  BaseDataLogicDescription *logdescription2 = (BaseDataLogicDescription *) y;
  DataLogicDescriptionClass *logdclass1 = (DataLogicDescriptionClass *) xc;
  DataLogicDescriptionClass *logdclass2 = (DataLogicDescriptionClass *) yc;

  return CompareLogicalDescriptions(logdescription1,logdescription2,
				    logdclass1,logdclass2);
}
/*F obj = operator()(cls,x,xclass)  . . . . . . . . . . . . . . BaseDataOperation
**
**  DESCRIPTION
**    cls: The class of the operation
**    x: The object to be operated on
**    xclass: The class of the object
**    obj: The result
**
**    This is a dummy one-dimensional call.  An empty object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseDataLogicalDescriptionCompare::operator()(DataObjectClass *cls,
							      BaseDataObject *x,
							      DataObjectClass *xclass)
{
  return operator()(x,xclass);
}
 
/*F log = CompareLogicalDescriptions(logic,descr1,descr2,logdclass1,logdclass2)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataLogical *BaseDataLogicalDescriptionCompare::CompareLogicalDescriptions(BaseDataLogicDescription *descr1,
									       BaseDataLogicDescription *descr2,
									       DataLogicDescriptionClass *logdclass1,
									       DataLogicDescriptionClass *logdclass2)
{
  DataLogicalClass *logclass = logdclass1->getLogicClass();
  BaseDataLogical *logic = (BaseDataLogical *) logclass->BaseDataObjectExample();
  BaseDataLogical *tmplog = (BaseDataLogical *) logclass->BaseDataObjectExample();

  if(ORSet)
    logic->SetAbsoluteFalse();
  else
    logic->SetAbsoluteTrue();
  
  ObjectList<String> names1 = descr1->ListOfObjectNames();
  ObjectList<String> names2 = descr2->ListOfObjectNames();
  if(names1.size() == names2.size())
    {
      ObjectList<String>::iterator name1;
      ObjectList<String>::iterator name2 = names2.begin();
      for(name1 = names1.begin(); name1 != names1.end(); name1++)
	{
	  BaseDataLogical *l1 = (BaseDataLogical *) descr1->GetObject(*name1);
	  BaseDataLogical *l2 = (BaseDataLogical *) descr2->GetObject(*name2);
	  tmplog->SetValue(l1->GetValue());
	  if(ANDElement)
	    tmplog->AND(*l2);
	  else
	    tmplog->OR(*l2);
	  if(ORSet)
	    logic->OR(*tmplog);
	  else
	    logic->AND(*tmplog);

	  name2++;
	}
    }
  else
    {
      cerr << "Logic Value mismatch (returning false)" << endl;
      logic->SetAbsoluteFalse();
    }
  delete tmplog;
  return logic;
}
/*S DataLogicalDescriptionCompareClass
 */
/*F DataLogicalDescriptionCompareClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataLogicalDescriptionCompareClass::DataLogicalDescriptionCompareClass()
{
  Identification = PREDICATE_LOGCOMP_ID;
  NameTag = PREDICATE_LOGCOMP_NAME;
  SubClass = "Operation";
  EncodeDecodeClass = NameTag;
} 
/*F DataLogicalDescriptionCompareClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataLogicalDescriptionCompareClass::DataLogicalDescriptionCompareClass(const DataLogicalDescriptionCompareClass& data)
  : DataOperationClass(data)
{
} 
 
/*F DataLogicalDescriptionCompareClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataLogicalDescriptionCompareClass::DataLogicalDescriptionCompareClass(const int id, 
								       const String& name,
								       const String& descr)
  : DataOperationClass(id,name,descr)
{
  SubClass = "Operation";
  EncodeDecodeClass = PREDICATE_LOGCOMP_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataLogicalDescriptionCompareClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataLogicalDescriptionCompareClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataLogicalDescriptionCompareClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataLogicalDescriptionCompareClass, there is no further information.
**
**  REMARKS
**
*/
bool DataLogicalDescriptionCompareClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataOperationClass::Read(in,set);
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataLogicalDescriptionCompareClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataLogicalDescriptionCompareClass::CopyClone(Identify *  objc)
{
  DataLogicalDescriptionCompareClass *objcfull = (DataLogicalDescriptionCompareClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataLogicalDescriptionCompareClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataLogicalDescriptionCompareClass::Clone()
    {
      DataLogicalDescriptionCompareClass* id = new DataLogicalDescriptionCompareClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataLogicalDescriptionCompareClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLogicalDescriptionCompareClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataLogicalDescriptionCompareClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataLogicalDescriptionCompareClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataLogicalDescriptionCompareClass::BaseDataObjectExample()
{ 
  //cout << "Make LogicalDescriptionCompare Example\n";
  return (BaseDataObject *) new BaseDataLogicalDescriptionCompare();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataLogicalDescriptionCompareClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataLogicalDescriptionCompareClass*& obj)
     {
     obj = new DataLogicalDescriptionCompareClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataLogicalDescriptionCompare
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataLogicalDescriptionCompare*& obj)
     {
     obj = new BaseDataLogicalDescriptionCompare;
     return obj->DecodeThis(buffer);
     }
/*S Utilities
 */
extern void InitialSetOfPredicateEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataPredicateClass,BaseDataPredicate,PREDICATE_BASE_NAME);
  EncodeDecodeRegisterClass(DataDescriptionClass,BaseDataDescription,PREDICATE_DESCRIPTION_NAME);
  EncodeDecodeRegisterClass(DataLogicDescriptionClass,BaseDataLogicDescription,PREDICATE_LOGICDESCR_NAME);
  EncodeDecodeRegisterClass(DataPartitionClass,BaseDataPartition,PREDICATE_PARTITION_NAME);
  EncodeDecodeRegisterClass(DataPartitionTableClass,BaseDataPartitionTable,PREDICATE_PARTITIONTABLE_NAME);
  EncodeDecodeRegisterClass(DataConjunctionClass,BaseDataConjunction,PREDICATE_CONJUNCTION_NAME);
  EncodeDecodeRegisterClass(DataDisjunctionClass,BaseDataDisjunction,PREDICATE_DISJUNCTION_NAME);
  EncodeDecodeRegisterClass(DataSetOfLogicDescriptionsClass,BaseDataSetOfLogicDescriptions,PREDICATE_LOGICDESCRSET_NAME);
  EncodeDecodeRegisterClass(DataLogicalDescriptionCompareClass,BaseDataLogicalDescriptionCompare,PREDICATE_LOGCOMP_NAME);
}
