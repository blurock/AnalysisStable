/*  FILE     SimulatedAnnealingType.hh
**  PACKAGE  SimulatedAnnealing
**  AUTHOR   
**
**  CONTENT
**    Class definitions for the "SimulatedAnnealing" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
*/
 
#ifndef BASIS_SimulatedAnnealingTYPE_HH
#define BASIS_SimulatedAnnealingTYPE_HH



/*C SimAnnHelpParameters
**
**  DESCRIPTION
**        
**  REMARKS
**
*/
class SimAnnHelpParameters
{
public:
	// help variables:
	#if OPTIONS_FILE
	  FILE *ptr_options;
	  char read_option[80];
	  int read_int;
	#if INT_LONG
	  LONG_INT read_long;
	#endif
	  double read_double;
	#endif

	SimAnnHelpParameters();
}; // end class SimAnnHelpParameters


      
/*C SimAnnParametersToAsaRun
**
**  DESCRIPTION
**        
**  REMARKS
**
*/
class SimAnnParametersToAsaRun : public virtual SimAnnHelpParameters
{
public:
	USER_DEFINES *USER_OPTIONS;

	SimAnnParametersToAsaRun();
	~SimAnnParametersToAsaRun();
};  // end class SimAnnParametersToAsaRun



/*C BaseDataSimAnnUpperLower . . . . . . . . . . . . .
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class BaseDataSimAnnUpperLower : public BaseDataObject
{
  VectorNumeric Upper;
  VectorNumeric Lower;
public:
  BaseDataSimAnnUpperLower();
  BaseDataSimAnnUpperLower(const BaseDataSimAnnUpperLower& data);
  BaseDataSimAnnUpperLower(const VectorNumeric& upper,
                           const VectorNumeric& lower);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  VectorNumeric getUpper();
  VectorNumeric getLower();
};  // end class BaseDataSimAnnUpperLower

/*C DataSimAnnUpperLowerClass . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataSimAnnUpperLowerClass : public DataObjectClass
{
public:
  DataSimAnnUpperLowerClass();
  DataSimAnnUpperLowerClass(const DataSimAnnUpperLowerClass& data);
  DataSimAnnUpperLowerClass(const int id, 
                            const String& name,
                            const String& descr);

  STANDARD_VIRTUAL_METHODS_CLASS;
};  // end class DataSimAnnUpperLowerClass



/*C SimAnnParametersToFunction
**
**  DESCRIPTION
**        
**  REMARKS
**
*/
class SimAnnParametersToFunction : public virtual SimAnnHelpParameters
{
public:
	// the number of parameters to optimize 
	ALLOC_INT *parameter_dimension;

	// pointer to array storage for asa arguments 
	double *parameter_lower_bound;
	double *parameter_upper_bound;

	double *cost_parameters;

	double *cost_tangents;

	// pointer to array storage for parameter type flags 
	int *parameter_int_real;
	
	BaseDataInstanceDoubleMatrix *TheOptMat;
	


	SimAnnParametersToFunction();
  SimAnnParametersToFunction(BaseDataInteger *parDim,
    BaseDataSimAnnUpperLower *upLow, 
		BaseDataDoubleVector *parVec,
		BaseDataInstanceDoubleMatrix *dataMat, 
		BaseDataDoubleVector *costTanVec,
		BaseDataDoubleVector *parIntRealVec);
	~SimAnnParametersToFunction();

	void initParFct(BaseDataInteger *parDim);
	void fillCost_Parameters(BaseDataDoubleVector *parVec);
	void fillCost_Tangents(BaseDataDoubleVector *costTanVec);
	void fillParameter_Int_Real(BaseDataDoubleVector *parIntRealVec);
	void fillUpperLower(BaseDataSimAnnUpperLower *upLow);
};  // end class SimAnnParametersToFunction



/*C BaseDataFunctionToOptimize  . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**
**  REMARKS
*/
class BaseDataFunctionToOptimize : public BaseDataOperation
{
public:
//  BaseDataInteger *KindOfTest;
  BaseDataInteger *TheParDim;
  BaseDataSimAnnUpperLower *TheUpLow;
  BaseDataDoubleVector *TheParVec;
	BaseDataInstanceDoubleMatrix *TheOptMat;
	BaseDataDoubleVector *TheCostTanVec;
	BaseDataDoubleVector *TheParIntRealVec;

