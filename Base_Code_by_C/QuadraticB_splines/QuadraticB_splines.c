//************************************************************************
//
//				This program is show an example of Quadratic B-splines
//											   ----made by SeokHo
//
//************************************************************************

#include <stdio.h>
#include <math.h>

#define ORD 2
#define N 21
#define VER 4

double cacu_N_start(int, int, double);
double cacu_N_end(int, int, double);

main()
{
	FILE *CP=fopen("control polygon.dat","wt");
	FILE *test=fopen("test.dat","wt");
	int i, n;
	double u[N], x, y, sig_x, sig_y;
	double ksi[VER], eta[VER];

	//...init coe
	ksi[0] = 0.1;
	ksi[1] = 0.1;
	ksi[2] = 1.0;
	ksi[3] = 0.8;

	eta[0] = 0.1;
	eta[1] = 1.0;
	eta[2] = 0.5;
	eta[3] = 0.2;

	for(i=0;i<VER;i++)
	{
		fprintf(CP, "%lf %lf\n", ksi[i], eta[i]);
	}

	//...init u array
	for(i=0;i<N;i++)
	{
		u[i] = (double)i/10.0;
	//	printf("%lf\n", u[i]);		//...check result
	}

	for(n=0;n<N;n++)
	{
		if(n<(N+1)/2)
		{
			sig_x = 0.0;
			sig_y = 0.0;
			for(i=0;i<VER-1;i++)
			{
				sig_x += ksi[i] *  cacu_N_start(ORD, i, u[n]);
				sig_y += eta[i] *  cacu_N_start(ORD, i, u[n]);
			}
			x = sig_x;
			y = sig_y;
			fprintf(test, "%lf %lf\n", x, y);
		//	printf("%lf %lf\n", x, y);	//...check result
		}
		else
		{
			sig_x = 0.0;
			sig_y = 0.0;
			for(i=1;i<VER;i++)
			{
				sig_x += ksi[i] *  cacu_N_end(ORD, i, u[n]);
				sig_y += eta[i] *  cacu_N_end(ORD, i, u[n]);
			}
			x = sig_x;
			y = sig_y;
			fprintf(test, "%lf %lf\n", x, y);
		//	printf("%lf %lf\n", x, y);	//...check result
		}
	}

	return 0;
}

double cacu_N_start(int UPSYBO, int DOWNSYBO, double U)
{
	int temp_ups, temp_downs;
	double temp_u, temp_resl;
	temp_ups=UPSYBO; temp_downs=DOWNSYBO; temp_u=U;
	if(temp_ups==2 && temp_downs==0)
	{
		temp_resl=1.0-2.0*temp_u+pow(temp_u,2);
	}
	else if(temp_ups==2 && temp_downs==1)
	{
		temp_resl=2.0*temp_u-(3.0/2.0)*pow(temp_u,2);
	}
	else if(temp_ups==temp_downs)
	{
		temp_resl=0.5*pow(temp_u,2);
	}
	else
	{
		temp_resl=0.0;
	}
	return temp_resl;
}

double cacu_N_end(int UPSYBO, int DOWNSYBO, double U)
{
	int temp_ups, temp_downs;
	double temp_u, temp_resl;
	temp_ups=UPSYBO; temp_downs=DOWNSYBO; temp_u=U;
	if(temp_ups==2 && temp_downs==0)
	{
		temp_resl=0.0;
	}
	else if(temp_ups==2 && temp_downs==1)
	{
		temp_resl=2.0-2.0*temp_u+0.5*pow(temp_u,2);
	}
	else if(temp_ups==temp_downs)
	{
		temp_resl=-2.0+4.0*temp_u-(3.0/2.0)*pow(temp_u,2);
	}
	else
	{
		temp_resl=1.0-2.0*temp_u+pow(temp_u,2);
	}
	return temp_resl;
}
