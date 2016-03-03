#include <iostream>
#include <cmath>
#include <fstream>

/*
Create 2D B-spline by SeokHo(SHI HAO)
you can get some B-spline data for using Tecplot
*/

#define rad -0.3				//...Number of Kslope

#define PI 3.1415926535			//...PI

using namespace std;

////////////////////////Data Point Class
class BP
{
public:
	void Init_BP_UN()
	{
		x = new double;
		y = new double;
		z = new double;
		BP_sn = new double;
		BP_un = new double;
	}
	void Free_BP_UN()
	{
		delete x;
		delete y;
		delete z;
		delete BP_sn;
		delete BP_un;
	}
	double *x, *y, *z;
	double *BP_sn, *BP_un;
};
////////////////////////Data Point Class


////////////////////////Data for Calculating Control Points
class CALTCP_XY
{
public:
	double **U_xy, *N;
	double **BP_N_xy, **temp_BP_N_xy, **inv_temp_BP_N_xy;
	int *pivot;
	double *plusminusone, *rhs;
	void Init_U(int xyl, int xyvarr)
	{
		U_xy = new double*[xyl];
		for(int index=0;index<xyl;index++)
		{
			U_xy[index] = new double[xyvarr];
		}
	}
	void Init_N(int xyod, int xybp)
	{
		N = new double[xyod+1];
		pivot = new int[xybp];
		plusminusone = new double;
		rhs = new double[xybp];

		BP_N_xy = new double*[xyod+1];
		for(int index=0;index<(xyod+1);index++)
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

		for(index=0;index<xybp;index++)
		{
			for(int i=0;i<xybp;i++)
			{
				temp_BP_N_xy[index][i] = 0.0;
				inv_temp_BP_N_xy[index][i] = 0.0;
			}
		}
	}
};

////////////////////////Control Point Class
class CP
{
public:
	
	void Init_CP()
	{
		ksi = new double;
		eta = new double;
		zeta = new double;
		ksi_dev1 = new double;
		eta_dev1 = new double;
		zeta_dev1 = new double;
		ksi_dev2 = new double;
		eta_dev2 = new double;
		zeta_dev2 = new double;
	}
	void Free_CP()
	{
		delete ksi;
		delete eta;
		delete zeta;
		delete ksi_dev1;
		delete eta_dev1;
		delete zeta_dev1;
		delete ksi_dev2;
		delete eta_dev2;
		delete zeta_dev2;
	}
	double *ksi, *eta, *zeta;
	double *ksi_dev1, *eta_dev1, *zeta_dev1;
	double *ksi_dev2, *eta_dev2, *zeta_dev2;
};
////////////////////////Control Point Class


////////////////////////Data for Calculating Bspline
class CALTBSPLINE_XY
{
public:
	double **U_xy, **U_xy_dev, *u_xy, *uN_temp_dev1, *uN_temp_dev2, *Nu;
	double **N_xy, **N_sig_xy, **N_dev1_xy, **N_sig_dev_1_xy, **N_dev2_xy, **N_sig_dev_2_xy;
	int index;
	int *pivot;
	double *plusminusone, *rhs;
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
		Nu = new double[xyod+1];
		pivot = new int[xyver];
		plusminusone = new double;
		rhs = new double[xyver];
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


////////////////////////Method Class
class CALT_MTHOD
{
public:
	
	void cacu_BP_sn(double *sn_1, double *xn, double *xn_1, double *yn, double *yn_1, double *res)
	{
		*res = *sn_1+sqrt(pow((*xn-*xn_1),2)+pow((*yn-*yn_1),2));
	}

