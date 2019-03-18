/*  FILE     InstancePCAType.hh
**  PACKAGE  InstancePCA
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "InstancePCA" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_INSTANCEPCATYPE_HH
#define CoreObjects_INSTANCEPCATYPE_HH

/*C BaseDataInstancePCAObject  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the InstancePCAObject class definitions
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataInstancePCAObject : public BaseDataObject
{
  BaseDataKeyWords VariableNames;
  MatrixNumeric Transformation;
  VectorNumeric EigenValues;
  
public:
  BaseDataInstancePCAObject();
  BaseDataInstancePCAObject(const BaseDataInstancePCAObject& data);
  BaseDataInstancePCAObject(const BaseDataKeyWords& names,
			    const MatrixNumeric& trans,
			    const VectorNumeric& eigen);
  ObjectList<String>& getVariableNames();
  double getEigenValue(unsigned int i);
  VectorNumeric& getEigenValues();
  MatrixNumeric transformCoordinates(MatrixNumeric& coords);
  
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);

};
/*C DataInstancePCAObjectClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataInstancePCAObjectClass : public DataObjectClass
{
public:
  DataInstancePCAObjectClass();
  DataInstancePCAObjectClass(const DataInstancePCAObjectClass& data);
  DataInstancePCAObjectClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
};
/*C BaseDataInstancePCA  . . . . . . . . . . . . . . .. . . . . . . .  data
**
**  DESCRIPTION
**    This is the InstancePCA class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataInstancePCA : public BaseDataAlgorithmOperation
{
  String imatrixS;
  BaseDataInstanceDoubleMatrix *imatrix;
  String pcaRootsS;
  BaseDataKeyWords *pcaRoots;
  
  String distributionRoot;
  String pcaObjectName;

  BaseDataInstancePCAObject *pcaObject;
  
  bool NormalizePCAInput(MatrixNumeric& mat,
			 BaseDataKeyWords& parameterkeys,
			 BaseDataSetOfInstances *instances);
public:
  BaseDataInstancePCA();
  BaseDataInstancePCA(const BaseDataInstancePCA& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
};
/*C DataInstancePCAClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataInstancePCAClass : public DataAlgorithmOperationClass
{
public:
  DataInstancePCAClass();
  DataInstancePCAClass(const DataInstancePCAClass& data);
  DataInstancePCAClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataPCAParameterGenerate  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the PCAParameterGenerate class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataPCAParameterGenerate : public BaseDataAlgorithmOperation
{
  String pcaS;
  String pcaObjectS;
  BaseDataInstancePCAObject *pcaObject;
  String rootnameS;
  String rootname;
  String instnamesS;
  String distributionname;
  BaseDataKeyWords *instnames;
  
public:
  BaseDataPCAParameterGenerate();
  BaseDataPCAParameterGenerate(const BaseDataPCAParameterGenerate& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
};
/*C DataPCAParameterGenerateClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataPCAParameterGenerateClass : public DataAlgorithmOperationClass
{
public:
  DataPCAParameterGenerateClass();
  DataPCAParameterGenerateClass(const DataPCAParameterGenerateClass& data);
  DataPCAParameterGenerateClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};


/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
