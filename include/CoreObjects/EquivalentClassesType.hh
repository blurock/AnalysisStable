/*  FILE     EquivalentClassesType.hh
**  PACKAGE  EquivalentClasses
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "EquivalentClasses" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_EQUIVALENTCLASSESTYPE_HH
#define CoreObjects_EQUIVALENTCLASSESTYPE_HH

/*C BaseDataDegreeOfEquivalence  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the DegreeOfEquivalence class definitions
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataDegreeOfEquivalence : public BaseDataObject
{
public:
  BaseDataDegreeOfEquivalence();
  BaseDataDegreeOfEquivalence(const BaseDataDegreeOfEquivalence& data);
  virtual bool Equivalent(BaseDataDegreeOfEquivalence *degree, BaseDataObject *obj);

  virtual bool WriteAsLine(ostream &out, DataObjectClass *cls);
  virtual bool WriteAsASCII(ostream &out, DataObjectClass *cls);
  virtual bool WriteAsLatex(ostream &out, DataObjectClass  *cls);
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataDegreeOfEquivalenceClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataDegreeOfEquivalenceClass : public DataObjectClass
{
  
public:
  DataDegreeOfEquivalenceClass();
  DataDegreeOfEquivalenceClass(const DataDegreeOfEquivalenceClass& data);
  DataDegreeOfEquivalenceClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataDegreeOfEquivalenceNumeric  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the DegreeOfEquivalenceNumeric class definitions
**
**  REMARKS
**    Inheirits BaseDataDegreeOfEquivalence
*/
class BaseDataDegreeOfEquivalenceNumeric : public BaseDataDegreeOfEquivalence
{
  BaseDataInstanceDoubleVector *Values;
public:
  BaseDataDegreeOfEquivalenceNumeric();
  BaseDataDegreeOfEquivalenceNumeric(const BaseDataDegreeOfEquivalenceNumeric& data);
  BaseDataDegreeOfEquivalenceNumeric(BaseDataInstanceDoubleVector *values);
  BaseDataInstanceDoubleVector *getValues() { return Values;}
  virtual bool Equivalent(BaseDataDegreeOfEquivalence *degree, BaseDataObject *obj);

  virtual bool WriteAsLine(ostream &out, DataObjectClass *cls);
  virtual bool WriteAsASCII(ostream &out, DataObjectClass *cls);
  virtual bool WriteAsLatex(ostream &out, DataObjectClass  *cls);
  STANDARD_VIRTUAL_METHODS_OBJECT;
};
/*C DataDegreeOfEquivalenceNumericClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataDegreeOfEquivalenceClass
*/
class DataDegreeOfEquivalenceNumericClass : public DataDegreeOfEquivalenceClass
{
  DataInstanceDoubleVectorClass *ValuesClass;
public:
  DataDegreeOfEquivalenceNumericClass();
  DataDegreeOfEquivalenceNumericClass(const DataDegreeOfEquivalenceNumericClass& data);
  DataDegreeOfEquivalenceNumericClass(const int id, 
		    const String& name,
		    const String& descr);

  DataInstanceDoubleVectorClass *getValuesClass() { return ValuesClass;}  
  STANDARD_VIRTUAL_METHODS_CLASS
};


/*C BaseDataEquivalentSet  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the EquivalentSet class definitions
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataEquivalentSet : public BaseDataObject
{
  BaseDataKeyWords ObjectNames;
  BaseDataDegreeOfEquivalence *Equivalence;
  BaseDataObject *CutOffCriteria;
  unsigned int SetCount;
public:
  BaseDataKeyWords *getNames() { return &ObjectNames;}
  BaseDataDegreeOfEquivalence *getDegreeOfEquivalence() { return Equivalence;}
  BaseDataObject *getCutOffCriteria();
  void setCutOffCriteria(BaseDataObject *criteria) { CutOffCriteria = criteria; }
  void setDegreeOfEquivalence(BaseDataDegreeOfEquivalence *equiv) {Equivalence = equiv;}
  BaseDataEquivalentSet();
  BaseDataEquivalentSet(const BaseDataEquivalentSet& data);
  bool Singleton() { return (ObjectNames.SizeOf() == 1);}

  bool BelongsInSet(BaseDataDegreeOfEquivalence *degree);
  void AddToSet(BaseDataDegreeOfEquivalence *degree);
  String *DefaultName(String& rootname);

  virtual bool WriteAsLine(ostream &out, DataObjectClass *cls);
  virtual bool WriteAsASCII(ostream &out, DataObjectClass *cls);
  virtual bool WriteAsLatex(ostream &out, DataObjectClass  *cls);
  STANDARD_VIRTUAL_METHODS_OBJECT;
};
/*C DataEquivalentSetClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION 714 349 4675                
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataEquivalentSetClass : public DataObjectClass
{
  DataDegreeOfEquivalenceClass *EquivalenceClass;
  DataObjectClass *CutOffCriteriaClass;
public:
  DataEquivalentSetClass();
  DataEquivalentSetClass(const DataEquivalentSetClass& data);
  DataEquivalentSetClass(const int id, 
		    const String& name,
		    const String& descr);
  DataDegreeOfEquivalenceClass *getEquivalenceClass() {return EquivalenceClass;}
  DataObjectClass *getCutOffCriteriaClass() { return CutOffCriteriaClass;}
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataSetOfEquivalentSets  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the SetOfEquivalentSets class definitions
**
**  REMARKS
**    Inheirits BaseDataSetOfObjects
*/
class BaseDataSetOfEquivalentSets : public BaseDataSetOfObjects
{
  unsigned int SetCount;
public:
  BaseDataSetOfEquivalentSets();
  BaseDataSetOfEquivalentSets(const BaseDataSetOfEquivalentSets& data);
  String *DefaultName(String& rootname);

