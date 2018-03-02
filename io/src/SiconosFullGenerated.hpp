// generated with build_from_doxygen.py
#ifndef SiconosFullGenerated_hpp
#define SiconosFullGenerated_hpp
#include <SiconosConfig.h>
#ifdef WITH_SERIALIZATION
#include "MechanicsFwd.hpp"
#include "SpaceFilter.hpp"
#include "SpaceFilter_impl.hpp"
#include "ExternalBody.hpp"
#include "Disk.hpp"
#include "Circle.hpp"
#include "DiskDiskR.hpp"
#include "DiskMovingPlanR.hpp"
#include "DiskPlanR.hpp"
#include "SphereLDS.hpp"
#include "SphereLDSPlanR.hpp"
#include "SphereLDSSphereLDSR.hpp"
#include "SphereNEDS.hpp"
#include "SphereNEDSPlanR.hpp"
#include "SphereNEDSSphereNEDSR.hpp"
#include "SiconosBodies.hpp"
#include "CircleCircleR.hpp"
#include "CircularDS.hpp"
#include "SiconosJoints.hpp"
#include "SiconosCollision.hpp"
#include "SiconosKernel.hpp"
#include "FirstOrderNonLinearDS.hpp"
#include "FirstOrderLinearDS.hpp"
#include "SiconosControl.hpp"
SICONOS_IO_REGISTER(SiconosException,
  (_reportMsg))
SICONOS_IO_REGISTER(SiconosMemory,
  (_indx)
  (_nbVectorsInMemory))
SICONOS_IO_REGISTER(BlockVector,
  (_sizeV)
  (_tabIndex)
  (_vect))
SICONOS_IO_REGISTER_WITH_BASES(BlockMatrix,(SiconosMatrix),
  (_dimCol)
  (_dimRow)
  (_mat)
  (_tabCol)
  (_tabRow))
SICONOS_IO_REGISTER(SiconosMatrix,
  (_num))
SICONOS_IO_REGISTER(GraphProperties,
  (symmetric))
SICONOS_IO_REGISTER(DynamicalSystemProperties,
  (W)
  (WBoundaryConditions)
  (absolute_position)
  (lower_block)
  (osi)
  (upper_block)
  (workMatrices)
  (workVectors))
SICONOS_IO_REGISTER(InteractionProperties,
  (absolute_position)
  (absolute_position_proj)
  (block)
  (forControl)
  (source)
  (source_pos)
  (target)
  (target_pos)
  (workBlockVectors)
  (workMatrices)
  (workVectors))
SICONOS_IO_REGISTER(MatrixIntegrator,
  (_DS)
  (_E)
  (_OSI)
  (_TD)
  (_isConst)
  (_mat)
  (_nsds)
  (_plugin)
  (_sim))
SICONOS_IO_REGISTER_WITH_BASES(DynamicalSystemsGraph,(_DynamicalSystemsGraph),
  (Ad)
  (AdInt)
  (B)
  (Bd)
  (L)
  (Ld)
  (dummy)
  (e)
  (groupId)
  (jacgx)
  (name)
  (pluginB)
  (pluginJacgx)
  (pluginL)
  (pluginU)
  (tmpXdot)
  (u))
SICONOS_IO_REGISTER_WITH_BASES(InteractionsGraph,(_InteractionsGraph),
  (blockProj)
  (dummy)
  (lower_blockProj)
  (name)
  (upper_blockProj))
SICONOS_IO_REGISTER(Topology,
  (_DSG)
  (_IG)
  (_hasChanged)
  (_numberOfConstraints)
  (_symmetric))
SICONOS_IO_REGISTER_WITH_BASES(MultipleImpactNSL,(NonSmoothLaw),
  (_ElasCof)
  (_ResCof)
  (_Stiff))
SICONOS_IO_REGISTER_WITH_BASES(ComplementarityConditionNSL,(NonSmoothLaw),
)
SICONOS_IO_REGISTER_WITH_BASES(FixedBC,(BoundaryCondition),
)
SICONOS_IO_REGISTER_WITH_BASES(HarmonicBC,(BoundaryCondition),
  (_a)
  (_aV)
  (_b)
  (_bV)
  (_omega)
  (_omegaV)
  (_phi)
  (_phiV))
SICONOS_IO_REGISTER(NSLawMatrix,
)
SICONOS_IO_REGISTER_WITH_BASES(EqualityConditionNSL,(NonSmoothLaw),
)
SICONOS_IO_REGISTER_WITH_BASES(NewtonImpactFrictionNSL,(NonSmoothLaw),
  (_en)
  (_et)
  (_mu))
SICONOS_IO_REGISTER_WITH_BASES(MixedComplementarityConditionNSL,(NonSmoothLaw),
  (_equalitySize))
SICONOS_IO_REGISTER(PluggedObject,
  (_pluginName))
SICONOS_IO_REGISTER_WITH_BASES(NewtonEulerFrom3DLocalFrameR,(NewtonEulerFrom1DLocalFrameR),
)
SICONOS_IO_REGISTER(NonSmoothDynamicalSystem::Changes,
  (typeOfChange)
  (ds)
  (i))
SICONOS_IO_REGISTER(NonSmoothDynamicalSystem,
  (_BVP)
  (_T)
  (_author)
  (_changeLog)
  (_date)
  (_description)
  (_mIsLinear)
  (_t)
  (_t0)
  (_title)
  (_topology))
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderLinearTIR,(FirstOrderR),
  (_e))
SICONOS_IO_REGISTER(BoundaryCondition,
  (_pluginPrescribedVelocity)
  (_prescribedVelocity)
  (_prescribedVelocityOld)
  (_velocityIndices))
