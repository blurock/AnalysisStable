/***********************************************************************
* Adaptive Simulated Annealing (ASA)
* Lester Ingber <ingber@ingber.com>
* Copyright (c) 1993-1997 Lester Ingber.  All Rights Reserved.
* The LICENSE file must be included with ASA code.
***********************************************************************/

#include "SimulatedAnnealing.hh"

//#define ASA_ID "/* $Id: myASA.cc,v 1.1 2008/02/17 12:13:28 blurock Exp $ */"

//#include "myASA.h"




/***********************************************************************
* generate_new_state
*       Generates a valid new state from the old state
***********************************************************************/
#if HAVE_ANSI
void
generate_new_state (double (*user_random_generator) (LONG_INT *),
		    LONG_INT * seed,
		    double *parameter_minimum,
		    double *parameter_maximum,
		    double *current_user_parameter_temp,
#if USER_GENERATING_FUNCTION
		    double *initial_user_parameter_temp,
		    double *temperature_scale_parameters,
#endif
		    ALLOC_INT * number_parameters,
		    int *parameter_type,
		    STATE * current_generated_state,
		    STATE * last_saved_state,
		    USER_DEFINES * OPTIONS)
#else
void
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
		    OPTIONS)
     double (*user_random_generator) ();
     LONG_INT *seed;
     double *parameter_minimum;
     double *parameter_maximum;
     double *current_user_parameter_temp;
#if USER_GENERATING_FUNCTION
     double *initial_user_parameter_temp;
     double *temperature_scale_parameters;
#endif
     ALLOC_INT *number_parameters;
     int *parameter_type;
     STATE *current_generated_state;
     STATE *last_saved_state;
     USER_DEFINES *OPTIONS;
#endif
{
  ALLOC_INT index_v;
  double x;
  double parameter_v, min_parameter_v, max_parameter_v, temperature_v,
    parameter_range_v;
#if USER_GENERATING_FUNCTION
  double init_param_temp_v;
  double temp_scale_params_v;
#endif
#if ASA_RESOLUTION
  double xres, xint, xminus, xplus, dx, dxminus, dxplus;
#endif

  /* generate a new value for each parameter */
  VFOR (index_v)
  {
    if (OPTIONS->Sequential_Parameters >= -1)
      {
	++OPTIONS->Sequential_Parameters;
	if (OPTIONS->Sequential_Parameters == *number_parameters)
	  OPTIONS->Sequential_Parameters = 0;
	index_v = OPTIONS->Sequential_Parameters;
      }
    min_parameter_v = parameter_minimum[index_v];
    max_parameter_v = parameter_maximum[index_v];
    parameter_range_v = max_parameter_v - min_parameter_v;

    /* ignore parameters that have too small a range */
    if (fabs (parameter_range_v) < (double) EPS_DOUBLE)
      continue;

    temperature_v = current_user_parameter_temp[index_v];
#if USER_GENERATING_FUNCTION
    init_param_temp_v = initial_user_parameter_temp[index_v];
    temp_scale_params_v = temperature_scale_parameters[index_v];
#endif
    parameter_v = last_saved_state->parameter[index_v];

    /* Handle discrete parameters. */
#if ASA_RESOLUTION
    xres = OPTIONS->Coarse_Resolution[index_v];
    if (xres > EPS_DOUBLE)
      {
	min_parameter_v -= (xres / TWO);
	max_parameter_v += (xres / TWO);
	parameter_range_v = max_parameter_v - min_parameter_v;
      }
#endif /* ASA_RESOLUTION */
    if (INTEGER_PARAMETER (index_v))
      {
#if ASA_RESOLUTION
	if (xres > EPS_DOUBLE)
	  {
	    ;
	  }
	else
	  {
#endif /* ASA_RESOLUTION */
	    min_parameter_v -= HALF;
	    max_parameter_v += HALF;
	    parameter_range_v = max_parameter_v - min_parameter_v;
	  }
#if ASA_RESOLUTION
      }
#endif

    /* generate a new state x within the parameter bounds */
    for (;;)
      {
#if USER_GENERATING_FUNCTION
	x = OPTIONS->Generating_Distrib (seed,
					 *number_parameters,
					 index_v,
					 temperature_v,
					 init_param_temp_v,
					 temp_scale_params_v,
					 parameter_v,
					 parameter_range_v,
					 last_saved_state->parameter,
					 OPTIONS);
#else
	x = parameter_v
	  + generate_asa_state (user_random_generator, seed, &temperature_v)
	  * parameter_range_v;
#endif /* USER_GENERATING_FUNCTION */
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

	/* exit the loop if within its valid parameter range */
	if (x <= max_parameter_v - (double) EPS_DOUBLE
	    && x >= min_parameter_v + (double) EPS_DOUBLE)
	  break;
      }

    /* Handle discrete parameters.
       You might have to check rounding on your machine. */
    if (INTEGER_PARAMETER (index_v))
      {
#if ASA_RESOLUTION
	if (xres > EPS_DOUBLE)
	  {
	    ;
	  }
	else
	  {
#endif /* ASA_RESOLUTION */
	    if (x < min_parameter_v + HALF)
	      x = min_parameter_v + HALF + (double) EPS_DOUBLE;
	    if (x > max_parameter_v - HALF)
	      x = max_parameter_v - HALF + (double) EPS_DOUBLE;

	    if (x + HALF > ZERO)
	      {
		x = (double) ((LONG_INT) (x + HALF));
	      }
	    else
	      {
		x = (double) ((LONG_INT) (x - HALF));
	      }
	    if (x > parameter_maximum[index_v])
	      x = parameter_maximum[index_v];
	    if (x < parameter_minimum[index_v])
	      x = parameter_minimum[index_v];
	  }
#if ASA_RESOLUTION
      }
    if (xres > EPS_DOUBLE)
      {
	if (x < min_parameter_v + xres / TWO)
	  x = min_parameter_v + xres / TWO + (double) EPS_DOUBLE;
	if (x > max_parameter_v - xres / TWO)
	  x = max_parameter_v - xres / TWO + (double) EPS_DOUBLE;

	if (x > parameter_maximum[index_v])
	  x = parameter_maximum[index_v];
	if (x < parameter_minimum[index_v])
	  x = parameter_minimum[index_v];
      }
#endif /* ASA_RESOLUTION */

    /* save the newly generated value */
    current_generated_state->parameter[index_v] = x;

    if (OPTIONS->Sequential_Parameters >= 0)
      break;
  }

}

/***********************************************************************
* generate_asa_state
*       This function generates a single value according to the
*       ASA generating function and the passed temperature
***********************************************************************/
#if HAVE_ANSI
double
generate_asa_state (double (*user_random_generator) (LONG_INT *),
		    LONG_INT * seed,
		    double *temp)
#else
double
generate_asa_state (user_random_generator,
		    seed,
		    temp)
     double (*user_random_generator) ();
     LONG_INT *seed;
     double *temp;
#endif
{
  double x, y, z;

  x = (*user_random_generator) (seed);
  y = x < HALF ? -ONE : ONE;
  z = y * *temp * (F_POW ((ONE + ONE / *temp), fabs (TWO * x - ONE)) - ONE);

  return (z);

}

/***********************************************************************
* accept_new_state
*	This procedure accepts or rejects a newly generated state,
*	depending on whether the difference between new and old
*	cost functions passes a statistical test. If accepted,
*	the current state is updated.
***********************************************************************/
#if HAVE_ANSI
void
accept_new_state (double (*user_random_generator) (LONG_INT *),
		  LONG_INT * seed,
		  double *parameter_minimum,
		  double *parameter_maximum,
		  double *current_cost_temperature,
#if ASA_SAMPLE
		  double *current_user_parameter_temp,
#endif
		  ALLOC_INT * number_parameters,
		  LONG_INT * recent_number_acceptances,
		  LONG_INT * number_accepted,
		  LONG_INT * index_cost_acceptances,
		  LONG_INT * number_acceptances_saved,
		  LONG_INT * recent_number_generated,
		  LONG_INT * number_generated,
		  LONG_INT * index_parameter_generations,
		  STATE * current_generated_state,
		  STATE * last_saved_state,
#if ASA_SAMPLE
		  FILE * ptr_asa_out,
#endif
		  USER_DEFINES * OPTIONS)
#else
void
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
		  OPTIONS)
     double (*user_random_generator) ();
     LONG_INT *seed;
     double *parameter_minimum;
     double *parameter_maximum;
     double *current_cost_temperature;
#if ASA_SAMPLE
     double *current_user_parameter_temp;
#endif
     ALLOC_INT *number_parameters;
     LONG_INT *recent_number_acceptances;
     LONG_INT *number_accepted;
     LONG_INT *index_cost_acceptances;
     LONG_INT *number_acceptances_saved;
     LONG_INT *recent_number_generated;
     LONG_INT *number_generated;
     LONG_INT *index_parameter_generations;
     STATE *current_generated_state;
     STATE *last_saved_state;
#if ASA_SAMPLE
     FILE *ptr_asa_out;
#endif
     USER_DEFINES *OPTIONS;

