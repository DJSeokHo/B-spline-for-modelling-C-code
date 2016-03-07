// VP.h: interface for the VP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VP_H__E7FF0E5D_BEA3_43AA_8D0E_FC0695BAF8C4__INCLUDED_)
#define AFX_VP_H__E7FF0E5D_BEA3_43AA_8D0E_FC0695BAF8C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class VP  
{
public:
	VP();
	virtual ~VP();
	
	//xyz
	void Set_ksi(double k)
	{
		ksi = k;
	}
	void Set_eta(double e)
	{
		eta = e;
	}
	void Set_zeta(double z)
	{
		zeta = z;
	}
	//xyz

	//xyz dev1
	void Set_ksi_dev1(double k1)
	{
		ksi_dev1 = k1;
	}
	void Set_eta_dev1(double e1)
	{
		eta_dev1 = e1;
	}
	void Set_zeta_dev1(double z1)
	{
		zeta_dev1 = z1;
	}
	//xyz dev1

	//xyz dev2
	void Set_ksi_dev2(double k2)
	{
		ksi_dev2 = k2;
	}
	void Set_eta_dev2(double e2)
	{
		eta_dev2 = e2;
	}
	void Set_zeta_dev2(double z2)
	{
		zeta_dev2 = z2;
	}
	//xyz dev2

	//xyz
	double Get_ksi()
	{
		return ksi;
	}
	double Get_eta()
	{
		return eta;
	}
	double Get_zeta()
	{
		return zeta;
	}
	//xyz

	//xyz dev1
	double Get_ksi_dev1()
	{
		return ksi_dev1;
	}
	double Get_eta_dev1()
	{
		return eta_dev1;
	}
	double Get_zeta_dev1()
	{
		return zeta_dev1;
	}
	//xyz dev1

	//xyz dev2
	double Get_ksi_dev2()
	{
		return ksi_dev2;
	}
	double Get_eta_dev2()
	{
		return eta_dev2;
	}
	double Get_zeta_dev2()
	{
		return zeta_dev2;
	}
	//xyz dev2

private:
	double ksi, eta, zeta;
	double ksi_dev1, eta_dev1, zeta_dev1;
	double ksi_dev2, eta_dev2, zeta_dev2;
};

#endif // !defined(AFX_VP_H__E7FF0E5D_BEA3_43AA_8D0E_FC0695BAF8C4__INCLUDED_)
