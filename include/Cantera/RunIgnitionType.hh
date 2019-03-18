/*  FILE     RunIgnitionType.hh
**  PACKAGE  RunIgnition
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "RunIgnition" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION      } else {
	cerr << "Expected 'd:' got '" << dLabel << "'" << endl;
      }

**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 Cantera Project, RISC Linz
*/
 
#ifndef Cantera_RUNIGNITIONTYPE_HH
#define Cantera_RUNIGNITIONTYPE_HH
#include <cantera/Cantera.h>
#include "cantera/kernel/converters/CKReader.h"
#include <cantera/zerodim.h>
#include <cantera/IdealGasMix.h>
#include <time.h>
#include <cantera/kernel/Array.h>
#include <cantera/kernel/plots.h>
#include <cantera/equilibrium.h>

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

/*C RxnDataIgnitionConditions  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the IgnitionConditions class definitions
**
**  REMARKS
**    Inheirits BaseDataRealBasedProperty
*/
class RxnDataIgnitionConditions : public RxnDataRealBasedProperty
{
public:
  BaseDataSetOfObjects *Species;
  BaseDataReal *Temperature;
  BaseDataReal *Pressure;
  BaseDataReal *DeltaT;

  RxnDataIgnitionConditions();
  RxnDataIgnitionConditions(const RxnDataIgnitionConditions& data);
  ostream& StandardASCIIOut(ostream& out) const;
  virtual bool WriteAsLine(ostream& out, DataObjectClass *objc);
  virtual bool WriteAsASCII(ostream& out, DataObjectClass *objc);
  virtual bool WriteAsLatex(ostream& out, DataObjectClass  *objc);

  STANDARD_VIRTUAL_METHODS_OBJECT

};
/*C RxnIgnitionConditionsClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataRealBasedPropertyClass
*/
class RxnIgnitionConditionsClass : public RxnRealBasedPropertyClass
{
public:
  DataSetOfObjectsClass *SpeciesClass;
  DataRealClass *SpeciesValueClass;
  DataRealClass *TemperatureClass;
  DataRealClass *PressureClass;
  DataRealClass *DeltaTClass;

  RxnIgnitionConditionsClass();
  RxnIgnitionConditionsClass(const RxnIgnitionConditionsClass& data);
  RxnIgnitionConditionsClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};



/*C RxnDataRunIgnition  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the RunIgnition class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class RxnDataRunIgnition : public BaseDataAlgorithmOperation
{
  String RootNameS;
  String ConditionsS;
  String FinalTimeS;
  String OutputNameS;
  String ForwardRatesS;
  String ReverseRatesS;
  String NetProductionRatesS;

  String RootName;
  double finalTime;
  String OutputAttribute;
  
  unsigned int numberOfIntervals;
  String inputFileName;

  RxnDataIgnitionConditions *Conditions;

public:
  RxnDataRunIgnition();
  RxnDataRunIgnition(const RxnDataRunIgnition& data);
  vector_fp *formSpeciesFromConditions(BaseDataAlgorithmRun *run);
  int kinetics(BaseDataAlgorithmRun *run);
  STANDARD_VIRTUAL_METHODS_OBJECT
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS

  IdealGasMix *GasState;

  int Iterations;
  double totalRuntime;
  double finalTemperature;
  int numberEvaluations;
  int numberEquations;
  double timeTMax;

private:

  double tlast;
  double dTmax;
  int OHindex;
  int CO2index;
  double timeOHMax;
  double OHMax;
  double CurrentTime;

  void ignitionTimeInitialize();
  void ignitionTimeCheck(double time, double dt, double temperature);
  void ignitionTimeFinalize(ostream& out);
  void SaveRealValue(double value, String& name);
  void SaveIntegerValue(int value, String& name);
  void runMatrixInitialize(int numruns, BaseDataAlgorithmRun *run);
  void runMatrixTimeStepInfo(int i);
  void runMatrixFinalize(BaseDataAlgorithmRun *run);
  void saveMatrix(const char n[], BaseDataKeyWords *columns,
		  MatrixNumeric *mat,BaseDataAlgorithmRun *run);
  void excelOutMatrix(BaseDataInstanceDoubleMatrix *mat,
		      BaseDataAlgorithmRun *run);

  BaseDataKeyWords *SpeciesNames;
  BaseDataKeyWords *IndexNames;
  
  MatrixNumeric *MassFractions;
  MatrixNumeric *NetProductionRates;
  MatrixNumeric *ForwardRates;
  MatrixNumeric *ReverseRates;
  MatrixNumeric *TimeStepProperties;

  void transferToMatrix(double *temp, unsigned int dim, 
			double time, MatrixNumeric *mat);
  
};
/*C RxnRunIgnitionClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class RxnRunIgnitionClass : public DataAlgorithmOperationClass
{
public:
  RxnRunIgnitionClass();
  RxnRunIgnitionClass(const RxnRunIgnitionClass& data);
  RxnRunIgnitionClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataRunSetOfConditions  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the RunSetOfConditions class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataRunSetOfConditions : public BaseDataAlgorithmOperation
{
  String RootNameS;
  String IterationSetS;
  String ConditionsS;
  String OutputNameS;

  String PressureAttribute;
  String TemperatureAttribute;
  String DeltaTAttribute;
  String SpeciesAttribute;
  
  BaseDataString *OutputAttribute;
  OpenOutputFile *fileSummary;
  BaseDataKeySet *ConditionNames;

  String RootName;
  BaseDataIterationSet *IterationSet;
  RxnDataIgnitionConditions *Conditions;
  RxnDataRunIgnition *Calculation;
public:
  BaseDataRunSetOfConditions();
  BaseDataRunSetOfConditions(const BaseDataRunSetOfConditions& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS
};
/*C DataRunSetOfConditionsClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataRunSetOfConditionsClass : public DataAlgorithmOperationClass
{
  RxnIgnitionConditionsClass *ConditionsClass;
public:
  DataRunSetOfConditionsClass();
  DataRunSetOfConditionsClass(const DataRunSetOfConditionsClass& data);
  DataRunSetOfConditionsClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};




#endif