#endif
{
#if USER_ACCEPTANCE_TEST
#else
  double delta_cost;
#endif
#if USER_ACCEPT_ASYMP_EXP
  double q;
#endif
  double prob_test, unif_test;
  double curr_cost_temp;
  ALLOC_INT index_v;
#if ASA_SAMPLE
  LONG_INT active_params;
  double weight_param_ind, weight_aver, range;
#endif

  /* update accepted and generated count */
  ++*number_acceptances_saved;
  ++*recent_number_generated;
  ++*number_generated;
  OPTIONS->N_Generated = *number_generated;

  /* increment the parameter index generation for each parameter */
  if (OPTIONS->Sequential_Parameters >= 0)
    {
      /* ignore parameters with too small a range */
      if (!PARAMETER_RANGE_TOO_SMALL (OPTIONS->Sequential_Parameters))
	++index_parameter_generations[OPTIONS->Sequential_Parameters];
    }
  else
    {
      VFOR (index_v)
      {
	if (!PARAMETER_RANGE_TOO_SMALL (index_v))
	  ++index_parameter_generations[index_v];
      }
    }

  /* effective cost function for testing acceptance criteria,
     calculate the cost difference and divide by the temperature */
  curr_cost_temp = *current_cost_temperature;
#if USER_ACCEPTANCE_TEST
  if (OPTIONS->Cost_Acceptance_Flag == TRUE)
    {
      if (OPTIONS->User_Acceptance_Flag == TRUE)
	{
	  unif_test = ZERO;
	  OPTIONS->User_Acceptance_Flag = FALSE;
	  OPTIONS->Cost_Acceptance_Flag = FALSE;
	}
      else
	{
	  unif_test = ONE;
	  OPTIONS->Cost_Acceptance_Flag = FALSE;
	}
    }
  else
    {
      OPTIONS->Acceptance_Test (current_generated_state->cost,
				*number_parameters,
				OPTIONS);
      if (OPTIONS->User_Acceptance_Flag == TRUE)
	{
	  unif_test = ZERO;
	  OPTIONS->User_Acceptance_Flag = FALSE;
	}
      else
	{
	  unif_test = ONE;
	}
    }
  prob_test = OPTIONS->Prob_Bias;
#else /* USER_ACCEPTANCE_TEST */
#if USER_COST_SCHEDULE
  curr_cost_temp =
    (OPTIONS->Cost_Schedule (*current_cost_temperature, OPTIONS)
     + (double) EPS_DOUBLE);
#endif
  delta_cost = (current_generated_state->cost - last_saved_state->cost)
    / (curr_cost_temp + (double) EPS_DOUBLE);

#if USER_ACCEPT_ASYMP_EXP
  q = OPTIONS->Asymp_Exp_Param;
  if (fabs (ONE - q) < (double) EPS_DOUBLE)
    prob_test = MIN (ONE, (F_EXP (EXPONENT_CHECK (-delta_cost))));
  else if ((ONE - (ONE - q) * delta_cost) < (double) EPS_DOUBLE)
    prob_test = MIN (ONE, (F_EXP (EXPONENT_CHECK (-delta_cost))));
  else
    prob_test = MIN (ONE, F_POW ((ONE - (ONE - q) * delta_cost),
				 (ONE / (ONE - q))));
#else /* USER_ACCEPT_ASYMP_EXP */
  prob_test = MIN (ONE, (F_EXP (EXPONENT_CHECK (-delta_cost))));
#endif /* USER_ACCEPT_ASYMP_EXP */

  unif_test = (*user_random_generator) (seed);
#endif /* USER_ACCEPTANCE_TEST */

#if ASA_SAMPLE
  active_params = 0;
  weight_aver = ZERO;
  VFOR (index_v)
  {
    /* ignore parameters with too small a range */
    if (PARAMETER_RANGE_TOO_SMALL (index_v))
      continue;
    ++active_params;
    range = parameter_maximum[index_v] - parameter_minimum[index_v];
    weight_param_ind = TWO
      * (fabs ((last_saved_state->parameter[index_v]
		- current_generated_state->parameter[index_v]) / range)
	 + current_user_parameter_temp[index_v])
      * F_LOG (ONE + ONE / current_user_parameter_temp[index_v]);
    weight_aver += weight_param_ind;
    OPTIONS->Bias_Generated[index_v] = ONE / weight_param_ind;
  }
  weight_aver /= (double) active_params;
  OPTIONS->Average_Weights = weight_aver;
  if (prob_test >= unif_test)
    {
      OPTIONS->Bias_Acceptance = prob_test;
    }
  else
    {
      OPTIONS->Bias_Acceptance = ONE - prob_test;
    }

#if ASA_PRINT
  if (OPTIONS->Limit_Weights < OPTIONS->Average_Weights)
    {
      fprintf (ptr_asa_out, ":SAMPLE#\n");
      if (prob_test >= unif_test)
	{
	  fprintf (ptr_asa_out,
#if INT_LONG
		   ":SAMPLE+ %10ld %*.*g %*.*g %*.*g %*.*g\n",
#else
		   ":SAMPLE+ %10d %*.*g %*.*g %*.*g\n",
#endif
		   OPTIONS->N_Accepted,
		   G_FIELD, G_PRECISION, current_generated_state->cost,
		   G_FIELD, G_PRECISION, *current_cost_temperature,
		   G_FIELD, G_PRECISION, OPTIONS->Bias_Acceptance,
		   G_FIELD, G_PRECISION, OPTIONS->Average_Weights);
	  VFOR (index_v)
	  {
	    /* ignore parameters with too small a range */
	    if (PARAMETER_RANGE_TOO_SMALL (index_v))
	      continue;
	    range = parameter_maximum[index_v] - parameter_minimum[index_v];
	    fprintf (ptr_asa_out,
#if INT_ALLOC
		     ":SAMPLE %11d %*.*g %*.*g %*.*g %*.*g\n",
#else
#if INT_LONG
		     ":SAMPLE %11ld %*.*g %*.*g %*.*g %*.*g\n",
#else
		     ":SAMPLE %11d %*.*g %*.*g %*.*g %*.*g\n",
#endif
#endif
		     index_v,
		     G_FIELD, G_PRECISION, current_generated_state->parameter[index_v],
		 G_FIELD, G_PRECISION, current_user_parameter_temp[index_v],
		     G_FIELD, G_PRECISION, OPTIONS->Bias_Generated[index_v],
		     G_FIELD, G_PRECISION, range);
	  }
	}
      else
	{
	  fprintf (ptr_asa_out,
#if INT_LONG
		   ":SAMPLE %11ld %*.*g %*.*g %*.*g %*.*g\n",
#else
		   ":SAMPLE %11d %*.*g %*.*g %*.*g\n",
#endif
		   OPTIONS->N_Accepted,
		   G_FIELD, G_PRECISION, last_saved_state->cost,
		   G_FIELD, G_PRECISION, *current_cost_temperature,
		   G_FIELD, G_PRECISION, OPTIONS->Bias_Acceptance,
		   G_FIELD, G_PRECISION, OPTIONS->Average_Weights);
	  VFOR (index_v)
	  {
	    /* ignore parameters with too small a range */
	    if (PARAMETER_RANGE_TOO_SMALL (index_v))
	      continue;
	    range = parameter_maximum[index_v] - parameter_minimum[index_v];
	    fprintf (ptr_asa_out,
#if INT_ALLOC
		     ":SAMPLE %11d %*.*g %*.*g %*.*g %*.*g\n",
#else
#if INT_LONG
		     ":SAMPLE %11ld %*.*g %*.*g %*.*g %*.*g\n",
#else
		     ":SAMPLE %11d %*.*g %*.*g %*.*g %*.*g\n",
#endif
#endif
		     index_v,
		 G_FIELD, G_PRECISION, last_saved_state->parameter[index_v],
		 G_FIELD, G_PRECISION, current_user_parameter_temp[index_v],
		     G_FIELD, G_PRECISION, OPTIONS->Bias_Generated[index_v],
		     G_FIELD, G_PRECISION, range);
	  }
	}
    }
#endif
#endif /* ASA_SAMPLE */

  /* accept/reject the new state */
  if (prob_test >= unif_test)
    {
      /* copy current state to the last saved state */

      last_saved_state->cost = current_generated_state->cost;
      VFOR (index_v)
      {
	/* ignore parameters with too small a range */
	if (PARAMETER_RANGE_TOO_SMALL (index_v))
	  continue;
	last_saved_state->parameter[index_v] =
	  current_generated_state->parameter[index_v];
      }

      /* update acceptance counts */
      ++*recent_number_acceptances;
      ++*number_accepted;
      ++*index_cost_acceptances;
      *number_acceptances_saved = *number_accepted;
      OPTIONS->N_Accepted = *number_accepted;
    }
}

/***********************************************************************
* reanneal
*	Readjust temperatures of generating and acceptance functions
***********************************************************************/
#if HAVE_ANSI
void
reanneal (double *parameter_minimum,
	  double *parameter_maximum,
	  double *tangents,
	  double *maximum_tangent,
	  double *current_cost_temperature,
	  double *initial_cost_temperature,
	  double *temperature_scale_cost,
	  double *current_user_parameter_temp,
	  double *initial_user_parameter_temp,
	  double *temperature_scale_parameters,
	  ALLOC_INT * number_parameters,
	  int *parameter_type,
	  LONG_INT * index_cost_acceptances,
	  LONG_INT * index_parameter_generations,
	  STATE * last_saved_state,
	  STATE * best_generated_state,
	  USER_DEFINES * OPTIONS)
#else
void
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
	  OPTIONS)
     double *parameter_minimum;
     double *parameter_maximum;
     double *tangents;
     double *maximum_tangent;
     double *current_cost_temperature;
     double *initial_cost_temperature;
     double *temperature_scale_cost;
     double *current_user_parameter_temp;
     double *initial_user_parameter_temp;
     double *temperature_scale_parameters;
     ALLOC_INT *number_parameters;
     int *parameter_type;
     LONG_INT *index_cost_acceptances;
     LONG_INT *index_parameter_generations;
     STATE *last_saved_state;
     STATE *best_generated_state;
     USER_DEFINES *OPTIONS;
