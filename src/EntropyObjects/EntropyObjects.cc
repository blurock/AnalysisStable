/*  FILE     EntropyObjects.cc
**  PACKAGE  EntropyObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Exported functions for the "EntropyObjects" package.
**
**  REFERENCES
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/

 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"
#include "InstanceAlgorithms.hh"
#include "PredicateObjects.hh"
#include "EvaluationTree.hh"
#include "EntropyObjects.hh"

//#define DEBUG_LEVEL1

/*S AlgorithmRoutines
 */
/*F conj = CreateConjunction(conjS,instances,instclass,run,runclass)
**
**  DESCRIPTION
**    conjS: The conjuction parameter name from run
**    instances: The set of instances
**    instclass: The instance class
**    run: The algorithm run
**    runclass: The run class
**
**  REMARKS
**
*/
BaseDataConjunction *CreateConjunction(const String& conjS,
                                       BaseDataSetOfInstances* instances,
                                       DataSetOfInstancesClass*,
                                       BaseDataAlgorithmRun* run,
                                       DataAlgorithmRunClass*)
{
  BaseDataConjunction *conj;
  if(run->ParameterInList(conjS))
    {
      BaseDataKeyWords *conjkeys = (BaseDataKeyWords *)
        run->ParameterValue(conjS);
      conj = conj->CreateConjunction(instances,conjkeys);
    }
  else
    conj = NULL;
  return conj;
}
 
/*F ans = WriteAsParameter(mat,matS,run)  . . . . . . . . . . .  write matrix
**
**  DESCRIPTION
**    mat: The matrix
**    matS: The name of the matrix object
**    run: The algorithm run
**    ans: true if successful
**
**  REMARKS
**
*/
bool WriteAsParameter(MatrixNumeric& mat, String& matS, BaseDataAlgorithmRun *run)
{
  BaseDataDoubleMatrix *partmat = new BaseDataDoubleMatrix(mat);
  partmat->NameTag = matS;
#ifdef DEBUG_LEVEL1
  cout << "\n---------------- Partition Matrix---------------------------\n";
  partmat->print(cout);
  cout << endl;
#endif
  bool result = run->AddParameter(partmat);
  delete partmat;
  return result;
}
 
/*F ans = WriteAsParameter(num,numS,run)  . . . . . . . . . . .  write double
**
**  DESCRIPTION
**    num: The double to write
**    numS: The name of the double
**    run: The algorithm run structure
**    ans: true if successful
**
**  REMARKS
**
*/
bool WriteAsParameter(const double num, String& numS, BaseDataAlgorithmRun *run)
{
  BaseDataReal *numobject = new BaseDataReal;
  numobject->NameTag = numS;
  numobject->SetValue(num);
#ifdef DEBUG_LEVEL1
  cout << "The Constant: " << numS << ": ";
  numobject->print(cout);
  cout << endl;
#endif
  run->AddParameter(numobject);
  delete numobject;
  return true;
}

/*S Decision Tree Utilites
 */
 
/*F count = ElementCountFromPartitionMatrix(mat)   number of virtual elements
**
**  DESCRIPTION
**    mat: The partition table matrix computed for all instances
**    count: The count derived from the partition table
**
**    This is an indirect way to get the count instead of using the BaseDataConjunction
**    structure.
**
**  REMARKS
**
*/
double ElementCountFromPartitionMatrix(MatrixNumeric& mat)
{
  unsigned int size1 = mat.size();
  unsigned int size2 = mat[0].size();
  
  double count = 0.0;
  
  for(unsigned int i=0;i < size1;i++)
    for(unsigned int j=0; j < size2; j++)
      {
        count += mat[i][j];
      }
  return count;
}

/*S Utility
 */
 
