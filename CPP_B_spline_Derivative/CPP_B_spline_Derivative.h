//************************************************************************
//
//				This program is show some examples of B-splines
//											   ----made by SeokHo
//
//************************************************************************

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>

#define rad -0.5
#define PI 3.1415926535
#define TINY 1.0e-20;

using namespace std;

class DataProp
{
public:
	void Set_LineNum(int LN)
	{
		LineNum = LN;
	}

	int Get_LineNum(void)
	{
		return LineNum;
	}
private:
	int LineNum;
};

class CalControlPoint
{
public:
	void Set_Data(int ord, int bp)
	{
		ORD = ord;
		BP = bp;
		BP_ARR = bp + ord + 1;
	}

	void Cal_Data()
	{
		BP_sn = new double[BP];
		BP_un = new double[BP];
		rhs = new double[BP];
		U = new double[BP_ARR];
		u = new double[BP];
		pivot = new int[BP];
		N = new double[ORD+1];

		BP_N = new double*[BP];
		for(int i=0;i<BP;i++)
		{
			BP_N[i] = new double[BP];
		}

		temp_BP_N = new double*[BP];
		for(i=0;i<BP;i++)
		{
			temp_BP_N[i] = new double[BP];
		}
	}

	double *BP_sn, *BP_un, plusminusone, *N;
	double *U, *u, **BP_N, **temp_BP_N, *rhs;
	int ORD, BP, BP_ARR, *pivot;
};

class CalBsplineCurve
{
public:
	
	void Set_Data(int num, int ord, int ver)
	{
		Num = num;
		ORD = ord;
		VER = ver;
		VER_ARR = ver + ord + 1;
	}
	
	void Cal_Data()
	{
		U = new double[VER_ARR];
		u = new double[Num];
	}

	double *U, *u;
	int Num, ORD, VER, VER_ARR;
};

class CalBsplineCurveSlope
{
public:
	
	void Set_Data(int num, int ord, int ver)
	{
		Num = num;
		ORD = ord;
		VER = ver;
		VER_ARR = ver + ord + 1;
	}
	
	void Cal_Data()
	{
		U = new double[VER_ARR];
		u = new double[Num];
		nders = new double*[ORD+1];
		for(int i=0;i<(ORD+1);i++)
		{
			nders[i] = new double[ORD+1];
		}
	}

	double *U, *u, **nders;
	int Num, ORD, VER, VER_ARR;
};

class BsplineCurve
{
public:
	void Set_Data(int num, int ord, int bp, int LT)
	{
		Num = num;
		ORD = ord;
		BP = bp;
		VER = BP;
		LineType = LT;
	}
	
	void Cal_Data()
	{
		BaseP_x = new double[BP];
		BaseP_y = new double[BP];
		BaseP_z = new double[BP];

		ksi = new double[VER];
		eta = new double[VER];
		zeta = new double[VER];

		x = new double[Num];
		y = new double[Num];
		z = new double[Num];

		xdev = new double*[2];
		for(int i=0;i<2;i++)
		{
			xdev[i] = new double[Num];
		}

		ydev = new double*[2];
		for(i=0;i<2;i++)
		{
			ydev[i] = new double[Num];
		}
		
		zdev = new double*[2];
		for(i=0;i<2;i++)
		{
			zdev[i] = new double[Num];
		}

		nx = new double[Num];
		ny = new double[Num];

		kslope = new double[Num];
	}
	
	double *BaseP_x, *BaseP_y, *BaseP_z, *ksi, *eta, *zeta, angle, arc;
	double *x, *y, *z, *nx, *ny, *kslope, **xdev, **ydev, **zdev;
	int Num, ORD, BP, VER, LineType;//0: WaterLine 1:BodyLine 2:SheerLine
};

class CalMethod
{
public:
	
	void create_Uni_Knot_Ver(int n, int p, double *knot)
	{
		int i, j, cot, m;
		double maxknotvalue;
		m=n+p+1;
		maxknotvalue=(double)(m-2*(p+1)+1);	
		for(cot=0;cot<m;cot++)
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
	}//..ComputeUniformKnotVector()

