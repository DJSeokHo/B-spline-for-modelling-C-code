/*
//--------------------------------------------------------
//..BSplinelib.cpp: Computes B-Spline Geometric Characteristics.
//  Method: Piegl and Tiller algorithm
//  Ref. Les Piegl and Wayne Tiller, 
//    "The NURBS Book," 2nd ed., Springer, 1996
//   1) CVector, CArray2d, ...  classes are implemented
//--------------------------------------------------------
// Symbols used in Piegl and Tiller:
//  p: Degree of polynomial; For cubic B-spline, p=3, (nOrder-1)
//  n: Number of control points(NCP) - 1; n+1= NCP
//  m: Number of knots(NK) - 1; m+1 = NK
//  m-n-p relation: m = n + p + 1;
//--------------------------------------------------------

*/

#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <iomanip.h>

///////////////////////////
#include "ldebug.h"
#include "hipandef.h"
///////////////////////////
#include "proplibd.h"
#include "bsplinelib.h"
///////////////////////////

#ifndef SKIP_COMMENT_LINE
#define SKIP_COMMENT_LINE ignore(80, '\n')
#endif

#ifndef CLEANUP_TRAILERS
#define CLEANUP_TRAILERS ignore(80, '\n')
#endif

const double TOLERANCE=double(1.0e-10);
//--------------------------------------------------------
int FindSpan(int n, int p, double u, CVector <double> &U)
{
  // Determine the knot span index, P&T p. 68
  // Input: n,p,u,U
  // Return: the knot span index
  //if (u==U[n+1]) return(n);  // Special case
  if (u>=U[n+1]) return(n);  // Special case
  //double tol=5.0e-5;
  //double diff = u-U[n+1];
  //diff = (diff>0) ? diff : -diff;
  //if (diff<tol) return(n);  // Special case

  int low = p;
  int high= n+1;  // Do binary search
  int mid = (low+high) / 2;
  while (u<U[mid] || u>=U[mid+1]) {
    if (u<U[mid]) high = mid;
    else	  low  = mid;
    mid = (low+high) / 2;
  }
  return(mid);
}

//--------------------------------------------------------
void BasisFuns(int iSpan, double u, int p, CVector <double> &U, 
               CVector <double> &N)
{
  //..Compute the nonvanishing basis function, P&T p.70
  //  Input: iSpan, u, p, U
  //  Output: N
  double saved, temp;
  CVector<double> left(p+1);
  CVector<double> right(p+1);
  int j, r;

  N[0] = 1.0;
  for (j=1; j<=p; j++) {
    left[j] = u - U[iSpan+1-j];
    right[j]= U[iSpan+j] - u;
    saved = 0.0;
    for (r=0; r<j; r++) {
      temp = N[r]/(right[r+1]+left[j-r]);
      N[r] = saved+right[r+1]*temp;
      saved = left[j-r]*temp;
    }
    N[j] = saved;
  }
}

//--------------------------------------------------------
void DersBasisFuns(int iSpan, double u, int p, int n,
		   CVector  <double> &U,
		   CArray2d <double> &ders)
{
  //..Piegl and Tiller, Algorithm (A2.3).
  //..Compute nonzero basis functions and their
  //  derivatives, up to and including the n-th
  //  derivatives (n<=p).
  //
  //  Input: iSpan, u, p, n, U
  //  Output: ders

  int j, k, r;
  double saved, temp;
  CVector<double> left(p+1);
  CVector<double> right(p+1);
  CArray2d<double> ndu(p+1, p+1);
  CArray2d<double> a(2, p+1);

  //..Algoritm (A2.2) to compute nonzero basis functions
  ndu[0][0] = 1.0;
  for (j=1; j<=p; j++) {
    left[j] = u - U[iSpan+1-j];
    right[j] = U[iSpan+j] - u;
    saved = 0.0;
    for (r=0; r<j; r++) {
      //..Lower triangle
      ndu[j][r] = right[r+1] + left[j-r];
      temp = ndu[r][j-1]/ndu[j][r]; //....divide by zero...
      //..Upper triangle
      ndu[r][j] = saved + right[r+1]*temp;
      saved = left[j-r]*temp;
    }
    ndu[j][j] = saved;
  }

  int j1, j2, s1, s2, rk, pk;
  double d;
  for (j=0; j<=p; j++) //..Load the basis functions
    ders[0][j] = ndu[j][p];
  //..Compute the derivatives (Eq. [2.9])
  for (r=0; r<=p; r++) { //..Loop over function index
    s1=0; s2=1;  //..Alternate rows in array a
    a[0][0] = 1.0;
    //..Loop to compute k-th derivative
    for (k=1; k<=n; k++) {
      d = 0.0;
      rk = r - k;
      pk = p - k;
      if (r>=k) {
        a[s2][0] = a[s1][0] / ndu[pk+1][rk];
        d = a[s2][0] * ndu[rk][pk];
      }
      if (rk>=-1) j1 = 1;
      else	  j1 = -rk;
      if (r-1<=pk) j2 = k - 1;
      else	   j2 = p - r;
      for (j=j1; j<=j2; j++) {
        a[s2][j] = (a[s1][j] - a[s1][j-1]) / ndu[pk+1][rk+j];
        d += a[s2][j] * ndu[rk+j][pk];
      }
      if (r<=pk) {
        a[s2][k] = -a[s1][k-1] / ndu[pk+1][r];
        d += a[s2][k] * ndu[r][pk];
      }
      ders[k][r] = d;
      j=s1; s1=s2; s2=j;  //..Switch rows
    }
  }
  //..Multiply through by the correct factors, (Eq. [2.9])
  r = p;
  for (k=1; k<=n; k++) {
    for (j=0; j<=p; j++) ders[k][j] *= r;
    r *= (p - k);
  }
}

//------------------------------------------------------------------
int ComputeUniformKnotVector(const int n, const int p, 
                             CVector <double> &knot)
{
  int i, j;
  int m = n + p + 1;
  double maxknotvalue = double((m) - 2*(p+1) + 2);
  //..Allocate memory.........
  //knot = new double[m+1];
  for (j=0; j<=p; j++) {
    knot[j] = 0.0;
    knot[m-j] = maxknotvalue;
  }
  for (j=p+1, i=1; j<=n; j++) {knot[j] = double(i++);}
  return (m+1);
}//..ComputeUniformKnotVector()


//------------------------------------------------
void getIJTec(ifstream &fin, int &itec, int &jtec)
{
  int i=0, j=0, lengbuf=0;
  char buf[256], *noblank;
  fin.getline(buf, 256, '\n');
  itec = 0; jtec =0;
  noblank = new char[lengbuf = strlen(buf)];
  for (i=0, j=0; j<lengbuf; j++) {
    if (!isspace(buf[j])) {
      noblank[i] = tolower(buf[j]);
      i++;
    }
  }
  noblank[i] = NULL;
  getIJStr(noblank, itec, jtec);
  delete [] noblank;
  return;
}

#define _LENGTH_ 80
#define _DELIMETER_ '\n'
//---------------------------------------------------------------
void getIJTec(ifstream &fstrm, int &itec, int &jtec, int ithzone)
{
  int i = 0, j = 1, lengbuf = 0;
  char buf[_LENGTH_], noblank[_LENGTH_];

  noblank[0] = NULL;

  do {
    fstrm.getline(buf, _LENGTH_, _DELIMETER_);
    if(strstr(buf, "zone")) {
      lengbuf = strlen(buf);
      if ( j != ithzone ) { j++; continue; }
      for ( i = 0, j = 0; j < lengbuf; j++)
        if(!isspace(buf[j])) noblank[i] = tolower(buf[j]), i++;
      noblank[i] = NULL;
      break;
    }
  } while (!fstrm.eof());

  if ( noblank[0] == NULL ) { itec = 0, jtec = 0; return; }
  getIJStr(noblank, itec, jtec);
  return;
}

//------------------------------------------------
void getIJStr(char *noblank, int &ival, int &jval)
{
  unsigned int i=0;
  char ibuf[10], jbuf[10], *p;

  //..get the number of i; if "i=" not exist, ival will be set by zero.
  if ((p = strstr(noblank, "i="))==NULL) {
    ival = 0;
    p = noblank;
  } else{
     ++++p;  i = 0;
    while (isdigit(ibuf[i++] = *p++));
    ibuf[i] = NULL, --p;
    ival = atoi(ibuf);
  }

  //..get the number of j; if "j=" not exist, jval will be set by zero.
  if ((p = strstr(p, "j="))==NULL) {
    jval = 0;
  } else{
    ++++p; i = 0;
    while (isdigit(jbuf[i++] = *p++));
    jbuf[i] = NULL;
    jval = atoi(jbuf);
  }
}

//--------------------------------------------------------
double Distance3D(double a[], double b[])
{
  //..Distance in 3-D coord.
  double d;
  d  = (a[0]-b[0])*(a[0]-b[0]);
  d += (a[1]-b[1])*(a[1]-b[1]);
  d += (a[2]-b[2])*(a[2]-b[2]);
  return sqrt(d);
}

//--------------------------------------------------------
void MatrixTranspose(CArray2d <double> &M, int mrows, int mcols, CArray2d <double> &T)
{
  int i,j;
  for (i=0; i<mrows; i++)
    for (j=0; j<mcols; j++)
      T[j][i] = M[i][j];
}

//--------------------------------------------------------
int MatrixMultiplication(CArray2d <double> &M, int mrows, int mcols,
			 CArray2d <double> &N, int nrows, int ncols,
			 CArray2d <double> &W)
{
  if (mcols!=nrows) return (-1); //..error code
  int i,j,k;
  for (i=0; i<mrows; i++) {
    for (j=0; j<ncols; j++) {
      W[i][j] = 0.0;
      for (k=0; k<mcols; k++) {
        W[i][j] += M[i][k] * N[k][j];
      }
    }
  }
  return 0;
}

