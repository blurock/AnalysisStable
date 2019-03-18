/*  FILE     DescriptionProbsType.hh
**  PACKAGE  DescriptionProbs
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "DescriptionProbs" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_DESCRIPTIONPROBSTYPE_HH
#define CoreObjects_DESCRIPTIONPROBSTYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
/*C BaseDataDescriptionMatrix  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the DescriptionMatrix class definitions
**
**  REMARKS
**    Inheirits BaseDataInstanceDoubleMatrix
*/
class BaseDataDescriptionMatrix : public BaseDataInstanceDoubleMatrix
{
public:
  BaseDataDescriptionMatrix();
  BaseDataDescriptionMatrix(const BaseDataDescriptionMatrix& data);
  BaseDataDescriptionMatrix(MatrixNumeric& mat,
			    BaseDataKeySet& insts,
			    BaseDataKeySet& attrs);
  BaseDataDescriptionMatrix(MatrixNumeric& mat,
			    BaseDataKeyWords& insts,
			    BaseDataKeyWords& attrs);

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataDescriptionMatrixClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataInstanceDoubleMatrixClass
*/
class DataDescriptionMatrixClass : public DataInstanceDoubleMatrixClass
{
public:
  DataDescriptionMatrixClass();
  DataDescriptionMatrixClass(const DataDescriptionMatrixClass& data);
  DataDescriptionMatrixClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataDetermineMembershipByTrying  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the DetermineMembershipByTrying class definitions
**
**  REMARKS
**    Inheirits BaseDataDescriptionMatrix
*/
class BaseDataDetermineMembershipByTrying : public BaseDataDescriptionMatrix
{
  MatrixNumeric GroupInstanceProbabilities;
  VectorNumeric NewInstanceDescrProbabilities;
  double newInstanceMembership;

  VectorNumeric *BelongsInGroupMeasure;
  double BelongsInExtraGroupMeasure;

  unsigned int numGroups;
  unsigned int numDescriptions;
  double totalNumberOfInstances;
  MatrixNumeric GroupDescrProbabilities;
  VectorNumeric *nodeInGroup;
  VectorNumeric *nodeNotInGroup;
  VectorNumeric *instanceCountOnGroup;
  VectorNumeric *descriptionOverAllGroups;
  VectorNumeric *totalDescriptionProbs;
  double totalDescriptionProbSquared;

  void ComputeTotalDescriptionProbs();
  void TotalDescriptionOverAllSons();
  void GroupInstanceCount();
  void TotalNumberOfInstances();
  void GroupMeasuresPreprocessing();
  void ComputeAsOnACluster();
  void ComputeAsExtraCluster();
public:
  BaseDataDetermineMembershipByTrying();
  BaseDataDetermineMembershipByTrying(const BaseDataDetermineMembershipByTrying& data);
  BaseDataDetermineMembershipByTrying(const BaseDataDescriptionMatrix& data);
  ~BaseDataDetermineMembershipByTrying();

  void setGroupProbabilities(MatrixNumeric&);
  void setNewInstance(VectorNumeric& newinstanceprobs, double membership);

  VectorNumeric *getBelongsInGroupMeasurePointer();
  double getBelongsInExtraGroupMeasure();
  int getBestGroup();

  void CalculateNewInstanceMembership();

  STANDARD_VIRTUAL_METHODS_OBJECT;
};
/*C DataDetermineMembershipByTryingClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataDescriptionMatrixClass
*/
class DataDetermineMembershipByTryingClass : public DataDescriptionMatrixClass
{
public:
  DataDetermineMembershipByTryingClass();
  DataDetermineMembershipByTryingClass(const DataDetermineMembershipByTryingClass& data);
  DataDetermineMembershipByTryingClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};


/*C BaseDataDescriptionMatrixSetUp  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the DescriptionMatrixSetUp class definitions
**
**  REMARKS
**    Inheirits BaseDataMatrixSetUp
*/
class BaseDataDescriptionMatrixSetUp : public BaseDataMatrixSetUp
{
  String descrObjectS;
public:
  BaseDataDescriptionMatrixSetUp();
  BaseDataDescriptionMatrixSetUp(const BaseDataDescriptionMatrixSetUp& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
    bool Calculate(BaseDataSetOfInstances* instances,
		   DataSetOfInstancesClass*instsclass,
		   BaseDataAlgorithmRun *,
		   DataAlgorithmRunClass*);

};
/*C DataDescriptionMatrixSetUpClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataMatrixSetUpClass
*/
class DataDescriptionMatrixSetUpClass : public DataMatrixSetUpClass
{
public:
  DataDescriptionMatrixSetUpClass();
  DataDescriptionMatrixSetUpClass(const DataDescriptionMatrixSetUpClass& data);
  DataDescriptionMatrixSetUpClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataCobwebBestGroup  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the CobwebBestGroup class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithm
*/
class BaseDataCobwebBestGroup : public BaseDataAlgorithmOperation
{
  String InstanceDescrProbsS;
  BaseDataDescriptionMatrix *InstanceDescrProbs;
  String GroupProbsS;
  BaseDataInstanceDoubleMatrix *GroupProbs;
  String SingleDescriptionS;
  BaseDataInstanceDoubleVector *SingleDescription;
  String SingleMembershipS;
  BaseDataReal *SingleMembership;
  BaseDataDetermineMembershipByTrying *Calc;

  String InGroupMeasureS;
  String ExtraGroupMeasureS;
public:
  BaseDataCobwebBestGroup();
  BaseDataCobwebBestGroup(const BaseDataCobwebBestGroup& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
};
/*C DataCobwebBestGroupClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmClass
*/
class DataCobwebBestGroupClass : public DataAlgorithmOperationClass
{
public:
  DataCobwebBestGroupClass();
  DataCobwebBestGroupClass(const DataCobwebBestGroupClass& data);
  DataCobwebBestGroupClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};



#endif
