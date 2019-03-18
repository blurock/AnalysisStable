/*  FILE     GoalObjects.cc
**  PACKAGE  GoalObjects
**  AUTHOR   Edward s. Blurock
**
**  CONTENT
**    Exported functions for the "GoalObjects" package.
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
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "GoalObjects.hh"

#ifdef _unix
template class list<BaseDataGoalSpec>;
#endif

/*S Utility
 */
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
/*F ans = RunAlgorithmAsGoal(level1)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int RunAlgorithmAsGoal(ReactionSystemBase *test,
                       DataSetOfObjectsClass& Standard)
{
  if(test->Inputs.size() < 6)
    {
      cout << "Input:\n";
      cout << "Filename: GoalRunClass Definition\n";
      cout << "Filename: GoalSpec Specification\n";
      cout << "Filename: Initial class set of instances\n";
      cout << "Filename: Initial set of instances\n";
      cout << "Debug: main routine debug (0 1 2) \n";
      cout << "Debug: goal routine debug (0 1 2) \n";
      
      return 1;
    }
  
  String rfilename = test->Inputs.front();
  test->Inputs.pop_front();
  
  String gfilename = test->Inputs.front();
  test->Inputs.pop_front();

  String icfilename = test->Inputs.front();
  test->Inputs.pop_front();
  
  String ifilename = test->Inputs.front();
  test->Inputs.pop_front();
  
  String debugS = test->Inputs.front();
  test->Inputs.pop_front();
  unsigned int maindebug = debugS.ToInteger();
  
  String gdebugS = test->Inputs.front();
  test->Inputs.pop_front();
  unsigned int goaldebug = gdebugS.ToInteger();
  


  DataGoalRunClass rclass(0,"Test","A GoalRunClass Test");
  DataGoalSpecClass sclass(0,"Test","A GoalSpec Test");
  BaseDataGoalSpec goalspec;

  Standard.SetDebugLevel(maindebug);

  if(maindebug > 0) 
    cout << "---------- Read Goal and Specs      ---------------------------\n";
  bool result = ReadGoalAndSpecs(rfilename,gfilename,
                                 rclass,sclass,goalspec,
                                 Standard,maindebug);
  if(result)
    {
      BaseDataSetOfInstances instances;
      DataSetOfInstancesClass instancesclass;
      if(result)
        {
          if(maindebug > 0) 
            cout << "---------- Read Instances and Class  ---------------------------\n";
          result =  result &&
            ReadInInstancesAndClass(icfilename,ifilename,
				    instances,instancesclass,Standard,maindebug);
          if(result)
            {
              if(maindebug > 0) 
                cout << "---------- Run The Goal ---------------------------\n";
              BaseDataGoalRun goalrun;
              goalrun.goalDebugLevel = goaldebug;
              
              result = result && goalrun.Run(goalspec,&instances,&instancesclass,&rclass);
              
              if(maindebug > 2)
                {
                  cout << "Final Instances\n";
                  instances.print(cout);
                  cout << endl;
                }
              if(maindebug > 1)
                {
                  cout << "Final Parameters\n";
                  goalrun.PrintParameters(cout);
                  cout << endl;
                }
              if(result)
                cout << "Goal Executed Successfully\n";
              else
                cout << "Goal Not Successful\n";
            }
        }
    }
  
  return 0;
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool ReadGoalAndSpecs(String& rfilename,
                      String& gfilename,
                      DataGoalRunClass& rclass,
                      DataGoalSpecClass& sclass,
                      BaseDataGoalSpec& goalspec,
                      DataSetOfObjectsClass& Standard,
                      unsigned int maindebug)
{
  bool result = true;
  
  OpenInputFile rfile(rfilename);
  OpenInputFile gfile(gfilename);

  if(rfile.IfOpen())
    {
      if(!gfile.IfOpen())
        {
          cerr << "GoalSpec file not found: " << gfilename << endl;
          result = false;
        }
    }
  else
    {
      cerr << " GoalRunClass file not found: " << rfilename << endl;
      result = false;
    }
      
  if(result && maindebug > 0)
    cout << "-------- Read in GoalRunClass instance ------------\n";
  result = result && rclass.Read(rfile.Stream,Standard);
  if(maindebug > 0)
    cout << "---------------------------------------------------\n";
  if(result)
    {
      if(maindebug > 1)
        {
          rclass.print(cout);
          cout << "\n";
        }
  
      if(maindebug > 0)
        cout << "-------- Get GoalSpec ------------------\n";
      result = result && goalspec.Read(gfile.Stream,
				       &(sclass));
      if(result)
        {
          if(maindebug > 1)
            {
              goalspec.print(cout);
              cout << "\n";
            }
        }
      else
        {
          cerr << "Error in reading GoalSpec file: " << gfilename << endl;
        }
    }
  else
    {
      cerr << "Error in reading RunGoalClass file: " << rfilename << endl;
    }
  
  return result;
}

/*S BaseDataGoalSpec
 */ 
