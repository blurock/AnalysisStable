/*  FILE     CobwebCluster.cc
**  PACKAGE  CobwebCluster
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "CobwebCluster" package.
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
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "InstanceAlgorithms.hh"
#include "DescriptionProbs.hh"
#include "PredicateObjects.hh"
#include "EvaluationTree.hh"
#include "ClusterTree.hh"
#include "CobwebCluster.hh"


ostream& PrintStringOfWidth(ostream& out, String& str, unsigned int width)
{
  unsigned int s = str.size();
  unsigned int diff = width - s;
  if(width < s) 
    diff = 0;
  out << str;
  for(unsigned int i=0;i<diff;i++)
    out << " ";
  return out;
}
/*S CobwebUtilities
 */
 
/*C DescriptionFromInstance
**
**  DESCRIPTION
**
**  REMARKS
**
*/  
class DescriptionFromInstance
{
  BaseDataInstance& Instance;
  DataInstanceClass& InstanceClass;
  BaseDataSetOfObjects* Description;
  BaseDataLogical logic;
  DataLogicalClass logclass;
  
public:
  DescriptionFromInstance(BaseDataInstance& instance,
			  DataInstanceClass& instclass,
			  BaseDataSetOfObjects* set)
    : Instance(instance),
    InstanceClass(instclass),
    Description(set)
    {
    }
  double operator()(String& description)
    {
      BaseDataOperation * opdescr = (BaseDataOperation *) Description->GetObject(description);
      opdescr->operator()(&logic,&Instance,&logclass,&InstanceClass);
      return logic.GetValue();
    }
};
/*F values = DescriptionValuesFromInstance(instance,instcalss)
**
**  DESCRIPTION
**    instance: The instance
**    instclass: The instance class
**
**    For each description predicate, the corresponding operator is called and
**    the value of the logical value is put in a double vector.
**
**  REMARKS
**
*/
VectorNumeric DescriptionValuesFromInstance(BaseDataInstance *instance,
					    DataInstanceClass *instclass,
					    BaseDataSetOfObjects *description)
{
  ObjectList<String> dlist = description->ListOfObjectNames();
  VectorNumeric values(dlist.size());
  DescriptionFromInstance calc(*instance,*instclass,description);
  transform(dlist.begin(),dlist.end(),values.begin(),calc);
  return values;
}

/*S BaseDataCobwebClusterNodeStats
 */ 
/*F BaseDataCobwebClusterNodeStats()  . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
S**
*/
BaseDataCobwebClusterNodeStats::BaseDataCobwebClusterNodeStats()
  : DescriptionProbs(NULL),
    GoalProbs(NULL),
    ProbChanges(NULL)
{
  Identification = COBWEBCLUSTER_NODESTATS_ID;
  NameTag = COBWEBCLUSTER_NODESTATS_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataCobwebClusterNodeStats(data)  . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataCobwebClusterNodeStats::BaseDataCobwebClusterNodeStats(const BaseDataCobwebClusterNodeStats& data)
  : BaseDataClusterNode(data)
{
  if(data.DescriptionProbs != NULL)
    DescriptionProbs = new VectorNumeric(*(data.DescriptionProbs));
  
  if(data.GoalProbs != NULL)
    GoalProbs = new VectorNumeric(*(data.GoalProbs));
  
  if(data.ProbChanges != NULL)
    ProbChanges = new VectorNumeric(*(data.ProbChanges));
  
}
  
/*F Read(in,objc) . . . . . . . . . .  Read in BaseDataCobwebClusterNodeStats
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterNodeStats::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  bool result = Read(in,objc,NameTag);

  return result;
}
/*F Read(in,objc,name)  . . . . . . .  Read in BaseDataCobwebClusterNodeStats
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterNodeStats::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataClusterNode::Read(in,objc,name);
  result =result && DescriptionProbs->Read(in); 
  result =result && GoalProbs->Read(in); 
  result =result && ProbChanges->Read(in);
  return result;
}
/*F out1 = print(out) . . . . . . . . . . . .  BaseDataCobwebClusterNodeStats
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataCobwebClusterNodeStats::print(ostream& out) const
{
  BaseDataClusterNode::print(out);
  if(DescriptionProbs != NULL)
    {
      out << "DescriptionProbs: "; 
      DescriptionProbs->print(out); 
      out << endl;
    }
  else
    out << "DescriptionProbs empty" << endl;
  if(GoalProbs != NULL)
    {
      out << "GoalProbs: "; 
      GoalProbs->print(out); 
      out << endl;
    }
  else
    out << "GoalProbs empty" << endl;
  if(ProbChanges != NULL)
    {
      out << "ProbChanges: ";
      ProbChanges->print(out);
      out << endl;
    }
  else
    out << "ProbChanges empty" << endl;
  
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . .  BaseDataCobwebClusterNodeStats
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataCobwebClusterNodeStats::Clone()
{
  BaseDataCobwebClusterNodeStats *obj = new BaseDataCobwebClusterNodeStats;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . .  BaseDataCobwebClusterNodeStats
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataCobwebClusterNodeStats::CopyClone(Identify * obj)
{
  BaseDataCobwebClusterNodeStats *objfull = (BaseDataCobwebClusterNodeStats *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . .  BaseDataCobwebClusterNodeStats
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterNodeStats::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataClusterNode::EncodeThis(buffer);
  String vec("VectorNumeric");
  if(DescriptionProbs != 0)
    {
      result = result && Encode(buffer,vec);
      result = result && DescriptionProbs->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);
  if(GoalProbs != 0)
    {
      result = result && Encode(buffer,vec);
      result = result && GoalProbs->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);
  if(ProbChanges != 0)
    {
      result = result && Encode(buffer,vec);
      result = result && ProbChanges->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . .  BaseDataCobwebClusterNodeStats
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterNodeStats::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataClusterNode::DecodeThis(buffer);
  String name;
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    {
      DescriptionProbs = new VectorNumeric();
      DescriptionProbs->DecodeThis(buffer);
    }
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    {
      GoalProbs = new VectorNumeric();
      GoalProbs->DecodeThis(buffer);
    }
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    {
      ProbChanges = new VectorNumeric();
      ProbChanges->DecodeThis(buffer);
    }

  return result;
}
 
/*F OutGoalInfo(out,nodeclass,prefix)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataCobwebClusterNodeStats::OutGoalInfo(ostream& out,
						 DataCobwebClusterNodeStatsClass *nodeclass,
						 String& prefix)
{
  bool first = true;
  
  unsigned int num = nodeclass->GoalNames->size();
  ObjectList<String>::iterator name = nodeclass->GoalNames->begin();
  for(unsigned int i=0; i < num; i++)
    {
      out << "%%%" << prefix;
      if(first)
	{
	  out << " Goals      : ";
	  first = false;
	}
      else
	{
	  out << "		";
	}
      out << setw(50) << *name << setw(15) << (*(GoalProbs))[i]/getInstanceCount();
      out << endl;
      
      name++;
    }
}
/*F TestNodePrint(out,nodeclass,prefix)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
double BaseDataCobwebClusterNodeStats::TestNodePrint(ostream& out,
						     BaseDataSetOfObjects& goals,
						     String& iname,
						     BaseDataInstance *instance,
						     DataInstanceClass *iclass,
						     DataCobwebClusterNodeStatsClass *nodeclass,
						     String& prefix)
{
  bool first = true;
  double diff = 0.0;
  BaseDataLogical logic;
  DataLogicalClass logclass;
  
  unsigned int num = nodeclass->GoalNames->size();
  ObjectList<String>::iterator name = nodeclass->GoalNames->begin();
  double total = 0.0;
  for(unsigned int i=0; i < num; i++)
    {
      BaseDataOperation * opdescr = (BaseDataOperation *) goals.GetObject(*name);
      if(first)
	{
	  //out << prefix << "----------------------------------------" << endl;
	  first = false;
	}
      //out << prefix;
      double gp = (*(GoalProbs))[i]/getInstanceCount();
      opdescr->operator()(&logic,instance,&logclass,iclass);
      double lp = logic.GetValue();
      total += gp;
      diff += gp*lp;
      /*
      out << setw(30) << name->c_str() << ": ";
      out << setprecision(4) << setw(7) << gp;
      out << setprecision(4) << setw(7) << lp;
      out << endl;
      */
      name++;
    }
  //out << prefix << "----------------------------------------" << endl;
  diff = diff / total;
  return diff;
}

class NodeDescription : public Identify
{
public:
  double Prob;
  double Diff;
  bool Latex;
  String Prefix;

  NodeDescription(String& name, double diff, double prob, bool latex, String& prefix)
    : Identify(name),
      Prob(prob),
      Diff(diff),
      Latex(latex),
      Prefix(prefix)
  {
  }
  NodeDescription(const NodeDescription& node)
    : Identify(node.NameTag),
      Prob(node.Prob),
      Diff(node.Diff),
      Latex(node.Latex),
      Prefix(node.Prefix)
  {
  }
  NodeDescription(){}
  virtual ~NodeDescription(){}
  virtual bool operator<(const NodeDescription& descr)
  {
    double diff = this->Diff;
    double prob = this->Prob;
    bool result = (diff*diff > descr.Diff*descr.Diff);
    if(diff == descr.Diff)
      result = (prob > descr.Prob);
    return result;
  }
  bool EncodeThis(CommBuffer& buffer){return true;};
  bool DecodeThis(CommBuffer& buffer){return true;};

  virtual bool operator==(const NodeDescription& node) const
  {
    return (Diff == node.Diff) && (Prob == node.Prob);
  }
  virtual ostream& print(ostream& out) const
  {
    if(Latex)
      {
	out << setw(50) << NameTag << "&";
	out << setw(15) << Prob << "&";
	if(!(NameTag == "CobwebRoot"))
	  out << setw(15) << Diff;
	out << " \\\\\\hline" << endl;
      }
    else
      {
	out << Prefix;
	out << setw(50) << NameTag << setw(15) << Prob;
	if(!(NameTag == "CobwebRoot"))
	  out << " (" << setw(15) << Diff << ")";
	out  << endl;
      }
    return out;
  }
};
bool Encode(CommBuffer& buffer, NodeDescription& node)
{
  return node.EncodeThis(buffer);
}
bool Decode(CommBuffer& buffer, NodeDescription& node)
{
  return node.DecodeThis(buffer);
}
ostream& operator<<(ostream& out, const NodeDescription& node)
  {
    return node.print(out);
  }

template class ObjectList<NodeDescription>;

