/*  FILE     RunIgnition.hh
**  PACKAGE  RunIgnition
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "RunIgnition" package in the Cantera environment
**
**  COPYRIGHT (C) 2000 Edward S. Blurock
*/
 
#ifndef Cantera_RUNIGNITION_HH
#define Cantera_RUNIGNITION_HH

#define RUNIGNITION_RUNIGNITION_ID            RUNIGNITION_BASE_ID + 11
#define RUNIGNITION_RUNIGNITION_NAME          "RunIgnition"
#define RUNIGNITION_IGNITIONSCONDITIONS_ID    RUNIGNITION_BASE_ID + 12
#define RUNIGNITION_IGNITIONSCONDITIONS_NAME  "IgnitionConditions"
#define RUNIGNITION_RUNSETOFCONDITIONS_ID     RUNIGNITION_BASE_ID + 13
#define RUNIGNITION_RUNSETOFCONDITIONS_NAME   "RunSetOfConditions"

#define CONDITIONS_ATTRIBUTE       "Conditions"
#define CONDITIONNAMES_ATTRIBUTE   "ConditionNames"
#define SPECIES_ATTRIBUTE          "Species"
#define PRESSURE_ATTRIBUTE         "Pressure"
#define TEMPERATURE_ATTRIBUTE      "Temperature"
#define DELTAT_ATTRIBUTE           "DeltaT"
#define FINALTIME_ATTRIBUTE        "FinalTime"
#define OUTPUTMATRIX_ATTRIBUTE     "OutputName"
#define STANDARD_CANTERA_EXTENSION ".cti"
#define ITERATIONSET_ATTRIBUTE     "IterationSet"
#define MOLFRACTIONS_ATTRIBUTE     "MolFractions"
#define RATES_FORWARD              "ForwardRates"
#define RATES_REVERSE              "ReverseRates"
#define RATES_NET                  "NetProductionRates"
#define TIMESTEP_PROPERTIES        "TimeStepProperties"

#define TIMETMAX_ATTRIBUTE           "TimeTemperatureMaximum"
#define TIMEOHMAX_ATTRIBUTE          "TimeOHMaximum"
#define TOTALRUNTIME_ATTRIBUTE       "TotalRunTime"
#define FINALTEMPERATURE_ATTRIBUTE   "FinalTemperature"
#define NUMBEREVALUATIONS_ATTRIBUTE  "NumberJacobianEvaluations"
#define NUMBEREQUATIONS_ATTRIBUTE    "NumberOfEquations"


template<class G, class A> void saveSoln(int i, double time, const G& gas, A& soln);
template<class G, class A> void saveSoln(double time, const G& gas, A& soln);
template<class G, class V> void makeDataLabels(const G& gas, V& names);
template<class G, class A> void plotSoln(string fname, string fmt, string title, const G& gas, const A& soln);

inline void writeCanteraHeader(ostream& s) {
    s << endl;
#ifdef CANTERA_VERSION
    s << "     Cantera version " << CANTERA_VERSION << endl;        
#else
    s << "     ???" << endl;
#endif
    s << "     Copyright California Institute of Technology, 2002." << endl;
    s << "     http://www.cantera.org" << endl;
    s << endl;
}


/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "RunIgnitionType.hh"

/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
void InitialRunIgnitionDecodeFunctions();
void AddRunIgnitionClasses(DataSetOfObjectsClass& set);

#endif
