#include <stdio.h>
#include <math.h>

#define rad 0.3
#define PI 3.1415926535

#define Num_u 11					//...umax
#define Num_v 11						//...vmax
#define ORD_i 3					//...i
#define ORD_j 3					//...j
#define VER_i 4					//...Number of i Vertices
#define VER_j 4				//...Number of j Vertices
#define VER_ARR_i VER_i+ORD_i+1		//...Number of parameter u
#define VER_ARR_j VER_j+ORD_j+1		//...Number of parameter v
#define BP_i 4						//...i
#define BP_j 4						//...j

void create_Uni_Vnj_Knot_Ver(int n, int p, double *knot);

double cacu_Nki(double, double, double, double, double, double, double);
double cacu_Nki_dev(int tk, double ui, double Nk_i_p_1, double ui_k, double Nk_i_1_p_1, double ui_k_1, double ui_1);
double cacu_nx(double, double);
double cacu_ny(double, double);
double cacu_kslope(double, double, double, double);
double ang_to_rad(double);
double cacu_BP_sn_uv(double, double, double, double, double, double, double);
double cacu_BP_un(double, double);
double cacu_BP_vn(double, double);

void matrix_inversion_using_elementary_operation(double original[BP_i][BP_j], double inverse[BP_i][BP_j], int dim);	

void Show_BaseP_Net(double BN_x[BP_i][BP_j], double BN_y[BP_i][BP_j], double BN_z[BP_i][BP_j]);
void Show_Contr_Net(double CN_x[VER_i][VER_j], double CN_y[VER_i][VER_j], double CN_z[VER_i][VER_j]);
void Show_surface(double sf_x[Num_u][Num_v], double sf_y[Num_u][Num_v], double sf_z[Num_u][Num_v]);

