#include <stdio.h>
#include <math.h>

#define rad 0.3
#define PI 3.1415926535

#define Num_c 21					//...vmax
#define Num_r 11					//...umax

#define ORD_u 5					//...i
#define ORD_v 3					//...j

#define fcol 7
#define frow 4


#define VER_ARR_u fcol+ORD_u+1		//...Number of parameter u
#define VER_ARR_v frow+ORD_v+1		//...Number of parameter v

void create_Uni_Vnj_Knot_Ver(int n, int p, double *knot);

double cacu_Nki(double, double, double, double, double, double, double);
double cacu_Nki_dev(int tk, double ui, double Nk_i_p_1, double ui_k, double Nk_i_1_p_1, double ui_k_1, double ui_1);
double cacu_n_P(double, double, double, double);
double cacu_kslope(double, double, double, double);
double ang_to_rad(double);
double cacu_BP_sn_uv(double, double, double, double, double, double, double);
double cacu_BP_un(double, double);
double cacu_BP_vn(double, double);

void matrix_inversion_using_elementary_operation_u(double original[frow][fcol], double inverse[frow][fcol], int dim);	
void matrix_inversion_using_elementary_operation_v(double original[fcol][frow], double inverse[fcol][frow], int dim);	

void Show_BaseP_Net(double BN_x[frow][fcol], double BN_y[frow][fcol], double BN_z[frow][fcol]);
void Show_Contr_Net(double sf_x[frow][fcol], double sf_y[frow][fcol], double sf_z[frow][fcol]);
void Show_surface(double sf_x[Num_r][Num_c], double sf_y[Num_r][Num_c], double sf_z[Num_r][Num_c]);