#endif
{
  ALLOC_INT index_v;
  int cost_test;
  double tmp_var_db3;
  double new_temperature;
  double log_new_temperature_ratio;
  double log_init_cur_temp_ratio;
  double temperature_rescale_power;
  double cost_best, cost_last;
  double tmp_dbl, tmp_dbl1;

  if (OPTIONS->Reanneal_Parameters == TRUE)
    {
      VFOR (index_v)
      {
	if (NO_REANNEAL (index_v))
	  continue;

	/* use the temp double to prevent overflow */
	tmp_dbl = (double) index_parameter_generations[index_v];

	/* skip parameters with too small range or integer parameters */
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

	/* ignore parameters with too small tangents */
	if (fabs (tangents[index_v]) < (double) EPS_DOUBLE)
	  continue;

	/* reset the index of parameter generations appropriately */
#if USER_REANNEAL_PARAMETERS
	new_temperature =
	  fabs (OPTIONS->Reanneal_Params_Function (
				       current_user_parameter_temp[index_v],
						    tangents[index_v],
						    *maximum_tangent,
						    OPTIONS));
#else
	new_temperature =
	  fabs (FUNCTION_REANNEAL_PARAMS (current_user_parameter_temp[index_v],
					  tangents[index_v],
					  *maximum_tangent));
#endif
	if (new_temperature < initial_user_parameter_temp[index_v])
	  {
	    log_init_cur_temp_ratio =
	      fabs (F_LOG (((double) EPS_DOUBLE
			    + initial_user_parameter_temp[index_v])
			   / ((double) EPS_DOUBLE + new_temperature)));
	    tmp_dbl = (double) EPS_DOUBLE
	      + F_POW (log_init_cur_temp_ratio
		       / temperature_scale_parameters[index_v],
		       (double) *number_parameters
#if QUENCH_PARAMETERS
		       / OPTIONS->User_Quench_Param_Scale[index_v]);
#else
	      );
#endif
	  }
	else
	  {
	    tmp_dbl = ONE;
	  }

	/* Reset index_parameter_generations if index reset too large,
	   and also reset the initial_user_parameter_temp, to achieve
	   the same new temperature. */
	while (tmp_dbl
	       > ((double) MAXIMUM_REANNEAL_INDEX))
	  {
	    log_new_temperature_ratio =
	      -temperature_scale_parameters[index_v] *
	      F_POW (tmp_dbl,
#if QUENCH_PARAMETERS
		     OPTIONS->User_Quench_Param_Scale[index_v]
#else
		     ONE
#endif
		     / (double) *number_parameters);
	    log_new_temperature_ratio =
	      EXPONENT_CHECK (log_new_temperature_ratio);
	    new_temperature =
	      initial_user_parameter_temp[index_v]
	      * F_EXP (log_new_temperature_ratio);
	    tmp_dbl /= (double) REANNEAL_SCALE;
	    temperature_rescale_power = ONE
	      / F_POW ((double) REANNEAL_SCALE,
#if QUENCH_PARAMETERS
		       OPTIONS->User_Quench_Param_Scale[index_v]
#else
		       ONE
#endif
		       / (double) *number_parameters);
	    initial_user_parameter_temp[index_v] = new_temperature
	      * F_POW (initial_user_parameter_temp[index_v] / new_temperature,
		       temperature_rescale_power);
	  }
	/* restore from temporary double */
	index_parameter_generations[index_v] = (LONG_INT) tmp_dbl;
      }
    }

  if (OPTIONS->Reanneal_Cost == 0)
    {
      ;
    }
  else if (OPTIONS->Reanneal_Cost < -1)
    {
      *index_cost_acceptances = 1;
    }
  else
    {
      /* reanneal : Reset the current cost temp and rescale the
         index of cost acceptances. */

      cost_best = best_generated_state->cost;
      cost_last = last_saved_state->cost;
#if USER_REANNEAL_COST
      cost_test = OPTIONS->Reanneal_Cost_Function (&cost_best,
						   &cost_last,
						   initial_cost_temperature,
						   current_cost_temperature,
						   OPTIONS);
      tmp_dbl1 = *current_cost_temperature;
#else
      cost_test = TRUE;
      if (OPTIONS->Reanneal_Cost == 1)
	{
	  /* (re)set the initial cost_temperature */
	  tmp_dbl = MAX (fabs (cost_last), fabs (cost_best));
	  tmp_dbl = MAX (tmp_dbl, fabs (cost_best - cost_last));
	  tmp_dbl = MAX ((double) EPS_DOUBLE, tmp_dbl);
	  *initial_cost_temperature = MIN (*initial_cost_temperature, tmp_dbl);
	}

      tmp_dbl = (double) *index_cost_acceptances;

      tmp_dbl1 = MAX (fabs (cost_last - cost_best), *current_cost_temperature);
      tmp_dbl1 = MAX ((double) EPS_DOUBLE, tmp_dbl1);
      tmp_dbl1 = MIN (tmp_dbl1, *initial_cost_temperature);
#endif /* USER_REANNEAL_COST */
      if (cost_test == TRUE && (*current_cost_temperature > tmp_dbl1))
	{
	  tmp_var_db3 =
	    fabs (F_LOG (((double) EPS_DOUBLE + *initial_cost_temperature) /
			 (tmp_dbl1)));
	  tmp_dbl = (double) EPS_DOUBLE + F_POW (tmp_var_db3
		      / *temperature_scale_cost, (double) *number_parameters
#if QUENCH_COST
				      / OPTIONS->User_Quench_Cost_Scale[0]);
#else
	    );
#endif
	}
      else
	{
	  log_init_cur_temp_ratio =
	    fabs (F_LOG (((double) EPS_DOUBLE + *initial_cost_temperature) /
			 ((double) EPS_DOUBLE + *current_cost_temperature)));
	  tmp_dbl = (double) EPS_DOUBLE
	    + F_POW (log_init_cur_temp_ratio
		     / *temperature_scale_cost, (double) *number_parameters
#if QUENCH_COST
		     / OPTIONS->User_Quench_Cost_Scale[0]
#else
#endif
	    );
	}

      /* reset index_cost_temperature if index reset too large */
      while (tmp_dbl > ((double) MAXIMUM_REANNEAL_INDEX))
	{
	  log_new_temperature_ratio = -*temperature_scale_cost *
	    F_POW (tmp_dbl,
#if QUENCH_COST
		   OPTIONS->User_Quench_Cost_Scale[0]
#else
		   ONE
#endif
		   / (double) *number_parameters);
	  log_new_temperature_ratio =
	    EXPONENT_CHECK (log_new_temperature_ratio);
	  new_temperature = *initial_cost_temperature
	    * F_EXP (log_new_temperature_ratio);
	  tmp_dbl /= (double) REANNEAL_SCALE;
	  temperature_rescale_power = ONE / F_POW ((double) REANNEAL_SCALE,
#if QUENCH_COST
					  OPTIONS->User_Quench_Cost_Scale[0]
#else
						   ONE
#endif
					     / (double) *number_parameters);
	  *initial_cost_temperature = new_temperature * F_POW
	    (*initial_cost_temperature / new_temperature,
	     temperature_rescale_power);
	}
      *index_cost_acceptances = (LONG_INT) tmp_dbl;
#if USER_ACCEPTANCE_TEST
      OPTIONS->Cost_Temp_Init = *initial_cost_temperature;
#endif
    }
}



/***********************************************************************
* test_asa_options
*       Tests user's selected options
***********************************************************************/
#if HAVE_ANSI
int
test_asa_options (LONG_INT * seed,
		  double *parameter_initial_final,
		  double *parameter_minimum,
		  double *parameter_maximum,
		  double *tangents,
		  double *curvature,
		  ALLOC_INT * number_parameters,
		  int *parameter_type,
		  int *valid_state_generated_flag,
		  int *exit_status,
		  FILE * ptr_asa_out,
		  USER_DEFINES * OPTIONS)
#else
int
test_asa_options (seed,
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
		  OPTIONS)
     LONG_INT *seed;
     double *parameter_initial_final;
     double *parameter_minimum;
     double *parameter_maximum;
     double *tangents;
     double *curvature;
     ALLOC_INT *number_parameters;
     int *parameter_type;
     int *valid_state_generated_flag;
     int *exit_status;
     FILE *ptr_asa_out;
     USER_DEFINES *OPTIONS;
