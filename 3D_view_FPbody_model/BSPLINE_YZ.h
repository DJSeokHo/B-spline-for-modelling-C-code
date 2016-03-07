// BSPLINE_YZ.h: interface for the BSPLINE_YZ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BSPLINE_YZ_H__CF24175B_D54F_4589_BDE3_9BDE4B0B20FA__INCLUDED_)
#define AFX_BSPLINE_YZ_H__CF24175B_D54F_4589_BDE3_9BDE4B0B20FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class BSPLINE_YZ  
{
public:
	BSPLINE_YZ();
	virtual ~BSPLINE_YZ();
	double *x, *y, *z;
	double *x_dev1, *y_dev1, *z_dev1;
	double *x_dev2, *y_dev2, *z_dev2;
	double *nx_yz, *ny_yz, *kslope_yz;
	BOOL Catch;

	int index;
	void Init(int yzn)
	{
		//xyz
		x = new double[yzn];

		y = new double[yzn];

		z = new double[yzn];	
		//xyz

		//xyz dev1
		x_dev1 = new double[yzn];

		y_dev1 = new double[yzn];

		z_dev1 = new double[yzn];
		//xyz dev1

		//xyz dev2
		x_dev2 = new double[yzn];

		y_dev2 = new double[yzn];
		
		z_dev2 = new double[yzn];
		//xyz dev2

		//nx ny nz
		nx_yz = new double[yzn];

		ny_yz = new double[yzn];
		//nx ny

		//kslope
		kslope_yz = new double[yzn];
		//kslope
	}
};

#endif // !defined(AFX_BSPLINE_YZ_H__CF24175B_D54F_4589_BDE3_9BDE4B0B20FA__INCLUDED_)