main()
{
	////////////////////////////////////////////////////// files
	FILE *Bspline=fopen("Bspline.dat","wt");
	FILE *Bsplinedev1=fopen("Bsplinedev1.dat","wt");
	FILE *Bsplinedev2=fopen("Bsplinedev2.dat","wt");
	FILE *CP=fopen("CP.dat","wt");
	FILE *CPdev1=fopen("CPdev1.dat","wt");
	FILE *CPdev2=fopen("CPdev2.dat","wt");
	FILE *uN=fopen("uN.dat","wt");
	FILE *uNdev1=fopen("uNdev1.dat","wt");
	FILE *uNdev2=fopen("uNdev2.dat","wt");
	FILE *uNBP=fopen("uNBP.dat","wt");
//	FILE *test=fopen("test.dat","wt");
	FILE *test_u=fopen("testu.dat","wt");
	FILE *test_v=fopen("testv.dat","wt");
	FILE *nxy=fopen("nxy.dat","wt");
	FILE *Bsplinenxny=fopen("Bsplinenxny.dat","wt");
	FILE *Kslope=fopen("Kslope.dat","wt");
	FILE *sig_u=fopen("sig_u","wt");
	FILE *sig_v=fopen("sig_v","wt");

	/////////////////////////////////////////////////////// index
	int i, j, p, q, n_i, n_j, cout_i, cout_j, cot, cot_u, cot_VER, ti, tj;
	
	/////////////////////////////////////////////////////// vertex
	double ContrNet_ij_ksi[VER_i][VER_j], ContrNet_ij_eta[VER_i][VER_j], ContrNet_ij_zeta[VER_i][VER_j];
	

	/////////////////////////////////////////////////////// base points
	double BasePNet_ij_ksi[BP_i][BP_j], BasePNet_ij_eta[BP_i][BP_j], BasePNet_ij_zeta[BP_i][BP_j];
	
	/////////////////////////////////////////////////////// sn and u,v for basis points
	double BP_sn_u[BP_i][BP_j], BP_sn_v[BP_i][BP_j], BP_un[BP_i][BP_j], BP_vn[BP_i][BP_j], BP_u[BP_i*BP_j], BP_v[BP_i*BP_j];

	/////////////////////////////////////////////////////// vector U V
	double U_temp[VER_ARR_i], V_temp[VER_ARR_j], U[VER_ARR_i], V[VER_ARR_j];
	
	/////////////////////////////////////////////////////// vector index
	double u[Num_u], v[Num_v];

	/////////////////////////////////////////////////////// basis function
	double N_u[ORD_i+1][VER_i], N_v[ORD_j+1][VER_j], N_sig_u[Num_u][VER_i], N_sig_v[Num_v][VER_j];
	double BP_N_u[ORD_i+1][BP_i], BP_N_v[ORD_j+1][BP_j];

	double temp_BP_N_u[BP_i][BP_j], temp_BP_N_v[BP_j][BP_i];
	double inv_temp_BP_N_u[BP_i][BP_j], inv_temp_BP_N_v[BP_j][BP_i];

	/////////////////////////////////////////////////////// result x y z
	double temp_x, temp_y, temp_z, x[Num_u][Num_v], y[Num_u][Num_v], z[Num_u][Num_v];
	double t_x[4], t_y[4], t_z[4];
	

	//...init BP Net
	BasePNet_ij_ksi[0][0] = 0.0; BasePNet_ij_eta[0][0] = 0.0; BasePNet_ij_zeta[0][0] = 0.5;
	BasePNet_ij_ksi[0][1] = 1.0; BasePNet_ij_eta[0][1] = 0.0; BasePNet_ij_zeta[0][1] = 0.0;
	BasePNet_ij_ksi[0][2] = 2.0; BasePNet_ij_eta[0][2] = 0.0; BasePNet_ij_zeta[0][2] = 0.0;
	BasePNet_ij_ksi[0][3] = 3.0; BasePNet_ij_eta[0][3] = 0.0; BasePNet_ij_zeta[0][3] = 0.5;

	BasePNet_ij_ksi[1][0] = 0.3; BasePNet_ij_eta[1][0] = 1.0; BasePNet_ij_zeta[1][0] = 0.5;
	BasePNet_ij_ksi[1][1] = 1.3; BasePNet_ij_eta[1][1] = 1.5; BasePNet_ij_zeta[1][1] = 0.0;
	BasePNet_ij_ksi[1][2] = 2.3; BasePNet_ij_eta[1][2] = 1.5; BasePNet_ij_zeta[1][2] = 0.0;
	BasePNet_ij_ksi[1][3] = 3.4; BasePNet_ij_eta[1][3] = 1.0; BasePNet_ij_zeta[1][3] = 0.5;

	BasePNet_ij_ksi[2][0] = 0.0; BasePNet_ij_eta[2][0] = 2.0; BasePNet_ij_zeta[2][0] = 1.0;
	BasePNet_ij_ksi[2][1] = 1.0; BasePNet_ij_eta[2][1] = 2.4; BasePNet_ij_zeta[2][1] = 0.5;
	BasePNet_ij_ksi[2][2] = 2.0; BasePNet_ij_eta[2][2] = 2.4; BasePNet_ij_zeta[2][2] = 0.5;
	BasePNet_ij_ksi[2][3] = 3.0; BasePNet_ij_eta[2][3] = 2.0; BasePNet_ij_zeta[2][3] = 1.0;

	BasePNet_ij_ksi[3][0] = 0.5; BasePNet_ij_eta[3][0] = 2.5; BasePNet_ij_zeta[3][0] = 1.5;
	BasePNet_ij_ksi[3][1] = 1.3; BasePNet_ij_eta[3][1] = 3.0; BasePNet_ij_zeta[3][1] = 1.0;
	BasePNet_ij_ksi[3][2] = 2.4; BasePNet_ij_eta[3][2] = 3.0; BasePNet_ij_zeta[3][2] = 1.0;
	BasePNet_ij_ksi[3][3] = 3.3; BasePNet_ij_eta[3][3] = 2.5; BasePNet_ij_zeta[3][3] = 1.5;	
	
	//...show BP Net
	Show_BaseP_Net(BasePNet_ij_ksi, BasePNet_ij_eta, BasePNet_ij_zeta);


	//...calculate u for basis point
	for(i=0;i<BP_i;i++)
	{
		for(j=0;j<BP_j;j++)
		{
			if(j==0)
			{
				BP_sn_u[i][0] = 0.0;
			}
			else
			{
				BP_sn_u[i][j] = cacu_BP_sn_uv(BP_sn_u[i][j-1], BasePNet_ij_ksi[i][j], BasePNet_ij_ksi[i][j-1], BasePNet_ij_eta[i][j], BasePNet_ij_eta[i][j-1], BasePNet_ij_zeta[i][j], BasePNet_ij_zeta[i][j-1]);
			}
		}
	}

	for(j=0;j<BP_j;j++)
	{
		for(i=0;i<BP_i;i++)
		{
			if(i==0)
			{
				BP_sn_v[j][0] = 0.0;
			}
			else
			{
				BP_sn_v[j][i] = cacu_BP_sn_uv(BP_sn_v[j][i-1], BasePNet_ij_ksi[i][j], BasePNet_ij_ksi[i-1][j], BasePNet_ij_eta[i][j], BasePNet_ij_eta[i-1][j], BasePNet_ij_zeta[i][j], BasePNet_ij_zeta[i-1][j]);
			}
		}
	}
	



	//...calculate the u
	for(i=0;i<BP_i;i++)
	{
		for(j=0;j<BP_j;j++)
		{
			BP_un[i][j] = cacu_BP_un(BP_sn_u[i][BP_j-1], BP_sn_u[i][j]);	
		}
	}
	//...create temp U knot
	create_Uni_Vnj_Knot_Ver(VER_i, ORD_i, U_temp);


	//...calculate the v
	for(j=0;j<BP_j;j++)
	{
		for(i=0;i<BP_i;i++)
		{
			BP_vn[j][i] = cacu_BP_vn(BP_sn_v[j][BP_i-1], BP_sn_v[j][i]);			
		}
	}
	//...create temp V knot
	create_Uni_Vnj_Knot_Ver(VER_j, ORD_j, V_temp);

	
	//...calculate basis function for temp Nu & temp Nv
	//...start from Nu
	for(cout_i=0;cout_i<4;cout_i++)			//first row
	{
	//	fprintf(test_u, "zone t=\"u\"\n");
		for(cout_j=0;cout_j<VER_j;cout_j++) //4 points in first row
		{
			for(n_j=0;n_j<BP_j;n_j++)		
			{
				for(p=0;p<=ORD_i;p++)
				{	
					for(j=0;j<VER_j;j++)
					{	
						if(p==0)
						{
							if(BP_un[cout_i][n_j]>=U_temp[j] && BP_un[cout_i][n_j]<U_temp[j+1])
							{
								BP_N_u[p][j] = 1.0;
							}
							else
							{
								BP_N_u[p][j] = 0.0;
							}
						}
						else if(p==ORD_i&&n_j==BP_j-1&&j==VER_j-1)
						{
							BP_N_u[p][j] = 1.0;				
						}
						else
						{
							BP_N_u[p][j] = cacu_Nki(BP_un[cout_i][n_j], U_temp[j], BP_N_u[p-1][j], U_temp[j+p], BP_N_u[p-1][j+1], U_temp[j+p+1], U_temp[j+1]);
						}
					}
					if(p==ORD_j)
					{				
						temp_BP_N_u[n_j][cout_j] = BP_N_u[ORD_i][cout_j];
					//	fprintf(test_u, "%lf\n", BP_N_u[ORD_i][cout_j]);
					}
				}
			}
		}

		matrix_inversion_using_elementary_operation(temp_BP_N_u,inv_temp_BP_N_u,BP_i);	

		for(cout_j=0;cout_j<BP_j;cout_j++)
		{
			ContrNet_ij_ksi[cout_i][cout_j] = 0.0;
			ContrNet_ij_eta[cout_i][cout_j] = 0.0;
			ContrNet_ij_zeta[cout_i][cout_j] = 0.0;
			
			for(j=0;j<BP_j;j++)
			{
				ContrNet_ij_ksi[cout_i][cout_j] += inv_temp_BP_N_u[cout_j][j] * BasePNet_ij_ksi[cout_i][j];
				ContrNet_ij_eta[cout_i][cout_j] += inv_temp_BP_N_u[cout_j][j] * BasePNet_ij_eta[cout_i][j];
				ContrNet_ij_zeta[cout_i][cout_j] += inv_temp_BP_N_u[cout_j][j] * BasePNet_ij_zeta[cout_i][j];
			}			
		}
	
		for(cout_j=0;cout_j<BP_j;cout_j++)
		{
		//	fprintf(test_u, "%lf %lf %lf\n", ContrNet_ij_ksi[cout_i][cout_j], ContrNet_ij_eta[cout_i][cout_j], ContrNet_ij_zeta[cout_i][cout_j]);
		}

	}
	
	for(cout_i=0;cout_i<BP_i;cout_i++)
	{
		fprintf(test_u, "zone t=\"u\"\n");
		for(cout_j=0;cout_j<BP_j;cout_j++)
		{
			fprintf(test_u, "%lf %lf %lf\n", ContrNet_ij_ksi[cout_i][cout_j], ContrNet_ij_eta[cout_i][cout_j], ContrNet_ij_zeta[cout_i][cout_j]);
		}
	}




	//...Nv
	
	for(cot=0;cot<BP_j;cot++)
	{
	//	fprintf(test_v, "zone t=\"u\"\n");
		for(cout_j=0;cout_j<VER_j;cout_j++) //4 points in first row
		{
		//	fprintf(test_v, "zone t=\"v\"\n");
			for(n_j=0;n_j<BP_j;n_j++)		
			{
		//		fprintf(test_v, "%lf ", BP_vn[0][n_j]);
				for(p=0;p<=ORD_i;p++)
				{	
					for(j=0;j<VER_j;j++)
					{	
						if(p==0)
						{
							if(BP_vn[cot][n_j]>=V_temp[j] && BP_vn[cot][n_j]<V_temp[j+1])
							{
								BP_N_v[p][j] = 1.0;
							}
							else
							{
								BP_N_v[p][j] = 0.0;
							}
						}
						else if(p==ORD_i&&n_j==BP_j-1&&j==VER_j-1)
						{
							BP_N_v[p][j] = 1.0;				
						}
						else
						{
							BP_N_v[p][j] = cacu_Nki(BP_vn[cot][n_j], V_temp[j], BP_N_v[p-1][j], V_temp[j+p], BP_N_v[p-1][j+1], V_temp[j+p+1], V_temp[j+1]);
						}
					}
					if(p==ORD_j)
					{				
						temp_BP_N_v[n_j][cout_j] = BP_N_v[ORD_i][cout_j];
				//		fprintf(test_v, "%lf\n", BP_N_v[ORD_i][cout_j]);
					}
				}
			}
		}

		matrix_inversion_using_elementary_operation(temp_BP_N_v,inv_temp_BP_N_v,BP_i);	

		fprintf(test_v, "zone t=\"v\"\n");
		for(cout_j=0;cout_j<BP_j;cout_j++)
		{
			temp_x = 0.0;
			temp_y = 0.0;
			temp_z = 0.0;
			
			for(j=0;j<BP_j;j++)
			{
				temp_x += inv_temp_BP_N_v[cout_j][j] * ContrNet_ij_ksi[j][cot];
				temp_y += inv_temp_BP_N_v[cout_j][j] * ContrNet_ij_eta[j][cot];
				temp_z += inv_temp_BP_N_v[cout_j][j] * ContrNet_ij_zeta[j][cot];
			}	
			t_x[cout_j] = temp_x;
			t_y[cout_j] = temp_y;
			t_z[cout_j] = temp_z;
			fprintf(test_v, "%lf %lf %lf\n", t_x[cout_j], t_y[cout_j], t_z[cout_j]);
		}
	}

	return 0;
}

