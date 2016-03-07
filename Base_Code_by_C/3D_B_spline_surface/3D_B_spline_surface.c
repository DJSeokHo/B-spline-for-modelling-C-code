#include <stdio.h>
#include <math.h>

#define Num_u 41						//...umax
#define Num_v 41						//...vmax
#define ORD_i 3						//...i
#define ORD_j 3						//...j
#define VER_i 4						//...Number of i Vertices
#define VER_j 4						//...Number of j Vertices
#define VER_ARR_i VER_i+ORD_i+1		//...Number of parameter u
#define VER_ARR_j VER_j+ORD_j+1		//...Number of parameter v

void Show_Contr_Net(double CN_x[ORD_i+1][ORD_j+1], double CN_y[ORD_i+1][ORD_j+1], double CN_z[ORD_i+1][ORD_j+1]);
void create_Uni_Knot(int, int, double *noda);
double cacu_basis_N_uv(double, double, double, double, double, double, double);
void Show_surface(double sf_x[Num_u][Num_v], double sf_y[Num_u][Num_v], double sf_z[Num_u][Num_v]);

main()
{
	int i, j, p, q, n_i, n_j, cout_i, cout_j;
	double ContrNet_ij_ksi[ORD_i+1][ORD_j+1], ContrNet_ij_eta[ORD_i+1][ORD_j+1], ContrNet_ij_zeta[ORD_i+1][ORD_j+1];
	double U_temp[VER_ARR_i], V_temp[VER_ARR_j], U[VER_ARR_i], V[VER_ARR_j];
	double u[Num_u], v[Num_v], N_u[ORD_i+1][VER_i], N_v[ORD_j+1][VER_j], N_sig_u[Num_u][VER_i], N_sig_v[Num_v][VER_j];
	double temp_x, temp_y, temp_z, x[Num_u][Num_v], y[Num_u][Num_v], z[Num_u][Num_v];

	//...init inter noda
	create_Uni_Knot(VER_i, ORD_i, U_temp);
	for(i=0;i<VER_ARR_i;i++)
	{
		U[i] = U_temp[i];
	}
	create_Uni_Knot(VER_j, ORD_j, V_temp);
	for(j=0;j<VER_ARR_j;j++)
	{
		V[j] = V_temp[j];
	}

/*//......check result
	for(i=0;i<VER_ARR_i;i++)
	{
		printf("%lf\n", U[i]);
	}
	for(j=0;j<VER_ARR_j;j++)
	{
		printf("%lf\n", V[j]);
	}
	printf("%d %d\n", cacl_KV_u, cacl_KV_v);
*///......check result

	//...init Control Net
	ContrNet_ij_ksi[0][0] = 0.0; ContrNet_ij_eta[0][0] = 2.5; ContrNet_ij_zeta[0][0] = 0.0;
	ContrNet_ij_ksi[0][1] = 0.0; ContrNet_ij_eta[0][1] = 2.0; ContrNet_ij_zeta[0][1] = 2.0;
	ContrNet_ij_ksi[0][2] = 0.0; ContrNet_ij_eta[0][2] = 1.0; ContrNet_ij_zeta[0][2] = 3.0;
	ContrNet_ij_ksi[0][3] = 0.0; ContrNet_ij_eta[0][3] = 0.0; ContrNet_ij_zeta[0][3] = 3.0;
	ContrNet_ij_ksi[1][0] = 1.0; ContrNet_ij_eta[1][0] = 3.0; ContrNet_ij_zeta[1][0] = 0.0;
	ContrNet_ij_ksi[1][1] = 1.0; ContrNet_ij_eta[1][1] = 3.0; ContrNet_ij_zeta[1][1] = 2.0;
	ContrNet_ij_ksi[1][2] = 1.0; ContrNet_ij_eta[1][2] = 1.5; ContrNet_ij_zeta[1][2] = 3.5;
	ContrNet_ij_ksi[1][3] = 1.0; ContrNet_ij_eta[1][3] = 0.0; ContrNet_ij_zeta[1][3] = 3.5;
	ContrNet_ij_ksi[2][0] = 3.0; ContrNet_ij_eta[2][0] = 3.0; ContrNet_ij_zeta[2][0] = 0.0;
	ContrNet_ij_ksi[2][1] = 3.0; ContrNet_ij_eta[2][1] = 3.0; ContrNet_ij_zeta[2][1] = 2.0;
	ContrNet_ij_ksi[2][2] = 3.0; ContrNet_ij_eta[2][2] = 1.5; ContrNet_ij_zeta[2][2] = 3.5;
	ContrNet_ij_ksi[2][3] = 3.0; ContrNet_ij_eta[2][3] = 0.0; ContrNet_ij_zeta[2][3] = 3.5;
	ContrNet_ij_ksi[3][0] = 4.0; ContrNet_ij_eta[3][0] = 2.5; ContrNet_ij_zeta[3][0] = 0.0;
	ContrNet_ij_ksi[3][1] = 4.0; ContrNet_ij_eta[3][1] = 2.0; ContrNet_ij_zeta[3][1] = 2.0;
	ContrNet_ij_ksi[3][2] = 4.0; ContrNet_ij_eta[3][2] = 1.0; ContrNet_ij_zeta[3][2] = 3.0;
	ContrNet_ij_ksi[3][3] = 4.0; ContrNet_ij_eta[3][3] = 0.0; ContrNet_ij_zeta[3][3] = 3.0;	
	Show_Contr_Net(ContrNet_ij_ksi, ContrNet_ij_eta, ContrNet_ij_zeta);

	//init u, v
	for(i=0;i<Num_u;i++)
	{
		u[i] = (double)i/40.0;	//!!!!!!!!!! Here set number of u can change the precision(point number)!!!!!!!!!!
//		printf("%lf\n", u[i]);	//......check result
	}
	for(j=0;j<Num_v;j++)
	{
		v[j] = (double)j/40.0;	//!!!!!!!!!! Here set number of u can change the precision(point number)!!!!!!!!!!
//		printf("%lf\n", v[j]);	//......check result
	}
	
	//...calculate basis function for Nu & Nv
	//...start from Nu
	for(cout_i=0;cout_i<VER_i;cout_i++)
	{
	//	fprintf(test_u, "zone t=\"test\"\n");
		for(n_i=0;n_i<Num_u;n_i++)
		{
		//	fprintf(test_u, "%lf ", u[n_i]);
			for(p=0;p<=ORD_i;p++)
			{
				for(i=0;i<VER_i;i++)
				{	
					if(p==0)
					{
						if(u[n_i]>=U[i] && u[n_i]<U[i+1])
						{
							N_u[p][i] = 1.0;
						}
						else
						{
							N_u[p][i] = 0.0;
						}
					}
					else if(p==ORD_i&&n_i==Num_u-1&&i==VER_i-1)
					{
						N_u[p][i] = 1.0;
					}
					else
					{
						N_u[p][i] = cacu_basis_N_uv(u[n_i], U[i], N_u[p-1][i], U[i+p], N_u[p-1][i+1], U[i+p+1], U[i+1]);
					}
				}
				if(p==ORD_i)		//Here means if we need Order 2, wo can get 2, if we need Order 3,we can get 3
				{
				//	fprintf(test_u, "%lf\n", N_u[ORD_i][cout_i]);
					N_sig_u[n_i][cout_i] = N_u[ORD_i][cout_i];
				}
			}
		}
	}
	//...Here is Nv
	for(cout_j=0;cout_j<VER_j;cout_j++)
	{
	//	fprintf(test_v, "zone t=\"test\"\n");
		for(n_j=0;n_j<Num_v;n_j++)
		{
		//	fprintf(test_v, "%lf ", v[n_j]);
			for(q=0;q<=ORD_j;q++)
			{
				for(j=0;j<VER_j;j++)
				{	
					if(q==0)
					{
						if(v[n_j]>=V[j] && v[n_j]<V[j+1])
						{
							N_v[q][j] = 1.0;
						}
						else
						{
							N_v[q][j] = 0.0;
						}
					}
					else if(q==ORD_j&&n_j==Num_v-1&&j==VER_j-1)
					{
						N_v[q][j] = 1.0;
					}
					else
					{
						N_v[q][j] = cacu_basis_N_uv(v[n_j], V[j], N_v[q-1][j], V[j+q], N_v[q-1][j+1], V[j+q+1], V[j+1]);
					}
				}
				if(q==ORD_j)		//Here means if we need Order 2, wo can get 2, if we need Order 3,we can get 3
				{
				//	fprintf(test_v, "%lf\n", N_v[ORD_j][cout_j]);
					N_sig_v[n_j][cout_j] = N_v[ORD_j][cout_j];
				}
			}
		}
	}

	for(n_i=0;n_i<Num_v;n_i++)
	{
		for(n_j=0;n_j<Num_v;n_j++)
		{
			temp_x = 0.0;
			temp_y = 0.0;
			temp_z = 0.0;
			for(p=0;p<VER_i;p++)
			{
				for(q=0;q<VER_j;q++)
				{
					temp_x += ContrNet_ij_ksi[p][q] * N_sig_u[n_i][p] * N_sig_v[n_j][q];
					temp_y += ContrNet_ij_eta[p][q] * N_sig_u[n_i][p] * N_sig_v[n_j][q];
					temp_z += ContrNet_ij_zeta[p][q] * N_sig_u[n_i][p] * N_sig_v[n_j][q];
				}
			}
			x[n_i][n_j] = temp_x;
			y[n_i][n_j] = temp_y;
			z[n_i][n_j] = temp_z;
		}
	}
	Show_surface(x, y, z);

	return 0;
}

