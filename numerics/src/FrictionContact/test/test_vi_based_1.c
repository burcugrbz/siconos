/* Siconos is a program dedicated to modeling, simulation and control
 * of non smooth dynamical systems.
 *
 * Copyright 2016 INRIA.
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

#include <stdio.h>                       // for NULL
#include <stdlib.h>                      // for malloc
#include "Friction_cst.h"                // for SICONOS_FRICTION_3D_NSN_AC_TEST
#include "VI_cst.h"   // for SICONOS_VI_EG_...
#include "SolverOptions.h"               // for SICONOS_DPARAM_TOL, SICONOS_...
#include "frictionContact_test_utils.h"  // for build_friction_test, build_test_colle...
#include "test_utils.h"                  // for TestCase

TestCase * build_test_collection(int n_data, const char ** data_collection, int* number_of_tests)
{

  *number_of_tests = 8; //n_data * n_solvers;
  TestCase * collection = (TestCase*)malloc((*number_of_tests) * sizeof(TestCase));

  int current = 0;

  {
    int d = 0; // FC3D_Example1.dat
    // rho = -1
    int dpos[] = {2, SICONOS_DPARAM_TOL, SICONOS_VI_EG_DPARAM_RHO}; 
    double dparam[] = {1e-8, -1.};
    int ipos[] = {1, SICONOS_IPARAM_MAX_ITER};
    int iparam[] = {10000};
    // 
    build_friction_test(data_collection[d],
               SICONOS_FRICTION_3D_EG, dpos, dparam, ipos, iparam,
               -1, NULL, NULL, NULL, NULL, &collection[current++]);
  }
  {
    int d = 0; // FC3D_Example1.da
    // rho = 1
    int dpos[] = {2, SICONOS_DPARAM_TOL, SICONOS_VI_EG_DPARAM_RHO}; 
    double dparam[] = {1e-8, 1.};
    int ipos[] = {1, SICONOS_IPARAM_MAX_ITER};
    int iparam[] = {10000};
    // 
    build_friction_test(data_collection[d],
               SICONOS_FRICTION_3D_EG, dpos, dparam, ipos, iparam,
               -1, NULL, NULL, NULL, NULL, &collection[current++]);
  }


  {
    int d = 2; // FrictionContact3D_1c.dat
    // rho = -3e-3
    int dpos[] = {2, SICONOS_DPARAM_TOL, SICONOS_VI_EG_DPARAM_RHO}; 
    double dparam[] = {1e-8, -3.e-3};
    int ipos[] = {1, SICONOS_IPARAM_MAX_ITER};
    int iparam[] = {10000};
    // 
    build_friction_test(data_collection[d],
               SICONOS_FRICTION_3D_EG, dpos, dparam, ipos, iparam,
               -1, NULL, NULL, NULL, NULL, &collection[current++]);
    // expected to fail
    collection[current-1].will_fail = 1;
  }
  {
    int d = 2; // FrictionContact3D_1c.dat
    // rho = -1
    int dpos[] = {2, SICONOS_DPARAM_TOL, SICONOS_VI_EG_DPARAM_RHO}; 
    double dparam[] = {1e-10, -1.};
    int ipos[] = {1, SICONOS_IPARAM_MAX_ITER};
    int iparam[] = {10000};
    // 
    build_friction_test(data_collection[d],
               SICONOS_FRICTION_3D_EG, dpos, dparam, ipos, iparam,
               -1, NULL, NULL, NULL, NULL, &collection[current++]);
  }
  {
    int d = 2; // FrictionContact3D_1c.dat
    // rho = -10
    int dpos[] = {2, SICONOS_DPARAM_TOL, SICONOS_VI_EG_DPARAM_RHO}; 
    double dparam[] = {1e-10, -10.};
    int ipos[] = {3, SICONOS_IPARAM_MAX_ITER, 2, 3};
    // 2 for IPARAM_PREALLOC ? or SICONOS_FRICTION_3D_IPARAM_INTERNAL_ERROR_STRATEGY ?// 3? 
    int iparam[] = {1000, 0, 0};
    // 
    build_friction_test(data_collection[d],
               SICONOS_FRICTION_3D_HP, dpos, dparam, ipos, iparam,
               -1, NULL, NULL, NULL, NULL, &collection[current++]);
    // expected to fail
    collection[current-1].will_fail = 1;
  }

  {
    int d = 6; // Capsules-i101-404.dat
    int dpos[] = {1, SICONOS_DPARAM_TOL}; 
    double dparam[] = {1e-10};
    int ipos[] = {2, SICONOS_IPARAM_MAX_ITER, 2};
    // 2 for IPARAM_PREALLOC ? or SICONOS_FRICTION_3D_IPARAM_INTERNAL_ERROR_STRATEGY ?
    int iparam[] = {1000, 1};
    // 
    build_friction_test(data_collection[d],
               SICONOS_FRICTION_3D_VI_FPP, dpos, dparam, ipos, iparam,
               -1, NULL, NULL, NULL, NULL, &collection[current++]);
    // expected to fail
    collection[current-1].will_fail = 1;
  }

  {
    int d = 6; // Capsules-i101-404.dat
    int dpos[] = {1, SICONOS_DPARAM_TOL}; 
    double dparam[] = {1e-8};
    int ipos[] = {1, SICONOS_IPARAM_MAX_ITER};
    int iparam[] = {100000};
    // 
    build_friction_test(data_collection[d],
               SICONOS_FRICTION_3D_FPP, dpos, dparam, ipos, iparam,
               -1, NULL, NULL, NULL, NULL, &collection[current++]);
    // expected to fail
    collection[current-1].will_fail = 1;
  }

{
    int d = 6; // Capsules-i101-404.dat
    int dpos[] = {1, SICONOS_DPARAM_TOL}; 
    double dparam[] = {1e-8};
    int ipos[] = {2, SICONOS_IPARAM_MAX_ITER, 2};
    // 2 for IPARAM_PREALLOC ? or SICONOS_FRICTION_3D_IPARAM_INTERNAL_ERROR_STRATEGY ?
    int iparam[] = {100000, 1};
    // 
    build_friction_test(data_collection[d],
               SICONOS_FRICTION_3D_VI_EG, dpos, dparam, ipos, iparam,
               -1, NULL, NULL, NULL, NULL, &collection[current++]);
    // expected to fail
    collection[current-1].will_fail = 1;
  }

  *number_of_tests = current;
  return collection;

}
