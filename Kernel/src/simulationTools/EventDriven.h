/* Siconos-Kernel version 1.3.0, Copyright INRIA 2005-2006.
 * Siconos is a program dedicated to modeling, simulation and control
 * of non smooth dynamical systems.
 * Siconos is a free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * Siconos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Siconos; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Contact: Vincent ACARY vincent.acary@inrialpes.fr
*/
#ifndef EVENTDRIVEN_H
#define EVENTDRIVEN_H

/** \class EventDriven
 *  \brief Simulation based on event driven method, ie events detection (see theoretical manual for more details).
 *  \author SICONOS Development Team - copyright INRIA
 *  \version 1.3.0.
 *  \date (Creation) Apr 26, 2004
 *
 * WARNING: at the time mainly written for Lagrangian systems !!!
 */

#include "Simulation.h"
#include "EventsManager.h"
#include "LCP.h"

class EventsManager;

class EventDriven : public Simulation
{

private:
  /** tool to manage events */
  EventsManager* eventsManager;

  /** flag used in DLSODAR -
   *  As input: 1 if first call, else 2
   *  As output: 2 if no root found, else 3
   */
  int istate;

  /** current starting time for integration */
  double tinit;

  /** current ending time for integration */
  double tend;

public:

  /** \fn EventDriven(Model * = NULL)
   *  \brief defaut constructor
   *  \param a pointer to the model that owns this simulation. NULL Model leads to exception
   */
  EventDriven(Model * = NULL);

  /** \fn EventDriven(SimulationXML*, Model*)
   *  \brief constructor with XML object of the EventDriven
   *  \param SimulationXML* : the XML object corresponding
   *  \param Model* : the Model which contains the Simulation
   */
  EventDriven(SimulationXML*, Model*);

  /** \fn ~EventDriven()
   *  \brief destructor
   */
  ~EventDriven();

  /* Getters and setters */

  /** \fn EventsManager* getEventsManagerPtr()
   *  \brief get the EventsManager
   *  \return a pointer to EventsManager
   */
  inline EventsManager* getEventsManagerPtr() const
  {
    return eventsManager;
  }

  /** \fn void setEventsManagerPtr(EventsManager*)
   *  \brief set the EventsManager of the OneStepNSProblem
   *  \param: a pointer on EventsManager
   */
  void setEventsManagerPtr(EventsManager*);

  /** \fn virtual void updateIndexSet(const unsigned int i) = 0;
   *  \brief update indexSets[i] of the topology, using current y and lambda values of Interactions.
   *  \param unsigned int: the number of the set to be updated
   */
  void updateIndexSet(const unsigned int);

  /** \fn void updateIndexSetsWithDoubleCondition();
   *   \brief update indexSets[1] and [2] (using current y and lambda values of Interactions) with conditions on y[2] AND lambda[2].
   */
  void updateIndexSetsWithDoubleCondition();

  /** \fn void computeF(OneStepIntegrator* osi, integer * sizeOfX, doublereal * time, doublereal * x, doublereal * xdot)
   *  \brief compute right-hand side of xdot = f(x,t), for the integrator osi.
   *  \param pointer to OneStepIntegrator.
   *  \param integer*, size of vector x
   *  \param doublereal*, time
   *  \param doublereal*, x:array of double
   *  \param doublereal*, derivative of x (in-out parameter)
   */
  void computeF(OneStepIntegrator*, integer *, doublereal *, doublereal *, doublereal *);

  /** \fn void computeJacobian(OneStepIntegrator*, integer *sizeOfX, doublereal *time, doublereal *x,  doublereal *jacob)
   *  \brief compute jacobian of the right-hand side
   *  \param pointer to OneStepIntegrator.
   *  \param integer*, size of vector x
   *  \param doublereal*, time
   *  \param doublereal*, x:array of double
   *  \param doublereal*, jacobian of f according to x (in-out parameter)
   */
  void computeJacobianF(OneStepIntegrator*, integer *, doublereal *, doublereal *,  doublereal *);

  /** \fn void computeG(OneStepIntegrator* osi, integer * nEq, doublereal * time, doublereal* x, integer * ng, doublereal * gOut)
   *  \brief compute constraint function g(x,t,...) for osi.
   *  \param pointer to OneStepIntegrator.
   *  \param integer*, size of vector x
   *  \param doublereal*, time
   *  \param doublereal*, x:array of double
   *  \param integer*, size of vector g (ie number of constraints)
   *  \param doublereal*, g (in-out parameter)
   */
  void computeG(OneStepIntegrator*, integer *, doublereal *, doublereal*, integer *, doublereal*);

  /** \fn void initialize()
   *  \brief initialisation of the simulation
   */
  void initialize();

  /** \fn void updateImpactState()
   *  \brief update input for impact case (ie compute p[1])
   */
  void updateImpactState();

  /** \fn void simulateOneStep()
    *  \brief run the whole simulation
    */
  void run();

  /** \fn void update(const unsigned int)
   *  \brief update input, output and indexSets.
   *  \param lambda order used to compute input
   */
  void update(const unsigned int);

  /** \fn void computeOneStep()
   *  \brief run simulation from one Event to the next
   */
  void computeOneStep();

  /** \fn void nextStep()
   *  \brief increments all the Integrators to next step of the simulation
   */
  void nextStep();

  /** \fn void advanceToEvent()
   *  \brief run simulation from one Event to the next, according to events manager settings.
   */
  void advanceToEvent();

  /** \fn EventDriven* convert (Simulation* str)
   *  \brief encapsulates an operation of dynamic casting. Needed by Python interface.
   *  \param Simulation* : the Simulation which must be converted
   * \return a pointer on the Simulation if it is of the right type, NULL otherwise
   */
  static EventDriven* convert(Simulation* str);

};

#endif // EVENTDRIVEN_H
