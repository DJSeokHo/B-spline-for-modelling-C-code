//************************************************************************
//
//				This program is show an example of Cubic Bezier Curves
//											   ----made by SeokHo
//
//************************************************************************
#include <stdio.h>
#include <math.h>

#define ORD 3
#define N 11

double cacu_N(int, int, double);

main()
{
	FILE *CP=fopen("control polygon.dat","wt");
	FILE *test=fopen("test.dat","wt");
	int i, n;
	double u[N], x, y, sig_x, sig_y;
	double ksi[ORD+1], eta[ORD+1];

	//...init coe
	ksi[0] = 0.1;
	ksi[1] = 0.1;
	ksi[2] = 1.0;
	ksi[3] = 0.8;

	eta[0] = 0.1;
	eta[1] = 1.0;
	eta[2] = 0.5;
	eta[3] = 0.2;

	for(i=0;i<=ORD;i++)
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
		sig_x = 0.0;
		sig_y = 0.0;
		for(i=0;i<=ORD;i++)
		{
			sig_x += ksi[i] *  cacu_N(ORD, i, u[n]);
			sig_y += eta[i] *  cacu_N(ORD, i, u[n]);
		}
		x = sig_x;
		y = sig_y;
		fprintf(test, "%lf %lf\n", x, y);
	}


	return 0;
}

double cacu_N(int UPSYBO, int DOWNSYBO, double U)
{
	int Factorial(int);
	int temp_ups, temp_downs;
	double temp_u, temp_resl;
	temp_ups=UPSYBO; temp_downs=DOWNSYBO; temp_u=U;
	temp_resl = (double)Factorial(temp_ups)/((double)Factorial(temp_downs)*(double)Factorial(temp_ups-temp_downs))
		*pow(temp_u,temp_downs)*pow((1.0-temp_u),(temp_ups-temp_downs));
	return temp_resl;
}

int Factorial(int f)
{
	int Prod=1, temp_f, Fi;
	temp_f=f;	
	if(0!=temp_f)
	{
		for(Fi=1;Fi<=temp_f;Fi++)
		{
			Prod *= Fi;
		}
	}
	return Prod;
}