//--------------------------------------------------------

void MatrixInverse(CArray2d <double> &M, int mrows, CArray2d <double> &MI)
{
  int i, j;
  CArray2d<double> ALUD(mrows, mrows);
  CVector<int> pivot(mrows);
  CVector<double> b(mrows);
  double plusminusone;

  ludcmp(M, ALUD, mrows, pivot, plusminusone);
  for (j=0; j<mrows; j++) {
    for (i=0; i<mrows; i++) {b[i] = 0.0;}
    b[j] = 1.0;
    lubksb(ALUD, mrows, pivot, b);
    for (i=0; i<mrows; i++) {MI[i][j] = b[i];}
  }
}

//--------------------------------------------------------------------------------
void MatrixSubstraction(int mrows, int mcols, CArray2d <double> &M,
			CArray2d <double> &N, CArray2d <double> &W)
{
  int i,j;
  for (i=0; i<mrows; i++) {
    for(j=0; j<mcols; j++) {
      W[i][j] = M[i][j] - N[i][j];
    }
  }
}

//--------------------------------------------------------
int B4FitForFoilCW(CArray2d <double> &Q,
		   int r,
		   CVector  <double> &Wq,
		   CArray2d <double> &D,
		   int s,
		   CVector  < int  > &I,
		   CVector  <double> &Wd,
		   int n,
		   int p,
		   CVector  <double> &U,
		   CArray2d <double> &P,
		   CVector <double> &ub,
		   int dimen)
{
  //////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////
  // dimen = 7 for 7D-coord for propeller application
  // xOffset[][7]
  //  Q[][0],[1],[2]: contains x,y,z-coord info
  //  Q[][3]: 4th dimension contains chordwise spacing info
  //	      Q[][0] varies from 1 to zero to 1..
  //	 [4][5][6]: contains Uin at offset points
  //  P[][]: returns control point info
  //	     P[][3] used for both dimen==3 and dimen==7
  //	     If dimen==7, P[][z] returns z-th coord, for z=0,1,2
  //				 s-coord for z=3
  //				 Ux,y,z vertices for z=4,5,6
  // This complexity is caused by using this function for both
  //   3-D planar wing and 3-D propeller blades whose x-coord
  //   can not be any longer be the base coord for B-spline
  //   fitting..need clean up later for propeller version...
  //////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////
  //..This program is identical to B4FitForFoil() except the
  //  numbering of the input Q is made in the clockwise
  //  direction.
  //..Weighted least square curve fit for foil section..
  //  Original: Converted from Kerwin's B4FIT.FOR
  //  New feature: Weighting and constraining options are added.
  //  Ref. 1) Kerwin, B4Fit.For
  //	   2) Piegl and Tiller algothrim (A9.6)
  //  Input: Q,r,Wq,D,s,I,Wd,n,p
  //  Output: U,P
  //  U[]: knot vector
  //  P[n+1][dimen]:  control point coordinates & chordwise coord
  //		      for B-Spline fitting
  //
  //  Q[r+1][dimen]: an array containing the points to fit,
  //		       (constrained and unconstrained)
  //  r: the upper index of Q[][dimen]
  //  Wq[r+1]: >0 if Q[i] is unconstrained, and Wq[i] is the weight
  //	       <0 if Q[i] is constrained
  //  D[s+1][dimen]: an array containing the derivatives;
  //		 s=-1 if no derivatives are specified
  //  s: there are s+1 derivatives in D[][dimen]
  //  I[s+1]:  an integer array; I[j] gives the index into Q[i] of
  //	       the point corresponding to the derivatives in D[j]
  //  Wd[s+1]: >0 if D[j] is unconstrained, and Wd[j] is the weight
  //  n: a fit with n+1 control points
  //  p: a fit with degree p curve.
  ofstream chk;
  chk.open("B4FitForFoilCW");
  chk.setf(ios::fixed | ios::showpoint);
  chk.precision(4);
  int i,j,k, mu2, mc2, jj;
  int ru = -1; int rc = -1;
  for (i=0; i<=r; i++) {
    if (Wq[i]>0.0) ru++;
    else	   rc++;
  }
  int su = -1; int sc = -1;
  for (j=0; j<=s; j++) {
    if (Wd[j]>0.0) su++;
    else	   sc++;
  }
  int mu = ru + su + 1; int mc = rc + sc + 1;
  if (mc>=n || mc+n>=mu+1) return (-1);  //..error code = -1

  //double *ub = new double[r+1];
  double big=1.0e06, half=0.5, zero=0.0, one=1.0, pi=3.1415927e00;
  double tol=TOLERANCE;
  double hun=1.0e02;
  CArray2d<double> nders(p+1, p+1);

  //...Set up arrays N,W,S,T,M
  CArray2d<double> N(mu+1, n+1);
  CArray2d<double> NT(n+1, mu+1);
  CArray2d<double> M(mc+1, n+1);
  CArray2d<double> S(mu+1, dimen);
  CArray2d<double> T(mc+1, dimen);
  CVector <double> W(mu+1);
  CArray2d<double> funs(2, p+1);
  CVector <double> Temp(p+1);
  CVector <double> Nu(p+1);
  CArray2d<double> DNu(p+1, p+1);

  //..Compute Uniform Knot Vector..
  int m = n + p + 1;
  double maxknotvalue = double((m) - 2*(p+1) + 2);
  for (j=0; j<=p; j++) {
    U[j] = 0.0;
    U[m-j] = maxknotvalue;
  }
  for (j=p+1, i=1; j<=n; j++) {U[j] = double(i++);}

  //..Find the minimum and maximum x coordinate of foil input data..
  double  xLE = big;
  int iLE;
  for (i=0; i<r+1; i++) {
    double Q0;
    if (dimen==3) {Q0=Q[i][0];}
    if (dimen==7) {Q0=Q[i][3];}
    if (Q0<xLE) {
      if (dimen==3) {xLE = Q[i][0];}
      if (dimen==7) {xLE = Q[i][3];}
      iLE = i;
    }
  }
  double  xTEL, xTEU;
  if (dimen==3) {xTEL = Q[0][0];xTEU = Q[r][0];}
  if (dimen==7) {xTEL = Q[0][3];xTEU = Q[r][3];}

  //..Find x-locations of vertices with cosine spacing..Adjust position-
  //  of pair of LE vertices(xVLE) to produce the desired xLE and find-
  //  parameter value uLE at the leading edge..
  double xVLE = xLE;
  double uLE = half * maxknotvalue;
  int nVH = (n+1) / 2;
  int jtry, ktry; int maxDeriv;
  int span, paramConverged, xConverged;
  double hChordU, hChordL, dtheta, cost,xCLE,dxdu,d2xdu;
  double x_computed, dx;
  CVector<double> xV(n+1);
  CVector<double> yRhs(r+1);

  //..Search the xVLE(control vertex near LE) giving xLE=0.
  jtry = 0;
  do {
    xConverged = 0;
    hChordU = half * (xTEU - xVLE);
    hChordL = half * (xTEL - xVLE);
    dtheta = pi / (nVH-1);
    for (i=0; i<nVH; i++) {
      cost = cos(double(i)*dtheta);
      xV[n-i] = xVLE + hChordU * (one + cost);
      xV[i] = xVLE + hChordL * (one + cost);
    }
    //..Search the parameter uLE where dx/du=0.
    ktry = 0;
    do {
      //..Use uLE,n,p, get Derivative up to 2nd degree..
      paramConverged = 0;
      span = FindSpan(n, p, uLE, U);
      DersBasisFuns(span, uLE, p, maxDeriv=2, U, nders);
      xCLE = dxdu = d2xdu = zero;
      for (j=0; j<=p; j++) {
        xCLE += nders[0][j] * xV[span-p+j];
        dxdu += nders[1][j] * xV[span-p+j];
        d2xdu += nders[2][j] * xV[span-p+j];
      }
      uLE -= dxdu/d2xdu;
      if (fabs(dxdu)<tol) {paramConverged=1; break;}
    } while(ktry++<30);
    if (paramConverged!=1) {
      cout << "LE Search error: xLE, xCLE, uLE="
	   << setw(10) << setprecision(5) << xLE
	      << setw(10) << setprecision(5) << xCLE
	      << setw(10) << setprecision(5) << uLE << endl;
      cout.flush();
      //return;
    }
    xVLE += -xCLE + xLE;
    if (fabs(xLE-xCLE)<tol * 10.0) {xConverged=1; break;}
  } while (jtry++<30);

  cout.precision(5);
  if (xConverged!=1) {
    cout << "LE Search error: xLE, xVCLE="
	 << setw(10) << xLE << setw(10) << xVLE << endl;
      //return (-1);
  }

  //..Find ub(x_data) for each input (x_data)point by iteration
  //  starting from the trailing edge on both the upper and lower
  //  surfaces.
  //  Then fill in the elements of the coefficient matrix N....
  for (i=0; i<r+1; i++) {
    if (i<iLE) { //..covers lower surface from TE..
      k = i;
      if (k==0) { ub[k] = zero;}
      else {ub[k] = ub[k-1];}
    } else if (i==r) { //..LE..
      k = iLE;
      ub[k] = uLE;
    } else{//..covers upper surface from TE..
      k = r + iLE - i;
      //if (k==r) {ub[k]
      if (k==r) {ub[k] = maxknotvalue;}
      else {ub[k] = ub[k+1];}
    }

    //..Search for parameter ubar[k] that satisfies
    //	|x_data[k]-x_computed[k]|<tol within tolerance
    ktry = 0;
    do {
      //..Use uLE,n,p, get Derivative up to 1st degree..
      paramConverged = 0;
      span = FindSpan(n, p, ub[k], U);
      DersBasisFuns(span, ub[k], p, maxDeriv=1, U, nders);
      x_computed = dxdu = zero;
      for (j=0; j<=p; j++) {
        x_computed += nders[0][j] * xV[span-p+j];
        dxdu += nders[1][j] * xV[span-p+j];
      }
      //cout << double(k) <<  "  " << ub[k] << endl;
      if (dimen==3) {dx = Q[k][0] - x_computed;}
      if (dimen==7) {dx = Q[k][3] - x_computed;}
      if (fabs(dx)<tol) {paramConverged=1; break;}
      if (k==iLE) {paramConverged=1;break;}
      if (dimen==3) {ub[k] += (Q[k][0] - x_computed)/dxdu;}
      if (dimen==7) {ub[k] += (Q[k][3] - x_computed)/dxdu;}
    } while(ktry++<200);
    cout.precision(5);
    if (paramConverged!=1) {
      double Qk;
      if (dimen==3) {Qk=Q[k][0];}
      if (dimen==7) {Qk=Q[k][3];}
      cout << "No ub[] convergence: "
	   << "\tk=" << k << "\tQk=" << Qk
	   << "\tx_computed=" << x_computed << endl;
      //return (-1);
    }
  }
  //..ub[k], k=0,...,r:  ubar vector is obtained..

  chk.precision(5);
  //..check u[]..
  for (i=0; i<r+1; i++) {
    double Q0,Q1;
    if (dimen==3) {Q0=Q[i][0];Q1=Q[i][0];}
    if (dimen==7) {Q0=Q[i][3];Q1=Q[i][3];}
    chk << "i=" << setw(4) << i << ", ubar[i],Qx,Qy="
        << setw(10) << ub[i]
        << setw(10) << Q0 << setw(10) << Q1 << endl;
  }

  //...........
  j = 0; //..current index into I[]
  mu2 = 0; mc2 = 0;  //..counters up to mu and mc.
  for (i=0; i<=r; i++) {
    span  = FindSpan(n,p,ub[i],U);
    int dflag = 0;
    if (j<=s)
      if (i==I[j]) dflag = 1;
    if (dflag==0) {
      BasisFuns(span, ub[i], p,U, Temp);
      for (jj=0; jj<=p; jj++) {funs[0][jj] = Temp[jj];}
    } else{
      DersBasisFuns(span,ub[i],p,1,U, DNu);
      for (jj=0; jj<=p; jj++) {
        funs[0][jj] = DNu[0][jj]; //..0-th derivative
        funs[1][jj] = DNu[1][jj]; //..first derivative
      }
    }
    if (Wq[i]>0.0) {
      //..Unconstrained point
      W[mu2] = Wq[i];
      for (jj=0; jj<=p; jj++) {N[mu2][span-p+jj] = funs[0][jj];}
      for (int z=0; z<dimen; z++) {
        S[mu2][z] = W[mu2] * Q[i][z];
      }
      mu2++;
    } else{
      //..Constrained point
      for (jj=0; jj<=p; jj++) {M[mc2][span-p+jj] = funs[0][jj];}
      for (int z=0; z<dimen; z++) {
        T[mc2][z] = Q[i][z];
      }
      mc2++;
    }
    if (dflag==1) {
      //..Derivative at this point
      if (Wd[j]>0.0) {
	//..Unconstrained derivative
	W[mu2] = Wd[j];
	for (jj=0; jj<=p; jj++) {N[mu2][span-p+jj] = funs[1][jj];}
	for (int z=0; z<dimen; z++) {
	  S[mu2][z] = W[mu2] * D[j][z];
	}
	mu2++;
      } else{
	//..Constrained derivative
	for (jj=0; jj<=p; jj++) {M[mc2][span-p+jj] = funs[1][jj];}
	for (int z=0; z<dimen; z++) {
	  T[mc2][z] = D[j][z];
	}
	mc2++;
      }
      j++;
    }//..dflag==1
  }//..end of for-loop i=0,...,r
  CArray2d<double> NTW(n+1, mu+1);
  MatrixTranspose(N, mu+1, n+1, NTW);
  for (j=0; j<mu+1; j++) {
    for (i=0; i<n+1; i++) {
      NTW[i][j] *= W[j];
    }
  }

  CArray2d<double> NTWN(n+1, n+1);
  CArray2d<double> NTWNInv(n+1, n+1);
  MatrixMultiplication(NTW,n+1,mu+1,  N,mu+1,n+1, NTWN);

  CArray2d<double> NTWS(n+1, dimen);
  MatrixMultiplication(NTW,n+1,mu+1,  S,mu+1,dimen, NTWS);

  CVector<double> b(n+1);
  //..LUDecompose NTWN matrix..
  CArray2d<double> ALUD(n+1, n+1);
  CVector<int> pivot(n+1);
  double plusminusone;

  ludcmp(NTWN, ALUD, n+1, pivot, plusminusone);

  //..Solve for the control points P[][dimen]..
  if (mc<0) {
    //..No constraints
    for (jj=0; jj<dimen; jj++) { //..3-/5-D coordinates..
      for (j=0; j<n+1; j++) {b[j] = NTWS[j][jj];}
      lubksb(ALUD, n+1, pivot, b);
      for (i=0; i<n+1; i++) {
	    P[i][jj] = b[i];
      }
    }
    return 0;
  }

  //..Compute (NTWN)-inverse
  MatrixInverse(NTWN, n+1, NTWNInv);

  CArray2d<double> MT(n+1,mc+1);
  MatrixTranspose(M, mc+1, n+1, MT);

  CArray2d<double> MNTWNInv(mc+1, n+1);
  MatrixMultiplication(M, mc+1, n+1, NTWNInv, n+1, n+1, MNTWNInv);
  //..Get coeff matrix to solve for Lagrange multiplier, Eq(9.75)
  CArray2d<double> LagrangeCoeffMatrix(mc+1, mc+1);
  MatrixMultiplication(MNTWNInv, mc+1, n+1, MT, n+1, mc+1,
		       LagrangeCoeffMatrix);

  //..Solve 3-/7-components..
  CArray2d<double> LagrangeRHS(mc+1, dimen);
  CArray2d<double> A(mc+1, dimen); //..Lagrange Multipliers
  MatrixMultiplication(MNTWNInv, mc+1, n+1, NTWS, n+1, dimen,
		       LagrangeRHS);
  MatrixSubstraction(mc+1,dimen, LagrangeRHS, T, LagrangeRHS);
  ludcmp(LagrangeCoeffMatrix, ALUD, mc+1, pivot, plusminusone);
  for (jj=0; jj<dimen; jj++) { //..3-/7-D coordinates..
    for (j=0; j<mc+1; j++) {b[j] = LagrangeRHS[j][jj];}
    lubksb(ALUD, mc+1, pivot, b);
    for (i=0; i<mc+1; i++) {A[i][jj] = b[i];}
  }
  //..Now solve for P[][dimen], using Eq.(9.74)..
  CArray2d<double> MTA(n+1, dimen);
  MatrixMultiplication(MT, n+1, mc+1, A, mc+1, dimen, MTA);
  MatrixSubstraction(n+1,dimen, NTWS, MTA, NTWS);
  if (dimen==3) {
    MatrixMultiplication(NTWNInv,n+1,n+1, NTWS,n+1,dimen, P);
  }
  if (dimen==7) {
    CArray2d<double> PPP(n+1,dimen);
    MatrixMultiplication(NTWNInv,n+1,n+1, NTWS,n+1,dimen, PPP);
    for (m=0; m<n+1; m++) {
      for (int z=0; z<dimen; z++) {
        P[m][z] = PPP[m][z];
      }
    }
  }
  return 0; //..ok
}