void Show_Contr_Net(double CN_x[ORD_i+1][ORD_j+1], double CN_y[ORD_i+1][ORD_j+1], double CN_z[ORD_i+1][ORD_j+1])
{
	FILE *CN=fopen("CN.dat","wt");
	int i, j;
	for(i=0;i<ORD_i+1;i++)
	{
		fprintf(CN, "zone t=\"CN\"\n");
		for(j=0;j<ORD_j+1;j++)
		{
			fprintf(CN, "%lf  ", CN_x[i][j]);
			fprintf(CN, "%lf  ", CN_y[i][j]);
			fprintf(CN, "%lf\n", CN_z[i][j]);
		}
	}
	for(i=0;i<ORD_i+1;i++)
	{
		fprintf(CN, "zone t=\"CN\"\n");
		for(j=0;j<ORD_j+1;j++)
		{
			fprintf(CN, "%lf  ", CN_x[j][i]);
			fprintf(CN, "%lf  ", CN_y[j][i]);
			fprintf(CN, "%lf\n", CN_z[j][i]);
		}
	}
}

void create_Uni_Knot(int n, int p, double *noda)
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

double cacu_basis_N_uv(double uv, double uvij, double Npq_1ij, double uvij_pq, double Npq_1ij_1, double uvij_pq_1, double uvij_1)
{	
//...!! parameter name is u because this is a normal 2D basis function. it can used for any other parameter.!!!
	double resl_uv, temp_uv, temp_uvij, temp_Npq_1ij, temp_uvij_pq, temp_uvij_pq_1, temp_Npq_1ij_1, temp_uvij_1, temp_left_uv, temp_right_uv;
	temp_uv=uv; temp_uvij=uvij; temp_Npq_1ij=Npq_1ij; temp_uvij_pq=uvij_pq; temp_uvij_pq_1=uvij_pq_1; temp_Npq_1ij_1=Npq_1ij_1; temp_uvij_1=uvij_1;
	if(((temp_uv-temp_uvij)*temp_Npq_1ij)==0 || (temp_uvij_pq-temp_uvij)==0)
	{
		temp_left_uv=0.0;
	}
	else
	{
		temp_left_uv=((temp_uv-temp_uvij)*temp_Npq_1ij)/(temp_uvij_pq-temp_uvij);
	}
	
	if(((temp_uvij_pq_1-temp_uv)*Npq_1ij_1)==0 || (temp_uvij_pq_1-temp_uvij_1)==0)
	{
		temp_right_uv=0.0;
	}
	else
	{
		temp_right_uv=((temp_uvij_pq_1-temp_uv)*Npq_1ij_1)/(temp_uvij_pq_1-temp_uvij_1);
	}		
	resl_uv=temp_left_uv+temp_right_uv;
	return resl_uv;
}

void Show_surface(double sf_x[Num_u][Num_v], double sf_y[Num_u][Num_v], double sf_z[Num_u][Num_v])
{
	FILE *test=fopen("test.dat","wt");
	int i, j;
	for(i=0;i<Num_u;i++)
	{
		fprintf(test, "zone t=\"test\"\n");
		for(j=0;j<Num_v;j++)
		{
			fprintf(test, "%lf  ", sf_x[i][j]);
			fprintf(test, "%lf  ", sf_y[i][j]);
			fprintf(test, "%lf\n", sf_z[i][j]);
		}
	}
	for(i=0;i<Num_u;i++)
	{
		fprintf(test, "zone t=\"test\"\n");
		for(j=0;j<Num_v;j++)
		{
			fprintf(test, "%lf  ", sf_x[j][i]);
			fprintf(test, "%lf  ", sf_y[j][i]);
			fprintf(test, "%lf\n", sf_z[j][i]);
		}
	}
}