void Show_BaseP_Net(double BN_x[BP_i][BP_j], double BN_y[BP_i][BP_j], double BN_z[BP_i][BP_j])
{
	FILE *BN=fopen("BPxy.dat","wt");
	int i, j;
	for(i=0;i<BP_i;i++)
	{
		fprintf(BN, "zone t=\"BN\"\n");
		for(j=0;j<BP_j;j++)
		{
			fprintf(BN, "%lf  ", BN_x[i][j]);
			fprintf(BN, "%lf  ", BN_y[i][j]);
			fprintf(BN, "%lf\n", BN_z[i][j]);
		}
	}
	for(j=0;j<BP_j;j++)
	{
		fprintf(BN, "zone t=\"BN\"\n");
		for(i=0;i<BP_i;i++)
		{
			fprintf(BN, "%lf  ", BN_x[i][j]);
			fprintf(BN, "%lf  ", BN_y[i][j]);
			fprintf(BN, "%lf\n", BN_z[i][j]);
		}
	}
}

void Show_surface(double sf_x[Num_u][Num_v], double sf_y[Num_u][Num_v], double sf_z[Num_u][Num_v])
{
	FILE *test=fopen("test.dat","wt");
	int i, j;
	for(i=0;i<4;i++)
	{
		fprintf(test, "zone t=\"test\"\n");
		for(j=0;j<4;j++)
		{
			fprintf(test, "%lf  ", sf_x[i][j]);
			fprintf(test, "%lf  ", sf_y[i][j]);
			fprintf(test, "%lf\n", sf_z[i][j]);
		}
	}
	for(i=0;i<4;i++)
	{
		fprintf(test, "zone t=\"test\"\n");
		for(j=0;j<4;j++)
		{
			fprintf(test, "%lf  ", sf_x[j][i]);
			fprintf(test, "%lf  ", sf_y[j][i]);
			fprintf(test, "%lf\n", sf_z[j][i]);
		}
	}
}