#endif /* HAVE_ANSI */
{
  int invalid, index_v;

  invalid = 0;

  if (seed == NULL)
    {
      print_string (ptr_asa_out, "*** seed == NULL ***");
      ++invalid;
    }
  if (parameter_initial_final == NULL)
    {
      print_string (ptr_asa_out, "*** parameter_initial_final == NULL ***");
      ++invalid;
    }
  if (parameter_minimum == NULL)
    {
      print_string (ptr_asa_out, "*** parameter_minimum == NULL ***");
      ++invalid;
    }
  if (parameter_maximum == NULL)
    {
      print_string (ptr_asa_out, "*** parameter_maximum == NULL ***");
      ++invalid;
    }
  if (tangents == NULL)
    {
      print_string (ptr_asa_out, "*** tangents == NULL ***");
      ++invalid;
    }
  if (OPTIONS->Curvature_0 == FALSE || OPTIONS->Curvature_0 == -1)
    {
      if (curvature == NULL)
	{
	  print_string (ptr_asa_out, "*** curvature == NULL ***");
	  ++invalid;
	}
    }
  if (number_parameters == NULL)
    {
      print_string (ptr_asa_out, "*** number_parameters == NULL ***");
      ++invalid;
    }
  if (parameter_type == NULL)
    {
      print_string (ptr_asa_out, "*** parameter_type == NULL ***");
      ++invalid;
    }
  if (valid_state_generated_flag == NULL)
    {
      print_string (ptr_asa_out, "*** valid_state_generated_flag == NULL ***");
      ++invalid;
    }
  if (exit_status == NULL)
    {
      print_string (ptr_asa_out, "*** exit_status == NULL ***");
      ++invalid;
    }
  if (OPTIONS == NULL)
    {
      print_string (ptr_asa_out, "*** OPTIONS == NULL ***");
      ++invalid;
    }

  VFOR (index_v)
    if (parameter_minimum[index_v] > parameter_maximum[index_v])
    {
      print_string_index (ptr_asa_out, "*** parameter_minimum[] > parameter_maximum[] ***", index_v);
      ++invalid;
    }
  VFOR (index_v)
    if (parameter_initial_final[index_v] < parameter_minimum[index_v])
    {
      print_string_index (ptr_asa_out, "*** parameter_initial[] < parameter_minimum[] ***", index_v);
      ++invalid;
    }
  VFOR (index_v)
    if (parameter_initial_final[index_v] > parameter_maximum[index_v])
    {
      print_string_index (ptr_asa_out, "*** parameter_initial[] > parameter_maximum[] ***", index_v);
      ++invalid;
    }
  if (*number_parameters < 1)
    {
      print_string (ptr_asa_out, "*** *number_parameters < 1 ***");
      ++invalid;
    }
  VFOR (index_v)
    if (parameter_type[index_v] != -2 && parameter_type[index_v] != 2 && parameter_type[index_v] != -1 && parameter_type[index_v] != 1)
    {
      print_string_index (ptr_asa_out, "*** parameter_type[] != -2 && parameter_type[] != 2 && parameter_type[] != -1 && parameter_type[] != 1 ***", index_v);
      ++invalid;
    }

  if (OPTIONS_FILE != FALSE && OPTIONS_FILE != TRUE)
    {
      print_string (ptr_asa_out, "*** OPTIONS_FILE != FALSE && OPTIONS_FILE != TRUE ***");
      ++invalid;
    }
  if (OPTIONS_FILE_DATA != FALSE && OPTIONS_FILE_DATA != TRUE)
    {
      print_string (ptr_asa_out, "*** OPTIONS_FILE_DATA != FALSE && OPTIONS_FILE_DATA != TRUE ***");
      ++invalid;
    }
  if (RECUR_OPTIONS_FILE != FALSE && RECUR_OPTIONS_FILE != TRUE)
    {
      print_string (ptr_asa_out, "*** RECUR_OPTIONS_FILE != FALSE && RECUR_OPTIONS_FILE != TRUE ***");
      ++invalid;
    }
  if (RECUR_OPTIONS_FILE_DATA != FALSE && RECUR_OPTIONS_FILE_DATA != TRUE)
    {
      print_string (ptr_asa_out, "*** RECUR_OPTIONS_FILE_DATA != FALSE && RECUR_OPTIONS_FILE_DATA != TRUE ***");
      ++invalid;
    }
  if (COST_FILE != FALSE && COST_FILE != TRUE)
    {
      print_string (ptr_asa_out, "*** COST_FILE != FALSE && COST_FILE != TRUE ***");
      ++invalid;
    }
  if (ASA_LIB != FALSE && ASA_LIB != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_LIB != FALSE && ASA_LIB != TRUE ***");
      ++invalid;
    }
  if (MY_TEMPLATE != FALSE && MY_TEMPLATE != TRUE)
    {
      print_string (ptr_asa_out, "*** MY_TEMPLATE != FALSE && MY_TEMPLATE != TRUE ***");
      ++invalid;
    }
  if (ASA_TEMPLATE_LIB != FALSE && ASA_TEMPLATE_LIB != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_TEMPLATE_LIB != FALSE && ASA_TEMPLATE_LIB != TRUE ***");
      ++invalid;
    }
  if (HAVE_ANSI != FALSE && HAVE_ANSI != TRUE)
    {
      print_string (ptr_asa_out, "*** HAVE_ANSI != FALSE && HAVE_ANSI != TRUE ***");
      ++invalid;
    }
  if (IO_PROTOTYPES != FALSE && IO_PROTOTYPES != TRUE)
    {
      print_string (ptr_asa_out, "*** IO_PROTOTYPES != FALSE && IO_PROTOTYPES != TRUE ***");
      ++invalid;
    }
  if (TIME_CALC != FALSE && TIME_CALC != TRUE)
    {
      print_string (ptr_asa_out, "*** TIME_CALC != FALSE && TIME_CALC != TRUE ***");
      ++invalid;
    }
  if (TIME_STD != FALSE && TIME_STD != TRUE)
    {
      print_string (ptr_asa_out, "*** TIME_STD != FALSE && TIME_STD != TRUE ***");
      ++invalid;
    }
  if (TIME_GETRUSAGE != FALSE && TIME_GETRUSAGE != TRUE)
    {
      print_string (ptr_asa_out, "*** TIME_GETRUSAGE != FALSE && TIME_GETRUSAGE != TRUE ***");
      ++invalid;
    }
  if (INT_LONG != FALSE && INT_LONG != TRUE)
    {
      print_string (ptr_asa_out, "*** INT_LONG != FALSE && INT_LONG != TRUE ***");
      ++invalid;
    }
  if (INT_ALLOC != FALSE && INT_ALLOC != TRUE)
    {
      print_string (ptr_asa_out, "*** INT_ALLOC != FALSE && INT_ALLOC != TRUE ***");
      ++invalid;
    }
  if (SMALL_FLOAT < ZERO)
    {
      print_string (ptr_asa_out, "*** SMALL_FLOAT < ZERO ***");
      ++invalid;
    }
  if (MIN_DOUBLE < ZERO)
    {
      print_string (ptr_asa_out, "*** MIN_DOUBLE < ZERO ***");
      ++invalid;
    }
  if (MAX_DOUBLE < ZERO)
    {
      print_string (ptr_asa_out, "*** MAX_DOUBLE < ZERO ***");
      ++invalid;
    }
  if (EPS_DOUBLE < ZERO)
    {
      print_string (ptr_asa_out, "*** EPS_DOUBLE < ZERO ***");
      ++invalid;
    }
  if (CHECK_EXPONENT != FALSE && CHECK_EXPONENT != TRUE)
    {
      print_string (ptr_asa_out, "*** CHECK_EXPONENT != FALSE && CHECK_EXPONENT != TRUE ***");
      ++invalid;
    }
  if (NO_PARAM_TEMP_TEST != FALSE && NO_PARAM_TEMP_TEST != TRUE)
    {
      print_string (ptr_asa_out, "*** NO_PARAM_TEMP_TEST != FALSE && NO_PARAM_TEMP_TEST != TRUE ***");
      ++invalid;
    }
  if (NO_COST_TEMP_TEST != FALSE && NO_COST_TEMP_TEST != TRUE)
    {
      print_string (ptr_asa_out, "*** NO_COST_TEMP_TEST != FALSE && NO_COST_TEMP_TEST != TRUE ***");
      ++invalid;
    }
  if (SELF_OPTIMIZE != FALSE && SELF_OPTIMIZE != TRUE)
    {
      print_string (ptr_asa_out, "*** SELF_OPTIMIZE != FALSE && SELF_OPTIMIZE != TRUE ***");
      ++invalid;
    }
  if (ASA_TEST != FALSE && ASA_TEST != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_TEST != FALSE && ASA_TEST != TRUE ***");
      ++invalid;
    }
  if (ASA_TEST_POINT != FALSE && ASA_TEST_POINT != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_TEST_POINT != FALSE && ASA_TEST_POINT != TRUE ***");
      ++invalid;
    }
  if (ASA_TEMPLATE != FALSE)
    {
      print_string (ptr_asa_out, "*** ASA_TEMPLATE != FALSE ***");
      ++invalid;
    }
  if (ASA_TEMPLATE_ASA_OUT_PID != FALSE && ASA_TEMPLATE_ASA_OUT_PID != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_TEMPLATE_ASA_OUT_PID != FALSE && ASA_TEMPLATE_ASA_OUT_PID != TRUE ***");
      ++invalid;
    }
  if (ASA_TEMPLATE_MULTIPLE != FALSE && ASA_TEMPLATE_MULTIPLE != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_TEMPLATE_MULTIPLE != FALSE && ASA_TEMPLATE_MULTIPLE != TRUE ***");
      ++invalid;
    }
  if (ASA_TEMPLATE_SELFOPT != FALSE && ASA_TEMPLATE_SELFOPT != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_TEMPLATE_SELFOPT != FALSE && ASA_TEMPLATE_SELFOPT != TRUE ***");
      ++invalid;
    }
  if (ASA_TEMPLATE_SAMPLE != FALSE && ASA_TEMPLATE_SAMPLE != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_TEMPLATE_SAMPLE != FALSE && ASA_TEMPLATE_SAMPLE != TRUE ***");
      ++invalid;
    }
  if (ASA_TEMPLATE_QUEUE != FALSE && ASA_TEMPLATE_QUEUE != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_TEMPLATE_QUEUE != FALSE && ASA_TEMPLATE_QUEUE != TRUE ***");
      ++invalid;
    }
  if (ASA_TEMPLATE_PARALLEL != FALSE && ASA_TEMPLATE_PARALLEL != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_TEMPLATE_PARALLEL != FALSE && ASA_TEMPLATE_PARALLEL != TRUE ***");
      ++invalid;
    }
  if (ASA_TEMPLATE_SAVE != FALSE && ASA_TEMPLATE_SAVE != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_TEMPLATE_SAVE != FALSE && ASA_TEMPLATE_SAVE != TRUE ***");
      ++invalid;
    }
  if (USER_INITIAL_COST_TEMP != FALSE && USER_INITIAL_COST_TEMP != TRUE)
    {
      print_string (ptr_asa_out, "*** USER_INITIAL_COST_TEMP != FALSE && USER_INITIAL_COST_TEMP != TRUE ***");
      ++invalid;
    }
  if (RATIO_TEMPERATURE_SCALES != FALSE && RATIO_TEMPERATURE_SCALES != TRUE)
    {
      print_string (ptr_asa_out, "*** RATIO_TEMPERATURE_SCALES != FALSE && RATIO_TEMPERATURE_SCALES != TRUE ***");
      ++invalid;
    }
  if (USER_INITIAL_PARAMETERS_TEMPS != FALSE && USER_INITIAL_PARAMETERS_TEMPS != TRUE)
    {
      print_string (ptr_asa_out, "*** USER_INITIAL_PARAMETERS_TEMPS != FALSE && USER_INITIAL_PARAMETERS_TEMPS != TRUE ***");
      ++invalid;
    }
  if (DELTA_PARAMETERS != FALSE && DELTA_PARAMETERS != TRUE)
    {
      print_string (ptr_asa_out, "*** DELTA_PARAMETERS != FALSE && DELTA_PARAMETERS != TRUE ***");
      ++invalid;
    }
  if (QUENCH_PARAMETERS != FALSE && QUENCH_PARAMETERS != TRUE)
    {
      print_string (ptr_asa_out, "*** QUENCH_PARAMETERS != FALSE && QUENCH_PARAMETERS != TRUE ***");
      ++invalid;
    }
  if (QUENCH_COST != FALSE && QUENCH_COST != TRUE)
    {
      print_string (ptr_asa_out, "*** QUENCH_COST != FALSE && QUENCH_COST != TRUE ***");
      ++invalid;
    }
  if (QUENCH_PARAMETERS_SCALE != FALSE && QUENCH_PARAMETERS_SCALE != TRUE)
    {
      print_string (ptr_asa_out, "*** QUENCH_PARAMETERS_SCALE != FALSE && QUENCH_PARAMETERS_SCALE != TRUE ***");
      ++invalid;
    }
  if (QUENCH_COST_SCALE != FALSE && QUENCH_COST_SCALE != TRUE)
    {
      print_string (ptr_asa_out, "*** QUENCH_COST_SCALE != FALSE && QUENCH_COST_SCALE != TRUE ***");
      ++invalid;
    }
  if (OPTIONAL_DATA != FALSE && OPTIONAL_DATA != TRUE)
    {
      print_string (ptr_asa_out, "*** OPTIONAL_DATA != FALSE && OPTIONAL_DATA != TRUE ***");
      ++invalid;
    }
  if (OPTIONAL_DATA_INT != FALSE && OPTIONAL_DATA_INT != TRUE)
    {
      print_string (ptr_asa_out, "*** OPTIONAL_DATA_INT != FALSE && OPTIONAL_DATA_INT != TRUE ***");
      ++invalid;
    }
  if (USER_COST_SCHEDULE != FALSE && USER_COST_SCHEDULE != TRUE)
    {
      print_string (ptr_asa_out, "*** USER_COST_SCHEDULE != FALSE && USER_COST_SCHEDULE != TRUE ***");
      ++invalid;
    }
  if (USER_ACCEPT_ASYMP_EXP != FALSE && USER_ACCEPT_ASYMP_EXP != TRUE)
    {
      print_string (ptr_asa_out, "*** USER_ACCEPT_ASYMP_EXP != FALSE && USER_ACCEPT_ASYMP_EXP != TRUE ***");
      ++invalid;
    }
  if (USER_ACCEPTANCE_TEST != FALSE && USER_ACCEPTANCE_TEST != TRUE)
    {
      print_string (ptr_asa_out, "*** USER_ACCEPTANCE_TEST != FALSE && USER_ACCEPTANCE_TEST != TRUE ***");
      ++invalid;
    }
  if (USER_GENERATING_FUNCTION != FALSE && USER_GENERATING_FUNCTION != TRUE)
    {
      print_string (ptr_asa_out, "*** USER_GENERATING_FUNCTION != FALSE && USER_GENERATING_FUNCTION != TRUE ***");
      ++invalid;
    }
  if (USER_REANNEAL_COST != FALSE && USER_REANNEAL_COST != TRUE)
    {
      print_string (ptr_asa_out, "*** USER_REANNEAL_COST != FALSE && USER_REANNEAL_COST != TRUE ***");
      ++invalid;
    }
  if (USER_REANNEAL_PARAMETERS != FALSE && USER_REANNEAL_PARAMETERS != TRUE)
    {
      print_string (ptr_asa_out, "*** USER_REANNEAL_PARAMETERS != FALSE && USER_REANNEAL_PARAMETERS != TRUE ***");
      ++invalid;
    }
  if (MAXIMUM_REANNEAL_INDEX < 1)
    {
      print_string (ptr_asa_out, "*** MAXIMUM_REANNEAL_INDEX < 1 ***");
      ++invalid;
    }
  if (REANNEAL_SCALE < ZERO)
    {
      print_string (ptr_asa_out, "*** REANNEAL_SCALE < ZERO ***");
      ++invalid;
    }
  if (ASA_SAMPLE != FALSE && ASA_SAMPLE != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_SAMPLE != FALSE && ASA_SAMPLE != TRUE ***");
      ++invalid;
    }
  if (ASA_QUEUE != FALSE && ASA_QUEUE != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_QUEUE != FALSE && ASA_QUEUE != TRUE ***");
      ++invalid;
    }
  if (ASA_RESOLUTION != FALSE && ASA_RESOLUTION != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_RESOLUTION != FALSE && ASA_RESOLUTION != TRUE ***");
      ++invalid;
    }
  if (FITLOC != FALSE && FITLOC != TRUE)
    {
      print_string (ptr_asa_out, "*** FITLOC != FALSE && FITLOC != TRUE ***");
      ++invalid;
    }
  if (FITLOC_ROUND != FALSE && FITLOC_ROUND != TRUE)
    {
      print_string (ptr_asa_out, "*** FITLOC_ROUND != FALSE && FITLOC_ROUND != TRUE ***");
      ++invalid;
    }
  if (ASA_PARALLEL != FALSE && ASA_PARALLEL != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_PARALLEL != FALSE && ASA_PARALLEL != TRUE ***");
      ++invalid;
    }
  if (ASA_SAVE != FALSE && ASA_SAVE != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_SAVE != FALSE && ASA_SAVE != TRUE ***");
      ++invalid;
    }
  if (SYSTEM_CALL != FALSE && SYSTEM_CALL != TRUE)
    {
      print_string (ptr_asa_out, "*** SYSTEM_CALL != FALSE && SYSTEM_CALL != TRUE ***");
      ++invalid;
    }
  if (FDLIBM_POW != FALSE && FDLIBM_POW != TRUE)
    {
      print_string (ptr_asa_out, "*** FDLIBM_POW != FALSE && FDLIBM_POW != TRUE ***");
      ++invalid;
    }
  if (FDLIBM_LOG != FALSE && FDLIBM_LOG != TRUE)
    {
      print_string (ptr_asa_out, "*** FDLIBM_LOG != FALSE && FDLIBM_LOG != TRUE ***");
      ++invalid;
    }
  if (FDLIBM_EXP != FALSE && FDLIBM_EXP != TRUE)
    {
      print_string (ptr_asa_out, "*** FDLIBM_EXP != FALSE && FDLIBM_EXP != TRUE ***");
      ++invalid;
    }
  if (ASA_PRINT != FALSE && ASA_PRINT != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_PRINT != FALSE && ASA_PRINT != TRUE ***");
      ++invalid;
    }
  if (USER_ASA_OUT != FALSE && USER_ASA_OUT != TRUE)
    {
      print_string (ptr_asa_out, "*** USER_ASA_OUT != FALSE && USER_ASA_OUT != TRUE ***");
      ++invalid;
    }
  if (ASA_PRINT_INTERMED != FALSE && ASA_PRINT_INTERMED != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_PRINT_INTERMED != FALSE && ASA_PRINT_INTERMED != TRUE ***");
      ++invalid;
    }
  if (ASA_PRINT_MORE != FALSE && ASA_PRINT_MORE != TRUE)
    {
      print_string (ptr_asa_out, "*** ASA_PRINT_MORE != FALSE && ASA_PRINT_MORE != TRUE ***");
      ++invalid;
    }
  if (G_FIELD < 0)
    {
      print_string (ptr_asa_out, "*** G_FIELD < 0 ***");
      ++invalid;
    }
  if (G_PRECISION < 0)
    {
      print_string (ptr_asa_out, "*** G_PRECISION < 0 ***");
      ++invalid;
    }

  if (OPTIONS->Limit_Acceptances < 0)
    {
      print_string (ptr_asa_out, "*** Limit_Acceptances < 0 ***");
      ++invalid;
    }
  if (OPTIONS->Limit_Generated < 0)
    {
      print_string (ptr_asa_out, "*** Limit_Generated < 0 ***");
      ++invalid;
    }
  if (OPTIONS->Limit_Invalid_Generated_States < 0)
    {
      print_string (ptr_asa_out, "*** Limit_Invalid_Generated_States < 0 ***");
      ++invalid;
    }
  if (OPTIONS->Accepted_To_Generated_Ratio <= ZERO)
    {
      print_string (ptr_asa_out, "*** Accepted_To_Generated_Ratio <= ZERO ***");
      ++invalid;
    }
  if (OPTIONS->Cost_Precision <= ZERO)
    {
      print_string (ptr_asa_out, "*** Cost_Precision <= ZERO ***");
      ++invalid;
    }
  if (OPTIONS->Maximum_Cost_Repeat < 0)
    {
      print_string (ptr_asa_out, "*** Maximum_Cost_Repeat < 0 ***");
      ++invalid;
    }
  if (OPTIONS->Number_Cost_Samples == 0 || OPTIONS->Number_Cost_Samples == -1)
    {
      print_string (ptr_asa_out, "*** Number_Cost_Samples == 0 || Number_Cost_Samples == -1 ***");
      ++invalid;
    }
  if (OPTIONS->Temperature_Ratio_Scale <= ZERO)
    {
      print_string (ptr_asa_out, "*** Temperature_Ratio_Scale <= ZERO ***");
      ++invalid;
    }
  if (OPTIONS->Cost_Parameter_Scale_Ratio <= ZERO)
    {
      print_string (ptr_asa_out, "*** Cost_Parameter_Scale_Ratio <= ZERO ***");
      ++invalid;
    }
  if (OPTIONS->Temperature_Anneal_Scale <= ZERO)
    {
      print_string (ptr_asa_out, "*** Temperature_Anneal_Scale <= ZERO ***");
      ++invalid;
    }
#if USER_INITIAL_COST_TEMP
  if (OPTIONS->User_Cost_Temperature[0] <= ZERO)
    {
      print_string (ptr_asa_out, "*** User_Cost_Temperature[0] <= ZERO ***");
      ++invalid;
    }
#endif
  if (OPTIONS->Include_Integer_Parameters != FALSE && OPTIONS->Include_Integer_Parameters != TRUE)
    {
      print_string (ptr_asa_out, "");
      ++invalid;
    }
  if (OPTIONS->User_Initial_Parameters != FALSE && OPTIONS->User_Initial_Parameters != TRUE)
    {
      print_string (ptr_asa_out, "*** User_Initial_Parameters != FALSE && User_Initial_Parameters != TRUE ***");
      ++invalid;
    }
  if (OPTIONS->Sequential_Parameters >= *number_parameters)
    {
      print_string (ptr_asa_out, "*** Sequential_Parameters >= *number_parameters ***");
      ++invalid;
    }
  if (OPTIONS->Initial_Parameter_Temperature <= ZERO)
    {
      print_string (ptr_asa_out, "*** Initial_Parameter_Temperature <= ZERO ***");
      ++invalid;
    }
#if RATIO_TEMPERATURE_SCALES
  VFOR (index_v)
    if (OPTIONS->User_Temperature_Ratio[index_v] <= ZERO)
    {
      print_string_index (ptr_asa_out, "*** User_Temperature_Ratio[] <= ZERO ***", index_v);
      ++invalid;
    }
#endif
#if USER_INITIAL_PARAMETERS_TEMPS
  VFOR (index_v)
    if (OPTIONS->User_Parameter_Temperature[index_v] <= ZERO)
    {
      print_string_index (ptr_asa_out, "*** User_Parameter_Temperature[] <= ZERO ***", index_v);
      ++invalid;
    }
#endif
  if (OPTIONS->Acceptance_Frequency_Modulus < 0)
    {
      print_string (ptr_asa_out, "*** Acceptance_Frequency_Modulus < 0 ***");
      ++invalid;
    }
  if (OPTIONS->Generated_Frequency_Modulus < 0)
    {
      print_string (ptr_asa_out, "*** Generated_Frequency_Modulus < 0 ***");
      ++invalid;
    }
  if (OPTIONS->Reanneal_Cost == -1)
    {
      print_string (ptr_asa_out, "*** Reanneal_Cost == -1 ***");
      ++invalid;
    }
  if (OPTIONS->Reanneal_Parameters != FALSE && OPTIONS->Reanneal_Parameters != TRUE)
    {
      print_string (ptr_asa_out, "*** Reanneal_Parameters != FALSE && Reanneal_Parameters != TRUE ***");
      ++invalid;
    }
  if (OPTIONS->Delta_X <= ZERO)
    {
      print_string (ptr_asa_out, "*** Delta_X <= ZERO ***");
      ++invalid;
    }
#if DELTA_PARAMETERS
  VFOR (index_v)
    if (OPTIONS->User_Delta_Parameter[index_v] <= ZERO)
    {
      print_string_index (ptr_asa_out, "*** User_Delta_Parameter[] <= ZERO ***", index_v);
      ++invalid;
    }
#endif
  if (OPTIONS->User_Tangents != FALSE && OPTIONS->User_Tangents != TRUE)
    {
      print_string (ptr_asa_out, "*** User_Tangents != FALSE && User_Tangents != TRUE ***");
      ++invalid;
    }
  if (OPTIONS->Curvature_0 != -1 && OPTIONS->Curvature_0 != FALSE && OPTIONS->Curvature_0 != TRUE)
    {
      print_string (ptr_asa_out, "*** Curvature_0 -1 && Curvature_0 != FALSE && Curvature_0 != TRUE ***");
      ++invalid;
    }
#if QUENCH_PARAMETERS
  VFOR (index_v)
    if (OPTIONS->User_Quench_Param_Scale[index_v] <= ZERO)
    {
      print_string_index (ptr_asa_out, "*** User_Quench_Param_Scale[] <= ZERO ***", index_v);
      ++invalid;
    }
#endif
#if QUENCH_COST
  if (OPTIONS->User_Quench_Cost_Scale[0] <= ZERO)
    {
      print_string (ptr_asa_out, "*** User_Quench_Cost_Scale[0] <= ZERO ***");
      ++invalid;
    }
#endif
#if OPTIONAL_DATA
  if (OPTIONS->Asa_Data_Dim < 1)
    {
      print_string (ptr_asa_out, "*** Asa_Data_Dim < 1 ***");
      ++invalid;
    }
  if (OPTIONS->Asa_Data == NULL)
    {
      print_string (ptr_asa_out, "*** Asa_Data == NULL ***");
      ++invalid;
    }
#endif
#if OPTIONAL_DATA_INT
  if (OPTIONS->Asa_Data_Dim_Int < 1)
    {
      print_string (ptr_asa_out, "*** Asa_Data_Dim_Int < 1 ***");
      ++invalid;
    }
  if (OPTIONS->Asa_Data_Int == NULL)
    {
      print_string (ptr_asa_out, "*** Asa_Data_Int == NULL ***");
      ++invalid;
    }
#endif
#if USER_ASA_OUT
  if (OPTIONS->Asa_Out_File == NULL)
    {
      print_string (ptr_asa_out, "*** Asa_Out_File == NULL ***");
      ++invalid;
    }
#endif
#if USER_COST_SCHEDULE
  if (OPTIONS->Cost_Schedule == NULL)
    {
      print_string (ptr_asa_out, "*** Cost_Schedule == NULL ***");
      ++invalid;
    }
#endif
#if USER_ACCEPTANCE_TEST
  if (OPTIONS->Acceptance_Test == NULL)
    {
      print_string (ptr_asa_out, "*** Acceptance_Test == NULL ***");
      ++invalid;
    }
  if (OPTIONS->User_Acceptance_Flag != FALSE && OPTIONS->User_Acceptance_Flag != TRUE)
    {
      print_string (ptr_asa_out, "*** User_Acceptance_Flag != FALSE && User_Acceptance_Flag != TRUE ***");
      ++invalid;
    }
  if (OPTIONS->Cost_Acceptance_Flag != FALSE && OPTIONS->Cost_Acceptance_Flag != TRUE)
    {
      print_string (ptr_asa_out, "*** Cost_Acceptance_Flag != FALSE && Cost_Acceptance_Flag != TRUE ***");
      ++invalid;
    }
#endif
#if USER_GENERATING_FUNCTION
  if (OPTIONS->Generating_Distrib == NULL)
    {
      print_string (ptr_asa_out, "*** Generating_Distrib == NULL ***");
      ++invalid;
    }
#endif
#if USER_REANNEAL_COST
  if (OPTIONS->Reanneal_Cost_Function == NULL)
    {
      print_string (ptr_asa_out, "*** Reanneal_Cost_Function == NULL ***");
      ++invalid;
    }
#endif
#if USER_REANNEAL_PARAMETERS
  if (OPTIONS->Reanneal_Params_Function == NULL)
    {
      print_string (ptr_asa_out, "*** Reanneal_Params_Function == NULL ***");
      ++invalid;
    }
#endif
#if ASA_SAMPLE
  if (OPTIONS->Bias_Generated == NULL)
    {
      print_string (ptr_asa_out, "*** Bias_Generated == NULL ***");
      ++invalid;
    }
  if (OPTIONS->Limit_Weights < ZERO)
    {
      print_string (ptr_asa_out, "*** Limit_Weights < ZERO ***");
      ++invalid;
    }
#endif
#if ASA_QUEUE
  if (OPTIONS->Queue_Size < 0)
    {
      print_string (ptr_asa_out, "*** Queue_Size < 0 ***");
      ++invalid;
    }
  if (OPTIONS->Queue_Size > 0)
    {
      if (OPTIONS->Queue_Resolution == NULL)
	{
	  print_string (ptr_asa_out, "*** Queue_Resolution == NULL ***");
	  ++invalid;
	}
    }
#endif
#if ASA_RESOLUTION
  if (OPTIONS->Coarse_Resolution == NULL)
    {
      print_string (ptr_asa_out, "*** Coarse_Resolution == NULL ***");
      ++invalid;
    }
#endif
#if ASA_PARALLEL
  if (OPTIONS->Gener_Block < 1)
    {
      print_string (ptr_asa_out, "*** Gener_Block < 1 ***");
      ++invalid;
    }
  if (OPTIONS->Gener_Block_Max < 1)
    {
      print_string (ptr_asa_out, "*** Gener_Block_Max < 1 ***");
      ++invalid;
    }
  if (OPTIONS->Gener_Mov_Avr < 1)
    {
      print_string (ptr_asa_out, "*** Gener_Mov_Avr < 1 ***");
      ++invalid;
    }
#endif

  return (invalid);
}

