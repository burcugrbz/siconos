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
#ifndef GLOBALFRICTIONCONTACT_TEST_UTILS_H
#define GLOBALFRICTIONCONTACT_TEST_UTILS_H

#include "SiconosConfig.h"  // for BUILD_AS_CPP // IWYU pragma: keep
#include "NumericsFwd.h"    // for SolverOptions
#include "test_utils.h"     // for TestCase#include <stdio.h>

#if defined(__cplusplus) && !defined(BUILD_AS_CPP)
extern "C"
{
#endif
  
  
  int globalFrictionContact_test_function(TestCase*);
  
#if defined(WITH_FCLIB)
  int gfc3d_test_function_hdf5(const char* path, SolverOptions* options);
#endif

#if defined(__cplusplus) && !defined(BUILD_AS_CPP)
}
#endif

#endif


