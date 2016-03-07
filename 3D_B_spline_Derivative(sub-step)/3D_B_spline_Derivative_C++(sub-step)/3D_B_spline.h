#include <iostream>
#include <cmath>
#include <fstream>

#define PI 3.1415926535

class INDX
{
public:
	//Set index
	void Set_Num_uv(int Nu, int Nv)
	{
		Num_u = Nu;
		Num_v = Nv;
	}

	void Set_ORD_ij(int Oi, int Oj)
	{
		ORD_i = Oi;
		ORD_j = Oj;
	}

	void Set_VER_ij(int Vi, int Vj)
	{
		VER_i = Vi;
		VER_j = Vj;
	}

	void Set_VER_ARR_ij()
	{
		VER_ARR_i = VER_i + ORD_i;
		VER_ARR_j = VER_j + ORD_j;
	}

	void Set_BP_ij(int Bi, int Bj)
	{
		BP_i = Bi;
		BP_j = Bj;
	}

	//Get index
	int Get_Num_u(void)
	{
		return Num_u;
	}
	int Get_Num_v(void)
	{
		return Num_v;
	}
	int Get_ORD_i(void)
	{
		return ORD_i;
	}
	int Get_ORD_j(void)
	{
		return ORD_j;
	}
	int Get_VER_i(void)
	{
		return VER_i;
	}
	int Get_VER_j(void)
	{
		return VER_j ;
	}
	int Get_VER_ARR_i(void)
	{
		return VER_ARR_i;
	}
	int Get_VER_ARR_j(void)
	{
		return VER_ARR_j;
	}
	int Get_BP_i(void)
	{
		return BP_i;
	}
	int Get_BP_j(void)
	{
		return BP_j;
	}

private:
	int Num_u;					//...umax
	int Num_v;						//...vmax
	int ORD_i;					//...i
	int ORD_j;					//...j
	int VER_i;					//...Number of i Vertices
	int VER_j;				//...Number of j Vertices
	int VER_ARR_i;		//...Number of parameter u
	int VER_ARR_j; 		//...Number of parameter v
	int BP_i;						//...i
	int BP_j;						//...j
};


class BasePNet
{
public:
	//Set
	void Set_ksi(double tk)
	{
		ksi = tk;
	}
	void Set_eta(double te)
	{
		eta = te;
	}
	void Set_zeta(double tz)
	{
		zeta = tz;
	}
	
	//Get
	double Get_ksi(void)
	{
		return ksi;
	}
	double Get_eta(void)
	{
		return eta;
	}
	double Get_zeta(void)
	{
		return zeta;
	}

private:
	double	ksi;
	double	eta;
	double  zeta;
};

class Mesod
{
public:
	double cacu_BP_sn_uv(double sn_1, double xn, double xn_1, double yn, double yn_1, double zn, double zn_1)
	{
		temp_resl=sn_1+sqrt(pow((xn-xn_1),2)+pow((yn-yn_1),2)+pow((zn-zn_1),2));
		return temp_resl;
	}

	double cacu_BP_un(double sNv_1, double sn, int BPi, int ORDi)
	{
		temp_resl=(((double)BPi-(double)ORDi)/sNv_1)*sn;
		return temp_resl;
	}

	double cacu_BP_vn(double sNv_1, double sn, int BPj, int ORDj)
	{
		temp_resl=((double)(BPj-ORDj)/sNv_1)*sn;
		return temp_resl;
	}
	
	void create_Uni_Vnj_Knot_Ver(int n, int p, double *noda)
	{
		int temp_m, temp_n, temp_p, temp_i, temp_j, temp_cot;
		double temp_maxnodavalue;
		temp_n=n; temp_p=p;
		temp_m=temp_n+temp_p+1;
		temp_maxnodavalue=(double)(temp_m-2*(temp_p+1)+1);	
		for(temp_cot=0;temp_cot<temp_n;temp_cot++)
		{
			noda[temp_cot]=0.0;
		}
		for(temp_j=0;temp_j<=temp_p;temp_j++) 
		{
			noda[temp_j]=0.0;
			noda[temp_m-temp_j]=temp_maxnodavalue;
		}
		for(temp_j=temp_p+1,temp_i=1;temp_j<=temp_n;temp_j++) 
		{
			noda[temp_j]=(double)temp_i++;
		}
	}

private:
	double temp_resl;
};