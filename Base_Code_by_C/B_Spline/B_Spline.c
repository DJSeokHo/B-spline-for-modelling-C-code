//************************************************************************
//
//				This program is show some examples of B-splines
//											   ----made by SeokHo
//
//************************************************************************

#include <stdio.h>
#include <math.h>

#define Num 91
#define ORD 3
#define VER 12					//...Number of Vertices
#define VER_ARR VER+ORD+1		//...Number of parameter u

void create_Uni_Knot_Ver(int *u_num, int n, int p, double *knot);
int FindSpan(int n, int p, double u, double *U);
double cacu_Nki(double, double, double, double, double, double, double);

main()
{
	FILE *test=fopen("test.dat","wt");
	FILE *CP=fopen("CP.dat","wt");
	int i, j, k, cacl_KV, spn[Num], n, cout, cot;
	double x, y, u[Num], U[VER_ARR], N[ORD+1][VER], N_sig[Num][VER];	
	double ksi[VER], eta[VER];
	
	//...init coe
	ksi[0] = 0.0;
	ksi[1] = 0.02;
	ksi[2] = 0.08;
	ksi[3] = 0.3;
	ksi[4] = 0.65;
	ksi[5] = 1.0;
	ksi[6] = 1.0;
	ksi[7] = 0.66;
	ksi[8] = 0.31;
	ksi[9] = 0.08;
	ksi[10] = 0.02;
	ksi[11] = 0.0;

	eta[0] = 0.0;
	eta[1] = 0.02;
	eta[2] = 0.03;
	eta[3] = 0.04;
	eta[4] = 0.045;
	eta[5] = 0.0;
	eta[6] = 0.0;
	eta[7] = -0.03;
	eta[8] = -0.028;
	eta[9] = -0.02;
	eta[10] = -0.01;
	eta[11] =0.0;

	for(i=0;i<VER;i++)
	{
		fprintf(CP, "%lf %lf\n", ksi[i], eta[i]);
	}
	create_Uni_Knot_Ver(&cacl_KV, VER, ORD, U);
//	printf("%d\n", cacl_KV);	//......check result
	
/*
	for(i=0;i<VER_ARR;i++)
	{
		printf("%lf\n", U[i]);
	}//......check result
*/

/*
	U[0] = 0.0;
	U[1] = 0.0;
	U[2] = 0.0;
	U[3] = 0.0;
	U[4] = 1.0;
	U[5] = 2.0;
	U[6] = 3.0;
	U[7] = 3.0;
	U[8] = 3.0;
	U[9] = 4.0;
	U[10] = 4.0;
	U[11] = 4.0;
	U[12] = 4.0;
*/
	for(i=0;i<Num;i++)
	{
		u[i] = (double)i/10.0;
//		printf("%lf\n", u[i]); //......check result
		spn[i] = FindSpan(VER, ORD, u[i], U);
//		printf("%d\n", spn[i]);	//......check result
	}
	
	for(cout=0;cout<VER;cout++)
	{
	//	fprintf(test, "zone t=\"test\"\n");
		for(n=0;n<Num;n++)
		{
			x = 0.0;
			y = 0.0;
		//	fprintf(test, "%lf ", u[n]);
			for(k=0;k<=ORD;k++)
			{
				for(i=0;i<VER;i++)
				{	
					if(k==0)
					{
						if(u[n]>=U[i] && u[n]<U[i+1])
						{
							N[k][i] = 1.0;
						}
						else
						{
							N[k][i] = 0.0;
						}
					}
					else if(k==ORD&&n==Num-1&&i==VER-1)
					{
						N[k][i] = 1.0;
					}
					else
					{
						N[k][i] = cacu_Nki(u[n], U[i], N[k-1][i], U[i+k], N[k-1][i+1], U[i+k+1], U[i+1]);
					}
				}
			//	printf("\n");	//......check result
				if(k==ORD)
				{
				//	fprintf(test, "%lf\n", N[ORD][cout]);
					N_sig[n][cout] = N[ORD][cout];
				}
			}
		}
	}

	for(n=0;n<Num;n++)
	{
		x = 0.0;
		y = 0.0;
		for(cot=0;cot<VER;cot++)
		{
			x += ksi[cot] * N_sig[n][cot];
			y += eta[cot] * N_sig[n][cot];
		}
		fprintf(test, "%lf %lf\n", x, y);
	}
	

	
	return 0;
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
}//..ComputeUniformKnotVector()

//----------------------------------------------------------------------
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

double cacu_Nki(double u, double ui, double Nk_1i, double ui_k, double Nk_1i_1, double ui_k_1, double ui_1)
{
	double resl, temp_u, temp_ui, temp_Nk_1i, temp_ui_k, temp_Nk_1i_1, temp_ui_k_1, temp_ui_1, temp_left, temp_right;
	temp_u=u; temp_ui=ui; temp_Nk_1i=Nk_1i; temp_ui_k=ui_k; temp_Nk_1i_1=Nk_1i_1; temp_ui_k_1=ui_k_1; temp_ui_1=ui_1;
	if(((temp_u-temp_ui)*temp_Nk_1i)==0 || (temp_ui_k-temp_ui)==0)
	{
		temp_left=0.0;
	}
	else
	{
		temp_left=((temp_u-temp_ui)*temp_Nk_1i)/(temp_ui_k-temp_ui);
	}
	
	if(((temp_ui_k_1-temp_u)*Nk_1i_1)==0 || (temp_ui_k_1-temp_ui_1)==0)
	{
		temp_right=0.0;
	}
	else
	{
		temp_right=((temp_ui_k_1-temp_u)*Nk_1i_1)/(temp_ui_k_1-temp_ui_1);
	}		
	resl=temp_left+temp_right;
	return resl;
}