  virtual bool WriteAsLine(ostream &out, DataObjectClass *cls);
  virtual bool WriteAsASCII(ostream &out, DataObjectClass *cls);
  virtual bool WriteAsLatex(ostream &out, DataObjectClass  *cls);
  STANDARD_VIRTUAL_METHODS_OBJECT;
};
/*C DataSetOfEquivalentSetsClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataSetOfEquivalentSetsClass : public DataSetOfObjectsClass
{
  DataEquivalentSetClass *EquivalentSetClass;
public:
  DataSetOfEquivalentSetsClass();
  DataSetOfEquivalentSetsClass(const DataSetOfEquivalentSetsClass& data);
  DataSetOfEquivalentSetsClass(const int id, 
		    const String& name,
		    const String& descr);
  DataEquivalentSetClass *getEquivalentSetClass() { return EquivalentSetClass;}
  
  DataSetOfObjectsClass *PointerToAllowedClasses() {return StandardAllowedClasses;}
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataSimpleEquivalentSetAlgorithm  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the SimpleEquivalentSetAlgorithm class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataSimpleEquivalentSetAlgorithm : public BaseDataAlgorithmOperation
{
  String RealCutOffS;
  BaseDataReal *RealCutOff;
  double CutOff;
  String MatrixOfProbsS;
  BaseDataInstanceDoubleMatrix *MatrixOfProbs;
  String EquivalentSetsS;
  String StartEquivalentSetsS;
  String NewEquivalentSetsS;

  DataSetOfEquivalentSetsClass *EquivalentSetsClass;
  BaseDataSetOfEquivalentSets *EquivalentSets;
  BaseDataSetOfEquivalentSets *NewEquivalentSets;

  MatrixNumeric *ProbMatrix;
  bool filterSingletons;
public:
  BaseDataSimpleEquivalentSetAlgorithm();
  BaseDataSimpleEquivalentSetAlgorithm(const BaseDataSimpleEquivalentSetAlgorithm& data);

  BaseDataSetOfEquivalentSets *GroupEquivalentSet(BaseDataEquivalentSet *set,
						  DataEquivalentSetClass *setclass);
  void AddNewSets(BaseDataSetOfEquivalentSets *sets);
  String *BuildEquivalenceName(BaseDataReal *cutoff, 
			       BaseDataInstanceDoubleVector *probs);
  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
};
/*C DataSimpleEquivalentSetAlgorithmClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataSimpleEquivalentSetAlgorithmClass : public DataAlgorithmOperationClass
{
public:
  DataSimpleEquivalentSetAlgorithmClass();
  DataSimpleEquivalentSetAlgorithmClass(const DataSimpleEquivalentSetAlgorithmClass& data);
  DataSimpleEquivalentSetAlgorithmClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataAddEquivalentNameToKeyWords  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the AddEquivalentNameToKeyWords class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataAddEquivalentNameToKeyWords : public BaseDataAlgorithmOperation
{
  String InstanceNameListS;
  BaseDataKeyWords *InstanceNameList;
  String ParametersS;
  BaseDataKeyWords *Parameters;
  String EquivalentSetsS;
  BaseDataSetOfEquivalentSets *EquivalentSets;
  
  String KeyWordListS;
  BaseDataKeyWords *KeyWordList;
  String ReplaceKeyS;
  bool ReplaceKey;
public:
  BaseDataAddEquivalentNameToKeyWords();
  BaseDataAddEquivalentNameToKeyWords(const BaseDataAddEquivalentNameToKeyWords& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;

};
/*C DataAddEquivalentNameToKeyWordsClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataAddEquivalentNameToKeyWordsClass : public DataAlgorithmOperationClass
{
public:
  DataAddEquivalentNameToKeyWordsClass();
  DataAddEquivalentNameToKeyWordsClass(const DataAddEquivalentNameToKeyWordsClass& data);
  DataAddEquivalentNameToKeyWordsClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};




/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
