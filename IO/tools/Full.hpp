SICONOS_IO_REGISTER_WITH_BASES(NewtonEulerFrom1DLocalFrameR, (NewtonEulerR),
                               (_isOnContact)
                               (_Pc1)
                               (_Pc2)
                               (_Nc)
                               (_Mabs_C)
                               (_NPG1)
                               (_NPG2)
                               (_AUX1)
                               (_AUX2))
SICONOS_IO_REGISTER_WITH_BASES(BlockVector, (SiconosVector),
                               (_sizeV)
                               (vect)
                               (_tabIndex))
SICONOS_IO_REGISTER_WITH_BASES(SensorPosition, (Sensor),
                               (_nSteps)
                               (_dataPlot)
                               (_k))
SICONOS_IO_REGISTER(NonSmoothDynamicalSystem,
                    (BVP)
                    (_topology)
                    (mIsLinear))
SICONOS_IO_REGISTER(Relation,
                    (_pluginh)
                    (_pluginJachx)
                    (_pluginJachlambda)
                    (_pluging)
                    (_pluginJacLg)
                    (_pluginf)
                    (_plugine)
                    (relationType)
                    (subType)
                    (_interaction)
                    (data)
                    (_workR)
                    (_workX)
                    (_workXdot)
                    (_workZ)
                    (_workY)
                    (_workL)
                    (_Residuy)
                    (_h_alpha)
                    (_jachlambda))
SICONOS_IO_REGISTER(ControlManager,
                    (_allSensors)
                    (_allActuators)
                    (_model))
SICONOS_IO_REGISTER_WITH_BASES(NewtonImpactNSL, (NonSmoothLaw),
                               (_e))
SICONOS_IO_REGISTER_WITH_BASES(NewtonEulerDS, (DynamicalSystem),
                               (_v)
                               (_v0)
                               (_vMemory)
                               (_qMemory)
                               (_forcesMemory)
                               (_dotqMemory)
                               (_qDim)
                               (_q)
                               (_deltaq)
                               (_q0)
                               (_dotq)
                               (_MObjToAbs)
                               (_I)
                               (_mass)
                               (_massMatrix)
                               (_luW)
                               (_T)
                               (_p)
                               (_mExt)
                               (_fExt)
                               (_forces)
                               (_jacobianvFL)
                               (_jacobianqDotForces)
                               (computeFIntPtr)
                               (computeJacobianFIntqPtr)
                               (computeJacobianFIntqDotPtr))
SICONOS_IO_REGISTER_WITH_BASES(PrimalFrictionContact, (LinearOSNS),
                               (_contactProblemDim)
                               (_sizeLocalOutput)
                               (_localVelocity)
                               (_localReaction)
                               (_tildeLocalVelocity)
                               (H)
                               (_mu)
                               (primalFrictionContact_driver))
SICONOS_IO_REGISTER(OSNSMatrix,
                    (dimRow)
                    (dimColumn)
                    (storageType)
                    (DSBlocksPositions)
                    //  (numericsMat)
                    (M1)
                    (Mt)
                    (M2))
SICONOS_IO_REGISTER_WITH_BASES(RelayNSL, (NonSmoothLaw),
                               (_lb)
                               (_ub))
SICONOS_IO_REGISTER_WITH_BASES(MixedComplementarityConditionNSL, (NonSmoothLaw),
                               (EqualitySize))
SICONOS_IO_REGISTER(UnitaryRelation,
                    (_mainInteraction)
                    (_relativePosition)
                    (_number)
                    (_absolutePosition)
                    (_absolutePositionProj)
                    (_workX)
                    (_workXq)
                    (_workFree)
                    (_workYp)
                    (_workZ))
SICONOS_IO_REGISTER_WITH_BASES(SensorEvent, (Event),
                               (_sensor))
SICONOS_IO_REGISTER(OneStepIntegrator,
                    (integratorType)
                    (OSIDynamicalSystems)
                    (OSIInteractions)
                    (_sizeMem)
                    (simulationLink))
SICONOS_IO_REGISTER_WITH_BASES(MLCP, (LinearOSNS),
                               (_n)
                               (_m)
                               (_curBlock)
                               //  (_numerics_problem)
                              )
