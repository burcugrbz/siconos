/* Siconos-sample , Copyright INRIA 2005-2011.
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
//-----------------------------------------------------------------------
//
//  DiodeBridgeCapFilter  : sample of an electrical circuit involving :
//  - a 1st linear dynamical system LSDiodeBridge1 consisting of
//        an LC oscillator (1 �F , 10 mH)
//  - a non smooth system : a 4 diodes bridge used as a full wave rectifier
//        of the supplied voltage across the LC oscillator, providing power
//    to the resistor load of the 2nd dynamical system
//      - a 2nd linear dynamical system LSDiodeBridge2 consisting of
//        a filtering capacitor in parallel with a load resistor
//
//  Expected behavior :
//  The initial state (Vc = 10 V , IL = 0) of the oscillator provides
//      an initial energy.
//  The oscillator period is 2 Pi sqrt(LC) ~ 0,628 ms.
//      The non smooth system is a full wave rectifier :
//  each phase (positive and negative) of the oscillation allows current
//      to flow in a constant direction through the load.
//      The capacitor filter acts as a tank providing energy to the load resistor
//      when the voltage across the oscillator weakens.
//      The load resistor consumes energy : the oscillation damps.
//
//  State variables LSDiodeBridge1:
//  - the voltage across the capacitor (or inductor)
//  - the current through the inductor
//
//  State variable LSDiodeBridge2:
//  - the voltage across the filtering capacitor
//
//  The interaction between the two dynamical systems is defined by :
//  - complementarity laws between diodes current and voltage. Depending on
//        the diode position in the bridge, y stands for the reverse voltage across
//    the diode or for the diode current (see figure in the template file)
//  - a linear time invariant relation between the state variables and y and
//    lambda (derived from the Kirchhoff laws)
//
//-----------------------------------------------------------------------

#include "SiconosKernel.hpp"

using namespace std;

int main(int argc, char* argv[])
{

  double t0 = 0.0;
  double T = 5e-3;           // Total simulation time
  double h_step = 1e-6;    // Time step
  double Lvalue = 1e-2;      // inductance
  double Cvalue = 1e-6;      // capacitance LC oscillator
  double Rvalue = 1e3;       // load resistance
  double Cfilt  = 300.0e-9;  // filtering capacitor
  double VinitLS1 = 10.0;    // initial voltage LC oscillator
  double VinitLS2 = 0.0;     // initial voltage Cfilt
  string Modeltitle = "DiodeBridgeCapFilter";

  try
  {

    // --- Linear system 1 (LC oscillator) specification ---
    SP::SiconosVector init_stateLS1(new SiconosVector(2));
    (*init_stateLS1)(0) = VinitLS1;

    SP::SimpleMatrix LS1_A(new SimpleMatrix(2, 2));
    (*LS1_A)(0 , 1) = -1.0 / Cvalue;
    (*LS1_A)(1 , 0) = 1.0 / Lvalue;

    cout << " LS1 matrice A = " << endl;
    LS1_A->display();
    SP::FirstOrderLinearDS LS1DiodeBridgeCapFilter(new FirstOrderLinearDS(init_stateLS1, LS1_A));

    // --- Linear system 2 (load and filter) specification ---
    SP::SiconosVector init_stateLS2(new SiconosVector(1));
    (*init_stateLS2)(0) = VinitLS2;

    SP::SimpleMatrix LS2_A(new SimpleMatrix(1, 1));
    (*LS2_A)(0 , 0) = -1.0 / (Rvalue * Cfilt);

    cout << " LS2 matrice A = " << endl;
    LS2_A->display();
    SP::FirstOrderLinearDS LS2DiodeBridgeCapFilter(new FirstOrderLinearDS(init_stateLS2, LS2_A));

    // --- Interaction between linear systems and non smooth system ---
    SP::SiconosMatrix Int_C(new SimpleMatrix(4, 3));
    (*Int_C)(0 , 2) = 1.0;
    (*Int_C)(2 , 0) = -1.0;
    (*Int_C)(2 , 2) = 1.0;
    (*Int_C)(3 , 0) = 1.0;

    SP::SiconosMatrix Int_D(new SimpleMatrix(4, 4));
    (*Int_D)(0 , 1) = -1.0;
    (*Int_D)(1 , 0) = 1.0;
    (*Int_D)(1 , 2) = 1.0;
    (*Int_D)(1 , 3) = -1.0;
    (*Int_D)(2 , 1) = -1.0;
    (*Int_D)(3 , 1) = 1.0;

    SP::SiconosMatrix Int_B(new SimpleMatrix(3, 4));
    (*Int_B)(0 , 2) = -1.0 / Cvalue;
    (*Int_B)(0 , 3) = 1.0 / Cvalue;
    (*Int_B)(2 , 0) = 1.0 / Cfilt;
    (*Int_B)(2 , 2) = 1.0 / Cfilt;

    SP::FirstOrderLinearTIR LTIRDiodeBridgeCapFilter(new FirstOrderLinearTIR(Int_C, Int_B));
    LTIRDiodeBridgeCapFilter->setDPtr(Int_D);
    SP::NonSmoothLaw nslaw(new ComplementarityConditionNSL(4));

    SP::Interaction InterDiodeBridgeCapFilter(new Interaction(4, nslaw, LTIRDiodeBridgeCapFilter));

    // --- Model creation ---
    SP::Model DiodeBridgeCapFilter(new Model(t0, T, Modeltitle));
    DiodeBridgeCapFilter->nonSmoothDynamicalSystem()->insertDynamicalSystem(LS1DiodeBridgeCapFilter);
    DiodeBridgeCapFilter->nonSmoothDynamicalSystem()->insertDynamicalSystem(LS2DiodeBridgeCapFilter);
    DiodeBridgeCapFilter->nonSmoothDynamicalSystem()->link(InterDiodeBridgeCapFilter, LS1DiodeBridgeCapFilter, LS2DiodeBridgeCapFilter);
    // ------------------
    // --- Simulation ---
    // ------------------

    // -- (1) OneStepIntegrators --
    double theta = 0.5;
    double gamma = 0.5;
    SP::Moreau aOSI(new Moreau(theta, gamma));
    aOSI->insertDynamicalSystem(LS1DiodeBridgeCapFilter);
    aOSI->insertDynamicalSystem(LS2DiodeBridgeCapFilter);
    aOSI->setUseGammaForRelation(true);
    // -- (2) Time discretisation --
    SP::TimeDiscretisation aTiDisc(new TimeDiscretisation(t0, h_step));
    // -- (3) Non smooth problem
    SP::LCP aLCP(new LCP());
    // -- (4) Simulation setup with (1) (2) (3)
    SP::TimeStepping aTS(new TimeStepping(aTiDisc, aOSI, aLCP));

    // Initialization
    cout << "====> Initialisation ..." << endl << endl;
    DiodeBridgeCapFilter->initialize(aTS);
    cout << " ---> End of initialization." << endl;


    int k = 0;
    double h = aTS->timeStep();
    int N = ceil((T - t0) / h); // Number of time steps

    // --- Get the values to be plotted ---
    // -> saved in a matrix dataPlot
    SimpleMatrix dataPlot(N, 7);

    // For the initial time step:

    // time
    dataPlot(k, 0) = DiodeBridgeCapFilter->t0();

    // inductor voltage
    dataPlot(k, 1) = (*LS1DiodeBridgeCapFilter->x())(0);

    // inductor current
    dataPlot(k, 2) = (*LS1DiodeBridgeCapFilter->x())(1);

    // diode R1 current
    dataPlot(k, 3) = (InterDiodeBridgeCapFilter->getLambda(0))(0);

    // diode R1 voltage
    dataPlot(k, 4) = -(*InterDiodeBridgeCapFilter->y(0))(0);

    // diode F2 voltage
    dataPlot(k, 5) = -(InterDiodeBridgeCapFilter->getLambda(0))(1);

    // diode F1 current
    dataPlot(k, 6) = (InterDiodeBridgeCapFilter->getLambda(0))(2);

    // --- Compute elapsed time ---
    boost::timer t;
    t.restart();
    // --- Time loop  ---
    while (k < N - 1)
    {
      // get current time step
      k++;

      // solve ...
      aTS->computeOneStep();

      // --- Get values to be plotted ---
      // time
      dataPlot(k, 0) = aTS->nextTime();

      // inductor voltage
      dataPlot(k, 1) = (*LS1DiodeBridgeCapFilter->x())(0);

      // inductor current
      dataPlot(k, 2) = (*LS1DiodeBridgeCapFilter->x())(1);

      // diode R1 current
      dataPlot(k, 3) = (InterDiodeBridgeCapFilter->getLambda(0))(0);

      // diode R1 voltage
      dataPlot(k, 4) = -(*InterDiodeBridgeCapFilter->y(0))(0);

      // diode F2 voltage
      dataPlot(k, 5) = -(InterDiodeBridgeCapFilter->getLambda(0))(1);

      // diode F1 current
      dataPlot(k, 6) = (InterDiodeBridgeCapFilter->getLambda(0))(2);

      aTS->nextStep();

    }


    // --- elapsed time computing ---
    cout << "time = " << t.elapsed() << endl;

    // Number of time iterations
    cout << "Number of iterations done: " << k << endl;

    // dataPlot (ascii) output
    ioMatrix::write("DiodeBridgeCapFilter.dat", "ascii", dataPlot, "noDim");
  }

  // --- Exceptions handling ---
  catch (SiconosException e)
  {
    cout << "SiconosException" << endl;
    cout << e.report() << endl;
  }
  catch (std::exception& e)
  {
    cout << "Exception: " << e.what() << endl;
    exit(-1);
  }
  catch (...)
  {
    cout << "Exception caught " << endl;
  }
}
