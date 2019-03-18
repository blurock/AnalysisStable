/*  FILE     PredicateGenType.hh
**  PACKAGE  PredicateGen
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "PredicateGen" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_PREDICATEGENTYPE_HH
#define CoreObjects_PREDICATEGENTYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
class DataCriticalPointsClass;
class DataReadCriticalPointsClass;
class DataPatternsFromCriticalPointsClass;

/*C BaseDataCriticalPoints  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the CriticalPoints class definitions
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataCriticalPoints : public BaseDataObject
{
  String Parameter;
  SymmetricPairList<double> Points;
  
public:
  BaseDataCriticalPoints();
  BaseDataCriticalPoints(const BaseDataCriticalPoints& data);

  SymmetricPairList<double> *PointerToPoints();
  String& getParameterName();
  
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataCriticalPointsClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataCriticalPointsClass : public DataObjectClass
{
public:
  DataCriticalPointsClass();
  DataCriticalPointsClass(const DataCriticalPointsClass& data);
  DataCriticalPointsClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataReadCriticalPoints  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ReadCriticalPoints class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataReadCriticalPoints : public BaseDataAlgorithmOperation
{
  String InputfileNamesS;
  BaseDataKeyWords* fileNamesK;
  String InputrootNameS;
  BaseDataKeyWords* rootNameK;
  
  String OutputPointListS;
  BaseDataKeyWords* PointList;
  String OutputCriticalPointsS;
  BaseDataCriticalPoints* Points;

  String rootName;
  
public:
  BaseDataReadCriticalPoints();
  BaseDataReadCriticalPoints(const BaseDataReadCriticalPoints& data);
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataReadCriticalPointsClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataReadCriticalPointsClass : public DataAlgorithmOperationClass
{
public:
  DataReadCriticalPointsClass();
  DataReadCriticalPointsClass(const DataReadCriticalPointsClass& data);
  DataReadCriticalPointsClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataPatternsFromCriticalPoints  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the PatternsFromCriticalPoints class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataPatternsFromCriticalPoints : public BaseDataAlgorithmOperation
{
  String InputpredicateTypesS;
  BaseDataKeyWords* predicateTypes;
  String InputcriticalPointListS;
  BaseDataKeyWords* criticalPointList;
  
  String OutputlistOfPredicatesS;
  BaseDataKeyWords* listOfPredicates;
  String OutputlistOfPartitionsS;
  BaseDataKeyWords* listOfPartitions;

public:
  BaseDataPatternsFromCriticalPoints();
  BaseDataPatternsFromCriticalPoints(const BaseDataPatternsFromCriticalPoints& data);
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataPatternsFromCriticalPointsClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataPatternsFromCriticalPointsClass : public DataAlgorithmOperationClass
{
public:
  DataPatternsFromCriticalPointsClass();
  DataPatternsFromCriticalPointsClass(const DataPatternsFromCriticalPointsClass& data);
  DataPatternsFromCriticalPointsClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataPredicatesFromDistribution  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the PredicatesFromDistribution class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataPredicatesFromDistribution : public BaseDataAlgorithmOperation
{
  String DistributionNamesS;
  BaseDataKeyWords *DistributionNames;
  String RootNameS;
  BaseDataString *RootNameString;
  String RootName;
  String PredicateS;
  BaseDataOperation *Predicate;
public:
  BaseDataPredicatesFromDistribution();
  BaseDataPredicatesFromDistribution(const BaseDataPredicatesFromDistribution& data);

  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
  STANDARD_VIRTUAL_METHODS_OBJECT;
};
/*C DataPredicatesFromDistributionClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataPredicatesFromDistributionClass : public DataAlgorithmOperationClass
{
public:
  DataPredicatesFromDistributionClass();
  DataPredicatesFromDistributionClass(const DataPredicatesFromDistributionClass& data);
  DataPredicatesFromDistributionClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataPredicatesFromKeyWords  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the PredicatesFromKeyWords class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataPredicatesFromKeyWords : public BaseDataAlgorithmOperation
{
  String KeyWordListS;
  BaseDataKeyWords *KeyWordList;
  String ParameterListS;
  BaseDataKeyWords *ParameterList;
  String RootNameS;
  BaseDataString *RootNameString;
  String RootName;
  String PredicateS;
  BaseDataOperation *Predicate;
public:
  BaseDataPredicatesFromKeyWords();
  BaseDataPredicatesFromKeyWords(const BaseDataPredicatesFromKeyWords& data);

  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataPredicatesFromKeyWordsClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataPredicatesFromKeyWordsClass : public DataAlgorithmOperationClass
{
public:
  DataPredicatesFromKeyWordsClass();
  DataPredicatesFromKeyWordsClass(const DataPredicatesFromKeyWordsClass& data);
  DataPredicatesFromKeyWordsClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};



#endif
