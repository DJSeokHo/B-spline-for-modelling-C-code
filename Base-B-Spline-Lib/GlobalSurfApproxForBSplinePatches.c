/*

  GlobalSurfApproxForBSplinePatches.cpp

*/

#include <fstream.h>
#include <iomanip.h>
#include <math.h>

//////////////////////
#include "ldebug.h"
#include "hipandef.h"
///////////////////////////////////////////////
#include "proplibd.h"
#include "bsplinelib.h"
#include "hipanpropclass.h"
#include "externalfunctions.h"
#include "globalsurfapproxforbsplinepatches.h"
///////////////////////////////////////////////
#include "constprop.h"

extern double alphaR;
///////////////////////
#define SKIPLINE ignore(80, '\n')
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
// Added for hipan3dsphere.cpp
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
//---------------------------------------------------------------
void GenerateSphereOffset
     (
       int nUOff,
       int nVOff,
       CArray3d <double> & xOff, //double ***xOff,
       CArray2d <double> & wOff  //double **wOff
     )
{
  int input_option;
  double a, b, c;

  cout << " Enter the input data option. " << endl
       << " 1. ellipsoid wing " << endl
       << " 2. sphere         " << endl
       << " .......... ";
  cin  >> input_option;

  if ( input_option == 1 ) {
    a = 0.5;
    b = 5.0;
    c = 0.5;

    a /= 2.0*a;
    b /= 2.0*a;
    c /= 2.0*a;
  } else {
    a = 0.5;
    b = 0.5;
    c = 0.5;
  }
  
  int n,m;
  double one=1.0, two=2.0, pi=3.14159265358979;
  double delth  = pi / (nVOff - one);
  double delph  = two*pi / (nUOff - one);

  for (m=0; m<nVOff; m++) {
    double theta = m * delth;
    for (n=0; n<nUOff; n++) {
      double ph = n * delph;
      xOff[m][n][0] = a*sin(theta) * cos(ph);
      xOff[m][n][1] = -b*cos(theta);
      xOff[m][n][2] = -c*sin(theta) * sin(ph);
	     xOff[m][n][3] = cos(alphaR);
	     xOff[m][n][4] = 0.0;
	     xOff[m][n][5] = sin(alphaR);
      //..default: no constraint..
      wOff[m][n] = one;
      //..constraint at Hub and Tip..
      wOff[0][n] = wOff[nVOff-1][n] = -one;
    }
    //..constraint at upper and lower edge of TE..
    wOff[m][0] = wOff[m][nUOff-1] = -one;
  }
}//..GenerateSphereOffset()

