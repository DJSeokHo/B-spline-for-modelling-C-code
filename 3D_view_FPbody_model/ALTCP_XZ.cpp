// ALTCP_XZ.cpp: implementation of the CALTCP_XZ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3D_view_FPbody_model.h"
#include "ALTCP_XZ.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CALTCP_XZ::CALTCP_XZ()
{

}

CALTCP_XZ::~CALTCP_XZ()
{

}

void CALTCP_XZ::Init_N(int xzod, int xzbp)
{
	BP_N_xz = new double*[xzod+1];
	for(index=0;index<(xzod+1);index++)
	{
		BP_N_xz[index] = new double[xzbp];
	}

	temp_BP_N_xz = new double*[xzbp];
	for(index=0;index<xzbp;index++)
	{
		temp_BP_N_xz[index] = new double[xzbp];
	}

	inv_temp_BP_N_xz = new double*[xzbp];
	for(index=0;index<xzbp;index++)
	{
		inv_temp_BP_N_xz[index] = new double[xzbp];
	}
}

void CALTCP_XZ::Init_U(int xzvarr)
{
	U_xz = new double[xzvarr];
}
