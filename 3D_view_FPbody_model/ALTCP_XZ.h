// ALTCP_XZ.h: interface for the CALTCP_XZ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALTCP_XZ_H__32BB590C_2A90_40D1_B5E1_E48D1A4CC8A6__INCLUDED_)
#define AFX_ALTCP_XZ_H__32BB590C_2A90_40D1_B5E1_E48D1A4CC8A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CALTCP_XZ  
{
public:
	void Init_U(int xzvarr);
	void Init_N(int xzod, int xzbp);
	CALTCP_XZ();
	virtual ~CALTCP_XZ();
	double *U_xz;
	double **BP_N_xz, **temp_BP_N_xz, **inv_temp_BP_N_xz;
	int index;

};

#endif // !defined(AFX_ALTCP_XZ_H__32BB590C_2A90_40D1_B5E1_E48D1A4CC8A6__INCLUDED_)