void SurfacePoint1P
     (
	int		   n,
	int		   p,
	CVector  <double> &U,
	int		   m,
	int		   q,
	CVector  <double> &V,
	CArray3d <double> &P,
	double		   u,
	double		   v,
	CVector <double>	&S)
{
  //..Piegl and Tiller, Algorithm (A3.5)
  //..Compute surface point
  //  Input: n,p,U, m,q,V, P,u,v
  //  Output: S

  CVector<double> Nu(p+1);
  CVector<double> Nv(q+1);

  int uspan = FindSpan(n,p,u,U);
  BasisFuns(uspan,u,p,U, Nu);
  int vspan = FindSpan(m,q,v,V);
  BasisFuns(vspan,v,q,V, Nv);

  double temp[3];
  int uind = uspan - p;

  S[0] = S[1] = S[2] = 0.0;

  for (int l=0; l<=q; l++) {
    temp[0] = temp[1] = temp[2] = 0.0;
    int vind = vspan - q + l;
    for (int k=0; k<=p; k++) {
      temp[0] += Nu[k] * P[vind][uind+k][0];
      temp[1] += Nu[k] * P[vind][uind+k][1];
      temp[2] += Nu[k] * P[vind][uind+k][2];
    }
    S[0] += Nv[l] * temp[0];
    S[1] += Nv[l] * temp[1];
    S[2] += Nv[l] * temp[2];
  }
}

/*
void SurfacePoint1P_Scalar
     (
	int		   n,
	int		   p,
	CVector  <double> &U,
	int		   m,
	int		   q,
	CVector  <double> &V,
	CArray2d <double> &P,
	double		   u,
	double		   v,
	double         &S)
{
  //..Piegl and Tiller, Algorithm (A3.5)
  //..Compute surface point
  //  Input: n,p,U, m,q,V, P,u,v
  //  Output: S

  CVector<double> Nu(p+1);
  CVector<double> Nv(q+1);

  int uspan = FindSpan(n,p,u,U);
  BasisFuns(uspan,u,p,U, Nu);
  int vspan = FindSpan(m,q,v,V);
  BasisFuns(vspan,v,q,V, Nv);

  double temp;
  int uind = uspan - p;

  S = 0.0;

  for (int l=0; l<=q; l++) {
    temp = 0.0;
    int vind = vspan - q + l;
    for (int k=0; k<=p; k++) {
      temp += Nu[k] * P[vind][uind+k];
    }
    S += Nv[l] * temp;
  }
}
*/

