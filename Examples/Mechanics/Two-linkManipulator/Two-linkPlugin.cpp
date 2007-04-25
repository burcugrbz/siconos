/* Siconos-sample version 2.0.1, Copyright INRIA 2005-2006.
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

#include <stdio.h>
#include <math.h>

#define PI 3.14159265

double l1 = 0.5;//length of the first link
double l2 = 0.5;//length of the second link
double m1 = 1; //mass of the first link
double m2 = 1; //mass of the second link
double I1 = 1;// the moment of inertia of the first link about the axis that passes through the center of mass (parallel to the Z axis)
double I2 = 1;// the moment of inertia of the second link about the axis that passes through the center of mass (parallel to the Z axis)
double g = 9.8;//gravitational acceleration
double gamma2 = 0.5;
double gamma1 = 5;
double P = 10;


extern "C" void mass(unsigned int sizeOfq, const double *q, double *mass, double* param)
{
  mass[0]  = m1 * (l1 * l1 / 4) + I1 + I2 + m2 * (l1 * l1 + (l2 * l2 / 4) + l1 * l2 * cos(q[1]));
  mass[1]  = I2 + m2 * l2 * l2 / 4 + m2 * l1 * l2 * cos(q[1]) / 2;
  mass[2]  = I2 + m2 * l2 * l2 / 4 + m2 * l1 * l2 * cos(q[1]) / 2;
  mass[3]  = I2 + m2 * l2 * l2 / 4;
}

extern "C" void NNL(unsigned int sizeOfq, const double *q, const double *velocity, double *NNL, double* param)
{
  NNL[0] = -m2 * l1 * l2 * sin(q[1]) * (velocity[0] * velocity[1] + velocity[1] * velocity[1] / 2) + g * (l1 * (m1 / 2 + m2) * cos(q[0]) + m2 * l2 * cos(q[0] + q[1]) / 2);
  NNL[1] = m2 * l1 * l2 * sin(q[1]) * velocity[0] * velocity[0] / 2 + g * m2 * l2 * cos(q[1] + q[0]) / 2;
}


extern "C" void U(unsigned int sizeOfq, double time, double *U, double* z)
{
  double m11 = m1 * (l1 * l1 / 4) + I1 + I2 + m2 * (l1 * l1 + (l2 * l2 / 4) + l1 * l2 * cos(z[1]));
  double m12 = (m2 * l2 * l2 / 4) + I2 + m2 * l1 * l2 * cos(z[1]) / 2;
  double m22 = (m2 * l2 * l2 / 4) + I2;

  double x = l1 * cos(z[0]) + l2 * cos(z[0] + z[1]);
  double y = l1 * sin(z[0]) + l2 * sin(z[0] + z[1]);

  double x1 = -l1 * sin(z[0]) * z[2] - l2 * sin(z[0] + z[1]) * (z[2] + z[3]);
  double y1 = l1 * cos(z[0]) * z[2] + l2 * cos(z[0] + z[1]) * (z[2] + z[3]);

  double grad11 = -y;
  double grad12 = -l2 * sin(z[0] + z[1]);
  double grad21 = x;
  double grad22 = l2 * cos(z[0] + z[1]);
  double det = grad11 * grad22 - grad12 * grad21;

  double d11 = grad22 / det;
  double d12 = -grad12 / det;
  double d21 = -grad21 / det;
  double d22 = grad11 / det;

  double dd11 =  -l1 * cos(z[0]) * z[2] - l2 * cos(z[0] + z[1]) * (z[2] + z[3]);
  double dd12 =  -l2 * cos(z[0] + z[1]) * (z[2] + z[3]);
  double dd21 =  -l1 * sin(z[0]) * z[2] - l2 * sin(z[0] + z[1]) * (z[2] + z[3]);
  double dd22 =  -l2 * sin(z[0] + z[1]) * (z[2] + z[3]);

  double mc11 = m11 * d11 + m12 * d21;
  double mc12 = m11 * d12 + m12 * d22;
  double mc21 = m12 * d11 + m22 * d21;
  double mc22 = m12 * d12 + m22 * d22;

  double qr11 = -(2 * PI / P) * 0.1 * sin(2 * PI * time / P) - gamma2 * (x - (0.65 + 0.1 * cos(2 * PI * time / P)));
  double qr12 = (2 * PI / P) * 0.1 * cos(2 * PI * time / P) - gamma2 * (y - 0.1 * sin(2 * PI * time / P));

  double qr21 = -(2 * PI / P) * (2 * PI / P) * 0.1 * cos(2 * PI * time / P) - gamma2 * (x1 + (2 * PI / P) * 0.1 * sin(2 * PI * time / P));
  double qr22 = -(2 * PI / P) * (2 * PI / P) * 0.1 * sin(2 * PI * time / P) - gamma2 * (y1 - (2 * PI / P) * 0.1 * cos(2 * PI * time / P));

  double s1 = x1 - qr11;
  double s2 = y1 - qr12;

  double a11 = mc11 * dd11 + mc12 * dd21;
  double a12 = mc11 * dd12 + mc12 * dd22;
  double a21 = mc21 * dd11 + mc22 * dd21;
  double a22 = mc21 * dd12 + mc22 * dd22;

  double a1 = -m2 * l1 * l2 * sin(z[1]) * z[3] * ((d11 * qr11 + d12 * qr12) + (d21 * qr11 + d22 * qr12) / 2) + g * (l1 * (m1 / 2 + m2) * cos(z[0]) + m2 * l2 * cos(z[0] + z[1]) / 2);
  double a2 = (a11 * d11 + a12 * d21) * qr11 + (a11 * d12 + a12 * d22) * qr12;
  double a3 = m2 * l1 * l2 * sin(z[1]) * z[2] * (d11 * qr11 + d12 * qr12) / 2 + g * m2 * l2 * cos(z[1] + z[0]) / 2;
  double a4 = (a21 * d11 + a22 * d21) * qr11 + (a21 * d12 + a22 * d22) * qr12;

  double T01 = mc11 * qr21 + mc12 * qr22;
  double T02 = a1 - a2;
  double T03 = grad11 * gamma1 * s1 + grad21 * gamma1 * s2;

  double T11 = mc21 * qr21 + mc22 * qr22;
  double T12 = a3 - a4;
  double T13 = grad12 * gamma1 * s1 + grad22 * gamma1 * s2;

  U[0] = T01 + T02 - T03;
  U[1] = T11 + T12 - T13;

}

extern "C" void jacobianQNNL(unsigned int sizeOfq, const double *q, const double *velocity, double *jacob, double* param)
{
  jacob[0] = 0;//-g*(l1*(m1/2+m2)*sin(q[0])+m2*l2*sin(q[0]+q[1])/2);
  jacob[1] = 0;//-g*m2*l2*sin(q[1]+q[0])/2;
  jacob[2] = -m2 * l1 * l2 * cos(q[1]) * (velocity[0] * velocity[1] + velocity[1] * velocity[1] / 2); //-g*m2*l2*sin(q[0]+q[1])/2 ;
  jacob[3] = (m2 * l1 * l2 * cos(q[1]) * velocity[0] * velocity[0] / 2); //-g*m2*l2*sin(q[1]+q[0])/2;
}

extern "C" void jacobianVNNL(unsigned int sizeOfq, const double *q, const  double *velocity, double *jacob, double* param)
{
  jacob[0] =   -m2 * l1 * l2 * sin(q[1]) * velocity[1];
  jacob[1] =   m2 * l1 * l2 * sin(q[1]) * velocity[0];
  jacob[2] =   -m2 * l1 * l2 * sin(q[1]) * (velocity[0] + velocity[1]);
  jacob[3] =  0;
}



extern "C" void h0(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, double* param)
{
  y[0] = 2 + l1 * cos(q[0]) + l2 * cos(q[0] + q[1]);
  y[1] = l1 * sin(q[0]) + l2 * sin(q[0] + q[1]);

}

extern "C" void G0(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, double* param)
{
  G[0] = 0;
  G[1] = l1 * cos(q[0]) + l2 * cos(q[0] + q[1]);
  G[2] = 0;
  G[3] = l2 * cos(q[0] + q[1]);
}

// extern "C" void h0(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, double* param)
// {
//     y[0] = l1*sin(q[0])+l2*sin(q[0]+q[1]);

// }

// extern "C" void G0(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, double* param)
// {
//   G[0] = l1*cos(q[0])+l2*cos(q[0]+q[1]);
//   G[1] = l2*cos(q[0]+q[1]);
// }

//extern "C" void h1(unsigned int sizeOfq, const double* q,const  double *velocity, unsigned int sizeOfY, double* x, double* param)
// {
//   x[0] = l1*cos(q[0])+l2*cos(q[0]+q[1]); // x
//   x[1] = l1*sin(q[0])+l2*sin(q[0]+q[1]); // y
//   x[2] = -l1*sin(q[0])*velocity[0]-l2*sin(q[0]+q[1])*(velocity[0]+velocity[1]); // x prime
//   x[3] = l1*cos(q[0])*velocity[0]+l2*cos(q[0]+q[1])*(velocity[0]+velocity[1]); // y prime
// }

// extern "C" void G1(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* H, double* param)
// {
//   H[0] = l1*cos(q[0])+l2*cos(q[0]+q[1]);
//   H[1] = -l1*sin(q[0])-l2*sin(q[0]+q[1]);
//   H[2] = l2*cos(q[0]+q[1]);
//   H[3] = -l2*sin(q[0]+q[1]);
// }

// extern "C" void hd(unsigned int sizeOfq, double time, unsigned int sizeOfY, double* xd, double* param)
// {
//   xd[0] =0.65+0.1*cos(2*3.14*time/T); // xd
//   xd[1] =0.1*sin(2*3.14*time/T);  // yd
// }

// extern "C" void Gd(unsigned int sizeOfq,double time, const double* q, unsigned int sizeOfY, double* Hd, double* param)
// {
//   Hd[0] = -(2*3.14/T)*0.1*sin(2*3.14*time/T);// xd prime
//   Hd[1] = (2*3.14/T)*0.1*cos(2*3.14*time/T); // yd prime
//   Hd[2] = -(2*3.14/T)*(2*3.14/T)*0.1*cos(2*3.14*time/T);// xd second
//   Hd[3] = -(2*3.14/T)*(2*3.14/T)*0.1*sin(2*3.14*time/T);// yd second
// }
// extern "C" void Qr1(unsigned int sizeOfq,double time, const double* q, unsigned int sizeOfY, double* qr, double* param)
// {
//   qr[0] = -(2*3.14/T)*0.1*sin(2*3.14*time/T)-gamma2*(l1*cos(q[0])+l2*cos(q[0]+q[1])-0.65+0.1*cos(2*3.14*time/T));//xr prime
//   qr[1] =(2*3.14/T)*0.1*cos(2*3.14*time/T)-gamma2*(l1*sin(q[0])+l2*sin(q[0]+q[1])-0.1*sin(2*3.14*time/T));//yr prime

// }

// extern "C" void Qr2(unsigned int sizeOfq, double time, const double* q,const  double *velocity, unsigned int sizeOfY, double* qrl, double* param)
// {
// //xr second
//   qrl[0] = -(2*3.14/T)*(2*3.14/T)*0.1*cos(2*3.14*time/T)-gamma2* (-l1*(sin(q[0])*velocity[0]-l2*sin(q[0]+q[1])*(velocity[0]+velocity[1])+(2*3.14/T)*0.1*sin(2*3.14*time/T)));
// //yr second
//   qrl[1] = -(2*3.14/T)*(2*3.14/T)*0.1*sin(2*3.14*time/T)-gamma2*(l1*cos(q[0])*velocity[0]+l2*cos(q[0]+q[1])*(velocity[0]+velocity[1])-(2*3.14/T)*0.1*cos(2*3.14*time/T));

// }
