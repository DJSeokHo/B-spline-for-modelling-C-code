// BSPLINE_XY.h: interface for the BSPLINE_XY class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BSPLINE_XY_H__5D69AA1F_700C_424A_B445_D550AFD57300__INCLUDED_)
#define AFX_BSPLINE_XY_H__5D69AA1F_700C_424A_B445_D550AFD57300__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class BSPLINE_XY  
{
public:
	BSPLINE_XY();
	virtual ~BSPLINE_XY();
	double *x, *y, *z;
	double *x_dev1, *y_dev1, *z_dev1;
	double *x_dev2, *y_dev2, *z_dev2;
	double *nx_xy, *ny_xy, *kslope_xy;
	BOOL Catch;

	int index;
	void Init(int xyn)
	{
		//xyz
		x = new double[xyn];

		y = new double[xyn];

		z = new double[xyn];
		//xyz

		//xyz dev1
		x_dev1 = new double[xyn];

		y_dev1 = new double[xyn];

		z_dev1 = new double[xyn];	
		//xyz dev1

		//xyz dev2
		x_dev2 = new double[xyn];

		y_dev2 = new double[xyn];

		z_dev2 = new double[xyn];
		//xyz dev2

		//nx ny nz
		nx_xy = new double[xyn];
		
		ny_xy = new double[xyn];
		//nx ny

		//kslope
		kslope_xy = new double[xyn];		
		//kslope
	}
};

#endif // !defined(AFX_BSPLINE_XY_H__5D69AA1F_700C_424A_B445_D550AFD57300__INCLUDED_)