/***********************************************************************
* print_string
*	This prints the designated string
***********************************************************************/
#if HAVE_ANSI
void
print_string (FILE * ptr_asa_out, char *string)
#else
void
print_string (ptr_asa_out, string)
     FILE *ptr_asa_out;
     char *string;
#endif /* HAVE_ANSI */
{
#if ASA_PRINT
  fprintf (ptr_asa_out, "%s\n", string);
#else
  ;
#endif
}

/***********************************************************************
* print_string_index
*	This prints the designated string and index
***********************************************************************/
#if HAVE_ANSI
void
print_string_index (FILE * ptr_asa_out, char *string, ALLOC_INT index)
#else
void
print_string_index (ptr_asa_out, string, index)
     FILE *ptr_asa_out;
     char *string;
     ALLOC_INT index;
#endif /* HAVE_ANSI */
{
#if ASA_PRINT
#if INT_ALLOC
  fprintf (ptr_asa_out, "%s index = %d\n", string, index);
#else
#if INT_LONG
  fprintf (ptr_asa_out, "%s index = %ld\n", string, index);
#else
  fprintf (ptr_asa_out, "%s index = %d\n", string, index);
#endif
#endif
#else
  ;
#endif
}

#if ASA_PRINT
/***********************************************************************
* print_state
*	Prints a description of the current state of the system
***********************************************************************/
#if HAVE_ANSI
void
print_state (double *parameter_minimum,
	     double *parameter_maximum,
	     double *tangents,
	     double *curvature,
	     double *current_cost_temperature,
	     double *current_user_parameter_temp,
	     double *accepted_to_generated_ratio,
	     ALLOC_INT * number_parameters,
	     int *curvature_flag,
	     LONG_INT * number_accepted,
	     LONG_INT * index_cost_acceptances,
	     LONG_INT * number_generated,
	     LONG_INT * number_invalid_generated_states,
	     STATE * last_saved_state,
	     STATE * best_generated_state,
	     FILE * ptr_asa_out,
	     USER_DEFINES * OPTIONS)
