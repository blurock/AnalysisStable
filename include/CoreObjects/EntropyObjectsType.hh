/*  FILE     EntropyObjectsType.hh
**  PACKAGE  EntropyObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "EntropyObjects" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_ENTROPYOBJECTSTYPE_HH
#define CoreObjects_ENTROPYOBJECTSTYPE_HH

 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
class DataEntropySelectPredicateClass;
class DataEntropyAlgorithmClass;

/*C BaseDataEntropyAlgorithm  . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the EntropyAlgorithm class
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataEntropyAlgorithm : public BaseDataAlgorithmOperation
{
  String entropyParametersS;
  BaseDataKeyWords* entropyParameters;
  String instanceListS;
  BaseDataKeyWords* instanceList;
  String tableS;
  BaseDataPartitionTable *table;
  String conjunctionS;
  BaseDataConjunction *conj;
  String logicDescriptionsS;
  BaseDataSetOfLogicDescriptions* logicDescriptions;
  
  String OutputMatS;
  MatrixNumeric *GainMat;
  String OutputGainS;
  double GainValue;
  
  DataConjunctionClass *conjclass;
  
public:
  BaseDataEntropyAlgorithm();
  BaseDataEntropyAlgorithm(const BaseDataEntropyAlgorithm& data);

  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataEntropyAlgorithmClass . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataEntropyAlgorithmClass : public DataAlgorithmOperationClass
{
public:
  DataEntropyAlgorithmClass();
  DataEntropyAlgorithmClass(const DataEntropyAlgorithmClass& data);
  DataEntropyAlgorithmClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

 

/*C BaseDataEntropySelectPredicate  . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the EntropySelectPredicate class definitions
**
**    The parameters that are used are:
**    SELECTION_DESCRIPTORS (SetOfDescriptors): The list of partitions as descriptors
**    SELECTION_GOAL        (EntropyGoal): The goal partition
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataEntropySelectPredicate : public BaseDataAlgorithmOperation
{
  String AlgorithmEntropyS;
  BaseDataAlgorithmOperation *AlgorithmEntropy;

  String InputGoalS;
  BaseDataKeyWords *keys;
  String InputDescriptorsS;
  BaseDataKeyWords *descriptors;
  

  String OutputTopPredicateS;
  BaseDataKeyWords *toppredicates;
  String OutputPartitionTable;
  BaseDataKeyWords *partitiontable;

  String top;
  String goalname;
  
  String entropygain;
  String parmS;
  String partitionS;
  String goalS;
  String descrS;
  String conjS;
  
public:
  BaseDataEntropySelectPredicate();
  BaseDataEntropySelectPredicate(const BaseDataEntropySelectPredicate& data);

  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
  STANDARD_VIRTUAL_METHODS_OBJECT;
  void SetEntropyAlgorithm(BaseDataAlgorithmOperation *);
};
/*C DataEntropySelectPredicateClass . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataEntropySelectPredicateClass : public DataAlgorithmOperationClass
{
public:
  DataEntropySelectPredicateClass();
  DataEntropySelectPredicateClass(const DataEntropySelectPredicateClass& data);
  DataEntropySelectPredicateClass(const int id, 
		    const String& name,
		    const String& descr);

  STANDARD_VIRTUAL_METHODS_CLASS
};


/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif




