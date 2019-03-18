/*  FILE     SimulatedAnnealing.hh
**  PACKAGE  SimulatedAnnealing
**  AUTHOR   
**
**  CONTENT
**    Definitions for the "SimulatedAnnealing" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
*/
 
#ifndef REACTION_SimulatedAnnealing_HH
#define REACTION_SimulatedAnnealing_HH


//  ALGORITHM_BASE_ID + 100 by REFORMBASISALG_PREDICATETEST_ID !! wh
#define SIMANNALG_ID                       ALGORITHM_BASE_ID + 110
#define SIMANNUPPERLOWER_ID                ALGORITHM_BASE_ID + 120

#define OPERATION_FCTTOOPT_ID              OPERATION_ID_BASE + 100
#define OPERATION_FCTTOOPTTEST_ID          OPERATION_ID_BASE + 110

#define SIMANNALG_NAME                     "SimulatedAnnealingAlgorithm"
#define SIMANNUPPERLOWER_NAME              "SimAnnUpperLower"
#define OPERATION_FCTTOOPT_NAME            "FunctionToOptimize"
#define OPERATION_FCTTOOPTTEST_NAME        "TestFunction1"


#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "MenuObjects.hh"
//#include "PredicateObjects.hh"
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"

/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
void AddSimAnnAlgorithmsClasses(DataSetOfObjectsClass& set);
extern void InitialSimAnnAlgorithmsEncodeDecodeRoutines();

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#ifdef _msdos_stl
#include <iostream>
#include <list>
#include <map>
using namespace std;
#pragma warning(disable:4786)
#endif

#ifdef _unix
#include "STL.h"
#endif

#include "defines.hh"

#ifndef USER_ID
#define USER_ID \
"/* $Id: SimulatedAnnealing.hh,v 1.1 2008/02/17 12:13:29 blurock Exp $ */"
#endif

#include "myUser.h"
#if MY_TEMPLATE			/* MY_TEMPLATE_includes */
  /* add your own include files as required */
#endif
#if COST_FILE
#include "myUser_cst.h"
#endif
#if ASA_LIB
static LONG_INT *asa_rand_seed;
#endif
#if ASA_TEMPLATE_SAVE		/* used to illustrate use of ASA_SAVE */
static double random_array[256];
#endif

#ifndef ASA_ID
#define ASA_ID \
"/* $Id: SimulatedAnnealing.hh,v 1.1 2008/02/17 12:13:29 blurock Exp $ */"
#endif


#include "myASA.h"




#include "SimulatedAnnealingType.hh"


/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/




#endif