SICONOS_IO_REGISTER_WITH_BASES(FrictionContact, (LinearOSNS),
                               (_contactProblemDim)
                               (_mu)
                               (_frictionContact_driver)
                               //  (_numerics_problem)
                              )
SICONOS_IO_REGISTER_WITH_BASES(QP, (OneStepNSProblem),
                               (Q)
                               (_p))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianR, (Relation),
                               (_jachq)
                               (_jachqDot))
SICONOS_IO_REGISTER_WITH_BASES(SchatzmanPaoli, (OneStepIntegrator),
                               (WMap)
                               (_WBoundaryConditionsMap)
                               (_theta)
                               (_gamma)
                               (_useGamma)
                               (_useGammaForRelation))
SICONOS_IO_REGISTER(SiconosMatrix,
                    (dimRow)
                    (dimCol)
                    (num))
SICONOS_IO_REGISTER(BlockCSRMatrix,
                    (nr)
                    (nc)
                    //  (numericsMatSparse)
                    //  (MBlockCSR)
                    (diagSizes)
                    (rowPos)
                    (colPos))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianLinearTIR, (LagrangianR),
                               (_F)
                               (_e))
SICONOS_IO_REGISTER_WITH_BASES(NewtonImpactFrictionNSL, (NonSmoothLaw),
                               (_en)
                               (_et)
                               (_mu))
SICONOS_IO_REGISTER_WITH_BASES(LCP, (LinearOSNS),
                               //  (_numerics_problem)
                              )
SICONOS_IO_REGISTER_WITH_BASES(NewtonEulerR, (Relation),
                               (_ysize)
                               (_xsize)
                               (_qsize)
                               (_workQ)
                               (_jachq)
                               (_jachqDot)
                               (_jachlambda)
                               (_e)
                               (_yProj)
                               (_contactForce)
                               (_jachqT))
SICONOS_IO_REGISTER_WITH_BASES(EventDriven, (Simulation),
                               (istate)
                               (TOL_ED))
SICONOS_IO_REGISTER(OneStepNSProblem,
                    (_numerics_solver_id)
                    (_numerics_solver_options)
                    (_id)
                    (_sizeOutput)
                    (_DSBlocks)
                    (_simulation)
                    (_OSNSInteractions)
                    (_levelMin)
                    (_levelMax)
                    (_maxSize)
                    (_CPUtime)
                    (_nbIter)
                    (_numerics_options)
                    (_hasBeUpdated))
SICONOS_IO_REGISTER_WITH_BASES(TimeStepping, (Simulation),
                               (_computeResiduY)
                               (_computeResiduR)
                               (_newtonTolerance)
                               (_newtonMaxIteration)
                               (_newtonNbSteps)
                               (_newtonResiduDSMax)
                               (_newtonResiduYMax)
                               (_newtonResiduRMax)
                               (_newtonOptions))
SICONOS_IO_REGISTER(Interaction,
                    (_initialized)
                    (_id)
                    (_number)
                    (_relativeDegree)
                    (_lowerLevelForOutput)
                    (_upperLevelForOutput)
                    (_lowerLevelForInput)
                    (_upperLevelForInput)
                    (_interactionSize)
                    (_numberOfRelations)
                    (_sizeOfDS)
                    (_sizeZ)
                    (_y)
                    (_yOld)
                    (_y_k)
                    (_yMemory)
                    (_steps)
                    (_lambda)
                    (_lambdaOld)
                    (_involvedDS)
                    (_nslaw)
                    (_relation))
SICONOS_IO_REGISTER(DynamicalSystem,
                    (_number)
                    (_n)
                    (_x0)
                    (_residuFree)
                    (_r)
                    (_normRef)
                    (_x)
                    (_jacxRhs)
                    (_jacgx)
                    (_jacxDotG)
                    (_z)
                    (_g)
                    (_pluging)
                    (_pluginJacgx)
                    (_pluginJacxDotG)
                    (_xMemory)
                    (_stepsInMemory)
                    (_workV)
                    (_workMatrix)
                    (_workFree)
                    (count))