SICONOS_IO_REGISTER_WITH_BASES(NewtonImpactNSL,(NonSmoothLaw),
  (_e))
SICONOS_IO_REGISTER_WITH_BASES(NewtonEulerFrom1DLocalFrameR,(NewtonEulerR),
  (_AUX1)
  (_AUX2)
  (_NPG1)
  (_NPG2)
  (_Nc)
  (_Pc1)
  (_Pc2)
  (_RotationAbsToContactFrame)
  (_isOnContact)
  (_relNc)
  (_relPc1)
  (_relPc2)
  (_rotationMatrixAbsToBody))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianLinearTIR,(LagrangianR),
  (_F)
  (_e))
SICONOS_IO_REGISTER_WITH_BASES(NormalConeNSL,(NonSmoothLaw),
  (_H)
  (_K))
SICONOS_IO_REGISTER_WITH_BASES(NewtonEulerR,(Relation),
  (_T)
  (_contactForce)
  (_dotjachq)
  (_e)
  (_jacglambda)
  (_jachlambda)
  (_jachq)
  (_jachqDot)
  (_jachqT)
  (_plugindotjacqh)
  (_secondOrderTimeDerivativeTerms))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianCompliantLinearTIR,(LagrangianR),
  (_F)
  (_e))
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderLinearR,(FirstOrderR),
  (_e))
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderLinearTIDS,(FirstOrderLinearDS),
)
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderType2R,(FirstOrderR),
)
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderType1R,(FirstOrderR),
)
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderLinearDS,(FirstOrderNonLinearDS),
  (_A)
  (_b)
  (_pluginA)
  (_pluginb))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianCompliantR,(LagrangianR),
  (_pluginJachlambda))
SICONOS_IO_REGISTER(NonSmoothLaw,
  (_size))
SICONOS_IO_REGISTER_WITH_BASES(RelayNSL,(NonSmoothLaw),
  (_lb)
  (_ub))
SICONOS_IO_REGISTER(Relation,
  (_pluginJacglambda)
  (_pluginJacgx)
  (_pluginJachlambda)
  (_pluginJachx)
  (_pluginJachz)
  (_plugine)
  (_pluginf)
  (_pluging)
  (_pluginh)
  (_relationType)
  (_subType))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianRheonomousR,(LagrangianR),
  (_hDot)
  (_pluginhDot))
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderNonLinearR,(FirstOrderR),
)
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderR,(Relation),
  (_B)
  (_C)
  (_D)
  (_F)
  (_K))
SICONOS_IO_REGISTER(Interaction,
  (__count)
  (_has2Bodies)
  (_interactionSize)
  (_lambda)
  (_lambdaMemory)
  (_lambdaOld)
  (_linkToDSVariables)
  (_lowerLevelForInput)
  (_lowerLevelForOutput)
  (_nslaw)
  (_number)
  (_relation)
  (_sizeOfDS)
  (_upperLevelForInput)
  (_upperLevelForOutput)
  (_y)
  (_yMemory)
  (_yOld)
  (_y_k))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianR,(Relation),
  (_dotjachq)
  (_jachlambda)
  (_jachq)
  (_jachqDot)
  (_pluginJachq))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianLinearDiagonalDS,(LagrangianDS),
  (_damping)
  (_mu)
  (_stiffness))
SICONOS_IO_REGISTER_WITH_BASES(FirstOrderNonLinearDS,(DynamicalSystem),
  (_M)
  (_f)
  (_fold)
  (_invM)
  (_jacobianfx)
  (_pluginJacxf)
  (_pluginM)
  (_pluginf)
  (_rMemory))
SICONOS_IO_REGISTER(DynamicalSystem,
  (__count)
  (_jacxRhs)
  (_n)
  (_number)
  (_r)
  (_stepsInMemory)
  (_x)
  (_x0)
  (_xMemory)
  (_z))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianScleronomousR,(LagrangianR),
  (_dotjacqhXqdot)
  (_plugindotjacqh))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianLinearTIDS,(LagrangianDS),
  (_C)
  (_K))
SICONOS_IO_REGISTER_WITH_BASES(LagrangianDS,(DynamicalSystem),
  (_boundaryConditions)
  (_fExt)
  (_fGyr)
  (_fInt)
  (_forces)
  (_forcesMemory)
  (_hasConstantFExt)
  (_hasConstantMass)
  (_inverseMass)
  (_jacobianFGyrq)
  (_jacobianFGyrqDot)
  (_jacobianFIntq)
  (_jacobianFIntqDot)
  (_jacobianqDotForces)
  (_jacobianqForces)
  (_mass)
  (_ndof)
  (_p)
  (_pMemory)
  (_pluginFExt)
  (_pluginFGyr)
  (_pluginFInt)
  (_pluginJacqDotFGyr)
  (_pluginJacqDotFInt)
  (_pluginJacqFGyr)
  (_pluginJacqFInt)
  (_pluginMass)
  (_q)
  (_q0)
  (_qMemory)
  (_reactionToBoundaryConditions)
  (_rhsMatrices)
  (_velocity0)
  (_velocityMemory))
