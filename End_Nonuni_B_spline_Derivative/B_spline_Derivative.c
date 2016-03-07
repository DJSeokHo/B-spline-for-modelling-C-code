//************************************************************************
//
//				This program is show some examples of B-splines
//											   ----made by SeokHo
//
//************************************************************************

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define Num 100
#define ORD 3
#define ENDD 2
#define BP 7				
#define VER_ARR VER+ORD+1		//...Number of parameter u
#define rad -0.5
#define VER BP
#define PI 3.1415926535
#define TINY 1.0e-20

void create_Uni_Knot_Ver(int n, int p, double *knot);
void create_Nonuni_Knot_Ver(int n, int p, double *arc_per_length, double *knot);
void create_End_Nonuni_Knot_Ver(int n, int p, double *arc_per_length, double *knot);

int FindSpan(int n, int p, double u, double *U);
void cacu_nx(double, double, double *res);
void cacu_ny(double, double, double *res);
void cacu_kslope(double, double, double, double, double *res);
void ang_to_rad(double *ANG, double *res);
void cacu_BP_sn(double *dests, double, double, double, double, double, double *res);
void cacu_BP_dests(double, double, double, double, double *dests);
void cacu_BP_un(double sNv_1, double sn, double *res, int bp, int ord);


void ludcmp(double **a, double **alud, int n, int *indx, double *d);
void lubksb (double **alud, int n, int *indx, double *b);
//void CurveDerivCpts(int n, int p, double *U, double *P, int d, int r1, int r2, double **PK);
void BasisFuns(int iSpan, double u, int p, double *U, double *N);
void CurvePoint(int n, int p, double *U, double *P, double u, double *S);
void DersBasisFuns(int iSpan, double u, int p, int n, double *U, double **ders);

