// ALTBSPLINE_XY.h: interface for the CALTBSPLINE_XY class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALTBSPLINE_XY_H__21F0A37C_D93B_4E01_9B96_97033C6F200C__INCLUDED_)
#define AFX_ALTBSPLINE_XY_H__21F0A37C_D93B_4E01_9B96_97033C6F200C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CALTBSPLINE_XY  
{
public:
	void Init_U_dev(int xyvarr);
	void Init_U(int xyvarr);
	CALTBSPLINE_XY();
	virtual ~CALTBSPLINE_XY();
	double *U_xy, *U_xy_dev, *u_xy, *uN_temp_dev1, *uN_temp_dev2;
	double **N_xy, **N_sig_xy, **N_dev1_xy, **N_sig_dev_1_xy, **N_dev2_xy, **N_sig_dev_2_xy;
	int index;

	void Init_N(int xyod, int xyver, int xynum)
	{
		//N_xyz
		N_xy = new double*[xyod+1];
		for(index=0;index<(xyod+1);index++)
		{
			N_xy[index] = new double[xyver];
		}
		//N_xyz

		//N_sig_xyz
		N_sig_xy = new double*[xynum];
		for(index=0;index<xynum;index++)
		{
			N_sig_xy[index] = new double[xyver];
		}
		//N_sig_xyz

		//N_dev1_xyz
		N_dev1_xy = new double*[xyod+1];
		for(index=0;index<(xyod+1);index++)
		{
			N_dev1_xy[index] = new double[xyver];
		}
		//N_dev1_xyz

		//N_sig_dev1_xyz
		N_sig_dev_1_xy = new double*[xynum];
		for(index=0;index<xynum;index++)
		{
			N_sig_dev_1_xy[index] = new double[xyver];
		}
		//N_sig_dev1_xyz

		//N_dev2_xyz
		N_dev2_xy = new double*[xyod+1];
		for(index=0;index<(xyod+1);index++)
		{
			N_dev2_xy[index] = new double[xyver];
		}
		//N_dev2_xyz

		//N_sig_dev_2_xyz
		N_sig_dev_2_xy = new double*[xynum];
		for(index=0;index<xynum;index++)
		{
			N_sig_dev_2_xy[index] = new double[xyver];
		}
		//N_sig_dev_2_xyz

		//u_xy
		u_xy = new double[xynum];
		//u_xy
		
		//uN_temp_dev1
		uN_temp_dev1 = new double[2];
		//uN_temp_dev1

		//uN_temp_dev2
		uN_temp_dev2 = new double[3];
		//uN_temp_dev2
	}
};

#endif // !defined(AFX_ALTBSPLINE_XY_H__21F0A37C_D93B_4E01_9B96_97033C6F200C__INCLUDED_)
