// BSPLINE_XZ.h: interface for the BSPLINE_XZ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BSPLINE_XZ_H__D92EDCD3_E429_406F_BE84_DFD3DA22E784__INCLUDED_)
#define AFX_BSPLINE_XZ_H__D92EDCD3_E429_406F_BE84_DFD3DA22E784__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class BSPLINE_XZ  
{
public:
	BSPLINE_XZ();
	virtual ~BSPLINE_XZ();
	double *x, *y, *z;
	double *x_dev1, *y_dev1, *z_dev1;
	double *x_dev2, *y_dev2, *z_dev2;
	double *nx_xz, *ny_xz, *kslope_xz;
	BOOL Catch;
	int index;
	void Init(int xzn)
	{
		//xyz
		x = new double[xzn];

		y = new double[xzn];
	
		z = new double[xzn];
		//xyz

		//xyz dev1
		x_dev1 = new double[xzn];

		y_dev1 = new double[xzn];

		z_dev1 = new double[xzn];
		//xyz dev1

		//xyz dev2
		x_dev2 = new double[xzn];

		y_dev2 = new double[xzn];
		
		z_dev2 = new double[xzn];
		//xyz dev2

		//nx ny nz
		nx_xz = new double[xzn];

		ny_xz = new double[xzn];
		//nx ny

		//kslope
		kslope_xz = new double[xzn];
		//kslope
	}
};

#endif // !defined(AFX_BSPLINE_XZ_H__D92EDCD3_E429_406F_BE84_DFD3DA22E784__INCLUDED_)
