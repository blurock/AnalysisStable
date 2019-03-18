// $Id: myuser.cc,v 1.1 2008/02/17 12:13:28 blurock Exp $ 

#include "SimulatedAnnealing.hh"


/***********************************************************************
* initialize_parameters - sample parameter initialization function
*	This depends on the users cost function to optimize (minimum).
*	The routine allocates storage needed for asa. The user should
*	define the number of parameters and their ranges,
*	and make sure the initial parameters are within
*	the minimum and maximum ranges. The array
*	parameter_int_real should be REAL_TYPE (-1) for real parameters,
*	and INTEGER_TYPE (1) for integer values
***********************************************************************/
#if HAVE_ANSI
void
initialize_parameters (double *cost_parameters,
		       double *parameter_lower_bound,
		       double *parameter_upper_bound,
		       double *cost_tangents,
		       double *cost_curvature,
		       ALLOC_INT * parameter_dimension,
		       int *parameter_int_real,
#if OPTIONS_FILE_DATA
		       FILE * ptr_options,
#endif
		       USER_DEFINES * USER_OPTIONS)
#else	// HAVE_ANSI
void
initialize_parameters (cost_parameters,
		       parameter_lower_bound,
		       parameter_upper_bound,
		       cost_tangents,
		       cost_curvature,
		       parameter_dimension,
		       parameter_int_real,
#if OPTIONS_FILE_DATA
		       ptr_options,
#endif
		       USER_OPTIONS)
     double *cost_parameters;
     double *parameter_lower_bound;
     double *parameter_upper_bound;
     double *cost_tangents;
     double *cost_curvature;
     ALLOC_INT *parameter_dimension;
     int *parameter_int_real;
#if OPTIONS_FILE_DATA
     FILE *ptr_options;
#endif
     USER_DEFINES *USER_OPTIONS;