SICONOS_IO_REGISTER_WITH_BASES(NewtonEulerDS,(DynamicalSystem),
  (_I)
  (_T)
  (_Tdot)
  (_acceleration)
  (_boundaryConditions)
  (_computeJacobianFIntqByFD)
  (_computeJacobianFInttwistByFD)
  (_computeJacobianMIntqByFD)
  (_computeJacobianMInttwistByFD)
  (_dotq)
  (_dotqMemory)
  (_epsilonFD)
  (_fExt)
  (_fInt)
  (_forcesMemory)
  (_hasConstantFExt)
  (_hasConstantMExt)
  (_inverseMass)
  (_isMextExpressedInInertialFrame)
  (_jacobianFIntq)
  (_jacobianFInttwist)
  (_jacobianMExtq)
  (_jacobianMGyrtwist)
  (_jacobianMIntq)
  (_jacobianMInttwist)
  (_jacobianWrenchTwist)
  (_jacobianWrenchq)
  (_mExt)
  (_mGyr)
  (_mInt)
  (_massMatrix)
  (_ndof)
  (_nullifyMGyr)
  (_p)
  (_pluginFExt)
  (_pluginFInt)
  (_pluginJacqFInt)
  (_pluginJacqMInt)
  (_pluginJactwistFInt)
  (_pluginJactwistMInt)
  (_pluginMExt)
  (_pluginMInt)
  (_q)
  (_q0)
  (_qDim)
  (_qMemory)
  (_reactionToBoundaryConditions)
  (_rhsMatrices)
  (_scalarMass)
  (_twist)
  (_twist0)
  (_twistMemory)
  (_wrench))
SICONOS_IO_REGISTER(ExtraAdditionalTerms,
)
SICONOS_IO_REGISTER_WITH_BASES(MoreauJeanBilbaoOSI,(OneStepIntegrator),
)
SICONOS_IO_REGISTER(InteractionManager,
  (_nslaws))
SICONOS_IO_REGISTER_WITH_BASES(TimeDiscretisationEvent,(Event),
)
SICONOS_IO_REGISTER_WITH_BASES(TimeSteppingCombinedProjection,(TimeStepping),
  (_constraintTol)
  (_constraintTolUnilateral)
  (_cumulatedNewtonNbIterations)
  (_doCombinedProj)
  (_doCombinedProjOnEquality)
  (_indexSetLevelForProjection)
  (_isIndexSetsStable)
  (_kIndexSetMax)
  (_maxViolationEquality)
  (_maxViolationUnilateral)
  (_nbCumulatedProjectionIteration)
  (_nbIndexSetsIteration)
  (_nbProjectionIteration)
  (_projectionMaxIteration))
SICONOS_IO_REGISTER_WITH_BASES(EventDriven,(Simulation),
  (_DSG0)
  (_TOL_ED)
  (_indexSet0)
  (_isNewtonConverge)
  (_istate)
  (_localizeEventMaxIter)
  (_newtonMaxIteration)
  (_newtonNbIterations)
  (_newtonResiduDSMax)
  (_newtonResiduYMax)
  (_newtonTolerance)
  (_numberOfOneStepNSproblems))
SICONOS_IO_REGISTER_WITH_BASES(NonSmoothEvent,(Event),
)
SICONOS_IO_REGISTER_WITH_BASES(QP,(OneStepNSProblem),
  (_Q)
  (_p))
SICONOS_IO_REGISTER_WITH_BASES(TimeSteppingD1Minus,(Simulation),
)
SICONOS_IO_REGISTER_WITH_BASES(MLCPProjectOnConstraints,(MLCP),
  (_alpha)
  (_doProjOnEquality)
  (_useMassNormalization))
SICONOS_IO_REGISTER_WITH_BASES(OSNSMultipleImpact,(LinearOSNS),
  (_DataMatrix)
  (_IsImpactEnd)
  (_Kcontact)
  (_Tol_Ener)
  (_Tol_Vel)
  (_WorkcContact)
  (_ZeroEner_EndIm)
  (_ZeroVel_EndIm)
  (_deltaImpulseContact)
  (_deltaP)
  (_distributionVector)
  (_elasticyCoefficientcontact)
  (_energyContact)
  (_energyPrimaryContact)
  (_forceContact)
  (_impulseContactUpdate)
  (_impulseVariable)
  (_isPrimaryContactEnergy)
  (_nContact)
  (_nStepMax)
  (_nStepSave)
  (_namefile)
  (_oldVelocityContact)
  (_primaryContactId)
  (_relativeVelocityPrimaryContact)
  (_restitutionContact)
  (_saveData)
  (_selectPrimaConInVel)
  (_sizeDataSave)
  (_stateContact)
  (_stepMaxSave)
  (_stepMinSave)
  (_timeVariable)
  (_tolImpact)
  (_tolImpulseContact)
  (_typeCompLaw)
  (_velocityContact))
SICONOS_IO_REGISTER_WITH_BASES(NewMarkAlphaOSI,(OneStepIntegrator),
  (_IsVelocityLevel)
  (_alpha_f)
  (_alpha_m)
  (_beta)
  (_gamma)
  (_orderDenseOutput))
SICONOS_IO_REGISTER_WITH_BASES(AVI,(LinearOSNS),
)
SICONOS_IO_REGISTER_WITH_BASES(TimeSteppingDirectProjection,(TimeStepping),
  (_constraintTol)
  (_constraintTolUnilateral)
  (_doOnlyProj)
  (_doProj)
  (_indexSetLevelForProjection)
  (_maxViolationEquality)
  (_maxViolationUnilateral)
  (_nbProjectionIteration)
  (_projectionMaxIteration))
SICONOS_IO_REGISTER_WITH_BASES(LinearOSNS,(OneStepNSProblem),
  (_M)
  (_keepLambdaAndYState)
  (_q)
  (_w)
  (_z))
