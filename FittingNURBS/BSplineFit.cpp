//===============================================================
//  Computer-Aided Design & Computer-Aided Manufacturing, 1999
//
// (C) 1999 Chungnam National University
//          Dept of Naval Architecture and Ocean Engineering
//
//  Program Name: BSplineFit.cpp
//  Version 1.0, 11/30/99, HUS
//================================================================
/*

  Object: Fitting Existing Data with B-splines

  Given data    : a set of N^v base points.
  Required eqns : x(u) = SUM[ i = 0 : N^v-1 ] Xi   * Nip(u)
                  y(u) = SUM[ i = 0 : N^v-1 ] Etai * Nip(u)  (87)


  1) To find Xi and Etai, 
     obtain a set of simultaneous equations for the
     unknown vertex locations Xii, Etai

     unknown : u

  2) Select u by polygonal arc length
     
     S(0) = 0
     Sn = Sn-1 + sqrt((Xn-Xn-1)**2 + (Yn-Yn-1)**2), n = 1,...,N^v-1   
     
  XY data
  i=0    0.0000    0.0000
  i=1   30.0000    0.5000
  i=2   60.0000    0.8660
  i=3   90.0000    1.0000
  i=4  120.0000    0.8660
  i=5  150.0000    0.5000
  i=6  180.0000    0.0000
  
  
  Polygonal arc length
  [ 0]  =+0.0000   [ 1]  =+30.0042  [ 2]  =+60.0064  [ 3]  =+90.0067  
  [ 4]  =+120.0070 [ 5]  =+150.0092 [ 6]  =+180.0134 
  
  parameter u
  [ 0]  =+0.0000   [ 1]  =+0.6667   [ 2]  =+1.3334   [ 3]  =+2.0000   
  [ 4]  =+2.6666   [ 5]  =+3.3333   [ 6]  =+4.0000   

  Knot vector(U)
  [  0]  =+0.0000   [  1]  =+0.0000   [  2]  =+0.0000   [  3]  =+0.0000   
  [  4]  =+1.0000   [  5]  =+2.0000   [  6]  =+3.0000   [  7]  =+4.0000   
  [  8]  =+4.0000   [  9]  =+4.0000   [ 10]  =+4.0000   
  
  Coefficient matrix
  i=0   1.0000   0.0000   0.0000   0.0000   0.0000   0.0000   0.0000
  i=1   0.0370   0.5185   0.3951   0.0494   0.0000   0.0000   0.0000
  i=2   0.0000   0.0741   0.5494   0.3704   0.0062   0.0000   0.0000
  i=3   0.0000   0.0000   0.1667   0.6667   0.1667   0.0000   0.0000
  i=4   0.0000   0.0000   0.0062   0.3704   0.5494   0.0741   0.0000
  i=5   0.0000   0.0000   0.0000   0.0494   0.3951   0.5185   0.0370
  i=6   0.0000   0.0000   0.0000   0.0000   0.0000   0.0000   1.0000
  
  
  GCV
  i=0    0.0000    0.0000
  i=1   14.9989    0.2597
  i=2   44.9966    0.7863
  i=3   90.0000    1.1069
  i=4  135.0034    0.7863
  i=5  165.0011    0.2597
  i=6  180.0000    0.0000
  
*/
#include <fstream.h>        //..header for file i/o
#include <iomanip.h>        //..header for file i/o manipulation
#include "ldebug.h"         //..  
#include "proplibd.h"       //..header for propeller library
#include "bsplinelib.h"     //..header for B-spline library
#include <math.h>           //..header for math library

#define pi_ 3.14159265358979
#define square(x) ((x)*(x))
#define toradian(x) ((x)*pi_/180.0)