#endif	// HAVE_ANSI
{
  //ALLOC_INT index = 0;
#if OPTIONS_FILE_DATA
  char read_option[80];
  ALLOC_INT read_index;
#endif
#if MY_TEMPLATE			/* MY_TEMPLATE_init_decl */
  /* add some declarations if required */
#endif

#if OPTIONS_FILE_DATA
  fscanf (ptr_options, "%s", read_option);

  for (index = 0; index < *parameter_dimension; ++index)
    {
#if MY_TEMPLATE			/* MY_TEMPLATE_read_opt */
      /* put in some code as required to alter lines read from asa_opt */
#endif
#if INT_ALLOC
      fscanf (ptr_options, "%d", &read_index);
#else
#if INT_LONG
      fscanf (ptr_options, "%ld", &read_index);
#else
      fscanf (ptr_options, "%d", &read_index);
#endif
#endif
      fscanf (ptr_options, "%lf%lf%lf%d",
	      &(parameter_lower_bound[read_index]),
	      &(parameter_upper_bound[read_index]),
	      &(cost_parameters[read_index]),
	      &(parameter_int_real[read_index]));
    }
#else /* OPTIONS_FILE_DATA */
#if ASA_TEST
  /* store the parameter ranges */
  for (index = 0; index < *parameter_dimension; ++index)
    parameter_lower_bound[index] = -10000.0;
  for (index = 0; index < *parameter_dimension; ++index)
    parameter_upper_bound[index] = 10000.0;

  /* store the initial parameter types */
  for (index = 0; index < *parameter_dimension; ++index)
    parameter_int_real[index] = REAL_TYPE;

  /* store the initial parameter values */
  for (index = 0; index < *parameter_dimension / 4.0; ++index)
    {
      cost_parameters[4 * (index + 1) - 4] = 999.0;
      cost_parameters[4 * (index + 1) - 3] = -1007.0;
      cost_parameters[4 * (index + 1) - 2] = 1001.0;
      cost_parameters[4 * (index + 1) - 1] = -903.0;
    }
#endif /* ASA_TEST */

  //	add here if not read from ASA_OPT  wh
#endif /* OPTIONS_FILE_DATA */

#if ASA_TEMPLATE_SAMPLE
  for (index = 0; index < *parameter_dimension; ++index)
    parameter_lower_bound[index] = 0;
  for (index = 0; index < *parameter_dimension; ++index)
    parameter_upper_bound[index] = 2.0;
  for (index = 0; index < *parameter_dimension; ++index)
    parameter_int_real[index] = REAL_TYPE;
  for (index = 0; index < *parameter_dimension; ++index)
    cost_parameters[index] = 0.5;
#endif

#if USER_INITIAL_PARAMETERS_TEMPS
  if ((USER_OPTIONS->User_Parameter_Temperature =
       (double *) calloc (*parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);
#if ASA_TEMPLATE
  for (index = 0; index < *parameter_dimension; ++index)
    USER_OPTIONS->User_Parameter_Temperature[index] = 1.0;
#endif
#endif /* USER_INITIAL_PARAMETERS_TEMPS */
#if USER_INITIAL_COST_TEMP
  if ((USER_OPTIONS->User_Cost_Temperature =
       (double *) calloc (1, sizeof (double))) == NULL)
      exit (9);
#if ASA_TEMPLATE
  USER_OPTIONS->User_Cost_Temperature[0] = 5.936648E+09;
#endif
#endif /* USER_INITIAL_COST_TEMP */
#if DELTA_PARAMETERS
  if ((USER_OPTIONS->User_Delta_Parameter =
       (double *) calloc (*parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);
#if ASA_TEMPLATE
  for (index = 0; index < *parameter_dimension; ++index)
    USER_OPTIONS->User_Delta_Parameter[index] = 0.001;
#endif
#endif /* DELTA_PARAMETERS */
#if QUENCH_PARAMETERS
  if ((USER_OPTIONS->User_Quench_Param_Scale =
       (double *) calloc (*parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);
#if ASA_TEMPLATE
  for (index = 0; index < *parameter_dimension; ++index)
    USER_OPTIONS->User_Quench_Param_Scale[index] = 1.0;
#endif
/*
#if ASA_TEMPLATE_MULTIPLE
  for (index = 0; index < *parameter_dimension; ++index)
    USER_OPTIONS->User_Quench_Param_Scale[index] = 1.0;
#endif
*/
#if ASA_TEMPLATE_SAVE
  for (index = 0; index < *parameter_dimension; ++index)
    USER_OPTIONS->User_Quench_Param_Scale[index] = 1.0;
#endif
#endif /* QUENCH_PARAMETERS */
#if QUENCH_COST
  if ((USER_OPTIONS->User_Quench_Cost_Scale =
       (double *) calloc (1, sizeof (double))) == NULL)
      exit (9);
#if ASA_TEMPLATE
  USER_OPTIONS->User_Quench_Cost_Scale[0] = 1.0;
#endif
/*
#if ASA_TEMPLATE_MULTIPLE
  USER_OPTIONS->User_Quench_Cost_Scale[0] = 1.0;
#endif
*/
#if ASA_TEMPLATE_SAVE
  USER_OPTIONS->User_Quench_Cost_Scale[0] = 1.0;
#endif
#endif /* QUENCH_COST */

  /* use asa_opt to read in QUENCH USER_OPTIONS */
#if OPTIONS_FILE_DATA
#if QUENCH_COST
  fscanf (ptr_options, "%s", read_option);
  fscanf (ptr_options, "%s", read_option);
  fscanf (ptr_options, "%lf", &(USER_OPTIONS->User_Quench_Cost_Scale[0]));

#if QUENCH_PARAMETERS
  fscanf (ptr_options, "%s", read_option);
  fscanf (ptr_options, "%s", read_option);
  for (index = 0; index < *parameter_dimension; ++index)
    {
#if INT_ALLOC
      fscanf (ptr_options, "%d", &read_index);
#else
#if INT_LONG
      fscanf (ptr_options, "%ld", &read_index);
#else
      fscanf (ptr_options, "%d", &read_index);
#endif
#endif
      fscanf (ptr_options, "%lf",
	      &(USER_OPTIONS->User_Quench_Param_Scale[read_index]));
    }
#endif /* QUENCH_PARAMETERS */
#endif /* QUENCH_COST */
#endif /* OPTIONS_FILE_DATA */

#if RATIO_TEMPERATURE_SCALES
  if ((USER_OPTIONS->User_Temperature_Ratio =
       (double *) calloc (*parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);
#if ASA_TEMPLATE
  for (index = 0; index < *parameter_dimension; ++index)
    USER_OPTIONS->User_Temperature_Ratio[index] = 1.0;
#endif
#endif /* RATIO_TEMPERATURE_SCALES */
  /* Defines the limit of collection of sampled data by asa */
#if ASA_SAMPLE
  /* create memory for Bias_Generated[] */
  if ((USER_OPTIONS->Bias_Generated =
       (double *) calloc (*parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);
#endif

#if ASA_QUEUE
  if ((USER_OPTIONS->Queue_Resolution =
       (double *) calloc (*parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);
#if ASA_TEMPLATE_QUEUE
  USER_OPTIONS->Queue_Size = 100;
  for (index = 0; index < *parameter_dimension; ++index)
    USER_OPTIONS->Queue_Resolution[index] = 0.001;
#endif
#endif /* ASA_QUEUE */
#if ASA_RESOLUTION
  if ((USER_OPTIONS->Coarse_Resolution =
       (double *) calloc (*parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);
#if ASA_TEMPLATE
  for (index = 0; index < *parameter_dimension; ++index)
    USER_OPTIONS->Coarse_Resolution[index] = 1.0;
#endif
#endif /* ASA_RESOLUTION */

#if MY_TEMPLATE			/* MY_TEMPLATE_params */
  /* If not using RECUR_OPTIONS_FILE_DATA or data read from asa_opt,
     store the parameter ranges
     store the parameter types
     store the initial parameter values
     other changes needed for initialization */
#endif /* MY_TEMPLATE params */
}



#if COST_FILE
#else
/***********************************************************************
* double cost_function
*	This is the users cost function to optimize
*	(find the minimum).
*	cost_flag is set to TRUE if the parameter set
*	does not violates any constraints
*       parameter_lower_bound and parameter_upper_bound may be
*       adaptively changed during the search.
***********************************************************************/

#if HAVE_ANSI
double
cost_function (double *x,
	       double *parameter_lower_bound,
	       double *parameter_upper_bound,
	       double *cost_tangents,
	       double *cost_curvature,
	       ALLOC_INT * parameter_dimension,
	       int *parameter_int_real,
	       int *cost_flag,
	       int *exit_code,
	       USER_DEFINES * USER_OPTIONS)
#else
double
cost_function (x,
	       parameter_lower_bound,
	       parameter_upper_bound,
	       cost_tangents,
	       cost_curvature,
	       parameter_dimension,
	       parameter_int_real,
	       cost_flag,
	       exit_code,
	       USER_OPTIONS)
     double *x;
     double *parameter_lower_bound;
     double *parameter_upper_bound;
     double *cost_tangents;
     double *cost_curvature;
     ALLOC_INT *parameter_dimension;
     int *parameter_int_real;
     int *cost_flag;
     int *exit_code;
     USER_DEFINES *USER_OPTIONS;
#endif
{

#if ASA_TEST			/* ASA test problem */
  /* Objective function from
   * %A A. Corana
   * %A M. Marchesi
   * %A C. Martini
   * %A S. Ridella
   * %T Minimizing multimodal functions of continuous variables
   *    with the "simulated annealing" algorithm
   * %J ACM Trans. Mathl. Software
   * %V 13
   * %N 3
   * %P 262-279
   * %D 1987
   *
   * This function, when used with ASA_TEST_POINT set to TRUE, contains
   * 1.0E20 local minima.  When *parameter_dimension is equal to 4, visiting
   * each minimum for a millisecond would take about the present age of the
   * universe to visit all these minima. */

  /* defines for the test problem, which assume *parameter_dimension
     is a multiple of 4.  If this is set to a large number, you
     likely should set Curvature_0 to TRUE. */
  double q_n, d_i, s_i, t_i, z_i, c_r;
  int k_i;
#if ASA_TEST_POINT
  int k_flag;
#endif
  LONG_INT i, j;
#if SELF_OPTIMIZE
#else
  static LONG_INT funevals = 0;
#endif
#if ASA_TEMPLATE_SAVE
  static int read_test = 0;
  FILE *ptr_read_test;
#endif

#if MY_TEMPLATE			/* MY_TEMPLATE_diminishing_ranges */
  /* insert code to automate changing ranges of parameters */
#endif
#if ASA_TEMPLATE		/* example of diminishing ranges */
  if (USER_OPTIONS->Locate_Cost == 12 && *(USER_OPTIONS->Best_Cost) < 1.0)
    {
      fprintf (ptr_out, "best_cost = %g\n", *(USER_OPTIONS->Best_Cost));
      for (i = 0; i < *parameter_dimension; ++i)
	{
	  parameter_lower_bound[i] = USER_OPTIONS->Best_Parameters[i]
	    - 0.5 * fabs (parameter_lower_bound[i]
			  - USER_OPTIONS->Best_Parameters[i]);
	  parameter_upper_bound[i] = USER_OPTIONS->Best_Parameters[i]
	    + 0.5 * fabs (parameter_upper_bound[i]
			  - USER_OPTIONS->Best_Parameters[i]);
	  parameter_lower_bound[i] = MIN (parameter_lower_bound[i],
				   USER_OPTIONS->Best_Parameters[i] - 0.01);
	  parameter_upper_bound[i] = MAX (parameter_upper_bound[i],
				   USER_OPTIONS->Best_Parameters[i] + 0.01);
	}
    }
#endif /* ASA_TEMPLATE */

  /* a_i = parameter_upper_bound[i] */
  s_i = 0.2;
  t_i = 0.05;
  c_r = 0.15;

#if ASA_TEST_POINT
  k_flag = 0;
  for (i = 0; i < *parameter_dimension; ++i)
    {
      if (x[i] > 0.0)
	{
	  k_i = (int) (x[i] / s_i + 0.5);
	}
      else if (x[i] < 0.0)
	{
	  k_i = (int) (x[i] / s_i - 0.5);
	}
      else
	{
	  k_i = 0;
	}
      if (k_i == 0)
	++k_flag;
    }
#endif /* ASA_TEST_POINT */

  q_n = 0.0;
  for (i = 0; i < *parameter_dimension; ++i)
    {
      j = i % 4;
      switch (j)
	{
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
      if (x[i] > 0.0)
	{
	  k_i = (int) (x[i] / s_i + 0.5);
	}
      else if (x[i] < 0.0)
	{
	  k_i = (int) (x[i] / s_i - 0.5);
	}
      else
	{
	  k_i = 0;
	}

#if ASA_TEST_POINT
      if (fabs (k_i * s_i - x[i]) < t_i && k_flag != *parameter_dimension)
#else
      if (fabs (k_i * s_i - x[i]) < t_i)
#endif
	{
	  if (k_i < 0)
	    {
	      z_i = k_i * s_i + t_i;
	    }
	  else if (k_i > 0)
	    {
	      z_i = k_i * s_i - t_i;
	    }
	  else
	    {
	      z_i = 0.0;
	    }
	  q_n += c_r * d_i * z_i * z_i;
	}
      else
	{
	  q_n += d_i * x[i] * x[i];
	}
    }
  funevals = funevals + 1;

#if ASA_TEMPLATE_SAVE
  /* cause a crash */
  if ((ptr_read_test = fopen ("asa_save", "r")) == NULL)
    {
      read_test = 1;
      fclose (ptr_read_test);
    }
  else
    {
      fclose (ptr_read_test);
    }
  /* will need a few hundred if testing ASA_PARALLEL to get an asa_save */
  if (funevals == 50 && read_test == 1)
    {
      exit (2);
    }
#endif

  *cost_flag = TRUE;

#if SELF_OPTIMIZE
#else
#if TIME_CALC
  /* print the time every PRINT_FREQUENCY evaluations */
  if ((PRINT_FREQUENCY > 0) && ((funevals % PRINT_FREQUENCY) == 0))
    {
      fprintf (ptr_out, "funevals = %ld  ", funevals);
      print_time ("", ptr_out);
    }
#endif
#endif

#if ASA_TEMPLATE_SAMPLE
  USER_OPTIONS->Cost_Acceptance_Flag = TRUE;
  if (USER_OPTIONS->User_Acceptance_Flag == FALSE && *cost_flag == TRUE)
    USER_OPTIONS->Acceptance_Test (q_n, *parameter_dimension, USER_OPTIONS);
#endif /* ASA_TEMPLATE_SAMPLE */

  return (q_n);
#else	// ASA_TEST
  {
	  //
	  //
	  //
	  //
	  //
	  //
	  //
	  //
	  //
	  return 1;
  }
#endif /* ASA_TEST */



#if ASA_TEMPLATE_SAMPLE

  int n;
  double cost;

  if (*cost_flag == FALSE)
    {
      for (n = 0; n < *parameter_dimension; ++n)
	cost_tangents[n] = 2.0 * x[n];
    }

  cost = 0.0;
  for (n = 0; n < *parameter_dimension; ++n)
    {
      cost += (x[n] * x[n]);
    }

  *cost_flag = TRUE;

  USER_OPTIONS->Cost_Acceptance_Flag = TRUE;
  if (USER_OPTIONS->User_Acceptance_Flag == FALSE && *cost_flag == TRUE)
    USER_OPTIONS->Acceptance_Test (cost, *parameter_dimension, USER_OPTIONS);

  return (cost);
#endif /* ASA_TEMPLATE_SAMPLE */
#if MY_TEMPLATE			/* MY_TEMPLATE_cost */
  /* Use the parameter values x[] and define your cost_function.
     The {} brackets around this function are already in place. */
#endif /* MY_TEMPLATE cost */
}
#endif /* COST_FILE */

 /* Here is a good random number generator */

#define SHUFFLE 256		/* size of random array */
#define MULT ((LONG_INT) 25173)
#define MOD ((LONG_INT) 65536)
#define INCR ((LONG_INT) 13849)
#define FMOD ((double) 65536.0)


#if ASA_LIB
/***********************************************************************
* LONG_INT asa_seed - returns initial random seed
***********************************************************************/

#if HAVE_ANSI
LONG_INT
asa_seed (LONG_INT seed)
#else
LONG_INT
asa_seed (seed)
     LONG_INT seed;
#endif
{
  static LONG_INT rand_seed;

  if (fabs (seed) > 0)
    {
      asa_rand_seed = &rand_seed;
      rand_seed = seed;
    }

  return (rand_seed);
}
#endif /* ASA_LIB */

/***********************************************************************
* double myrand - returns random number between 0 and 1
*	This routine returns the random number generator between 0 and 1
***********************************************************************/

#if HAVE_ANSI
double
myrand (LONG_INT * rand_seed)
#else
double
myrand (rand_seed)
     LONG_INT *rand_seed;
#endif
 /* returns random number in {0,1} */
{
#if TRUE			/* (change to FALSE for alternative RNG) */
  *rand_seed = (LONG_INT) ((MULT * (*rand_seed) + INCR) % MOD);
  return ((double) (*rand_seed) / FMOD);
#else
  /* See "Random Number Generators: Good Ones Are Hard To Find,"
     Park & Miller, CACM 31 (10) (October 1988) pp. 1192-1201.
     ***********************************************************
     THIS IMPLEMENTATION REQUIRES AT LEAST 32 BIT INTEGERS
     *********************************************************** */
#define _A_MULTIPLIER  16807L
#define _M_MODULUS     2147483647L	/* (2**31)-1 */
#define _Q_QUOTIENT    127773L	/* 2147483647 / 16807 */
#define _R_REMAINDER   2836L	/* 2147483647 % 16807 */
  long lo;
  long hi;
  long test;

  hi = *rand_seed / _Q_QUOTIENT;
  lo = *rand_seed % _Q_QUOTIENT;
  test = _A_MULTIPLIER * lo - _R_REMAINDER * hi;
  if (test > 0)
    {
      *rand_seed = test;
    }
  else
    {
      *rand_seed = test + _M_MODULUS;
    }
  return ((double) *rand_seed / _M_MODULUS);
#endif /* alternative RNG */
}

/***********************************************************************
* double randflt
***********************************************************************/

#if HAVE_ANSI
double
randflt (LONG_INT * rand_seed)
#else
double
randflt (rand_seed)
     LONG_INT *rand_seed;
#endif
 /* shuffles random numbers in random_array[SHUFFLE] array */
{

  /* This RNG is a modified algorithm of that presented in
     * %A K. Binder
     * %A D. Stauffer
     * %T A simple introduction to Monte Carlo simulations and some
     *    specialized topics
     * %B Applications of the Monte Carlo Method in statistical physics
     * %E K. Binder
     * %I Springer-Verlag
     * %C Berlin
     * %D 1985
     * %P 1-36
     * where it is stated that such algorithms have been found to be
     * quite satisfactory in many statistical physics applications. */

  double rranf;
  unsigned kranf;
  int n;
  static int initial_flag = 0;
#if ASA_TEMPLATE_SAVE
#else
  static double random_array[SHUFFLE];	/* random variables */
#endif

  if (initial_flag == 0 || *rand_seed < 0)
    {
      if (*rand_seed < 0)
	*rand_seed = -*rand_seed;

      for (n = 0; n < SHUFFLE; ++n)
	random_array[n] = myrand (rand_seed);
      initial_flag = 1;

      for (n = 0; n < 1000; ++n)	/* warm up random generator */
	rranf = randflt (rand_seed);

      return (rranf);
    }

  kranf = (unsigned) (myrand (rand_seed) * SHUFFLE) % SHUFFLE;
  rranf = *(random_array + kranf);
  *(random_array + kranf) = myrand (rand_seed);

  return (rranf);
}

#if USER_COST_SCHEDULE
#if HAVE_ANSI
double
user_cost_schedule (double test_temperature,
		    USER_DEFINES * USER_OPTIONS)
#else
double
user_cost_schedule (test_temperature,
		    USER_OPTIONS)
     double test_temperature;
     USER_DEFINES *USER_OPTIONS;
#endif /* HAVE_ANSI */
{
  double x;

#if ASA_TEMPLATE_SAMPLE
  x = F_POW (test_temperature, 0.15);
#endif
#if ASA_TEMPLATE
  x = test_temperature;
#endif

  return (x);
}
#endif /* USER_COST_SCHEDULE */

#if USER_ACCEPTANCE_TEST
#if HAVE_ANSI
void
user_acceptance_test (double current_cost,
		      ALLOC_INT * parameter_dimension,
		      USER_DEFINES * USER_OPTIONS)
#else
void
user_acceptance_test (current_cost,
		      parameter_dimension,
		      USER_OPTIONS)
     double current_cost;
     ALLOC_INT *parameter_dimension;
     USER_DEFINES *USER_OPTIONS;
#endif /* HAVE_ANSI */
{
  double x, uniform_test, curr_cost_temp;
#if USER_ACCEPT_ASYMP_EXP
  double q, delta_cost;
#endif

#if ASA_TEMPLATE		/* ASA cost index */
  /* Calculate the current ASA cost index.  This could be useful
     to define a new schedule for the cost temperature, beyond
     simple changes that can be made using USER_COST_SCHEDULE. */

  double k_temperature, quench, y;

#if QUENCH_COST
  quench = USER_OPTIONS->User_Quench_Cost_Scale[0];
#else
  quench = 1.0;
#endif /* QUENCH_COST */
  y = -F_LOG (USER_OPTIONS->Cost_Temp_Curr
	    / USER_OPTIONS->Cost_Temp_Init) / USER_OPTIONS->Cost_Temp_Scale;

  k_temperature = F_POW (y, (double) *parameter_dimension / quench);
#endif /* ASA cost index */

  uniform_test = randflt (USER_OPTIONS->Random_Seed);
  curr_cost_temp = USER_OPTIONS->Cost_Temp_Curr;

#if ASA_TEMPLATE
#if USER_COST_SCHEDULE
  curr_cost_temp =
    (USER_OPTIONS->Cost_Schedule (USER_OPTIONS->Cost_Temp_Curr,
				  USER_OPTIONS)
     + (double) EPS_DOUBLE);
#else
  curr_cost_temp = USER_OPTIONS->Cost_Temp_Curr;
#endif
#endif /* ASA_TEMPLATE */

#if USER_ACCEPT_ASYMP_EXP
#if USER_COST_SCHEDULE
  curr_cost_temp =
    (USER_OPTIONS->Cost_Schedule (USER_OPTIONS->Cost_Temp_Curr,
				  USER_OPTIONS)
     + (double) EPS_DOUBLE);
#endif

  delta_cost = (current_cost - *(USER_OPTIONS->Last_Cost))
    / (curr_cost_temp + (double) EPS_DOUBLE);

  /* The following asymptotic approximation to the exponential
   * function, "Tsallis statistics," was proposed in
   * %A T.J.P. Penna
   * %T Traveling salesman problem and Tsallis statistics
   * %J Phys. Rev. E
   * %V 50
   * %N 6
   * %P R1-R3
   * %D 1994
   * While the use of the TSP for a test case is of dubious value (since
   * there are many special algorithms for this problem), the use of this
   * function is another example of how to control the rate of annealing
   * of the acceptance criteria.  E.g., if you require a more moderate
   * acceptance test, then negative q may be helpful. */

  q = USER_OPTIONS->Asymp_Exp_Param;
  if (fabs (1.0 - q) < (double) EPS_DOUBLE)
    x = MIN (1.0, (F_EXP (-delta_cost)));	/* Boltzmann test */
  else if ((1.0 - (1.0 - q) * delta_cost) < (double) EPS_DOUBLE)
    x = MIN (1.0, (F_EXP (-delta_cost)));	/* Boltzmann test */
  else
    x = MIN (1.0, F_POW ((1.0 - (1.0 - q) * delta_cost), (1.0 / (1.0 - q))));

  USER_OPTIONS->Prob_Bias = x;
  if (x >= uniform_test)
    USER_OPTIONS->User_Acceptance_Flag = TRUE;
  else
    USER_OPTIONS->User_Acceptance_Flag = FALSE;

#endif /* USER_ACCEPT_ASYMP_EXP */
}
#endif /* USER_ACCEPTANCE_TEST */

#if USER_GENERATING_FUNCTION
#if HAVE_ANSI
double
user_generating_distrib (LONG_INT * seed,
			 ALLOC_INT * parameter_dimension,
			 ALLOC_INT index_v,
			 double temperature_v,
			 double init_param_temp_v,
			 double temp_scale_params_v,
			 double parameter_v,
			 double parameter_range_v,
			 double *last_saved_parameter,
			 USER_DEFINES * USER_OPTIONS)
#else
double
user_generating_distrib (seed,
			 parameter_dimension,
			 index_v,
			 temperature_v,
			 init_param_temp_v,
			 temp_scale_params_v,
			 parameter_v,
			 parameter_range_v,
			 last_saved_parameter,
			 USER_OPTIONS)
     LONG_INT *seed;
     ALLOC_INT *parameter_dimension;
     ALLOC_INT index_v;
     double temperature_v;
     double init_param_temp_v;
     double temp_scale_params_v;
     double parameter_v;
     double parameter_range_v;
     double *last_saved_parameter;
     USER_DEFINES *USER_OPTIONS;
#endif
{
  double x, y, z;
#if FALSE			/* set to TRUE to activate */
  /* Calculate the current ASA temperature index for parameter_v.
     This could be useful, e.g., to define a slower polynomial
     or logarithmic schedule, as would be required by Cauchy
     or Gaussian distributions, respectively.  These distributions
     are defined below. */

  double k_temperature_v, temperature_0_v, quench_v;
  static double PI = 3.14159265358979323846;

#if QUENCH_PARAMETERS
  quench_v = USER_OPTIONS->User_Quench_Param_Scale[index_v];
#else
  quench_v = 1.0;
#endif /* QUENCH_PARAMETERS */
  y = -F_LOG (temperature_v / init_param_temp_v) / temp_scale_params_v;

  k_temperature_v = F_POW (y, (double) *parameter_dimension / quench_v);
#endif

#if ASA_TEMPLATE
  /* This is the ASA distribution.  A slower temperature schedule can be
     obtained here, e.g., temperature_v = pow(temperature_v, 0.5); */

  x = randflt (seed);
  y = x < 0.5 ? -1.0 : 1.0;
  z = y * temperature_v * (F_POW ((1.0 + 1.0 / temperature_v),
				  fabs (2.0 * x - 1.0)) - 1.0);

  x = parameter_v + z * parameter_range_v;
#endif /* ASA_TEMPLATE */

#if FALSE			/* Cauchy Distribution */
  /* Note that this is a one-dimensional Cauchy distribution, which
     may not be optimal for problems in more than one dimension. */

  for (;;)
    {
      x = 2.0 * myrand (seed) - 1.0;
      y = 2.0 * myrand (seed) - 1.0;
      z = x * x + y * y;
      if (z <= 1.0)
	break;
    }
  if (fabs (x) < (double) EPS_DOUBLE)
    x = (x < 0.0 ? x - (double) EPS_DOUBLE : x + (double) EPS_DOUBLE);

  z = (y / x);

  temperature_0_v = parameter_range_v;
  y = temperature_0_v / k_temperature_v;

  x = parameter_v + y * z;

  return (x);
#endif /* Cauchy Distribution */

#if FALSE			/* Gaussian Distribution */
  /* Note that this is a one-dimensional Gaussian distribution, which
     may not be optimal for problems in more than one dimension. */

  x = randflt (seed);
  y = randflt (seed);

  if (x < (double) EPS_DOUBLE)
    x += (double) EPS_DOUBLE;
  z = sqrt (-2.0 * F_LOG (x)) * sin (2.0 * PI * y);

  temperature_0_v = parameter_range_v;
  y = temperature_0_v / F_LOG (k_temperature_v);

  x = parameter_v + y * z;

  return (x);
#endif /* Gaussian Distribution */

  return (x);
}
#endif /* USER_GENERATING_FUNCTION */

#if USER_REANNEAL_COST
#if HAVE_ANSI
int
user_reanneal_cost (double *cost_best,
		    double *cost_last,
		    double *initial_cost_temperature,
		    double *current_cost_temperature,
		    USER_DEFINES * USER_OPTIONS)
#else
int
user_reanneal_cost (cost_best,
		    cost_last,
		    initial_cost_temperature,
		    current_cost_temperature,
		    USER_OPTIONS)
     double *cost_best;
     double *cost_last;
     double *initial_cost_temperature;
     double *current_cost_temperature;
     USER_DEFINES *USER_OPTIONS;
#endif /* HAVE_ANSI */
{
  int cost_test;
  double tmp_dbl;

#if ASA_TEMPLATE
  static int first_time = 1;
  static double save_last[3];
  double average_cost_last;

  if (first_time == 1)
    {
      first_time = 0;
      save_last[0] = save_last[1] = save_last[2] = *cost_last;
    }

  save_last[2] = save_last[1];
  save_last[1] = save_last[0];
  save_last[0] = *cost_last;
  average_cost_last = fabs ((save_last[0] + save_last[1] + save_last[2]) / 3.0);

  tmp_dbl = MAX (fabs (*cost_best), average_cost_last);
  tmp_dbl = MAX ((double) EPS_DOUBLE, tmp_dbl);
  *initial_cost_temperature = MIN (*initial_cost_temperature, tmp_dbl);

  /* This test can be useful if your cost function goes from a positive
     to a negative value, and you do not want to get get stuck in a local
     minima around zero due to the default in reanneal().  Pick any
     number instead of 0.0001 */
  tmp_dbl = MIN (fabs (*cost_last), fabs (*cost_best));
  if (tmp_dbl < 0.0001)
    cost_test = FALSE;
  else
    cost_test = TRUE;
#endif /* ASA_TEMPLATE */

  tmp_dbl = MAX (fabs (cost_last), fabs (cost_best));
  tmp_dbl = MAX ((double) EPS_DOUBLE, tmp_dbl);
  *initial_cost_temperature = MIN (*initial_cost_temperature, tmp_dbl);

  *current_cost_temperature =
    MAX (fabs (cost_last - cost_best), *current_cost_temperature);
  *current_cost_temperature =
    MAX ((double) EPS_DOUBLE, *current_cost_temperature);
  *current_cost_temperature =
    MIN (*current_cost_temperature, *initial_cost_temperature);

  cost_test = TRUE;

  return (cost_test);
}
#endif /* USER_REANNEAL_COST */

#if USER_REANNEAL_PARAMETERS
#if HAVE_ANSI
double
user_reanneal_params (double current_temp,
		      double tangent,
		      double max_tangent,
		      USER_DEFINES * USER_OPTIONS)
#else
double
user_reanneal_params (current_temp,
		      tangent,
		      max_tangent,
		      USER_OPTIONS)
     double current_temp;
     double tangent;
     double max_tangent;
     USER_DEFINES *USER_OPTIONS;
#endif /* HAVE_ANSI */
{
#if ASA_TEMPLATE
  double x;

  x = current_temp * (max_tangent / tangent);

  return (x);
#endif
}
#endif /* USER_REANNEAL_PARAMETERS */

#if SELF_OPTIMIZE

/***********************************************************************
* main
*	This is a sample calling program to self-optimize ASA
***********************************************************************/
#if HAVE_ANSI

#if ASA_LIB
void
asa_main (
#if ASA_TEMPLATE_LIB
	   double *main_recur_cost_value,
	   double *main_recur_cost_parameters,
	   int *main_recur_exit_code
#endif
)
#else /* ASA_LIB */
int
main (int argc, char **argv)
#endif				/* ASA_LIB */

#else /* HAVE_ANSI */

#if ASA_LIB
void
asa_main (
#if ASA_TEMPLATE_LIB
	   main_recur_cost_value,
	   main_recur_cost_parameters,
	   main_recur_exit_code
#endif
)
#if ASA_TEMPLATE_LIB
     double *main_recur_cost_value;
     double *main_recur_cost_parameters;
     int *main_recur_exit_code;
#endif

#else /* ASA_LIB */
int
main (argc, argv)
     int argc;
     char **argv;
#endif /* ASA_LIB */

#endif /* HAVE_ANSI */
{

  /* seed for random number generator */
  static LONG_INT *recur_rand_seed;

#if RECUR_OPTIONS_FILE
  FILE *recur_ptr_options;
  char read_option[80];
  int read_int;
#if INT_LONG
  LONG_INT read_long;
#endif
  double read_double;
#endif

  int *recur_exit_code;
#if ASA_LIB
#else
  int compile_cnt;
#endif

  double *recur_parameter_lower_bound, *recur_parameter_upper_bound;
  double *recur_cost_parameters, *recur_cost_tangents, *recur_cost_curvature;
  double recur_cost_value;

  ALLOC_INT *recur_parameter_dimension;
  int *recur_parameter_int_real;
  int *recur_cost_flag;
  ALLOC_INT recur_v;
#if MY_TEMPLATE			/* MY_TEMPLATE_recur_main_decl */
  /* add some declarations if required */
#endif

  USER_DEFINES *RECUR_USER_OPTIONS;

  if ((recur_parameter_dimension =
       (ALLOC_INT *) calloc (1, sizeof (ALLOC_INT))) == NULL)
    exit (9);
  if ((recur_exit_code = (int *) calloc (1, sizeof (int))) == NULL)
      exit (9);
  if ((recur_cost_flag = (int *) calloc (1, sizeof (int))) == NULL)
      exit (9);

  if ((RECUR_USER_OPTIONS =
       (USER_DEFINES *) calloc (1, sizeof (USER_DEFINES))) == NULL)
    exit (9);

#if RECUR_OPTIONS_FILE
  recur_ptr_options = fopen ("asa_opt_recur", "r");

#if INT_LONG
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%ld", &read_long);
  RECUR_USER_OPTIONS->Limit_Acceptances = read_long;
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%ld", &read_long);
  RECUR_USER_OPTIONS->Limit_Generated = read_long;
#else
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%d", &read_int);
  RECUR_USER_OPTIONS->Limit_Acceptances = read_int;
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%d", &read_int);
  RECUR_USER_OPTIONS->Limit_Generated = read_int;
#endif
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%d", &read_int);
  RECUR_USER_OPTIONS->Limit_Invalid_Generated_States = read_int;
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%lf", &read_double);
  RECUR_USER_OPTIONS->Accepted_To_Generated_Ratio = read_double;

  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%lf", &read_double);
  RECUR_USER_OPTIONS->Cost_Precision = read_double;
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%d", &read_int);
  RECUR_USER_OPTIONS->Maximum_Cost_Repeat = read_int;
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%d", &read_int);
  RECUR_USER_OPTIONS->Number_Cost_Samples = read_int;
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%lf", &read_double);
  RECUR_USER_OPTIONS->Temperature_Ratio_Scale = read_double;
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%lf", &read_double);
  RECUR_USER_OPTIONS->Cost_Parameter_Scale_Ratio = read_double;
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%lf", &read_double);
  RECUR_USER_OPTIONS->Temperature_Anneal_Scale = read_double;

  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%d", &read_int);
  RECUR_USER_OPTIONS->Include_Integer_Parameters = read_int;
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%d", &read_int);
  RECUR_USER_OPTIONS->User_Initial_Parameters = read_int;
#if INT_ALLOC
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%d", &read_int);
  RECUR_USER_OPTIONS->Sequential_Parameters = read_int;
#else
#if INT_LONG
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%ld", &read_long);
  RECUR_USER_OPTIONS->Sequential_Parameters = read_long;
#else
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%d", &read_int);
  RECUR_USER_OPTIONS->Sequential_Parameters = read_int;
#endif
#endif
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%lf", &read_double);
  RECUR_USER_OPTIONS->Initial_Parameter_Temperature = read_double;

  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%d", &read_int);
  RECUR_USER_OPTIONS->Acceptance_Frequency_Modulus = read_int;
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%d", &read_int);
  RECUR_USER_OPTIONS->Generated_Frequency_Modulus = read_int;
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%d", &read_int);
  RECUR_USER_OPTIONS->Reanneal_Cost = read_int;
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%d", &read_int);
  RECUR_USER_OPTIONS->Reanneal_Parameters = read_int;

  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%lf", &read_double);
  RECUR_USER_OPTIONS->Delta_X = read_double;
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%d", &read_int);
  RECUR_USER_OPTIONS->User_Tangents = read_int;
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%d", &read_int);
  RECUR_USER_OPTIONS->Curvature_0 = read_int;

#else /* RECUR_OPTIONS_FILE */
  RECUR_USER_OPTIONS->Limit_Acceptances = 100;
  RECUR_USER_OPTIONS->Limit_Generated = 1000;
  RECUR_USER_OPTIONS->Limit_Invalid_Generated_States = 1000;
  RECUR_USER_OPTIONS->Accepted_To_Generated_Ratio = 1.0E-4;

  RECUR_USER_OPTIONS->Cost_Precision = 1.0E-18;
  RECUR_USER_OPTIONS->Maximum_Cost_Repeat = 2;
  RECUR_USER_OPTIONS->Number_Cost_Samples = 2;
  RECUR_USER_OPTIONS->Temperature_Ratio_Scale = 1.0E-5;
  RECUR_USER_OPTIONS->Cost_Parameter_Scale_Ratio = 1.0;
  RECUR_USER_OPTIONS->Temperature_Anneal_Scale = 100.0;

  RECUR_USER_OPTIONS->Include_Integer_Parameters = FALSE;
  RECUR_USER_OPTIONS->User_Initial_Parameters = TRUE;
  RECUR_USER_OPTIONS->Sequential_Parameters = -1;
  RECUR_USER_OPTIONS->Initial_Parameter_Temperature = 1.0;

  RECUR_USER_OPTIONS->Acceptance_Frequency_Modulus = 15;
  RECUR_USER_OPTIONS->Generated_Frequency_Modulus = 10000;
  RECUR_USER_OPTIONS->Reanneal_Cost = FALSE;
  RECUR_USER_OPTIONS->Reanneal_Parameters = FALSE;

  RECUR_USER_OPTIONS->Delta_X = 1.0E-6;
  RECUR_USER_OPTIONS->User_Tangents = FALSE;
  RECUR_USER_OPTIONS->Curvature_0 = TRUE;

#endif /* RECUR_OPTIONS_FILE */

  /* the number of parameters for the recur_cost_function */
#if RECUR_OPTIONS_FILE_DATA
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%s", read_option);

#if INT_ALLOC
  fscanf (recur_ptr_options, "%d", &read_int);
  *recur_parameter_dimension = read_int;
#else
#if INT_LONG
  fscanf (recur_ptr_options, "%ld", &read_long);
  *recur_parameter_dimension = read_long;
#else
  fscanf (recur_ptr_options, "%d", &read_int);
  *recur_parameter_dimension = read_int;
#endif
#endif

#else /* RECUR_OPTIONS_FILE_DATA */
#if ASA_TEMPLATE_SELFOPT
  *recur_parameter_dimension = 2;
#endif
#if MY_TEMPLATE			/* MY_TEMPLATE_recur_dim */
  /* If not using RECUR_OPTIONS_FILE_DATA or data read from recur_asa_opt,
     insert the number of parameters for the recur_cost_function */
#endif /* MY_TEMPLATE recur_dim */
#endif /* RECUR_OPTIONS_FILE_DATA */
  if ((recur_parameter_lower_bound =
       (double *) calloc (*recur_parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);
  if ((recur_parameter_upper_bound =
       (double *) calloc (*recur_parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);

  if ((recur_cost_parameters =
       (double *) calloc (*recur_parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);

  if ((recur_parameter_int_real =
       (int *) calloc (*recur_parameter_dimension, sizeof (int))
      ) == NULL)
      exit (9);

  if ((recur_cost_tangents =
       (double *) calloc (*recur_parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);

  if (RECUR_USER_OPTIONS->Curvature_0 == FALSE
      || RECUR_USER_OPTIONS->Curvature_0 == -1)
    {

      if ((recur_cost_curvature =
	   (double *) calloc ((*recur_parameter_dimension)
			      * (*recur_parameter_dimension),
			      sizeof (double))) == NULL)
	  exit (9);
    }
  else
    {
      recur_cost_curvature = (double *) NULL;
    }

#if ASA_TEMPLATE_SELFOPT
  /* Set memory to that required for use. */
  RECUR_USER_OPTIONS->Asa_Data_Dim = 1;
  if ((RECUR_USER_OPTIONS->Asa_Data =
       (double *) calloc (1, sizeof (double))) == NULL)
      exit (9);
  /* Use Asa_Data[0] as flag, e.g., if used with SELF_OPTIMIZE. */
  RECUR_USER_OPTIONS->Asa_Data[0] = 0;
#endif

  /* open the output file */
#if ASA_SAVE
  ptr_out = fopen ("myUser_out", "a");
#else
  ptr_out = fopen ("myUser_out", "w");
#endif
  /* use this instead if you want output to stdout */
#if FALSE
  ptr_out = stdout;
#endif
  fprintf (ptr_out, "%s\n\n", USER_ID);

#if ASA_LIB
#else
  /* print out compile options set by user in Makefile */
  if (argc > 1)
    {
      fprintf (ptr_out, "CC = %s\n", argv[1]);
      for (compile_cnt = 2; compile_cnt < argc; ++compile_cnt)
	{
	  fprintf (ptr_out, "\t%s\n", argv[compile_cnt]);
	}
      fprintf (ptr_out, "\n");
    }
#endif
#if TIME_CALC
  /* print starting time */
  print_time ("start", ptr_out);
#endif
  fflush (ptr_out);

  if ((recur_rand_seed =
       (LONG_INT *) calloc (1, sizeof (LONG_INT))) == NULL)
    exit (9);

  /* first value of *recur_rand_seed */
#if ASA_LIB
  *recur_rand_seed = (asa_rand_seed ? *asa_rand_seed : (LONG_INT) 696969);
#else
  *recur_rand_seed = 696969;
#endif

  randflt (recur_rand_seed);

#if USER_COST_SCHEDULE
  RECUR_USER_OPTIONS->Cost_Schedule = recur_user_cost_schedule;
#endif
#if USER_ACCEPTANCE_TEST
  RECUR_USER_OPTIONS->Acceptance_Test = recur_user_acceptance_test;
#endif
#if USER_ACCEPT_ASYMP_EXP
  RECUR_USER_OPTIONS->Asymp_Exp_Param = 1.0;
#endif
#if USER_GENERATING_FUNCTION
  RECUR_USER_OPTIONS->Generating_Distrib = recur_user_generating_distrib;
#endif
#if USER_REANNEAL_COST
  RECUR_USER_OPTIONS->Reanneal_Cost_Function = recur_user_reanneal_cost;
#endif
#if USER_REANNEAL_PARAMETERS
  RECUR_USER_OPTIONS->Reanneal_Params_Function = recur_user_reanneal_params;
#endif

#if MY_TEMPLATE			/* MY_TEMPLATE_recur_pre_initialize */
  /* last changes before entering recur_initialize_parameters() */
#endif

  /* initialize the users parameters, allocating space, etc.
     Note that the default is to have asa generate the initial
     recur_cost_parameters that satisfy the user's constraints. */

  recur_initialize_parameters (recur_cost_parameters,
			       recur_parameter_lower_bound,
			       recur_parameter_upper_bound,
			       recur_cost_tangents,
			       recur_cost_curvature,
			       recur_parameter_dimension,
			       recur_parameter_int_real,
#if RECUR_OPTIONS_FILE_DATA
			       recur_ptr_options,
#endif
			       RECUR_USER_OPTIONS);
#if RECUR_OPTIONS_FILE
  fclose (recur_ptr_options);
#endif


#if USER_ASA_OUT
  if ((RECUR_USER_OPTIONS->Asa_Out_File =
       (char *) calloc (80, sizeof (char))
      ) == NULL)
      exit (9);
#if ASA_TEMPLATE_SELFOPT
  strcpy (RECUR_USER_OPTIONS->Asa_Out_File, "asa_sfop");
#endif
#endif

  recur_cost_value = asa (recur_cost_function,
			  randflt,
			  recur_rand_seed,
			  recur_cost_parameters,
			  recur_parameter_lower_bound,
			  recur_parameter_upper_bound,
			  recur_cost_tangents,
			  recur_cost_curvature,
			  recur_parameter_dimension,
			  recur_parameter_int_real,
			  recur_cost_flag,
			  recur_exit_code,
			  RECUR_USER_OPTIONS);
#if FITLOC
  /* Fit_Local and Penalty may be set adaptively */
  RECUR_USER_OPTIONS->Penalty = 1000;
  RECUR_USER_OPTIONS->Fit_Local = 1;
  if (RECUR_USER_OPTIONS->Fit_Local == 1)
    {
      recur_cost_value = fitloc (recur_cost_parameters,
				 recur_parameter_lower_bound,
				 recur_parameter_upper_bound,
				 recur_cost_tangents,
				 recur_cost_curvature,
				 recur_parameter_dimension,
				 recur_parameter_int_real,
				 recur_cost_flag,
				 recur_exit_code,
				 RECUR_USER_OPTIONS,
				 ptr_out);
    }
#endif /* FITLOC */

  fprintf (ptr_out, "\n\n recur_cost_value = %12.7g\n",
	   recur_cost_value);
#if MY_TEMPLATE			/* MY_TEMPLATE_recur_post_recur_asa */
#endif
#if ASA_TEMPLATE_LIB
  *main_recur_cost_value = recur_cost_value;
  for (recur_v = 0; recur_v < *recur_parameter_dimension; ++recur_v)
    {
      main_recur_cost_parameters[recur_v] = recur_cost_parameters[recur_v];
    }
  *main_recur_exit_code = *recur_exit_code;
#endif

  for (recur_v = 0; recur_v < *recur_parameter_dimension; ++recur_v)
#if INT_ALLOC
    fprintf (ptr_out, "recur_cost_parameters[%d] = %12.7g\n",
#else
#if INT_LONG
    fprintf (ptr_out, "recur_cost_parameters[%ld] = %12.7g\n",
#else
    fprintf (ptr_out, "recur_cost_parameters[%d] = %12.7g\n",
#endif
#endif
	     recur_v, recur_cost_parameters[recur_v]);

  fprintf (ptr_out, "\n\n");

#if TIME_CALC
  /* print ending time */
  print_time ("end", ptr_out);
#endif

  /* close all files */
  fclose (ptr_out);

#if OPTIONAL_DATA
  free (RECUR_USER_OPTIONS->Asa_Data);
#endif
#if OPTIONAL_DATA_INT
  free (RECUR_USER_OPTIONS->Asa_Data_Int);
#endif
#if USER_ASA_OUT
  free (RECUR_USER_OPTIONS->Asa_Out_File);
#endif
#if ASA_SAMPLE
  free (RECUR_USER_OPTIONS->Bias_Generated);
#endif
#if ASA_QUEUE
  free (RECUR_USER_OPTIONS->Queue_Resolution);
#endif
#if ASA_RESOLUTION
  free (RECUR_USER_OPTIONS->Coarse_Resolution);
#endif
  if (RECUR_USER_OPTIONS->Curvature_0 == FALSE
      || RECUR_USER_OPTIONS->Curvature_0 == -1)
    free (recur_cost_curvature);
#if USER_INITIAL_PARAMETERS_TEMPS
  free (RECUR_USER_OPTIONS->User_Parameter_Temperature);
#endif
#if USER_INITIAL_COST_TEMP
  free (RECUR_USER_OPTIONS->User_Cost_Temperature);
#endif
#if DELTA_PARAMETERS
  free (RECUR_USER_OPTIONS->User_Delta_Parameter);
#endif
#if QUENCH_PARAMETERS
  free (RECUR_USER_OPTIONS->User_Quench_Param_Scale);
#endif
#if QUENCH_COST
  free (RECUR_USER_OPTIONS->User_Quench_Cost_Scale);
#endif
#if RATIO_TEMPERATURE_SCALES
  free (RECUR_USER_OPTIONS->User_Temperature_Ratio);
#endif
  free (RECUR_USER_OPTIONS);
  free (recur_parameter_dimension);
  free (recur_exit_code);
  free (recur_cost_flag);
  free (recur_parameter_lower_bound);
  free (recur_parameter_upper_bound);
  free (recur_cost_parameters);
  free (recur_parameter_int_real);
  free (recur_cost_tangents);
  free (recur_rand_seed);

#if ASA_LIB
#else
  exit (0);
  /* NOTREACHED */
#endif
}

/***********************************************************************
* recur_initialize_parameters
*	This depends on the users cost function to optimize (minimum).
*	The routine allocates storage needed for asa. The user should
*	define the number of parameters and their ranges,
*	and make sure the initial parameters are within
*	the minimum and maximum ranges. The array
*	recur_parameter_int_real should be REAL_TYPE (-1)
*       for real parameters,
***********************************************************************/
#if HAVE_ANSI
void
recur_initialize_parameters (double *recur_cost_parameters,
			     double *recur_parameter_lower_bound,
			     double *recur_parameter_upper_bound,
			     double *recur_cost_tangents,
			     double *recur_cost_curvature,
			     ALLOC_INT * recur_parameter_dimension,
			     int *recur_parameter_int_real,
#if RECUR_OPTIONS_FILE_DATA
			     FILE * recur_ptr_options,
#endif
			     USER_DEFINES * RECUR_USER_OPTIONS)
#else
void
recur_initialize_parameters (recur_cost_parameters,
			     recur_parameter_lower_bound,
			     recur_parameter_upper_bound,
			     recur_cost_tangents,
			     recur_cost_curvature,
			     recur_parameter_dimension,
			     recur_parameter_int_real,
#if RECUR_OPTIONS_FILE_DATA
			     recur_ptr_options,
#endif
			     RECUR_USER_OPTIONS)
     double *recur_parameter_lower_bound;
     double *recur_parameter_upper_bound;
     double *recur_cost_parameters;
     double *recur_cost_tangents;
     double *recur_cost_curvature;
     ALLOC_INT *recur_parameter_dimension;
     int *recur_parameter_int_real;
#if RECUR_OPTIONS_FILE_DATA
     FILE *recur_ptr_options;
#endif
     USER_DEFINES *RECUR_USER_OPTIONS;
#endif
{
  ALLOC_INT index;
#if RECUR_OPTIONS_FILE_DATA
  char read_option[80];
  ALLOC_INT read_index;
#endif
#if MY_TEMPLATE			/* MY_TEMPLATE_recur_init_decl */
  /* add some declarations if required */
#endif

#if RECUR_OPTIONS_FILE_DATA
  fscanf (recur_ptr_options, "%s", read_option);

  for (index = 0; index < *recur_parameter_dimension; ++index)
    {
#if MY_TEMPLATE			/* MY_TEMPLATE_recur_read_opt */
      /* put in some code as required to alter lines read from recur_asa_opt */
#endif
#if INT_ALLOC
      fscanf (recur_ptr_options, "%d", &read_index);
#else
#if INT_LONG
      fscanf (recur_ptr_options, "%ld", &read_index);
#else
      fscanf (recur_ptr_options, "%d", &read_index);
#endif
#endif
      fscanf (recur_ptr_options, "%lf%lf%lf%d",
	      &(recur_parameter_lower_bound[read_index]),
	      &(recur_parameter_upper_bound[read_index]),
	      &(recur_cost_parameters[read_index]),
	      &(recur_parameter_int_real[read_index]));
    }
#else /* RECUR_OPTIONS_FILE_DATA */
#if ASA_TEMPLATE_SELFOPT
  /*  NOTE:
     USER_OPTIONS->Temperature_Ratio_Scale = x[0];
     USER_OPTIONS->Cost_Parameter_Scale_Ratio = x[1];
   */

  /* store the initial parameter values */
  recur_cost_parameters[0] = 1.0E-5;
  recur_cost_parameters[1] = 1.0;

  recur_parameter_lower_bound[0] = 1.0E-6;
  recur_parameter_upper_bound[0] = 1.0E-4;

  recur_parameter_lower_bound[1] = 0.5;
  recur_parameter_upper_bound[1] = 3.0;

  /* store the initial parameter types */
  for (index = 0; index < *recur_parameter_dimension; ++index)
    recur_parameter_int_real[index] = REAL_TYPE;
#endif
#endif /* RECUR_OPTIONS_FILE_DATA */

#if USER_INITIAL_PARAMETERS_TEMPS
  if ((RECUR_USER_OPTIONS->User_Parameter_Temperature =
       (double *) calloc (*recur_parameter_dimension,
			  sizeof (double))) == NULL)
      exit (9);
  for (index = 0; index < *recur_parameter_dimension; ++index)
    RECUR_USER_OPTIONS->User_Parameter_Temperature[index] = 1.0;
#endif /* USER_INITIAL_PARAMETERS_TEMPS */
#if USER_INITIAL_COST_TEMP
  if ((RECUR_USER_OPTIONS->User_Cost_Temperature =
       (double *) calloc (1, sizeof (double))) == NULL)
      exit (9);
  RECUR_USER_OPTIONS->User_Cost_Temperature[0] = 5.936648E+09;
#endif /* USER_INITIAL_COST_TEMP */
#if DELTA_PARAMETERS
  if ((RECUR_USER_OPTIONS->User_Delta_Parameter =
       (double *) calloc (*recur_parameter_dimension,
			  sizeof (double))) == NULL)
      exit (9);
  for (index = 0; index < *recur_parameter_dimension; ++index)
    RECUR_USER_OPTIONS->User_Delta_Parameter[index] = 0.001;
#endif /* DELTA_PARAMETERS */
#if QUENCH_PARAMETERS
  if ((RECUR_USER_OPTIONS->User_Quench_Param_Scale =
       (double *) calloc (*recur_parameter_dimension,
			  sizeof (double))) == NULL)
      exit (9);
#if ASA_TEMPLATE
  for (index = 0; index < *recur_parameter_dimension; ++index)
    RECUR_USER_OPTIONS->User_Quench_Param_Scale[index] = 1.0;
#endif
#endif /* QUENCH_PARAMETERS */
#if QUENCH_COST
  if ((RECUR_USER_OPTIONS->User_Quench_Cost_Scale =
       (double *) calloc (1, sizeof (double))) == NULL)
      exit (9);
#if ASA_TEMPLATE
  RECUR_USER_OPTIONS->User_Quench_Cost_Scale[0] = 1.0;
#endif
#endif /* QUENCH_COST */

  /* use asa_opt_recur to read in QUENCH RECUR_USER_OPTIONS */
#if RECUR_OPTIONS_FILE_DATA
#if QUENCH_COST
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%lf",
	  &(RECUR_USER_OPTIONS->User_Quench_Cost_Scale[0]));

#if QUENCH_PARAMETERS
  fscanf (recur_ptr_options, "%s", read_option);
  fscanf (recur_ptr_options, "%s", read_option);
  for (index = 0; index < *recur_parameter_dimension; ++index)
    {
#if INT_ALLOC
      fscanf (recur_ptr_options, "%d", &read_index);
#else
#if INT_LONG
      fscanf (recur_ptr_options, "%ld", &read_index);
#else
      fscanf (recur_ptr_options, "%d", &read_index);
#endif
#endif
      fscanf (recur_ptr_options, "%lf",
	      &(RECUR_USER_OPTIONS->User_Quench_Param_Scale[read_index]));
    }
#endif /* QUENCH_PARAMETERS */
#endif /* QUENCH_COST */
#endif /* RECUR_OPTIONS_FILE_DATA */
#if RATIO_TEMPERATURE_SCALES
  if ((RECUR_USER_OPTIONS->User_Temperature_Ratio =
       (double *) calloc (*recur_parameter_dimension,
			  sizeof (double))) == NULL)
      exit (9);
#if ASA_TEMPLATE
  for (index = 0; index < *recur_parameter_dimension; ++index)
    RECUR_USER_OPTIONS->User_Temperature_Ratio[index] = 1.0;
#endif
#endif /* RATIO_TEMPERATURE_SCALES */
  /* Defines the limit of collection of sampled data by asa */
#if ASA_SAMPLE
  /* create memory for Bias_Generated[] */
  if ((RECUR_USER_OPTIONS->Bias_Generated =
       (double *) calloc (*recur_parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);
#if ASA_TEMPLATE
  RECUR_USER_OPTIONS->Limit_Weights = 1.0E-7;
#if QUENCH_COST
  RECUR_USER_OPTIONS->User_Quench_Cost_Scale[0] = 1.0;
#endif
#if QUENCH_PARAMETERS
  for (index = 0; index < *recur_parameter_dimension; ++index)
    RECUR_USER_OPTIONS->User_Quench_Param_Scale[index] = 1.0;
#endif
#endif /* ASA_TEMPLATE */
#endif /* ASA_SAMPLE */

#if ASA_TEMPLATE
#if ASA_PARALLEL
  RECUR_USER_OPTIONS->Gener_Block = 1;
  RECUR_USER_OPTIONS->Gener_Block_Max = 1;
  RECUR_USER_OPTIONS->Gener_Mov_Avr = 1;
#endif
#endif
#if ASA_QUEUE
  if ((RECUR_USER_OPTIONS->Queue_Resolution =
       (double *) calloc (*parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);
#if ASA_TEMPLATE_QUEUE
  RECUR_USER_OPTIONS->Queue_Size = 0;
#endif
#endif /* ASA_QUEUE */
#if ASA_RESOLUTION
  if ((RECUR_USER_OPTIONS->Coarse_Resolution =
       (double *) calloc (*parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);
#if ASA_TEMPLATE_QUEUE
  RECUR_USER_OPTIONS->Coarse_Resolution = 0;
#endif
#endif /* ASA_RESOLUTION */
#if MY_TEMPLATE			/* MY_TEMPLATE_recur_params */
  /* If not using RECUR_OPTIONS_FILE_DATA or data read from recur_asa_opt,
     store the recur_parameter ranges
     store the recur_parameter types
     store the initial recur_parameter values
     other changes needed for initialization */
#endif /* MY_TEMPLATE recur_params */
}

/***********************************************************************
* double recur_cost_function
*	This is the users cost function to optimize
*	(find the minimum).
*	cost_flag is set to TRUE if the parameter set
*	does not violates any constraints
*       recur_parameter_lower_bound and recur_parameter_upper_bound
*       may be adaptively changed during the search.
***********************************************************************/
#if HAVE_ANSI
double
recur_cost_function (double *x,
		     double *recur_parameter_lower_bound,
		     double *recur_parameter_upper_bound,
		     double *recur_cost_tangents,
		     double *recur_cost_curvature,
		     ALLOC_INT * recur_parameter_dimension,
		     int *recur_parameter_int_real,
		     int *recur_cost_flag,
		     int *recur_exit_code,
		     USER_DEFINES * RECUR_USER_OPTIONS)
#else
double
recur_cost_function (x,
		     recur_parameter_lower_bound,
		     recur_parameter_upper_bound,
		     recur_cost_tangents,
		     recur_cost_curvature,
		     recur_parameter_dimension,
		     recur_parameter_int_real,
		     recur_cost_flag,
		     recur_exit_code,
		     RECUR_USER_OPTIONS)
     double *x;
     double *recur_parameter_lower_bound;
     double *recur_parameter_upper_bound;
     double *recur_cost_tangents;
     double *recur_cost_curvature;
     ALLOC_INT *recur_parameter_dimension;
     int *recur_parameter_int_real;
     int *recur_cost_flag;
     int *recur_exit_code;
     USER_DEFINES *RECUR_USER_OPTIONS;
#endif
{
  double cost_value;
  static LONG_INT recur_funevals = 0;
  int *exit_code;
#if OPTIONS_FILE
  FILE *ptr_options;
  char read_option[80];
  int read_int;
#if INT_LONG
  LONG_INT read_long;
#endif
  double read_double;
#endif
#if MY_TEMPLATE			/* MY_TEMPLATE_recur_cost_decl */
  /* add some declarations if required */
#endif

  double *parameter_lower_bound, *parameter_upper_bound;
  double *cost_parameters;
  double *cost_tangents, *cost_curvature;
  ALLOC_INT *parameter_dimension;
  int *parameter_int_real;
  int *cost_flag;
  static LONG_INT *rand_seed;
  static int initial_flag = 0;


  USER_DEFINES *USER_OPTIONS;

  recur_funevals = recur_funevals + 1;

  if ((rand_seed =
       (LONG_INT *) calloc (1, sizeof (LONG_INT))) == NULL)
    exit (9);

  if ((USER_OPTIONS =
       (USER_DEFINES *) calloc (1, sizeof (USER_DEFINES))) == NULL)
    exit (9);

#if OPTIONS_FILE
  /* Test to see if asa_opt is in correct directory.
     This is useful for some PC and Mac compilers. */
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
#else /* OPTIONS_FILE */
  /* USER_OPTIONS->Limit_Acceptances = 10000; */
  USER_OPTIONS->Limit_Acceptances = 1000;
  USER_OPTIONS->Limit_Generated = 99999;
  USER_OPTIONS->Limit_Invalid_Generated_States = 1000;
  USER_OPTIONS->Accepted_To_Generated_Ratio = 1.0E-6;

  USER_OPTIONS->Cost_Precision = 1.0E-18;
  USER_OPTIONS->Maximum_Cost_Repeat = 2;
  USER_OPTIONS->Number_Cost_Samples = 2;

  /* These variables are set below in x[.] */
  /* USER_OPTIONS->Temperature_Ratio_Scale = 1.0E-5; */
  /* USER_OPTIONS->Cost_Parameter_Scale_Ratio = 1.0; */

  USER_OPTIONS->Temperature_Anneal_Scale = 100.;

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
  USER_OPTIONS->Curvature_0 = TRUE;
#endif /* OPTIONS_FILE */

  USER_OPTIONS->Temperature_Ratio_Scale = x[0];
  USER_OPTIONS->Cost_Parameter_Scale_Ratio = x[1];

  if (initial_flag == 0)
    {
      /* first value of *rand_seed */
#if ASA_LIB
      *rand_seed = (asa_rand_seed ? *asa_rand_seed : (LONG_INT) 696969);
#else
      *rand_seed = 696969;
#endif
    }

  if ((parameter_dimension =
       (ALLOC_INT *) calloc (1, sizeof (ALLOC_INT))) == NULL)
    exit (9);
  if ((exit_code = (int *) calloc (1, sizeof (int))) == NULL)
      exit (9);
  if ((cost_flag = (int *) calloc (1, sizeof (int))) == NULL)
      exit (9);

  /* the number of parameters for the cost function */
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

#else /* OPTIONS_FILE_DATA */
#if ASA_TEST
  /* set parameter dimension if SELF_OPTIMIZE=TRUE */
  *parameter_dimension = 4;
#endif /* ASA_TEST */
#endif /* OPTIONS_FILE_DATA */
#if MY_TEMPLATE			/* MY_TEMPLATE_recur_dim */
  /* If not using OPTIONS_FILE_DATA or data read from asa_opt,
     set parameter dimension if SELF_OPTIMIZE=TRUE */
#endif /* MY_TEMPLATE recur_dim */

  if ((parameter_lower_bound =
       (double *) calloc (*parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);
  if ((parameter_upper_bound =
       (double *) calloc (*parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);
  if ((cost_parameters =
       (double *) calloc (*parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);
  if ((parameter_int_real =
       (int *) calloc (*parameter_dimension, sizeof (int))
      ) == NULL)
      exit (9);
  if ((cost_tangents =
       (double *) calloc (*parameter_dimension, sizeof (double))
      ) == NULL)
      exit (9);

  if (USER_OPTIONS->Curvature_0 == FALSE || USER_OPTIONS->Curvature_0 == -1)
    {
      if ((cost_curvature =
	   (double *) calloc ((*parameter_dimension) *
			      (*parameter_dimension),
			      sizeof (double))) == NULL)
	  exit (9);
    }
  else
    {
      cost_curvature = (double *) NULL;
    }

#if ASA_TEMPLATE_SELFOPT
  /* Set memory to that required for use. */
  USER_OPTIONS->Asa_Data_Dim = 2;
  if ((USER_OPTIONS->Asa_Data =
       (double *) calloc (2, sizeof (double))) == NULL)
      exit (9);
  /* Use Asa_Data[0] as flag, e.g., if used with SELF_OPTIMIZE. */
  USER_OPTIONS->Asa_Data[0] = 1.0;
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

  initialize_parameters (cost_parameters,
			 parameter_lower_bound,
			 parameter_upper_bound,
			 cost_tangents,
			 cost_curvature,
			 parameter_dimension,
			 parameter_int_real,
#if OPTIONS_FILE_DATA
			 ptr_options,
#endif
			 USER_OPTIONS);
#if OPTIONS_FILE
  fclose (ptr_options);
#endif

  /* It might be a good idea to place a loop around this call,
     and to average over several values of funevals returned by
     trajectories of cost_value. */

  funevals = 0;

#if USER_ASA_OUT
  if ((USER_OPTIONS->Asa_Out_File =
       (char *) calloc (80, sizeof (char))
      ) == NULL)
      exit (9);
#if ASA_TEMPLATE_SELFOPT
  strcpy (USER_OPTIONS->Asa_Out_File, "asa_rcur");
#endif
#endif
  cost_value = asa (cost_function,
		    randflt,
		    rand_seed,
		    cost_parameters,
		    parameter_lower_bound,
		    parameter_upper_bound,
		    cost_tangents,
		    cost_curvature,
		    parameter_dimension,
		    parameter_int_real,
		    cost_flag,
		    exit_code,
		    USER_OPTIONS);
#if MY_TEMPLATE			/* MY_TEMPLATE_recur_post_asa */
#endif

  if (cost_value > .001)
    {
      *recur_cost_flag = FALSE;
    }
  else
    {
      *recur_cost_flag = TRUE;
    }

#if FALSE			/* set to 1 to activate FAST EXIT */
  /* Make a quick exit */
  if (recur_funevals >= 10)
    {
      *recur_cost_flag = FALSE;
      RECUR_USER_OPTIONS->Limit_Invalid_Generated_States = 0;
      fprintf (ptr_out, "FAST EXIT set at recur_funevals = 10\n\n");
    }
#endif

  /* print every RECUR_PRINT_FREQUENCY evaluations */
  if ((RECUR_PRINT_FREQUENCY > 0) &&
      ((recur_funevals % RECUR_PRINT_FREQUENCY) == 0))
    {
      USER_OPTIONS->Temperature_Ratio_Scale = x[0];
      fprintf (ptr_out, "USER_OPTIONS->Temperature_Ratio_Scale = %12.7g\n",
	       USER_OPTIONS->Temperature_Ratio_Scale);
      USER_OPTIONS->Cost_Parameter_Scale_Ratio = x[1];
      fprintf (ptr_out, "USER_OPTIONS->Cost_Parameter_Scale_Ratio = %12.7g\n",
	       USER_OPTIONS->Cost_Parameter_Scale_Ratio);
    }
#if TIME_CALC
  print_time ("", ptr_out);
#endif

  fprintf (ptr_out, "recur_funevals = %ld, *recur_cost_flag = %d\n",
	   recur_funevals, *recur_cost_flag);
  /* cost function = number generated at best cost */
#if ASA_TEMPLATE_SELFOPT
  funevals = (LONG_INT) (USER_OPTIONS->Asa_Data[1]);
  fprintf (ptr_out, "\tbest_funevals = %ld, cost_value = %12.7g\n\n",
	   funevals, cost_value);
  /* cost function = total number generated during run */
#endif
#if ASA_SAMPLE
  fprintf (ptr_out, "\tfunevals = %ld, cost_value = %12.7g\n\n",
	   funevals, cost_value);
#endif
  fflush (ptr_out);

#if ASA_TEMPLATE_SAMPLE
  ptr_asa = fopen ("myASA_out", "r");
  sample (ptr_out, ptr_asa);
#endif

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
  if (USER_OPTIONS->Curvature_0 == FALSE || USER_OPTIONS->Curvature_0 == -1)
    free (cost_curvature);
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
  free (parameter_dimension);
  free (exit_code);
  free (cost_flag);
  free (parameter_lower_bound);
  free (parameter_upper_bound);
  free (cost_parameters);
  free (parameter_int_real);
  free (cost_tangents);
  free (rand_seed);

  return ((double) funevals);
}

#if USER_COST_SCHEDULE
#if HAVE_ANSI
double
recur_user_cost_schedule (double test_temperature,
			  USER_DEFINES * RECUR_USER_OPTIONS)
#else
double
recur_user_cost_schedule (test_temperature,
			  RECUR_USER_OPTIONS)
     double test_temperature;
     USER_DEFINES *RECUR_USER_OPTIONS;
#endif /* HAVE_ANSI */
{
#if ASA_TEMPLATE
  double x;

  x = test_temperature;

  return (x);
#endif
}
#endif /* USER_COST_SCHEDULE */

#if USER_ACCEPTANCE_TEST
#if HAVE_ANSI
void
recur_user_acceptance_test (double current_cost,
			    ALLOC_INT * recur_parameter_dimension,
			    USER_DEFINES * RECUR_USER_OPTIONS)
#else
void
recur_user_acceptance_test (current_cost,
			    recur_parameter_dimension,
			    RECUR_USER_OPTIONS)
     double current_cost;
     ALLOC_INT *recur_parameter_dimension;
     USER_DEFINES *RECUR_USER_OPTIONS;
#endif /* HAVE_ANSI */
{
  double x, uniform_test, curr_cost_temp;
#if USER_ACCEPT_ASYMP_EXP
  double q, delta_cost;
#endif

#if ASA_TEMPLATE		/* ASA cost index */
  /* Calculate the current ASA cost index.  This could be useful
     to define a new schedule for the cost temperature, beyond
     simple changes that can be made using USER_COST_SCHEDULE. */

  double k_temperature, quench, y;

#if QUENCH_COST
  quench = RECUR_USER_OPTIONS->User_Quench_Cost_Scale[0];
#else
  quench = 1.0;
#endif /* QUENCH_COST */
  y = -F_LOG (RECUR_USER_OPTIONS->Cost_Temp_Curr
	      / RECUR_USER_OPTIONS->Cost_Temp_Init)
    / RECUR_USER_OPTIONS->Cost_Temp_Scale;

  k_temperature = F_POW (y, (double) *recur_parameter_dimension / quench);
#endif /* ASA cost index */

  uniform_test = randflt (RECUR_USER_OPTIONS->Random_Seed);
  curr_cost_temp = RECUR_USER_OPTIONS->Cost_Temp_Curr;

#if ASA_TEMPLATE
#if USER_COST_SCHEDULE
  curr_cost_temp =
    (RECUR_USER_OPTIONS->Cost_Schedule (RECUR_USER_OPTIONS->Cost_Temp_Curr,
					RECUR_USER_OPTIONS)
     + (double) EPS_DOUBLE);
#else
  curr_cost_temp = RECUR_USER_OPTIONS->Cost_Temp_Curr;
#endif
#endif /* ASA_TEMPLATE */

#if USER_ACCEPT_ASYMP_EXP
#if USER_COST_SCHEDULE
  curr_cost_temp =
    (RECUR_USER_OPTIONS->Cost_Schedule (RECUR_USER_OPTIONS->Cost_Temp_Curr,
					RECUR_USER_OPTIONS)
     + (double) EPS_DOUBLE);
#endif

  delta_cost = (current_cost - *(RECUR_USER_OPTIONS->Last_Cost))
    / (curr_cost_temp + (double) EPS_DOUBLE);

  q = RECUR_USER_OPTIONS->Asymp_Exp_Param;
  if (fabs (1.0 - q) < (double) EPS_DOUBLE)
    x = MIN (1.0, (F_EXP (-delta_cost)));	/* Boltzmann test */
  else if ((1.0 - (1.0 - q) * delta_cost) < (double) EPS_DOUBLE)
    x = MIN (1.0, (F_EXP (-delta_cost)));	/* Boltzmann test */
  else
    x = MIN (1.0, F_POW ((1.0 - (1.0 - q) * delta_cost), (1.0 / (1.0 - q))));

  RECUR_USER_OPTIONS->Prob_Bias = x;
  if (x >= uniform_test)
    RECUR_USER_OPTIONS->User_Acceptance_Flag = TRUE;
  else
    RECUR_USER_OPTIONS->User_Acceptance_Flag = FALSE;

#endif /* USER_ACCEPT_ASYMP_EXP */
}
#endif /* USER_ACCEPTANCE_TEST */

#if USER_GENERATING_FUNCTION
#if HAVE_ANSI
double
recur_user_generating_distrib (LONG_INT * seed,
			       ALLOC_INT * recur_parameter_dimension,
			       ALLOC_INT index_v,
			       double temperature_v,
			       double init_param_temp_v,
			       double temp_scale_params_v,
			       double parameter_v,
			       double parameter_range_v,
			       double *last_saved_parameter,
			       USER_DEFINES * RECUR_USER_OPTIONS)
#else
double
recur_user_generating_distrib (seed,
			       recur_parameter_dimension,
			       index_v,
			       temperature_v,
			       init_param_temp_v,
			       temp_scale_params_v,
			       parameter_v,
			       parameter_range_v,
			       last_saved_parameter,
			       RECUR_USER_OPTIONS)
     LONG_INT *seed;
     ALLOC_INT *recur_parameter_dimension;
     ALLOC_INT index_v;
     double temperature_v;
     double init_param_temp_v;
     double temp_scale_params_v;
     double parameter_v;
     double parameter_range_v;
     double *last_saved_parameter;
     USER_DEFINES *RECUR_USER_OPTIONS;
#endif
{
  double x, y, z;
#if FALSE			/* set to TRUE to activate */
  /* Calculate the current ASA temperature index for parameter_v.
     This could be useful, e.g., to define a slower polynomial
     or logarithmic schedule, as would be required by Cauchy
     or Gaussian distributions, respectively.  These distributions
     are defined below. */

  double k_temperature_v, temperature_0_v, quench_v;
  static double PI = 3.14159265358979323846;

#if QUENCH_PARAMETERS
  quench_v = USER_OPTIONS->User_Quench_Param_Scale[index_v];
#else
  quench_v = 1.0;
#endif
  y = -F_LOG (temperature_v / init_param_temp_v) / temp_scale_params_v;

  k_temperature_v = F_POW (y, (double) *recur_parameter_dimension / quench_v);
#endif

#if ASA_TEMPLATE
  /* This is the ASA distribution.  A slower temperature schedule can be
     obtained here, e.g., temperature_v = pow(temperature_v, 0.5); */

  x = randflt (seed);
  y = x < 0.5 ? -1.0 : 1.0;
  z = y * temperature_v * (F_POW ((1.0 + 1.0 / temperature_v),
				  fabs (2.0 * x - 1.0)) - 1.0);

  x = parameter_v + z * parameter_range_v;
#endif /* ASA_TEMPLATE */

#if FALSE			/* Cauchy Distribution */
  /* Note that this is a one-dimensional Cauchy distribution, which
     may not be optimal for problems in more than one dimension. */

  for (;;)
    {
      x = 2.0 * myrand (seed) - 1.0;
      y = 2.0 * myrand (seed) - 1.0;
      z = x * x + y * y;
      if (z <= 1.0)
	break;
    }
  if (fabs (x) < (double) EPS_DOUBLE)
    x = (x < 0.0 ? x - (double) EPS_DOUBLE : x + (double) EPS_DOUBLE);

  z = (y / x);

  temperature_0_v = parameter_range_v;
  y = temperature_0_v / k_temperature_v;

  x = parameter_v + y * z;

  return (x);
#endif /* Cauchy Distribution */

#if FALSE			/* Gaussian Distribution */
  /* Note that this is a one-dimensional Gaussian distribution, which
     may not be optimal for problems in more than one dimension. */

  x = randflt (seed);
  y = randflt (seed);

  if (x < (double) EPS_DOUBLE)
    x += (double) EPS_DOUBLE;
  z = sqrt (-2.0 * F_LOG (x)) * sin (2.0 * PI * y);

  temperature_0_v = parameter_range_v;
  y = temperature_0_v / F_LOG (k_temperature_v);

  x = parameter_v + y * z;

  return (x);
#endif /* Gaussian Distribution */

  return (x);
}
#endif /* USER_GENERATING_FUNCTION */

#if USER_REANNEAL_COST
#if HAVE_ANSI
int
recur_user_reanneal_cost (double *cost_best,
			  double *cost_last,
			  double *initial_cost_temperature,
			  double *current_cost_temperature,
			  USER_DEFINES * RECUR_USER_OPTIONS)
#else
int
recur_user_reanneal_cost (cost_best,
			  cost_last,
			  initial_cost_temperature,
			  current_cost_temperature,
			  RECUR_USER_OPTIONS)
     double *cost_best;
     double *cost_last;
     double *initial_cost_temperature;
     double *current_cost_temperature;
     USER_DEFINES *RECUR_USER_OPTIONS;
#endif /* HAVE_ANSI */
{
#if ASA_TEMPLATE
  double tmp_dbl;

  tmp_dbl = MAX (fabs (*cost_last), fabs (*cost_best));
  tmp_dbl = MAX ((double) EPS_DOUBLE, tmp_dbl);
  *initial_cost_temperature = MIN (*initial_cost_temperature, tmp_dbl);

  return (TRUE);
#endif
}
#endif /* USER_REANNEAL_COST */

#if USER_REANNEAL_PARAMETERS
#if HAVE_ANSI
double
recur_user_reanneal_params (double current_temp,
			    double tangent,
			    double max_tangent,
			    USER_DEFINES * RECUR_USER_OPTIONS)
#else
double
recur_user_reanneal_params (current_temp,
			    tangent,
			    max_tangent,
			    RECUR_USER_OPTIONS)
     double current_temp;
     double tangent;
     double max_tangent;
     USER_DEFINES *RECUR_USER_OPTIONS;
#endif /* HAVE_ANSI */
{
#if ASA_TEMPLATE
  double x;

  x = current_temp * (max_tangent / tangent);

  return (x);
#endif
}
#endif /* USER_REANNEAL_PARAMETERS */
#endif /* SELF_OPTIMIZE */

#if FITLOC
#if HAVE_ANSI
double
calcf (double *xloc,
       double *parameter_lower_bound,
       double *parameter_upper_bound,
       double *cost_tangents,
       double *cost_curvature,
       ALLOC_INT * parameter_dimension,
       int *parameter_int_real,
       int *cost_flag,
       int *exit_code,
       USER_DEFINES * OPTIONS,
       FILE * ptr_out)
#else
double
calcf (xloc,
       parameter_lower_bound,
       parameter_upper_bound,
       cost_tangents,
       cost_curvature,
       parameter_dimension,
       parameter_int_real,
       cost_flag,
       exit_code,
       OPTIONS,
       ptr_out)
     double *x;
     double *parameter_lower_bound;
     double *parameter_upper_bound;
     double *cost_tangents;
     double *cost_curvature;
     ALLOC_INT *parameter_dimension;
     int *parameter_int_real;
     int *cost_flag;
     int *exit_code;
     USER_DEFINES *OPTIONS;
     FILE *ptr_out;
#endif
{
  ALLOC_INT index_v;
#if FITLOC_ROUND
  double x, min_parameter_v, max_parameter_v, parameter_range_v;
#endif
  double floc, dum;

#if FITLOC_ROUND
  /* The following section for adjustments of parameters is taken from
     generate_new_state() in asa.c */
  for (index_v = 0; index_v < *parameter_dimension; ++index_v)
    {
      if (fabs (parameter_lower_bound[index_v] - parameter_upper_bound[index_v])
	  < EPS_DOUBLE)
	continue;

      x = xloc[index_v];

      min_parameter_v = parameter_lower_bound[index_v];
      max_parameter_v = parameter_upper_bound[index_v];
      parameter_range_v = max_parameter_v - min_parameter_v;

      /* Handle discrete parameters. */
#if ASA_RESOLUTION
      xres = OPTIONS->Coarse_Resolution[index_v];
      if (xres > EPS_DOUBLE)
	{
	  min_parameter_v -= (xres / 2.0);
	  max_parameter_v += (xres / 2.0);
	  parameter_range_v = max_parameter_v - min_parameter_v;
	}
#endif /* ASA_RESOLUTION */
      if (parameter_int_real[index_v] > 0)
	{
#if ASA_RESOLUTION
	  if (xres > EPS_DOUBLE)
	    {
	      ;
	    }
	  else
	    {
#endif /* ASA_RESOLUTION */
	      min_parameter_v -= 0.5;
	      max_parameter_v += 0.5;
	      parameter_range_v = max_parameter_v - min_parameter_v;
	    }
#if ASA_RESOLUTION
	}
#endif
#if ASA_RESOLUTION
      if (xres > EPS_DOUBLE)
	{
	  xint = xres * (double) ((LONG_INT) (x / xres));
	  xplus = xint + xres;
	  xminus = xint - xres;
	  dx = fabs (xint - x);
	  dxminus = fabs (xminus - x);
	  dxplus = fabs (xplus - x);

	  if (dx < dxminus && dx < dxplus)
	    x = xint;
	  else if (dxminus < dxplus)
	    x = xminus;
	  else
	    x = xplus;
	}
#endif /* ASA_RESOLUTION */

      /* Handle discrete parameters.
         You might have to check rounding on your machine. */
      if (parameter_int_real[index_v] > 0)
	{
#if ASA_RESOLUTION
	  if (xres > EPS_DOUBLE)
	    {
	      ;
	    }
	  else
	    {
#endif /* ASA_RESOLUTION */
	      if (x < min_parameter_v + 0.5)
		x = min_parameter_v + 0.5 + (double) EPS_DOUBLE;
	      if (x > max_parameter_v - 0.5)
		x = max_parameter_v - 0.5 + (double) EPS_DOUBLE;

	      if (x + 0.5 > 0.0)
		{
		  x = (double) ((LONG_INT) (x + 0.5));
		}
	      else
		{
		  x = (double) ((LONG_INT) (x - 0.5));
		}
	      if (x > parameter_upper_bound[index_v])
		x = parameter_upper_bound[index_v];
	      if (x < parameter_lower_bound[index_v])
		x = parameter_lower_bound[index_v];
	    }
#if ASA_RESOLUTION
	}
      if (xres > EPS_DOUBLE)
	{
	  if (x < min_parameter_v + xres / 2.0)
	    x = min_parameter_v + xres / 2.0 + (double) EPS_DOUBLE;
	  if (x > max_parameter_v - xres / 2.0)
	    x = max_parameter_v - xres / 2.0 + (double) EPS_DOUBLE;

	  if (x > parameter_upper_bound[index_v])
	    x = parameter_upper_bound[index_v];
	  if (x < parameter_lower_bound[index_v])
	    x = parameter_lower_bound[index_v];
	}
#endif /* ASA_RESOLUTION */
      if ((x < parameter_lower_bound[index_v])
	  || (x > parameter_upper_bound[index_v]))
	{
	  ;
	}
      else
	{
	  xloc[index_v] = x;
	}
    }
#endif /* FITLOC_ROUND */

  floc = cost_function (xloc,
			parameter_lower_bound,
			parameter_upper_bound,
			cost_tangents,
			cost_curvature,
			parameter_dimension,
			parameter_int_real,
			cost_flag,
			exit_code,
			OPTIONS);

  if (*cost_flag == FALSE)
    {
      floc += OPTIONS->Penalty;
    }

  for (index_v = 0; index_v < *parameter_dimension; ++index_v)
    {
      if (fabs (parameter_lower_bound[index_v] - parameter_upper_bound[index_v])
	  < EPS_DOUBLE)
	continue;
      dum = parameter_upper_bound[index_v] - xloc[index_v];
      if (dum < EPS_DOUBLE)
	floc += OPTIONS->Penalty;
      dum = xloc[index_v] - parameter_lower_bound[index_v];
      if (dum < EPS_DOUBLE)
	floc += OPTIONS->Penalty;
    }

  return (floc);
}

#if HAVE_ANSI
double
fitloc (double *xloc,
	double *parameter_lower_bound,
	double *parameter_upper_bound,
	double *cost_tangents,
	double *cost_curvature,
	ALLOC_INT * parameter_dimension,
	int *parameter_int_real,
	int *cost_flag,
	int *exit_code,
	USER_DEFINES * OPTIONS,
	FILE * ptr_out)
#else
double
fitloc (xloc,
	parameter_lower_bound,
	parameter_upper_bound,
	cost_tangents,
	cost_curvature,
	parameter_dimension,
	parameter_int_real,
	cost_flag,
	exit_code,
	OPTIONS,
	ptr_out)
     double *xloc;
     double *parameter_lower_bound;
     double *parameter_upper_bound;
     double *cost_tangents;
     double *cost_curvature;
     ALLOC_INT *parameter_dimension;
     int *parameter_int_real;
     int *cost_flag;
     int *exit_code;
     USER_DEFINES *OPTIONS;
     FILE *ptr_out;
#endif
{
  ALLOC_INT index_v;
#if FITLOC_ROUND
  double x, min_parameter_v, max_parameter_v, parameter_range_v;
#endif
  double *xsave;
  double tol1, tol2, alpha, beta1, beta2, gamma, delta, floc, fsave, ffinal;
  int itermax, no_progress, tot_iters, locflg;
#if ASA_RESOLUTION
  double xres, xint, xminus, xplus, dx, dxminus, dxplus;
#endif

  if (OPTIONS->Fit_Local == 1)
    {
      fprintf (ptr_out, "\n\nSTART LOCAL FIT\n");
    }
  else
    {
      fprintf (ptr_out, "\n\nSTART LOCAL FIT Independent of ASA\n");
    }
  fflush (ptr_out);

  xsave = (double *) calloc (*parameter_dimension, sizeof (double));

  /* The following simplex parameters may need adjustments for your system. */
  tol1 = EPS_DOUBLE;
  tol2 = EPS_DOUBLE * 100.;
  itermax = 500;
  no_progress = 4;
  alpha = 1.0;
  beta1 = 0.75;
  beta2 = 0.75;
  gamma = 1.25;
  delta = 2.50;

  for (index_v = 0; index_v < *parameter_dimension; ++index_v)
    {
      xsave[index_v] = xloc[index_v];
    }

  fsave = cost_function (xloc,
			 parameter_lower_bound,
			 parameter_upper_bound,
			 cost_tangents,
			 cost_curvature,
			 parameter_dimension,
			 parameter_int_real,
			 cost_flag,
			 exit_code,
			 OPTIONS);

  tot_iters = simplex (xloc,
		       parameter_lower_bound,
		       parameter_upper_bound,
		       cost_tangents,
		       cost_curvature,
		       parameter_dimension,
		       parameter_int_real,
		       cost_flag,
		       exit_code,
		       OPTIONS,
		       ptr_out,
		       tol1,
		       tol2,
		       itermax,
		       no_progress,
		       alpha,
		       beta1,
		       beta2,
		       gamma,
		       delta);
  fflush (ptr_out);

#if FITLOC_ROUND
  /* The following section for adjustments of parameters is taken from
     generate_new_state() in asa.c */
  for (index_v = 0; index_v < *parameter_dimension; ++index_v)
    {
      if (fabs (parameter_lower_bound[index_v] - parameter_upper_bound[index_v])
	  < EPS_DOUBLE)
	continue;

      x = xloc[index_v];

      min_parameter_v = parameter_lower_bound[index_v];
      max_parameter_v = parameter_upper_bound[index_v];
      parameter_range_v = max_parameter_v - min_parameter_v;

      /* Handle discrete parameters. */
#if ASA_RESOLUTION
      xres = OPTIONS->Coarse_Resolution[index_v];
      if (xres > EPS_DOUBLE)
	{
	  min_parameter_v -= (xres / 2.0);
	  max_parameter_v += (xres / 2.0);
	  parameter_range_v = max_parameter_v - min_parameter_v;
	}
#endif /* ASA_RESOLUTION */
      if (parameter_int_real[index_v] > 0)
	{
#if ASA_RESOLUTION
	  if (xres > EPS_DOUBLE)
	    {
	      ;
	    }
	  else
	    {
#endif /* ASA_RESOLUTION */
	      min_parameter_v -= 0.5;
	      max_parameter_v += 0.5;
	      parameter_range_v = max_parameter_v - min_parameter_v;
	    }
#if ASA_RESOLUTION
	}
#endif
#if ASA_RESOLUTION
      if (xres > EPS_DOUBLE)
	{
	  xint = xres * (double) ((LONG_INT) (x / xres));
	  xplus = xint + xres;
	  xminus = xint - xres;
	  dx = fabs (xint - x);
	  dxminus = fabs (xminus - x);
	  dxplus = fabs (xplus - x);

	  if (dx < dxminus && dx < dxplus)
	    x = xint;
	  else if (dxminus < dxplus)
	    x = xminus;
	  else
	    x = xplus;
	}
#endif /* ASA_RESOLUTION */

      /* Handle discrete parameters.
         You might have to check rounding on your machine. */
      if (parameter_int_real[index_v] > 0)
	{
#if ASA_RESOLUTION
	  if (xres > EPS_DOUBLE)
	    {
	      ;
	    }
	  else
	    {
#endif /* ASA_RESOLUTION */
	      if (x < min_parameter_v + 0.5)
		x = min_parameter_v + 0.5 + (double) EPS_DOUBLE;
	      if (x > max_parameter_v - 0.5)
		x = max_parameter_v - 0.5 + (double) EPS_DOUBLE;

	      if (x + 0.5 > 0.0)
		{
		  x = (double) ((LONG_INT) (x + 0.5));
		}
	      else
		{
		  x = (double) ((LONG_INT) (x - 0.5));
		}
	      if (x > parameter_upper_bound[index_v])
		x = parameter_upper_bound[index_v];
	      if (x < parameter_lower_bound[index_v])
		x = parameter_lower_bound[index_v];
	    }
#if ASA_RESOLUTION
	}
      if (xres > EPS_DOUBLE)
	{
	  if (x < min_parameter_v + xres / 2.0)
	    x = min_parameter_v + xres / 2.0 + (double) EPS_DOUBLE;
	  if (x > max_parameter_v - xres / 2.0)
	    x = max_parameter_v - xres / 2.0 + (double) EPS_DOUBLE;

	  if (x > parameter_upper_bound[index_v])
	    x = parameter_upper_bound[index_v];
	  if (x < parameter_lower_bound[index_v])
	    x = parameter_lower_bound[index_v];
	}
#endif /* ASA_RESOLUTION */
      if ((x < parameter_lower_bound[index_v])
	  || (x > parameter_upper_bound[index_v]))
	{
	  fprintf (ptr_out, "OUT OF BOUNDS xloc[%ld] = %g\n",
		   index_v, xloc[index_v]);
	}
      else
	{
	  xloc[index_v] = x;
	}
    }
#endif /* FITLOC_ROUND */

  floc = cost_function (xloc,
			parameter_lower_bound,
			parameter_upper_bound,
			cost_tangents,
			cost_curvature,
			parameter_dimension,
			parameter_int_real,
			cost_flag,
			exit_code,
			OPTIONS);

  if (fabs (floc - fsave) < (double) EPS_DOUBLE)
    {
      locflg = 1;
      ffinal = fsave;
      fprintf (ptr_out, "\nsame global cost = %g\tlocal cost = %g\n\n",
	       fsave, floc);
    }
  else
    {
      if (floc < fsave)
	{
	  locflg = 0;
	  ffinal = floc;
	}
      else
	{
	  locflg = 1;
	  ffinal = fsave;
	}
      fprintf (ptr_out, "\nDIFF global cost = %g\tlocal cost = %g\n\n",
	       fsave, floc);
    }

  for (index_v = 0; index_v < *parameter_dimension; ++index_v)
    {
      if (fabs (xloc[index_v] - xsave[index_v]) < (double) EPS_DOUBLE)
	{
	  fprintf (ptr_out, "same global param[%ld] = %g\tlocal param = %g\n",
		   index_v, xsave[index_v], xloc[index_v]);
	}
      else
	{
	  fprintf (ptr_out, "DIFF global param[%ld] = %g\tlocal param = %g\n",
		   index_v, xsave[index_v], xloc[index_v]);
	  if (locflg == 1)
	    {
	      xloc[index_v] = xsave[index_v];
	    }
	}
    }

  fprintf (ptr_out, "\n");
  fflush (ptr_out);

  free (xsave);

  return (ffinal);
}

/*
   Written by Mark Johnson <mark@microunity.com>, based on 
   %A J.A. Nelder
   %A R. Mead
   %T A simplex method for function minimization
   %J Computer J. (UK)
   %V 7
   %D 1964
   %P 308-313
   adapted for use in ASA by Lester Ingber <ingber@ingber.com>
 */

#if HAVE_ANSI
int
simplex (double *x,
	 double *parameter_lower_bound,
	 double *parameter_upper_bound,
	 double *cost_tangents,
	 double *cost_curvature,
	 ALLOC_INT * parameter_dimension,
	 int *parameter_int_real,
	 int *cost_flag,
	 int *exit_code,
	 USER_DEFINES * OPTIONS,
	 FILE * ptr_out,
	 double tol1,
	 double tol2,
	 int itermax,
	 int no_progress,
	 double alpha,
	 double beta1,
	 double beta2,
	 double gamma,
	 double delta)
#else
int
simplex (x,
	 parameter_lower_bound,
	 parameter_upper_bound,
	 cost_tangents,
	 cost_curvature,
	 parameter_dimension,
	 parameter_int_real,
	 cost_flag,
	 exit_code,
	 OPTIONS,
	 ptr_out,
	 tol1,
	 tol2,
	 itermax,
	 no_progress,
	 alpha,
	 beta1,
	 beta2,
	 gamma,
	 delta)
     double *x;
     double *parameter_lower_bound;
     double *parameter_upper_bound;
     double *cost_tangents;
     double *cost_curvature;
     ALLOC_INT *parameter_dimension;
     int *parameter_int_real;
     int *cost_flag;
     int *exit_code;
     USER_DEFINES *OPTIONS;
     FILE *ptr_out;
     double tol1;
     double tol2;
     int itermax;
     int no_progress;
     double alpha;
     double beta1;
     double beta2;
     double gamma;
     double delta;
#endif
{
  double fs, fl, fh, fr, fe, fc1, fc2, ftmp, flast;
  double err1;
  double *fvals;
  double **splx;		/* the simplex of points */
  double *x0;			/* centroid of simplex */
  double *xr;			/* point for a reflection */
  double *xe;			/* point for an expansion */
  double *xc1;			/* point for a minor contraction */
  double *xc2;			/* point for a major contraction */
  int s, l, h;
  int i, j, iters, futility;
  int lastprint;

  fvals = (double *) calloc (*parameter_dimension + 1, sizeof (double));
  splx = (double **) calloc (*parameter_dimension + 1, sizeof (double *));
  for (i = 0; i <= *parameter_dimension; i++)
    splx[i] = (double *) calloc (*parameter_dimension, sizeof (double));
  x0 = (double *) calloc (*parameter_dimension, sizeof (double));
  xr = (double *) calloc (*parameter_dimension, sizeof (double));
  xe = (double *) calloc (*parameter_dimension, sizeof (double));
  xc1 = (double *) calloc (*parameter_dimension, sizeof (double));
  xc2 = (double *) calloc (*parameter_dimension, sizeof (double));

  /* build the initial simplex */
  for (i = 0; i < *parameter_dimension; i++)
    {
      splx[0][i] = x[i];
    }
  for (i = 1; i <= *parameter_dimension; i++)
    {
      for (j = 0; j < *parameter_dimension; j++)
	{
	  if ((j + 1) == i)
	    splx[i][j] = (x[j] * 2.25) + tol2;
	  else
	    splx[i][j] = x[j];
	  xr[j] = splx[i][j];
	}
      fvals[i] = calcf (xr,
			parameter_lower_bound,
			parameter_upper_bound,
			cost_tangents,
			cost_curvature,
			parameter_dimension,
			parameter_int_real,
			cost_flag,
			exit_code,
			OPTIONS,
			ptr_out);
    }

  /* and of course compute function at starting point */
  fvals[0] = calcf (x,
		    parameter_lower_bound,
		    parameter_upper_bound,
		    cost_tangents,
		    cost_curvature,
		    parameter_dimension,
		    parameter_int_real,
		    cost_flag,
		    exit_code,
		    OPTIONS,
		    ptr_out);

  /* now find the largest, 2nd largest, smallest f values */
  if (fvals[0] > fvals[1])
    {
      h = 0;
      s = 1;
      l = 1;
    }
  else
    {
      h = 1;
      s = 0;
      l = 0;
    }
  fh = fvals[h];
  fs = fvals[s];
  fl = fvals[l];
  for (i = 2; i <= *parameter_dimension; i++)
    {
      if (fvals[i] <= fvals[l])
	{
	  l = i;
	  fl = fvals[i];
	}
      else
	{
	  if (fvals[i] >= fvals[h])
	    {
	      s = h;
	      fs = fh;
	      h = i;
	      fh = fvals[i];
	    }
	  else if (fvals[i] >= fvals[s])
	    {
	      s = i;
	      fs = fvals[i];
	    }
	}
    }
  if ((s == h) || (s == l) || (h == l))
    fprintf (ptr_out, "\nPANIC: s,l,h not unique %d %d %d\n", s, h, l);

  fprintf (ptr_out, "INITIAL SIMPLEX:\n");
  for (i = 0; i <= *parameter_dimension; i++)
    {
      for (j = 0; j < *parameter_dimension; j++)
	{
	  fprintf (ptr_out, "   %11.4g", splx[i][j]);
	}
      fprintf (ptr_out, "      f = %12.5g", fvals[i]);
      if (i == h)
	fprintf (ptr_out, "  HIGHEST");
      if (i == s)
	fprintf (ptr_out, "  SECOND HIGHEST");
      if (i == l)
	fprintf (ptr_out, "  LOWEST");
      fprintf (ptr_out, "\n");
    }

/* MAJOR LOOP */

  flast = fl;
  futility = 0;
  lastprint = 0;
  iters = 0;
  err1 = 1.1 + (1.1 * tol1);
  while ((err1 > tol1) && (iters < itermax) &&
	 (futility < (*parameter_dimension * no_progress)))
    {
      iters++;

      /* now find the largest, 2nd largest, smallest f values */
      if (fvals[0] > fvals[1])
	{
	  h = 0;
	  s = 1;
	  l = 1;
	}
      else
	{
	  h = 1;
	  s = 0;
	  l = 0;
	}
      fh = fvals[h];
      fs = fvals[s];
      fl = fvals[l];
      for (i = 2; i <= *parameter_dimension; i++)
	{
	  if (fvals[i] <= fvals[l])
	    {
	      l = i;
	      fl = fvals[i];
	    }
	  else
	    {
	      if (fvals[i] >= fvals[h])
		{
		  s = h;
		  fs = fh;
		  h = i;
		  fh = fvals[i];
		}
	      else if (fvals[i] >= fvals[s])
		{
		  s = i;
		  fs = fvals[i];
		}
	    }
	}
      if ((s == h) || (s == l) || (h == l))
	fprintf (ptr_out, "\nPANIC: s,l,h not unique %d %d %d\n", s, h, l);

      /* compute the centroid */
      for (j = 0; j < *parameter_dimension; j++)
	{
	  x0[j] = 0.0;
	  for (i = 0; i <= *parameter_dimension; i++)
	    {
	      if (i != h)
		x0[j] += splx[i][j];
	    }
	  x0[j] /= ((double) *parameter_dimension);
	}

      if (fl < flast)
	{
	  flast = fl;
	  futility = 0;
	}
      else
	futility += 1;

      fprintf (ptr_out, "Iteration %3d f(best) = %12.6g halt? = %11.5g\n",
	       iters, fl, err1);
      if ((iters - lastprint) >= 100)
	{
	  fprintf (ptr_out, "\n     Best point seen so far:\n");
	  for (i = 0; i < *parameter_dimension; i++)
	    {
	      fprintf (ptr_out, "     x[%3d] = %15.7g\n", i, splx[l][i]);
	    }
	  lastprint = iters;
	  fprintf (ptr_out, "\n");
	}
      fflush (stdout);

      /* STEP 1: compute a reflected point xr */
      for (i = 0; i < *parameter_dimension; i++)
	{
	  xr[i] = ((1.0 + alpha) * x0[i]) - (alpha * splx[h][i]);
	}
      fr = calcf (xr,
		  parameter_lower_bound,
		  parameter_upper_bound,
		  cost_tangents,
		  cost_curvature,
		  parameter_dimension,
		  parameter_int_real,
		  cost_flag,
		  exit_code,
		  OPTIONS,
		  ptr_out);

      /* typical outcome: <2nd-biggest , >lowest .  Go again */
      if ((fr < fs) && (fr > fl))
	{
	  for (i = 0; i < *parameter_dimension; i++)
	    {
	      splx[h][i] = xr[i];
	    }
	  fvals[h] = fr;
	  goto more_iterations;
	}

      /* STEP 2: if reflected point is favorable, expand the simplex */
      if (fr < fl)
	{
	  for (i = 0; i < *parameter_dimension; i++)
	    {
	      xe[i] = (gamma * xr[i]) + ((1.0 - gamma) * x0[i]);
	    }
	  fe = calcf (xe,
		      parameter_lower_bound,
		      parameter_upper_bound,
		      cost_tangents,
		      cost_curvature,
		      parameter_dimension,
		      parameter_int_real,
		      cost_flag,
		      exit_code,
		      OPTIONS,
		      ptr_out);
	  if (fe < fr)		/* win big; expansion point tiny */
	    {
	      for (i = 0; i < *parameter_dimension; i++)
		{
		  splx[h][i] = xe[i];
		}
	      fvals[h] = fh = fe;
	    }
	  else
	    /* still ok; reflection point a winner */
	    {
	      for (i = 0; i < *parameter_dimension; i++)
		{
		  splx[h][i] = xr[i];
		}
	      fvals[h] = fh = fr;
	    }
	  goto more_iterations;
	}

      /* STEP 3: if reflected point is unfavorable, contract simplex */
      if (fr > fs)
	{
	  if (fr < fh)		/* may as well replace highest pt */
	    {
	      for (i = 0; i < *parameter_dimension; i++)
		{
		  splx[h][i] = xr[i];
		}
	      fvals[h] = fh = fr;
	    }
	  for (i = 0; i < *parameter_dimension; i++)
	    {
	      xc1[i] = (beta1 * xr[i]) + ((1.0 - beta1) * x0[i]);
	    }
	  fc1 = calcf (xc1,
		       parameter_lower_bound,
		       parameter_upper_bound,
		       cost_tangents,
		       cost_curvature,
		       parameter_dimension,
		       parameter_int_real,
		       cost_flag,
		       exit_code,
		       OPTIONS,
		       ptr_out);
	  if (fc1 < fh)		/* slight contraction worked */
	    {
	      for (i = 0; i < *parameter_dimension; i++)
		{
		  splx[h][i] = xc1[i];
		}
	      fvals[h] = fh = fc1;
	      goto more_iterations;
	    }
	  /* now have to try strong contraction */
	  for (i = 0; i < *parameter_dimension; i++)
	    {
	      xc2[i] = (beta2 * splx[h][i]) + ((1.0 - beta2) * x0[i]);
	    }
	  fc2 = calcf (xc2,
		       parameter_lower_bound,
		       parameter_upper_bound,
		       cost_tangents,
		       cost_curvature,
		       parameter_dimension,
		       parameter_int_real,
		       cost_flag,
		       exit_code,
		       OPTIONS,
		       ptr_out);
	  if (fc2 < fh)		/* strong contraction worked */
	    {
	      for (i = 0; i < *parameter_dimension; i++)
		{
		  splx[h][i] = xc2[i];
		}
	      fvals[h] = fh = fc2;
	      goto more_iterations;
	    }
	}

      /* STEP 4: nothing worked.  collapse the simplex around xl */
      for (i = 0; i <= *parameter_dimension; i++)
	{
	  if (i != l)
	    {
	      for (j = 0; j < *parameter_dimension; j++)
		{
		  splx[i][j] = (splx[i][j] + splx[l][j]) / delta;
		  xr[j] = splx[i][j];
		}
	      fvals[i] = calcf (xr,
				parameter_lower_bound,
				parameter_upper_bound,
				cost_tangents,
				cost_curvature,
				parameter_dimension,
				parameter_int_real,
				cost_flag,
				exit_code,
				OPTIONS,
				ptr_out);
	    }
	}

    more_iterations:

      ftmp = 0.00;
      for (i = 0; i <= *parameter_dimension; i++)
	{
	  ftmp += fvals[i];
	}
      ftmp /= ((double) (*parameter_dimension + 1));

      err1 = 0.00;
      for (i = 0; i <= *parameter_dimension; i++)
	{
	  err1 += ((fvals[i] - ftmp) * (fvals[i] - ftmp));
	}
      err1 /= ((double) (*parameter_dimension + 1));
      err1 = sqrt (err1);

    }				/* end of major while loop */

  /* find the smallest f value */
  l = 0;
  fl = fvals[0];
  for (i = 1; i <= *parameter_dimension; i++)
    {
      if (fvals[i] < fvals[l])
	l = i;
    }

  /* give it back to the user */
  for (i = 0; i < *parameter_dimension; i++)
    {
      x[i] = splx[l][i];
    }

  free (fvals);
  for (i = 0; i <= *parameter_dimension; i++)
    free (splx[i]);
  free (splx);
  free (x0);
  free (xr);
  free (xe);
  free (xc1);
  free (xc2);

  return (iters);
}
#else
#endif /* FITLOC */

#if ASA_TEMPLATE_SAMPLE

#if HAVE_ANSI
void
sample (FILE * ptr_out, FILE * ptr_asa)
#else
void
sample (ptr_out, ptr_asa)
     FILE *ptr_out;
     FILE *ptr_asa;
#endif
{
  int ind, n_samples, n_accept, index, dim;
  double cost, cost_temp, bias_accept;
  double param, temp, bias_gener, aver_weight, range;
  double sum, norm, answer, prod, binsize;
  char ch[80], sample[8];

  /*
     This is a demonstration of using ASA_SAMPLE to perform the double integral
     of exp(-x^2 - y^2) for x and y between 0 and 2.  The mesh is quite crude.

     The temperature-dependent acceptance and generated biases factor are
     divided out, and the actual cost function weights each point.
   */

  dim = 2;
  norm = sum = 0.;
  n_samples = 0;

  fprintf (ptr_out,
	   ":SAMPLE:   n_accept   cost        cost_temp    bias_accept    \
 aver_weight\n");
  fprintf (ptr_out,
	   ":SAMPLE:   index      param[]     temp[]       bias_gener[]   \
 range[]\n");
  for (;;)
    {
      fscanf (ptr_asa, "%s", ch);
      if (!strcmp (ch, "exit_status"))
	{
	  break;
	}
      if (strcmp (ch, ":SAMPLE#"))
	{
	  continue;
	}
      ++n_samples;
      fprintf (ptr_out, "%s\n", ch);
      fflush (ptr_out);
      fscanf (ptr_asa, "%s%d%lf%lf%lf%lf",
	  sample, &n_accept, &cost, &cost_temp, &bias_accept, &aver_weight);
      if (strcmp (sample, ":SAMPLE+"))
	{
	  fprintf (ptr_out, "%s %11d %12.7g %12.7g %12.7g %12.7g\n",
	       sample, n_accept, cost, cost_temp, bias_accept, aver_weight);
	}
      else
	{
	  fprintf (ptr_out, "%s %10d %12.7g %12.7g %12.7g %12.7g\n",
	       sample, n_accept, cost, cost_temp, bias_accept, aver_weight);
	}
      prod = bias_accept;
      binsize = 1.0;
      for (ind = 0; ind < dim; ++ind)
	{
	  fscanf (ptr_asa, "%s%d%lf%lf%lf%lf",
		  sample, &index, &param, &temp, &bias_gener, &range);
	  fprintf (ptr_out, "%s %11d %12.7g %12.7g %12.7g %12.7g\n",
		   sample, index, param, temp, bias_gener, range);
	  prod *= bias_gener;
	  binsize *= range;
	}
      /* In this example, retrieve integrand from sampling function */
      sum += ((F_EXP (-cost) * binsize) / prod);
      norm += (binsize / prod);
    }
  sum /= norm;

  answer = 1.0;
  for (ind = 0; ind < dim; ++ind)
    {
      answer *= (0.5 * sqrt (3.14159265) * erf (2.0));
    }

  fprintf (ptr_out, "\n");
  fprintf (ptr_out, "sum = %12.7g, answer = %12.7g\n", sum, answer);
  fprintf (ptr_out, "n_samples = %d, norm = %12.7g\n", n_samples, norm);
  fflush (ptr_out);

}
#endif /* ASA_TEMPLATE_SAMPLE */
#if ASA_TEMPLATE_LIB
int
main ()
{
  double main_cost_value;
  double *main_cost_parameters;
  int main_exit_code;
  LONG_INT number_params;
  ALLOC_INT n_param;
  FILE *ptr_main;

  ptr_main = stdout;

  /* Note this assumes the *parameter_dimension = 4 */
  number_params = 4;

  if ((main_cost_parameters =
       (double *) calloc (number_params, sizeof (double))
      ) == NULL)
      exit (9);

  asa_seed (696969);		/* This is the default random seed. */
  asa_main (&main_cost_value,
	    main_cost_parameters,
	    &main_exit_code);

  fprintf (ptr_main, "main_exit_code = %d\n", main_exit_code);
  fprintf (ptr_main, "main_cost_value = %12.7g\n", main_cost_value);
  fprintf (ptr_main, "parameter\tvalue\n");
  for (n_param = 0; n_param < number_params; ++n_param)
    {
      fprintf (ptr_main,
#if INT_ALLOC
	       "%d\t\t%12.7g\n",
#else
#if INT_LONG
	       "%ld\t\t%12.7g\n",
#else
	       "%d\t\t%12.7g\n",
#endif
#endif
	       n_param, main_cost_parameters[n_param]);
    }

  exit (0);
/* NOTREACHED */
}
#endif /* ASA_TEMPLATE_LIB */