main()
{
	////////////////////////////////////////////////////// files
	FILE *CP=fopen("CP.dat","wt");

	FILE *uN=fopen("uN.dat","wt");
	FILE *vN=fopen("vN.dat","wt");

	FILE *uNdev1=fopen("uNdev1.dat","wt");
	FILE *vNdev1=fopen("vNdev1.dat","wt");

	FILE *BP_u=fopen("BP_u.dat","wt");
	FILE *BP_v=fopen("BP_v.dat","wt");

	FILE *Qij_u_1=fopen("Qij_u_1.dat","wt");
	FILE *Qij_v_1=fopen("Qij_v_1.dat","wt");
	
	FILE *P_laod_u=fopen("P_laod_u.dat","wt");
	FILE *P_laod_v=fopen("P_laod_v.dat","wt");

	FILE *n_P=fopen("n_P.dat","wt");

	FILE *Kslope=fopen("Kslope.dat","wt");

	FILE *test=fopen("test.dat","wt");

	/////////////////////////////////////////////////////// index
	int i, j, r, c, p, q, n_r, n_c, cout_r, cout_c, cot, uNt, vNt;
	
	/////////////////////////////////////////////////////// base points
	double BasePNet_ij_ksi[frow][fcol], BasePNet_ij_eta[frow][fcol], BasePNet_ij_zeta[frow][fcol];

	/////////////////////////////////////////////////////// sn and u,v for basis points
	double BP_sn_u[frow][fcol], BP_sn_v[fcol][frow], BP_un[frow][fcol], BP_vn[fcol][frow];

	/////////////////////////////////////////////////////// vector U V
	double U_temp[VER_ARR_u], V_temp[VER_ARR_v], U[VER_ARR_u], V[VER_ARR_v];
	double U_dev[VER_ARR_u-1], V_dev[VER_ARR_v-1];

	/////////////////////////////////////////////////////// basis function
	double BP_N_u[ORD_u+1][fcol], BP_N_v[ORD_v+1][frow], temp_BP_N_u[frow][fcol], temp_BP_N_v[fcol][frow];
	double inv_temp_BP_N_u[frow][fcol], inv_temp_BP_N_v[fcol][frow];

	/////////////////////////////////////////////////////// vertex
	double ContrNet_ij_ksi[frow][fcol], ContrNet_ij_eta[frow][fcol], ContrNet_ij_zeta[frow][fcol];
	double t_x[frow][fcol], t_y[frow][fcol], t_z[frow][fcol];
	double ContrNet_ij_ksi_dev_1_u[frow][fcol-1], ContrNet_ij_eta_dev_1_u[frow][fcol-1], ContrNet_ij_zeta_dev_1_u[frow][fcol-1];
	double ContrNet_ij_ksi_dev_1_v[frow-1][fcol-1], ContrNet_ij_eta_dev_1_v[frow-1][fcol-1], ContrNet_ij_zeta_dev_1_v[frow-1][fcol-1];

	/////////////////////////////////////////////////////// u,v parameter
	double u[Num_c], v[Num_r];

	/////////////////////////////////////////////////////// basis function
	double N_u[ORD_u+1][fcol], N_v[ORD_v+1][frow], N_sig_u[Num_c][fcol], N_sig_v[Num_r][frow];

	/////////////////////////////////////////////////////// result x y z
	double temp_x, temp_y, temp_z;
	double x[Num_r][Num_c], y[Num_r][Num_c], z[Num_r][Num_c];
	double x_dev1_u[Num_r][Num_c], y_dev1_u[Num_r][Num_c], z_dev1_u[Num_r][Num_c];
	double x_dev1_v[Num_c][Num_r], y_dev1_v[Num_c][Num_r], z_dev1_v[Num_c][Num_r];
	
	/////////////////////////////////////////////////////// basis function for derivative
	double N_u_dev1[ORD_u][fcol], N_u_sig_dev_1[Num_c][fcol];
	double N_v_dev1[ORD_v][frow], N_v_sig_dev_1[Num_r][frow];
	double uN_temp_dev1[2], vN_temp_dev1[2];
	double temp_x_dev1_u, temp_y_dev1_u, temp_z_dev1_u;
	double temp_x_dev1_v, temp_y_dev1_v, temp_z_dev1_v;

	/////////////////////////////////////////////////////// result for derivative
	double nx[Num_r][Num_c], ny[Num_r][Num_c], nz[Num_r][Num_c];


	double testx[4][Num_c], testy[4][Num_c], testz[4][Num_c]; 
	double testxl[4][Num_c], testyl[4][Num_c], testzl[4][Num_c]; 
	double testnx[4][Num_c], testny[4][Num_c], testnz[4][Num_c]; 

	//...init BP Net
	BasePNet_ij_ksi[0][0] = -4.005; BasePNet_ij_eta[0][0] = 0.3; BasePNet_ij_zeta[0][0] = -1.1;
	BasePNet_ij_ksi[0][1] = -4.01; BasePNet_ij_eta[0][1] = 0.3005; BasePNet_ij_zeta[0][1] = -1.1005;
	BasePNet_ij_ksi[0][2] = -4.005; BasePNet_ij_eta[0][2] = 0.3; BasePNet_ij_zeta[0][2] = -0.3;
	BasePNet_ij_ksi[0][3] = -4.01; BasePNet_ij_eta[0][3] = 0.3005; BasePNet_ij_zeta[0][3] = 0.0;
	BasePNet_ij_ksi[0][4] = -4.005; BasePNet_ij_eta[0][4] = 0.3; BasePNet_ij_zeta[0][4] = 0.3;
	BasePNet_ij_ksi[0][5] = -4.01; BasePNet_ij_eta[0][5] = 0.3005; BasePNet_ij_zeta[0][5] = 1.1005;
	BasePNet_ij_ksi[0][6] = -4.005; BasePNet_ij_eta[0][6] = 0.3; BasePNet_ij_zeta[0][6] = 1.1;
	
	BasePNet_ij_ksi[1][0] = -4.0; BasePNet_ij_eta[1][0] = 1.0; BasePNet_ij_zeta[1][0] = -1.5;
	BasePNet_ij_ksi[1][1] = -3.5; BasePNet_ij_eta[1][1] = 1.005; BasePNet_ij_zeta[1][1] = -1.4005;
	BasePNet_ij_ksi[1][2] = -0.7; BasePNet_ij_eta[1][2] = 1.3; BasePNet_ij_zeta[1][2] = -1.4;
	BasePNet_ij_ksi[1][3] = -0.0; BasePNet_ij_eta[1][3] = 1.2; BasePNet_ij_zeta[1][3] =  0.0;
	BasePNet_ij_ksi[1][4] = -0.7; BasePNet_ij_eta[1][4] = 1.3; BasePNet_ij_zeta[1][4] =  1.4;
	BasePNet_ij_ksi[1][5] = -3.5; BasePNet_ij_eta[1][5] = 1.005; BasePNet_ij_zeta[1][5] =  1.4005;
	BasePNet_ij_ksi[1][6] = -4.0; BasePNet_ij_eta[1][6] = 1.0; BasePNet_ij_zeta[1][6] =  1.5;

	BasePNet_ij_ksi[2][0] = -4.0; BasePNet_ij_eta[2][0] = 2.0; BasePNet_ij_zeta[2][0] = -1.5;
	BasePNet_ij_ksi[2][1] = -3.5; BasePNet_ij_eta[2][1] = 2.005; BasePNet_ij_zeta[2][1] = -1.5005;
	BasePNet_ij_ksi[2][2] = -1.0; BasePNet_ij_eta[2][2] = 2.0; BasePNet_ij_zeta[2][2] = -1.5;
	BasePNet_ij_ksi[2][3] = -0.0; BasePNet_ij_eta[2][3] = 2.005; BasePNet_ij_zeta[2][3] =  0.0;
	BasePNet_ij_ksi[2][4] = -1.0; BasePNet_ij_eta[2][4] = 2.0; BasePNet_ij_zeta[2][4] =  1.5;
	BasePNet_ij_ksi[2][5] = -3.5; BasePNet_ij_eta[2][5] = 2.005; BasePNet_ij_zeta[2][5] =  1.5005;
	BasePNet_ij_ksi[2][6] = -4.0; BasePNet_ij_eta[2][6] = 2.0; BasePNet_ij_zeta[2][6] =  1.5;

	BasePNet_ij_ksi[3][0] = -4.0; BasePNet_ij_eta[3][0] = 3.0; BasePNet_ij_zeta[3][0] = -2.1;
	BasePNet_ij_ksi[3][1] = -3.5; BasePNet_ij_eta[3][1] = 3.005; BasePNet_ij_zeta[3][1] = -1.9;
	BasePNet_ij_ksi[3][2] = -0.5; BasePNet_ij_eta[3][2] = 3.0; BasePNet_ij_zeta[3][2] = -1.7;
	BasePNet_ij_ksi[3][3] =  1.0; BasePNet_ij_eta[3][3] = 3.005; BasePNet_ij_zeta[3][3] =  0.0;
	BasePNet_ij_ksi[3][4] = -0.5; BasePNet_ij_eta[3][4] = 3.0; BasePNet_ij_zeta[3][4] =  1.7;
	BasePNet_ij_ksi[3][5] = -3.5; BasePNet_ij_eta[3][5] = 3.005; BasePNet_ij_zeta[3][5] =  1.9;
	BasePNet_ij_ksi[3][6] = -4.0; BasePNet_ij_eta[3][6] = 3.0; BasePNet_ij_zeta[3][6] =  2.1;
/*
	BasePNet_ij_ksi[4][0] = -4.4; BasePNet_ij_eta[4][0] = 3.3; BasePNet_ij_zeta[4][0] = -2.3;
	BasePNet_ij_ksi[4][1] = -3.9; BasePNet_ij_eta[4][1] = 3.305; BasePNet_ij_zeta[4][1] = -2.1;
	BasePNet_ij_ksi[4][2] = -0.9; BasePNet_ij_eta[4][2] = 3.3; BasePNet_ij_zeta[4][2] = -2.0;
	BasePNet_ij_ksi[4][3] =  1.4; BasePNet_ij_eta[4][3] = 3.305; BasePNet_ij_zeta[4][3] =  0.3;
	BasePNet_ij_ksi[4][4] = -0.9; BasePNet_ij_eta[4][4] = 3.3; BasePNet_ij_zeta[4][4] =  2.0;
	BasePNet_ij_ksi[4][5] = -3.9; BasePNet_ij_eta[4][5] = 3.305; BasePNet_ij_zeta[4][5] =  2.1;
	BasePNet_ij_ksi[4][6] = -4.4; BasePNet_ij_eta[4][6] = 3.3; BasePNet_ij_zeta[4][6] =  2.3;
*/
	//...show BP Net
	Show_BaseP_Net(BasePNet_ij_ksi, BasePNet_ij_eta, BasePNet_ij_zeta);

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
				BP_sn_u[i][j] = cacu_BP_sn_uv(BP_sn_u[i][j-1], BasePNet_ij_ksi[i][j], BasePNet_ij_ksi[i][j-1], BasePNet_ij_eta[i][j], BasePNet_ij_eta[i][j-1], BasePNet_ij_zeta[i][j], BasePNet_ij_zeta[i][j-1]);
			}
		}
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
				BP_sn_v[j][i] = cacu_BP_sn_uv(BP_sn_v[j][i-1], BasePNet_ij_ksi[i][j], BasePNet_ij_ksi[i-1][j], BasePNet_ij_eta[i][j], BasePNet_ij_eta[i-1][j], BasePNet_ij_zeta[i][j], BasePNet_ij_zeta[i-1][j]);
			}
		}
	}

	//...calculate the u parameter
	for(i=0;i<frow;i++)
	{
		for(j=0;j<fcol;j++)
		{
			BP_un[i][j] = cacu_BP_un(BP_sn_u[i][fcol-1], BP_sn_u[i][j]);	
		}
	}
	//...create temp U knot
	create_Uni_Vnj_Knot_Ver(fcol, ORD_u, U_temp);

	//...calculate the v parameter
	for(j=0;j<fcol;j++)
	{
		for(i=0;i<frow;i++)
		{
			BP_vn[j][i] = cacu_BP_vn(BP_sn_v[j][frow-1], BP_sn_v[j][i]);	
		}
	}
	//...create temp V knot
	create_Uni_Vnj_Knot_Ver(frow, ORD_v, V_temp);

	//...calculate basis function for temp Nu & temp Nv
	//...start from Nu
	for(cout_r=0;cout_r<frow;cout_r++)			//row
	{
		for(cout_c=0;cout_c<fcol;cout_c++)		//col
		{
			fprintf(BP_u, "zone t=\"BP_u\"\n");
			for(n_c=0;n_c<fcol;n_c++)		
			{
				fprintf(BP_u, "%lf ", BP_un[cout_r][n_c]);
				for(p=0;p<=ORD_u;p++)
				{	
					for(c=0;c<fcol;c++)
					{	
						if(p==0)
						{
							if(BP_un[cout_r][n_c]>=U_temp[c] && BP_un[cout_r][n_c]<U_temp[c+1])
							{
								BP_N_u[p][c] = 1.0;
							}
							else
							{
								BP_N_u[p][c] = 0.0;
							}
						}
						else if(p==ORD_u&&n_c==fcol-1&&c==fcol-1)
						{
							BP_N_u[p][c] = 1.0;				
						}
						else
						{
							BP_N_u[p][c] = cacu_Nki(BP_un[cout_r][n_c], U_temp[c], BP_N_u[p-1][c], U_temp[c+p], BP_N_u[p-1][c+1], U_temp[c+p+1], U_temp[c+1]);
						}
					}
					if(p==ORD_u)
					{				
						temp_BP_N_u[n_c][cout_c] = BP_N_u[ORD_u][cout_c];
						fprintf(BP_u, "%lf\n", BP_N_u[ORD_u][cout_c]);
					}
				}
			}
		}

		matrix_inversion_using_elementary_operation_u(temp_BP_N_u,inv_temp_BP_N_u,fcol);	

		for(cout_c=0;cout_c<fcol;cout_c++)
		{
			ContrNet_ij_ksi[cout_r][cout_c] = 0.0;
			ContrNet_ij_eta[cout_r][cout_c] = 0.0;
			ContrNet_ij_zeta[cout_r][cout_c] = 0.0;
			
			for(c=0;c<fcol;c++)
			{
				ContrNet_ij_ksi[cout_r][cout_c] += inv_temp_BP_N_u[cout_c][c] * BasePNet_ij_ksi[cout_r][c];
				ContrNet_ij_eta[cout_r][cout_c] += inv_temp_BP_N_u[cout_c][c] * BasePNet_ij_eta[cout_r][c];
				ContrNet_ij_zeta[cout_r][cout_c] += inv_temp_BP_N_u[cout_c][c] * BasePNet_ij_zeta[cout_r][c];
			}			
		}
	}

	//...Nv
	for(cout_c=0;cout_c<fcol;cout_c++)			//col
	{
		for(cout_r=0;cout_r<frow;cout_r++)		//row
		{
			fprintf(BP_v, "zone t=\"BP_v\"\n");
			for(n_r=0;n_r<frow;n_r++)		
			{
				fprintf(BP_v, "%lf ", BP_vn[cout_c][n_r]);
				for(q=0;q<=ORD_v;q++)
				{	
					for(r=0;r<frow;r++)
					{	
						if(q==0)
						{
							if(BP_vn[cout_c][n_r]>=V_temp[r] && BP_vn[cout_c][n_r]<V_temp[r+1])
							{
								BP_N_v[q][r] = 1.0;
							}
							else
							{
								BP_N_v[q][r] = 0.0;
							}
						}
						else if(q==ORD_v&&n_r==frow-1&&r==frow-1)
						{
							BP_N_v[q][r] = 1.0;				
						}
						else
						{
							BP_N_v[q][r] = cacu_Nki(BP_vn[cout_c][n_r], V_temp[r], BP_N_v[q-1][r], V_temp[r+q], BP_N_v[q-1][r+1], V_temp[r+q+1], V_temp[r+1]);
						}
					}
					if(q==ORD_v)
					{				
						temp_BP_N_v[n_r][cout_r] = BP_N_v[ORD_v][cout_r];
						fprintf(BP_v, "%lf\n", BP_N_v[ORD_v][cout_r]);
					}
				}
			}
		}

		matrix_inversion_using_elementary_operation_v(temp_BP_N_v,inv_temp_BP_N_v,frow);	

		for(cout_r=0;cout_r<frow;cout_r++)
		{
			temp_x = 0.0;
			temp_y = 0.0;
			temp_z = 0.0;
			
			for(r=0;r<frow;r++)
			{
				temp_x += inv_temp_BP_N_v[cout_r][r] * ContrNet_ij_ksi[r][cout_c];
				temp_y += inv_temp_BP_N_v[cout_r][r] * ContrNet_ij_eta[r][cout_c];
				temp_z += inv_temp_BP_N_v[cout_r][r] * ContrNet_ij_zeta[r][cout_c];
			}
			t_x[cout_r][cout_c] = temp_x;
			t_y[cout_r][cout_c] = temp_y;
			t_z[cout_r][cout_c] = temp_z;
		}
	}

	for(i=0;i<frow;i++)
	{
		for(j=0;j<fcol;j++)
		{
			ContrNet_ij_ksi[i][j] = t_x[i][j];
			ContrNet_ij_eta[i][j] = t_y[i][j];
			ContrNet_ij_zeta[i][j] = t_z[i][j];
		}
	}

	Show_Contr_Net(ContrNet_ij_ksi,ContrNet_ij_eta,ContrNet_ij_zeta);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

							//end of the control-net's calculation

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//...U knot
	create_Uni_Vnj_Knot_Ver(fcol, ORD_u, U_temp);
	for(i=0;i<VER_ARR_u;i++)
	{
		U[i] = U_temp[i];
	}

	//...init u parameter
	for(i=0;i<Num_c;i++)
	{
		u[i] = (double)i/10.0;	
	}

	//...calculate basis function for Nu & Nv
	//...start from Nu
	for(cout_c=0;cout_c<fcol;cout_c++)		//col
	{
		fprintf(uN, "zone t=\"uN\"\n");
		fprintf(uNdev1, "zone t=\"uNdev1\"\n");
		for(n_c=0;n_c<Num_c;n_c++)		
		{
			fprintf(uN, "%lf ", u[n_c]);
		//	fprintf(uNdev1, "%lf ", u[n_c]);
			for(p=0;p<=ORD_u;p++)
			{	
				for(c=0;c<fcol;c++)
				{	
					if(p==0)
					{
						if(u[n_c]>=U[c] && u[n_c]<U[c+1])
						{
							N_u[p][c] = 1.0;
						}
						else
						{
							N_u[p][c] = 0.0;
						}
					}
					else if(p==ORD_u&&n_c==Num_c-1&&c==fcol-1)
					{
						N_u[p][c] = 1.0;				
					}
					else
					{
						N_u[p][c] = cacu_Nki(u[n_c], U[c], N_u[p-1][c], U[c+p], N_u[p-1][c+1], U[c+p+1], U[c+1]);
						N_u_dev1[p][c] = cacu_Nki_dev(p, U[c], N_u[p-1][c], U[c+p], N_u[p-1][c+1], U[c+p+1], U[c+1]);
					}
				}
				if(p==ORD_u)
				{	
					if(n_c==0 && cout_c==0)
					{
						for(uNt=0;uNt<2;uNt++)
						{
							uN_temp_dev1[uNt] = N_u_dev1[ORD_u][uNt];
						}
					}
					for(uNt=0;uNt<2;uNt++)
					{
						if(n_c==Num_c-1 && cout_c == fcol - (uNt + 1))
						{
							N_u_dev1[ORD_u][fcol - (uNt + 1)] = uN_temp_dev1[1 - uNt];
						}
					}
					
					fprintf(uN, "%lf\n", N_u[ORD_u][cout_c]);
					fprintf(uNdev1, "%lf\n", N_u_dev1[ORD_u][cout_c]);

					N_sig_u[n_c][cout_c] = N_u[ORD_u][cout_c];
					N_u_sig_dev_1[n_c][cout_c] = N_u[ORD_u-1][cout_c+1];		//dev 1 importent,this is right
				}
			}
		}
	}

	for(n_r=0;n_r<frow;n_r++)
	{	
		fprintf(test,"zone t=\"test\"\n");
		for(n_c=0;n_c<Num_c;n_c++)
		{
			temp_x = 0.0;
			temp_y = 0.0;
			temp_z = 0.0;

			for(q=0;q<fcol;q++)
			{
				temp_x += ContrNet_ij_ksi[n_r][q] * N_sig_u[n_c][q];
				temp_y += ContrNet_ij_eta[n_r][q] * N_sig_u[n_c][q];
				temp_z += ContrNet_ij_zeta[n_r][q] * N_sig_u[n_c][q];
			}
		
			testx[n_r][n_c] = temp_x;
			testy[n_r][n_c] = temp_y;
			testz[n_r][n_c] = temp_z;
			fprintf(test,"%lf %lf %lf\n", testx[n_r][n_c], testy[n_r][n_c], testz[n_r][n_c]);
		}
	}

	//...calcuate Qij by u
	for(i=0;i<frow;i++)
	{
		for(j=0;j<fcol-1;j++)
		{
			ContrNet_ij_ksi_dev_1_u[i][j] = ((ORD_u)/(U[j+ORD_u+1]-U[j+1])) * (ContrNet_ij_ksi[i][j+1]-ContrNet_ij_ksi[i][j]);
			ContrNet_ij_eta_dev_1_u[i][j] = ((ORD_u)/(U[j+ORD_u+1]-U[j+1])) * (ContrNet_ij_eta[i][j+1]-ContrNet_ij_eta[i][j]);
			ContrNet_ij_zeta_dev_1_u[i][j] = ((ORD_u)/(U[j+ORD_u+1]-U[j+1])) * (ContrNet_ij_zeta[i][j+1]-ContrNet_ij_zeta[i][j]);
			fprintf(Qij_u_1, "%lf %lf\n", ContrNet_ij_ksi_dev_1_u[i][j], ContrNet_ij_eta_dev_1_u[i][j], ContrNet_ij_zeta_dev_1_u[i][j]);
		}
	}

	for(n_r=0;n_r<frow;n_r++)
	{	
		for(n_c=0;n_c<Num_c;n_c++)
		{
			temp_x_dev1_u = 0.0;
			temp_y_dev1_u = 0.0;
			temp_z_dev1_u = 0.0;
		
			for(q=0;q<fcol-1;q++)
			{
				if(n_c==Num_c-1)
				{
					temp_x_dev1_u = ContrNet_ij_ksi_dev_1_u[n_r][fcol-2];
					temp_y_dev1_u = ContrNet_ij_eta_dev_1_u[n_r][fcol-2];
					temp_z_dev1_u = ContrNet_ij_zeta_dev_1_u[n_r][fcol-2];
				}
				else if(n_c==0)
				{
					temp_x_dev1_u = ContrNet_ij_ksi_dev_1_u[n_r][0];
					temp_y_dev1_u = ContrNet_ij_eta_dev_1_u[n_r][0];
					temp_z_dev1_u = ContrNet_ij_zeta_dev_1_u[n_r][0];
				}
				else
				{
					temp_x_dev1_u += ContrNet_ij_ksi_dev_1_u[n_r][q] * N_u_sig_dev_1[n_c][q];
					temp_y_dev1_u += ContrNet_ij_eta_dev_1_u[n_r][q] * N_u_sig_dev_1[n_c][q];
					temp_z_dev1_u += ContrNet_ij_zeta_dev_1_u[n_r][q] * N_u_sig_dev_1[n_c][q];
				}
			}
			
			x_dev1_u[n_r][n_c] = temp_x_dev1_u;
			y_dev1_u[n_r][n_c] = temp_y_dev1_u;
			z_dev1_u[n_r][n_c] = temp_z_dev1_u;

			testnx[n_r][n_c] = cacu_n_P(x_dev1_u[n_r][n_c], x_dev1_u[n_r][n_c], y_dev1_u[n_r][n_c], z_dev1_u[n_r][n_c]);
			testny[n_r][n_c] = cacu_n_P(y_dev1_u[n_r][n_c], x_dev1_u[n_r][n_c], y_dev1_u[n_r][n_c], z_dev1_u[n_r][n_c]);
			testnz[n_r][n_c] = cacu_n_P(z_dev1_u[n_r][n_c], x_dev1_u[n_r][n_c], y_dev1_u[n_r][n_c], z_dev1_u[n_r][n_c]);
		
			fprintf(P_laod_u,  "zone t=\"nxy\"\n");
			fprintf(P_laod_u, "%lf %lf %lf\n", testx[n_r][n_c], testy[n_r][n_c], testz[n_r][n_c]);
			fprintf(P_laod_u, "%lf %lf %lf\n", testnx[n_r][n_c]+testx[n_r][n_c], testy[n_r][n_c]+testny[n_r][n_c],  testz[n_r][n_c]+testnz[n_r][n_c]);
		}
	}



	//...V knot
	create_Uni_Vnj_Knot_Ver(frow, ORD_v, V_temp);
	for(j=0;j<VER_ARR_v;j++)
	{
		V[j] = V_temp[j];
	}

	//...init v parameter
	for(j=0;j<Num_r;j++)
	{
		v[j] = (double)j/10.0;	
	}

	//...Here is Nv
	for(cout_r=0;cout_r<frow;cout_r++)		//row
	{
		fprintf(vN, "zone t=\"vN\"\n");
		fprintf(vNdev1, "zone t=\"vNdev1\"\n");
		for(n_r=0;n_r<Num_r;n_r++)		
		{
			fprintf(vN, "%lf ", v[n_r]);
			fprintf(vNdev1, "%lf ", v[n_r]);
			for(q=0;q<=ORD_v;q++)
			{	
				for(r=0;r<frow;r++)
				{	
					if(q==0)
					{
						if(v[n_r]>=V[r] && v[n_r]<V[r+1])
						{
							N_v[q][r] = 1.0;
						}
						else
						{
							N_v[q][r] = 0.0;
						}
					}
					else if(q==ORD_v&&n_r==Num_r-1&&r==frow-1)
					{
						N_v[q][r] = 1.0;				
					}
					else
					{
						N_v[q][r] = cacu_Nki(v[n_r], V[r], N_v[q-1][r], V[r+q], N_v[q-1][r+1], V[r+q+1], V[r+1]);
						N_v_dev1[q][r] = cacu_Nki_dev(q, V[r], N_v[q-1][r], V[r+q], N_v[q-1][r+1], V[r+q+1], V[r+1]);
					
					}
				}
				if(q==ORD_v)
				{	
					if(n_r==0 && cout_r==0)
					{
						for(vNt=0;vNt<2;vNt++)
						{
							vN_temp_dev1[vNt] = N_v_dev1[ORD_v][vNt];
						}
					}
					for(vNt=0;vNt<2;vNt++)
					{
						if(n_r==Num_r-1 && cout_r == frow - (vNt + 1))
						{
							N_v_dev1[ORD_v][frow - (vNt + 1)] = vN_temp_dev1[1 - vNt];
						}
					}
					
					fprintf(vN, "%lf\n", N_v[ORD_v][cout_r]);
					fprintf(vNdev1, "%lf\n", N_v_dev1[ORD_v][cout_r]);

					N_sig_v[n_r][cout_r] = N_v[ORD_v][cout_r];
					N_v_sig_dev_1[n_r][cout_r] = N_v[ORD_v-1][cout_r+1];		//dev 1 importent,this is right
				}
			}
		}
	}

	//...calcuate Qij by u
	for(j=0;j<fcol-1;j++)
	{
		ContrNet_ij_ksi_dev_1_u[1][j] = ((ORD_u)/(U[j+ORD_u+1]-U[j+1])) * (ContrNet_ij_ksi[1][j+1]-ContrNet_ij_ksi[1][j]);
		ContrNet_ij_eta_dev_1_u[1][j] = ((ORD_u)/(U[j+ORD_u+1]-U[j+1])) * (ContrNet_ij_eta[1][j+1]-ContrNet_ij_eta[1][j]);
		ContrNet_ij_zeta_dev_1_u[1][j] = ((ORD_u)/(U[j+ORD_u+1]-U[j+1])) * (ContrNet_ij_zeta[1][j+1]-ContrNet_ij_zeta[1][j]);
		fprintf(Qij_u_1, "%lf %lf\n", ContrNet_ij_ksi_dev_1_u[1][j], ContrNet_ij_zeta_dev_1_u[1][j]);
	}
	
	//...calcuate Qij by v
	for(i=0;i<frow-1;i++)
	{
		ContrNet_ij_ksi_dev_1_v[i][0] = ((ORD_v)/(V[i+ORD_v+1]-V[i+1])) * (ContrNet_ij_ksi_dev_1_u[i+1][j]-ContrNet_ij_ksi_dev_1_u[i][j]);
		ContrNet_ij_eta_dev_1_v[i][0] = ((ORD_v)/(V[i+ORD_v+1]-V[i+1])) * (ContrNet_ij_eta_dev_1_u[i+1][j]-ContrNet_ij_eta_dev_1_u[i][j]);
		ContrNet_ij_zeta_dev_1_v[i][0] = ((ORD_v)/(V[i+ORD_v+1]-V[i+1])) * (ContrNet_ij_zeta_dev_1_u[i+1][j]-ContrNet_ij_zeta_dev_1_u[i][j]);
//		fprintf(Qij_v, "%lf %lf %lf\n", ContrNet_ij_ksi_dev_1_v[i][j], ContrNet_ij_eta_dev_1_v[i][j], ContrNet_ij_zeta_dev_1_v[i][j]);
	}



	for(n_r=0;n_r<Num_r;n_r++)
	{	
		for(n_c=0;n_c<Num_c;n_c++)
		{
			temp_x = 0.0;
			temp_y = 0.0;
			temp_z = 0.0;

			for(p=0;p<frow;p++)
			{
				for(q=0;q<fcol;q++)
				{
					temp_x += ContrNet_ij_ksi[p][q] * N_sig_u[n_c][q] * N_sig_v[n_r][p];
					temp_y += ContrNet_ij_eta[p][q] * N_sig_u[n_c][q] * N_sig_v[n_r][p];
					temp_z += ContrNet_ij_zeta[p][q] * N_sig_u[n_c][q] * N_sig_v[n_r][p];
				}
			}
			x[n_r][n_c] = temp_x;
			y[n_r][n_c] = temp_y;
			z[n_r][n_c] = temp_z;
		}
	}

	Show_surface(x, y, z);