/*F BaseDataGoalSpec()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGoalSpec::BaseDataGoalSpec()
{
  Identification = GOALS_SPEC_ID;
  NameTag = GOALS_SPEC_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataGoalSpec(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGoalSpec::BaseDataGoalSpec(const BaseDataGoalSpec& data)
  : BaseDataObject(data),
    ParameterSpecs(data.ParameterSpecs)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataGoalSpec
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataGoalSpec::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  bool result = true;
  String spec = str.ReadNext();
  if(!(spec == "GoalSpec:"))
    {
      cout << "Expected GoalSpec: (Got: ";
      cout << spec;
      cout << "\n";
      result = false;
    }
  else
    {
      NameTag = str.ReadNext();
      result = Read(in,objc,NameTag);
    }

  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataGoalSpec
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataGoalSpec::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);
  result = result && ParameterSpecs.Read(in);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataGoalSpec
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGoalSpec::print(ostream& out) const
{
  //BaseDataObject::print(out);
  
  SymmetricPairList<String>::const_iterator specs;
  
  out << "   GoalSpec: ";
  out << NameTag;
  out << "[";
  
  for(specs = ParameterSpecs.begin();
      specs != ParameterSpecs.end();
      specs++)
    {
      if(specs != ParameterSpecs.begin())
        out << ",";
      
      out << " (";
      out << (*specs).J;
      out << ") ";
      out << (*specs).I;
    }
  cout << "] ";
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataGoalSpec
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGoalSpec::Clone()
{
  BaseDataGoalSpec *obj = new BaseDataGoalSpec;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataGoalSpec
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGoalSpec::CopyClone(Identify *obj)
{
  BaseDataGoalSpec *objfull = (BaseDataGoalSpec *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGoalSpec
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGoalSpec::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && ParameterSpecs.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGoalSpec
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGoalSpec::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && ParameterSpecs.DecodeThis(buffer);

  return result;
}
 
/*F ans = AddGoalSpecification(name,classname)  . . . . . . . . .  add object
**
**  DESCRIPTION
**    name: The name of the parameter
**    classname: The class name of the parameter object
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGoalSpec::AddGoalSpecification(const String& name, const String& classname)
{
  return ParameterSpecs.AddObject(name,classname);
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataGoalSpec::operator==(BaseDataGoalSpec& spec)
{
  bool result = (NameTag == spec.NameTag);
  
  return result;
}
/*F params = getParameterSpecs()
**
**  DESCRIPTION
**    params: The list of parameters
**
**  REMARKS
**
*/
ObjectNameClassPairs* BaseDataGoalSpec::getParameterSpecs()
{
  return &ParameterSpecs;
}
/*F ans = ClassNamesEqual(spec)
**
**  DESCRIPTION
**    spec: The goal spec to be compared with
**    ans: true if the class names are exactly equal
**
**  REMARKS
**
*/
bool BaseDataGoalSpec::ClassNamesEqual(BaseDataGoalSpec& spec)
{
  bool result = true;

  if(ParameterSpecs.size() ==
     spec.ParameterSpecs.size())
    {
      ObjectNameClassPairs::iterator str 
	= ParameterSpecs.begin();
      ObjectNameClassPairs::iterator specstr;
      for(specstr =  spec.ParameterSpecs.begin();
	  result &&
	    specstr != spec.ParameterSpecs.end();
	  specstr++)
	{
	  result = result && ( (*str).J == (*specstr).J );
	  str++;
	}
    }
  else
    result = false;

  return result;
}
/*F ans = VariableNamesEqual(spec)
**
**  DESCRIPTION
**    spec: The goal spec to be compared with
**    ans: true if the class names are exactly equal
**
**  REMARKS
**
*/
bool BaseDataGoalSpec::VariableNamesEqual(BaseDataGoalSpec& spec)
{
  bool result = true;

  if(ParameterSpecs.size() ==
     spec.ParameterSpecs.size())
    {
      ObjectNameClassPairs::iterator str 
	= ParameterSpecs.begin();
      ObjectNameClassPairs::iterator specstr;
      for(specstr =  spec.ParameterSpecs.begin();
	  result &&
	    specstr != spec.ParameterSpecs.end();
	  specstr++)
	{
	  result = result && ( (*str).I == (*specstr).I );
	  str++;
	}
    }
  else
    result = false;

  return result;
}
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataGoalSpec::operator<(BaseDataGoalSpec& spec)
{
  bool result = (NameTag < spec.NameTag);
  
  return result;
}
/*S DataGoalSpecClass
 */
/*F DataGoalSpecClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGoalSpecClass::DataGoalSpecClass()
{
  Identification = GOALS_SPEC_ID;
  NameTag = GOALS_SPEC_NAME;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataGoalSpecClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGoalSpecClass::DataGoalSpecClass(const DataGoalSpecClass& data)
  : DataObjectClass(data)
{
} 
 
/*F DataGoalSpecClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataGoalSpecClass::DataGoalSpecClass(const int id, 
                                 const String& name,
                                 const String& descr)
  : DataObjectClass(id,name,descr)
{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = GOALS_SPEC_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataGoalSpecClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGoalSpecClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataGoalSpecClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGoalSpecClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGoalSpecClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataGoalSpecClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGoalSpecClass::CopyClone(Identify * objc)
    {
      DataGoalSpecClass *objcfull = (DataGoalSpecClass* ) objc;
      
      *this = *objcfull;
    }
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataGoalSpecClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGoalSpecClass::Clone()
    {
      DataGoalSpecClass* id = new DataGoalSpecClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataGoalSpecClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGoalSpecClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataGoalSpecClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGoalSpecClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataGoalSpecClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataGoalSpec();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGoalSpecClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGoalSpecClass*& obj)
     {
     obj = new DataGoalSpecClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataGoalSpec
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGoalSpec*& obj)
     {
     obj = new BaseDataGoalSpec;
     return obj->DecodeThis(buffer);
     }

/*S BaseDataGoalSummary
 */ 
