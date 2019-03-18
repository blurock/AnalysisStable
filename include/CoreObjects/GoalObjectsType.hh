/*  FILE     GoalObjectsType.hh
**  PACKAGE  GoalObjects
**  AUTHOR   Edward s. Blurock
**
**  CONTENT
**    Class definitions for the "GoalObjects" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_GOALOBJECTSTYPE_HH
#define CoreObjects_GOALOBJECTSTYPE_HH

 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
class DataGoalSpecClass;
class DataGoalInstantiationClass;
class DataGoalSummaryClass;
class DataGoalRunClass;
class BaseDataSetOfGoalDefs;
class DataSetOfGoalDefsClass;


/*C BaseDataGoalSpec  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the GoalSpec class definitions
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataGoalSpec : public BaseDataObject
{
  ObjectNameClassPairs ParameterSpecs;
public:
  STANDARD_VIRTUAL_METHODS_OBJECT

  BaseDataGoalSpec();
  BaseDataGoalSpec(const BaseDataGoalSpec& data);
  
  bool AddGoalSpecification(const String& name, const String& classname);
  ObjectNameClassPairs* getParameterSpecs();

  bool operator==(BaseDataGoalSpec& spec);
  bool operator<(BaseDataGoalSpec& spec);
  bool VariableNamesEqual(BaseDataGoalSpec& spec);
  bool ClassNamesEqual(BaseDataGoalSpec& spec);
};
/*C DataGoalSpecClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataGoalSpecClass : public DataObjectClass
{
public:
  STANDARD_VIRTUAL_METHODS_CLASS

  DataGoalSpecClass();
  DataGoalSpecClass(const DataGoalSpecClass& data);
  DataGoalSpecClass(const int id, 
		    const String& name,
		    const String& descr);
};

/*C BaseDataGoalSummary . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**
**  REMARKS
**    Inheirits BaseDataGoalSpec
*/
class BaseDataGoalSummary : public BaseDataAlgorithmSummary
{
  ObjectList<BaseDataGoalSpec> Prerequisites;
public:
  STANDARD_VIRTUAL_METHODS_OBJECT

  BaseDataGoalSpec GoalSpec;
  BaseDataGoalSummary();
  BaseDataGoalSummary(const BaseDataGoalSummary& data);

  bool AddPrerequisitesToEnd(ObjectList<BaseDataGoalSpec>& slist);
  ObjectList<BaseDataGoalSpec> GetPrerequisites();
};
/*C DataGoalSummaryClass  . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataGoalSpecClass
*/
class DataGoalSummaryClass : public DataAlgorithmSummaryClass
{
public:
  STANDARD_VIRTUAL_METHODS_CLASS

  DataGoalSpecClass GoalSpecClass;
  DataGoalSummaryClass();
  DataGoalSummaryClass(const DataGoalSummaryClass& data);
  DataGoalSummaryClass(const int id, 
		    const String& name,
		    const String& descr);
};

/*C BaseDataSetOfGoalDefs . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**
**  REMARKS
**    Inheirits BaseDataSetOfObjects
*/
class BaseDataSetOfGoalDefs : public BaseDataObject
{
  SearchableObjectListFull<BaseDataGoalSpec,BaseDataGoalSummary> GoalDefs;
  
public:
  STANDARD_VIRTUAL_METHODS_OBJECT

  BaseDataSetOfGoalDefs();
  BaseDataSetOfGoalDefs(const BaseDataSetOfGoalDefs& data);

  BaseDataGoalSummary& GetGoalSummary(BaseDataGoalSpec& spec);
  void GetPrerequisiteListReverse(ObjectList<BaseDataGoalSpec>& specs, 
				  ObjectList<BaseDataGoalSpec>& prereqs);
};
/*C DataSetOfGoalDefsClass  . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataSetOfGoalDefsClass : public DataObjectClass
{
public:
  DataGoalSummaryClass GoalSummaryClass;
  
  STANDARD_VIRTUAL_METHODS_CLASS

  DataSetOfGoalDefsClass();
  DataSetOfGoalDefsClass(const DataSetOfGoalDefsClass& data);
  DataSetOfGoalDefsClass(const int id, 
		    const String& name,
		    const String& descr);
};

/*C BaseDataGoalRun . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**
**  REMARKS
**    Inheirits BaseDataAlgorithmRun
*/
class BaseDataGoalRun : public BaseDataAlgorithmRun
{
  BaseDataGoalSummary GoalSummary;
  BaseDataInstance GoalParameters;
  
public:
  String goalDebugLevelS;
  unsigned int goalDebugLevel;
  
  STANDARD_VIRTUAL_METHODS_OBJECT

  BaseDataGoalRun();
  BaseDataGoalRun(const BaseDataGoalRun& data);

  virtual void Instantiate(BaseDataAlgorithmSummary *summary,
			   DataAlgorithmRunClass *runclass);
  virtual bool Run(BaseDataSetOfInstances* instances,
		   DataSetOfInstancesClass* instancesclass,
		   DataAlgorithmRunClass* runclass);
  bool Run(ObjectList<BaseDataGoalSpec>& specs,
	   BaseDataSetOfInstances* instances,
	   DataSetOfInstancesClass* instancesclass,
	   DataAlgorithmRunClass* runclass);
  bool Run(BaseDataGoalSpec& spec,
	   BaseDataSetOfInstances* instances,
	   DataSetOfInstancesClass* instancesclass,
	   DataAlgorithmRunClass* runclass);
  virtual ObjectList<String> TransferInputParameters(BaseDataAlgorithmRun *run,
				       BaseDataSetOfInstances *instances);
  virtual ObjectList<String> TransferBackResultParameters(BaseDataAlgorithmRun *run,
					    BaseDataSetOfInstances *instances);
};
/*C DataGoalRunClass  . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmRunClass
*/
class DataGoalRunClass : public DataAlgorithmRunClass
{
  DataGoalSummaryClass GoalSummaryClass;
  DataSetOfGoalDefsClass GoalDefsClass;
  
public:
  BaseDataSetOfGoalDefs GoalDefs;

  STANDARD_VIRTUAL_METHODS_CLASS

  DataGoalRunClass();
  DataGoalRunClass(const DataGoalRunClass& data);
  DataGoalRunClass(const int id, 
		    const String& name,
		    const String& descr);
};
/*C AlgorithmSystemSave
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class GoalSystemSave : public AlgorithmSystemSave
{
  String GoalClassS;
  
public:
  GoalSystemSave(int argc, char *argv[])
    : AlgorithmSystemSave(argc,argv),
    GoalClassS("NONE")
    {
    }
  
  virtual void EncodeDecodeObjectsSetUp();
  virtual void StandardObjectsSetUp();
  virtual void CommandSetUp();

  virtual bool DecodeSavedObjects(CommBuffer& buffer);
  virtual bool EncodeSavedObjects(CommBuffer& buffer);

  String& getGoalClassName()
    {
      return GoalClassS;
    }
  void setGoalClassName(String& name)
    {
      GoalClassS = name;
    }
};

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
