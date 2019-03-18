/*  FILE     ConsecutiveType.hh
**  PACKAGE  Consecutive
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "Consecutive" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_CONSECUTIVETYPE_HH
#define CoreObjects_CONSECUTIVETYPE_HH

/*C BaseDataClusterInstanceSets  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ClusterInstanceSets class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataClusterInstanceSets : public BaseDataAlgorithmOperation
{
  String InstanceNameListS;
  BaseDataKeyWords *InstanceNameList;
  String ClusterS;
  BaseDataClusterTree *Cluster;
  String RootNameS;
  BaseDataString *RootName;

  BaseDataKeyWords *ClusterSetNames;

public:
  BaseDataClusterInstanceSets();
  BaseDataClusterInstanceSets(const BaseDataClusterInstanceSets& data);

  BaseDataKeyWords *getNames(BaseDataClusterNode *node, String& name);  
  void TraverseSons(BaseDataClusterNode *node,
		    BaseDataSetOfInstances *instances);  
  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
};
/*C DataClusterInstanceSetsClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataClusterInstanceSetsClass : public DataAlgorithmOperationClass
{
public:
  DataClusterInstanceSetsClass();
  DataClusterInstanceSetsClass(const DataClusterInstanceSetsClass& data);
  DataClusterInstanceSetsClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataConsecutiveSeries  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ConsecutiveSeries class definitions
**
**  REMARKS
**    Inheirits BaseDataSetOfObjects
*/
class BaseDataConsecutiveSeries : public BaseDataSetOfObjects
{
public:
  String Top;
  String Bottom;
  BaseDataKeyWords GapList;
  unsigned int NumberOfElements;

  BaseDataConsecutiveSeries();
  BaseDataConsecutiveSeries(const BaseDataConsecutiveSeries& data);
  bool WriteAsLine(ostream& out, DataObjectClass *objc);
  bool WriteAsASCII(ostream& out, DataObjectClass* objc);
  bool WriteAsLatex(ostream& out, DataObjectClass* cls);

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataConsecutiveSeriesClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataConsecutiveSeriesClass : public DataSetOfObjectsClass
{
public:
  DataConsecutiveSeriesClass();
  DataConsecutiveSeriesClass(const DataConsecutiveSeriesClass& data);
  DataConsecutiveSeriesClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataConsecutiveSeriesSet  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ConsecutiveSeriesSet class definitions
**
**  REMARKS
**    Inheirits BaseDataSetOfObjects
*/
class BaseDataConsecutiveSeriesSet : public BaseDataSetOfObjects
{
public:
  BaseDataConsecutiveSeriesSet();
  BaseDataConsecutiveSeriesSet(const BaseDataConsecutiveSeriesSet& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  bool WriteAsLine(ostream& out, DataObjectClass *objc);
  bool WriteAsASCII(ostream& out, DataObjectClass* objc);
  bool WriteAsLatex(ostream& out, DataObjectClass* cls);
};
/*C DataConsecutiveSeriesSetClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataSetOfObjectsClass
*/
class DataConsecutiveSeriesSetClass : public DataSetOfObjectsClass
{
  String RootNameS;
  String InstanceNameListS;
  String ClusterSetsS;
  
  BaseDataConsecutiveSeriesSet *ConsecutiveSet;
  
public:
  DataConsecutiveSeriesSetClass();
  DataConsecutiveSeriesSetClass(const DataConsecutiveSeriesSetClass& data);
  DataConsecutiveSeriesSetClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
  DataSetOfObjectsClass*  PointerToAllowedClasses();
};
/*C BaseDataConsecutive  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the Consecutive class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataConsecutive : public BaseDataAlgorithmOperation
{
  String RootNameS;
  String InstanceNameListS;
  BaseDataKeyWords *InstanceNameList;
  String ClusterSetsS;
  BaseDataKeyWords *ClusterSets;
  String MaximumGapS;
  BaseDataInteger *MaximumGap;
  String MinimumS;
  BaseDataInteger *Minimum;

  unsigned int maximumGap;
  unsigned int minimum;

  BaseDataConsecutiveSeriesSet *ConsecutiveSets;
public:
  BaseDataConsecutive();
  BaseDataConsecutive(const BaseDataConsecutive& data);
  void AddNameTagToSeries(BaseDataConsecutiveSeries *series,
			  String& cluster, unsigned int subseries);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
};
/*C DataConsecutiveClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataConsecutiveClass : public DataAlgorithmOperationClass
{
public:
  DataConsecutiveClass();
  DataConsecutiveClass(const DataConsecutiveClass& data);
  DataConsecutiveClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataSortElements  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the SortElements class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataSortElements : public BaseDataAlgorithmOperation
{
  String InstanceNameListS;
  BaseDataKeyWords *InstanceNameList;
  String SortParameterS;
  BaseDataString *SortParameter;
  BaseDataKeyWords *Sorted;

public:
  BaseDataSortElements();
  BaseDataSortElements(const BaseDataSortElements& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
};
/*C DataSortElementsClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataSortElementsClass : public DataAlgorithmOperationClass
{
public:
  DataSortElementsClass();
  DataSortElementsClass(const DataSortElementsClass& data);
  DataSortElementsClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};







/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
