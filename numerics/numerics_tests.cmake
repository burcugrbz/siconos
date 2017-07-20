include(tools4tests)

# wrapper are not needed
set(TEST_WRAP)

if(WITH_${COMPONENT}_TESTING)
  
  BEGIN_TEST(src/tools/test)
  if(HAS_LAPACK_DGESVD)
    NEW_TEST(pinvtest testpinv.c)
  endif()
  NEW_TEST(test_op3x3 test_op3x3.c)
  NEW_TEST(test_timers_interf test_timers_interf.c)
  NEW_TEST(test_cblas test_cblas.c)
  NEW_TEST(test_dgesv test_dgesv.c)
  if(HAS_LAPACK_DGESVD)
    NEW_TEST(test_gesvd test_gesvd.c)
  endif()
  if(HAS_LAPACK_DGELS)
    NEW_TEST(test_dgels test_dgels.c)
  endif()
  NEW_TEST(test_dpotrf test_dpotrf.c)
  #NEW_TEST(NumericsMatrixTest main_NumericsMatrix.c)
  NEW_TEST(NumericsMatrixTest0 NumericsMatrix_test0.c)
  NEW_TEST(NumericsMatrixTest1 NumericsMatrix_test1.c)
  NEW_TEST(NumericsMatrixTest2 NumericsMatrix_test2.c)
  NEW_TEST(NumericsMatrixTest3 NumericsMatrix_test3.c)
  NEW_TEST(NumericsMatrixTest4 NumericsMatrix_test4.c)
  NEW_TEST(NumericsMatrixTest5 NumericsMatrix_test5.c)
  NEW_TEST(NumericsMatrixTest6 NumericsMatrix_test6.c)
  NEW_TEST(SBMTest1 SBM_test1.c)
  NEW_TEST(SBMTest2 SBM_test2.c)
  NEW_TEST(SBMTest3 SBM_test3.c)
  NEW_TEST(SBMTest4 SBM_test4.c)
  NEW_TEST(SBMTest5 SBM_test5.c)
  NEW_TEST(SparseMatrix0 SparseMatrix_test0.c)
  NEW_TEST(SparseMatrix_NM_gemm SparseMatrix_NM_gemm.c)
  IF(HAS_ONE_LP_SOLVER)
   NEW_TEST(Vertex_extraction vertex_problem.c)
  ENDIF(HAS_ONE_LP_SOLVER)
 END_TEST()

 BEGIN_TEST2(src/LCP/test)

  MACRO(SET_LCP_TEST_AS_FAILED DATASET_LCP_DIAG FAILING_ALGO)
   FOREACH(_DS ${DATASET_LCP_DIAG})
    FOREACH(_SOLVER ${FAILING_ALGO})
     SET(test-LCP_${_SOLVER}-lcp_${_DS}_PROPERTIES WILL_FAIL TRUE)
    ENDFOREACH()
   ENDFOREACH()
  ENDMACRO()

  SET(DATASET_LCP "lcp_mmc.dat;lcp_deudeu.dat;lcp_trivial.dat;lcp_ortiz.dat;lcp_enum_fails.dat")
  LIST(APPEND DATASET_LCP
   "lcp_exp_murty.dat;lcp_exp_murty2.dat;lcp_CPS_1.dat;lcp_CPS_2.dat;lcp_CPS_3.dat;lcp_CPS_4.dat;lcp_CPS_4bis.dat;lcp_CPS_5.dat")
  SET(DATASET_BLOCK_LCP "lcp_deudeu_block.dat")
  # PSOR is not working :(
  SET(SICONOS_LCP_SOLVERS
   "ENUM;LEMKE;CPG;PGS;RPGS;LATIN;LATIN_W;QP;NSQP;AVI_CAOFERRIS;NEWTONMIN;NEWTON_FBLSA;NEWTON_MINFBLSA;BARD;MURTY;PIVOT;PIVOT_LUMOD;PATHSEARCH")
  IF(HAVE_PATHFERRIS)
   LIST(APPEND SICONOS_LCP_SOLVERS "PATH")
  ENDIF()
  IF(HAVE_GAMS_C_API)
   LIST(APPEND SICONOS_LCP_SOLVERS "GAMS")
  ENDIF(HAVE_GAMS_C_API)
  FOREACH(_DS ${DATASET_LCP})
    FOREACH(_SOLVER ${SICONOS_LCP_SOLVERS})
     NEW_LCP_TEST(SICONOS_LCP_${_SOLVER} ${_DS})
    ENDFOREACH()
  ENDFOREACH()
  FOREACH(_DS ${DATASET_BLOCK_LCP})
   FOREACH(_SOLVER ${SICONOS_LCP_SOLVERS})
    NEW_LCP_TEST(SICONOS_LCP_${_SOLVER} ${_DS} 1)
    ENDFOREACH()
  ENDFOREACH()

  # CPG does not work everywhere
  SET(test-LCP_CPG-lcp_deudeu_PROPERTIES WILL_FAIL TRUE)
  SET(test-LCP_CPG-lcp_exp_murty_PROPERTIES WILL_FAIL TRUE)
  SET(test-LCP_CPG-lcp_CPS_2_PROPERTIES WILL_FAIL TRUE)
  SET(test-LCP_CPG-lcp_CPS_4_PROPERTIES WILL_FAIL TRUE)
  SET(test-LCP_CPG-lcp_CPS_4bis_PROPERTIES WILL_FAIL TRUE)

  # problem with Cholesky here
  SET_LCP_TEST_AS_FAILED("exp_murty;exp_murty2" "LATIN;LATIN_W")
  RM_TEST2(SICONOS_LCP_LATIN "lcp_ortiz.dat")
  RM_TEST2(SICONOS_LCP_LATIN_W "lcp_ortiz.dat")

  # QP reformulation does not always work when the matrix is not symmetric
  # Use NSQP
  SET_LCP_TEST_AS_FAILED("exp_murty;exp_murty2;ortiz;enum_fails;CPS_2;CPS_3;CPS_4;CPS_4bis" "QP")

  # NEWTONMIN has no backup descent dir -> problem in DGESV -> GAME OVER !
  SET(test-LCP_NEWTONMIN-lcp_CPS_1_PROPERTIES WILL_FAIL TRUE)
  SET(test-LCP_NEWTONMIN-lcp_CPS_2_PROPERTIES WILL_FAIL TRUE)
  SET(test-LCP_NEWTONMIN-lcp_CPS_5_PROPERTIES WILL_FAIL TRUE)

  # NaN showing up in DGESV -> NEWTONMIN looks really buggy
  SET(test-LCP_NEWTONMIN-lcp_CPS_4_PROPERTIES WILL_FAIL TRUE)
  SET(test-LCP_NEWTONMIN-lcp_CPS_4bis_PROPERTIES WILL_FAIL TRUE)
  SET(test-LCP_NEWTONMIN-lcp_enum_fails_PROPERTIES WILL_FAIL TRUE)

  # those test cannot be solved with an algorithm that requires non-zero
  # diagonal elements, that is PGS, BARD, MURTY, LATIN and LATIN_W
  SET_LCP_TEST_AS_FAILED("enum_fails;CPS_2;CPS_3;CPS_4;CPS_4bis" "PGS;BARD;MURTY;LATIN;LATIN_W")
  # suprinsingly this works ...
  SET(test-LCP_MURTY-lcp_enum_fails_PROPERTIES WILL_FAIL FALSE)

  # those test cannot be solved with Lemke-based solvers (CPS_3 is for Lemke-Howson)
  SET_LCP_TEST_AS_FAILED("CPS_3" "LEMKE;AVI_CAOFERRIS;PIVOT;PIVOT_LUMOD;PATHSEARCH")

  # PSD matrices and those algo does not seem to be a good idea
  SET_LCP_TEST_AS_FAILED("CPS_2;CPS_3" "NSQP;RPGS")

  # lcp_mmc is of size 26, way too much for enum
  RM_TEST2(SICONOS_LCP_ENUM "lcp_mmc.dat")
  # this LCP was put here to show that enum does not work on every LCP, likely
  # due to numerical problems, but works on some system ...
  RM_TEST2(SICONOS_LCP_ENUM "lcp_enum_fails.dat")

  # TODO backup path when GDESV fails
  SET(test-LCP_NEWTON_FBLSA-lcp_CPS_1_PROPERTIES WILL_FAIL TRUE)

  # special tests
  NEW_LCP_TEST(SICONOS_LCP_ENUM lcp_Pang_isolated_sol.dat)
  NEW_LCP_TEST(SICONOS_LCP_ENUM lcp_Pang_isolated_sol_perturbed.dat)
  SET(test-LCP_ENUM-lcp_Pang_isolated_sol_perturbed_PROPERTIES WILL_FAIL TRUE)
  NEW_LCP_TEST(SICONOS_LCP_ENUM lcp_inf_sol_perturbed.dat)

  # TODO refinment of solution
  # NEW_LCP_TEST(SICONOS_LCP_LEMKE lcp_tobenna.dat)
  # NEW_LCP_TEST(SICONOS_LCP_PIVOT lcp_tobenna.dat)
  #  NEW_LCP_TEST(SICONOS_LCP_PIVOT_LUMOD lcp_tobenna.dat)
  # LUMOD is not ready for prime time now
  SET(test-LCP_PIVOT_LUMOD-lcp_mmc_PROPERTIES WILL_FAIL TRUE)
  IF(DEV_MODE)
   SET(test-LCP_PIVOT-lcp_tobenna_PROPERTIES WILL_FAIL FALSE)
   #   SET(test-LCP_PIVOT_LUMOD-lcp_tobenna_PROPERTIES WILL_FAIL FALSE)
  ENDIF(DEV_MODE)

  IF(HAVE_PATHFERRIS)
   NEW_LCP_TEST(SICONOS_LCP_PATH lcp_tobenna.dat)
  ENDIF(HAVE_PATHFERRIS)
  IF(HAVE_GAMS_C_API)
   NEW_LCP_TEST(SICONOS_LCP_GAMS lcp_tobenna.dat)
  ENDIF(HAVE_GAMS_C_API)

  NEW_TEST(LCP_DefaultSolverOptionstest LinearComplementarity_DefaultSolverOptions_test.c)

  END_TEST(LCP/test)

  BEGIN_TEST2(src/Relay/test)

  SET(DATA_SET "relay1.dat;relay_2x2.dat;relay_4x4.dat;relay_simple2.dat;step_1x1.dat;step_2x2.dat;step_4x4.dat")
  SET(SICONOS_RELAY_SOLVERS "ENUM;LEMKE;PGS;AVI_CAOFERRIS")
  IF(HAS_ONE_LP_SOLVER)
   LIST(APPEND SICONOS_RELAY_SOLVERS "AVI_CAOFERRIS_TEST")
  ENDIF()

  IF(HAVE_PATHFERRIS)
   LIST(APPEND SICONOS_RELAY_SOLVERS "PATH")
  ENDIF()
  FOREACH(_DS ${DATA_SET})
    FOREACH(_SOLVER ${SICONOS_RELAY_SOLVERS})
      NEW_RELAY_TEST(SICONOS_RELAY_${_SOLVER} ${_DS})
    ENDFOREACH()
  ENDFOREACH()

  # ENUM on an LCP of size 30 is a bad idea ...
  RM_TEST2(RELAY_ENUM "relay1.dat")

  NEW_TEST(Relaytest1 relay_test1.c)
  NEW_TEST(Relaytest2 relay_test2.c)

  IF(HAVE_PATHFERRIS)
    NEW_TEST(Relaytest3 relay_test3.c)
  ENDIF(HAVE_PATHFERRIS)

  NEW_TEST(Relaytest10 relay_test10.c)
  NEW_TEST(Relaytest11 relay_test11.c)
  NEW_TEST(Relaytest12 relay_test12.c)
  NEW_TEST(Relaytest13 relay_test13.c)
  NEW_TEST(Relaytest20 relay_test20.c)
  NEW_TEST(Steptest1 step_test1.c)
  NEW_TEST(Steptest2 step_test2.c)
  NEW_TEST(Steptest3 step_test3.c)
  NEW_TEST(Steptest4 step_test4.c)

  END_TEST()


  BEGIN_TEST(src/MLCP/test)
  IF(HAVE_SYSTIMES_H AND WITH_CXX)
    NEW_TEST(MLCPtest main_mlcp.cpp)
  ENDIF(HAVE_SYSTIMES_H AND WITH_CXX)
  NEW_TEST(ReadWrite_MLCPtest MixedLinearComplementarity_ReadWrite_test.c)
  END_TEST()

  BEGIN_TEST(src/MCP/test)
  NEW_TEST(MCPtest MCP_test.c)
  NEW_TEST(MCPtest1 MCP_test1.c)
  END_TEST()

  BEGIN_TEST(src/NCP/test)
  SET(SICONOS_NCP_SOLVERS "NEWTON_FBLSA;NEWTON_MINFBLSA;PATHSEARCH")
  IF(HAVE_PATHFERRIS)
    LIST(APPEND SICONOS_NCP_SOLVERS "PATH")
  ENDIF(HAVE_PATHFERRIS)

  SET(SICONOS_NCP_TEST_PROBLEMS "NCP_ZI1")
  IF(DEV_MODE)
   LIST(APPEND SICONOS_NCP_TEST_PROBLEMS "NCP_ZIT1")
  ENDIF(DEV_MODE)

  FOREACH(_PB ${SICONOS_NCP_TEST_PROBLEMS})
   FOREACH(_SOLVER ${SICONOS_NCP_SOLVERS})
    NEW_NCP_TEST(${_PB} SICONOS_NCP_${_SOLVER})
   ENDFOREACH()
  ENDFOREACH()

  # Oliverie
  IF(NOT DEV_MODE)
   SET(NCP_NEWTON_FBLSA-NCP_ZI1_PROPERTIES WILL_FAIL TRUE)
   set_tests_properties(NCP_NEWTON_FBLSA-NCP_ZI1 PROPERTIES TIMEOUT 60)
  ENDIF(NOT DEV_MODE)

  END_TEST() # NCP

  BEGIN_TEST(src/FrictionContact/test)
  #===========================================
  # 3D Friction Contact tests
  #===========================================
  # (see FrictionContact/test/README for short details)
  # --> Must be uptodated!
  # Set name of input file used to generate c-files for tests
  SET(NSGS_TOL 1e-6)
  SET(NSGS_NB_IT 10000)
  NEW_TEST(FC3D_DefaultSolverOptionstest fc3d_DefaultSolverOptions_test.c)
  NEW_TEST(FC3D_sparse_test fc3d_sparse_test.c)

  STRING(CONCAT FC3D_DATA_SET "Capsules-i100-1090.dat;Capsules-i100-889.dat;Capsules-i101-404.dat;Capsules-i103-990.dat;Capsules-i122-1617.dat;")
  STRING(CONCAT FC3D_DATA_SET "FC3D_Example1.dat;Example1_Fc3D_SBM.dat;FrictionContact3D_1c.dat;FrictionContact3D_RR_1c.dat;")
  STRING(CONCAT FC3D_DATA_SET "NESpheres_10_1.dat;NESpheres_30_1.dat;")
  STRING(CONCAT FC3D_DATA_SET "Rover1039.dat;Rover1040.dat;Rover1041.dat;Rover11035.dat;Rover11211.dat;Rover3865.dat;Rover4144.dat;")
  STRING(CONCAT FC3D_DATA_SET "Rover4493.dat;Rover4516.dat;Rover4609.dat;Rover4613.dat;Rover4622.dat;Rover9770.dat;")
  STRING(CONCAT FC3D_DATA_SET "Confeti-ex13-Fc3D-SBM.dat;")

  foreach(_DAT ${FC3D_DATA_SET})
    # --- GAMS Solvers ---
    if(HAVE_GAMS_C_API)
      NEW_FC_3D_TEST(${_DAT} SICONOS_FRICTION_3D_GAMS_PATH)
      NEW_FC_3D_TEST(${_DAT} SICONOS_FRICTION_3D_GAMS_LCP_PATH)
      if(HAVE_GAMS_PATHVI)
	NEW_FC_3D_TEST(${_DAT} SICONOS_FRICTION_3D_GAMS_PATHVI)
	NEW_FC_3D_TEST(${_DAT} SICONOS_FRICTION_3D_GAMS_LCP_PATHVI)
      endif()
    endif()

    # --- NSGS on FC3D_DATA_SET ---
    NEW_FC_3D_TEST(${_DAT} SICONOS_FRICTION_3D_NSGS 1e-5 10000)

    NEW_FC_3D_TEST(${_DAT} SICONOS_FRICTION_3D_NSGS 1e-5 10000
      SICONOS_FRICTION_3D_ONECONTACT_NSN_GP 0 0
      INTERNAL_IPARAM 10 1)    

    NEW_FC_3D_TEST(${_DAT} SICONOS_FRICTION_3D_NSGS 1e-5 10000
      SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithLocalIteration 1e-12  10)
    
    NEW_FC_3D_TEST(${_DAT} SICONOS_FRICTION_3D_NSGS 1e-5 10000
      SICONOS_FRICTION_3D_ONECONTACT_NSN_GP 0 0
      INTERNAL_IPARAM SICONOS_FRICTION_3D_NSN_HYBRID_STRATEGY SICONOS_FRICTION_3D_NSN_HYBRID_STRATEGY_PLI_NSN_LOOP)

    # --- Nonsmooth Newton on FC3D_DATA_SET ---
    NEW_FC_3D_TEST(${_DAT} SICONOS_FRICTION_3D_NSN_AC 1e-5 1000
      0 0 0
      IPARAM 1 1)
     NEW_FC_3D_TEST(${_DAT} SICONOS_FRICTION_3D_NSN_AC_TEST 1e-5 1000
      0 0 0
      IPARAM 1 1)
    NEW_FC_3D_TEST(${_DAT} SICONOS_FRICTION_3D_NSN_AC 1e-3 1000)
    NEW_FC_3D_TEST(${_DAT} SICONOS_FRICTION_3D_NSN_AC_TEST 1e-3 1000)
    NEW_FC_3D_TEST(${_DAT} SICONOS_FRICTION_3D_NSN_FB 1e-3 1000)
    NEW_FC_3D_TEST(${_DAT} SICONOS_FRICTION_3D_NSN_NM 1e-3 1000)
  endforeach()


  
  # --- NSGS with different local solvers and parameters ---
  NEW_FC_3D_TEST(Example1_Fc3D_SBM.dat
    SICONOS_FRICTION_3D_NSGS 1e-16 ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnCone)
  
  NEW_FC_3D_TEST(Example1_Fc3D_SBM.dat
    SICONOS_FRICTION_3D_NSGS  1e-16 ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithDiagonalization)
 
  NEW_FC_3D_TEST(Example1_Fc3D_SBM.dat
    SICONOS_FRICTION_3D_NSGS 1e-16 ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithLocalIteration  1e-3 10)

  NEW_FC_3D_TEST(Example1_Fc3D_SBM.dat
    SICONOS_FRICTION_3D_NSGS  1e-16 ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithRegularization 0 0
    DPARAM 3 0.1)
    
  NEW_FC_3D_TEST(Example1_Fc3D_SBM.dat
    SICONOS_FRICTION_3D_NSGS  1e-16 ${NSGS_NB_IT}
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithLocalIteration 1e-3 10
    DPARAM 8 1.7
    IPARAM 8 1)

  # NEW_FC_3D_TEST(Example1_Fc3D_SBM.dat
  #   SICONOS_FRICTION_3D_NSGS  1e-16 1000
  #   SICONOS_FRICTION_3D_NCPGlockerFBNewton 0 0
  #   WILL_FAIL)

  NEW_FC_3D_TEST(Example1_Fc3D_SBM.dat
    SICONOS_FRICTION_3D_NSGS  1e-16 1000
    SICONOS_FRICTION_3D_NCPGlockerFBFixedPoint 0.0 10
    WILL_FAIL)

  NEW_FC_3D_TEST(Capsules-i122-1617.dat
    SICONOS_FRICTION_3D_NSGS  1e-07 1000000
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithLocalIteration 1e-16 20
    DPARAM 8 1.0
    IPARAM 8 1)

  NEW_FC_3D_TEST(Confeti-ex13-4contact-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_NSGS  1e-05 10000
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnCone 0.0 0
    DPARAM 8 1.0
    IPARAM 8 1)

  NEW_FC_3D_TEST(Confeti-ex13-4contact-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_NSGS  1e-12 10000
    SICONOS_FRICTION_3D_ONECONTACT_NSN 1e-18 10
    INTERNAL_IPARAM 1 0)
  
  NEW_FC_3D_TEST(Confeti-ex13-4contact-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_NSGS  1e-12 10000
    SICONOS_FRICTION_3D_ONECONTACT_NSN 1e-18 10
    INTERNAL_IPARAM 1 1)

  NEW_FC_3D_TEST(Confeti-ex13-4contact-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_NSGS  1e-12 10000
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithLocalIteration 1e-6 100)

  NEW_FC_3D_TEST(Confeti-ex13-4contact-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_NSGS  1e-12 10000
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithRegularization 0.0 0)

  NEW_FC_3D_TEST(problem-checkTwoRods1-condensed.dat
    SICONOS_FRICTION_3D_NSGS  1e-05 10000
    SICONOS_FRICTION_3D_ONECONTACT_NSN 0.0 0
    INTERNAL_IPARAM 1 1)
  NEW_FC_3D_TEST(FC3D_Example1.dat
    SICONOS_FRICTION_3D_NSGS  1e-5 ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_NSN 1e-18 10)
  NEW_FC_3D_TEST(Rover1039.dat
    SICONOS_FRICTION_3D_NSGS ${NSGS_TOL} ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_QUARTIC 1e-6 10)
  NEW_FC_3D_TEST(Rover1040.dat
    SICONOS_FRICTION_3D_NSGS ${NSGS_TOL} ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_QUARTIC 1e-6 10)
  NEW_FC_3D_TEST(Rover1041.dat
    SICONOS_FRICTION_3D_NSGS  ${NSGS_TOL} ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_QUARTIC 1e-6 10)
  NEW_FC_3D_TEST(Rover3865.dat 
    SICONOS_FRICTION_3D_NSGS ${NSGS_TOL} ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_QUARTIC 1e-6 10)
  NEW_FC_3D_TEST(Rover4144.dat
    SICONOS_FRICTION_3D_NSGS  ${NSGS_TOL} ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_QUARTIC 1e-6 10)
  NEW_FC_3D_TEST(Rover4396.dat
    SICONOS_FRICTION_3D_NSGS ${NSGS_TOL} ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_QUARTIC 1e-6 10)
  NEW_FC_3D_TEST(Rover4493.dat
    SICONOS_FRICTION_3D_NSGS ${NSGS_TOL} ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_QUARTIC 1e-6 10)
  NEW_FC_3D_TEST(Rover4516.dat
    SICONOS_FRICTION_3D_NSGS  ${NSGS_TOL} ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_QUARTIC 1e-6 10)
  NEW_FC_3D_TEST(Rover4609.dat
    SICONOS_FRICTION_3D_NSGS  ${NSGS_TOL} ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_QUARTIC 1e-6 10)
  NEW_FC_3D_TEST(Rover4613.dat
    SICONOS_FRICTION_3D_NSGS  ${NSGS_TOL} ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_QUARTIC 1e-6 10)
  NEW_FC_3D_TEST(Rover4622.dat
    SICONOS_FRICTION_3D_NSGS ${NSGS_TOL} ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_QUARTIC 1e-6 10)
  NEW_FC_3D_TEST(Rover9770.dat
    SICONOS_FRICTION_3D_NSGS ${NSGS_TOL} ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_QUARTIC 1e-6 10)
  NEW_FC_3D_TEST(Rover11035.dat
    SICONOS_FRICTION_3D_NSGS ${NSGS_TOL} ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_QUARTIC 1e-6 10)
  NEW_FC_3D_TEST(Rover11211.dat
    SICONOS_FRICTION_3D_NSGS ${NSGS_TOL} ${NSGS_NB_IT} 
    SICONOS_FRICTION_3D_ONECONTACT_QUARTIC 1e-6 10)
  NEW_FC_3D_TEST(Confeti-ex03-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_NSGS 1e-5 10000
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnCone 0.0 0
    WILL_FAIL)
  NEW_FC_3D_TEST(Confeti-ex03-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_NSGS 1e-12 1000
    SICONOS_FRICTION_3D_ONECONTACT_NSN 1e-16  10)

  NEW_FC_3D_TEST(Confeti-ex03-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_NSGS 1e-12 10000
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithLocalIteration 1e-12  10)

  NEW_FC_3D_TEST(Confeti-ex13-4contact-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_NSGS 1e-12 10000
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithRegularization 1e-8  10)

  NEW_FC_3D_TEST(Confeti-ex13-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_NSGS 1e-2 10000
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnCone 0.0 0)

  NEW_FC_3D_TEST(Confeti-ex13-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_NSGS 1e-5 1000
    SICONOS_FRICTION_3D_ONECONTACT_NSN 1e-16 10)

  NEW_FC_3D_TEST(Confeti-ex13-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_NSGS 1e-12 10000
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithLocalIteration 1e-06  100)

  NEW_FC_3D_TEST(Confeti-ex03-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_NSGS 1e-8 20000
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithLocalIteration 1e-16 100)
  
  NEW_FC_3D_TEST(FC3D_Example1_SBM.dat
    SICONOS_FRICTION_3D_NSGSV 1e-5 10000
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnCone_velocity 0 0
    INTERNAL_IPARAM 0 0
    INTERNAL_DPARAM 0 0.
    WILL_FAIL)
  
  # --- Extra-gradient ---

  NEW_FC_3D_TEST(Confeti-ex13-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_EG  1e-08 10000
    0 0 0
    DPARAM 3 -3e3)

  NEW_FC_3D_TEST(Confeti-ex13-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_EG  1e-10 10000
    0 0 0
    DPARAM 3 -1.0)

  NEW_FC_3D_TEST(FC3D_Example1_SBM.dat
    SICONOS_FRICTION_3D_EG  1e-8 100000
    0 0 0
    DPARAM 3 -1.0)

  NEW_FC_3D_TEST(FC3D_Example1_SBM.dat
    SICONOS_FRICTION_3D_EG  1e-8 100000
    0 0 0
    DPARAM 3 1.0)

  # --- Tresca Fixed Point ---
  NEW_FC_3D_TEST(Confeti-ex13-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_TFP)
 
  #TFP with ProjectedGradientOnCylinder is not working ...
  NEW_FC_3D_TEST(Confeti-ex13-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_TFP 1e-4 100
    SICONOS_FRICTION_3D_PGoC 1e-6 200
    WILL_FAIL)

  NEW_FC_3D_TEST(FC3D_Example1_SBM.dat
    SICONOS_FRICTION_3D_TFP 1e-16 100)


  
  NEW_FC_3D_TEST(Confeti-ex03-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_TFP 10e-8 2000)

  NEW_FC_3D_TEST(Confeti-ex03-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_TFP 10e-8 2000
    0 0 0
    IPARAM 1 1)

  NEW_FC_3D_TEST(FC3D_Example1_SBM.dat
    SICONOS_FRICTION_3D_TFP 0 0
    SICONOS_FRICTION_3D_PGoC 0 0
    WILL_FAIL)
  
  NEW_FC_3D_TEST(FC3D_Example1_SBM.dat
    SICONOS_FRICTION_3D_TFP 0 0
    SICONOS_FRICTION_3D_PGoC 0 0
    INTERNAL_IPARAM 2 20
    INTERNAL_DPARAM 3 -1.
    INTERNAL_DPARAM 4 -1.e-6)

  # ---- Hyperplane Projection ----
  # HP is not converging
  NEW_FC_3D_TEST(Confeti-ex13-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_HP 1e-3 1000
    0 0 0
    WILL_FAIL)

  NEW_FC_3D_TEST(FC3D_Example1_SBM.dat
    SICONOS_FRICTION_3D_HP)

  # ---- Varitionnal Inequalities formulation ----
  NEW_FC_3D_TEST(Confeti-ex13-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_VI_EG 1e-8 10000
    0 0 0
    DPARAM 3 -3e3)

  NEW_FC_3D_TEST(Confeti-ex13-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_VI_FPP 1e-8 100000
    0 0 0
    IPARAM 1 2
    IPARAM 2 0
    IPARAM 3 0
    DPARAM 3 -1e1)

  NEW_FC_3D_TEST(BoxesStack1-i100000-32.hdf5.dat
    SICONOS_FRICTION_3D_VI_FPP 1e-3 100000
    0 0 0
    IPARAM 2 1)

  NEW_FC_3D_TEST(BoxesStack1-i100000-32.hdf5.dat
    SICONOS_FRICTION_3D_FPP 1e-8 100000)

  NEW_FC_3D_TEST(BoxesStack1-i100000-32.hdf5.dat
    SICONOS_FRICTION_3D_VI_EG 1e-8 100000
    0 0 0
    IPARAM 2 1)

  # --- Test from rock pile simulations using "time of birth" feature --- 
  # failure in local solver with line search
  NEW_FC_3D_TEST(RockPile_tob1.dat SICONOS_FRICTION_3D_NSGS 1e-3 10000
    SICONOS_FRICTION_3D_ONECONTACT_NSN_GP 1e-16 100)
  #  an increasing number of newton iterations implies a failure
  NEW_FC_3D_TEST(RockPile_tob1.dat SICONOS_FRICTION_3D_NSGS 1e-3 10000
    SICONOS_FRICTION_3D_ONECONTACT_NSN_GP 1e-16 1000 WILL_FAIL )
  # removinf the line --search is worth
  NEW_FC_3D_TEST(RockPile_tob1.dat SICONOS_FRICTION_3D_NSGS 1e-3 2000
    SICONOS_FRICTION_3D_ONECONTACT_NSN 1e-16 100 WILL_FAIL)

  # ---- PROX ---
  
  NEW_FC_3D_TEST(FC3D_Example1_SBM.dat
    SICONOS_FRICTION_3D_PROX 1e-8 100)
  

  NEW_FC_3D_TEST(OneObject-i1028-138.hdf5.dat
    SICONOS_FRICTION_3D_PROX  1e-8 100000
    0 0 0
    DPARAM 3 1e4
    IPARAM 1 1)

  # --------------------------------------- #
  ### problems known as difficult
  # --------------------------------------- #
  # KaplasTower-i1061-4.hdf5.dat

  
  NEW_FC_3D_TEST(KaplasTower-i1061-4.hdf5.dat SICONOS_FRICTION_3D_NSGS 1e-5 2000
    SICONOS_FRICTION_3D_ONECONTACT_NSN_GP 0 0 WILL_FAIL)
  NEW_FC_3D_TEST(KaplasTower-i1061-4.hdf5.dat SICONOS_FRICTION_3D_NSGS 1e-5 1500
    SICONOS_FRICTION_3D_ONECONTACT_NSN_GP 0 0
    INTERNAL_IPARAM 10 1
    WILL_FAIL)
  NEW_FC_3D_TEST(KaplasTower-i1061-4.hdf5.dat SICONOS_FRICTION_3D_NSGS 1e-5 1500
    SICONOS_FRICTION_3D_ONECONTACT_NSN_GP 0 0
    INTERNAL_IPARAM SICONOS_FRICTION_3D_NSN_HYBRID_STRATEGY SICONOS_FRICTION_3D_NSN_HYBRID_STRATEGY_PLI_NSN_LOOP
    WILL_FAIL)
  
  NEW_FC_3D_TEST(KaplasTower-i1061-4.hdf5.dat SICONOS_FRICTION_3D_NSN_AC 5e-2 1000)
  NEW_FC_3D_TEST(KaplasTower-i1061-4.hdf5.dat SICONOS_FRICTION_3D_NSN_AC_TEST 5e-2 1000)
  NEW_FC_3D_TEST(KaplasTower-i1061-4.hdf5.dat SICONOS_FRICTION_3D_NSN_FB 5e-2 1000)
  NEW_FC_3D_TEST(KaplasTower-i1061-4.hdf5.dat SICONOS_FRICTION_3D_NSN_NM 5e-2 1000)


  NEW_FC_3D_TEST(KaplasTower-i1061-4.hdf5.dat
    SICONOS_FRICTION_3D_PROX  1e-3 10
    0 0 0
    DPARAM 3 1e4
    IPARAM 1 1)

  # OneObject-i100000-499.hdf5.dat
  NEW_FC_3D_TEST(OneObject-i100000-499.hdf5.dat
    SICONOS_FRICTION_3D_NSGS 1e-5 100000
    SICONOS_FRICTION_3D_ONECONTACT_NSN_GP 0 0
    WILL_FAIL)
  NEW_FC_3D_TEST(OneObject-i100000-499.hdf5.dat SICONOS_FRICTION_3D_NSGS 1e-5 10000
    SICONOS_FRICTION_3D_ONECONTACT_NSN_GP 0 0
    INTERNAL_IPARAM 10 1
    WILL_FAIL)
  NEW_FC_3D_TEST(OneObject-i100000-499.hdf5.dat SICONOS_FRICTION_3D_NSGS 1e-5 10000
    SICONOS_FRICTION_3D_ONECONTACT_NSN_GP 0 0
    INTERNAL_IPARAM SICONOS_FRICTION_3D_NSN_HYBRID_STRATEGY SICONOS_FRICTION_3D_NSN_HYBRID_STRATEGY_PLI_NSN_LOOP
    WILL_FAIL)
  NEW_FC_3D_TEST(OneObject-i100000-499.hdf5.dat SICONOS_FRICTION_3D_NSN_AC 1e-5 100
    0 0 0
    IPARAM 1 1)   
   NEW_FC_3D_TEST(OneObject-i100000-499.hdf5.dat SICONOS_FRICTION_3D_NSN_AC_TEST 1e-5 100
    0 0 0
    IPARAM 1 1)   

  NEW_FC_3D_TEST(OneObject-i100000-499.hdf5.dat SICONOS_FRICTION_3D_NSN_AC 1e-3 1000)
  NEW_FC_3D_TEST(OneObject-i100000-499.hdf5.dat SICONOS_FRICTION_3D_NSN_AC_TEST 1e-3 1000)
  NEW_FC_3D_TEST(OneObject-i100000-499.hdf5.dat SICONOS_FRICTION_3D_NSN_FB 1e-3 1000)
  NEW_FC_3D_TEST(OneObject-i100000-499.hdf5.dat SICONOS_FRICTION_3D_NSN_NM 1e-3 1000)
  NEW_FC_3D_TEST(OneObject-i100000-499.hdf5.dat
    SICONOS_FRICTION_3D_PROX  1e-8 100000
    0 0 0
    DPARAM 3 1e4
    IPARAM 1 1)
  NEW_FC_3D_TEST(OneObject-i100000-499.hdf5.dat
    SICONOS_FRICTION_3D_TFP 1e-8 100
    0 0 0
    DPARAM 3 1e4
    WILL_FAIL)

  # BoxesStack1-i100000-32.hdf5.dat
  # NEW_FC_3D_TEST(BoxesStack1-i100000-32.hdf5.dat
  #   SICONOS_FRICTION_3D_NSGS 1e-5 100000
  #   SICONOS_FRICTION_3D_ONECONTACT_NSN_GP 0 0
  #   WILL_FAIL)
  NEW_FC_3D_TEST(BoxesStack1-i100000-32.hdf5.dat SICONOS_FRICTION_3D_NSGS 1e-5 10000
    SICONOS_FRICTION_3D_ONECONTACT_NSN_GP 0 0
    INTERNAL_IPARAM 10 1
    WILL_FAIL)
  NEW_FC_3D_TEST(BoxesStack1-i100000-32.hdf5.dat SICONOS_FRICTION_3D_NSGS 1e-5 10000
    SICONOS_FRICTION_3D_ONECONTACT_NSN_GP 0 0
    INTERNAL_IPARAM SICONOS_FRICTION_3D_NSN_HYBRID_STRATEGY SICONOS_FRICTION_3D_NSN_HYBRID_STRATEGY_PLI_NSN_LOOP
    WILL_FAIL)
  NEW_FC_3D_TEST(BoxesStack1-i100000-32.hdf5.dat SICONOS_FRICTION_3D_NSN_AC 1e-5 500
    0 0 0
    IPARAM 1 1)   
   NEW_FC_3D_TEST(BoxesStack1-i100000-32.hdf5.dat SICONOS_FRICTION_3D_NSN_AC_TEST 1e-5 500
    0 0 0
    IPARAM 1 1)   

  NEW_FC_3D_TEST(BoxesStack1-i100000-32.hdf5.dat SICONOS_FRICTION_3D_NSN_AC 1e-3 1000)
  NEW_FC_3D_TEST(BoxesStack1-i100000-32.hdf5.dat SICONOS_FRICTION_3D_NSN_AC_TEST 1e-3 1000)
  NEW_FC_3D_TEST(BoxesStack1-i100000-32.hdf5.dat SICONOS_FRICTION_3D_NSN_FB 1e-3 1000)
  NEW_FC_3D_TEST(BoxesStack1-i100000-32.hdf5.dat SICONOS_FRICTION_3D_NSN_NM 1e-3 1000)
  NEW_FC_3D_TEST(BoxesStack1-i100000-32.hdf5.dat
    SICONOS_FRICTION_3D_PROX  1e-8 100000
    0 0 0
    DPARAM 3 1e4
    IPARAM 1 1)
  NEW_FC_3D_TEST(BoxesStack1-i100000-32.hdf5.dat
    SICONOS_FRICTION_3D_TFP 1e-8 100
    0 0 0
    DPARAM 3 1e4
    WILL_FAIL)


  # Rover4396.dat
  NEW_FC_3D_TEST(Rover4396.dat SICONOS_FRICTION_3D_NSGS 1e-5 10000
    SICONOS_FRICTION_3D_ONECONTACT_NSN_GP 0 0
    WILL_FAIL)
    
  NEW_FC_3D_TEST(Rover4396.dat SICONOS_FRICTION_3D_NSGS 1e-5 10000
    SICONOS_FRICTION_3D_ONECONTACT_NSN_GP 0 0
    INTERNAL_IPARAM 10 1)    
  
  NEW_FC_3D_TEST(Rover4396.dat SICONOS_FRICTION_3D_NSGS 1e-5 10000
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithLocalIteration 1e-12  10)
  
  NEW_FC_3D_TEST(Rover4396.dat SICONOS_FRICTION_3D_NSGS 1e-5 10000
    SICONOS_FRICTION_3D_ONECONTACT_NSN_GP 0 0
    INTERNAL_IPARAM SICONOS_FRICTION_3D_NSN_HYBRID_STRATEGY SICONOS_FRICTION_3D_NSN_HYBRID_STRATEGY_PLI_NSN_LOOP WILL_FAIL)
  NEW_FC_3D_TEST(Rover4396.dat SICONOS_FRICTION_3D_NSN_AC 1e-5 1000
    0 0 0
    IPARAM 1 1)   
  NEW_FC_3D_TEST(Rover4396.dat SICONOS_FRICTION_3D_NSN_AC 1e-3 1000)
  NEW_FC_3D_TEST(Rover4396.dat SICONOS_FRICTION_3D_NSN_FB 1e-3 1000)
  NEW_FC_3D_TEST(Rover4396.dat SICONOS_FRICTION_3D_NSN_NM 1e-3 1000)
  
  
  # --- LMGC driver ---

  NEW_TEST(FC3DNewFromFortranData fc3d_newFromFortranData.c)
  NEW_TEST(FC3DLmgcDriver1 fc3d_LmgcDriver_test1.c)
  NEW_TEST(FC3DLmgcDriver2 fc3d_LmgcDriver_test2.c)
  NEW_TEST(FC3DLmgcDriver3 fc3d_LmgcDriver_test3.c)

  NEW_TEST(FC3DLmgcDriver4 fc3d_LmgcDriver_test4.c)

  NEW_TEST(FC3DLmgcDriver5 fc3d_LmgcDriver_test5.c)

  # --- DeSaxce Fixed Point ---
  NEW_FC_3D_TEST(BoxesStack1-i100000-32.hdf5.dat
    SICONOS_FRICTION_3D_DSFP 1e-3 100000
    0 0 0
    DPARAM 3 8e-4)

  NEW_FC_3D_TEST(Confeti-ex03-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_DSFP 0 0
    0 0 0
    DPARAM 3 1e2)

  NEW_FC_3D_TEST(Confeti-ex13-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_DSFP  1e-08 10000
    0 0 0
    DPARAM 3 5e3)

  NEW_FC_3D_TEST(FC3D_Example1_SBM.dat
    SICONOS_FRICTION_3D_DSFP  1e-8 100000
    0 0 0
    DPARAM 3 2.0)
  
  # --- AC Fixed Point ---
  NEW_FC_3D_TEST(Confeti-ex03-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_ACLMFP 1e-8 200)
  NEW_FC_3D_TEST(Confeti-ex03-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_ACLMFP 1e-8 200
    0 0 0
    IPARAM 1 1)

  # --- Second Order Cone formulation ---
  NEW_FC_3D_TEST(Confeti-ex03-Fc3D-SBM.dat
    SICONOS_FRICTION_3D_SOCLCP 0 0
    0 1e-8 20000)

  # --- Quartic ---
  NEW_FC_3D_TEST(FrictionContact3D_1c.dat SICONOS_FRICTION_3D_ONECONTACT_QUARTIC)
  NEW_FC_3D_TEST(FrictionContact3D_RR_1c.dat SICONOS_FRICTION_3D_ONECONTACT_QUARTIC)

  # ---------------------------------------------------	
  # --- Global friction contact problem formulation ---
  # ---------------------------------------------------

  # Example 0
  NEW_GFC_3D_TEST(GFC3D_Example0.dat SICONOS_GLOBAL_FRICTION_3D_NSGS)
  NEW_GFC_3D_TEST(GFC3D_Example0.dat SICONOS_GLOBAL_FRICTION_3D_NSGS 0 0
    SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnCone 0 0
    INTERNAL_IPARAM 0 0
    INTERNAL_DPARAM 0 0.)
  NEW_GFC_3D_TEST(GFC3D_Example0.dat SICONOS_GLOBAL_FRICTION_3D_NSGS_WR)
  NEW_GFC_3D_TEST(GFC3D_Example0.dat SICONOS_GLOBAL_FRICTION_3D_PROX_WR)
  NEW_GFC_3D_TEST(GFC3D_Example0.dat SICONOS_GLOBAL_FRICTION_3D_DSFP_WR)
  NEW_GFC_3D_TEST(GFC3D_Example0.dat SICONOS_GLOBAL_FRICTION_3D_NSGSV_WR 0 0
    0 0 0
    WILL_FAIL)
  NEW_GFC_3D_TEST(GFC3D_Example0.dat SICONOS_GLOBAL_FRICTION_3D_TFP_WR)
  NEW_GFC_3D_TEST(GFC3D_Example0.dat SICONOS_GLOBAL_FRICTION_3D_VI_EG 0 0 0 0 0 WILL_FAIL)
  NEW_GFC_3D_TEST(GFC3D_Example0.dat SICONOS_GLOBAL_FRICTION_3D_VI_FPP 0 0 0 0 0 WILL_FAIL)

  
  # Example 0 SBM
  NEW_GFC_3D_TEST(GFC3D_Example0_SBM.dat SICONOS_GLOBAL_FRICTION_3D_NSGS)

  # Example 1
  NEW_GFC_3D_TEST(GFC3D_Example1.dat SICONOS_GLOBAL_FRICTION_3D_NSGS_WR 0 0
    0 0 0
    INTERNAL_IPARAM 0 2000)
  NEW_GFC_3D_TEST(GFC3D_Example1.dat SICONOS_GLOBAL_FRICTION_3D_NSN_AC 0 0 0 0 0 WILL_FAIL)
  NEW_GFC_3D_TEST(GFC3D_Example1.dat SICONOS_GLOBAL_FRICTION_3D_VI_EG 0 0 0 0 0 )
  NEW_GFC_3D_TEST(GFC3D_Example1.dat SICONOS_GLOBAL_FRICTION_3D_VI_FPP 0 0 0 0 0)
  NEW_GFC_3D_TEST(GFC3D_Example1.dat SICONOS_GLOBAL_FRICTION_3D_NSGS 0 0 0 0 0 WILL_FAIL)

  # Example 2
  NEW_GFC_3D_TEST(GFC3D_Example2.dat SICONOS_GLOBAL_FRICTION_3D_NSGS_WR)

  # Example OneContact			     
  NEW_GFC_3D_TEST(GFC3D_OneContact.dat SICONOS_GLOBAL_FRICTION_3D_NSGS_WR)

  # Example TwoRods1
  NEW_GFC_3D_TEST(GFC3D_TwoRods1.dat SICONOS_GLOBAL_FRICTION_3D_NSN_AC_WR 0 0
    0 0 0
    INTERNAL_IPARAM 0 1000
    INTERNAL_DPARAM 0 1e-10)
  NEW_GFC_3D_TEST(GFC3D_TwoRods1.dat SICONOS_GLOBAL_FRICTION_3D_NSGS)
  NEW_GFC_3D_TEST(GFC3D_TwoRods1.dat SICONOS_GLOBAL_FRICTION_3D_NSGS_WR)

  # Alart Curnier functions
  NEW_TEST(AlartCurnierFunctions_test fc3d_AlartCurnierFunctions_test.c)

  # 
  if(WITH_FCLIB)
    NEW_TEST(FCLIB_test1 fc3d_writefclib_local_test.c)
    NEW_GFC_3D_TEST_HDF5(LMGC_GFC3D_CubeH8.hdf5 SICONOS_GLOBAL_FRICTION_3D_NSGS)
    NEW_GFC_3D_TEST_HDF5(LMGC_GlobalFrictionContactProblem00046.hdf5 SICONOS_GLOBAL_FRICTION_3D_NSN_AC)
    NEW_GFC_3D_TEST_HDF5(LMGC_GlobalFrictionContactProblem00046.hdf5 SICONOS_GLOBAL_FRICTION_3D_VI_EG)
    NEW_GFC_3D_TEST_HDF5(LMGC_GlobalFrictionContactProblem00046.hdf5 SICONOS_GLOBAL_FRICTION_3D_NSGS_WR)
  endif()
  
  #===========================================
  # 2D Friction Contact tests
  #===========================================
  ## test 2D dense on two differents files

  NEW_FC_2D_TEST(FrictionContactProblem00374.dat SICONOS_FRICTION_2D_NSGS)
  NEW_FC_2D_TEST(FrictionContactProblem00374.dat SICONOS_FRICTION_2D_CPG)
  NEW_FC_2D_TEST(FrictionContactProblem00374.dat SICONOS_FRICTION_2D_LATIN)
  NEW_FC_2D_TEST(FrictionContactProblem00394.dat SICONOS_FRICTION_2D_NSGS)
  NEW_FC_2D_TEST(FrictionContactProblem00394.dat SICONOS_FRICTION_2D_CPG)
  NEW_FC_2D_TEST(FrictionContactProblem00394.dat SICONOS_FRICTION_2D_LATIN)

  ## test 2D sparse on 4 differents files
  NEW_FC_2D_TEST(FrictionContactProblem00727.dat SICONOS_FRICTION_2D_NSGS 1e-12 5000)
  NEW_FC_2D_TEST(FrictionContactProblem00031.dat SICONOS_FRICTION_2D_NSGS 1e-12 5000)
  NEW_FC_2D_TEST(FrictionContactProblem00071.dat SICONOS_FRICTION_2D_NSGS 1e-12 5000)
  NEW_FC_2D_TEST(FrictionContactProblem00237.dat SICONOS_FRICTION_2D_NSGS 1e-12 5000)

  NEW_FC_2D_TEST(FC2D_SliderCrankLagrangian00000.dat SICONOS_FRICTION_2D_LEMKE)
  NEW_FC_2D_TEST(FrictionContactProblem00374.dat SICONOS_FRICTION_2D_LEMKE)
  NEW_FC_2D_TEST(FC2D_SliderCrankLagrangian00001.dat SICONOS_FRICTION_2D_LEMKE 0 0
    0 0 0 WILL_FAIL)

  NEW_FC_2D_TEST(FC2D_SliderCrankLagrangian00000.dat SICONOS_FRICTION_2D_ENUM)
  NEW_FC_2D_TEST(FC2D_SliderCrankLagrangian00001.dat SICONOS_FRICTION_2D_ENUM)

 
 END_TEST()



  

  
  BEGIN_TEST(src/GenericMechanical/test)

  # Warning. Only test GMP4 GMP5 have fc3d problem inside

  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP0.dat)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP1.dat)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP2.dat)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP3.dat)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP4.dat)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP5.dat)
  SET(test-GMP-REDUCED0_3D_ONECONTACT_QUARTIC-GMP6_PROPERTIES WILL_FAIL TRUE)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP6.dat)

  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_NSN_GP GMP0.dat)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_NSN_GP GMP1.dat)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_NSN_GP GMP2.dat)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_NSN_GP GMP3.dat)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_NSN_GP GMP4.dat)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_NSN_GP GMP5.dat)

  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_NSN GMP4.dat)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_NSN GMP5.dat)

  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithLocalIteration GMP4.dat)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithLocalIteration GMP5.dat)
  
  IF(HAS_LAPACK_DGESVD)
    NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP0.dat 0 0 0 0 0 1)
    NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP1.dat 0 0 0 0 0 1)
    NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP2.dat 0 0 0 0 0 1)
    NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP3.dat 0 0 0 0 0 1)
    NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP4.dat 0 0 0 0 0 1)
    NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP5.dat 0 0 0 0 0 1)
