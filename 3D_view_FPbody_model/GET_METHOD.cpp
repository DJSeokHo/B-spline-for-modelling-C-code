// GET_METHOD.cpp: implementation of the GET_METHOD class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3D_view_FPbody_model.h"
#include "GET_METHOD.h"

#define PI 3.1415926535

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GET_METHOD::GET_METHOD()
{

}

GET_METHOD::~GET_METHOD()
{

}

double GET_METHOD::ang_to_rad(double ANG)
{
	return(ANG*PI)/180;
}

double GET_METHOD::cacu_BP_sn(double sn_1, double xn, double xn_1, double yn, double yn_1)
{
	return (sn_1+sqrt(pow((xn-xn_1),2)+pow((yn-yn_1),2)));
}

double GET_METHOD::cacu_BP_un(double sNv_1, double sn, int od, int bp)
{
	return (((double)(bp-od)/sNv_1)*sn);
}

double GET_METHOD::cacu_Nki(double u, double ui, double Nk_1i, double ui_k, double Nk_1i_1, double ui_k_1, double ui_1)
{
	double temp_left, temp_right;
	if(((u-ui)*Nk_1i)==0 || (ui_k-ui)==0)
	{
		temp_left=0.0;
	}
	else
	{
		temp_left=((u-ui)*Nk_1i)/(ui_k-ui);
	}
	
	if(((ui_k_1-u)*Nk_1i_1)==0 || (ui_k_1-ui_1)==0)
	{
		temp_right=0.0;
	}
	else
	{
		temp_right=((ui_k_1-u)*Nk_1i_1)/(ui_k_1-ui_1);
	}		
	return temp_left+temp_right;
}

double GET_METHOD::cacu_Nki_dev(int tk, double ui, double Nk_1i, double ui_k, double Nk_1i_1, double ui_k_1, double ui_1)
{
	double temp_left, temp_right;
	if(tk==0 || (ui_k-ui)==0)
	{
		temp_left=0.0;
	}
	else
	{
		temp_left=tk*(Nk_1i)/(ui_k-ui);
	}
	
	if(tk==0 || (ui_k_1-ui_1)==0)
	{
		temp_right=0.0;
	}
	else
	{
		temp_right=tk*(Nk_1i_1)/(ui_k_1-ui_1);
	}		
	return temp_left-temp_right;
}

double GET_METHOD::cacu_nx(double xu, double yu)
{
	return (-yu)/(sqrt(pow(yu,2)+pow(xu,2)));
}

double GET_METHOD::cacu_ny(double xu, double yu)
{
	return (xu)/(sqrt(pow(yu,2)+pow(xu,2)));
}

double GET_METHOD::cacu_kslope(double xu, double yu, double xuu, double yuu)
{
	double temp_up, temp_down;
	temp_up=(yuu*xu)-(xuu*yu);
	temp_down=pow((pow(xu,2)+pow(yu,2)),1.5);
	return temp_up/temp_down;
}

void GET_METHOD::matrix_inversion_using_elementary_operation(double **original, double **inverse, int dim)
{
int row, column, pivot_column, max_index;
	double max_value, ftemp1, ftemp2, pivot_value;
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

void GET_METHOD::create_Uni_Knot_Ver(int *u_num, int n, int p, double *knot, int verarr)
{
	int temp_m, temp_n, temp_p, i, j, cot;
	double maxknotvalue;
	temp_n=n; temp_p=p;
	temp_m=temp_n+temp_p+1;
	maxknotvalue=(double)(temp_m-2*(temp_p+1)+1);	
	for(cot=0;cot<verarr;cot++)
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
}

int GET_METHOD::FindSpan(int n, int p, double u, double *U)
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



