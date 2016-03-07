// ALTCP_XY.h: interface for the CALTCP_XY class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALTCP_XY_H__F2A2B133_62A2_4036_ABA9_43CA422DC416__INCLUDED_)
#define AFX_ALTCP_XY_H__F2A2B133_62A2_4036_ABA9_43CA422DC416__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CALTCP_XY  
{
public:
	void Init_U(int xyvarr);
	void Init_N(int xyod, int xybp);
	CALTCP_XY();
	virtual ~CALTCP_XY();
	double *U_xy;
	double **BP_N_xy, **temp_BP_N_xy, **inv_temp_BP_N_xy;
	int index;

};

#endif // !defined(AFX_ALTCP_XY_H__F2A2B133_62A2_4036_ABA9_43CA422DC416__INCLUDED_)
