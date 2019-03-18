/*  FILE     RuleSystem.hh
**  PACKAGE  RuleSystem
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "RuleSystem" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_RULESYSTEM_HH
#define CoreObjects_RULESYSTEM_HH

#define RULESYSTEM_RULE_ID            RULESYSTEM_BASE + 1
#define RULESYSTEM_RULE_NAME          "ActionRule"
#define RULESYSTEM_RULESET_ID         RULESYSTEM_BASE + 2
#define RULESYSTEM_RULESET_NAME       "SetOfRules"
#define RULESYSTEM_SYSTEM_ID          RULESYSTEM_BASE + 3
#define RULESYSTEM_SYSTEM_NAME        "ProductionSystem"
#define RULESYSTEM_SEARCH_ID          RULESYSTEM_BASE + 4
#define RULESYSTEM_SEARCH_NAME        "ProductionSystemSearch"
#define RULESYSTEM_RULEEXE_ID         RULESYSTEM_BASE + 5
#define RULESYSTEM_RULEEXE_NAME       "ExecuteActionRule"
#define RULESYSTEM_PRODNODE_ID        RULESYSTEM_BASE + 6
#define RULESYSTEM_PRODNODE_NAME      "ProductionSystemNode"
#define RULESYSTEM_PARSYSTEM_ID       RULESYSTEM_BASE + 7
#define RULESYSTEM_PARSYSTEM_NAME     "ParameterizedProductionRun"

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "RuleSystemType.hh"


/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
void AddRuleSystemClasses(DataSetOfObjectsClass& set);
extern void InitialSetOfRuleSystemEncodeDecodeRoutines();
String NonDeterministicChoice(BaseDataSetOfObjects *choices);


#endif
