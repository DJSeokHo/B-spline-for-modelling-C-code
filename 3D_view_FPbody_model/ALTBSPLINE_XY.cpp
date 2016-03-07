// ALTBSPLINE_XY.cpp: implementation of the CALTBSPLINE_XY class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3D_view_FPbody_model.h"
#include "ALTBSPLINE_XY.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CALTBSPLINE_XY::CALTBSPLINE_XY()
{

}

CALTBSPLINE_XY::~CALTBSPLINE_XY()
{

}

void CALTBSPLINE_XY::Init_U(int xyvarr)
{
	U_xy = new double[xyvarr];
}

void CALTBSPLINE_XY::Init_U_dev(int xyvarr)
{
	U_xy_dev = new double[xyvarr];
}