void CHipanProp::
     GlobalSurfApproxForBSplinePatches(ifstream &_v1) {

  using namespace const_prop;

  double alpha;

/*
  do {
    cout << "\n === Enter Angle of Attack in deg: ";
    cin >> alpha;
  } while (alpha>90.0);
*/
  alpha  = 0.0;
  alphaR = alpha * pi / 180.0;

  int i, j, m;
  int z, n, nUOff, nVOff; //..fixed; not essential.. //kgd ...nvoff=101

  ifstream fin("s608new.dat");

  int nx, ny, ii, jj;
  CArray3d <double> xoff_in, xoff_out;

  fin >> nx >> ny;             fin.SKIPLINE;

  xoff_in.setdimsize(ny, nx, 3);

  int nn=nx+(nx-1), mm=ny;
  xoff_out.setdimsize(mm, nn, 3);
  nUOff = nn;
  nVOff = mm;

  for (jj=0; jj<ny; jj++) {
    for (ii=0; ii<nx; ii++) {
      for (z=0; z<3; z++) fin >> xoff_in[jj][ii][z];

      fin.SKIPLINE;
    }
  }

  for (jj=0; jj<ny; jj++) {
    for (ii=0; ii<nx; ii++) {
      for (z=0; z<3; z++) xoff_out[jj][ii][z] = xoff_in[jj][nx-1-ii][z];
    }
    for (ii=nx; ii<nn; ii++) {
      xoff_out[jj][ii][0] =  xoff_in[jj][ii-nx+1][0];
      xoff_out[jj][ii][1] = -xoff_in[jj][ii-nx+1][1];
      xoff_out[jj][ii][2] =  xoff_in[jj][ii-nx+1][2];
    }
  }
    
  CArray3d <double> xOff(nVOff, nUOff, nDimenOff);
  CArray2d <double> wOff(nVOff, nUOff);

  ////////////////////////////////////////////////////////
  // generate offset array
  ////////////////////////////////////////////////////////
  for (mm=0; mm<nVOff; mm++) {
    for (nn=0; nn<nUOff; nn++) {
      xOff[mm][nn][0] = xoff_out[mm][nn][0];
      xOff[mm][nn][1] = xoff_out[mm][nn][1];
      xOff[mm][nn][2] = xoff_out[mm][nn][2];
      xOff[mm][nn][3] = 1.0;
      xOff[mm][nn][4] = 0.0;
      xOff[mm][nn][5] = 0.0;
      //..default: no constraint..
      wOff[mm][nn] = one;
      //..constraint at Hub and Tip..
      wOff[0][nn] = wOff[nVOff-1][nn] = -one;
    }
    //..constraint at upper and lower edge of TE..
    wOff[mm][0] = wOff[mm][nUOff-1] = -one;
  }

  ofstream xoff("xoff.tec");
  xoff << " variables = x, y, z " << endl << "zone i = " << nUOff << ",j= " << nVOff << endl;
  for (j=0; j<nVOff; j++)
    for (i=0; i<nUOff; i++)
    xoff << xOff[j][i][0] << "  "
         << xOff[j][i][1] << "  "
         << xOff[j][i][2] << endl;
  xoff.close();

  CArray3d <double> xGCVLoc(BSPatch[0].nVGCV, BSPatch[0].nUGCV, 6);

  for(int _b=0; _b<nBSPatch; _b++) {
/*
    SurfaceApproxFixednmForSphere
     (
      nUOff-1   , nVOff-1, xOff,
      BSPatch[_b].nUGDegree, BSPatch[_b].nVGDegree,//(7.6)
      BSPatch[_b].nUGCV-1 , BSPatch[_b].nVGCV-1, 
      BSPatch[_b].Ug      , BSPatch[_b].Vg,
      xGCVLoc,
      6
     );
*/

    GlobalSurfInterp
    (
       nUOff-1,
	   nVOff-1,
       6,
	   xOff,
	   BSPatch[_b].nUGDegree,
	   BSPatch[_b].nVGDegree,
       BSPatch[_b].Ug, 
       BSPatch[_b].Vg,
       xGCVLoc
    );

    for (m=0; m<BSPatch[_b].nVGCV; m++) {
      for (n=0; n<BSPatch[_b].nUGCV; n++) {
        for (z=0; z<3; z++) {
          BSPatch[_b].xGCV[m][n][z] = xGCVLoc[m][n][z];
          BSPatch[_b].UinGCV[m][n][z] = xGCVLoc[m][n][3+z];
        }
      } //...n-Loop
    } //...m-Loop
  }//..i for BSPatch..


//////////////////////////////////   SPHERE HERE   //////////////////////////////
/*
  nUOff = 101;
  nVOff = 51; 
    
  CArray3d <double> xOff(nVOff, nUOff, nDimenOff);
  CArray2d <double> wOff(nVOff, nUOff);
  CVector <double> vbarBlade(nVOff);

  GenerateSphereOffset(nUOff, nVOff, xOff, wOff);

  ofstream xoff("xoff.tec");
  xoff << " variables = x, y, z " << endl << "zone i = " << nUOff << ",j= " << nVOff << endl;
  for (j=0; j<nVOff; j++)
    for (i=0; i<nUOff; i++)
    xoff << xOff[j][i][0] << "  "
         << xOff[j][i][1] << "  "
         << xOff[j][i][2] << endl;
  xoff.close();

  CArray3d <double> xGCVLoc(BSPatch[0].nVGCV, BSPatch[0].nUGCV, 6);

  for(int _b = 0; _b < nBSPatch; _b++) {

    SurfaceApproxFixednmForSphere
     (
      nUOff-1   , nVOff-1, xOff,
      BSPatch[_b].nUGDegree, BSPatch[_b].nVGDegree,//(7.6)
      BSPatch[_b].nUGCV-1 , BSPatch[_b].nVGCV-1, 
      BSPatch[_b].Ug      , BSPatch[_b].Vg,
      xGCVLoc,
      6
     );

    for (m=0; m<BSPatch[_b].nVGCV; m++) {
      for (n=0; n<BSPatch[_b].nUGCV; n++) {
        for (z=0; z<3; z++) {
          BSPatch[_b].xGCV[m][n][z] = xGCVLoc[m][n][z];
          BSPatch[_b].UinGCV[m][n][z] = xGCVLoc[m][n][3+z];
        }
      } //...n-Loop
    } //...m-Loop
  }//..i for BSPatch..
*/
////////////////////////////////////////////////////////////////////////////////////

  ofstream xgcv("xgcv.tec",ios::out);
  xgcv << "variables = x,y,z" << endl;
  xgcv.setf(ios::fixed | ios::right | ios::showpoint);
  xgcv.precision(5);

  xgcv << " variables = x, y, z " << endl << "zone i = " << BSPatch[0].nUGCV << ",j= " 
                                                         << BSPatch[0].nVGCV << endl;
  for (j=0; j<BSPatch[0].nVGCV; j++)
    for (i=0; i<BSPatch[0].nUGCV; i++)
    xgcv << xGCVLoc[j][i][0] << "  "
         << xGCVLoc[j][i][1] << "  "
         << xGCVLoc[j][i][2] << endl;

  xgcv.close();

  int nGridOffset = 50;
  CVector <double> uGridOff(nGridOffset), vGridOff(nGridOffset);

  double delGrid = 1.0 / double(nGridOffset-1);  
  for(i=0; i<nGridOffset; i++) {
    uGridOff[i] = double(i) * delGrid;
    vGridOff[i] = double(i) * delGrid;
  }
  uGridOff[nGridOffset-1] = 1.0;
  vGridOff[nGridOffset-1] = 1.0;

  ofstream sgeom("result_geom.tec");
  ofstream normal("normal_vec.tec");

  sgeom << "variables = x, y, z\n"
        << "zone i = " << nGridOffset << ", j = " << nGridOffset << endl;
  normal << "variables = x, y, z, nx, ny, nz\n"
         << "zone i = " << nGridOffset << ", j = " << nGridOffset << endl;
  CVector <double> xG(3), enCP(3);
  for(j=0; j<nGridOffset; j++) {
    double v = vGridOff[j];
    for(i=0; i<nGridOffset; i++) {
      double u = uGridOff[i];
      SurfacePoint1P(
        BSPatch[0].nUGCV-1, 
        BSPatch[0].nUGDegree,
        BSPatch[0].Ug, 
        BSPatch[0].nVGCV-1,
        BSPatch[0].nVGDegree, 
        BSPatch[0].Vg,
        BSPatch[0].xGCV,
        u,
        v, 
        xG);
      sgeom << xG[0] << ' ' << xG[1] << ' ' << xG[2] << endl;

      NormalVector
            (
             u,
             v,
             BSPatch[0].nUGCV-1,
             BSPatch[0].nVGCV-1,
             BSPatch[0].xGCV,
             BSPatch[0].nUGDegree,
             BSPatch[0].nVGDegree,
             BSPatch[0].Ug,
             BSPatch[0].Vg,
             enCP
      );
      normal << xG[0] << ' ' << xG[1] << ' ' << xG[2] << ' '
             << enCP[0] << ' ' << enCP[1] << ' ' << enCP[2] << endl;
    }
  }

  sgeom.close();
  normal.close();

}

