/*  FILE     SimulatedAnnealing.cpp
**  PACKAGE  SimulatedAnnealing    
**  AUTHOR   
**
**  CONTENT
**    
**
**  REFERENCES
**
*/
//#include "CommBuffer.hh"
//#include "String.hh"
//#include "Objects.hh"
#define TEMPLATE_INSTANTIATION
//#include "Vector.hh"


//#include "CoreDataObjects.hh"
//#include "NumericObjects.hh"
//#include "LogicalObjects.hh"
//#include "FunctionReal1DObjects.hh"
//#include "OperationObjects.hh"
//#include "DataObjects.hh"
//#include "InstanceObjects.hh"
//#include "MenuObjects.hh"
////#include "PredicateObjects.hh"
//#include "DirectedTreeObjects.hh"
//#include "SelectObjects.hh"
//#include "AlgorithmObjects.hh"

#include "SimulatedAnnealing.hh"
BaseDataFunctionToOptimize* SimulatedAnnealing::fToUse = NULL;	// important!!!

//#include "VASLModels.hh"

/*S SimAnnHelpParameters
 */ 
/*C SimAnnHelpParameters . . . . . . . . . . . . . . . . . . .empty constructor
**
**  DESCRIPTION
**        
**  REMARKS
**
*/
SimAnnHelpParameters::SimAnnHelpParameters()
{
	#if OPTIONS_FILE
	  ptr_options = NULL;
	  read_option[0] = '\0';
	  read_int = 0;
	#if INT_LONG
	  read_long = 0;
	#endif
	  read_double = 0;
	#endif
}



/*S SimAnnParametersToAsaRun
 */ 
/*C SimAnnParametersToAsaRun . . . . . . . . . . . . . . . . . . .empty constructor
**
**  DESCRIPTION
**        
**  REMARKS
**
*/
SimAnnParametersToAsaRun::SimAnnParametersToAsaRun()
: SimAnnHelpParameters()
{
	if ((USER_OPTIONS 
		=	(USER_DEFINES *) calloc (1, sizeof (USER_DEFINES))) == NULL)
		exit (9);

	#if OPTIONS_FILE
	  // Test to see if asa_opt is in correct directory.
	  //   This is useful for some PC and Mac compilers. 
	  if ((ptr_options = fopen ("myASA_opt", "r")) == NULL)
		exit (6);

	#if INT_LONG
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%ld", &read_long);
	  USER_OPTIONS->Limit_Acceptances = read_long;
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%ld", &read_long);
	  USER_OPTIONS->Limit_Generated = read_long;
	#else
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%d", &read_int);
	  USER_OPTIONS->Limit_Acceptances = read_int;
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%d", &read_int);
	  USER_OPTIONS->Limit_Generated = read_int;
	#endif
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%d", &read_int);
	  USER_OPTIONS->Limit_Invalid_Generated_States = read_int;
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%lf", &read_double);
	  USER_OPTIONS->Accepted_To_Generated_Ratio = read_double;

	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%lf", &read_double);
	  USER_OPTIONS->Cost_Precision = read_double;
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%d", &read_int);
	  USER_OPTIONS->Maximum_Cost_Repeat = read_int;
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%d", &read_int);
	  USER_OPTIONS->Number_Cost_Samples = read_int;
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%lf", &read_double);
	  USER_OPTIONS->Temperature_Ratio_Scale = read_double;
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%lf", &read_double);
	  USER_OPTIONS->Cost_Parameter_Scale_Ratio = read_double;
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%lf", &read_double);
	  USER_OPTIONS->Temperature_Anneal_Scale = read_double;

	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%d", &read_int);
	  USER_OPTIONS->Include_Integer_Parameters = read_int;
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%d", &read_int);
	  USER_OPTIONS->User_Initial_Parameters = read_int;
	#if INT_ALLOC
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%d", &read_int);
	  USER_OPTIONS->Sequential_Parameters = read_int;
	#else
	#if INT_LONG
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%ld", &read_long);
	  USER_OPTIONS->Sequential_Parameters = read_long;
	#else
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%d", &read_int);
	  USER_OPTIONS->Sequential_Parameters = read_int;
	#endif
	#endif
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%lf", &read_double);
	  USER_OPTIONS->Initial_Parameter_Temperature = read_double;

	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%d", &read_int);
	  USER_OPTIONS->Acceptance_Frequency_Modulus = read_int;
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%d", &read_int);
	  USER_OPTIONS->Generated_Frequency_Modulus = read_int;
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%d", &read_int);
	  USER_OPTIONS->Reanneal_Cost = read_int;
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%d", &read_int);
	  USER_OPTIONS->Reanneal_Parameters = read_int;

	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%lf", &read_double);
	  USER_OPTIONS->Delta_X = read_double;
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%d", &read_int);
	  USER_OPTIONS->User_Tangents = read_int;
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%d", &read_int);
	  USER_OPTIONS->Curvature_0 = read_int;

	#else // OPTIONS_FILE 
	  // USER_OPTIONS->Limit_Acceptances = 10000; 
	  USER_OPTIONS->Limit_Acceptances = 1000;
	  USER_OPTIONS->Limit_Generated = 99999;
	  USER_OPTIONS->Limit_Invalid_Generated_States = 1000;
	  // USER_OPTIONS->Accepted_To_Generated_Ratio = 1.0E-6; 
	  USER_OPTIONS->Accepted_To_Generated_Ratio = 1.0E-4;

	  USER_OPTIONS->Cost_Precision = 1.0E-18;
	  USER_OPTIONS->Maximum_Cost_Repeat = 5;
	  USER_OPTIONS->Number_Cost_Samples = 5;
	  USER_OPTIONS->Temperature_Ratio_Scale = 1.0E-5;
	  USER_OPTIONS->Cost_Parameter_Scale_Ratio = 1.0;
	  USER_OPTIONS->Temperature_Anneal_Scale = 100.0;

	  USER_OPTIONS->Include_Integer_Parameters = FALSE;
	  USER_OPTIONS->User_Initial_Parameters = FALSE;
	  USER_OPTIONS->Sequential_Parameters = -1;
	  USER_OPTIONS->Initial_Parameter_Temperature = 1.0;

	  USER_OPTIONS->Acceptance_Frequency_Modulus = 100;
	  USER_OPTIONS->Generated_Frequency_Modulus = 10000;
	  USER_OPTIONS->Reanneal_Cost = 1;
	  USER_OPTIONS->Reanneal_Parameters = TRUE;

	  USER_OPTIONS->Delta_X = 0.001;
	  USER_OPTIONS->User_Tangents = FALSE;
	  USER_OPTIONS->Curvature_0 = FALSE;

	#endif // OPTIONS_FILE 

	  // ALLOCATE STORAGE 

	#if ASA_TEMPLATE_SAVE
	  // Such data could be saved in a user_save file, but for
	  //   convenience here everything is saved in asa_save. 
	  USER_OPTIONS->Asa_Data_Dim = 256;
	  if ((USER_OPTIONS->Asa_Data =
		   (double *) calloc (256, sizeof (double))) == NULL)
		  exit (9);
	  USER_OPTIONS->Asa_Data = random_array;
	#endif

	#if USER_ASA_OUT
	  if ((USER_OPTIONS->Asa_Out_File =
		   (char *) calloc (80, sizeof (char))
		  ) == NULL)
		  exit (9);
	#endif

	#if ASA_TEMPLATE_SAMPLE
//	  *parameter_dimension = 2; in class SimAnnParametersToFunction
	  USER_OPTIONS->Limit_Acceptances = 2000;
	  USER_OPTIONS->User_Tangents = TRUE;
	  USER_OPTIONS->Limit_Weights = 1.0E-7;
	#endif
	#if ASA_TEMPLATE_PARALLEL
	  USER_OPTIONS->Gener_Block = 100;
	  USER_OPTIONS->Gener_Block_Max = 512;
	  USER_OPTIONS->Gener_Mov_Avr = 3;
	#endif

	#if USER_COST_SCHEDULE
	  USER_OPTIONS->Cost_Schedule = user_cost_schedule;
	#endif

	#if USER_ACCEPTANCE_TEST
	  USER_OPTIONS->Acceptance_Test = user_acceptance_test;
	#endif
	#if USER_ACCEPT_ASYMP_EXP
	  USER_OPTIONS->Asymp_Exp_Param = 1.0;
	#endif
	#if USER_GENERATING_FUNCTION
	  USER_OPTIONS->Generating_Distrib = user_generating_distrib;
	#endif
	#if USER_REANNEAL_COST
	  USER_OPTIONS->Reanneal_Cost_Function = user_reanneal_cost;
	#endif
	#if USER_REANNEAL_PARAMETERS
	  USER_OPTIONS->Reanneal_Params_Function = user_reanneal_params;
	#endif
}
/*C SimAnnParametersToAsaRun . . . . . . . . . . . . . . . . . . .destructor
**
**  DESCRIPTION
**        
**  REMARKS
**
*/
SimAnnParametersToAsaRun::~SimAnnParametersToAsaRun()
{
	#if OPTIONAL_DATA
		free (USER_OPTIONS->Asa_Data);
	#endif
	#if OPTIONAL_DATA_INT
		free (USER_OPTIONS->Asa_Data_Int);
	#endif
	#if USER_ASA_OUT
		free (USER_OPTIONS->Asa_Out_File);
	#endif
	#if ASA_SAMPLE
		free (USER_OPTIONS->Bias_Generated);
	#endif
	#if ASA_QUEUE
		free (USER_OPTIONS->Queue_Resolution);
	#endif
	#if ASA_RESOLUTION
		free (USER_OPTIONS->Coarse_Resolution);
	#endif

	#if USER_INITIAL_PARAMETERS_TEMPS
		free (USER_OPTIONS->User_Parameter_Temperature);
	#endif
	#if USER_INITIAL_COST_TEMP
		free (USER_OPTIONS->User_Cost_Temperature);
	#endif
	#if DELTA_PARAMETERS
		free (USER_OPTIONS->User_Delta_Parameter);
	#endif
	#if QUENCH_PARAMETERS
		free (USER_OPTIONS->User_Quench_Param_Scale);
	#endif
	#if QUENCH_COST
		free (USER_OPTIONS->User_Quench_Cost_Scale);
	#endif
	#if RATIO_TEMPERATURE_SCALES
		free (USER_OPTIONS->User_Temperature_Ratio);
	#endif

	free (USER_OPTIONS);
}



/*S SimAnnParametersToFunction
 */ 
/*C SimAnnParametersToFunction . . . . . . . . . . . . . . . . . . .constructor
**
**  DESCRIPTION
**        
**  REMARKS
**
*/
SimAnnParametersToFunction::SimAnnParametersToFunction()
: SimAnnHelpParameters()
{
  BaseDataInteger *dimHlp = new BaseDataInteger();
  dimHlp->SetValue(0);
	initParFct(dimHlp);
	delete dimHlp;
	
	TheOptMat = new BaseDataInstanceDoubleMatrix();
}
/*C SimAnnParametersToFunction . . . . . . . . . . . . . . . . . . .constructor
**
**  DESCRIPTION
**        
**  REMARKS
**
*/
SimAnnParametersToFunction::SimAnnParametersToFunction(BaseDataInteger *parDim,
  	    BaseDataSimAnnUpperLower *upLow, 
				BaseDataDoubleVector *parVec,
				BaseDataInstanceDoubleMatrix *dataMat,
				BaseDataDoubleVector *costTanVec,
				BaseDataDoubleVector *parIntRealVec)
: SimAnnHelpParameters()
{
  TheOptMat = (BaseDataInstanceDoubleMatrix *) PointerClone((BaseDataObject *) dataMat);
	initParFct(parDim);
  
	fillUpperLower(upLow);
	fillCost_Parameters(parVec);
	fillCost_Tangents(costTanVec);
	fillParameter_Int_Real(parIntRealVec);
}
/*C SimAnnParametersToFunction . . . . . . . . . . . . . . . . . . .destructor
**
**  DESCRIPTION
**        
**  REMARKS
**
*/
SimAnnParametersToFunction::~SimAnnParametersToFunction()
{
//	free (parameter_dimension);
	free (parameter_lower_bound);
	free (parameter_upper_bound);
	free (cost_parameters);
	free (parameter_int_real);
	free (cost_tangents);

  if(TheOptMat != NULL)
    delete TheOptMat;
  
  TheOptMat = NULL;
}
/*C SimAnnParametersToFunction::fillCost_Parameters . . . . . . . . .
**
**  DESCRIPTION
**        
**  REMARKS
**
*/
void SimAnnParametersToFunction::fillCost_Parameters(BaseDataDoubleVector *parVec)
{
  for (int i=0; i<*parameter_dimension; i++) {
    cost_parameters[i] = (parVec->CurrentVector())[i];
  }
}
/*C SimAnnParametersToFunction::fillCost_Tangents . . . . . . . . .
**
**  DESCRIPTION
**        
**  REMARKS
**
*/
void SimAnnParametersToFunction::fillCost_Tangents(BaseDataDoubleVector *costTanVec)
{
  for (int i=0; i<*parameter_dimension; i++) {
    cost_tangents[i] = (costTanVec->CurrentVector())[i];
  }
}
/*C SimAnnParametersToFunction::fillParameter_Int_Real . . . . . . . . .
**
**  DESCRIPTION
**        
**  REMARKS
**
*/
void SimAnnParametersToFunction::fillParameter_Int_Real(BaseDataDoubleVector *parIntRealVec)
{
  for (int i=0; i<*parameter_dimension; i++) {
    parameter_int_real[i] = (int) (parIntRealVec->CurrentVector())[i];
  }
}
/*C SimAnnParametersToFunction::fillCost_Parameters . . . . . . . . .
**
**  DESCRIPTION
**        
**  REMARKS
**
*/
void SimAnnParametersToFunction::fillUpperLower(BaseDataSimAnnUpperLower *upLow)
{
  VectorNumeric up = upLow->getUpper();
  VectorNumeric low = upLow->getLower();

  for (int i=0; i<*parameter_dimension; i++) {
    parameter_upper_bound[i] = up[i];
    parameter_lower_bound[i] = low[i];
  }

}
/*C SimAnnParametersToFunction::initParFct . . . . . . . . .
**
**  DESCRIPTION
**        
**  REMARKS
**
*/
void SimAnnParametersToFunction::initParFct(BaseDataInteger *parDim)
{
	if ((parameter_dimension =
		(ALLOC_INT *) calloc (1, sizeof (ALLOC_INT))) == NULL)
		exit (9);

  *parameter_dimension = parDim->GetValue();
  
	// the number of parameters for the cost function 
	#if OPTIONS_FILE_DATA
	  fscanf (ptr_options, "%s", read_option);
	  fscanf (ptr_options, "%s", read_option);

	#if INT_ALLOC
	  fscanf (ptr_options, "%d", &read_int);
	  *parameter_dimension = read_int;
	#else
	#if INT_LONG
	  fscanf (ptr_options, "%ld", &read_long);
	  *parameter_dimension = read_long;
	#else
	  fscanf (ptr_options, "%d", &read_int);
	  *parameter_dimension = read_int;
	#endif
	#endif

	#else // OPTIONS_FILE_DATA 
	#if ASA_TEST
	  *parameter_dimension = 4;
	#endif // ASA_TEST 
	#endif // OPTIONS_FILE_DATA 

	#if ASA_TEMPLATE_SAMPLE
	  *parameter_dimension = 2;
	#endif

	// allocate parameter minimum space 
	if ((parameter_lower_bound =
		(double *) calloc (*parameter_dimension, sizeof (double))
		) == NULL)
		exit (9);
	// allocate parameter maximum space 
	if ((parameter_upper_bound =
		(double *) calloc (*parameter_dimension, sizeof (double))
		) == NULL)
		exit (9);

	// allocate parameter initial values; the parameter final values
	//   will be stored here later 
	if ((cost_parameters =
		(double *) calloc (*parameter_dimension, sizeof (double))
		) == NULL)
		exit (9);
		
	// allocate the parameter types, real or integer 
	if ((parameter_int_real =
		(int *) calloc (*parameter_dimension, sizeof (int))
		) == NULL)
		exit (9);

	// allocate space for parameter cost_tangents -
	//   used for reannealing 
	if ((cost_tangents =
		(double *) calloc (*parameter_dimension, sizeof (double))
		) == NULL)
		exit (9);		
}



/*S BaseDataFunctionToOptimize
 */ 
/*F BaseDataFunctionToOptimize()  . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataFunctionToOptimize::BaseDataFunctionToOptimize()
{
  Identification = OPERATION_FCTTOOPT_ID;
  NameTag = OPERATION_FCTTOOPT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  
  TheParDim = new BaseDataInteger();
//  initKindOfTest();
  TheUpLow = new BaseDataSimAnnUpperLower();
  TheParVec = new BaseDataDoubleVector();
  TheOptMat = new BaseDataInstanceDoubleMatrix();
  TheCostTanVec = new BaseDataDoubleVector();
  TheParIntRealVec = new BaseDataDoubleVector();
  
  TheParToFct = new SimAnnParametersToFunction();
} 
/*F BaseDataFunctionToOptimize(data)  . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataFunctionToOptimize::BaseDataFunctionToOptimize(const BaseDataFunctionToOptimize& data)
: BaseDataOperation(data)
{
//  KindOfTest = (BaseDataInteger *) PointerClone((BaseDataObject *) data.KindOfTest);
  TheParDim = (BaseDataInteger *) PointerClone((BaseDataObject *) data.TheParDim);
  TheUpLow = (BaseDataSimAnnUpperLower *) PointerClone((BaseDataObject *) data.TheUpLow);
  TheParVec = (BaseDataDoubleVector *) PointerClone((BaseDataObject *) data.TheParVec);
  TheOptMat = (BaseDataInstanceDoubleMatrix *) PointerClone((BaseDataObject *) data.TheOptMat);
  TheCostTanVec = (BaseDataDoubleVector *) PointerClone((BaseDataObject *) data.TheCostTanVec);
  TheParIntRealVec = (BaseDataDoubleVector *) PointerClone((BaseDataObject *) data.TheParIntRealVec);

  createTheParToFct();
}
/*F BaseDataFunctionToOptimize. . . . . . . . . . . constructor
**
**  DESCRIPTION
**
**  REMARKS
*/
BaseDataFunctionToOptimize::BaseDataFunctionToOptimize(BaseDataInteger *parDim,
				BaseDataSimAnnUpperLower *upLow, 
				BaseDataDoubleVector *parVec,
				BaseDataInstanceDoubleMatrix *dataMat,
				BaseDataDoubleVector *costTanVec,
				BaseDataDoubleVector *parIntRealVec)
{
  TheParDim = (BaseDataInteger *) PointerClone((BaseDataObject *) parDim);
  TheUpLow = (BaseDataSimAnnUpperLower *) PointerClone((BaseDataObject *) upLow);
  TheParVec = (BaseDataDoubleVector *) PointerClone((BaseDataObject *) parVec);
  TheOptMat = (BaseDataInstanceDoubleMatrix *) PointerClone((BaseDataObject *) dataMat);
  TheCostTanVec = (BaseDataDoubleVector *) PointerClone((BaseDataObject *) costTanVec);
  TheParIntRealVec = (BaseDataDoubleVector *) PointerClone((BaseDataObject *) parIntRealVec);

//  initKindOfTest();

  Identification = OPERATION_FCTTOOPT_ID;
  NameTag = OPERATION_FCTTOOPT_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

  createTheParToFct();
}
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataFunctionToOptimize::~BaseDataFunctionToOptimize()
{
//  if(KindOfTest != NULL)
//    delete KindOfTest;
  if(TheParDim != NULL)
    delete TheParDim;
  if(TheUpLow != NULL)
    delete TheUpLow;
  if(TheParVec != NULL)
    delete TheParVec;
  if(TheOptMat != NULL)
    delete TheOptMat;
  if(TheCostTanVec != NULL)
    delete TheCostTanVec;
  if(TheParIntRealVec != NULL)
    delete TheParIntRealVec;
  if(TheParToFct != NULL)
    delete TheParToFct;
  
//  KindOfTest = NULL;
  TheParDim = NULL;
  TheUpLow = NULL;
  TheParVec = NULL;
  TheOptMat = NULL;
  TheCostTanVec = NULL;
  TheParIntRealVec = NULL;
  TheParToFct = NULL;
}
/*F initKindOfTest()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
//void BaseDataFunctionToOptimize::initKindOfTest(void)
//{
//  KindOfTest = new BaseDataInteger();
//  KindOfTest->SetValue(0);
//}
/*F setKindOfTest. . . . . . . . . . . BaseDataFunctionToOptimize
**
**  DESCRIPTION
**
**  REMARKS
**
*/
//void BaseDataFunctionToOptimize::setKindOfTest(BaseDataInteger *intObj)
//{
//  KindOfTest = (BaseDataInteger *) PointerClone((BaseDataObject *) intObj);
//}
/*F setTheOptMat. . . . . . . . . . . BaseDataFunctionToOptimize
**
**  DESCRIPTION
**
**  REMARKS
**
*/
void BaseDataFunctionToOptimize::setTheOptMat(BaseDataInstanceDoubleMatrix *optMat)
{
  TheOptMat = (BaseDataInstanceDoubleMatrix *) PointerClone((BaseDataObject *) optMat);
}
/*F createTheParToFct. . . . . . . . . . . BaseDataFunctionToOptimize
**
**  DESCRIPTION
**
**  REMARKS
**
*/
void BaseDataFunctionToOptimize::createTheParToFct(void)
{
  TheParToFct = new SimAnnParametersToFunction(TheParDim,
                                               TheUpLow, 
                                               TheParVec, 
                                               TheOptMat,
                                               TheCostTanVec,
                                               TheParIntRealVec);
}
/*F Read(in,objc) . . . . . . . . . . . Read in BaseDataFunctionToOptimize
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataFunctionToOptimize::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();

  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . Read in BaseDataFunctionToOptimize
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataFunctionToOptimize::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = true;
  
  if(objc->getDebugLevel() > 2) {
    cout << "Read in FunctionToOptimize:\n";
  }

  
  BaseDataOperation::Read(in,objc,name);
  //DataFunctionToOptimizeClass * objclass = (DataFunctionToOptimizeClass *) objc;


//  result = result && KindOfTest->Read(in,objc,name);
//  if(objc->getDebugLevel() > 2) {
//    cout << "Success: KindOfTest" << endl;
//  }
  
  result = result && TheParDim->Read(in,objc,name);
  if(objc->getDebugLevel() > 2) {
    cout << "Success: TheParDim" << endl;
  }
  
  result = result && TheUpLow->Read(in,objc,name);
  if(objc->getDebugLevel() > 2) {
    cout << "Success: TheUpLow" << endl;
  }

  result = result && TheParVec->Read(in,objc,name);
  if(objc->getDebugLevel() > 2) {
    cout << "Success: TheParVec" << endl;
  }

  result = result && TheOptMat->Read(in,objc,name);
  if(objc->getDebugLevel() > 2) {
    cout << "Success: TheOptMat" << endl;
  }

  result = result && TheCostTanVec->Read(in,objc,name);
  if(objc->getDebugLevel() > 2) {
    cout << "Success: TheCostTanVec" << endl;
  }

  result = result && TheParIntRealVec->Read(in,objc,name);
  if(objc->getDebugLevel() > 2) {
    cout << "Success: TheParIntRealVec" << endl;
  }


  TheParToFct = new SimAnnParametersToFunction (TheParDim,
                                         TheUpLow, 
                                         TheParVec, 
                                         TheOptMat,
                                         TheCostTanVec,
                                         TheParIntRealVec);
  return result;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . .  BaseDataFunctionToOptimize
**
**  DESCRIPTION
**    out: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataFunctionToOptimize::print(ostream& out) const
{
  BaseDataOperation::print(out);

  out << endl;
//  out << " KindOfTest: " << endl;
//  if(KindOfTest != NULL)
//    KindOfTest->print(out);
//  else
//    out << "  Not Given " << endl;

  out << " TheParDim: " << endl;
  if(TheParDim != NULL)
    TheParDim->print(out);
  else
    out << "  Not Given " << endl;

  out << endl;
  out << " TheUpLow: " << endl;
  if(TheUpLow != NULL)
    TheUpLow->print(out);
  else
    out << "  Not Given " << endl;

  out << endl;
  out << " TheParVec: " << endl;
  if(TheParVec != NULL)
    TheParVec->print(out);
  else
    out << "  Not Given " << endl;

  out << endl;
  out << " TheOptMat: " << endl;
  if(TheOptMat != NULL)
    TheOptMat->print(out);
  else
    out << "  Not Given " << endl;

  out << endl;
  out << " TheCostTanVec: " << endl;
  if(TheCostTanVec != NULL)
    TheCostTanVec->print(out);
  else
    out << "  Not Given " << endl;

  out << endl;
  out << " TheParIntRealVec: " << endl;
  if(TheParIntRealVec != NULL)
    TheParIntRealVec->print(out);
  else
    out << "  Not Given " << endl;

  out << endl;
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . .  BaseDataFunctionToOptimize
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataFunctionToOptimize::Clone()
{
  BaseDataFunctionToOptimize *obj = new BaseDataFunctionToOptimize(*this);
  return obj;
}
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . .  BaseDataFunctionToOptimize
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataFunctionToOptimize::CopyClone(Identify * obj)
{
  BaseDataFunctionToOptimize *objfull = (BaseDataFunctionToOptimize *) obj;
  *this = *objfull;
  BaseDataOperation::CopyClone(obj);
  
//  KindOfTest = (BaseDataInteger *) PointerClone((BaseDataObject *) objfull->KindOfTest);
  TheParDim = (BaseDataInteger *) PointerClone((BaseDataObject *) objfull->TheParDim);
  TheUpLow = (BaseDataSimAnnUpperLower *) PointerClone((BaseDataObject *) objfull->TheUpLow);
  TheParVec = (BaseDataDoubleVector *) PointerClone((BaseDataObject *) objfull->TheParVec);
  TheOptMat = (BaseDataInstanceDoubleMatrix *) PointerClone((BaseDataObject *) objfull->TheOptMat);
  TheCostTanVec = (BaseDataDoubleVector *) PointerClone((BaseDataObject *) objfull->TheCostTanVec);
  TheParIntRealVec = (BaseDataDoubleVector *) PointerClone((BaseDataObject *) objfull->TheParIntRealVec);

  createTheParToFct();
  // KindOfTest
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . .  BaseDataFunctionToOptimize
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataFunctionToOptimize::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::EncodeThis(buffer);

//  result = result && KindOfTest->EncodeThis(buffer);
  result = result && TheParDim->EncodeThis(buffer);
  result = result && TheUpLow->EncodeThis(buffer);
  result = result && TheParVec->EncodeThis(buffer);
  result = result && TheOptMat->EncodeThis(buffer);
  result = result && TheCostTanVec->EncodeThis(buffer);
  result = result && TheParIntRealVec->EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . .  BaseDataFunctionToOptimize
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataFunctionToOptimize::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataOperation::DecodeThis(buffer);

//  result = result && KindOfTest->DecodeThis(buffer);
  result = result && TheParDim->DecodeThis(buffer);
  result = result && TheUpLow->DecodeThis(buffer);
  result = result && TheParVec->DecodeThis(buffer);
  result = result && TheOptMat->DecodeThis(buffer);
  result = result && TheCostTanVec->DecodeThis(buffer);
  result = result && TheParIntRealVec->DecodeThis(buffer);
  
  createTheParToFct();

  return result;
}
/*F obj = operator()(x) . . . . . . . . . . . . . . . . . . BaseDataFunctionToOptimize
**
**  DESCRIPTION
**    x: The object to be operated on
**    obj: The result
**
**
**  REMARKS
**
*/
BaseDataReal BaseDataFunctionToOptimize::operator()(BaseDataDoubleVector *parToOpt, 
                         BaseDataInstanceDoubleMatrix *dataMat,
                         DataDoubleVectorClass *parToOptClass, 
                         DataInstanceDoubleMatrixClass *dataMatClass) 
{
	cout << "standard op(BaseDataDoubleVector *, BaseDataInstanceDoubleMatrix *) BaseDataFunctionToOptimize " << endl;
  BaseDataReal val;
  val.SetValue(0.0);
  
  return val;
}
/*F obj = testOptimizedResult . . . . . . . . . . . . . . . . . . BaseDataFunctionToOptimize
**
**  DESCRIPTION
**    x: The object to be operated on
**    obj: The result
**
**
**  REMARKS
**
*/
BaseDataInstanceDoubleMatrix * BaseDataFunctionToOptimize::testOptimizedResult(BaseDataDoubleVector *origPars, 
																	 BaseDataDoubleVector *optimizedPars, 
																	 BaseDataInstanceDoubleMatrix *dataMat)
{
	cout << "standard testOptimizedResult " << endl;
	return dataMat;
}
/*F obj = parameterDimension() . . . . . . . . . . . . . . . . . . BaseDataFunctionToOptimize
**
**  DESCRIPTION
**    x: The object to be operated on
**    obj: The result
**
**
**  REMARKS
**
*/
ALLOC_INT BaseDataFunctionToOptimize::parameterDimension()
{
  return TheParDim->GetValue();
}