#else
void
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
	     OPTIONS)
     double *parameter_minimum;
     double *parameter_maximum;
     double *tangents;
     double *curvature;
     double *current_cost_temperature;
     double *current_user_parameter_temp;
     double *accepted_to_generated_ratio;
     ALLOC_INT *number_parameters;
     int *curvature_flag;
     LONG_INT *number_accepted;
     LONG_INT *index_cost_acceptances;
     LONG_INT *number_generated;
     LONG_INT *number_invalid_generated_states;
     STATE *last_saved_state;
     STATE *best_generated_state;
     FILE *ptr_asa_out;
     USER_DEFINES *OPTIONS;
#endif /* HAVE_ANSI */
{
  ALLOC_INT index_v;
  ALLOC_INT index_vv, index_v_vv;

  fprintf (ptr_asa_out, "\n");
#if TIME_CALC
  print_time ("", ptr_asa_out);
#endif

  if (OPTIONS->Curvature_0 == TRUE)
    *curvature_flag = FALSE;
  if (OPTIONS->Curvature_0 == -1)
    *curvature_flag = TRUE;

#if INT_LONG
  fprintf (ptr_asa_out,
       "*index_cost_acceptances = %ld, *current_cost_temperature = %*.*g\n",
	   *index_cost_acceptances,
	   G_FIELD, G_PRECISION, *current_cost_temperature);
  fprintf (ptr_asa_out,
	   "*accepted_to_generated_ratio = %*.*g,\
 *number_invalid... = %ld\n",
	   G_FIELD, G_PRECISION, *accepted_to_generated_ratio,
	   (*number_invalid_generated_states));
  fprintf (ptr_asa_out,
	   "*number_generated = %ld, *number_accepted = %ld\n",
	   *number_generated, *number_accepted);
#else
  fprintf (ptr_asa_out,
	"*index_cost_acceptances = %d, *current_cost_temperature = %*.*g\n",
	   *index_cost_acceptances,
	   G_FIELD, G_PRECISION, *current_cost_temperature);
  fprintf (ptr_asa_out,
	   "*accepted_to_generated_ratio = %*.*g,\
 *number_invalid... = %d\n",
	   G_FIELD, G_PRECISION, *accepted_to_generated_ratio,
	   *number_invalid_generated_states);
  fprintf (ptr_asa_out,
	   "*number_generated = %d, *number_accepted = %d\n",
	   *number_generated, *number_accepted);
#endif

  fprintf (ptr_asa_out,
	   "best...->cost = %*.*g,\
 last...->cost = %*.*g\n",
	   G_FIELD, G_PRECISION, best_generated_state->cost,
	   G_FIELD, G_PRECISION, last_saved_state->cost);

  /* Note that tangents will not be calculated until reanneal
     is called, and therefore their listing in the printout only
     is relevant then */

  fprintf (ptr_asa_out, "index_v  best...->parameter current_parameter_temp\ttangent\n");
  VFOR (index_v)
  {
    /* ignore too small ranges */
    if (PARAMETER_RANGE_TOO_SMALL (index_v))
      continue;
    fprintf (ptr_asa_out,
#if INT_ALLOC
	     "%d\t%*.*g\t\t%*.*g\t%*.*g\n",
#else
#if INT_LONG
	     "%ld\t%*.*g\t\t%*.*g\t%*.*g\n",
#else
	     "%d\t%*.*g\t\t%*.*g\t%*.*g\n",
#endif
#endif
	     index_v,
	     G_FIELD, G_PRECISION, best_generated_state->parameter[index_v],
	     G_FIELD, G_PRECISION, current_user_parameter_temp[index_v],
	     G_FIELD, G_PRECISION, tangents[index_v]);
  }

  if (*curvature_flag == TRUE)
    {
      /* print curvatures */
      VFOR (index_v)
      {
	/* ignore too small ranges */
	if (PARAMETER_RANGE_TOO_SMALL (index_v))
	  continue;
	fprintf (ptr_asa_out, "\n");
	VFOR (index_vv)
	{
	  /* only print upper diagonal of matrix */
	  if (index_v < index_vv)
	    continue;
	  /* ignore too small ranges (index_vv) */
	  if (PARAMETER_RANGE_TOO_SMALL (index_vv))
	    continue;

	  /* index_v_vv: row index_v, column index_vv */
	  index_v_vv = ROW_COL_INDEX (index_v, index_vv);

	  if (index_v == index_vv)
	    {
	      fprintf (ptr_asa_out,
#if INT_ALLOC
		       "curvature[%d][%d] = %*.*g\n",
#else
#if INT_LONG
		       "curvature[%ld][%ld] = %*.*g\n",
#else
		       "curvature[%d][%d] = %*.*g\n",
#endif
#endif
		       index_v, index_vv,
		       G_FIELD, G_PRECISION, curvature[index_v_vv]);
	    }
	  else
	    {
	      fprintf (ptr_asa_out,
#if INT_ALLOC
		       "curvature[%d][%d] = %*.*g \t = curvature[%d][%d]\n",
#else
#if INT_LONG
		   "curvature[%ld][%ld] = %*.*g \t = curvature[%ld][%ld]\n",
#else
		       "curvature[%d][%d] = %*.*g \t = curvature[%d][%d]\n",
#endif
#endif
		       index_v, index_vv,
		       G_FIELD, G_PRECISION, curvature[index_v_vv],
		       index_vv, index_v);
	    }
	}
      }
    }
  fprintf (ptr_asa_out, "\n");
  fflush (ptr_asa_out);

}

