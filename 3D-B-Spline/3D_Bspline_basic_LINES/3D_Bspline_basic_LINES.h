#include <iostream>
#include <cmath>
#include <fstream>

#define Num 191					//...Number of Bspline Point

#define rad -0.5				//...Number of Kslope

#define PI 3.1415926535			//...PI

using namespace std;

////////////////////////Data Point Class
class BP
{
public:
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
////////////////////////Data Point Class


////////////////////////Data for Calculating Control Points
class CALTCP_XY
{
public:
	double **U_xy;
	double **BP_N_xy, **temp_BP_N_xy, **inv_temp_BP_N_xy;
	int index;
	void Init_U(int xyl, int xyvarr)
	{
		U_xy = new double*[xyl];
		for(index=0;index<xyl;index++)
		{
			U_xy[index] = new double[xyvarr];
		}
	}
	void Init_N(int xyod, int xybp)
	{
		BP_N_xy = new double*[xyod+1];
		for(index=0;index<(xyod+1);index++)
		{
			BP_N_xy[index] = new double[xybp];
		}

		temp_BP_N_xy = new double*[xybp];
		for(index=0;index<xybp;index++)
		{
			temp_BP_N_xy[index] = new double[xybp];
		}

		inv_temp_BP_N_xy = new double*[xybp];
		for(index=0;index<xybp;index++)
		{
			inv_temp_BP_N_xy[index] = new double[xybp];
		}
	}
};

class CALTCP_YZ
{
public:
	double **U_yz;
	double **BP_N_yz, **temp_BP_N_yz, **inv_temp_BP_N_yz;
	int index;
	void Init_U(int yzl, int yzvarr)
	{
		U_yz = new double*[yzl];
		for(index=0;index<yzl;index++)
		{
			U_yz[index] = new double[yzvarr];
		}
	}
	void Init_N(int yzod, int yzbp)
	{
		BP_N_yz = new double*[yzod+1];
		for(index=0;index<(yzod+1);index++)
		{
			BP_N_yz[index] = new double[yzbp];
		}

		temp_BP_N_yz = new double*[yzbp];
		for(index=0;index<yzbp;index++)
		{
			temp_BP_N_yz[index] = new double[yzbp];
		}

		inv_temp_BP_N_yz = new double*[yzbp];
		for(index=0;index<yzbp;index++)
		{
			inv_temp_BP_N_yz[index] = new double[yzbp];
		}
	}
};

class CALTCP_XZ
{
public:
	double **U_xz;
	double **BP_N_xz, **temp_BP_N_xz, **inv_temp_BP_N_xz;
	int index;
	void Init_U(int xzl, int xzvarr)
	{
		U_xz = new double*[xzl];
		for(index=0;index<xzl;index++)
		{
			U_xz[index] = new double[xzvarr];
		}
	}
	void Init_N(int xzod, int xzbp)
	{
		BP_N_xz = new double*[xzod+1];
		for(index=0;index<(xzod+1);index++)
		{
			BP_N_xz[index] = new double[xzbp];
		}

		temp_BP_N_xz = new double*[xzbp];
		for(index=0;index<xzbp;index++)
		{
			temp_BP_N_xz[index] = new double[xzbp];
		}

		inv_temp_BP_N_xz = new double*[xzbp];
		for(index=0;index<xzbp;index++)
		{
			inv_temp_BP_N_xz[index] = new double[xzbp];
		}
	}
};
////////////////////////Data for Calculating Control Points


////////////////////////Control Point Class
class CP
{
public:
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
////////////////////////Control Point Class


////////////////////////Data for Calculating Bspline
class CALTBSPLINE_XY
{
public:
	double **U_xy, **U_xy_dev, *u_xy, *uN_temp_dev1, *uN_temp_dev2;
	double **N_xy, **N_sig_xy, **N_dev1_xy, **N_sig_dev_1_xy, **N_dev2_xy, **N_sig_dev_2_xy;
	int index;

	void Init_U(int xyl, int xyvarr)
	{
		U_xy = new double*[xyl];
		for(index=0;index<xyl;index++)
		{
			U_xy[index] = new double[xyvarr];
		}
	}

	void Init_U_dev(int xyl, int xyvarr)
	{
		U_xy_dev = new double*[xyl];
		for(index=0;index<xyl;index++)
		{
			U_xy_dev[index] = new double[xyvarr];
		}
	}

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

class CALTBSPLINE_YZ
{
public:
	double **U_yz, **U_yz_dev, *u_yz, *uN_temp_dev1, *uN_temp_dev2;
	double **N_yz, **N_sig_yz, **N_dev1_yz, **N_sig_dev_1_yz, **N_dev2_yz, **N_sig_dev_2_yz;
	int index;