main()
{
	FILE *Bspline=fopen("Bspline.dat","wt");
	FILE *Bsplineslope=fopen("Bsplineslope.dat","wt");

	FILE *CP=fopen("CP.dat","wt");
	FILE *BPxy=fopen("BPxy.dat","wt");
	
	FILE *test=fopen("test.dat","wt");

	int k, i, j, spn, *pivot;

	double *BaseP_x, *BaseP_y, *End_BaseP_x, *End_BaseP_y, angle, arc, D0_x, D0_y, Dn_x, Dn_y;
	double *BP_sn, *BP_dests, **BP_N, **temp_BP_N, *N, plusminusone;

	double *x, *y, *u, **xdev, **ydev;	
	double *ksi, *eta, *rhs;

	double *U, *Nonuni_U, *End_Nonuni_U;
	double maxu, delu, **nders;
	double *nx, *ny, *kslope;

	BaseP_x = (double*)malloc(sizeof(double) * BP);
	BaseP_y = (double*)malloc(sizeof(double) * BP);
	End_BaseP_x = (double*)malloc(sizeof(double) * (BP+ENDD));
	End_BaseP_y = (double*)malloc(sizeof(double) * (BP+ENDD));
	BP_sn = (double*)malloc(sizeof(double) * BP);
	BP_dests = (double*)malloc(sizeof(double));

	N = (double*)malloc(sizeof(double) * (ORD+1));
	U = (double*)malloc(sizeof(double) * (VER_ARR+ENDD));
	Nonuni_U = (double*)malloc(sizeof(double) * VER_ARR);
	End_Nonuni_U = (double*)malloc(sizeof(double) * (VER_ARR+ENDD));
	pivot = (int*)malloc(sizeof(int) * (VER+ENDD));

	rhs = (double*)malloc(sizeof(double) * (VER+ENDD));
	ksi = (double*)malloc(sizeof(double) * (VER+ENDD));
	eta = (double*)malloc(sizeof(double) * (VER+ENDD));
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
/*
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
*/	
	BP_N = (double**)malloc(sizeof(double*) * (BP+ENDD));
	BP_N[0] = (double*)malloc(sizeof(double) * (BP+ENDD) * (BP+ENDD));
	for(i=1; i<(BP+ENDD); i++)
	{
		BP_N[i] = BP_N[i-1] + (BP+ENDD);
	}
	
	temp_BP_N = (double**)malloc(sizeof(double*) * (BP+ENDD));
	temp_BP_N[0] = (double*)malloc(sizeof(double) * (BP+ENDD) * (BP+ENDD));
	for(i=1; i<(BP+ENDD); i++)
	{
		temp_BP_N[i] = temp_BP_N[i-1] + (BP+ENDD);
	}

	//...init datapoint	.... bow shape

	BaseP_x[0] = 0.000; 
	BaseP_x[1] = 0.200; 
	BaseP_x[2] = 1.000; 
	BaseP_x[3] = 1.500; 
	BaseP_x[4] = 2.500; 
	BaseP_x[5] = 3.100; 
	BaseP_x[6] = 2.500; 
//	BaseP_x[7] = 3.500; 

	BaseP_y[0] = 0.000;
	BaseP_y[1] = 0.500;
	BaseP_y[2] = 0.700;
	BaseP_y[3] = 0.250;
	BaseP_y[4] = 0.000;
	BaseP_y[5] = 1.150;
	BaseP_y[6] = 1.330;
//	BaseP_y[7] = 1.700; 

//init End BP	
	for(i=0;i<(BP+ENDD);i++)
	{
		End_BaseP_x[i] = End_BaseP_y[i] = 0.0;
	}

	End_BaseP_x[0] = BaseP_x[0];
	End_BaseP_y[0] = BaseP_y[0];

	End_BaseP_x[BP+ENDD-1] = BaseP_x[BP-1];
	End_BaseP_y[BP+ENDD-1] = BaseP_y[BP-1];

	for(i=ENDD;i<(BP+ENDD)-2;i++)
	{
		End_BaseP_x[i] = BaseP_x[i-ENDD/2];
		End_BaseP_y[i] = BaseP_y[i-ENDD/2];
	}

	for(i=0;i<BP;i++)
	{
		fprintf(BPxy, "%lf %lf\n", BaseP_x[i], BaseP_y[i]);
	}

	*BP_dests = 0.0;
	for(i=1;i<BP;i++)
	{
		cacu_BP_dests(BaseP_x[i], BaseP_x[i-1], BaseP_y[i], BaseP_y[i-1], BP_dests);
	}
	
//	D0 = Dn = *BP_dests * 0.0;
	
	End_BaseP_x[ENDD/2] = 0.000;
	End_BaseP_y[ENDD/2] = 10.000;//D0;
	End_BaseP_x[BP+ENDD-2] = -10.000;
	End_BaseP_y[BP+ENDD-2] = 0.000;//Dn;

	for(i=0;i<(BP+ENDD);i++)
	{
//		printf("%lf %lf\n", End_BaseP_x[i], End_BaseP_y[i]);
	}

	for(i=0;i<BP;i++)
	{
		if(i==0)
		{
			BP_sn[i] = 0.0;
		}
		else
		{
			cacu_BP_sn(BP_dests, BP_sn[i-1], BaseP_x[i], BaseP_x[i-1], BaseP_y[i], BaseP_y[i-1], &BP_sn[i]);
		}
//		printf("%lf\n", BP_sn[i]);
	}
	
//	create_Nonuni_Knot_Ver(BP, ORD, BP_sn, Nonuni_U);
	create_End_Nonuni_Knot_Ver(BP, ORD, BP_sn, End_Nonuni_U);

	for(i=0;i<VER_ARR;i++)
	{
//		printf("%lf\n", Nonuni_U[i]);
	}

	for(i=0;i<(VER_ARR+ENDD);i++)
	{
//		printf("%lf\n", End_Nonuni_U[i]);
	}
/*
	for(i=0;i<BP;i++)
	{
		for(j=0;j<BP;j++)
		{
			BP_N[i][j] = 0.0;
			temp_BP_N[i][j] = 0.0;
		}
	}
	
	for(j=0;j<BP;j++) 
	{
		spn = FindSpan(BP-1, ORD, BP_sn[j], Nonuni_U);
		BasisFuns(spn, BP_sn[j], ORD, Nonuni_U, N); 
		for(i=0;i<=ORD;i++) 
		{
			BP_N[j][spn-ORD+i] = N[i];
		}
	}

	for(i=0;i<BP;i++)
	{
		for(j=0;j<BP;j++)
		{
			fprintf(test, "%lf ", BP_N[i][j]);
		}
		fprintf(test, "\n");
	}
*/

	for(i=0;i<(BP+ENDD);i++)
	{
		for(j=0;j<(BP+ENDD);j++)
		{
			BP_N[i][j] = 0.0;
			temp_BP_N[i][j] = 0.0;
		}
	}
	
	for(j=1;j<(BP+ENDD)-1;j++) 
	{
		spn = FindSpan((BP+ENDD)-1, ORD, BP_sn[j-1], End_Nonuni_U);
		BasisFuns(spn, BP_sn[j-1], ORD, End_Nonuni_U, N); 
		for(i=0;i<=ORD;i++) 
		{
			BP_N[j][spn-ORD+i] = N[i];
		}
	}
	
	for(j=1;j<(BP+ENDD)-1;j++)
	{
		if(j==(0+ENDD/2) || j==((BP+ENDD)-2))
		{
			spn = FindSpan((BP+ENDD)-1, ORD, BP_sn[j-1], End_Nonuni_U);
			DersBasisFuns(spn, BP_sn[j-1], ORD, 1, End_Nonuni_U, nders);
			for(i=0;i<=ORD;i++) 
			{
				BP_N[j][spn-ORD+i] = nders[1][i];
			}
		}
	}
	
	BP_N[0][0] = BP_N[BP+ENDD-1][BP+ENDD-1]= 1.0;
/*
	for(i=0;i<(BP+ENDD);i++)
	{
		for(j=0;j<(BP+ENDD);j++)
		{
			fprintf(test, "%lf ", BP_N[i][j]);
		}
		fprintf(test, "\n");
	}
*/

	ludcmp(BP_N, temp_BP_N, (BP+ENDD), pivot, &plusminusone);  

	for(i=0;i<(BP+ENDD);i++) 
	{
		rhs[i] = End_BaseP_x[i];
	}
	lubksb(temp_BP_N, (BP+ENDD), pivot, rhs);
	for(i=0;i<(BP+ENDD);i++) 
	{
		ksi[i] = rhs[i];
	}

	for(i=0;i<(BP+ENDD);i++) 
	{
		rhs[i] = End_BaseP_y[i];
	}
	lubksb(temp_BP_N, (BP+ENDD), pivot, rhs);
	for(i=0;i<(BP+ENDD);i++) 
	{
		eta[i] = rhs[i];
	}
	
	for(i=0;i<(VER+ENDD);i++)
	{
		fprintf(CP, "%lf %lf\n", ksi[i], eta[i]);
	}

	create_Uni_Knot_Ver((VER+ENDD), ORD, U);

	maxu = (double)((VER+ENDD) - ORD);
	delu = maxu / (double)(Num-1);
	
	for(i=0;i<Num;i++)
	{
		u[i] = (double)i * delu;
		CurvePoint((VER+ENDD)-1, ORD, U, ksi, u[i], &x[i]);
		CurvePoint((VER+ENDD)-1, ORD, U, eta, u[i], &y[i]);
		fprintf(Bspline, "%lf %lf\n", x[i], y[i]);
	}

	for(k=0;k<2;k++)
	{
		for(i=0;i<Num;i++)
		{
			xdev[k][i] = 0.0;
			ydev[k][i] = 0.0;
			spn = FindSpan((VER+ENDD)-1, ORD, u[i], U);
			DersBasisFuns(spn, u[i], ORD, k+1, U, nders);
			for(j=0;j<=ORD;j++)
			{
				xdev[k][i] += nders[k+1][j] * ksi[spn-ORD+j];
				ydev[k][i] += nders[k+1][j] * eta[spn-ORD+j];
			}
		}
	}

	for(i=0;i<Num;i++)
	{
		fprintf(Bsplineslope, "zone t=\"Bsplineslope\"\n");
		cacu_nx(xdev[0][i], ydev[0][i], &nx[i]);
		cacu_ny(xdev[0][i], ydev[0][i], &ny[i]);
		cacu_kslope(xdev[0][i], ydev[0][i], xdev[1][i], ydev[1][i], &kslope[i]);
		fprintf(Bsplineslope, "%lf %lf\n", x[i], y[i]);
		fprintf(Bsplineslope, "%lf %lf\n", x[i]+nx[i]*kslope[i]*rad, y[i]+ny[i]*kslope[i]*rad);
	}
/*	*/
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
}//..ComputeUniformKnotVector()

