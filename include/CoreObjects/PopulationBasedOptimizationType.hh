/*  FILE     PopulationBasedOptimizationType.hh
**  PACKAGE  PopulationBasedOptimization
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "PopulationBasedOptimization" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_POPULATIONBASEDOPTIMIZATIONTYPE_HH
#define CoreObjects_POPULATIONBASEDOPTIMIZATIONTYPE_HH

class DataPopulationObjectClass;
class BaseDataPopulationObject;
class DataPopulationClass;
class BaseDataPopulation;
class DataGeneticObjectClass;

/*C BaseDataGeneticObject  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the GeneticObject class definitions
**
**  REMARKS
**    Inheirits BaseDataOperation
*/
class BaseDataGeneticObject : public BaseDataOperation
{
public:
  BaseDataGeneticObject();
  BaseDataGeneticObject(const BaseDataGeneticObject& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_GENETIC_OBJECT_METHODS;
};
/*C DataGeneticObjectClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOperationClass
*/
class DataGeneticObjectClass : public DataOperationClass
{
  DataObjectClass *ObjectClass;
public:
  DataGeneticObjectClass();
  DataGeneticObjectClass(const DataGeneticObjectClass& data);
  DataGeneticObjectClass(const int id, 
		    const String& name,
		    const String& descr);
  DataObjectClass *getObjectClass();
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataPopulationObject  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the PopulationObject class definitions
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataPopulationObject : public BaseDataObject
{
  double Value;
  BaseDataObject *ValueObject;
public:
  double InstanceValue;
  BaseDataPopulationObject();
  BaseDataPopulationObject(const BaseDataPopulationObject& data);
  ~BaseDataPopulationObject();
  void AssignValue(double value);
  double GetValue();
  virtual bool AddValueObject(BaseDataObject *obj, DataPopulationObjectClass *objclass);
  virtual BaseDataObject *getValueObject();
  bool AddInstanceValue(BaseDataReal *obj);
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataPopulationObjectClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataPopulationObjectClass : public DataObjectClass
{
  DataObjectClass *BaseObjectClass;
public:
  DataPopulationObjectClass();
  DataPopulationObjectClass(const DataPopulationObjectClass& data);
  DataPopulationObjectClass(const int id, 
		    const String& name,
		    const String& descr);
  virtual void setBaseObjectClass(DataObjectClass *objclass);
  virtual DataObjectClass *getBaseObjectClass();
  virtual BaseDataObject *BasePopulationObject();
  bool AddInstanceValue(BaseDataObject *obj,
			DataSetOfObjectsClass *set);
  STANDARD_VIRTUAL_METHODS_CLASS;
};
/*C BaseDataPopulation  . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the Population class definitions
**
**  REMARKS
**    Inheirits BaseDataSetOfObjects
*/
class BaseDataPopulation : public BaseDataSetOfObjects
{
  BaseDataGeneticObject *GeneticObject;
  unsigned int PopulationSize;
  String PopulationObjectNameRoot;
  unsigned int popCount;
  ObjectList<String> *SortedObjects;
  double TotalSum;
public:
  double MinimumCost;
  double MaximumCost;
  BaseDataPopulation();
  BaseDataPopulation(const BaseDataPopulation& data);
  ~BaseDataPopulation();

  String *GenerateNextPopulationObjectName();
  void setPopulationSize(unsigned int popsize);
  unsigned int getPopulationSize();
  BaseDataGeneticObject *getGeneticObject();
  virtual void AddPopulationObject(BaseDataObject *obj);
  virtual bool GenerateInitialPopulation(BaseDataPopulationObject *popobjectbase,
					 DataPopulationClass *popclass);
  bool AssignPopulationValue(double value, String& name);
  virtual void InitializePopulationInformation(BaseDataObject *objbase,
					       BaseDataSetOfInstances *instances, 
					       DataSetOfInstancesClass *instsclass);
  void SortPopulation();
  double UpdateTotalPopulationValueSum();
  double getTotalSum();
  ObjectList<String> *getSortedObjects();
  void TransferEssentialData(BaseDataPopulation *pop);
  void DetermineMinimumAndMaximumCost();

  STANDARD_VIRTUAL_METHODS_OBJECT;
};
/*C DataPopulationClass . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataPopulationClass : public DataSetOfObjectsClass
{
  DataPopulationObjectClass *ObjectClass;
  DataGeneticObjectClass *GeneticClass;
public:
  DataPopulationClass();
  DataPopulationClass(const DataPopulationClass& data);
  DataPopulationClass(const int id, 
		    const String& name,
		    const String& descr);
  void setPopulationObjectClass(DataPopulationObjectClass *objclass);
  DataPopulationObjectClass *getPopulationObjectClass();
  DataGeneticObjectClass *getGeneticClass();
  STANDARD_VIRTUAL_METHODS_CLASS;
};
/*C BaseDataPopulationCost  . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the PopulationCost class definitions
**
**  REMARKS
**    Inheirits BaseDataOptimizeCostFunction
*/
class BaseDataPopulationCost : public BaseDataOptimizeCostFunction
{
  BaseDataParameterizedFunction *Expression;
public:
  BaseDataPopulationCost();
  BaseDataPopulationCost(const BaseDataPopulationCost& data);
  ~BaseDataPopulationCost();

  virtual void InitializeParameters(DataOptimizeCostFunctionClass *costclass,
				    BaseDataSetOfInstances*,
				    DataSetOfInstancesClass*);
  virtual BaseDataObject *operator()(DataObjectClass *objclass,
				     BaseDataObject *x,
				     BaseDataObject *y,
				     DataObjectClass *xclass,
				     DataObjectClass *yclass);
  virtual BaseDataObject *operator()(DataObjectClass *objclass,
				     BaseDataObject *x,
				     DataObjectClass *xclass);
  virtual void AdjustCosts(BaseDataReal *value, BaseDataObject *obj,
			   DataSetOfObjectsClass *set);
  virtual void AccumulateCosts(BaseDataObject *cost);
  virtual void InitializeCost();
  BaseDataParameterizedFunction *getExpression();
  STANDARD_VIRTUAL_METHODS_OBJECT;
};
/*C DataPopulationCostClass . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOptimizeCostFunctionClass
*/
class DataPopulationCostClass : public DataOptimizeCostFunctionClass
{
  DataParameterizedFunctionClass *ExpressionClass;
public:
  DataPopulationCostClass();
  DataPopulationCostClass(const DataPopulationCostClass& data);
  DataPopulationCostClass(const int id, 
		    const String& name,
		    const String& descr);
  DataParameterizedFunctionClass *getExpressionClass();
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataGeneticBasedOptimization  . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the GeneticBasedOptimization class definitions
**
**  REMARKS
**    Inheirits BaseDataOptimizeOperation
*/   
class BaseDataGeneticBasedOptimization : public BaseDataOptimizeOperation
{
  String CostFunctionS;
  String PopulationS;
public:
  BaseDataGeneticBasedOptimization();
  BaseDataGeneticBasedOptimization(const BaseDataGeneticBasedOptimization& data);
  ~BaseDataGeneticBasedOptimization();
  virtual void InitializeObjectToOptimize(BaseDataOptimizeCostFunction *cost,
					  DataOptimizeCostFunctionClass *cclass,
					  BaseDataSetOfInstances*,
					  DataSetOfInstancesClass*);
  virtual bool PerformSingleIteration(BaseDataSetOfObjects *parameters,
				      DataSetOfObjectsClass *parclass,
				      BaseDataSetOfInstances *instances,
				      DataSetOfInstancesClass *);
  virtual String& SelectObjectFromPopulation(BaseDataPopulation *pop);

  bool AddCrossOverObjects(BaseDataPopulationObject *popobjectbase,
			   DataPopulationObjectClass *objclass,
			   BaseDataPopulation *pop, 
			   DataPopulationClass *popclass,
			   String& left, String& right);
  virtual bool UpdateCurrentCosts(DataOptimizeCostFunctionClass *cost,
				  BaseDataSetOfInstances *instances,
				  DataSetOfInstancesClass *instsclass);
  virtual bool MutateObject(BaseDataPopulation *pop, 
			    DataPopulationClass *popclass,
			    String& mutant);
  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
};
/*C DataGeneticBasedOptimizationClass . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataOptimizeOperationClass
*/
class DataGeneticBasedOptimizationClass : public DataOptimizeOperationClass
{
public:
  DataGeneticBasedOptimizationClass();
  DataGeneticBasedOptimizationClass(const DataGeneticBasedOptimizationClass& data);
  DataGeneticBasedOptimizationClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataGeneticAlgorithm  . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the GeneticAlgorithm class definitions
**
**  REMARKS
**    Inheirits BaseDataGeneticBasedOptimization
*/
class BaseDataGeneticAlgorithm : public BaseDataGeneticBasedOptimization
{
  ObjectList<String> Parameters;

public:
  BaseDataGeneticAlgorithm();
  BaseDataGeneticAlgorithm(const BaseDataGeneticAlgorithm& data);
  void InitializeObjectToOptimize(BaseDataOptimizeCostFunction *cost,
				  DataOptimizeCostFunctionClass *cclass,
				  BaseDataSetOfInstances*,
				  DataSetOfInstancesClass*);
  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
};
/*C DataGeneticAlgorithmClass . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataGeneticBasedOptimizationClass
*/
class DataGeneticAlgorithmClass : public DataGeneticBasedOptimizationClass
{
public:
  DataGeneticAlgorithmClass();
  DataGeneticAlgorithmClass(const DataGeneticAlgorithmClass& data);
  DataGeneticAlgorithmClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
