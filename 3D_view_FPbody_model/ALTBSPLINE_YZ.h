// ALTBSPLINE_YZ.h: interface for the CALTBSPLINE_YZ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALTBSPLINE_YZ_H__274DCC2D_A8AF_485B_AAAE_036DCD821AC0__INCLUDED_)
#define AFX_ALTBSPLINE_YZ_H__274DCC2D_A8AF_485B_AAAE_036DCD821AC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CALTBSPLINE_YZ  
{
public:
	CALTBSPLINE_YZ();
	virtual ~CALTBSPLINE_YZ();
	double *U_yz, *U_yz_dev, *u_yz, *uN_temp_dev1, *uN_temp_dev2;
	double **N_yz, **N_sig_yz, **N_dev1_yz, **N_sig_dev_1_yz, **N_dev2_yz, **N_sig_dev_2_yz;
	int index;

	void Init_U(int yzvarr)
	{
		U_yz = new double[yzvarr];
	}

	void Init_U_dev(int yzvarr)
	{
		U_yz_dev = new double[yzvarr];
	}

	void Init_N(int yzod, int yzver, int yznum)
	{
		//N_xyz
		N_yz = new double*[yzod+1];
		for(index=0;index<(yzod+1);index++)
		{
			N_yz[index] = new double[yzver];
		}
		//N_xyz

		//N_sig_xyz
		N_sig_yz = new double*[yznum];
		for(index=0;index<yznum;index++)
		{
			N_sig_yz[index] = new double[yzver];
		}
		//N_sig_xyz

		//N_dev1_xyz
		N_dev1_yz = new double*[yzod+1];
		for(index=0;index<(yzod+1);index++)
		{
			N_dev1_yz[index] = new double[yzver];
		}
		//N_dev1_xyz

		//N_sig_dev1_xyz
		N_sig_dev_1_yz = new double*[yznum];
		for(index=0;index<yznum;index++)
		{
			N_sig_dev_1_yz[index] = new double[yzver];
		}
		//N_sig_dev1_xyz

		//N_dev2_xyz
		N_dev2_yz = new double*[yzod+1];
		for(index=0;index<(yzod+1);index++)
		{
			N_dev2_yz[index] = new double[yzver];
		}
		//N_dev2_xyz

		//N_sig_dev_2_xyz
		N_sig_dev_2_yz = new double*[yznum];
		for(index=0;index<yznum;index++)
		{
			N_sig_dev_2_yz[index] = new double[yzver];
		}
		//N_sig_dev_2_xyz

		//u_yz
		u_yz = new double[yznum];
		//u_yz
		
		//uN_temp_dev1
		uN_temp_dev1 = new double[2];
		//uN_temp_dev1

		//uN_temp_dev2
		uN_temp_dev2 = new double[3];
		//uN_temp_dev2
	}
};

#endif // !defined(AFX_ALTBSPLINE_YZ_H__274DCC2D_A8AF_485B_AAAE_036DCD821AC0__INCLUDED_)