//--------------------------------------------------------
void GlobalCurveInterp
     (
       const int           n,
       CArray2d <double> & Q,
       const int           r,
       const int           p,
       int               & m,
       CVector  <double> & U,
       CArray2d <double> & P
     )
{
  //..Global interpolation through n+1 points
  //  Piegl and Tiller Algorithm (A9.1)
  //  Input: n, Q, r, p
  //  Output: m, U, P
  //  r: number of coordinates, 3 for 3-D.

  int i, k;
  double a[3], b[3];
  m = n + p + 1;

  //..Compute uk using Centripetal method, Eq.(9.6)
  CVector<double> uk(n+1);
  double d = 0.0;
  CVector<double> dist(n+1);

  for (k=1; k<=n; k++){
    for (i=0; i<3; i++) {
      a[i] = Q[k][i]; b[i] = Q[k-1][i];
    }
    dist[k] = Distance3D(a, b);
    d += dist[k];
  }

  uk[0] = 0.0;
  uk[n] = 1.0;
  for (k=1; k<=n-1; k++) {
    uk[k] = uk[k-1] + dist[k]/d;
  }

  //..Compute knot vectors using averaging technique..
  for (k=0; k<=p; k++) {
    U[k] = 0.0;
    U[m-k] = 1.0;
  }
  double sum;
  for (int j=1; j<=n-p; j++) {
    sum = 0.0;
    for (i=j; i<=j+p-1; i++) {
      sum += uk[i];
    }
    U[j+p] = sum / double(p);
  }

  //..Allocate and initialize Array A to zero
  CArray2d<double> A(n+1, n+1);
  CArray2d<double> ALUD(n+1, n+1);
  int span;
  CVector<double> N(p+1);
  for (i=0; i<=n; i++) {
    //..Set up coefficient matrix..
    span = FindSpan(n,p,uk[i],U);
    BasisFuns(span,uk[i],p,U,N); //..Get ith row
    for (k=0; k<=p; k++) {A[i][span-p+k] = N[k];}
  }
  CVector<double> rhs(n+1);
  CVector<int>	  pivot(n+1);
  double plusminusone;
  //..Use banded matrix solver later..
  //LUDecomposition(A,n+1,p-1);
  ludcmp(A,ALUD, n+1, pivot, plusminusone);
  for (i=0; i<r; i++) { //..r is the number of coordinates
    for (j=0; j<=n; j++) {
     rhs[j] = Q[j][i]; //..ith coordinate of Q[j]
    }
    lubksb(ALUD, n+1, pivot, rhs);
    for (j=0; j<=n; j++) P[j][i] = rhs[j];
  }
}

//--------------------------------------------------------
void GlobalSurfInterp
     (
	const int	   n,
	const int	   m,
    const int      r, //... added argument
	CArray3d <double> &Q,
	const int	   p,
	const int	   q,
	CVector  <double> &U,
	CVector  <double> &V,
	CArray3d <double> &P)
{
  //..Global surface interpolation..
  //  Piegl and Tiller Algorithm (A9.4)
  //  Input: n,m,Q,p,q
  //  Output: U,V,P
  int i, j, k, l, jj, errorcode = 0;
  CVector<double> uk(n+1);
  CVector<double> vl(m+1);
  double sum;

  errorcode = SurfMeshParams(n, m, Q, uk, vl);	//..get parameters
  if (errorcode<0) {
    cout << "GlobalSurfInterp():\n"
	 << "errorcode = " << errorcode
	 << " is raised in SurfMeshParams().\n";
  }

  //..Compute knot vector U[] using technique..
  for (k=0; k<=p; k++) {
    U[k] = 0.0;  U[n+p+1-k] = 1.0;
  }
  for (j=1; j<=n-p; j++) {
    sum = 0.0;
    for (i=j; i<=j+p-1; i++) {
      sum += uk[i];
    }
    U[j+p] = sum / double(p);
  }

  //..Compute knot vector V[] using averaging technique..
  for (k=0; k<=q; k++) {
    V[k] = 0.0;  V[m+q+1-k] = 1.0;
  }
  for (j=1; j<=m-q; j++) {
    sum = 0.0;
    for (i=j; i<=j+q-1; i++) {
      sum += vl[i];
    }
    V[j+q] = sum / double(q);
  }

  int mm;
  int bignm = ((n+1)>(m+1)) ? (n+1) : (m+1);
  CArray2d<double> QQ(n+1, r);
  CArray2d<double> RR(bignm, r);
  CArray2d<double> PP(m+1, r);
  CArray3d<double> R(m+1, n+1, r);

  for (l=m; l>=0; l--) {
    //..chordwise interpolation thru Q[l][0],...,Q[l][n]
    //	get R[l][n][3],...,R[l][n][3]
    for (i=0; i<=n; i++) {
      for (jj=0; jj<r; jj++) {QQ[i][jj] = Q[l][i][jj];}
    }
    GlobalCurveInterp(n, QQ, r, p, mm, U, RR);
    for (i=0; i<=n; i++) {
      for (jj=0; jj<r; jj++) {R[l][i][jj] = RR[i][jj];}
    }
  }
  for (i=n; i>=0; i--) {
    //..spanwise interpolation thru R[0][i],...,R[m][i]
    //	get P[0][i], ..., P[m][i]
    for (j=0; j<=m; j++) {
      for (jj=0; jj<r; jj++) {RR[j][jj] = R[j][i][jj];}
    }
    GlobalCurveInterp(m, RR, r, q, mm, V, PP);
    for (j=0; j<=m; j++) {
      for (jj=0; jj<r; jj++) {P[j][i][jj] = PP[j][jj];}
    }
  }
}

//--------------------------------------------------------
int SurfMeshParams
    (
       const int	  n,
       const int	  m,
       CArray3d <double> &Q,
       CVector	<double> &uk,
       CVector	<double> &vl
    )
//int SurfMeshParams(const int n, const int m, double ***Q,
//		     double *uk, double *vl)
{
  //..Compute parameters for global surfaces interpolation
  //  Piegl and Tiller Algorithm (A9.3)
  //  Input: n, m, Q
  //  Output: uk, vl
  int k, l, jj;
  double a[3], b[3], d, total;
  int cds_size = ((n+1)>(m+1)) ? (n+1) : (m+1);
  CVector<double> cds(cds_size);

  //..First get the uk..
  int num = m + 1; //..number of nondegenerate rows
  uk[0] = 0.0;
  uk[n] = 1.0;
  for (k=1; k<n; k++) {uk[k] = 0.0;}
  for (l=0; l<=m; l++) {
    total = 0.0;  //..total chord length of row
    for (k=1; k<=n; k++) {
      for (jj=0; jj<3; jj++) {
	a[jj] = Q[l][k][jj];
	b[jj] = Q[l][k-1][jj];
      }
      cds[k] = Distance3D(a, b);
      total += cds[k];
    }
    //if (total==0.0) num--;
    double totalabs;
    totalabs = (total-0.0) ? total : -total;
    if (totalabs<TOLERANCE) num--;
    else{
      d = 0.0;
      for (k=1; k<n; k++) {
	d += cds[k];
	uk[k] += d/total;
      }
    }
  }
  if (num==0) return(-1); //..return error code = -1
  for (k=1; k<n; k++) uk[k] /= double(num);
  //..Next, get the vl..
  num = n + 1; //..number of nondegenerate rows
  vl[0] = 0.0;
  vl[m] = 1.0;
  for (k=1; k<m; k++) {vl[k] = 0.0;}
  for (l=0; l<=n; l++) {
    total = 0.0;  //..total chord length of column
    for (k=1; k<=m; k++) {
      for (jj=0; jj<3; jj++) {
	a[jj] = Q[k][l][jj];
	b[jj] = Q[k-1][l][jj];
      }
      cds[k] = Distance3D(a, b);
      total += cds[k];
    }
    //if (total==0.0) num--;
    double totalabs;
    totalabs = (total-0.0) ? total : -total;
    if (totalabs<TOLERANCE) num--;
    else{
      d = 0.0;
      for (k=1; k<m; k++) {
	d += cds[k];
	vl[k] += d/total;
      }
    }
  }
  if (num==0) return(-2); //..return error code = -2
  for (k=1; k<m; k++) vl[k] /= double(num);

  return 0;
}

//--------------------------------------------------------
void GlobalSurfApproxFixednm
     (
	const int	   r,
	const int	   s,
	CArray3d <double> &Q,
	const int	   p,
	const int	   q,
	const int	   n,
	const int	   m,
	CVector  <double> &U,
	CVector  <double> &V,
	CArray3d <double> &P
     )