#    SET(test-GMP-REDUCED1_3D_QUARTIC-GMP6_PROPERTIES WILL_FAIL TRUE)
    NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP6.dat 0 0 0 0 0 1)
  endif()
  
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP0.dat 0 0 0 0 0 2)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP1.dat 0 0 0 0 0 2)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP2.dat 0 0 0 0 0 2)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP3.dat 0 0 0 0 0 2)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP4.dat 0 0 0 0 0 2)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP5.dat 0 0 0 0 0 2)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP6.dat 0 0 0 0 0 2)
  
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP0.dat 0 0 0 0 0 3)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP1.dat 0 0 0 0 0 3)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP2.dat 0 0 0 0 0 3)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP3.dat 0 0 0 0 0 3)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_QUARTIC GMP6.dat 0 0 0 0 0 3)

  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_NSN_GP GMP4.dat 0 0 0 0 0 2)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_NSN_GP GMP5.dat 0 0 0 0 0 2)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_NSN_GP GMP6.dat 0 0 0 0 0 2)

  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_NSN GMP4.dat 0 0 0 0 0 2)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_NSN GMP5.dat 0 0 0 0 0 2)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_NSN GMP6.dat 0 0 0 0 0 2)

  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithLocalIteration GMP4.dat 0 0 0 0 0 2)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithLocalIteration GMP5.dat 0 0 0 0 0 2)
  NEW_GMP_TEST(SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithLocalIteration GMP6.dat 0 0 0 0 0 2)





  END_TEST()
  #BEGIN_TEST(src/GenericMechanical/test)
  #NEW_TEST(GMP_FAILED GenericMechanical_test1.c)
  #END_TEST()


  # === Variationnal inequalities tests ===

  BEGIN_TEST(src/VI/test)
  NEW_TEST(VI_test0 VI_test.c)
  NEW_TEST(VI_test1 VI_test1.c)
  NEW_TEST(VI_test2 VI_test2.c)
  NEW_TEST(VI_test3 VI_test3.c)
  NEW_TEST(VI_test5 VI_test5.c)
  NEW_TEST(VI_testFC3D1 VI_testFC3D1.c)
  NEW_TEST(VI_testFC3D2 VI_testFC3D2.c)
  NEW_TEST(VI_testFC3D3 VI_testFC3D3.c)
  SET(VI_testFC3D3_PROPERTIES WILL_FAIL TRUE)


  SET(SICONOS_VI_SOLVERS "BOX_QI;BOX_AVI_LSA")
  IF(HAVE_PATHFERRIS)
   LIST(APPEND SICONOS_VI_SOLVERS "BOX_PATH")
  ENDIF(HAVE_PATHFERRIS)

  IF(DEV_MODE)
   SET(SICONOS_VI_TEST_PROBLEMS "VI_ZI1;VI_ZIT1")
  ENDIF(DEV_MODE)

  FOREACH(_PB ${SICONOS_VI_TEST_PROBLEMS})
   FOREACH(_SOLVER ${SICONOS_VI_SOLVERS})
    NEW_NCP_TEST(${_PB} SICONOS_VI_${_SOLVER})
   ENDFOREACH()
  ENDFOREACH()
 END_TEST()

  BEGIN_TEST(src/AVI/test)

  IF(HAS_ONE_LP_SOLVER)
   NEW_TEST(AVI_twisting implicit_twisting.c)
  ENDIF(HAS_ONE_LP_SOLVER)

  END_TEST(AVI/test)


  BEGIN_TEST(src/SOCP/test)
    NEW_TEST(SOCLCP_test1 soclcp_test1.c)
    NEW_TEST(SOCLCP_test2 soclcp_test2.c)
    NEW_TEST(SOCLCP_test3 soclcp_test3.c)
    # timeout on all machines, see
    # http://cdash-bipop.inrialpes.fr/testSummary.php?project=1&name=SOCLCP_test4&date=2015-09-03
    # Feel free to remove this once it is fixed --xhub
    #NEW_TEST(SOCLCP_test4 soclcp_test4.c)
    #NEW_TEST(SOCLCP_test5 soclcp_test5.c)
    NEW_TEST(SOCLCP_fc3d_to_soclcp  fc3d_to_soclcp.c)
  END_TEST(SOCP/test)

  add_library(numerics-test SHARED ${TEST_UTILS_SOURCES})
  set_target_properties("numerics-test" PROPERTIES
   LINKER_LANGUAGE "C")
  include(WindowsLibrarySetup)
  windows_library_extra_setup("numerics-test" "numerics-test")
  target_link_libraries(numerics-test ${PRIVATE} ${COMPONENT})
  target_link_libraries(numerics-test ${PRIVATE} ${${COMPONENT}_LINK_LIBRARIES})
endif()