double cacu_BP_sn_uv(double sn_1, double xn, double xn_1, double yn, double yn_1, double zn, double zn_1)
{
	double temp_sn_1, temp_xn, temp_xn_1, temp_yn, temp_yn_1, temp_zn, temp_zn_1, temp_resl;
	temp_sn_1=sn_1; temp_xn=xn; temp_xn_1=xn_1; temp_yn=yn; temp_yn_1=yn_1; temp_zn=zn; temp_zn_1=zn_1;
	temp_resl=temp_sn_1+sqrt(pow((temp_xn-temp_xn_1),2)+pow((temp_yn-temp_yn_1),2)+pow((temp_zn-temp_zn_1),2));
	return temp_resl;
}

double cacu_BP_un(double sNv_1, double sn)
{
	double temp_sNv_1, temp_sn, temp_resl;
	temp_sNv_1=sNv_1; temp_sn=sn;
	temp_resl=(((double)BP_i-(double)ORD_i)/temp_sNv_1)*temp_sn;
	return temp_resl;
}

double cacu_BP_vn(double sNv_1, double sn)
{
	double temp_sNv_1, temp_sn, temp_resl;
	temp_sNv_1=sNv_1; temp_sn=sn;
	temp_resl=((double)(BP_j-ORD_j)/temp_sNv_1)*temp_sn;
	return temp_resl;
}

void create_Uni_Vnj_Knot_Ver(int n, int p, double *noda)
{
	int temp_m, temp_n, temp_p, temp_i, temp_j, temp_cot;
	double temp_maxnodavalue;
	temp_n=n; temp_p=p;
	temp_m=temp_n+temp_p+1;
	temp_maxnodavalue=(double)(temp_m-2*(temp_p+1)+1);	
	for(temp_cot=0;temp_cot<temp_n;temp_cot++)
	{
		noda[temp_cot]=0.0;
	}
	for(temp_j=0;temp_j<=temp_p;temp_j++) 
	{
		noda[temp_j]=0.0;
		noda[temp_m-temp_j]=temp_maxnodavalue;
	}
	for(temp_j=temp_p+1,temp_i=1;temp_j<=temp_n;temp_j++) 
	{
		noda[temp_j]=(double)temp_i++;
	}
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

void matrix_inversion_using_elementary_operation(double original[BP_i][BP_j], double inverse[BP_i][BP_j], int dim)
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