/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataCobwebClusterNodeStats::OutDescriptionInfo(ostream& out, 
							DataCobwebClusterNodeStatsClass *nodeclass,
							double cutoff,
							String& prefix)
{
  double diff;
  unsigned int num = nodeclass->DescriptorNames->size();
  ObjectList<String>::iterator name = nodeclass->DescriptorNames->begin();
  double cutoff2 = cutoff*cutoff;
  ObjectList<NodeDescription> nodelist;
  for(unsigned int i=0;i < num; i++)
    {
      if(!(NameTag == "CobwebRoot"))
	diff = (*(ProbChanges))[i];
      else
	diff = 1.0;
      
      if(cutoff2 < diff*diff)
	{
	  double prob = (*(DescriptionProbs))[i]/getInstanceCount();
	  NodeDescription node(*name, diff, prob, true,prefix);
	  nodelist.AddObject(node);
	}
      name++;
    }
  nodelist.Sort();
  out << "%%%%---------------------------------------------------------" << endl;
  out << "\\begin{figure}" << endl;
  out << "\\begin{tabular}{|l|l|l|}" << endl;
  nodelist.print(out);
  out << "\\end{tabular}" << endl;
  out << "\\caption{Node: '" << NameTag << "' of COBWEB tree}" << endl;
  out << "\\end{tabular}" << endl;
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
ostream& BaseDataCobwebClusterNodeStats::PrintASCIINodeInfo(ostream& out,
							    String& prefix,
							    DataDirectedTreeClass *,
							    DataObjectClass * nclass,
							    BaseDataSetOfInstances&,
							    DataSetOfInstancesClass&)
{
  DataCobwebClusterNodeStatsClass *nodeclass = (DataCobwebClusterNodeStatsClass *) nclass;
  bool prtinstances = true;
  
  ObjectList<int> empty;
  ObjectList<String> strnames = 
    ElementClusterAssignment.ListOfObjectNames(empty);
  ObjectList<String>::iterator name;

  out << "\\begin{center}" << endl;
  out << setw(20) << NameTag << ": " << setw(10) << strnames.size() << " Instances " << endl;
  out << "\\end{center}" << endl;

  if(prtinstances)
    {
      out << "%%%" << prefix;
      out << " Instances:";
      for(name = strnames.begin(); name != strnames.end(); name++)
	{
	  BaseDataLogical *log = 
	    (BaseDataLogical *) ElementClusterAssignment.GetObject(*name);
	  out << "[" << *name << "," << log->GetValue() << "] ";
	}
      out << endl;
    }
  else
    {
    }
  if(DescriptionProbs != 0)
    {
      OutGoalInfo(out,nodeclass,prefix);
      OutDescriptionInfo(out,nodeclass,0.2,prefix);
    }
  
  return out;
}
/*F ans = WriteAsLine(out,objc) . . . . . . .  BaseDataCobwebClusterNodeStats
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
bool BaseDataCobwebClusterNodeStats::WriteAsLine(ostream& out, DataObjectClass *objc)
{
    return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . .  BaseDataCobwebClusterNodeStats
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
bool BaseDataCobwebClusterNodeStats::WriteAsASCII(ostream& out, DataObjectClass* objc)
{
  bool result = BaseDataClusterNode::WriteAsASCII(out,objc);
  out << "%% CobwebClusterNodeStats " << NameTag << "   Description Probabilities" << endl;
  if(DescriptionProbs != NULL)
    result = result && DescriptionProbs->WriteAsASCII(out);
  else
    out << " 0 " << endl;
  out << "%% CobwebClusterNodeStats " << NameTag << "   Goal Probabilities" << endl;
  if(GoalProbs != NULL)
    result = result && GoalProbs->WriteAsASCII(out);
  else
    out << " 0 " << endl;
  out << "%% CobwebClusterNodeStats " << NameTag << "   Probability Changes" << endl;
  if(ProbChanges != NULL)
    result = result && ProbChanges->WriteAsASCII(out);
  else
    out << " 0 " << endl;
  return result;
}
 
/*F ans = WriteAsLatex(out,objc)  . . . . . .  BaseDataCobwebClusterNodeStats
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
bool BaseDataCobwebClusterNodeStats::WriteAsLatex(ostream& out, DataObjectClass *objc)
{
  DataCobwebClusterNodeStatsClass *nodecls = (DataCobwebClusterNodeStatsClass *) objc;
  out << "\\begin{tabular}[l|l|l]\\hline" << endl;
  ObjectList<String>::iterator name;
  unsigned int count = 0;
  for(name = nodecls->DescriptorNames->begin();
      name != nodecls->DescriptorNames->end();
      name++)
    {
      out << setw(20) << *name << " & ";
      out << (*DescriptionProbs)[count] << " & ";
      out << (*ProbChanges)[count];
      out << "\\\\" << endl;
      count++;
    }
  out << "\\end{tabular}" << endl;

  out << "\\begin{tabular}[l|l]\\hline" << endl;
  count = 0;
  for(name = nodecls->GoalNames->begin();
      name != nodecls->GoalNames->end();
      name++)
    {
      out << setw(20) << *name << " & ";
      out << (*GoalProbs)[count];
      out << " \\\\  " << endl;
      count++;
    }
  out << "\\end{tabular}" << endl;

  return true;
}

/*S DataCobwebClusterNodeStatsClass
 */
/*F DataCobwebClusterNodeStatsClass() . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataCobwebClusterNodeStatsClass::DataCobwebClusterNodeStatsClass()
  : DescriptorNames(NULL),
    GoalNames(NULL)
{
  Identification = COBWEBCLUSTER_NODESTATS_ID;
  NameTag = COBWEBCLUSTER_NODESTATS_NAME;
  SubClass = CLUSTER_NODE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataCobwebClusterNodeStatsClass(data) . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataCobwebClusterNodeStatsClass::DataCobwebClusterNodeStatsClass(const DataCobwebClusterNodeStatsClass& data)
  : DataClusterNodeClass(data)
{
  if(data.GoalNames != NULL)
    GoalNames = data.GoalNames->Clone();
  else
    GoalNames = NULL;
  if(data.DescriptorNames != NULL)
    DescriptorNames = data.DescriptorNames->Clone();
  else
    DescriptorNames = NULL;
} 
 
/*F DataCobwebClusterNodeStatsClass(id,name,descr)  . . . . . . . constructor
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
DataCobwebClusterNodeStatsClass::DataCobwebClusterNodeStatsClass(const int id, 
								 const String& name,
								 const String& descr)
  : DataClusterNodeClass(id,name,descr),
    DescriptorNames(NULL),
    GoalNames(NULL)
{
  SubClass = CLUSTER_NODE_NAME;
  EncodeDecodeClass = COBWEBCLUSTER_NODESTATS_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . DataCobwebClusterNodeStatsClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataCobwebClusterNodeStatsClass::print(ostream& out) const
{
  DataClusterNodeClass::print(out);
  out << "Goal Names: ";
  if(GoalNames != NULL)
    {
      GoalNames->print(out);
      out << endl;
    }
  else
    {
      out << " None " << endl;
    }
  out << "Descriptor Names: ";
  if(DescriptorNames != NULL)
    {
      DescriptorNames->print(out);
      out << endl;
    }
  else
    {
      out << " None " << endl;
    }
  return out;
}
/*F in1 = Read(in)  . . . . . . . . . . . . . DataCobwebClusterNodeStatsClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.	For the
**    base DataCobwebClusterNodeStatsClass, there is no further information.
**
**  REMARKS
**
*/
bool DataCobwebClusterNodeStatsClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataClusterNodeClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . DataCobwebClusterNodeStatsClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataCobwebClusterNodeStatsClass::CopyClone(Identify *  objc)
{
  DataCobwebClusterNodeStatsClass *objcfull = (DataCobwebClusterNodeStatsClass *) objc;
  
  *this = *objcfull;
  if(objcfull->GoalNames != NULL)
    GoalNames = objcfull->GoalNames->Clone();
  else
    GoalNames = NULL;
  if(objcfull->DescriptorNames != NULL)
    DescriptorNames = objcfull->DescriptorNames->Clone();
  else
    DescriptorNames = NULL;

}
/*F objc = Clone()  . . . . . . . . . . . . . DataCobwebClusterNodeStatsClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataCobwebClusterNodeStatsClass::Clone()
{
  DataCobwebClusterNodeStatsClass* id = new DataCobwebClusterNodeStatsClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . DataCobwebClusterNodeStatsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataCobwebClusterNodeStatsClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataClusterNodeClass::EncodeThis(buffer);
  if(GoalNames != NULL)
    {
      String str("ObjectList");
      result = result && Encode(buffer,str);
      result = result && GoalNames->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);
  if(DescriptorNames != NULL)
    {
      String str("ObjectList");
      result = result && Encode(buffer,str);
      result = result && DescriptorNames->EncodeThis(buffer);
    }
  else
    result = result && Encode(buffer,NoStructure);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . DataCobwebClusterNodeStatsClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataCobwebClusterNodeStatsClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataClusterNodeClass::DecodeThis(buffer);
  String name;
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    {
      GoalNames = new ObjectList<String>();
      GoalNames->DecodeThis(buffer);
    }
  result = result && Decode(buffer,name);
  if(name != NoStructure)
    {
      DescriptorNames = new ObjectList<String>();
      DescriptorNames->DecodeThis(buffer);
    }

  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.	This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataCobwebClusterNodeStatsClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataCobwebClusterNodeStats();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . DataCobwebClusterNodeStatsClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataCobwebClusterNodeStatsClass*& obj)
{
  obj = new DataCobwebClusterNodeStatsClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . .  BaseDataCobwebClusterNodeStats
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataCobwebClusterNodeStats*& obj)
{
  obj = new BaseDataCobwebClusterNodeStats;
  return obj->DecodeThis(buffer);
}

/*S BaseDataCobwebClusterTree
 */ 
/*F BaseDataCobwebClusterTree() . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataCobwebClusterTree::BaseDataCobwebClusterTree()
  : SmallestNodeForAssignmentS(CLUSTER_SMALLEST_ASSIGNED),
    testInstanceNamesS(COBWEB_TESTSET),
    trainInstanceNamesS(COBWEB_TRAININGSET),
    matrixInstanceNamesS("TotalInstanceNameList"),
    GroupProbsS(COBWEB_BEST_GROUP_GROUPPROBS),
    SingleDescriptionS(COBWEB_BEST_GROUP_SINGLE),
    SingleMembershipS(COBWEB_BEST_GROUP_MEMBERSHIP),
    InGroupMeasureS(COBWEB_BEST_GROUP_INGROUP),
    ExtraGroupMeasureS(COBWEB_BEST_GROUP_EXTRAGROUP),
    measureAlgS("CobwebMeasure"),
    cobwebTreeS("CobwebClusterTree"),
    AttributeListS("AttributeNames")
{
  Identification = COBWEBCLUSTER_BASETREE_ID;
  NameTag = COBWEBCLUSTER_BASETREE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

  String dtitle("-------------------------- Tree Description ---------------------------\n");
  String gtitle("-------------------------------Tree Goals -----------------------------\n");
  String otitle("-------------------------------Tree Nodes -----------------------------\n");
  Description.setTitle(dtitle);
  Description.NameTag = "Description Base Objects";
  Goals.setTitle(gtitle);
  Goals.NameTag = "Goal Description Base Objects";
} 
/*F BaseDataCobwebClusterTree(data) . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataCobwebClusterTree::BaseDataCobwebClusterTree(const BaseDataCobwebClusterTree& data)
  : BaseDataClusterTree(data),
    SmallestNodeForAssignmentS(data.SmallestNodeForAssignmentS),
    SmallestNodeForAssignmentR(data.SmallestNodeForAssignmentR),
    SmallestNodeForAssignment(data.SmallestNodeForAssignment),
    testInstanceNamesS(data.testInstanceNamesS),
    testInstanceNames(data.testInstanceNames),
    trainInstanceNamesS(data.trainInstanceNamesS),
    trainInstanceNames(data.trainInstanceNames),
    GroupProbsS(data.GroupProbsS),
    SingleDescriptionS(data.SingleDescriptionS),
    SingleMembershipS(data.SingleMembershipS),
    Description(data.Description),
    Goals(data.Goals),
    AttributeListS(data.AttributeListS)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . Read in BaseDataCobwebClusterTree
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterTree::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . Read in BaseDataCobwebClusterTree
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterTree::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = true;
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . BaseDataCobwebClusterTree
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataCobwebClusterTree::print(ostream& out) const
{
  BaseDataClusterTree::print(out);
  out << "\n====================================================================\n";
  Goals.print(out);
  Description.print(out);
  testInstanceNames.print(out);
  trainInstanceNames.print(out);
  out << "\n====================================================================\n";

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . BaseDataCobwebClusterTree
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataCobwebClusterTree::Clone()
{
  BaseDataCobwebClusterTree *obj = new BaseDataCobwebClusterTree;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . BaseDataCobwebClusterTree
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataCobwebClusterTree::CopyClone(Identify * obj)
{
  BaseDataCobwebClusterTree *objfull = (BaseDataCobwebClusterTree *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . BaseDataCobwebClusterTree
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterTree::EncodeThis(CommBuffer& buffer)
{
  bool result = true;
  result = result && BaseDataClusterTree::EncodeThis(buffer);
  result = result && Goals.EncodeThis(buffer);
  result = result && Description.EncodeThis(buffer);
  result = result && trainInstanceNames.EncodeThis(buffer);
  result = result && testInstanceNames.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . BaseDataCobwebClusterTree
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterTree::DecodeThis(CommBuffer& buffer)
{
  bool result = true;
  result = result && BaseDataClusterTree::DecodeThis(buffer);
  result = result && Goals.DecodeThis(buffer);
  result = result && Description.DecodeThis(buffer);
  result = result && trainInstanceNames.DecodeThis(buffer);
  result = result && testInstanceNames.DecodeThis(buffer);

  return result;
}
 
 
/*F name = getTrainListName()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
String& BaseDataCobwebClusterTree::getTrainListName()
{
  return trainInstanceNamesS;
}
 
/*F setTrainListName(name)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataCobwebClusterTree::setTrainListName(String& name)
{
  trainInstanceNamesS = name;
}
/*F names = getTrainInstanceNames() . . . . . . . . . . . . list of instances
**
**  DESCRIPTION
**    names: The list of instance names
**
**  REMARKS
**
*/
BaseDataKeyWords& BaseDataCobwebClusterTree::getTrainInstanceNames()
{
  return trainInstanceNames;
}
/*F ans = setTrainInstanceNames(namesaskeys)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataCobwebClusterTree::setTrainInstanceNames(BaseDataKeyWords& namesaskeys)
{
  trainInstanceNames = namesaskeys;
  bool result = true;
  if(trainInstanceNames.GetKeyWords().size() < 1)
    result = false;
  return result;
}
/*F names = getTestInstanceNames() . . . . . . . . . . . . list of instances
**
**  DESCRIPTION
**    names: The list of instance names
**
**  REMARKS
**
*/
BaseDataKeyWords& BaseDataCobwebClusterTree::getTestInstanceNames()
{
  return testInstanceNames;
}
/*F ans = setTestInstanceNames(namesaskeys)
**
**  DESCRIPTION
**    namesaskeys: 
**  REMARKS
**
*/
bool BaseDataCobwebClusterTree::setTestInstanceNames(BaseDataKeyWords& namesaskeys)
{
  testInstanceNames = namesaskeys;
  bool result = true;
  if(testInstanceNames.GetKeyWords().size() < 1)
    {
      result = false;
      cerr << "No Test Instances Listed" << endl;
    }

  return result;
}
/*F pnt = getDescription()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSetOfObjects *BaseDataCobwebClusterTree::getDescription()
{
  return &Description;
}
/*F ans = Description(description,set) 
**
**  DESCRIPTION
**    description: The set of key names of the descriptions
**    set: The source of the descriptions
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterTree::setDescription(BaseDataKeyWords& description,
					       BaseDataSetOfObjects* set)
{
  ObjectList<String> names = description.GetKeyWords();
  bool result = false;
  ObjectList<String>::iterator name;
  BaseDataObject *obj;
  
  for(name = names.begin(); name != names.end() ; name++)
    {
      if(set->IsInList(*name))
	{
	  result = true;
	  obj = set->GetObject(*name);
	  result = Description.AddObject(obj);
	}
      else
	{
	  cerr << "Description not found: '" << *name << "'" << endl;
	  result = false;
	}
    }
  return result;
}
/*F pnt = getGoals()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSetOfObjects *BaseDataCobwebClusterTree::getGoals()
{
  return &Goals;
}
/*F ans = setGoals(goals,set)
**
**  DESCRIPTION
**    goals: The goal keywords
**    set: classes
**
**    This routine sets up the goal objects in Goal
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterTree::setGoals(BaseDataKeyWords& goals,
					 BaseDataSetOfObjects* set)
{
  ObjectList<String> names = goals.GetKeyWords();
  bool result = false;
  ObjectList<String>::iterator name;
  BaseDataObject *obj;
  
  for(name = names.begin(); name != names.end() ; name++)
    {
      if(set->IsInList(*name))
	{
	  result = true;
	  obj = set->GetObject(*name);
	  result = Goals.AddObject(obj);
	}
      else
	{
	  cerr << "Goal not found: '" << *name << endl;
	  result = false;
	}
    }
  return result;
}
/*F nclass = InitializeNodeClass(classes)
**
**  DESCRIPTION
**    classes: The possible set of classes
**
**  REMARKS
**
*/
DataClusterNodeClass *BaseDataCobwebClusterTree::InitializeNodeClass(DataSetOfObjectsClass* classes)
{
  DataCobwebClusterNodeStatsClass *nodeclass = (DataCobwebClusterNodeStatsClass *) 
    BaseDataClusterTree::InitializeNodeClass(classes);

  ObjectList<int> empty;
  BaseDataSetOfObjects *descr = getDescription();

  ObjectList<String> dnames = descr->ListOfObjectNames(empty);

  nodeclass->DescriptorNames = new ObjectList<String>(dnames);

  BaseDataSetOfObjects *goal = getGoals();

  ObjectList<String> gnames = goal->ListOfObjectNames(empty);
  nodeclass->GoalNames = new ObjectList<String>(gnames);
  
  return nodeclass;
}
 
/*F DetermineBestNode(sons,allowednode,sizelimit,treeclass)
**
**  DESCRIPTION
**    sons: The list of sons
**    treeclass: The tree class
**
**  REMARKS
**
*/
String BaseDataCobwebClusterTree::DetermineBestNode(ObjectList<String>& sons,
						    bool allownewnode, bool sizelimit,
						    DataCobwebClusterTreeClass *treeclass)
{
  String bestnode = COBWEB_ADD_INSTANCE_ALONE;
  double best = ExtraGroupMeasure->GetValue();

  VectorNumeric vec = InGroupMeasure->CurrentVector();
  ObjectList<String>::iterator son = sons.begin();

  if(!allownewnode) {
      best = vec[0];
      bestnode = *son;
    }
  
  for(unsigned int node = 0; node < sons.size();node++)
    {
      BaseDataCobwebClusterNodeStats *nodestats = (BaseDataCobwebClusterNodeStats *) Tree.GetNode(*son);
      if(best < vec[node]) {
	  if(!sizelimit || nodestats->NumberOfElementsInCluster() >= SmallestNodeSize) {
	    best = vec[node];
	    bestnode = *son;
	  }
	}
      son++;
    }
  return bestnode;
}
/*F best = DetermineBestFromNode(node,name,treeclass)
**
**  DESCRIPTION
**    node: The parent node
**    name: The name of the instance
**    treeclass: The tree class
**    name: The name of the best node from the category
**
**  REMARKS
**
*/
String BaseDataCobwebClusterTree::DetermineBestFromNode(BaseDataClusterNode *node,
							String& name, 
							bool allownewnode, bool sizelimit,
							DataClusterTreeClass *treeclass)
{
  DataCobwebClusterTreeClass *cobwebclass = (DataCobwebClusterTreeClass *) treeclass;
  ObjectList<String> *sons = Tree.GetSons(node->NameTag);
  BaseDataInstance *instance = (BaseDataInstance *) Instances->GetInstance(name);
  ComputeClusteringMeasure(node->NameTag,instance,*sons,cobwebclass);
  String bestname = DetermineBestNode(*sons,allownewnode,sizelimit,cobwebclass);
  delete sons;
  return bestname;
}
 
/*F treeclass = SetUpGlobalInformation(instances,instancesclass,run,runclass)
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**
**    This sets up temporary information for use by the helping
**    member functions of the Calculate routine.  This is done
**    so as to only send the tree class as an argument
**    
**  REMARKS
**
*/
DataClusterTreeClass *BaseDataCobwebClusterTree::SetUpGlobalInformation(BaseDataSetOfInstances* instances,
									DataSetOfInstancesClass* instancesclass,
									BaseDataAlgorithmRun *run,
									DataAlgorithmRunClass* rclass)
{
  DataCobwebClusterTreeClass *treeclass = (DataCobwebClusterTreeClass *) 
    instancesclass->PointerToAllowedClasses()->GetObjectClass(GetType());

  Instances = instances;
  Run = run;

  treeclass->RunClass = rclass;
  treeclass->Classes = instancesclass->PointerToAllowedClasses();
  treeclass->InstanceClass = (DataInstanceClass *) treeclass->Classes->GetObjectClass(INSTANCE_INSTANCE_NAME);
  treeclass->InstancesClass = instancesclass;

  return treeclass;
} 
/*F logic = InitializeMembership()
**
**  DESCRIPTION
**    logic: example for membership
**
**  REMARKS
**
*/
BaseDataLogical *BaseDataCobwebClusterTree::InitializeMembership()
{
  BaseDataContinuous *logic =  new BaseDataContinuous();
  logic->SetValue(1.0);
  return (BaseDataLogical *) logic;
}
 
/*F InitializeRootNode(treeclass)
**
**  DESCRIPTION
**    Sets up the root node with dimensions of:
**          DescriptionProbs
**          GoalProbs
**          ProbChanges
**  REMARKS
**
*/
void BaseDataCobwebClusterTree::InitializeRootNode(DataClusterTreeClass *treeclass)
{
  BaseDataClusterTree::InitializeRootNode(treeclass);

  BaseDataCobwebClusterNodeStats *rootnode =(BaseDataCobwebClusterNodeStats *) Tree.getRootNode();
      
  ObjectList<String> description = getDescription()->ListOfObjectNames();
  ObjectList<String> goals = getGoals()->ListOfObjectNames();
  rootnode->DescriptionProbs = new VectorNumeric(description.size());
  rootnode->GoalProbs = new VectorNumeric(goals.size());
  rootnode->ProbChanges = new VectorNumeric(description.size());
}
/*F ans = ComputeInstanceDescriptionMatrixFromParent(parent,treeclass)
**
**  DESCRIPTION
**    parent:  The parent node
**    treeclass: The tree class
**
**    The purpose of this routine is to setup and use the description
**       measure.  The technique is to isolate out the instances
**       from the DescriptionMatrix.
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterTree::ComputeInstanceDescriptionMatrixFromParent(BaseDataClusterNode *parent,
									   DataCobwebClusterTreeClass *treeclass)
{
  if(treeclass->RunClass->getDebugLevel() > 3)
    {
      cout << "ComputeInstanceDescriptionMatrixFromParent for node: " << parent->NameTag << endl;
    }
  ObjectList<String> ilist = parent->InstancesOnNode();
  BaseDataKeyWords *ilistkeys = new BaseDataKeyWords(ilist);
  ilistkeys->NameTag = matrixInstanceNamesS;


  String descrMatS(DESCRIPTION_MATRIX_NAME);

  BaseDataInstanceDoubleMatrix *mat = DescriptionMatrix->isolateRowsByInstanceName(ilistkeys);
  mat->NameTag = descrMatS;

  BaseDataDescriptionMatrix *descrmat = 
    new BaseDataDescriptionMatrix(mat->CurrentMatrix(),
				  mat->getInstanceNames(),
				  mat->getParameterNames());
  descrmat->NameTag = descrMatS;
  Run->AddParameter(descrmat);
  delete mat;
  delete descrmat;

  delete ilistkeys;

  return true;
}

/*F ans = ComputeInstanceDescriptionMatrix(parent,treeclass)
**
**  DESCRIPTION
**    parent:  The parent node
**    treeclass: The tree class
**
**    The purpose of this routine is to setup and use the description
**       measure (getDescriptionMeasure()).
**
**    This routine is called by InitializeIncrementClusterTree, and AddNextLevel.
**       Both have to set up the AttributeListS parameter in operation parameter list
**
**    Uses the algorithm for the description measure (getDescriptionMeasure()).  This
**    needs as input:
**          matrixInstanceNamesS (BaseDataKeyWords):  The list of instances
**                  on the parent node (parent->InstancesOnNode())
**              This parameter is removed from the parameter list after the
**              call
**          AttributeListS (BaseDataKeyWords): The list of descriptions (predicates)
**                  used to form matrix of descriptions
**              This list never changes, so it is initialized in the parameters
**              before this routine.
**
**    matrixInstanceNamesS (TotalInstanceNameList)
**    AttributeListS       (AttributeNames)
**  REMARKS
**
*/
bool BaseDataCobwebClusterTree::ComputeInstanceDescriptionMatrix(BaseDataKeyWords *ilistkeys,
								 DataCobwebClusterTreeClass *treeclass)
{
  if(treeclass->RunClass->getDebugLevel() > 4)
    {
      cout << endl << "Begin: ----------- ComputeInstanceDescriptionMatrix: Before Class ------------- " << endl;
      ilistkeys->print(cout);
      cout << endl << "End:   ----------- ComputeInstanceDescriptionMatrix: Before Class ------------- " << endl;
    }
  Run->AddParameter(ilistkeys);
  BaseDataAlgorithmOperation *descroperation = getDescriptionMeasure();
  if(treeclass->RunClass->getDebugLevel() > 4)
    {
      cout << "The Description Algorithm: " << endl;
      descroperation->print(cout);
      cout << endl;
    }
  bool result;
  result = descroperation->operator()(Instances,treeclass->InstancesClass,Run,treeclass->RunClass);
  if(!result) {
    cerr << "======================================================================" << endl;
    cerr << "Description Measure Failed: " << endl;
    Run->print(cerr);
    cerr << "======================================================================" << endl;
  }
  if(treeclass->RunClass->getDebugLevel() > 4)
    {
      cout << endl << "Begin: ------------- Parameters after run ----------------------" << endl;
      Run->PrintParameters(cout);
      cout << endl << "Begin: ------------- Parameters after run ----------------------" << endl;
    }
  Run->RemoveParameter(matrixInstanceNamesS);

  return result;
}


 
/*F alg = getClusteringMeasure()
**
**  DESCRIPTION
**    alg:The clustering algorithm
**
**  REMARKS
**
*/
BaseDataAlgorithmOperation *BaseDataCobwebClusterTree::getClusteringMeasure()
{
  return measureAlg;
}
/*F alg = getDescriptionMeasure()
**
**  DESCRIPTION
**    alg:The clustering algorithm
**
**  REMARKS
**
*/
BaseDataAlgorithmOperation *BaseDataCobwebClusterTree::getDescriptionMeasure()
{
  return descriptionAlg;
}
/*F result = ComputeClusteringMeasure(parentname,tobeadded,sons,treeclass)
**
**  DESCRIPTION
**    parentname: The name of the parent node.
**    sons: The sons of the parent
**    treeclass: The tree class information
**
**  REMARKS
**    countsmat (GroupProbsS):  The matrix of sons versus instances:
**        Row:     sons
**        Column:  The extent that the instance resides on that son
**                 (1: fully resides in node, 0: not in node)
**    singlevec (SingleDescriptionS):   From DescriptionValuesFromInstance, the list of description operations
**                is performed for each instance in the list.  The result is a vector
**                of doubles (logic values).
**    membership (SingleMemberShipS): Initial membership, usually 1.0.
**
**    The call to the clustering measure gives:
**      InGroupMeasureS: The vector of measure (corresponding to the sons)
**        which gives the cluster measure.
**      ExtraGroupMeasureS: The measure if the object is by itself.
*/
bool BaseDataCobwebClusterTree::ComputeClusteringMeasure(String& parentname,
							 BaseDataInstance *tobeadded,
							 ObjectList<String>& sons,
							 DataCobwebClusterTreeClass *treeclass)
{
  if(treeclass->RunClass->getDebugLevel() > 3)
      cout << "ComputeClusteringMeasure from node " << parentname << endl;
  // Set up description list names
  ObjectList<String> distnames = Description.ListOfObjectNames();
  BaseDataKeyWords dlistkeys(distnames);
  dlistkeys.NameTag = AttributeListS;
  // Get parent
  BaseDataClusterNode *node = (BaseDataClusterNode *) Tree.GetNode(parentname);
  // Set up matrix instance names on parent node
  ObjectList<String> ilist = node->InstancesOnNode();
  BaseDataKeyWords ilistkeys(ilist);
  ilistkeys.NameTag = matrixInstanceNamesS;

  if(treeclass->RunClass->getDebugLevel() > 4)
    {
      cout << "Description and Instance Lists" << endl;
      dlistkeys.print(cout);
      cout << endl;
      ilistkeys.print(cout);
      cout << endl;
    }
  
  MatrixNumeric nodeinstcounts = CalculateInstancesOnSubNodes(parentname,ilist);
  BaseDataInstanceDoubleMatrix countsmat(nodeinstcounts,ilistkeys,dlistkeys);
  countsmat.NameTag = GroupProbsS;

  BaseDataInstanceDoubleVector *singlevec = DescriptionMatrix->getRow(tobeadded->NameTag);
  singlevec->NameTag = SingleDescriptionS;

  BaseDataReal membership;
  membership.SetValue(1.0);
  membership.NameTag = SingleMembershipS;

  if(treeclass->RunClass->getDebugLevel() > 4)
    {
      cout << "Begin: ----------- Parameters for Computing Clustering Measure ----------- " << endl;
      countsmat.print(cout);
      cout << endl;
      singlevec->print(cout);
      cout << endl;
      membership.print(cout);
      cout << endl;
      cout << "End:   ----------- Parameters for Computing Clustering Measure ----------- " << endl;
    }
  Run->AddParameter(&countsmat);
  Run->AddParameter(singlevec);
  Run->AddParameter(&membership);
  delete singlevec;
  
  BaseDataAlgorithmOperation *measure = getClusteringMeasure();
  bool result = measure->operator()(Instances,treeclass->InstancesClass,Run,treeclass->RunClass);
  if(result) {
    InGroupMeasure = (BaseDataDoubleVector *) Run->ParameterValue(InGroupMeasureS);
    ExtraGroupMeasure = (BaseDataReal *) Run->ParameterValue(ExtraGroupMeasureS);

    if(treeclass->RunClass->getDebugLevel() > 4)
      {
	cout << "Results of Measure Call" << endl;
	InGroupMeasure->print(cout);
	cout << endl;
	ExtraGroupMeasure->print(cout);
	cout << endl;
      }
  } else {
    cerr << "Cluster Measure failed:  Nothing Computed" << endl; 
  }
  Run->RemoveParameter(GroupProbsS);
  Run->RemoveParameter(SingleDescriptionS);
  Run->RemoveParameter(SingleMembershipS);
  return result;
}  
 
/*F TransferClusterTree(tree)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void BaseDataCobwebClusterTree::TransferClusterTree(BaseDataClusterTree *tree)
{
  BaseDataClusterTree::TransferClusterTree(tree);
  BaseDataCobwebClusterTree *ntree = (BaseDataCobwebClusterTree *) tree;
  Description.CopyClone(ntree->getDescription());
  Goals.CopyClone(ntree->getGoals());
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
bool BaseDataCobwebClusterTree::SetUpAlgorithms(BaseDataSetOfInstances*,
						DataSetOfInstancesClass*,
						BaseDataAlgorithmRun *run,
						DataAlgorithmRunClass *rclass)
{
  bool result = true;
  if(rclass->getDebugLevel() > 1)
    {
      cout << "List of Algorithms" << endl;
      run->GetListOfSubAlgorithms().print(cout);
    }
  ObjectList<String> algnames = run->GetListOfSubAlgorithms();
  algnames.pop_front();

  String description = algnames.front();
  algnames.pop_front();
  descriptionAlg = run->GetSubAlgorithm(description);

  String measure = algnames.front();
  algnames.pop_front();
  measureAlg = run->GetSubAlgorithm(measure);

  if(rclass->getDebugLevel() > 1)
    {
      cout << endl << "Algorithms Selected" << endl;
      descriptionAlg->print(cout);
      cout << endl;
      measureAlg->print(cout);
      cout << endl;
    }
  return result;
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
bool BaseDataCobwebClusterTree::CheckInput(BaseDataSetOfInstances *instances,
					   DataSetOfInstancesClass *instancesclass,
					   BaseDataAlgorithmRun* run,
					   DataAlgorithmRunClass *runclass)
{
  bool result = BaseDataClusterTree::CheckInput(instances,instancesclass,
							    run,runclass);

  if(!run->ParameterInList(testInstanceNamesS))
    {
      cerr << "The parameter '" << testInstanceNamesS << "' was not in the list of parameters\n";
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
bool BaseDataCobwebClusterTree::SetUpInput(BaseDataSetOfInstances *instances,
					   DataSetOfInstancesClass *instancesclass,
					   BaseDataAlgorithmRun *run,
					   DataAlgorithmRunClass *rclass)
{
  bool result = BaseDataClusterTree::SetUpInput(instances,instancesclass,
							    run,rclass);

  BaseDataKeyWords *tlist = (BaseDataKeyWords *) run->ParameterValue(testInstanceNamesS);

  result = result && setTestInstanceNames(*tlist);

  if(instances->IsInList(SmallestNodeForAssignmentS)) {
    SmallestNodeForAssignmentR = (BaseDataReal *)
      instances->GetObject(SmallestNodeForAssignmentS);
    SmallestNodeForAssignment = SmallestNodeForAssignmentR->GetValue();
  } else {
    SmallestNodeForAssignment = 0.10;
  }
  
  if(result)
    {
      ObjectList<String> inames = getTestInstanceNames().GetKeyWords();
      ObjectList<String> traintest = getTrainInstanceNames().GetKeyWords();
      traintest.AddOnlyUniqueObjects(inames);
    } 
  else
    {
      cerr << "SetUp failed: Faulty Description" << endl;
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
bool BaseDataCobwebClusterTree::Calculate(BaseDataSetOfInstances* instances,
					  DataSetOfInstancesClass* instancesclasses,
					  BaseDataAlgorithmRun *run,
					  DataAlgorithmRunClass* rclass)
{
  TreeClass = (DataClusterTreeClass *) SetUpGlobalInformation(instances,instancesclasses,run,rclass);
  DataCobwebClusterTreeClass *tclass = (DataCobwebClusterTreeClass *) TreeClass;

  tclass->ClusterNodeAssignmentClassS  = "ClusterAssignmentClass";
  tclass->ClusterAssignmentName        = "ClusterAssignment";
  tclass->ClusterAssignmentBaseClassS  = "NValued";

  NodeClass = (DataCobwebClusterNodeStatsClass *) 
    InitializeNodeClass(tclass->Classes);
  instancesclasses->PointerToAllowedClasses()->AddObjectClass(*NodeClass);
  TreeClass->setNodeClass(NodeClass);

  return EvaluateWithCluster(tclass,instances,instancesclasses,
			     run,rclass);
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
bool BaseDataCobwebClusterTree::WriteOutputValues(BaseDataSetOfInstances*,
						  DataSetOfInstancesClass*,
						  BaseDataAlgorithmRun*,
						  DataAlgorithmRunClass*)
{
  bool result = true;
  
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
bool BaseDataCobwebClusterTree::ConcludeRun(BaseDataSetOfInstances*,
					    DataSetOfInstancesClass*,
					    BaseDataAlgorithmRun*,
					    DataAlgorithmRunClass*)
{
  bool result = true;
  
  //delete objTest;
  
  return result;
}
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataCobwebClusterTree::InitializeIncrementClusterTree(BaseDataSetOfInstances *instances,
							       DataSetOfInstancesClass *instancesclasses,
							       BaseDataAlgorithmRun *run,
							       DataAlgorithmRunClass *rclass)
{
  bool result = true;

  BaseDataCobwebClusterTree *tree = (BaseDataCobwebClusterTree *) 
    run->ParameterValue(getCobwebTreeName());
  TransferClusterTree(tree);

  DataCobwebClusterTreeClass *TreeClass = (DataCobwebClusterTreeClass *)
    SetUpGlobalInformation(instances,instancesclasses,run,rclass);

  InitializeNodeClass(TreeClass->Classes);

  BaseDataClusterNode *node = (BaseDataClusterNode *) Tree.getRootNode();

  ObjectList<String> *sons = Tree.GetSons(node->NameTag);

  ObjectList<String> dlist = getDescription()->ListOfObjectNames();

  BaseDataKeyWords dlistkeys(dlist);
  dlistkeys.NameTag = AttributeListS;
  Run->AddParameter(&dlistkeys);

  ObjectList<String> inames = getTestInstanceNames().GetKeyWords();
  ObjectList<String> traintest = getTrainInstanceNames().GetKeyWords();
  traintest.AddOnlyUniqueObjects(inames);
  BaseDataKeyWords ilist(traintest);
  ilist.NameTag = matrixInstanceNamesS;

  ComputeInstanceDescriptionMatrix(&ilist,TreeClass);

  String descrMatS(DESCRIPTION_MATRIX_NAME);
  BaseDataDescriptionMatrix *descmat = (BaseDataDescriptionMatrix *) instances->GetObject(descrMatS);
  
  DescriptionMatrix = new BaseDataDescriptionMatrix(*descmat);

  ComputeInstanceDescriptionMatrixFromParent(node,TreeClass);

  delete sons;
  return result;
} 
/*F EvaluateWithCluster()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataCobwebClusterTree::EvaluateWithCluster(DataCobwebClusterTreeClass *treeclass,
						    BaseDataSetOfInstances *instances,
						    DataSetOfInstancesClass *instancesclasses,
						    BaseDataAlgorithmRun *run,
						    DataAlgorithmRunClass *rclass)
{
  bool result = true;
  instancesclasses->SetDebugLevel(rclass->getDebugLevel());
  treeclass->RunClass->SetDebugLevel(rclass->getDebugLevel());
  InitializeIncrementClusterTree(instances,instancesclasses,
				 run,rclass);
  String pre("     :");
  //double diff = 0.0;
  String prefix("");
  DataSetOfObjectsClass *classes = instancesclasses->PointerToAllowedClasses();

  BaseDataCobwebClusterNodeStats *node = (BaseDataCobwebClusterNodeStats *) Tree.getRootNode();
  ObjectList<String> names = getTestInstanceNames().GetKeyWords();

  double total = names.size();
  SmallestNodeSize = SmallestNodeForAssignment * total;

  ObjectList<String> *sons = Tree.GetSons(node->NameTag);

  cout << "Smallest Node Size: " << SmallestNodeForAssignment << " * " << total << " = " << SmallestNodeSize << endl;

  ObjectList<String> ValidNodeNames = ValidNodesToNValued(instances,treeclass,classes);

  BaseDataSetOfObjects *levelset = LevelKeySets(getMaxLevel(),classes);

  cout << "ClusterLevelValues:" << endl;

  ObjectList<String>::iterator name;
  for(name = names.begin();name != names.end();name++) {
      if(rclass->getDebugLevel() > 1) {
	  cout << "Evaluate Instance: " << *name << endl;
	}
      BaseDataInstance *instance = (BaseDataInstance *) instances->GetInstance(*name);
      LevelValuesForInstance(instance, node, 1, getMaxLevel(),levelset,treeclass);

      /*
      unsigned int itype = instance->GetType();
      DataInstanceClass *iclass = (DataInstanceClass *) classes->GetObjectClass(itype);
      ComputeInstanceDescriptionMatrixFromParent(node,treeclass);
      String bestname = DetermineBestFromNode(node,*name,false,true,treeclass);
      BaseDataCobwebClusterNodeStats *sonnode = (BaseDataCobwebClusterNodeStats *) Tree.GetNode(bestname);
      diff += sonnode->TestNodePrint(cout,Goals,*name,instance,iclass,NodeClass,pre);

      ResultPrintout(*name, sons, bestname,pre);
      //AssignNValuedClassForNode(instance,bestname,treeclass);
      */
    }
  delete sons;
  
  SetUpPartitions(treeclass,instances,levelset,classes);
  /*
  if(names.size() > 1)
    {
      cout << "Sum of  Comparisons in Test Instances: " << diff;
      cout << "	over " << names.size() << " Instances" << endl;
      diff /= (double) names.size();
      cout << "Average Accuracy (in percent) : " << diff*100.0 << endl;
    }
  */
  delete levelset;

  return result;
}
/*F diff = ResultPrintout(sons, bestname)
**
**  DESCRIPTION
**    sons:  The list of sons on the node
**    bestname: The 'best' node name
**    diff:     The difference
**
**  REMARKS
**
*/
void BaseDataCobwebClusterTree::ResultPrintout(String& name, ObjectList<String> *sons, String& bestname, String& pre)
{
  cout << "============================================================" << endl;
  cout << "Best of Sons for " << name << ": " << bestname << endl;

  cout << pre;
  cout << setw(20) << "Alone" << ":  " << ExtraGroupMeasure->GetValue() << endl;
  unsigned int count = 0;
  VectorNumeric vec = InGroupMeasure->CurrentVector();
  
  ObjectList<String>::iterator son;
  for(son = sons->begin(); son != sons->end(); son++) {
    cout << pre;
    cout << setw(20) << son->c_str() << ":  ";
    cout << setprecision(10) << setw(15) << vec[count] << endl;
    count++;
  }
}
/*F SetUpPartitions(levelsets)
**
**  DESCRIPTION
**    levelsets:     The set of level sets
**    instances:     The set of instances and attributes
**    classes:       The set of classes
**    levelsets:     The set of level sets
**    
**   This routine cycles through the set of level sets and 
**   by calling SetUpSinglePartitions, the partition for 
**   each level is set up.
**
**  REMARKS
**
*/
void BaseDataCobwebClusterTree::SetUpPartitions(DataCobwebClusterTreeClass *treeclass,
						BaseDataSetOfObjects *instances,
						BaseDataSetOfObjects *levelsets,
						DataSetOfObjectsClass *classes) {
  DataNValuedClass *reference = treeclass->ClusterNodeAssignmentClass;
  DataExactlyEqualPredicateClass *compare = treeclass->CreateComparePredicateClass(reference,classes);

  ObjectList<String> names = levelsets->ListOfObjectNames();
  for(ObjectList<String>::iterator name=names.begin(); 
      name != names.end();
      name++) {
    cout << "Set " << *name << endl;
    BaseDataKeyWords *keys = (BaseDataKeyWords *) levelsets->GetObject(*name);
    SetUpSinglePartitions(treeclass,keys,reference,compare,instances,classes);
  }
}
/*F SetUpSinglePartitions(names, reference, instances, classes)
**
**  DESCRIPTION
**    names:         The set of names for that level
**    reference:     The NValued reference
**    instances:     The set of instances and attributes
**    classes:       The set of classes
**
**    This routine creates:
**       1.   The nvalued object with the cluster node name, one for each in the partition (valueNodename)
**       2.   The list of partitions:  ComparePartitionLevelx
**       3.   ExactlyEqualPredicate, comparing the nvalued with (compareNodeName
**       
**  REMARKS
**
*/
void BaseDataCobwebClusterTree::SetUpSinglePartitions(DataCobwebClusterTreeClass *treeclass,
						      BaseDataKeyWords *keynames,
						      DataNValuedClass *reference,
						      DataExactlyEqualPredicateClass *compareclass,
						      BaseDataSetOfObjects *instances,
						      DataSetOfObjectsClass *classes) {

  DataKeyWordsClass *keywordsclass = (DataKeyWordsClass *) classes->GetObjectClass("KeyWords");

  ObjectList<String> names = keynames->GetKeyWords();

  BaseDataKeyWords *partition = (BaseDataKeyWords *) keywordsclass->BaseDataObjectExample();
  partition->NameTag = "ComparePartition";
  partition->NameTag.AppendToEnd(keynames->NameTag);

  cout << "Set up partitions for Level set: '" << keynames->NameTag << "'" << endl;

  for(ObjectList<String>::iterator name=names.begin(); name != names.end(); name++) {
    // The NValued value to compare with
    BaseDataNValued *v = (BaseDataNValued *) reference->BaseDataObjectExample();
    String vname("value");
    vname.AppendToEnd(*name);
    v->NameTag = vname;
    v->SetValue(reference->NameValueCorrs[*name]);

    // The Predicate to compare with
    String cname("compare");
    cname.AppendToEnd(keynames->NameTag);
    cname.AppendToEnd(*name);
    String nm(cname);
    BaseDataExactlyEqualPredicate *c = (BaseDataExactlyEqualPredicate *) compareclass->BaseDataObjectExample();
    c->NameTag = cname;
    String keyname(treeclass->ClusterAssignmentName);
    keyname.AppendToEnd(keynames->NameTag);
    c->setParameterName(keyname);
    c->setCompareObject(v);
    c->setLogicClass(compareclass->logicClass);
    instances->AddObject(c);
    partition->AddKeyWord(nm);
    delete c;
    delete v;
  }
  instances->AddObject(partition);
  delete partition;
}

