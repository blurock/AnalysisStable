/*  FILE     AlgorithmObjects.hh
**  PACKAGE  AlgorithmObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "AlgorithmObjects" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_ALGORITHMOBJECTS_HH
#define CoreObjects_ALGORITHMOBJECTS_HH

#define ALGORITHM_PARAMETERS_ID     ALGORITHM_BASE_ID + 20
#define ALGORITHM_SUMMARY_ID        ALGORITHM_BASE_ID + 30
#define ALGORITHM_RESULTS_ID        ALGORITHM_BASE_ID + 40
#define ALGORITHM_DEFINITION_ID     ALGORITHM_BASE_ID + 50
#define ALGORITHM_RUN_ID            ALGORITHM_BASE_ID + 60
#define ALGORITHM_OPERATION_ID      ALGORITHM_BASE_ID + 70
#define ALGORITHM_TEST_ID           ALGORITHM_BASE_ID + 80
#define ALGORITHM_PARAMETERS_NAME       "Parameters"
#define ALGORITHM_SUMMARY_NAME          "AlgorithmSummary"
#define ALGORITHM_RESULTS_NAME          "AlgorithmResults"
#define ALGORITHM_DEFINITION_NAME       "AlgorithmDefinition"
#define ALGORITHM_RUN_NAME              "AlgorithmRun"
#define ALGORITHM_OPERATION_NAME        "AlgorithmOperation"
#define ALGORITHM_TEST_NAME             "AlgorithmTest"

#include "MenuObjects.hh"
 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#define STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS                         \
virtual bool SetUpAlgorithms(BaseDataSetOfInstances*,                     \
			     DataSetOfInstancesClass*,                    \
			     BaseDataAlgorithmRun* run,                   \
			     DataAlgorithmRunClass*);                     \
virtual bool SetUpInput(BaseDataSetOfInstances* instances,                \
		        DataSetOfInstancesClass* instancesclass,          \
			BaseDataAlgorithmRun* run,                        \
			DataAlgorithmRunClass* runclass);                 \
virtual bool WriteOutputValues(BaseDataSetOfInstances*,                   \
			       DataSetOfInstancesClass*,                  \
			       BaseDataAlgorithmRun* run,                 \
			       DataAlgorithmRunClass*);                  \
virtual bool ConcludeRun(BaseDataSetOfInstances*,                         \
			 DataSetOfInstancesClass*,                        \
			 BaseDataAlgorithmRun*,                           \
			 DataAlgorithmRunClass* );                        \
virtual bool CheckInput(BaseDataSetOfInstances*,                          \
			DataSetOfInstancesClass*,                         \
			BaseDataAlgorithmRun* run,                        \
			DataAlgorithmRunClass*);                          \
virtual bool Calculate(BaseDataSetOfInstances* instances,                 \
		       DataSetOfInstancesClass* instancesclass,           \
		       BaseDataAlgorithmRun *run,                         \
		       DataAlgorithmRunClass*);


/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "AlgorithmObjectsType.hh"

bool CheckInputVariable(const String& name, const String& descr, BaseDataAlgorithmRun *run);
void AddBaseAlgorithmClasses(DataSetOfObjectsClass& set);
extern int AlgorithmAndInstanceReadIn(ObjectList<String>& inputs,
				      DataSetOfObjectsClass standardclasses);
extern int AlgorithmAndInstanceMultipleAlgorithms(ObjectList<String>& inputs,
						  DataSetOfObjectsClass& standardclasses);
extern void InitialSetOfAlgorithmObjectsEncodeDecodeRoutines();
int SetAlgorithmClass(ReactionSystemBase *sys);
int RunAlgorithm(ReactionSystemBase *sys);

#endif
