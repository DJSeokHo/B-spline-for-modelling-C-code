#include <stdio.h>
#include <math.h>

#define Num 81
#define ORD 2
#define VER 9					//...Number of Vertices
#define VER_ARR VER+ORD+1		//...Number of parameter u

void create_Uni_Knot_Ver(int *u_num, int, int, double *knot);
//int FindSpan(int, int, double, double *U);
double cacu_Nki(double, double, double, double, double, double, double, double);
double cacu_x(double *Nki, double *KSI);
double cacu_y(double *Nki, double *ETA);
double cacu_x_hi(double *Nki, double *KSI, double *HI);
double cacu_y_hi(double *Nki, double *ETA, double *HI);

main()
{
	FILE *test=fopen("test.dat","wt");
	FILE *CP=fopen("CP.dat","wt");
	int i, j, k, cacl_KV, n, cout, cot;
	double x, y, u[Num], U[VER_ARR], N[ORD+1][VER], N_sig[Num][VER];	
	double ksi[VER], eta[VER], hi[VER];
	
	//...init coe
	ksi[0] = 0.0;
	ksi[1] = 1.0;
	ksi[2] = 1.0;
	ksi[3] = 1.0;
	ksi[4] = 0.0;
	ksi[5] = -1.0;
	ksi[6] = -1.0;
	ksi[7] = -1.0;
	ksi[8] = 0.0;

	eta[0] = 0.0;
	eta[1] = 0.0;
	eta[2] = 1.0;
	eta[3] = 2.0;
	eta[4] = 2.0;
	eta[5] = 2.0;
	eta[6] = 1.0;
	eta[7] = 0.0;
	eta[8] = 0.0;

	hi[0] = 1.0;
	hi[1] = 0.70711;
	hi[2] = 1.0;
	hi[3] = 0.70711;
	hi[4] = 1.0;
	hi[5] = 0.70711;
	hi[6] = 1.0;
	hi[7] = 0.70711;
	hi[8] = 1.0;

	for(i=0;i<VER;i++)
	{
		fprintf(CP, "%lf %lf\n", ksi[i], eta[i]);
	}
//	create_Uni_Knot_Ver(&cacl_KV, VER, ORD, U);
//	printf("%d\n", cacl_KV);	//......check result
	
/*
	for(i=0;i<VER_ARR;i++)
	{
		printf("%lf\n", U[i]);
	}//......check result
*/
	U[0] = 0.0;
	U[1] = 0.0;
	U[2] = 0.0;
	U[3] = 1.0;
	U[4] = 1.0;
	U[5] = 2.0;
	U[6] = 2.0;
	U[7] = 3.0;
	U[8] = 3.0;
	U[9] = 4.0;
	U[10] = 4.0;
	U[11] = 4.0;

	for(i=0;i<Num;i++)
	{
		u[i] = (double)i/20.0;	//!!!!!!!!!! Here set number of u can change the precision(point number)!!!!!!!!!!
//		printf("%lf\n", u[i]); //......check result
//		spn[i] = FindSpan(VER, ORD, u[i], U);
//		printf("%d\n", spn[i]);	//......check result
	}
	
	for(cout=0;cout<VER;cout++)
	{
	//	fprintf(test, "zone t=\"test\"\n");
		for(n=0;n<Num;n++)
		{
			x = 0.0;
			y = 0.0;
	//		fprintf(test, "%lf ", u[n]);
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
						N[k][i] = cacu_Nki(u[n], U[i], N[k-1][i], U[i+k], U[i+k+1], N[k-1][i+1], U[i+k+1], U[i+1]);
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
		x = cacu_x_hi(N_sig[n], ksi, hi);
		y = cacu_y_hi(N_sig[n], eta, hi);
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

/*//----------------------------------------------------------------------
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
}//..FindSpan()*/

double cacu_Nki(double u, double ui, double Nk_1i, double ui_k, double ui_K_1, double Nk_1i_1, double ui_k_1, double ui_1)
{
	double resl, temp_u, temp_ui, temp_Nk_1i, temp_ui_k, temp_ui_K_1, temp_Nk_1i_1, temp_ui_k_1, temp_ui_1, temp_left, temp_right;
	temp_u=u; temp_ui=ui; temp_Nk_1i=Nk_1i; temp_ui_k=ui_k; temp_ui_K_1=ui_K_1; temp_Nk_1i_1=Nk_1i_1; temp_ui_k_1=ui_k_1; temp_ui_1=ui_1;
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

double cacu_x(double *Nki, double *KSI)
{
	double temp_resl_x;
	int i;
	temp_resl_x=0.0;
	for(i=0;i<VER;i++)
	{
		temp_resl_x+=KSI[i]*Nki[i];
	}
	return temp_resl_x;
}

double cacu_y(double *Nki, double *ETA)
{
	double temp_resl_y;
	int i;
	temp_resl_y=0.0;
	for(i=0;i<VER;i++)
	{
		temp_resl_y+=ETA[i]*Nki[i];
	}
	return temp_resl_y;
}

double cacu_x_hi(double *Nki, double *KSI, double *HI)
{
	double temp_resl_x, temp_up, temp_down;
	int i;
	temp_up=0.0; temp_down=0.0;
	for(i=0;i<VER;i++)
	{
		temp_up+=KSI[i]*HI[i]*Nki[i];
		temp_down+=HI[i]*Nki[i];
	}
	temp_resl_x=temp_up/temp_down;
	return temp_resl_x;
}	

double cacu_y_hi(double *Nki, double *ETA, double *HI)
{
	double temp_resl_y, temp_up, temp_down;
	int i;
	temp_up=0.0; temp_down=0.0;
	for(i=0;i<VER;i++)
	{
		temp_up+=ETA[i]*HI[i]*Nki[i];
		temp_down+=HI[i]*Nki[i];
	}
	temp_resl_y=temp_up/temp_down;
	return temp_resl_y;
}