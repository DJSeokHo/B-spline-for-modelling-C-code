#include "3D_B_spline.h"

using namespace std;

int main(void)
{
	int i, j;
	int BP_i, BP_j, ORD_i, ORD_j, VER_i, VER_j, VER_ARR_i, VER_ARR_j;

	INDX *INDX_Object;
	BasePNet **BPN;

	INDX_Object = new INDX;

	INDX_Object->Set_BP_ij(4, 4);
	INDX_Object->Set_ORD_ij(3, 3);
	INDX_Object->Set_VER_ij(4, 4);
	INDX_Object->Set_VER_ARR_ij();

	BP_i = INDX_Object->Get_BP_i();
	BP_j = INDX_Object->Get_BP_j();
	ORD_i = INDX_Object->Get_ORD_i();
	ORD_j = INDX_Object->Get_ORD_j();
	VER_i = INDX_Object->Get_VER_i();
	VER_j = INDX_Object->Get_VER_j();
	VER_ARR_i = INDX_Object->Get_VER_ARR_i();
	VER_ARR_j = INDX_Object->Get_VER_ARR_j();

	BPN = new BasePNet*[BP_i];
	for(i = 0;i < BP_i; i++)
	{
		 BPN[i]=new BasePNet[BP_j];
	}

	//...init BP Net ksi
	BPN[0][0].Set_ksi(0.0);
	BPN[0][1].Set_ksi(1.0);
	BPN[0][2].Set_ksi(2.0);
	BPN[0][3].Set_ksi(3.0);

	BPN[1][0].Set_ksi(0.3);
	BPN[1][1].Set_ksi(1.3);
	BPN[1][2].Set_ksi(2.3);
	BPN[1][3].Set_ksi(3.4);

	BPN[2][0].Set_ksi(0.0);
	BPN[2][1].Set_ksi(1.0);
	BPN[2][2].Set_ksi(2.0);
	BPN[2][3].Set_ksi(3.0);

	BPN[3][0].Set_ksi(0.5);
	BPN[3][1].Set_ksi(1.3);
	BPN[3][2].Set_ksi(2.4);
	BPN[3][3].Set_ksi(3.3);

	//...init BP Net eta
	BPN[0][0].Set_eta(0.0);
	BPN[0][1].Set_eta(0.0);
	BPN[0][2].Set_eta(0.0);
	BPN[0][3].Set_eta(0.0);

	BPN[1][0].Set_eta(1.3);
	BPN[1][1].Set_eta(1.5);
	BPN[1][2].Set_eta(1.5);
	BPN[1][3].Set_eta(1.0);

	BPN[2][0].Set_eta(2.0);
	BPN[2][1].Set_eta(2.4);
	BPN[2][2].Set_eta(2.4);
	BPN[2][3].Set_eta(2.0);

	BPN[3][0].Set_eta(2.5);
	BPN[3][1].Set_eta(3.0);
	BPN[3][2].Set_eta(3.0);
	BPN[3][3].Set_eta(2.5);

	//...init BP Net zeta
	BPN[0][0].Set_zeta(0.5);
	BPN[0][1].Set_zeta(0.0);
	BPN[0][2].Set_zeta(0.0);
	BPN[0][3].Set_zeta(0.5);

	BPN[1][0].Set_zeta(0.5);
	BPN[1][1].Set_zeta(0.0);
	BPN[1][2].Set_zeta(0.0);
	BPN[1][3].Set_zeta(0.5);

	BPN[2][0].Set_zeta(1.0);
	BPN[2][1].Set_zeta(0.5);
	BPN[2][2].Set_zeta(0.5);
	BPN[2][3].Set_zeta(1.0);

	BPN[3][0].Set_zeta(1.5);
	BPN[3][1].Set_zeta(1.0);
	BPN[3][2].Set_zeta(1.0);
	BPN[3][3].Set_zeta(1.5);

	for(i=0;i<BP_i;i++)
	{
		for(j=0;j<BP_j;j++)
		{
			cout<<"("<<BPN[i][j].Get_ksi()<<")"<<" "<<"("<<BPN[i][j].Get_eta()<<")"<<" "<<"("<<BPN[i][j].Get_zeta()<<")"<<endl;
		}
	}
	
	//...show BP Net
	ofstream BN;
	BN.open("BPxy.dat");
	for(i=0;i<BP_i;i++)
	{
		BN<<"zone t=\"BN\""<<endl;
		for(j=0;j<BP_j;j++)
		{
			BN<<BPN[i][j].Get_ksi()<<" ";
			BN<<BPN[i][j].Get_eta()<<" ";
			BN<<BPN[i][j].Get_zeta()<<endl;
		}
	}
	for(j=0;j<BP_j;j++)
	{
		BN<<"zone t=\"BN\""<<endl;
		for(i=0;i<BP_i;i++)
		{
			BN<<BPN[i][j].Get_ksi()<<" ";
			BN<<BPN[i][j].Get_eta()<<" ";
			BN<<BPN[i][j].Get_zeta()<<endl;
		}
	}
	

	double **BP_sn_u, **BP_sn_v;

	BP_sn_u = new double*[BP_i];
	for(i = 0;i < BP_i; i++)
	{
		 BP_sn_u[i]=new double[BP_j];
	}

	BP_sn_v = new double*[BP_i];
	for(i = 0;i < BP_i; i++)
	{
		 BP_sn_v[i]=new double[BP_j];
	}

	Mesod *MD;
	MD = new Mesod;

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
				BP_sn_u[i][j] = MD->cacu_BP_sn_uv(BP_sn_u[i][j-1], BPN[i][j].Get_ksi(), BPN[i][j-1].Get_ksi(), BPN[i][j].Get_eta(), BPN[i][j-1].Get_eta(), BPN[i][j].Get_zeta(), BPN[i][j-1].Get_zeta());
			}
		}
	}
	//...calculate v for basis point
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
				BP_sn_v[j][i] = MD->cacu_BP_sn_uv(BP_sn_v[j][i-1], BPN[i][j].Get_ksi(), BPN[i-1][j].Get_ksi(), BPN[i][j].Get_eta(), BPN[i-1][j].Get_eta(), BPN[i][j].Get_zeta(), BPN[i-1][j].Get_zeta());
			}
		}
	}


	double **BP_un, **BP_vn;

	BP_un = new double*[BP_i];
	for(i = 0;i < BP_i; i++)
	{
		 BP_un[i]=new double[BP_j];
	}

	BP_vn = new double*[BP_j];
	for(j = 0;j < BP_j; j++)
	{
		 BP_vn[j]=new double[BP_i];
	}

	double *U_temp, *V_temp;

	U_temp = new double[VER_ARR_i];
	V_temp = new double[VER_ARR_j];

	//...calculate the u
	for(i=0;i<BP_i;i++)
	{
		for(j=0;j<BP_j;j++)
		{
			BP_un[i][j] = MD->cacu_BP_un(BP_sn_u[i][BP_j-1], BP_sn_u[i][j], BP_i, ORD_i);	
		}
	}
	//...create temp U knot
	MD->create_Uni_Vnj_Knot_Ver(VER_i, ORD_i, U_temp);

	//...calculate the v
	for(j=0;j<BP_j;j++)
	{
		for(i=0;i<BP_i;i++)
		{
			BP_vn[j][i] = MD->cacu_BP_vn(BP_sn_v[j][BP_i-1], BP_sn_v[j][i], BP_j, ORD_j);			
		}
	}
	//...create temp V knot
	MD->create_Uni_Vnj_Knot_Ver(VER_j, ORD_j, V_temp);

	return 0;
}