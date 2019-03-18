/*  FILE     CoreDataObjectsType.hh
**  PACKAGE  CoreDataObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "CoreDataObjects" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_COREDATAOBJECTSTYPE_HH
#define CoreObjects_COREDATAOBJECTSTYPE_HH
 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
class DataObjectClass;
class DataSetOfObjectsClass;

/*C BaseDataObject  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the most baPrint Class
sic data object.  It defines the general
**    routines for all data objects:
**    - GetType(): Retrieve the type of variable
**
**    and also the set of virtual functions for each object
**    - Read(stream,objc): Read from ASCII stream (using objc for additional format info)
**    - Read(stream,objc,name): Read from ASCII stream (if the name of the object already known)
**    - Write(stream,objc): Write with formatting details
**    - Clone(),CloneCopy(obj): Clone a copy
**    - EncodeThis(buffer),DecodeThis(buffer): Encode and Decode routines
**    - print(out): Standard default output routine
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataObject : public Identify
{
  unsigned int DataType;
    
public:
  String EncodeDecodeClass;
  unsigned int GetType() const;
  void SetType(unsigned int type);
    
  BaseDataObject();
  BaseDataObject(const BaseDataObject& data);
    
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool Write(ostream& out, DataObjectClass *objc);
  virtual bool WriteAsLine(ostream& out, DataObjectClass *objc);
  virtual bool WriteAsASCII(ostream& out, DataObjectClass *objc);
  virtual bool WriteAsLatex(ostream& out, DataObjectClass  *objc);

  virtual bool WriteAsLine(ostream& out)  {return false; };
  virtual bool WriteAsASCII(ostream& out) {return false; }
  virtual bool WriteAsLatex(ostream& out) {return false; }

  virtual bool operator==(BaseDataObject *obj);
  virtual bool operator>(BaseDataObject *obj);
  virtual bool operator<(BaseDataObject *obj);
};
/*C DataObjectClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**    This is the base function about a data type:
**       Identification: The numerical value of the type
**       NameTag: The ASCII name of the type
**       Description: The text description of the class
**
**    The are two print modes in this class:
**    - PrintMode: This specifies how the object represented by this class
**      should be printed
**    - ClassPrintMode: This is how this class itself should be printed 
**      (when, for example, a list of possible object types is wanted).
**
**    The basic functions:
**    - SetPrintMode(mode): The print mode of the data type 
**      (used in the print routine)
**    - SetPrintMode(mode): The print mode of the class itself
**      (used in the print routine)
**
**  REMARKS
**
*/
class DataObjectClass : public BaseDataObject
{
  unsigned int PrintMode;
  unsigned int ClassPrintMode;
  
public:
  String SubClass;
  String Description;

  DataObjectClass();
  DataObjectClass(const DataObjectClass& data);
  DataObjectClass(const int id, 
                  const String& name,
                  const String& descr);
  istream& ReadDataObjectClass(istream& in);

  unsigned int getPrintMode();
  unsigned int getClassPrintMode();
  unsigned int getDebugLevel();
  void SetPrintMode(const unsigned int mode);
  void SetClassPrintMode(const unsigned int mode);
  void SetDebugLevel(const unsigned int debug);
  
  virtual bool WriteAsLine(ostream& out);
  virtual bool WriteAsASCII(ostream& out);
  virtual bool WriteAsLatex(ostream& out);

  STANDARD_VIRTUAL_METHODS_CLASS;
};
 
/*C BaseDataSetOfObjects  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the SetOfObjects class definitions.  
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataSetOfObjects : public BaseDataObject
{
  SearchableListOfMixedObjectsIdentify Objects;
  NameIDCorrespondences IDCorrs;
  unsigned int IDcount;
  bool AssignedID;
  
public:
  BaseDataSetOfObjects();
  BaseDataSetOfObjects(const BaseDataSetOfObjects& data);
  STANDARD_VIRTUAL_METHODS_OBJECT;

  void Initialisation();
  virtual BaseDataObject *GetObject(const unsigned int id);
  virtual BaseDataObject *GetObject(const String& name);
  virtual bool AddObject(BaseDataObject *obj);
  virtual bool RemoveObject(String& name);
  virtual ObjectList<String> ListOfObjectNames();
  virtual ObjectList<String> ListOfObjectNames(ObjectList<int>& tlist);
  virtual bool IsInList(const String& name);
  ObjectList<int>& NamesToIDs(const ObjectList<String>& names);
  unsigned int MergeSetOfObjects(BaseDataSetOfObjects *objects);
  unsigned int NextIdentification();

  bool ReadAsTriplet(istream& in, DataSetOfObjectsClass *set);
  void setTitle(String& title);
  void setDelimitor(String& delimitor);
  void NoIDAssignment();

  virtual bool WriteAsLine(ostream& out, DataObjectClass *objc);
  virtual bool WriteAsASCII(ostream& out, DataObjectClass *objc);
  virtual bool WriteAsLatex(ostream& out, DataObjectClass  *objc);
};
/*C DataSetOfObjectsClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataSetOfObjectsClass : public DataObjectClass
{
  BaseDataSetOfObjects AllowedClasses;
  ObjectNameClassPairs ObjectTypes;
  unsigned int IDCount;
  
  int PrintMode;
  int ClassPrintMode;
  String ClassEndDelimitor;
  NameIDCorrespondences AvailablePrintModes;

public:
  bool ReadClassPairs;
  bool ReadAllowedClasses;

  DataSetOfObjectsClass();
  DataSetOfObjectsClass(const DataSetOfObjectsClass& data);
  DataSetOfObjectsClass(const int id, 
                        const String& name,
                        const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;

  bool ReadInAttributeTypes(istream& in);
  virtual DataObjectClass * GetObjectClass(const unsigned int id);
  virtual DataObjectClass * GetObjectClass(const String& name);
  virtual bool AddObjectClass(DataObjectClass& c);

  unsigned int        MergeSetOfObjectClasses(DataSetOfObjectsClass& classes);
  ObjectList<int>& TranslateClassNames(const ObjectList<String>& names);
  Identify * CloneClassFromName(String& name);
  virtual bool IsInList(const String& name);  
  virtual void Initialisation();
  bool ReplaceObjectTypes(const ObjectNameClassPairs& pairs);
  virtual ObjectList<String> ListOfClassNames();
  ObjectNameClassPairs& getNameClassPairs();

  bool IsOfClass(const String& reference, const String& subclass);
  bool IsOfClass(BaseDataObject& object,const String& subclass);
  void SetUpStandardPrintModes();
  bool SetPrintMode(const String& mode);
  bool SetClassPrintMode(const String& mode);
  void AddAvailablePrintMode(const int id,const String& mode);
  unsigned int GetPrintMode(const String modename);
  unsigned int GetPrintMode() const;
  unsigned int GetClassPrintMode() const;
  void ChangeEndDelimitor(const String& delim);
  unsigned int DebugLevel();
  void SetPrintModeOfPresentClasses(bool printobject, const int mode);

  unsigned int getIDCount();
  void setIDCount(unsigned int idcount);
  
  virtual DataSetOfObjectsClass *PointerToAllowedClasses();
  
  virtual bool WriteAsLine(ostream& out);
  virtual bool WriteAsASCII(ostream& out);
  virtual bool WriteAsLatex(ostream& out);


  void ReInitializeObjectNames();
  bool ReadInClassNamePairs(istream& in);
  bool ReadInClassNamePairsWithoutKeyWord(istream& in);

  friend class BaseDataSetOfObjects;
};
/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/

#endif