	//----------------------------------------------------------------------
	int FindSpan(int n, int p, double u, double *U)
	{
		int low, high, mid;// Do binary search
		low=p; 
		high=n+1;// Do binary search
		mid=(low+high)/2;
		if(u>=U[n+1])
		{
			return n; // Special case
		}
		while(u<U[mid] ||u>=U[mid+1])
		{
			if(u<U[mid])
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

	void cacu_nx(double xu, double yu, double *res)
	{
		*res=(-yu)/(sqrt(pow(yu,2)+pow(xu,2)));
	}

	void cacu_ny(double xu, double yu, double *res)
	{
		*res=(xu)/(sqrt(pow(yu,2)+pow(xu,2)));
	}

	void cacu_kslope(double xu, double yu, double xuu, double yuu, double *res)
	{
		*res=((yuu*xu)-(xuu*yu))/(pow((pow(xu,2)+pow(yu,2)),1.5));
	}

	void ang_to_rad(double *ANG, double *res)
	{
		*res=(*ANG*PI)/180;
	}

	void cacu_BP_sn(double sn_1, double xn, double xn_1, double yn, double yn_1, double *res)
	{
		*res=sn_1+sqrt(pow((xn-xn_1),2)+pow((yn-yn_1),2));
	}

	void cacu_BP_un(double sNv_1, double sn, double *res, int bp, int ord)
	{
		*res=((double)(bp-ord)/sNv_1)*sn;
	}

	void BasisFuns(int iSpan, double u, int p, double *U, double *N)
	{
		double saved, temp;
		int j, r;
		double *left;
		double *right;
		left = new double[p+1];
		right = new double[p+1];

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

	void ludcmp(double **a, double **alud, int n, int *indx, double *d)
	{
		int i,imax,j,k;
		double big,dum,sum,temp;
		double *vv;

		vv = new double[n];

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

	void lubksb (double **alud, int n, int *indx, double *b)
	{
		int i,ii=0,ip,j,non_vanishing_index;
		double sum;

		for(i=0;i<n;i++) 
		{
			ip=indx[i];
			sum=b[ip];
			b[ip]=b[i];

			if(ii) 
			{
				for(j=non_vanishing_index;j<=i-1;j++)
				{
					sum -= alud[i][j]*b[j];
				}
			} 
			else if(sum) 
			{
				ii=1; 
				non_vanishing_index = i;
			}
			b[i]=sum;
		}
		for(i=n-1;i>=0;i--) 
		{
			sum=b[i];
			for(j=i+1;j<n;j++) 
			{
				sum -= alud[i][j]*b[j];
			}
			b[i]=sum/alud[i][i];
		}
	}

	void CurvePoint(int n, int p, double *U, double *P, double u, double *S)
	{
		double *Nu;
		int k, uspan, uind;
		
		Nu = new double[p+1];

		uspan = FindSpan(n, p, u, U);
		BasisFuns(uspan, u, p, U, Nu);
		uind = uspan - p;

		*S = 0.0;
		for(k=0; k<=p; k++) 
		{
			*S += Nu[k] * P[uind+k];
		}
	}
	/*
	void CurveDerivCpts(int n, int p, double *U, double *P, int d, int r1, int r2, double **PK)
	{ 
		int tmp, r, i, k;
		r = r2-r1;
		for(i=0;i<=r;i++)
		{
			PK[0][i] = P[r1+i] ;
		}
		for(k=1;k<=d;k++)
		{
			tmp = p-k+1;
			for(i=0;i<=r-k;i++)
			{
				PK[k][i] = tmp*(PK[k-1][i+1]-PK[k-1] [i])/(U[r1+i+p+1]-U[r1+i+k]);
			}
		}
	}
	*/
	void DersBasisFuns(int iSpan, double u, int p, int n, double *U, double **ders)
	{
		//..Piegl and Tiller, Algorithm (A2.3).
		//..Compute nonzero basis functions and their
		//  derivatives, up to and including the n-th
		//  derivatives (n<=p).
		//
		//  Input: iSpan, u, p, n, U
		//  Output: ders

		int i, j, k, r, j1, j2, s1, s2, rk, pk;
		double saved, temp, d;
		double *left, *right, **ndu, **a;

		left = new double[p+1];
		right = new double[p+1];
		
		ndu = new double*[p+1];
		for(i=0;i<(p+1);i++)
		{
			ndu[i] = new double[p+1];
		}
		
		a = new double*[2];
		for(i=0;i<2;i++)
		{
			a[i] = new double[p+1];
		}

		//..Algoritm (A2.2) to compute nonzero basis functions
		ndu[0][0] = 1.0;
		for (j=1; j<=p; j++) 
		{
			left[j] = u - U[iSpan+1-j];
			right[j] = U[iSpan+j] - u;
			saved = 0.0;
			for (r=0; r<j; r++) 
			{
				//..Lower triangle
				ndu[j][r] = right[r+1] + left[j-r];
				temp = ndu[r][j-1]/ndu[j][r]; //....divide by zero...
				//..Upper triangle
				ndu[r][j] = saved + right[r+1]*temp;
				saved = left[j-r]*temp;
			}
			ndu[j][j] = saved;
		}

		for(j=0; j<=p; j++)
		{//..Load the basis functions
			ders[0][j] = ndu[j][p];
		}
		//..Compute the derivatives (Eq. [2.9])
		for (r=0; r<=p; r++) 
		{ //..Loop over function index
			s1=0; s2=1;  //..Alternate rows in array a
			a[0][0] = 1.0;
			//..Loop to compute k-th derivative
			for (k=1; k<=n; k++) 
			{
				d = 0.0;
				rk = r - k;
				pk = p - k;
				if (r>=k) 
				{
					a[s2][0] = a[s1][0] / ndu[pk+1][rk];
					d = a[s2][0] * ndu[rk][pk];
				}
				if (rk>=-1) 
				{
					j1 = 1;
				}
				else	
				{
					j1 = -rk;
				}
				if (r-1<=pk) 
				{
					j2 = k - 1;
				}
				else	 
				{
					j2 = p - r;
				}
				for (j=j1; j<=j2; j++) 
				{
					a[s2][j] = (a[s1][j] - a[s1][j-1]) / ndu[pk+1][rk+j];
					d += a[s2][j] * ndu[rk+j][pk];
				}
				if (r<=pk) 
				{
					a[s2][k] = -a[s1][k-1] / ndu[pk+1][r];
					d += a[s2][k] * ndu[r][pk];
				}
				ders[k][r] = d;
				j=s1; s1=s2; s2=j;  //..Switch rows
			}
		}
		//..Multiply through by the correct factors, (Eq. [2.9])
		r = p;
		for (k=1; k<=n; k++) 
		{
			for (j=0; j<=p; j++)
			{
				ders[k][j] *= r;
			}
			r *= (p - k);
		}
	}
};