void create_Nonuni_Knot_Ver(int n, int p, double *arc_per_length, double *knot)
{
	int i, j, m, lop;
	m=n+p+1;
	for(lop=0;lop<m;lop++)
	{
		knot[lop]=0.0;
		if(lop>=0 && lop<=p)
		{
			knot[lop]=0.0;
		}
		if(lop>=m-p-1 && lop<m)
		{
			knot[lop]=1.0;
		}
	}
	for(j=1;j<n-p;j++)
	{
		for(i=j;i<=j+p-1;i++)
		{
			knot[j+p]+=arc_per_length[i];
		}
		knot[j+p]=knot[j+p]/p;
	}
}

void create_End_Nonuni_Knot_Ver(int n, int p, double *arc_per_length, double *knot)
{
	
	int i, j, m, lop;
	m=n+p+1+ENDD;
	for(lop=0;lop<m;lop++)
	{
		knot[lop]=0.0;
		if(lop>=0 && lop<=p)
		{
			knot[lop]=0.0;
		}
		if(lop>=m-p-1 && lop<m)
		{
			knot[lop]=1.0;
		}
	}
	for(j=0;j<n-p+1;j++)
	{
		for(i=j;i<=j+p-1;i++)
		{
			knot[j+p+1]+=arc_per_length[i];
		}
		knot[j+p+1]=knot[j+p+1]/p;
	}
}

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
	if((-yu)==0 && sqrt(pow(yu,2)+pow(xu,2))==0)
	{
		*res=0.0;
	}
	else
	{
		*res=(-yu)/(sqrt(pow(yu,2)+pow(xu,2)));
	}
}