/*F info = InfoContent(p) . . . . . . . . . . . . . . . . . . . . .  p*log2(p)
**
**  DESCRIPTION
**    p: The probability
**    info: The number of bits (or entropy if you want)
**
**    This simply calculates p*log2(p)
**
**  REMARKS
**
*/
double InfoContent(double p)
{
  double info = 0.0;
  
  if(p > 1e-10 )
    info = p * log(p)*LOG2_INVERSE;
  else
    info = 0.0;
  
  return info;
}
/*F gain = ComputeStandardEntropyGain(mat)  . . . from partition table matrix
**
**  DESCRIPTION
**    mat: The partition table matrix
**    gain: The entropy (# of bits) gain
**
**  REMARKS
**
*/
double ComputeStandardEntropyGain(MatrixNumeric& mat)
{
  unsigned int i,j;
  
  unsigned int sizeofgoals = mat.size();
  unsigned int sizeofdescr = mat[0].size();

  VectorNumeric goalstotal(sizeofgoals);
  VectorNumeric descrtotal(sizeofdescr);
  VectorNumeric subentropy(sizeofdescr);
  
  for(i=0;i<sizeofgoals;i++)
    goalstotal[i] = 0.0;
      
  for(j=0;j<sizeofdescr;j++)
    {
      descrtotal[j] = 0.0;
      subentropy[j] = 0.0;
    }
  
  for(i=0;i<sizeofgoals;i++)
    for(j=0;j<sizeofdescr;j++)
      {
        goalstotal[i] += mat[i][j];
        descrtotal[j] += mat[i][j];
      }
  double p;
  
  for(i=0;i<sizeofgoals;i++)
    for(j=0;j<sizeofdescr;j++)
      {
        p = mat[i][j] / descrtotal[j];
        subentropy[j] -= InfoContent(p);
      }
  double entropyafter = 0.0;
  for(j=0; j< sizeofdescr;j++)
    {
      entropyafter += subentropy[j] * descrtotal[j];
    }

  double entropybefore = 0.0;
  for(i=0;i<sizeofgoals;i++)
    {
      entropybefore -= InfoContent(goalstotal[i]);
    }

  double g = entropybefore - entropyafter;
  
  return g;
}

/*S BaseDataEntropyAlgorithm
 */ 
