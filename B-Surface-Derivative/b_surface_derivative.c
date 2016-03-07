//************************************************************************
//
//				This program is show some examples of B-splines
//											   ----made by SeokHo
//
//************************************************************************

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define Num_c 50					//...vmax
#define Num_r 50					//...umax

#define ORD_u 3					//...i
#define ORD_v 3					//...j

#define frow 4
#define fcol 5

#define VER_ARR_u fcol+ORD_u+1		//...Number of parameter u
#define VER_ARR_v frow+ORD_v+1		//...Number of parameter v

#define PI 3.1415926535
#define TINY 1.0e-20;
#define rad 0.002

void create_Uni_Vnj_Knot_Ver(int n, int p, double *knot);

int FindSpan(int n, int p, double u, double *U);
void cacu_nx(double, double, double *res);
void cacu_ny(double, double, double *res);
void cacu_nx_surface(double, double, double, double, double *res);
void cacu_ny_surface(double, double, double, double, double *res);
void cacu_nz_surface(double, double, double, double, double *res);
//void cacu_kslope(double, double, double, double, double *res);
void ang_to_rad(double *ANG, double *res);
void cacu_BP_sn(double, double, double, double, double, double, double, double *res);
void cacu_BP_uvn(double sNv_1, double sn, double *res, int bp, int ord);


void ludcmp(double **a, double **alud, int n, int *indx, double *d);
void lubksb (double **alud, int n, int *indx, double *b);
void BasisFuns(int iSpan, double u, int p, double *U, double *N);
void DersBasisFuns(int iSpan, double u, int p, int n, double *U, double **ders);
void SurfacePoint(int n, int p, double *U, int m, int q, double *V, double **Px, double **Py, double **Pz, double u, double v, double *Sx, double *Sy, double *Sz);