void main(void) {

  int nv, p, i;
  const double xmax = 180.0;
  ofstream res("res.out");
  car2d xy;

  p = 3;
  nv = 7;
  xy.setdimsize(nv, 2);

  double delx = xmax / double(nv-1);

  for(i = 0; i < nv; i++) {
    xy[i][0] = double(i)*delx;
    xy[i][1] = sin(toradian(xy[i][0]));
  }
/*
	xy[0][0] = -4.000;
	xy[1][0] = 0.000;  
	xy[2][0] = 3.037; 
	xy[3][0] = 5.941;  
	xy[4][0] = 7.769;
	xy[5][0] = 8.406; 
	xy[6][0] = 8.948;  
	xy[7][0] = 9.075;
	xy[8][0] = 8.789;   
	xy[9][0] = 7.705;
	xy[10][0] = 5.941;
	xy[11][0] = 3.037;
	xy[12][0] = 0.000; 
	xy[13][0] = 0.000; 
	xy[14][0] = 0.034; 
	xy[15][0] = 0.524;  
	xy[16][0] = 1.267;  
	xy[17][0] = 3.037;
	xy[18][0] = 5.941; 
	
	xy[0][1] = 0.000;
	xy[1][1] = 1.252;  
	xy[2][1] = 2.340; 
	xy[3][1] = 4.206;  
	xy[4][1] = 6.000;
	xy[5][1] = 7.000; 
	xy[6][1] = 8.000;  
	xy[7][1] = 9.000;
	xy[8][1] = 10.000;   
	xy[9][1] = 11.000;
	xy[10][1] = 11.198;
	xy[11][1] = 11.516;
	xy[12][1] = 11.947; 
	xy[13][1] = 12.300; 
	xy[14][1] = 13.000; 
	xy[15][1] = 14.500;  
	xy[16][1] = 16.000;  
	xy[17][1] = 18.640;
	xy[18][1] = 23.013;
*/
  res << "\nXY data\n" << xy << endl;
	
  // polygonal arc length
  cvecd s(nv);
  s[0] = 0.0;
  for(int j = 1; j < nv; j++) {
    s[j] = s[j-1] + sqrt(square(xy[j][0] - xy[j-1][0]) + 
                         square(xy[j][1] - xy[j-1][1]));

  }
  res << "\nPolygonal arc length\n"
      << s << endl;

  cvecd u(nv);
  for(j = 0; j < nv; j++) {
    u[j] = ( double(nv) - double(p)) / s[nv-1] * s[j];
}
  res << "parameter u\n" << u << endl;

  cvecd U(nv + p + 1);
  ComputeUniformKnotVector(nv-1, p, U);
  for(i=0;i<nv+p+1;i++)
  {
}
  res << "\nKnot vector\n" << U << endl;

  car2d A(nv, nv);
  cvecd N(p+1);
  for(j = 0; j < nv; j++) {
    int span = FindSpan(nv-1, p, u[j], U);
    BasisFuns(span, u[j], p, U, N); 
    for(int a=0; a<=p; a++) {
      A[j][span-p+a] = N[a];
   }
  }


  res << "\nCoefficient matrix\n" << A << endl;

  car2d ALUD(nv, nv);
  car2d P(nv, 2);
  cvecd rhs(nv);
  cveci pivot(nv);
  double plusminusone;
  // Xi  *P = Y(ui)
  // Etai*P = Y(ui) 
  //..solve simultaneous equation by LU Decomposition..
  ludcmp(A, ALUD, nv, pivot, plusminusone);  


  for(j = 0; j < 2; j++) {
    for(i = 0; i < nv; i++) rhs[i] = xy[i][j];
    lubksb(ALUD, nv, pivot, rhs);
    for(i = 0; i < nv; i++) P[i][j] = rhs[i];
  }

  res << "\nGCV\n" << P << endl;
  res.close();

  ofstream fig60("fig60.dat");
  fig60.setf(ios::showpoint | ios::right | ios::fixed);
  fig60.precision(6);
  fig60 << "variables = x, y\n"
        << "zone t = \"Input Points\", i = " << nv << endl;
  for(j = 0; j < nv; j++) 
    fig60 << setw(10) << xy[j][0] << ' '
          << setw(10) << xy[j][1] << endl;

  fig60 << "zone t = \"B-spline Control Polygon\", i = " << nv << endl;
  for(j = 0; j < nv; j++) 
    fig60 << setw(10) << P[j][0] << ' '
          << setw(10) << P[j][1] << endl;


  int nuout = 50;
  cvecd uout(nuout), point(2);
  double maxu = double(nv - p);
  double delu = maxu / double(nuout-1);
//  printf("%lf, %lf\n", maxu, double(nuout-1));
  for(i = 0; i < nuout; i++)
  {
   uout[i] = double(i) * delu;
 }

  fig60 << "zone t = \"Evaluated B-spline\", i = " << nuout << endl;
  for(i = 0; i < nuout; i++) {
    CurvePoint1P (
      nv-1, 
      p, 
      U, 
      P, 
      uout[i], 
      point, 
      2
    );
    fig60 << setw(10) << point[0] << ' '
          << setw(10) << point[1] << endl;
  }
}