// ALTCP_YZ.h: interface for the CALTCP_YZ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALTCP_YZ_H__200B78F8_8810_438F_9F8E_71A7D963AECE__INCLUDED_)
#define AFX_ALTCP_YZ_H__200B78F8_8810_438F_9F8E_71A7D963AECE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CALTCP_YZ  
{
public:
	void Init_U(int yzvarr);
	void Init_N(int yzod, int yzbp);
	CALTCP_YZ();
	virtual ~CALTCP_YZ();
	double *U_yz;
	double **BP_N_yz, **temp_BP_N_yz, **inv_temp_BP_N_yz;
	int index;

};

#endif // !defined(AFX_ALTCP_YZ_H__200B78F8_8810_438F_9F8E_71A7D963AECE__INCLUDED_)