void cacu_ny(double xu, double yu, double *res)
{
	if((xu)==0 && sqrt(pow(yu,2)+pow(xu,2))==0)
	{
		*res=0.0;
	}
	else
	{
		*res=(xu)/(sqrt(pow(yu,2)+pow(xu,2)));
	}
}

void cacu_kslope(double xu, double yu, double xuu, double yuu, double *res)
{
	if(((yuu*xu)-(xuu*yu))==0 && (pow((pow(xu,2)+pow(yu,2)),1.5))==0)
	{
		*res=0.0;
	}
	else
	{
		*res=((yuu*xu)-(xuu*yu))/(pow((pow(xu,2)+pow(yu,2)),1.5));
	}
}

void ang_to_rad(double *ANG, double *res)
{
	*res=(*ANG*PI)/180;
}

void cacu_BP_sn(double *dests, double sn_1, double xn, double xn_1, double yn, double yn_1, double *res)
{
	*res=sn_1+sqrt(fabs(pow((xn-xn_1),2)+pow((yn-yn_1),2)))/ *dests;
}

void cacu_BP_dests(double xn, double xn_1, double yn, double yn_1, double *dests)
{
	*dests+=sqrt(fabs(pow((xn-xn_1),2)+pow((yn-yn_1),2)));
}

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
	Nu = (double*)malloc(sizeof(double) * (ORD+1));

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

	left = (double*)malloc((p+1) * sizeof(double));
	right = (double*)malloc((p+1) * sizeof(double));
	
	ndu = (double**)malloc(sizeof(double*) * (p+1));
	ndu[0] = (double*)malloc(sizeof(double) * (p+1) * (p+1));
	for(i=1; i<(p+1); i++)
	{
		ndu[i] = ndu[i-1] + (p+1);
	}
	
	a = (double**)malloc(sizeof(double*) * 2);
	a[0] = (double*)malloc(sizeof(double) * 2 * (p+1));
	for(i=1; i<2; i++)
	{
		a[i] = a[i-1] + (p+1);
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
