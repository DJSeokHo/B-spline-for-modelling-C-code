// BP.h: interface for the BP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BP_H__4B7F77AE_40A1_449E_B1DC_6C3AA8B010AA__INCLUDED_)
#define AFX_BP_H__4B7F77AE_40A1_449E_B1DC_6C3AA8B010AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class BP  
{
public:
	int LineStatus;	//0:Line 1:Curve
	int LineFixed;	//0:XY fixed 1:YZ fixed 2:XZ fixed

	BOOL Catch;
	BP();
	virtual ~BP();
	
	void Set_x(double tx)
	{
		x = tx;
	}
	void Set_y(double ty)
	{
		y = ty;
	}
	void Set_z(double tz)
	{
		z = tz;
	}
	double Get_x()
	{
		return x;
	}
	double Get_y()
	{
		return y;
	}
	double Get_z()
	{
		return z;
	}
	void Set_BP_sn(double sn)
	{
		BP_sn = sn;
	}
	double Get_BP_sn()
	{
		return BP_sn;
	}

	void Set_BP_un(double un)
	{
		BP_un = un;
	}
	double Get_BP_un()
	{
		return BP_un;
	}

private:
	double x, y, z;
	double BP_sn, BP_un;
};

#endif // !defined(AFX_BP_H__4B7F77AE_40A1_449E_B1DC_6C3AA8B010AA__INCLUDED_)
