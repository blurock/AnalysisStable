/*  FILE     GeneticOperationsType.hh
**  PACKAGE  GeneticOperations
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "GeneticOperations" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
#ifndef CoreObjects_GENETICOPERATIONSTYPE_HH
#define CoreObjects_GENETICOPERATIONSTYPE_HH

/*C BaseDataGeneticDistribution  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the GeneticDistribution class definitions
**
**  REMARKS
**    Inheirits BaseDataGeneticObject
*/
class BaseDataGeneticDistribution : public BaseDataGeneticObject
{
  String DistributionName;
  String ParameterName;
  BaseDataAttributeDistribution *Distribution;
public:
  BaseDataGeneticDistribution();
  BaseDataGeneticDistribution(const BaseDataGeneticDistribution& data);
  ~BaseDataGeneticDistribution();

  STANDARD_VIRTUAL_METHODS_OBJECT
  STANDARD_VIRTUAL_GENETIC_OBJECT_METHODS;
  double GenerateDoubleValueFromDistribution();
};
/*C DataGeneticDistributionClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataGeneticObjectClass
*/
class DataGeneticDistributionClass : public DataGeneticObjectClass
{
  DataAttributeDistributionClass *DistributionClass;
public:
  DataGeneticDistributionClass();
  DataGeneticDistributionClass(const DataGeneticDistributionClass& data);
  DataGeneticDistributionClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataGeneticStdDev  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the GeneticStdDev class definitions
**
**  REMARKS
**    Inheirits BaseDataGeneticObject
*/
class BaseDataGeneticStdDev : public BaseDataGeneticDistribution
{
public:
  BaseDataGeneticStdDev();
  BaseDataGeneticStdDev(const BaseDataGeneticStdDev& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataGeneticStdDevClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataGeneticObjectClass
*/
class DataGeneticStdDevClass : public DataGeneticDistributionClass
{
public:
  DataGeneticStdDevClass();
  DataGeneticStdDevClass(const DataGeneticStdDevClass& data);
  DataGeneticStdDevClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataGeneticInterval  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the GeneticInterval class definitions
**
**  REMARKS
**    Inheirits BaseDataGeneticObject
*/
class BaseDataGeneticInterval : public BaseDataGeneticDistribution
{
public:
  BaseDataGeneticInterval();
  BaseDataGeneticInterval(const BaseDataGeneticInterval& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataGeneticIntervalClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataGeneticObjectClass
*/
class DataGeneticIntervalClass : public DataGeneticDistributionClass
{
public:
  DataGeneticIntervalClass();
  DataGeneticIntervalClass(const DataGeneticIntervalClass& data);
  DataGeneticIntervalClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataGeneticConstant  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the GeneticConstant class definitions
**
**  REMARKS
**    Inheirits BaseDataGeneticObject
*/
class BaseDataGeneticConstant : public BaseDataGeneticObject
{
public:
  BaseDataGeneticConstant();
  BaseDataGeneticConstant(const BaseDataGeneticConstant& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataGeneticConstantClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataGeneticObjectClass
*/
class DataGeneticConstantClass : public DataGeneticObjectClass
{
  DataSetOfObjectsClass *GeneticObjectsClass;
public:
  DataGeneticConstantClass();
  DataGeneticConstantClass(const DataGeneticConstantClass& data);
  DataGeneticConstantClass(const int id, 
		    const String& name,
		    const String& descr);
  DataSetOfObjectsClass *getGeneticParametersClass();
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataGeneticSetOfParameters  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the GeneticSetOfParameters class definitions
**
**  REMARKS
**    Inheirits BaseDataGeneticObject
*/
class BaseDataGeneticSetOfParameters : public BaseDataGeneticObject
{
  BaseDataSetOfObjects *GeneticObjects;
public:
  BaseDataGeneticSetOfParameters();
  BaseDataGeneticSetOfParameters(const BaseDataGeneticSetOfParameters& data);
  ~BaseDataGeneticSetOfParameters();
  BaseDataGeneticObject *GetGeneticParameter(String& name);
  STANDARD_VIRTUAL_GENETIC_OBJECT_METHODS;
  STANDARD_VIRTUAL_METHODS_OBJECT;
};
/*C DataGeneticSetOfParametersClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataGeneticObjectClass
*/
class DataGeneticSetOfParametersClass : public DataGeneticObjectClass
{
  DataSetOfObjectsClass *GeneticObjectsClass;
public:
  DataGeneticSetOfParametersClass();
  DataGeneticSetOfParametersClass(const DataGeneticSetOfParametersClass& data);
  DataGeneticSetOfParametersClass(const int id, 
		    const String& name,
		    const String& descr);
  DataSetOfObjectsClass *PointerToAllowedClasses();
  DataGeneticObjectClass *GetGeneticClass(unsigned int type);
  STANDARD_VIRTUAL_METHODS_CLASS;
};
    

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
