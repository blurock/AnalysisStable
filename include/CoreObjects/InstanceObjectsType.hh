/*  FILE     InstanceObjectsType.hh
**  PACKAGE  InstanceObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "InstanceObjects" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_INSTANCEOBJECTSTYPE_HH
#define CoreObjects_INSTANCEOBJECTSTYPE_HH

 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
class DataInstanceDoubleMatrixClass;
class DataInstanceDoubleVectorClass;
class DataInstanceClass;
class DataSetOfInstancesClass;
class BaseDataInstanceDoubleVector;
/*C BaseDataInstance  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the Instance class definitions
**
**  REMARKS
**    Inheirits BaseDataSetOfObjects
*/
class BaseDataInstance : public BaseDataSetOfObjects
{
public:
  String Description;
    
  BaseDataInstance();
  BaseDataInstance(const BaseDataInstance& data);
    
  ObjectList<String> ListOfAttributeNames(ObjectList<int>& tlist);
  BaseDataObject *GetAttributeValue(const String& name);
  bool ObjectExists(const String& name);
  bool AddAttribute(BaseDataObject *obj);
  bool RemoveAttribute(String& name);
    
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataInstanceClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataInstanceClass : public DataSetOfObjectsClass
{
public:
  DataInstanceClass();
  DataInstanceClass(const DataInstanceClass& data);
  DataInstanceClass(const int id, 
                    const String& name,
                    const String& descr);
  virtual BaseDataObject * BaseDataObjectExample();
  virtual DataSetOfObjectsClass *PointerToAllowedClasses();
};

/*C BaseDataSetOfInstances  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the SetOfInstances class
**
**  REMARKS
**    Inheirits BaseDataSetOfObjects
*/
class BaseDataSetOfInstances : public BaseDataSetOfObjects
{
  String Description;
  BaseDataSetOfObjects Instances;
  
public:
  BaseDataSetOfInstances();
  BaseDataSetOfInstances(const BaseDataSetOfInstances& data);