SICONOS_IO_REGISTER(Sensor,
                    (_type)
                    (_id)
                    (_data)
                    (_model)
                    (_timeDiscretisation)
                    (_eSensor))
SICONOS_IO_REGISTER(Topology,
                    (_allInteractions)
                    (_DSG)
                    (_URG)
                    (_isTopologyUpToDate)
                    (_hasChanged)
                    (_numberOfConstraints)
                    (_symmetric))
SICONOS_IO_REGISTER(Actuator,
                    (_type)
                    (_id)
                    (_allSensors)
                    (_allDS)
                    (_model)
                    (_timeDiscretisation)
                    (_eActuator))
SICONOS_IO_REGISTER(SiconosException,
                    (reportMsg))
SICONOS_IO_REGISTER(SiconosMemory,
                    (_maxSize)
                    (_nbVectorsInMemory)
                    (_vectorMemory))
SICONOS_IO_REGISTER(Simulation,
                    (_name)
                    (_timeDiscretisation)
                    (_eventsManager)
                    (_tinit)
                    (_tend)
                    (_tout)
                    (_allOSI)
                    (_osiMap)
                    (_allNSProblems)
                    (_model)
                    (_levelMinForOutput)
                    (_levelMaxForOutput)
                    (_levelMinForInput)
                    (_levelMaxForInput)
                    (_tolerance)
                    (_printStat)
                    (_staticLevels)
                    (_levelsAreComputed)
                    (statOut)
                    (_useRelativeConvergenceCriterion)
                    (_relativeConvergenceCriterionHeld)
                    (_relativeConvergenceTol))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianLinearTIDS, (LagrangianDS),
                               (_K)
                               (_C))
SICONOS_IO_REGISTER_WITH_BASES(GenericMechanical, (LinearOSNS),
                               (_pnumerics_GMP))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianScleronomousR, (LagrangianR),
                               (_pluginjqh)
                               (_pluginjqhdot)
                               (_NLh2dot))
SICONOS_IO_REGISTER(Model,
                    (_t)
                    (_t0)
                    (_T)
                    (_strat)
                    (_nsds)
                    (_title)
                    (_author)
                    (_description)
                    (_date))
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderNonLinearDS, (DynamicalSystem),
                               (_M)
                               (_f)
                               (_fold)
                               (_jacobianfx)
                               (_pluginf)
                               (_pluginJacxf)
                               (_pluginM)
                               (_rMemory)
                               (_residur)
                               (_g_alpha)
                               (_xp)
                               (_xq)
                               (_invM))
SICONOS_IO_REGISTER_WITH_BASES(Relay, (LinearOSNS),
                               (_lb)
                               (_ub)
                               //  (_numerics_problem)
                              )
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderLinearDS, (FirstOrderNonLinearDS),
                               (_A)
                               (_b)
                               (_pluginA)
                               (_pluginb))
SICONOS_IO_REGISTER_WITH_BASES(MLCP2, (MLCP),
                               (mFirstCall))
SICONOS_IO_REGISTER_WITH_BASES(LinearOSNS, (OneStepNSProblem),
                               (_w)
                               (_z)
                               (_M)
                               (_q)
                               (_MStorageType)
                               (_keepLambdaAndYState))
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderType2R, (FirstOrderR),
                               (jacgx))
SICONOS_IO_REGISTER_WITH_BASES(TimeSteppingProjectOnConstraints, (TimeStepping),
                               (_constraintTol)
                               (_constraintTolUnilateral)
                               (_doProj)
                               (_doOnlyProj))
SICONOS_IO_REGISTER_WITH_BASES(Lsodar, (OneStepIntegrator),
                               (intData)
                               (rtol)
                               (atol)
                               (rwork)
                               (iwork)
                               (jroot)
                               (xWork))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianRheonomousR, (LagrangianR),
                               (_hDot)
                               (_pluginhDot)
                               (_pluginJachq))
SICONOS_IO_REGISTER_WITH_BASES(MultipleImpactNSL, (NonSmoothLaw),
                               (_ResCof)
                               (_Stiff)
                               (_ElasCof))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianCompliantR, (LagrangianR),
                               (_pluginJachq)
                               (_pluginJachlambda))
