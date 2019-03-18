/*  FILE     GoalObjects.hh
**  PACKAGE  GoalObjects
**  AUTHOR   Edward s. Blurock
**
**  CONTENT
**    Prototypes for the "GoalObjects" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_GOALOBJECTS_HH
#define CoreObjects_GOALOBJECTS_HH

#define GOALS_SPEC_ID               GOALS_BASE_ID + 10
#define GOALS_SPEC_NAME             "GoalSpec"
#define GOALS_SUMMARY_ID            GOALS_BASE_ID + 20
#define GOALS_SUMMARY_NAME          "GoalSummary"
#define GOALS_RUN_ID                GOALS_BASE_ID + 30
#define GOALS_RUN_NAME              "GoalRun"
#define GOALS_SETOFDEFS_ID          GOALS_BASE_ID + 40
#define GOALS_SETOFDEFS_NAME        "SetOfGoalDefs"


/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "GoalObjectsType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
bool operator==(const BaseDataGoalSpec& spec1,BaseDataGoalSpec& spec2);
bool operator<(const BaseDataGoalSpec& spec1,BaseDataGoalSpec& spec2);

bool ReadGoalAndSpecs(String& rfilename,
		      String& gfilename,
		      DataGoalRunClass& rclass,
		      DataGoalSpecClass& sclass,
		      BaseDataGoalSpec& goalspec,
		      DataSetOfObjectsClass& Standard,
		      unsigned int maindebug);
int RunAlgorithmAsGoal(ReactionSystemBase *level1,
		       DataSetOfObjectsClass& Standard);
void AddGoalObjectsClasses(DataSetOfObjectsClass& set);
extern void InitialGoalObjectsEncodeDecodeRoutines();
int SetGoalClass(ReactionSystemBase *sys);
int RunGoal(ReactionSystemBase *sys);

#endif