/*F levelsets = LevelKeySets(maxlevel,classes)
**
**  DESCRIPTION
**    maxlevel:     The maximum level to go down to
**    classes:      Set of object classes
**    levelset:     The set of level sets (empty)
**
**  REMARKS
**
*/
BaseDataSetOfObjects *BaseDataCobwebClusterTree::LevelKeySets(int maxlevel,
							      DataSetOfObjectsClass *classes) {
  BaseDataSetOfObjects *levelset = new BaseDataSetOfObjects();
  
  DataKeyWordsClass *keyclass = (DataKeyWordsClass *) classes->GetObjectClass(DATAOBJ_KEYWORDS_NAME);
  
  for(int i=0;i<maxlevel;i++) {
    String name = "Level";
    String levelS = Int2String(i);
    name.AppendToEnd(levelS);
    
    BaseDataKeyWords *levelkey = (BaseDataKeyWords *) keyclass->BaseDataObjectExample();
    levelkey->NameTag = name;

    levelset->AddObject(levelkey);

    delete levelkey;
  }
  return levelset;
}
/*F ans = LevelValuesForInstance(instancename, parent, level)
**
**  DESCRIPTION
**    instancename: The name of the instance
**    parent:       The parent node
**    level:        The current level of the tree
**    maxlevel:     The maximum level to go down to
**    
**    Recursive routine to assign the level node to an instance
**
**  REMARKS
**
*/
void BaseDataCobwebClusterTree::LevelValuesForInstance(BaseDataInstance *instance, 
						       BaseDataCobwebClusterNodeStats *parent, 
						       int level, int maxlevel,
						       BaseDataSetOfObjects *levelkeys,
						       DataCobwebClusterTreeClass *treeclass) {
  String levelname;
  BaseDataCobwebClusterNodeStats *bestnode;
  if(level < maxlevel) {
    ObjectList<String> *sons = Tree.GetSons(parent->NameTag);
    if(sons->size() > 0) {
      ComputeInstanceDescriptionMatrixFromParent(parent,treeclass);
      levelname = DetermineBestFromNode(parent,instance->NameTag,false,true,TreeClass);
    } else {
      levelname = parent->NameTag;
    }
    bestnode = (BaseDataCobwebClusterNodeStats *) Tree.GetNode(levelname);
    int next = level + 1;
    LevelValuesForInstance(instance,bestnode,next,maxlevel,levelkeys,treeclass);

    String name = "Level";
    String levelS = Int2String(level);
    name.AppendToEnd(levelS);
    
    BaseDataKeyWords *keys = (BaseDataKeyWords *) levelkeys->GetObject(name);
    if(!keys->KeyWordInList(bestnode->NameTag)) {
      keys->AddKeyWord(bestnode->NameTag);
    }

    AssignNValuedClassForNode(instance,bestnode->NameTag,name,treeclass);
  }
}
/*F ans = IsValidNode(node)
**
**  DESCRIPTION
**    node:  The node to evaluate
**    ans: True if a 'valid' node
**
**    This evaluates the node according to the the criteria
**     given in the cluster to see whether it should be
**     be considered or ignored.
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterTree::IsValidNode(BaseDataCobwebClusterNodeStats *nodestat) {
  bool result = nodestat->NumberOfElementsInCluster() >= SmallestNodeSize;
  return result;
}
/*F list = ValidNodesToNValued(instances,treeclass,classes)
**
**  DESCRIPTION
**    instances:  The set of instances and attributes
**    treeclass:  The class of the tree
**    classes:    The total set of current classes
**    
**    This finds the valid nodes and converts the list to a 
**    single NValued logic class
**    
**
**  REMARKS
**
*/
ObjectList<String> BaseDataCobwebClusterTree::ValidNodesToNValued(BaseDataSetOfInstances *instances,
								  DataCobwebClusterTreeClass *treeclass,
								  DataSetOfObjectsClass *classes) {

  ObjectList<String> validnodes;
  ObjectList<String> nodelist = Tree.ListOfObjectNames();
  ObjectList<String>::iterator node;

  for(node = nodelist.begin(); node != nodelist.end(); node++) {
    BaseDataCobwebClusterNodeStats *nodestat = (BaseDataCobwebClusterNodeStats *) Tree.GetNode(*node);
    if(IsValidNode(nodestat)) {
      validnodes.AddObject(*node);
    }
  }

  treeclass->ClusterNodeAssignmentClass = 
    treeclass->SetUpNValuedClass(validnodes,
				 treeclass->ClusterAssignmentBaseClassS,
				 treeclass->ClusterNodeAssignmentClassS,
				 treeclass->ClusterAssignmentName,
				 instances,
				 classes);

  return validnodes;
}
/*F ans = AssignNValuedClassForNode(instance,bestnode,treeclass)
**
**  DESCRIPTION
**    instance: The instance to store the value
**    bestnode: The name of the best node (the assignment)
**    treeclass: The tree class of the cluster
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterTree::AssignNValuedClassForNode(BaseDataInstance *instance,
							  String &bestnode, String& postfix,
							  DataCobwebClusterTreeClass *treeclass )
{
  DataNValuedClass *logicclass = treeclass->ClusterNodeAssignmentClass;

  BaseDataNValued *logicvalue = (BaseDataNValued *) logicclass->BaseDataObjectExample();
  logicvalue->NameTag = treeclass->ClusterAssignmentName;
  logicvalue->NameTag.AppendToEnd(postfix);
  logicvalue->SetValue(logicclass->NameValueCorrs[bestnode]);

  bool result = instance->AddAttribute(logicvalue);
  delete logicvalue;
  cout << "Instance: " << instance->NameTag << " Value: " << logicvalue->NameTag << " = " << bestnode << endl;
  return result;
}
/*F name = getCobwebTreeName()
**
**  DESCRIPTION
**    name: The name of the cobweb tree
**
**  REMARKS
**
*/
String BaseDataCobwebClusterTree::getCobwebTreeName()
{
  return cobwebTreeS;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . BaseDataCobwebClusterTree
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
bool BaseDataCobwebClusterTree::WriteAsLine(ostream& out, DataObjectClass *objc)
{
    return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . BaseDataCobwebClusterTree
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
bool BaseDataCobwebClusterTree::WriteAsASCII(ostream& out, DataObjectClass *objc)
{
  out << "%%%%%%%%%%%%%%%%%%%%% CobwebClusterTree " << NameTag << endl;
  DataCobwebClusterTreeClass *treecls = (DataCobwebClusterTreeClass *) objc;
  DataSetOfObjectsClass *classes = treecls->PointerToAllowedClasses();
  SetUpClassNamePairs(&Description,classes);
  out << "%%   CobwebClusterTree Desscription" << endl;
  classes->getNameClassPairs().WriteAsASCII(out);
  Description.WriteAsASCII(out,classes);
  /*
  out << "%%   CobwebClusterTree Goals" << endl;
  SetUpClassNamePairs(&Goals,classes);
  classes->getNameClassPairs().WriteAsASCII(out);
  Goals.WriteAsASCII(out,classes);
  out << "%%   CobwebClusterTree Tree and Nodes" << endl;
  */
  return BaseDataClusterTree::WriteAsASCII(out,objc);
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . BaseDataCobwebClusterTree
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
bool BaseDataCobwebClusterTree::WriteAsLatex(ostream& out, DataObjectClass*obj)
{
  bool result = BaseDataClusterTree::WriteAsLatex(out,obj);
  return result;
}

/*S DataCobwebClusterTreeClass
 */
/*F DataCobwebClusterTreeClass()  . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataCobwebClusterTreeClass::DataCobwebClusterTreeClass()
{
  Identification = COBWEBCLUSTER_BASETREE_ID;
  NameTag = COBWEBCLUSTER_BASETREE_NAME;
  SubClass = CLUSTER_TREE_NAME;
  EncodeDecodeClass = NameTag;

  String name(COBWEBCLUSTER_NODESTATS_NAME);
    DataClusterTreeClass::setNodeClassName(name);
} 
/*F DataCobwebClusterTreeClass(data)  . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataCobwebClusterTreeClass::DataCobwebClusterTreeClass(const DataCobwebClusterTreeClass& data)
  : DataClusterTreeClass(data),
    PredicateClassInfo(data.PredicateClassInfo),
    KeyWordClass(data.KeyWordClass)
{
} 
 
/*F DataCobwebClusterTreeClass(id,name,descr) . . . . . . . . . . constructor
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
DataCobwebClusterTreeClass::DataCobwebClusterTreeClass(const int id, 
						       const String& name,
						       const String& descr)
  : DataClusterTreeClass(id,name,descr)
{
  SubClass = CLUSTER_TREE_NAME;
  EncodeDecodeClass = COBWEBCLUSTER_BASETREE_NAME;

  String name1(COBWEBCLUSTER_NODESTATS_NAME);
  DataClusterTreeClass::setNodeClassName(name1);
} 
/*F out1 = print(out) . . . . . . . . . . . . . .  DataCobwebClusterTreeClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataCobwebClusterTreeClass::print(ostream& out) const
{
  DataClusterTreeClass::print(out);
       
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . .  DataCobwebClusterTreeClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.	For the
**    base DataCobwebClusterTreeClass, there is no further information.
**
**  REMARKS
**
*/
bool DataCobwebClusterTreeClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataClusterTreeClass::Read(in,set);
  //result = result && PredicateClassInfo.Read(in,set);
  //result = result && KeyWordClass.Read(in,set);
  
  return result;
}
/*F CreateComparePredicate( classes)
**
**  DESCRIPTION
**    classes:      Set of object classes
**
**  REMARKS
**
*/
DataExactlyEqualPredicateClass *DataCobwebClusterTreeClass::CreateComparePredicateClass(DataNValuedClass *objectclass,
											DataSetOfObjectsClass *classes){
  int ID = classes->getIDCount();
  // The 'true/false' class used for recognition
  String t("True");
  String f("False");
  String tfanswerS("CompareAnswerValue");
  DataNValuedClass *tfanswerbase = (DataNValuedClass *) classes->GetObjectClass("NValued");
  DataNValuedClass *tfanswer     = (DataNValuedClass *) tfanswerbase->Clone();
  tfanswer->NameTag = tfanswerS;
  tfanswer->Identification      = ID;
  ID++;
  tfanswer->NameValueCorrs[t] = 0.0;
  tfanswer->NameValueCorrs[f] = 1.0;
  classes->AddObjectClass(*tfanswer);
  delete tfanswer;
  tfanswer = (DataNValuedClass *) classes->GetObjectClass(tfanswerS);

  // The compare predicate class
  String valuecompareS("ValueCompare");
  DataExactlyEqualPredicateClass *compare = (DataExactlyEqualPredicateClass *) classes->GetObjectClass("ExactlyEqualPredicate");
  compare->NameTag = valuecompareS;
  compare->Identification = ID;
  ID++;
  compare->objectClass = objectclass;
  compare->logicClass = tfanswer;

  classes->AddObjectClass(*compare);
  classes->setIDCount(ID);
  return compare;

} 
/*F CopyClone(objc) . . . . . . . . . . . . . . .  DataCobwebClusterTreeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataCobwebClusterTreeClass::CopyClone(Identify *  objc)
{
  DataCobwebClusterTreeClass *objcfull = (DataCobwebClusterTreeClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . .  DataCobwebClusterTreeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataCobwebClusterTreeClass::Clone()
{
  DataCobwebClusterTreeClass* id = new DataCobwebClusterTreeClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . .  DataCobwebClusterTreeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataCobwebClusterTreeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = true;
  result = result && DataClusterTreeClass::EncodeThis(buffer);
  result = result && PredicateClassInfo.EncodeThis(buffer);
  result = result && KeyWordClass.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . .  DataCobwebClusterTreeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataCobwebClusterTreeClass::DecodeThis(CommBuffer& buffer)
{
  bool result = true;
  result = result && DataClusterTreeClass::DecodeThis(buffer);
  result = result && PredicateClassInfo.DecodeThis(buffer);
  result = result && KeyWordClass.DecodeThis(buffer);

  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.	This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataCobwebClusterTreeClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataCobwebClusterTree();
  obj->SetType(Identification);
  return obj;
}
/*F classinfo = getPredicateClass() . . . . . . . . . . pointer to class info
**
**  DESCRIPTION
**    classinfo: pointer to predicate classes
**
**  REMARKS
**
*/
DataSetOfObjectsClass * DataCobwebClusterTreeClass::getPredicateClassInfo()
{
  return &PredicateClassInfo;
}
 
/*F keywordclass = getKeyWordClass() 
**
**  DESCRIPTION
**    keywordclass: 
**
**  REMARKS
**
*/
DataKeyWordsClass * DataCobwebClusterTreeClass::getKeyWordClass()
{
  return &KeyWordClass;
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . .  DataCobwebClusterTreeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataCobwebClusterTreeClass*& obj)
{
  obj = new DataCobwebClusterTreeClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . BaseDataCobwebClusterTree
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataCobwebClusterTree*& obj)
{
  obj = new BaseDataCobwebClusterTree;
  return obj->DecodeThis(buffer);
}
/*F classes = PointerToAllowedClasses()
**
**  DESCRIPTION
**    classes: The standard set of object classes
**
**  REMARKS
**
*/
DataSetOfObjectsClass *DataCobwebClusterTreeClass::PointerToAllowedClasses()
{
  return StandardAllowedClasses;
}
/*F nvalued = SetUpNValuedClass(names,baseclassS,classnameS,parametername,classes)
**
**  DESCRIPTION
**    This generates an NValued class based on the 'names'
**    given and then generates the recognition predicates
**    associated with it.
**
**    The classes generated are:
**       The class from the names (nvalued)
**           Base              :  NValued
**           Derived Base Class:  baseclassS
**           Class Name        :  classnameS
**       The 'true/false' class used for recognition (tfanswer)
**           Base  Class       :  NValued
**           Class Name        :  CompareAnswerValue
**       The class of the comparison predicated with the NValued (compare)
**         name class used as the object class to compare (nvalued) and 
**         the 'true/false' (tfanswer) class as the logic of the answer.
**           Base Class        :  ExactlyEqualPredicate
**           Class Name        :  ValueCompare
**
**     The object classes generated are:
**       For each name a 'ValueCompare' (derived from
**         'ExactlyEqualPredicate') object is created  (c):
**             Base            : ExactlyEqualPredicate
**             BaseClass       : ValueCompare
**             Object Name     : compare+name
**             Compare Parameter: parametername
**       Inside this class is the 'NValued' class of the names:
**             Base            : NValued
**             BaseClass       : classnameS
**             Object Name     : value+name
**           
**
**  REMARKS
**
*/
DataNValuedClass *DataCobwebClusterTreeClass::SetUpNValuedClass(ObjectList<String> &names,
								String& baseclassS,
								String& classnameS,
								String& parametername,
								BaseDataSetOfInstances *instances,
								DataSetOfObjectsClass *classes)
{
  ObjectList<String>::iterator name;

  unsigned int ID = classes->getIDCount();

  // The NValued class associated with the names
  DataNValuedClass *nvaluedbase = (DataNValuedClass *)   classes->GetObjectClass(baseclassS);
  DataNValuedClass *nvalued = (DataNValuedClass *) nvaluedbase->Clone();
  nvalued->NameTag = classnameS;
  nvalued->Identification = ID;
  ID++;

  int num = names.size();
  double numd = num;
  double inc = 1.0 / numd;
  double count = 0.0;
  for(name=names.begin(); name != names.end(); name++) {
    nvalued->NameValueCorrs[*name] = count;
    count += inc;
  }
  DataObjectClass *objcls = nvalued;
  classes->AddObjectClass(*objcls);

  DataExactlyEqualPredicateClass *compare = CreateComparePredicateClass(nvalued,classes);
  
  BaseDataKeyWords *partition = new BaseDataKeyWords();
  partition->NameTag = "ComparePartition";

  count = 0.0;
  for(name=names.begin(); name != names.end(); name++) {
    String vname("value");
    vname.AppendToEnd(*name);
    BaseDataNValued *v = (BaseDataNValued *) nvalued->BaseDataObjectExample();
    v->NameTag = vname;
    v->SetValue(count);

    String cname("compare");
    cname.AppendToEnd(*name);
    String nm(cname);
    BaseDataExactlyEqualPredicate *c = (BaseDataExactlyEqualPredicate *) compare->BaseDataObjectExample();
    c->NameTag = cname;
    c->setParameterName(parametername);
    c->setCompareObject(v);
    instances->AddObject(c);
    partition->AddKeyWord(nm);
    delete c;
    delete v;

    count += inc;
  }
  instances->AddObject(partition);
  delete partition;
  classes->setIDCount(ID);

  return nvalued;
}

/*S BaseDataCobwebClusterTreeCreate
 */ 
/*F BaseDataCobwebClusterTreeCreate() . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataCobwebClusterTreeCreate::BaseDataCobwebClusterTreeCreate()
  : logicTypeS(COBWEB_LOGIC_TYPE),
    trainInstanceNamesS(COBWEB_TRAININGSET),
    descriptionNamesS(COBWEB_DESCRIPTION),
    goalNamesS(COBWEB_GOALS)
{
  Identification = COBWEBCLUSTER_TREECREATE_ID;
  NameTag = COBWEBCLUSTER_TREECREATE_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataCobwebClusterTreeCreate(data) . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataCobwebClusterTreeCreate::BaseDataCobwebClusterTreeCreate(const BaseDataCobwebClusterTreeCreate& data)
  : BaseDataCobwebClusterTree(data),
    logicTypeS(data.logicTypeS),
    trainInstanceNamesS(data.trainInstanceNamesS),
    descriptionNamesS(data.descriptionNamesS),
    goalNamesS(data.goalNamesS)
{
}
/*F Read(in,objc) . . . . . . . . . . Read in BaseDataCobwebClusterTreeCreate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterTreeCreate::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)	. . . . . . . Read in BaseDataCobwebClusterTreeCreate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterTreeCreate::Read(istream& , DataObjectClass* , const String&)
{
  return true;
}
 
/*F out1 = print(out) . . . . . . . . . . . . BaseDataCobwebClusterTreeCreate
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataCobwebClusterTreeCreate::print(ostream& out) const
{
  BaseDataCobwebClusterTree::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . BaseDataCobwebClusterTreeCreate
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataCobwebClusterTreeCreate::Clone()
{
  BaseDataCobwebClusterTreeCreate *obj = new BaseDataCobwebClusterTreeCreate;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . BaseDataCobwebClusterTreeCreate
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataCobwebClusterTreeCreate::CopyClone(Identify * obj)
{
  BaseDataCobwebClusterTreeCreate *objfull = (BaseDataCobwebClusterTreeCreate *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . BaseDataCobwebClusterTreeCreate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterTreeCreate::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataCobwebClusterTree::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . BaseDataCobwebClusterTreeCreate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterTreeCreate::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataCobwebClusterTree::DecodeThis(buffer);
  return result;
}
 
 
 
 
/*F StartToAddInstanceToClusterTree(instance,treeclass)
**
**  DESCRIPTION
**    instance: The name of the instance
**    logic: The logic of the description
**
**    This is the top routine of adding an instance to the cobweb cluster tree.
**    - rootnode: The rootnode
**    - Set the initial logic and that the instance membership such that the 
**	instance is 100% in the root node
**    - iclass,instance: The instance and the instance class
**    - names: The names of the instances already of the cobweb tree
**    - tdescr: matrix of descriptions(rows) by instances(columns)
**    - Add  to the next level
**    - add the instance to the current node
**    
**  REMARKS
**
*/
void BaseDataCobwebClusterTreeCreate::StartToAddInstanceToClusterTree(String& instname,
								      DataClusterTreeClass *treeclass)
{
  DataCobwebClusterTreeCreateClass *ctreeclass = (DataCobwebClusterTreeCreateClass *) treeclass;
  if(ctreeclass->RunClass->getDebugLevel() > 2)
    {
      cout << "StartToAddInstanceToClusterTree: " << instname << endl;
    }
  BaseDataClusterNode *rootnode = 
    (BaseDataClusterNode *) Tree.GetNode(Tree.getRootNodeName());

  BaseDataLogical *logic = InitializeMembership();

  rootnode->AssignElementToCluster(instname,logic);
  BaseDataInstance *instance = (BaseDataInstance *) Instances->GetInstance(instname);


  AddToNextLevel(rootnode,instance,logic,treeclass);
  AddInstanceToClusterNode(rootnode,instance,logic,ctreeclass);

  if(ctreeclass->getDebugLevel() > 2)
    {
      cout << "Begin: ---------------- AddInstanceToClusterNode ---------------- \n";
      Tree.print(cout);
      cout << "End:   ---------------- AddInstanceToClusterNode ---------------- \n";
    }
  delete logic;
}
 
/*F AddToNextLevel(parent,tobeadd,membership,treeclass)
**
**  DESCRIPTION
**    parent: the parent node 
**    tobeadded: The instance to be added to the sons
**    membership: The current membership value of the instance to be added
**    treeclass: The tree class
**
**    If the level has not been exceeded, then the instances are added to the sons
**    - If there are no sons, then an empty node with just the instance is added
**	(representing the new cluster) and a subnode with just the instance (for the
**	instance node itself).
**    - If there are, the membership values are determined, and then used to add
**	to sons
**    - Add instance to parent node
**
**    dist: The membership values of the instance to the sons, plus the membership
**	    value if the son is in a new cluster
**
**  REMARKS
**
*/
void 
BaseDataCobwebClusterTreeCreate::AddToNextLevel(BaseDataClusterNode *parent,
						BaseDataInstance *tobeadded,
						BaseDataLogical *membership,
						DataClusterTreeClass *tclass)
{
  DataCobwebClusterTreeCreateClass *treeclass = (DataCobwebClusterTreeCreateClass *) tclass;
  if(parent->getLevel() < getMaxLevel())
    {
      ObjectList<String> *sons = Tree.GetSons(parent->NameTag);
      if(sons->size() == 0)
	{
	  if(treeclass->RunClass->getDebugLevel() > 2)
	    {
	      cout << "Add Terminal Node: " << parent->NameTag << endl;
	    }
	  BaseDataClusterNode *node = AddEmptyNode(parent,treeclass->getNodeClass(),tobeadded,membership);
	  AddInstanceToClusterNode(node,tobeadded,membership,treeclass);
	}
      else
	{
	  if(treeclass->RunClass->getDebugLevel() > 2)
	    {
	      cout << "Determine Best of Sons: ";
	      sons->print(cout);
	      cout << endl;
	    }

	  ComputeInstanceDescriptionMatrixFromParent(parent,treeclass);
	  
	  ComputeClusteringMeasure(parent->NameTag,tobeadded,*sons,treeclass);

	  String bestname = BaseDataCobwebClusterTree::DetermineBestNode(*sons,true,false,treeclass);
	  if(treeclass->RunClass->getDebugLevel() > 2)
	    {
	      cout << "Best of Sons:" << bestname << endl;
	    }
	  Run->RemoveParameter(InGroupMeasureS);
	  Run->RemoveParameter(ExtraGroupMeasureS);
	  String descmatrixS("DescriptionMatrix");
	  Run->RemoveParameter(descmatrixS);


	  BaseDataClusterNode *bestnode = (BaseDataClusterNode *)
	    AddInstanceToSons(bestname,parent,tobeadded,membership,treeclass);
	  if(bestnode != NULL)
	    AddToNextLevel(bestnode,tobeadded,membership,treeclass);
	}
      delete sons;
    }
  else
    {
      if(treeclass->RunClass->getDebugLevel() > 2)
	{
	  cout << "\n------------ Maximum Level (" << getMaxLevel();
	  cout << ") Reached by ";
	  cout << parent->NameTag << " ----------------\n";
	}
    }
  if(treeclass->RunClass->getDebugLevel() > 2)
    {
      cout << "\n------------ After AddToNextLevel Tree ----------------\n";
      Tree.print(cout);
    }
}
 
/*F AddInstanceToClusterNode(node,instance,membership,treeclass) 
**
**  DESCRIPTION
**    instance: The instance to add to the 
**  REMARKS
**
*/
void BaseDataCobwebClusterTreeCreate::AddInstanceToClusterNode(BaseDataClusterNode *node,
							       BaseDataInstance* instance,
							       BaseDataLogical *membership,
							       DataClusterTreeClass *treeclass)
{
  BaseDataClusterTree::AddInstanceToClusterNode(node,instance,membership);
  BaseDataCobwebClusterNodeStats *snode = (BaseDataCobwebClusterNodeStats *) node;
  ObjectList<String> inames = getTrainInstanceNames().GetKeyWords();
  
  MatrixNumeric *iprobs = snode->ExtentInClusterAsMatrix(inames);

  MatrixNumeric dprobs = (*iprobs) * (*descrMatrix);
  MatrixNumeric gprobs = (*iprobs) * (*goalMatrix);

  if(snode->DescriptionProbs != NULL)
    {
      delete snode->DescriptionProbs;
      snode->DescriptionProbs = NULL;
    }
  if(snode->GoalProbs != NULL)
    {
      delete snode->GoalProbs;
      snode->GoalProbs = NULL;
    }
  snode->DescriptionProbs = new VectorNumeric(dprobs[0]);
  snode->GoalProbs = new VectorNumeric(gprobs[0]);

  if(!(snode->NameTag == Tree.getRootNode()->NameTag))
    {
      String name = Tree.GetParent(node->NameTag);
      BaseDataCobwebClusterNodeStats *parentnode = (BaseDataCobwebClusterNodeStats *) Tree.GetNode(name);
      parentnode->setInstanceCount(parentnode->NumberOfElementsInCluster());
      VectorNumeric pprobs(*(parentnode->DescriptionProbs));
      if(parentnode->getInstanceCount() > 0)
	{
	  transform(pprobs.begin(),pprobs.end(),pprobs.begin(),
		    bind2nd(divides<double>(),parentnode->getInstanceCount()));
	}
      transform(dprobs[0].begin(),dprobs[0].end(),dprobs[0].begin(),
		bind2nd(divides<double>(),snode->getInstanceCount()));
      transform(dprobs[0].begin(),dprobs[0].end(),
		pprobs.begin(),pprobs.begin(),minus<double>());
      snode->ProbChanges = new VectorNumeric(pprobs);
    }
}
/*F AddInstanceToSons(name,parent,instance,membership,treeclass)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataCobwebClusterNodeStats *
BaseDataCobwebClusterTreeCreate::AddInstanceToSons(String& bestname,
						   BaseDataClusterNode *parent,
						   BaseDataInstance *instance,
						   BaseDataLogical *membership,
						   DataClusterTreeClass *treeclass)
{
  BaseDataCobwebClusterNodeStats *bestnode;
  
  if(!(bestname == COBWEB_ADD_INSTANCE_ALONE))
    {
      bestnode = (BaseDataCobwebClusterNodeStats *) Tree.GetNode(bestname);
      AddInstanceToClusterNode(bestnode,instance,membership,treeclass);
      bestnode->setInstanceCount(bestnode->NumberOfElementsInCluster());
    }
  else
    {
      BaseDataClusterNode *node = AddEmptyNode(parent,treeclass->getNodeClass(),instance,membership);
      AddInstanceToClusterNode(node,instance,membership,treeclass);
      node->setInstanceCount(membership->GetValue());
      bestnode = NULL;
    }
  return bestnode;
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
bool BaseDataCobwebClusterTreeCreate::SetUpAlgorithms(BaseDataSetOfInstances *instances,
						      DataSetOfInstancesClass *instsclass,
						      BaseDataAlgorithmRun *run,
						      DataAlgorithmRunClass *rclass)
{
  return BaseDataCobwebClusterTree::SetUpAlgorithms(instances,instsclass,run,rclass);
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
bool BaseDataCobwebClusterTreeCreate::CheckInput(BaseDataSetOfInstances* instances,
						 DataSetOfInstancesClass* instancesclass,
						 BaseDataAlgorithmRun* run,
						 DataAlgorithmRunClass* runclass)
{
  bool result = BaseDataCobwebClusterTree::CheckInput(instances,instancesclass,
							    run,runclass);

  if(run->ParameterInList(getTrainListName()))
    {
      if(run->ParameterInList(descriptionNamesS))
	{
	  if(run->ParameterInList(goalNamesS))
	    {
	      if(!run->ParameterInList(logicTypeS))
		{
		  cerr << "5 The parameter '"<< logicTypeS << "' was not in the list of parameters\n";
		  result = false;
		}	   
	    }
	  else
	    {
	      cerr << "3 The parameter '" << goalNamesS << "' was not in the list of parameters\n";
	      result = false;
	    }
	}
      else
	{
	  cerr << "2 The parameter '" << descriptionNamesS << "' was not in the list of parameters\n";
	  result = false;
	}
    }
  else
    {
      cerr << "1 The parameter '" << getTrainListName() << "' was not in the list of parameters\n";
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
**    1. logicType: The first keyword in the logic type is the logic type used
**    2. maxLevel: A numeric value (the maximum tree level)
**    3. trainInstanceNames: from keywords
**    4. dlist: The list of descriptors
**    5. glist: The list of goals
**    6. descrMatrix: Matrix of descriptions versus instances
**    7. goalMatrix: Matrix of goals versus instances
**
**  REMARKS
**
*/
bool BaseDataCobwebClusterTreeCreate::SetUpInput(BaseDataSetOfInstances* instances,
						 DataSetOfInstancesClass* instancesclass,
						 BaseDataAlgorithmRun* run,
						 DataAlgorithmRunClass* rclass)
{
  bool result = BaseDataCobwebClusterTree::SetUpInput(instances,instancesclass,
							    run,rclass);

  BaseDataKeyWords *keylogic = (BaseDataKeyWords *) run->ParameterValue(logicTypeS);
  ObjectList<String> logicstrings = keylogic->GetKeyWords();
  if(logicstrings.size() < 1)
    {
      cerr << "No logic type specified in '" << logicTypeS << "'\n";
      result = false;
    }
  else
    {
      logicType = logicstrings.front();

      BaseDataKeyWords *tlist = (BaseDataKeyWords *) run->ParameterValue(getTrainListName());
      if( rclass->getDebugLevel() > 1)
	{
	  cout << "Training Set List" << endl;
	  tlist->print(cout);
	  cout << endl;
	}
      setTrainInstanceNames(*tlist);
      
      BaseDataKeyWords *dlist = (BaseDataKeyWords *) run->ParameterValue(descriptionNamesS);
      if( rclass->getDebugLevel() > 1)
	{
	  cout << "Description List" << endl;
	  dlist->print(cout);
	  cout << endl;
	}
      result = result && setDescription(*dlist,instances);
      
      BaseDataKeyWords *glist = (BaseDataKeyWords *) run->ParameterValue(goalNamesS);
      if( rclass->getDebugLevel() > 1)
	{
	  cout << "Goal List" << endl;
	  dlist->print(cout);
	  cout << endl;
	}
      result = result && setGoals(*glist,instances);
      
      if( rclass->getDebugLevel() > 1)
	{
	  cout << "Description used for Cobweb Tree" << endl;
	  if(!(getDescription() == NULL))
	    {
	      getDescription()->print(cout);
	    }
	  else
	    {
	      cout << "No Description" << endl;
	    }
	}
      if(result)
	{
	  ObjectList<String> inames = getTrainInstanceNames().GetKeyWords();
	  /*
	  descrMatrix = new
	    MatrixNumeric(MatrixOfProbabilitiesCalc(inames,*(getDescription()),
						  *instances,*instancesclass));
	  goalMatrix = new
	    MatrixNumeric(MatrixOfProbabilitiesCalc(inames,*(getGoals()),
						  *instances,*instancesclass)); 
	  */
	  descrMatrix = MatrixOfProbabilitiesCalc(inames,*(getDescription()),
						  *instances,*instancesclass);
	  goalMatrix =  MatrixOfProbabilitiesCalc(inames,*(getGoals()),
						  *instances,*instancesclass); 
	}      
      else
	{
	  cerr << "SetUp failed: Faulty Description" << endl;
	}
      
    }
  return result;
}
 
/*F InitializeIncrementClusterTree
**
**  DESCRIPTION
**    Sets up:  
**        TreeClass (SetUpGlobalInformation)
**        NodeClass (InitializeNodeClass)
**             (set within TreeClass)
**        Tree.setRootNodeName:  hard coded to "Cobweb"
              (InitializeRootNode)
**        
**  REMARKS
**
*/
bool BaseDataCobwebClusterTreeCreate::InitializeIncrementClusterTree(BaseDataSetOfInstances* instances,
								     DataSetOfInstancesClass* instancesclass,
								     BaseDataAlgorithmRun *run,
								     DataAlgorithmRunClass* rclass)
{
  bool result = true;
  if(rclass->getDebugLevel() > 1)
    {
      cout << "BaseDataCobwebClusterTreeCreate" << endl;
    }

  
  TreeClass = (DataClusterTreeClass *) SetUpGlobalInformation(instances,instancesclass,run,rclass);
  DataCobwebClusterTreeClass *tclass = (DataCobwebClusterTreeClass *) TreeClass;
  NodeClass = (DataCobwebClusterNodeStatsClass *) 
    InitializeNodeClass(tclass->Classes);
  TreeClass->setNodeClass(NodeClass);

  instancesclass->PointerToAllowedClasses()->AddObjectClass(*NodeClass);

  if(true)
    {
      String rootname("Cobweb");
      Tree.setRootNodeName(rootname);
      InitializeRootNode(TreeClass);
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
bool BaseDataCobwebClusterTreeCreate::BuildIncrementClusterTree(BaseDataSetOfInstances* instances,
								DataSetOfInstancesClass* instancesclasses,
								BaseDataAlgorithmRun *run,
								DataAlgorithmRunClass* rclass)
{
  bool result = true;
  if(rclass->getDebugLevel() > 1)
    {
      cout << "BuildIncrementClusterTree" << endl;
    }
  InitializeIncrementClusterTree(instances,instancesclasses,
				 run,rclass);
  DataCobwebClusterTreeClass *tclass = (DataCobwebClusterTreeClass *) TreeClass;

  // Set up description list
  ObjectList<String> dlist = getDescription()->ListOfObjectNames();
  BaseDataKeyWords dlistkeys(dlist);
  dlistkeys.NameTag = AttributeListS;
  Run->AddParameter(&dlistkeys);

  if(rclass->getDebugLevel() > 1)
    {
      cout << "BuildIncrementClusterTree: Loop" << endl;
    }
  ObjectList<String> names = getTrainInstanceNames().GetKeyWords();
  BaseDataKeyWords *ilistkeys = new BaseDataKeyWords(names);
  ilistkeys->NameTag = matrixInstanceNamesS;

  DataCobwebClusterTreeCreateClass *treeclass = (DataCobwebClusterTreeCreateClass *) TreeClass;

  ComputeInstanceDescriptionMatrix(ilistkeys,treeclass);
  
  String descrMatS(DESCRIPTION_MATRIX_NAME);
  BaseDataDescriptionMatrix *descmat = (BaseDataDescriptionMatrix *) instances->GetObject(descrMatS);

  DescriptionMatrix = new BaseDataDescriptionMatrix(*descmat);

  ObjectList<String>::iterator name;
  for(name = names.begin();
      name != names.end();
      name++)
    {
      if(rclass->getDebugLevel() > 1)
	{
	  cout << "Add Instance: " << *name << endl;
	}
      
      StartToAddInstanceToClusterTree(*name,TreeClass);
      if(rclass->getDebugLevel() > 2)
	{
	  Tree.print(cout);
	}
    }
  if(rclass->getDebugLevel() > 0)
    {
      Tree.PrintASCIITree(cout,(DataDirectedTreeClass *) TreeClass,
			  (DataObjectClass *) NodeClass,
			  *Instances,*(tclass->InstancesClass));
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
bool BaseDataCobwebClusterTreeCreate::Calculate(BaseDataSetOfInstances* instances,
						DataSetOfInstancesClass* instancesclasses,
						BaseDataAlgorithmRun *run,
						DataAlgorithmRunClass* rclass)
{
  return BuildIncrementClusterTree(instances,instancesclasses,
					run,rclass);
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
bool BaseDataCobwebClusterTreeCreate::WriteOutputValues(BaseDataSetOfInstances*,
							DataSetOfInstancesClass*,
							BaseDataAlgorithmRun* run,
							DataAlgorithmRunClass*)
{
  bool result = true;

  BaseDataCobwebClusterTree *ctree = new BaseDataCobwebClusterTree(*this);
  ctree->NameTag = getCobwebTreeName();
  ctree->EncodeDecodeClass = "Object.CobwebClusterTree";
  ctree->SetType(COBWEBCLUSTER_BASETREE_ID);
  
  run->AddParameter(ctree);

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
bool BaseDataCobwebClusterTreeCreate::ConcludeRun(BaseDataSetOfInstances*,
						  DataSetOfInstancesClass*,
						  BaseDataAlgorithmRun*,
						  DataAlgorithmRunClass*)
{
  bool result = true;
  return result;
}
 

/*S DataCobwebClusterTreeCreateClass
 */
/*F DataCobwebClusterTreeCreateClass()  . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataCobwebClusterTreeCreateClass::DataCobwebClusterTreeCreateClass()
{
  Identification = COBWEBCLUSTER_TREECREATE_ID;
  NameTag = COBWEBCLUSTER_TREECREATE_NAME;
  SubClass = COBWEBCLUSTER_BASETREE_NAME;
  EncodeDecodeClass = NameTag;

  String name(COBWEBCLUSTER_NODESTATS_NAME);
  DataClusterTreeClass::setNodeClassName(name);
} 
/*F DataCobwebClusterTreeCreateClass(data)  . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataCobwebClusterTreeCreateClass::DataCobwebClusterTreeCreateClass(const DataCobwebClusterTreeCreateClass& data)
  : DataCobwebClusterTreeClass(data)
{
} 
 
/*F DataCobwebClusterTreeCreateClass(id,name,descr) . . . . . . . constructor
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
DataCobwebClusterTreeCreateClass::DataCobwebClusterTreeCreateClass(const int id, 
								   const String& name,
								   const String& descr)
  : DataCobwebClusterTreeClass(id,name,descr)
{
  SubClass = COBWEBCLUSTER_BASETREE_NAME;
  EncodeDecodeClass = COBWEBCLUSTER_TREECREATE_NAME;
  String name1(COBWEBCLUSTER_NODESTATS_NAME);
  DataClusterTreeClass::setNodeClassName(name1);
}
 
/*F out1 = print(out) . . . . . . . . . . .  DataCobwebClusterTreeCreateClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataCobwebClusterTreeCreateClass::print(ostream& out) const
{
  DataCobwebClusterTreeClass::print(out);
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . .  DataCobwebClusterTreeCreateClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.	For the
**    base DataCobwebClusterTreeCreateClass, there is no further information.
**
**  REMARKS
**
*/
bool DataCobwebClusterTreeCreateClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataCobwebClusterTreeClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . .  DataCobwebClusterTreeCreateClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataCobwebClusterTreeCreateClass::CopyClone(Identify *  objc)
{
  DataCobwebClusterTreeCreateClass *objcfull = (DataCobwebClusterTreeCreateClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . .  DataCobwebClusterTreeCreateClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataCobwebClusterTreeCreateClass::Clone()
{
  DataCobwebClusterTreeCreateClass* id = new DataCobwebClusterTreeCreateClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . .  DataCobwebClusterTreeCreateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataCobwebClusterTreeCreateClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataCobwebClusterTreeClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . .  DataCobwebClusterTreeCreateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataCobwebClusterTreeCreateClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataCobwebClusterTreeClass::DecodeThis(buffer);
  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.	This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataCobwebClusterTreeCreateClass::BaseDataObjectExample()
{ 
  BaseDataObject *obj = (BaseDataObject *) new BaseDataCobwebClusterTreeCreate();
  obj->SetType(Identification);
  return obj;
}
/*F ans = TopDecode(buffer,obj) . . . . . .  DataCobwebClusterTreeCreateClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataCobwebClusterTreeCreateClass*& obj)
{
  obj = new DataCobwebClusterTreeCreateClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . BaseDataCobwebClusterTreeCreate
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataCobwebClusterTreeCreate*& obj)
{
  obj = new BaseDataCobwebClusterTreeCreate;
  return obj->DecodeThis(buffer);
}
 
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/

/*S Utilities
 */
/*F AddEntropyAlgorithmClasses(set) . . . . . . . .  basic algorithm data types
**
**  DESCRIPTION
**    set: The set of data types
**
**  REMARKS
**
*/
void AddCobwebAlgorithmClasses(DataSetOfObjectsClass& set)
{
  String nodestatsdescr("The Cluster Node Statistics");
  String cobtreedescr("The Cobweb Cluster Tree");
  String cobtreecreatedescr("Create Cobweb Cluster Tree");
  
  DataCobwebClusterNodeStatsClass nodestatsclass(COBWEBCLUSTER_NODESTATS_ID,
						 COBWEBCLUSTER_NODESTATS_NAME,
						 nodestatsdescr);
  DataCobwebClusterTreeClass cobtreeclass(COBWEBCLUSTER_BASETREE_ID,
					  COBWEBCLUSTER_BASETREE_NAME,
					  cobtreedescr);
  DataCobwebClusterTreeCreateClass cobtreecreateclass(COBWEBCLUSTER_TREECREATE_ID,
						      COBWEBCLUSTER_TREECREATE_NAME,
						      cobtreecreatedescr);

  set.AddObjectClass(nodestatsclass);
  set.AddObjectClass(cobtreeclass);
  set.AddObjectClass(cobtreecreateclass);

}
 
/*F CobwebClusterEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void CobwebClusterEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataCobwebClusterNodeStatsClass,BaseDataCobwebClusterNodeStats,COBWEBCLUSTER_NODESTATS_NAME);
  EncodeDecodeRegisterClass(DataCobwebClusterTreeClass,BaseDataCobwebClusterTree,COBWEBCLUSTER_BASETREE_NAME);
  EncodeDecodeRegisterClass(DataCobwebClusterTreeCreateClass,BaseDataCobwebClusterTreeCreate,COBWEBCLUSTER_TREECREATE_NAME);

//  bool (*toproutine)(CommBuffer&,Identify*&);
//
//  bool (*rout3)(CommBuffer&,DataCobwebClusterNodeStatsClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout3;
//  SingleDecodeRoutine p3(COBWEBCLUSTER_NODESTATS_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p3.StructureName] = p3;
//
//  bool (*rout4)(CommBuffer&,DataCobwebClusterTreeClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout4;
//  SingleDecodeRoutine p4(COBWEBCLUSTER_BASETREE_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p4.StructureName] = p4;
//
//  bool (*rout5)(CommBuffer&,DataCobwebClusterTreeCreateClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout5;
//  SingleDecodeRoutine p5(COBWEBCLUSTER_TREECREATE_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p5.StructureName] = p5;
//
//  String s31("Object.");
//  String s311(COBWEBCLUSTER_NODESTATS_NAME);
//  s31.AppendToEnd(s311);
//  bool (*rout33)(CommBuffer&,BaseDataCobwebClusterNodeStats*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout33;
//  SingleDecodeRoutine p33(s31,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p33.StructureName] = p33;
//
//  String s41("Object.");
//  String s411(COBWEBCLUSTER_BASETREE_NAME);
//  s41.AppendToEnd(s411);
//  bool (*rout44)(CommBuffer&,BaseDataCobwebClusterTree*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout44;
//  SingleDecodeRoutine p44(s41,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p44.StructureName] = p44;
//
//  String s51("Object.");
//  String s511(COBWEBCLUSTER_TREECREATE_NAME);
//  s51.AppendToEnd(s511);
//  bool (*rout55)(CommBuffer&,BaseDataCobwebClusterTreeCreate*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout55;
//  SingleDecodeRoutine p55(s51,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p55.StructureName] = p55;
  
}
