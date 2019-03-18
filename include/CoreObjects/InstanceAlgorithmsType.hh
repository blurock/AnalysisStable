/*  FILE     InstanceAlgorithmsType.hh
**  PACKAGE  InstanceAlgorithms
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "InstanceAlgorithms" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_INSTANCEALGORITHMSTYPE_HH
#define CoreObjects_INSTANCEALGORITHMSTYPE_HH

 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
class DataInstanceSetUpClass;
class DataAttributeSetUpClass;
class DataMatrixSetUpClass;
class DataInstanceASCIIReadClass;
class DataReadMatrixClass;
class DataMatrixToInstancesClass;

/*C BaseDataAttributeSetUp  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the AttributeSetUp class definitions with the following 
**    virtual functions:
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataAttributeSetUp : public BaseDataAlgorithmOperation
{
  String instanceNameListS;
  BaseDataKeyWords *instanceNameList;
  String attributeSpecsS;
  BaseDataKeyWords *attributeSpecs;
  
  String byTypeS;
  bool byType;
  String byNameS;
  bool byName;
  String allValuesS;
  bool allValues;
  
  String attributeNamesS;
  BaseDataKeyWords *attributeNames;
  String allAttributeNamesS;
  BaseDataKeyWords *allAttributeNames;

public:
  BaseDataAttributeSetUp();
  BaseDataAttributeSetUp(const BaseDataAttributeSetUp& data);

  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataAttributeSetUpClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**    This is the base function about a data type:
**       Identification: The numerical value of the type
**       NameTag: The ASCII name of the type
**       Description: The text description of the class
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataAttributeSetUpClass : public DataAlgorithmOperationClass
{
public:
  DataAttributeSetUpClass();
  DataAttributeSetUpClass(const DataAttributeSetUpClass& data);
  DataAttributeSetUpClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
};
/*C BaseDataInstanceSetUp  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the InstanceSetUp class definitions with the following 
**    virtual functions:
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataInstanceSetUp : public BaseDataAlgorithmOperation
{
  String instanceNameListS;
  BaseDataKeyWords *instanceNameList;
  String testPercentageS;
  BaseDataNumeric *testPercentage;

  String totalInstanceNameListS;
  BaseDataKeyWords *totalInstanceNameList;
  String testInstanceNameListS;
  BaseDataKeyWords *testInstanceNameList;
  String trainInstanceNameListS;
  BaseDataKeyWords *trainInstanceNameList;

public:
  BaseDataInstanceSetUp();
  BaseDataInstanceSetUp(const BaseDataInstanceSetUp& data);
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataInstanceSetUpClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**    This is the base function about a data type:
**       Identification: The numerical value of the type
**       NameTag: The ASCII name of the type
**       Description: The text description of the class
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataInstanceSetUpClass : public DataAlgorithmOperationClass
{
public:
  DataInstanceSetUpClass();
  DataInstanceSetUpClass(const DataInstanceSetUpClass& data);
  DataInstanceSetUpClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
};
/*C BaseDataMatrixSetUp  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the MatrixSetUp class definitions with the following 
**    virtual functions:
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataMatrixSetUp : public BaseDataAlgorithmOperation
{
  String totalInstanceNameListS;
  String attributeNamesS;
  String matrixObjectS;
  String rootNameS;
  
public:
  BaseDataKeyWords *totalInstanceNameList;
  BaseDataKeyWords *attributeNames;
  BaseDataInstanceDoubleMatrix *matrixObject;

  BaseDataMatrixSetUp();
  BaseDataMatrixSetUp(const BaseDataMatrixSetUp& data);
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataMatrixSetUpClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**    This is the base function about a data type:
**       Identification: The numerical value of the type
**       NameTag: The ASCII name of the type
**       Description: The text description of the class
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataMatrixSetUpClass : public DataAlgorithmOperationClass
{
public:
  DataMatrixSetUpClass();
  DataMatrixSetUpClass(const DataMatrixSetUpClass& data);
  DataMatrixSetUpClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
};
/*C BaseDataInstanceASCIIRead  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the InstanceASCIIRead class definitions with the following 
**    virtual functions:
**    - Read(stream,objc): Read from ASCII stream (using objc for additional format info)
**    - Read(stream,objc,name): Read from ASCII stream (if the name of the object already known)
**    - Write(stream,objc): Write with formatting details
**    - Clone(),CopyClone(obj): Clone a copy
**    - EncodeThis(buffer),DecodeThis(buffer): Encode and Decode routines
**    - print(out): Standard default output routine
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataInstanceASCIIRead : public BaseDataAlgorithmOperation
{
  String instanceReadFilesS;
  BaseDataKeyWords *instanceReadFiles;
  
public:
  BaseDataInstanceASCIIRead();
  BaseDataInstanceASCIIRead(const BaseDataInstanceASCIIRead& data);
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataInstanceASCIIReadClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**    This is the base function about a data type:
**       Identification: The numerical value of the type
**       NameTag: The ASCII name of the type
**       Description: The text description of the class
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataInstanceASCIIReadClass : public DataAlgorithmOperationClass
{
public:
  DataInstanceASCIIReadClass();
  DataInstanceASCIIReadClass(const DataInstanceASCIIReadClass& data);
  DataInstanceASCIIReadClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
};
/*C BaseDataInstancesFromPredicate  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the InstancesFromPredicate class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataInstancesFromPredicate : public BaseDataAlgorithmOperation
{
  String instanceNameListS;
  BaseDataKeyWords *instanceNameList;
  String predicateListS;
  BaseDataKeyWords *predicateList;
public:
  BaseDataInstancesFromPredicate();
  BaseDataInstancesFromPredicate(const BaseDataInstancesFromPredicate& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS
};
/*C DataInstancesFromPredicateClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataInstancesFromPredicateClass : public DataAlgorithmOperationClass
{
public:
  DataInstancesFromPredicateClass();
  DataInstancesFromPredicateClass(const DataInstancesFromPredicateClass& data);
  DataInstancesFromPredicateClass(const int id, 
		    const String& name,

		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataMatrixGraphOutput  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the MatrixGraphOutput class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataMatrixGraphOutput : public BaseDataAlgorithmOperation
{
  String MatrixObjectS;
  BaseDataInstanceDoubleMatrix *MatrixObject;
  String RootNameS;
  BaseDataString *RootName;
  String XcoordS;
  BaseDataString *Xcoord;
  String YcoordsS;
  BaseDataKeyWords *Ycoords;

  String rootName;
  String xParameter;

  ObjectList<String> yParameters;
  MatrixNumeric *outMatrix;

public:
  BaseDataMatrixGraphOutput();
  BaseDataMatrixGraphOutput(const BaseDataMatrixGraphOutput& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS
};
/*C DataMatrixGraphOutputClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataMatrixGraphOutputClass : public DataAlgorithmOperationClass
{
public:
  DataMatrixGraphOutputClass();
  DataMatrixGraphOutputClass(const DataMatrixGraphOutputClass& data);
  DataMatrixGraphOutputClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataReadMatrix  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ReadMatrix class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataReadMatrix : public BaseDataAlgorithmOperation
{
  String matrixReadClassParameterS;
  String indexPrefixParameterS;
  String fileNameParameterS;
  String matrixNameParameterS;

 BaseDataProgressVariableMatrix    *Matrix;
  DataProgressVariableMatrixClass   *MatrixClass;
  String fileNameS;
  String matrixNameS;
  String indexPrefixS;

public:
  BaseDataReadMatrix();
  BaseDataReadMatrix(const BaseDataReadMatrix& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS
};
/*C DataReadMatrixClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataReadMatrixClass : public DataAlgorithmOperationClass
{
public:
  DataReadMatrixClass();
  DataReadMatrixClass(const DataReadMatrixClass& data);
  DataReadMatrixClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataMatrixToInstances  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the MatrixToInstances class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataMatrixToInstances : public BaseDataAlgorithmOperation
{
  String matrixNameParameterS;
  String realTypeParameterS;

  String matrixNameS;
  DataRealClass *realType;
public:
  BaseDataMatrixToInstances();
  BaseDataMatrixToInstances(const BaseDataMatrixToInstances& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS
};
/*C DataMatrixToInstancesClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataMatrixToInstancesClass : public DataAlgorithmOperationClass
{
public:
  DataMatrixToInstancesClass();
  DataMatrixToInstancesClass(const DataMatrixToInstancesClass& data);
  DataMatrixToInstancesClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};




/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