SICONOS_IO_REGISTER(TimeDiscretisation,
                    (h)
                    (k)
                    (tk)
                    (tdCase)
                    (pos))
SICONOS_IO_REGISTER(NonSmoothLaw,
                    (_size)
                    (_sizeProjectOnConstraints))
SICONOS_IO_REGISTER(BoundaryCondition,
                    (_velocityIndices)
                    (_prescribedVelocity)
                    (_prescribedVelocityOld)
                    (_pluginPrescribedVelocity))
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderLinearR, (FirstOrderR),
                               (_F)
                               (_e))
SICONOS_IO_REGISTER_WITH_BASES(BlockMatrix, (SiconosMatrix),
                               (_mat)
                               (_tabRow)
                               (_tabCol))
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderLinearTIR, (FirstOrderR),
                               (_F)
                               (_e))
SICONOS_IO_REGISTER_WITH_BASES(Equality, (LinearOSNS),
                               //  (_numerics_problem)
                              )
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderR, (Relation),
                               (Jachx)
                               (Jacglambda))
SICONOS_IO_REGISTER_WITH_BASES(Moreau, (OneStepIntegrator),
                               (WMap)
                               (_WBoundaryConditionsMap)
                               (_theta)
                               (_gamma)
                               (_useGamma)
                               (_useGammaForRelation))
SICONOS_IO_REGISTER(Event,
                    (timeOfEvent)
                    (type)
                    (dTime)
                    (tick))
SICONOS_IO_REGISTER_WITH_BASES(ActuatorEvent, (Event),
                               (_actuator))
SICONOS_IO_REGISTER_WITH_BASES(OSNSMultipleImpact, (LinearOSNS),
                               (Impulse_variable)
                               (Time_variable)
                               (Ncontact)
                               (NstepEst)
                               (NstepMax)
                               (TOL_IMPACT)
                               (TypeCompLaw)
                               (VelContact)
                               (OldVelContact)
                               (EnerContact)
                               (WcContact)
                               (DistriVector)
                               (StateContact)
                               (Kcontact)
                               (ResContact)
                               (ElasCoefContact)
                               (DelImpulseContact)
                               (TolImpulseContact)
                               (ImpulseContact_update)
                               (ForceContact)
                               (SelectPrimaConInVel)
                               (IdPrimaContact)
                               (IsPrimaConEnergy)
                               (VelAtPrimaCon)
                               (EnerAtPrimaCon)
                               (DeltaP)
                               (OutputFile)
                               (NameFile)
                               (YesSaveData)
                               (NstepSave)
                               (IsNumberOfStepsEst)
                               (_DataMatrix)
                               (YesSaveByMatrix)
                               (SizeDataSave)
                               (_IsImpactEnd))
SICONOS_IO_REGISTER(PluggedObject,
                    //  (fPtr)

                    (pluginName))
SICONOS_IO_REGISTER(EventsManager,
                    //  (_allEvents)
                    // (_currentEvent)
                    //  (_nextEvent)
                    //  (_ETD)
                    //  (_ENonSmooth)
                    //  (_simulation)
                    //  (_hasNS)
                    //  (_hasCM)
                    (GapLimit2Events))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianDS, (DynamicalSystem),
                               (_ndof)
                               (_q)
                               (_q0)
                               (_velocity0)
                               (_qMemory)
                               (_velocityMemory)
                               (_p)
                               (_mass)
                               (_fInt)
                               (_jacobianFIntq)
                               (_jacobianFIntqDot)
                               (_fExt)
                               (_NNL)
                               (_jacobianNNLq)
                               (_jacobianNNLqDot)
                               (_forces)
                               (_jacobianqForces)
                               (_jacobianqDotForces)
                               (_boundaryConditions)
                               (_reactionToBoundaryConditions)
                               (_pluginMass)
                               (_pluginFInt)
                               (_pluginFExt)
                               (_pluginNNL)
                               (_pluginJacqFInt)
                               (_pluginJacqDotFInt)
                               (_pluginJacqNNL)
                               (_pluginJacqDotNNL))
SICONOS_IO_REGISTER(UnitaryRelationsSet,
                    (fpt)
                    (setOfT))