main()
{
	FILE *Bsurface=fopen("Bsurface.dat","wt");
	FILE *BCurvesurface=fopen("BCurvesurface.dat","wt");
	FILE *BsplineNBu=fopen("BsplineNBu.dat","wt");
	FILE *BsplineNBv=fopen("BsplineNBv.dat","wt");
	FILE *test=fopen("test.dat","wt");
//	FILE *Bsplineslope=fopen("Bsplineslope.dat","wt");

	FILE *CP=fopen("CP.dat","wt");

	int i, j, spn, *pivot_u, *pivot_v, cout, r, c, k, uspan, vspan;

	double **bsurf_x, **bsurf_y, **bsurf_z;
	double **bsurf_net_x, **bsurf_net_y, **bsurf_net_z;
	double **bsurface_x, **bsurface_y, **bsurface_z;
	double **BP_sn_u, **BP_sn_v, **BP_un, **BP_vn;
	double **BP_Nu, **BP_Nv, **temp_BP_Nu, **temp_BP_Nv, *Nu, *Nv, plusminusone;
	double *rhs_u, *rhs_v;
	double *u, *v, maxu, delu;

	double **xdev_u, **ydev_u, **zdev_u;	
	double **xdev_v, **ydev_v, **zdev_v;

	double *U_temp, *V_temp, *U, *V;
	double **nders_u, **nders_v;
	double **nx, **ny, **nz;

//	double *nx, *ny, *kslope;

	bsurf_x = (double**)malloc(sizeof(double*) * frow);
	bsurf_x[0] = (double*)malloc(sizeof(double) * frow * fcol);
	for(i=1; i<frow; i++)
	{
		bsurf_x[i] = bsurf_x[i-1] + fcol;
	}

	bsurf_y = (double**)malloc(sizeof(double*) * frow);
	bsurf_y[0] = (double*)malloc(sizeof(double) * frow * fcol);
	for(i=1; i<frow; i++)
	{
		bsurf_y[i] = bsurf_y[i-1] + fcol;
	}

	bsurf_z = (double**)malloc(sizeof(double*) * frow);
	bsurf_z[0] = (double*)malloc(sizeof(double) * frow * fcol);
	for(i=1; i<frow; i++)
	{
		bsurf_z[i] = bsurf_z[i-1] + fcol;
	}

	bsurf_net_x = (double**)malloc(sizeof(double*) * frow);
	bsurf_net_x[0] = (double*)malloc(sizeof(double) * frow * fcol);
	for(i=1; i<frow; i++)
	{
		bsurf_net_x[i] = bsurf_net_x[i-1] + fcol;
	}

	bsurf_net_y = (double**)malloc(sizeof(double*) * frow);
	bsurf_net_y[0] = (double*)malloc(sizeof(double) * frow * fcol);
	for(i=1; i<frow; i++)
	{
		bsurf_net_y[i] = bsurf_net_y[i-1] + fcol;
	}

	bsurf_net_z = (double**)malloc(sizeof(double*) * frow);
	bsurf_net_z[0] = (double*)malloc(sizeof(double) * frow * fcol);
	for(i=1; i<frow; i++)
	{
		bsurf_net_z[i] = bsurf_net_z[i-1] + fcol;
	}
	
	bsurface_x = (double**)malloc(sizeof(double*) * Num_r);
	bsurface_x[0] = (double*)malloc(sizeof(double) * Num_r * Num_c);
	for(i=1; i<Num_r; i++)
	{
		bsurface_x[i] = bsurface_x[i-1] + Num_c;
	}

	bsurface_y = (double**)malloc(sizeof(double*) * Num_r);
	bsurface_y[0] = (double*)malloc(sizeof(double) * Num_r * Num_c);
	for(i=1; i<Num_r; i++)
	{
		bsurface_y[i] = bsurface_y[i-1] + Num_c;
	}

	bsurface_z = (double**)malloc(sizeof(double*) * Num_r);
	bsurface_z[0] = (double*)malloc(sizeof(double) * Num_r * Num_c);
	for(i=1; i<Num_r; i++)
	{
		bsurface_z[i] = bsurface_z[i-1] + Num_c;
	}

	BP_sn_u = (double**)malloc(sizeof(double*) * frow);
	BP_sn_u[0] = (double*)malloc(sizeof(double) * frow * fcol);
	for(i=1; i<frow; i++)
	{
		BP_sn_u[i] = BP_sn_u[i-1] + fcol;
	}
	
	BP_sn_v = (double**)malloc(sizeof(double*) * fcol);
	BP_sn_v[0] = (double*)malloc(sizeof(double) * fcol * frow);
	for(i=1; i<fcol; i++)
	{
		BP_sn_v[i] = BP_sn_v[i-1] + frow;
	}

	BP_un = (double**)malloc(sizeof(double*) * frow);
	BP_un[0] = (double*)malloc(sizeof(double) * frow * fcol);
	for(i=1; i<frow; i++)
	{
		BP_un[i] = BP_un[i-1] + fcol;
	}

	BP_vn = (double**)malloc(sizeof(double*) * fcol);
	BP_vn[0] = (double*)malloc(sizeof(double) * fcol * frow);
	for(i=1; i<fcol; i++)
	{
		BP_vn[i] = BP_vn[i-1] + frow;
	}

	BP_Nu = (double**)malloc(sizeof(double*) * fcol);
	BP_Nu[0] = (double*)malloc(sizeof(double) * fcol * fcol);
	for(i=1; i<fcol; i++)
	{
		BP_Nu[i] = BP_Nu[i-1] + fcol;
	}
	
	BP_Nv = (double**)malloc(sizeof(double*) * frow);
	BP_Nv[0] = (double*)malloc(sizeof(double) * frow * frow);
	for(i=1; i<frow; i++)
	{
		BP_Nv[i] = BP_Nv[i-1] + frow;
	}

	temp_BP_Nu = (double**)malloc(sizeof(double*) * fcol);
	temp_BP_Nu[0] = (double*)malloc(sizeof(double) * fcol * fcol);
	for(i=1; i<fcol; i++)
	{
		temp_BP_Nu[i] = temp_BP_Nu[i-1] + fcol;
	}
	
	temp_BP_Nv = (double**)malloc(sizeof(double*) * frow);
	temp_BP_Nv[0] = (double*)malloc(sizeof(double) * frow * frow);
	for(i=1; i<frow; i++)
	{
		temp_BP_Nv[i] = temp_BP_Nv[i-1] + frow;
	}

	xdev_u = (double**)malloc(sizeof(double*) * Num_r);
	xdev_u[0] = (double*)malloc(sizeof(double) * Num_r * Num_c);
	for(i=1; i<Num_r; i++)
	{
		xdev_u[i] = xdev_u[i-1] + Num_c;
	}

	ydev_u = (double**)malloc(sizeof(double*) * Num_r);
	ydev_u[0] = (double*)malloc(sizeof(double) * Num_r * Num_c);
	for(i=1; i<Num_r; i++)
	{
		ydev_u[i] = ydev_u[i-1] + Num_c;
	}

	zdev_u = (double**)malloc(sizeof(double*) * Num_r);
	zdev_u[0] = (double*)malloc(sizeof(double) * Num_r * Num_c);
	for(i=1; i<Num_r; i++)
	{
		zdev_u[i] = zdev_u[i-1] + Num_c;
	}

	xdev_v = (double**)malloc(sizeof(double*) * Num_r);
	xdev_v[0] = (double*)malloc(sizeof(double) * Num_r * Num_c);
	for(i=1; i<Num_r; i++)
	{
		xdev_v[i] = xdev_v[i-1] + Num_c;
	}

	ydev_v = (double**)malloc(sizeof(double*) * Num_r);
	ydev_v[0] = (double*)malloc(sizeof(double) * Num_r * Num_c);
	for(i=1; i<Num_r; i++)
	{
		ydev_v[i] = ydev_v[i-1] + Num_c;
	}

	zdev_v = (double**)malloc(sizeof(double*) * Num_r);
	zdev_v[0] = (double*)malloc(sizeof(double) * Num_r * Num_c);
	for(i=1; i<Num_r; i++)
	{
		zdev_v[i] = zdev_v[i-1] + Num_c;
	}

	nders_u = (double**)malloc(sizeof(double*) * (ORD_u+1));
	nders_u[0] = (double*)malloc(sizeof(double) * (ORD_u+1) * (ORD_u+1));
	for(i=1; i<(ORD_u+1); i++)
	{
		nders_u[i] = nders_u[i-1] + (ORD_u+1);
	}

	nders_v = (double**)malloc(sizeof(double*) * (ORD_v+1));
	nders_v[0] = (double*)malloc(sizeof(double) * (ORD_v+1) * (ORD_v+1));
	for(i=1; i<(ORD_v+1); i++)
	{
		nders_v[i] = nders_v[i-1] + (ORD_v+1);
	}

	nx = (double**)malloc(sizeof(double*) * Num_r);
	nx[0] = (double*)malloc(sizeof(double) * Num_r * Num_c);
	for(i=1; i<Num_r; i++)
	{
		nx[i] = nx[i-1] + Num_c;
	}

	ny = (double**)malloc(sizeof(double*) * Num_r);
	ny[0] = (double*)malloc(sizeof(double) * Num_r * Num_c);
	for(i=1; i<Num_r; i++)
	{
		ny[i] = ny[i-1] + Num_c;
	}
	
	nz = (double**)malloc(sizeof(double*) * Num_r);
	nz[0] = (double*)malloc(sizeof(double) * Num_r * Num_c);
	for(i=1; i<Num_r; i++)
	{
		nz[i] = nz[i-1] + Num_c;
	}


/*
	nders_v = (double**)malloc(sizeof(double*) * (ORD_v+1));
	nders_v[0] = (double*)malloc(sizeof(double) * (ORD_v+1) * (ORD_v+1));
	for(i=1; i<(ORD_v+1); i++)
	{
		nders_v[i] = nders_v[i-1] + (ORD_v+1);
	}
*/
	U_temp = (double*)malloc(sizeof(double) * VER_ARR_u);
	V_temp = (double*)malloc(sizeof(double) * VER_ARR_v);
	
	U = (double*)malloc(sizeof(double) * VER_ARR_u);
	V = (double*)malloc(sizeof(double) * VER_ARR_v);

	Nu = (double*)malloc(sizeof(double) * (ORD_u+1));
	Nv = (double*)malloc(sizeof(double) * (ORD_v+1));
	
	pivot_u = (int*)malloc(sizeof(int) * fcol);
	pivot_v = (int*)malloc(sizeof(int) * frow);

	rhs_u = (double*)malloc(sizeof(double) * fcol);
	rhs_v = (double*)malloc(sizeof(double) * frow);
	
	u = (double*)malloc(sizeof(double) * Num_c);
	v = (double*)malloc(sizeof(double) * Num_r);

/*	
	nx = (double*)malloc(sizeof(double) * Num);
	ny = (double*)malloc(sizeof(double) * Num);
	kslope = (double*)malloc(sizeof(double) * Num);

*/	
	//...init datapoint	
	bsurf_x[0][0] = 0.0;
	bsurf_x[0][1] = 1.0;
	bsurf_x[0][2] = 2.0;
	bsurf_x[0][3] = 3.0;
	bsurf_x[0][4] = 4.0;

	bsurf_x[1][0] = 0.0;
	bsurf_x[1][1] = 1.0;
	bsurf_x[1][2] = 2.0;
	bsurf_x[1][3] = 3.0;
	bsurf_x[1][4] = 4.0;

	bsurf_x[2][0] = 0.0;
	bsurf_x[2][1] = 1.0;
	bsurf_x[2][2] = 2.0;
	bsurf_x[2][3] = 3.0;
	bsurf_x[2][4] = 4.0;

	bsurf_x[3][0] = 0.0;
	bsurf_x[3][1] = 1.0;
	bsurf_x[3][2] = 2.0;
	bsurf_x[3][3] = 3.0;
	bsurf_x[3][4] = 4.0;

	bsurf_y[0][0] = 0.3;
	bsurf_y[0][1] = 0.3;
	bsurf_y[0][2] = 0.3;
	bsurf_y[0][3] = 0.3;
	bsurf_y[0][4] = 0.3;

	bsurf_y[1][0] = 1.0;
	bsurf_y[1][1] = 1.0;
	bsurf_y[1][2] = 1.0;
	bsurf_y[1][3] = 1.0;
	bsurf_y[1][4] = 1.0;

	bsurf_y[2][0] = 2.0;
	bsurf_y[2][1] = 2.0;
	bsurf_y[2][2] = 2.0;
	bsurf_y[2][3] = 2.0;
	bsurf_y[2][4] = 2.0;

	bsurf_y[3][0] = 3.0;
	bsurf_y[3][1] = 3.0;
	bsurf_y[3][2] = 3.0;
	bsurf_y[3][3] = 3.0;
	bsurf_y[3][4] = 3.0;

	bsurf_z[0][0] = -0.5;
	bsurf_z[0][1] = 0.0;
	bsurf_z[0][2] = 0.3;
	bsurf_z[0][3] = 0.0;
	bsurf_z[0][4] = -0.5;

	bsurf_z[1][0] = 1.0;
	bsurf_z[1][1] = 1.8;
	bsurf_z[1][2] = 2.1;
	bsurf_z[1][3] = 1.8;
	bsurf_z[1][4] = 1.0;

	bsurf_z[2][0] = 2.3;
	bsurf_z[2][1] = 2.8;
	bsurf_z[2][2] = 3.1;
	bsurf_z[2][3] = 2.8;
	bsurf_z[2][4] = 2.3;

	bsurf_z[3][0] = 2.5;
	bsurf_z[3][1] = 3.0;
	bsurf_z[3][2] = 3.3;
	bsurf_z[3][3] = 3.0;
	bsurf_z[3][4] = 2.5;


	for(i=0;i<frow;i++)
	{
		fprintf(Bsurface, "zone t=\"BSurfaceNet\"\n");
		for(j=0;j<fcol;j++)
		{
			fprintf(Bsurface, "%lf %lf %lf\n", bsurf_x[i][j], bsurf_y[i][j], bsurf_z[i][j]);
		}
	}

	for(j=0;j<fcol;j++)
	{
		fprintf(Bsurface, "zone t=\"BSurfaceNet\"\n");
		for(i=0;i<frow;i++)
		{
			fprintf(Bsurface, "%lf %lf %lf\n", bsurf_x[i][j], bsurf_y[i][j], bsurf_z[i][j]);
		}
	}
	
	//...calculate arc length for basis point u
	for(i=0;i<frow;i++)
	{
		for(j=0;j<fcol;j++)
		{
			if(j==0)
			{
				BP_sn_u[i][0] = 0.0;
			}
			else
			{
				cacu_BP_sn(BP_sn_u[i][j-1], bsurf_x[i][j], bsurf_x[i][j-1], bsurf_y[i][j], bsurf_y[i][j-1], bsurf_z[i][j], bsurf_z[i][j-1], &BP_sn_u[i][j]);
			}
//			printf("%lf\n", BP_sn_u[i][j]);
		}
//		printf("\n");
	}
	
	//...calculate arc length for basis point v
	for(j=0;j<fcol;j++)
	{
		for(i=0;i<frow;i++)
		{
			if(i==0)
			{
				BP_sn_v[j][0] = 0.0;
			}
			else
			{
				cacu_BP_sn(BP_sn_v[j][i-1], bsurf_x[i][j], bsurf_x[i-1][j], bsurf_y[i][j], bsurf_y[i-1][j], bsurf_z[i][j], bsurf_z[i-1][j], &BP_sn_v[j][i]);
			}
//			printf("%lf\n", BP_sn_v[j][i]);
		}
//		printf("\n");
	}

	//...calculate the u parameter
	for(i=0;i<frow;i++)
	{
		for(j=0;j<fcol;j++)
		{
			cacu_BP_uvn(BP_sn_u[i][fcol-1], BP_sn_u[i][j], &BP_un[i][j], fcol, ORD_u);	
//			printf("%lf ", BP_sn_u[i][j]);
		}
//		printf("\n");
	}

	//...create temp U knot
	create_Uni_Vnj_Knot_Ver(fcol, ORD_u, U_temp);
	

	//...calculate the v parameter
	for(j=0;j<fcol;j++)
	{
		for(i=0;i<frow;i++)
		{
			cacu_BP_uvn(BP_sn_v[j][frow-1], BP_sn_v[j][i], &BP_vn[j][i], frow, ORD_v);	
//			printf("%lf ", BP_vn[j][i]);
		}
//		printf("\n");
	}
	//...create temp V knot
	create_Uni_Vnj_Knot_Ver(frow, ORD_v, V_temp);
	
	for(i=0;i<fcol;i++)
	{
		for(j=0;j<fcol;j++)
		{
			BP_Nu[i][j] = 0.0;
			temp_BP_Nu[i][j] = 0.0;
		//	printf("%lf ", BP_Nu[i][j]);
		//	printf("%lf ", temp_BP_Nu[i][j]);
		}
	//	printf("\n");
	}

	for(j=0;j<frow;j++)
	{
		for(i=0;i<frow;i++)
		{
			BP_Nv[j][i] = 0.0;
			temp_BP_Nv[j][i] = 0.0;
		//	printf("%lf ", BP_Nv[j][i]);
		//	printf("%lf ", temp_BP_Nv[j][i]);
		}
	//	printf("\n");
	}

	for(cout=0;cout<frow;cout++)
	{
		for(j=0;j<fcol;j++) 
		{
			spn = FindSpan(fcol-1, ORD_u, BP_un[cout][j], U_temp);
			BasisFuns(spn, BP_un[cout][j], ORD_u, U_temp, Nu); 
			for(i=0;i<=ORD_u;i++) 
			{
				BP_Nu[j][spn-ORD_u+i] = Nu[i];
			}
		}	
		ludcmp(BP_Nu, temp_BP_Nu, fcol, pivot_u, &plusminusone);  
		
		for(i=0;i<fcol;i++) 
		{
			rhs_u[i] = bsurf_x[cout][i];
		}
		lubksb(temp_BP_Nu, fcol, pivot_u, rhs_u);
		for(i=0;i<fcol;i++) 
		{
			bsurf_net_x[cout][i] = rhs_u[i];
		}
		
		for(i=0;i<fcol;i++) 
		{
			rhs_u[i] = bsurf_y[cout][i];
		}
		lubksb(temp_BP_Nu, fcol, pivot_u, rhs_u);
		for(i=0;i<fcol;i++) 
		{
			bsurf_net_y[cout][i] = rhs_u[i];
		}

		for(i=0;i<fcol;i++) 
		{
			rhs_u[i] = bsurf_z[cout][i];
		}
		lubksb(temp_BP_Nu, fcol, pivot_u, rhs_u);
		for(i=0;i<fcol;i++) 
		{
			bsurf_net_z[cout][i] = rhs_u[i];
		}
	}
	
	for(cout=0;cout<fcol;cout++)
	{
		for(j=0;j<frow;j++) 
		{
			spn = FindSpan(frow-1, ORD_v, BP_vn[cout][j], V_temp);
			BasisFuns(spn, BP_vn[cout][j], ORD_v, V_temp, Nv); 
			for(i=0;i<=ORD_v;i++) 
			{
				BP_Nv[j][spn-ORD_v+i] = Nv[i];
			}
		}
		ludcmp(BP_Nv, temp_BP_Nv, frow, pivot_v, &plusminusone);  
		
		for(i=0;i<frow;i++) 
		{
			rhs_v[i] = bsurf_net_x[i][cout];
		}
		lubksb(temp_BP_Nv, frow, pivot_v, rhs_v);
		for(i=0;i<frow;i++) 
		{
			bsurf_net_x[i][cout] = rhs_v[i];
		}
		
		for(i=0;i<frow;i++) 
		{
			rhs_v[i] = bsurf_net_y[i][cout];
		}
		lubksb(temp_BP_Nv, frow, pivot_v, rhs_v);
		for(i=0;i<frow;i++) 
		{
			bsurf_net_y[i][cout] = rhs_v[i];
		}

		for(i=0;i<frow;i++) 
		{
			rhs_v[i] = bsurf_net_z[i][cout];
		}
		lubksb(temp_BP_Nv, frow, pivot_v, rhs_v);
		for(i=0;i<frow;i++) 
		{
			bsurf_net_z[i][cout] = rhs_v[i];
		}
	}
	
	for(i=0;i<frow;i++)
	{
		fprintf(CP, "zone t=\"CP\"\n");
		for(j=0;j<fcol;j++)
		{
			fprintf(CP, "%lf %lf %lf\n", bsurf_net_x[i][j], bsurf_net_y[i][j], bsurf_net_z[i][j]);
		}
	}
	
	for(i=0;i<fcol;i++)
	{
		fprintf(CP, "zone t=\"CP\"\n");
		for(j=0;j<frow;j++)
		{
			fprintf(CP, "%lf %lf %lf\n", bsurf_net_x[j][i], bsurf_net_y[j][i], bsurf_net_z[j][i]);
		}
	}
	
	create_Uni_Vnj_Knot_Ver(fcol, ORD_u, U);
	create_Uni_Vnj_Knot_Ver(frow, ORD_v, V);

	maxu = (double)(fcol - ORD_u);
	delu = maxu / (double)(Num_c-1);
	for(i=0;i<Num_c;i++)
	{
		u[i] = (double)i * delu;
	//	printf("%lf\n", u[i]);
	}

	maxu = (double)(frow - ORD_v);
	delu = maxu / (double)(Num_r-1);
	for(i=0;i<Num_r;i++)
	{
		v[i] = (double)i * delu;
	//	printf("%lf\n", v[i]);
	}

	
//SurfacePoint(int n, int p, double *U, int m, int q, double *V, double **P, double u, double v, double *Sx)
	
	for(i=0;i<Num_r;i++)
	{
		for(j=0;j<Num_c;j++)
		{
			SurfacePoint(fcol-1, ORD_u, U, frow-1, ORD_v, V, bsurf_net_x, bsurf_net_y, bsurf_net_z, u[j], v[i], &bsurface_x[i][j], &bsurface_y[i][j], &bsurface_z[i][j]);
		}
	}
	
	for(i=0;i<Num_r;i++)
	{
		fprintf(BCurvesurface, "zone t=\"BCurvesurface\"\n");
		for(j=0;j<Num_c;j++)
		{
			fprintf(BCurvesurface, "%lf %lf %lf\n", bsurface_x[i][j], bsurface_y[i][j], bsurface_z[i][j]);
		}
	}

	for(i=0;i<Num_c;i++)
	{
		fprintf(BCurvesurface, "zone t=\"BCurvesurface\"\n");
		for(j=0;j<Num_r;j++)
		{
			fprintf(BCurvesurface, "%lf %lf %lf\n", bsurface_x[j][i], bsurface_y[j][i], bsurface_z[j][i]);
		}
	}
/*	
	for(k=0;k<2;k++)
	{
		for(i=0;i<1;i++)
		{
			for(j=0;j<Num_c;j++)
			{
				xdev[i][j] = 0.0;
				ydev[i][j] = 0.0;
				zdev[i][j] = 0.0;
				uspan = FindSpan(fcol-1, ORD_u, u[j], U);
				DersBasisFuns(uspan, u[j], ORD_u, k+1, U, nders_u);
				for(c=0;c<=ORD_u;c++)
				{
					xdev[i][j] += nders_u[k+1][c] * bsurf_net_x[i][uspan-ORD_u+c];
					ydev[i][j] += nders_u[k+1][c] * bsurf_net_y[i][uspan-ORD_u+c];
					zdev[i][j] += nders_u[k+1][c] * bsurf_net_z[i][uspan-ORD_u+c];
				}
				
				if(k==0)
				{
					fprintf(BsplineNBu, "zone t=\"BsplineNB\"\n");
					cacu_nx(xdev[i][j], zdev[i][j], &nx_u[i][j]);
					cacu_ny(xdev[i][j], zdev[i][j], &ny_u[i][j]);
					fprintf(BsplineNBu, "%lf %lf %lf\n", bsurface_x[i][j], bsurface_y[i][j], bsurface_z[i][j]);
					fprintf(BsplineNBu, "%lf %lf %lf\n", bsurface_x[i][j]+nx_u[i][j], bsurface_y[i][j], bsurface_z[i][j]+ny_u[i][j]);
				}
			}
		}
	}
*/
/*
	for(k=0;k<2;k++)
	{
		for(i=0;i<Num_r;i++)
		{
			for(j=0;j<1;j++)
			{
				xdev[i][j] = 0.0;
				ydev[i][j] = 0.0;
				zdev[i][j] = 0.0;
				vspan = FindSpan(frow-1, ORD_v, v[i], V);
				DersBasisFuns(vspan, v[i], ORD_v, k+1, V, nders_v);
				for(r=0;r<=ORD_v;r++)
				{
					xdev[i][j] += nders_v[k+1][r] * bsurf_net_x[vspan-ORD_v+r][j];
					ydev[i][j] += nders_v[k+1][r] * bsurf_net_y[vspan-ORD_v+r][j];
					zdev[i][j] += nders_v[k+1][r] * bsurf_net_z[vspan-ORD_v+r][j];
				}

				if(k==0)
				{
					fprintf(BsplineNBv, "zone t=\"BsplineNBv\"\n");
					cacu_nx(ydev[i][j], zdev[i][j], &nx_u[i][j]);
					cacu_ny(ydev[i][j], zdev[i][j], &ny_u[i][j]);
					fprintf(BsplineNBv, "%lf %lf %lf\n", bsurface_x[i][j], bsurface_y[i][j], bsurface_z[i][j]);
					fprintf(BsplineNBv, "%lf %lf %lf\n", bsurface_x[i][j], bsurface_y[i][j]+nx_u[i][j], bsurface_z[i][j]+ny_u[i][j]);
				}
			}
		}
	}
*/

	for(k=0;k<1;k++)			
	{
		for(i=0;i<Num_r;i++)
		{
			for(j=0;j<Num_c;j++)
			{
				xdev_u[i][j] = xdev_v[i][j] = 0.0;
				ydev_u[i][j] = ydev_v[i][j] = 0.0;
				zdev_u[i][j] = zdev_v[i][j] = 0.0;
		
				uspan = FindSpan(fcol-1, ORD_u, u[j], U);
				DersBasisFuns(uspan, u[j], ORD_u, k+1, U, nders_u);
				vspan = FindSpan(frow-1, ORD_v, v[i], V);
				DersBasisFuns(vspan, v[i], ORD_v, k+1, V, nders_v);

				for(r=0;r<=ORD_v;r++)
				{
					for(c=0;c<=ORD_u;c++)
					{
						xdev_u[i][j] += nders_u[k+1][c] * bsurf_net_x[vspan-ORD_v+r][uspan-ORD_u+c];
						ydev_u[i][j] += nders_u[k+1][c] * bsurf_net_y[vspan-ORD_v+r][uspan-ORD_u+c];
						zdev_u[i][j] += nders_u[k+1][c] * bsurf_net_z[vspan-ORD_v+r][uspan-ORD_u+c];

						xdev_v[i][j] += bsurf_net_x[vspan-ORD_v+r][uspan-ORD_u+c] * nders_v[k+1][r];
						ydev_v[i][j] += bsurf_net_y[vspan-ORD_v+r][uspan-ORD_u+c] * nders_v[k+1][r];
						zdev_v[i][j] += bsurf_net_z[vspan-ORD_v+r][uspan-ORD_u+c] * nders_v[k+1][r];
					}
				}
				cacu_nx_surface(ydev_u[i][j], zdev_v[i][j], ydev_v[i][j], zdev_u[i][j], &nx[i][j]);
				cacu_ny_surface(zdev_u[i][j], xdev_v[i][j], zdev_v[i][j], xdev_u[i][j], &ny[i][j]);
				cacu_nz_surface(xdev_u[i][j], ydev_v[i][j], xdev_v[i][j], ydev_u[i][j], &nz[i][j]);
				fprintf(test, "zone t=\"test\"\n");
				fprintf(test, "%lf %lf %lf\n", bsurface_x[i][j], bsurface_y[i][j], bsurface_z[i][j]);
				fprintf(test, "%lf %lf %lf\n", bsurface_x[i][j]+nx[i][j]*rad, bsurface_y[i][j]+ny[i][j]*rad, bsurface_z[i][j]+nz[i][j]*rad);
			}
		}

	}		

/*

	for(k=0;k<1;k++)
	{
		for(i=0;i<Num_r;i++)
		{
			for(j=0;j<Num_c;j++)
			{
				xdev_v[i][j] = 0.0;
				ydev_v[i][j] = 0.0;
				zdev_v[i][j] = 0.0;
				
				uspan = FindSpan(fcol-1, ORD_u, u[j], U);
				DersBasisFuns(uspan, u[j], ORD_u, k+1, U, nders_u);

				vspan = FindSpan(frow-1, ORD_v, v[i], V);
				DersBasisFuns(vspan, v[i], ORD_v, k+1, V, nders_v);

				for(r=0;r<=ORD_v;r++)
				{
					xdev_u[i][j] = 0.0;
					ydev_u[i][j] = 0.0;
					zdev_u[i][j] = 0.0;

					for(c=0;c<=ORD_u;c++)
					{
						xdev_u[i][j] += nders_u[k+1][c] * bsurf_net_x[vspan-ORD_v+r][uspan-ORD_u+c];
						ydev_u[i][j] += nders_u[k+1][c] * bsurf_net_y[vspan-ORD_v+r][uspan-ORD_u+c];
						zdev_u[i][j] += nders_u[k+1][c] * bsurf_net_z[vspan-ORD_v+r][uspan-ORD_u+c];
					}
				
					xdev_v[i][j] += xdev_u[i][j] * nders_v[k+1][r];
					ydev_v[i][j] += ydev_u[i][j] * nders_v[k+1][r];
					zdev_v[i][j] += zdev_u[i][j] * nders_v[k+1][r];
				}			
			}
		}
	}
*/

/*
	BaseP_x[0] = -4.000;
	BaseP_x[1] = 0.000;  
	BaseP_x[2] = 3.037; 
	BaseP_x[3] = 5.941;  
	BaseP_x[4] = 7.769;
	BaseP_x[5] = 8.406; 
	BaseP_x[6] = 8.948;  
	BaseP_x[7] = 9.075;
	BaseP_x[8] = 8.789;   
	BaseP_x[9] = 7.705;
	BaseP_x[10] = 5.941;
	BaseP_x[11] = 3.037;
	BaseP_x[12] = 0.000; 
	BaseP_x[13] = 0.000; 
	BaseP_x[14] = 0.034; 
	BaseP_x[15] = 0.524;  
	BaseP_x[16] = 1.267;  
	BaseP_x[17] = 3.037;
	BaseP_x[18] = 5.941; 
*/	
/*
	BaseP_y[0] = 0.000;
	BaseP_y[1] = 1.252;  
	BaseP_y[2] = 2.340; 
	BaseP_y[3] = 4.206;  
	BaseP_y[4] = 6.000;
	BaseP_y[5] = 7.000; 
	BaseP_y[6] = 8.000;  
	BaseP_y[7] = 9.000;
	BaseP_y[8] = 10.000;   
	BaseP_y[9] = 11.000;
	BaseP_y[10] = 11.198;
	BaseP_y[11] = 11.516;
	BaseP_y[12] = 11.947; 
	BaseP_y[13] = 12.300; 
	BaseP_y[14] = 13.000; 
	BaseP_y[15] = 14.500;  
	BaseP_y[16] = 16.000;  
	BaseP_y[17] = 18.640;
	BaseP_y[18] = 23.013;

	ksi[0] = 0.000;
	ksi[1] = 0.250;  
	ksi[2] = 0.500; 
	ksi[3] = 0.500;  
	ksi[4] = 0.750;
	ksi[5] = 1.000;

	eta[0] = 0.000;
	eta[1] = -1.000;  
	eta[2] = -0.200; 
	eta[3] = -0.200;  
	eta[4] = -0.950;
	eta[5] = 0.150;
*/

	return 0;
}