SICONOS_IO_REGISTER(Simulation,
  (_OSIDSmap)
  (_T)
  (_allNSProblems)
  (_allOSI)
  (_eventsManager)
  (_interman)
  (_isInitialized)
  (_name)
  (_nsds)
  (_nsdsChangeLogPosition)
  (_numberOfIndexSets)
  (_printStat)
  (_relativeConvergenceCriterionHeld)
  (_relativeConvergenceTol)
  (_staticLevels)
  (_tend)
  (_tinit)
  (_tolerance)
  (_tout)
  (_useRelativeConvergenceCriterion)
  (statOut))
SICONOS_IO_REGISTER_WITH_BASES(ZeroOrderHoldOSI,(OneStepIntegrator),
  (_useGammaForRelation))
SICONOS_IO_REGISTER_WITH_BASES(Equality,(LinearOSNS),
)
SICONOS_IO_REGISTER_WITH_BASES(GenericMechanical,(LinearOSNS),
)
SICONOS_IO_REGISTER_WITH_BASES(MoreauJeanCombinedProjectionOSI,(MoreauJeanOSI),
)
SICONOS_IO_REGISTER_WITH_BASES(MoreauJeanDirectProjectionOSI,(MoreauJeanOSI),
  (_activateYPosThreshold)
  (_activateYVelThreshold)
  (_deactivateYPosThreshold)
  (_deactivateYVelThreshold))
SICONOS_IO_REGISTER_WITH_BASES(TimeStepping,(Simulation),
  (_computeResiduR)
  (_computeResiduY)
  (_displayNewtonConvergence)
  (_isNewtonConverge)
  (_newtonCumulativeNbIterations)
  (_newtonMaxIteration)
  (_newtonNbIterations)
  (_newtonOptions)
  (_newtonResiduDSMax)
  (_newtonResiduRMax)
  (_newtonResiduYMax)
  (_newtonTolerance)
  (_newtonUpdateInteractionsPerIteration)
  (_resetAllLambda)
  (_warnOnNonConvergence))
SICONOS_IO_REGISTER(OneStepIntegrator,
  (_dynamicalSystemsGraph)
  (_extraAdditionalTerms)
  (_integratorType)
  (_isInitialized)
  (_levelMaxForInput)
  (_levelMaxForOutput)
  (_levelMinForInput)
  (_levelMinForOutput)
  (_simulation)
  (_sizeMem)
  (_steps))
SICONOS_IO_REGISTER_WITH_BASES(Relay,(LinearOSNS),
  (_lb)
  (_ub))
SICONOS_IO_REGISTER_WITH_BASES(LCP,(LinearOSNS),
)
SICONOS_IO_REGISTER_WITH_BASES(MLCP,(LinearOSNS),
  (_curBlock)
  (_m)
  (_n))
SICONOS_IO_REGISTER_WITH_BASES(SchatzmanPaoliOSI,(OneStepIntegrator),
  (_gamma)
  (_theta)
  (_useGamma)
  (_useGammaForRelation))
SICONOS_IO_REGISTER(Event,
  (_dTime)
  (_eventCreated)
  (_k)
  (_reschedule)
  (_td)
  (_tick)
  (_tickIncrement)
  (_timeOfEvent)
  (_type))
SICONOS_IO_REGISTER(TimeDiscretisation,
  (_h)
  (_hgmp)
  (_t0)
  (_t0gmp)
  (_tk)
  (_tkV)
  (_tkp1))
SICONOS_IO_REGISTER(EventsManager,
  (_GapLimit2Events)
  (_NSeventInsteadOfTD)
  (_T)
  (_eNonSmooth)
  (_events)
  (_k)
  (_td))
SICONOS_IO_REGISTER(OneStepNSProblem,
  (_hasBeenUpdated)
  (_indexSetLevel)
  (_inputOutputLevel)
  (_maxSize)
  (_simulation)
  (_sizeOutput))
SICONOS_IO_REGISTER(OSNSMatrix,
  (_M1)
  (_M2)
  (_dimColumn)
  (_dimRow)
  (_storageType))
SICONOS_IO_REGISTER_WITH_BASES(OSNSMatrixProjectOnConstraints,(OSNSMatrix),
)
SICONOS_IO_REGISTER(BlockCSRMatrix,
  (_diagsize0)
  (_diagsize1)
  (_nc)
  (_nr)
  (_sparseBlockStructuredMatrix)
  (colPos)
  (rowPos))
SICONOS_IO_REGISTER_WITH_BASES(MoreauJeanGOSI,(OneStepIntegrator),
  (_WBoundaryConditionsMap)
  (_explicitNewtonEulerDSOperators)
  (_gamma)
  (_theta)
  (_useGamma)
  (_useGammaForRelation))
SICONOS_IO_REGISTER_WITH_BASES(MoreauJeanOSI,(OneStepIntegrator),
  (_explicitNewtonEulerDSOperators)
  (_gamma)
  (_theta)
  (_useGamma)
  (_useGammaForRelation))
SICONOS_IO_REGISTER_WITH_BASES(EulerMoreauOSI,(OneStepIntegrator),
  (_gamma)
  (_theta)
  (_useGamma)
  (_useGammaForRelation))
SICONOS_IO_REGISTER_WITH_BASES(ContactR,(NewtonEulerFrom3DLocalFrameR),
  (base)
  (contactor)
  (ds)
  (shape))
SICONOS_IO_REGISTER_WITH_BASES(PivotJointR,(KneeJointR),
  (_A)
  (_A1x)
  (_A1y)
  (_A1z)
  (_A2x)
  (_A2y)
  (_A2z)
  (_cq2q101)
  (_cq2q102)
  (_cq2q103)
  (_cq2q104)
  (_initial_AscalA)
  (_initial_AscalA1)
  (_initial_AscalA2)
  (_previousAngle)
  (_twistCount))