//void GlobalSurfApproxFixednm(const int r, const int s, double ***Q,
//		 const int p, const int q, const int n, const int m,
//		 double *U, double *V, double ***P)
{
//////////////////////////////////////
//////////////////////////////////////
// Note Uniform Knot Vector is used
//////////////////////////////////////
//////////////////////////////////////
  //..Global surface approx with fixed num of ctrl pts
  //  Piegl and Tiller Algorithm (A9.7)
  //  Input: r,s,Q,p,q,n,m
  //  Output: U[n+p+2],V[m+q+2],P[m+1][n+1][3]
  //
  ofstream chk;
  chk.open("GlobalSurfApproxFixednm");
  chk.setf(ios::showpoint | ios::fixed);
  chk.precision(5);

  int i,j,k, errorcode = 0, jj;
  CVector<double> ub(r+1);
  CVector<double> vb(s+1);
  int bigrsM = ((r-1)>(s-1)) ? (r-1) : (s-1);
  CVector<double> N0p(bigrsM);
  CVector<double> Nnp(bigrsM);
  int bigpq = ((p+1)>(q+1)) ? (p+1) : (q+1);
  CVector<double> NN(bigpq);
  int bignmM = ((n-1)>(m-1)) ? (n-1) : (m-1);
  CVector<double> b(bignmM);
  int span, row;

  errorcode = SurfMeshParams(r,s,Q,ub,vb);

  if (errorcode<0) {
    cout << "GlobalSurfApproxFixednm():\n"
	 << "errorcode = " << errorcode
	 << " is raised in SurfMeshParams().\n";
  }

  //..Compute knot vectors U[] and V[] using Eq. (9.69)..
//  ComputeKnotVectorUsingEq_9_69(r, p, n, ub, U);
//  ComputeKnotVectorUsingEq_9_69(s, q, m, vb, V);
////////////////////////////////////////////////////////////////
  ComputeUniformKnotVector(n, p, U);
  ComputeUniformKnotVector(m, q, V);
  for (i=0; i<n+p+2; i++) {U[i] /= U[n+p+1];}
  for (i=0; i<m+q+2; i++) {V[i] /= V[m+q+1];}
////////////////////////////////////////////////////////////////
  chk << "\n ub/vb vectors...\n";
  for (i=0; i<r+1; i++) {
    chk << "i=" << setw(4) << i << setw(10) << ub[i] << endl;
  }
  chk << endl;
  for (i=0; i<s+1; i++) {
    chk << "i=" << setw(4) << i
	<< setw(10) << setprecision(5) << vb[i] << endl;
  }
  chk << "\n U/V knot vectors...\n";
  for (i=0; i<n+p+2; i++) {
    chk << "i=" << setw(4) << i << setw(10) << U[i] << endl;
  }
  chk << endl;
  for (i=0; i<m+q+2; i++) {
    chk << "i=" << setw(4) << i << setw(10) << V[i] << endl;
  }
  //========================================//
  //  Interpolate in the chordwise direction
  //========================================//

  //..Construct Nu-matrix
  CArray2d<double> Nu(r-1,n-1);

  row = 0;
  for (j=1; j<=r-1; j++, row++) {
    N0p[row] = 0.0;
    Nnp[row] = 0.0;
    span = FindSpan(n,p,ub[j],U);
    BasisFuns(span, ub[j], p, U, NN);
    //BasisFuns(span, ub[j], p, U, &NN);
    for (jj=0; jj<=p; jj++) {
      if ((span-p+jj)==0) {
	N0p[row] = NN[0];
      } else if ((span-p+jj)==n) {
	Nnp[row] = NN[p];
      } else{
	Nu[row][span-p+jj-1] = NN[jj];
      }
    }
  }
  //cout << endl << "Nu[][]" << endl << Nu << endl;
  CArray2d<double> NuT(n-1,r-1);
  MatrixTranspose(Nu, r-1,n-1, NuT);
  //MatrixTranspose(&Nu, r-1,n-1, &NuT);

  CArray2d<double> NTNu(n-1,n-1);
  MatrixMultiplication(NuT, n-1,r-1, Nu,r-1,n-1, NTNu);
  //MatrixMultiplication(&NuT, n-1,r-1, &Nu,r-1,n-1, &NTNu);

  //..LUDecompose NTNu..
  CArray2d<double> ALUD(n-1,n-1);
  CVector<int> pivot(n-1);
  double plusminusone;

  ludcmp(NTNu, ALUD, n-1, pivot, plusminusone);
  //ludcmp(&NTNu, &ALUD, n-1, &pivot, &plusminusone);

  int bigrs = ((r+1)>(s+1)) ? (r+1) : (s+1);
  CArray2d<double> R(bigrs,3);

  CArray2d<double> Ru(n-1,3);
  //..Temp: storage of control points after u-wise interpolation..
  CArray3d<double> Temp(n+1,s+1,3);

  //..Covers spanwise stations..
  for (j=0; j<=s; j++) {
    //..u-direction fit..
    for (jj=0; jj<3; jj++) { //..First and last points are fixed..
      Temp[0][j][jj] = Q[j][0][jj];
      Temp[n][j][jj] = Q[j][r][jj];
    }
    //..Build remainder vector using Eq.(9.63)..
    row = 0;
    for (k=1; k<=r-1; k++, row++) {
      for (i=0; i<3; i++) { //..3 coord.
        R[k][i] = Q[j][k][i] - N0p[row]*Q[j][0][i]
			     - Nnp[row]*Q[j][r][i];
      }
    }

    //..Assemble RHS vector by matrix product: NuT * R..
    row = 0;
    for (k=1; k<=n-1; k++, row++) {
      for (i=0; i<3; i++) {Ru[row][i] = 0.0;}
      for (i=0; i<3; i++) { //..3 coordinates
      for (jj=0; jj<r-1; jj++) {
        Ru[row][i] += NuT[row][jj] * R[jj+1][i];
	   }
      }
    }

    //..Back-substitution..
    for (i=0; i<3; i++) { //..3-D coordinates..
      for (k=0; k<n-1; k++) {b[k] = Ru[k][i];}
      //lubksb(&ALUD, n-1, &pivot, &b);
      lubksb(ALUD, n-1, pivot, b);
      for (k=0; k<n-1; k++) {Temp[k+1][j][i] = b[k];}
    }
  }//..spanwise j-loop ends here.


  //=======================================//
  //  Interpolate in the spanwise direction
  //=======================================//

  //..Construct Nv-matrix
  CArray2d<double> Nv(s-1,m-1);

  row = 0;
  for (j=1; j<=s-1; j++, row++) {
    N0p[row] = 0.0;
    Nnp[row] = 0.0;
    span = FindSpan(m,q,vb[j],V);
    BasisFuns(span, vb[j], q, V, NN);
    //BasisFuns(span, vb[j], q, V, &NN);
    for (jj=0; jj<=q; jj++) {
      if ((span-q+jj)==0) {
	N0p[row] = NN[0];
      } else if ((span-q+jj)==m){
	Nnp[row] = NN[q];
      } else{
	Nv[row][span-q+jj-1] = NN[jj];
      }
    }
  }

  CArray2d<double> NvT(m-1,s-1);
  MatrixTranspose(Nv, s-1,m-1, NvT);
  //MatrixTranspose(&Nv, s-1,m-1, &NvT);

  CArray2d<double> NTNv(m-1,m-1);
  MatrixMultiplication(NvT, m-1,s-1, Nv,s-1,m-1, NTNv);
  //MatrixMultiplication(&NvT, m-1,s-1, &Nv,s-1,m-1, &NTNv);

  //..LUDecompose NTNv..
  CArray2d<double> ALUDv(m-1,m-1);
  CVector<int> pivotv(m-1);

  //ludcmp(&NTNv, &ALUDv, m-1, &pivotv, &plusminusone);
  ludcmp(NTNv, ALUDv, m-1, pivotv, plusminusone);
  for (i=0; i<bigrs; i++) {
    for (j=0; j<3; j++) {R[i][j] = 0.0;}
  }

  CArray2d<double> Rv(m-1,3);

  //..Covers chordwise control points..
  for (i=0; i<=n; i++) {
    //..v-direction fits..
    for (jj=0; jj<3; jj++) { //..First(Hub) and last(tip) points are fixed..
      P[0][i][jj] = Temp[i][0][jj];
      P[m][i][jj] = Temp[i][s][jj];
    }
    //..Build remainder vector using Eq.(9.63)..
    row = 0;
    for (k=1; k<=s-1; k++, row++) {
      for (jj=0; jj<3; jj++) { //..3 coord.
	R[k][jj] = Temp[i][k][jj] - N0p[row]*Temp[i][0][jj]
				  - Nnp[row]*Temp[i][s][jj];
      }
    }

    //..Assemble RHS vector by matrix product: NvT * R..
    int ii;
    row = 0;
    for (k=1; k<=m-1; k++, row++) {
      for (ii=0; ii<3; ii++) {Rv[row][ii] = 0.0;}
      for (ii=0; ii<3; ii++) { //..3 coordinates
      for (jj=0; jj<s-1; jj++) {
       Rv[row][ii] += NvT[row][jj] * R[jj+1][ii];
      }
      }
    }

    //..Back-substitution..
    for (ii=0; ii<3; ii++) { //..3-D coordinates..
      for (k=0; k<m-1; k++) {b[k] = Rv[k][ii];}
      //lubksb(&ALUDv, m-1, &pivotv, &b);
      lubksb(ALUDv, m-1, pivotv, b);
      for (k=0; k<m-1; k++) {P[k+1][i][ii] = b[k];}
    }
  }//..chordwise i-loop ends here.

}
//--------------------------------------------------------
void GlobalSurfApproxFixednm
     (
       const     int	     r,
       const     int	     s,
       CArray3d <double> & Q,
       const     int	     p,
       const     int	     q,
       const     int	     n,
       const     int	     m,
       CVector  <double> & U,
       CVector  <double> & V,
       CArray3d <double> & P,
       const     int       nDimenOff
     )