/*F BaseDataGoalSummary()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGoalSummary::BaseDataGoalSummary()
{
  Identification = GOALS_SUMMARY_ID;
  NameTag = GOALS_SUMMARY_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataGoalSummary(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGoalSummary::BaseDataGoalSummary(const BaseDataGoalSummary& data)
  : BaseDataAlgorithmSummary(data),
    Prerequisites(data.Prerequisites),
    GoalSpec(data.GoalSpec)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataGoalSummary
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**    Reads two words:
**    - 'GoalSummary:' used as file alignment check
**    - The name of the GoalSummary instance
**
**  REMARKS
**
*/
bool BaseDataGoalSummary::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  String spec = str.ReadNext();
  bool result = true;
  if(!(spec == "GoalSummary:"))
    {
      cout << "Expected 'GoalSummary' (Got: ";
      cout << spec;
      cout << "\n";
      
      result = false;
    }
  else
    {
      NameTag = str.ReadNext();
      result = Read(in,objc,NameTag);
    }
  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataGoalSummary
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataGoalSummary::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmSummary::Read(in,objc,name);
  result = result && GoalSpec.Read(in,objc,name);
  GoalSpec.NameTag = name;
  
  StreamObjectInput str(in,' ');
  String gname = str.ReadNext();
  while(!(gname == "END") && result)
    {
      BaseDataGoalSpec gspec;
      gspec.NameTag = gname;
      
      result = result && gspec.Read(in,objc,gname);
      if(result)
        {
          Prerequisites.AddObject(gspec);
          gname = str.ReadNext();
        }
    }
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataGoalSummary
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGoalSummary::print(ostream& out) const
{
  cout << "GoalSummary:  ";
  GoalSpec.print(out);
  
  cout << "\nPrerequisite Goals\n";
  Prerequisites.print(out);
  cout << "\nThe Algorithm of the Goal\n";
  BaseDataAlgorithmSummary::print(out);
  cout << "\n";
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataGoalSummary
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGoalSummary::Clone()
{
  BaseDataGoalSummary *obj = new BaseDataGoalSummary;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataGoalSummary
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGoalSummary::CopyClone(Identify *obj)
{
  BaseDataGoalSummary *objfull = (BaseDataGoalSummary *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGoalSummary
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGoalSummary::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmSummary::EncodeThis(buffer);
  result = result && Prerequisites.EncodeThis(buffer);
  result = result && GoalSpec.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGoalSummary
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGoalSummary::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmSummary::DecodeThis(buffer);
  result = result && Prerequisites.DecodeThis(buffer);
  result = result && GoalSpec.DecodeThis(buffer);

  return result;
}
 
 
/*F ans = AddPrerequisitesToEnd(slist) 
**
**  DESCRIPTION
**    slist: list to add prerequisites to
**    ans: true if new prerequisites added
**
**  REMARKS
**
*/
bool BaseDataGoalSummary::AddPrerequisitesToEnd(ObjectList<BaseDataGoalSpec>& slist)
{
  bool result = true;
  unsigned isize = slist.size();

  slist.AddOnlyUniqueObjects(Prerequisites);
  if(isize == slist.size())
    result = false;
  
  return result;
}
 
/*F prereqs = GetPrerequisites()  . . . . . . . . . . get set of prereq goals
**
**  DESCRIPTION
**    prereqs: Set of prerequisite goals
**
**  REMARKS
**
*/
ObjectList<BaseDataGoalSpec> BaseDataGoalSummary::GetPrerequisites()
{
  return Prerequisites;
}
/*S DataGoalSummaryClass
 */
/*F DataGoalSummaryClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGoalSummaryClass::DataGoalSummaryClass()
{
  Identification = GOALS_SUMMARY_ID;
  NameTag = GOALS_SUMMARY_NAME;
  SubClass = ALGORITHM_SUMMARY_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataGoalSummaryClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGoalSummaryClass::DataGoalSummaryClass(const DataGoalSummaryClass& data)
  : DataAlgorithmSummaryClass(data),
    GoalSpecClass(data.GoalSpecClass)
{
} 
 
/*F DataGoalSummaryClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataGoalSummaryClass::DataGoalSummaryClass(const int id, 
                                 const String& name,
                                 const String& descr)
  : DataAlgorithmSummaryClass(id,name,descr)
{
  SubClass = ALGORITHM_SUMMARY_NAME;
  EncodeDecodeClass = GOALS_SUMMARY_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataGoalSummaryClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGoalSummaryClass::print(ostream& out) const
{
  DataAlgorithmSummaryClass::print(out);
  GoalSpecClass.print(out);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataGoalSummaryClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGoalSummaryClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGoalSummaryClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmSummaryClass::Read(in,set);
  result = result && GoalSpecClass.Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataGoalSummaryClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGoalSummaryClass::CopyClone(Identify *objc)
    {
      DataGoalSummaryClass* objcfull = (DataGoalSummaryClass* ) objc;
      
      *this = *objcfull;
    }
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataGoalSummaryClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGoalSummaryClass::Clone()
    {
      DataGoalSummaryClass* id = new DataGoalSummaryClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataGoalSummaryClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGoalSummaryClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmSummaryClass::EncodeThis(buffer);
  result = result && GoalSpecClass.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataGoalSummaryClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGoalSummaryClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmSummaryClass::DecodeThis(buffer);
  result = result && GoalSpecClass.DecodeThis(buffer);

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
BaseDataObject * DataGoalSummaryClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataGoalSummary();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGoalSummaryClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGoalSummaryClass*& obj)
     {
     obj = new DataGoalSummaryClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataGoalSummary
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGoalSummary*& obj)
     {
     obj = new BaseDataGoalSummary;
     return obj->DecodeThis(buffer);
     }

/*S BaseDataGoalRun
 */ 
/*F BaseDataGoalRun()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataGoalRun::BaseDataGoalRun()
  : goalDebugLevelS("GoalDebug"),
    goalDebugLevel(0)
{
  Identification = GOALS_RUN_ID;
  NameTag = GOALS_RUN_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataGoalRun(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataGoalRun::BaseDataGoalRun(const BaseDataGoalRun& data)
  : BaseDataAlgorithmRun(data),
    GoalSummary(data.GoalSummary),
    GoalParameters(data.GoalParameters)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataGoalRun
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataGoalRun::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataGoalRun
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataGoalRun::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = GoalSummary.Read(in,objc,name);
  DataAlgorithmRunClass *rclass = (DataAlgorithmRunClass *) objc;
  DataSetOfObjectsClass *allowed = rclass->AlgorithmSummaryClass.PointerToAllowedClasses();
  
  result = allowed->ReplaceObjectTypes(*(GoalSummary.GoalSpec.getParameterSpecs()));
  result = result && GoalParameters.Read(in,allowed,name);
  BaseDataAlgorithmRun::Instantiate(&GoalSummary,rclass);
  
  return result;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataGoalRun
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataGoalRun::print(ostream& out) const
{
  out << "------------------GoalSummary:\n";
  GoalSummary.print(out);
  out << "------------------AlgorithmRun\n";
  BaseDataAlgorithmRun::print(out);
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataGoalRun
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataGoalRun::Clone()
{
  BaseDataGoalRun *obj = new BaseDataGoalRun;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataGoalRun
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataGoalRun::CopyClone(Identify *obj)
{
  BaseDataGoalRun *objfull = (BaseDataGoalRun *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGoalRun
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGoalRun::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmRun::EncodeThis(buffer);
  result = result && GoalSummary.EncodeThis(buffer);
  result = result && GoalParameters.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataGoalRun
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataGoalRun::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmRun::DecodeThis(buffer);
  result = result && GoalSummary.DecodeThis(buffer);
  result = result && GoalParameters.DecodeThis(buffer);

  return result;
}
 
/*F Instantiate(summary,runclass) . . . . . . . . . . . . Instantiate GoalRun
**
**  DESCRIPTION
**    summary: The Summary
**    runclass: The Run Information
**
**    The class is instantiated by:
**    - Calling the Instantiation of AlgorithmRun
**
**  REMARKS
**
*/
void BaseDataGoalRun::Instantiate(BaseDataAlgorithmSummary *summary,
                                  DataAlgorithmRunClass *runclass)
{
  NameTag = summary->NameTag;
  
  BaseDataGoalSummary *goalsum = (BaseDataGoalSummary *) summary;
  DataGoalRunClass *goalclass = (DataGoalRunClass *) runclass;
  GoalSummary = *goalsum;
  
  BaseDataAlgorithmRun::Instantiate(goalsum,goalclass);
}
 
/*F Run(instances,instancesclass,runclass)  . . . . . . . . . .  Run the goal
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The class information associated with the instances
**    runclass: The classes of the run objects
**
**    First the prerequisites are run and then the algorithm.
**
**  REMARKS
**
*/
bool BaseDataGoalRun::Run(BaseDataSetOfInstances* instances,
                          DataSetOfInstancesClass* instancesclass,
                          DataAlgorithmRunClass* runclass)
{
  if(goalDebugLevel > 1)
    {
      cout << "===== Entering Run(instances,instancesclass,runclass)\n";
      cout << runclass->NameTag;
      cout << "\n";
    }
  if(goalDebugLevel > 2)
    {
      cout << "Single Run: Summary ------------------------------------------\n";
      GoalSummary.print(cout);
      cout << "\nSingle Run: Summary ------------------------------------------\n";
    }
  runclass->SetDebugLevel(goalDebugLevel);
  
  bool result = true;
  result = result && BaseDataAlgorithmRun::Run(instances,instancesclass,runclass);
  
  if(goalDebugLevel > 1)
    {
      cout << "Single Run: Parameters ------------------------------------------\n";
      PrintParameters(cout);
      cout << "\nSingle Run: Parameters ------------------------------------------\n";
    }
  
  return result;
}
 
/*F Run(specs,instances,instancesclass,runclass)  . . .  Run the listed goals
**
**  DESCRIPTION
**    specs: The list of subgoals (GoalSpecs) to run
**    instances: The set of instances
**    instancesclass: The class information associated with the instances
**    runclass: The classes of the run objects
**
**    Each of the Subgoals (because they were derived from the current 
**    GoalRun instace) are run.
**    
**  REMARKS
**
*/
bool BaseDataGoalRun::Run(ObjectList<BaseDataGoalSpec>& specs,
                          BaseDataSetOfInstances* instances,
                          DataSetOfInstancesClass* instancesclass,
                          DataAlgorithmRunClass* runclass)
{
  bool result = true;
  
  ObjectList<BaseDataGoalSpec>::iterator spec;
  for(spec = specs.begin();
      spec != specs.end() && result;
      spec++)
    {
      result = result && Run(*spec,instances,instancesclass,runclass);
    }
  return result;
}
 
/*F Run(spec,instances,instancesclass,runclass) . . . . . . . . Run a subgoal
**
**  DESCRIPTION
**    spec: The subgoal to run
**    instances: The set of instances
**    instancesclass: The class information associated with the instances
**    runclass: The classes of the run objects
**
**    The goal specification is used to retrieve the GoalSummary (through
**    the list of goal definitions).  The GoalRun is then instantiated and run.
**    
**  REMARKS
**
*/
bool BaseDataGoalRun::Run(BaseDataGoalSpec& spec,
                          BaseDataSetOfInstances* instances,
                          DataSetOfInstancesClass* instancesclass,
                          DataAlgorithmRunClass* runclass)
{
  bool result = true;
  if(goalDebugLevel > 1)
    {
      cout << "------------- Run a Prerequisite: ------------------------\n";
      cout << spec;
      cout << "\n--------------------------------------------------------\n";
    }
  
  BaseDataGoalRun run;
  DataGoalRunClass *goalclass = (DataGoalRunClass *) runclass;
  BaseDataGoalSummary summary = goalclass->GoalDefs.GetGoalSummary(spec);
  run.goalDebugLevel = goalDebugLevel;
  
  run.Instantiate(&summary,runclass);
  if(goalDebugLevel > 2)
    {
      cout << "\n----- The Goal Summary----------------------------------\n";
      cout << run.GoalSummary;
      cout << "\n--------------------------------------------------------\n";
    }
  
  ObjectList<BaseDataGoalSpec> prereqs = run.GoalSummary.GetPrerequisites();
  if(goalDebugLevel > 0)
    {
      cout << "Prerequisites: ";
      prereqs.print(cout);
      cout << "\n";
    }
  
  run.TransferInputParameters(this,instances);
  
  result = result && run.Run(prereqs,instances,instancesclass,runclass);
  
  if(result)
    {
      ObjectList<String> notfound = run.TransferInputParameters(this,instances);

      if(goalDebugLevel > 0)
        {
	  cout << "\nParameters in Current\n";
	  PrintParameters(cout);
	  cout << "\n";
	}
      if(notfound.size() != 0)
        {
          cerr << "Not all Input Parameters Found:\n";
          notfound.print(cerr);
          cerr << "\n";
        }
      if(goalDebugLevel > 0)
        {
          cout << "Prerequisites for '" << run.NameTag << "' satisfied: running algorithm\n";
        }
      run.goalDebugLevel = goalDebugLevel;
      
      result = run.Run(instances,instancesclass,runclass);
    }
  
  if(result)
    {
      ObjectList<String> rnotfound = run.TransferBackResultParameters(this,instances);
      if(goalDebugLevel > 2)
	{
	  cout << "\n--------------------------------------------------------------------\n";
	  cout << "For Run: " << summary.NameTag;
	  cout << "\n-------------------- Parameters in run -----------------------------\n";
	  run.PrintParameters(cout);
	  cout << "\n-------------------- Parameters in Current -------------------------\n";
	  PrintParameters(cout);
	  cout << "\n--------------------------------------------------------------------\n";
	}
      
      if(rnotfound.size() != 0)
	{
	  cerr << "Not all Result Parameters Produced\n";
	  rnotfound.print(cerr);
	  cerr << "\n";
	}
    }

  return result;
}
 
/*F TransferInputParameters(run,instances)  . . . . . . . transfer parameters
**
**  DESCRIPTION
**    run: The GoalRun specification
**    instances: The set of instances
**
**  REMARKS
**
*/
ObjectList<String> BaseDataGoalRun::TransferInputParameters(BaseDataAlgorithmRun *run,
                                                            BaseDataSetOfInstances *instances)
{
  return BaseDataAlgorithmRun::TransferInputParameters(run,instances);
  
}
/*F TransferBackResultParameters(run,instances) . . . . . transfer parameters
**
**  DESCRIPTION
**    run: The GoalRun specification
**    instances: The set of instances
**    
**  REMARKS
**
*/
ObjectList<String> BaseDataGoalRun::TransferBackResultParameters(BaseDataAlgorithmRun *run,
                                                                 BaseDataSetOfInstances *instances)
{
  return BaseDataAlgorithmRun::TransferBackResultParameters(run,instances);
  
}
/*S DataGoalRunClass
 */
/*F DataGoalRunClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataGoalRunClass::DataGoalRunClass()
{
  Identification = GOALS_RUN_ID;
  NameTag = GOALS_RUN_NAME;
  SubClass = ALGORITHM_RUN_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataGoalRunClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataGoalRunClass::DataGoalRunClass(const DataGoalRunClass& data)
  : DataAlgorithmRunClass(data),
    GoalSummaryClass(data.GoalSummaryClass),
    GoalDefsClass(data.GoalDefsClass),
    GoalDefs(data.GoalDefs)
{
} 
 
/*F DataGoalRunClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataGoalRunClass::DataGoalRunClass(const int id, 
                                 const String& name,
                                 const String& descr)
  : DataAlgorithmRunClass(id,name,descr)
{
  SubClass = ALGORITHM_RUN_NAME;
  EncodeDecodeClass = GOALS_RUN_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataGoalRunClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataGoalRunClass::print(ostream& out) const
{
  DataAlgorithmRunClass::print(out);
  GoalSummaryClass.print(out);
  GoalDefs.print(out);
  GoalDefsClass.print(out);
  
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataGoalRunClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataGoalRunClass, there is no further information.
**
**  REMARKS
**
*/
bool DataGoalRunClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  //cout << "Read AlgorithmRun Class\n";
  
  bool result = DataAlgorithmRunClass::Read(in,set);
  //if(result)
  //cout << "Read GoalDefs Class\n";
  
  result = result && GoalDefsClass.Read(in,set);

  //if(result)
  //cout << "Read GoalDefs\n";
  
  result = result && GoalDefs.Read(in,&GoalDefsClass);
  
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataGoalRunClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataGoalRunClass::CopyClone(Identify *objc)
    {
      DataGoalRunClass* objcfull = (DataGoalRunClass* ) objc;
      
      *this = *objcfull;
    }
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataGoalRunClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataGoalRunClass::Clone()
    {
      DataGoalRunClass* id = new DataGoalRunClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataGoalRunClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGoalRunClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmRunClass::EncodeThis(buffer);
  result = result && GoalSummaryClass.EncodeThis(buffer);
  result = result && GoalDefs.EncodeThis(buffer);
  result = result && GoalDefsClass.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataGoalRunClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataGoalRunClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmRunClass::DecodeThis(buffer);
  result = result && GoalSummaryClass.DecodeThis(buffer);
  result = result && GoalDefs.DecodeThis(buffer);
  result = result && GoalDefsClass.DecodeThis(buffer);

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
BaseDataObject * DataGoalRunClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataGoalRun();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataGoalRunClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataGoalRunClass*& obj)
     {
     obj = new DataGoalRunClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataGoalRun
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataGoalRun*& obj)
     {
     obj = new BaseDataGoalRun;
     return obj->DecodeThis(buffer);
     }

/*S BaseDataSetOfGoalDefs
 */ 
/*F BaseDataSetOfGoalDefs()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSetOfGoalDefs::BaseDataSetOfGoalDefs()
{
  Identification = GOALS_SETOFDEFS_ID;
  NameTag = GOALS_SETOFDEFS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataSetOfGoalDefs(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataSetOfGoalDefs::BaseDataSetOfGoalDefs(const BaseDataSetOfGoalDefs& data)
  : BaseDataObject(data),
    GoalDefs(data.GoalDefs)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataSetOfGoalDefs
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataSetOfGoalDefs::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  bool result = true;
  String spec = str.ReadNext();
  if(!(spec == "SetOfGoalDefs:"))
    {
      cout << "Expected SetOfGoalDefs: (Got: ";
      cout << spec;
      cout << "\n";
      
      result = false;
    }
  
  else
    {
      NameTag = str.ReadNext();
      result = Read(in,objc,NameTag);
    }
  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataSetOfGoalDefs
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataSetOfGoalDefs::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);
  DataSetOfGoalDefsClass *sumclass = (DataSetOfGoalDefsClass *) objc;
  
  StreamObjectInput str(in,' ');
  String gname = str.ReadNext();
  while(gname == "GoalSummary:" && result)
    {
      
      gname = str.ReadNext();
      
      BaseDataGoalSummary summary;
      summary.NameTag = gname;
      
      result = result && summary.Read(in,&(sumclass->GoalSummaryClass),gname);
      
      GoalDefs[summary.GoalSpec] = summary;
      
      gname = str.ReadNext();
    }
  if(!(gname == "END"))
    {
      result = false;
      cerr << "Expected GoalSummary: or END, got";
      cerr << gname;
      cerr << "\n";
    }
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataSetOfGoalDefs
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataSetOfGoalDefs::print(ostream& out) const
{
  BaseDataObject::print(out);
  GoalDefs.print(out);
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataSetOfGoalDefs
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataSetOfGoalDefs::Clone()
{
  BaseDataSetOfGoalDefs *obj = new BaseDataSetOfGoalDefs;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataSetOfGoalDefs
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataSetOfGoalDefs::CopyClone(Identify *obj)
{
  BaseDataSetOfGoalDefs *objfull = (BaseDataSetOfGoalDefs *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSetOfGoalDefs
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSetOfGoalDefs::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && GoalDefs.EncodeThis(buffer);
  
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSetOfGoalDefs
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSetOfGoalDefs::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && GoalDefs.DecodeThis(buffer);

  return result;
}
 
/*F summary = GetGoalSummary(spec)  . . . . . . . . . . . . summary from spec
**
**  DESCRIPTION
**    spec: The goal specification
**    summary: The goal summary
**
**  REMARKS
**
*/
BaseDataGoalSummary& BaseDataSetOfGoalDefs::GetGoalSummary(BaseDataGoalSpec& spec)
{
  BaseDataGoalSummary *summary = new BaseDataGoalSummary;
 
  map<BaseDataGoalSpec,BaseDataGoalSummary,less<BaseDataGoalSpec> >::iterator iter;
  for(iter = GoalDefs.begin();
      iter != GoalDefs.end();
      iter++)
    {
      BaseDataGoalSpec g((*iter).first);
      if(spec.operator==(g))
	summary->CopyClone(&(*iter).second);
      
    }
  
  return *summary;
}
 
/*F GetPrerequisiteListReverse(specs,prereqs) 
**
**  DESCRIPTION
**    specs: The list of GoalSpecs to expand
**    prereqs: The list of prerequisites to add to
**
**  REMARKS
**
*/
void BaseDataSetOfGoalDefs::GetPrerequisiteListReverse(ObjectList<BaseDataGoalSpec>& specs, 
                                                       ObjectList<BaseDataGoalSpec>& prereqs)
{
  bool result = false;
  
  ObjectList<BaseDataGoalSpec>::iterator ilist;
  for(ilist = specs.begin();
      ilist != specs.end();
      ilist++)
    {
      BaseDataGoalSummary summary = GoalDefs[*ilist];
      result = result || summary.AddPrerequisitesToEnd(prereqs);
    }
  if(result)
    {
      ObjectList<BaseDataGoalSpec> newlist = prereqs;
      GetPrerequisiteListReverse(newlist,prereqs);
    }
}
/*S DataSetOfGoalDefsClass
 */
/*F DataSetOfGoalDefsClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataSetOfGoalDefsClass::DataSetOfGoalDefsClass()
{
  Identification = GOALS_SETOFDEFS_ID;
  NameTag = GOALS_SETOFDEFS_NAME;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataSetOfGoalDefsClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataSetOfGoalDefsClass::DataSetOfGoalDefsClass(const DataSetOfGoalDefsClass& data)
  : DataObjectClass(data),
    GoalSummaryClass(data.GoalSummaryClass)
{
} 
 
/*F DataSetOfGoalDefsClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataSetOfGoalDefsClass::DataSetOfGoalDefsClass(const int id, 
                                 const String& name,
                                 const String& descr)
  : DataObjectClass(id,name,descr)
{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = GOALS_SETOFDEFS_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataSetOfGoalDefsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataSetOfGoalDefsClass::print(ostream& out) const
{
  DataObjectClass::print(out);
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataSetOfGoalDefsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataSetOfGoalDefsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataSetOfGoalDefsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataSetOfGoalDefsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataSetOfGoalDefsClass::CopyClone(Identify *objc)
    {
      DataSetOfGoalDefsClass* objcfull = (DataSetOfGoalDefsClass* ) objc;
      
      *this = *objcfull;
    }
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataSetOfGoalDefsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataSetOfGoalDefsClass::Clone()
    {
      DataSetOfGoalDefsClass* id = new DataSetOfGoalDefsClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataSetOfGoalDefsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSetOfGoalDefsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  result = result && GoalSummaryClass.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataSetOfGoalDefsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSetOfGoalDefsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
  result = result && GoalSummaryClass.DecodeThis(buffer);

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
BaseDataObject * DataSetOfGoalDefsClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataSetOfGoalDefs();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataSetOfGoalDefsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataSetOfGoalDefsClass*& obj)
     {
     obj = new DataSetOfGoalDefsClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataSetOfGoalDefs
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataSetOfGoalDefs*& obj)
     {
     obj = new BaseDataSetOfGoalDefs;
     return obj->DecodeThis(buffer);
     }
/*S Utilities
 */
 
/*F InitialGoalObjectsEncodeDecodeRoutines()  . . . . . .  instance algorithm
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialGoalObjectsEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataGoalSpecClass,BaseDataGoalSpec,GOALS_SPEC_NAME);
  EncodeDecodeRegisterClass(DataGoalSummaryClass,BaseDataGoalSummary,GOALS_SUMMARY_NAME);
  EncodeDecodeRegisterClass(DataGoalRunClass,BaseDataGoalRun,GOALS_RUN_NAME);
  EncodeDecodeRegisterClass(DataSetOfGoalDefsClass,BaseDataSetOfGoalDefs,GOALS_SETOFDEFS_NAME);

//  bool (*toproutine)(CommBuffer&,Identify*&);
//
//  bool (*rout1)(CommBuffer&,DataGoalSpecClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout1;
//  SingleDecodeRoutine p1(GOALS_SPEC_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p1.StructureName] = p1;
//  
//  bool (*rout2)(CommBuffer&,DataGoalSummaryClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout2;
//  SingleDecodeRoutine p2(GOALS_SUMMARY_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p2.StructureName] = p2;
//  
//  bool (*rout3)(CommBuffer&,DataGoalRunClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout3;
//  SingleDecodeRoutine p3(GOALS_RUN_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p3.StructureName] = p3;
//  
//  bool (*rout4)(CommBuffer&,DataSetOfGoalDefsClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout4;
//  SingleDecodeRoutine p4(GOALS_SETOFDEFS_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p4.StructureName] = p4;
//  
//
//  String s11("Object.");
//  String s111(GOALS_SPEC_NAME);
//  s11.AppendToEnd(s111);
//  bool (*rout11)(CommBuffer&,BaseDataGoalSpec*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout11;
//  SingleDecodeRoutine p11(s11,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p11.StructureName] = p11;
//  
//  String s22("Object.");
//  String s222(GOALS_SUMMARY_NAME);
//  s22.AppendToEnd(s222);
//  bool (*rout22)(CommBuffer&,BaseDataGoalSummary*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout22;
//  SingleDecodeRoutine p22(s22,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p22.StructureName] = p22;
//  
//  String s33("Object.");
//  String s333(GOALS_RUN_NAME);
//  s33.AppendToEnd(s333);
//  bool (*rout33)(CommBuffer&,BaseDataGoalRun*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout33;
//  SingleDecodeRoutine p33(s33,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p33.StructureName] = p33;
//  
//  String s44("Object.");
//  String s444(GOALS_SETOFDEFS_NAME);
//  s44.AppendToEnd(s444);
//  bool (*rout44)(CommBuffer&,BaseDataSetOfGoalDefs*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout44;
//  SingleDecodeRoutine p44(s44,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p44.StructureName] = p44;
  
}
 
/*F AddGoalObjectsClasses(set)  . . . . . . . . . . . . . add classes to list
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AddGoalObjectsClasses(DataSetOfObjectsClass& set)
{
  String specdescr("The Goal Specification");
  String summarydescr("The Goal Summary Specification");
  String rundescr("The Goal Run Specification");
  String setdescr("The Goal Defs Specification");

  DataGoalSpecClass specclass(GOALS_SPEC_ID,GOALS_SPEC_NAME,specdescr);
  DataGoalSummaryClass summaryclass(GOALS_SUMMARY_ID,GOALS_SUMMARY_NAME,summarydescr);
  DataGoalRunClass runclass(GOALS_RUN_ID,GOALS_RUN_NAME,rundescr);
  DataSetOfGoalDefsClass setclass(GOALS_SETOFDEFS_ID,GOALS_SETOFDEFS_NAME,setdescr);

  set.AddObjectClass(specclass);
  set.AddObjectClass(summaryclass);
  set.AddObjectClass(runclass);
  set.AddObjectClass(setclass);
  
}
/*S GoalSystemSave
 */
/*F CommandSetUp()  . . . . . . . . . . . . . . . . . . . AlgorithmSystemSave
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void GoalSystemSave::CommandSetUp()
{
  AlgorithmSystemSave::CommandSetUp();
  
  SingleSystemCommand readcom("RunGoal",
			      "Run Goal",
			      &RunGoal);
  Commands.AddObject(readcom.getName(),readcom);

  SingleSystemCommand goalclass("SetGoalClass",
				"Set the Run Goal Class",
				&SetGoalClass);
  Commands.AddObject(goalclass.getName(),goalclass);
}

/*F StandardObjectsSetUp()  . . . . . . . . . . . . . . . GoalSystemSave
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void GoalSystemSave::StandardObjectsSetUp()
{
  AlgorithmSystemSave::StandardObjectsSetUp();
  AddGoalObjectsClasses(getStandard());
}

/*F EncodeDecodeObjectsSetUp() . . . . . . . . . . . . . . GoalSystemSave
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void GoalSystemSave::EncodeDecodeObjectsSetUp()
{
  AlgorithmSystemSave::EncodeDecodeObjectsSetUp();
  InitialGoalObjectsEncodeDecodeRoutines();
}

/*F EncodeSavedObjects(buffer)  . . . . . . . . . . . . . GoalSystemSave
**
**  DESCRIPTION
**    buffer:  The 
**  REMARKS
**
*/
bool GoalSystemSave::EncodeSavedObjects(CommBuffer& buffer)
{
  bool result = AlgorithmSystemSave::EncodeSavedObjects(buffer);
  result = result && Encode(buffer,GoalClassS);
  if(!result)
    cerr << "Error in Writing Goal Encode Objects\n";
  
  return result;
}
/*F DecodeSavedObjects(buffer)
**
**  DESCRIPTION
**    buffer: 
**  REMARKS
**
*/
bool GoalSystemSave::DecodeSavedObjects(CommBuffer& buffer)
{
  bool result = AlgorithmSystemSave::DecodeSavedObjects(buffer);
  result = result && Decode(buffer,GoalClassS);
  
  return result;
}
/*F SetGoalClass(sys)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int SetGoalClass(ReactionSystemBase *sys)
{
  GoalSystemSave *system = (GoalSystemSave *) sys;
  int result = 0;
  
  if(system->Inputs.size() <  1)
    {
      cerr << "Expected:\n";
      cerr << "      GoalRun: Name of Goal run in Instances\n";
      return 1;
    }
  
  String goalS = system->GetNextInput();

  if(system->InstanceClasses.PointerToAllowedClasses()->IsInList(goalS))
    {
      system->setGoalClassName(goalS);
      cout << "Goal Class set to: " << goalS << endl;
      cout << system->getGoalClassName();
      cout << endl;
      
    }
  else 
    {
      cerr << "Goal Class not found: " << goalS << endl;
      result = SYSTEM_ERROR_RETURN;
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
int RunGoal(ReactionSystemBase *sys)
{
  DataGoalRunClass *runclass;
  BaseDataGoalSpec *goalspec;
  GoalSystemSave *system = (GoalSystemSave *) sys;
  bool result = true;
  
  if(system->Inputs.size() <  1)
    {
      cerr << "Expected:\n";
      cerr << "      GoalSpec: Name of Goal Specification in Instances\n";
      return 1;
    }
  
  String specS = system->GetNextInput();
  if(system->Inputs.size() >=  1)
    {
      String debugS = system->GetNextInput();
      unsigned int debug = debugS.ToInteger();
      system->InstanceClasses.SetDebugLevel(debug);
    }
  
  if(system->InstanceClasses.PointerToAllowedClasses()->IsInList(system->getGoalClassName()))
    {
      runclass = (DataGoalRunClass *)
	system->InstanceClasses.PointerToAllowedClasses()->GetObjectClass(system->getGoalClassName());
      if(system->Instances.IsInList(specS))
	{
	  goalspec  = (BaseDataGoalSpec *) system->Instances.GetObject(specS);
	  if(system->InstanceClasses.getDebugLevel() > 0) 
	    {
	      cout << "\nRun -------------------------------------------------------\n";
	      goalspec->print(cout);
	      cout << "\nRun -------------------------------------------------------\n";
	    }
	}
      else
	{
	  cerr << "Goal Specification not found: '" << specS << "'" << endl;
	  result = false;
	}
    }
  else
    {
      cerr << "Goal Class not found: '" << system->getGoalClassName() << "'" << endl;
      result = false;
    }
  
  if(result)
    {
      BaseDataGoalRun goalrun;
      goalrun.goalDebugLevel = system->InstanceClasses.getDebugLevel();
      if(goalrun.goalDebugLevel > 0) 
	cout << "---------- Run The Goal ---------------------------\n";
      
      goalrun.Run(*goalspec,
		  &system->Instances,
		  &system->InstanceClasses,
		  runclass);
      
      if(goalrun.goalDebugLevel > 2)
	{
	  cout << "Final Instances\n";
	  system->Instances.print(cout);
	  cout << endl;
                }
      if(goalrun.goalDebugLevel > 1)
	{
	  cout << "Final Parameters\n";
                  goalrun.PrintParameters(cout);
                  cout << endl;
	}
      int res;
      if(result)
	{
	  res = SYSTEM_NORMAL_RETURN;
	  cout << "Goal Executed Successfully\n";
	}
      else
	{
	  res = SYSTEM_ERROR_RETURN;
	  cout << "Goal Not Successful\n";
	}
    }
  return result;
}
