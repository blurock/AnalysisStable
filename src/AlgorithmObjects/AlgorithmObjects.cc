/*  FILE     AlgorithmObjects.cc
**  PACKAGE  AlgorithmObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "AlgorithmObjects" package.
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
#include "MenuObjects.hh"
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"

int MenuChoiceAlgorithmTree(ReactionSystemBase *sys);

/*S Utilities
*/
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool CheckInputVariable(const String& name, const String& descr, BaseDataAlgorithmRun *run)
{
  bool result = true;
  if(!run->ParameterInList(name))
    {
      cerr << "The " << descr << " parameter '" << name << "' was not in the list of parameters";
      result = false;
    }
  return result;
}
/*F ans = AlgorithmAndInstanceMultipleAlgorithms(inputs,standardclasses)  run
**
**  DESCRIPTION
**    inputs: The set of input strings
**    standardclasses: The set of standard classes 
**    ans: 0 if run successful
**
**  REMARKS
**
*/
int AlgorithmAndInstanceMultipleAlgorithms(ObjectList<String>& inputs,
						  DataSetOfObjectsClass& standardclasses)
{
  if(inputs.size() < 2)
    {
      cout << "Input:\n";
      cout << "A filename argument\n";
      cout << "Filename: AlgorithmRun Class\n";
      cout << "Filename: AlgorithmRun Definition\n";
      cout << "Filename: Initial classes of instances and parameters\n";
      cout << "Filename: Initial set of instances and parameters\n";
      cout << "Debug: T to print instances and parameters\n";
      cout << "Commands: Keywords of the commands (with given starting point in the tree)\n";
      
      return 1;
    }
  
  DataAlgorithmRunClass rclass(0,"Test","A Test Run of an Algorithm");

  String algorithmClassS = inputs.front();
  inputs.pop_front();
  OpenInputFile algorithmClass(algorithmClassS);

  String algorithmDefS = inputs.front();
  inputs.pop_front();
  OpenInputFile algorithmDef(algorithmDefS);

  String instancesClassS = inputs.front();
  inputs.pop_front();
  OpenInputFile instancesClass(instancesClassS);

  String instancesDefS = inputs.front();
  inputs.pop_front();
  OpenInputFile instancesDef(instancesDefS);

  String debugS = inputs.front();
  inputs.pop_front();
  bool debug = false;
  if(debugS == "T")
    debug = true;

  cout << "Read in Instances (and Class, of course)";
  BaseDataSetOfInstances instances;
  DataSetOfInstancesClass instancesclass;
  instancesclass.Read(instancesClass.Stream,standardclasses);
  instances.Read(instancesDef.Stream,&instancesclass);
  
  cout << "Read in Algorihthm Run Class\n";
  rclass.Read(algorithmClass.Stream,standardclasses);

  if(debug)
    {
      cout << "\n=================+++++++++++++++++++++++++++++++++++++++\n";
      cout << "The AlgorithmRun Class\n";
      rclass.print(cout);
      cout << "\n=================+++++++++++++++++++++++++++++++++++++++\n";
    }
  
  BaseDataAlgorithmRun run;
  
  cout << "Read in Algorihthm Run Class\n";
  run.Read(algorithmDef.Stream,&rclass,algorithmDefS);
  if(debug)
    {
      cout << "\n+++++++++++++++++++++++++++++++++++++++\n";
      
      cout << "The algorithm:\n";
      run.print(cout);
      cout << "\n";
      cout << "\n+++++++++++++++++++++++++++++++++++++++\n";
    }
  
  ObjectList<String> *commands = new ObjectList<String>;
  commands->ChangeTitle("Commands To Run\n");
  
  ObjectList<String> notfound = run.TransferInputParameters(&run,&instances);
  while(inputs.size() > 0)
    {
      String com = inputs.front();
      inputs.pop_front();
      String full = run.BuildFullAlgorithmCategory(com);
      commands->AddObject(full);
    }
  commands->print(cout);
  cout << "\n";
  
  run.Run(*commands,&instances,&instancesclass,&rclass);

  cout << "The Matrix Object:\n";
  BaseDataInstanceDoubleMatrix *instmat = (BaseDataInstanceDoubleMatrix *) run.ParameterValue("MatrixObject");
  instmat->print(cout);
  cout << "\n";
  
  if(debug)
    {
      cout << "\n-------------------- Finished Running Command ----------------\n";
      cout << "Final Run Parameters:\n";
      run.PrintParameters(cout);
      cout << "\n--------------------    The Instance Values   ------------------\n";
      instances.print(cout);
      cout << endl;
    }
  
  return 0;

}
/*F ans = AlgorithmAndInstanceReadIn(inputs,standardclasses) standard algorithm routine
**
**  DESCRIPTION
**    inputs: The set of input keywords
**    standardclasses: The set of standard classes
**    ans: 0 if run successful
**
**  REMARKS
**
*/
extern int AlgorithmAndInstanceReadIn(ObjectList<String>& inputs,
				      DataSetOfObjectsClass standardclasses)
{
  if(inputs.size() < 4)
    {
      cout << "Input:\n";
      cout << "Filename: AlgorithmRun Class Definition\n";
      cout << "Filename: AlgorithmRun Definition\n";
      cout << "Filename: Instance Class Definition\n";
      cout << "Filename: Set of instances\n";
      cout << "[Debug: T if to print instances and algorithms (optional)]\n";
      
      return 1;
    }
  
  String algorithmClassS = inputs.front();
  inputs.pop_front();
  OpenInputFile algorithmClassF(algorithmClassS);

  String algorithmS = inputs.front();
  inputs.pop_front();
  OpenInputFile algorithmF(algorithmS);

  String instancesClassS = inputs.front();
  inputs.pop_front();
  OpenInputFile instancesClassF(instancesClassS);

  String instancesS = inputs.front();
  inputs.pop_front();
  OpenInputFile instancesF(instancesS);

  bool debug = false;
  if(inputs.size() > 0)
    {
      String debugS = inputs.front();
      inputs.pop_front();
      if(debugS == "T")
	debug = true;
    }
  
  BaseDataSetOfInstances instances;
  DataSetOfInstancesClass instancesclass;
  DataAlgorithmRunClass rclass(0,"Test","A Test Run of an Algorithm");
  BaseDataAlgorithmRun run;

  cout << "*****************************************************************************\n";
  cout << "Read in Instances Class\n";
  bool result = instancesclass.Read(instancesClassF.Stream,standardclasses);
  if(!result)
    {
      cout << "Read in of Class Unsuccessful\n";
    }

  if(result)
    {
      cout << "*****************************************************************************\n";
      cout << "Read in Instances\n";

      result = result && instances.Read(instancesF.Stream,&instancesclass,standardclasses.NameTag);
      if(result)
	{
	  if(debug)
	    {
	      cout << "Algorithm: ====================================================\n";
	      instances.print(cout);
	      cout << "\n";
	      cout << "Algorithm: ====================================================\n";
	    }
	}
      else
	{
	  cout << "Unsuccessful read of Instance Information\n";
	}
    }
    
  if(result)
    {
      cout << "*****************************************************************************\n";
      cout << "Read in Algorihthm Run Class\n";
      result = result && rclass.Read(algorithmClassF.Stream,standardclasses);
      if(result)
	{
	  if(debug)
	    {
	      cout << "Algorithm: ====================================================\n";
	      cout << "The AlgorithmRun Class\n";
	      rclass.print(cout);
	      cout << "\n";
	      cout << "Algorithm: ====================================================\n";
	    }
	}
      else
	{
	  cout << "Unsuccessful Algorithm Run Class Read\n";
	}
    }
  
  if(result)
    {
      cout << "*****************************************************************************\n";
      cout << "Read in Algorihthm Run \n";
      result = result && run.Read(algorithmF.Stream,&rclass);
      ObjectList<String> notfound = run.TransferInputParameters(&run,&instances);
      if(result)
	{
	  if(debug)
	    {
	      cout << "Algorithm: ====================================================\n";
	      cout << "Parameters not Transfered\n";
	      notfound.print(cout);
	      cout << "\n";
	  
	      cout << "The algorithm:\n";
	      run.print(cout);
	      cout << "\n";
	      cout << "Algorithm: ====================================================\n";
	    }
	}
      else
	{
	  cout << "Algorithm Read Unsuccessful\n";
	}
      
    }

  if(result)
    {
      cout << "*****************************************************************************\n";
      result = result && run.Run(&instances,&instancesclass,&rclass);
      cout << "\n";
      if(!result)
	{
	  cout << "Run Unsuccessful\n";
	}
    }
  
  return 0;
}

/*S BaseDataAlgorithmSummary
 */ 