/*	
	//...calcuate Qij by u
	for(i=0;i<frow;i++)
	{
		fprintf(Qij_u, "zone t=\"Qij_u\"\n");
		for(j=0;j<fcol-1;j++)
		{
			ContrNet_ij_ksi_dev_1_u[i][j] = ((ORD_u)/(U[j+ORD_u+1]-U[j+1])) * (ContrNet_ij_ksi[i][j+1]-ContrNet_ij_ksi[i][j]);
			ContrNet_ij_eta_dev_1_u[i][j] = ((ORD_u)/(U[j+ORD_u+1]-U[j+1])) * (ContrNet_ij_eta[i][j+1]-ContrNet_ij_eta[i][j]);
			ContrNet_ij_zeta_dev_1_u[i][j] = ((ORD_u)/(U[j+ORD_u+1]-U[j+1])) * (ContrNet_ij_zeta[i][j+1]-ContrNet_ij_zeta[i][j]);
			fprintf(Qij_u, "%lf %lf %lf\n", ContrNet_ij_ksi_dev_1_u[i][j], ContrNet_ij_eta_dev_1_u[i][j], ContrNet_ij_zeta_dev_1_u[i][j]);
		}
	}

	//...calcuate Qij by v
	for(j=0;j<fcol-1;j++)
	{
		fprintf(Qij_v, "zone t=\"Qij_v\"\n");
		for(i=0;i<frow-1;i++)
		{
			ContrNet_ij_ksi_dev_1_v[i][j] = ((ORD_v)/(V[i+ORD_v+1]-V[i+1])) * (ContrNet_ij_ksi_dev_1_u[i+1][j]-ContrNet_ij_ksi_dev_1_u[i][j]);
			ContrNet_ij_eta_dev_1_v[i][j] = ((ORD_v)/(V[i+ORD_v+1]-V[i+1])) * (ContrNet_ij_eta_dev_1_u[i+1][j]-ContrNet_ij_eta_dev_1_u[i][j]);
			ContrNet_ij_zeta_dev_1_v[i][j] = ((ORD_v)/(V[i+ORD_v+1]-V[i+1])) * (ContrNet_ij_zeta_dev_1_u[i+1][j]-ContrNet_ij_zeta_dev_1_u[i][j]);
			fprintf(Qij_v, "%lf %lf %lf\n", ContrNet_ij_ksi_dev_1_v[i][j], ContrNet_ij_eta_dev_1_v[i][j], ContrNet_ij_zeta_dev_1_v[i][j]);
		}
	}
	


	for(n_r=0;n_r<Num_r;n_r++)
	{	
		for(n_c=0;n_c<Num_c;n_c++)
		{
			temp_x = 0.0;
			temp_y = 0.0;
			temp_z = 0.0;

			for(p=0;p<frow;p++)
			{
				for(q=0;q<fcol;q++)
				{
					temp_x += ContrNet_ij_ksi[p][q] * N_sig_u[n_c][q] * N_sig_v[n_r][p];
					temp_y += ContrNet_ij_eta[p][q] * N_sig_u[n_c][q] * N_sig_v[n_r][p];
					temp_z += ContrNet_ij_zeta[p][q] * N_sig_u[n_c][q] * N_sig_v[n_r][p];
				}
			}
			x[n_r][n_c] = temp_x;
			y[n_r][n_c] = temp_y;
			z[n_r][n_c] = temp_z;
		}
	}

	
	for(n_r=0;n_r<Num_r;n_r++)
	{	
		fprintf(P_laod_u, "zone t=\"P_laod_u\"\n");
		for(n_c=0;n_c<Num_c;n_c++)
		{
			temp_x_dev1_u = 0.0;
			temp_y_dev1_u = 0.0;
			temp_z_dev1_u = 0.0;
			for(p=0;p<frow;p++)
			{
				for(q=0;q<fcol-1;q++)
				{
					if(n_c==Num_c-1)
					{
						temp_x_dev1_u = ContrNet_ij_ksi_dev_1_u[p][fcol-2];
						temp_y_dev1_u = ContrNet_ij_eta_dev_1_u[p][fcol-2];
						temp_z_dev1_u = ContrNet_ij_zeta_dev_1_u[p][fcol-2];
					}
					else if(n_c==0)
					{
						temp_x_dev1_u = ContrNet_ij_ksi_dev_1_u[p][0];
						temp_y_dev1_u = ContrNet_ij_eta_dev_1_u[p][0];
						temp_z_dev1_u = ContrNet_ij_zeta_dev_1_u[p][0];
					}
					else
					{
						temp_x_dev1_u += ContrNet_ij_ksi_dev_1_u[p][q] * N_u_sig_dev_1[n_c][q];
						temp_y_dev1_u += ContrNet_ij_eta_dev_1_u[p][q] * N_u_sig_dev_1[n_c][q];
						temp_z_dev1_u += ContrNet_ij_zeta_dev_1_u[p][q] * N_u_sig_dev_1[n_c][q];
					}
				}
			}
			
			x_dev1_u[n_r][n_c] = temp_x_dev1_u;
			y_dev1_u[n_r][n_c] = temp_y_dev1_u;
			z_dev1_u[n_r][n_c] = temp_z_dev1_u;

			fprintf(P_laod_u, "%lf %lf %lf\n", x_dev1_u[n_r][n_c], y_dev1_u[n_r][n_c], z_dev1_u[n_r][n_c]);
		}
	}

	for(n_c=0;n_c<Num_c;n_c++)
	{	
		fprintf(P_laod_v, "zone t=\"P_laod_v\"\n");
		for(n_r=0;n_r<Num_r;n_r++)
		{
			temp_x_dev1_v = 0.0;
			temp_y_dev1_v = 0.0;
			temp_z_dev1_v = 0.0;
			for(q=0;q<fcol-1;q++)
			{
				for(p=0;p<frow-1;p++)
				{
					if(n_r==Num_r-1)
					{
						temp_x_dev1_v = ContrNet_ij_ksi_dev_1_v[frow-2][q];
						temp_y_dev1_v = ContrNet_ij_eta_dev_1_v[frow-2][q];
						temp_z_dev1_v = ContrNet_ij_zeta_dev_1_v[frow-2][q];
					}
					else if(n_r==0)
					{
						temp_x_dev1_v = ContrNet_ij_ksi_dev_1_v[0][q];
						temp_y_dev1_v = ContrNet_ij_eta_dev_1_v[0][q];
						temp_z_dev1_v = ContrNet_ij_zeta_dev_1_v[0][q];
					}
					else
					{
						temp_x_dev1_v += ContrNet_ij_ksi_dev_1_v[p][q] * N_v_sig_dev_1[n_r][p];
						temp_y_dev1_v += ContrNet_ij_eta_dev_1_v[p][q] * N_v_sig_dev_1[n_r][p];
						temp_z_dev1_v += ContrNet_ij_zeta_dev_1_v[p][q] * N_v_sig_dev_1[n_r][p];
					}
				}
			}
			x_dev1_v[n_c][n_r] = temp_x_dev1_v;
			y_dev1_v[n_c][n_r] = temp_y_dev1_v;
			z_dev1_v[n_c][n_r] = temp_z_dev1_v;

			fprintf(P_laod_v, "%lf %lf %lf\n", x_dev1_v[n_c][n_r], y_dev1_v[n_c][n_r], z_dev1_v[n_c][n_r]);
		}
	}
	

	for(n_r=0;n_r<Num_r;n_r++)
	{	
		for(n_c=0;n_c<Num_c;n_c++)
		{
	
	
		}
	}
*/



	return 0;
}