	void cacu_BP_un(double *sNv_1, double *sn, int od, int bp, double *res)
	{
		*res =  (((double)(bp-od) / *sNv_1)* *sn);
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
	
	void BasisFuns(int iSpan, double u, int p, double *U, double *N)
	{
		//..Compute the nonvanishing basis function, P&T p.70
		//  Input: iSpan, u, p, U
		//  Output: N
		double saved, temp;
		int j, r;
		double *left;
		double *right;
		left = (double*)malloc((p+1)*sizeof(double));
		right = (double*)malloc((p+1)*sizeof(double));

		N[0] = 1.0;
		for (j=1;j<=p;j++) 
		{
			left[j] = u - U[iSpan+1-j];
			right[j] = U[iSpan+j] - u;
			saved = 0.0;
			for (r=0;r<j;r++) 
			{
				temp = N[r]/(right[r+1]+left[j-r]);
				N[r] = saved+right[r+1]*temp;
				saved = left[j-r]*temp;
			}
			N[j] = saved;
		}
	}

	#define TINY 1.0e-20;

	void ludcmp(double **a, double **alud, int n, int *indx, double *d)
	{
		int i,imax,j,k;
		double big,dum,sum,temp;
		double *vv;

		vv=(double*)malloc(n*sizeof(double));

		*d=1.0;
		for (i=0; i<n; i++) {
		for (j=0; j<n; j++) alud[i][j]=a[i][j];
		}


		for (i=0; i<n; i++) {
		big=0.0;
		for (j=0; j<n; j++)
		if ((temp=fabs(alud[i][j])) > big) big=temp;
		//	  if (big == 0.0) nrerror("Singular matrix in routine LUDCMP");
		vv[i]=1.0/big;
		}
		for (j=0; j<n; j++) {
		for (i=0; i<j; i++) {
		sum=alud[i][j];
		for (k=0; k<i; k++) sum -= alud[i][k]*alud[k][j];
		alud[i][j]=sum;
		}
		big=0.0;
		for (i=j; i<n; i++) {
		sum=alud[i][j];
		for (k=0; k<j; k++) sum -= alud[i][k]*alud[k][j];
		alud[i][j]=sum;
		if ( (dum=vv[i]*fabs(sum)) >= big) {
		big=dum;
		imax=i;
		}
		}
		if (j != imax) {
		for (k=0; k<n; k++) {
		dum=alud[imax][k];
		alud[imax][k]=alud[j][k];
		alud[j][k]=dum;
		}
		*d = -*d;
		vv[imax]=vv[j];
		}
		indx[j]=imax;
		if (alud[j][j] == 0.0f) alud[j][j] = (double)TINY;
		if (j != n-1) {
		dum=1.0/(alud[j][j]);
		for (i=j+1; i<n; i++) alud[i][j] *= dum;
		}
		}
	}

	void  lubksb (double **alud, int n, int *indx, double *b)
	{
		int i,ii=0,ip,j,non_vanishing_index;
		double sum;

		for (i=0; i<n; i++) {
		ip=indx[i];
		sum=b[ip];
		b[ip]=b[i];

		if (ii) {
		for (j=non_vanishing_index; j<=i-1; j++)
			sum -= alud[i][j]*b[j];
		} else if (sum) {
		ii=1; non_vanishing_index = i;
		}
		b[i]=sum;
		}
		for (i=n-1; i>=0; i--) {
		sum=b[i];
		for (j=i+1; j<n; j++) sum -= alud[i][j]*b[j];
		b[i]=sum/alud[i][i];
		}
	}
/*
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
*/
	void create_Uni_Knot_Ver(int n, int p, double *knot, int verarr)
	{
		int i, j, cot, m;
		double maxknotvalue;
		m=n+p+1;
		maxknotvalue=(double)(m-2*(p+1)+1);	
		for(cot=0;cot<verarr;cot++)
		{
			knot[cot]=0.0;
		}
		for(j=0;j<=p;j++) 
		{
			knot[j]=0.0;
			knot[m-j]=maxknotvalue;
		}
		for(j=p+1,i=1;j<=n;j++) 
		{
			knot[j]=(double)i++;
		}
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
