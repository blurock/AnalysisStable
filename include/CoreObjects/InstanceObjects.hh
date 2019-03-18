/*  FILE     InstanceObjects.hh
**  PACKAGE  InstanceObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "InstanceObjects" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_INSTANCEOBJECTS_HH
#define CoreObjects_INSTANCEOBJECTS_HH

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "InstanceObjectsType.hh"


#define INSTANCE_INSTANCE_ID          INSTANCE_ID_BASE + 10
#define INSTANCE_SETOFINSTANCES_ID    INSTANCE_ID_BASE + 20
#define INSTANCE_MATRIX_ID            INSTANCE_ID_BASE + 30
#define INSTANCE_VECTOR_ID            INSTANCE_ID_BASE + 40
#define INSTANCE_PROGRESSMATRIX_ID    INSTANCE_ID_BASE + 7

#define INSTANCE_INSTANCE_NAME        "Instance"
#define INSTANCE_SETOFINSTANCES_NAME  "Instances"
#define INSTANCE_MATRIX_NAME          "InstanceMatrix"
#define INSTANCE_VECTOR_NAME          "InstanceVector"
#define INSTANCE_PROGRESSMATRIX_NAME "ProgressVariableMatrix"

#define TOO_BIG_ROW_NUMBER   99999999

/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
void InitialSetOfInstanceEncodeDecodeRoutines();
bool ReadInInstancesAndClass(String& icfilename,
			     String& ifilename,
			     BaseDataSetOfInstances& instances,
			     DataSetOfInstancesClass& instancesclass,
			     DataSetOfObjectsClass& Standard,
			     unsigned int maindebug);
bool InstanceEncodeTest(String& classfilename, String& filename, 
			DataSetOfObjectsClass& standard,
			CommBuffer& buf);
bool InstanceDecodeTest(CommBuffer& buf);
bool InstanceEncodeTest(CommBuffer& buf);
int InstanceReadTest(ReactionSystemBase* sys);
int InstanceCloneDeleteTest(ReactionSystemBase* sys);
int InstanceEncodeDecodeTest(ReactionSystemBase* sys);
bool ReadEncoded(istream& in, CommBuffer*& buffer);
bool WriteEncoded(ostream& out, CommBuffer& buffer);
int PrintInstanceAttribute(ostream& out,
			   String& instance,
			   String& attribute,
			   BaseDataSetOfInstances& instances,
			   DataSetOfInstancesClass& instsclass);
int PrintInstanceInfo(ReactionSystemBase *sys);
void AddInstanceClasses(DataSetOfObjectsClass& set);
int DataInformationOut(String ptype, ostream& out, ReactionSystemBase *sys);
#endif