/*F BaseDataAlgorithmSummary()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataAlgorithmSummary::BaseDataAlgorithmSummary()
{
  Identification = ALGORITHM_SUMMARY_ID;
  NameTag = ALGORITHM_SUMMARY_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  Keys.NameTag = "Algorithm Keys";
  AlgorithmKeys.NameTag = "Algorithm Selection Keys";
  Results.NameTag = "Algorithm Results";
} 
/*F BaseDataAlgorithmSummary(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataAlgorithmSummary::BaseDataAlgorithmSummary(const BaseDataAlgorithmSummary& data)
  : BaseDataObject(data),
    AlgorithmCategory(data.AlgorithmCategory),
    Keys(data.Keys),
    AlgorithmKeys(data.AlgorithmKeys),
    Parameters(data.Parameters),
    Results(data.Results)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataAlgorithmSummary
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataAlgorithmSummary::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataAlgorithmSummary
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**    The order of the read in objects is:
**    - A set of keywords to define the base algorithm category (list end with END)
**    - A set of keywords to guide the algorithm execution (list end with END)
**    - The name class pairs of the parameters (list end with END)
**    - A dummy number, The parameter name and a description (on one separete line)
**    - The set of parameters
**    - The set of result parameters
**
**  REMARKS
**
*/
bool BaseDataAlgorithmSummary::Read(istream& in, DataObjectClass* objc, const String& name)
{
  DataAlgorithmSummaryClass *sumclass = (DataAlgorithmSummaryClass *) objc;
  String sumname(name);
  
  bool result = BaseDataObject::Read(in,objc,name);
  StreamObjectInput str(in,' ');
  
  BaseDataKeyWords categories;
  String keyname("KeyWords.");
  keyname.AppendToEnd(sumname);
  categories.Read(in,&(sumclass->KeyWordClass),keyname);
  AlgorithmCategory = categories.BuildCategoryName();
  
  result = result && Keys.Read(in,&(sumclass->KeyWordClass),keyname);
  AlgorithmKeys.Read(in,&(sumclass->KeyWordClass),keyname);

  result = result && Parameters.Read(in);

  result = result && Results.Read(in,&(sumclass->KeyWordClass),keyname);

  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataAlgorithmSummary
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataAlgorithmSummary::print(ostream& out) const
{
  BaseDataObject::print(out);
  out << endl << "Algorithm Category: ";
  out << AlgorithmCategory;
  out << endl;
  Keys.print(out);
  AlgorithmKeys.print(out);
  cout << "Parameters:" << endl;
  Parameters.print(out);
  Results.print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataAlgorithmSummary
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataAlgorithmSummary::Clone()
{
  BaseDataAlgorithmSummary *obj = new BaseDataAlgorithmSummary;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataAlgorithmSummary
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataAlgorithmSummary::CopyClone(Identify * obj)
{
  BaseDataAlgorithmSummary *objfull = (BaseDataAlgorithmSummary *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataAlgorithmSummary
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataAlgorithmSummary::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && Encode(buffer,AlgorithmCategory);
  result = result && Keys.EncodeThis(buffer);
  result = result && AlgorithmKeys.EncodeThis(buffer);
  result = result && Parameters.EncodeThis(buffer);
  result = result && Results.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataAlgorithmSummary
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataAlgorithmSummary::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && Decode(buffer,AlgorithmCategory);
  result = result && Keys.DecodeThis(buffer);
  result = result && AlgorithmKeys.DecodeThis(buffer);
  result = result && Parameters.DecodeThis(buffer);
  result = result && Results.DecodeThis(buffer);

  return result;
}
 
/*F category = GetAlgorithmCategory() . . . . . . . . . . . . .  get category
**
**  DESCRIPTION
**    category: The category of algorithms that this algorithm performs
**
**  REMARKS
**
*/
String& BaseDataAlgorithmSummary::GetAlgorithmCategory()
{
  return AlgorithmCategory;
}
/*F algkeys = GetAlgorithmKeys()  . . . . . . . . . . . .  get algorithm keys
**
**  DESCRIPTION
**    category: The category of algorithms that this algorithm performs
**
**  REMARKS
**
*/
BaseDataKeyWords& BaseDataAlgorithmSummary::GetAlgorithmKeys()
{
  return AlgorithmKeys;
}
 
/*F klist = ListOfKeyWords() . . . . . . . . . . . . . . list of key names
**
**  DESCRIPTION
**    klist: The list of valid keys
**
**  REMARKS
**
*/
ObjectList<String>& BaseDataAlgorithmSummary::ListOfKeyWords()
{
  return Keys.GetKeyWords();
}
/*F ans = KeyWordInList(keyword)  . . . . . . . .  keyword among list of Keys
**
**  DESCRIPTION
**    keyword: key to check
**    ans: True if in list
**
**  REMARKS
**
*/
bool BaseDataAlgorithmSummary::KeyWordInList(const String& keyword)
{
  return Keys.KeyWordInList(keyword);
}
/*F plist = ListOfParameterNames()  . . . . . . . . . . . . . . list of names
**
**  DESCRIPTION
**    plist: The names of the parameters
**
**  REMARKS
**
*/
ObjectList<String>& BaseDataAlgorithmSummary::ListOfParameterNames()
{
  return Parameters.ObjectNames;
}
/*F plist = ListOfResultNames() . . . . . . . . . . . . . . . . list of names
**
**  DESCRIPTION
**    plist: The names of the parameters
**
**  REMARKS
**
*/
ObjectList<String>& BaseDataAlgorithmSummary::ListOfResultNames()
{
  return Results.GetKeyWords();
}
/*F ans = ParameterInList(name) . . . . . . . . . . check if parameter exists
**
**  DESCRIPTION
**    name: The name of the parameter
**    ans: True if the parameter is in the list of parameters
**
**  REMARKS
**
*/
bool BaseDataAlgorithmSummary::ParameterInList(const String& name)
{
  bool result = true;
  ObjectList<String>::iterator pos = find(Parameters.ObjectNames.begin(),
					  Parameters.ObjectNames.end(),
					  name);
  if(pos == Parameters.ObjectNames.end())
    result = false;
  
  return result;
}
 
/*F TransferKeyWords(summary) . .  add algorithm keywords to current
**
**  DESCRIPTION
**    summary: The algorithm information
**
**  REMARKS
**
*/
void BaseDataAlgorithmSummary::TransferKeyWords(BaseDataAlgorithmSummary *summary)
{
  ObjectList<String> keys = summary->ListOfKeyWords();
  ObjectList<String>::iterator key;
  for(key = keys.begin();
      key != keys.end();
      key++)
    {
      Keys.AddKeyWord(*key);
    }
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . .  BaseDataAlgorithmSummary
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
bool BaseDataAlgorithmSummary::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  return BaseDataObject::WriteAsLine(out,objc);
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . .  BaseDataAlgorithmSummary
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
bool BaseDataAlgorithmSummary::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  DataAlgorithmSummaryClass *sumclass = (DataAlgorithmSummaryClass *) objc;
  bool result = BaseDataObject::WriteAsASCII(out,objc);

  String next;
  String category(AlgorithmCategory);
  String del("#");
  category.AppendToEnd(del);
  category.IsolateNextWord(next,'#');
  while(!category.IsEmpty())
    {
      out << next << " ";
      category.IsolateNextWord(next,'#');
      category.EliminateLeadingBlanks();
    }
  out << next << " END" << endl;
  
  result = result && Keys.WriteAsASCII(out,&sumclass->KeyWordClass);
  result = result && AlgorithmKeys.WriteAsASCII(out,&sumclass->KeyWordClass);
  Parameters.WriteAsASCII(out);
  result = result && Results.WriteAsASCII(out,&sumclass->KeyWordClass);
  
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . .  BaseDataAlgorithmSummary
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
bool BaseDataAlgorithmSummary::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  out << "\\begin{verbatim}" << endl;
  bool result = WriteAsASCII(out,objc);
  out << "\\end{verbatim}" << endl;
  
  return result;
}
 

/*S DataAlgorithmSummaryClass
 */
/*F DataAlgorithmSummaryClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataAlgorithmSummaryClass::DataAlgorithmSummaryClass()
{
  NameTag = ALGORITHM_SUMMARY_NAME;
  Identification = ALGORITHM_SUMMARY_ID;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = ALGORITHM_SUMMARY_NAME;
} 
/*F DataAlgorithmSummaryClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataAlgorithmSummaryClass::DataAlgorithmSummaryClass(const DataAlgorithmSummaryClass& data)
  : DataObjectClass(data),
    SelectClass(data.SelectClass),
    SubAlgorithms(data.SubAlgorithms),
    KeyWordClass(data.KeyWordClass)
{
} 
 
/*F DataAlgorithmSummaryClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataAlgorithmSummaryClass::DataAlgorithmSummaryClass(const int id, 
						     const String& name,
						     const String& descr)
  : DataObjectClass(id,name,descr)
{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = ALGORITHM_SUMMARY_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataAlgorithmSummaryClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataAlgorithmSummaryClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  out << "\n================DataAlgorithmSummaryClass===============\n";
  out <<   "---- The Selection Tree Class Information----\n";
  SelectClass.print(out);
  out << "\n------------- The Selection Tree ------------\n";
  SubAlgorithms.print(out);
  out << "\n";
  
  return out;
}
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . . . . . DataAlgorithmSummaryClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**    set: The set of classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataAlgorithmSummaryClass, there is no further information.
**
**    The objects read in are:
**    - The set of subalgorithms (as a SelectionTree)
**
**  REMARKS
**
*/
bool DataAlgorithmSummaryClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  
  bool result = DataObjectClass::Read(in,set);
  cout << "Read SelectClass (SelectionTreeClass)\n";
  result = result && SelectClass.Read(in,set);
  cout << "Read SubAlgorithms (SelectionTree)\n";
  unsigned int debuglevel = set.getDebugLevel();
  SelectClass.SetDebugLevel(debuglevel);
  result = result && SubAlgorithms.Read(in,&SelectClass,set.NameTag);
  cout << "====== After Reading SubAlgorithms: '";
  cout << NameTag << "'" << endl;
  
  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataAlgorithmSummaryClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataAlgorithmSummaryClass::CopyClone(Identify *  objc)
{
  DataAlgorithmSummaryClass *objcfull = (DataAlgorithmSummaryClass *) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataAlgorithmSummaryClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataAlgorithmSummaryClass::Clone()
{
  DataAlgorithmSummaryClass* id = new DataAlgorithmSummaryClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataAlgorithmSummaryClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataAlgorithmSummaryClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  result = result && SelectClass.EncodeThis(buffer);
  result = result && SubAlgorithms.EncodeThis(buffer);
  result = result && KeyWordClass.EncodeThis(buffer);
  
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataAlgorithmSummaryClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataAlgorithmSummaryClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
  result = result && SelectClass.DecodeThis(buffer);
  result = result && SubAlgorithms.DecodeThis(buffer);
  result = result && KeyWordClass.DecodeThis(buffer);
  
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
BaseDataObject * DataAlgorithmSummaryClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataAlgorithmSummary();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataAlgorithmSummaryClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataAlgorithmSummaryClass*& obj)
{
  obj = new DataAlgorithmSummaryClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataAlgorithmSummary
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataAlgorithmSummary*& obj)
{
  obj = new BaseDataAlgorithmSummary;
  return obj->DecodeThis(buffer);
}
 
/*F subalgs = GetSubAlgorithms(in,category) . .  read in set of subalgorithms
**
**  DESCRIPTION
**    in: The input stream
**    algchoices: The algorithm choices as keywords
**    subalgs: The chosen algorithms
**
**  REMARKS
**
*/
BaseDataSelections& DataAlgorithmSummaryClass::GetSubAlgorithms(const String& category,
								BaseDataKeyWords& algchoices)
{
  ObjectList<String> *selections = SubAlgorithms.GetChoices(category);
  ObjectList<String> choices = algchoices.GetKeyWords();
  
  if(getDebugLevel() > 2)
    {
    cout << "The list of Categories: " << endl;
    selections->print(cout) << endl;
    cout << "The list of Choices: " << endl;
    choices.print(cout);
    cout << endl;
    }

  return SubAlgorithms.GetSelections(*selections,choices);
}
 
/*F pntr = PointerToAllowedClasses()  . . .  pointer to DataSetOfObjectsClass
**
**  DESCRIPTION
**    pntr: Pointer to allowed classes
**
**  REMARKS
**
*/
DataSetOfObjectsClass *DataAlgorithmSummaryClass::PointerToAllowedClasses()
{
  return SelectClass.PointerToAllowedClasses();
}
 
/*F ans = SetUpSelectionTree(treename,instances,instsclass)
**
**  DESCRIPTION
**    treename: The name of the Selection tree to use (from instances)
**    instances: the set of instances
**    instsclass: The set of instance classes
**    ans: true if successful 
**
**    This sets up the algorithm selection tree and its corresponding class.
**
**  REMARKS
**
*/
bool DataAlgorithmSummaryClass::SetUpSelectionTree(String& treename,
						   BaseDataSetOfInstances& instances,
						   DataSetOfInstancesClass& instsclass)
{
  bool result = true;
  
  if(instances.IsInList(treename))
    {
      BaseDataSelectionTree *tree = (BaseDataSelectionTree *) instances.GetObject(treename);
      SubAlgorithms.CopyClone(tree);
      unsigned int type = SubAlgorithms.GetType();
      DataSelectionTreeClass *treeclass = (DataSelectionTreeClass *) 
	instsclass.PointerToAllowedClasses()->GetObjectClass(type);
      SelectClass.CopyClone(treeclass);
    }
  else
    {
      cerr << "Selection Tree not found: " << treename << "\n";
      result = false;
    }
  return result;
}


/*S BaseDataAlgorithmRun
 */ 
/*F BaseDataAlgorithmRun()  . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataAlgorithmRun::BaseDataAlgorithmRun()
  : IDCount(0)
{
  Identification = ALGORITHM_RUN_ID;
  NameTag = ALGORITHM_RUN_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataAlgorithmRun(data)  . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataAlgorithmRun::BaseDataAlgorithmRun(const BaseDataAlgorithmRun& data)
  :  BaseDataObject(data),
     SubAlgorithms(data.SubAlgorithms),
     IntermediateResults(data.IntermediateResults),
     IDCount(0),
     AlgorithmSummary(data.AlgorithmSummary)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . .  Read in BaseDataAlgorithmRun
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataAlgorithmRun::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  bool result = Read(in,objc,NameTag);
  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . .  Read in BaseDataAlgorithmRun
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataAlgorithmRun::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);
  DataAlgorithmRunClass *runc = (DataAlgorithmRunClass *) objc;
  
  result = result && AlgorithmSummary.Read(in,&(runc->AlgorithmSummaryClass),name);
  
  Instantiate(&AlgorithmSummary,runc);

  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . .  BaseDataAlgorithmRun
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataAlgorithmRun::print(ostream& out) const
{
  BaseDataObject::print(out);
  AlgorithmSummary.print(out);
  
  out << "\n================================\n";
  SubAlgorithms.print(out);
  out << "\n";


  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . .  BaseDataAlgorithmRun
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataAlgorithmRun::Clone()
{
  BaseDataAlgorithmRun *obj = new BaseDataAlgorithmRun;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataAlgorithmRun
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataAlgorithmRun::CopyClone(Identify * obj)
{
  BaseDataAlgorithmRun *objfull = (BaseDataAlgorithmRun *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataAlgorithmRun
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataAlgorithmRun::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && AlgorithmSummary.EncodeThis(buffer);
  result = result && SubAlgorithms.EncodeThis(buffer);
  result = result && IntermediateResults.EncodeThis(buffer);
  result = result && Encode(buffer,IDCount);
  
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataAlgorithmRun
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataAlgorithmRun::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  result = result && AlgorithmSummary.DecodeThis(buffer);
  result = result && SubAlgorithms.DecodeThis(buffer);
  result = result && IntermediateResults.DecodeThis(buffer);
  result = result && Decode(buffer,IDCount);

  return result;
}
 
 
/*F ans = AddParameter(obj) . . . . . . Add attribute to intermediate results
**
**  DESCRIPTION
**    obj: Attribute to add to intermediate results
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataAlgorithmRun::AddParameter(BaseDataObject *obj)
{
  obj->Identification = IDCount;
  IDCount++;
  return IntermediateResults.AddAttribute(obj);
}
/*F ans = RemoveParameter(name) . . . . . . Add attribute to intermediate results
**
**  DESCRIPTION
**    name: Attribute name to remove from intermediate results
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataAlgorithmRun::RemoveParameter(String& name)
{
  return IntermediateResults.RemoveAttribute(name);
}
/*F obj = ParameterValue(name)  . . . . . . . . . . . . .  get parameter object
**
**  DESCRIPTION
**    name: The name of the parameter
**    obj: The parameter object
**
**  REMARKS
**
*/
BaseDataObject *BaseDataAlgorithmRun::ParameterValue(const String& name)
{
  BaseDataObject *obj = NULL;
  
  if(IntermediateResults.ObjectExists(name))
    obj = IntermediateResults.GetAttributeValue(name);
  else
    {
      cout << "Object Not found: ";
      cout << name << "\n";
      obj = new BaseDataObject;
    }
  return obj;
}
/*F ans = ParameterInList(name) . . . . . . . . . is the parameter available?
**
**  DESCRIPTION
**    name: The name of the parameter
**    ans: True if available
**
**  REMARKS
**
*/
bool BaseDataAlgorithmRun::ParameterInList(const String& name)
{
  return IntermediateResults.ObjectExists(name);
}
/*F Instantiate(summary,runclass) . . . . . . . . .  instantiate AlgorithmRun
**
**  DESCRIPTION
**    summary: The AlgorithmSummary information
**    runclass: The AlgorithmRunClass information
**
**    The AlgorithmRun is instantiated by instantiating the 
**    selected SubAlgorithms according to the keywords.
**
**  REMARKS
**
*/
void BaseDataAlgorithmRun::Instantiate(BaseDataAlgorithmSummary *summary,
				       DataAlgorithmRunClass *runclass)
{
  if(summary != &AlgorithmSummary)
    AlgorithmSummary = *summary;
  if(runclass->getDebugLevel() > 2)
    {
      cout << "Instantiate:" << summary->GetAlgorithmCategory() << endl;;
      summary->print(cout);
      cout << endl;
    }
  
  if(runclass->getDebugLevel() > 3)
    {
      cout <<
	"----------------------------------------------------------------------------------------------\n";
      runclass->AlgorithmSummaryClass.print(cout);
      cout << endl;
      cout <<
	"----------------------------------------------------------------------------------------------\n";
    }
  
  if(runclass->getDebugLevel() > 2)
    {
      cout <<
	"----------------------------------------------------------------------------------------------\n";
      cout << "GetSubAlgorithms: ";
      summary->GetAlgorithmCategory().print(cout);
      cout << "     (";
      summary->GetAlgorithmKeys().GetKeyWords().print(cout);
      cout << ")" << endl;
      cout <<
	"----------------------------------------------------------------------------------------------\n";
    }
  runclass->AlgorithmSummaryClass.SetDebugLevel(runclass->getDebugLevel());
  
  SubAlgorithms = runclass->AlgorithmSummaryClass.GetSubAlgorithms(summary->GetAlgorithmCategory(),
								   summary->GetAlgorithmKeys());
  if(runclass->getDebugLevel() > 2)
    {
      GetListOfSubAlgorithms().print(cout);
      cout << endl;
    }
  if(runclass->getDebugLevel() > 3)
    {
      GetListOfSubAlgorithms().print(cout);
  
      cout <<
	"Begin: The Sub Algorithms: --------------------------------------------------------------------------\n";
      cout << "";
      
      SubAlgorithms.print(cout);
      cout << endl;
      cout <<
	"End:   The Sub Algorithms: --------------------------------------------------------------------------\n";
    }
  
}
/*F ans = Run(algorithm,instances,instancesclass,runclass) . . . . . . . . . . . . . run algorithm
**
**  DESCRIPTION
**    algorithm: The algorithm category
**    instances: The set of instances
**    instancesclass: The classes
**    runclass: The class information of the run
**    ans: true if successful
**
**    The algorithm category is specifies the algorithm type.  For this
**    particular run, a specific algorithm was selected and will be executed.
**    The algorithm name is without the base category information of this run
**    (The full name will be built).  That means to use this, the subtree 
**    structure of the algorithm selection tree must be known.
**
**  REMARKS
**
*/
bool BaseDataAlgorithmRun::Run(const String& algorithm,
			       BaseDataSetOfInstances* instances,
			       DataSetOfInstancesClass* instancesclass,
			       DataAlgorithmRunClass* runclass)
{
  if(runclass->getDebugLevel() > 1)
    {
      cout << "The Algorithm: " << algorithm << endl;
    }
  
  BaseDataAlgorithmOperation *op = GetSubAlgorithm(algorithm);
  bool result = op->operator()(instances,instancesclass,this,runclass);
  if(runclass->getDebugLevel() > 2)
    {
      cout << "++++++++++++++++Parameters after Algorithm Run\n";
      PrintParameters(cout);
      cout << "\n++++++++++++++++Parameters after Algorithm Run\n";
    }
  
  return result;
}
 
/*F ans = Run(algorithms,instances,instancesclass,runclass)  . . . .  run a sequence of algorithms
**
**  DESCRIPTION
**    algorithms: The list of algorithm categories (see Run(algorithm,...) for name details
**    instances: The set of instances
**    instancesclass: The classes
**    runclass: The class information of the run
**    ans: true if successful
**
**  REMARKS
**
*/
bool BaseDataAlgorithmRun::Run(const ObjectList<String>& algorithms,
			       BaseDataSetOfInstances* instances,
			       DataSetOfInstancesClass* instancesclass,
			       DataAlgorithmRunClass* runclass)
{
  bool result = true;
  
  ObjectList<String>::const_iterator iter;
  for(iter=algorithms.begin();iter!=algorithms.end();iter++)
    {
      result = result && Run(*iter,instances,instancesclass,runclass);
    }  
  return result;
}
/*F ans = Run(instances,instancesclass,runclass) . . . . . . . . . . . . . run the first algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The classes
**    runclass: The classes of the run objects
**    ans: true if successful
**
**    This routine defaults to running the first algorithm listed
**    (The rest of the algorithms are considered auxillary)
**
**  REMARKS
**
*/
bool BaseDataAlgorithmRun::Run(BaseDataSetOfInstances* instances,
			       DataSetOfInstancesClass* instancesclass,
			       DataAlgorithmRunClass* runclass)
{
  bool result = true;
  
  if(runclass->getDebugLevel() > 3)
    {
      cout << "AlgorithmRun::Run(instances,instancesclass,runclass): ";
      cout << NameTag;
      cout << "\n";
    }
  
  ObjectList<String> algs = GetListOfSubAlgorithms();
  if(runclass->getDebugLevel() > 2)
    {
      cout << "Routines: (The first is called):" << endl;
      algs.print(cout);
      cout << endl;
    }
    
  if(algs.size() >= 1)
    result = Run(algs.front(),instances,instancesclass,runclass);
  else
    cout << "No Routine Specified\n";
  return result;
}
 
/*F fullname = BuildFullAlgorithmCategory(cat)   full name from category name
**
**  DESCRIPTION
**    category: The algorithm category
**    fullname: The name under which the algorithm is stored in the list of algorithms
**
**    The algorithms are stored under their full path names.  The front part of the path 
**    has to be added get the corresponding category name
**
**  REMARKS
**
*/
String& BaseDataAlgorithmRun::BuildFullAlgorithmCategory(const String& category)
{
  String *name = new String(AlgorithmSummary.GetAlgorithmCategory());
  String delimitor("#");
  
  String cat(category);
  name->AppendToEnd(delimitor);
  name->AppendToEnd(cat);
  return *name;
}
 
/*F ans = WriteAsLine(out,objc)  . . . . . . . . . . . . . . . . .  BaseDataObject
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
bool BaseDataAlgorithmRun::WriteAsLine(ostream& out, DataObjectClass *objc)
{
    return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . . . . .  BaseDataObject
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
bool BaseDataAlgorithmRun::WriteAsASCII(ostream&, DataObjectClass*)
{
    return true;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . . . . . .  BaseDataObject
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
bool BaseDataAlgorithmRun::WriteAsLatex(ostream& out, DataObjectClass*)
{
    return true;
}

/*F names = GetListOfSubAlgorithms()  . . . . . . . . . list of subalgorithms
**
**  DESCRIPTION
**    names: The list of names
**
**  REMARKS
**
*/
ObjectList<String> BaseDataAlgorithmRun::GetListOfSubAlgorithms()
{
  return SubAlgorithms.GetListOfSelections();
}
/*F subalg = GetSubAlgorithm(name)  . . . . . . . . . the subalgorithm
**
**  DESCRIPTION
**   name: The name of the subalgorithm category
**   subalg: The subalgorithm
**
**  REMARKS
**
*/
BaseDataAlgorithmOperation* BaseDataAlgorithmRun::GetSubAlgorithm(const String& name)
{
  return (BaseDataAlgorithmOperation *) SubAlgorithms.GetSelectedObject(name);
}
 
/*F notfound = TransferInputParameters(run,instances) . . . . . transfer to current run
**
**  DESCRIPTION
**    run: The run information
**    instances: The set of instances
**    notfound: The parameters not found
**
**    This transfers parameters that are to be used in the current run.
**
**    This transfers the input parameters
**    from the input run to the current run.  The parameters
**    that are transfered are those listed in the summary of the 
**    current run.
**
**  REMARKS
**
*/
ObjectList<String> BaseDataAlgorithmRun::TransferInputParameters(BaseDataAlgorithmRun *run,
								 BaseDataSetOfInstances* instances)
{
  AlgorithmSummary.TransferKeyWords(&(run->AlgorithmSummary));

  ObjectList<String> namelist = AlgorithmSummary.ListOfParameterNames();
  ObjectList<String>::iterator name;
  ObjectList<String> notfound;
  
  for(name = namelist.begin();
      name != namelist.end();
      name++)
    {
      if(run->ParameterInList(*name))
	{
	  BaseDataObject *object = run->ParameterValue(*name);
	  AddParameter(object);
	}
      else if(instances->IsInList(*name))
	{
	  BaseDataObject *object = instances->GetObject(*name);
	  AddParameter(object);
	}
      else
	{
	  notfound.AddObject(*name);
	}
    }
  return notfound;
}
 
/*F notfound = TransferBackResultParameters(,instances) . . . . . . .  return result parameters
**
**  DESCRIPTION
**    run: The run information
**    instances: The set of instances
**    notfound: Those parameters not found (i.e. not generated)
**
**    This transfers the information created by the current run to 
**    that of the listed run.
**
**  REMARKS
**
*/
ObjectList<String> BaseDataAlgorithmRun::TransferBackResultParameters(BaseDataAlgorithmRun *     ,
								      BaseDataSetOfInstances *instances)
{
  ObjectList<String> namelist = AlgorithmSummary.ListOfResultNames();
  ObjectList<String>::iterator name;
  ObjectList<String> notfound;
  
  for(name = namelist.begin();
      name != namelist.end();
      name++)
    {
      if(IntermediateResults.ObjectExists(*name))
	{
	  BaseDataObject *object = ParameterValue(*name);
	  instances->AddObject(object);
	}
      else
	{
	  cerr << "Parameter not found in Intermediate results: '" << *name << "'" << endl;
	  notfound.AddObject(*name);
	}
    } 
  return notfound;
}
 
/*F PrintParameters(out)  . . . . . . . . . . .  print out list of parameters
**
**  DESCRIPTION
**    out: The output stream
**
**  REMARKS
**
*/
void BaseDataAlgorithmRun::PrintParameters(ostream& out)
{
  IntermediateResults.print(out);
}
/*S DataAlgorithmRunClass
 */
/*F DataAlgorithmRunClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataAlgorithmRunClass::DataAlgorithmRunClass()
{
  NameTag = ALGORITHM_RUN_NAME;
  Identification = ALGORITHM_RUN_ID;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = ALGORITHM_RUN_NAME;
} 
/*F DataAlgorithmRunClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataAlgorithmRunClass::DataAlgorithmRunClass(const DataAlgorithmRunClass& data)
  : DataObjectClass(data),
    AlgorithmSummaryClass(data.AlgorithmSummaryClass)
     // the rest
{
} 
 
/*F DataAlgorithmRunClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataAlgorithmRunClass::DataAlgorithmRunClass(const int id, 
					     const String& name,
					     const String& descr)
  : DataObjectClass(id,name,descr)
{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = ALGORITHM_RUN_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataAlgorithmRunClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataAlgorithmRunClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  AlgorithmSummaryClass.print(out);
  
  out << NameTag << "  ";
  // the rest
       
       return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . . . . . DataAlgorithmRunClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataAlgorithmRunClass, there is no further information.
**
**  REMARKS
**
*/
bool DataAlgorithmRunClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataObjectClass::Read(in,set);
  result = result && AlgorithmSummaryClass.Read(in,set);
  cout << "====== After Reading AlgorithmSummary: '";
  cout << NameTag << "'" << endl;
  

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataAlgorithmRunClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataAlgorithmRunClass::CopyClone(Identify * objc)
{
  DataAlgorithmRunClass *objcfull = (DataAlgorithmRunClass *) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataAlgorithmRunClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataAlgorithmRunClass::Clone()
{
  DataAlgorithmRunClass* id = new DataAlgorithmRunClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataAlgorithmRunClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataAlgorithmRunClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  result = result && AlgorithmSummaryClass.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataAlgorithmRunClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataAlgorithmRunClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
  result = result && AlgorithmSummaryClass.DecodeThis(buffer);

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
BaseDataObject * DataAlgorithmRunClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataAlgorithmRun();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataAlgorithmRunClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataAlgorithmRunClass*& obj)
{
  obj = new DataAlgorithmRunClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataAlgorithmRun
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataAlgorithmRun*& obj)
{
  obj = new BaseDataAlgorithmRun;
  return obj->DecodeThis(buffer);
}

/*S BaseDataAlgorithmOperation
 */ 
/*F BaseDataAlgorithmOperation()  . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataAlgorithmOperation::BaseDataAlgorithmOperation()
  : debugPrintS("DebugLevel"),
    debugPrint(0)
{
  Identification = ALGORITHM_OPERATION_ID;
  NameTag = ALGORITHM_OPERATION_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataAlgorithmOperation(data)  . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataAlgorithmOperation::BaseDataAlgorithmOperation(const BaseDataAlgorithmOperation& data)
  : BaseDataObject(data),
    debugPrintS("DebugLevel"),
    debugPrint(0)

{
}
 
/*F Read(in,objc) . . . . . . . . . . . .  Read in BaseDataAlgorithmOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataAlgorithmOperation::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  
  
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . .  Read in BaseDataAlgorithmOperation
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataAlgorithmOperation::Read(istream& in, DataObjectClass* objc, const String& name)
{
  return BaseDataObject::Read(in,objc,name);
}
 
/*F out1 = print(out) . . . . . . . . . . . . . .  BaseDataAlgorithmOperation
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataAlgorithmOperation::print(ostream& out) const
{
  BaseDataObject::print(out);
  out << debugPrintS << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . .  BaseDataAlgorithmOperation
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataAlgorithmOperation::Clone()
{
  BaseDataAlgorithmOperation *obj = new BaseDataAlgorithmOperation;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . .  BaseDataAlgorithmOperation
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataAlgorithmOperation::CopyClone(Identify * obj)
{
  BaseDataAlgorithmOperation *objfull = (BaseDataAlgorithmOperation *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . .  BaseDataAlgorithmOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataAlgorithmOperation::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  // The rest: result = result && EncodeThis(buffer);
  // The rest: result = result && Encode(buffer,-------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . .  BaseDataAlgorithmOperation
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataAlgorithmOperation::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  // The rest: result = result && Decode(buffer,-------);
  // result = result && DecodeThis(buffer);

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
bool BaseDataAlgorithmOperation::SetUpAlgorithms(BaseDataSetOfInstances*,
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
bool BaseDataAlgorithmOperation::CheckInput(BaseDataSetOfInstances*,
					    DataSetOfInstancesClass*,
					    BaseDataAlgorithmRun*,
					    DataAlgorithmRunClass*)
{
  return true;
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
bool BaseDataAlgorithmOperation::SetUpInput(BaseDataSetOfInstances*,
					    DataSetOfInstancesClass*,
					    BaseDataAlgorithmRun*,
					    DataAlgorithmRunClass*)
{
  return true;
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
bool BaseDataAlgorithmOperation::Calculate(BaseDataSetOfInstances*,
					   DataSetOfInstancesClass*,
					   BaseDataAlgorithmRun*,
					   DataAlgorithmRunClass*)
{
  return true;
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
bool BaseDataAlgorithmOperation::WriteOutputValues(BaseDataSetOfInstances*,
						   DataSetOfInstancesClass*,
						   BaseDataAlgorithmRun*,
						   DataAlgorithmRunClass*)
{
  return true;
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
bool BaseDataAlgorithmOperation::ConcludeRun(BaseDataSetOfInstances*,
					     DataSetOfInstancesClass*,
					     BaseDataAlgorithmRun*,
					     DataAlgorithmRunClass*)
{
  return true;
}
/*F operator()(instances,instancesclass,run,runclass) . . . . . . . algorithm
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
bool BaseDataAlgorithmOperation::operator()(BaseDataSetOfInstances* instances,
					    DataSetOfInstancesClass* instancesclass,
					    BaseDataAlgorithmRun* run,
					    DataAlgorithmRunClass* runclass)
{
  if(runclass->getDebugLevel() > 2)
    {
      cout << "Operation: ";
      cout << run->NameTag;
      cout << " (Class Info: " << runclass->NameTag << ")\n";
    }

  DataObjectClass *objclass = 
    instancesclass->PointerToAllowedClasses()->GetObjectClass(GetType());
  if(instances->IsInList(debugPrintS))
    {
      BaseDataInteger *numdebug = (BaseDataInteger *) instances->GetObject(debugPrintS);
      objclass->SetDebugLevel(numdebug->GetValue());
    }
  debugPrint = objclass->getDebugLevel();
  if(runclass->getDebugLevel() > 4)
    cout << endl << "CheckInput" << endl;
  bool result = CheckInput(instances,instancesclass,run,runclass);

  if(runclass->getDebugLevel() > 4)
    cout << endl << "SetUpAlgorithms" << endl;
  result = result && SetUpAlgorithms(instances,instancesclass,run,runclass);
  if(runclass->getDebugLevel() > 4)
    cout << endl << "SetUpInput" << endl;
  result = result && SetUpInput(instances,instancesclass,run,runclass);
  if(runclass->getDebugLevel() > 4)
    cout << endl << "Calculate" << endl;
  result = result && Calculate(instances,instancesclass,run,runclass);
  if(runclass->getDebugLevel() > 4)
    cout << endl << "WriteOutputValues" << endl;
  result = result && WriteOutputValues(instances,instancesclass,run,runclass);
  if(runclass->getDebugLevel() > 4)
    cout << endl << "ConcludeRun" << endl;
  result = result && ConcludeRun(instances,instancesclass,run,runclass);
  if(runclass->getDebugLevel() > 4)
    cout << endl << "End of Algorithm Run" << endl;

  return result;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . .  BaseDataAlgorithmOperation
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
bool BaseDataAlgorithmOperation::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  return BaseDataObject::WriteAsLine(out,objc);
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . .  BaseDataAlgorithmOperation
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
bool BaseDataAlgorithmOperation::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  return BaseDataObject::WriteAsASCII(out,objc);
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . .  BaseDataAlgorithmOperation
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
bool BaseDataAlgorithmOperation::WriteAsLatex(ostream& out, DataObjectClass* objc)
{
  return BaseDataObject::WriteAsLatex(out,objc);
}

/*S DataAlgorithmOperationClass
 */
/*F DataAlgorithmOperationClass() . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataAlgorithmOperationClass::DataAlgorithmOperationClass()
{
  NameTag = ALGORITHM_OPERATION_NAME;
  Identification = ALGORITHM_OPERATION_ID;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = ALGORITHM_OPERATION_NAME;
} 
/*F DataAlgorithmOperationClass(data) . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataAlgorithmOperationClass::DataAlgorithmOperationClass(const DataAlgorithmOperationClass& data)
  : DataObjectClass(data)
     // the rest
{
} 
 
/*F DataAlgorithmOperationClass(id,name,descr)  . . . . . . . . . constructor
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
DataAlgorithmOperationClass::DataAlgorithmOperationClass(const int id, 
							 const String& name,
							 const String& descr)
  : DataObjectClass(id,name,descr)
{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = ALGORITHM_OPERATION_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . DataAlgorithmOperationClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataAlgorithmOperationClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  out << NameTag << "  ";
  return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . DataAlgorithmOperationClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataAlgorithmOperationClass, there is no further information.
**
**  REMARKS
**
*/
bool DataAlgorithmOperationClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataObjectClass::Read(in,set);
  // the rest

       return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . DataAlgorithmOperationClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataAlgorithmOperationClass::CopyClone(Identify * objc)
{
  DataAlgorithmOperationClass *objcfull = (DataAlgorithmOperationClass *) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . DataAlgorithmOperationClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataAlgorithmOperationClass::Clone()
{
  DataAlgorithmOperationClass* id = new DataAlgorithmOperationClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . DataAlgorithmOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataAlgorithmOperationClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  // The rest: result = result && Encode(buffer,-------);
  // result = result && EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . DataAlgorithmOperationClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataAlgorithmOperationClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
  // The rest: result = result && Decode(buffer,-------);
  // result = result && DecodeThis(buffer);

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
BaseDataObject * DataAlgorithmOperationClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataAlgorithmOperation();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . DataAlgorithmOperationClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataAlgorithmOperationClass*& obj)
{
  obj = new DataAlgorithmOperationClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . .  BaseDataAlgorithmOperation
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataAlgorithmOperation*& obj)
{
  obj = new BaseDataAlgorithmOperation;
  return obj->DecodeThis(buffer);
}


/*S BaseDataTestAlgorithm
 */ 
/*F BaseDataTestAlgorithm()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataTestAlgorithm::BaseDataTestAlgorithm()
{
  Identification = ALGORITHM_TEST_ID;
  NameTag = ALGORITHM_TEST_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataTestAlgorithm(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataTestAlgorithm::BaseDataTestAlgorithm(const BaseDataTestAlgorithm& data)
  : BaseDataAlgorithmOperation(data)
{
}
 
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataTestAlgorithm
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataTestAlgorithm::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataTestAlgorithm
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataTestAlgorithm::Read(istream& in, DataObjectClass* objc, const String& name)
{
  
  // The rest of the read objects
  
       return BaseDataAlgorithmOperation::Read(in,objc,name);
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . BaseDataTestAlgorithm
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataTestAlgorithm::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  // The rest of the print objects

       return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . BaseDataTestAlgorithm
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataTestAlgorithm::Clone()
{
  BaseDataTestAlgorithm *obj = new BaseDataTestAlgorithm;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . BaseDataTestAlgorithm
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataTestAlgorithm::CopyClone(Identify * obj)
{
  BaseDataTestAlgorithm *objfull = (BaseDataTestAlgorithm *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . BaseDataTestAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataTestAlgorithm::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  // The rest: result = result && EncodeThis(buffer);
  // The rest: result = result && Encode(buffer,-------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . BaseDataTestAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataTestAlgorithm::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  // The rest: result = result && Decode(buffer,-------);
  // result = result && DecodeThis(buffer);

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
bool BaseDataTestAlgorithm::SetUpAlgorithms(BaseDataSetOfInstances*,
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
bool BaseDataTestAlgorithm::CheckInput(BaseDataSetOfInstances*,
				       DataSetOfInstancesClass*,
				       BaseDataAlgorithmRun* run,
				       DataAlgorithmRunClass*)
{
  bool result = true;
  
  if(!run->ParameterInList("Test"))
    {
      cout << "The parameter 'Test' was not in the list of parameters\n";
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
bool BaseDataTestAlgorithm::SetUpInput(BaseDataSetOfInstances*,
				       DataSetOfInstancesClass*,
				       BaseDataAlgorithmRun* run,
				       DataAlgorithmRunClass*)
{
  objTest = run->ParameterValue("Test");
  level0Parameter = run->AlgorithmSummary.KeyWordInList("Level0");
  parameterParameter = run->AlgorithmSummary.KeyWordInList("Parameter");

  return true;
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
bool BaseDataTestAlgorithm::Calculate(BaseDataSetOfInstances* instances,
				      DataSetOfInstancesClass* instancesclass,
				      BaseDataAlgorithmRun* run,
				      DataAlgorithmRunClass*)
{
  cout << "List of Possible Tests: Level0, Parameter\n";
  
  cout << "List of Test to be made\n";
  ObjectList<String> keys = run->AlgorithmSummary.ListOfKeyWords();
  keys.print(cout);
  cout << "\n";
  
  cout << ">>>>>>>>>>>>>>>>>>>>>>Level0: Print Instances and Run Definition<<<<<<<<<<<<<<<<<<<<<<<<\n";
  if(level0Parameter)
    {
      cout << instancesclass->NameTag;
      cout << "\n";
      
      cout << "--------------- The set of Instances from Algorithm Calculate -----------------\n";
      instances->print(cout);
      
      cout << "--------------- The Run Defintion and Parameters In Algorithm Calculate -------\n";
      run->print(cout);
    }
  else
    {
      cout << "Key 'Level0' not set\n";
    }
  
  cout << ">>>>>>>>>>>>>>>>>>>>>>Parameter: Parameter Test<<<<<<<<<<<<<<<<<<<<<<<<\n";
  if(parameterParameter)
    {
      cout << "The list of parameter names from summary\n";
      ObjectList<String> pnames = run->AlgorithmSummary.ListOfParameterNames();
      pnames.print(cout);
      cout << "\n";
      
      if(pnames.size() > 0)
	{
	  cout << "The first parameter value:\n";
	  String param = pnames.front();
	  BaseDataObject *paramobj = run->ParameterValue(param);
	  paramobj->print(cout);
	  cout << "\n";
	}
      else
	{
	  cout << "No Parameters Listed\n";
	}
      cout << "The Parameter 'Test'\n";
      objTest->print(cout);
      cout << "\n";
    }
  else
    {
      cout << "Key 'Parameter' not set\n";
    }
  return true;
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
bool BaseDataTestAlgorithm::WriteOutputValues(BaseDataSetOfInstances*,
					      DataSetOfInstancesClass*,
					      BaseDataAlgorithmRun*,
					      DataAlgorithmRunClass*)
{
  return true;
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
bool BaseDataTestAlgorithm::ConcludeRun(BaseDataSetOfInstances*,
					DataSetOfInstancesClass*,
					BaseDataAlgorithmRun*,
					DataAlgorithmRunClass*)
{
  delete objTest;
  
  return true;
}
/*S DataTestAlgorithmClass
 */
/*F DataTestAlgorithmClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataTestAlgorithmClass::DataTestAlgorithmClass()
{
  NameTag = ALGORITHM_TEST_NAME;
  Identification = ALGORITHM_TEST_ID;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = ALGORITHM_TEST_NAME;
} 
/*F DataTestAlgorithmClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataTestAlgorithmClass::DataTestAlgorithmClass(const DataTestAlgorithmClass& data)
  : DataAlgorithmOperationClass(data)
     // the rest
{
} 
 
/*F DataTestAlgorithmClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
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
DataTestAlgorithmClass::DataTestAlgorithmClass(const int id, 
					       const String& name,
					       const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = ALGORITHM_OPERATION_NAME;
  EncodeDecodeClass = ALGORITHM_TEST_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataTestAlgorithmClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataTestAlgorithmClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  out << NameTag << "  ";
  // the rest
	   
       return out;
}
 
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . . . . . DataTestAlgorithmClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataTestAlgorithmClass, there is no further information.
**
**  REMARKS
**
*/
bool DataTestAlgorithmClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);
  // the rest

       return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataTestAlgorithmClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataTestAlgorithmClass::CopyClone(Identify * objc)
{
  DataTestAlgorithmClass *objcfull = (DataTestAlgorithmClass *) objc;
      
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataTestAlgorithmClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataTestAlgorithmClass::Clone()
{
  DataTestAlgorithmClass* id = new DataTestAlgorithmClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataTestAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataTestAlgorithmClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  // The rest: result = result && Encode(buffer,-------);
  // result = result && EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataTestAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataTestAlgorithmClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
  // The rest: result = result && Decode(buffer,-------);
  // result = result && DecodeThis(buffer);

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
BaseDataObject * DataTestAlgorithmClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataTestAlgorithm();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataTestAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataTestAlgorithmClass*& obj)
{
  obj = new DataTestAlgorithmClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataTestAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataTestAlgorithm*& obj)
{
  obj = new BaseDataTestAlgorithm;
  return obj->DecodeThis(buffer);
}

/*S AlgorithmSystemSave
 */
 
/*F CommandSetUp()  . . . . . . . . . . . . . . . . . . . AlgorithmSystemSave
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AlgorithmSystemSave::CommandSetUp()
{
  InstanceSystemMenu::CommandSetUp();
  
  SingleSystemCommand readcom("RunAlgorithm",
			      "Run Algorithm",
			      &RunAlgorithm);
  Commands.AddObject(readcom.getName(),readcom);

  SingleSystemCommand algclass("SetAlgorithmClass",
			       "Set the Run Algorithm Class",
			       &SetAlgorithmClass);
  Commands.AddObject(algclass.getName(),algclass);

  SingleSystemCommand algtree("AlgorithmTree",
			       "Print Algorithm Tree",
			       &MenuChoiceAlgorithmTree);
  Commands.AddObject(algtree.getName(),algtree);
}
/*F StandardObjectsSetUp()  . . . . . . . . . . . . . . . AlgorithmSystemSave
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AlgorithmSystemSave::StandardObjectsSetUp()
{
  InstanceSystemMenu::StandardObjectsSetUp();
  AddBaseAlgorithmClasses(getStandard());
  AddSelectionTreeClasses(getStandard());
  AddDirectedTreeObjects(getStandard());
}

/*F EncodeDecodeObjectsSetUp() . . . . . . . . . . . . . . AlgorithmSystemSave
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AlgorithmSystemSave::EncodeDecodeObjectsSetUp()
{
  InstanceSystemMenu::EncodeDecodeObjectsSetUp();
  InitialSetOfDirectedTreesEncodeDecodeRoutines();
  InitialSetOfSelectionTreeEncodeDecodeRoutines();
  InitialSetOfAlgorithmObjectsEncodeDecodeRoutines();
}

/*F EncodeSavedObjects(buffer)  . . . . . . . . . . . . . AlgorithmSystemSave
**
**  DESCRIPTION
**    buffer:  The 
**  REMARKS
**
*/
bool AlgorithmSystemSave::EncodeSavedObjects(CommBuffer& buffer)
{
  bool result = InstanceSystemMenu::EncodeSavedObjects(buffer);
  result = result && Encode(buffer,AlgorithmClassS);
  if(!result)
    cerr << "Error in Writing Algorithm Encode Objects\n";
  
  return result;
}
/*F DecodeSavedObjects(buffer)
**
**  DESCRIPTION
**    buffer: 
**  REMARKS
**
*/
bool AlgorithmSystemSave::DecodeSavedObjects(CommBuffer& buffer)
{
  bool result = InstanceSystemMenu::DecodeSavedObjects(buffer);
  result = result && Decode(buffer,AlgorithmClassS);
  
  return result;
}
/*S StandardSystemRoutines
 */
/*F SetAlgorithmClass(sys)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int SetAlgorithmClass(ReactionSystemBase *sys)
{
  AlgorithmSystemSave *system = (AlgorithmSystemSave *) sys;
  int result = 0;
  
  if(system->Inputs.size() <  1)
    {
      cerr << "Expected:\n";
      cerr << "      AlgorithmRun: Name of Algorithm run in Instances\n";
      return 1;
    }
  
  String summaryS = system->GetNextInput();

  if(system->InstanceClasses.IsInList(summaryS))
    {
      system->setAlgorithmClassName(summaryS);
      cout << "Algorithm Run set to : ";
      cout << summaryS;
      cout << endl;
    }
  else
    {
      cerr << "The algorithm run not found: " << summaryS << endl;
    }
  
  return result;
}
/*F menutree = AddNodesToMenuTree(selecttree,menutree,nodename)
**
**  DESCRIPTION
**    selecttree: The algorithm tree
**    menutree: The menu tree representing the algorithm tree
**    node:  The name of the current node to add (and recursively the sons)
**
**  REMARKS
**
*/
static BaseDataMenuDirectedTreeObject& AddNodesToMenuTree(BaseDataSelectionTree *selecttree,
							  BaseDataMenuDirectedTreeObject& menutree,
							  String& nodename)
{
  menutree.AddNode(nodename);
  ObjectList<String> *sons = selecttree->GetSons(nodename);
  while(sons->size()> 0)
    {
      String son = sons->front();
      sons->pop_front();
      menutree.AddBond(son,nodename);
      menutree = AddNodesToMenuTree(selecttree,menutree,son);
    }
  delete sons;
  return menutree;
}
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int BuildAlgorithmTreeWindow(AlgorithmSystemSave *system)
{
  int ans = SYSTEM_NORMAL_RETURN;

  BaseDataMenuWindow window;
  DataMenuWindowClass windowclass;
  String run(system->getSysMenuCommand());
  String com(" AlgorithmTree ");
  run.AppendToEnd(com);
  DataSetOfObjectsClass *classes = system->InstanceClasses.PointerToAllowedClasses();
  String algtreename = system->getAlgorithmClassName();

  if(classes->IsInList(algtreename))
    {
      DataAlgorithmRunClass *runclass = (DataAlgorithmRunClass *)
	classes->GetObjectClass(algtreename);
      
      BaseDataSelectionTree *selecttree = &(runclass->AlgorithmSummaryClass.SubAlgorithms);
      BaseDataObject *root = selecttree->getRootNode();
      String rootname = root->NameTag;
      BaseDataMenuDirectedTreeObject menutree;
      DataMenuDirectedTreeObjectClass treeclass;
      menutree.setCommand(run);
      menutree.SetRootNode(rootname);

      menutree = AddNodesToMenuTree(selecttree,menutree,rootname);
      window.setMenuObject(&menutree);
      window.Write(cout,&treeclass);
    }
  return ans;
}

 
/*F ans = BuildAlgorithmNodeTreeObject(system,name)
**
**  DESCRIPTION
**    system: The system information
**    name: The name of the node
**
**    If the node is a terminal node, then it is an algorithm and 
**    will be displayed.
**
**  REMARKS
**
*/
static int BuildAlgorithmNodeTreeObject(AlgorithmSystemSave *system, String& name)
{
  int ans = SYSTEM_NORMAL_RETURN;

  DataSetOfObjectsClass *classes = system->InstanceClasses.PointerToAllowedClasses();
  String algtreename = system->getAlgorithmClassName();
  
  if(classes->IsInList(algtreename))
    {
      BaseDataMenuWindow window;
      DataMenuWindowClass windowclass;

      DataAlgorithmRunClass *runclass = (DataAlgorithmRunClass *)
	classes->GetObjectClass(algtreename);
      
      BaseDataSelectionTree *selecttree = &(runclass->AlgorithmSummaryClass.SubAlgorithms);
      if(selecttree->NodeInTree(name))
	{
	  BaseDataObject *node = selecttree->GetNode(name);

	  BaseDataMenuCoreObject obj;
	  DataMenuCoreObjectClass objclass;

	  obj.setAsAttributeObject(node);
	  window.setMenuObject(&obj);
	  window.Write(cout,&objclass);
	}
    }

  return ans;
}
/*F ans = MenuChoiceAlgorithmTree(sys)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int MenuChoiceAlgorithmTree(ReactionSystemBase *sys)
{
  AlgorithmSystemSave *system = (AlgorithmSystemSave *) sys;
  int ans = SYSTEM_NORMAL_RETURN;

  if(system->Inputs.size() <  1)
    {
      BuildAlgorithmTreeWindow(system);
      return ans;
    }
  String nodename = system->GetNextInput();  
  BuildAlgorithmNodeTreeObject(system,nodename);
  return ans;
}
int RunAlgorithmByName(String summaryS, String algclassname, unsigned int debug,
		       BaseDataSetOfInstances &instances,
		       DataSetOfInstancesClass &instanceclasses);

/*F RunAlgorithm(sys)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int RunAlgorithm(ReactionSystemBase *sys)
{
  AlgorithmSystemSave *system = (AlgorithmSystemSave *) sys;
  int result = 0;
  
  if(system->Inputs.size() <  1)
    {
      cerr << "Expected:\n";
      cerr << "      AlgorithmSummary: Name of Algorithm Summary in Instances\n";
      return 1;
    }
  
  String summaryS = system->GetNextInput();

  if(system->Inputs.size() >= 1)
    {
      String debugS = system->GetNextInput();
      unsigned int debug = debugS.ToInteger();
      result = RunAlgorithmByName(summaryS,system->getAlgorithmClassName(),debug,system->Instances,system->InstanceClasses);
    }
  
  return result;
}

int RunAlgorithmByName(String summaryS, String algclassname, unsigned int debug,
			 BaseDataSetOfInstances &instances,
			 DataSetOfInstancesClass &instanceclasses)
{
  int result = 0;
  if(instanceclasses.IsInList(algclassname))
     {
       DataAlgorithmRunClass *runclass = (DataAlgorithmRunClass *)
	instanceclasses.PointerToAllowedClasses()->GetObjectClass(algclassname);
      runclass->SetDebugLevel(debug);
      instanceclasses.SetDebugLevel(debug);

      if(instances.IsInList(summaryS))
	{
	  BaseDataAlgorithmSummary *summary 
	    = (BaseDataAlgorithmSummary *) instances.GetObject(summaryS);
	  BaseDataAlgorithmRun run;
	  
	  run.Instantiate(summary,runclass);
	  ObjectList<String> missing = run.TransferInputParameters(&run,
								   &instances);
	  if(missing.size() > 0)
	    {
	      cerr << "Not all Parameters found in instances:\n";
	      missing.print(cerr);
	      cerr << endl;
	      result = 1;
	    }
	  else
	    {
	      result = run.Run(&instances,
			       &instanceclasses,
			       runclass);
	      
	      ObjectList<String> bmissing = run.TransferBackResultParameters(&run,
									     &instances);
	      if(bmissing.size() > 0)
		{
		  cerr << "Not all Result Parameters found:\n";
		  bmissing.print(cerr);
		  cerr << endl;
		  result = 1;
		}
	    }
	}      
      else
	{
	  cerr << "Algorithm Summary not found: '";
	  cerr << summaryS << "'" << endl;
	  result = 1;
	}
    }
  else
    {
      cerr << "Algorithms Not Set up yet\n";
      result = 1;
    }
  return result;
}


/*S Utility
 */
/*F AddBasicAlgorithmClasses(set) . . . . . . . .  basic algorithm data types
**
**  DESCRIPTION
**    set: The set of data types
**
**  REMARKS
**
*/
void AddBaseAlgorithmClasses(DataSetOfObjectsClass& set)
{
  String algdescr("Basic Algorithm Class");
  String tstdescr("Algorithm Class Tester");
  String sumdescr("Algorithm Summary Class");
  String rundescr("Algorithm Run Class");

  DataAlgorithmSummaryClass sumclass(ALGORITHM_SUMMARY_ID,ALGORITHM_SUMMARY_NAME,sumdescr);
  DataAlgorithmRunClass runclass(ALGORITHM_RUN_ID,ALGORITHM_RUN_NAME,rundescr);
  DataAlgorithmOperationClass algclass(ALGORITHM_OPERATION_ID,ALGORITHM_OPERATION_NAME,algdescr);
  DataTestAlgorithmClass tstclass(ALGORITHM_TEST_ID,ALGORITHM_TEST_NAME,tstdescr);
  
  set.AddObjectClass(sumclass);
  set.AddObjectClass(runclass);
  set.AddObjectClass(algclass);
  set.AddObjectClass(tstclass);
}
 
/*F InitialSetOfAlgorithmObjectsEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialSetOfAlgorithmObjectsEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataAlgorithmSummaryClass,BaseDataAlgorithmSummary,ALGORITHM_SUMMARY_NAME);
  EncodeDecodeRegisterClass(DataAlgorithmRunClass,BaseDataAlgorithmRun,ALGORITHM_RUN_NAME);
  EncodeDecodeRegisterClass(DataAlgorithmOperationClass,BaseDataAlgorithmOperation,ALGORITHM_OPERATION_NAME);
  EncodeDecodeRegisterClass(DataTestAlgorithmClass,BaseDataTestAlgorithm,ALGORITHM_TEST_NAME);

//  bool (*toproutine)(CommBuffer&,Identify*&);
//
//  bool (*rout1)(CommBuffer&,DataAlgorithmSummaryClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout1;
//  SingleDecodeRoutine p1(ALGORITHM_SUMMARY_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p1.StructureName] = p1;
//
//  bool (*rout2)(CommBuffer&,DataAlgorithmRunClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout2;
//  SingleDecodeRoutine p2(ALGORITHM_RUN_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p2.StructureName] = p2;
//  
//  bool (*rout3)(CommBuffer&,DataAlgorithmOperationClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout3;
//  SingleDecodeRoutine p3(ALGORITHM_OPERATION_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p3.StructureName] = p3;
//
//  bool (*rout4)(CommBuffer&,DataTestAlgorithmClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout4;
//  SingleDecodeRoutine p4(ALGORITHM_TEST_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p4.StructureName] = p4;
//
//  String s1("Object.");
//  String s11(ALGORITHM_SUMMARY_NAME);
//  s1.AppendToEnd(s11);
//  bool (*rout11)(CommBuffer&,BaseDataAlgorithmSummary*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout11;
//  SingleDecodeRoutine p11(s1,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p11.StructureName] = p11;
//
//  String s2("Object.");
//  String s21(ALGORITHM_RUN_NAME);
//  s2.AppendToEnd(s21);
//  bool (*rout21)(CommBuffer&,BaseDataAlgorithmRun*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout21;
//  SingleDecodeRoutine p21(s2,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p21.StructureName] = p21;
//  
//  String s3("Object.");
//  String s31(ALGORITHM_OPERATION_NAME);
//  s3.AppendToEnd(s31);
//  bool (*rout31)(CommBuffer&,BaseDataAlgorithmOperation*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout31;
//  SingleDecodeRoutine p31(s3,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p31.StructureName] = p31;
//
//  String s4("Object.");
//  String s41(ALGORITHM_TEST_NAME);
//  s4.AppendToEnd(s41);
//  bool (*rout41)(CommBuffer&,BaseDataTestAlgorithm*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout41;
//  SingleDecodeRoutine p41(s4,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p41.StructureName] = p41;
}