//void GlobalSurfApproxFixednm(const int r, const int s, double ***Q,
//		 const int p, const int q, const int n, const int m,
//		 double *U, double *V, double ***P)
{
//////////////////////////////////////
//////////////////////////////////////
// Note Uniform Knot Vector is used
//////////////////////////////////////
//////////////////////////////////////
  //..Global surface approx with fixed num of ctrl pts
  //  Piegl and Tiller Algorithm (A9.7)
  //  Input: r,s,Q,p,q,n,m
  //  Output: U[n+p+2],V[m+q+2],P[m+1][n+1][3]
  //
  ofstream chk;
  chk.open("GlobalSurfApproxFixednm");
  chk.setf(ios::showpoint | ios::fixed);
  chk.precision(5);

  int i,j,k, errorcode = 0, jj;
  CVector<double> ub(r+1);
  CVector<double> vb(s+1);
  int bigrsM = ((r-1)>(s-1)) ? (r-1) : (s-1);
  CVector<double> N0p(bigrsM);
  CVector<double> Nnp(bigrsM);
  int bigpq = ((p+1)>(q+1)) ? (p+1) : (q+1);
  CVector<double> NN(bigpq);
  int bignmM = ((n-1)>(m-1)) ? (n-1) : (m-1);
  CVector<double> b(bignmM);
  int span, row;

  errorcode = SurfMeshParams(r,s,Q,ub,vb);

  if (errorcode<0) {
    cout << "GlobalSurfApproxFixednm():\n"
	 << "errorcode = " << errorcode
	 << " is raised in SurfMeshParams().\n";
  }

//..Compute knot vectors U[] and V[] using Eq. (9.69)..
//  ComputeKnotVectorUsingEq_9_69(r, p, n, ub, U);
//  ComputeKnotVectorUsingEq_9_69(s, q, m, vb, V);
////////////////////////////////////////////////////////////////
  ComputeUniformKnotVector(n, p, U);
  ComputeUniformKnotVector(m, q, V);
  for (i=0; i<n+p+2; i++) {U[i] /= U[n+p+1];}
  for (i=0; i<m+q+2; i++) {V[i] /= V[m+q+1];}
////////////////////////////////////////////////////////////////
  chk << "\n ub/vb vectors...\n";
  for (i=0; i<r+1; i++) {
    chk << "i=" << setw(4) << i << setw(10) << ub[i] << endl;
  }
  chk << endl;
  for (i=0; i<s+1; i++) {
    chk << "i=" << setw(4) << i
	<< setw(10) << setprecision(5) << vb[i] << endl;
  }
  chk << "\n U/V knot vectors...\n";
  for (i=0; i<n+p+2; i++) {
    chk << "i=" << setw(4) << i << setw(10) << U[i] << endl;
  }
  chk << endl;
  for (i=0; i<m+q+2; i++) {
    chk << "i=" << setw(4) << i << setw(10) << V[i] << endl;
  }
  //========================================//
  //  Interpolate in the chordwise direction
  //========================================//

  //..Construct Nu-matrix
  CArray2d<double> Nu(r-1,n-1);

  row = 0;
  for (j=1; j<=r-1; j++, row++) {
    N0p[row] = 0.0;
    Nnp[row] = 0.0;
    span = FindSpan(n,p,ub[j],U);
    BasisFuns(span, ub[j], p, U, NN);
    //BasisFuns(span, ub[j], p, U, &NN);
    for (jj=0; jj<=p; jj++) {
      if ((span-p+jj)==0) {
        N0p[row] = NN[0];
      } else if ((span-p+jj)==n) {
        Nnp[row] = NN[p];
      } else{
        Nu[row][span-p+jj-1] = NN[jj];
      }
    }
  }
  //cout << endl << "Nu[][]" << endl << Nu << endl;
  CArray2d<double> NuT(n-1,r-1);
  MatrixTranspose(Nu, r-1,n-1, NuT);
  //MatrixTranspose(&Nu, r-1,n-1, &NuT);

  CArray2d<double> NTNu(n-1,n-1);
  MatrixMultiplication(NuT, n-1,r-1, Nu,r-1,n-1, NTNu);
  //MatrixMultiplication(&NuT, n-1,r-1, &Nu,r-1,n-1, &NTNu);

  //..LUDecompose NTNu..
  CArray2d<double> ALUD(n-1,n-1);
  CVector<int> pivot(n-1);
  double plusminusone;

  ludcmp(NTNu, ALUD, n-1, pivot, plusminusone);
  //ludcmp(&NTNu, &ALUD, n-1, &pivot, &plusminusone);

  int bigrs = ((r+1)>(s+1)) ? (r+1) : (s+1);
  //CArray2d<double> R(bigrs,3);
  CArray2d<double> R(bigrs, nDimenOff);
  //CArray2d<double> Ru(n-1,3);
  CArray2d<double> Ru(n-1,nDimenOff);
  //..Temp: storage of control points after u-wise interpolation..
  //CArray3d<double> Temp(n+1,s+1,3);
  CArray3d<double> Temp(n+1,s+1,nDimenOff);
  //..Covers spanwise stations..
  for (j=0; j<=s; j++) {
    //..u-direction fit..
    //for (jj=0; jj<3; jj++) { //..First and last points are fixed..
      for (jj=0; jj<nDimenOff; jj++) {
      Temp[0][j][jj] = Q[j][0][jj];
      Temp[n][j][jj] = Q[j][r][jj];
    }
    //..Build remainder vector using Eq.(9.63)..
    row = 0;
    for (k=1; k<=r-1; k++, row++) {
      //for (i=0; i<3; i++) { //..3 coord.
        for (i=0; i<nDimenOff; i++) {
        R[k][i] = Q[j][k][i] - N0p[row]*Q[j][0][i]
			     - Nnp[row]*Q[j][r][i];
      }
    }

    //..Assemble RHS vector by matrix product: NuT * R..
    row = 0;
    for (k=1; k<=n-1; k++, row++) {
      //for (i=0; i<3; i++) {Ru[row][i] = 0.0;}
      for (i=0; i<nDimenOff; i++) {Ru[row][i] = 0.0;}
      //for (i=0; i<3; i++) { //..3 coordinates
      for (i=0; i<nDimenOff; i++) { //..3 coordinates
      for (jj=0; jj<r-1; jj++) {
        Ru[row][i] += NuT[row][jj] * R[jj+1][i];
	   }
      }
    }

    //..Back-substitution..
    //for (i=0; i<3; i++) { //..3-D coordinates..
    for (i=0; i<nDimenOff; i++) { //..3-D coordinates..
      for (k=0; k<n-1; k++) {b[k] = Ru[k][i];}
      //lubksb(&ALUD, n-1, &pivot, &b);
      lubksb(ALUD, n-1, pivot, b);
      for (k=0; k<n-1; k++) {Temp[k+1][j][i] = b[k];}
    }
  }//..spanwise j-loop ends here.


  //=======================================//
  //  Interpolate in the spanwise direction
  //=======================================//

  //..Construct Nv-matrix
  CArray2d<double> Nv(s-1,m-1);

  row = 0;
  for (j=1; j<=s-1; j++, row++) {
    N0p[row] = 0.0;
    Nnp[row] = 0.0;
    span = FindSpan(m,q,vb[j],V);
    BasisFuns(span, vb[j], q, V, NN);
    //BasisFuns(span, vb[j], q, V, &NN);
    for (jj=0; jj<=q; jj++) {
      if ((span-q+jj)==0) {
        N0p[row] = NN[0];
      } else if ((span-q+jj)==m){
        Nnp[row] = NN[q];
      } else{
        Nv[row][span-q+jj-1] = NN[jj];
      }
    }
  }

  CArray2d<double> NvT(m-1,s-1);
  MatrixTranspose(Nv, s-1,m-1, NvT);
  //MatrixTranspose(&Nv, s-1,m-1, &NvT);

  CArray2d<double> NTNv(m-1,m-1);
  MatrixMultiplication(NvT, m-1,s-1, Nv,s-1,m-1, NTNv);
  //MatrixMultiplication(&NvT, m-1,s-1, &Nv,s-1,m-1, &NTNv);

  //..LUDecompose NTNv..
  CArray2d<double> ALUDv(m-1,m-1);
  CVector<int> pivotv(m-1);

  //ludcmp(&NTNv, &ALUDv, m-1, &pivotv, &plusminusone);
  ludcmp(NTNv, ALUDv, m-1, pivotv, plusminusone);
  for (i=0; i<bigrs; i++) {
    //for (j=0; j<3; j++) {R[i][j] = 0.0;}
    for (j=0; j<nDimenOff; j++) {R[i][j] = 0.0;}
  }

  //CArray2d<double> Rv(m-1,3);
  CArray2d<double> Rv(m-1,nDimenOff);

  //..Covers chordwise control points..
  for (i=0; i<=n; i++) {
    //..v-direction fits..
    //for (jj=0; jj<3; jj++) { //..First(Hub) and last(tip) points are fixed..
    for (jj=0; jj<nDimenOff; jj++) {
      P[0][i][jj] = Temp[i][0][jj];
      P[m][i][jj] = Temp[i][s][jj];
    }
    //..Build remainder vector using Eq.(9.63)..
    row = 0;
    for (k=1; k<=s-1; k++, row++) {
      //for (jj=0; jj<3; jj++) { //..3 coord.
      for (jj=0; jj<nDimenOff; jj++) { //..3 coord.
          R[k][jj] = Temp[i][k][jj] - N0p[row]*Temp[i][0][jj]
				  - Nnp[row]*Temp[i][s][jj];
      }
    }

    //..Assemble RHS vector by matrix product: NvT * R..
    int ii;
    row = 0;
    for (k=1; k<=m-1; k++, row++) {
      //for (ii=0; ii<3; ii++) {Rv[row][ii] = 0.0;}
      //for (ii=0; ii<3; ii++) { //..3 coordinates
      for (ii=0; ii<nDimenOff; ii++) {Rv[row][ii] = 0.0;}
      for (ii=0; ii<nDimenOff; ii++) { //..3 coordinates
      for (jj=0; jj<s-1; jj++) {
       Rv[row][ii] += NvT[row][jj] * R[jj+1][ii];
      }
      }
    }

    //..Back-substitution..
    //for (ii=0; ii<3; ii++) { //..3-D coordinates..
    for (ii=0; ii<nDimenOff; ii++) { //..3-D coordinates..
      for (k=0; k<m-1; k++) {b[k] = Rv[k][ii];}
      //lubksb(&ALUDv, m-1, &pivotv, &b);
      lubksb(ALUDv, m-1, pivotv, b);
      for (k=0; k<m-1; k++) {P[k+1][i][ii] = b[k];}
    }
  }//..chordwise i-loop ends here.
}

