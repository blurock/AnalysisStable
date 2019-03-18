/*  FILE     RuleSystem.cc
**  PACKAGE  RuleSystem
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "RuleSystem" package.
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
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "EvaluationTree.hh"
#include "ExpressionTree.hh"
#include "ParameterizedFunction.hh"
#include "RuleSystem.hh"

/*S BaseDataActionRule
 */ 
/*F BaseDataActionRule()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataActionRule::BaseDataActionRule()
  : Condition(NULL),
    Actions(NULL),
    CutOff(0.5)
{
  Identification = RULESYSTEM_RULE_ID;
  NameTag = RULESYSTEM_RULE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataActionRule(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataActionRule::BaseDataActionRule(const BaseDataActionRule& data)
  : BaseDataParameterizedFunction(data),
    CutOff(data.CutOff)
{
  Condition = (BaseDataParameterizedFunction *) PointerClone(data.Condition);
  Actions = (BaseDataParameterSet *) PointerClone(data.Actions);
}
/*F ~BaseDataActionRule() . . . . . . . . . . . . . . . . . . . .  destructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataActionRule::~BaseDataActionRule()
{
  if(Condition != NULL)
    delete Condition;
  if(Actions != NULL)
    delete Actions;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataActionRule
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataActionRule::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataActionRule
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataActionRule::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = true;
  String actionrule("ActionRule:");
  result = result && CheckReadKeyWord(in,actionrule);
  result = result && BaseDataParameterizedFunction::Read(in,objc,name);

  String condition("ActionRuleCondition:");
  result = result && CheckReadKeyWord(in,condition);
  DataActionRuleClass *ruleclass = (DataActionRuleClass *) objc;

  String conditionnotdefined("The Condition Class has not been specified");
  cout << "Begin: ------ Condition Class -------------" << endl;
  ruleclass->getConditionClass()->print(cout);
  cout << endl << "End:  ------ Condition Class -------------" << endl;
  result = result && PointerObjectRead(in,(BaseDataObject *&) Condition,
				       ruleclass->getConditionClass(),
				       conditionnotdefined);

  String cutoff("CutOff:");
  result = result && CheckReadKeyWord(in,cutoff);
  StreamObjectInput str(in,' ');
  String cutoffs = str.ReadNext();
  CutOff = cutoffs.ToFloat();

  String set("ActionRuleSetOfActions:");
  result = result && CheckReadKeyWord(in,set);
  String actionnotdefined("The Set of Actions Class has not been specified");
  result = result && PointerObjectRead(in,(BaseDataObject *&) Actions,
				       ruleclass->getActionClass(),
				       actionnotdefined);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataActionRule
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataActionRule::print(ostream& out) const
{
  BaseDataParameterizedFunction::print(out);

  PointerPrint(out,"The Rule Condtions\n","Rule Conditions not specified",Condition);
  out << endl << "CutOff Criteria:" << CutOff << endl;
  PointerPrint(out,"The Rule Actions\n","Rule Actions not specified",Actions);
  out << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataActionRule
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataActionRule::Clone()
{
  BaseDataActionRule *obj = new BaseDataActionRule(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataActionRule
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataActionRule::CopyClone(Identify * obj)
{
  BaseDataActionRule *objfull = (BaseDataActionRule *) obj;
  *this = *objfull;
  Condition = (BaseDataParameterizedFunction *) PointerClone(objfull->Condition);
  Actions = (BaseDataParameterSet *) PointerClone(objfull->Actions);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataActionRule
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataActionRule::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataParameterizedFunction::EncodeThis(buffer);
  result = result && PointerEncode(buffer,(BaseDataObject *&) Condition);
  result = result && PointerEncode(buffer,(BaseDataObject *&) Actions);
  result = result && Encode(buffer,CutOff);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataActionRule
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataActionRule::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataParameterizedFunction::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Condition);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Actions);
  result = result && Decode(buffer,CutOff);
  return result;
}
 
 
/*F ans = AddAction(action) . . . . . . . . . . . . . . .  BaseDataActionRule
**
**  DESCRIPTION
**    action: action to add to action list
**    ans: True if successful
**    
**  REMARKS
**
*/
bool BaseDataActionRule::AddAction(BaseDataParameterizedFunction *action)
{
  return Actions->AddObject(action);
}
/*F ans = RemoveAction(action)
**
**  DESCRIPTION
**    action: The name of the action to remove from list
**    ans: True if successful
**    
**  REMARKS
**
*/
bool BaseDataActionRule::RemoveAction(String &action)
{
  return Actions->RemoveObject(action);
}
/*F condition = getCondition()  . . . . . . . . . . . . .  BaseDataActionRule
**
**  DESCRIPTION
**    condition: The condition within the rule
**
**  REMARKS
**
*/
BaseDataParameterizedFunction *BaseDataActionRule::getCondition()
{
  return Condition;
}
/*F setCondtion(condition)  . . . . . . . . . . . . . . .  BaseDataActionRule
**
**  DESCRIPTION
**    condition: The condition to be inserted (no copy made)
**
**  REMARKS
**
*/
void BaseDataActionRule::setCondition(BaseDataParameterizedFunction *condition)
{
  if(Condition != NULL)
    delete Condition;
  Condition = condition;
}
 
/*F ans = EvaluateCondition(cls,set,instance,setclass,instclass) BaseDataActionRule
**
**  DESCRIPTION
**    cls: The ActionRule class
**    set: The set of parameters for the condition
**    instance: The instance on which to perform the action
**    setclass: The set of class information from parameter set
**    instclass: The instance class
**
**    This evaluates the condition part of the rule.  The result is checked
**    to see that a logical type is returned.
**    
**  REMARKS
**
*/
BaseDataLogical *BaseDataActionRule::EvaluateCondition(DataActionRuleClass *cls,
						       BaseDataParameterSet *set,
						       BaseDataInstance *instance,
						       DataParameterSetClass *setclass,
						       DataInstanceClass *instclass)
{
  BaseDataLogical *logical;
  DataSetOfObjectsClass *setofobjects = instclass->DataInstanceClass::PointerToAllowedClasses();
  if(Condition != NULL)
    {
      if(instclass->getDebugLevel() > 2)
	{
	  cout << "EvaluateCondtion: " << endl;
	  Condition->print(cout);
	  cout << endl;
	}
      logical = (BaseDataLogical *) Condition->operator()(cls,set,instance,
							  setclass,instclass);
      if(logical != NULL) {
	/*
	  cout << "Condition Result: " << endl;
	  logical->print(cout);
	  cout << endl;
	  unsigned int ltype = logical->GetType();
	  cout << "DataType: " << ltype << endl;
	  DataObjectClass *oclass = setofobjects->GetObjectClass(logical->GetType());
	  cout << oclass->NameTag << endl;
	  oclass->print(cout);
	  cout << endl;
	  cout << "==============================================================================" << endl;
	  setofobjects->print(cout);
	  cout << endl << "==============================================================================" << endl;
	*/
	if(instclass->getDebugLevel() > 2) {
	  cout << "Condition Result: " << endl;
	  logical->print(cout);
	  cout << endl;
	}
	String logname(LOGICAL_BASE_NAME);
	if(!setofobjects->IsOfClass(*logical,logname)) {
	  cerr << "Condition operator did not yield a logical valued result" << endl;
	  logical->print(cerr);
	  cerr << endl;
	  cerr << endl << "Will yield 'false'" << endl;
	  logical = new BaseDataLogical();
	  logical->SetAbsoluteFalse();
	}
      } else {
	cerr << "Condition not able to be evaluated: yielding false" << endl;
	logical = new BaseDataLogical();
	logical->SetAbsoluteFalse();
      }
    } else {
    cerr << "Condition not specified yet -- yields 'false'" << endl;
    logical = new BaseDataLogical();
    logical->SetAbsoluteFalse();
  }
  return logical;
}
/*F ans = EvaluateAction(name,cls,inst,insts,iclass,isclass) BaseDataActionRule
**
**  DESCRIPTION
**    name: The name of the action to evaluate
**    cls: The ActionRule class
**    inst: The instance on which to perform the action
**    insts: The set of instances with attribute info (if needed)
**    iclass: The instance class
**    isclass: The set of instances class
**
**  REMARKS
**
*/
bool BaseDataActionRule::EvaluateAction(String &name,
					DataActionRuleClass *cls,
					BaseDataParameterSet *set,
					BaseDataInstance *instance,
					DataParameterSetClass *setclass,
					DataInstanceClass *instclass)
{
  bool result = true;
  BaseDataParameterizedFunction *action = (BaseDataParameterizedFunction *) Actions->GetObject(name);
  if(instclass->getDebugLevel() > 2)
    {
      cout << "Action:" << endl;
      action->print(cout);
      cout << endl;
    }
  unsigned int otype = action->GetType();
  DataParameterizedFunctionClass *oclass = (DataParameterizedFunctionClass *) 
    setclass->PointerToAllowedClasses()->GetObjectClass(otype);
  BaseDataObject *answer = action->operator()(oclass,set,instance,setclass,instclass);
  if(answer != NULL) {
    answer->NameTag = name;
    result = result && instance->AddObject(answer);
    delete answer;
  } else {
    cerr << "Action: " << name << " not performed" << endl;
    result = false;
  }
  return result;
}
/*F ans = EvaluateAllActions(cls,inst,insts,iclass,isclass) BaseDataActionRule
**
**  DESCRIPTION
**    cls: The ActionRule class
**    inst: The instance on which to perform the action
**    insts: The set of instances with attribute info (if needed)
**    iclass: The instance class
**    isclass: The set of instances class
**    
**  REMARKS
**
*/
bool BaseDataActionRule::EvaluateAllActions(DataActionRuleClass *cls,
					    BaseDataParameterSet *set,
					    BaseDataInstance *instance,
					    DataParameterSetClass *setclass,
					    DataInstanceClass *instclass)
{
  bool result = true;
  if(Actions!= NULL)
    {
      ObjectList<String> actions = Actions->OrderedListOfParameterNames();
      ObjectList<String>::iterator action;
      for(action = actions.begin();
	  action != actions.end() && result;
	  action++)
	{
	  result = EvaluateAction(*action,cls,set,instance,setclass,instclass);
	}
    }
  else
    {
      cerr << "Actions not specified: no action taken" << endl;
      result = false;
    }
  return result;
}
 
