/*  FILE     CoreDataObjects.hh
**  PACKAGE  CoreDataObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "CoreDataObjects" package in the CoreObjects environment
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_COREDATAOBJECTS_HH
#define CoreObjects_COREDATAOBJECTS_HH

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "BasisSystem.hh"
#include "ONames.hh"
#include "CommBuffer.hh"
#include "String.hh"
#include "MixedClasses.hh"
#include "Objects.hh"
#include "Pairs.hh"
#include "NonStandard.hh"

/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#define EncodeDecodeRegisterClass(T1, T2, name)                \
{                                                              \
  bool (*toproutine)(CommBuffer&,Identify*&);                  \
                                                               \
  String sb("Object.");                                        \
  String sc(name);                                             \
  sb.AppendToEnd(sc);                                          \
  bool (*rout1)(CommBuffer&,T2*&) = TopDecode;                 \
  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout1;       \
  SingleDecodeRoutine p1(sb,toproutine);                       \
  (*SetOfEncodeDecodeRoutines)[p1.StructureName] = p1;         \
                                                               \
                                                               \
  bool (*rout5)(CommBuffer&,T1*&) = TopDecode;                 \
  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout5;       \
  SingleDecodeRoutine p5(name,toproutine);                     \
  (*SetOfEncodeDecodeRoutines)[p5.StructureName] = p5;         \
}
#define STANDARD_VIRTUAL_METHODS_OBJECT                                        \
  virtual Identify * Clone();                                                  \
  virtual void CopyClone(Identify *obj);                                 \
  virtual bool EncodeThis(CommBuffer& buffer);                                 \
  virtual bool DecodeThis(CommBuffer& buffer);                                 \
  virtual bool Read(istream& in, DataObjectClass* objc);                       \
  virtual bool Read(istream& in, DataObjectClass* objc, const String& name);   \
  virtual ostream& print(ostream& out) const;
#define STANDARD_VIRTUAL_METHODS_CLASS                                         \
  virtual ostream& print(ostream& out) const;                                  \
  using BaseDataObject::Read;						\
  virtual bool Read(istream& in, DataSetOfObjectsClass& set);                  \
  virtual void CopyClone(Identify* objc);                               \
  virtual Identify * Clone(void);                                              \
  virtual bool EncodeThis(CommBuffer& buffer);                                 \
  virtual bool DecodeThis(CommBuffer& buffer);                                 \
  virtual BaseDataObject * BaseDataObjectExample();


#define DEBUG_LEVEL_MULT           1000
#define DEBUG_LEVEL_0              0
#define DEBUG_LEVEL_1              1
#define DEBUG_LEVEL_2              2
#define DEBUG_LEVEL_3              3
#define DEBUG_LEVEL_4              4
#define DEBUG_LEVEL0_NAME          "Debug0"
#define DEBUG_LEVEL1_NAME          "Debug1"
#define DEBUG_LEVEL2_NAME          "Debug2"
#define DEBUG_LEVEL3_NAME          "Debug3"
#define DEBUG_LEVEL4_NAME          "Debug4"

#define CORE_PRINT_BASE            1
#define CORE_PRINT_ID_QUIET        0
#define CORE_PRINT_ID_LINE         1
#define CORE_PRINT_ID_DETAILED     2
#define CORE_PRINT_ID_WRITE        3
#define CORE_PRINT_ID_LATEX        4

#define CORE_PRINT_NAME_QUIET        "Quiet"
#define CORE_PRINT_NAME_LINE         "Line"
#define CORE_PRINT_NAME_DETAILED     "Detailed"
#define CORE_PRINT_NAME_WRITE        "Write"
#define CORE_PRINT_NAME_LATEX        "Latex"

#define COREOBJECTS_BASE_ID         98
#define COREOBJECTS_BASE_NAME       "Object"
#define COREOBJECTS_SET_ID         99
#define COREOBJECTS_SET_NAME       "SetOfObjects"

#define NUMERIC_ID_BASE               100
#define LOGICAL_ID_BASE               1000
#define ODREADFUNC_ID_BASE            2000
#define OPERATION_ID_BASE             3000
#define LOGICALOP_ID_BASE             3100
#define INSTANCE_ID_BASE              4000
#define SELECTION_BASE_ID             5000
#define ALGORITHM_BASE_ID             6000
#define INSTALGORITHMS_BASE_ID        7000
#define MATALGORITHMS_BASE_ID         8000
#define GOALS_BASE_ID                 9000
#define PREDICATE_ID_BASE             10000
#define ENTROPY_BASE_ID               11000
#define TREE_DECISION_BASE_ID         12000
#define PREDGEN_ID_BASE               13000
#define COBWEBCLUSTER_ID              14000
#define DIRECTEDTREE_ID_BASE          15000
#define EVALUATIONTREE_ID_BASE        16000
#define DATAOBJECTS_ID_BASE           17000
#define EXPRESSIONTREE_ID_BASE        18000
#define DISTRIBUTION_BASE_ID          19000
#define PCAINSTANCE_BASE_ID           20000
#define PREDICATEGOAL_BASE            21000
#define BASEOBJECTS_BASE_ID           22000
#define OPTIMIZECOST_BASE             30000
#define OPTIMIZE_BASE                 30100
#define POPULATION_BASE               30200
#define PARAMETERIZED_BASE            30300
#define GENETIC_BASE                  30400
#define RULESYSTEM_BASE               30500
#define VECOPERATION_BASE             30600
#define VERIFY_ENVIRONMENT_BASE       30700 
#define CONSECUTIVE_BASE              30800
#define NUMERICPROPS_BASE             30900
#define EQUIVALENTSETS_BASE           31000
#define CHEMKINCONVERT_BASE_ID        31100
#define RUNIGNITION_BASE_ID           31200
#define ITERATOR_BASE_ID              31300

#define ALGORITHM_KEYWORDS_ID       ALGORITHM_BASE_ID + 10
#define ALGORITHM_KEYWORDS_NAME         "KeyWords"

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjectsType.hh"

/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
extern DataSetOfObjectsClass *StandardAllowedClasses;

ObjectList<String> *SetOfDerivedClasses(DataSetOfObjectsClass *classes,
					ObjectList<String>& baseclasses);
bool ReadInClassNamePairsAndSetOfObjects(istream& in,
					 String &name,
					 BaseDataSetOfObjects *set,
					 DataSetOfObjectsClass *oclasses);
void WriteSetOfClasses(ObjectList<String>& names, 
		       ostream& out,
		       DataSetOfObjectsClass& classes);
void SetUpClassNamePairs(BaseDataSetOfObjects *objects,
			 DataSetOfObjectsClass *classes);

void AddCoreDataObjectClasses(DataSetOfObjectsClass& set);
extern void InitialCoreDataObjectEncodeDecodeRoutines();

bool DecodeFromName(bool result, CommBuffer& buffer, String& name, Identify *&str);
BaseDataObject *PointerClone(BaseDataObject *obj);
bool BoolEncode(CommBuffer& buffer, bool b);
bool BoolDecode(CommBuffer& buffer, bool& b);
bool PointerDecode(CommBuffer &buffer, BaseDataObject *&obj);
bool PointerEncode(CommBuffer &buffer, BaseDataObject *obj);
void PointerPrint(ostream& out, const String& title, const String& noobject, BaseDataObject *obj);
bool PointerClassRead(istream& in,DataObjectClass *&obj,
		      const String& classtype,
		      DataSetOfObjectsClass &set, 
		      const String& notdefined);
bool PointerObjectRead(istream& in, BaseDataObject *&obj,DataObjectClass *cls, String& notdefined);

bool CheckReadKeyWord(istream& in, String &key);

extern String PlaceHoldersKeyWord;
extern String NoClassNamePairsKeyWord;
extern String NoReadKeyWord;
extern String ReadAsTripletKeyWord;

#endif