SICONOS_IO_REGISTER_WITH_BASES(SphereLDSPlanR,(LagrangianScleronomousR),
  (A)
  (B)
  (C)
  (D)
  (n1)
  (n2)
  (n3)
  (nN)
  (nU)
  (r)
  (ru1)
  (ru2)
  (ru3)
  (rv1)
  (rv2)
  (rv3)
  (u1)
  (u2)
  (u3)
  (v1)
  (v2)
  (v3))
SICONOS_IO_REGISTER_WITH_BASES(SphereLDSSphereLDSR,(LagrangianScleronomousR),
  (r1)
  (r1pr2)
  (r2))
SICONOS_IO_REGISTER_WITH_BASES(SphereNEDSSphereNEDSR,(NewtonEulerFrom3DLocalFrameR),
  (r1)
  (r1pr2)
  (r2))
SICONOS_IO_REGISTER_WITH_BASES(ExternalBody,(LagrangianDS),
)
SICONOS_IO_REGISTER_WITH_BASES(Circle,(CircularDS),
)
SICONOS_IO_REGISTER_WITH_BASES(FixedJointR,(NewtonEulerJointR),
  (_G10G20d1x)
  (_G10G20d1y)
  (_G10G20d1z)
  (_cq2q101)
  (_cq2q102)
  (_cq2q103)
  (_cq2q104))
SICONOS_IO_REGISTER_WITH_BASES(KneeJointR,(NewtonEulerJointR),
  (_G1P0x)
  (_G1P0y)
  (_G1P0z)
  (_G2P0x)
  (_G2P0y)
  (_G2P0z)
  (_P0))
SICONOS_IO_REGISTER_WITH_BASES(NewtonEulerJointR,(NewtonEulerR),
  (_absoluteRef)
  (_allowSelfCollide)
  (_axes)
  (_points))
SICONOS_IO_REGISTER_WITH_BASES(SphereLDS,(LagrangianDS),
  (I)
  (massValue)
  (radius))
SICONOS_IO_REGISTER_WITH_BASES(SphereNEDSPlanR,(NewtonEulerFrom3DLocalFrameR),
  (A)
  (B)
  (C)
  (D)
  (n1)
  (n2)
  (n3)
  (nN)
  (nU)
  (r)
  (ru1)
  (ru2)
  (ru3)
  (rv1)
  (rv2)
  (rv3)
  (u1)
  (u2)
  (u3)
  (v1)
  (v2)
  (v3))
SICONOS_IO_REGISTER_WITH_BASES(CircleCircleR,(CircularR),
)
SICONOS_IO_REGISTER_WITH_BASES(CircularR,(LagrangianScleronomousR),
  (_r1)
  (_r2))
SICONOS_IO_REGISTER_WITH_BASES(Disk,(CircularDS),
)
SICONOS_IO_REGISTER_WITH_BASES(DiskDiskR,(CircularR),
  (r1pr2))
SICONOS_IO_REGISTER_WITH_BASES(DiskPlanR,(LagrangianScleronomousR),
  (A)
  (A2)
  (AB)
  (AC)
  (B)
  (B2)
  (BC)
  (C)
  (finite)
  (halfWidth)
  (r)
  (sqrA2pB2)
  (width)
  (x1)
  (x2)
  (xCenter)
  (y1)
  (y2)
  (yCenter))
SICONOS_IO_REGISTER(SiconosBodies,
  (_plans)
  (_playground)
  (_sim))
SICONOS_IO_REGISTER(SiconosCollisionQueryResult,
  (body)
  (contactor)
  (distance)
  (point)
  (shape))
SICONOS_IO_REGISTER_WITH_BASES(SphereNEDS,(NewtonEulerDS),
  (radius))
SICONOS_IO_REGISTER_WITH_BASES(BodyDS,(NewtonEulerDS),
  (_allowSelfCollide)
  (_contactors)
  (_useContactorInertia))
SICONOS_IO_REGISTER_WITH_BASES(CircularDS,(LagrangianDS),
  (massValue)
  (radius))
SICONOS_IO_REGISTER_WITH_BASES(JointFrictionR,(NewtonEulerR),
  (_axis)
  (_axisMax)
  (_axisMin)
  (_jachqTmp)
  (_joint))
SICONOS_IO_REGISTER_WITH_BASES(SiconosCollisionManager,(InteractionManager),
)
SICONOS_IO_REGISTER(SiconosShape,
  (_inside_margin)
  (_outside_margin)
  (_version))
SICONOS_IO_REGISTER_WITH_BASES(JointStopR,(NewtonEulerR),
  (_axis)
  (_axisMax)
  (_axisMin)
  (_dir)
  (_jachqTmp)
  (_joint)
  (_pos))
SICONOS_IO_REGISTER_WITH_BASES(CouplerJointR,(NewtonEulerJointR),
  (_dof1)
  (_dof2)
  (_joint1)
  (_joint2)
  (_offset)
  (_ratio)
  (_ref1)
  (_ref1_index)
  (_ref2)
  (_ref2_index))
SICONOS_IO_REGISTER_WITH_BASES(CylindricalJointR,(NewtonEulerJointR),
  (_G1P0)
  (_G2P0)
  (_V1)
  (_V2)
  (_axis0)
  (_cq2q101)
  (_cq2q102)
  (_cq2q103)
  (_cq2q104)
  (_initialAngle)
  (_previousAngle)
  (_twistCount))