/***********************************************************************
* print_asa_options
*	Prints user's selected options
***********************************************************************/
#if HAVE_ANSI
void
print_asa_options (FILE * ptr_asa_out, USER_DEFINES * OPTIONS)
#else
void
print_asa_options (ptr_asa_out, OPTIONS)
     FILE *ptr_asa_out;
     USER_DEFINES *OPTIONS;
#endif /* HAVE_ANSI */
{
  fprintf (ptr_asa_out,
	   "\t\tADAPTIVE SIMULATED ANNEALING\n\n");

  fprintf (ptr_asa_out, "%s\n\n", ASA_ID);

  fprintf (ptr_asa_out, "OPTIONS_FILE = %d\n",
	   (int) OPTIONS_FILE);
  fprintf (ptr_asa_out, "OPTIONS_FILE_DATA = %d\n",
	   (int) OPTIONS_FILE_DATA);
  fprintf (ptr_asa_out, "RECUR_OPTIONS_FILE = %d\n",
	   (int) RECUR_OPTIONS_FILE);
  fprintf (ptr_asa_out, "RECUR_OPTIONS_FILE_DATA = %d\n",
	   (int) RECUR_OPTIONS_FILE_DATA);
  fprintf (ptr_asa_out, "COST_FILE = %d\n",
	   (int) COST_FILE);
  fprintf (ptr_asa_out, "ASA_LIB = %d\n",
	   (int) ASA_LIB);
  fprintf (ptr_asa_out, "HAVE_ANSI = %d\n",
	   (int) HAVE_ANSI);
  fprintf (ptr_asa_out, "IO_PROTOTYPES = %d\n",
	   (int) IO_PROTOTYPES);
  fprintf (ptr_asa_out, "TIME_CALC = %d\n",
	   (int) TIME_CALC);
  fprintf (ptr_asa_out, "TIME_STD = %d\n",
	   (int) TIME_STD);
  fprintf (ptr_asa_out, "TIME_GETRUSAGE = %d\n",
	   (int) TIME_GETRUSAGE);
  fprintf (ptr_asa_out, "INT_LONG = %d\n",
	   (int) INT_LONG);
  fprintf (ptr_asa_out, "INT_ALLOC = %d\n",
	   (int) INT_ALLOC);
  fprintf (ptr_asa_out, "SMALL_FLOAT = %*.*g\n",
	   G_FIELD, G_PRECISION, (double) SMALL_FLOAT);
  fprintf (ptr_asa_out, "MIN_DOUBLE = %*.*g\n",
	   G_FIELD, G_PRECISION, (double) MIN_DOUBLE);
  fprintf (ptr_asa_out, "MAX_DOUBLE = %*.*g\n",
	   G_FIELD, G_PRECISION, (double) MAX_DOUBLE);
  fprintf (ptr_asa_out, "EPS_DOUBLE = %*.*g\n",
	   G_FIELD, G_PRECISION, (double) EPS_DOUBLE);
  fprintf (ptr_asa_out, "CHECK_EXPONENT = %d\n",
	   (int) CHECK_EXPONENT);
  fprintf (ptr_asa_out, "NO_PARAM_TEMP_TEST = %d\n",
	   (int) NO_PARAM_TEMP_TEST);
  fprintf (ptr_asa_out, "NO_COST_TEMP_TEST = %d\n",
	   (int) NO_COST_TEMP_TEST);
  fprintf (ptr_asa_out, "SELF_OPTIMIZE = %d\n",
	   (int) SELF_OPTIMIZE);
  fprintf (ptr_asa_out, "ASA_TEST = %d\n",
	   (int) ASA_TEST);
  fprintf (ptr_asa_out, "ASA_TEST_POINT = %d\n",
	   (int) ASA_TEST_POINT);
  fprintf (ptr_asa_out, "ASA_TEMPLATE = %d\n",
	   (int) ASA_TEMPLATE);
  fprintf (ptr_asa_out, "MY_TEMPLATE = %d\n",
	   (int) MY_TEMPLATE);
  fprintf (ptr_asa_out, "ASA_TEMPLATE_LIB = %d\n",
	   (int) ASA_TEMPLATE_LIB);
  fprintf (ptr_asa_out, "ASA_TEMPLATE_ASA_OUT_PID = %d\n",
	   (int) ASA_TEMPLATE_ASA_OUT_PID);
  fprintf (ptr_asa_out, "ASA_TEMPLATE_MULTIPLE = %d\n",
	   (int) ASA_TEMPLATE_MULTIPLE);
  fprintf (ptr_asa_out, "ASA_TEMPLATE_SELFOPT = %d\n",
	   (int) ASA_TEMPLATE_SELFOPT);
  fprintf (ptr_asa_out, "ASA_TEMPLATE_SAMPLE = %d\n",
	   (int) ASA_TEMPLATE_SAMPLE);
  fprintf (ptr_asa_out, "ASA_TEMPLATE_QUEUE = %d\n",
	   (int) ASA_TEMPLATE_QUEUE);
  fprintf (ptr_asa_out, "ASA_TEMPLATE_PARALLEL = %d\n",
	   (int) ASA_TEMPLATE_PARALLEL);
  fprintf (ptr_asa_out, "ASA_TEMPLATE_SAVE = %d\n",
	   (int) ASA_TEMPLATE_SAVE);
  fprintf (ptr_asa_out, "USER_INITIAL_COST_TEMP = %d\n",
	   (int) USER_INITIAL_COST_TEMP);
  fprintf (ptr_asa_out, "RATIO_TEMPERATURE_SCALES = %d\n",
	   (int) RATIO_TEMPERATURE_SCALES);
  fprintf (ptr_asa_out, "USER_INITIAL_PARAMETERS_TEMPS = %d\n",
	   (int) USER_INITIAL_PARAMETERS_TEMPS);
  fprintf (ptr_asa_out, "DELTA_PARAMETERS = %d\n",
	   (int) DELTA_PARAMETERS);
  fprintf (ptr_asa_out, "QUENCH_PARAMETERS = %d\n",
	   (int) QUENCH_PARAMETERS);
  fprintf (ptr_asa_out, "QUENCH_COST = %d\n",
	   (int) QUENCH_COST);
  fprintf (ptr_asa_out, "QUENCH_PARAMETERS_SCALE = %d\n",
	   (int) QUENCH_PARAMETERS_SCALE);
  fprintf (ptr_asa_out, "QUENCH_COST_SCALE = %d\n",
	   (int) QUENCH_COST_SCALE);
  fprintf (ptr_asa_out, "OPTIONAL_DATA = %d\n",
	   (int) OPTIONAL_DATA);
  fprintf (ptr_asa_out, "OPTIONAL_DATA_INT = %d\n",
	   (int) OPTIONAL_DATA_INT);
  fprintf (ptr_asa_out, "USER_COST_SCHEDULE = %d\n",
	   (int) USER_COST_SCHEDULE);
  fprintf (ptr_asa_out, "USER_ACCEPT_ASYMP_EXP = %d\n",
	   (int) USER_ACCEPT_ASYMP_EXP);
  fprintf (ptr_asa_out, "USER_ACCEPTANCE_TEST = %d\n",
	   (int) USER_ACCEPTANCE_TEST);
  fprintf (ptr_asa_out, "USER_GENERATING_FUNCTION = %d\n",
	   (int) USER_GENERATING_FUNCTION);
  fprintf (ptr_asa_out, "USER_REANNEAL_COST = %d\n",
	   (int) USER_REANNEAL_COST);
  fprintf (ptr_asa_out, "USER_REANNEAL_PARAMETERS = %d\n",
	   (int) USER_REANNEAL_PARAMETERS);
#if INT_LONG
  fprintf (ptr_asa_out, "MAXIMUM_REANNEAL_INDEX = %ld\n",
	   (LONG_INT) MAXIMUM_REANNEAL_INDEX);
#else
  fprintf (ptr_asa_out, "MAXIMUM_REANNEAL_INDEX = %d\n",
	   (LONG_INT) MAXIMUM_REANNEAL_INDEX);
#endif
  fprintf (ptr_asa_out, "REANNEAL_SCALE = %*.*g\n",
	   G_FIELD, G_PRECISION, (double) REANNEAL_SCALE);
  fprintf (ptr_asa_out, "ASA_SAMPLE = %d\n",
	   (int) ASA_SAMPLE);
  fprintf (ptr_asa_out, "ASA_QUEUE = %d\n",
	   (int) ASA_QUEUE);
  fprintf (ptr_asa_out, "ASA_RESOLUTION = %d\n",
	   (int) ASA_RESOLUTION);
  fprintf (ptr_asa_out, "FITLOC = %d\n",
	   (int) FITLOC);
  fprintf (ptr_asa_out, "FITLOC_ROUND = %d\n",
	   (int) FITLOC_ROUND);
  fprintf (ptr_asa_out, "ASA_PARALLEL = %d\n",
	   (int) ASA_PARALLEL);
  fprintf (ptr_asa_out, "ASA_SAVE = %d\n",
	   (int) ASA_SAVE);
  fprintf (ptr_asa_out, "SYSTEM_CALL = %d\n",
	   (int) SYSTEM_CALL);
  fprintf (ptr_asa_out, "FDLIBM_POW = %d\n",
	   (int) FDLIBM_POW);
  fprintf (ptr_asa_out, "FDLIBM_LOG = %d\n",
	   (int) FDLIBM_LOG);
  fprintf (ptr_asa_out, "FDLIBM_EXP = %d\n\n",
	   (int) FDLIBM_EXP);

  fprintf (ptr_asa_out, "ASA_PRINT = %d\n",
	   (int) ASA_PRINT);
#if USER_ASA_OUT
  fprintf (ptr_asa_out, "ASA_OUT = %s\n",
	   OPTIONS->Asa_Out_File);
#else
  fprintf (ptr_asa_out, "ASA_OUT = %s\n",
	   ASA_OUT);
#endif
  fprintf (ptr_asa_out, "USER_ASA_OUT = %d\n",
	   (int) USER_ASA_OUT);
  fprintf (ptr_asa_out, "ASA_PRINT_INTERMED = %d\n",
	   (int) ASA_PRINT_INTERMED);
  fprintf (ptr_asa_out, "ASA_PRINT_MORE = %d\n",
	   (int) ASA_PRINT_MORE);
  fprintf (ptr_asa_out, "G_FIELD = %d\n",
	   (int) G_FIELD);
  fprintf (ptr_asa_out, "G_PRECISION = %d\n\n",
	   (int) G_PRECISION);

#if INT_LONG
  fprintf (ptr_asa_out, "OPTIONS->Limit_Acceptances = %ld\n",
	   (LONG_INT) OPTIONS->Limit_Acceptances);
  fprintf (ptr_asa_out, "OPTIONS->Limit_Generated = %ld\n",
	   (LONG_INT) OPTIONS->Limit_Generated);
#else
  fprintf (ptr_asa_out, "OPTIONS->Limit_Acceptances = %d\n",
	   (LONG_INT) OPTIONS->Limit_Acceptances);
  fprintf (ptr_asa_out, "OPTIONS->Limit_Generated = %d\n",
	   (LONG_INT) OPTIONS->Limit_Generated);
#endif
  fprintf (ptr_asa_out, "OPTIONS->Limit_Invalid_Generated_States = %d\n",
	   OPTIONS->Limit_Invalid_Generated_States);
  fprintf (ptr_asa_out, "OPTIONS->Accepted_To_Generated_Ratio = %*.*g\n\n",
	   G_FIELD, G_PRECISION, OPTIONS->Accepted_To_Generated_Ratio);

  fprintf (ptr_asa_out, "OPTIONS->Cost_Precision = %*.*g\n",
	   G_FIELD, G_PRECISION, OPTIONS->Cost_Precision);
  fprintf (ptr_asa_out, "OPTIONS->Maximum_Cost_Repeat = %d\n",
	   OPTIONS->Maximum_Cost_Repeat);
  fprintf (ptr_asa_out, "OPTIONS->Number_Cost_Samples = %d\n",
	   OPTIONS->Number_Cost_Samples);
  fprintf (ptr_asa_out, "OPTIONS->Temperature_Ratio_Scale = %*.*g\n",
	   G_FIELD, G_PRECISION, OPTIONS->Temperature_Ratio_Scale);
  fprintf (ptr_asa_out, "OPTIONS->Cost_Parameter_Scale_Ratio = %*.*g\n",
	   G_FIELD, G_PRECISION, OPTIONS->Cost_Parameter_Scale_Ratio);
  fprintf (ptr_asa_out, "OPTIONS->Temperature_Anneal_Scale = %*.*g\n",
	   G_FIELD, G_PRECISION, OPTIONS->Temperature_Anneal_Scale);

  fprintf (ptr_asa_out, "OPTIONS->Include_Integer_Parameters = %d\n",
	   OPTIONS->Include_Integer_Parameters);
  fprintf (ptr_asa_out, "OPTIONS->User_Initial_Parameters = %d\n",
	   OPTIONS->User_Initial_Parameters);
#if INT_ALLOC
  fprintf (ptr_asa_out, "OPTIONS->Sequential_Parameters = %d\n",
	   (int) OPTIONS->Sequential_Parameters);
#else
#if INT_LONG
  fprintf (ptr_asa_out, "OPTIONS->Sequential_Parameters = %ld\n",
	   (LONG_INT) OPTIONS->Sequential_Parameters);
#else
  fprintf (ptr_asa_out, "OPTIONS->Sequential_Parameters = %d\n",
	   (LONG_INT) OPTIONS->Sequential_Parameters);
#endif
#endif
  fprintf (ptr_asa_out, "OPTIONS->Initial_Parameter_Temperature = %*.*g\n",
	   G_FIELD, G_PRECISION, OPTIONS->Initial_Parameter_Temperature);

  fprintf (ptr_asa_out, "OPTIONS->Acceptance_Frequency_Modulus = %d\n",
	   OPTIONS->Acceptance_Frequency_Modulus);
  fprintf (ptr_asa_out, "OPTIONS->Generated_Frequency_Modulus = %d\n",
	   OPTIONS->Generated_Frequency_Modulus);
  fprintf (ptr_asa_out, "OPTIONS->Reanneal_Cost = %d\n",
	   OPTIONS->Reanneal_Cost);
  fprintf (ptr_asa_out, "OPTIONS->Reanneal_Parameters = %d\n\n",
	   OPTIONS->Reanneal_Parameters);

  fprintf (ptr_asa_out, "OPTIONS->Delta_X = %*.*g\n",
	   G_FIELD, G_PRECISION, OPTIONS->Delta_X);
  fprintf (ptr_asa_out, "OPTIONS->User_Tangents = %d\n",
	   OPTIONS->User_Tangents);
  fprintf (ptr_asa_out, "OPTIONS->Curvature_0 = %d\n\n",
	   OPTIONS->Curvature_0);

  fprintf (ptr_asa_out, "\n");
}
#endif /* ASA_PRINT */

