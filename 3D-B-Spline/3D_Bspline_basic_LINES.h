#include <iostream>
#include <cmath>
#include <fstream>

#define Num 191
#define ORD 3
#define VER 23					//...Number of Vertices	
#define VER_ARR VER+ORD+1		//...Number of parameter u
#define rad -0.3
#define BP 23
#define PI 3.1415926535

#define XYLINE 23
#define YZLINE 23
#define XZLINE 23

double **U_xy, **U_yz, **U_xz;
double **U_xy_dev, **U_yz_dev, **U_xz_dev;

class BP_XY
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

private:
	double x, y, z;
};

class BP_YZ
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

private:
	double x, y, z;
};

class BP_XZ
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
	

private:
	double x, y, z;
};

class CALTCP_XYZ
{
public:

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
	double BP_sn, BP_un;
};

class CP_XY
{
public:
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
private:
	double ksi, eta, zeta;
};

class CP_YZ
{
public: 
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
private:
	double ksi, eta, zeta;
};

class CP_XZ
{
public:
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
private:
	double ksi, eta, zeta;
};

class LINE_XY
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
	void Set_u(double tu)
	{
		u = tu;
	}
	void Set_spn(double tspn)
	{
		spn = tspn;
	}
	void Set_spn_dev(double tspn_dev)
	{
		spn_dev = tspn_dev;
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
	double Get_u()
	{
		return u;
	}
	double Get_spn()
	{
		return spn;
	}
	double Get_spn_dev()
	{
		return spn_dev;
	}
private:
	double x, y, z, u, spn, spn_dev;
};

class LINE_YZ
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
	void Set_u(double tu)
	{
		u = tu;
	}
	void Set_spn(double tspn)
	{
		spn = tspn;
	}
	void Set_spn_dev(double tspn_dev)
	{
		spn_dev = tspn_dev;
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
	double Get_u()
	{
		return u;
	}
	double Get_spn()
	{
		return spn;
	}
	double Get_spn_dev()
	{
		return spn_dev;
	}
private:
	double x, y, z, u, spn, spn_dev;
};

class LINE_XZ
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
	void Set_u(double tu)
	{
		u = tu;
	}
	void Set_spn(double tspn)
	{
		spn = tspn;
	}
	void Set_spn_dev(double tspn_dev)
	{
		spn_dev = tspn_dev;
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
	double Get_u()
	{
		return u;
	}
	double Get_spn()
	{
		return spn;
	}
	double Get_spn_dev()
	{
		return spn_dev;
	}
private:
	double x, y, z, u, spn, spn_dev;
};

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

	double cacu_BP_un(double sNv_1, double sn)
	{
		return (((double)(BP-ORD)/sNv_1)*sn);
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

	void matrix_inversion_using_elementary_operation(double original[BP][BP], double inverse[BP][BP], int dim)
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
	void create_Uni_Knot_Ver(int *u_num, int n, int p, double *knot)
	{
		int temp_m, temp_n, temp_p, i, j, cot;
		double maxknotvalue;
		temp_n=n; temp_p=p;
		temp_m=temp_n+temp_p+1;
		maxknotvalue=(double)(temp_m-2*(temp_p+1)+1);	
		for(cot=0;cot<VER_ARR;cot++)
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

	double BP_N[ORD+1][BP], temp_BP_N[BP][BP], inv_temp_BP_N[BP][BP];
};


