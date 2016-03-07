// ALTCP_YZ.cpp: implementation of the CALTCP_YZ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3D_view_FPbody_model.h"
#include "ALTCP_YZ.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CALTCP_YZ::CALTCP_YZ()
{

}

CALTCP_YZ::~CALTCP_YZ()
{

}

void CALTCP_YZ::Init_N(int yzod, int yzbp)
{
	BP_N_yz = new double*[yzod+1];
	for(index=0;index<(yzod+1);index++)
	{
		BP_N_yz[index] = new double[yzbp];
	}

	temp_BP_N_yz = new double*[yzbp];
	for(index=0;index<yzbp;index++)
	{
		temp_BP_N_yz[index] = new double[yzbp];
	}

	inv_temp_BP_N_yz = new double*[yzbp];
	for(index=0;index<yzbp;index++)
	{
		inv_temp_BP_N_yz[index] = new double[yzbp];
	}
}

void CALTCP_YZ::Init_U(int yzvarr)
{
	U_yz = new double[yzvarr];
}