/*F BaseDataEntropyAlgorithm()  . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataEntropyAlgorithm::BaseDataEntropyAlgorithm()
  : entropyParametersS(ENTROPY_PARAMETERS),
    instanceListS(CURRENT_INSTANCELIST),
    logicDescriptionsS(LOGIC_DESCRIPTIONS),
    OutputMatS(ENTROPY_MATRIX),
    OutputGainS(ENTROPY_GAIN)
{
  Identification = ENTROPY_ALG_ID;
  NameTag = ENTROPY_ALG_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataEntropyAlgorithm(data)  . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataEntropyAlgorithm::BaseDataEntropyAlgorithm(const BaseDataEntropyAlgorithm& data)
  : BaseDataAlgorithmOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . . . . .  Read in BaseDataEntropyAlgorithm
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataEntropyAlgorithm::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . .  Read in BaseDataEntropyAlgorithm
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataEntropyAlgorithm::Read(istream& in, DataObjectClass* objc, const String& name)
{
  return BaseDataAlgorithmOperation::Read(in,objc,name);
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . .  BaseDataEntropyAlgorithm
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataEntropyAlgorithm::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . .  BaseDataEntropyAlgorithm
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataEntropyAlgorithm::Clone()
{
  BaseDataEntropyAlgorithm *obj = new BaseDataEntropyAlgorithm;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . . . . .  BaseDataEntropyAlgorithm
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataEntropyAlgorithm::CopyClone(Identify * obj)
{
  BaseDataEntropyAlgorithm *objfull = (BaseDataEntropyAlgorithm *) obj;
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . .  BaseDataEntropyAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataEntropyAlgorithm::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);

  return result;
}
 
/*F ans = DecodeThis(buffer)  . . . . . . . . . . .  BaseDataEntropyAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataEntropyAlgorithm::DecodeThis(CommBuffer& buffer)
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
bool BaseDataEntropyAlgorithm::SetUpAlgorithms(BaseDataSetOfInstances*,
                                               DataSetOfInstancesClass*,
                                               BaseDataAlgorithmRun* ,
                                               DataAlgorithmRunClass*)
{
  return true;
}
/*F ans = WriteOutputValues(instances,instancesclass,run,runclass)  algorithm
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataEntropyAlgorithm::WriteOutputValues(BaseDataSetOfInstances*,
                                                 DataSetOfInstancesClass*,
                                                 BaseDataAlgorithmRun* run,
                                                 DataAlgorithmRunClass*) 
{
  bool result = WriteAsParameter(*GainMat,OutputMatS,run);
  result = result && WriteAsParameter(GainValue,OutputGainS,run);

  return result;
}
/*F ans = ConcludeRun(instances,instancesclass,run,runclass)  . . . algorithm
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataEntropyAlgorithm::ConcludeRun(BaseDataSetOfInstances*,
                                           DataSetOfInstancesClass*,
                                           BaseDataAlgorithmRun*,
                                           DataAlgorithmRunClass* ) 
{
  delete conj;
  delete table;
  delete GainMat;

  return true;
  
}
/*F ans = CheckInput(instances,instancesclass,run,runclass) . . . . algorithm
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataEntropyAlgorithm::CheckInput(BaseDataSetOfInstances*,
                                          DataSetOfInstancesClass*,
                                          BaseDataAlgorithmRun* run,
                                          DataAlgorithmRunClass*)
{
  bool result = true;
  
  if(run->ParameterInList(entropyParametersS))
    {
      if(run->ParameterInList(instanceListS))
        {
          if(!run->ParameterInList(logicDescriptionsS))
            {
              cerr << "Logic Descriptions not found: '" << logicDescriptionsS << "'" << endl;
              result = false;
            }
        }
      else
        {
          cerr << "Instance List not found: " << instanceListS << endl;
          result = false;
        }
    }
  else
    {
      cerr << "Entropy Parameters table not found: " << entropyParametersS << endl;
      result = false;
    }
  return result;
}
/*F ans = SetUpInput(instances,instancesclass,run,runclass) . . . . algorithm
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataEntropyAlgorithm::SetUpInput(BaseDataSetOfInstances*,
                                          DataSetOfInstancesClass*,
                                          BaseDataAlgorithmRun* run,
                                          DataAlgorithmRunClass*)
{
  bool result = true;
  
  instanceList = (BaseDataKeyWords *) run->ParameterValue(instanceListS);
  logicDescriptions = (BaseDataSetOfLogicDescriptions *) run->ParameterValue(logicDescriptionsS);
  BaseDataKeyWords *k1 = (BaseDataKeyWords *) run->ParameterValue(entropyParametersS);  
  ObjectList<String> names = k1->GetKeyWords();
  if(names.size() > 0)
    {
      tableS = names.front();
      names.pop_front();
      if(names.size() > 0)
        {
          conjunctionS = names.front();
          names.pop_front();
        }
      else
        {
          result = false;
          cerr << "Empty Conjunction Class\n";
        }
    }
  else
    {
      result = false;
      cerr << "No Entropy Parameters in '" << entropyParametersS << "' given\n";
      cerr << "Expecting: PartitionTable [Conjunction]\n";
    }
  
  return result;
}
 
/*F ans = Calculate(instances,instancesclass,run,runclass)  . . . . algorithm
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataEntropyAlgorithm::Calculate(BaseDataSetOfInstances* instances,
                                         DataSetOfInstancesClass* instancesclass,
                                         BaseDataAlgorithmRun* run,
                                         DataAlgorithmRunClass* runclass)
{
  bool result = true;
  
  if(runclass->getDebugLevel() > 4)
    {
      cout << "\n---------------- BaseDataEntropyAlgorithm::Calculate---------------------------\n";
    }
  table = new BaseDataPartitionTable(instances,tableS);
  if(runclass->getDebugLevel() > 4)
    {
      cout << "BaseDataEntropyAlgorithm::Calculate   Partition Table\n";
      table->print(cout);
    }
  conj = CreateConjunction(conjunctionS,
                           instances,instancesclass,
                           run,runclass);
      
  if(conj != NULL)
    {
      conjclass = (DataConjunctionClass *) instancesclass->PointerToAllowedClasses()->GetObjectClass(conj->GetType());
    }
  else
    {
      result = false;
      cerr << "Conjunction Parameter not found: ";
      cerr << conjunctionS << endl;
    }
  ObjectList<String> names = instanceList->GetKeyWords();
  DataSetOfLogicDescriptionsClass descrclass;

  if(runclass->getDebugLevel() > 4)
    {
      cout << "BaseDataEntropyAlgorithm::Calculate   Conjunction: " << endl;
      conj->print(cout);
      cout << endl;
    }
  GainMat = table->CalculatePartitionMatrixFromSet(*logicDescriptions,
                                                   instances,instancesclass,
                                                   descrclass,
                                                   conj,conjclass,
                                                   names);
  if(runclass->getDebugLevel() > 4)
    {
      cout << "BaseDataEntropyAlgorithm::Calculate   GainMat: " << endl;
      GainMat->print(cout);
      cout << endl;
    }
  GainValue = ComputeStandardEntropyGain(*GainMat);
  if(runclass->getDebugLevel() > 4)
    {
      cout << "BaseDataEntropyAlgorithm::Calculate   GainValue: ";
      cout << GainValue << endl;
    }  
  return true;
}

//#define DEBUG_LEVEL1

/*S DataEntropyAlgorithmClass
 */
