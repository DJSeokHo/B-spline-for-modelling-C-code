//************************************************************************
//
//				This program is show how to using Lagrance insert
//				method to calculate an example of polynomial in 3 
//				base point.
//											   ----made by SeokHo
//
//************************************************************************
#include <stdio.h>

#define N 10		//...number of base point

main()
{
	FILE *test = fopen("test.dat","wt");

	int i, j, p;
	double Li[N], x, y, xj[N], fz[N], fm[N];
	double speclcase=0.0;
	double xi[N] = {0.10,0.15,0.30,0.40,0.50,0.60,0.70,0.85,0.90,1.00};
	double yi[N] = {0.90,0.86,0.78,0.67,0.60,0.55,0.48,0.42,0.38,0.36};

	for(i=0;i<N;i++)
	{
		fz[i] = 1.0;	//Numerator
		fm[i] = 1.0;	//denominator
	}

	for(p=0;p<1000;p++)
	{
		x = (double)p/1000;
		y = 0.0;
		speclcase = 0.0;
		for(i=0;i<N;i++)
		{
			fz[i] = 1.0;
			fm[i] = 1.0;
		}
		//...Calculate Lagrance result polynomials Li
		for(i=0;i<N;i++)
		{
			for(j=0;j<=N-1;j++)
			{
				if(i!=j)
				{
					fz[i] *= (x - xi[j]);
					fm[i] *= (xi[i] - xi[j]);
					Li[i] = fz[i] / fm[i];
				}
			}
		//	printf("%d  %lf\n", i+1, Li[i]);	//..check value
			y += yi[i] * Li[i];					//..y is result
			speclcase += Li[i];					//..special case
		}
		printf("%lf  %0.2f\n", y, speclcase);	//..check value
		fprintf(test, "%lf %lf\n", x, y);
	}
	return 0;
}