//--------------------------------------------------------
int B4FitForFoilCWForCamber
    (
       CArray2d <double>  &Q,
       int                 r,
       CVector  <double> &Wq,
       CArray2d <double>  &D,
       int                 s, 
       CVector  <int>     &I,
       CVector  <double> &Wd, 
       int                 n,
       int                 p,
       CVector  <double>  &U,
       CArray2d <double>  &P,
       CVector  <double> &ub
    ) 
//int B4FitForFoilCWForCamber(double **Q, int r,  double *Wq,
//                 double **D, int s, int *I, double *Wd, 
//                 int n, int p,
//                 double *U, double **P, double *ub) 
{
  //..This program is identical to B4FitForFoil() except the 
  //  numbering of the input Q is made in the clockwise
  //  direction.
  //..Weighted least square curve fit for foil section..
  //  Original: Converted from Kerwin's B4FIT.FOR
  //  New feature: Weighting and constraining options are added.
  //  Ref. 1) Kerwin, B4Fit.For 
  //       2) Piegl and Tiller algothrim (A9.6)
  //  Input: Q,r,Wq,D,s,I,Wd,n,p
  //  Output: U,P
  //  U[]: knot vector
  //  P[n+1][3]:  control point coordinates
  //
  //  Q[r+1][3]: an array containing the points to fit,
  //                   (constrained and unconstrained)
  //  r: the upper index of Q[][3]
  //  Wq[r+1]: >0 if Q[i] is unconstrained, and Wq[i] is the weight
  //           <0 if Q[i] is constrained
  //  D[s+1][3]: an array containing the derivatives; 
  //             s=-1 if no derivatives are specified
  //  s: there are s+1 derivatives in D[][3]
  //  I[s+1]:  an integer array; I[j] gives the index into Q[i] of 
  //           the point corresponding to the derivatives in D[j]
  //  Wd[s+1]: >0 if D[j] is unconstrained, and Wd[j] is the weight
  //  n: a fit with n+1 control points
  //  p: a fit with degree p curve.
  ofstream chk;
  chk.open("B4FitForCamber");
  chk.setf(ios::fixed | ios::showpoint);
  chk.precision(4);
  int i,j, mu2,mc2, jj;  
  int ru = -1; int rc = -1;
  for (i=0; i<=r; i++) {
    if (Wq[i]>0.0) ru++;
    else           rc++;
  }
  int su = -1; int sc = -1;
  for (j=0; j<=s; j++) {
    if (Wd[j]>0.0) su++;
    else           sc++;
  }
  int mu = ru + su + 1; int mc = rc + sc + 1;
  if (mc>=n || mc+n>=mu+1) return (-1);  //..error code = -1

  //double *ub = new double[r+1];
  double big=1.0e06, half=0.5, zero=0.0, one=1.0, pi=3.1415927e00;
  double tol=5.0e-5;  //..TOLERANCE;
  double hun=1.0e02;
  CArray2d<double> nders(p+1, p+1);

  //...Set up arrays N,W,S,T,M
  CArray2d<double> N(mu+1, n+1);
  CArray2d<double> NT(n+1, mu+1);
  CArray2d<double> M(mc+1, n+1);
  CArray2d<double> S(mu+1, 3);
  CArray2d<double> T(mc+1, 3);
  CVector <double> W(mu+1);
  CArray2d<double> funs(2, p+1);
  CVector <double> Temp(p+1);
  CVector <double> Nu(p+1);
  CArray2d<double> DNu(p+1, p+1);

  //..Compute Uniform Knot Vector..
  int m = n + p + 1;     
  double maxknotvalue = double((m) - 2*(p+1) + 2);
  for (j=0; j<=p; j++) {
    U[j] = 0.0;
    U[m-j] = maxknotvalue;
  }
  for (j=p+1, i=1; j<=n; j++) {U[j] = double(i++);}
  
  //..Find the minimum and maximum x coordinate of input data..
  double  xLE = Q[0][0];  ////// zero;
  int iLE = 0;
  double  xTE = Q[r][0];

  //..Find x-locations of vertices with cosine spacing..
  int jtry, ktry; int maxDeriv;
  int span, paramConverged;
  double hChord, dtheta, cost, dxdu;
  double x_computed, dx;
  CVector<double> xV(n+1);
  CVector<double> yRhs(r+1);

  //..Search the xVLE(control vertex near LE) giving xLE=0.
  jtry = 0;
  hChord = (xTE - xLE) * half;
  dtheta = pi / (n+1-1);
  for (i=0; i<n+1; i++) {
    cost = cos(double(i)*dtheta);
    xV[i] = xLE + hChord * (one - cost);
  }
  cout.precision(5);

  //..Find ub(x_data) for each input (x_data)point by iteration 
  //  starting from the leading edge on the camber line..
  for (i=0; i<r+1; i++) {
    if (i==0) {ub[i] = zero;}
    else {ub[i] = ub[i-1];}
    //..Search for parameter ubar[k] that satisfies 
    //  |x_data[k]-x_computed[k]|<tol within tolerance
    ktry = 0;
    do {
      //..Use uLE,n,p, get Derivative up to 1st degree..
      paramConverged = 0;
      span = FindSpan(n, p, ub[i], U);
      DersBasisFuns(span, ub[i], p, maxDeriv=1, U, nders);
      //DersBasisFuns(span, ub[i], p, maxDeriv=1, U, &nders);
      x_computed = dxdu = zero;
      for (j=0; j<=p; j++) {
        x_computed += nders[0][j] * xV[span-p+j];
        dxdu += nders[1][j] * xV[span-p+j];
      }
      dx = Q[i][0] - x_computed;
      if (fabs(dx)<tol) {paramConverged=1; break;}
      ub[i] += (Q[i][0] - x_computed)/dxdu;
    } while(ktry++<100);
    cout.precision(5);
    if (paramConverged!=1) {
      cout << "No ub[] convergence: " 
           << "\tk=" << i << "\tQ[k][0]=" << Q[i][0]
           << "\tx_computed=" << x_computed << endl;
      //return (-1);
    }//..ub[i], i=0,...,r:  ubar vector is obtained..
  }
  chk.precision(5);
  //..check u[]..
  for (i=0; i<r+1; i++) {
    chk << "i=" << setw(4) << i << ", ubar[i],Qx,Qy=" 
        << setw(10) << ub[i] 
        << setw(10) << Q[i][0] << setw(10) << Q[i][1] << endl;
  }
  chk.flush();

  //...........
  j = 0; //..current index into I[]
  mu2 = 0; mc2 = 0;  //..counters up to mu and mc.
  for (i=0; i<=r; i++) {
    span  = FindSpan(n,p,ub[i],U);
    int dflag = 0;
    if (j<=s)
      if (i==I[j]) dflag = 1;
    if (dflag==0) {
      BasisFuns(span, ub[i], p,U, Temp);    
      //BasisFuns(span, ub[i], p,U, &Temp);    
      for (jj=0; jj<=p; jj++) {funs[0][jj] = Temp[jj];}
    } else{
      DersBasisFuns(span,ub[i],p,1,U, DNu);
      //DersBasisFuns(span,ub[i],p,1,U, &DNu);
      for (jj=0; jj<=p; jj++) {
        funs[0][jj] = DNu[0][jj]; //..0-th derivative
        funs[1][jj] = DNu[1][jj]; //..first derivative
      }
    }
    if (Wq[i]>0.0) {
      //..Unconstrained point
      W[mu2] = Wq[i];
      for (jj=0; jj<=p; jj++) {N[mu2][span-p+jj] = funs[0][jj];}
      S[mu2][0] = W[mu2] * Q[i][0];
      S[mu2][1] = W[mu2] * Q[i][1];
      S[mu2][2] = W[mu2] * Q[i][2];
      mu2++;
    } else{
      //..Constrained point
      for (jj=0; jj<=p; jj++) {M[mc2][span-p+jj] = funs[0][jj];}
      T[mc2][0] = Q[i][0];
      T[mc2][1] = Q[i][1];
      T[mc2][2] = Q[i][2];
      mc2++;
    }
    if (dflag==1) {
      //..Derivative at this point
      if (Wd[j]>0.0) {
        //..Unconstrained derivative
        W[mu2] = Wd[j];
        for (jj=0; jj<=p; jj++) {N[mu2][span-p+jj] = funs[1][jj];}
         S[mu2][0] = W[mu2] * D[j][0];
         S[mu2][1] = W[mu2] * D[j][1];
         S[mu2][2] = W[mu2] * D[j][2];
         mu2++;
      } else{
        //..Constrained derivative
        for (jj=0; jj<=p; jj++) {M[mc2][span-p+jj] = funs[1][jj];}
        T[mc2][0] = D[j][0];
        T[mc2][1] = D[j][1];
        T[mc2][2] = D[j][2];
        mc2++;
      }
      j++;
    }//..dflag==1
  }//..end of for-loop i=0,...,r
  CArray2d<double> NTW(n+1, mu+1);
  MatrixTranspose(N, mu+1, n+1, NTW);
  //MatrixTranspose(&N, mu+1, n+1, &NTW);
  for (j=0; j<mu+1; j++) {
    for (i=0; i<n+1; i++) {
      NTW[i][j] *= W[j];
    }
  }

  CArray2d<double> NTWN(n+1, n+1);
  CArray2d<double> NTWNInv(n+1, n+1);
  MatrixMultiplication(NTW,n+1,mu+1,  N,mu+1,n+1, NTWN);
  //MatrixMultiplication(&NTW,n+1,mu+1,  &N,mu+1,n+1, &NTWN);

  CArray2d<double> NTWS(n+1, 3);
  MatrixMultiplication(NTW,n+1,mu+1,  S,mu+1,3, NTWS);
  //MatrixMultiplication(&NTW,n+1,mu+1,  &S,mu+1,3, &NTWS);

  CVector<double> b(n+1);
  //..LUDecompose NTWN matrix..
  CArray2d<double> ALUD(n+1, n+1);
  CVector<int> pivot(n+1);
  double plusminusone;

  //ludcmp(&NTWN, &ALUD, n+1, &pivot, &plusminusone);
  ludcmp(NTWN, ALUD, n+1, pivot, plusminusone);

  //..Solve for the control points P[][3]..
  if (mc<0) {
    //..No constraints
    for (jj=0; jj<3; jj++) { //..3-D coordinates..
      for (j=0; j<n+1; j++) {b[j] = NTWS[j][jj];}  
      //lubksb(&ALUD, n+1, &pivot, &b);
      lubksb(ALUD, n+1, pivot, b);
      for (i=0; i<n+1; i++) {
        //if (jj==0) {P[i][jj] = xV[i];}
        //else {
          P[i][jj] = b[i];
        //}
      }
    }
    return 0;
  }

  //..Compute (NTWN)-inverse
  MatrixInverse(NTWN, n+1, NTWNInv);
  //MatrixInverse(&NTWN, n+1, &NTWNInv);
  
  CArray2d<double> MT(n+1,mc+1);
  MatrixTranspose(M, mc+1, n+1, MT);
  //MatrixTranspose(&M, mc+1, n+1, &MT);

  CArray2d<double> MNTWNInv(mc+1, n+1);
  MatrixMultiplication(M, mc+1, n+1, NTWNInv, n+1, n+1, MNTWNInv);
  //MatrixMultiplication(&M, mc+1, n+1, &NTWNInv, n+1, n+1, &MNTWNInv);
  //..Get coeff matrix to solve for Lagrange multiplier, Eq(9.75)
  CArray2d<double> LagrangeCoeffMatrix(mc+1, mc+1);
  MatrixMultiplication(MNTWNInv, mc+1, n+1, MT, n+1, mc+1, 
                       LagrangeCoeffMatrix);
  //MatrixMultiplication(&MNTWNInv, mc+1, n+1, &MT, n+1, mc+1, 
  //                     &LagrangeCoeffMatrix);

  //..Solve 3-components..
  CArray2d<double> LagrangeRHS(mc+1, 3);
  CArray2d<double> A(mc+1, 3); //..Lagrange Multipliers
  MatrixMultiplication(MNTWNInv, mc+1, n+1, NTWS, n+1, 3, 
                       LagrangeRHS);
//  MatrixMultiplication(&MNTWNInv, mc+1, n+1, &NTWS, n+1, 3, 
//                     &LagrangeRHS);
  MatrixSubstraction(mc+1,3, LagrangeRHS, T, LagrangeRHS);
  //MatrixSubstraction(mc+1,3, &LagrangeRHS, &T, &LagrangeRHS);
  //ludcmp(&LagrangeCoeffMatrix, &ALUD, mc+1, &pivot, &plusminusone);
  ludcmp(LagrangeCoeffMatrix, ALUD, mc+1, pivot, plusminusone);
  for (jj=0; jj<3; jj++) { //..3-D coordinates..
    for (j=0; j<mc+1; j++) {b[j] = LagrangeRHS[j][jj];}  
    //lubksb(&ALUD, mc+1, &pivot, &b);
    lubksb(ALUD, mc+1, pivot, b);
    for (i=0; i<mc+1; i++) {A[i][jj] = b[i];}
  }

  //..Now solve for P[][3], using Eq.(9.74)..
  CArray2d<double> MTA(n+1, 3);
  MatrixMultiplication(MT, n+1, mc+1, A, mc+1, 3, MTA);
  MatrixSubstraction(n+1,3, NTWS, MTA, NTWS);
  MatrixMultiplication(NTWNInv,n+1,n+1, NTWS,n+1,3, P);

  //MatrixMultiplication(&MT, n+1, mc+1, &A, mc+1, 3, &MTA);
  //MatrixSubstraction(n+1,3, &NTWS, &MTA, &NTWS);
  //MatrixMultiplication(&NTWNInv,n+1,n+1, &NTWS,n+1,3, P);

  return 0; //..ok
}