SICONOS_IO_REGISTER(FMatrix,
)
SICONOS_IO_REGISTER_WITH_BASES(PrismaticJointR,(NewtonEulerJointR),
  (_G10G20d1x)
  (_G10G20d1y)
  (_G10G20d1z)
  (_V1)
  (_V1x)
  (_V1y)
  (_V1z)
  (_V2)
  (_V2x)
  (_V2y)
  (_V2z)
  (_axis0)
  (_cq2q101)
  (_cq2q102)
  (_cq2q103)
  (_cq2q104))
SICONOS_IO_REGISTER(SiconosContactor,
  (collision_group)
  (offset)
  (shape))
SICONOS_IO_REGISTER_WITH_BASES(DiskMovingPlanR,(LagrangianRheonomousR),
  (_A)
  (_AADot)
  (_ADot)
  (_ADotFunction)
  (_AFunction)
  (_B)
  (_BBDot)
  (_BDot)
  (_BDotFunction)
  (_BFunction)
  (_C)
  (_CDot)
  (_CDotFunction)
  (_CFunction)
  (_cubsqrA2pB2)
  (_r)
  (_sqrA2pB2)
  (_time))
SICONOS_IO_REGISTER(Hashed,
  (body)
  (i)
  (j)
  (k))
SICONOS_IO_REGISTER(SpaceFilter,
  (_bboxfactor)
  (_cellsize)
  (_hash_table)
  (_plans)
  (circlecircle_relations)
  (diskdisk_relations)
  (diskplan_relations))
SICONOS_IO_REGISTER(SiconosContactorSet,
)
SICONOS_IO_REGISTER(space_hash,
)
SICONOS_IO_REGISTER(CircleCircleRDeclaredPool,
)
SICONOS_IO_REGISTER(DiskDiskRDeclaredPool,
)
SICONOS_IO_REGISTER_WITH_BASES(SiconosPlane,(SiconosShape),
)
SICONOS_IO_REGISTER(DiskPlanRDeclaredPool,
)
SICONOS_IO_REGISTER_WITH_BASES(SiconosSphere,(SiconosShape),
  (_radius))
SICONOS_IO_REGISTER_WITH_BASES(SiconosBox,(SiconosShape),
  (_dimensions))
SICONOS_IO_REGISTER_WITH_BASES(SiconosCylinder,(SiconosShape),
  (_length)
  (_radius))
SICONOS_IO_REGISTER_WITH_BASES(SiconosConvexHull,(SiconosShape),
  (_vertices))
SICONOS_IO_REGISTER_WITH_BASES(SiconosMesh,(SiconosShape),
  (_indexes)
  (_vertices))
SICONOS_IO_REGISTER_WITH_BASES(SiconosHeightMap,(SiconosShape),
  (_height_data)
  (_length_x)
  (_length_y))
SICONOS_IO_REGISTER_WITH_BASES(ExplicitLinearSMC,(CommonSMC),
  (_sigma))
SICONOS_IO_REGISTER_WITH_BASES(LinearSMC,(CommonSMC),
)
SICONOS_IO_REGISTER_WITH_BASES(LuenbergerObserver,(Observer),
  (_C)
  (_L)
  (_pass)
  (_theta))
SICONOS_IO_REGISTER_WITH_BASES(SlidingReducedOrderObserver,(Observer),
  (_C)
  (_L)
  (_pass)
  (_theta))
SICONOS_IO_REGISTER_WITH_BASES(Twisting,(CommonSMC),
)
SICONOS_IO_REGISTER_WITH_BASES(PID,(Actuator),
  (_K)
  (_curDeltaT)
  (_ref))
SICONOS_IO_REGISTER_WITH_BASES(CommonSMC,(Actuator),
  (_Csurface)
  (_D)
  (_DS_SMC)
  (_OSNSPB_SMC)
  (_alpha)
  (_computeResidus)
  (_eventsManager)
  (_indx)
  (_integratorSMC)
  (_interactionSMC)
  (_invCB)
  (_lambda)
  (_noUeq)
  (_nsLawSMC)
  (_nsdsSMC)
  (_pluginJacglambdaName)
  (_pluginJachlambdaName)
  (_pluginJachxName)
  (_plugineName)
  (_pluginhName)
  (_precision)
  (_relationSMC)
  (_simulationSMC)
  (_td)
  (_thetaSMC)
  (_ueq)
  (_us))
SICONOS_IO_REGISTER_WITH_BASES(LinearSMCOT2,(CommonSMC),
  (_DSPhi)
  (_DSPred)
  (_PhiOSI)
  (_PredOSI)
  (_X)
  (_XPhi)
  (_Xhat)
  (_coeff)
  (_nsdsPhi)
  (_nsdsPred)
  (_simulPhi)
  (_simulPred)
  (_tdPhi)
  (_tdPred))
SICONOS_IO_REGISTER_WITH_BASES(LinearSMCimproved,(LinearSMC),
  (_inDisceteTimeSlidingPhase)
  (_predictionPerturbation)
  (_ubPerturbation)
  (_up))
SICONOS_IO_REGISTER(ControlSimulation,
  (_CM)
  (_DSG0)
  (_IG0)
  (_N)
  (_T)
  (_dataLegend)
  (_dataM)
  (_elapsedTime)
  (_h)
  (_nDim)
  (_nsds)
  (_processIntegrator)
  (_processSimulation)
  (_processTD)
  (_saveOnlyMainSimulation)
  (_silent)
  (_t0)
  (_theta))
SICONOS_IO_REGISTER_WITH_BASES(ActuatorEvent,(Event),
  (_actuator))
SICONOS_IO_REGISTER_WITH_BASES(SensorEvent,(Event),
  (_sensor))
