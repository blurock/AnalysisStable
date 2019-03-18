/*  FILE     InstancePCA.cc
**  PACKAGE  InstancePCA
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "InstancePCA" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjects.hh"
#include "Vector.hh"
#include "PrimitiveStats.hh"
#include "MatrixNumeric.hh"
#include "BasicLaTeXTable.hh"
#include "MatrixOut.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "ExpressionTree.hh"
#include "MatrixUtilities.hh"
#include "BasicLaTeXTable.hh"
#include "EigenValuesOut.hh"
#include "EigenValues.hh"
#include "PCAAnalysis.hh"
#include "InstancePCA.hh"
#include "DistributionAlgorithm.hh"

/*S BaseDataInstancePCAObject
 */ 
/*F BaseDataInstancePCAObject() . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataInstancePCAObject::BaseDataInstancePCAObject()
{
  Identification = PCAINSTANCE_OBJECT_ID;
  NameTag = PCAINSTANCE_OBJECT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataInstancePCAObject(data) . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataInstancePCAObject::BaseDataInstancePCAObject(const BaseDataKeyWords& names,
						     const MatrixNumeric& trans,
						     const VectorNumeric& eigen)
  : VariableNames(names),
    Transformation(trans),
    EigenValues(eigen)
{
  Identification = PCAINSTANCE_OBJECT_ID;
  NameTag = PCAINSTANCE_OBJECT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;  
}
/*F BaseDataInstancePCAObject(data) . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataInstancePCAObject::BaseDataInstancePCAObject(const BaseDataInstancePCAObject& data)
  : BaseDataObject(data),
    VariableNames(data.VariableNames),
    Transformation(data.Transformation),
    EigenValues(data.EigenValues)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . Read in BaseDataInstancePCAObject
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataInstancePCAObject::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . Read in BaseDataInstancePCAObject
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataInstancePCAObject::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);
  result = result && VariableNames.Read(in,objc,name);
  result = result && Transformation.Read(in);
  result = result && EigenValues.Read(in);
  
  return result;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . BaseDataInstancePCAObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool BaseDataInstancePCAObject::WriteAsLine(ostream& out, DataObjectClass *objc)
{
  BaseDataObject::WriteAsLine(out,objc);
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . . . . .  BaseDataInstancePCAObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool BaseDataInstancePCAObject::WriteAsASCII(ostream& in, DataObjectClass*objc)
{
  bool result = BaseDataObject::WriteAsASCII(in,objc);
  result = result && VariableNames.WriteAsASCII(in,objc);
  //result = result && Transformation.WriteAsASCII(in);
  result = result && EigenValues.WriteAsASCII(in);
  return result;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . . . . . .  BaseDataObject
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool BaseDataInstancePCAObject::WriteAsLatex(ostream& out, DataObjectClass*)
{
  out << endl;
  out << " %%% ================ Principle Component Analysis ================= ";
  out << endl;
  
  unsigned int vars;
  BaseDataKeyWords keys = VariableNames;
  
  ObjectList<String> names = keys.GetKeyWords();
  out << "\\begin{table}" << endl;
  out << "\\begin{tabular}";

  out << "{ l";
  for(unsigned int v=0;v<EigenValues.size();v++)
    {
      out << " | l";
    }
  out << "}\\hline" << endl;

  out << " Eigenvalue   ";
  double total = 0.0;
  for(unsigned int vv=0;vv<EigenValues.size();vv++)
      total += EigenValues[vv];
  double sum = 0.0;
  for(unsigned int vvv=0;vvv<EigenValues.size();vvv++)
    {
      sum += EigenValues[vvv];
      out  << "& ";
      out << setw(10) << setprecision(3) << 100*sum/total;
    }
  out << "\\\\\\hline" << endl;
  
  ObjectList<String>::iterator name = names.begin();
  MatrixNumeric mat = Transformation;
  for(vars = 0; vars < names.size(); vars++)
    {
      VectorNumeric coefs = mat.getMatrixColumn(vars);
      
      out << setw(20) << *name;
      for(unsigned int c=0;c<coefs.size();c++)
	{
	  out  << "& ";
	  out << setw(10) << setprecision(4) << coefs[c];
	}
      out << "\\\\\\hline" << endl;
      name++;
    }
  out << "\\end{tabular}" << endl;
  out << "\\end{table}" << endl;
  out << endl;

  return true;
  
}

/*F out1 = print(out) . . . . . . . . . . . . . . . BaseDataInstancePCAObject
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataInstancePCAObject::print(ostream& out) const
{
  BaseDataObject::print(out);
  out << endl;
  out << " ================ Principle Component Analysis ================= ";
  out << endl;
  
  unsigned int vars;
  BaseDataKeyWords keys = VariableNames;
  
  ObjectList<String> names = keys.GetKeyWords();
  double total = 0.0;
  for(unsigned int v1=0;v1<EigenValues.size();v1++)
    total += EigenValues[v1];

  out << " Vars  /   Eigenvalue   ";
  double percent = 0.0;
  for(unsigned int v=0;v<EigenValues.size();v++)
    {
      percent += 100.0*EigenValues[v]/total;
      out << setw(15) << setprecision(5) << percent;
    }
  out << endl;
  
  ObjectList<String>::iterator name = names.begin();
  MatrixNumeric mat = Transformation;
  for(vars = 0; vars < names.size(); vars++)
    {
      VectorNumeric coefs = mat.getMatrixColumn(vars);
      
      out << setw(20) << *name;
      out << " : ";
      for(unsigned int c=0;c<coefs.size();c++)
	out << setw(15) << setprecision(7) << coefs[c];
      out << endl;
      name++;
    }
  out << " ================ Principle Component Analysis ================= ";
  out << endl;

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . BaseDataInstancePCAObject
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataInstancePCAObject::Clone()
{
  BaseDataInstancePCAObject *obj = new BaseDataInstancePCAObject;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . BaseDataInstancePCAObject
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataInstancePCAObject::CopyClone(Identify * obj)
{
  BaseDataInstancePCAObject *objfull = (BaseDataInstancePCAObject *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . BaseDataInstancePCAObject
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInstancePCAObject::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && VariableNames.EncodeThis(buffer);
  result = result && Transformation.EncodeThis(buffer);
  result = result && EigenValues.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . BaseDataInstancePCAObject
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInstancePCAObject::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::DecodeThis(buffer);
  if(result)
    cout << "Success ";
  else
    cout << "Nope ";
  
  result = result && VariableNames.DecodeThis(buffer);
  result = result && Transformation.DecodeThis(buffer);
  result = result && EigenValues.DecodeThis(buffer);
  return result;
}
 
/*F names = getVariableNames() get list of names
**
**  DESCRIPTION
**    names: The list of variables used for the PCA analysis
**
**  REMARKS
**
*/
ObjectList<String>& BaseDataInstancePCAObject::getVariableNames()
{
  return VariableNames.GetKeyWords();
}
 
