//************************************************************************
//
//				This program is show how to use Newton difference
//				method to calculate an example.
//											   ----made by SeokHo
//
//************************************************************************


#include <stdio.h>
#include <math.h>

#define N 5
#define IT 400
main()
{
	FILE *test=fopen("test.dat","wt");
	FILE *basep=fopen("basep.dat","wt");
	double basey[N], d[N][N], basex[N], t[N], x[IT]={0,}, y[IT]={0,}, a[N], b[N];
	int i, j, n;
	double item[N], X, Y;

	//..init	In this example, we calculate ln(x) function while x = 6.0
/*
	basex[0] = 0.0; 
	basex[1] = 8.0;
	basex[2] = 19.0;
	basex[3] = 18.0;
	basex[4] = 27.0;
	basex[5] = 19.0;
	basex[6] = 2.0;

	basey[0] = 0.0;
	basey[1] = 3.0;
	basey[2] = 12.0;
	basey[3] = 32.0;
	basey[4] = 45.0;
	basey[5] = 48.0;
	basey[6] = 46.0;
*/

	basex[0] = 0.0; 
	basex[1] = 1.0;
	basex[2] = 1.0;
	basex[3] = 0.0;
	basex[4] = 0.0;

	basey[0] = 0.0;
	basey[1] = 0.0;
	basey[2] = 1.0;
	basey[3] = 1.0;
	basey[4] = 0.0;

	for(n=0;n<N;n++)
	{
		fprintf(basep, "%lf %lf\n", basex[n], basey[n]);
	}

	for(n=0;n<N;n++)	//...Here mean's we know t0, we get t for n=1,...N-1
	{
		if(n==0)
		{
			t[n] = 0.0;
		}
		else
		{
			t[n] = sqrt(pow((basex[n] - basex[n-1]), 2) + pow((basey[n] - basey[n-1]), 2)) + t[n-1];
		}
	//	printf("%lf\n", t[n]);			//...check result
	}

//...calculate coe a  ***********************************************
	for(i=0;i<N;i++)
	{
		d[i][0] = basex[i];				//...dependent variable is x
	}
	for(j=1;j<N;j++)
	{
		for(i=0;i<N-j;i++)
		{
			d[i][j] = (d[i+1][j-1] - d[i][j-1]) / (t[i+j] - t[i]);		//...independent variable is t
		}
	}
	for(i=0;i<N;i++)
	{
		a[i] = d[0][i];
	//	printf("%7.4f\n", a[i]);	//...check result
	}
	for(n=0;n<IT;n++)
	{
		X = (double)n/100;//!!!!!!!!!!!!!!!!!!!!...here is important about the value
		Y = 0.0;
		for(i=0;i<N;i++)
		{
			item[i] = 1.0;
		}
		for(i=1;i<N;i++)
		{
			for(j=0;j<i;j++)
			{
				item[i] *= (X - t[j]);
			}
			
			item[i] = item[i] * a[i];		
			Y += item[i];
		}
		Y += a[0];
		x[n] = Y;
	//	printf("%lf\n", x[n]);
	}

//...calculate coe b  ***********************************************
	for(i=0;i<N;i++)
	{
		d[i][0] = basey[i];				//...dependent variable is y
	}
	for(j=1;j<N;j++)
	{
		for(i=0;i<N-j;i++)
		{
			d[i][j] = (d[i+1][j-1] - d[i][j-1]) / (t[i+j] - t[i]);		//...independent variable is t
		}
	}
	for(i=0;i<N;i++)
	{
		b[i] = d[0][i];
	//	printf("%7.4f\n", b[i]);	//...check result
	}
	for(n=0;n<IT;n++)
	{
		X = (double)n/100;//!!!!!!!!!!!!!!!!!!!!...here is important about the value
		Y = 0.0;
		for(i=0;i<N;i++)
		{
			item[i] = 1.0;
		}
		for(i=1;i<N;i++)
		{
			for(j=0;j<i;j++)
			{
				item[i] *= (X - t[j]);
			}
			
			item[i] = item[i] * b[i];		
			Y += item[i];
		}
		Y += b[0];
		y[n] = Y;
	//	printf("%lf\n", y[n]);
		fprintf(test, "%lf %lf\n", x[n], y[n]);
	}

	return 0;		//...end
}