SICONOS_IO_REGISTER_WITH_BASES(LinearSensor,(ControlSensor),
  (_data)
  (_dataPlot)
  (_k)
  (_matC)
  (_matD)
  (_nSteps))
SICONOS_IO_REGISTER_WITH_BASES(ControlSensor,(Sensor),
  (_delay)
  (_storedY))
SICONOS_IO_REGISTER(Observer,
  (_DS)
  (_e)
  (_id)
  (_integrator)
  (_nsds)
  (_sensor)
  (_simulation)
  (_td)
  (_type)
  (_xHat)
  (_y))
SICONOS_IO_REGISTER(ControlManager,
  (_allActuators)
  (_allObservers)
  (_allSensors)
  (_sim))
SICONOS_IO_REGISTER(Actuator,
  (_B)
  (_id)
  (_pluginJacgxName)
  (_plugingName)
  (_sensor)
  (_type)
  (_u))
SICONOS_IO_REGISTER(Sensor,
  (_DS)
  (_DSx)
  (_id)
  (_type))

template <class Archive>
void siconos_io_register_generated_Control(Archive& ar)
{
  ar.register_type(static_cast<ExplicitLinearSMC*>(NULL));
  ar.register_type(static_cast<LinearSMC*>(NULL));
  ar.register_type(static_cast<LuenbergerObserver*>(NULL));
  ar.register_type(static_cast<SlidingReducedOrderObserver*>(NULL));
  ar.register_type(static_cast<Twisting*>(NULL));
  ar.register_type(static_cast<PID*>(NULL));
  ar.register_type(static_cast<LinearSMCOT2*>(NULL));
  ar.register_type(static_cast<LinearSMCimproved*>(NULL));
  ar.register_type(static_cast<ActuatorEvent*>(NULL));
  ar.register_type(static_cast<SensorEvent*>(NULL));
  ar.register_type(static_cast<LinearSensor*>(NULL));
  ar.register_type(static_cast<ControlManager*>(NULL));
}

template <class Archive>
void siconos_io_register_generated_Kernel(Archive& ar)
{
  ar.register_type(static_cast<SiconosException*>(NULL));
  ar.register_type(static_cast<SiconosMemory*>(NULL));
  ar.register_type(static_cast<BlockVector*>(NULL));
  ar.register_type(static_cast<BlockMatrix*>(NULL));
  ar.register_type(static_cast<GraphProperties*>(NULL));
  ar.register_type(static_cast<DynamicalSystemProperties*>(NULL));
  ar.register_type(static_cast<InteractionProperties*>(NULL));
  ar.register_type(static_cast<MatrixIntegrator*>(NULL));
  ar.register_type(static_cast<DynamicalSystemsGraph*>(NULL));
  ar.register_type(static_cast<InteractionsGraph*>(NULL));
  ar.register_type(static_cast<Topology*>(NULL));
  ar.register_type(static_cast<MultipleImpactNSL*>(NULL));
  ar.register_type(static_cast<ComplementarityConditionNSL*>(NULL));
  ar.register_type(static_cast<FixedBC*>(NULL));
  ar.register_type(static_cast<HarmonicBC*>(NULL));
  ar.register_type(static_cast<NSLawMatrix*>(NULL));
  ar.register_type(static_cast<EqualityConditionNSL*>(NULL));
  ar.register_type(static_cast<NewtonImpactFrictionNSL*>(NULL));
  ar.register_type(static_cast<MixedComplementarityConditionNSL*>(NULL));
  ar.register_type(static_cast<PluggedObject*>(NULL));
  ar.register_type(static_cast<NewtonEulerFrom3DLocalFrameR*>(NULL));
  ar.register_type(static_cast<NonSmoothDynamicalSystem*>(NULL));
  ar.register_type(static_cast<NonSmoothDynamicalSystem::Changes*>(NULL));
  ar.register_type(static_cast<FirstOrderLinearTIR*>(NULL));
  ar.register_type(static_cast<BoundaryCondition*>(NULL));
  ar.register_type(static_cast<NewtonImpactNSL*>(NULL));
  ar.register_type(static_cast<NewtonEulerFrom1DLocalFrameR*>(NULL));
  ar.register_type(static_cast<LagrangianLinearTIR*>(NULL));
  ar.register_type(static_cast<NormalConeNSL*>(NULL));
  ar.register_type(static_cast<NewtonEulerR*>(NULL));
  ar.register_type(static_cast<LagrangianCompliantLinearTIR*>(NULL));
  ar.register_type(static_cast<FirstOrderLinearR*>(NULL));
  ar.register_type(static_cast<FirstOrderLinearTIDS*>(NULL));
  ar.register_type(static_cast<FirstOrderType2R*>(NULL));
  ar.register_type(static_cast<FirstOrderType1R*>(NULL));
  ar.register_type(static_cast<FirstOrderLinearDS*>(NULL));
  ar.register_type(static_cast<LagrangianCompliantR*>(NULL));
  ar.register_type(static_cast<RelayNSL*>(NULL));
  ar.register_type(static_cast<LagrangianRheonomousR*>(NULL));
  ar.register_type(static_cast<FirstOrderNonLinearR*>(NULL));
  ar.register_type(static_cast<Interaction*>(NULL));
  ar.register_type(static_cast<LagrangianLinearDiagonalDS*>(NULL));
  ar.register_type(static_cast<FirstOrderNonLinearDS*>(NULL));
  ar.register_type(static_cast<LagrangianScleronomousR*>(NULL));
  ar.register_type(static_cast<LagrangianLinearTIDS*>(NULL));
  ar.register_type(static_cast<LagrangianDS*>(NULL));
  ar.register_type(static_cast<NewtonEulerDS*>(NULL));
  ar.register_type(static_cast<MoreauJeanBilbaoOSI*>(NULL));
  ar.register_type(static_cast<InteractionManager*>(NULL));
  ar.register_type(static_cast<TimeDiscretisationEvent*>(NULL));
  ar.register_type(static_cast<TimeSteppingCombinedProjection*>(NULL));
  ar.register_type(static_cast<EventDriven*>(NULL));
  ar.register_type(static_cast<NonSmoothEvent*>(NULL));
  ar.register_type(static_cast<QP*>(NULL));
  ar.register_type(static_cast<TimeSteppingD1Minus*>(NULL));
  ar.register_type(static_cast<MLCPProjectOnConstraints*>(NULL));
  ar.register_type(static_cast<OSNSMultipleImpact*>(NULL));
  ar.register_type(static_cast<NewMarkAlphaOSI*>(NULL));
  ar.register_type(static_cast<AVI*>(NULL));
  ar.register_type(static_cast<TimeSteppingDirectProjection*>(NULL));
  ar.register_type(static_cast<ZeroOrderHoldOSI*>(NULL));
  ar.register_type(static_cast<Equality*>(NULL));
  ar.register_type(static_cast<GenericMechanical*>(NULL));
  ar.register_type(static_cast<MoreauJeanCombinedProjectionOSI*>(NULL));
  ar.register_type(static_cast<MoreauJeanDirectProjectionOSI*>(NULL));
  ar.register_type(static_cast<TimeStepping*>(NULL));
  ar.register_type(static_cast<Relay*>(NULL));
  ar.register_type(static_cast<LCP*>(NULL));
  ar.register_type(static_cast<MLCP*>(NULL));
  ar.register_type(static_cast<SchatzmanPaoliOSI*>(NULL));
  ar.register_type(static_cast<TimeDiscretisation*>(NULL));
  ar.register_type(static_cast<EventsManager*>(NULL));
  ar.register_type(static_cast<OSNSMatrix*>(NULL));
  ar.register_type(static_cast<OSNSMatrixProjectOnConstraints*>(NULL));
  ar.register_type(static_cast<BlockCSRMatrix*>(NULL));
  ar.register_type(static_cast<MoreauJeanGOSI*>(NULL));
  ar.register_type(static_cast<MoreauJeanOSI*>(NULL));
  ar.register_type(static_cast<EulerMoreauOSI*>(NULL));
}

