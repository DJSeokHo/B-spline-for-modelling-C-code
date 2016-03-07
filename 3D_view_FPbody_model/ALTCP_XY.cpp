// ALTCP_XY.cpp: implementation of the CALTCP_XY class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3D_view_FPbody_model.h"
#include "ALTCP_XY.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CALTCP_XY::CALTCP_XY()
{

}

CALTCP_XY::~CALTCP_XY()
{

}

void CALTCP_XY::Init_N(int xyod, int xybp)
{
	BP_N_xy = new double*[xyod+1];
	for(index=0;index<(xyod+1);index++)
	{
		BP_N_xy[index] = new double[xybp];
	}

	temp_BP_N_xy = new double*[xybp];
	for(index=0;index<xybp;index++)
	{
		temp_BP_N_xy[index] = new double[xybp];
	}

	inv_temp_BP_N_xy = new double*[xybp];
	for(index=0;index<xybp;index++)
	{
		inv_temp_BP_N_xy[index] = new double[xybp];
	}
}

void CALTCP_XY::Init_U(int xyvarr)
{
	U_xy = new double[xyvarr];	
}
