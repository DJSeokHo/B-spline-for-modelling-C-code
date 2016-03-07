// ALTBSPLINE_XZ.h: interface for the CALTBSPLINE_XZ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALTBSPLINE_XZ_H__71BC24F7_4B34_4D28_82AB_0C337CC8B355__INCLUDED_)
#define AFX_ALTBSPLINE_XZ_H__71BC24F7_4B34_4D28_82AB_0C337CC8B355__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CALTBSPLINE_XZ  
{
public:
	CALTBSPLINE_XZ();
	virtual ~CALTBSPLINE_XZ();
	double *U_xz, *U_xz_dev, *u_xz, *uN_temp_dev1, *uN_temp_dev2;
	double **N_xz, **N_sig_xz, **N_dev1_xz, **N_sig_dev_1_xz, **N_dev2_xz, **N_sig_dev_2_xz;
	int index;

	void Init_U(int xzvarr)
	{
		U_xz = new double[xzvarr];
	}

	void Init_U_dev(int xzvarr)
	{
		U_xz_dev = new double[xzvarr];
	}

	void Init_N(int xzod, int xzver, int xznum)
	{
		//N_xyz
		N_xz = new double*[xzod+1];
		for(index=0;index<(xzod+1);index++)
		{
			N_xz[index] = new double[xzver];
		}
		//N_xyz

		//N_sig_xyz
		N_sig_xz = new double*[xznum];
		for(index=0;index<xznum;index++)
		{
			N_sig_xz[index] = new double[xzver];
		}
		//N_sig_xyz

		//N_dev1_xyz
		N_dev1_xz = new double*[xzod+1];
		for(index=0;index<(xzod+1);index++)
		{
			N_dev1_xz[index] = new double[xzver];
		}
		//N_dev1_xyz

		//N_sig_dev1_xyz
		N_sig_dev_1_xz = new double*[xznum];
		for(index=0;index<xznum;index++)
		{
			N_sig_dev_1_xz[index] = new double[xzver];
		}
		//N_sig_dev1_xyz

		//N_dev2_xyz
		N_dev2_xz = new double*[xzod+1];
		for(index=0;index<(xzod+1);index++)
		{
			N_dev2_xz[index] = new double[xzver];
		}
		//N_dev2_xyz

		//N_sig_dev_2_xyz
		N_sig_dev_2_xz = new double*[xznum];
		for(index=0;index<xznum;index++)
		{
			N_sig_dev_2_xz[index] = new double[xzver];
		}
		//N_sig_dev_2_xyz

		//u_xz
		u_xz = new double[xznum];
		//u_xz
		
		//uN_temp_dev1
		uN_temp_dev1 = new double[2];
		//uN_temp_dev1

		//uN_temp_dev2
		uN_temp_dev2 = new double[3];
		//uN_temp_dev2
	}
};

#endif // !defined(AFX_ALTBSPLINE_XZ_H__71BC24F7_4B34_4D28_82AB_0C337CC8B355__INCLUDED_)