/*F DataEntropyAlgorithmClass() . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataEntropyAlgorithmClass::DataEntropyAlgorithmClass()
{
  Identification = ENTROPY_ALG_ID;
  NameTag = ENTROPY_ALG_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataEntropyAlgorithmClass(data) . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataEntropyAlgorithmClass::DataEntropyAlgorithmClass(const DataEntropyAlgorithmClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataEntropyAlgorithmClass(id,name,descr)  . . . . . . . . . . constructor
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
DataEntropyAlgorithmClass::DataEntropyAlgorithmClass(const int id, 
                                                     const String& name,
                                                     const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = ENTROPY_ALG_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . . . . DataEntropyAlgorithmClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataEntropyAlgorithmClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  // the rest
       
       return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . DataEntropyAlgorithmClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataEntropyAlgorithmClass, there is no further information.
**
**  REMARKS
**
*/
bool DataEntropyAlgorithmClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  return DataAlgorithmOperationClass::Read(in,set);
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . . . . DataEntropyAlgorithmClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataEntropyAlgorithmClass::CopyClone(Identify * objc)
{
  DataEntropyAlgorithmClass *objcfull = (DataEntropyAlgorithmClass *) objc;
  *this = *objcfull;
}
 
/*F objc = Clone()  . . . . . . . . . . . . . . . . DataEntropyAlgorithmClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataEntropyAlgorithmClass::Clone()
{
  DataEntropyAlgorithmClass* id = new DataEntropyAlgorithmClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . DataEntropyAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataEntropyAlgorithmClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . DataEntropyAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataEntropyAlgorithmClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataEntropyAlgorithmClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataEntropyAlgorithm();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . DataEntropyAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataEntropyAlgorithmClass*& obj)
{
  obj = new DataEntropyAlgorithmClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . .  BaseDataEntropyAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataEntropyAlgorithm*& obj)
{
  obj = new BaseDataEntropyAlgorithm;
  return obj->DecodeThis(buffer);
}

/*S BaseDataEntropySelectPredicate
 */ 