	void Init_U(int yzl, int yzvarr)
	{
		U_yz = new double*[yzl];
		for(index=0;index<yzl;index++)
		{
			U_yz[index] = new double[yzvarr];
		}
	}

	void Init_U_dev(int yzl, int yzvarr)
	{
		U_yz_dev = new double*[yzl];
		for(index=0;index<yzl;index++)
		{
			U_yz_dev[index] = new double[yzvarr];
		}
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

class CALTBSPLINE_XZ
{
public:
	double **U_xz, **U_xz_dev, *u_xz, *uN_temp_dev1, *uN_temp_dev2;
	double **N_xz, **N_sig_xz, **N_dev1_xz, **N_sig_dev_1_xz, **N_dev2_xz, **N_sig_dev_2_xz;
	int index;

	void Init_U(int xzl, int xzvarr)
	{
		U_xz = new double*[xzl];
		for(index=0;index<xzl;index++)
		{
			U_xz[index] = new double[xzvarr];
		}
	}

	void Init_U_dev(int xzl, int xzvarr)
	{
		U_xz_dev = new double*[xzl];
		for(index=0;index<xzl;index++)
		{
			U_xz_dev[index] = new double[xzvarr];
		}
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
////////////////////////Data for Calculating Bspline


////////////////////////BSpline Class
class BSPLINE_XY
{
public:
	double **x, **y, **z;
	double **x_dev1, **y_dev1, **z_dev1;
	double **x_dev2, **y_dev2, **z_dev2;
	double **nx_xy, **ny_xy, **kslope_xy;

	int index;
	void Init(int xyl, int xyn)
	{
		//xyz
		x = new double*[xyl];
		for(index=0;index<xyl;index++)
		{
			x[index] = new double[xyn];
		}
		y = new double*[xyl];
		for(index=0;index<xyl;index++)
		{
			y[index] = new double[xyn];
		}
		z = new double*[xyl];
		for(index=0;index<xyl;index++)
		{
			z[index] = new double[xyn];
		}
		//xyz

		//xyz dev1
		x_dev1 = new double*[xyl];
		for(index=0;index<xyl;index++)
		{
			x_dev1[index] = new double[xyn];
		}
		y_dev1 = new double*[xyl];
		for(index=0;index<xyl;index++)
		{
			y_dev1[index] = new double[xyn];
		}
		z_dev1 = new double*[xyl];
		for(index=0;index<xyl;index++)
		{
			z_dev1[index] = new double[xyn];
		}
		//xyz dev1

		//xyz dev2
		x_dev2 = new double*[xyl];
		for(index=0;index<xyl;index++)
		{
			x_dev2[index] = new double[xyn];
		}
		y_dev2 = new double*[xyl];
		for(index=0;index<xyl;index++)
		{
			y_dev2[index] = new double[xyn];
		}
		z_dev2 = new double*[xyl];
		for(index=0;index<xyl;index++)
		{
			z_dev2[index] = new double[xyn];
		}
		//xyz dev2

		//nx ny nz
		nx_xy = new double*[xyl];
		for(index=0;index<xyl;index++)
		{
			nx_xy[index] = new double[xyn];
		}
	
		ny_xy = new double*[xyl];
		for(index=0;index<xyl;index++)
		{
			ny_xy[index] = new double[xyn];
		}
		//nx ny

		//kslope
		kslope_xy = new double*[xyl];
		for(index=0;index<xyl;index++)
		{
			kslope_xy[index] = new double[xyn];
		}
		//kslope
	}
};

class BSPLINE_YZ
{
public:
	double **x, **y, **z;
	double **x_dev1, **y_dev1, **z_dev1;
	double **x_dev2, **y_dev2, **z_dev2;
	double **nx_yz, **ny_yz, **kslope_yz;

	int index;
	void Init(int yzl, int yzn)
	{
		//xyz
		x = new double*[yzl];
		for(index=0;index<yzl;index++)
		{
			x[index] = new double[yzn];
		}
		y = new double*[yzl];
		for(index=0;index<yzl;index++)
		{
			y[index] = new double[yzn];
		}
		z = new double*[yzl];
		for(index=0;index<yzl;index++)
		{
			z[index] = new double[yzn];
		}
		//xyz

		//xyz dev1
		x_dev1 = new double*[yzl];
		for(index=0;index<yzl;index++)
		{
			x_dev1[index] = new double[yzn];
		}
		y_dev1 = new double*[yzl];
		for(index=0;index<yzl;index++)
		{
			y_dev1[index] = new double[yzn];
		}
		z_dev1 = new double*[yzl];
		for(index=0;index<yzl;index++)
		{
			z_dev1[index] = new double[yzn];
		}
		//xyz dev1

		//xyz dev2
		x_dev2 = new double*[yzl];
		for(index=0;index<yzl;index++)
		{
			x_dev2[index] = new double[yzn];
		}
		y_dev2 = new double*[yzl];
		for(index=0;index<yzl;index++)
		{
			y_dev2[index] = new double[yzn];
		}
		z_dev2 = new double*[yzl];
		for(index=0;index<yzl;index++)
		{
			z_dev2[index] = new double[yzn];
		}
		//xyz dev2

		//nx ny nz
		nx_yz = new double*[yzl];
		for(index=0;index<yzl;index++)
		{
			nx_yz[index] = new double[yzn];
		}
	
		ny_yz = new double*[yzl];
		for(index=0;index<yzl;index++)
		{
			ny_yz[index] = new double[yzn];
		}
		//nx ny

		//kslope
		kslope_yz = new double*[yzl];
		for(index=0;index<yzl;index++)
		{
			kslope_yz[index] = new double[yzn];
		}
		//kslope
	}
};

class BSPLINE_XZ
{
public:
	double **x, **y, **z;
	double **x_dev1, **y_dev1, **z_dev1;
	double **x_dev2, **y_dev2, **z_dev2;
	double **nx_xz, **ny_xz, **kslope_xz;

	int index;
	void Init(int xzl, int xzn)
	{
		//xyz
		x = new double*[xzl];
		for(index=0;index<xzl;index++)
		{
			x[index] = new double[xzn];
		}
		y = new double*[xzl];
		for(index=0;index<xzl;index++)
		{
			y[index] = new double[xzn];
		}
		z = new double*[xzl];
		for(index=0;index<xzl;index++)
		{
			z[index] = new double[xzn];
		}
		//xyz

		//xyz dev1
		x_dev1 = new double*[xzl];
		for(index=0;index<xzl;index++)
		{
			x_dev1[index] = new double[xzn];
		}
		y_dev1 = new double*[xzl];
		for(index=0;index<xzl;index++)
		{
			y_dev1[index] = new double[xzn];
		}
		z_dev1 = new double*[xzl];
		for(index=0;index<xzl;index++)
		{
			z_dev1[index] = new double[xzn];
		}
		//xyz dev1

		//xyz dev2
		x_dev2 = new double*[xzl];
		for(index=0;index<xzl;index++)
		{
			x_dev2[index] = new double[xzn];
		}
		y_dev2 = new double*[xzl];
		for(index=0;index<xzl;index++)
		{
			y_dev2[index] = new double[xzn];
		}
		z_dev2 = new double*[xzl];
		for(index=0;index<xzl;index++)
		{
			z_dev2[index] = new double[xzn];
		}
		//xyz dev2

		//nx ny nz
		nx_xz = new double*[xzl];
		for(index=0;index<xzl;index++)
		{
			nx_xz[index] = new double[xzn];
		}
	
		ny_xz = new double*[xzl];
		for(index=0;index<xzl;index++)
		{
			ny_xz[index] = new double[xzn];
		}
		//nx ny

		//kslope
		kslope_xz = new double*[xzl];
		for(index=0;index<xzl;index++)
		{
			kslope_xz[index] = new double[xzn];
		}
		//kslope
	}
};
////////////////////////BSpline Class


////////////////////////Method Class
class CALT_MTHOD
{
public:
	double ang_to_rad(double ANG)
	{
		return(ANG*PI)/180;
	}
	
	double cacu_BP_sn(double sn_1, double xn, double xn_1, double yn, double yn_1)
	{
		return (sn_1+sqrt(pow((xn-xn_1),2)+pow((yn-yn_1),2)));
	}

	double cacu_BP_un(double sNv_1, double sn, int od, int bp)
	{
		return (((double)(bp-od)/sNv_1)*sn);
	}

	double cacu_Nki(double u, double ui, double Nk_1i, double ui_k, double Nk_1i_1, double ui_k_1, double ui_1)
	{
		double temp_left, temp_right;
		if(((u-ui)*Nk_1i)==0 || (ui_k-ui)==0)
		{
			temp_left=0.0;
		}
		else
		{
			temp_left=((u-ui)*Nk_1i)/(ui_k-ui);
		}
		
		if(((ui_k_1-u)*Nk_1i_1)==0 || (ui_k_1-ui_1)==0)
		{
			temp_right=0.0;
		}
		else
		{
			temp_right=((ui_k_1-u)*Nk_1i_1)/(ui_k_1-ui_1);
		}		
		return temp_left+temp_right;
	}

	double cacu_Nki_dev(int tk, double ui, double Nk_1i, double ui_k, double Nk_1i_1, double ui_k_1, double ui_1)
	{
		double temp_left, temp_right;
		if(tk==0 || (ui_k-ui)==0)
		{
			temp_left=0.0;
		}
		else
		{
			temp_left=tk*(Nk_1i)/(ui_k-ui);
		}
		
		if(tk==0 || (ui_k_1-ui_1)==0)
		{
			temp_right=0.0;
		}
		else
		{
			temp_right=tk*(Nk_1i_1)/(ui_k_1-ui_1);
		}		
		return temp_left-temp_right;
	}
	
	double cacu_nx(double xu, double yu)
	{
		return (-yu)/(sqrt(pow(yu,2)+pow(xu,2)));
	}

	double cacu_ny(double xu, double yu)
	{
		return (xu)/(sqrt(pow(yu,2)+pow(xu,2)));
	}
	
	double cacu_kslope(double xu, double yu, double xuu, double yuu)
	{
		double temp_up, temp_down;
		temp_up=(yuu*xu)-(xuu*yu);
		temp_down=pow((pow(xu,2)+pow(yu,2)),1.5);
		return temp_up/temp_down;
	}

	void matrix_inversion_using_elementary_operation(double **original, double **inverse, int dim)
	{
		int row, column, pivot_column, max_index;
		double max_value, ftemp1, ftemp2, pivot_value;
		for( row = 0; row < dim; row++ )
			for( column = 0; column < dim; column++ ){
				if( row == column )
					inverse[row][column] = 1;
				else
					inverse[row][column] = 0;
			}
			for( pivot_column = 0; pivot_column < dim; pivot_column++ ){
				max_index = original[0][column];
				max_value = 0;
				for( row = pivot_column; row < dim; row++ )
					if( original[row][pivot_column]*original[row][pivot_column] > max_value*max_value ){
						max_index = row;
						max_value = original[row][pivot_column];
					}
					if(pivot_column != max_index )
						for( column = 0; column < dim; column++ ){
							ftemp1 = original[pivot_column][column];
							ftemp2 = inverse[pivot_column][column];
							original[pivot_column][column] = original[max_index][column];
							inverse[pivot_column][column] = inverse[max_index][column];
							original[max_index][column] = ftemp1;
							inverse[max_index][column] = ftemp2;
						}
						pivot_value = original[pivot_column][pivot_column];
						for(column = 0; column < dim; column++ ){
							original[pivot_column][column] /= pivot_value;
							inverse[pivot_column][column] /= pivot_value;
						}
						for( row = 0; row < dim; row++ )
							if( row != pivot_column ){
								ftemp1 = original[row][pivot_column];
								for( column = 0; column < dim; column++ ){

									original[row][column] -= ftemp1*original[pivot_column][column];
									inverse[row][column] -= ftemp1*inverse[pivot_column][column];

								}
							}
			}
	}

	void create_Uni_Knot_Ver(int *u_num, int n, int p, double *knot, int verarr)
	{
		int temp_m, temp_n, temp_p, i, j, cot;
		double maxknotvalue;
		temp_n=n; temp_p=p;
		temp_m=temp_n+temp_p+1;
		maxknotvalue=(double)(temp_m-2*(temp_p+1)+1);	
		for(cot=0;cot<verarr;cot++)
		{
			knot[cot]=0.0;
		}
		for(j=0;j<=p;j++) 
		{
			knot[j]=0.0;
			knot[temp_m-j]=maxknotvalue;
		}
		for(j=p+1,i=1;j<=n;j++) 
		{
			knot[j]=(double)i++;
		}
		*u_num = temp_m;
	}

	int FindSpan(int n, int p, double u, double *U)
	{
		int temp_n, temp_p, low, high, mid;// Do binary search
		double temp_u;
		temp_n=n; temp_p=p; temp_u=u;
		low=temp_p; 
		high=temp_n+1;// Do binary search
		mid=(low+high)/2;
		if(temp_u>=U[temp_n+1])
		{
			return temp_n; // Special case
		}
		while(temp_u<U[mid] || temp_u>=U[mid+1])
		{
			if(temp_u<U[mid])
			{
				high=mid;
			}
			else
			{
				low=mid;
			}
			mid=(low+high)/2;
		}
		return mid;
	}//..FindSpan()
};
////////////////////////Method Class