  bool AddInstance(BaseDataInstance& instance);
  bool RemoveInstance(String& name);
  ObjectList<String> ListOfInstanceNames();
  bool InstanceInSet(const String& name);
  BaseDataInstance *GetInstance(const String& name);
  ObjectList<String>& ListOfInstanceAttributeNames(ObjectList<String>& instances,
                                                   ObjectList<String>& tlist,
                                                   DataSetOfInstancesClass& setclasses,
                                                   bool commontoall);
  ObjectList<String> ListOfSetAttributeNames(ObjectList<int>& tlist);
  void PrintMissingAttributeNames(ObjectList<String>& instances,
                                  ObjectList<String>& tlist,
                                  DataSetOfInstancesClass& setclasses,
                                  ObjectList<String>& fullset);

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataSetOfInstancesClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataSetOfInstancesClass : public DataSetOfObjectsClass
{
  DataInstanceClass AllowedInstanceClasses;
  
public:
  DataSetOfInstancesClass();
  DataSetOfInstancesClass(const DataSetOfInstancesClass& data);
  DataSetOfInstancesClass(const int id, 
                          const String& name,
                          const String& descr);

  ObjectList<int>& TranslateInstanceAttributeClassNames(const ObjectList<String>& names);
  ObjectList<int>& TranslateSetAttributeClassNames(const ObjectList<String>& names);
  DataObjectClass *GetAllowedInstanceClasses();
  virtual DataSetOfObjectsClass *PointerToAllowedClasses();
  DataInstanceClass *PointerToInstanceClass();
  
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataInstanceDoubleMatrix  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the InstanceDoubleMatrix
**
**  REMARKS
**    Inheirits BaseDataDoubleMatrix
*/
class BaseDataInstanceDoubleMatrix : public BaseDataDoubleMatrix
{
  BaseDataKeySet Parameters;
  BaseDataKeySet Instances;
public:
  BaseDataInstanceDoubleMatrix();
  BaseDataInstanceDoubleMatrix(const BaseDataInstanceDoubleMatrix& data);
  BaseDataInstanceDoubleMatrix(const MatrixNumeric& mat,
                               const BaseDataKeySet& instances,
                               const BaseDataKeySet& parameters);
  BaseDataInstanceDoubleMatrix(const MatrixNumeric& mat,
                               const BaseDataKeyWords& instances,
                               const BaseDataKeyWords& parameters);
  STANDARD_VIRTUAL_METHODS_OBJECT;
  BaseDataKeySet& getInstanceNames();
  BaseDataKeySet& getParameterNames();
  unsigned int CorrespondingColumn(String& name);
  unsigned int CorrespondingRow(String& rowname);
  BaseDataInstanceDoubleVector *getColumn(String& colname) ;
  BaseDataInstanceDoubleVector *getRow(String& rowname); 
  MatrixNumeric *formReducedMatrix(BaseDataKeyWords *parameters);
  BaseDataInstanceDoubleMatrix *isolateRowsByInstanceName(BaseDataKeyWords *rownames);
  BaseDataInstanceDoubleMatrix *isolateColumnsByParameterName(BaseDataKeyWords *rownames);
};
/*C DataInstanceDoubleMatrixClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataDoubleMatrixClass
*/
class DataInstanceDoubleMatrixClass : public DataDoubleMatrixClass
{
public:
  DataInstanceDoubleMatrixClass();
  DataInstanceDoubleMatrixClass(const DataInstanceDoubleMatrixClass& data);
  DataInstanceDoubleMatrixClass(const int id, 
                                const String& name,
                                const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataInstanceDoubleVector  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the InstanceDoubleVector class
**
**  REMARKS
**    Inheirits BaseDataDoubleVector
*/
class BaseDataInstanceDoubleVector : public BaseDataDoubleVector
{
  BaseDataKeySet Parameters;
public:
  BaseDataInstanceDoubleVector();
  BaseDataInstanceDoubleVector(const BaseDataInstanceDoubleVector& data);
  BaseDataInstanceDoubleVector(VectorNumeric& vec, BaseDataKeySet& keys);
  BaseDataInstanceDoubleVector(VectorNumeric& vec, BaseDataKeyWords& keys);
  STANDARD_VIRTUAL_METHODS_OBJECT
  void AddElement(String& name, double value);
  BaseDataKeySet& getParameterNames() { return Parameters;};
  //BaseDataSetOfObjects *asAttributeValuePairs();
};
/*C DataInstanceDoubleVectorClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**    This is the base function about a data type:
**       Identification: The numerical value of the type
**       NameTag: The ASCII name of the type
**       Description: The text description of the class
**
**  REMARKS
**     Inheirits DataDoubleVectorClass
*/
class DataInstanceDoubleVectorClass : public DataDoubleVectorClass
{
public:
  DataInstanceDoubleVectorClass();
  DataInstanceDoubleVectorClass(const DataInstanceDoubleVectorClass& data);
  DataInstanceDoubleVectorClass(const int id, 
                                const String& name,
                                const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C InstanceSystem
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class InstanceSystem : public ReactionSystemLevel1
{
  DataSetOfObjectsClass Standard;
public:
  BaseDataSetOfInstances Instances;
  DataSetOfInstancesClass InstanceClasses;

  InstanceSystem(int argc, char *argv[])
    : ReactionSystemLevel1(argc,argv)
    {
    }
  DataSetOfObjectsClass& getStandard();
  

  virtual void EncodeDecodeObjectsSetUp();
  virtual void StandardObjectsSetUp();
  virtual void CommandSetUp();
  
  virtual void Initialization();
  virtual int Run();
  virtual int Exit();

  int FileReadIn();
  int EncodeTest();
  int CloneDeleteTest();
  
};
 
/*C BaseDataProgressVariableMatrix  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ProgressVariableMatrix class definitions
**
**  REMARKS
**    Inheirits BaseDataDoubleMatrix
*/
class BaseDataProgressVariableMatrix : public BaseDataInstanceDoubleMatrix
{
public:
  BaseDataProgressVariableMatrix();
  BaseDataProgressVariableMatrix(const BaseDataProgressVariableMatrix& data);

  bool AddAsInstances(BaseDataSetOfInstances &instances,
		      DataSetOfInstancesClass &instclass);

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataProgressVariableMatrixClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataDoubleMatrixClass
*/
class DataProgressVariableMatrixClass : public DataInstanceDoubleMatrixClass
{
public:
  String InstanceBaseName;
  String ProgressVariable;

  DataProgressVariableMatrixClass();
  DataProgressVariableMatrixClass(const DataProgressVariableMatrixClass& data);
  DataProgressVariableMatrixClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS

  void Initialize();

};



/*C InstanceSystemSave
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class InstanceSystemSave : public InstanceSystem
{
  String RootName;
  bool SaveIt;
  bool IncrementVersion;
  bool ReadIt;
  String VersionS;
  unsigned int Version;
  bool Successful;
  String Delimitor;
  String SysCommand;

  OpenInputDataFile *RestartFile;
  OpenOutputDataFile *SaveFile;
public:
  InstanceSystemSave(int argc, char *argv[])
    : InstanceSystem(argc,argv),
      SaveIt(false),
      IncrementVersion(true),
      ReadIt(false),
      Successful(true),
      Delimitor("."),
      RestartFile(NULL),
      SaveFile(NULL)
    {
    }
  
  virtual void CommandSetUp();
  virtual void Initialization();
  virtual int Exit();
  virtual bool DecodeSavedObjects(CommBuffer& buffer);
  virtual bool EncodeSavedObjects(CommBuffer& buffer);
  bool RestartObjectInitialization();
  bool RestartObjectExit();
  bool SetUpOutputFile();
  bool ReadInVersion();
  bool SetUpCommand();
  int TopLevelMenu(ostream& out);
  int SecondLevelStart(ostream& out);
  int PrintInstancesInfo();
  bool WriteCPP(String& writename,
		CommBuffer* buffer);
  bool WriteC(String& writename,
		CommBuffer* buffer);
  bool ReadCPP(String &readname,
	       CommBuffer *&buffer);
  bool ReadC(String &readname,
	       CommBuffer *&buffer);
  virtual void PrintListOfNames(String& ptype, 
				String& prefix,
				ostream& out,
				ObjectList<String>& names);
  virtual void BaseDataObjectOut(String& ptype, 
				 BaseDataObject *obj, 
				 ostream& out);
  unsigned int getVersion()
    {
      return Version;
    }
  String& getRootName()
    {
      return RootName;
    }
};


/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