template <class Archive>
void siconos_io_register_generated_Mechanics(Archive& ar)
{
  ar.register_type(static_cast<ContactR*>(NULL));
  ar.register_type(static_cast<PivotJointR*>(NULL));
  ar.register_type(static_cast<SphereLDSPlanR*>(NULL));
  ar.register_type(static_cast<SphereLDSSphereLDSR*>(NULL));
  ar.register_type(static_cast<SphereNEDSSphereNEDSR*>(NULL));
  ar.register_type(static_cast<Circle*>(NULL));
  ar.register_type(static_cast<FixedJointR*>(NULL));
  ar.register_type(static_cast<KneeJointR*>(NULL));
  ar.register_type(static_cast<SphereLDS*>(NULL));
  ar.register_type(static_cast<SphereNEDSPlanR*>(NULL));
  ar.register_type(static_cast<CircleCircleR*>(NULL));
  ar.register_type(static_cast<CircularR*>(NULL));
  ar.register_type(static_cast<Disk*>(NULL));
  ar.register_type(static_cast<DiskDiskR*>(NULL));
  ar.register_type(static_cast<DiskPlanR*>(NULL));
  ar.register_type(static_cast<SiconosCollisionQueryResult*>(NULL));
  ar.register_type(static_cast<SphereNEDS*>(NULL));
  ar.register_type(static_cast<BodyDS*>(NULL));
  ar.register_type(static_cast<CircularDS*>(NULL));
  ar.register_type(static_cast<JointFrictionR*>(NULL));
  ar.register_type(static_cast<SiconosShape*>(NULL));
  ar.register_type(static_cast<JointStopR*>(NULL));
  ar.register_type(static_cast<CouplerJointR*>(NULL));
  ar.register_type(static_cast<CylindricalJointR*>(NULL));
  ar.register_type(static_cast<FMatrix*>(NULL));
  ar.register_type(static_cast<PrismaticJointR*>(NULL));
  ar.register_type(static_cast<SiconosContactor*>(NULL));
  ar.register_type(static_cast<DiskMovingPlanR*>(NULL));
  ar.register_type(static_cast<Hashed*>(NULL));
  ar.register_type(static_cast<SpaceFilter*>(NULL));
  ar.register_type(static_cast<SiconosContactorSet*>(NULL));
  ar.register_type(static_cast<space_hash*>(NULL));
  ar.register_type(static_cast<CircleCircleRDeclaredPool*>(NULL));
  ar.register_type(static_cast<DiskDiskRDeclaredPool*>(NULL));
  ar.register_type(static_cast<SiconosPlane*>(NULL));
  ar.register_type(static_cast<DiskPlanRDeclaredPool*>(NULL));
  ar.register_type(static_cast<SiconosSphere*>(NULL));
  ar.register_type(static_cast<SiconosBox*>(NULL));
  ar.register_type(static_cast<SiconosCylinder*>(NULL));
  ar.register_type(static_cast<SiconosConvexHull*>(NULL));
  ar.register_type(static_cast<SiconosMesh*>(NULL));
  ar.register_type(static_cast<SiconosHeightMap*>(NULL));
}
#endif
#endif