/*F eigenvalue = getEigenValues(i)  . . . . . . . . .  get the ith eigenvalue
**
**  DESCRIPTION
**    i: which eigenvalue to retrieve
**    eigenvalue: The ith eigenvalue
**
**  REMARKS
**
*/
double BaseDataInstancePCAObject::getEigenValue(unsigned int i)
{
  return EigenValues[i];
}
 
/*F vec = getEigenValues()  . . . . . . . . . . . . get vector of eigenvalues
**
**  DESCRIPTION
**    vec: The vector of eigenvalues
**
**  REMARKS
**
*/
VectorNumeric& BaseDataInstancePCAObject::getEigenValues()
{
  return EigenValues;
}
 
/*F transformed = transformCoordinates(coords)  . . . . . . . PCA coordinates
**
**  DESCRIPTION
**    coords: A set of a set of coordinates 
**    transformed: The transformed set
**
**  REMARKS
**
*/
MatrixNumeric BaseDataInstancePCAObject::transformCoordinates(MatrixNumeric& coords)
{
  return Transformation * coords;
}

/*S DataInstancePCAObjectClass
 */
/*F DataInstancePCAObjectClass()  . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataInstancePCAObjectClass::DataInstancePCAObjectClass()
{
  Identification = PCAINSTANCE_OBJECT_ID;
  NameTag = PCAINSTANCE_OBJECT_NAME;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataInstancePCAObjectClass(data)  . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataInstancePCAObjectClass::DataInstancePCAObjectClass(const DataInstancePCAObjectClass& data)
  : DataObjectClass(data)
{
} 
 
/*F DataInstancePCAObjectClass(id,name,descr) . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataInstancePCAObjectClass::DataInstancePCAObjectClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataObjectClass(id,name,descr)
{
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = PCAINSTANCE_OBJECT_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . .  DataInstancePCAObjectClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataInstancePCAObjectClass::print(ostream& out) const
{
  DataObjectClass::print(out);
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . .  DataInstancePCAObjectClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataInstancePCAObjectClass, there is no further information.
**
**  REMARKS
**
*/
bool DataInstancePCAObjectClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataObjectClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . .  DataInstancePCAObjectClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataInstancePCAObjectClass::CopyClone(Identify *  objc)
{
  DataInstancePCAObjectClass *objcfull = (DataInstancePCAObjectClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . .  DataInstancePCAObjectClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataInstancePCAObjectClass::Clone()
    {
      DataInstancePCAObjectClass* id = new DataInstancePCAObjectClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . .  DataInstancePCAObjectClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataInstancePCAObjectClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . .  DataInstancePCAObjectClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataInstancePCAObjectClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);
//  result = result && Decode(buffer,-----);

  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataInstancePCAObjectClass::BaseDataObjectExample()
{ 
  //cout << "Make InstancePCAObject Example\n";
  return (BaseDataObject *) new BaseDataInstancePCAObject();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . .  DataInstancePCAObjectClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataInstancePCAObjectClass*& obj)
     {
     obj = new DataInstancePCAObjectClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . BaseDataInstancePCAObject
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataInstancePCAObject*& obj)
     {
     obj = new BaseDataInstancePCAObject;
     return obj->DecodeThis(buffer);
     }
/*S BaseDataInstancePCA
 */ 
/*F BaseDataInstancePCA() . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataInstancePCA::BaseDataInstancePCA()
  : imatrixS("MatrixObject"),
    pcaRootsS("PCANames")
{
  Identification = PCAINSTANCE_PCA_ID;
  NameTag = PCAINSTANCE_PCA_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataInstancePCA(data) . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataInstancePCA::BaseDataInstancePCA(const BaseDataInstancePCA& data)
  : BaseDataAlgorithmOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . Read in BaseDataInstancePCA
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataInstancePCA::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . Read in BaseDataInstancePCA
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataInstancePCA::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);

  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . BaseDataInstancePCA
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataInstancePCA::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . BaseDataInstancePCA
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataInstancePCA::Clone()
{
  BaseDataInstancePCA *obj = new BaseDataInstancePCA;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . BaseDataInstancePCA
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataInstancePCA::CopyClone(Identify * obj)
{
  BaseDataInstancePCA *objfull = (BaseDataInstancePCA *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . BaseDataInstancePCA
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInstancePCA::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  //result = result && ---.EncodeThis(buffer);
  //result = result && Encode(buffer,---);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . BaseDataInstancePCA
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataInstancePCA::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  // The rest

  return result;
}
/*F ans = SetUpAlgorithms(instances,instancesclass,run,runclass)  . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataInstancePCA::SetUpAlgorithms(BaseDataSetOfInstances*,
						      DataSetOfInstancesClass*,
						      BaseDataAlgorithmRun* ,
						      DataAlgorithmRunClass*)
{
  return true;
}
/*F ans = CheckInput(instances,instancesclass,run,runclass) . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**
**  REMARKS
**
*/
bool BaseDataInstancePCA::CheckInput(BaseDataSetOfInstances*,
						 DataSetOfInstancesClass*,
						 BaseDataAlgorithmRun* run,
						 DataAlgorithmRunClass*)
{
  bool result = true;

  if(run->ParameterInList(imatrixS))
    {
      if(!run->ParameterInList(pcaRootsS))
	{
	  cerr << "Parameter not found '" << pcaRootsS << "'" << endl;
	  result = false;
	}
    }
  else
    {
      cerr << "The parameter '" << imatrixS << "' was not in the list of parameters";
      result = false;
    }

  return result;
}
/*F ans = SetUpInput(instances,instancesclass,run,runclass) . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataInstancePCA::SetUpInput(BaseDataSetOfInstances*,
						 DataSetOfInstancesClass*,
						 BaseDataAlgorithmRun* run,
						 DataAlgorithmRunClass*)
{
  bool result = true;
  imatrix = (BaseDataInstanceDoubleMatrix *) run->ParameterValue(imatrixS);
  pcaRoots = (BaseDataKeyWords *) run->ParameterValue(pcaRootsS);
  ObjectList<String> pcaRootNames = pcaRoots->GetKeyWords();
  if(pcaRootNames.size() == 3)
    {
      pcaObjectName = pcaRootNames.front();
      pcaRootNames.pop_front();
      distributionRoot = pcaRootNames.front();
      pcaRootNames.pop_front();
    }
  else
    {
      cerr << "Expected: PCA object name and distribution name (only) for '" << pcaRootsS << endl;
      cerr << "Got: ";
      pcaRootNames.print(cerr);
      cerr << endl;
      result = false;
    }
  
  return result;
}
/*F ans = Calculate(instances,instancesclass,run,runclass)  . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataInstancePCA::Calculate(BaseDataSetOfInstances* instances,
				    DataSetOfInstancesClass*,
				    BaseDataAlgorithmRun* run,
				    DataAlgorithmRunClass*)
{
  bool result = true;

  MatrixNumeric mat = imatrix->CurrentMatrix().transpose();

  if(run->AlgorithmSummary.KeyWordInList("Normalize"))
     {
       BaseDataKeyWords parameterskeys = imatrix->getParameterNames();
       NormalizePCAInput(mat,parameterskeys,instances);
     }
  MatrixUtilities mutil(mat);
  PCAAnalysis *pca = new PCAAnalysis(mutil,false,false);

  pcaObject = new BaseDataInstancePCAObject(imatrix->getParameterNames(),
					    pca->getEigenVectors(),
					    pca->getEigenValues());
  delete pca;
  
  pcaObject->NameTag = pcaObjectName;
  pcaObject->print(cout);
  
  return result;
}
/*F ans = WriteOutputValues(instances,instancesclass,run,runclass)  algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataInstancePCA::WriteOutputValues(BaseDataSetOfInstances *instances,
					    DataSetOfInstancesClass*,
					    BaseDataAlgorithmRun* run,
					    DataAlgorithmRunClass*)
{
  bool result = true;
  
  instances->AddObject(pcaObject);

  return result;
}
/*F ans = ConcludeRun(instances,instancesclass,run,runclass)  . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataInstancePCA::ConcludeRun(BaseDataSetOfInstances*,
						  DataSetOfInstancesClass*,
						  BaseDataAlgorithmRun*,
						  DataAlgorithmRunClass*)
{
  bool result = true;
//  delete something
  return result;
}
 
 
/*F NormalizePCAInput(mat,parameterkeys,instances)
**
**  DESCRIPTION
**    mat: The matrix to normalize
**    parameterkeys: The list of parameters in the matrix
**    instances: The list of instances
**
**    This normalizes the input matrix according to the 
**    distributon information retrieved from the instances
**
**  REMARKS
**
*/
bool BaseDataInstancePCA::NormalizePCAInput(MatrixNumeric& mat,
					    BaseDataKeyWords& parameterskeys,
					    BaseDataSetOfInstances *instances)
  {
    cout << "Normalizing PCA Matrix" << endl;
    bool result = true;
    unsigned int dim1 = mat[0].size();
    ObjectList<String> parameternames = parameterskeys.GetKeyWords();
    ObjectList<String>::iterator name;
    unsigned int iname = 0;
    for(name = parameternames.begin(); !(name == parameternames.end()); name++)
      {
	String dname(distributionRoot);
	dname.AppendToEnd(*name);
	BaseDataAttributeDistribution *dist = (BaseDataAttributeDistribution *) instances->GetObject(dname);
	if(dist != NULL)
	  {
	    PrimitiveStats *stats = dist->getStatistics();
	    double ave    = stats->Average;
	    double stddev = stats->StdDev;
	    double dev3 = stddev * 3.0;
	    cout << setw(20) << *name << " " << setw(20) << ave << " " << setw(20) << stddev << " " << dev3 << endl;
	    for(unsigned int j=0;j!= dim1;j++)
	      {
		mat[iname][j] = (mat[iname][j] - ave)/dev3;
	      }
	  }
	else
	  {
	    cerr << "Distribution not found: '" << dname << "'" << endl;
	    result = false;
	  }
	iname++;
      }
    return result;
  }
/*S DataInstancePCAClass
 */
/*F DataInstancePCAClass()  . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataInstancePCAClass::DataInstancePCAClass()
{
  Identification = PCAINSTANCE_PCA_ID;
  NameTag = PCAINSTANCE_PCA_NAME;
  SubClass = ALGORITHM_OPERATION_NAME;
  EncodeDecodeClass = NameTag;
} 
/*F DataInstancePCAClass(data)  . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataInstancePCAClass::DataInstancePCAClass(const DataInstancePCAClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataInstancePCAClass(id,name,descr) . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataInstancePCAClass::DataInstancePCAClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = ALGORITHM_OPERATION_NAME;
  EncodeDecodeClass = PCAINSTANCE_PCA_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . . .  DataInstancePCAClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataInstancePCAClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . .  DataInstancePCAClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataInstancePCAClass, there is no further information.
**
**  REMARKS
**
*/
bool DataInstancePCAClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . .  DataInstancePCAClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataInstancePCAClass::CopyClone(Identify *  objc)
{
  DataInstancePCAClass *objcfull = (DataInstancePCAClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . .  DataInstancePCAClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataInstancePCAClass::Clone()
    {
      DataInstancePCAClass* id = new DataInstancePCAClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . .  DataInstancePCAClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataInstancePCAClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . .  DataInstancePCAClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataInstancePCAClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
//  result = result && Decode(buffer,-----);

  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataInstancePCAClass::BaseDataObjectExample()
{ 
  //cout << "Make InstancePCA Example\n";
  return (BaseDataObject *) new BaseDataInstancePCA();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . .  DataInstancePCAClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataInstancePCAClass*& obj)
     {
     obj = new DataInstancePCAClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . BaseDataInstancePCA
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataInstancePCA*& obj)
     {
     obj = new BaseDataInstancePCA;
     return obj->DecodeThis(buffer);
     }

/*S BaseDataPCAParameterGenerate
 */ 
/*F BaseDataPCAParameterGenerate()  . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataPCAParameterGenerate::BaseDataPCAParameterGenerate()
  : pcaS("PCANames"),
    instnamesS("TotalInstanceNameList")
{
  Identification = PCAINSTANCE_GEN_ID;
  NameTag = PCAINSTANCE_GEN_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataPCAParameterGenerate(data)  . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataPCAParameterGenerate::BaseDataPCAParameterGenerate(const BaseDataPCAParameterGenerate& data)
  : BaseDataAlgorithmOperation(data),
    pcaS("PCANames"),
    instnamesS("TotalInstanceNameList")
{
}
/*F Read(in,objc) . . . . . . . . . . .  Read in BaseDataPCAParameterGenerate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataPCAParameterGenerate::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . .  Read in BaseDataPCAParameterGenerate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataPCAParameterGenerate::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);
  
  return result;
}
 
/*F out1 = print(out) . . . . . . . . . . . . .  BaseDataPCAParameterGenerate
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataPCAParameterGenerate::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . .  BaseDataPCAParameterGenerate
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataPCAParameterGenerate::Clone()
{
  BaseDataPCAParameterGenerate *obj = new BaseDataPCAParameterGenerate;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . .  BaseDataPCAParameterGenerate
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataPCAParameterGenerate::CopyClone(Identify * obj)
{
  BaseDataPCAParameterGenerate *objfull = (BaseDataPCAParameterGenerate *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . .  BaseDataPCAParameterGenerate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPCAParameterGenerate::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . .  BaseDataPCAParameterGenerate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataPCAParameterGenerate::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  return result;
}
/*F ans = SetUpAlgorithms(instances,instancesclass,run,runclass)  . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataPCAParameterGenerate::SetUpAlgorithms(BaseDataSetOfInstances*,
						      DataSetOfInstancesClass*,
						      BaseDataAlgorithmRun* ,
						      DataAlgorithmRunClass*)
{
  return true;
}
/*F ans = CheckInput(instances,instancesclass,run,runclass) . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**
**  REMARKS
**
*/
bool BaseDataPCAParameterGenerate::CheckInput(BaseDataSetOfInstances *instances,
						 DataSetOfInstancesClass*,
						 BaseDataAlgorithmRun* run,
						 DataAlgorithmRunClass*)
{
  bool result = true;

  if(run->ParameterInList(pcaS))
    {
      BaseDataKeyWords *pcakeys = (BaseDataKeyWords *) run->ParameterValue(pcaS);
      ObjectList<String> names = pcakeys->GetKeyWords();
      if(names.size()  == 3)
	{
	  pcaObjectS = names.front();
	  if(instances->IsInList(pcaObjectS))
	    {
	      if(!run->ParameterInList(instnamesS))
		{
		  cerr << "The parameter '" << instnamesS << "' was not in the list of parameters" << endl;
		  result = false;
		}
	    }
	  else
	    {
	      cerr << "The parameter '" << pcaObjectS << "' was not in the list of parameters" << endl;
	      result = false;
	    }
	}
      else
	{
	  cerr << "Not the required parameters in  '" << pcaS << "'" << endl;
	  result = false;
	}
    }
  else
    {
      cerr << "The parameter '" << pcaS << "' was not in the list of parameters" << endl;
      result = false;
    }
    
  
  return result;
}
/*F ans = SetUpInput(instances,instancesclass,run,runclass) . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataPCAParameterGenerate::SetUpInput(BaseDataSetOfInstances *instances,
						 DataSetOfInstancesClass*,
						 BaseDataAlgorithmRun* run,
						 DataAlgorithmRunClass*)
{
  bool result = true;

  instnames = (BaseDataKeyWords *) run->ParameterValue(instnamesS);
  BaseDataKeyWords *keys = (BaseDataKeyWords *) run->ParameterValue(pcaS);
  ObjectList<String> names = keys->GetKeyWords();
  names.pop_front();
  distributionname = names.front();
  names.pop_front();
  rootname = names.front();

  pcaObject = (BaseDataInstancePCAObject *) instances->GetObject(pcaObjectS);
  
  return result;
}
/*F ans = Calculate(instances,instancesclass,run,runclass)  . . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataPCAParameterGenerate::Calculate(BaseDataSetOfInstances* instances,
						DataSetOfInstancesClass*,
						BaseDataAlgorithmRun*,
						DataAlgorithmRunClass*)
{
  bool result = true;
  ObjectList<String> vars = pcaObject->getVariableNames();
  MatrixNumeric parameters(vars.size(),1);
  MatrixNumeric corrections(vars.size(),2);
  ObjectList<String> names = instnames->GetKeyWords();
  ObjectList<String>::iterator name;
  unsigned int ii;
  
  ObjectList<String>::iterator var = vars.begin();
  for(ii=0;ii != vars.size() ; ii++)
    {
      String name(distributionname);
      name.AppendToEnd(*var);
      if(instances->IsInList(name))
	{
	  BaseDataAttributeDistribution *dist = (BaseDataAttributeDistribution *) instances->GetObject(name);
	  PrimitiveStats *stats = dist->getStatistics();
	  double ave    = stats->Average;
	  double stddev = stats->StdDev;
	  double dev3 = stddev * 3.0;
	  corrections[ii][0] = ave;
	  corrections[ii][1] = dev3;
	  var++;
	}
      else
	{
	  cerr << "Distribution '" << name << "' not found" << endl;
	  cerr << "Parameter '" << *var << "' not normalized" << endl;
	}
    }
  var = vars.begin();
  for(name = names.begin();!(name == names.end());name++)
    {
      BaseDataInstance *instance = instances->GetInstance(*name);
      ObjectList<String>::iterator var = vars.begin();
      for(ii=0;ii != vars.size() ; ii++)
	{
	  BaseDataReal *number = (BaseDataReal *) instance->GetObject(*var);
	  parameters[ii][0] = (number->GetValue() - corrections[ii][0])/corrections[ii][1];
	  var++;
	}
      MatrixNumeric ans = pcaObject->transformCoordinates(parameters);
      for(ii=0;ii < ans.size();ii++)
	{
	  BaseDataReal *newparameter = new BaseDataReal;
	  newparameter->NameTag = rootname;
	  String num = Int2String(ii);
	  newparameter->NameTag.AppendToEnd(num);
	  newparameter->SetValue(ans[ii][0]);
	  
	  instance->AddObject(newparameter);
	  delete newparameter;
	}
    }
  
  return result;
}
/*F ans = WriteOutputValues(instances,instancesclass,run,runclass)  algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataPCAParameterGenerate::WriteOutputValues(BaseDataSetOfInstances*,
							DataSetOfInstancesClass*,
							BaseDataAlgorithmRun*,
							DataAlgorithmRunClass*)
{
  bool result = true;
  return result;
}
/*F ans = ConcludeRun(instances,instancesclass,run,runclass)  . . . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataPCAParameterGenerate::ConcludeRun(BaseDataSetOfInstances*,
						  DataSetOfInstancesClass*,
						  BaseDataAlgorithmRun*,
						  DataAlgorithmRunClass*)
{
  bool result = true;
//  delete something
  return result;
}
 
 
 
/*S DataPCAParameterGenerateClass
 */
/*F DataPCAParameterGenerateClass() . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataPCAParameterGenerateClass::DataPCAParameterGenerateClass()
{
  Identification = PCAINSTANCE_GEN_ID;
  NameTag = PCAINSTANCE_GEN_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataPCAParameterGenerateClass(data) . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataPCAParameterGenerateClass::DataPCAParameterGenerateClass(const DataPCAParameterGenerateClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataPCAParameterGenerateClass(id,name,descr)  . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataPCAParameterGenerateClass::DataPCAParameterGenerateClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = PCAINSTANCE_GEN_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . DataPCAParameterGenerateClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataPCAParameterGenerateClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . DataPCAParameterGenerateClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataPCAParameterGenerateClass, there is no further information.
**
**  REMARKS
**
*/
bool DataPCAParameterGenerateClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);

  return result;
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . DataPCAParameterGenerateClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataPCAParameterGenerateClass::CopyClone(Identify *  objc)
{
  DataPCAParameterGenerateClass *objcfull = (DataPCAParameterGenerateClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . DataPCAParameterGenerateClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataPCAParameterGenerateClass::Clone()
    {
      DataPCAParameterGenerateClass* id = new DataPCAParameterGenerateClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . DataPCAParameterGenerateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPCAParameterGenerateClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . DataPCAParameterGenerateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataPCAParameterGenerateClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataPCAParameterGenerateClass::BaseDataObjectExample()
{ 
  //cout << "Make PCAParameterGenerate Example\n";
  return (BaseDataObject *) new BaseDataPCAParameterGenerate();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . DataPCAParameterGenerateClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataPCAParameterGenerateClass*& obj)
     {
     obj = new DataPCAParameterGenerateClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . .  BaseDataPCAParameterGenerate
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataPCAParameterGenerate*& obj)
     {
     obj = new BaseDataPCAParameterGenerate;
     return obj->DecodeThis(buffer);
     }

/*S Utilities
 */
/*F InitialPCAEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialPCAEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataInstancePCAClass,BaseDataInstancePCA,PCAINSTANCE_PCA_NAME);
  EncodeDecodeRegisterClass(DataInstancePCAObjectClass,BaseDataInstancePCAObject,PCAINSTANCE_OBJECT_NAME);
  EncodeDecodeRegisterClass(DataPCAParameterGenerateClass,BaseDataPCAParameterGenerate,PCAINSTANCE_GEN_NAME);


//  bool (*toproutine)(CommBuffer&,Identify*&) = TopDecode;
//  bool (*rout1)(CommBuffer&,DataInstancePCAClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&, Identify*&)) rout1;
//  SingleDecodeRoutine p1(PCAINSTANCE_PCA_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p1.StructureName] = p1;
//
//  bool (*rout2)(CommBuffer&,DataInstancePCAObjectClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&, Identify*&)) rout2;
//  SingleDecodeRoutine p2(PCAINSTANCE_OBJECT_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p2.StructureName] = p2;
//
//  bool (*rout3)(CommBuffer&, DataPCAParameterGenerateClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&, Identify*&)) rout3;
//  SingleDecodeRoutine p3(PCAINSTANCE_GEN_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p3.StructureName] = p3;
//
//  String s1("Object.");
//  String s11(PCAINSTANCE_PCA_NAME);
//  s1.AppendToEnd(s11);
//  bool (*rout11)(CommBuffer&,BaseDataInstancePCA*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&, Identify*&)) rout11;
//  SingleDecodeRoutine p11(s1,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p11.StructureName] = p11;
//  
//  String s2("Object.");
//  String s21(PCAINSTANCE_OBJECT_NAME);
//  s2.AppendToEnd(s21);
//  bool (*rout21)(CommBuffer&,BaseDataInstancePCAObject*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&, Identify*&)) rout21;
//  SingleDecodeRoutine p21(s2,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p21.StructureName] = p21;
//  
//  String s3("Object.");
//  String s31(PCAINSTANCE_GEN_NAME);
//  s3.AppendToEnd(s31);
//  bool (*rout31)(CommBuffer&,BaseDataPCAParameterGenerate*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&, Identify*&)) rout31;
//  SingleDecodeRoutine p31(s3,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p31.StructureName] = p31;
  
}
/*F AddBasePCAClasses(set)  . . . . . . . . . . .  basic algorithm data types
**
**  DESCRIPTION
**    set: The set of data types
**
**  REMARKS
**
*/
void AddBasePCAClasses(DataSetOfObjectsClass& set)
{
  String pcadescr("Principle Component Analysis");
  String objdescr("Principle Component Analysis Object");
  String gendescr("Principle Component Analysis Variable Generation");

  DataInstancePCAClass          pcaclass(PCAINSTANCE_PCA_ID,PCAINSTANCE_PCA_NAME,pcadescr);
  DataInstancePCAObjectClass    objclass(PCAINSTANCE_OBJECT_ID,PCAINSTANCE_OBJECT_NAME,objdescr);
  DataPCAParameterGenerateClass genclass(PCAINSTANCE_GEN_ID,PCAINSTANCE_GEN_NAME,gendescr);

  set.AddObjectClass(pcaclass);
  set.AddObjectClass(objclass);
  set.AddObjectClass(genclass);
}
