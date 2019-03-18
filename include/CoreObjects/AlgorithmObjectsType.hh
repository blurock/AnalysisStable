/*  FILE     AlgorithmObjectsType.hh
**  PACKAGE  AlgorithmObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "AlgorithmObjects" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_ALGORITHMOBJECTSTYPE_HH
#define CoreObjects_ALGORITHMOBJECTSTYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
class DataAlgorithmSummaryClass;
class DataAlgorithmRunClass;
class DataAlgorithmOperationClass;
class DataTestAlgorithmClass;

class BaseDataAlgorithmOperation;

/*C BaseDataAlgorithmSummary  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This has the basic information defining an Algorithm:
**    - AlgorithmCategory: The routine base is the category in the algorithm tree of this algorithm
**    - Keys: A set of string keywords to guide the execution of the algorithm
**    - AlgorithmKeys: The set of specific routine names (referenced from the algorithm category) used
**    - Parameters: A set of extra parameters (no restriction on data type, but meant to be simple things like
**      numbers)
**
**    This is basically the minimal amount of information needed to define an algorithm and
**    to be able to reproduce the results.  It will also be used in the analysis of 
**    algorithms.
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataAlgorithmSummary : public BaseDataObject
{
  String AlgorithmCategory;
  BaseDataKeyWords Keys;
  BaseDataKeyWords AlgorithmKeys;
  ObjectNameClassPairs Parameters;
  BaseDataKeyWords Results;
  
public:
  BaseDataAlgorithmSummary();
  BaseDataAlgorithmSummary(const BaseDataAlgorithmSummary& data);

  STANDARD_VIRTUAL_METHODS_OBJECT  

  String& GetAlgorithmCategory();
  virtual void TransferKeyWords(BaseDataAlgorithmSummary *summary);
  BaseDataKeyWords& GetAlgorithmKeys();
  ObjectList<String>& ListOfKeyWords();
  bool KeyWordInList(const String& keyword);
  ObjectList<String>& ListOfParameterNames();
  bool ParameterInList(const String& name);
  ObjectList<String>& ListOfResultNames();
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataAlgorithmSummaryClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataAlgorithmSummaryClass : public DataObjectClass
{
public:
  DataSelectionTreeClass SelectClass;
  BaseDataSelectionTree SubAlgorithms;
  DataKeyWordsClass KeyWordClass;
  
  STANDARD_VIRTUAL_METHODS_CLASS

  DataAlgorithmSummaryClass();
  DataAlgorithmSummaryClass(const DataAlgorithmSummaryClass& data);
  DataAlgorithmSummaryClass(const int id, 
		    const String& name,
		    const String& descr);
  BaseDataSelections& GetSubAlgorithms(const String& category,
				       BaseDataKeyWords& algchoices);
  DataSetOfObjectsClass *PointerToAllowedClasses();
  bool SetUpSelectionTree(String& treename,
			  BaseDataSetOfInstances& instances,
			  DataSetOfInstancesClass& instsclass);
  
};

/*C BaseDataAlgorithmRun  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the AlgorithmRun class definitions
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataAlgorithmRun : public BaseDataObject
{
  BaseDataSelections SubAlgorithms;
  BaseDataInstance IntermediateResults;
  int IDCount;
  
public:
  
  BaseDataAlgorithmSummary AlgorithmSummary;  

  STANDARD_VIRTUAL_METHODS_OBJECT

  BaseDataAlgorithmRun();
  BaseDataAlgorithmRun(const BaseDataAlgorithmRun& data);

  ObjectList<String> GetListOfSubAlgorithms();
  BaseDataAlgorithmOperation* GetSubAlgorithm(const String& name);
  String& BuildFullAlgorithmCategory(const String& name);
  
  virtual void Instantiate(BaseDataAlgorithmSummary *summary,
			   DataAlgorithmRunClass *runclass);
  
  bool Run(const String& algorithm,
	   BaseDataSetOfInstances* instances,
	   DataSetOfInstancesClass* instancesclass,
	   DataAlgorithmRunClass* runclass);
  bool Run(const ObjectList<String>& algorithms,
	   BaseDataSetOfInstances* instances, 
	   DataSetOfInstancesClass* instancesclass,
	   DataAlgorithmRunClass* runclass);
  virtual bool Run(BaseDataSetOfInstances* instances, 
		   DataSetOfInstancesClass* instancesclass,
		   DataAlgorithmRunClass* runclass);
  virtual ObjectList<String> TransferInputParameters(BaseDataAlgorithmRun *run,
						     BaseDataSetOfInstances* instances);
  virtual ObjectList<String> TransferBackResultParameters(BaseDataAlgorithmRun *run,
							  BaseDataSetOfInstances* instances);
  bool ParameterInList(const String& name);
  BaseDataObject *ParameterValue(const String& name);
  bool AddParameter(BaseDataObject *obj);
  bool RemoveParameter(String& name);
  void PrintParameters(ostream& out);
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataAlgorithmRunClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataAlgorithmRunClass : public DataObjectClass
{
public:
  DataAlgorithmSummaryClass AlgorithmSummaryClass;
  
  DataAlgorithmRunClass();
  DataAlgorithmRunClass(const DataAlgorithmRunClass& data);
  DataAlgorithmRunClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS  
};

/*C BaseDataAlgorithmOperation  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the AlgorithmOperation class
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataAlgorithmOperation : public BaseDataObject
{
public:
  String debugPrintS;
  unsigned int debugPrint;
  
  STANDARD_VIRTUAL_METHODS_OBJECT

  BaseDataAlgorithmOperation();
  BaseDataAlgorithmOperation(const BaseDataAlgorithmOperation& data);

  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS

  bool operator()(BaseDataSetOfInstances* instances,
		  DataSetOfInstancesClass* instancesclass,
		  BaseDataAlgorithmRun* run,
		  DataAlgorithmRunClass* runclass);
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataAlgorithmOperationClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataAlgorithmOperationClass : public DataObjectClass
{
public:
  DataAlgorithmOperationClass();
  DataAlgorithmOperationClass(const DataAlgorithmOperationClass& data);
  DataAlgorithmOperationClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataTestAlgorithm  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the TestAlgorithm class
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataTestAlgorithm : public BaseDataAlgorithmOperation
{
  bool level0Parameter;
  bool parameterParameter;
  BaseDataObject *objTest;
  
public:
  BaseDataTestAlgorithm();
  BaseDataTestAlgorithm(const BaseDataTestAlgorithm& data);

  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataTestAlgorithmClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataTestAlgorithmClass : public DataAlgorithmOperationClass
{
public:
  DataTestAlgorithmClass();
  DataTestAlgorithmClass(const DataTestAlgorithmClass& data);
  DataTestAlgorithmClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

 
/*C AlgorithmSystemSave
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class AlgorithmSystemSave : public InstanceSystemMenu
{
  String AlgorithmClassS;
  
public:
  AlgorithmSystemSave(int argc, char *argv[])
    : InstanceSystemMenu(argc,argv),
    AlgorithmClassS("NONE")
    {
    }
  
  virtual void EncodeDecodeObjectsSetUp();
  virtual void StandardObjectsSetUp();
  virtual void CommandSetUp();

  virtual bool DecodeSavedObjects(CommBuffer& buffer);
  virtual bool EncodeSavedObjects(CommBuffer& buffer);

  String& getAlgorithmClassName()
    {
      return AlgorithmClassS;
    }
  void setAlgorithmClassName(String& name)
    {
      AlgorithmClassS = name;
    }
};


#endif