void cacu_BP_sn(double sn_1, double xn, double xn_1, double yn, double yn_1, double zn, double zn_1, double *res)
{
	*res=sn_1+sqrt(pow((xn-xn_1),2)+pow((yn-yn_1),2)+pow((zn-zn_1),2));
}

void cacu_BP_uvn(double sNv_1, double sn, double *res, int bp, int ord)
{
	*res=((double)(bp-ord)/sNv_1)*sn;
}

void create_Uni_Vnj_Knot_Ver(int n, int p, double *knot)
{
	int i, j, cot, m;
	double maxknotvalue;
	m=n+p+1;
	maxknotvalue=(double)(m-2*(p+1)+1);	
	for(cot=0;cot<n;cot++)
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

void SurfacePoint(int n, int p, double *U, int m, int q, double *V, double **Px, double **Py, double **Pz, double u, double v, double *Sx, double *Sy, double *Sz)
{
	//..Piegl and Tiller, Algorithm (A3.5)
	int uspan, vspan, l, k, uind, vind;
	double tempx, tempy, tempz, *tp_Nu, *tp_Nv;

	tp_Nu = (double*)malloc(sizeof(double) * (p+1));
	tp_Nv = (double*)malloc(sizeof(double) * (q+1));

	uspan = FindSpan(n, p, u, U);
	BasisFuns(uspan, u, p, U, tp_Nu);
	vspan = FindSpan(m, q, v, V);
	BasisFuns(vspan, v, q, V, tp_Nv);

	uind = uspan - p;

	*Sx = *Sy = *Sz = 0.0;
	for(l=0;l<=q;l++) 
	{
		tempx = tempy = tempz = 0.0;
		vind = vspan - q + l;
		for(k=0;k<=p;k++) 
		{ 
			tempx += tp_Nu[k] * Px[vind][uind+k];
			tempy += tp_Nu[k] * Py[vind][uind+k];
			tempz += tp_Nu[k] * Pz[vind][uind+k];
		}
		*Sx += tp_Nv[l] * tempx;
		*Sy += tp_Nv[l] * tempy;
		*Sz += tp_Nv[l] * tempz;
	}
	free(tp_Nu);
	free(tp_Nv);
}

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

void cacu_nx_surface(double ydu, double zdv, double ydv, double zdu, double *res)
{
	*res=ydu*zdv-ydv*zdu;
}

void cacu_ny_surface(double zdu, double xdv, double zdv, double xdu, double *res)
{
	*res=zdu*xdv-zdv*xdu;
}

void cacu_nz_surface(double xdu, double ydv, double xdv, double ydu, double *res)
{
	*res=xdu*ydv-xdv*ydu;
}


void cacu_nx(double xu, double yu, double *res)
{
	*res=(-yu)/(sqrt(pow(yu,2)+pow(xu,2)));
}

void cacu_ny(double xu, double yu, double *res)
{
	*res=(xu)/(sqrt(pow(yu,2)+pow(xu,2)));
}