  SimAnnParametersToFunction *TheParToFct;

  BaseDataFunctionToOptimize();
  BaseDataFunctionToOptimize(BaseDataInteger *parDim,
				BaseDataSimAnnUpperLower *upLow, 
				BaseDataDoubleVector *parVec,
				BaseDataInstanceDoubleMatrix *dataMat,
				BaseDataDoubleVector *costTanVec,
				BaseDataDoubleVector *parIntRealVec);
  BaseDataFunctionToOptimize(const BaseDataFunctionToOptimize& data);
  ~BaseDataFunctionToOptimize();

  STANDARD_VIRTUAL_METHODS_OBJECT;

  virtual BaseDataReal operator()(BaseDataDoubleVector *parToOpt, 
                                  BaseDataInstanceDoubleMatrix *dataMat,
                                  DataDoubleVectorClass *parToOptClass, 
                                  DataInstanceDoubleMatrixClass *dataMatClass);
	
	virtual BaseDataInstanceDoubleMatrix * testOptimizedResult(
																	 BaseDataDoubleVector *origPars, 
																	 BaseDataDoubleVector *optimizedPars, 
																	 BaseDataInstanceDoubleMatrix *dataMat);
																	 
//  void setKindOfTest(BaseDataInteger *intObj);
  void setTheOptMat(BaseDataInstanceDoubleMatrix *optMat);
  void createTheParToFct();
  ALLOC_INT parameterDimension(void);
//  void initKindOfTest(void);
}; // end class BaseDataFunctionToOptimize

/*C DataFunctionToOptimizeClass . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataFunctionToOptimizeClass : public DataOperationClass
{
public:
  DataFunctionToOptimizeClass();
  DataFunctionToOptimizeClass(const DataFunctionToOptimizeClass& data);
  DataFunctionToOptimizeClass(const int id, 
                              const String& name,
                              const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
};  // end class DataFunctionToOptimizeClass


/*C BaseDataSimAnnAlgorithm  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ReformPredicateTest class definitions
**
**  REMARKS
**    Inheirits BaseDataAlgorithmOperation
*/
class BaseDataSimAnnAlgorithm : public BaseDataAlgorithmOperation
{
  String TheUpperLowerS;
  BaseDataSimAnnUpperLower *TheUpperLower;
  String TheFunctionToOptimizeS;
  BaseDataFunctionToOptimize *TheFunctionToOptimize;
  String TestTheOptS;
  bool TestTheOpt;

  String TrainMatrixObjectS;
  BaseDataInstanceDoubleMatrix *TrainMatrixObject;
  String TestMatrixObjectS;
  BaseDataInstanceDoubleMatrix *TestMatrixObject;
  String TheOptimizedParsS;
  BaseDataInstanceDoubleVector *TheOptimizedPars;

public:
  BaseDataSimAnnAlgorithm();
  BaseDataSimAnnAlgorithm(const BaseDataSimAnnAlgorithm& data);
  ~BaseDataSimAnnAlgorithm();

  bool CalculateOptimization();
  bool CalculateTestFunction(BaseDataSetOfInstances* instances);
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
  STANDARD_VIRTUAL_METHODS_OBJECT;
};  // end class BaseDataSimAnnAlgorithm

/*C DataSimAnnAlgorithmClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataAlgorithmOperationClass
*/
class DataSimAnnAlgorithmClass : public DataAlgorithmOperationClass
{
public:
  DataSimAnnAlgorithmClass();
  DataSimAnnAlgorithmClass(const DataSimAnnAlgorithmClass& data);
  DataSimAnnAlgorithmClass(const int id, 
                           const String& name,
                           const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
};  // end class DataSimAnnAlgorithmClass




/*C SimulatedAnnealing
**
**  DESCRIPTION
**        
**  REMARKS
**
*/
//class SimulatedAnnealing : public SimAnnParametersToAsaRun 
class SimulatedAnnealing
{
public:
	// Declarations:
	int *exit_code;
	ALLOC_INT n_param;
	