int LookForLELocation
    (
      int                 nGCVerticesM1,
      int                 nDegree,
      CVector  <double> & uKnot,
      CArray2d <double> & xGCVertex,
      double            & xLE,
      double            & uLE,
      double            & chordLETE
    )
{
//  using namespace const_prop;
  double half = 0.5, zero = 0.0;
  int j, maxDeriv, span;
  int nGCVertices = nGCVerticesM1 + 1;
  double tol=5.0e-05;
  CArray2d<double> nders(nDegree+1, nDegree+1);

  double  xTEL = xGCVertex[0][0];
  double  xTEU = xGCVertex[nGCVertices-1][0];
  uLE = half * uKnot[nGCVertices-1 + nDegree + 1];

   // Find parameter value uLE at the leading edge..
  double xVLE = xGCVertex[nGCVertices/2][0];
  int ktry;
  int paramConverged;
  double xCLE,dxdu,d2xdu;

  //..Search the parameter uLE giving dx/du=0.
  ktry = 0;
  do {
    //..Use uLE,n,p, get Derivative up to 2nd degree..
    paramConverged = 0;
    span = FindSpan(nGCVertices-1, nDegree, uLE, uKnot);
    DersBasisFuns(span, uLE, nDegree, maxDeriv=2, uKnot, nders);
    xCLE = dxdu = d2xdu = zero;
    for (j=0; j<=nDegree; j++) {
      xCLE += nders[0][j] * xGCVertex[span-nDegree+j][0];
      dxdu += nders[1][j] * xGCVertex[span-nDegree+j][0];
      d2xdu += nders[2][j] * xGCVertex[span-nDegree+j][0];
    }
    uLE -= dxdu/d2xdu;
    if (fabs(dxdu)<tol) {paramConverged=1; break;}
  } while(ktry++<30);
  if (paramConverged!=1) {
    cout.precision(5);
    cout << "LE Search error: xLE, xCLE, uLE=" 
         << setw(10) << setprecision(5) << xLE
         << setw(10) << setprecision(5) << xCLE
         << setw(10) << setprecision(5) << uLE << endl;
    //return -1;
  }

  xLE = xCLE;
  chordLETE = xTEL - xLE;
  return 0;
}

void CurvePoint1P
     (
       int                 n,
       int                 p,
       CVector  <double> & U,
       CArray2d <double> & P,
       double              u,
       CVector  <double> & S, 
       int                 nDimenOff
     )
{
  CVector<double> Nu(p+1);

  int k, i, uspan = FindSpan(n,p,u,U);
  BasisFuns(uspan,u,p,U, Nu);

  double *temp = new double[nDimenOff];
  int uind = uspan - p;

  for(k =0; k < nDimenOff; k++){
    S[k] = 0.0;
    temp[k] = 0.0;
  }
  for(k=0; k<=p; k++) {
    for(i = 0; i < nDimenOff; i++) 
    S[i] += Nu[k] * P[uind+k][i];
//    S[1] += Nu[k] * P[uind+k][1];
//    S[2] += Nu[k] * P[uind+k][2];
  }
}

//////////////////////////////////////////
//.. insert new routine
//////////////////////////////////////////
void NormalVector
     (
       double              uc,
       double              vc,
       int                 nUGCVM1,
       int                 nVGCVM1,
       CArray3d <double> & xGCV,
       int                 nUGDegree,
       int                 nVGDegree,
       CVector  <double> & Ug,
       CVector  <double> & Vg,
       CVector  <double> & enVEC
     )
{
  int nUGCV = nUGCVM1 + 1;
  int nVGCV = nVGCVM1 + 1;

  int z, d, uspang, vspang, maxDeriv=1;
  double drdu[3], drdv[3];
  double jacobian;

  CArray2d<double> Ndersg(nUGDegree+1,nUGDegree+1);
  CArray2d<double> Mdersg(nVGDegree+1,nVGDegree+1);

  double xg;

  uspang = FindSpan(nUGCV-1, nUGDegree, uc, Ug);
  DersBasisFuns(uspang, uc, nUGDegree, maxDeriv, Ug, Ndersg);
  vspang = FindSpan(nVGCV-1, nVGDegree, vc, Vg);
  DersBasisFuns(vspang, vc, nVGDegree, maxDeriv, Vg, Mdersg);

  drdu[0] = drdu[1] = drdu[2] = 0.0;
  drdv[0] = drdv[1] = drdv[2] = 0.0;
  for (int ag=0; ag<=nUGDegree; ag++) {
    for (int bg=0; bg<=nVGDegree; bg++) {
      for (d=0; d<3; d++) {
        int tqb = vspang-nVGDegree+bg;
        int spa = uspang-nUGDegree+ag;
        xg = xGCV[tqb][spa][d];
        double NM = Ndersg[0][ag] * Mdersg[0][bg];
        drdu[d] += Ndersg[1][ag] * Mdersg[0][bg] * xg;
        drdv[d] += Ndersg[0][ag] * Mdersg[1][bg] * xg;
      }//..d:3-dimensions
    }
  }

  double en[3],drudrv[3];
  prcros(drdu, drdv, drudrv);
  jacobian = sqrt(prdot(drudrv,drudrv));
  for (z=0; z<3; z++) {en[z]=drudrv[z]/jacobian;}
  for (z=0; z<3; z++) {enVEC[z]=en[z];}

}

//... End of BSPlineLib.cpp