/*F BaseDataEntropySelectPredicate()  . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataEntropySelectPredicate::BaseDataEntropySelectPredicate()
  : AlgorithmEntropyS("3-EntropyAlg#Entropy"),
    AlgorithmEntropy(NULL),
    InputGoalS(SELECTION_GOAL),
    InputDescriptorsS(SELECTION_DESCRIPTORS),
    OutputTopPredicateS(ENTROPY_TOP_PREDICATE),
    OutputPartitionTable(ENTROPY_PARTITION_TABLE),
    entropygain(ENTROPY_GAIN),
    parmS(ENTROPY_PARAMETERS),
    partitionS(ENTROPY_PARTITION_TABLE),
    goalS(SELECTION_GOAL),
    descrS(SELECTION_DESCRIPTORS),
    conjS(ENTROPY_CONJUNCTION)
{
  Identification = ENTROPY_SELECT_ID;
  NameTag = ENTROPY_SELECT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataEntropySelectPredicate(data)  . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataEntropySelectPredicate::BaseDataEntropySelectPredicate(const BaseDataEntropySelectPredicate& data)
  : BaseDataAlgorithmOperation(data)
{
}
/*F Read(in,objc) . . . . . . . . . .  Read in BaseDataEntropySelectPredicate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataEntropySelectPredicate::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . .  Read in BaseDataEntropySelectPredicate
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataEntropySelectPredicate::Read(istream& in, DataObjectClass* objc, const String& name)
{
  return BaseDataAlgorithmOperation::Read(in,objc,name);
}
 
/*F out1 = print(out) . . . . . . . . . . . .  BaseDataEntropySelectPredicate
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataEntropySelectPredicate::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . .  BaseDataEntropySelectPredicate
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataEntropySelectPredicate::Clone()
{
  BaseDataEntropySelectPredicate *obj = new BaseDataEntropySelectPredicate;
  obj->CopyClone(this);
  return obj;
}
 
/*F CopyClone(obj)  . . . . . . . . . . . . .  BaseDataEntropySelectPredicate
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataEntropySelectPredicate::CopyClone(Identify * obj)
{
  BaseDataEntropySelectPredicate *objfull = (BaseDataEntropySelectPredicate *) obj;
  
  *this = *objfull;
}
 
/*F ans = EncodeThis(buffer)  . . . . . . . .  BaseDataEntropySelectPredicate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataEntropySelectPredicate::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . .  BaseDataEntropySelectPredicate
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataEntropySelectPredicate::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  return result;
}
 
/*F ans = NoCommonKeys(keys1,keys2) . . . . . . . . . . . . .  check keywords
**
**  DESCRIPTION
**    keys1,keys2: The set of keys
**    ans: true if no common keys among the two sets
**
**  REMARKS
**
*/
static bool NoCommonKeys(BaseDataKeyWords& keys1, BaseDataKeyWords& keys2)
{
  ObjectList<String> k1 = keys1.GetKeyWords();
  ObjectList<String> k2 = keys2.GetKeyWords();

  k2.Intersected(k1);
  bool result = false;
  if(k2.size() == 0)
    result = true;
  return result;
}
/*F name = FindBest(names,values,conj,instances)  . . . . . best from entropy
**
**  DESCRIPTION
**    names: The names of the partitions
**    values: The corresponding entropy values of the partitions
**    conj: The conjuction leading to the node
**    instances: The set of instances
**    name: The best partition
**
**  REMARKS
**
*/
static String FindBest(ObjectList<String>& names, ObjectList<double>& values,
                       BaseDataConjunction& conj,
                       BaseDataSetOfInstances *instances)
{
  ObjectList<String>::iterator name;
  ObjectList<double>::iterator value = values.begin();
  BaseDataKeyWords exclude = conj.KeyWordsFromConjunction();
  
  double top = -1.0e+20;
  String *topname = new String;
  
  for(name = names.begin();
      name != names.end();
      name++) {
      if(*value > top ) {
          BaseDataKeyWords *keys = (BaseDataKeyWords *) instances->GetObject(*name);
          if(NoCommonKeys(exclude,*keys)) {
              top = *value;
              *topname = *name;
            }
        }
      value++;
    }
  return *topname;
}
/*F setEntropyAlgorithmName(entropy) 
**
**  DESCRIPTION
**    entropy: The entropy algorithm
**
**  REMARKS
**
*/
void BaseDataEntropySelectPredicate::SetEntropyAlgorithm(BaseDataAlgorithmOperation *entropy)
{
  AlgorithmEntropy = entropy;
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
bool BaseDataEntropySelectPredicate::SetUpAlgorithms(BaseDataSetOfInstances*,
                                                     DataSetOfInstancesClass*,
                                                     BaseDataAlgorithmRun* run,
                                                     DataAlgorithmRunClass* rclass)
{
  if(AlgorithmEntropy == NULL)
    {
      ObjectList<String> algnames = run->GetListOfSubAlgorithms();
      AlgorithmEntropyS  = algnames.front();
      AlgorithmEntropy = run->GetSubAlgorithm(AlgorithmEntropyS);
    }
    
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
bool BaseDataEntropySelectPredicate::CheckInput(BaseDataSetOfInstances*,
                                                DataSetOfInstancesClass*,
                                                BaseDataAlgorithmRun* run,
                                                DataAlgorithmRunClass*)
{
  bool result = true;
  
  if(!run->ParameterInList(SELECTION_GOAL))
    {
      cerr << "No goal specified in: ";
      cerr << SELECTION_GOAL;
      cerr << endl;
      result = false;
    }
  else
    {
      BaseDataKeyWords *keys = (BaseDataKeyWords *) run->ParameterValue(SELECTION_GOAL);
      ObjectList<String> goalnames = keys->GetKeyWords();
      
      if(goalnames.size() == 0)
        {
          cerr << "Goal Parameter not found: ";
          cerr << SELECTION_GOAL;
          cerr << endl;
          result = false;
        }      
      else
        {
          if(!run->ParameterInList(SELECTION_DESCRIPTORS))
            {
              cerr << "Descriptor List Parameter not found: ";
              cerr << SELECTION_DESCRIPTORS;
              cerr << endl;
              result = false;
            }
        }
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
bool BaseDataEntropySelectPredicate::SetUpInput(BaseDataSetOfInstances*,
                                                DataSetOfInstancesClass*,
                                                BaseDataAlgorithmRun* run,
                                                DataAlgorithmRunClass* runclass)
{
  keys = (BaseDataKeyWords *) run->ParameterValue(InputGoalS);
  descriptors = (BaseDataKeyWords *) run->ParameterValue(SELECTION_DESCRIPTORS);

  if(runclass->getDebugLevel() > 2)
    {
      cout << "The Input Goal: \n";
      keys->print(cout);
      cout << endl;
      cout << "The Descriptors: \n";
      descriptors->print(cout);
      cout << endl;
    }
  
  return true;
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
bool BaseDataEntropySelectPredicate::Calculate(BaseDataSetOfInstances* instances,
                                               DataSetOfInstancesClass* instancesclass,
                                               BaseDataAlgorithmRun* run,
                                               DataAlgorithmRunClass* runclass)
{
  BaseDataKeyWords entropyparameters;
  entropyparameters.NameTag = parmS;
  entropyparameters.AddKeyWord(partitionS);
  entropyparameters.AddKeyWord(conjS);
  bool result = run->AddParameter(&entropyparameters);
  
  ObjectList<String> goalnames = keys->GetKeyWords();
  goalname = goalnames.front();
  
  ObjectList<String> names = descriptors->GetKeyWords();
  ObjectList<String>::iterator name;
  ObjectList<double> values;
  double bestvalue = 0.0;
  for(name = names.begin(); name != names.end() && result; name++) {
      if(instances->IsInList(*name)) {
          if(runclass->getDebugLevel() > 2) {
              cout << "Partition: " << *name << endl;
            }
          
          BaseDataKeyWords partitiontable;
          partitiontable.NameTag = ENTROPY_PARTITION_TABLE;
          partitiontable.Identification = instances->NextIdentification();
          partitiontable.AddKeyWord(goalname);
          partitiontable.AddKeyWord(*name);
          if(runclass->getDebugLevel() > 2)
            {
              cout << "Partition Table: \n";
              partitiontable.print(cout);
              cout << endl;
              cout << "DebugLevel: " << runclass->getDebugLevel() << endl;
              cout << "Entropy Operator: \n";
              AlgorithmEntropy->print(cout);
              cout << endl;
            }
          

          result = result && instances->AddObject(&partitiontable);
          result = result && AlgorithmEntropy->operator()(instances,instancesclass,run,runclass);
          if(result)
            {
              BaseDataReal *obj = (BaseDataReal *) run->ParameterValue(entropygain);
              double value = obj->GetValue();
	      if(bestvalue < value) {
		bestvalue = value;
	      }
		
	      if(runclass->getDebugLevel() > 0)
		{
		  cout << setw(10) << value << " ";
		  cout << *name << endl;
		}
              values.AddObject(value);
              
            }
          else
            {
              cerr << "Entropy Operator failed\n";
            }
          
        }
      else
        {
          cerr << "Partition not found: ";
          cerr << *name;
          cerr << "\n";
          values.AddObject(0.0);
        }
    }
  if(result)
    {
      BaseDataConjunction *conj = CreateConjunction(conjS,instances,instancesclass,run,runclass);
      top = FindBest(names,values,*conj,instances);
      delete conj;
    }
  WriteAsParameter(bestvalue,entropygain,run);
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
bool BaseDataEntropySelectPredicate::WriteOutputValues(BaseDataSetOfInstances*,
                                                       DataSetOfInstancesClass*,
                                                       BaseDataAlgorithmRun *run,
                                                       DataAlgorithmRunClass*)
{
  toppredicates = new BaseDataKeyWords;
  toppredicates->AddKeyWord(top);
  toppredicates->NameTag = OutputTopPredicateS;
  run->AddParameter(toppredicates);
  return true;
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
bool BaseDataEntropySelectPredicate::ConcludeRun(BaseDataSetOfInstances*,
                                                 DataSetOfInstancesClass*,
                                                 BaseDataAlgorithmRun*,
                                                 DataAlgorithmRunClass*)
{
  delete toppredicates;
  delete partitiontable;
  
  return true;
}
/*S DataEntropySelectPredicateClass
 */
/*F DataEntropySelectPredicateClass() . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataEntropySelectPredicateClass::DataEntropySelectPredicateClass()
{
  Identification = ENTROPY_SELECT_ID;
  NameTag = ENTROPY_SELECT_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataEntropySelectPredicateClass(data) . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataEntropySelectPredicateClass::DataEntropySelectPredicateClass(const DataEntropySelectPredicateClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
 
/*F DataEntropySelectPredicateClass(id,name,descr)  . . . . . . . constructor
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
DataEntropySelectPredicateClass::DataEntropySelectPredicateClass(const int id, 
                                                                 const String& name,
                                                                 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = ENTROPY_SELECT_NAME;
}
 
/*F out1 = print(out) . . . . . . . . . . . . DataEntropySelectPredicateClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataEntropySelectPredicateClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
       
  return out;
}
 
/*F in1 = Read(in)  . . . . . . . . . . . . . DataEntropySelectPredicateClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataEntropySelectPredicateClass, there is no further information.
**
**  REMARKS
**
*/
bool DataEntropySelectPredicateClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  return DataAlgorithmOperationClass::Read(in,set);
}
 
/*F CopyClone(objc) . . . . . . . . . . . . . DataEntropySelectPredicateClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataEntropySelectPredicateClass::CopyClone(Identify *  objc)
{
  DataEntropySelectPredicateClass *objcfull = (DataEntropySelectPredicateClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . DataEntropySelectPredicateClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataEntropySelectPredicateClass::Clone()
{
  DataEntropySelectPredicateClass* id = new DataEntropySelectPredicateClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . DataEntropySelectPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataEntropySelectPredicateClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . DataEntropySelectPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataEntropySelectPredicateClass::DecodeThis(CommBuffer& buffer)
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
BaseDataObject * DataEntropySelectPredicateClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataEntropySelectPredicate();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . DataEntropySelectPredicateClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataEntropySelectPredicateClass*& obj)
{
  obj = new DataEntropySelectPredicateClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . .  BaseDataEntropySelectPredicate
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataEntropySelectPredicate*& obj)
{
  obj = new BaseDataEntropySelectPredicate;
  return obj->DecodeThis(buffer);
}
/*S Utility
 */
/*F AddEntropyClasses(set) . . . . . . . .  basic algorithm data types
**
**  DESCRIPTION
**    set: The set of data types
**
**  REMARKS
**
*/
void AddEntropyAlgorithmClasses(DataSetOfObjectsClass& set)
{
  String algdescr("The Entropy Algorithm");
  String seldescr("The Entropy Select Algorithm");
  DataEntropyAlgorithmClass algclass(ENTROPY_ALG_ID,
				     ENTROPY_ALG_NAME,
				     algdescr);
  DataEntropySelectPredicateClass selclass(ENTROPY_SELECT_ID,
					   ENTROPY_SELECT_NAME,
					   seldescr);
  set.AddObjectClass(algclass);
  set.AddObjectClass(selclass);
}
/*F InitialEntropyAlgorithmEncodeDecodeRoutines()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialEntropyAlgorithmEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataEntropyAlgorithmClass,BaseDataEntropyAlgorithm,ENTROPY_ALG_NAME);
  EncodeDecodeRegisterClass(DataEntropySelectPredicateClass,BaseDataEntropySelectPredicate,ENTROPY_SELECT_NAME);
//  bool (*toproutine)(CommBuffer&,Identify*&);
//
//  bool (*rout1)(CommBuffer&,DataEntropyAlgorithmClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout1;
//  SingleDecodeRoutine p1(ENTROPY_ALG_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p1.StructureName] = p1;
//
//  bool (*rout2)(CommBuffer&,DataEntropySelectPredicateClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout2;
//  SingleDecodeRoutine p2(ENTROPY_SELECT_NAME,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p2.StructureName] = p2;
//
//  String s11("Object.");
//  String s111(ENTROPY_ALG_NAME);
//  s11.AppendToEnd(s111);
//  bool (*rout11)(CommBuffer&,BaseDataEntropyAlgorithm*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout11;
//  SingleDecodeRoutine p11(s11,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p11.StructureName] = p11;
//
//  String s21("Object.");
//  String s211(ENTROPY_SELECT_NAME);
//  s21.AppendToEnd(s211);
//  bool (*rout21)(CommBuffer&,BaseDataEntropySelectPredicate*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout21;
//  SingleDecodeRoutine p21(s21,toproutine);
//  (*SetOfEncodeDecodeRoutines)[p21.StructureName] = p21;
}