	#if ASA_LIB
	#else
	  int compile_cnt;
	#endif
	#if ASA_TEMPLATE_SAMPLE
	  FILE *ptr_asa;
	#endif
	#if ASA_TEMPLATE_ASA_OUT_PID
	  char pid_file[15];
	  int pid_int;
	#endif

	double *cost_curvature;
	double cost_value;

	// valid flag for cost function 
	int *cost_flag;

	// seed for random number generator 
	LONG_INT *rand_seed;

	#if MY_TEMPLATE			// MY_TEMPLATE_main_decl 
	  // add some declarations if required 
	#endif
/*
	#if ASA_TEMPLATE_MULTIPLE
	  int n_asa, n_trajectory;
	  ALLOC_INT index;
	  char asa_file[8];
	// the following moved to constructor!
	//	#if HAVE_ANSI
	//	  char asa_file[8] = "asa_x_y";
	//	#else
	//	  char asa_file[8];
	//	  asa_file[0] = asa_file[2] = 'a';
	//	  asa_file[1] = 's';
	//	  asa_file[3] = asa_file[5] = '_';
	//	  asa_file[4] = 'x';
	//	  asa_file[6] = 'y';
	//	  asa_file[7] = '\0';
	//	#endif // HAVE_ANSI 
	#endif // ASA_TEMPLATE_MULTIPLE 
*/	
	FILE *ptr_out;

  SimAnnParametersToAsaRun *parAsaRun;
  USER_DEFINES *USER_OPTIONS;

	static BaseDataFunctionToOptimize* fToUse;
    
public:
  SimulatedAnnealing(BaseDataFunctionToOptimize* fct);
  ~SimulatedAnnealing();

	static double cstFunctionIntern(double *x) {
    VectorNumeric vecHlp(fToUse->parameterDimension());
		for (int i=0; i<fToUse->parameterDimension(); i++) {		
      vecHlp[i] = x[i];
		}
		
		BaseDataDoubleVector *parVec = new BaseDataDoubleVector(vecHlp);

    BaseDataReal r = fToUse->operator()(parVec, 
                                        fToUse->TheParToFct->TheOptMat,
                                        new DataDoubleVectorClass(),
                                        new DataInstanceDoubleMatrixClass());
    delete parVec;
		return r.GetValue();
	};

// Deklarations:
  double calculate();
	double asa (double (*user_cost_function) (double *),
		double (*user_random_generator) (LONG_INT *));
	void asa_exit (double (*user_cost_function) (double *),
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
		USER_DEFINES * OPTIONS);
	void cost_derivatives (double (*user_cost_function) (double *),
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
		USER_DEFINES * OPTIONS);
	void initSA(void);
};	// end class SimulatedAnnealing





/*C BaseDataTestFunction1
**
**  DESCRIPTION
**        
**  REMARKS
**
*/
class BaseDataTestFunction1 : public BaseDataFunctionToOptimize
{
public:
  BaseDataTestFunction1();
  BaseDataTestFunction1(const BaseDataTestFunction1& data);
  BaseDataTestFunction1(BaseDataInteger *parDim,
      BaseDataSimAnnUpperLower *upLow, 
      BaseDataDoubleVector *parVec, 
      BaseDataInstanceDoubleMatrix *dataMat,
      BaseDataDoubleVector *costTanVec,
      BaseDataDoubleVector *parIntRealVec);

  STANDARD_VIRTUAL_METHODS_OBJECT;

  virtual BaseDataReal operator()(BaseDataDoubleVector *parToOpt, 
                                  BaseDataInstanceDoubleMatrix *dataMat,
                                  DataDoubleVectorClass *parToOptClass, 
                                  DataInstanceDoubleMatrixClass *dataMatClass);
}; // end class BaseDataTestFunction1


/*C DataTestFunction1Class . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataTestFunction1Class : public DataFunctionToOptimizeClass
{
public:
  DataTestFunction1Class();
  DataTestFunction1Class(const DataTestFunction1Class& data);
  DataTestFunction1Class(const int id, 
                         const String& name,
                         const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
};  // end class DataFunctionToOptimizeClass


#endif