#if TIME_CALC
#if TIME_GETRUSAGE
/***********************************************************************
* print_time
*	This calculates the time and runtime and prints it.
***********************************************************************/
#if HAVE_ANSI
void
print_time (char *message, FILE * ptr_asa_out)
#else
void
print_time (message, ptr_asa_out)
     char *message;
     FILE *ptr_asa_out;
#endif /* HAVE_ANSI */
{
  int who = RUSAGE_SELF;	/* Check our own time */
  struct rusage usage;

  /* get the resource usage information */
#if TIME_STD
  syscall (SYS_GETRUSAGE, who, &usage);
#else
  getrusage (who, &usage);
#endif

  /* print the usage time in reasonable form */
  aux_print_time (&usage.ru_utime, message, ptr_asa_out);
}

/***********************************************************************
* aux_print_time
*      auxiliary print the time routine
***********************************************************************/
#if HAVE_ANSI
void
aux_print_time (struct timeval *time, char *message,
		FILE * ptr_asa_out)
#else
void
aux_print_time (time, message, ptr_asa_out)
     struct timeval *time;
     char *message;
     FILE *ptr_asa_out;
#endif /* HAVE_ANSI */
{
  static double sx;
  double us, s, m, h;
  double ds, dm, dh;

  /* calculate the new microseconds, seconds, minutes, hours
     and the differences since the last call */
  us = (double) ((int) ((double) EPS_DOUBLE + time->tv_usec)) / 1.E6;
  s = (double) ((int) ((double) EPS_DOUBLE + time->tv_sec)) + us;
  ds = s - sx;
  sx = s;

  h = (int) ((double) EPS_DOUBLE + s / 3600.);
  m = (int) ((double) EPS_DOUBLE + s / 60.) - 60. * h;
  s -= (3600. * h + 60. * m);
  dh = (int) ((double) EPS_DOUBLE + ds / 3600.);
  dm = (int) ((double) EPS_DOUBLE + ds / 60.) - 60. * dh;
  ds -= (3600. * dh + 60. * dm);

  /* print the statistics */
  fprintf (ptr_asa_out,
	   "%s:time: %gh %gm %gs; incr: %gh %gm %gs\n",
	   message, h, m, s, dh, dm, ds);
}
#else /* TIME_GETRUSAGE */
  /* Note that on many machines the time resolution of this algorithm
   * may be less than the other alternatives, e.g., rounding off the
   * number of ticks to the nearest tens of thousands.  Also, because
   * time here is typically indexed by a long integer, there typically
   * is a cycle of time in periods of fractions of an hour.  For
   * example, under Solaris 2.5.1:  The value returned by clock() is
   * defined in microseconds, since the first call to clock(), for
   *  compatibility with  systems that have * CPU clocks with much higher
   * resolution.  Because of this, the value returned will wrap around
   * after accumulating only 2147 seconds of CPU time (about 36 minutes).
   *
   * See asa.h for two places where some additional modifications should
   * be made under SunOS 4.1.x. */

#if HAVE_ANSI
void
print_time (char *message, FILE * ptr_asa_out)
#else
void
print_time (message, ptr_asa_out)
     char *message;
     FILE *ptr_asa_out;
#endif /* HAVE_ANSI */
{
  aux_print_time (clock (), message, ptr_asa_out);

}				/*print_time */

/***********************************************************************
* aux_print_time
*      auxiliary print the time routine
***********************************************************************/
#if HAVE_ANSI
void
aux_print_time (clock_t time, char *message, FILE * ptr_asa_out)
#else
void
aux_print_time (time, message, ptr_asa_out)
     clock_t time;
     char *message;
     FILE *ptr_asa_out;
#endif /* HAVE_ANSI */
{
  static clock_t previousTime = -1;
  clock_t diffTime;
  double clocksPerSecF = CLOCKS_PER_SEC;
  double timeF, diffF;
  double s, m, h;
  double ds, dm, dh;

  if (previousTime != -1)
    {
      diffTime = time - previousTime;
      timeF = time;
      diffF = diffTime;
      previousTime = time;

      s = timeF / clocksPerSecF;
      ds = diffF / clocksPerSecF;

      h = (int) ((double) EPS_DOUBLE + s / 3600.);
      m = (int) ((double) EPS_DOUBLE + s / 60.) - 60. * h;
      s -= (3600. * h + 60. * m);
      dh = (int) ((double) EPS_DOUBLE + ds / 3600.);
      dm = (int) ((double) EPS_DOUBLE + ds / 60.) - 60. * dh;
      ds -= (3600. * dh + 60. * dm);

      fprintf (ptr_asa_out,
	       "%s:time: %gh %gm %gs; incr: %gh %gm %gs\n",
	       message, h, m, s, dh, dm, ds);
    }
  else
    {
      /* The first call will be invalid - don't output anything. */
      fprintf (ptr_asa_out, "TIMING PARAMETERS: ticks/sec: %lu\n",
	       CLOCKS_PER_SEC);
      previousTime = time;
    }
}				/* aux_print_time */

#endif /* TIME_GETRUSAGE */

#endif /* TIME_CALC */
