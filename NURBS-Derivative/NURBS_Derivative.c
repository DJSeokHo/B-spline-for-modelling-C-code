//************************************************************************
//
//				This program is show some examples of B-splines
//											   ----made by SeokHo
//
//************************************************************************

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define Num 40
#define ORD 3
#define BP 6					//...Number of Vertices	
#define VER_ARR VER+ORD+1		//...Number of parameter u
#define rad -0.5
#define VER BP
#define PI 3.1415926535
#define TINY 1.0e-20

void create_Uni_Knot_Ver(int n, int p, double *knot);
void CurvePoint(int n, int p, double *U, double *P, double u, double *S);
void CurvePoint_NR(int n, int p, double *U, double *Pw, double *w, double u, double *C);
int FindSpan(int n, int p, double u, double *U);
void BasisFuns(int iSpan, double u, int p, double *U, double *N);\

main()
{
	FILE *Bspline=fopen("Bspline.dat","wt");
	FILE *Bsplineslope=fopen("Bsplineslope.dat","wt");

	FILE *CP=fopen("CP.dat","wt");
	FILE *BPxy=fopen("BPxy.dat","wt");

	int i, *pivot;

	double *BaseP_x, *BaseP_y;
	double *BP_sn, *BP_un, **BP_N, **temp_BP_N, *N;

	double *x, *y, *u, **xdev, **ydev;	
	double *ksi, *eta, *wksi, *weta, *weights, *rhs;
	

	double *U;
	double maxu, delu, **nders;
	double *nx, *ny, *kslope;

	BaseP_x = (double*)malloc(sizeof(double) * BP);
	BaseP_y = (double*)malloc(sizeof(double) * BP);
	BP_sn = (double*)malloc(sizeof(double) * BP);
	BP_un = (double*)malloc(sizeof(double) * BP);
	
	N = (double*)malloc(sizeof(double) * (ORD+1));
	U = (double*)malloc(sizeof(double) * VER_ARR);
	pivot = (int*)malloc(sizeof(int) * VER);

	rhs = (double*)malloc(sizeof(double) * VER);
	ksi = (double*)malloc(sizeof(double) * VER);
	eta = (double*)malloc(sizeof(double) * VER);
	wksi = (double*)malloc(sizeof(double) * VER);
	weta = (double*)malloc(sizeof(double) * VER);
	weights = (double*)malloc(sizeof(double) * VER);
	x = (double*)malloc(sizeof(double) * Num);
	y = (double*)malloc(sizeof(double) * Num);
	u = (double*)malloc(sizeof(double) * Num);
	nx = (double*)malloc(sizeof(double) * Num);
	ny = (double*)malloc(sizeof(double) * Num);
	kslope = (double*)malloc(sizeof(double) * Num);

	nders = (double**)malloc(sizeof(double*) * (ORD+1));
	nders[0] = (double*)malloc(sizeof(double) * (ORD+1) * (ORD+1));
	for(i=1; i<(ORD+1); i++)
	{
		nders[i] = nders[i-1] + (ORD+1);
	}

	xdev = (double**)malloc(sizeof(double*) * 2);
	xdev[0] = (double*)malloc(sizeof(double) * 2 * Num);
	for(i=1; i<2; i++)
	{
		xdev[i] = xdev[i-1] + Num;
	}

	ydev = (double**)malloc(sizeof(double*) * 2);
	ydev[0] = (double*)malloc(sizeof(double) * 2 * Num);
	for(i=1; i<2; i++)
	{
		ydev[i] = ydev[i-1] + Num;
	}

	BP_N = (double**)malloc(sizeof(double*) * BP);
	BP_N[0] = (double*)malloc(sizeof(double) * BP * BP);
	for(i=1; i<BP; i++)
	{
		BP_N[i] = BP_N[i-1] + BP;
	}
	
	temp_BP_N = (double**)malloc(sizeof(double*) * BP);
	temp_BP_N[0] = (double*)malloc(sizeof(double) * BP * BP);
	for(i=1; i<BP; i++)
	{
		temp_BP_N[i] = temp_BP_N[i-1] + BP;
	}

	create_Uni_Knot_Ver(VER, ORD, U);
	
	for(i=0;i<VER_ARR;i++)
	{
		printf("%lf\n", U[i]);
	}

	ksi[0] = 0.000;
	ksi[1] = 1.000;  
	ksi[2] = 1.000; 
	ksi[3] = 2.000;  
	ksi[4] = 2.000;
	ksi[5] = 3.000;
	
	eta[0] = 0.000;
	eta[1] = 0.000;  
	eta[2] = 1.000; 
	eta[3] = 1.000;  
	eta[4] = 0.000;
	eta[5] = 0.000; 

	for(i=0;i<VER;i++)
	{
		fprintf(CP, "%lf %lf\n", ksi[i], eta[i]);
	}
	
	weights[0] = 1.000;
	weights[1] = 1.000;  
	weights[2] = 1.000; 
	weights[3] = 1.000;  
	weights[4] = 1.000;
	weights[5] = 1.000;



	maxu = (double)(VER - ORD);
	delu = maxu / (double)(Num-1);
	
	for(i=0;i<Num;i++)
	{
		u[i] = (double)i * delu;
		CurvePoint_NR(VER-1, ORD, U, ksi, weights, u[i], &x[i]);
		CurvePoint_NR(VER-1, ORD, U, eta, weights, u[i], &y[i]);
		fprintf(Bspline, "%lf %lf\n", x[i], y[i]);
	}


	return 0;
}

void create_Uni_Knot_Ver(int n, int p, double *knot)
{
	int i, j, cot, m;
	double maxknotvalue;
	m=n+p+1;
	maxknotvalue=(double)(m-2*(p+1)+1);	
	for(cot=0;cot<VER_ARR;cot++)
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
}//..ComputeUniformKntotVector()

void CurvePoint(int n, int p, double *U, double *P, double u, double *S)
{
	double *Nu;
	int i, uspan, uind;
	Nu = (double*)malloc(sizeof(double) * (ORD+1));
	
	uspan = FindSpan(n, p, u, U);
	BasisFuns(uspan, u, p, U, Nu);
	uind = uspan - p;

	*S = 0.0;
	
	for(i=0; i<=p; i++) 
	{
		*S += Nu[i] * P[uind+i];
	}
}

void CurvePoint_NR(int n, int p, double *U, double *P, double *w, double u, double *C)
{
	double *Nu, *Ru, up, down;
	int i, k, uind, uspan;
	Nu = (double*)malloc(sizeof(double) * (ORD+1));
	
	uspan = FindSpan(n, p, u, U);
	BasisFuns(uspan, u, p, U, Nu);
	uind = uspan - p;

	up = 0.0; down = 0.0; *C = 0.0;

	for(k=0; k<=p; k++) 
	{
		up += Nu[k] * P[uind+k] * w[uind+k];
		down += Nu[k] * w[uind+k];
	}
	*C = up / down;
}

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

void BasisFuns(int iSpan, double u, int p, double *U, double *N)
{
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