void Show_BaseP_Net(double BN_x[frow][fcol], double BN_y[frow][fcol], double BN_z[frow][fcol])
{	
	FILE *BN=fopen("BPxy.dat","wt");
	int i, j;
/*	for(i=0;i<frow;i++)
	{
		fprintf(BN, "zone t=\"BN\"\n");
		for(j=0;j<fcol;j++)
		{
			fprintf(BN, "%lf  ", BN_x[i][j]);
			fprintf(BN, "%lf  ", BN_y[i][j]);
			fprintf(BN, "%lf\n", BN_z[i][j]);
		}
	}
	for(j=0;j<fcol;j++)
	{
		fprintf(BN, "zone t=\"BN\"\n");
		for(i=0;i<frow;i++)
		{
			fprintf(BN, "%lf  ", BN_x[i][j]);
			fprintf(BN, "%lf  ", BN_y[i][j]);
			fprintf(BN, "%lf\n", BN_z[i][j]);
		}
	}*/
	for(i=0;i<frow;i++)
	{
	//	fprintf(BN, "zone t=\"BN\"\n");
		for(j=3;j<4;j++)
		{
			fprintf(BN, "%lf ", BN_x[i][j]);
			fprintf(BN, "%lf\n", BN_y[i][j]);
		//	fprintf(BN, "%lf\n", BN_z[i][j]);
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
	temp_resl=(((double)fcol-(double)ORD_u)/temp_sNv_1)*temp_sn;
	return temp_resl;
}

double cacu_BP_vn(double sNv_1, double sn)
{
	double temp_sNv_1, temp_sn, temp_resl;
	temp_sNv_1=sNv_1; temp_sn=sn;
	temp_resl=((double)(frow-ORD_v)/temp_sNv_1)*temp_sn;
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

void Show_Contr_Net(double sf_x[frow][fcol], double sf_y[frow][fcol], double sf_z[frow][fcol])
{	
	FILE *CP=fopen("CP.dat","wt");
	int i, j;
	for(i=0;i<frow;i++)
	{
		fprintf(CP, "zone t=\"test\"\n");
		for(j=0;j<fcol;j++)
		{
			fprintf(CP, "%lf  ", sf_x[i][j]);
			fprintf(CP, "%lf  ", sf_y[i][j]);
			fprintf(CP, "%lf\n", sf_z[i][j]);
		}
	}
	for(i=0;i<fcol;i++)
	{
		fprintf(CP, "zone t=\"test\"\n");
		for(j=0;j<frow;j++)
		{
			fprintf(CP, "%lf  ", sf_x[j][i]);
			fprintf(CP, "%lf  ", sf_y[j][i]);
			fprintf(CP, "%lf\n", sf_z[j][i]);
		}
	}
}

void Show_surface(double sf_x[Num_r][Num_c], double sf_y[Num_r][Num_c], double sf_z[Num_r][Num_c])
{
	FILE *Bsurface=fopen("Bsurface.dat","wt");
	int i, j;
	for(i=0;i<Num_r;i++)
	{
		fprintf(Bsurface, "zone t=\"Bsurface\"\n");
		for(j=0;j<Num_c;j++)
		{
			fprintf(Bsurface, "%lf  ", sf_x[i][j]);
			fprintf(Bsurface, "%lf  ", sf_y[i][j]);
			fprintf(Bsurface, "%lf\n", sf_z[i][j]);
		}
	}
	for(i=0;i<Num_c;i++)
	{
		fprintf(Bsurface, "zone t=\"Bsurface\"\n");
		for(j=0;j<Num_r;j++)
		{
			fprintf(Bsurface, "%lf  ", sf_x[j][i]);
			fprintf(Bsurface, "%lf  ", sf_y[j][i]);
			fprintf(Bsurface, "%lf\n", sf_z[j][i]);
		}
	}
}

double cacu_Nki_dev(int tk, double ui, double Nk_1i, double ui_k, double Nk_1i_1, double ui_k_1, double ui_1)
{
	double resl, temp_ui, temp_Nk_1i, temp_ui_k, temp_Nk_1i_1, temp_ui_k_1, temp_ui_1, temp_left, temp_right;
	int temp_tk;
	temp_tk=tk; temp_ui=ui; temp_Nk_1i=Nk_1i; temp_ui_k=ui_k; temp_Nk_1i_1=Nk_1i_1; temp_ui_k_1=ui_k_1; temp_ui_1=ui_1;
	if(temp_tk==0 || (temp_ui_k-temp_ui)==0)
	{
		temp_left=0.0;
	}
	else
	{
		temp_left=temp_tk*(temp_Nk_1i)/(temp_ui_k-temp_ui);
	}
	
	if(temp_tk==0 || (temp_ui_k_1-temp_ui_1)==0)
	{
		temp_right=0.0;
	}
	else
	{
		temp_right=temp_tk*(Nk_1i_1)/(temp_ui_k_1-temp_ui_1);
	}		
	resl=temp_left-temp_right;
	return resl;
}

double cacu_n_P(double Pf, double Px, double Py, double Pz)
{
	double temp_res, temp_pf, temp_px, temp_py, temp_pz;
	temp_pf=Pf; temp_px=Px; temp_py=Py; temp_pz=Pz;
	temp_res = temp_pf / sqrt(pow(temp_px,2)+pow(temp_py,2)+pow(temp_pz,2));
	return temp_res;
}

void matrix_inversion_using_elementary_operation_u(double original[frow][fcol], double inverse[frow][fcol], int dim)
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

	
void matrix_inversion_using_elementary_operation_v(double original[fcol][frow], double inverse[fcol][frow], int dim)
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