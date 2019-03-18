/*  FILE     DistributionAlgorithmType.hh
**  PACKAGE  DistributionAlgorithm
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "DistributionAlgorithm" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_DISTRIBUTIONALGORITHMTYPE_HH
#define CoreObjects_DISTRIBUTIONALGORITHMTYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
/*C BaseDataAttributeDistribution  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the AttributeDistribution class definitions
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataAttributeDistribution : public BaseDataObject
{
  PrimitiveStats *Distribution;
public:
  BaseDataAttributeDistribution();
  BaseDataAttributeDistribution(const BaseDataAttributeDistribution& data);
  BaseDataAttributeDistribution(VectorNumeric& vec);
  ~BaseDataAttributeDistribution();

  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
  PrimitiveStats *getStatistics();
};
/*C DataAttributeDistributionClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataAttributeDistributionClass : public DataObjectClass
{
public:
  DataAttributeDistributionClass();
  DataAttributeDistributionClass(const DataAttributeDistributionClass& data);
  DataAttributeDistributionClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataDistributionAlgorithm  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the DistributionAlgorithm class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataDistributionAlgorithm : public BaseDataAlgorithmOperation
{
  String imatrixS;
  BaseDataInstanceDoubleMatrix *imatrix;
  String rootnameS;
  String rootname;

  String distributionNamesS;
  BaseDataKeyWords *distributionNames;
  
public:
  BaseDataDistributionAlgorithm();
  BaseDataDistributionAlgorithm(const BaseDataDistributionAlgorithm& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
};
/*C DataDistributionAlgorithmClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataDistributionAlgorithmClass : public DataAlgorithmOperationClass
{
public:
  DataDistributionAlgorithmClass();
  DataDistributionAlgorithmClass(const DataDistributionAlgorithmClass& data);
  DataDistributionAlgorithmClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataNormalizeOperation  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the NormalizeOperation class definitions
**
**  REMARKS
**    Inheirits BaseDataParameterizedFunction
*/
class BaseDataNormalizeOperation : public BaseDataParameterizedFunction
{
public:
  BaseDataNormalizeOperation();
  BaseDataNormalizeOperation(const BaseDataNormalizeOperation& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
  STANDARD_VIRTUAL_OPERATION_METHODS;
};
/*C DataNormalizeOperationClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataParameterizedFunctionClass
*/
class DataNormalizeOperationClass : public DataParameterizedFunctionClass
{
public:
  DataNormalizeOperationClass();
  DataNormalizeOperationClass(const DataNormalizeOperationClass& data);
  DataNormalizeOperationClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataSimpleNormalizeOperation  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the SimpleNormalizeOperation class definitions
**
**  REMARKS
**    Inheirits BaseDataNormalizeOperation
*/
class BaseDataSimpleNormalizeOperation : public BaseDataNormalizeOperation
{
public:
  BaseDataSimpleNormalizeOperation();
  BaseDataSimpleNormalizeOperation(const BaseDataSimpleNormalizeOperation& data);
  STANDARD_VIRTUAL_METHODS_OBJECT;
  bool InsertParameterSet();
};
/*C DataSimpleNormalizeOperationClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataNormalizeOperationClass
*/
class DataSimpleNormalizeOperationClass : public DataNormalizeOperationClass
{
public:
  DataSimpleNormalizeOperationClass();
  DataSimpleNormalizeOperationClass(const DataSimpleNormalizeOperationClass& data);
  DataSimpleNormalizeOperationClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
};
/*C BaseDataSimpleNormalize  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the SimpleNormalize class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataSimpleNormalize : public BaseDataOperation
{
  BaseDataNumeric *OffSet;
  BaseDataNumeric *Scale;
public:
  BaseDataSimpleNormalize();
  BaseDataSimpleNormalize(const BaseDataSimpleNormalize& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
  STANDARD_VIRTUAL_OPERATION_METHODS;
  BaseDataObject *CalculateSimpleNormalization(BaseDataObject *x);

  BaseDataNumeric *getOffSet();
  BaseDataNumeric *getScale();
  void setOffSet(BaseDataNumeric *offset);
  void setScale(BaseDataNumeric *scale);
  
};
/*C DataSimpleNormalizeClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataSimpleNormalizeClass : public DataOperationClass
{
  DataNumericClass *OffSetClass;
  DataNumericClass *ScaleClass;
public:
  DataSimpleNormalizeClass();
  DataSimpleNormalizeClass(const DataSimpleNormalizeClass& data);
  DataSimpleNormalizeClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
  DataNumericClass *getOffSetClass();
  DataNumericClass *getScaleClass();
  void setOffSetClass(DataNumericClass *offsetcls);
  void setScaleClass(DataNumericClass *scalecls);
};
/*C BaseDataNormalizeOpFromDistribution  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the NormalizeOpFromDistribution class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataNormalizeOpFromDistribution : public BaseDataAlgorithmOperation
{
  String DistributionListS;
  BaseDataKeyWords * DistributionList;
  String RootNameS;
  BaseDataString *RootName;
  String OperationClassS;
  DataNormalizeOperationClass *ParameterizedOperationClass;
  String ExpressionTreeClassS;
  BaseDataString *ExpressionTreeClass;
  DataExpressionTreeClass *Expressions;

  DataSimpleNormalizeClass *NormOpClass;
  DataParameterSetClass *ParamsClass;
  String OpListS;
  BaseDataKeyWords *OpList;

public:
  BaseDataNormalizeOpFromDistribution();
  BaseDataNormalizeOpFromDistribution(const BaseDataNormalizeOpFromDistribution& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
  bool NoDeviationCheck(PrimitiveStats *stats);
  double SetOffSetFactor(PrimitiveStats *stats,BaseDataAlgorithmRun *run);
  double SetScaleFactor(PrimitiveStats *stats,BaseDataAlgorithmRun *run);

};
/*C DataNormalizeOpFromDistributionClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataNormalizeOpFromDistributionClass : public DataAlgorithmOperationClass
{
public:
  DataNormalizeOpFromDistributionClass();
  DataNormalizeOpFromDistributionClass(const DataNormalizeOpFromDistributionClass& data);
  DataNormalizeOpFromDistributionClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

#endif
