/*  FILE     OptimizeType.hh
**  PACKAGE  Optimize
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "Optimize" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_OPTIMIZETYPE_HH
#define CoreObjects_OPTIMIZETYPE_HH

class DataOptimizeCostFunctionClass;
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
/*C BaseDataOptimizeCostFunction  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the OptimizeCostFunction class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataOptimizeCostFunction : public BaseDataOperation
{
  bool ResultWithParameters;
  BaseDataSetOfObjects *Parameters;
  BaseDataObject *OptimizeObject;
  BaseDataObject *CurrentCost;
  ObjectList<String> TrainInstanceNames;
  
public:

  unsigned int MaximumIterationCount;
  unsigned int IterationCount;

  BaseDataOptimizeCostFunction();
  BaseDataOptimizeCostFunction(const BaseDataOptimizeCostFunction& data);
  ~BaseDataOptimizeCostFunction();

  void SetOptimizeObject(BaseDataObject *current);
  BaseDataObject *GetOptimizeObject();
  virtual BaseDataSetOfObjects *ExtractParameters(DataOptimizeCostFunctionClass *costclass);
  virtual void InsertParameters(BaseDataSetOfObjects *parameters);
  virtual void InitializeCost();
  virtual BaseDataObject *operator()(DataObjectClass *objclass,
				     BaseDataObject *x,
				     DataObjectClass *xclass);
  virtual BaseDataObject *operator()(DataObjectClass *objclass,
				     BaseDataObject *x,
				     BaseDataObject *y,
				     DataObjectClass *xclass,
				     DataObjectClass *yclass);
  virtual void AccumulateCosts(BaseDataObject *cost);
  virtual void InitializeParameters(DataOptimizeCostFunctionClass *,
				    BaseDataSetOfInstances*,
				    DataSetOfInstancesClass*);
  BaseDataSetOfObjects *getParameters();
  BaseDataObject *getCurrentCost();
  void setCurrentCost(BaseDataObject *);
  ObjectList<String>& getTrainInstanceNames();
  void setTrainInstanceNames(ObjectList<String>& names);
  STANDARD_VIRTUAL_METHODS_OBJECT;
};
/*C DataOptimizeCostFunctionClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataOptimizeCostFunctionClass : public DataOperationClass
{
  DataSetOfObjectsClass *ParameterClass;
public:
  DataOptimizeCostFunctionClass();
  DataOptimizeCostFunctionClass(const DataOptimizeCostFunctionClass& data);
  DataOptimizeCostFunctionClass(const int id, 
		    const String& name,
		    const String& descr);
  DataSetOfObjectsClass *getParameterClass();
  void setParameterClass(DataSetOfObjectsClass *);
  STANDARD_VIRTUAL_METHODS_CLASS;
};
/*C BaseDataRealVectorCostFunction  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the RealVectorCostFunction class definitions
**
**  REMARKS
**    Inheirits BaseDataOptimizeCostFunction
*/
class BaseDataRealVectorCostFunction : public BaseDataOptimizeCostFunction
{
public:
  BaseDataRealVectorCostFunction();
  BaseDataRealVectorCostFunction(const BaseDataRealVectorCostFunction& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataRealVectorCostFunctionClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOptimizeCostFunctionClass
*/
class DataRealVectorCostFunctionClass : public DataOptimizeCostFunctionClass
{
public:
  DataRealVectorCostFunctionClass();
  DataRealVectorCostFunctionClass(const DataRealVectorCostFunctionClass& data);
  DataRealVectorCostFunctionClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataOptimizeOperation  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the OptimizeOperation class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataOptimizeOperation : public BaseDataAlgorithmOperation
{
  String OptimizationCostS;
  BaseDataOptimizeCostFunction *OptimizationCost;
  String TrainInstanceNamesS;
  ObjectList<String> TrainInstanceNames;
  String MaximumIterationCountS;
  
  String OptimizeObjectS;
  BaseDataObject *OptimizeObject;

public:
  String FinalResultS;
  BaseDataOptimizeOperation();
  BaseDataOptimizeOperation(const BaseDataOptimizeOperation& data);
  ~BaseDataOptimizeOperation();

  virtual BaseDataOptimizeCostFunction *getCurrentCostFunction();
  BaseDataObject *getOptimizeObject();
  void getOptimizeObject(BaseDataObject *);
  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
  virtual bool InitializeOptimization(DataOptimizeCostFunctionClass *costclass,
				      BaseDataSetOfInstances *instances,
				      DataSetOfInstancesClass *instsclass);
  virtual bool OptimizationNotDone();
  virtual bool PerformSingleIteration(BaseDataSetOfObjects *parameters,
				      DataSetOfObjectsClass *parclass,
				      BaseDataSetOfInstances *instances,
				      DataSetOfInstancesClass *);
  virtual bool UpdateCurrentCosts(DataOptimizeCostFunctionClass *costclass,
				  BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instsclass);
  virtual void InitializeObjectToOptimize(BaseDataOptimizeCostFunction *cost,
					  DataOptimizeCostFunctionClass *cclass,
					  BaseDataSetOfInstances*,
					  DataSetOfInstancesClass*);
};
/*C DataOptimizeOperationClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataOptimizeOperationClass : public DataAlgorithmOperationClass
{
public:
  DataOptimizeOperationClass();
  DataOptimizeOperationClass(const DataOptimizeOperationClass& data);
  DataOptimizeOperationClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataRealOptimizeOperation  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the RealOptimizeOperation class definitions
**
**  REMARKS
**    Inheirits BaseDataOptimizeOperation
*/
class BaseDataRealOptimizeOperation : public BaseDataOptimizeOperation
{
public:
  BaseDataRealOptimizeOperation();
  BaseDataRealOptimizeOperation(const BaseDataRealOptimizeOperation& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataRealOptimizeOperationClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOptimizeOperationClass
*/
class DataRealOptimizeOperationClass : public DataOptimizeOperationClass
{
public:
  DataRealOptimizeOperationClass();
  DataRealOptimizeOperationClass(const DataRealOptimizeOperationClass& data);
  DataRealOptimizeOperationClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataSimpleIterativeOptimize  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the SimpleIterativeOptimize class definitions
**
**  REMARKS
**    Inheirits BaseDataRealOptimizeOperation
*/
class BaseDataSimpleIterativeOptimize : public BaseDataRealOptimizeOperation
{
public:
  BaseDataSimpleIterativeOptimize();
  BaseDataSimpleIterativeOptimize(const BaseDataSimpleIterativeOptimize& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataSimpleIterativeOptimizeClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataRealOptimizeOperationClass
*/
class DataSimpleIterativeOptimizeClass : public DataRealOptimizeOperationClass
{
public:
  DataSimpleIterativeOptimizeClass();
  DataSimpleIterativeOptimizeClass(const DataSimpleIterativeOptimizeClass& data);
  DataSimpleIterativeOptimizeClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

#endif
