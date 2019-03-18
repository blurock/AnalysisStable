/*  FILE     VerifyEnvironmentType.hh
**  PACKAGE  VerifyEnvironment
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "VerifyEnvironment" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_VERIFYENVIRONMENTTYPE_HH
#define CoreObjects_VERIFYENVIRONMENTTYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
/*C BaseDataVerifyErrorOperation  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the VerifyErrorOperation class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataVerifyErrorOperation : public BaseDataOperation
{
public:
  BaseDataVerifyErrorOperation();
  BaseDataVerifyErrorOperation(const BaseDataVerifyErrorOperation& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataVerifyErrorOperationClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataVerifyErrorOperationClass : public DataOperationClass
{
public:
  DataVerifyErrorOperationClass();
  DataVerifyErrorOperationClass(const DataVerifyErrorOperationClass& data);
  DataVerifyErrorOperationClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataVerifyOperation  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the VerifyOperation class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataVerifyOperation : public BaseDataOperation
{
  BaseDataVerifyErrorOperation *ErrorOperation;
  BaseDataLogicalOperation *CombineOperation;
  double IndividualCutoff;
  double TotalCutOff;
public:
  BaseDataVerifyOperation();
  BaseDataVerifyOperation(const BaseDataVerifyOperation& data);
 STANDARD_VIRTUAL_METHODS_OBJECT;
 STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataVerifyOperationClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataVerifyOperationClass : public DataOperationClass
{
  DataVerifyErrorOperationClass *ErrorOperationClass;
  DataLogicalOperationClass *CombineOperationClass;
public:
  DataVerifyOperationClass();
  DataVerifyOperationClass(const DataVerifyOperationClass& data);
  DataVerifyOperationClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS

  DataVerifyErrorOperationClass *getErrorOperationClass();
  DataLogicalOperationClass *getCombineOperationClass();
};
/*C BaseDataVerifyErrorAlgorithm  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the VerifyErrorAlgorithm class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataVerifyErrorAlgorithm : public BaseDataAlgorithmOperation
{
  String VerificationOperationS;
  BaseDataVerifyOperation *VerificationOperation;
  String LogicalDescriptionNamesS;
  BaseDataKeyWords *LogicalDescriptionNames;
  String InstanceNamesS;
  BaseDataKeyWords *InstanceNames;

  String ErrorInstanceNamesS;
  ObjectList<String> *ErrorInstanceNames;
public:
  BaseDataVerifyErrorAlgorithm();
  BaseDataVerifyErrorAlgorithm(const BaseDataVerifyErrorAlgorithm& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
};
/*C DataVerifyErrorAlgorithmClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataVerifyErrorAlgorithmClass : public DataAlgorithmOperationClass
{
public:
  DataVerifyErrorAlgorithmClass();
  DataVerifyErrorAlgorithmClass(const DataVerifyErrorAlgorithmClass& data);
  DataVerifyErrorAlgorithmClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

#endif