/*F ans = InitializeRule(cls)
**
**  DESCRIPTION
**    cls: The rule class information
**    ans: true if successful
**
**  REMARKS
**
*/
bool BaseDataActionRule::InitializeRule(DataActionRuleClass *cls,
					BaseDataParameterSet *globalparams)
{
  bool result = true;
  BaseDataParameterSet *ruleparameterset = (BaseDataParameterSet *) getParameterSet();
  Condition->InsertParameterSet(globalparams);
  Condition->InsertParameterSet(ruleparameterset);
  Condition->InsertParameterSet();
  if(Actions!= NULL)
    {
      ObjectList<String> actions = Actions->OrderedListOfParameterNames();
      ObjectList<String>::iterator actionname;
      for(actionname = actions.begin();
	  actionname != actions.end() && result;
	  actionname++)
	{
	  cout << "Action to Initialize: " << *actionname << endl;
	  BaseDataParameterizedFunction *action = (BaseDataParameterizedFunction *) Actions->GetObject(*actionname);
	  action->InsertParameterSet(globalparams);
	  action->InsertParameterSet(ruleparameterset);
	  action->InsertParameterSet();
	}
    }
  else
    {
      cerr << "Actions not specified" << endl;
      result = false;
    }
  return result;
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataObject *BaseDataActionRule::operator()(DataObjectClass *cls,
					       BaseDataObject *x, DataObjectClass *xclass)
{
  return (BaseDataObject *) x->Clone();
}
 
/*F operator()  . . . . . . . . . . . . . . . . . . . . .  BaseDataActionRule
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataObject *BaseDataActionRule::operator()(DataObjectClass *cls,
					       BaseDataObject *x, BaseDataObject *y,
					       DataObjectClass *xclass, DataObjectClass *yclass)
{
  DataActionRuleClass *rulecls = (DataActionRuleClass *) cls;
  BaseDataParameterSet *set = (BaseDataParameterSet *) x;
  BaseDataInstance *instance = (BaseDataInstance *) y;
  DataParameterSetClass *setclass = (DataParameterSetClass *) xclass;
  DataInstanceClass *instclass = (DataInstanceClass *) yclass;
  BaseDataLogical *logical = EvaluateCondition(rulecls,set,instance,setclass,instclass);
  if(ShouldActionBePerformed(logical))
    {
      EvaluateAllActions(rulecls,set,instance,setclass,instclass);
    }
  BaseDataObject *cost;
  String costS("Cost");
  if(instance->IsInList(costS))
    {
      cost = (BaseDataObject *) instance->GetObject(costS)->Clone();
    }
  else
    {
      cost = new BaseDataReal();
      BaseDataReal *rcost = (BaseDataReal *) cost;
      rcost->SetValue(10000000.0);
    }
  return cost;
}
 
/*F ans = ShouldActionBePerformed(logical)
**
**  DESCRIPTION
**    logical: The logical result from the Condition
**    ans: true/false interpretation
**
**  REMARKS
**
*/
bool BaseDataActionRule::ShouldActionBePerformed(BaseDataLogical *logical)
{
  bool result = false;
  if(logical->GetValue() > CutOff)
    result = true;
  return result;
}

/*S DataActionRuleClass
 */
/*F DataActionRuleClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataActionRuleClass::DataActionRuleClass()
  : ConditionClass(NULL),
    ActionClass(NULL)
{
  Identification = RULESYSTEM_RULE_ID;
  NameTag = RULESYSTEM_RULE_NAME;
  SubClass = "ParameterizedFunction";
  EncodeDecodeClass = NameTag;
} 
/*F DataActionRuleClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataActionRuleClass::DataActionRuleClass(const DataActionRuleClass& data)
  : DataParameterizedFunctionClass(data)
{
  ConditionClass = (DataParameterizedFunctionClass *) PointerClone(data.ConditionClass);
  ActionClass = (DataParameterSetClass *) PointerClone(data.ActionClass);
} 

/*F DataActionRuleClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataActionRuleClass::DataActionRuleClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataParameterizedFunctionClass(id,name,descr),
    ConditionClass(NULL),
    ActionClass(NULL)
{
  SubClass = "ParameterizedFunction";
  EncodeDecodeClass = RULESYSTEM_RULE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataActionRuleClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataActionRuleClass::print(ostream& out) const
{
  DataParameterizedFunctionClass::print(out);
  out << endl;
  PointerPrint(out,"Condition Class:","No Condition Class defined",ConditionClass);       
  out << endl;
  PointerPrint(out,"Set of Actions Class:","No Actions Class defined",ActionClass);       
  
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataActionRuleClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataActionRuleClass, there is no further information.
**
**  REMARKS
**
*/
bool DataActionRuleClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataParameterizedFunctionClass::Read(in,set);
  String conditiontype(PARAMETERIZED_FUNCTION_NAME);
  String conditionnotdefined("Condition Class");
  PointerClassRead(in,(DataObjectClass *&) ConditionClass,
		   conditiontype,set,conditionnotdefined);
  String actiontype(PARAMETERIZED_SET_NAME);
  String actionnotdefined("Set Of Action Class");
  PointerClassRead(in,(DataObjectClass *&) ActionClass,
		   actiontype,set,actionnotdefined);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataActionRuleClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataActionRuleClass::CopyClone(Identify *  objc)
{
  DataActionRuleClass *objcfull = (DataActionRuleClass *) objc;
  *this = *objcfull;
  ConditionClass = (DataParameterizedFunctionClass *) PointerClone(objcfull->ConditionClass);
  ActionClass = (DataParameterSetClass *) PointerClone(objcfull->ActionClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataActionRuleClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataActionRuleClass::Clone()
    {
      DataActionRuleClass* id = new DataActionRuleClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataActionRuleClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataActionRuleClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataParameterizedFunctionClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,(BaseDataObject *&) ConditionClass);
  result = result && PointerEncode(buffer,(BaseDataObject *&) ActionClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataActionRuleClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataActionRuleClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataParameterizedFunctionClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) ConditionClass);
  result = result && PointerDecode(buffer,(BaseDataObject *&) ActionClass);
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
BaseDataObject * DataActionRuleClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataActionRule();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataActionRuleClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataActionRuleClass*& obj)
     {
     obj = new DataActionRuleClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataActionRule
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataActionRule*& obj)
     {
     obj = new BaseDataActionRule;
     return obj->DecodeThis(buffer);
     } 
/*F condclass = getConditionClass() . . . . . . . . . . . DataActionRuleClass
**
**  DESCRIPTION
**    condclass: The current condition class
**
**  REMARKS
**
*/
DataParameterizedFunctionClass *DataActionRuleClass::getConditionClass()
{
  return ConditionClass;
}
/*F actclass = getActionClass() . . . . . . . . . . . . . DataActionRuleClass
**
**  DESCRIPTION
**    actclass: The set of actions class
**
**  REMARKS
**
*/
DataParameterSetClass *DataActionRuleClass::getActionClass()
{
  return ActionClass;
}
/*S BaseDataExecuteActionRule
 */ 
/*F BaseDataExecuteActionRule()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataExecuteActionRule::BaseDataExecuteActionRule()
  : actionRuleS("Rule"),
    TrainInstanceNamesS("TrainInstanceNameList")
{
  Identification = RULESYSTEM_RULEEXE_ID;
  NameTag = RULESYSTEM_RULEEXE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataExecuteActionRule(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataExecuteActionRule::BaseDataExecuteActionRule(const BaseDataExecuteActionRule& data)
  : BaseDataAlgorithmOperation(data),
    actionRuleS(data.actionRuleS),
    TrainInstanceNamesS(data.TrainInstanceNamesS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataExecuteActionRule
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataExecuteActionRule::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataExecuteActionRule
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataExecuteActionRule::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataExecuteActionRule
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataExecuteActionRule::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataExecuteActionRule
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataExecuteActionRule::Clone()
{
  BaseDataExecuteActionRule *obj = new BaseDataExecuteActionRule(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataExecuteActionRule
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataExecuteActionRule::CopyClone(Identify * obj)
{
  BaseDataExecuteActionRule *objfull = (BaseDataExecuteActionRule *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataExecuteActionRule
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExecuteActionRule::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataExecuteActionRule
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataExecuteActionRule::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  // The rest

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
bool BaseDataExecuteActionRule::SetUpAlgorithms(BaseDataSetOfInstances*,
						      DataSetOfInstancesClass*,
						      BaseDataAlgorithmRun* ,
						      DataAlgorithmRunClass*)
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
bool BaseDataExecuteActionRule::CheckInput(BaseDataSetOfInstances*,
					   DataSetOfInstancesClass*,
					   BaseDataAlgorithmRun *run,
					   DataAlgorithmRunClass*)
{
  bool result = true;

  if(run->ParameterInList(actionRuleS))
    {
      if(run->ParameterInList(TrainInstanceNamesS))
	{
	}
      else
	{
	  cerr << "The parameter '" << TrainInstanceNamesS << "' was not in the list of parameters";
	  result = false;
	}
    }
  else
    {
      cerr << "The parameter '" << actionRuleS << "' was not in the list of parameters";
      result = false;
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
bool BaseDataExecuteActionRule::SetUpInput(BaseDataSetOfInstances* instances,
					   DataSetOfInstancesClass* instancesclass,
					   BaseDataAlgorithmRun *run,
					   DataAlgorithmRunClass* rclass)
{
  bool result = true;

  actionRule = (BaseDataActionRule *) run->ParameterValue(actionRuleS);
  TrainInstanceNames = (BaseDataKeyWords *) run->ParameterValue(TrainInstanceNamesS);
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
bool BaseDataExecuteActionRule::Calculate(BaseDataSetOfInstances *instances,
					  DataSetOfInstancesClass *instsclass,
					  BaseDataAlgorithmRun*,
					  DataAlgorithmRunClass*)
{
  bool result = true;
  DataInstanceClass *instclass = (DataInstanceClass *) 
    instsclass->PointerToAllowedClasses()->GetObjectClass(INSTANCE_INSTANCE_ID);
  DataParameterSetClass *setclass = (DataParameterSetClass *) 
    instsclass->PointerToAllowedClasses()->GetObjectClass(PARAMETERIZED_SET_ID);
  DataActionRuleClass *pfuncclass = (DataActionRuleClass *) 
    instsclass->PointerToAllowedClasses()->GetObjectClass(actionRule->GetType());
  BaseDataParameterSet *set = actionRule->getParameterSet();
  actionRule->InitializeRule(pfuncclass,set);
  ObjectList<String> instnames = TrainInstanceNames->GetKeyWords();
  ObjectList<String>::iterator name;
  for(name = instnames.begin();name != instnames.end();name++)
    {
      cout << "Instance: " << *name << endl;
      BaseDataInstance *instance = (BaseDataInstance *) instances->GetInstance(*name);
      actionRule->operator()(pfuncclass,set,instance,setclass,instclass);
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
bool BaseDataExecuteActionRule::WriteOutputValues(BaseDataSetOfInstances*,
							DataSetOfInstancesClass*,
							BaseDataAlgorithmRun* run,
							DataAlgorithmRunClass*)
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
bool BaseDataExecuteActionRule::ConcludeRun(BaseDataSetOfInstances*,
						  DataSetOfInstancesClass*,
						  BaseDataAlgorithmRun*,
						  DataAlgorithmRunClass*)
{
  bool result = true;
//  delete something
  return result;
}
 
/*S DataExecuteActionRuleClass
 */
/*F DataExecuteActionRuleClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataExecuteActionRuleClass::DataExecuteActionRuleClass()
{
  Identification = RULESYSTEM_RULEEXE_ID;
  NameTag = RULESYSTEM_RULEEXE_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataExecuteActionRuleClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataExecuteActionRuleClass::DataExecuteActionRuleClass(const DataExecuteActionRuleClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataExecuteActionRuleClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataExecuteActionRuleClass::DataExecuteActionRuleClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = RULESYSTEM_RULEEXE_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataExecuteActionRuleClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataExecuteActionRuleClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataExecuteActionRuleClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataExecuteActionRuleClass, there is no further information.
**
**  REMARKS
**
*/
bool DataExecuteActionRuleClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataExecuteActionRuleClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataExecuteActionRuleClass::CopyClone(Identify *  objc)
{
  DataExecuteActionRuleClass *objcfull = (DataExecuteActionRuleClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataExecuteActionRuleClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataExecuteActionRuleClass::Clone()
    {
      DataExecuteActionRuleClass* id = new DataExecuteActionRuleClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataExecuteActionRuleClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataExecuteActionRuleClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataExecuteActionRuleClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataExecuteActionRuleClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataExecuteActionRuleClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj =  new BaseDataExecuteActionRule();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataExecuteActionRuleClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataExecuteActionRuleClass*& obj)
     {
     obj = new DataExecuteActionRuleClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataExecuteActionRule
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataExecuteActionRule*& obj)
     {
     obj = new BaseDataExecuteActionRule;
     return obj->DecodeThis(buffer);
     }

/*S BaseDataSetOfRules
 */ 
/*F BaseDataSetOfRules()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSetOfRules::BaseDataSetOfRules()
{
  Identification = RULESYSTEM_RULESET_ID;
  NameTag = RULESYSTEM_RULESET_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataSetOfRules(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataSetOfRules::BaseDataSetOfRules(const BaseDataSetOfRules& data)
  : BaseDataParameterSet(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataSetOfRules
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataSetOfRules::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataSetOfRules
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataSetOfRules::Read(istream& in, DataObjectClass* objc, const String& name)
{
  String key("SetOfRules:");
  CheckReadKeyWord(in,key);
  bool result = BaseDataParameterSet::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataSetOfRules
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataSetOfRules::print(ostream& out) const
{
  BaseDataParameterSet::print(out);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataSetOfRules
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataSetOfRules::Clone()
{
  BaseDataSetOfRules *obj = new BaseDataSetOfRules;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataSetOfRules
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataSetOfRules::CopyClone(Identify * obj)
{
  BaseDataSetOfRules *objfull = (BaseDataSetOfRules *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSetOfRules
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSetOfRules::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataParameterSet::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSetOfRules
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSetOfRules::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataParameterSet::DecodeThis(buffer);
  // The rest

  return result;
}
 
 
/*S DataSetOfRulesClass
 */
/*F DataSetOfRulesClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataSetOfRulesClass::DataSetOfRulesClass()
{
  Identification = RULESYSTEM_RULESET_ID;
  NameTag = RULESYSTEM_RULESET_NAME;
  SubClass = "ParameterSet";
  EncodeDecodeClass = NameTag;
} 
/*F DataSetOfRulesClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataSetOfRulesClass::DataSetOfRulesClass(const DataSetOfRulesClass& data)
  : DataParameterSetClass(data)
{
} 
 
/*F DataSetOfRulesClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataSetOfRulesClass::DataSetOfRulesClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataParameterSetClass(id,name,descr)
{
  SubClass = "ParameterSet";
  EncodeDecodeClass = RULESYSTEM_RULESET_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataSetOfRulesClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataSetOfRulesClass::print(ostream& out) const
{
  DataParameterSetClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataSetOfRulesClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataSetOfRulesClass, there is no further information.
**
**  REMARKS
**
*/
bool DataSetOfRulesClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataParameterSetClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataSetOfRulesClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataSetOfRulesClass::CopyClone(Identify *  objc)
{
  DataSetOfRulesClass *objcfull = (DataSetOfRulesClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataSetOfRulesClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataSetOfRulesClass::Clone()
    {
      DataSetOfRulesClass* id = new DataSetOfRulesClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataSetOfRulesClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSetOfRulesClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataParameterSetClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataSetOfRulesClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSetOfRulesClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataParameterSetClass::DecodeThis(buffer);
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
BaseDataObject * DataSetOfRulesClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataSetOfRules();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataSetOfRulesClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataSetOfRulesClass*& obj)
     {
     obj = new DataSetOfRulesClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataSetOfRules
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataSetOfRules*& obj)
     {
     obj = new BaseDataSetOfRules;
     return obj->DecodeThis(buffer);
     }
/*F objc = PointerToAllowedClasses()  . . . .  the allowed set of class types
**
**  DESCRIPTION
**    objc: The pointer to the allowed classes
**  REMARKS
**
*/
DataSetOfObjectsClass*  DataSetOfRulesClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}
/*F ans = InitializeDataOnNode(instance)  . . . DataProductionSystemNodeClass
**
**  DESCRIPTION
**    instance: The initial data
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataProductionSystemNode::InitializeDataOnNode(BaseDataInstance *instance)
{
  bool result = true;
  Data = (BaseDataInstance *) instance->Clone();
  return result;
}

/*S BaseDataProductionSystemNode
 */ 
/*F BaseDataProductionSystemNode()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataProductionSystemNode::BaseDataProductionSystemNode()
  : Data(NULL),
    HeuristicValue(0.0),
    Level(0.0),
    LogicCost(0.0),
    RuleConditionValues(NULL)
     
{
  Identification = RULESYSTEM_PRODNODE_ID;
  NameTag = RULESYSTEM_PRODNODE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataProductionSystemNode(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataProductionSystemNode::BaseDataProductionSystemNode(const BaseDataProductionSystemNode& data)
  : BaseDataTreeNode(data),
    HeuristicValue(data.HeuristicValue),
    Level(data.Level),
    LogicCost(data.LogicCost)
{
  Data = (BaseDataInstance *) PointerClone(data.Data);
  RuleConditionValues = (BaseDataSetOfObjects *) PointerClone(data.RuleConditionValues);
}
 
/*F~BaseDataProductionSystemNode()  . . . . . .  BaseDataProductionSystemNode
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataProductionSystemNode::~BaseDataProductionSystemNode()
{
  if(Data)
    delete Data;
  if(RuleConditionValues)
    delete RuleConditionValues;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataProductionSystemNode
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataProductionSystemNode::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataProductionSystemNode
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataProductionSystemNode::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataTreeNode::Read(in,objc,name);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataProductionSystemNode
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataProductionSystemNode::print(ostream& out) const
{
  BaseDataTreeNode::print(out);
  String title("Data for Node");
  String noobject("No Data Defined for Node");
  PointerPrint(out,title,noobject,Data);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataProductionSystemNode
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataProductionSystemNode::Clone()
{
  BaseDataProductionSystemNode *obj = new BaseDataProductionSystemNode(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataProductionSystemNode
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataProductionSystemNode::CopyClone(Identify * obj)
{
  BaseDataProductionSystemNode *objfull = (BaseDataProductionSystemNode *) obj;
  *this = *objfull;
  Data = (BaseDataInstance *) PointerClone(objfull->Data);
  RuleConditionValues = (BaseDataSetOfObjects *) PointerClone(objfull->RuleConditionValues);
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataProductionSystemNode
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataProductionSystemNode::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataTreeNode::EncodeThis(buffer);
  result = result && Encode(buffer,HeuristicValue);
  result = result && Encode(buffer,Level);
  result = result && Encode(buffer,LogicCost);
  result = result && Encode(buffer,RuleUsed);
  result = result && PointerEncode(buffer,Data);
  result = result && PointerEncode(buffer,RuleConditionValues);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataProductionSystemNode
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataProductionSystemNode::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataTreeNode::DecodeThis(buffer);
  result = result && Decode(buffer,HeuristicValue);
  result = result && Decode(buffer,Level);
  result = result && Decode(buffer,LogicCost);
  result = result && Decode(buffer,RuleUsed);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Data);
  result = result && PointerDecode(buffer,(BaseDataObject *&) RuleConditionValues);
  return result;
}
/*F value = GetHeuristicValue() . . . . . . . .  BaseDataProductionSystemNode
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
double BaseDataProductionSystemNode::GetHeuristicValue()
{
  return HeuristicValue;
}
 
/*F SetHeuristicValue(value)  . . . . . . . . .  BaseDataProductionSystemNode
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataProductionSystemNode::SetHeuristicValue(double value)
{
  HeuristicValue = value;
}
/*F level = GetLevel()  . . . . . . . . . . . .  BaseDataProductionSystemNode
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
double BaseDataProductionSystemNode::GetLevel()
{
  return Level;
}
 
/*F SetLevel(value) . . . . . . . . . . . . . .  BaseDataProductionSystemNode
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataProductionSystemNode::SetLevel(double value)
{
  Level = value;
}
 
/*F data = GetData()  . . . . . . . . . . . . . . BaseDataProductionSystemNod
**
**  DESCRIPTION
**    data: The current data set of the node
**  REMARKS
**
*/
BaseDataInstance *BaseDataProductionSystemNode::GetData()
{
  return Data;
}
/*F out = PrintASCIINodeInfo(out,node,prefix,treeclass,nodeclass,instances,instsclass)
**
**  DESCRIPTION
**    out: The output stream
**    node: The node to be printed
**    prefix: The ASCII prefix for the node
**    treeclass: The directed tree class
**    nodeclass: The node class
**    instances: The set of instances
**    instsclass: The instances class
**    
**  REMARKS
**
*/
ostream& BaseDataProductionSystemNode::PrintASCIINodeInfo(ostream& out,
							  String& prefix,
							  DataDirectedTreeClass *,
							  DataObjectClass *,
							  BaseDataSetOfInstances&,
							  DataSetOfInstancesClass&)
{
  out << prefix;
  out << getPrintName();
  out << "  (" << HeuristicValue << ", " << LogicCost << ") ";
  out << RuleUsed << " -> ";
  if(Data->IsInList("Cost"))
    {
      BaseDataReal *num = (BaseDataReal *) Data->GetObject("Cost");
      out << num->GetValue() << " ";
    }
  else
    {
      out << " (no cost) ";
    }
  out << endl;
  return out;
}
 
/*S DataProductionSystemNodeClass
 */
/*F DataProductionSystemNodeClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataProductionSystemNodeClass::DataProductionSystemNodeClass()
  : DataClass(NULL)
{
  Identification = RULESYSTEM_PRODNODE_ID;
  NameTag = RULESYSTEM_PRODNODE_NAME;
  SubClass = "TreeNode";
  EncodeDecodeClass = NameTag;
} 
/*F DataProductionSystemNodeClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataProductionSystemNodeClass::DataProductionSystemNodeClass(const DataProductionSystemNodeClass& data)
  : DataTreeNodeClass(data)
{
  DataClass = (DataInstanceClass *) PointerClone(data.DataClass);
} 
 
/*F DataProductionSystemNodeClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataProductionSystemNodeClass::DataProductionSystemNodeClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataTreeNodeClass(id,name,descr),
    DataClass(NULL)
{
  SubClass = "TreeNode";
  EncodeDecodeClass = "ProductionSystemNode";
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataProductionSystemNodeClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataProductionSystemNodeClass::print(ostream& out) const
{
  DataTreeNodeClass::print(out);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataProductionSystemNodeClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataProductionSystemNodeClass, there is no further information.
**
**  REMARKS
**
*/
bool DataProductionSystemNodeClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataTreeNodeClass::Read(in,set);
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataProductionSystemNodeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataProductionSystemNodeClass::CopyClone(Identify *  objc)
{
  DataProductionSystemNodeClass *objcfull = (DataProductionSystemNodeClass *) objc;
  *this = *objcfull;
  DataClass = (DataInstanceClass *) PointerClone(objcfull->DataClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataProductionSystemNodeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataProductionSystemNodeClass::Clone()
    {
      DataProductionSystemNodeClass* id = new DataProductionSystemNodeClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataProductionSystemNodeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataProductionSystemNodeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataTreeNodeClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,DataClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataProductionSystemNodeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataProductionSystemNodeClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataTreeNodeClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) DataClass);
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
BaseDataObject * DataProductionSystemNodeClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataProductionSystemNode();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataProductionSystemNodeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataProductionSystemNodeClass*& obj)
     {
     obj = new DataProductionSystemNodeClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataProductionSystemNode
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataProductionSystemNode*& obj)
     {
     obj = new BaseDataProductionSystemNode;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataProductionSystem
 */ 
/*F BaseDataProductionSystem()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataProductionSystem::BaseDataProductionSystem()
  : Rules(NULL),
    //GoalStateCondition(NULL),
    Tree(NULL),
    Costs(NULL), 
    CostParameter("Cost"),
    GeneratedNodesS("GeneratedNodes"),
    GeneratedNodeS("GeneratedNode"),
    MaximumNumberOfGoals(0),
    MaximumNumberOfNodes(0),
    BreadthFirst(false),
    DepthFirst(false),
    HeuristicSearch(true)
{
  Identification = RULESYSTEM_SYSTEM_ID;
  NameTag = RULESYSTEM_SYSTEM_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  String delim("\n");
  String title("The Goal Nodes\n");
  GoalNodes.ChangeTitle(title);
  GoalNodes.ChangeDelimitor(delim);
} 
/*F BaseDataProductionSystem(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataProductionSystem::BaseDataProductionSystem(const BaseDataProductionSystem& data)
  : BaseDataParameterizedExpression(data),
    OpenNodes(data.OpenNodes),
    GoalNodes(data.GoalNodes),
    CostParameter(data.CostParameter),
    GeneratedNodesS(data.GeneratedNodesS),
    GeneratedNodeS(data.GeneratedNodeS),
    GoalResultNames(data.GoalResultNames),
    MaximumNumberOfGoals(data.MaximumNumberOfGoals),
    MaximumNumberOfNodes(data.MaximumNumberOfNodes),
    BreadthFirst(data.BreadthFirst),
    DepthFirst(data.DepthFirst),
    HeuristicSearch(data.HeuristicSearch)
{
  Rules = (BaseDataSetOfRules *) PointerClone(data.Rules);
  //GoalStateCondition = (BaseDataParameterizedFunction *) PointerClone(data.GoalStateCondition);
  Tree = (BaseDataDirectedTree *) PointerClone(data.Tree);
  Costs = (BaseDataSetOfObjects *) PointerClone(data.Costs);
}
 
/*F ~BaseDataProductionSystem()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataProductionSystem::~BaseDataProductionSystem()
{
  if(Rules)
    delete Rules;
  //if(GoalStateCondition)
  //delete GoalStateCondition;
  if(Tree)
    delete Tree;
  if(Costs)
    delete Costs;
}

/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataProductionSystem
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataProductionSystem::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataProductionSystem
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataProductionSystem::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = true;
  StreamObjectInput str(in,' ');

  DataProductionSystemClass *prodclass = (DataProductionSystemClass *) objc;
  String notdefined("The Rules Class not defined yet");
  String condnotdefined("The Goal State Condition Class not defined yet");

  String key0("ProductionSystem:");
  CheckReadKeyWord(in,key0);

  String key1("GeneratedNode:");
  CheckReadKeyWord(in,key1);
  GeneratedNodeS = str.ReadNext();

  String key2("NumberOfGoals:");
  CheckReadKeyWord(in,key2);
  String countS = str.ReadNext();
  MaximumNumberOfGoals = countS.ToInteger();

  String key3("GoalResults:");
  CheckReadKeyWord(in,key3);
  DataKeyWordsClass *keyclass = new DataKeyWordsClass();
  GoalResultNames.Read(in,keyclass,NameTag);

  String key("GoalCondition:");
  CheckReadKeyWord(in,key);
  result = result && BaseDataParameterizedExpression::Read(in,objc,name);
  //result = result && PointerObjectRead(in,(BaseDataObject *&) GoalStateCondition,
  //(DataObjectClass *) prodclass->getGoalStateConditionClass(),
  //condnotdefined);
  result = result && PointerObjectRead(in,(BaseDataObject *&) Rules,
				       (DataObjectClass *) prodclass->getRulesClass(),
				       notdefined);
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataProductionSystem
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataProductionSystem::print(ostream& out) const
{
    if(GoalNodes.size() == 0)
	{
	    out << "Production System Not run yet" << endl;
	    out << "Goal Condition:" << endl;
	    GoalNodes.print(out);
	    out << endl;
	    ObjectList<String> rulenames = Rules->ListOfObjectNames();
	    out << "Rules:" << endl;
	    rulenames.print(out);
	    out << endl;
	}
    else
	{
	    GoalNodes.print(out);
	    out << endl;
	}
    return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataProductionSystem
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataProductionSystem::Clone()
{
  BaseDataProductionSystem *obj = new BaseDataProductionSystem(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataProductionSystem
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataProductionSystem::CopyClone(Identify * obj)
{
  BaseDataProductionSystem *objfull = (BaseDataProductionSystem *) obj;
  *this = *objfull;
  BaseDataParameterizedExpression::CopyClone(obj);
  Rules = (BaseDataSetOfRules *) PointerClone(objfull->Rules);
  //GoalStateCondition = (BaseDataParameterizedFunction *) PointerClone(objfull->GoalStateCondition);
  Tree = (BaseDataDirectedTree *) PointerClone(objfull->Tree);
  Costs = (BaseDataSetOfObjects *) PointerClone(objfull->Costs);
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataProductionSystem
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataProductionSystem::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataParameterizedExpression::EncodeThis(buffer);
  result = result && PointerEncode(buffer,(BaseDataObject *&) Rules);
  //result = result && PointerEncode(buffer,(BaseDataObject *&) GoalStateCondition);
  result = result && Encode(buffer,GeneratedNodesS);
  result = result && Encode(buffer,GeneratedNodeS);
  result = result && Encode(buffer,CostParameter);
  result = result && Encode(buffer,GoalResultNames);
  result = result && Encode(buffer,MaximumNumberOfGoals);
  result = result && Encode(buffer,MaximumNumberOfNodes);
  result = result && OpenNodes.EncodeThis(buffer);
  result = result && GoalNodes.EncodeThis(buffer);
  result = result && PointerEncode(buffer,(BaseDataObject *&) Tree);
  result = result && PointerEncode(buffer,(BaseDataObject *&) Costs);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataProductionSystem
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataProductionSystem::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataParameterizedExpression::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Rules);
  //result = result && PointerDecode(buffer,(BaseDataObject *&) GoalStateCondition);
  result = result && Decode(buffer,GeneratedNodesS);
  result = result && Decode(buffer,GeneratedNodeS);
  result = result && Decode(buffer,CostParameter);
  result = result && Decode(buffer,GoalResultNames);
  result = result && Decode(buffer,MaximumNumberOfGoals);
  result = result && Decode(buffer,MaximumNumberOfNodes);
  result = result && OpenNodes.DecodeThis(buffer);
  result = result && GoalNodes.DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Tree);
  result = result && PointerDecode(buffer,(BaseDataObject *&) Costs);
  return result;
}
/*F ans = SystemInitialization(prodclass) . . . . .  BaseDataProductionSystem
**
**  DESCRIPTION
**    prodclass: The production system class
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataProductionSystem::SystemInitialization(DataProductionSystemClass *prodclass,
						    BaseDataSetOfObjects *instance)
{
  bool result = true;

  DataDirectedTreeClass *tclass = prodclass->getTreeClass();
  Tree = (BaseDataDirectedTree *) tclass->BaseDataObjectExample();
  String start("Start");
  Tree->SetRootNode(start);
  Costs = new BaseDataSetOfObjects();

  //BaseDataParameterSet *parameters = GoalStateCondition->getParameterSet();
  BaseDataParameterSet *parameters = getParameterSet();
  cout << "BaseDataProductionSystem::SystemInitialization" << endl;
  parameters->print(cout);
  cout << endl;
  //GoalStateCondition->InsertParameterSet(parameters);
  InsertParameterSet(parameters);
  InsertParameterSet();
  DataSetOfObjectsClass *objclasses = prodclass->getRulesClass()->PointerToAllowedClasses();
  BaseDataActionRule *rule;
  DataActionRuleClass *ruleclass;
  ObjectList<String> rulenames = Rules->OrderedListOfParameterNames();
  ObjectList<String>::iterator rulename;
  for(rulename = rulenames.begin();
      rulename != rulenames.end();
      rulename++)
    {
	if(prodclass->getDebugLevel() > 3 )
	    cout << "Initialize Rule: " << *rulename << endl;
	rule = (BaseDataActionRule *) Rules->GetObject(*rulename);
	ruleclass = (DataActionRuleClass *) objclasses->GetObjectClass(rule->GetType());
	if(prodclass->getDebugLevel() > 4)
	    {
		cout << "Rule To Initialize:" << endl;
		rule->print(cout);
		cout << endl;
	    }
	rule->InitializeRule(ruleclass,parameters);
    }
  return result;
}
/*F ans = SetUpRootNode(prodclass,instance) . . . .  BaseDataProductionSystem
**
**  DESCRIPTION
**    prodclass: The production system class
**    instance: The instance to initialize production system
**    ans: true if successful
**
**  REMARKS
**
*/
bool BaseDataProductionSystem::SetUpRootNode(DataProductionSystemClass *prodclass,
					     BaseDataInstance *instance)
{
  bool result = true;
  DataProductionSystemNodeClass *nclass = (DataProductionSystemNodeClass *) prodclass->getNodeClass();
  BaseDataProductionSystemNode *node = (BaseDataProductionSystemNode *) nclass->BaseDataObjectExample();

  node->NameTag = Tree->getRootNodeName();

  Tree->AddNode(node);
  delete node;
  node = (BaseDataProductionSystemNode *) Tree->getRootNode();

  node->SetLevel(0.0);
  node->RuleConditionValues = new BaseDataSetOfObjects();
  result = result && node->InitializeDataOnNode(instance);
  result = result && SetHeuristicValueOnNode(node,NULL);
  result = result && AddToOpenOrGoalList(prodclass,node,NULL);
  return result;
}
/*F ans = SetUpNewNode(prodclass,assignedcost,original) BaseDataProductionSystem
**
**  DESCRIPTION
**    prodclass: The production system class information
**    assignedcost: The heuristic value of the node alone
**    original: The parent node from which it stems
**
**  REMARKS
**
*/
BaseDataProductionSystemNode *BaseDataProductionSystem::SetUpNewNode(DataProductionSystemClass *prodclass,
								     BaseDataProductionSystemNode *original)
{
  DataProductionSystemNodeClass *nclass = (DataProductionSystemNodeClass *) prodclass->getNodeClass();
  BaseDataProductionSystemNode *node = (BaseDataProductionSystemNode *) nclass->BaseDataObjectExample();

  node->NameTag = Tree->SetNewNodeName(node,original->NameTag);
  String newnodename = node->NameTag;
  Tree->AddNode(node);
  delete node;
  node = (BaseDataProductionSystemNode *) Tree->GetNode(newnodename);

  node->SetLevel(1.0 + original->GetLevel());
  node->InitializeDataOnNode(original->GetData());
  node->RuleConditionValues = new BaseDataSetOfObjects();
  Tree->AddConnection(original->NameTag,node->NameTag);
  return node;
}
					      
/*F ans = RunProductionSystem(prodclass,instance)  .  BaseDataProductionSystem
**
**  DESCRIPTION
**    prodclass: The production system class
**    instance: The instance on which to perform the set of rules
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataProductionSystem::RunProductionSystem(DataProductionSystemClass *prodclass,
						   BaseDataInstance *instance)
{
  bool result = true;
  if(prodclass->getDebugLevel() > 0)
      cout << "Begin:      SystemInitialization" << endl;
  //for(unsigned int i=0;i<10000;i++)
  //result = result && SystemInitialization(prodclass,instance);
  result = result && SystemInitialization(prodclass,instance);
  cout << "End:        SystemInitialization" << endl;

  result = result && SetUpRootNode(prodclass,instance);
  unsigned int nodecount = 0;

  bool notdone = true;

  while(OpenNodesNotEmpty() && result && notdone)
    {
      String nextnode = ChooseNextOpenNode();
      if(prodclass->getDebugLevel() > 0)
	cout << "Expand Node: '" << nextnode << "'" << endl;
      BaseDataProductionSystemNode *node = (BaseDataProductionSystemNode *) Tree->GetNode(nextnode);
      if(prodclass->getDebugLevel() > 1)
	{      
	  node->GetData()->WriteAsASCII(cout,new DataInstanceClass());
	  cout << endl;
	}

      result = result && ExpandNode(prodclass,node);
      nodecount++;
      if(nodecount > MaximumNumberOfNodes)
	{
	  cout << "Maximum Number of Nodes reached (" << MaximumNumberOfNodes << ")" << endl;
	  result = false;
	}
      if(GoalNodes.size() >= MaximumNumberOfGoals)
	{
	  notdone = false;
	}
    }

  if(prodclass->getDebugLevel() > 0)
    cout << "RunProductionSystem: Finished" << endl;
  if(prodclass->getDebugLevel() > 0)
    {
      cout << "Goal Nodes: ";
      GoalNodes.print(cout);
      cout << endl;
    }

  return result;
}
 
/*F ans = AddToOpenOrGoalList(node) . . . . . . . . . . . .  BaseDataProductionSystem
**
**  DESCRIPTION
**    node: The node to add to the open list
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataProductionSystem::AddToOpenOrGoalList(DataProductionSystemClass *prodclass,
						   BaseDataProductionSystemNode *node,
						   BaseDataProductionSystemNode *parent)
{
  bool result = true;
  if(IsAGoalNode(prodclass,node))
    {
      if(prodclass->getDebugLevel() > 0)
	cout << "Goal Node Found: '" << node->NameTag << "'" << endl;
      GoalNodes.AddObject(node->NameTag);
    }
  else
    {
      if(prodclass->getDebugLevel() > 0)
	cout << "Add Node To Open List: '" << node->NameTag << "'" << endl;
      EvaluateRuleConditions(prodclass,node);
      OpenNodes.AddObject(node->NameTag);
    }
  return result;
}
 
/*F ans = IsAGoalNode(prodclass,node)
**
**  DESCRIPTION
**    prodclass: The production system class information
**    node: The node information
**    ans: True if the node is a goal node
**
**  REMARKS
**
*/
bool BaseDataProductionSystem::IsAGoalNode(DataProductionSystemClass *prodclass,
					   BaseDataProductionSystemNode *node)
{
  bool result = true;
  DataSetOfObjectsClass *objclasses = prodclass->getRulesClass()->PointerToAllowedClasses();
  BaseDataInstance *instance = node->GetData();
  DataInstanceClass *instclass = (DataInstanceClass *) objclasses->GetObjectClass(INSTANCE_INSTANCE_ID);
  BaseDataParameterSet set;
  DataParameterSetClass setclass;
  if(prodclass->getDebugLevel() > 1)
    {
      cout << "Evaluate Goal Condtion: " << endl;
      //GoalStateCondition->print(cout);
      //cout << endl;
      //cout << "Goal State Condition Class" << endl;
      //prodclass->getGoalStateConditionClass()->print(cout);
      //cout << endl;
      cout << "The Instance:" << endl;
      instance->print(cout);
      cout << endl;
      cout << "The Instance:" << endl;
      instclass->print(cout);
      cout << endl;
    }

  //BaseDataLogical *logic = (BaseDataLogical *) GoalStateCondition->operator()(prodclass->getGoalStateConditionClass(),
  //&set,instance,&setclass,instclass);
  BaseDataLogical *logic = (BaseDataLogical *) operator()(prodclass->getOperationClass(),
							  &set,instance,&setclass,instclass);
  if(logic != NULL)
    {
      if(prodclass->getDebugLevel() > 1)
	{
	  cout << "Goal Condition Result:" << endl;
	  logic->print(cout);
	  cout << endl;
	}
      result = false;
      if(logic->GetValue() > 0.5)
	result = true;
      delete logic;
    }
  else
    {
      cerr << "No Logic Value: assuming false" << endl;
      result = false;
    }
  return result;
}				   
/*F nodename = ChooseNextOpenNode() . . . . . . . .  BaseDataProductionSystem
**
**  DESCRIPTION
**    nodename: The next node to process
**
**  REMARKS
**
*/
String BaseDataProductionSystem::ChooseNextOpenNode()
{
  String next = NonDeterministicChoice(Costs);
  if(!Costs->IsInList(next))
    {
      cerr << "Something amiss in Choose Next Open Node" << endl;
      Costs->print(cerr);
      cerr << endl;
    }
  return next;
}
 
/*F notempty = OpenNodesNotEmpty()  . . . . . . . .  BaseDataProductionSystem
**
**  DESCRIPTION
**    notempty: True if more nodes to expand
**
**  REMARKS
**
*/
bool BaseDataProductionSystem::OpenNodesNotEmpty()
{
  return OpenNodes.size() > 0;
}
 
/*F ans = ExpandNode(node,rules)
**
**  DESCRIPTION
**    nodes: The node to expand
**    rules: The set of rules
**  REMARKS
**
*/
bool BaseDataProductionSystem::ExpandNode(DataProductionSystemClass *prodclass,
					  BaseDataProductionSystemNode *node)
{
  bool result = true;
  double lcost = 0.0;
  String chosen = NonDeterministicChoice(node->RuleConditionValues);
  if(node->RuleConditionValues->IsInList(chosen))
    {
      BaseDataReal *logcost = (BaseDataReal *) node->RuleConditionValues->GetObject(chosen);
      lcost = logcost->GetValue();
      node->RuleConditionValues->RemoveObject(chosen);
      if(prodclass->getDebugLevel() > 0)
	cout << "Rule Chosen: " << chosen << endl;
      BaseDataProductionSystemNode *newnode = SetUpNewNode(prodclass,node);
      newnode->LogicCost = lcost;
      if(prodclass->getDebugLevel() > 0)
	cout << "New Node Name: '" << newnode->NameTag << "'" << endl;
      result = result && ApplyRuleToNode(prodclass,chosen,newnode);
      result = result && SetHeuristicValueOnNode(newnode,node);
      if(newnode->GetData()->IsInList(GeneratedNodesS))
	{
	  if(prodclass->getDebugLevel() > 0)
	    cout << "Expand the Generated Nodes" << endl;
	  ExpandGeneratedNodes(prodclass,newnode);
	}
      else
	{
	  if(prodclass->getDebugLevel() > 0)
	    cout << "Add to open list" << endl;
	  result = result && AddToOpenOrGoalList(prodclass,newnode,node);
	}
    }
  else
    {
      if(prodclass->getDebugLevel() > 1)
	cout << "Removing Node from Open List: " << node->NameTag << endl;
      Costs->RemoveObject(node->NameTag);
      OpenNodes.RemoveObject(node->NameTag);
    }
  return result;
}
/*F ans = ExpandGeneratedNode(prodclass,node)
**
**  DESCRIPTION
**    prodclass: The production system class
**    node: The node with generated nodes to expand
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataProductionSystem::ExpandGeneratedNodes(DataProductionSystemClass *prodclass,
						    BaseDataProductionSystemNode *node)
{
  bool result = true;
  BaseDataParameterSet *generatednodes = 
    (BaseDataParameterSet *) node->GetData()->GetObject(GeneratedNodesS)->Clone();
  node->GetData()->RemoveObject(GeneratedNodesS);

  ObjectList<String> names = generatednodes->OrderedListOfParameterNames();
  if(prodclass->getDebugLevel() > 1)
    cout << "ExpandGeneratedNodes: '" << node->NameTag << "' " << names.size() << endl;
  ObjectList<String>::iterator name;
  for(name = names.begin();
      name != names.end() && result;
      name++)
    {
      BaseDataObject *obj = generatednodes->GetObject(*name);
      if(prodclass->getDebugLevel() > 1)
	{
	  cout << "GeneratedObject: " << GeneratedNodeS << endl;
	  obj->print(cout);
	  cout << endl;
	}
      BaseDataProductionSystemNode *newnode = SetUpNewNode(prodclass,node);
      BaseDataInstance *data = newnode->GetData();
      obj->NameTag = GeneratedNodeS;
      data->AddObject(obj);
      result = result && SetHeuristicValueOnNode(newnode,node);
      result = result && AddToOpenOrGoalList(prodclass,newnode,node);
    }

  delete generatednodes;

  return result;
} 
/*F ans = SetHeuristicValueOnNode(newnode)
**
**  DESCRIPTION
**    newnode: The node to add the SetHeuristicValue
**    ans: True if successfull
**
**  REMARKS
**
*/
bool BaseDataProductionSystem::SetHeuristicValueOnNode(BaseDataProductionSystemNode *node,
						       BaseDataProductionSystemNode *parent)
{
  bool result = true;
  double assignedcost = 1.0;
  if(node->GetData()->IsInList(CostParameter))
    {
      BaseDataReal *nodecost = (BaseDataReal *) node->GetData()->GetObject(CostParameter);
      assignedcost = nodecost->GetValue();
    }

  double cost = 0.0;
  if(DepthFirst)
    cost = 0.0;
  else if(BreadthFirst)
      cost = node->GetLevel();
  else
    {
      if(parent != NULL)
	{
	  cost = assignedcost + parent->GetHeuristicValue();
	}
      else
	{
	  cost =  assignedcost;
	}
    }

  BaseDataReal *rcost = new BaseDataReal();
  rcost->NameTag = node->NameTag;
  rcost->SetValue(cost);
  node->SetHeuristicValue(cost);
  Costs->AddObject(rcost);
  delete rcost;

  return result;
}
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataProductionSystem::ApplyRuleToNode(DataProductionSystemClass *prodclass,
					       String& rulename,
					       BaseDataProductionSystemNode *node)
{
  bool result = true;
  BaseDataActionRule *rule;
  DataSetOfObjectsClass *objclasses = (DataSetOfObjectsClass *) prodclass->PointerToAllowedClasses();
  rule = (BaseDataActionRule *) Rules->GetObject(rulename);
  unsigned int tp = rule->GetType();
  DataActionRuleClass *ruleclass = ( DataActionRuleClass *) objclasses->GetObjectClass(tp);

  BaseDataInstance *data = node->GetData();
  DataInstanceClass *instclass = new DataInstanceClass();

  BaseDataParameterSet set;
  DataParameterSetClass setclass;
  BaseDataActionRule *crule = (BaseDataActionRule *) rule->Clone();
  result  = crule->EvaluateAllActions(ruleclass,
					 &set,data,
					 &setclass,instclass);
  delete crule;
  node->RuleUsed = rulename;

  return result;
}
  
/*F ans = EvaluateRuleConditions(node,rules)
**
**  DESCRIPTION
**    nodes: The node to expand
**    rules: The set of rules
**  REMARKS
**
*/
bool BaseDataProductionSystem::EvaluateRuleConditions(DataProductionSystemClass *prodclass,
						      BaseDataProductionSystemNode *node)
{
  bool result = true;
  DataSetOfObjectsClass *objclasses = prodclass->getRulesClass()->PointerToAllowedClasses();

  BaseDataInstance *instance = node->GetData();
  DataInstanceClass *instclass = (DataInstanceClass *) objclasses->GetObjectClass(INSTANCE_INSTANCE_ID);
  BaseDataParameterSet set;
  DataParameterSetClass setclass;
  cout << endl << "=======================================================" << endl;
  getParameterSet()->print(cout);
  cout << endl << "=======================================================" << endl;
  BaseDataReal *num = new BaseDataReal();
  BaseDataActionRule *rule;
  DataActionRuleClass *ruleclass;
  double value;
  ObjectList<String> rulenames = Rules->OrderedListOfParameterNames();
  ObjectList<String>::iterator rulename;
  for(rulename = rulenames.begin();
      rulename != rulenames.end();
      rulename++)
    {
      rule = (BaseDataActionRule *) Rules->GetObject(*rulename);
      ruleclass = (DataActionRuleClass *) objclasses->GetObjectClass(rule->GetType());
      BaseDataLogical *logic = rule->EvaluateCondition(ruleclass,
						       getParameterSet(),instance,&setclass,instclass);
      value = logic->GetValue();
      if(rule->ShouldActionBePerformed(logic))
	{
	  if(prodclass->getDebugLevel() > 0)
	    cout << "Rule Condition: " << *rulename << "   " << node->NameTag << " " << value << endl;
	  num->NameTag = *rulename;
	  num->SetValue(value);
	  node->RuleConditionValues->AddObject(num);
	}
      else
	{
	  if(prodclass->getDebugLevel() > 0)
	    cout << "Rule Not to be Included: " << *rulename << "   " << node->NameTag << " " << value << endl;
	}
      delete logic;
    }
  delete num;
  return result;
}
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataProductionSystem::PrintSearchTree(ostream& out,
					       DataProductionSystemClass *prodclass,
					       BaseDataSetOfInstances *instances,
					       DataSetOfInstancesClass *instsclass)
{
  Tree->PrintASCIITree(out,prodclass->getTreeClass(),
		       prodclass->getNodeClass(),
		       *instances,*instsclass);
}
 
/*F parameters = ExtractProductionSystemParameters()
**
**  DESCRIPTION
**    parameters: The specified goal parameters
**
**  REMARKS
**
*/
BaseDataParameterSet *BaseDataProductionSystem::ExtractProductionSystemParameters()
{
  BaseDataParameterSet *total = new BaseDataParameterSet();
  total->NameTag = NameTag;
  ObjectList<String> paramnames = GoalResultNames.GetKeyWords();
  ObjectList<String>::iterator goal,paramname;
  for(goal = GoalNodes.begin(); goal != GoalNodes.end(); goal++)
    {
      BaseDataProductionSystemNode *node = (BaseDataProductionSystemNode *) Tree->GetNode(*goal);
      BaseDataInstance *data = node->GetData();
      BaseDataParameterSet *parameters = new BaseDataParameterSet();
      parameters->NameTag = *goal;
      total->AddObject(parameters);
      delete parameters;
      parameters = (BaseDataParameterSet *) total->GetObject(*goal);

      for(paramname = paramnames.begin();
	  paramname != paramnames.end();
	  paramname++)
	{
	  if(data->IsInList(*paramname))
	    {
	      BaseDataObject *object = data->GetObject(*paramname);
	      parameters->AddObject(object);
	    }
	}
    }
  return total;
}
/*F operator()(cls,x,xc)  . . . . . . . . . . Execute the function with input
**
**  DESCRIPTION
**    cls: This class
**    x: The set of objects as input parameters
**    xc: The class of the set of objects
**
**    The operation at this level can be used to set up the output object
**
**  REMARKS
**
*/
BaseDataObject *BaseDataProductionSystem::operator()(DataObjectClass *cls,
						       BaseDataObject *x,
						       DataObjectClass *xc)
{
  return operator()(x,xc);
}
 
/*F obj = operator()(cls,x,xc,y,yc) . . . . . . . . with parameters and input
**
**  DESCRIPTION
**    cls: This class
**    x: The set of function parameters
**    xc: The function parameter class
**    y: The input parameters
**    yc: The input parameter class
**
**  REMARKS
**
*/
BaseDataObject *BaseDataProductionSystem::operator()(DataObjectClass *cls,
							  BaseDataObject *x,
							  BaseDataObject *y,
							  DataObjectClass *xc,
							  DataObjectClass *yc)
{
  return operator()(x,y,xc,yc);
}
/*F operator()(cls,x,xc)  . . . . . . . . . . Execute the function with input
**
**  DESCRIPTION
**    cls: This class
**    x: The set of objects as input parameters
**    xc: The class of the set of objects
**
**    The operation at this level can be used to set up the output object
**
**  REMARKS
**
*/
BaseDataObject *BaseDataProductionSystem::operator()(BaseDataObject *x,
							  DataObjectClass *xc)
{
  return (BaseDataObject *) x->Clone();
}
 
/*F obj = operator()(cls,x,xc,y,yc) . . . . . . . . with parameters and input
**
**  DESCRIPTION
**    cls: This class
**    x: The set of function parameters
**    xc: The function parameter class
**    y: The input parameters
**    yc: The input parameter class
**
**  REMARKS
**
*/
BaseDataObject *BaseDataProductionSystem::operator()(BaseDataObject *x,
						     BaseDataObject *y,
						     DataObjectClass *xc,
						     DataObjectClass *yc)
{
  BaseDataParameterSet *objects = (BaseDataParameterSet *) x;
  //  BaseDataInstance *instance = (BaseDataInstance *) y;
  //DataInstanceClass *instclass = (DataInstanceClass *) yc;
  //DataSetOfObjectsClass *classes = instclass->PointerToAllowedClasses();
  //unsigned int ptype = GetType();
  //DataProductionSystemClass *prodclass = (DataProductionSystemClass *) classes->GetObjectClass(ptype);
  InsertParameterSet(objects,true);
  String FinalCostS("FinalCost");
  BaseDataReal *cost = (BaseDataReal *) getOperation()->operator()(getParameterSet(),y,xc,yc);
  if(cost != NULL) {
    cout << "================================" << endl;
    cost->print(cout);
    cost->NameTag = FinalCostS;
    cout << "================================" << endl;
    //RunProductionSystem(prodclass,instance);
    //if(instance->IsInList(FinalCostS)) {
    //cost = (BaseDataReal *) instance->GetObject(FinalCostS)->Clone();
  } else {
    cerr << "Cost not able to be evaluated: set to zero" << endl;
    cost = new BaseDataReal();
    cost->SetValue(0.0);
    cost->NameTag = FinalCostS;
  }
  return cost;
}

/*S DataProductionSystemClass
 */
/*F DataProductionSystemClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataProductionSystemClass::DataProductionSystemClass()
  : RulesClass(NULL),
    //GoalStateConditionClass(NULL),
    NodeClass(NULL),
    TreeClass(NULL)
{
  Identification = RULESYSTEM_SYSTEM_ID;
  NameTag = RULESYSTEM_SYSTEM_NAME;
  SubClass = "SetOfObjects";
  EncodeDecodeClass = NameTag;
} 
/*F DataProductionSystemClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataProductionSystemClass::DataProductionSystemClass(const DataProductionSystemClass& data)
  : DataParameterizedExpressionClass(data)
{
  RulesClass = (DataSetOfRulesClass *) PointerClone(data.RulesClass);
  //GoalStateConditionClass = (DataParameterizedFunctionClass *) PointerClone(data.GoalStateConditionClass);
  NodeClass = (DataProductionSystemNodeClass *) PointerClone(data.NodeClass);
  TreeClass = (DataDirectedTreeClass *) PointerClone(data.TreeClass);
} 
 
/*F DataProductionSystemClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataProductionSystemClass::DataProductionSystemClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataParameterizedExpressionClass(id,name,descr),
    RulesClass(NULL),
    //GoalStateConditionClass(NULL),
    NodeClass(NULL),
    TreeClass(NULL)
{
  SubClass = "SetOfObjects";
  EncodeDecodeClass = RULESYSTEM_SYSTEM_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataProductionSystemClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataProductionSystemClass::print(ostream& out) const
{
  out << "==========================================================" << endl;
  DataParameterizedExpressionClass::print(out);
  out << endl << "==========================================================" << endl;
  cout << "             Goal State Condition Class";
  out << endl <<  "==========================================================" << endl;
  if(GoalStateConditionClass != NULL) 
    GoalStateConditionClass->print(out);
  else
    out << "Goal State Condition Class not defined";
  out << endl <<  "==========================================================" << endl;
  out << "              Node Class";
  out << endl <<  "==========================================================" << endl;
  if(NodeClass != NULL)
    NodeClass->print(out);
  else
    out << " Node Class not defined";
  out << endl <<  "==========================================================" << endl;
  out << "              TreeClass Class";
  out << endl <<  "==========================================================" << endl;
  if(TreeClass != NULL)
    TreeClass->print(out);
  else
    out << " TreeClass Class not defined";
  out << endl <<  "==========================================================" << endl;
  out << "              Rules Class";
  out << endl <<  "==========================================================" << endl;
  if(RulesClass != NULL)
    RulesClass->print(out);
  else
    out << "Rules Class  not defined ";
  out << endl <<  "==========================================================" << endl;
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataProductionSystemClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataProductionSystemClass, there is no further information.
**
**  REMARKS
**
*/
bool DataProductionSystemClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = true;
  result = result && DataParameterizedExpressionClass::Read(in,set);
  //String gnotdefined("Goal State Condition Class");
  //result = result && PointerClassRead(in,
  //(DataObjectClass *&) GoalStateConditionClass,
  //PARAMETERIZED_FUNCTION_NAME,
  //set,
  //gnotdefined);
  String rnotdefined("Rules Class");
  cout << "Read Rules Class: '" << RULESYSTEM_RULESET_NAME << "' " << endl;
  result = result && PointerClassRead(in,
				      (DataObjectClass *&) RulesClass,
				      RULESYSTEM_RULESET_NAME,
				      set,
				      rnotdefined);
  String nnotdefined("Node Class");
  cout << "Read Node Class: '" << RULESYSTEM_PRODNODE_NAME << "' " << endl;
  result = result && PointerClassRead(in,
				      (DataObjectClass *&) NodeClass,
				      RULESYSTEM_PRODNODE_NAME,
				      set,
				      nnotdefined);
  String tnotdefined("Tree Class");
  cout << "Read Tree Class: '" << DIRECTEDTREE_BASE_NAME << "' " << endl;
  result = result && PointerClassRead(in,
				      (DataObjectClass *&) TreeClass,
				      DIRECTEDTREE_BASE_NAME,
				      set,
				      tnotdefined);
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataProductionSystemClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataProductionSystemClass::CopyClone(Identify *  objc)
{
  DataProductionSystemClass *objcfull = (DataProductionSystemClass *) objc;
  *this = *objcfull;
  DataParameterizedExpressionClass::CopyClone(objc);
  RulesClass = (DataSetOfRulesClass *) PointerClone(objcfull->RulesClass);
  //GoalStateConditionClass = (DataParameterizedFunctionClass *) PointerClone(objcfull->GoalStateConditionClass);
  NodeClass = (DataProductionSystemNodeClass *) PointerClone(objcfull->NodeClass);
  TreeClass = (DataDirectedTreeClass *) PointerClone(objcfull->TreeClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataProductionSystemClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataProductionSystemClass::Clone()
{
  DataProductionSystemClass* id = new DataProductionSystemClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataProductionSystemClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataProductionSystemClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataParameterizedExpressionClass::EncodeThis(buffer);
  result = result && PointerEncode(buffer,(DataObjectClass *&) RulesClass);
  //result = result && PointerEncode(buffer,(DataObjectClass *&) GoalStateConditionClass);
  result = result && PointerEncode(buffer,(DataObjectClass *&) NodeClass);
  result = result && PointerEncode(buffer,(DataObjectClass *&) TreeClass);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataProductionSystemClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataProductionSystemClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataParameterizedExpressionClass::DecodeThis(buffer);
  result = result && PointerDecode(buffer,(BaseDataObject *&) RulesClass);
  //result = result && PointerDecode(buffer,(BaseDataObject *&) GoalStateConditionClass);
  result = result && PointerDecode(buffer,(BaseDataObject *&) NodeClass);
  result = result && PointerDecode(buffer,(BaseDataObject *&) TreeClass);
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
BaseDataObject * DataProductionSystemClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataProductionSystem();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataProductionSystemClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataProductionSystemClass*& obj)
     {
     obj = new DataProductionSystemClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataProductionSystem
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataProductionSystem*& obj)
     {
     obj = new BaseDataProductionSystem;
     return obj->DecodeThis(buffer);
     }

 
/*F rulesclass = getRulesClass()  . . . . . . . . . DataProductionSystemClass
**
**  DESCRIPTION
**    rulesclass: The set of rules class
**
**  REMARKS
**
*/
DataSetOfRulesClass *DataProductionSystemClass::getRulesClass()
{
  return RulesClass;
}
/*F nodeclass = getNodeClass()  . . . . . . . . . . DataProductionSystemClass
**
**  DESCRIPTION
**    nodeclass: The production system node class
**
**  REMARKS
**
*/
DataProductionSystemNodeClass *DataProductionSystemClass::getNodeClass()
{
  return NodeClass;
}
/*F treeclass = getTreeClass()  . . . . . . . . . DataProductionSystemClass
**
**  DESCRIPTION
**    treeclass: The production system tree class
**
**  REMARKS
**
*/
DataDirectedTreeClass *DataProductionSystemClass::getTreeClass()
{
  return TreeClass;
}
 
/*F condclass = getGoalStateConditionClass()  . . . DataProductionSystemClass
**
**  DESCRIPTION
**    condclass: The Goal State Condition Function Class
**
**  REMARKS
**
DataParameterizedFunctionClass *DataProductionSystemClass::getGoalStateConditionClass()
{
  return GoalStateConditionClass;
}
*/
/*F objc = PointerToAllowedClasses()  . . . .  the allowed set of class types
**
**  DESCRIPTION
**    objc: The pointer to the allowed classes
**  REMARKS
**
*/
DataSetOfObjectsClass*  DataProductionSystemClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}

/*S BaseDataProductionSystemSearch
 */ 
/*F BaseDataProductionSystemSearch()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataProductionSystemSearch::BaseDataProductionSystemSearch()
  : ProductionSystemS("ProductionSystem"),
    TrainInstanceNamesS("TrainInstanceNameList"),
    MaxNodesS("MaximumNumberOfNodes")
{
  Identification = RULESYSTEM_SEARCH_ID;
  NameTag = RULESYSTEM_SEARCH_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataProductionSystemSearch(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataProductionSystemSearch::BaseDataProductionSystemSearch(const BaseDataProductionSystemSearch& data)
  : BaseDataAlgorithmOperation(data),
    ProductionSystemS(data.ProductionSystemS),
    TrainInstanceNamesS(data.TrainInstanceNamesS),
    MaxNodesS(data.MaxNodesS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataProductionSystemSearch
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataProductionSystemSearch::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataProductionSystemSearch
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataProductionSystemSearch::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataProductionSystemSearch
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataProductionSystemSearch::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataProductionSystemSearch
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataProductionSystemSearch::Clone()
{
  BaseDataProductionSystemSearch *obj = new BaseDataProductionSystemSearch(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataProductionSystemSearch
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataProductionSystemSearch::CopyClone(Identify * obj)
{
  BaseDataProductionSystemSearch *objfull = (BaseDataProductionSystemSearch *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataProductionSystemSearch
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataProductionSystemSearch::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataProductionSystemSearch
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataProductionSystemSearch::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
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
bool BaseDataProductionSystemSearch::SetUpAlgorithms(BaseDataSetOfInstances*,
						      DataSetOfInstancesClass*,
						      BaseDataAlgorithmRun* ,
						      DataAlgorithmRunClass*)
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
bool BaseDataProductionSystemSearch::CheckInput(BaseDataSetOfInstances*,
						DataSetOfInstancesClass*,
						BaseDataAlgorithmRun *run,
						DataAlgorithmRunClass*)
{
  bool result = true;
  if(run->ParameterInList(TrainInstanceNamesS))
    {
      if(run->ParameterInList(ProductionSystemS))
	{
	  if(run->ParameterInList(MaxNodesS))
	    {
	    }
	  else
	    {
	      cerr << "The maximum number of nodes '" << MaxNodesS << "' was not in the list of parameters" << endl;
	      result = false;
	    }
	}
      else
	{
	  cerr << "The production system '" << ProductionSystemS << "' was not in the list of parameters" << endl;
	  result = false;
	}
    }
  else
    {
      cerr << "The training set '" << TrainInstanceNamesS << "' was not in the list of parameters" << endl;
      result = false;
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
bool BaseDataProductionSystemSearch::SetUpInput(BaseDataSetOfInstances* instances,
						 DataSetOfInstancesClass* instancesclass,
						 BaseDataAlgorithmRun *run,
						 DataAlgorithmRunClass* rclass)
{
  bool result = true;

  TrainInstanceNameKeys = (BaseDataKeyWords *) run->ParameterValue(TrainInstanceNamesS);
  TrainInstanceNames = TrainInstanceNameKeys->GetKeyWords();
  ProductionSystem = (BaseDataProductionSystem *) run->ParameterValue(ProductionSystemS);
  MaxNodes= (BaseDataInteger *) run->ParameterValue(MaxNodesS);

  ProductionSystem->MaximumNumberOfNodes = MaxNodes->GetValue();
  ProductionSystem->BreadthFirst = run->AlgorithmSummary.KeyWordInList("BreadthFirst");
  ProductionSystem->DepthFirst = run->AlgorithmSummary.KeyWordInList("DepthFirst");
  ProductionSystem->HeuristicSearch = run->AlgorithmSummary.KeyWordInList("HeuristicSearch");

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
bool BaseDataProductionSystemSearch::Calculate(BaseDataSetOfInstances *instances,
					       DataSetOfInstancesClass *instanceclass,
					       BaseDataAlgorithmRun *run,
					       DataAlgorithmRunClass *runclass)
{
  bool result = true;
  unsigned int ptype = ProductionSystem->GetType();
  DataProductionSystemClass *prodclass = (DataProductionSystemClass *)
    instanceclass->PointerToAllowedClasses()->GetObjectClass(ptype);
  prodclass->SetDebugLevel(runclass->getDebugLevel());

  ObjectList<String>::iterator name;
  for(name = TrainInstanceNames.begin();
      name != TrainInstanceNames.end() && result;
      name++)
    {
      cout << "Production System Execute on: " << *name << endl;
      BaseDataProductionSystem *prodsystem = (BaseDataProductionSystem *) ProductionSystem->Clone();
      BaseDataInstance *instance = instances->GetInstance(*name); 
      instanceclass->SetDebugLevel(runclass->getDebugLevel());
      result = prodsystem->RunProductionSystem(prodclass,instance);
      prodsystem->PrintSearchTree(cout,prodclass,instances,instanceclass);
      BaseDataParameterSet *parameters = prodsystem->ExtractProductionSystemParameters();
      instance->AddObject(parameters);
      delete parameters;
      delete prodsystem;
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
bool BaseDataProductionSystemSearch::WriteOutputValues(BaseDataSetOfInstances*,
							DataSetOfInstancesClass*,
							BaseDataAlgorithmRun* run,
							DataAlgorithmRunClass*)
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
bool BaseDataProductionSystemSearch::ConcludeRun(BaseDataSetOfInstances*,
						  DataSetOfInstancesClass*,
						  BaseDataAlgorithmRun*,
						  DataAlgorithmRunClass*)
{
  bool result = true;
//  delete something
  return result;
}
 

 
/*S DataProductionSystemSearchClass
 */
/*F DataProductionSystemSearchClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataProductionSystemSearchClass::DataProductionSystemSearchClass()
{
  Identification = RULESYSTEM_SEARCH_ID;
  NameTag = RULESYSTEM_SEARCH_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataProductionSystemSearchClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataProductionSystemSearchClass::DataProductionSystemSearchClass(const DataProductionSystemSearchClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataProductionSystemSearchClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataProductionSystemSearchClass::DataProductionSystemSearchClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = RULESYSTEM_SEARCH_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataProductionSystemSearchClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataProductionSystemSearchClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataProductionSystemSearchClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataProductionSystemSearchClass, there is no further information.
**
**  REMARKS
**
*/
bool DataProductionSystemSearchClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataProductionSystemSearchClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataProductionSystemSearchClass::CopyClone(Identify *  objc)
{
  DataProductionSystemSearchClass *objcfull = (DataProductionSystemSearchClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataProductionSystemSearchClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataProductionSystemSearchClass::Clone()
    {
      DataProductionSystemSearchClass* id = new DataProductionSystemSearchClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataProductionSystemSearchClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataProductionSystemSearchClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataProductionSystemSearchClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataProductionSystemSearchClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
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
BaseDataObject * DataProductionSystemSearchClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj =  new BaseDataProductionSystemSearch();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataProductionSystemSearchClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataProductionSystemSearchClass*& obj)
     {
     obj = new DataProductionSystemSearchClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataProductionSystemSearch
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataProductionSystemSearch*& obj)
     {
     obj = new BaseDataProductionSystemSearch;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataParameterizedProductionRun
 */ 
/*F BaseDataParameterizedProductionRun()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataParameterizedProductionRun::BaseDataParameterizedProductionRun()
{
  Identification = RULESYSTEM_PARSYSTEM_ID;
  NameTag = RULESYSTEM_PARSYSTEM_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataParameterizedProductionRun(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataParameterizedProductionRun::BaseDataParameterizedProductionRun(const BaseDataParameterizedProductionRun& data)
  : BaseDataParameterizedFunction(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataParameterizedProductionRun
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataParameterizedProductionRun::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataParameterizedProductionRun
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataParameterizedProductionRun::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataParameterizedFunction::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataParameterizedProductionRun
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataParameterizedProductionRun::print(ostream& out) const
{
  BaseDataParameterizedFunction::print(out);
  //PointerPrint(out,"The List of Parameters: ","No Parameters",Parameters);
  // The rest

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataParameterizedProductionRun
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataParameterizedProductionRun::Clone()
{
  BaseDataParameterizedProductionRun *obj = new BaseDataParameterizedProductionRun(*this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataParameterizedProductionRun
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataParameterizedProductionRun::CopyClone(Identify * obj)
{
  BaseDataParameterizedProductionRun *objfull = (BaseDataParameterizedProductionRun *) obj;
  *this = *objfull;
  //Parameter = (BaseData... *) PointerClone(objfull->Parameter)
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataParameterizedProductionRun
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataParameterizedProductionRun::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataParameterizedFunction::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);
  //result = result && PointerEncode(buffer,Parameters);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataParameterizedProductionRun
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataParameterizedProductionRun::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataParameterizedFunction::DecodeThis(buffer);
  // The rest

  return result;
}
 
 
/*S DataParameterizedProductionRunClass
 */
/*F DataParameterizedProductionRunClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataParameterizedProductionRunClass::DataParameterizedProductionRunClass()
{
  Identification = RULESYSTEM_PARSYSTEM_ID;
  NameTag = RULESYSTEM_PARSYSTEM_NAME;
  SubClass = "ParameterizedFunction";
  EncodeDecodeClass = NameTag;
} 
/*F DataParameterizedProductionRunClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataParameterizedProductionRunClass::DataParameterizedProductionRunClass(const DataParameterizedProductionRunClass& data)
  : DataParameterizedFunctionClass(data)
{
} 
 
/*F DataParameterizedProductionRunClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataParameterizedProductionRunClass::DataParameterizedProductionRunClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataParameterizedFunctionClass(id,name,descr)
{
  SubClass = "ParameterizedFunction";
  EncodeDecodeClass = RULESYSTEM_PARSYSTEM_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataParameterizedProductionRunClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataParameterizedProductionRunClass::print(ostream& out) const
{
  DataParameterizedFunctionClass::print(out);
  //PointerPrint(out,"  The Class: "," No Class Defined ",Class);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataParameterizedProductionRunClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataParameterizedProductionRunClass, there is no further information.
**
**  REMARKS
**
*/
bool DataParameterizedProductionRunClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataParameterizedFunctionClass::Read(in,set);
  //result = result && PointerClassRead(in,(DataObjectClass *&) Class,
  //COREOBJECTS_BASE_NAME,
  //set," No Class ");
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataParameterizedProductionRunClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataParameterizedProductionRunClass::CopyClone(Identify *  objc)
{
  DataParameterizedProductionRunClass *objcfull = (DataParameterizedProductionRunClass *) objc;
  *this = *objcfull;
  //ParameterClass = (DataSetOfObjectsClass *) PointerClone(objcfull->ParameterClass);
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataParameterizedProductionRunClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataParameterizedProductionRunClass::Clone()
    {
      DataParameterizedProductionRunClass* id = new DataParameterizedProductionRunClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataParameterizedProductionRunClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataParameterizedProductionRunClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataParameterizedFunctionClass::EncodeThis(buffer);
  //result = result && PointerEncode(buffer,Class);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataParameterizedProductionRunClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataParameterizedProductionRunClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataParameterizedFunctionClass::DecodeThis(buffer);
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
BaseDataObject * DataParameterizedProductionRunClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = new BaseDataParameterizedProductionRun();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataParameterizedProductionRunClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataParameterizedProductionRunClass*& obj)
     {
     obj = new DataParameterizedProductionRunClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataParameterizedProductionRun
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataParameterizedProductionRun*& obj)
     {
     obj = new BaseDataParameterizedProductionRun;
     return obj->DecodeThis(buffer);
     }
//EncodeDecodeRegisterClass<DataParameterizedProductionRunClass,BaseDataParameterizedProductionRun>(_NAME);
//String descr("The Class");
//DataParameterizedProductionRunClass class(_ID,_NAME,descr);
//set.AddObjectClass(class);

/*S Utilities
 */
/*F InitialSetOfRuleSystemEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialSetOfRuleSystemEncodeDecodeRoutines()
{
   EncodeDecodeRegisterClass(DataActionRuleClass,BaseDataActionRule,RULESYSTEM_RULE_NAME);
   EncodeDecodeRegisterClass(DataSetOfRulesClass,BaseDataSetOfRules,RULESYSTEM_RULESET_NAME);
   EncodeDecodeRegisterClass(DataProductionSystemClass,BaseDataProductionSystem,RULESYSTEM_SYSTEM_NAME);
   EncodeDecodeRegisterClass(DataProductionSystemSearchClass,BaseDataProductionSystemSearch,RULESYSTEM_SEARCH_NAME);
   EncodeDecodeRegisterClass(DataExecuteActionRuleClass,BaseDataExecuteActionRule,RULESYSTEM_RULEEXE_NAME);
   EncodeDecodeRegisterClass(DataProductionSystemNodeClass,BaseDataProductionSystemNode,RULESYSTEM_PRODNODE_NAME);
}
/*F AddRuleSystemClasses(set)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AddRuleSystemClasses(DataSetOfObjectsClass& set)
{
  String ruledescr("The condition and actions of a rule");
  String setdescr("The set of rules in the production system");
  String sysdescr("The running production system environment");
  String srchdescr("The production system algorithm");
  String ruleexedescr("The rule action execution algorithm");
  String nodedescr("The production system node");
  
  DataActionRuleClass ruleclass(RULESYSTEM_RULE_ID,RULESYSTEM_RULE_NAME,ruledescr);
  DataSetOfRulesClass setclass(RULESYSTEM_RULESET_ID,RULESYSTEM_RULESET_NAME,setdescr);
  DataProductionSystemClass sysclass(RULESYSTEM_SYSTEM_ID,RULESYSTEM_SYSTEM_NAME,sysdescr);
  DataProductionSystemSearchClass srchclass(RULESYSTEM_SEARCH_ID,RULESYSTEM_SEARCH_NAME,srchdescr);
  DataExecuteActionRuleClass ruleexeclass(RULESYSTEM_RULEEXE_ID,RULESYSTEM_RULEEXE_NAME,ruleexedescr);
  DataProductionSystemNodeClass nodeclass(RULESYSTEM_PRODNODE_ID,RULESYSTEM_PRODNODE_NAME,nodedescr);

  set.AddObjectClass(ruleexeclass);
  set.AddObjectClass(setclass);
  set.AddObjectClass(sysclass);
  set.AddObjectClass(srchclass);
  set.AddObjectClass(ruleclass);
  set.AddObjectClass(nodeclass);
}
 
/*F name = NonDeterministicChoice(choices)  . . . . . . . . . weighted choice
**
**  DESCRIPTION
**    choices: The list of heuristic values
**    name: The weighted choice from the values
**
**  REMARKS
**
*/
String NonDeterministicChoice(BaseDataSetOfObjects *choices)
{
  ObjectList<String> names = choices->ListOfObjectNames();
  if(names.size() != 0)
    {
      ObjectList<String>::iterator name;
      double total = 0.0;
      for(name = names.begin();name != names.end();name++)
	{
	  BaseDataReal *value = (BaseDataReal *) choices->GetObject(*name);
	  total += value->GetValue();
	}
      
      double rndm = ((double) random()) / ((double) RAND_MAX);
      double pick = rndm * total;
      
      name = names.begin();
      BaseDataReal *value = (BaseDataReal *) choices->GetObject(*name);
      double sum = value->GetValue();
      while(sum < pick)
	{
	  name++;
	  BaseDataReal *value = (BaseDataReal *) choices->GetObject(*name);
	  sum += value->GetValue();
	}
      return *name;
    }
  else
    {
      String *dummy = new String();
      return *dummy;
    }
}
