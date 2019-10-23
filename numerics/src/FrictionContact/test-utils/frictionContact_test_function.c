/* Siconos is a program dedicated to modeling, simulation and control
 * of non smooth dynamical systems.
 *
 * Copyright 2018 INRIA.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#include <math.h>                        // for isfinite
#include <stdio.h>                       // for printf, fclose, fopen, fprintf
#include <stdlib.h>                      // for calloc, free, malloc, exit
#include "FrictionContactProblem.h"      // for FrictionContactProblem, fric...
#include "GAMSlink.h"                    // for SN_GAMSparams
#include "NonSmoothDrivers.h"            // for fc2d_driver, fc3d_driver
#include "NumericsFwd.h"                 // for SolverOptions, FrictionConta...
#include "SOCLCP_Solvers.h"              // for soclcp_setDefaultSolverOptions
#include "SolverOptions.h"               // for SolverOptions, solver_option...
#include "fc3d_Solvers.h"                // for fc3d_setDefaultSolverOptions
#include "frictionContact_test_utils.h"  // for build_friction_test, frictio...
#include "test_utils.h"                  // for TestCase
#include "SiconosConfig.h" // for WITH_FCLIB, HAVE_GAMS_C_API // IWYU pragma: keep

// avoid a conflict with old csparse.h in case fclib includes it
#define _CS_H

#if defined(WITH_FCLIB)
#include <time.h>
#include <fclib_interface.h>
#include "fc3d_solvers_wr.h"
#endif

void build_friction_test(const char * filename,
                int solver_id, int* d_ind, double* dparam, int * i_ind, int* iparam,
                int internal_solver_id, int * i_d_ind, double * internal_dparam, int * i_i_ind, int * internal_iparam,
                TestCase* testname)
{
  // reference file name
  testname->filename = filename;
  // By default, test is expected to succeed.
  testname->will_fail = 0;

  // Set solver options to default.
  testname->options = (SolverOptions *)malloc(sizeof(SolverOptions));
  fc3d_setDefaultSolverOptions(testname->options, solver_id);
  // Fill iparam and dparam in.
  if(iparam)
    for(int i=0; i<i_ind[0]; ++i)
      testname->options->iparam[i_ind[i+1]] = iparam[i];

  // dparam
  if(dparam)
    for(int i=0; i<d_ind[0]; ++i)
      testname->options->dparam[d_ind[i+1]] = dparam[i];

  // Internal solver setup
  if(internal_solver_id>0)
    {
      if (internal_solver_id >= 400 && internal_solver_id < 700)
        fc3d_setDefaultSolverOptions(testname->options->internalSolvers, internal_solver_id);
      else if (internal_solver_id >= 1100 && internal_solver_id < 1200)
        soclcp_setDefaultSolverOptions(testname->options->internalSolvers, internal_solver_id);
      else
        {
          fprintf(stderr, "unknown internal solver\n");
          exit(EXIT_FAILURE);
        }
      // internal iparam
      if(internal_iparam)
        for(int i=0; i<i_i_ind[0]; ++i)
          testname->options->internalSolvers[0].iparam[i_i_ind[i+1]] = internal_iparam[i];
      // internal dparam
      if(internal_dparam)
        for(int i=0; i<i_d_ind[0]; ++i)
          testname->options->internalSolvers[0].dparam[i_d_ind[i+1]] = internal_dparam[i];
    }
}

void frictionContact_test_gams_opts(SN_GAMSparams* GP, int solverId)
{
#ifdef HAVE_GAMS_C_API
  if (solverId == SICONOS_FRICTION_3D_GAMS_PATHVI ||
      solverId == SICONOS_FRICTION_3D_GAMS_LCP_PATHVI ||
      solverId == SICONOS_GLOBAL_FRICTION_3D_GAMS_PATHVI)
    {
    add_GAMS_opt_str(GP, "avi_start", "ray_first", GAMS_OPT_SOLVER);
    add_GAMS_opt_str(GP, "ratio_tester", "expand", GAMS_OPT_SOLVER);
    add_GAMS_opt_double(GP, "expand_eps", 0., GAMS_OPT_SOLVER);
    add_GAMS_opt_bool(GP, "ratio_tester_tfirst", false, GAMS_OPT_SOLVER);
//    add_GAMS_opt_int(GP, "scheduler_decompose", 1, GAMS_OPT_SOLVER);
//    add_GAMS_opt_str(GP, "lemke_factorization_method", "minos_blu", GAMS_OPT_SOLVER);
  }
  else if (solverId == SICONOS_FRICTION_3D_GAMS_PATH ||
      solverId == SICONOS_FRICTION_3D_GAMS_LCP_PATH ||
      solverId == SICONOS_GLOBAL_FRICTION_3D_GAMS_PATH
      )
  {
    add_GAMS_opt_int(GP, "linear_model_perturb", 0, GAMS_OPT_SOLVER);
    add_GAMS_opt_double(GP, "proximal_perturbation", 0., GAMS_OPT_SOLVER);
    add_GAMS_opt_double(GP, "proximal_initial_maximum", 0., GAMS_OPT_SOLVER);
    add_GAMS_opt_str(GP, "crash_method", "none", GAMS_OPT_SOLVER);
    add_GAMS_opt_int(GP, "crash_perturb", 0, GAMS_OPT_SOLVER);
    add_GAMS_opt_int(GP, "restart_limit", 0, GAMS_OPT_SOLVER);
//    add_GAMS_opt_str(GP, "lemke_start", "first", GAMS_OPT_SOLVER);
//    add_GAMS_opt_int(GP, "output_linear_model", 1, GAMS_OPT_SOLVER);
//    add_GAMS_opt_int(GP, "output_minor_iterations_frequency", 1, GAMS_OPT_SOLVER);
//    add_GAMS_opt_int(GP, "output_linear_model", 1, GAMS_OPT_SOLVER);

  }
  else
  {
    fprintf(stderr, "frictionContact_test_gams_opts :: ERROR unknown solverId = %d e.g. solver named %s", solverId, solver_options_id_to_name(solverId));
  }
  add_GAMS_opt_int(GP, "minor_iteration_limit", 100000, GAMS_OPT_SOLVER);
  add_GAMS_opt_int(GP, "major_iteration_limit", 20, GAMS_OPT_SOLVER);
  add_GAMS_opt_double(GP, "expand_delta", 1e-10, GAMS_OPT_SOLVER);
#endif
}

int frictionContact_test_function(TestCase* current)
{
  int info = -1 ;

  FrictionContactProblem * problem  = frictionContact_new_from_filename(current->filename);
  FILE * foutput  =  fopen("checkinput.dat", "w");
  info = frictionContact_printInFile(problem, foutput);

#ifdef WITH_FCLIB
  int global_hdf5_output =0;
  
  if(global_hdf5_output)
    {
      /* get the current calendar time */
      int stime;
      long ltime;
      ltime = time(NULL);
      stime = (unsigned) ltime/2;
      srand(stime);
      char filename[100];
      sprintf(filename,"gfc3d_%d.hdf5",rand());
      
      GlobalFrictionContactProblem * gfc3d = fc3d_reformulation_global_problem(problem);
      
      char * title = "--";
      char * description = "--";
      char * mathInfo = "--";
      
      globalFrictionContact_fclib_write(gfc3d,
                                        title,
                                        description,
                                        mathInfo,
                                        filename);
      
    }
