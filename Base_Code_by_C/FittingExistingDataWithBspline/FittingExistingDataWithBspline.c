#include <stdio.h>
#include <math.h>

#define VER 7
#define IT 400
#define PI 3.1415926535
#define ORD 3

double ang_to_rad(double);                        //trans degree to radian
double cacu_Nki(double, double, double, double, double, double, double);
void matrix_inversion_using_elementary_operation( float original[VER][VER], float inverse[VER][VER], int dim );	//coe

main()
{
	FILE *BP=fopen("BP.dat","wt");
	
	int i, j, n, k;
	double basex[VER], basey[VER];
	double u[VER], s[VER];
	double ksi[VER], eta[VER], N[VER][VER];

	for(i=0;i<VER;i++)
	{
		basex[i] = (PI / (VER - 1)) / PI * 180 * (double)i;
	}

	for(i=0;i<VER;i++)
	{
		basey[i] = sin(ang_to_rad(basex[i]));
		fprintf(BP, "%lf %lf\n", basex[i], basey[i]);
	//	printf("%lf %lf\n", basex[i], basey[i]);
	}
	
	for(n=0;n<VER;n++)	//...Here mean's we know s0, we get t for n=1,...N-1
	{
		if(n==0)
		{
			s[n] = 0.0;		//...s means poly-arc
		}
		else
		{
			s[n] = sqrt(pow((basex[n] - basex[n-1]), 2) + pow((basey[n] - basey[n-1]), 2)) + s[n-1];	//...s means poly-arc
		}
	//	printf("%lf\n", s[n]);			//...check result
	}

	for(n=0;n<VER;n++)	//...Here mean's we know t0, we get t for n=1,...N-1
	{
		u[n] = (VER - ORD) / (s[VER - 1]) * s[n];
	//	printf("%lf\n", u[n]);			//...check result
	}
	
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
		if(k==ORD)
		{
			fprintf(test, "%lf\n", N[ORD][cout]);
			N_sig[n][cout] = N[ORD][cout];
		}

	}
	
	

	return 0;
}

double ang_to_rad(double ANG)
{
	double temp_rad, temp_ang;
	temp_ang=ANG;
	temp_rad=(temp_ang*PI)/180;
	return temp_rad;
}

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

void matrix_inversion_using_elementary_operation( float original[VER][VER], float inverse[VER][VER], int dim )
{
	int row, column, pivot_column, max_index;
	float max_value, ftemp1, ftemp2, pivot_value;
	for( row = 0; row < dim; row++ )
		for( column = 0; column < dim; column++ ){
			if( row == column )
				inverse[row][column] = 1;
			else
				inverse[row][column] = 0;
		}
		for( pivot_column = 0; pivot_column < dim; pivot_column++ ){
			max_index = original[0][column];
			max_value = 0;
			for( row = pivot_column; row < dim; row++ )
				if( original[row][pivot_column]*original[row][pivot_column] > max_value*max_value ){
					max_index = row;
					max_value = original[row][pivot_column];
				}
				if(pivot_column != max_index )
					for( column = 0; column < dim; column++ ){
						ftemp1 = original[pivot_column][column];
						ftemp2 = inverse[pivot_column][column];
						original[pivot_column][column] = original[max_index][column];
						inverse[pivot_column][column] = inverse[max_index][column];
						original[max_index][column] = ftemp1;
						inverse[max_index][column] = ftemp2;
					}
					pivot_value = original[pivot_column][pivot_column];
					for(column = 0; column < dim; column++ ){
						original[pivot_column][column] /= pivot_value;
						inverse[pivot_column][column] /= pivot_value;
					}
					for( row = 0; row < dim; row++ )
						if( row != pivot_column ){
							ftemp1 = original[row][pivot_column];
							for( column = 0; column < dim; column++ ){
								original[row][column] -= ftemp1*original[pivot_column][column];
								inverse[row][column] -= ftemp1*inverse[pivot_column][column];
							}
						}
		}
}