/*S DataFunctionToOptimizeClass
 */ 
/*F DataFunctionToOptimizeClass() . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataFunctionToOptimizeClass::DataFunctionToOptimizeClass()
{
  Identification = OPERATION_FCTTOOPT_ID;
  SubClass = OPERATION_BASE_NAME;
  EncodeDecodeClass = OPERATION_FCTTOOPT_NAME;
} 
/*F DataFunctionToOptimizeClass(data) . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataFunctionToOptimizeClass::DataFunctionToOptimizeClass(const DataFunctionToOptimizeClass& data)
  : DataOperationClass(data)
{
} 
/*F DataFunctionToOptimizeClass(id,name,descr)  . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataFunctionToOptimizeClass::DataFunctionToOptimizeClass(const int id, 
                                                         const String& name,
                                                         const String& descr)
  : DataOperationClass(id,name,descr)

{
  SubClass = OPERATION_BASE_NAME;
  EncodeDecodeClass = OPERATION_FCTTOOPT_NAME;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . DataFunctionToOptimizeClass
**
**  DESCRIPTION
**    out: The output buffer
**
**  REMARKS
**
*/
ostream& DataFunctionToOptimizeClass::print(ostream& out) const
{
  DataOperationClass::print(out);
  return out;
}
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . DataFunctionToOptimizeClass
**
**  DESCRIPTION
**    in: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataNumOpMinusClass, there is no further information.
**
**  REMARKS
**
*/
bool DataFunctionToOptimizeClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataOperationClass::Read(in,set);
  return result;
}
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . DataFunctionToOptimizeClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataFunctionToOptimizeClass::CopyClone(Identify * objc)
{
  DataFunctionToOptimizeClass *objcfull = (DataFunctionToOptimizeClass*) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . DataFunctionToOptimizeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataFunctionToOptimizeClass::Clone()
{
  DataFunctionToOptimizeClass* id = new DataFunctionToOptimizeClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . DataFunctionToOptimizeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataFunctionToOptimizeClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . DataFunctionToOptimizeClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataFunctionToOptimizeClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataOperationClass::DecodeThis(buffer);
  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataFunctionToOptimizeClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataFunctionToOptimize();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . DataFunctionToOptimizeClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataFunctionToOptimizeClass*& obj)
{
  obj = new DataFunctionToOptimizeClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . .  BaseDataFunctionToOptimize
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataFunctionToOptimize*& obj)
{
  obj = new BaseDataFunctionToOptimize;
  return obj->DecodeThis(buffer);
}




/*S BaseDataTestFunction1
 */ 
/*F BaseDataTestFunction1()  . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataTestFunction1::BaseDataTestFunction1()
{
  Identification = OPERATION_FCTTOOPTTEST_ID;
  NameTag = OPERATION_FCTTOOPTTEST_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
  
//  TheParToFct = new SimAnnParametersToFunction();
} 
/*F BaseDataTestFunction1(data)  . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataTestFunction1::BaseDataTestFunction1(const BaseDataTestFunction1& data)
: BaseDataFunctionToOptimize(data)
{
}
/*F BaseDataTestFunction1. . . . . . . . . . . constructor
**
**  DESCRIPTION
**
**  REMARKS
*/
BaseDataTestFunction1::BaseDataTestFunction1(BaseDataInteger *parDim,
				BaseDataSimAnnUpperLower *upLow, 
				BaseDataDoubleVector *parVec,
				BaseDataInstanceDoubleMatrix *dataMat, 
				BaseDataDoubleVector *costTanVec,
				BaseDataDoubleVector *parIntRealVec)
:    BaseDataFunctionToOptimize(parDim,
        upLow, 
        parVec,
        dataMat,
        costTanVec,
        parIntRealVec)
{
  Identification = OPERATION_FCTTOOPTTEST_ID;
  NameTag = OPERATION_FCTTOOPTTEST_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;

}
/*F Read(in,objc) . . . . . . . . . . . Read in BaseDataTestFunction1
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataTestFunction1::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();

  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . Read in BaseDataTestFunction1
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataTestFunction1::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = true;
  
//  if(objc->getDebugLevel() > 2) {
    cout << "Read in TestFunction1:#####################################\n";
//  }

  
  BaseDataFunctionToOptimize::Read(in,objc,name);

  return result;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . .  BaseDataTestFunction1
**
**  DESCRIPTION
**    out: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataTestFunction1::print(ostream& out) const
{
  BaseDataFunctionToOptimize::print(out);

  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . .  BaseDataTestFunction1
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataTestFunction1::Clone()
{
  BaseDataTestFunction1 *obj = new BaseDataTestFunction1(*this);
  return obj;
}
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . .  BaseDataTestFunction1
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataTestFunction1::CopyClone(Identify * obj)
{
  BaseDataTestFunction1 *objfull = (BaseDataTestFunction1 *) obj;
  *this = *objfull;
  BaseDataFunctionToOptimize::CopyClone(obj);
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . .  BaseDataTestFunction1
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataTestFunction1::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataFunctionToOptimize::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . .  BaseDataTestFunction1
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataTestFunction1::DecodeThis(CommBuffer& buffer)
{
  bool result = BaseDataFunctionToOptimize::DecodeThis(buffer);
  return result;
}
/*F obj = operator()(x) . . . . . . . . . . . . . . . . . . BaseDataTestFunction1
**
**  DESCRIPTION
**    x: The object to be operated on
**    obj: The result
**
**
**  REMARKS
**
*/
BaseDataReal BaseDataTestFunction1::operator()(BaseDataDoubleVector *parToOpt, 
                         BaseDataInstanceDoubleMatrix *dataMat,
                         DataDoubleVectorClass *parToOptClass, 
                         DataInstanceDoubleMatrixClass *dataMatClass) 
{
    VectorNumeric *x = new VectorNumeric(parToOpt->CurrentVector());

//	cout << "------------------- TestFunction1 OPERATOR ------------------------" << endl;
    double q_n, d_i, s_i, t_i, z_i, c_r;
    int k_i;
    LONG_INT i, j;
    static LONG_INT funevals = 0;

    s_i = 0.2;
    t_i = 0.05;
    c_r = 0.15;

    q_n = 0.0;

    for (i = 0; i < 4; ++i) {
//    for (i = 0; i < *parameter_dimension; ++i) {
      j = i % 4;
      switch (j) {
        case 0:
          d_i = 1.0;
          break;
        case 1:
          d_i = 1000.0;
          break;
        case 2:
          d_i = 10.0;
          break;
        default:
          d_i = 100.0;
      }
      if ((*x)[i] > 0.0) {
        k_i = (int) ((*x)[i] / s_i + 0.5);
      }
      else if ((*x)[i] < 0.0) {
        k_i = (int) ((*x)[i] / s_i - 0.5);
      }
      else {
        k_i = 0;
      }

      if (fabs (k_i * s_i - (*x)[i]) < t_i) {
        if (k_i < 0) {
          z_i = k_i * s_i + t_i;
        }
        else if (k_i > 0)	{
          z_i = k_i * s_i - t_i;
        }
        else {
          z_i = 0.0;
        }
        q_n += c_r * d_i * z_i * z_i;
      }
      else {
        q_n += d_i * (*x)[i] * (*x)[i];
      }
    }

    funevals = funevals + 1;

#if TIME_CALC
    if ((PRINT_FREQUENCY > 0) && ((funevals % PRINT_FREQUENCY) == 0))	{
      fprintf (ptr_out, "funevals = %ld  ", funevals);
      print_time ("", ptr_out);
    }
#endif
    
//    cout << "returnvalue: " << q_n << endl;    

    BaseDataReal r;
    r.SetValue(q_n);
    
    delete x;
    return (r);
}


/*S DataTestFunction1Class
 */ 
/*F DataTestFunction1Class() . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataTestFunction1Class::DataTestFunction1Class()
{
  SubClass = OPERATION_FCTTOOPT_NAME;
  EncodeDecodeClass = OPERATION_FCTTOOPTTEST_NAME;
} 
/*F DataTestFunction1Class(data) . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataTestFunction1Class::DataTestFunction1Class(const DataTestFunction1Class& data)
  : DataFunctionToOptimizeClass(data)
{
} 
/*F DataTestFunction1Class(id,name,descr)  . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataTestFunction1Class::DataTestFunction1Class(const int id, 
                                               const String& name,
                                               const String& descr)
  : DataFunctionToOptimizeClass(id,name,descr)

{
  SubClass = OPERATION_FCTTOOPT_NAME;
  EncodeDecodeClass = OPERATION_FCTTOOPTTEST_NAME;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . DataTestFunction1Class
**
**  DESCRIPTION
**    out: The output buffer
**
**  REMARKS
**
*/
ostream& DataTestFunction1Class::print(ostream& out) const
{
  DataFunctionToOptimizeClass::print(out);
  return out;
}
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . DataTestFunction1Class
**
**  DESCRIPTION
**    in: The input buffer
**    set: The set of standard classes
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataNumOpMinusClass, there is no further information.
**
**  REMARKS
**
*/
bool DataTestFunction1Class::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataFunctionToOptimizeClass::Read(in,set);
  return result;
}
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . DataTestFunction1Class
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataTestFunction1Class::CopyClone(Identify * objc)
{
  DataTestFunction1Class *objcfull = (DataTestFunction1Class*) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . DataFunctionToOptimizeClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataTestFunction1Class::Clone()
{
  DataTestFunction1Class* id = new DataTestFunction1Class(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . DataTestFunction1Class
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataTestFunction1Class::EncodeThis(CommBuffer& buffer)
{
  bool result = DataFunctionToOptimizeClass::EncodeThis(buffer);
  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . DataTestFunction1Class
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataTestFunction1Class::DecodeThis(CommBuffer& buffer)
{
  bool result = DataFunctionToOptimizeClass::DecodeThis(buffer);
  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataTestFunction1Class::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataTestFunction1();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . DataTestFunction1Class
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataTestFunction1Class*& obj)
{
  obj = new DataTestFunction1Class;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . .  BaseDataTestFunction1
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataTestFunction1*& obj)
{
  obj = new BaseDataTestFunction1;
  return obj->DecodeThis(buffer);
}


/*S BaseDataSimAnnUpperLower
 */ 
/*F BaseDataSimAnnUpperLower()  . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSimAnnUpperLower::BaseDataSimAnnUpperLower()
{
  Identification = SIMANNUPPERLOWER_ID;
  NameTag = SIMANNUPPERLOWER_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataSimAnnUpperLower(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataSimAnnUpperLower::BaseDataSimAnnUpperLower(const BaseDataSimAnnUpperLower& data)
: BaseDataObject(data),
  Upper(data.Upper),
  Lower(data.Lower)
{
}
/*F BaseDataSimAnnUpperLower(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataSimAnnUpperLower::BaseDataSimAnnUpperLower(const VectorNumeric& upper,
                                                   const VectorNumeric& lower)
: BaseDataObject(),
  Upper(upper),
  Lower(lower)
{
  Identification = SIMANNUPPERLOWER_ID;
  NameTag = SIMANNUPPERLOWER_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
}
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataSimAnnUpperLower
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataSimAnnUpperLower::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  bool result = Read(in,objc,NameTag);
  
  return result;
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataSimAnnUpperLower
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataSimAnnUpperLower::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataObject::Read(in,objc,name);
  StreamObjectInput str(in,' ');
  
  result = result && Upper.Read(in);
  result = result && Lower.Read(in);
  
//  cout << "Names.Read: " << endl;
//  Names.clear();
//  String currName = str.ReadNext();
//  while(!(currName == "END")) {
//    Names.AddObject(currName);
//  }
  
  return result;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataSimAnnUpperLower
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataSimAnnUpperLower::print(ostream& out) const
{
  BaseDataObject::print(out);
  out << "\n";
  out << "Upper: ";
  Upper.print(out);
  out << "\n";
  out << "Lower: ";
  Lower.print(out);
  out << "\n";
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataSimAnnUpperLower
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataSimAnnUpperLower::Clone()
{
  BaseDataSimAnnUpperLower *obj = new BaseDataSimAnnUpperLower;
  obj->CopyClone(this);
  return obj;
}
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataSimAnnUpperLower
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataSimAnnUpperLower::CopyClone(Identify * obj)
{
  BaseDataSimAnnUpperLower *objfull = (BaseDataSimAnnUpperLower *) obj;
  
  *this = *objfull;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSimAnnUpperLower
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSimAnnUpperLower::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataObject::EncodeThis(buffer);
  result = result && Upper.EncodeThis(buffer);
  result = result && Lower.EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSimAnnUpperLower
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSimAnnUpperLower::DecodeThis(CommBuffer& buffer)
{
  cout << "Decode: SimAnn UpperLower\n";
  
  bool result = BaseDataObject::DecodeThis(buffer);
  if(result)
    cout << "Success:\n";
  else
    cout << "Not Successful\n";

  result = result && Upper.DecodeThis(buffer);
  if(result)
    cout << "Success:\n";
  else
    cout << "Not Successful\n";

  result = result && Lower.DecodeThis(buffer);
  if(result)
    cout << "Success:\n";
  else
    cout << "Not Successful\n";

  return result;
}



/*S DataSimAnnUpperLowerClass
 */
/*F DataSimAnnUpperLowerClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataSimAnnUpperLowerClass::DataSimAnnUpperLowerClass()
{
  NameTag = SIMANNUPPERLOWER_NAME;
  Identification = SIMANNUPPERLOWER_ID;
  SubClass = COREOBJECTS_BASE_NAME;
  EncodeDecodeClass = SIMANNUPPERLOWER_NAME;
} 
/*F DataSimAnnUpperLowerClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataSimAnnUpperLowerClass::DataSimAnnUpperLowerClass(const DataSimAnnUpperLowerClass& data)
  : DataObjectClass(data)
{
} 
/*F DataSimAnnUpperLowerClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataSimAnnUpperLowerClass::DataSimAnnUpperLowerClass(const int id, 
                                                     const String& name,
                                                     const String& descr)
  : DataObjectClass(id,name,descr)
{
  EncodeDecodeClass = SIMANNUPPERLOWER_NAME;
  SubClass = COREOBJECTS_BASE_NAME;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataSimAnnUpperLowerClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataSimAnnUpperLowerClass::print(ostream& out) const
{
  DataObjectClass::print(out);
  out << NameTag << "  ";
  // the rest
           
  return out;
}
/*F in1 = Read(in,set)  . . . . . . . . . . . . . . . . . . . . . DataSimAnnUpperLowerClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**  REMARKS
**
*/
bool DataSimAnnUpperLowerClass::Read(istream& in, DataSetOfObjectsClass& set)
{
  bool result = DataObjectClass::Read(in,set);

  return result;
}
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataSimAnnUpperLowerClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataSimAnnUpperLowerClass::CopyClone(Identify *  objc)
{
  DataSimAnnUpperLowerClass *objcfull = (DataSimAnnUpperLowerClass*) objc;
      
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataSimAnnUpperLowerClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataSimAnnUpperLowerClass::Clone()
{
  DataSimAnnUpperLowerClass* id = new DataSimAnnUpperLowerClass(*this);
  return (Identify *) id;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataSimAnnUpperLowerClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSimAnnUpperLowerClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::EncodeThis(buffer);
  // The rest: result = result && Encode(buffer,-------);
  // result = result && EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataSimAnnUpperLowerClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSimAnnUpperLowerClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataObjectClass::DecodeThis(buffer);

  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataSimAnnUpperLowerClass::BaseDataObjectExample()
{ 
  return (BaseDataObject *) new BaseDataSimAnnUpperLower();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataSimAnnUpperLowerClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataSimAnnUpperLowerClass*& obj)
{
  obj = new DataSimAnnUpperLowerClass;
  return obj->DecodeThis(buffer);
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataSimAnnUpperLowerClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataSimAnnUpperLower*& obj)
{
  obj = new BaseDataSimAnnUpperLower;
  return obj->DecodeThis(buffer);
}
/*F vect = getUpper()  . . . . . . . . . . . . . .  BaseDataSimAnnUpperLower
**
**  DESCRIPTION
**    vect: The current
**
**  REMARKS
**
*/
VectorNumeric BaseDataSimAnnUpperLower::getUpper()
{
  return Upper;
}
/*F vect = getLower()  . . . . . . . . . . . . . .  BaseDataSimAnnUpperLower
**
**  DESCRIPTION
**    vect: The current
**
**  REMARKS
**
*/
VectorNumeric BaseDataSimAnnUpperLower::getLower()
{
  return Lower;
}



/*S SimulatedAnnealing
 */ 
/*F SimulatedAnnealing. . . . . . . . . .. constructor
**
**  DESCRIPTION
**
**  REMARKS
*/
SimulatedAnnealing::SimulatedAnnealing(BaseDataFunctionToOptimize* fct) 
{
  fToUse = (BaseDataFunctionToOptimize *) PointerClone((BaseDataObject *) fct);
  initSA();
}
/*F SimulatedAnnealing. . . . . . . . . .. destructor
**
**  DESCRIPTION
**
**  REMARKS
*/
SimulatedAnnealing::~SimulatedAnnealing()
{
	//	last output after all of asa
	fprintf (ptr_out, "exit code = %d\n", *exit_code);
	fprintf (ptr_out, "final cost value = %12.7g\n", cost_value);
	fprintf (ptr_out, "parameter\tvalue\n");
	
	for (n_param = 0; n_param < *(fToUse->TheParToFct->parameter_dimension); ++n_param)
	{
			  fprintf (ptr_out,
	#if INT_ALLOC
				   "%d\t\t%12.7g\n",
	#else
	#if INT_LONG
				   "%ld\t\t%12.7g\n",
	#else
				   "%d\t\t%12.7g\n",
	#endif
	#endif
				   n_param, fToUse->TheParToFct->cost_parameters[n_param]);
	}

	#if TIME_CALC
		  // print ending time 
		  print_time ("end", ptr_out);
	#endif
	#if ASA_TEMPLATE_SAMPLE
	  ptr_asa = fopen ("myASA_out", "r");
	  sample (ptr_out, ptr_asa);
	#endif

	  // close all files 
	  fclose (ptr_out);

	if (USER_OPTIONS->Curvature_0 == FALSE || USER_OPTIONS->Curvature_0 == -1)
		free (cost_curvature);

	free (exit_code);
	free (cost_flag);
	free (rand_seed);

	/*
	#if ASA_LIB
	#else
	cout << "Should not get here" << endl;
	  exit (0);
	  // NOTREACHED 
	#endif
	*/
  if (fToUse != NULL)
    delete fToUse;
  if(parAsaRun != NULL)
    delete parAsaRun;
    
  fToUse = NULL;
  parAsaRun = NULL;
}
/*F SimulatedAnnealing::initSA
**
**  DESCRIPTION
**
**  REMARKS
*/
void SimulatedAnnealing::initSA(void)
{
  parAsaRun = new SimAnnParametersToAsaRun();
  USER_OPTIONS = parAsaRun->USER_OPTIONS;
  
//	#if ASA_TEMPLATE_MULTIPLE
//	  asa_file[0] = asa_file[2] = 'a';
//	  asa_file[1] = 's';
//	  asa_file[3] = asa_file[5] = '_';
//	  asa_file[4] = 'x';
//	  asa_file[6] = 'y';
//	  asa_file[7] = '\0';
//	#endif // ASA_TEMPLATE_MULTIPLE 

	#if ASA_TEMPLATE_ASA_OUT_PID
	  pid_file[0] = 'u';
	  pid_file[1] = 's';
	  pid_file[2] = 'e';
	  pid_file[3] = 'r';
	  pid_file[4] = '_';
	  pid_file[5] = 'o';
	  pid_file[6] = 'u';
	  pid_file[7] = 't';
	  pid_file[8] = '_';
	  pid_file[14] = '\0';

	  pid_int = getpid ();
	  if (pid_int < 0)
		{
		  pid_int = -pid_int;
		}

	  if (pid_int > 99999)
		{
		  pid_file[8] = '1';
		  pid_int = pid_int % 100000;
		}

	  if (pid_int < 10 && pid_int > 0)
		{
		  pid_file[9] = '0';
		  pid_file[10] = '0';
		  pid_file[11] = '0';
		  pid_file[12] = '0';
		  pid_file[13] = '0' + pid_int;
		}
	  else if (pid_int >= 10 && pid_int < 100)
		{
		  pid_file[9] = '0';
		  pid_file[10] = '0';
		  pid_file[11] = '0';
		  pid_file[12] = '0' + (int) (pid_int / 10);
		  pid_file[13] = '0' + (pid_int % 10);
		}
	  else if (pid_int >= 100 && pid_int < 1000)
		{
		  pid_file[9] = '0';
		  pid_file[10] = '0';
		  pid_file[11] = '0' + (int) (pid_int / 100);
		  pid_file[12] = '0' + (int) ((pid_int % 100) / 10);
		  pid_file[13] = '0' + ((pid_int % 100) % 10);
		}
	  else if (pid_int >= 1000 && pid_int < 10000)
		{
		  pid_file[9] = '0';
		  pid_file[10] = '0' + (int) (pid_int / 1000);
		  pid_file[11] = '0' + (int) ((pid_int % 1000) / 100);
		  pid_file[12] = '0' + (int) (((pid_int % 1000) % 100) / 10);
		  pid_file[13] = '0' + (((pid_int % 1000) % 100) % 10);
		}
	  else if (pid_int >= 10000 && pid_int <= 99999)
		{
		  pid_file[9] = '0' + (int) (pid_int / 10000);
		  pid_file[10] = '0' + (int) ((pid_int % 10000) / 1000);
		  pid_file[11] = '0' + (int) (((pid_int % 10000) % 1000) / 100);
		  pid_file[12] = '0' + (int) (((pid_int % 10000) % 1000) % 100 / 10);
		  pid_file[13] = '0' + ((((pid_int % 10000) % 1000) % 100) % 10);
		}
	  else
		{
		  pid_file[8] = '0';
		  pid_file[9] = '0';
		  pid_file[10] = '0';
		  pid_file[11] = '0';
		  pid_file[12] = '0';
		  pid_file[13] = '0';
		}
	  ptr_out = fopen (pid_file, "w");
	#else // ASA_TEMPLATE_ASA_OUT_PID 

	  // open the output file 
	#if ASA_SAVE
	  ptr_out = fopen ("myUser_out", "a");
	#else
	  // set "w" to "a" to save data from multiple runs 
	  ptr_out = fopen ("myUser_out", "w");
	#endif

	#endif // ASA_TEMPLATE_ASA_OUT_PID 

	  // use this instead if you want output to stdout 
	#if FALSE
	  ptr_out = stdout;
	#endif
	  fprintf (ptr_out, "%s\n\n", USER_ID);


	#if TIME_CALC
	  // print starting time 
	  print_time ("start", ptr_out);
	#endif
	  fflush (ptr_out);

	if ((rand_seed =
	   (LONG_INT *) calloc (1, sizeof (LONG_INT))) == NULL)
		exit (9);
	
	  // first value of *rand_seed 
	#if ASA_LIB
	  *rand_seed = (asa_rand_seed ? *asa_rand_seed : (LONG_INT) 696969);
	#else
	  *rand_seed = 696969;
	#endif


	  // initialize random number generator with first call 
	  randflt (rand_seed);


	if ((exit_code = (int *) calloc (1, sizeof (int))) == NULL)
		exit (9);
	if ((cost_flag = (int *) calloc (1, sizeof (int))) == NULL)
		exit (9);

	if (USER_OPTIONS->Curvature_0 == FALSE || USER_OPTIONS->Curvature_0 == -1)
	{
		  // allocate space for parameter cost_curvatures/covariance 
		  if ((cost_curvature =
		   (double *) calloc ((*(fToUse->TheParToFct->parameter_dimension)) *
              					  (*(fToUse->TheParToFct->parameter_dimension)),
                          sizeof (double))) == NULL)
		  exit (9);
	}
	else
	{
		  cost_curvature = (double *) NULL;
	}


	#if MY_TEMPLATE			// MY_TEMPLATE_dim 
	  // If not using OPTIONS_FILE_DATA or data read from asa_opt,
	  //   insert the number of parameters for the cost_function 
	#endif // MY_TEMPLATE dim 


	#if MY_TEMPLATE			// MY_TEMPLATE_pre_initialize 
	  // last changes before entering initialize_parameters() 
	#endif

	//---------------------------------------------------
	  initialize_parameters (fToUse->TheParToFct->cost_parameters,
				 fToUse->TheParToFct->parameter_lower_bound,
				 fToUse->TheParToFct->parameter_upper_bound,
				 fToUse->TheParToFct->cost_tangents,
				 cost_curvature,
				 fToUse->TheParToFct->parameter_dimension,
				 fToUse->TheParToFct->parameter_int_real,
	#if OPTIONS_FILE_DATA
				 ptr_options,
	#endif
				 USER_OPTIONS);
	//---------------------------------------------------

	#if OPTIONS_FILE
	  fclose (ptr_options);
	#endif

	  // optimize the cost_function, returning the results in
	  //   cost_value and cost_parameters 
/*
	#if ASA_TEMPLATE_MULTIPLE
	  // multiple asa() quenched calls + multiple asa_out files
	  //   (To get longer quenched runs, decrease SMALL_FLOAT.) 
	  for (n_asa = 1; n_asa <= *parameter_dimension; n_asa++)
		{
		  asa_file[4] = 'A' + n_asa - 1;
		  USER_OPTIONS->User_Quench_Cost_Scale[0] = (double) n_asa;
		  for (index = 0; index < *parameter_dimension; ++index)
		USER_OPTIONS->User_Quench_Param_Scale[index] =
		  (double) n_asa;
		  for (n_trajectory = 0; n_trajectory < 3; ++n_trajectory)
		{
		  asa_file[6] = 'a' + n_trajectory;
		  strcpy (USER_OPTIONS->Asa_Out_File, asa_file);
	#endif
*/
	#if ASA_TEMPLATE_ASA_OUT_PID
		  pid_file[0] = 'a';
		  pid_file[1] = 's';
		  pid_file[2] = 'a';
		  pid_file[3] = '_';
		  pid_file[4] = 'o';
		  pid_file[5] = 'u';
		  pid_file[6] = 't';
		  pid_file[7] = '_';

		  pid_int = getpid ();
		  if (pid_int < 0)
			{
			  pid_file[7] = '0';
			  pid_int = -pid_int;
			}

		  strcpy (USER_OPTIONS->Asa_Out_File, pid_file);
	#endif
	
}
/*F SimulatedAnnealing::calculate. . . . . . . . . .
**
**  DESCRIPTION
**
**  REMARKS
*/
double SimulatedAnnealing::calculate() {
  cost_value = asa(cstFunctionIntern, randflt);
  return cost_value;
}
/*F asa. . . . . . . . . .. 
**
**  DESCRIPTION
**       This procedure implements the full ASA function optimization.
**
**  REMARKS
*/
double SimulatedAnnealing::
asa (double (*user_cost_function) (double *),
     double (*user_random_generator) (LONG_INT *))
{
  LONG_INT * seed;
	if ((seed =
	   (LONG_INT *) calloc (1, sizeof (LONG_INT))) == NULL)
		exit (9);
	seed = rand_seed;

  int *exit_status;
	if ((exit_status = (int *) calloc (1, sizeof (int))) == NULL)
		exit (9);
	exit_status = exit_code;

  int *valid_state_generated_flag;
	if ((valid_state_generated_flag = (int *) calloc (1, sizeof (int))) == NULL)
		exit (9);
	valid_state_generated_flag = cost_flag;

  double *parameter_minimum;
	if ((parameter_minimum =
		(double *) calloc (*(fToUse->TheParToFct->parameter_dimension), sizeof (double))
		) == NULL)
		exit (9);
	parameter_minimum = fToUse->TheParToFct->parameter_lower_bound;

  double *parameter_maximum;
	if ((parameter_maximum =
		(double *) calloc (*(fToUse->TheParToFct->parameter_dimension), sizeof (double))
		) == NULL)
		exit (9);
	parameter_maximum = fToUse->TheParToFct->parameter_upper_bound;

  double *parameter_initial_final;
	if ((parameter_initial_final =
		(double *) calloc (*(fToUse->TheParToFct->parameter_dimension), sizeof (double))
		) == NULL)
		exit (9);
	parameter_initial_final = fToUse->TheParToFct->cost_parameters;

  double *tangents;
	if ((tangents =
		(double *) calloc (*(fToUse->TheParToFct->parameter_dimension), sizeof (double))
		) == NULL)
		exit (9);
	tangents = fToUse->TheParToFct->cost_tangents;

  double *curvature;
	if ((cost_curvature =
		(double *) calloc ((*(fToUse->TheParToFct->parameter_dimension)) *
		(*(fToUse->TheParToFct->parameter_dimension)),
		sizeof (double))) == NULL)
		exit (9);
	curvature = cost_curvature;
	
	ALLOC_INT * number_parameters;
 	if ((number_parameters =
		(ALLOC_INT *) calloc (1, sizeof (ALLOC_INT))) == NULL)
		exit (9);
	number_parameters = fToUse->TheParToFct->parameter_dimension;
	
	int *parameter_type;
	if ((parameter_type =
		(int *) calloc (*(fToUse->TheParToFct->parameter_dimension), sizeof (int))
		) == NULL)
		exit (9);
	parameter_type = fToUse->TheParToFct->parameter_int_real;

	USER_DEFINES * OPTIONS = USER_OPTIONS;
	if ((OPTIONS 
		=	(USER_DEFINES *) calloc (1, sizeof (USER_DEFINES))) == NULL)
		exit (9);
	OPTIONS = USER_OPTIONS;



#if USER_INITIAL_COST_TEMP
#if USER_REANNEAL_COST
#else
  int index_cost_constraint;	/* index cost functions averaged */
#endif /* USER_REANNEAL_COST */
#else /* USER_INITIAL_COST_TEMP */
  int index_cost_constraint;	/* index cost functions averaged */
#endif /* USER_INITIAL_COST_TEMP */

  int index_cost_repeat,	/* test OPTIONS->Cost_Precision when =
				   OPTIONS->Maximum_Cost_Repeat */
    tmp_var_int, tmp_var_int1, tmp_var_int2;	/* temporary integers */

  ALLOC_INT index_v,		/* iteration index */
   *start_sequence;		/* initial OPTIONS->Sequential_Parameters
				   used if >= 0 */
  double final_cost,		/* best cost to return to user */
    tmp_var_db, tmp_var_db1, tmp_var_db2;	/* temporary doubles */
  int *curvature_flag;
  FILE *ptr_asa_out;		/* file ptr to output file */

  /* The 3 states that are kept track of during the annealing process */
  STATE *current_generated_state, *last_saved_state, *best_generated_state;

#if ASA_PARALLEL
  /* parallel generated states */
  STATE *gener_block_state;
#endif

#if ASA_SAVE
  FILE *ptr_save;
  int asa_read;
#endif

  int immediate_flag;		/* save Immediate_Exit */

  /* The array of tangents (absolute value of the numerical derivatives),
     and the maximum |tangent| of the array */
  double *maximum_tangent;

  /* ratio of acceptances to generated points - determines when to
     test/reanneal */
  double *accepted_to_generated_ratio;

  /* temperature parameters */
  double temperature_scale, *temperature_scale_parameters;
  /* relative scalings of cost and parameters to temperature_scale */
  double *temperature_scale_cost;
  double *current_user_parameter_temp;
  double *initial_user_parameter_temp;
  double *current_cost_temperature;
  double *initial_cost_temperature;
  double log_new_temperature_ratio;	/* current *temp = initial *temp *
					   exp(log_new_temperature_ratio) */
  ALLOC_INT *index_exit_v;	/* information for asa_exit */

  /* counts of generated states and acceptances */
  LONG_INT *index_parameter_generations;
  LONG_INT *number_generated, *best_number_generated_saved;
  LONG_INT *recent_number_generated, *number_accepted;
  LONG_INT *recent_number_acceptances, *index_cost_acceptances;
  LONG_INT *number_acceptances_saved, *best_number_accepted_saved;

  /* Flag indicates that the parameters generated were
     invalid according to the cost function validity criteria. */
  LONG_INT *number_invalid_generated_states;
  LONG_INT repeated_invalid_states;

#if ASA_QUEUE
  int queue_new;		/* flag to add new entry */
  int *save_queue_flag;		/* save valid_state_generated_flag */
  LONG_INT queue;		/* index of queue */
  LONG_INT queue_v;		/* index of parameters in queue */
  LONG_INT save_queue_test;	/* test if all parameters are present */
  LONG_INT save_queue;		/* last filled position in queue */
  LONG_INT save_queue_indx;	/* current position in queue */
  double *save_queue_cost, *save_queue_param;	/* saved states */
#endif

#if ASA_PARALLEL
  LONG_INT index_parallel;	/* count of parallel generated states */
  LONG_INT parallel_generated;	/* saved *recent_number_generated */
  LONG_INT parallel_block_max;	/* saved OPTIONS->Gener_Block_Max */
#endif

  /* used to index repeated and recursive calls to asa */
  /* This assumes that multiple calls (>= 1) _or_ recursive
     calls are being made to asa */
  static int asa_open = FALSE;
  static int number_asa_open = 0;
  static int recursive_asa_open = 0;

  /* initializations */

  if ((curvature_flag =
       (int *) calloc (1, sizeof (int))) == NULL)
      exit (9);
  if ((maximum_tangent =
       (double *) calloc (1, sizeof (double))) == NULL)
      exit (9);
  if ((accepted_to_generated_ratio =
       (double *) calloc (1, sizeof (double))) == NULL)
      exit (9);
  if ((temperature_scale_cost =
       (double *) calloc (1, sizeof (double))) == NULL)
      exit (9);
  if ((current_cost_temperature =
       (double *) calloc (1, sizeof (double))) == NULL)
      exit (9);
  if ((initial_cost_temperature =
       (double *) calloc (1, sizeof (double))) == NULL)
      exit (9);
  if ((index_exit_v =
       (ALLOC_INT *) calloc (1, sizeof (ALLOC_INT))) == NULL)
    exit (9);
  if ((start_sequence =
       (ALLOC_INT *) calloc (1, sizeof (ALLOC_INT))) == NULL)
    exit (9);
  if ((number_generated =
       (LONG_INT *) calloc (1, sizeof (LONG_INT))) == NULL)
    exit (9);
  if ((best_number_generated_saved =
       (LONG_INT *) calloc (1, sizeof (LONG_INT))) == NULL)
    exit (9);
  if ((recent_number_generated =
       (LONG_INT *) calloc (1, sizeof (LONG_INT))) == NULL)
    exit (9);
  if ((number_accepted =
       (LONG_INT *) calloc (1, sizeof (LONG_INT))) == NULL)
    exit (9);
  if ((recent_number_acceptances =
       (LONG_INT *) calloc (1, sizeof (LONG_INT))) == NULL)
    exit (9);
  if ((index_cost_acceptances =
       (LONG_INT *) calloc (1, sizeof (LONG_INT))) == NULL)
    exit (9);
  if ((number_acceptances_saved =
       (LONG_INT *) calloc (1, sizeof (LONG_INT))) == NULL)
    exit (9);
  if ((best_number_accepted_saved =
       (LONG_INT *) calloc (1, sizeof (LONG_INT))) == NULL)
    exit (9);
  if ((number_invalid_generated_states =
       (LONG_INT *) calloc (1, sizeof (LONG_INT))) == NULL)
    exit (9);

  if ((current_generated_state =
       (STATE *) calloc (1, sizeof (STATE))) == NULL)
    exit (9);
  if ((last_saved_state =
       (STATE *) calloc (1, sizeof (STATE))) == NULL)
    exit (9);
  if ((best_generated_state =
       (STATE *) calloc (1, sizeof (STATE))) == NULL)
    exit (9);
#if ASA_PARALLEL
  if ((gener_block_state =
       (STATE *) calloc (OPTIONS->Gener_Block_Max, sizeof (STATE))) == NULL)
    exit (9);
#endif

#if ASA_PRINT
  ;
#else
  ptr_asa_out = (FILE *) NULL;
#endif

  OPTIONS->Immediate_Exit = FALSE;

  if (asa_open == FALSE)
    {
      asa_open = TRUE;
      ++number_asa_open;
#if ASA_PRINT
      if (number_asa_open == 1)
	{
	  /* open the output file */
#if USER_ASA_OUT
	  if (!strcmp (OPTIONS->Asa_Out_File, "STDOUT"))
	    {
	      ptr_asa_out = stdout;
	    }
	  else
	    {
#if ASA_SAVE
	      ptr_asa_out = fopen (OPTIONS->Asa_Out_File, "a");
#else
	      ptr_asa_out = fopen (OPTIONS->Asa_Out_File, "w");
#endif
	    }
#else /* USER_ASA_OUT */
	  if (!strcmp (ASA_OUT, "STDOUT"))
	    {
	      ptr_asa_out = stdout;
	    }
	  else
	    {
#if ASA_SAVE
	      ptr_asa_out = fopen (ASA_OUT, "a");
#else
	      ptr_asa_out = fopen (ASA_OUT, "w");
#endif
	    }
#endif /* USER_ASA_OUT */
	}
      else
	{
#if USER_ASA_OUT
	  if (!strcmp (OPTIONS->Asa_Out_File, "STDOUT"))
	    {
	      ptr_asa_out = stdout;
	    }
	  else
	    {
	      ptr_asa_out = fopen (OPTIONS->Asa_Out_File, "a");
	    }
#else
	  if (!strcmp (ASA_OUT, "STDOUT"))
	    {
	      ptr_asa_out = stdout;
	    }
	  else
	    {
	      ptr_asa_out = fopen (ASA_OUT, "a");
	    }
#endif
	  fprintf (ptr_asa_out, "\n\n\t\t number_asa_open = %d\n",
		   number_asa_open);
	}
#endif /* ASA_PRINT */
    }
  else
    {
      ++recursive_asa_open;
#if ASA_PRINT
      if (recursive_asa_open == 1)
	{
	  /* open the output file */
#if ASA_SAVE
#if USER_ASA_OUT
	  if (!strcmp (OPTIONS->Asa_Out_File, "STDOUT"))
	    {
	      ptr_asa_out = stdout;
	    }
	  else
	    {
	      ptr_asa_out = fopen (OPTIONS->Asa_Out_File, "a");
	    }
#else
	  if (!strcmp (ASA_OUT, "STDOUT"))
	    {
	      ptr_asa_out = stdout;
	    }
	  else
	    {
	      ptr_asa_out = fopen (ASA_OUT, "a");
	    }
#endif
#else /* ASA_SAVE */
#if USER_ASA_OUT
	  if (!strcmp (OPTIONS->Asa_Out_File, "STDOUT"))
	    {
	      ptr_asa_out = stdout;
	    }
	  else
	    {
	      ptr_asa_out = fopen (OPTIONS->Asa_Out_File, "w");
	    }
#else
	  if (!strcmp (ASA_OUT, "STDOUT"))
	    {
	      ptr_asa_out = stdout;
	    }
	  else
	    {
	      ptr_asa_out = fopen (ASA_OUT, "w");
	    }
#endif
#endif /* ASA_SAVE */
	}
      else
	{
#if USER_ASA_OUT
	  if (!strcmp (OPTIONS->Asa_Out_File, "STDOUT"))
	    {
	      ptr_asa_out = stdout;
	    }
	  else
	    {
	      ptr_asa_out = fopen (OPTIONS->Asa_Out_File, "a");
	    }
#else
	  if (!strcmp (ASA_OUT, "STDOUT"))
	    {
	      ptr_asa_out = stdout;
	    }
	  else
	    {
	      ptr_asa_out = fopen (ASA_OUT, "a");
	    }
#endif
	  fprintf (ptr_asa_out, "\n\n\t\t recursive_asa_open = %d\n",
		   recursive_asa_open);
	}
#endif /* ASA_PRINT */
    }

#if ASA_PRINT
  /* print header information as defined by user */
  print_asa_options (ptr_asa_out, OPTIONS);

#if TIME_CALC
  /* print starting time */
  print_time ("start_asa", ptr_asa_out);
#endif
  fflush (ptr_asa_out);
#endif /* ASA_PRINT */

  /* set indices and counts to 0 */
  *best_number_generated_saved =
    *number_generated =
    *recent_number_generated =
    *recent_number_acceptances = 0;
  *index_cost_acceptances =
    *best_number_accepted_saved =
    *number_accepted =
    *number_acceptances_saved = 0;
  index_cost_repeat = 0;

  OPTIONS->N_Accepted = *number_accepted;
  OPTIONS->N_Generated = *number_generated;

#if ASA_SAMPLE
  OPTIONS->N_Generated = 0;
  OPTIONS->Average_Weights = 1.0;
#endif

  /* do not calculate curvatures initially */
  *curvature_flag = FALSE;

  /* allocate storage for all parameters */
  if ((current_generated_state->parameter =
       (double *) calloc (*number_parameters, sizeof (double))
      ) == NULL)
      exit (9);
  if ((last_saved_state->parameter =
       (double *) calloc (*number_parameters, sizeof (double))
      ) == NULL)
      exit (9);
  if ((best_generated_state->parameter =
       (double *) calloc (*number_parameters, sizeof (double))
      ) == NULL)
      exit (9);
#if ASA_PARALLEL
  parallel_block_max = OPTIONS->Gener_Block_Max;
  parallel_generated = OPTIONS->Gener_Block;

  for (index_parallel = 0; index_parallel < parallel_block_max;
       ++index_parallel)
    {
      if ((gener_block_state[index_parallel].parameter =
	   (double *) calloc (*number_parameters, sizeof (double))
	  ) == NULL)
	  exit (9);
    }
#endif

  OPTIONS->Best_Cost = &(best_generated_state->cost);
  OPTIONS->Best_Parameters = best_generated_state->parameter;
  OPTIONS->Last_Cost = &(last_saved_state->cost);
  OPTIONS->Last_Parameters = last_saved_state->parameter;

  if ((initial_user_parameter_temp =
       (double *) calloc (*number_parameters, sizeof (double))
      ) == NULL)
      exit (9);
  if ((index_parameter_generations =
       (LONG_INT *) calloc (*number_parameters, sizeof (LONG_INT))
      ) == NULL)
    exit (9);

  /* set all temperatures */
  if ((current_user_parameter_temp =
       (double *) calloc (*number_parameters, sizeof (double))
      ) == NULL)
      exit (9);
#if USER_INITIAL_PARAMETERS_TEMPS
  VFOR (index_v)
    current_user_parameter_temp[index_v] =
    initial_user_parameter_temp[index_v] =
    OPTIONS->User_Parameter_Temperature[index_v];
#else
  VFOR (index_v)
    current_user_parameter_temp[index_v] =
    initial_user_parameter_temp[index_v] =
    OPTIONS->Initial_Parameter_Temperature;
#endif

  if ((temperature_scale_parameters =
       (double *) calloc (*number_parameters, sizeof (double))
      ) == NULL)
      exit (9);

#if USER_INITIAL_COST_TEMP
#if USER_ACCEPTANCE_TEST
  OPTIONS->Cost_Temp_Curr =
    OPTIONS->Cost_Temp_Init =
#endif
    *initial_cost_temperature = *current_cost_temperature =
    OPTIONS->User_Cost_Temperature[0];
#endif

  /* set parameters to the initial parameter values */
  VFOR (index_v)
    last_saved_state->parameter[index_v] =
    current_generated_state->parameter[index_v] =
    parameter_initial_final[index_v];
#if USER_ACCEPTANCE_TEST
  OPTIONS->Random_Seed = seed;
  OPTIONS->Random_Seed[0] = *seed;
  OPTIONS->User_Acceptance_Flag = TRUE;
  OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif

#if ASA_PRINT
#if INT_LONG
  fprintf (ptr_asa_out, "Initial Random Seed = %ld\n\n", *seed);
#else
  fprintf (ptr_asa_out, "Initial Random Seed = %d\n\n", *seed);
#endif
#endif /* ASA_PRINT */

  /* save initial user value of OPTIONS->Sequential_Parameters */
  *start_sequence = OPTIONS->Sequential_Parameters;

#if ASA_PRINT
  fprintf (ptr_asa_out,
#if INT_ALLOC
	   "*number_parameters = %d\n\n", *number_parameters);
#else
#if INT_LONG
	   "*number_parameters = %ld\n\n", *number_parameters);
#else
	   "*number_parameters = %d\n\n", *number_parameters);
#endif
#endif

  /* print the min, max, current values, and types of parameters */
  fprintf (ptr_asa_out,
	   "index_v parameter_minimum parameter_maximum\
 parameter_value parameter_type \n");

#if ASA_PRINT_INTERMED
  VFOR (index_v)
    fprintf (ptr_asa_out,
#if INT_ALLOC
	     " %-8d %-*.*g \t\t %-*.*g \t %-*.*g %-7d\n",
#else
#if INT_LONG
	     " %-8ld %-*.*g \t\t %-*.*g \t %-*.*g %-7d\n",
#else
	     " %-8d %-*.*g \t\t %-*.*g \t %-*.*g %-7d\n",
#endif
#endif
	     index_v,
	     G_FIELD, G_PRECISION, parameter_minimum[index_v],
	     G_FIELD, G_PRECISION, parameter_maximum[index_v],
	  G_FIELD, G_PRECISION, current_generated_state->parameter[index_v],
	     parameter_type[index_v]);

  fprintf (ptr_asa_out, "\n\n");
#endif /* ASA_PRINT_INTERMED */
  /* Print out user-defined OPTIONS */

#if DELTA_PARAMETERS
  VFOR (index_v)
    fprintf (ptr_asa_out,
#if INT_ALLOC
	     "OPTIONS->User_Delta_Parameter[%d] = %*.*g\n",
#else
#if INT_LONG
	     "OPTIONS->User_Delta_Parameter[%ld] = %*.*g\n",
#else
	     "OPTIONS->User_Delta_Parameter[%d] = %*.*g\n",
#endif
#endif
	     index_v,
	     G_FIELD, G_PRECISION, OPTIONS->User_Delta_Parameter[index_v]);
#endif /* DELTA_PARAMETERS */

#if QUENCH_PARAMETERS
  VFOR (index_v)
    fprintf (ptr_asa_out,
#if INT_ALLOC
	     "OPTIONS->User_Quench_Param_Scale[%d] = %*.*g\n",
#else
#if INT_LONG
	     "OPTIONS->User_Quench_Param_Scale[%ld] = %*.*g\n",
#else
	     "OPTIONS->User_Quench_Param_Scale[%d] = %*.*g\n",
#endif
#endif
	     index_v,
	   G_FIELD, G_PRECISION, OPTIONS->User_Quench_Param_Scale[index_v]);
#endif /* QUENCH_PARAMETERS */

#if QUENCH_COST
  fprintf (ptr_asa_out,
	   "\nOPTIONS->User_Quench_Cost_Scale = %*.*g\n\n",
	   G_FIELD, G_PRECISION, OPTIONS->User_Quench_Cost_Scale[0]);
#endif /* QUENCH_COST */

#if USER_INITIAL_PARAMETERS_TEMPS
  VFOR (index_v)
    fprintf (ptr_asa_out,
#if INT_ALLOC
	     "OPTIONS->User_Parameter_Temperature[%d] = %*.*g\n",
#else
#if INT_LONG
	     "OPTIONS->User_Parameter_Temperature[%ld] = %*.*g\n",
#else
	     "OPTIONS->User_Parameter_Temperature[%d] = %*.*g\n",
#endif
#endif
	     index_v,
	     G_FIELD, G_PRECISION, initial_user_parameter_temp[index_v]);
#endif /* USER_INITIAL_PARAMETERS_TEMPS */

#if RATIO_TEMPERATURE_SCALES
  VFOR (index_v)
    fprintf (ptr_asa_out,
#if INT_ALLOC
	     "OPTIONS->User_Temperature_Ratio[%d] = %*.*g\n",
#else
#if INT_LONG
	     "OPTIONS->User_Temperature_Ratio[%ld] = %*.*g\n",
#else
	     "OPTIONS->User_Temperature_Ratio[%d] = %*.*g\n",
#endif
#endif
	     index_v,
	     G_FIELD, G_PRECISION, OPTIONS->User_Temperature_Ratio[index_v]);
#endif /* RATIO_TEMPERATURE_SCALES */

#if USER_INITIAL_COST_TEMP
  fprintf (ptr_asa_out,
	   "OPTIONS->User_Cost_Temperature[0] = %*.*g\n",
	   G_FIELD, G_PRECISION, *initial_cost_temperature);
#endif /* USER_INITIAL_COST_TEMP */

  fflush (ptr_asa_out);
#endif /* ASA_PRINT */

#if ASA_PARALLEL
#if ASA_PRINT
  fprintf (ptr_asa_out,
#if INT_LONG
	   "Initial ASA_PARALLEL OPTIONS->\n\t Gener_Block = %ld\n\
 \t Gener_Block_Max = %ld\n \t Gener_Mov_Avr= %d\n\n",
#else
	   "ASA_PARALLEL OPTIONS->\n\t Gener_Block = %d\n\
 \t Gener_Block_Max = %d\n \t Gener_Mov_Avr= %d\n\n",
#endif
    OPTIONS->Gener_Block, OPTIONS->Gener_Block_Max, OPTIONS->Gener_Mov_Avr);
#endif
#endif /* ASA_PARALLEL */

#if ASA_SAMPLE
  fprintf (ptr_asa_out, "OPTIONS->Limit_Weights = %*.*g\n\n",
	   G_FIELD, G_PRECISION, OPTIONS->Limit_Weights);
#endif

#if ASA_SAVE
  if ((ptr_save = fopen ("asa_save", "r")) == NULL)
    {
      fclose (ptr_save);
      asa_read = FALSE;
    }
  else
    {
      fclose (ptr_save);
      asa_read = TRUE;

      /* give some value to avoid any problems with other OPTIONS */
#if USER_ACCEPTANCE_TEST
      OPTIONS->Cost_Temp_Curr =
	OPTIONS->Cost_Temp_Init =
#endif
	current_generated_state->cost
	= *initial_cost_temperature = *current_cost_temperature = 3.1416;
    }
#endif

  /* compute temperature scales */
  tmp_var_db1 = -F_LOG ((OPTIONS->Temperature_Ratio_Scale));
  tmp_var_db2 = F_LOG (OPTIONS->Temperature_Anneal_Scale);
  temperature_scale = tmp_var_db1 * F_EXP
    (-tmp_var_db2 / (double) *number_parameters);

  /* set here in case not used */
  tmp_var_db = ZERO;

#if QUENCH_PARAMETERS
#if RATIO_TEMPERATURE_SCALES
  VFOR (index_v)
    temperature_scale_parameters[index_v] =
    tmp_var_db1 * F_EXP
#if QUENCH_PARAMETERS_SCALE
    (-(tmp_var_db2 * OPTIONS->User_Quench_Param_Scale[index_v])
#else
    (-(tmp_var_db2)
#endif
     / (double) *number_parameters)
    * OPTIONS->User_Temperature_Ratio[index_v];
#else
  VFOR (index_v)
    temperature_scale_parameters[index_v] =
    tmp_var_db1 * F_EXP
#if QUENCH_PARAMETERS_SCALE
    (-(tmp_var_db2 * OPTIONS->User_Quench_Param_Scale[index_v])
#else
    (-(tmp_var_db2)
#endif
     / (double) *number_parameters);
#endif /* RATIO_TEMPERATURE_SCALES */
#else /* QUENCH_PARAMETERS */
#if RATIO_TEMPERATURE_SCALES
  VFOR (index_v)
    temperature_scale_parameters[index_v] =
    tmp_var_db1 * F_EXP (-(tmp_var_db2) / (double) *number_parameters)
    * OPTIONS->User_Temperature_Ratio[index_v];
#else
  VFOR (index_v)
    temperature_scale_parameters[index_v] =
    tmp_var_db1 * F_EXP (-(tmp_var_db2) / (double) *number_parameters);
#endif /* RATIO_TEMPERATURE_SCALES */
#endif /* QUENCH_PARAMETERS */

#if USER_ACCEPTANCE_TEST
  OPTIONS->Cost_Temp_Scale =
#endif
    *temperature_scale_cost =
#if QUENCH_COST
#if QUENCH_COST_SCALE
    tmp_var_db1 * F_EXP (-(tmp_var_db2 * OPTIONS->User_Quench_Cost_Scale[0])
#else
    tmp_var_db1 * F_EXP (-(tmp_var_db2)
#endif
       / (double) *number_parameters) * OPTIONS->Cost_Parameter_Scale_Ratio;
#else /* QUENCH_COST */
    tmp_var_db1 * F_EXP (-(tmp_var_db2)
       / (double) *number_parameters) * OPTIONS->Cost_Parameter_Scale_Ratio;
#endif /* QUENCH_COST */

  /* set the initial index of parameter generations to 1 */
  VFOR (index_v)
    index_parameter_generations[index_v] = 1;

  /* test user-defined options before calling cost function */
  tmp_var_int = test_asa_options (seed,
				  parameter_initial_final,
				  parameter_minimum,
				  parameter_maximum,
				  tangents,
				  curvature,
				  number_parameters,
				  parameter_type,
				  valid_state_generated_flag,
				  exit_status,
				  ptr_asa_out,
				  OPTIONS);
  if (tmp_var_int > 0)
    {
#if ASA_PRINT
      fprintf (ptr_asa_out, "total number invalid OPTIONS = %d\n", tmp_var_int);
      fflush (ptr_asa_out);
#endif
      *exit_status = INVALID_USER_INPUT;
      goto EXIT_ASA;
    }

#if USER_INITIAL_COST_TEMP
#else
  /* calculate the average cost over samplings of the cost function */
  if (OPTIONS->Number_Cost_Samples < -1)
    {
      tmp_var_db1 = ZERO;
      tmp_var_db2 = ZERO;
      tmp_var_int = -OPTIONS->Number_Cost_Samples;
    }
  else
    {
      tmp_var_db1 = ZERO;
      tmp_var_int = OPTIONS->Number_Cost_Samples;
    }

  OPTIONS->Locate_Cost = 0;	/* initial cost temp */

  for (index_cost_constraint = 0;
       index_cost_constraint < tmp_var_int;
       ++index_cost_constraint)
    {
      *number_invalid_generated_states = 0;
      repeated_invalid_states = 0;
      OPTIONS->Sequential_Parameters = *start_sequence - 1;
      do
	{
	  ++(*number_invalid_generated_states);
	  generate_new_state (user_random_generator,
			      seed,
			      parameter_minimum,
			      parameter_maximum,
			      current_user_parameter_temp,
#if USER_GENERATING_FUNCTION
			      initial_user_parameter_temp,
			      temperature_scale_parameters,
#endif
			      number_parameters,
			      parameter_type,
			      current_generated_state,
			      last_saved_state,
			      OPTIONS);
	  *valid_state_generated_flag = TRUE;
#if USER_ACCEPTANCE_TEST
	  OPTIONS->User_Acceptance_Flag = TRUE;
	  OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif
	  tmp_var_db =
	    user_cost_function (current_generated_state->parameter);

	  if (COST_FUNCTION_TEST (tmp_var_db))
	    {
	      *exit_status = INVALID_COST_FUNCTION;
	      goto EXIT_ASA;
	    }
	  ++repeated_invalid_states;
	  if (repeated_invalid_states >
	      OPTIONS->Limit_Invalid_Generated_States)
	    {
	      *exit_status = TOO_MANY_INVALID_STATES;
	      goto EXIT_ASA;
	    }
	}
      while (*valid_state_generated_flag == FALSE);
      --(*number_invalid_generated_states);

      if (OPTIONS->Number_Cost_Samples < -1)
	{
	  tmp_var_db1 += tmp_var_db;
	  tmp_var_db2 += (tmp_var_db * tmp_var_db);
	}
      else
	{
	  tmp_var_db1 += fabs (tmp_var_db);
	}
    }
  if (OPTIONS->Number_Cost_Samples < -1)

    {
      tmp_var_db1 /= (double) tmp_var_int;
      tmp_var_db2 /= (double) tmp_var_int;
      tmp_var_db = sqrt (fabs ((tmp_var_db2 - tmp_var_db1 * tmp_var_db1)
			       * ((double) tmp_var_int
				  / ((double) tmp_var_int - ONE))))
	+ (double) EPS_DOUBLE;
    }
  else
    {
      tmp_var_db = tmp_var_db1 / tmp_var_int;
    }

#if USER_ACCEPTANCE_TEST
  OPTIONS->Cost_Temp_Curr =
    OPTIONS->Cost_Temp_Init =
#endif
    *initial_cost_temperature = *current_cost_temperature =
    tmp_var_db;
#endif /* USER_INITIAL_COST_TEMP */

  /* set all parameters to the initial parameter values */
  VFOR (index_v)
    best_generated_state->parameter[index_v] =
    last_saved_state->parameter[index_v] =
    current_generated_state->parameter[index_v] =
    parameter_initial_final[index_v];

  OPTIONS->Locate_Cost = 1;	/* initial cost value */

  /* if using user's initial parameters */
  if (OPTIONS->User_Initial_Parameters == TRUE)
    {
      *valid_state_generated_flag = TRUE;
#if USER_ACCEPTANCE_TEST
      OPTIONS->User_Acceptance_Flag = TRUE;
      OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif
#if ASA_SAVE
      if (asa_read == FALSE)
#endif
	current_generated_state->cost =
	  user_cost_function (current_generated_state->parameter);

    if (COST_FUNCTION_TEST (current_generated_state->cost))
	{
	  *exit_status = INVALID_COST_FUNCTION;
	  goto EXIT_ASA;
	}
#if ASA_PRINT
      if (*valid_state_generated_flag == FALSE)
	fprintf (ptr_asa_out,
		 "user's initial parameters generated \
FALSE *valid_state_generated_flag\n");
#endif
    }
  else
    {
      /* let asa generate valid initial parameters */
      repeated_invalid_states = 0;
      OPTIONS->Sequential_Parameters = *start_sequence - 1;
      do
	{
	  ++(*number_invalid_generated_states);
	  generate_new_state (user_random_generator,
			      seed,
			      parameter_minimum,
			      parameter_maximum,
			      current_user_parameter_temp,
#if USER_GENERATING_FUNCTION
			      initial_user_parameter_temp,
			      temperature_scale_parameters,
#endif
			      number_parameters,
			      parameter_type,
			      current_generated_state,
			      last_saved_state,
			      OPTIONS);
	  *valid_state_generated_flag = TRUE;
#if USER_ACCEPTANCE_TEST
	  OPTIONS->User_Acceptance_Flag = TRUE;
	  OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif
	  current_generated_state->cost =
	    user_cost_function (current_generated_state->parameter);

	  if (COST_FUNCTION_TEST (current_generated_state->cost))
	    {
	      *exit_status = INVALID_COST_FUNCTION;
	      goto EXIT_ASA;
	    }
	  ++repeated_invalid_states;
	  if (repeated_invalid_states >
	      OPTIONS->Limit_Invalid_Generated_States)
	    {
	      *exit_status = TOO_MANY_INVALID_STATES;
	      goto EXIT_ASA;
	    }
	}
      while (*valid_state_generated_flag == FALSE);
      --(*number_invalid_generated_states);
    }				/* OPTIONS->User_Initial_Parameters */

  /* set all states to the last one generated */
  VFOR (index_v)
  {
    /* ignore parameters that have too small a range */
    if (PARAMETER_RANGE_TOO_SMALL (index_v))
      continue;
    best_generated_state->parameter[index_v] =
      last_saved_state->parameter[index_v] =
      current_generated_state->parameter[index_v];
  }

  /* set all costs to the last one generated */
  best_generated_state->cost = last_saved_state->cost =
    current_generated_state->cost;

  *accepted_to_generated_ratio = ONE;

  /* do not calculate curvatures initially */
  *curvature_flag = FALSE;

#if ASA_PRINT
  fprintf (ptr_asa_out,
	   "temperature_scale = %*.*g\n",
	   G_FIELD, G_PRECISION, temperature_scale);
#if RATIO_TEMPERATURE_SCALES
#if ASA_PRINT_INTERMED
  VFOR (index_v)
  {
    fprintf (ptr_asa_out,
#if INT_ALLOC
	     "temperature_scale_parameters[%d] = %*.*g\n",
#else
#if INT_LONG
	     "temperature_scale_parameters[%ld] = %*.*g\n",
#else
	     "temperature_scale_parameters[%d] = %*.*g\n",
#endif
#endif
	     index_v,
	     G_FIELD, G_PRECISION, temperature_scale_parameters[index_v]);
  }
#endif
#else
  fprintf (ptr_asa_out,
	   "temperature_scale_parameters[0] = %*.*g\n",
	   G_FIELD, G_PRECISION, temperature_scale_parameters[0]);
#endif /* RATIO_TEMPERATURE_SCALES */
  fprintf (ptr_asa_out,
	   "*temperature_scale_cost = %*.*g\n",
	   G_FIELD, G_PRECISION, *temperature_scale_cost);
  fprintf (ptr_asa_out, "\n\n");

#if ASA_PRINT_INTERMED
  print_state (parameter_minimum,
	       parameter_maximum,
	       tangents,
	       curvature,
	       current_cost_temperature,
	       current_user_parameter_temp,
	       accepted_to_generated_ratio,
	       number_parameters,
	       curvature_flag,
	       number_accepted,
	       index_cost_acceptances,
	       number_generated,
	       number_invalid_generated_states,
	       last_saved_state,
	       best_generated_state,
	       ptr_asa_out,
	       OPTIONS);
#endif
  fprintf (ptr_asa_out, "\n");

  fflush (ptr_asa_out);
#endif

#if ASA_SAMPLE
#if ASA_PRINT
  fprintf (ptr_asa_out,
	   ":SAMPLE:   n_accept   cost        cost_temp    bias_accept    \
 aver_weight\n");
  fprintf (ptr_asa_out,
	   ":SAMPLE:   index      param[]     temp[]       bias_gener[]   \
 range[]\n");
#endif
#endif

  /* reset the current cost and the number of generations performed */
  *number_invalid_generated_states = 0;
  *best_number_generated_saved =
    *number_generated = *recent_number_generated = 0;
  OPTIONS->N_Generated = *number_generated;
  VFOR (index_v)
  {
    /* ignore parameters that have too small a range */
    if (PARAMETER_RANGE_TOO_SMALL (index_v))
      continue;
    index_parameter_generations[index_v] = 1;
  }
#if USER_ACCEPTANCE_TEST
  OPTIONS->User_Acceptance_Flag = FALSE;
  OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif

#if ASA_QUEUE
  if (OPTIONS->Queue_Size > 0)
    {
      if ((save_queue_flag =
	   (int *) calloc (OPTIONS->Queue_Size, sizeof (int))
	  ) == NULL)
	  exit (9);
      if ((save_queue_cost =
	   (double *) calloc (OPTIONS->Queue_Size, sizeof (double))
	  ) == NULL)
	  exit (9);
      if ((save_queue_param =
	   (double *) calloc ((*number_parameters) * OPTIONS->Queue_Size,
			      sizeof (double))
	  ) == NULL)
	  exit (9);
    }
#if ASA_PRINT
#if INT_ALLOC
  fprintf (ptr_asa_out, "OPTIONS->Queue_Size = %d\n",
	   OPTIONS->Queue_Size);
#else
#if INT_LONG
  fprintf (ptr_asa_out, "OPTIONS->Queue_Size = %ld\n",
	   OPTIONS->Queue_Size);
#else
  fprintf (ptr_asa_out, "OPTIONS->Queue_Size = %d\n",
	   OPTIONS->Queue_Size);
#endif
#endif
  if (OPTIONS->Queue_Size > 0)
    {
      VFOR (index_v)
      {
	fprintf (ptr_asa_out,
#if INT_ALLOC
		 "Queue_Resolution[%d] = %*.*g\n",
#else
#if INT_LONG
		 "Queue_Resolution[%ld] = %*.*g\n",
#else
		 "Queue_Resolution[%d] = %*.*g\n",
#endif
#endif
		 index_v,
		 G_FIELD, G_PRECISION, OPTIONS->Queue_Resolution[index_v]);
      }

#endif /* ASA_PRINT */
      /* fill arrays to check allocated memory */
      for (queue = 0; queue < OPTIONS->Queue_Size; ++queue)
	{
	  VFOR (index_v)
	  {
	    if (PARAMETER_RANGE_TOO_SMALL (index_v))
	      {
		continue;
	      }
	    queue_v = index_v + queue * (LONG_INT) (*number_parameters);
	    save_queue_param[queue_v] =
	      current_generated_state->parameter[index_v];
	  }
	  save_queue_cost[queue] = current_generated_state->cost;
	  save_queue_flag[queue] = *valid_state_generated_flag;
	}
    }
  save_queue = save_queue_indx = 0;
#endif /* ASA_QUEUE */

#if ASA_RESOLUTION
#if ASA_PRINT
  VFOR (index_v)
  {
    fprintf (ptr_asa_out,
#if INT_ALLOC
	     "Coarse_Resolution[%d] = %*.*g\n",
#else
#if INT_LONG
	     "Coarse_Resolution[%ld] = %*.*g\n",
#else
	     "Coarse_Resolution[%d] = %*.*g\n",
#endif
#endif
	     index_v,
	     G_FIELD, G_PRECISION, OPTIONS->Coarse_Resolution[index_v]);
  }
#endif /* ASA_PRINT */
#endif /* ASA_RESOLUTION */

  OPTIONS->Sequential_Parameters = *start_sequence - 1;

  /* MAIN ANNEALING LOOP */
  while (
	  ((*number_accepted <= OPTIONS->Limit_Acceptances)
	   || (OPTIONS->Limit_Acceptances == 0))
	  &&
	  ((*number_generated <= OPTIONS->Limit_Generated)
	   || (OPTIONS->Limit_Generated == 0))
    )
    {

      tmp_var_db1 = -F_LOG ((OPTIONS->Temperature_Ratio_Scale));

      /* compute temperature scales */
      tmp_var_db2 = F_LOG (OPTIONS->Temperature_Anneal_Scale);
      temperature_scale = tmp_var_db1 *
	F_EXP (-tmp_var_db2 / (double) *number_parameters);

#if QUENCH_PARAMETERS
#if RATIO_TEMPERATURE_SCALES
      VFOR (index_v)
	temperature_scale_parameters[index_v] = tmp_var_db1 * F_EXP
#if QUENCH_PARAMETERS_SCALE
	(-(tmp_var_db2 * OPTIONS->User_Quench_Param_Scale[index_v])
#else
	(-(tmp_var_db2)
#endif
	 / (double) *number_parameters)
	* OPTIONS->User_Temperature_Ratio[index_v];
#else
      VFOR (index_v)
	temperature_scale_parameters[index_v] = tmp_var_db1 * F_EXP
#if QUENCH_PARAMETERS_SCALE
	(-(tmp_var_db2 * OPTIONS->User_Quench_Param_Scale[index_v])
#else
	(-(tmp_var_db2)
#endif
	 / (double) *number_parameters);
#endif /* RATIO_TEMPERATURE_SCALES */
#else /* QUENCH_PARAMETERS */
#if RATIO_TEMPERATURE_SCALES
      VFOR (index_v)
	temperature_scale_parameters[index_v] =
	tmp_var_db1 * F_EXP (-(tmp_var_db2) / (double) *number_parameters)
	* OPTIONS->User_Temperature_Ratio[index_v];
#else
      VFOR (index_v)
	temperature_scale_parameters[index_v] =
	tmp_var_db1 * F_EXP (-(tmp_var_db2) / (double) *number_parameters);
#endif /* RATIO_TEMPERATURE_SCALES */
#endif /* QUENCH_PARAMETERS */

#if USER_ACCEPTANCE_TEST
      OPTIONS->Cost_Temp_Scale =
#endif
	*temperature_scale_cost =
#if QUENCH_COST
#if QUENCH_COST_SCALE
	tmp_var_db1 * F_EXP (-(tmp_var_db2 * OPTIONS->User_Quench_Cost_Scale[0])
#else
	tmp_var_db1 * F_EXP (-(tmp_var_db2)
#endif
       / (double) *number_parameters) * OPTIONS->Cost_Parameter_Scale_Ratio;
#else /* QUENCH_COST */
	tmp_var_db1 * F_EXP (-(tmp_var_db2)
       / (double) *number_parameters) * OPTIONS->Cost_Parameter_Scale_Ratio;
#endif /* QUENCH_COST */

      /* CALCULATE NEW TEMPERATURES */

      /* calculate new parameter temperatures */
      VFOR (index_v)
      {
	/* skip parameters with too small a range */
	if (PARAMETER_RANGE_TOO_SMALL (index_v))
	  continue;

	log_new_temperature_ratio =
	  -temperature_scale_parameters[index_v] *
	  F_POW ((double) index_parameter_generations[index_v],
#if QUENCH_PARAMETERS
		 OPTIONS->User_Quench_Param_Scale[index_v]
#else /* QUENCH_PARAMETERS */
		 ONE
#endif /* QUENCH_PARAMETERS */
		 / (double) *number_parameters);
	/* check (and correct) for too large an exponent */
	log_new_temperature_ratio =
	  EXPONENT_CHECK (log_new_temperature_ratio);
	current_user_parameter_temp[index_v] =
	  initial_user_parameter_temp[index_v]
	  * F_EXP (log_new_temperature_ratio);

#if NO_PARAM_TEMP_TEST
	if (current_user_parameter_temp[index_v]
	    < (double) EPS_DOUBLE)
	  current_user_parameter_temp[index_v] =
	    (double) EPS_DOUBLE;
#else
	/* check for too small a parameter temperature */
	if (current_user_parameter_temp[index_v]
	    < (double) EPS_DOUBLE)
	  {
	    *exit_status = P_TEMP_TOO_SMALL;
	    *index_exit_v = index_v;
	    goto EXIT_ASA;
	  }
#endif
      }

      /* calculate new cost temperature */
      log_new_temperature_ratio =
	-*temperature_scale_cost
	* F_POW ((double) *index_cost_acceptances,
#if QUENCH_COST
		 OPTIONS->User_Quench_Cost_Scale[0]
#else
		 ONE
#endif
		 / (double) *number_parameters);
      log_new_temperature_ratio =
	EXPONENT_CHECK (log_new_temperature_ratio);
#if USER_ACCEPTANCE_TEST
      OPTIONS->Cost_Temp_Curr =
	OPTIONS->Cost_Temp_Init =
#endif
	*current_cost_temperature = *initial_cost_temperature
	* F_EXP (log_new_temperature_ratio);

#if NO_COST_TEMP_TEST
      if (*current_cost_temperature < (double) EPS_DOUBLE)
#if USER_ACCEPTANCE_TEST
	OPTIONS->Cost_Temp_Curr =
#endif
	  *current_cost_temperature = (double) EPS_DOUBLE;
#else
      /* check for too small a cost temperature */
      if (*current_cost_temperature < (double) EPS_DOUBLE)
	{
	  *exit_status = C_TEMP_TOO_SMALL;
	  goto EXIT_ASA;
	}
#endif


#if ASA_SAVE
      if (asa_read == TRUE)
	{
	  ptr_save = fopen ("asa_save", "r");

	  fread (number_parameters, sizeof (ALLOC_INT),
		 1, ptr_save);
	  fread (parameter_minimum, sizeof (double),
		 *number_parameters, ptr_save);
	  fread (parameter_maximum, sizeof (double),
		 *number_parameters, ptr_save);
	  fread (tangents, sizeof (double),
		 *number_parameters, ptr_save);
	  fread (current_user_parameter_temp, sizeof (double),
		 *number_parameters, ptr_save);
	  fread (initial_user_parameter_temp, sizeof (double),
		 *number_parameters, ptr_save);
	  fread (temperature_scale_parameters, sizeof (double),
		 *number_parameters, ptr_save);

	  fread (parameter_type, sizeof (int),
		 *number_parameters, ptr_save);
	  fread (&index_cost_repeat, sizeof (int), 1, ptr_save);

	  fread (current_cost_temperature, sizeof (double),
		 1, ptr_save);
	  fread (initial_cost_temperature, sizeof (double),
		 1, ptr_save);
	  fread (temperature_scale_cost, sizeof (double),
		 1, ptr_save);
	  fread (accepted_to_generated_ratio, sizeof (double),
		 1, ptr_save);

	  fread (curvature_flag, sizeof (int), 1, ptr_save);

	  fread (seed, sizeof (LONG_INT), 1, ptr_save);
	  fread (number_generated, sizeof (LONG_INT), 1, ptr_save);
	  fread (number_accepted, sizeof (LONG_INT), 1, ptr_save);
	  fread (number_acceptances_saved, sizeof (LONG_INT),
		 1, ptr_save);
	  fread (recent_number_acceptances, sizeof (LONG_INT),
		 1, ptr_save);
	  fread (recent_number_generated, sizeof (LONG_INT),
		 1, ptr_save);
	  fread (number_invalid_generated_states, sizeof (LONG_INT),
		 1, ptr_save);
	  fread (index_cost_acceptances, sizeof (LONG_INT),
		 1, ptr_save);
	  fread (best_number_generated_saved, sizeof (LONG_INT),
		 1, ptr_save);
	  fread (best_number_accepted_saved, sizeof (LONG_INT),
		 1, ptr_save);

	  fread (index_parameter_generations, sizeof (LONG_INT),
		 *number_parameters, ptr_save);

	  fread (current_generated_state->parameter,
		 sizeof (double), *number_parameters, ptr_save);
	  fread (last_saved_state->parameter,
		 sizeof (double), *number_parameters, ptr_save);
	  fread (best_generated_state->parameter,
		 sizeof (double), *number_parameters, ptr_save);
	  fread (&(current_generated_state->cost),
		 sizeof (double), 1, ptr_save);
	  fread (&(last_saved_state->cost),
		 sizeof (double), 1, ptr_save);
	  fread (&(best_generated_state->cost),
		 sizeof (double), 1, ptr_save);

	  fread (&(OPTIONS->Limit_Acceptances), sizeof (LONG_INT),
		 1, ptr_save);
	  fread (&(OPTIONS->Limit_Generated), sizeof (LONG_INT),
		 1, ptr_save);
	  fread (&(OPTIONS->Limit_Invalid_Generated_States), sizeof (int),
		 1, ptr_save);
	  fread (&(OPTIONS->Accepted_To_Generated_Ratio), sizeof (double),
		 1, ptr_save);
	  fread (&(OPTIONS->Cost_Precision), sizeof (double),
		 1, ptr_save);
	  fread (&(OPTIONS->Maximum_Cost_Repeat), sizeof (int),
		 1, ptr_save);
	  fread (&(OPTIONS->Number_Cost_Samples), sizeof (int),
		 1, ptr_save);
	  fread (&(OPTIONS->Temperature_Ratio_Scale), sizeof (double),
		 1, ptr_save);
	  fread (&(OPTIONS->Cost_Parameter_Scale_Ratio), sizeof (double),
		 1, ptr_save);
	  fread (&(OPTIONS->Temperature_Anneal_Scale), sizeof (double),
		 1, ptr_save);
	  fread (&(OPTIONS->Include_Integer_Parameters), sizeof (int),
		 1, ptr_save);
	  fread (&(OPTIONS->User_Initial_Parameters), sizeof (int),
		 1, ptr_save);
	  fread (&(OPTIONS->Sequential_Parameters), sizeof (ALLOC_INT),
		 1, ptr_save);
	  fread (&(OPTIONS->Initial_Parameter_Temperature), sizeof (double),
		 1, ptr_save);
	  fread (&(OPTIONS->Acceptance_Frequency_Modulus), sizeof (int),
		 1, ptr_save);
	  fread (&(OPTIONS->Generated_Frequency_Modulus), sizeof (int),
		 1, ptr_save);
	  fread (&(OPTIONS->Reanneal_Cost), sizeof (int),
		 1, ptr_save);
	  fread (&(OPTIONS->Reanneal_Parameters), sizeof (int),
		 1, ptr_save);
	  fread (&(OPTIONS->Delta_X), sizeof (double),
		 1, ptr_save);
	  fread (&(OPTIONS->User_Tangents), sizeof (int),
		 1, ptr_save);

#if USER_INITIAL_COST_TEMP
	  fread (OPTIONS->User_Cost_Temperature, sizeof (double),
		 1, ptr_save);
#endif
#if RATIO_TEMPERATURE_SCALES
	  fread (OPTIONS->User_Temperature_Ratio, sizeof (double),
		 *number_parameters, ptr_save);
#endif
#if USER_INITIAL_PARAMETERS_TEMPS
	  fread (OPTIONS->User_Parameter_Temperature, sizeof (double),
		 *number_parameters, ptr_save);
#endif
#if DELTA_PARAMETERS
	  fread (OPTIONS->User_Delta_Parameter, sizeof (double),
		 *number_parameters, ptr_save);
#endif
#if QUENCH_PARAMETERS
	  fread (OPTIONS->User_Quench_Param_Scale, sizeof (double),
		 *number_parameters, ptr_save);
#endif
#if QUENCH_COST
	  fread (OPTIONS->User_Quench_Cost_Scale, sizeof (double),
		 1, ptr_save);
#endif
	  fread (&(OPTIONS->N_Accepted), sizeof (LONG_INT), 1, ptr_save);
	  fread (&(OPTIONS->N_Generated), sizeof (LONG_INT), 1, ptr_save);
	  fread (&(OPTIONS->Locate_Cost), sizeof (int), 1, ptr_save);
	  fread (&(OPTIONS->Immediate_Exit), sizeof (int), 1, ptr_save);
#if OPTIONAL_DATA
	  fread (&(OPTIONS->Asa_Data_Dim), sizeof (ALLOC_INT),
		 1, ptr_save);
	  fread (OPTIONS->Asa_Data, sizeof (double),
		 OPTIONS->Asa_Data_Dim, ptr_save);
#endif
#if OPTIONAL_DATA_INT
	  fread (&(OPTIONS->Asa_Data_Dim_Int), sizeof (ALLOC_INT), 1, ptr_save);
	  fread (OPTIONS->Asa_Data_Int, sizeof (LONG_INT),
		 OPTIONS->Asa_Data_Dim_Int, ptr_save);
#endif
#if USER_ASA_OUT
	  fread (OPTIONS->Asa_Out_File, sizeof (char), 1, ptr_save);
#endif
#if USER_COST_SCHEDULE
	  fread (&(OPTIONS->Cost_Schedule), sizeof (char), 1, ptr_save);
#endif
#if USER_ACCEPT_ASYMP_EXP
	  fread (&(OPTIONS->Asymp_Exp_Param), sizeof (double), 1, ptr_save);
#endif
#if USER_ACCEPTANCE_TEST
	  fread (&(OPTIONS->Acceptance_Test), sizeof (char), 1, ptr_save);
	  fread (&(OPTIONS->User_Acceptance_Flag), sizeof (int), 1, ptr_save);
	  fread (&(OPTIONS->Cost_Acceptance_Flag), sizeof (int), 1, ptr_save);
	  fread (&(OPTIONS->Cost_Temp_Curr), sizeof (double), 1, ptr_save);
	  fread (&(OPTIONS->Cost_Temp_Init), sizeof (double), 1, ptr_save);
	  fread (&(OPTIONS->Cost_Temp_Scale), sizeof (double), 1, ptr_save);
#endif
#if USER_GENERATING_FUNCTION
	  fread (&(OPTIONS->Generating_Distrib), sizeof (char), 1, ptr_save);
#endif
#if USER_REANNEAL_COST
	  fread (OPTIONS->Reanneal_Cost_Function, sizeof (char), 1, ptr_save);
#endif
#if USER_REANNEAL_PARAMETERS
	  fread (&(OPTIONS->Reanneal_Params_Function), sizeof (char),
		 1, ptr_save);
#endif
#if ASA_SAMPLE
	  fread (&(OPTIONS->Bias_Acceptance), sizeof (double), 1, ptr_save);
	  fread (OPTIONS->Bias_Generated, sizeof (double),
		 *number_parameters, ptr_save);
	  fread (&(OPTIONS->Average_Weights), sizeof (double), 1, ptr_save);
	  fread (&(OPTIONS->Limit_Weights), sizeof (double), 1, ptr_save);
#endif
#if ASA_QUEUE
	  fread (&save_queue, sizeof (LONG_INT), 1, ptr_save);
	  fread (&save_queue_indx, sizeof (LONG_INT), 1, ptr_save);
	  fread (&(OPTIONS->Queue_Size), sizeof (ALLOC_INT),
		 1, ptr_save);
	  if (OPTIONS->Queue_Size > 0)
	    {
	      fread (save_queue_flag, sizeof (int), save_queue, ptr_save);
	      fread (save_queue_cost, sizeof (double), save_queue, ptr_save);
	      fread (save_queue_param, sizeof (double),
		    (*number_parameters) * (OPTIONS->Queue_Size), ptr_save);
	      fread (OPTIONS->Queue_Resolution, sizeof (double),
		     *number_parameters, ptr_save);
	    }
#endif
#if ASA_RESOLUTION
	  fread (OPTIONS->Coarse_Resolution, sizeof (double),
		 *number_parameters, ptr_save);
#endif
#if FITLOC
	  fread (OPTIONS->Fit_Local, sizeof (int), 1, ptr_save);
	  fread (OPTIONS->Penalty, sizeof (double), 1, ptr_save);
#endif
#if ASA_PARALLEL
	  fread (&parallel_generated, sizeof (LONG_INT), 1, ptr_save);
	  fread (&parallel_block_max, sizeof (LONG_INT), 1, ptr_save);
	  for (index_parallel = 0; index_parallel < parallel_block_max;
	       ++index_parallel)
	    {
	      fread (gener_block_state[index_parallel].parameter,
		     sizeof (double), *number_parameters, ptr_save);
	      fread (&(gener_block_state[index_parallel].cost),
		     sizeof (double), 1, ptr_save);
#if USER_ACCEPTANCE_TEST
	      fread (&(gener_block_state[index_parallel].par_user_accept_flag),
		     sizeof (int), 1, ptr_save);
	      fread (&(gener_block_state[index_parallel].par_cost_accept_flag),
		     sizeof (int), 1, ptr_save);
#endif
	    }
	  fread (&(OPTIONS->Gener_Mov_Avr), sizeof (int), 1, ptr_save);
	  fread (&(OPTIONS->Gener_Block), sizeof (LONG_INT), 1, ptr_save);
	  fread (&(OPTIONS->Gener_Block_Max), sizeof (LONG_INT), 1, ptr_save);
#endif

	  fclose (ptr_save);

	  asa_read = FALSE;
#if ASA_PRINT
	  print_state (parameter_minimum,
		       parameter_maximum,
		       tangents,
		       curvature,
		       current_cost_temperature,
		       current_user_parameter_temp,
		       accepted_to_generated_ratio,
		       number_parameters,
		       curvature_flag,
		       number_accepted,
		       index_cost_acceptances,
		       number_generated,
		       number_invalid_generated_states,
		       last_saved_state,
		       best_generated_state,
		       ptr_asa_out,
		       OPTIONS);
#endif /* ASA_PRINT */

	  goto SAVED_ASA;
	}
#endif /* ASA_SAVE */

      /* GENERATE NEW PARAMETERS */

      /* generate a new valid set of parameters */
#if ASA_PARALLEL
      /* *** ENTER CODE TO SPAWN OFF PARALLEL GENERATED STATES *** */

      /* check if need more memory allocated to gener_block_state */
      if (OPTIONS->Gener_Block_Max > parallel_block_max)
	{
	  for (index_parallel = 0; index_parallel < parallel_block_max;
	       ++index_parallel)
	    {
	      free (gener_block_state[index_parallel].parameter);
	    }
	  free (gener_block_state);

	  if ((gener_block_state =
	       (STATE *) calloc (OPTIONS->Gener_Block_Max,
				 sizeof (STATE))) == NULL)
	    exit (9);

	  parallel_block_max = OPTIONS->Gener_Block_Max;

	  for (index_parallel = 0; index_parallel < parallel_block_max;
	       ++index_parallel)
	    {
	      if ((gener_block_state[index_parallel].parameter =
		   (double *) calloc (*number_parameters, sizeof (double))
		  ) == NULL)
		  exit (9);
	    }
	}

#if ASA_TEMPLATE_PARALLEL
      for (index_parallel = 0; index_parallel < OPTIONS->Gener_Block;
	   ++index_parallel)
	{
#endif /* ASA_TEMPLATE_PARALLEL */
#endif /* ASA_PARALLEL */

	  if (OPTIONS->Locate_Cost < 0)
	    {
	      OPTIONS->Locate_Cost = 12;	/* generate new state from new best */
	    }
	  else
	    {
	      OPTIONS->Locate_Cost = 2;		/* generate new state */
	    }

	  repeated_invalid_states = 0;
	  do
	    {
	      ++(*number_invalid_generated_states);
	      generate_new_state (user_random_generator,
				  seed,
				  parameter_minimum,
				  parameter_maximum,
				  current_user_parameter_temp,
#if USER_GENERATING_FUNCTION
				  initial_user_parameter_temp,
				  temperature_scale_parameters,
#endif
				  number_parameters,
				  parameter_type,
				  current_generated_state,
				  last_saved_state,
				  OPTIONS);

	      *valid_state_generated_flag = TRUE;
#if USER_ACCEPTANCE_TEST
	      OPTIONS->User_Acceptance_Flag = FALSE;
	      OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif
#if ASA_QUEUE
	      /* Binary trees do not seem necessary since we are assuming
	         that the cost function calculation is the bottleneck.
	         However, see the MISC.DIR/asa_contrib file for
	         source code for doubly-linked and hashed lists. */
	      if (OPTIONS->Queue_Size == 0)	/* in case recursive use */
		{
		  queue_new = 1;
		}
	      else
		{
		  queue_new = 1;
		  for (queue = 0; queue < save_queue; ++queue)
		    {
		      save_queue_test = 0;
		      VFOR (index_v)
		      {
			if (PARAMETER_RANGE_TOO_SMALL (index_v))
			  {
			    ++save_queue_test;
			  }
			else
			  {
			    queue_v = index_v + queue
			      * (LONG_INT) (*number_parameters);
			    if (fabs (
				 current_generated_state->parameter[index_v]
				       - save_queue_param[queue_v])
				<= (OPTIONS->Queue_Resolution[index_v]
				    + EPS_DOUBLE))
			      {
				++save_queue_test;
			      }
			  }
		      }
		      if (save_queue_test == *number_parameters)
			{
			  tmp_var_db = save_queue_cost[queue];
			  *valid_state_generated_flag =
			    save_queue_flag[queue];
			  queue_new = 0;
			  --(*number_generated);
#if ASA_TEMPLATE_QUEUE
#if ASA_PRINT_MORE
#if INT_LONG
			  fprintf (ptr_asa_out, "ASA_QUEUE: %ld \t %*.*g\n",
#else
			  fprintf (ptr_asa_out, "ASA_QUEUE: %d \t %*.*g\n",
#endif
				   OPTIONS->N_Generated,
				   G_FIELD, G_PRECISION, tmp_var_db);
#endif
#endif
			  break;
			}
		    }
		}
	      if (queue_new == 1)
		{
		  tmp_var_db =
		    user_cost_function (
					 current_generated_state->parameter,
					 parameter_minimum,
					 parameter_maximum,
					 tangents,
					 curvature,
					 number_parameters,
					 parameter_type,
					 valid_state_generated_flag,
					 exit_status,
					 OPTIONS);
		  if (COST_FUNCTION_TEST (tmp_var_db))
		    {
		      *exit_status = INVALID_COST_FUNCTION;
		      goto EXIT_ASA;
		    }
		  if (OPTIONS->Queue_Size > 0)	/* in case recursive use */
		    {
		      VFOR (index_v)
		      {
			if (PARAMETER_RANGE_TOO_SMALL (index_v))
			  {
			    continue;
			  }
			queue_v = index_v + save_queue_indx
			  * (LONG_INT) (*number_parameters);
			save_queue_param[queue_v] =
			  current_generated_state->parameter[index_v];
		      }
		      save_queue_cost[save_queue_indx] = tmp_var_db;
		      save_queue_flag[save_queue_indx]
			= *valid_state_generated_flag;

		      ++save_queue;
		      if (save_queue == (LONG_INT) OPTIONS->Queue_Size)
			--save_queue;

		      ++save_queue_indx;
		      if (save_queue_indx == (LONG_INT) OPTIONS->Queue_Size)
			save_queue_indx = 0;
		    }
		}
#else /* ASA_QUEUE */
	      tmp_var_db =
		user_cost_function (current_generated_state->parameter);

		if (COST_FUNCTION_TEST (tmp_var_db))
		{
		  *exit_status = INVALID_COST_FUNCTION;
		  goto EXIT_ASA;
		}
#endif /* ASA_QUEUE */
	      current_generated_state->cost = tmp_var_db;
	      ++repeated_invalid_states;
	      if (repeated_invalid_states >
		  OPTIONS->Limit_Invalid_Generated_States)
		{
		  *exit_status = TOO_MANY_INVALID_STATES;
		  goto EXIT_ASA;
		}
	    }
	  while (*valid_state_generated_flag == FALSE);
	  --(*number_invalid_generated_states);
#if ASA_PARALLEL
	  gener_block_state[index_parallel].cost
	    = current_generated_state->cost;
#if USER_ACCEPTANCE_TEST
	  gener_block_state[index_parallel].par_user_accept_flag =
	    OPTIONS->User_Acceptance_Flag;
	  gener_block_state[index_parallel].par_cost_accept_flag =
	    OPTIONS->Cost_Acceptance_Flag;
#endif
	  VFOR (index_v)
	  {
	    /* ignore parameters with too small a range */
	    if (PARAMETER_RANGE_TOO_SMALL (index_v))
	      continue;
	    gener_block_state[index_parallel].parameter[index_v] =
	      current_generated_state->parameter[index_v];
	  }
#if ASA_TEMPLATE_PARALLEL
	}
#endif /* ASA_TEMPLATE_PARALLEL */
      /* *** EXIT CODE SPAWNING OFF PARALLEL GENERATED STATES *** */
#endif /* ASA_PARALLEL */

      /* ACCEPT/REJECT NEW PARAMETERS */

#if ASA_PARALLEL
      for (index_parallel = 0; index_parallel < OPTIONS->Gener_Block;
	   ++index_parallel)
	{
	  current_generated_state->cost
	    = gener_block_state[index_parallel].cost;
#if USER_ACCEPTANCE_TEST
	  OPTIONS->User_Acceptance_Flag =
	    gener_block_state[index_parallel].par_user_accept_flag;
	  OPTIONS->Cost_Acceptance_Flag =
	    gener_block_state[index_parallel].par_cost_accept_flag;
#endif
	  VFOR (index_v)
	  {
	    /* ignore parameters with too small a range */
	    if (PARAMETER_RANGE_TOO_SMALL (index_v))
	      continue;
	    current_generated_state->parameter[index_v] =
	      gener_block_state[index_parallel].parameter[index_v];
	  }
#endif /* ASA_PARALLEL */
	  /* decide to accept/reject the new state */
	  accept_new_state (user_random_generator,
			    seed,
			    parameter_minimum,
			    parameter_maximum,
			    current_cost_temperature,
#if ASA_SAMPLE
			    current_user_parameter_temp,
#endif
			    number_parameters,
			    recent_number_acceptances,
			    number_accepted,
			    index_cost_acceptances,
			    number_acceptances_saved,
			    recent_number_generated,
			    number_generated,
			    index_parameter_generations,
			    current_generated_state,
			    last_saved_state,
#if ASA_SAMPLE
			    ptr_asa_out,
#endif
			    OPTIONS);

	  /* calculate the ratio of acceptances to generated states */
	  *accepted_to_generated_ratio =
	    (double) (*recent_number_acceptances + 1) /
	    (double) (*recent_number_generated + 1);

	  /* CHECK FOR NEW MINIMUM */

	  if (current_generated_state->cost < best_generated_state->cost)
	    {
	      /* NEW MINIMUM FOUND */

	      OPTIONS->Locate_Cost = -1;

	      /* reset the recent acceptances and generated counts */
#if ASA_PARALLEL
	      parallel_generated = *recent_number_generated;
#endif
	      *recent_number_acceptances = *recent_number_generated = 0;
	      *best_number_generated_saved = *number_generated;
	      *best_number_accepted_saved = *number_accepted;
	      index_cost_repeat = 0;

	      /* copy the current state into the best_generated state */
	      best_generated_state->cost = current_generated_state->cost;
	      VFOR (index_v)
	      {
		/* ignore parameters that have too small a range */
		if (PARAMETER_RANGE_TOO_SMALL (index_v))
		  continue;
		best_generated_state->parameter[index_v] =
		  current_generated_state->parameter[index_v];
	      }

	      /* printout the new minimum state and value */
#if ASA_PRINT
	      fprintf (ptr_asa_out,
#if INT_LONG
		       "best...->cost=%-*.*g  \
*number_accepted=%ld  *number_generated=%ld\n",
		       G_FIELD, G_PRECISION, best_generated_state->cost,
#else
		       "best...->cost=%-*.*g  \
*number_accepted=%d  *number_generated=%d\n",
		       G_FIELD, G_PRECISION, best_generated_state->cost,
#endif /* INT_LONG */
		       *number_accepted, *number_generated);
#if ASA_PARALLEL
	      /* print OPTIONS->Gener_Block just used */
	      fprintf (ptr_asa_out,
#if INT_LONG
		       "OPTIONS->Gener_Block = %ld\n",
#else
		       "OPTIONS->Gener_Block = %d\n",
#endif /* INT_LONG */
		       OPTIONS->Gener_Block);
#endif /* ASA_PARALLEL */
#if ASA_PRINT_MORE
#if INT_ALLOC
	      fprintf (ptr_asa_out, "Present Random Seed = %d\n\n", *seed);
#else
#if INT_LONG
	      fprintf (ptr_asa_out, "Present Random Seed = %ld\n\n", *seed);
#else
	      fprintf (ptr_asa_out, "Present Random Seed = %d\n\n", *seed);
#endif
#endif
	      print_state (parameter_minimum,
			   parameter_maximum,
			   tangents,
			   curvature,
			   current_cost_temperature,
			   current_user_parameter_temp,
			   accepted_to_generated_ratio,
			   number_parameters,
			   curvature_flag,
			   number_accepted,
			   index_cost_acceptances,
			   number_generated,
			   number_invalid_generated_states,
			   last_saved_state,
			   best_generated_state,
			   ptr_asa_out,
			   OPTIONS);
#endif /* ASA_PRINT_MORE */
	      fflush (ptr_asa_out);
#endif /* ASA_PRINT */

#if ASA_PARALLEL
	      /* leave index_parallel loop after new minimum */
	      break;
#endif /* ASA_PARALLEL */
	    }
#if ASA_PARALLEL
	}
#endif /* ASA_PARALLEL */

#if ASA_PARALLEL
      if (OPTIONS->Gener_Mov_Avr > 0)
	{
	  OPTIONS->Gener_Block = (LONG_INT)
	    ((((double) OPTIONS->Gener_Mov_Avr - ONE)
	    * (double) (OPTIONS->Gener_Block) + (double) parallel_generated)
	     / (double) (OPTIONS->Gener_Mov_Avr));
	  OPTIONS->Gener_Block =
	    MIN (OPTIONS->Gener_Block, parallel_block_max);
	}
#endif /* ASA_PARALLEL */

#if ASA_SAVE
      /* These writes are put here with these tests, instead of just
         after a new best state is found, to prevent any confusion with
         any parallel code that might be added by users. */
      if (
	   *recent_number_acceptances == 0
	   && *recent_number_generated == 0
	   && *best_number_generated_saved == *number_generated
	   && *best_number_accepted_saved == *number_accepted
	   && index_cost_repeat == 0
	)
	{
	  ptr_save = fopen ("asa_save", "w");

	  fwrite (number_parameters, sizeof (ALLOC_INT),
		  1, ptr_save);
	  fwrite (parameter_minimum, sizeof (double),
		  *number_parameters, ptr_save);
	  fwrite (parameter_maximum, sizeof (double),
		  *number_parameters, ptr_save);
	  fwrite (tangents, sizeof (double),
		  *number_parameters, ptr_save);
	  fwrite (current_user_parameter_temp, sizeof (double),
		  *number_parameters, ptr_save);
	  fwrite (initial_user_parameter_temp, sizeof (double),
		  *number_parameters, ptr_save);
	  fwrite (temperature_scale_parameters, sizeof (double),
		  *number_parameters, ptr_save);

	  fwrite (parameter_type, sizeof (int),
		  *number_parameters, ptr_save);
	  fwrite (&index_cost_repeat, sizeof (int), 1, ptr_save);

	  fwrite (current_cost_temperature, sizeof (double),
		  1, ptr_save);
	  fwrite (initial_cost_temperature, sizeof (double),
		  1, ptr_save);
	  fwrite (temperature_scale_cost, sizeof (double),
		  1, ptr_save);
	  fwrite (accepted_to_generated_ratio, sizeof (double),
		  1, ptr_save);

	  fwrite (curvature_flag, sizeof (int), 1, ptr_save);

	  fwrite (seed, sizeof (LONG_INT), 1, ptr_save);
	  fwrite (number_generated, sizeof (LONG_INT), 1, ptr_save);
	  fwrite (number_accepted, sizeof (LONG_INT), 1, ptr_save);
	  fwrite (number_acceptances_saved, sizeof (LONG_INT),
		  1, ptr_save);
	  fwrite (recent_number_acceptances, sizeof (LONG_INT),
		  1, ptr_save);
	  fwrite (recent_number_generated, sizeof (LONG_INT),
		  1, ptr_save);
	  fwrite (number_invalid_generated_states, sizeof (LONG_INT),
		  1, ptr_save);
	  fwrite (index_cost_acceptances, sizeof (LONG_INT),
		  1, ptr_save);
	  fwrite (best_number_generated_saved, sizeof (LONG_INT),
		  1, ptr_save);
	  fwrite (best_number_accepted_saved, sizeof (LONG_INT),
		  1, ptr_save);

	  fwrite (index_parameter_generations, sizeof (LONG_INT),
		  *number_parameters, ptr_save);

	  fwrite (current_generated_state->parameter,
		  sizeof (double), *number_parameters, ptr_save);
	  fwrite (last_saved_state->parameter,
		  sizeof (double), *number_parameters, ptr_save);
	  fwrite (best_generated_state->parameter,
		  sizeof (double), *number_parameters, ptr_save);
	  fwrite (&(current_generated_state->cost),
		  sizeof (double), 1, ptr_save);
	  fwrite (&(last_saved_state->cost),
		  sizeof (double), 1, ptr_save);
	  fwrite (&(best_generated_state->cost),
		  sizeof (double), 1, ptr_save);

	  fwrite (&(OPTIONS->Limit_Acceptances), sizeof (LONG_INT),
		  1, ptr_save);
	  fwrite (&(OPTIONS->Limit_Generated), sizeof (LONG_INT),
		  1, ptr_save);
	  fwrite (&(OPTIONS->Limit_Invalid_Generated_States), sizeof (int),
		  1, ptr_save);
	  fwrite (&(OPTIONS->Accepted_To_Generated_Ratio), sizeof (double),
		  1, ptr_save);
	  fwrite (&(OPTIONS->Cost_Precision), sizeof (double),
		  1, ptr_save);
	  fwrite (&(OPTIONS->Maximum_Cost_Repeat), sizeof (int),
		  1, ptr_save);
	  fwrite (&(OPTIONS->Number_Cost_Samples), sizeof (int),
		  1, ptr_save);
	  fwrite (&(OPTIONS->Temperature_Ratio_Scale), sizeof (double),
		  1, ptr_save);
	  fwrite (&(OPTIONS->Cost_Parameter_Scale_Ratio), sizeof (double),
		  1, ptr_save);
	  fwrite (&(OPTIONS->Temperature_Anneal_Scale), sizeof (double),
		  1, ptr_save);
	  fwrite (&(OPTIONS->Include_Integer_Parameters), sizeof (int),
		  1, ptr_save);
	  fwrite (&(OPTIONS->User_Initial_Parameters), sizeof (int),
		  1, ptr_save);
	  fwrite (&(OPTIONS->Sequential_Parameters), sizeof (ALLOC_INT),
		  1, ptr_save);
	  fwrite (&(OPTIONS->Initial_Parameter_Temperature), sizeof (double),
		  1, ptr_save);
	  fwrite (&(OPTIONS->Acceptance_Frequency_Modulus), sizeof (int),
		  1, ptr_save);
	  fwrite (&(OPTIONS->Generated_Frequency_Modulus), sizeof (int),
		  1, ptr_save);
	  fwrite (&(OPTIONS->Reanneal_Cost), sizeof (int),
		  1, ptr_save);
	  fwrite (&(OPTIONS->Reanneal_Parameters), sizeof (int),
		  1, ptr_save);
	  fwrite (&(OPTIONS->Delta_X), sizeof (double),
		  1, ptr_save);
	  fwrite (&(OPTIONS->User_Tangents), sizeof (int),
		  1, ptr_save);

#if USER_INITIAL_COST_TEMP
	  fwrite (OPTIONS->User_Cost_Temperature, sizeof (double),
		  1, ptr_save);
#endif
#if RATIO_TEMPERATURE_SCALES
	  fwrite (OPTIONS->User_Temperature_Ratio, sizeof (double),
		  *number_parameters, ptr_save);
#endif
#if USER_INITIAL_PARAMETERS_TEMPS
	  fwrite (OPTIONS->User_Parameter_Temperature, sizeof (double),
		  *number_parameters, ptr_save);
#endif
#if DELTA_PARAMETERS
	  fwrite (OPTIONS->User_Delta_Parameter, sizeof (double),
		  *number_parameters, ptr_save);
#endif
#if QUENCH_PARAMETERS
	  fwrite (OPTIONS->User_Quench_Param_Scale, sizeof (double),
		  *number_parameters, ptr_save);
#endif
#if QUENCH_COST
	  fwrite (OPTIONS->User_Quench_Cost_Scale, sizeof (double),
		  1, ptr_save);
#endif
	  fwrite (&(OPTIONS->N_Accepted), sizeof (LONG_INT), 1, ptr_save);
	  fwrite (&(OPTIONS->N_Generated), sizeof (LONG_INT), 1, ptr_save);
	  fwrite (&(OPTIONS->Locate_Cost), sizeof (int), 1, ptr_save);
	  fwrite (&(OPTIONS->Immediate_Exit), sizeof (int), 1, ptr_save);
#if OPTIONAL_DATA
	  fwrite (&(OPTIONS->Asa_Data_Dim), sizeof (ALLOC_INT), 1, ptr_save);
	  fwrite (OPTIONS->Asa_Data, sizeof (double),
		  OPTIONS->Asa_Data_Dim, ptr_save);
#endif
#if OPTIONAL_DATA_INT
	  fwrite (&(OPTIONS->Asa_Data_Dim_Int), sizeof (ALLOC_INT),
		  1, ptr_save);
	  fwrite (OPTIONS->Asa_Data_Int, sizeof (LONG_INT),
		  OPTIONS->Asa_Data_Dim_Int, ptr_save);
#endif
#if USER_ASA_OUT
	  fwrite (OPTIONS->Asa_Out_File, sizeof (char), 1, ptr_save);
#endif
#if USER_COST_SCHEDULE
	  fwrite (&(OPTIONS->Cost_Schedule), sizeof (char), 1, ptr_save);
#endif
#if USER_ACCEPT_ASYMP_EXP
	  fwrite (&(OPTIONS->Asymp_Exp_Param), sizeof (double), 1, ptr_save);
#endif
#if USER_ACCEPTANCE_TEST
	  fwrite (&(OPTIONS->Acceptance_Test), sizeof (char), 1, ptr_save);
	  fwrite (&(OPTIONS->User_Acceptance_Flag), sizeof (int), 1, ptr_save);
	  fwrite (&(OPTIONS->Cost_Acceptance_Flag), sizeof (int), 1, ptr_save);
	  fwrite (&(OPTIONS->Cost_Temp_Curr), sizeof (double), 1, ptr_save);
	  fwrite (&(OPTIONS->Cost_Temp_Init), sizeof (double), 1, ptr_save);
	  fwrite (&(OPTIONS->Cost_Temp_Scale), sizeof (double), 1, ptr_save);
#endif
#if USER_GENERATING_FUNCTION
	  fwrite (&(OPTIONS->Generating_Distrib), sizeof (char), 1, ptr_save);
#endif
#if USER_REANNEAL_COST
	  fwrite (OPTIONS->Reanneal_Cost_Function, sizeof (char), 1, ptr_save);
#endif
#if USER_REANNEAL_PARAMETERS
	  fwrite (&(OPTIONS->Reanneal_Params_Function), sizeof (char),
		  1, ptr_save);
#endif
#if ASA_SAMPLE
	  fwrite (&(OPTIONS->Bias_Acceptance), sizeof (double), 1, ptr_save);
	  fwrite (OPTIONS->Bias_Generated, sizeof (double),
		  *number_parameters, ptr_save);
	  fwrite (&(OPTIONS->Average_Weights), sizeof (double), 1, ptr_save);
	  fwrite (&(OPTIONS->Limit_Weights), sizeof (double), 1, ptr_save);
#endif
#if ASA_QUEUE
	  fwrite (save_queue, sizeof (LONG_INT), 1, ptr_save);
	  fwrite (save_queue_indx, sizeof (LONG_INT), 1, ptr_save);
	  fwrite (&(OPTIONS->Queue_Size), sizeof (ALLOC_INT),
		  1, ptr_save);
	  if (OPTIONS->Queue_Size > 0)
	    {
	      fwrite (save_queue_flag, sizeof (int), save_queue, ptr_save);
	      fwrite (save_queue_cost, sizeof (double), save_queue, ptr_save);
	      fwrite (save_queue_param, sizeof (double),
		    (*number_parameters) * (OPTIONS->Queue_Size), ptr_save);
	      fwrite (OPTIONS->Queue_Resolution, sizeof (double),
		      *number_parameters, ptr_save);
	    }
#endif
#if ASA_RESOLUTION
	  fwrite (OPTIONS->Coarse_Resolution, sizeof (double),
		  *number_parameters, ptr_save);
#endif
#if FITLOC
	  fwrite (OPTIONS->Fit_Local, sizeof (int), 1, ptr_save);
	  fwrite (OPTIONS->Penalty, sizeof (double), 1, ptr_save);
#endif
#if ASA_PARALLEL
	  fwrite (&parallel_generated, sizeof (LONG_INT), 1, ptr_save);
	  fwrite (&parallel_block_max, sizeof (LONG_INT), 1, ptr_save);
	  for (index_parallel = 0; index_parallel < parallel_block_max;
	       ++index_parallel)
	    {
	      fwrite (gener_block_state[index_parallel].parameter,
		      sizeof (double), *number_parameters, ptr_save);
	      fwrite (&(gener_block_state[index_parallel].cost),
		      sizeof (double), 1, ptr_save);
#if USER_ACCEPTANCE_TEST
	      fwrite (&(gener_block_state[index_parallel].par_user_accept_flag),
		      sizeof (int), 1, ptr_save);
	      fwrite (&(gener_block_state[index_parallel].par_cost_accept_flag),
		      sizeof (int), 1, ptr_save);
#endif
	    }
	  fwrite (&(OPTIONS->Gener_Mov_Avr), sizeof (int), 1, ptr_save);
	  fwrite (&(OPTIONS->Gener_Block), sizeof (LONG_INT), 1, ptr_save);
	  fwrite (&(OPTIONS->Gener_Block_Max), sizeof (LONG_INT), 1, ptr_save);
#endif

	  fclose (ptr_save);

	SAVED_ASA:

#if SYSTEM_CALL
	  /* extra protection in case run aborts during write */
	  system ("/bin/cp asa_save asa_save.old");
#endif
#if ASA_PRINT
#if INT_ALLOC
	  fprintf (ptr_asa_out, "Present Random Seed = %d\n\n", *seed);
#else
#if INT_LONG
	  fprintf (ptr_asa_out, "Present Random Seed = %ld\n\n", *seed);
#else
	  fprintf (ptr_asa_out, "Present Random Seed = %d\n\n", *seed);
#endif
#endif
#endif /* ASA_PRINT */
	}
#endif /* ASA_SAVE */

      if (OPTIONS->Immediate_Exit == TRUE)
	{
	  *exit_status = IMMEDIATE_EXIT;
	  goto EXIT_ASA;
	}

      /* PERIODIC TESTING/REANNEALING/PRINTING SECTION */

      if (OPTIONS->Acceptance_Frequency_Modulus == 0)
	tmp_var_int1 = FALSE;
      else if ((int) (*number_accepted %
		    ((LONG_INT) OPTIONS->Acceptance_Frequency_Modulus)) == 0
	       && *number_acceptances_saved == *number_accepted)
	tmp_var_int1 = TRUE;
      else
	tmp_var_int1 = FALSE;

      if (OPTIONS->Generated_Frequency_Modulus == 0)
	tmp_var_int2 = FALSE;
      else if ((int) (*number_generated %
		    ((LONG_INT) OPTIONS->Generated_Frequency_Modulus)) == 0)
	tmp_var_int2 = TRUE;
      else
	tmp_var_int2 = FALSE;

      if (
	   tmp_var_int1 == TRUE || tmp_var_int2 == TRUE
	   || (*accepted_to_generated_ratio
	       < OPTIONS->Accepted_To_Generated_Ratio)
	)
	{
	  if (*accepted_to_generated_ratio
	      < (OPTIONS->Accepted_To_Generated_Ratio))
	    *recent_number_acceptances = *recent_number_generated = 0;

	  /* if best.cost repeats OPTIONS->Maximum_Cost_Repeat then exit */
	  if (OPTIONS->Maximum_Cost_Repeat != 0)
	    {
	      if (fabs (last_saved_state->cost - best_generated_state->cost)
		  < OPTIONS->Cost_Precision)
		{
		  ++index_cost_repeat;
		  if (index_cost_repeat == (OPTIONS->Maximum_Cost_Repeat))
		    {
		      *exit_status = COST_REPEATING;
		      goto EXIT_ASA;
		    }
		}
	      else
		{
		  index_cost_repeat = 0;
		}
	    }

	  if (OPTIONS->Reanneal_Parameters == TRUE)
	    {
	      OPTIONS->Locate_Cost = 3;		/* reanneal parameters */

	      /* calculate tangents, not curvatures, to reanneal */
	      *curvature_flag = FALSE;
	      cost_derivatives (user_cost_function,
				parameter_minimum,
				parameter_maximum,
				tangents,
				curvature,
				maximum_tangent,
				number_parameters,
				parameter_type,
				exit_status,
				curvature_flag,
				valid_state_generated_flag,
				number_invalid_generated_states,
				current_generated_state,
				best_generated_state,
				ptr_asa_out,
				OPTIONS);
	      if (*exit_status == INVALID_COST_FUNCTION)
		{
		  goto EXIT_ASA;
		}
	    }

#if USER_REANNEAL_COST
#else
	  if (OPTIONS->Reanneal_Cost == 0 || OPTIONS->Reanneal_Cost == 1)
	    {
	      ;
	    }
	  else
	    {
	      immediate_flag = OPTIONS->Immediate_Exit;

	      if (OPTIONS->Reanneal_Cost < -1)
		{
		  tmp_var_int = -OPTIONS->Reanneal_Cost;
		}
	      else
		{
		  tmp_var_int = OPTIONS->Reanneal_Cost;
		}
	      tmp_var_db1 = ZERO;
	      tmp_var_db2 = ZERO;

	      for (index_cost_constraint = 0;
		   index_cost_constraint < tmp_var_int;
		   ++index_cost_constraint)
		{
		  OPTIONS->Locate_Cost = 4;	/* reanneal cost */

		  *number_invalid_generated_states = 0;
		  repeated_invalid_states = 0;
		  OPTIONS->Sequential_Parameters = *start_sequence - 1;
		  do
		    {
		      ++(*number_invalid_generated_states);
		      generate_new_state (user_random_generator,
					  seed,
					  parameter_minimum,
					  parameter_maximum,
					  current_user_parameter_temp,
#if USER_GENERATING_FUNCTION
					  initial_user_parameter_temp,
					  temperature_scale_parameters,
#endif
					  number_parameters,
					  parameter_type,
					  current_generated_state,
					  last_saved_state,
					  OPTIONS);
		      *valid_state_generated_flag = TRUE;
#if USER_ACCEPTANCE_TEST
		      OPTIONS->User_Acceptance_Flag = TRUE;
		      OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif

#if ASA_QUEUE
		      if (OPTIONS->Queue_Size == 0)
			{
			  queue_new = 1;
			}
		      else
			{
			  queue_new = 1;
			  for (queue = 0; queue < save_queue; ++queue)
			    {
			      save_queue_test = 0;
			      VFOR (index_v)
			      {
				if (PARAMETER_RANGE_TOO_SMALL (index_v))
				  {
				    ++save_queue_test;
				  }
				else
				  {
				    queue_v = index_v + queue
				      * (LONG_INT) (*number_parameters);
				    if (fabs (
					       current_generated_state->parameter[index_v]
					       - save_queue_param[queue_v])
					< (OPTIONS->Queue_Resolution[index_v]
					   + EPS_DOUBLE))
				      {
					++save_queue_test;
				      }
				  }
			      }
			      if (save_queue_test == *number_parameters)
				{
				  tmp_var_db = save_queue_cost[queue];
				  *valid_state_generated_flag =
				    save_queue_flag[queue];
				  queue_new = 0;
#if ASA_TEMPLATE_QUEUE
#if ASA_PRINT_MORE
#if INT_LONG
				  fprintf (ptr_asa_out, "ASA_QUEUE: %ld \t %*.*g\n",
#else
				  fprintf (ptr_asa_out, "ASA_QUEUE: %d \t %*.*g\n",
#endif
					   OPTIONS->N_Generated,
					   G_FIELD, G_PRECISION, tmp_var_db);
#endif
#endif
				  break;
				}
			    }
			}
		      if (queue_new == 1)
			{
			  tmp_var_db =
			    user_cost_function (
					 current_generated_state->parameter,
						 parameter_minimum,
						 parameter_maximum,
						 tangents,
						 curvature,
						 number_parameters,
						 parameter_type,
						 valid_state_generated_flag,
						 exit_status,
						 OPTIONS);
			  if (COST_FUNCTION_TEST (tmp_var_db))
			    {
			      *exit_status = INVALID_COST_FUNCTION;
			      goto EXIT_ASA;
			    }
			  if (OPTIONS->Queue_Size > 0)
			    {
			      VFOR (index_v)
			      {
				if (PARAMETER_RANGE_TOO_SMALL (index_v))
				  {
				    continue;
				  }
				queue_v = index_v + save_queue
				  * (LONG_INT) (*number_parameters);
				save_queue_param[queue_v] =
				  current_generated_state->parameter[index_v];
			      }
			      save_queue_cost[save_queue] = tmp_var_db;
			      save_queue_flag[save_queue]
				= *valid_state_generated_flag;

			      ++save_queue;
			      if (save_queue == (LONG_INT) OPTIONS->Queue_Size)
				--save_queue;

			      ++save_queue_indx;
			      if (save_queue_indx == (LONG_INT) OPTIONS->Queue_Size)
				save_queue_indx = 0;
			    }
			}
#else /* ASA_QUEUE */
		      tmp_var_db =
			user_cost_function (current_generated_state->parameter);

			if (COST_FUNCTION_TEST (tmp_var_db))
			{
			  *exit_status = INVALID_COST_FUNCTION;
			  goto EXIT_ASA;
			}
#endif /* ASA_QUEUE */
		      ++repeated_invalid_states;
		      if (repeated_invalid_states >
			  OPTIONS->Limit_Invalid_Generated_States)
			{
			  *exit_status = TOO_MANY_INVALID_STATES;
			  goto EXIT_ASA;
			}
		    }
		  while (*valid_state_generated_flag == FALSE);
		  --(*number_invalid_generated_states);

		  tmp_var_db1 += tmp_var_db;
		  tmp_var_db2 += (tmp_var_db * tmp_var_db);
		}
	      tmp_var_db1 /= (double) tmp_var_int;
	      tmp_var_db2 /= (double) tmp_var_int;
	      tmp_var_db = sqrt (fabs ((tmp_var_db2 - tmp_var_db1 * tmp_var_db1)
				       * ((double) tmp_var_int
					  / ((double) tmp_var_int - ONE))));
	      if (OPTIONS->Reanneal_Cost < -1)
		{
		  *current_cost_temperature = *initial_cost_temperature =
		    tmp_var_db + (double) EPS_DOUBLE;
		}
	      else
		{
		  *initial_cost_temperature = tmp_var_db + (double) EPS_DOUBLE;
		}
	      OPTIONS->Immediate_Exit = immediate_flag;
	    }
#endif /* USER_REANNEAL_COST */

	  reanneal (parameter_minimum,
		    parameter_maximum,
		    tangents,
		    maximum_tangent,
		    current_cost_temperature,
		    initial_cost_temperature,
		    temperature_scale_cost,
		    current_user_parameter_temp,
		    initial_user_parameter_temp,
		    temperature_scale_parameters,
		    number_parameters,
		    parameter_type,
		    index_cost_acceptances,
		    index_parameter_generations,
		    last_saved_state,
		    best_generated_state,
		    OPTIONS);
#if ASA_PRINT_INTERMED
#if ASA_PRINT
	  print_state (parameter_minimum,
		       parameter_maximum,
		       tangents,
		       curvature,
		       current_cost_temperature,
		       current_user_parameter_temp,
		       accepted_to_generated_ratio,
		       number_parameters,
		       curvature_flag,
		       number_accepted,
		       index_cost_acceptances,
		       number_generated,
		       number_invalid_generated_states,
		       last_saved_state,
		       best_generated_state,
		       ptr_asa_out,
		       OPTIONS);

	  fprintf (ptr_asa_out, "\n");
	  fflush (ptr_asa_out);
#endif
#endif
	}
    }

  /* FINISHED ANNEALING and MINIMIZATION */

  *exit_status = NORMAL_EXIT;
EXIT_ASA:

  asa_exit (user_cost_function,
	    &final_cost,
	    parameter_initial_final,
	    parameter_minimum,
	    parameter_maximum,
	    tangents,
	    curvature,
	    maximum_tangent,
	    current_cost_temperature,
	    initial_user_parameter_temp,
	    current_user_parameter_temp,
	    accepted_to_generated_ratio,
	    number_parameters,
	    parameter_type,
	    valid_state_generated_flag,
	    exit_status,
	    index_exit_v,
	    start_sequence,
	    number_accepted,
	    best_number_accepted_saved,
	    index_cost_acceptances,
	    number_generated,
	    number_invalid_generated_states,
	    index_parameter_generations,
	    best_number_generated_saved,
	    current_generated_state,
	    last_saved_state,
	    best_generated_state,
	    ptr_asa_out,
	    OPTIONS);
  free (curvature_flag);
  free (maximum_tangent);
  free (accepted_to_generated_ratio);
  free (temperature_scale_cost);
  free (current_cost_temperature);
  free (initial_cost_temperature);
  free (number_generated);
  free (best_number_generated_saved);
  free (recent_number_generated);
  free (number_accepted);
  free (recent_number_acceptances);
  free (index_cost_acceptances);
  free (number_acceptances_saved);
  free (best_number_accepted_saved);
  free (number_invalid_generated_states);
  free (current_generated_state->parameter);
  free (last_saved_state->parameter);
  free (best_generated_state->parameter);
  free (current_generated_state);
  free (last_saved_state);
  free (best_generated_state);
#if ASA_QUEUE
  free (save_queue_flag);
  free (save_queue_cost);
  free (save_queue_param);
#endif
#if ASA_PARALLEL
  for (index_parallel = 0; index_parallel < parallel_block_max;
       ++index_parallel)
    {
      free (gener_block_state[index_parallel].parameter);
    }
  free (gener_block_state);
#endif
//  free (initial_user_parameter_temp);
//  free (index_exit_v);
//  free (start_sequence);
//  free (index_parameter_generations);
//  free (current_user_parameter_temp);
//  free (temperature_scale_parameters);
//  if (recursive_asa_open == 0)
//    asa_open = FALSE;
//	
//  free(OPTIONS);
//  free(parameter_type);
//  free(number_parameters);
//  free(curvature);
//  free(tangents);
//  free(parameter_initial_final);
//  free(parameter_maximum);
//  free(parameter_minimum);
//  free(valid_state_generated_flag);
//  free(exit_status);
//  free(seed);

  return (final_cost);
}
/*F asa_exit
**
**  DESCRIPTION
**	This procedures copies the best parameters and cost into
**       final_cost and parameter_initial_final
**
**  REMARKS
*/
void
SimulatedAnnealing::
asa_exit (double (*user_cost_function) (double *),
	  double *final_cost,
	  double *parameter_initial_final,
	  double *parameter_minimum,
	  double *parameter_maximum,
	  double *tangents,
	  double *curvature,
	  double *maximum_tangent,
	  double *current_cost_temperature,
	  double *initial_user_parameter_temp,
	  double *current_user_parameter_temp,
	  double *accepted_to_generated_ratio,
	  ALLOC_INT * number_parameters,
	  int *parameter_type,
	  int *valid_state_generated_flag,
	  int *exit_status,
	  ALLOC_INT * index_exit_v,
	  ALLOC_INT * start_sequence,
	  LONG_INT * number_accepted,
	  LONG_INT * best_number_accepted_saved,
	  LONG_INT * index_cost_acceptances,
	  LONG_INT * number_generated,
	  LONG_INT * number_invalid_generated_states,
	  LONG_INT * index_parameter_generations,
	  LONG_INT * best_number_generated_saved,
	  STATE * current_generated_state,
	  STATE * last_saved_state,
	  STATE * best_generated_state,
	  FILE * ptr_asa_out,
	  USER_DEFINES * OPTIONS)
{
  ALLOC_INT index_v;		/* iteration index */
  int *curvature_flag;
  int tmp_locate;

  tmp_locate = OPTIONS->Locate_Cost;

  if ((curvature_flag =
       (int *) calloc (1, sizeof (int))) == NULL)
      exit (9);

  if (*exit_status != TOO_MANY_INVALID_STATES
      && *exit_status != IMMEDIATE_EXIT
      && *exit_status != INVALID_USER_INPUT
      && *exit_status != INVALID_COST_FUNCTION)
    {
      if (OPTIONS->Curvature_0 != TRUE)
	OPTIONS->Locate_Cost = 5;	/* calc curvatures while exiting asa */

      /* calculate curvatures and tangents at best point */
      *curvature_flag = TRUE;
      cost_derivatives (user_cost_function,
			parameter_minimum,
			parameter_maximum,
			tangents,
			curvature,
			maximum_tangent,
			number_parameters,
			parameter_type,
			exit_status,
			curvature_flag,
			valid_state_generated_flag,
			number_invalid_generated_states,
			current_generated_state,
			best_generated_state,
			ptr_asa_out,
			OPTIONS);
    }
  /* return final function minimum and associated parameters */
  *final_cost = best_generated_state->cost;
  VFOR (index_v)
  {
    parameter_initial_final[index_v] =
      best_generated_state->parameter[index_v];
  }

  OPTIONS->N_Accepted = *best_number_accepted_saved;
  OPTIONS->N_Generated = *best_number_generated_saved;

#if ASA_PRINT
  if (*exit_status != INVALID_USER_INPUT
      && *exit_status != INVALID_COST_FUNCTION)
    print_state (parameter_minimum,
		 parameter_maximum,
		 tangents,
		 curvature,
		 current_cost_temperature,
		 current_user_parameter_temp,
		 accepted_to_generated_ratio,
		 number_parameters,
		 curvature_flag,
		 number_accepted,
		 index_cost_acceptances,
		 number_generated,
		 number_invalid_generated_states,
		 last_saved_state,
		 best_generated_state,
		 ptr_asa_out,
		 OPTIONS);

  switch (*exit_status)
    {
    case NORMAL_EXIT:
      fprintf (ptr_asa_out,
	       "\n\n NORMAL_EXIT exit_status = %d\n",
	       *exit_status);
      break;
    case P_TEMP_TOO_SMALL:
      fprintf (ptr_asa_out,
	       "\n\n P_TEMP_TOO_SMALL exit_status = %d\n",
	       *exit_status);
      fprintf (ptr_asa_out,
#if INT_ALLOC
	       "current_user_parameter_temp[%d] too small = %*.*g\n",
#else
#if INT_LONG
	       "current_user_parameter_temp[%ld] too small = %*.*g\n",
#else
	       "current_user_parameter_temp[%d] too small = %*.*g\n",
#endif
#endif
	       *index_exit_v,
	  G_FIELD, G_PRECISION, current_user_parameter_temp[*index_exit_v]);
      break;
    case C_TEMP_TOO_SMALL:
      fprintf (ptr_asa_out,
	       "\n\n C_TEMP_TOO_SMALL exit_status = %d\n",
	       *exit_status);
      fprintf (ptr_asa_out,
	       "*current_cost_temperature too small = %*.*g\n",
	       G_FIELD, G_PRECISION, *current_cost_temperature);
      break;
    case COST_REPEATING:
      fprintf (ptr_asa_out,
	       "\n\n COST_REPEATING exit_status = %d\n",
	       *exit_status);
      break;
    case TOO_MANY_INVALID_STATES:
      fprintf (ptr_asa_out,
	       "\n\n  TOO_MANY_INVALID_STATES exit_status = %d\n",
	       *exit_status);
      break;
    case IMMEDIATE_EXIT:
      fprintf (ptr_asa_out,
	       "\n\n  IMMEDIATE_EXIT exit_status = %d\n",
	       *exit_status);
      break;
    case INVALID_USER_INPUT:
      fprintf (ptr_asa_out,
	       "\n\n  INVALID_USER_INPUT exit_status = %d\n",
	       *exit_status);
      break;
    case INVALID_COST_FUNCTION:
      fprintf (ptr_asa_out,
	       "\n\n  INVALID_COST_FUNCTION exit_status = %d\n",
	       *exit_status);
      break;
    default:
      fprintf (ptr_asa_out, "\n\n ERR: no exit code available = %d\n",
	       *exit_status);
    }

  switch (OPTIONS->Locate_Cost)
    {
    case 0:
      fprintf (ptr_asa_out,
	       " Locate_Cost = %d, initial cost temperature\n",
	       OPTIONS->Locate_Cost);
      break;
    case 1:
      fprintf (ptr_asa_out,
	       " Locate_Cost = %d, initial cost value\n",
	       OPTIONS->Locate_Cost);
      break;
    case 2:
      fprintf (ptr_asa_out,
	       " Locate_Cost = %d, new generated state\n",
	       OPTIONS->Locate_Cost);
      break;
    case 12:
      fprintf (ptr_asa_out,
      " Locate_Cost = %d, new generated state just after a new best state\n",
	       OPTIONS->Locate_Cost);
      break;
    case 3:
      fprintf (ptr_asa_out,
	    " Locate_Cost = %d, cost derivatives, reannealing parameters\n",
	       OPTIONS->Locate_Cost);
      break;
    case 4:
      fprintf (ptr_asa_out,
	       " Locate_Cost = %d, reannealing cost temperature\n",
	       OPTIONS->Locate_Cost);
      break;
    case 5:
      fprintf (ptr_asa_out,
	 " Locate_Cost = %d, calculating curvatures while exiting asa ()\n",
	       OPTIONS->Locate_Cost);
      break;
    case -1:
      fprintf (ptr_asa_out,
      " Locate_Cost = %d, exited main asa () loop by user-defined OPTIONS\n",
	       OPTIONS->Locate_Cost);
      break;
    default:
      fprintf (ptr_asa_out,
	       " Locate_Cost = %d, no index available for Locate_Cost\n",
	       OPTIONS->Locate_Cost);
    }

  if (*exit_status != INVALID_USER_INPUT
      && *exit_status != INVALID_COST_FUNCTION)
    {
      fprintf (ptr_asa_out,
	       "final_cost = best_generated_state->cost = %-*.*g\n",
	       G_FIELD, G_PRECISION, *final_cost);
#if INT_LONG
      fprintf (ptr_asa_out,
	       "*number_accepted at best_generated_state->cost = %ld\n",
	       *best_number_accepted_saved);
      fprintf (ptr_asa_out,
	       "*number_generated at best_generated_state->cost = %ld\n",
	       *best_number_generated_saved);
#else
      fprintf (ptr_asa_out,
	       "*number_accepted at best_generated_state->cost = %d\n",
	       *best_number_accepted_saved);
      fprintf (ptr_asa_out,
	       "*number_generated at best_generated_state->cost = %d\n",
	       *best_number_generated_saved);
#endif
    }
#endif

#if ASA_TEMPLATE_SELFOPT
  if (OPTIONS->Asa_Data[0] > (double) MIN_DOUBLE)
    OPTIONS->Asa_Data[1] = (double) (*best_number_generated_saved);
#endif

  /* reset OPTIONS->Sequential_Parameters */
  OPTIONS->Sequential_Parameters = *start_sequence;

  /* return unused space */
  free (curvature_flag);

#if ASA_PRINT
#if TIME_CALC
  /* print ending time */
  print_time ("asa_end", ptr_asa_out);
#endif
  fprintf (ptr_asa_out, "\n\n\n");
  fflush (ptr_asa_out);
  fclose (ptr_asa_out);
#endif
}
/*F cost_derivatives
**
**  DESCRIPTION
**	This procedure calculates the derivatives of the cost function
**	with respect to its parameters.  The first derivatives are
**	used as a sensitivity measure for reannealing.  The second
**	derivatives are calculated only if *curvature_flag=TRUE;
**	these are a measure of the covariance of the fit when a
**	minimum is found.
**
**  REMARKS
*/
	  /* Calculate the numerical derivatives of the best
	     generated state found so far */

	  /* In this implementation of ASA, no checks are made for
	     *valid_state_generated_flag=FALSE for differential neighbors
	     to the current best state. */

	  /* Assuming no information is given about the metric of the parameter
	     space, use simple Cartesian space to calculate curvatures. */

void
SimulatedAnnealing::
cost_derivatives (double (*user_cost_function) (double *),
		  double *parameter_minimum,
		  double *parameter_maximum,
		  double *tangents,
		  double *curvature,
		  double *maximum_tangent,
		  ALLOC_INT * number_parameters,
		  int *parameter_type,
		  int *exit_status,
		  int *curvature_flag,
		  int *valid_state_generated_flag,
		  LONG_INT * number_invalid_generated_states,
		  STATE * current_generated_state,
		  STATE * best_generated_state,
		  FILE * ptr_asa_out,
		  USER_DEFINES * OPTIONS)
{
  ALLOC_INT index_v, index_vv, index_v_vv, index_vv_v;
  LONG_INT saved_num_invalid_gen_states;
#if ASA_PRINT
  LONG_INT tmp_saved;
#endif
  double parameter_v, parameter_vv, parameter_v_offset, parameter_vv_offset;
  double recent_best_cost;
  double new_cost_state_1, new_cost_state_2, new_cost_state_3;
  double delta_parameter_v, delta_parameter_vv;
  int immediate_flag;

  if (OPTIONS->Curvature_0 == TRUE)
    *curvature_flag = FALSE;
  if (OPTIONS->Curvature_0 == -1)
    *curvature_flag = TRUE;

  /* save Immediate_Exit flag */
  immediate_flag = OPTIONS->Immediate_Exit;

  /* save the best cost */
  recent_best_cost = best_generated_state->cost;

  /* copy the best state into the current state */
  VFOR (index_v)
  {
    /* ignore parameters with too small ranges */
    if (PARAMETER_RANGE_TOO_SMALL (index_v))
      continue;
    current_generated_state->parameter[index_v] =
      best_generated_state->parameter[index_v];
  }

  saved_num_invalid_gen_states = (*number_invalid_generated_states);

  /* set parameters (& possibly constraints) to best state */
  *valid_state_generated_flag = TRUE;
#if USER_ACCEPTANCE_TEST
  OPTIONS->User_Acceptance_Flag = TRUE;
  OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif
  current_generated_state->cost =
    user_cost_function (current_generated_state->parameter);

  if (COST_FUNCTION_TEST (current_generated_state->cost))
    {
      *exit_status = INVALID_COST_FUNCTION;
      return;
    }
  if (*valid_state_generated_flag == FALSE)
    ++(*number_invalid_generated_states);

  if (OPTIONS->User_Tangents == TRUE)
    {
      *valid_state_generated_flag = FALSE;
#if USER_ACCEPTANCE_TEST
      OPTIONS->User_Acceptance_Flag = TRUE;
      OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif
      current_generated_state->cost =
		user_cost_function (current_generated_state->parameter);

    if (COST_FUNCTION_TEST (current_generated_state->cost))
	{
	  *exit_status = INVALID_COST_FUNCTION;
	  return;
	}
      if (*valid_state_generated_flag == FALSE)
	++(*number_invalid_generated_states);
    }
  else
    {
      /* calculate tangents */
      VFOR (index_v)
      {
	if (NO_REANNEAL (index_v))
	  {
	    tangents[index_v] = ZERO;
	    continue;
	  }
	/* skip parameters with too small range or integer parameters */
	if (OPTIONS->Include_Integer_Parameters == TRUE)
	  {
	    if (PARAMETER_RANGE_TOO_SMALL (index_v))
	      {
		tangents[index_v] = ZERO;
		continue;
	      }
	  }
	else
	  {
	    if (PARAMETER_RANGE_TOO_SMALL (index_v) ||
		INTEGER_PARAMETER (index_v))
	      {
		tangents[index_v] = ZERO;
		continue;
	      }
	  }

	/* save the v_th parameter and delta_parameter */
	parameter_v = best_generated_state->parameter[index_v];
#if DELTA_PARAMETERS
	delta_parameter_v = OPTIONS->User_Delta_Parameter[index_v];
#else
	delta_parameter_v = OPTIONS->Delta_X;
#endif

	parameter_v_offset = (ONE + delta_parameter_v) * parameter_v;
	if (parameter_v_offset > parameter_maximum[index_v] ||
	    parameter_v_offset < parameter_minimum[index_v])
	  {
	    delta_parameter_v = -delta_parameter_v;
	    parameter_v_offset = (ONE + delta_parameter_v) * parameter_v;
	  }

	/* generate the first sample point */
	current_generated_state->parameter[index_v] = parameter_v_offset;
	*valid_state_generated_flag = TRUE;
#if USER_ACCEPTANCE_TEST
	OPTIONS->User_Acceptance_Flag = TRUE;
	OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif
	current_generated_state->cost =
	  user_cost_function (current_generated_state->parameter);

	if (COST_FUNCTION_TEST (current_generated_state->cost))
	  {
	    *exit_status = INVALID_COST_FUNCTION;
	    return;
	  }
	if (*valid_state_generated_flag == FALSE)
	  ++(*number_invalid_generated_states);
	new_cost_state_1 = current_generated_state->cost;

	/* restore the parameter state */
	current_generated_state->parameter[index_v] = parameter_v;

	/* calculate the numerical derivative */
	tangents[index_v] = (new_cost_state_1 - recent_best_cost)
	  / (delta_parameter_v * parameter_v + (double) EPS_DOUBLE);

      }
    }

  /* find the maximum |tangent| from all tangents */
  *maximum_tangent = 0;
  VFOR (index_v)
  {
    if (NO_REANNEAL (index_v))
      continue;

    /* ignore too small ranges and integer parameters types */
    if (OPTIONS->Include_Integer_Parameters == TRUE)
      {
	if (PARAMETER_RANGE_TOO_SMALL (index_v))
	  continue;
      }
    else
      {
	if (PARAMETER_RANGE_TOO_SMALL (index_v) ||
	    INTEGER_PARAMETER (index_v))
	  continue;
      }

    /* find the maximum |tangent| (from all tangents) */
    if (fabs (tangents[index_v]) > *maximum_tangent)
      {
	*maximum_tangent = fabs (tangents[index_v]);
      }
  }

  if (*curvature_flag == TRUE || *curvature_flag == -1)
    {
      /* calculate diagonal curvatures */
      VFOR (index_v)
      {
	if (NO_REANNEAL (index_v))
	  {
	    index_v_vv = ROW_COL_INDEX (index_v, index_v);
	    curvature[index_v_vv] = ZERO;
	    continue;
	  }
	/* skip parameters with too small range or integer parameters */
	if (OPTIONS->Include_Integer_Parameters == TRUE)
	  {
	    if (PARAMETER_RANGE_TOO_SMALL (index_v))
	      {
		index_v_vv = ROW_COL_INDEX (index_v, index_v);
		curvature[index_v_vv] = ZERO;
		continue;
	      }
	  }
	else
	  {
	    if (PARAMETER_RANGE_TOO_SMALL (index_v) ||
		INTEGER_PARAMETER (index_v))
	      {
		index_v_vv = ROW_COL_INDEX (index_v, index_v);
		curvature[index_v_vv] = ZERO;
		continue;
	      }
	  }

	/* save the v_th parameter and delta_parameter */
	parameter_v = best_generated_state->parameter[index_v];
#if DELTA_PARAMETERS
	delta_parameter_v = OPTIONS->User_Delta_Parameter[index_v];
#else
	delta_parameter_v = OPTIONS->Delta_X;
#endif

	if (parameter_v + delta_parameter_v * fabs (parameter_v)
	    > parameter_maximum[index_v])
	  {
	    /* generate the first sample point */
	    current_generated_state->parameter[index_v] =
	      parameter_v - TWO * delta_parameter_v * fabs (parameter_v);
	    *valid_state_generated_flag = TRUE;
#if USER_ACCEPTANCE_TEST
	    OPTIONS->User_Acceptance_Flag = TRUE;
	    OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif
	    current_generated_state->cost =
	      user_cost_function (current_generated_state->parameter);

		if (COST_FUNCTION_TEST (current_generated_state->cost))
	      {
		*exit_status = INVALID_COST_FUNCTION;
		return;
	      }
	    if (*valid_state_generated_flag == FALSE)
	      ++(*number_invalid_generated_states);
	    new_cost_state_1 = current_generated_state->cost;

	    /* generate the second sample point */
	    current_generated_state->parameter[index_v] =
	      parameter_v - delta_parameter_v * fabs (parameter_v);

	    *valid_state_generated_flag = TRUE;
#if USER_ACCEPTANCE_TEST
	    OPTIONS->User_Acceptance_Flag = TRUE;
	    OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif
	    current_generated_state->cost =
	      user_cost_function (current_generated_state->parameter);

		if (COST_FUNCTION_TEST (current_generated_state->cost))
	      {
		*exit_status = INVALID_COST_FUNCTION;
		return;
	      }
	    if (*valid_state_generated_flag == FALSE)
	      ++(*number_invalid_generated_states);
	    new_cost_state_2 = current_generated_state->cost;

	    /* restore the parameter state */
	    current_generated_state->parameter[index_v] =
	      parameter_v;

	    /* index_v_vv: row index_v, column index_v */
	    index_v_vv = ROW_COL_INDEX (index_v, index_v);

	    /* calculate and store the curvature */
	    curvature[index_v_vv] =
	      (recent_best_cost - TWO * new_cost_state_2
	       + new_cost_state_1) / (delta_parameter_v * delta_parameter_v
			 * parameter_v * parameter_v + (double) EPS_DOUBLE);
	  }
	else if (parameter_v - delta_parameter_v * fabs (parameter_v)
		 < parameter_minimum[index_v])
	  {
	    /* generate the first sample point */
	    current_generated_state->parameter[index_v] =
	      parameter_v + TWO * delta_parameter_v * fabs (parameter_v);
	    *valid_state_generated_flag = TRUE;
#if USER_ACCEPTANCE_TEST
	    OPTIONS->User_Acceptance_Flag = TRUE;
	    OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif
	    current_generated_state->cost =
	      user_cost_function (current_generated_state->parameter);

		if (COST_FUNCTION_TEST (current_generated_state->cost))
	      {
		*exit_status = INVALID_COST_FUNCTION;
		return;
	      }
	    if (*valid_state_generated_flag == FALSE)
	      ++(*number_invalid_generated_states);
	    new_cost_state_1 = current_generated_state->cost;

	    /* generate the second sample point */
	    current_generated_state->parameter[index_v] =
	      parameter_v + delta_parameter_v * fabs (parameter_v);

	    *valid_state_generated_flag = TRUE;
#if USER_ACCEPTANCE_TEST
	    OPTIONS->User_Acceptance_Flag = TRUE;
	    OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif
	    current_generated_state->cost =
	      user_cost_function (current_generated_state->parameter);

		if (COST_FUNCTION_TEST (current_generated_state->cost))
	      {
		*exit_status = INVALID_COST_FUNCTION;
		return;
	      }
	    if (*valid_state_generated_flag == FALSE)
	      ++(*number_invalid_generated_states);
	    new_cost_state_2 = current_generated_state->cost;

	    /* restore the parameter state */
	    current_generated_state->parameter[index_v] =
	      parameter_v;

	    /* index_v_vv: row index_v, column index_v */
	    index_v_vv = ROW_COL_INDEX (index_v, index_v);

	    /* calculate and store the curvature */
	    curvature[index_v_vv] =
	      (recent_best_cost - TWO * new_cost_state_2
	       + new_cost_state_1) / (delta_parameter_v * delta_parameter_v
			 * parameter_v * parameter_v + (double) EPS_DOUBLE);
	  }
	else
	  {
	    /* generate the first sample point */
	    parameter_v_offset = (ONE + delta_parameter_v) * parameter_v;
	    current_generated_state->parameter[index_v] = parameter_v_offset;
	    *valid_state_generated_flag = TRUE;
#if USER_ACCEPTANCE_TEST
	    OPTIONS->User_Acceptance_Flag = TRUE;
	    OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif
	    current_generated_state->cost =
	      user_cost_function (current_generated_state->parameter);

		if (COST_FUNCTION_TEST (current_generated_state->cost))
	      {
		*exit_status = INVALID_COST_FUNCTION;
		return;
	      }
	    if (*valid_state_generated_flag == FALSE)
	      ++(*number_invalid_generated_states);
	    new_cost_state_1 = current_generated_state->cost;

	    /* generate the second sample point */
	    current_generated_state->parameter[index_v] =
	      (ONE - delta_parameter_v) * parameter_v;

	    *valid_state_generated_flag = TRUE;
#if USER_ACCEPTANCE_TEST
	    OPTIONS->User_Acceptance_Flag = TRUE;
	    OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif
	    current_generated_state->cost =
	      user_cost_function (current_generated_state->parameter);

		if (COST_FUNCTION_TEST (current_generated_state->cost))
	      {
		*exit_status = INVALID_COST_FUNCTION;
		return;
	      }
	    if (*valid_state_generated_flag == FALSE)
	      ++(*number_invalid_generated_states);
	    new_cost_state_2 = current_generated_state->cost;

	    /* restore the parameter state */
	    current_generated_state->parameter[index_v] =
	      parameter_v;

	    /* index_v_vv: row index_v, column index_v */
	    index_v_vv = ROW_COL_INDEX (index_v, index_v);

	    /* calculate and store the curvature */
	    curvature[index_v_vv] =
	      (new_cost_state_2 - TWO * recent_best_cost
	       + new_cost_state_1) / (delta_parameter_v * delta_parameter_v
			 * parameter_v * parameter_v + (double) EPS_DOUBLE);
	  }
      }

      /* calculate off-diagonal curvatures */
      VFOR (index_v)
      {
	/* save the v_th parameter and delta_x */
	parameter_v = current_generated_state->parameter[index_v];
#if DELTA_PARAMETERS
	delta_parameter_v = OPTIONS->User_Delta_Parameter[index_v];
#else
	delta_parameter_v = OPTIONS->Delta_X;
#endif

	VFOR (index_vv)
	{
	  /* index_v_vv: row index_v, column index_vv */
	  index_v_vv = ROW_COL_INDEX (index_v, index_vv);
	  index_vv_v = ROW_COL_INDEX (index_vv, index_v);

	  if (NO_REANNEAL (index_vv) || NO_REANNEAL (index_v))
	    {
	      curvature[index_vv_v] = curvature[index_v_vv] = ZERO;
	      continue;
	    }

	  /* calculate only the upper diagonal */
	  if (index_v <= index_vv)
	    continue;

	  /* skip parms with too small range or integer parameters */
	  if (OPTIONS->Include_Integer_Parameters == TRUE)
	    {
	      if (PARAMETER_RANGE_TOO_SMALL (index_v) ||
		  PARAMETER_RANGE_TOO_SMALL (index_vv))
		{
		  curvature[index_vv_v] = curvature[index_v_vv] = ZERO;
		  continue;
		}
	    }
	  else
	    {
	      if (INTEGER_PARAMETER (index_v) ||
		  INTEGER_PARAMETER (index_vv) ||
		  PARAMETER_RANGE_TOO_SMALL (index_v) ||
		  PARAMETER_RANGE_TOO_SMALL (index_vv))
		{
		  curvature[index_vv_v] = curvature[index_v_vv] = ZERO;
		  continue;
		}
	    }
	  /* save the vv_th parameter and delta_parameter */
	  parameter_vv =
	    current_generated_state->parameter[index_vv];
#if DELTA_PARAMETERS
	  delta_parameter_vv = OPTIONS->User_Delta_Parameter[index_vv];
#else
	  delta_parameter_vv = OPTIONS->Delta_X;
#endif

	  /* generate first sample point */
	  parameter_v_offset = current_generated_state->parameter[index_v] =
	    (ONE + delta_parameter_v) * parameter_v;
	  parameter_vv_offset = current_generated_state->parameter[index_vv] =
	    (ONE + delta_parameter_vv) * parameter_vv;
	  if (parameter_v_offset > parameter_maximum[index_v] ||
	      parameter_v_offset < parameter_minimum[index_v])
	    {
	      delta_parameter_v = -delta_parameter_v;
	      current_generated_state->parameter[index_v] =
		(ONE + delta_parameter_v) * parameter_v;
	    }
	  if (parameter_vv_offset > parameter_maximum[index_vv] ||
	      parameter_vv_offset < parameter_minimum[index_vv])
	    {
	      delta_parameter_vv = -delta_parameter_vv;
	      current_generated_state->parameter[index_vv] =
		(ONE + delta_parameter_vv) * parameter_vv;
	    }

	  *valid_state_generated_flag = TRUE;
#if USER_ACCEPTANCE_TEST
	  OPTIONS->User_Acceptance_Flag = TRUE;
	  OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif
	  current_generated_state->cost =
	    user_cost_function (current_generated_state->parameter);

	  if (COST_FUNCTION_TEST (current_generated_state->cost))
	    {
	      *exit_status = INVALID_COST_FUNCTION;
	      return;
	    }
	  if (*valid_state_generated_flag == FALSE)
	    ++(*number_invalid_generated_states);
	  new_cost_state_1 = current_generated_state->cost;

	  /* restore the v_th parameter */
	  current_generated_state->parameter[index_v] =
	    parameter_v;

	  /* generate second sample point */
	  *valid_state_generated_flag = TRUE;
#if USER_ACCEPTANCE_TEST
	  OPTIONS->User_Acceptance_Flag = TRUE;
	  OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif
	  current_generated_state->cost =
	    user_cost_function (current_generated_state->parameter);

		if (COST_FUNCTION_TEST (current_generated_state->cost))
	    {
	      *exit_status = INVALID_COST_FUNCTION;
	      return;
	    }
	  if (*valid_state_generated_flag == FALSE)
	    ++(*number_invalid_generated_states);
	  new_cost_state_2 = current_generated_state->cost;

	  /* restore the vv_th parameter */
	  current_generated_state->parameter[index_vv] =
	    parameter_vv;

	  /* generate third sample point */
	  current_generated_state->parameter[index_v] =
	    (ONE + delta_parameter_v) * parameter_v;
	  *valid_state_generated_flag = TRUE;
#if USER_ACCEPTANCE_TEST
	  OPTIONS->User_Acceptance_Flag = TRUE;
	  OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif
	  current_generated_state->cost =
	    user_cost_function (current_generated_state->parameter);

	  if (COST_FUNCTION_TEST (current_generated_state->cost))
	    {
	      *exit_status = INVALID_COST_FUNCTION;
	      return;
	    }
	  if (*valid_state_generated_flag == FALSE)
	    ++(*number_invalid_generated_states);
	  new_cost_state_3 = current_generated_state->cost;

	  /* restore the v_th parameter */
	  current_generated_state->parameter[index_v] =
	    parameter_v;

	  /* calculate and store the curvature */
	  curvature[index_vv_v] = curvature[index_v_vv] =
	    (new_cost_state_1 - new_cost_state_2
	     - new_cost_state_3 + recent_best_cost)
	    / (delta_parameter_v * delta_parameter_vv
	       * parameter_v * parameter_vv
	       + (double) EPS_DOUBLE);
	}
      }
    }

  /* restore Immediate_Exit flag */
  OPTIONS->Immediate_Exit = immediate_flag;

  /* restore the best cost function value */
  current_generated_state->cost = recent_best_cost;
#if ASA_PRINT
  tmp_saved = *number_invalid_generated_states - saved_num_invalid_gen_states;
  if (tmp_saved > 0)
#if INT_LONG
    fprintf (ptr_asa_out,
	  "Generated %ld invalid states when calculating the derivatives\n",
	     tmp_saved);
#else
    fprintf (ptr_asa_out,
	   "Generated %d invalid states when calculating the derivatives\n",
	     tmp_saved);
#endif
#endif /* ASA_PRINT */
  *number_invalid_generated_states = saved_num_invalid_gen_states;
#if USER_ACCEPTANCE_TEST
  OPTIONS->User_Acceptance_Flag = TRUE;
  OPTIONS->Cost_Acceptance_Flag = FALSE;
#endif
}



/*S BaseDataSimAnnAlgorithm
 */ 
/*F BaseDataSimAnnAlgorithm()  . . . . . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSimAnnAlgorithm::BaseDataSimAnnAlgorithm()
: TheUpperLowerS("TheUpperLower"),
  TheFunctionToOptimizeS("TheFunctionToOptimize"),
  TestTheOptS("TestTheOpt"),
  TestTheOpt(false),
  TrainMatrixObjectS("TrainMatrixObject"),
  TestMatrixObjectS("TestMatrixObject"),
  TheOptimizedParsS("TheOptimizedPars")
//  KindOfTestS("KindOfTest")
{
  Identification = SIMANNALG_ID;
  NameTag = SIMANNALG_NAME;
  SetType(Identification);
  String name("Object.");
  name.AppendToEnd(NameTag);
  EncodeDecodeClass = name;
} 
/*F BaseDataSimAnnAlgorithm(data)  . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    data: data to be copied
**
**  REMARKS
**
*/
BaseDataSimAnnAlgorithm::BaseDataSimAnnAlgorithm(const BaseDataSimAnnAlgorithm& data)
  : BaseDataAlgorithmOperation(data)
{
}
/*F ~BaseDataSimAnnAlgorithm()  . . . . . . . . . . . . . . . . . . . destructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
BaseDataSimAnnAlgorithm::~BaseDataSimAnnAlgorithm()
{
} 
/*F Read(in,objc) . . . . . . . . . . . . . . . . . .  Read in BaseDataSimAnnAlgorithm
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**
**  REMARKS
**
*/
bool BaseDataSimAnnAlgorithm::Read(istream& in, DataObjectClass* objc)
{
  StreamObjectInput str(in,' ');
  NameTag = str.ReadNext();
  return Read(in,objc,NameTag);
}
/*F Read(in,objc,name)  . . . . . . . . . . . . . . .  Read in BaseDataSimAnnAlgorithm
**
**  DESCRIPTION
**    in: The input stream
**    objc: The class definition
**    name: The name of the object (already assigned)
**
**  REMARKS
**
*/
bool BaseDataSimAnnAlgorithm::Read(istream& in, DataObjectClass* objc, const String& name)
{
  bool result = BaseDataAlgorithmOperation::Read(in,objc,name);

  // The rest

  return result;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . .  BaseDataSimAnnAlgorithm
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**  REMARKS
**
*/
ostream& BaseDataSimAnnAlgorithm::print(ostream& out) const
{
  BaseDataAlgorithmOperation::print(out);
  // The rest
//  out << "TheFunctionToOptimize:" << endl;
//  TheFunctionToOptimize->print(out);
//  out << "MatrixObject:" << endl;
//  MatrixObject->print(out);
//  out << "TheUpperLower :" << endl;
//  TheUpperLower->print(out);
  
  return out;
}
/*F obj = Clone() . . . . . . . . . . . . . . . . . . . . . . .BaseDataSimAnnAlgorithm
**
**  DESCRIPTION
**    obj: The copy
**
**  REMARKS
**
*/
Identify * BaseDataSimAnnAlgorithm::Clone()
{
  BaseDataSimAnnAlgorithm *obj = new BaseDataSimAnnAlgorithm;
  obj->CopyClone(this);
  return obj;
}
/*F CopyClone(obj)  . . . . . . . . . . . . . . . . . . . . . .BaseDataSimAnnAlgorithm
**
**  DESCRIPTION
**    obj: The object to be copied
**
**  REMARKS
**
*/
void BaseDataSimAnnAlgorithm::CopyClone(Identify * obj)
{
  BaseDataSimAnnAlgorithm *objfull = (BaseDataSimAnnAlgorithm *) obj;
  
  *this = *objfull;
}
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSimAnnAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSimAnnAlgorithm::EncodeThis(CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::EncodeThis(buffer);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . .  BaseDataSimAnnAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool BaseDataSimAnnAlgorithm::DecodeThis (CommBuffer& buffer)
{
  bool result = BaseDataAlgorithmOperation::DecodeThis(buffer);
  return result;
}
/*F ans = SetUpAlgorithms(instances,instancesclass,run,runclass)  . algorithm
**
**  DESCRIPTION
**    instances: The set of instances
**    instancesclass: The set of instance object classes
**    run: The algorithm run information
**    runclass: The run class
**    
**  REMARKS
**
*/
bool BaseDataSimAnnAlgorithm::SetUpAlgorithms(BaseDataSetOfInstances*,
						      DataSetOfInstancesClass*,
						      BaseDataAlgorithmRun* ,
						      DataAlgorithmRunClass*)
{
  return true;
}
/*F ans = CheckInput(instances,instancesclass,run,runclass) . . . . BaseDataSimAnnAlgorithm
**
**  DESCRIPTION
**    instances:     The set of instances
**    instancesclass: The instance classes
**    run:            The algorithm run class
**    runclass:       The class of algorithm run
**    
**  REMARKS
**
*/
bool BaseDataSimAnnAlgorithm::CheckInput(BaseDataSetOfInstances*,
					DataSetOfInstancesClass*,
					BaseDataAlgorithmRun* run,
					DataAlgorithmRunClass*)
{
  bool result = true;


  if(run->AlgorithmSummary.KeyWordInList(TestTheOptS)) {
    TestTheOpt = true;
    if(run->ParameterInList(TheOptimizedParsS)) {
      if(run->ParameterInList(TestMatrixObjectS)) {
      }
      else {
        cerr << "Error: TestMatrixObject Parameters: '" << TestMatrixObjectS << "' not found" << endl;
        result = false; 
      }				
    }
    else {
      cerr << "Error: Optimized Parameters: '" << TheOptimizedParsS << "' not found" << endl;
      result = false; 
    }				
  }
  else {
    TestTheOpt = false;
    if(run->ParameterInList(TrainMatrixObjectS)) {
    }
    else {
      cerr << "Error: TrainMatrixObject Parameters: '" << TrainMatrixObjectS << "' not found" << endl;
      result = false; 
    }				
  }

  if(run->ParameterInList(TheFunctionToOptimizeS)) {
//    if(run->ParameterInList(KindOfTestS)) {
//    }
//    else {
//      cerr << "Error: KindOfTest Parameter: '" << KindOfTestS << "' not found." << endl;
//      result = false;
//    }
  }
  else {
    cerr << "Error: Function To Optimize: '" << TheFunctionToOptimizeS << "' not found" << endl;
    result = false; 
  }
  
  return result;
}
/*F ans = SetUpInput(instances,instancesclass,run,runclass) . . . . BaseDataSimAnnAlgorithm
**
**  DESCRIPTION
**    instances:     The set of instances
**    instancesclass: The instance classes
**    run:            The algorithm run class
**    runclass:       The class of algorithm run
**
**  REMARKS
**
*/
bool BaseDataSimAnnAlgorithm::SetUpInput(BaseDataSetOfInstances*,
					DataSetOfInstancesClass*,
					BaseDataAlgorithmRun* run,
					DataAlgorithmRunClass*)
{
  bool result = true;
  
  if(TestTheOpt) 
    {
      TheOptimizedPars = (BaseDataInstanceDoubleVector *) run->ParameterValue(TheOptimizedParsS);
      TestMatrixObject = (BaseDataInstanceDoubleMatrix *) run->ParameterValue(TestMatrixObjectS);
    }
  else 
    {
      TrainMatrixObject = (BaseDataInstanceDoubleMatrix *) run->ParameterValue(TrainMatrixObjectS)->Clone();
    }
  TheUpperLower = (BaseDataSimAnnUpperLower *) run->ParameterValue(TheUpperLowerS)->Clone();
  TheFunctionToOptimize = (BaseDataFunctionToOptimize *) run->ParameterValue(TheFunctionToOptimizeS)->Clone();
  
  if(TestTheOpt) 
    {
      TheFunctionToOptimize->setTheOptMat(TestMatrixObject);
    }
  else 
    {
      TheFunctionToOptimize->setTheOptMat(TrainMatrixObject);
    }
  TheFunctionToOptimize->createTheParToFct();
  
  if(debugPrint > 0) {
    cout << endl;
    cout << "The Function To Optimize: " << endl;
    TheFunctionToOptimize->print(cout);    
    cout << endl;
    cout << "The Kind Of Test: " << endl;
    cout << endl;
    if(TestTheOpt) {
      cout << "The Test Matrix: " << endl;
      TestMatrixObject->print(cout);    
    }
    else 
      {
	cout << "The Train Matrix: " << endl;
	TrainMatrixObject->print(cout);    
      }
    cout << endl;
    cout << "The UpperLower: " << endl;
    TheUpperLower->print(cout);    
    cout << endl;
    cout << "Allowed KeyWord: ";
    cout << TestTheOptS << endl;
    if (TestTheOpt) 
      {
	cout << "The optimized results will be tested!" << endl;
      }
    cout << endl;
  }
  
  return result;
} 
/*F ans = Calculate(instances,instancesclass,run,runclass)  . . . . BaseDataSimAnnAlgorithm
**
**  DESCRIPTION
**    instances:     The set of instances
**    instancesclass: The instance classes
**    run:            The algorithm run class
**    runclass:       The class of algorithm run
**
**  REMARKS
**
*/
bool BaseDataSimAnnAlgorithm::Calculate(BaseDataSetOfInstances* instances,
				       DataSetOfInstancesClass* instancesclass,
				       BaseDataAlgorithmRun* run,
				       DataAlgorithmRunClass*)
{
  bool result = true;
  cout << "*******************************************************" << endl;
  cout << "SA	       BaseDataSimAnnAlgorithm::Calculate() called" << endl;
  cout << "*******************************************************" << endl;
  
  if(TestTheOpt == false) // i.e. optimize it
    { 
      CalculateOptimization();
      cout << "The Optimized Parameters" << endl;
      TheOptimizedPars->print(cout);
      cout << endl;
      run->AddParameter(TheOptimizedPars);
    }
  else 	// i.e. TestTheOpt == true, i.e. test the optimized result
    {
      result = CalculateTestFunction(instances);
    }
  return result;
}
 
/*F CalculateTestFunction()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataSimAnnAlgorithm::CalculateTestFunction(BaseDataSetOfInstances* instances)
{
  bool result = true;
      cout << "XXX orig. parameters: XXXXXXXXXXXXXX" << endl;
      TheFunctionToOptimize->TheParVec->print(cout);
      cout << "XXX opt. parameters: XXXXXXXXXXXXXXX" << endl;
      TheOptimizedPars->print(cout);
      cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;

      // to change: the original parameters are inside TheFunctionToOptimize!!!

      cout << "before testOptimizedResult" << endl;
      BaseDataInstanceDoubleMatrix *mat = 
	TheFunctionToOptimize->testOptimizedResult(TheFunctionToOptimize->TheParVec,
						   TheOptimizedPars,
						   TestMatrixObject);
      cout << "after testOptimizedResult" << endl;

      BaseDataKeyWords instNames = mat->getInstanceNames();
      ObjectList<String> names = instNames.GetKeyWords();
      BaseDataKeyWords parNames = mat->getParameterNames();
      ObjectList<String> pnames = parNames.GetKeyWords();

      ObjectList<String>::iterator iterNames;
      ObjectList<String>::iterator iterPNames;

      BaseDataReal *currReal = new BaseDataReal();

      for( iterNames=names.begin(); iterNames!=names.end(); iterNames++) 
	{
	  BaseDataInstance *currInst = (BaseDataInstance *) instances->GetInstance(*iterNames);

	  iterPNames = pnames.begin();
	  for(unsigned int countI=0; countI<mat->CurrentMatrix()[0].size(); countI++) 
	    {
	      int countP = 0;

	      currReal->NameTag = (*iterPNames);
	      currReal->SetValue( mat->CurrentMatrix()[countI][countP]);
	      currInst->AddObject(currReal);

	      countP++;
	      iterPNames++;
	    }
	}
return result;
}
 
/*F CalculateOptimization()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool BaseDataSimAnnAlgorithm::CalculateOptimization()
{
  bool result = true;
  cout << "XXX optimize XXXXXXXXXXXXXXXXXXXXXXXX" << endl;
  TheFunctionToOptimize->print(cout);
  cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
  
  SimulatedAnnealing	sa(TheFunctionToOptimize);
  cout << "After the SimulatedAnnealing Initialization" << endl;

  sa.parAsaRun->USER_OPTIONS->Limit_Generated = 10;
  sa.parAsaRun->USER_OPTIONS->Cost_Precision = 1e-7;
  
  sa.calculate();
  
  cout << "\nAFTER RUN: "  << endl;
  cout << "parameter_dimension ";
  cout << sa.fToUse->TheParDim->GetValue() << endl;
  cout << sa.fToUse->TheParToFct->parameter_dimension[0] << endl;
  if (sa.fToUse->TheParDim->GetValue() != sa.fToUse->TheParToFct->parameter_dimension[0]) 
    {
      cerr << "Warning: The parameter dimensions does not fit!" << endl;		
    }
  int n = sa.fToUse->TheParDim->GetValue();
  VectorNumeric vec(n);
  VectorNumeric::iterator vecelement = vec.begin();
  for (int i=0; i<sa.fToUse->TheParDim->GetValue(); i++)
    {
      *vecelement = sa.fToUse->TheParToFct->cost_parameters[i];
      vecelement++;
      cout << "cost_parameters " << sa.fToUse->TheParToFct->cost_parameters[i] << endl;
      cout << "parameter_lower_bound " << sa.fToUse->TheParToFct->parameter_lower_bound[i] << endl;
      cout << "parameter_upper_bound " << sa.fToUse->TheParToFct->parameter_upper_bound[i] << endl;
      cout << "cost_tangents " << sa.fToUse->TheParToFct->cost_tangents[i] << endl;
      cout << "cost_curvature " << sa.cost_curvature[i] << endl;
      cout << "parameter_int_real " << sa.fToUse->TheParToFct->parameter_int_real[i] << endl;
    }
  BaseDataKeySet params;
  TheOptimizedPars = new BaseDataInstanceDoubleVector(vec,params);
  TheOptimizedPars->NameTag = TheOptimizedParsS;  
#if OPTIONS_FILE_DATA
  cout << "ptr_options " << saptr_options << endl;
#endif
  return result;
}

/*F ans = WriteOutputValues(instances,instancesclass,run,runclass)  BaseDataSimAnnAlgorithm
**
**  DESCRIPTION
**    instances:     The set of instances
**    instancesclass: The instance classes
**    run:            The algorithm run class
**    runclass:       The class of algorithm run
**    
**  REMARKS
**
*/
bool BaseDataSimAnnAlgorithm::WriteOutputValues(BaseDataSetOfInstances*,
					       DataSetOfInstancesClass*,
					       BaseDataAlgorithmRun* run,
					       DataAlgorithmRunClass*) 
{
  bool result = true;

//  run->AddParameter(MatrixObject);

  return result;
}
/*F ans = ConcludeRun(instances,instancesclass,run,runclass)  . . . BaseDataSimAnnAlgorithm
**
**  DESCRIPTION
**    instances:     The set of instances
**    instancesclass: The instance classes
**    run:            The algorithm run class
**    runclass:       The class of algorithm run
**    
**  REMARKS
**
*/
bool BaseDataSimAnnAlgorithm::ConcludeRun(BaseDataSetOfInstances*,
					 DataSetOfInstancesClass*,
					 BaseDataAlgorithmRun*,
					 DataAlgorithmRunClass* ) 
{
  return true;
}



/*S DataSimAnnAlgorithmClass
 */
/*F DataSimAnnAlgorithmClass() . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**
**  REMARKS
**
*/
DataSimAnnAlgorithmClass::DataSimAnnAlgorithmClass()
{
  Identification = SIMANNALG_ID;
  NameTag = SIMANNALG_NAME;
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = NameTag;
} 
/*F DataSimAnnAlgorithmClass(data) . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**     data: The class to be copied
**
**  REMARKS
**
*/
DataSimAnnAlgorithmClass::DataSimAnnAlgorithmClass(const DataSimAnnAlgorithmClass& data)
  : DataAlgorithmOperationClass(data)
{
} 
/*F DataSimAnnAlgorithmClass(id,name,descr)  . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    id: The ID of the object class
**    name: The name of the object class
**    descr: A text description of the object
**
**
**  REMARKS
**
*/
DataSimAnnAlgorithmClass::DataSimAnnAlgorithmClass(const int id, 
				 const String& name,
				 const String& descr)
  : DataAlgorithmOperationClass(id,name,descr)
{
  SubClass = "AlgorithmOperation";
  EncodeDecodeClass = SIMANNALG_NAME;
}
/*F out1 = print(out) . . . . . . . . . . . . . . . . . . . . DataSimAnnAlgorithmClass
**
**  DESCRIPTION
**    out1,out: The output buffer
**
**  REMARKS
**
*/
ostream& DataSimAnnAlgorithmClass::print(ostream& out) const
{
  DataAlgorithmOperationClass::print(out);
  // the rest
       
       return out;
}
/*F in1 = Read(in)  . . . . . . . . . . . . . . . . . . . . . DataSimAnnAlgorithmClass
**
**  DESCRIPTION
**    in,in1: The input buffer
**
**    This reads in the rest of the information (after the type
**    has been determined from the first line.  For the
**    base DataReformPredicateTestClass, there is no further information.
**
**  REMARKS
**
*/
bool DataSimAnnAlgorithmClass::Read(istream& in, DataSetOfObjectsClass &set)
{
  bool result = DataAlgorithmOperationClass::Read(in,set);

  return result;
}
/*F CopyClone(objc) . . . . . . . . . . . . . . . . . . . . . DataSimAnnAlgorithmClass
**
**  DESCRIPTION
**    objc: The class to be copied
**
**  REMARKS
**
*/
void DataSimAnnAlgorithmClass::CopyClone(Identify *  objc)
{
  DataSimAnnAlgorithmClass *objcfull = (DataSimAnnAlgorithmClass *) objc;
  *this = *objcfull;
}
/*F objc = Clone()  . . . . . . . . . . . . . . . . . . . . . DataSimAnnAlgorithmClass
**
**  DESCRIPTION
**    objc: The object class that was created
**
**  REMARKS
**
*/
Identify * DataSimAnnAlgorithmClass::Clone()
    {
      DataSimAnnAlgorithmClass* id = new DataSimAnnAlgorithmClass(*this);
      return (Identify *) id;
    }
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . DataSimAnnAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSimAnnAlgorithmClass::EncodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::EncodeThis(buffer);
  // result = result && Encode(buffer,------);

  return result;
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . DataSimAnnAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool DataSimAnnAlgorithmClass::DecodeThis(CommBuffer& buffer)
{
  bool result = DataAlgorithmOperationClass::DecodeThis(buffer);
//  result = result && Decode(buffer,-----);

  return result;
}
/*F obj = BaseDataObjectExample() . . . . . . . . . . . . .  create an object
**
**  DESCRIPTION
**    obj: The created object
**
**    This function is used to create an empty instance of a object 
**    given the class.  This is used so that the virtual functions
**    of the object can be used.
**
**  REMARKS
**
*/
BaseDataObject * DataSimAnnAlgorithmClass::BaseDataObjectExample()
{ 
  //cout << "Make BaseDataSimAnnAlgorithm Example\n";
  return (BaseDataObject *) new BaseDataSimAnnAlgorithm();
}
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . DataSimAnnAlgorithmClass
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, DataSimAnnAlgorithmClass*& obj)
     {
     obj = new DataSimAnnAlgorithmClass;
     return obj->DecodeThis(buffer);
     }
/*F ans = TopDecode(buffer,obj) . . . . . . . . . . . . . . . BaseDataSimAnnAlgorithm
**
**  DESCRIPTION
**    buffer: The buffer 
**    obj: The object
**    ans: True if successful
**
**  REMARKS
**
*/
bool TopDecode(CommBuffer& buffer, BaseDataSimAnnAlgorithm*& obj)
     {
     obj = new BaseDataSimAnnAlgorithm;
     return obj->DecodeThis(buffer);
     }
/*F AddSimAnnAlgorithmsClasses(set) . . . . . . . . . . . . add new classes
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void AddSimAnnAlgorithmsClasses(DataSetOfObjectsClass& set)
{
  String simAnnDescr("Algorithm: Simulated Annealing");
  String fctToOptDescr("Function To Optimize Class");
  String testFct1Descr("TestFunction1 Class");
  String simAnnUpperLowerDescr("Upper Lower Bounds Class");
  
  DataSimAnnAlgorithmClass simAnnTstClass(SIMANNALG_ID,SIMANNALG_NAME,simAnnDescr);
  DataFunctionToOptimizeClass fctToOptClass(OPERATION_FCTTOOPT_ID,OPERATION_FCTTOOPT_NAME,fctToOptDescr);
  DataTestFunction1Class testFct1Class(OPERATION_FCTTOOPTTEST_ID,OPERATION_FCTTOOPTTEST_NAME,testFct1Descr);
  DataSimAnnUpperLowerClass simAnnUpperLowerClass(SIMANNUPPERLOWER_ID,SIMANNUPPERLOWER_NAME,simAnnUpperLowerDescr);
      
  set.AddObjectClass(simAnnTstClass);
  set.AddObjectClass(fctToOptClass);
  set.AddObjectClass(testFct1Class);
  set.AddObjectClass(simAnnUpperLowerClass);
}
/*F InitialSimAnnAlgorithmsEncodeDecodeRoutines() . . .  instance algorithm
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
extern void InitialSimAnnAlgorithmsEncodeDecodeRoutines()
{
  EncodeDecodeRegisterClass(DataSimAnnAlgorithmClass,BaseDataSimAnnAlgorithm,SIMANNALG_NAME);
  EncodeDecodeRegisterClass(DataFunctionToOptimizeClass,BaseDataFunctionToOptimize,OPERATION_FCTTOOPT_NAME);
  EncodeDecodeRegisterClass(DataSimAnnUpperLowerClass,BaseDataSimAnnUpperLower,SIMANNUPPERLOWER_NAME);
  EncodeDecodeRegisterClass(DataTestFunction1Class,BaseDataTestFunction1,OPERATION_FCTTOOPTTEST_NAME);

//  bool (*toproutine)(CommBuffer&,Identify*&);
//
//  bool (*rout0)(CommBuffer&,BaseDataSimAnnAlgorithm*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout0;
//  SingleDecodeRoutine p0("Object.SimulatedAnnealingAlgorithm",toproutine);
//  (*SetOfEncodeDecodeRoutines)[p0.StructureName] = p0;
//
//  bool (*rout01)(CommBuffer&,DataSimAnnAlgorithmClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout01;
//  SingleDecodeRoutine p01("SimulatedAnnealingAlgorithm",toproutine);
//  (*SetOfEncodeDecodeRoutines)[p01.StructureName] = p01;
//
//
//  bool (*rout1)(CommBuffer&,BaseDataFunctionToOptimize*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout1;
//  SingleDecodeRoutine p1("Object.FunctionToOptimize",toproutine);
//  (*SetOfEncodeDecodeRoutines)[p1.StructureName] = p1;
//
//  bool (*rout11)(CommBuffer&,DataFunctionToOptimizeClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout11;
//  SingleDecodeRoutine p11("FunctionToOptimize",toproutine);
//  (*SetOfEncodeDecodeRoutines)[p11.StructureName] = p11;
//
//
//  bool (*rout2)(CommBuffer&,BaseDataSimAnnUpperLower*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout2;
//  SingleDecodeRoutine p2("Object.SimAnnUpperLower",toproutine);
//  (*SetOfEncodeDecodeRoutines)[p2.StructureName] = p2;
//
//  bool (*rout21)(CommBuffer&,DataSimAnnUpperLowerClass*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout21;
//  SingleDecodeRoutine p21("SimAnnUpperLower",toproutine);
//  (*SetOfEncodeDecodeRoutines)[p21.StructureName] = p21;
//
//  
//  bool (*rout3)(CommBuffer&,BaseDataTestFunction1*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout3;
//  SingleDecodeRoutine p3("Object.TestFunction1",toproutine);
//  (*SetOfEncodeDecodeRoutines)[p3.StructureName] = p3;
//
//  bool (*rout31)(CommBuffer&,DataTestFunction1Class*&) = TopDecode;
//  toproutine = (bool (*)(CommBuffer&,Identify*&)) rout31;
//  SingleDecodeRoutine p31("TestFunction1",toproutine);
//  (*SetOfEncodeDecodeRoutines)[p31.StructureName] = p31;
}