#endif

  int NC = problem->numberOfContacts;
  int dim = problem->dimension;
  //int dim = problem->numberOfContacts;

  double *reaction = (double*)calloc(dim * NC, sizeof(double));
  double *velocity = (double*)calloc(dim * NC, sizeof(double));

  solver_options_print(current->options);

  if (dim == 2)
    {
      info = fc2d_driver(problem,
                         reaction , velocity,
                         current->options);
    }
  else if (dim == 3)
    {
      info = fc3d_driver(problem,
                         reaction , velocity,
                         current->options);
    }
  else
    info = 1;

  for (int k = 0; k < dim * NC; ++k)
  {
    info = info == 0 ? !(isfinite(velocity[k]) && isfinite(reaction[k])) : info;
  }
  
  if (!info)
    printf("test successful, residual = %g\t, iteration = %i \n", current->options->dparam[1], current->options->iparam[1]);
  else
    printf("test unsuccessful, residual = %g, info = %d, nb iter = %d\n", current->options->dparam[1], info, current->options->iparam[SICONOS_IPARAM_ITER_DONE]);

  free(reaction);
  free(velocity);
  frictionContactProblem_free(problem);
  solver_options_delete(current->options);
  solver_options_nullify(current->options);
  fclose(foutput);

  return info;
}


#if defined(WITH_FCLIB)
int frictionContact_test_function_hdf5(const char * path, SolverOptions * options)
{

  int k, info = -1 ;
  /* FrictionContactProblem* problem = (FrictionContactProblem *)malloc(sizeof(FrictionContactProblem)); */
  /* info = frictionContact_newFromFile(problem, f); */

  FrictionContactProblem* problem = frictionContact_fclib_read(path);
  FILE * foutput  =  fopen("checkinput.dat", "w");
  info = frictionContact_printInFile(problem, foutput);

  int NC = problem->numberOfContacts;
  int dim = problem->dimension;
  //int dim = problem->numberOfContacts;

  double *reaction = (double*)calloc(dim * NC, sizeof(double));
  double *velocity = (double*)calloc(dim * NC, sizeof(double));

  if (dim == 2)
  {
    info = fc2d_driver(problem,
		       reaction , velocity,
		       options);
  }
  else if (dim == 3)
  {
    info = fc3d_driver(problem,
		       reaction , velocity,
		       options);
  }
  else
  {
    info = 1;
  }
  printf("\n");

  int print_size =10;

  if  (dim * NC >= print_size)
  {
    printf("First values (%i)\n", print_size);
    for (k = 0 ; k < print_size; k++)
    {
      printf("Velocity[%i] = %12.8e \t \t Reaction[%i] = %12.8e\n", k, velocity[k], k , reaction[k]);
    }
    printf(" ..... \n");
  }
  else
  {
    for (k = 0 ; k < dim * NC; k++)
    {
      printf("Velocity[%i] = %12.8e \t \t Reaction[%i] = %12.8e\n", k, velocity[k], k , reaction[k]);
    }
    printf("\n");
  }

  for (k = 0; k < dim * NC; ++k)
  {
    info = info == 0 ? !(isfinite(velocity[k]) && isfinite(reaction[k])) : info;
  }

  if (!info)
  {
    printf("test successful, residual = %g\n", options->dparam[1]);
  }
  else
  {
    printf("test unsuccessful, residual = %g\n", options->dparam[1]);
  }
  free(reaction);
  free(velocity);

  frictionContactProblem_free(problem);
  fclose(foutput);

  return info;

}

#endif