//--------------------------------------------------------
void SurfaceApproxFixednmForSphere
     (
       int                 nUOffM1,
       int                 nVOffM1,
       CArray3d <double> & xOff,
       int                 nUDegree,
       int                 nVDegree,
       int                 nUGCVM1,
       int                 nVGCVM1,
       CVector	<double> & Ug,
       CVector	<double> & Vg,
       CArray3d <double> & xGCV,
       int                 nDimenOff
     )
{
   int nUOff = nUOffM1+1;
   int nVOff = nVOffM1+1;
   int nUGCV = nUGCVM1+1;
   int nVGCV = nVGCVM1+1;

   GlobalSurfApproxFixednm(
     nUOff-1 , nVOff-1 , 
     xOff    ,
     nUDegree, nVDegree,
     nUGCV-1 , nVGCV-1 ,
     Ug      , Vg      , xGCV,
     nDimenOff
   );
}

//--------------------------------------------------------
#ifndef  SKIP_COMMENT_LINE
#define  SKIP_COMMENT_LINE ignore(80,'\n')
#endif

#ifndef  CLEANUP_TRAILERS
#define  CLEANUP_TRAILERS  ignore(80,'\n')
#endif

void CHipanProp::ReadXOffset 
     (
        ifstream _v1,
        CVector < CArray3d <double> > &xOff,
        CArray2d<double> &wOff
     )  
{
  using namespace const_prop;

  int i, j, k, _b, z, m, n, iTec, jTec;
  CVector <int> check(5);

  for(i = 0; i < 5; i++) check[i] = 0;
  for(_b = 0; _b < nBSPatch; _b++) {
    switch(BSPatch[_b].bspatch_t) {
      case BLADE_BSPLINE_PATCH     : check[0] = 1; break;
      case HUB_FRONT_BSPLINE_PATCH : check[1] = 1; break;
      case HUB_MID_BSPLINE_PATCH   : check[2] = 1; break;
      case HUB_END_BSPLINE_PATCH   : check[3] = 1; break;
      case WAKE_BSPLINE_PATCH      : check[4] = 1; break;
    }
  }   

  _v1.SKIP_COMMENT_LINE;
  //*************************************************
  //if(check[0]) {
  //if(BSPatch[_b].bspatch_t == BLADE_BSPLINE_PATCH) {
  //*************************************************
    getIJTec(_v1, iTec, jTec);
    xOff[0].setdimsize(jTec, iTec, nDimenOff);

    for(j = 0; j < jTec; j++) 
    for(i = 0; i < iTec; i++) { 
      for(z = 0; z < 4 ; z++) _v1 >> xOff[0][j][i][z];
      _v1.CLEANUP_TRAILERS;
    }

    int nUOff, nVOff;
    nVOff = xOff[0].getlayersize();
    nUOff = xOff[0].getrowsize();
    ///////////////////////////////////////////////////////////////
    // Compute Uin at offset coordinates
    // Addedd here to merge into B-Spline fitting routine
    ///////////////////////////////////////////////////////////////
    double uin[3];
    for (j=0; j<nVOff; j++) {
      for (i=0; i<nUOff; i++) {
        uin[0] = cos(alphaR); // kgd double(1.0);
        uin[1] = 0.0; //kgd -pi * xOff[0][j][i][2]/advco;
        uin[2] = sin(alphaR); //kgd  pi * xOff[0][j][i][1]/advco;
        for (z=0; z<3; z++) {
          xOff[0][j][i][nDimenOff-3+z] = uin[z];
        }
     }
    }

    wOff.setdimsize(nVOff, nUOff);
    for (m=0; m<nVOff; m++) {
      for (n=0; n<nUOff; n++) {
        //..default: no constraint..
        wOff[m][n] = double(1.0);
        //..constraint at Hub and Tip..//..Not assigned!
      }
      //..constraint at upper and lower surfaces of TE..
      wOff[m][0] = wOff[m][nUOff-1] = -double(1.0);
    }
  //************************************************************
  //} 
    //else if ( BSPatch[_b].bspatch_t == HUB_FRONT_BSPLINE_PATCH ||
    //          BSPatch[_b].bspatch_t == HUB_MID_BSPLINE_PATCH   ||
    //          BSPatch[_b].bspatch_t == HUB_END_BSPLINE_PATCH    )
   // if(check
  //{
  //************************************************************ 
    int nVHub, nUHub0, nUHub1, nUHub2;
    getIJTec(_v1, iTec, jTec);
    //******************************************
    if(check[1] && check[2] && check[3]) {
    //******************************************
    nVHub = jTec;
    nUHub0 = nUHub2 = iTec/3;
    nUHub1 = nUHub0+2;

    CArray3d <double> _xOff(jTec, iTec, 3);
     for(j = 0; j < jTec; j++) {
       for(i = 0; i < iTec; i++) {
         _v1 >> _xOff[j][i][0] >> _xOff[j][i][1] >> _xOff[j][i][2];
         _v1.CLEANUP_TRAILERS;
       }
     }

    xOff[1].setdimsize(nVHub, nUHub0, nDimenOff-1);
    xOff[2].setdimsize(nVHub, nUHub1, nDimenOff-1);
    xOff[3].setdimsize(nVHub, nUHub2, nDimenOff-1);

     for(j = 0; j < nVHub; j++) {
       for(i = 0; i < nUHub0; i++) {
         xOff[1][j][i][0] = _xOff[j][i][0];
         xOff[1][j][i][1] = _xOff[j][i][1];
         xOff[1][j][i][2] = _xOff[j][i][2];

         xOff[2][j][i][0] = _xOff[j][nUHub0+i][0];
         xOff[2][j][i][1] = _xOff[j][nUHub0+i][1];
         xOff[2][j][i][2] = _xOff[j][nUHub0+i][2];

         xOff[3][j][i][0] = _xOff[j][nUHub0+nUHub0+i+2][0];
         xOff[3][j][i][1] = _xOff[j][nUHub0+nUHub0+i+2][1];
         xOff[3][j][i][2] = _xOff[j][nUHub0+nUHub0+i+2][2];
       }
     }
     for(i = 0; i < nVHub; i++) {
       for(j = 0; j < 2; j++) {
         xOff[2][i][nUHub0+j][0] = _xOff[i][nUHub0+nUHub0+j+1][0];
         xOff[2][i][nUHub0+j][1] = _xOff[i][nUHub0+nUHub0+j+1][1];
         xOff[2][i][nUHub0+j][2] = _xOff[i][nUHub0+nUHub0+j+1][2];
       }
     }
     for(k = 1; k < 4; k++) {
       nVOff = xOff[k].getlayersize();
       nUOff = xOff[k].getrowsize();
       for (j=0; j<nVOff; j++) {
         for (i=0; i<nUOff; i++) {
           uin[0] = cos(alphaR); //kgd double(1.0);
		         uin[1] = 0.0; //kgd -pi * xOff[k][j][i][2]/advco;
           uin[2] = sin(alphaR); //kgd pi * xOff[k][j][i][1]/advco;
           //uin[1] = -pi * xOff[k][j][i][2]/advco;
           //uin[2] =  pi * xOff[k][j][i][1]/advco;
           for (z=0; z<3; z++) {
             xOff[k][j][i][nDimenOff-4+z] = uin[z];
           }
         }
       }
     }
     //*****************************************************
     } else { 
     //*****************************************************
      double x1, x2, x3;
      for(j = 0; j < jTec; j++) {
       for(i = 0; i < iTec; i++) {
         _v1 >> x1 >> x2 >> x3; _v1.CLEANUP_TRAILERS;
       }
     }
     //****************************************************
     }
     //****************************************************
  //*******************************************************
  //} else if (BSPatch[_b].bspatch_t == WAKE_BSPLINE_PATCH) {
  //*******************************************************
    if(!check[1] && !check[2] && !check[3]) _b = 1;
    else _b = 4;
    getIJTec(_v1, iTec, jTec);
    xOff[_b].setdimsize(jTec, iTec, 3);

    for(j = 0; j < jTec; j++) 
    for(i = 0; i < iTec; i++) {
      _v1 >> xOff[_b][j][i][0]
          >> xOff[_b][j][i][1]
          >> xOff[_b][j][i][2];
      _v1.CLEANUP_TRAILERS;
    }
  //*******************************************************
  //} else;
  //*******************************************************
  //=======================================================
  //}
  //=======================================================
}  

#undef  SKIP_COMMENT_LINE
#undef  CLEANUP_TRAILERS

//... End of GlobalSurfApproxForBSplinePatches.cpp
