#include "2D_Bspline_Basic_LINES.h"

/*
Create 2D B-spline by SeokHo(SHI HAO)
you can get some B-spline data for using Tecplot
*/



//...Out Put X-Y, Y-Z, X-Z
int *XYLINE;	
int *XYBP;
int *XYVER;
int *XYORD;
int *XYBPARR;
int *XYVERARR;
int *XYNUM;

//...Init X-Y, Y-Z, X-Z malloc
BP **BP_xy;
CP **CP_xy;
BSPLINE_XY *BSPL_xy;

CALT_MTHOD *CaltMethod;
CALTCP_XY *caltCP_XY;
CALTBSPLINE_XY *caltBSP_XY;

void Init_Num_Ord()
{
	XYLINE=new int;
	XYBP=new int;
	XYVER=new int;
	XYORD=new int;
	XYBPARR=new int;
	XYVERARR=new int;
	XYNUM=new int;

	//...Init Num Ord
	*XYLINE = 1;				//...Number of X-Y Line
	*XYBP  = 7;	
	*XYVER = *XYBP;
	*XYORD = 3;
	*XYNUM = 40;
	*XYVERARR = *XYORD + *XYVER;
	*XYBPARR = *XYORD + *XYBP;

	/////////////////////////////////Init BP
	BP_xy = new BP*[*XYLINE];
	for(int index=0;index<*XYLINE;index++)
	{
		BP_xy[index] = new BP[*XYBP];
	}
		
	for(index=0;index<*XYLINE;index++)
	{
		for(int i=0;i<*XYBP;i++)
		{
			BP_xy[index][i].Init_BP_UN();
		}
	}

	/////////////////////////////////Init CP
	CP_xy = new CP*[*XYLINE];
	for(index=0;index<*XYLINE;index++)
	{
		CP_xy[index] = new CP[*XYBP];
	}

	for(index=0;index<*XYLINE;index++)
	{
		for(int i=0;i<*XYVER;i++)
		{
			CP_xy[index][i].Init_CP();
		}
	}

	/////////////////////////////////Init CP method
	caltCP_XY = new CALTCP_XY;
	caltCP_XY->Init_N(*XYORD, *XYBP);
	caltCP_XY->Init_U(*XYLINE, *XYVERARR); 
	
	/////////////////////////////////Init BSPLine method
	
	BSPL_xy = new BSPLINE_XY;
	caltBSP_XY = new CALTBSPLINE_XY;
	BSPL_xy->Init(*XYLINE, *XYNUM);
	caltBSP_XY->Init_U(*XYLINE, *XYVERARR);
	caltBSP_XY->Init_N(*XYORD, *XYVER, *XYNUM);
	caltBSP_XY->Init_U_dev(*XYLINE, *XYVERARR-2);
}

void Init_Method()
{
	CaltMethod = new CALT_MTHOD;
}

void Init_BP_XY()
{
	int index;
	
	ofstream BPx;
	BPx.open("BPx.dat");

	index = 0;
		
	*BP_xy[index][0].x = -4.000;
	*BP_xy[index][1].x = 0.000;  
	*BP_xy[index][2].x = 3.037; 
	*BP_xy[index][3].x = 5.941;  
	*BP_xy[index][4].x = 7.769;
	*BP_xy[index][5].x = 8.406; 
	*BP_xy[index][6].x = 8.948; 
	
	*BP_xy[index][0].y = 0.000;
	*BP_xy[index][1].y = 1.252;  
	*BP_xy[index][2].y = 2.340; 
	*BP_xy[index][3].y = 4.206;  
	*BP_xy[index][4].y = 6.000;
	*BP_xy[index][5].y = 7.000; 
	*BP_xy[index][6].y = 8.000;  

	*BP_xy[index][0].z = 0.000;
	*BP_xy[index][1].z = 0.000;  
	*BP_xy[index][2].z = 0.000; 
	*BP_xy[index][3].z = 0.000;  
	*BP_xy[index][4].z = 0.000;
	*BP_xy[index][5].z = 0.000; 
	*BP_xy[index][6].z = 0.000; 

	BPx<<"zone t=\"BPx\""<<endl;
	for(int i=0;i<*XYBP;i++)
	{
		BPx<<*BP_xy[index][i].x<<" "<<*BP_xy[index][i].y<<" "<<*BP_xy[index][i].z<<endl;
	}		

	BPx.close();
}

void CALT_CP_XY()
{
	int index;

	ofstream BP_snx;
	BP_snx.open("BP_snx.dat");
	ofstream BP_unx;
	BP_unx.open("BP_unx.dat");

	index = 0;

	BP_snx<<"zone t=\"BP_sn\""<<endl;
	BP_unx<<"zone t=\"BP_un\""<<endl;
	for(int i=0;i<*XYBP;i++)
	{
		if(i==0)
		{
			*BP_xy[index][i].BP_sn = 0.0;
		}
		else
		{
			CaltMethod->cacu_BP_sn(BP_xy[index][i-1].BP_sn, BP_xy[index][i].x, BP_xy[index][i-1].x, BP_xy[index][i].y, BP_xy[index][i-1].y, BP_xy[index][i].BP_sn);
		}
		BP_snx<<*BP_xy[index][i].BP_sn<<endl;
	}
	
	for(i=0;i<*XYBP;i++)
	{
		CaltMethod->cacu_BP_un(BP_xy[index][*XYBP-1].BP_sn, BP_xy[index][i].BP_sn, *XYORD, *XYBP, BP_xy[index][i].BP_un);
		BP_unx<<*BP_xy[index][i].BP_un<<endl;
	}

	CaltMethod->create_Uni_Knot_Ver(*XYBP, *XYORD, caltCP_XY->U_xy[index], *XYBPARR);
	
	BP_snx.close();
	BP_unx.close();

	//...Calculate Basic Function N and Control Point
	ofstream uNBPx;
	uNBPx.open("uNBPx.dat");
	ofstream CPx;
	CPx.open("CPx.dat");

	int spn;

	for(int j=0;j<*XYBP;j++)
	{
		spn = CaltMethod->FindSpan(*XYBP-1, *XYORD, *BP_xy[index][j].BP_un, caltCP_XY->U_xy[index]);
		CaltMethod->BasisFuns(spn, *BP_xy[index][j].BP_un, *XYORD, caltCP_XY->U_xy[index], caltCP_XY->N); 
		for(int i=0;i<=*XYORD;i++) 
		{
			caltCP_XY->temp_BP_N_xy[j][spn-*XYORD+i] = caltCP_XY->N[i];
		}
	}
	
	CaltMethod->ludcmp(caltCP_XY->temp_BP_N_xy, caltCP_XY->inv_temp_BP_N_xy, *XYBP, caltCP_XY->pivot, caltCP_XY->plusminusone); 
	for(j=0;j<*XYBP;j++)
	{
		caltCP_XY->rhs[j] = *BP_xy[index][j].x;
	}
	CaltMethod->lubksb(caltCP_XY->inv_temp_BP_N_xy, *XYBP, caltCP_XY->pivot, caltCP_XY->rhs);
	for(j=0;j<*XYBP;j++)
	{
		*CP_xy[index][j].ksi = caltCP_XY->rhs[j];
	}
	for(j=0;j<*XYBP;j++)
	{
		caltCP_XY->rhs[j] = *BP_xy[index][j].y;
	}
	CaltMethod->lubksb(caltCP_XY->inv_temp_BP_N_xy, *XYBP, caltCP_XY->pivot, caltCP_XY->rhs);
	for(j=0;j<*XYBP;j++)
	{
		*CP_xy[index][j].eta = caltCP_XY->rhs[j];
		*CP_xy[index][j].zeta = 0.0;
	}
	for(i=0;i<*XYVER;i++)
	{
		CPx<<*CP_xy[index][i].ksi<<" "<<*CP_xy[index][i].eta<<" "<<*CP_xy[index][i].zeta<<endl;
	}
	
	uNBPx.close();
	CPx.close();
}

void CALT_BSPLINE_XY()
{
	//...Calculate basic function N Ndev1 Ndev2
	int index, i, cout, n, k, uNt, cot;
	index = 0;

	CaltMethod->create_Uni_Knot_Ver(*XYVER, *XYORD, caltBSP_XY->U_xy[index], *XYVERARR);

	ofstream uNx, uNdev1x, uNdev2x;
	uNx.open("uNx.dat");
	uNdev1x.open("uNdev1x.dat");
	uNdev2x.open("uNdev2x.dat");
		
	ofstream CPdev1x;
	CPdev1x.open("CPdev1x.dat");
	ofstream CPdev2x;
	CPdev2x.open("CPdev2x.dat");
	
	ofstream Bsplinex;
	Bsplinex.open("Bsplinex.dat");
	ofstream Bsplinedev1x;
	Bsplinedev1x.open("Bsplinedev1x.dat");
	ofstream Bsplinedev2x;
	Bsplinedev2x.open("Bsplinedev2x.dat");
	ofstream nxyx;
	nxyx.open("nxyx.dat");
	ofstream Bsplinenxnyx;
	Bsplinenxnyx.open("Bsplinenxnyx.dat");
	ofstream Kslopex;
	Kslopex.open("Kslopex.dat");
	
	double *maxu;
	double *delu;
	maxu = new double;
	delu = new double;
	*maxu = (double)(*XYVER - *XYORD);
	*delu = *maxu / (double)(*XYNUM-1);

	//...XYZ... u spn U
	for(i=0;i<*XYNUM;i++)
	{
		caltBSP_XY->u_xy[i] = (double)i * *delu;
	}

	for(i=0;i<*XYNUM;i++)
	{
		int *uspan, *uind;
		uspan = new int;
		uind = new int;

		*uspan = CaltMethod->FindSpan(*XYVER-1, *XYORD, caltBSP_XY->u_xy[i], caltBSP_XY->U_xy[index]);
		CaltMethod->BasisFuns(*uspan, caltBSP_XY->u_xy[i], *XYORD, caltBSP_XY->U_xy[index], caltBSP_XY->Nu);
	
		*uind = *uspan - *XYORD;
	
		BSPL_xy->x[index][i] = 0.0;
		BSPL_xy->y[index][i] = 0.0;
		BSPL_xy->z[index][i] = 0.0;
	
		for(int k=0;k<=*XYORD;k++) 
		{
			BSPL_xy->x[index][i] += caltBSP_XY->Nu[k] * *CP_xy[index][*uind+k].ksi;
			BSPL_xy->y[index][i] += caltBSP_XY->Nu[k] * *CP_xy[index][*uind+k].eta;
		}
		Bsplinex<<BSPL_xy->x[index][i]<<" "<<BSPL_xy->y[index][i]<<" "<<BSPL_xy->z[index][i]<<endl;
		delete uspan;
		delete uind;
	}
	delete maxu;
	delete delu;


/*
////////////////////////////////////////////////////////////////////////////////

	//...XY...N
	for(cout=0;cout<*XYVER;cout++)
	{
		uNx<<"zone t=\"uN\""<<endl;
		uNdev1x<<"zone t=\"uNdev1\""<<endl;
		uNdev2x<<"zone t=\"uNdev2\""<<endl;
		for(n=0;n<*XYNUM;n++)
		{
			uNx<<caltBSP_XY->u_xy[n]<<" ";
			uNdev1x<<caltBSP_XY->u_xy[n]<<" ";
			uNdev2x<<caltBSP_XY->u_xy[n]<<" ";
			for(k=0;k<=*XYORD;k++)
			{	
				for(i=0;i<*XYVER;i++)
				{	
					if(k==0)
					{
						if(caltBSP_XY->u_xy[n]>=caltBSP_XY->U_xy[index][i] && caltBSP_XY->u_xy[n]<caltBSP_XY->U_xy[index][i+1])
						{
							caltBSP_XY->N_xy[k][i] = 1.0;
						}
						else
						{
							caltBSP_XY->N_xy[k][i] = 0.0;
						}
					}
					else if(k==*XYORD&&n==*XYNUM-1&&i==*XYVER-1)
					{
						caltBSP_XY->N_xy[k][i] = 1.0;				
					}
					else
					{
						caltBSP_XY->N_xy[k][i]	= CaltMethod->cacu_Nki(caltBSP_XY->u_xy[n], caltBSP_XY->U_xy[index][i], caltBSP_XY->N_xy[k-1][i], caltBSP_XY->U_xy[index][i+k], caltBSP_XY->N_xy[k-1][i+1], caltBSP_XY->U_xy[index][i+k+1], caltBSP_XY->U_xy[index][i+1]);
						caltBSP_XY->N_dev1_xy[k][i] = CaltMethod->cacu_Nki_dev(k, caltBSP_XY->U_xy[index][i], caltBSP_XY->N_xy[k-1][i], caltBSP_XY->U_xy[index][i+k], caltBSP_XY->N_xy[k-1][i+1], caltBSP_XY->U_xy[index][i+k+1], caltBSP_XY->U_xy[index][i+1]);
						caltBSP_XY->N_dev2_xy[k][i] = CaltMethod->cacu_Nki_dev(k, caltBSP_XY->U_xy[index][i], caltBSP_XY->N_dev1_xy[k-1][i], caltBSP_XY->U_xy[index][i+k], caltBSP_XY->N_dev1_xy[k-1][i+1], caltBSP_XY->U_xy[index][i+k+1], caltBSP_XY->U_xy[index][i+1]);
					}
				}
				if(k==*XYORD)
				{			
					if(n==0 && cout==0)
					{
						for(uNt=0;uNt<2;uNt++)
						{
							caltBSP_XY->uN_temp_dev1[uNt] = caltBSP_XY->N_dev1_xy[*XYORD][uNt];
						}
					}
					for(uNt=0;uNt<2;uNt++)
					{
						if(n==*XYNUM-1 && cout == *XYVER - (uNt + 1))
						{
							caltBSP_XY->N_dev1_xy[*XYORD][*XYVER - (uNt + 1)] = caltBSP_XY->uN_temp_dev1[1 - uNt];
						}
					}

					if(n==0 && cout==0)
					{
						for(uNt=0;uNt<3;uNt++)
						{
							caltBSP_XY->uN_temp_dev2[uNt] = caltBSP_XY->N_dev2_xy[*XYORD][uNt];
						}
					}
					for(uNt=0;uNt<3;uNt++)
					{
						if(n==*XYNUM-1 && cout == *XYVER - (uNt + 1))
						{
							caltBSP_XY->N_dev2_xy[*XYORD][*XYVER - (uNt + 1)] = caltBSP_XY->uN_temp_dev2[uNt];
						}
					}

					uNx<<caltBSP_XY->N_xy[*XYORD][cout]<<endl;
					uNdev1x<<caltBSP_XY->N_dev1_xy[*XYORD][cout]<<endl;
					uNdev2x<<caltBSP_XY->N_dev2_xy[*XYORD][cout]<<endl;

					caltBSP_XY->N_sig_xy[n][cout] = caltBSP_XY->N_xy[*XYORD][cout];
					caltBSP_XY->N_sig_dev_1_xy[n][cout] = caltBSP_XY->N_xy[*XYORD-1][cout+1];		//dev 1 importent,this is right
					caltBSP_XY->N_sig_dev_2_xy[n][cout] = caltBSP_XY->N_xy[*XYORD-2][cout+2];		//dev 2 importent,this is right
				}
			}
		}
	}
	
	//...XY...CP...dev
	for(i=0;i<*XYVER-1;i++)
	{		
		CP_xy[index][i].Set_ksi_dev1(((*XYORD)/(caltBSP_XY->U_xy[index][i+*XYORD+1]-caltBSP_XY->U_xy[index][i+1]))*(CP_xy[index][i+1].Get_ksi()-CP_xy[index][i].Get_ksi()));
		CP_xy[index][i].Set_eta_dev1(((*XYORD)/(caltBSP_XY->U_xy[index][i+*XYORD+1]-caltBSP_XY->U_xy[index][i+1]))*(CP_xy[index][i+1].Get_eta()-CP_xy[index][i].Get_eta()));		
		CP_xy[index][i].Set_zeta_dev1(((*XYORD)/(caltBSP_XY->U_xy[index][i+*XYORD+1]-caltBSP_XY->U_xy[index][i+1]))*(CP_xy[index][i+1].Get_zeta()-CP_xy[index][i].Get_zeta()));		
		
		CPdev1x<<CP_xy[index][i].Get_ksi_dev1()<<" "<<CP_xy[index][i].Get_eta_dev1()<<" "<<CP_xy[index][i].Get_zeta_dev1()<<endl;
	}
	CaltMethod->create_Uni_Knot_Ver(*XYVER-1, *XYORD-1, caltBSP_XY->U_xy_dev[index], *XYVERARR-2);

	for(i=0;i<*XYVER-2;i++)
	{
		CP_xy[index][i].Set_ksi_dev2(((*XYORD-1)/(caltBSP_XY->U_xy_dev[index][i+*XYORD-1+1]-caltBSP_XY->U_xy_dev[index][i+1]))*(CP_xy[index][i+1].Get_ksi_dev1()-CP_xy[index][i].Get_ksi_dev1()));
		CP_xy[index][i].Set_eta_dev2(((*XYORD-1)/(caltBSP_XY->U_xy_dev[index][i+*XYORD-1+1]-caltBSP_XY->U_xy_dev[index][i+1]))*(CP_xy[index][i+1].Get_eta_dev1()-CP_xy[index][i].Get_eta_dev1()));		
		CP_xy[index][i].Set_zeta_dev2(((*XYORD-1)/(caltBSP_XY->U_xy_dev[index][i+*XYORD-1+1]-caltBSP_XY->U_xy_dev[index][i+1]))*(CP_xy[index][i+1].Get_zeta_dev1()-CP_xy[index][i].Get_zeta_dev1()));		
		
		CPdev2x<<CP_xy[index][i].Get_ksi_dev2()<<" "<<CP_xy[index][i].Get_eta_dev2()<<" "<<CP_xy[index][i].Get_zeta_dev2()<<endl;
	}
	
	temp_x = new double;
	temp_y = new double;
	temp_z = new double;
	
	temp_x_dev1 = new double;
	temp_y_dev1 = new double;
	temp_z_dev1 = new double;
		
	temp_x_dev2 = new double;
	temp_y_dev2 = new double;
	temp_z_dev2 = new double;
	
	//...XY...Bspline...normal vector...kslope
	for(n=0;n<*XYNUM;n++)
	{	
		*temp_x = 0.0;
		*temp_y = 0.0;
		*temp_z = 0.0;
		
		*temp_x_dev1 = 0.0;
		*temp_y_dev1 = 0.0;
		*temp_z_dev1 = 0.0;
		
		*temp_x_dev2 = 0.0;
		*temp_y_dev2 = 0.0;
		*temp_z_dev2 = 0.0;

		for(cot=0;cot<*XYVER;cot++)
		{
			*temp_x += CP_xy[index][cot].Get_ksi() * caltBSP_XY->N_sig_xy[n][cot];
			*temp_y += CP_xy[index][cot].Get_eta() * caltBSP_XY->N_sig_xy[n][cot];
			*temp_z += CP_xy[index][cot].Get_zeta() * caltBSP_XY->N_sig_xy[n][cot];
		}
		
		for(cot=0;cot<*XYVER-1;cot++)
		{
			if(n==*XYNUM-1)
			{
				*temp_x_dev1 = CP_xy[index][*XYVER-2].Get_ksi_dev1();
				*temp_y_dev1 = CP_xy[index][*XYVER-2].Get_eta_dev1();
				*temp_z_dev1 = CP_xy[index][*XYVER-2].Get_zeta_dev1();
			}
			else if(n==0)
			{
				*temp_x_dev1 = CP_xy[index][0].Get_ksi_dev1();
				*temp_y_dev1 = CP_xy[index][0].Get_eta_dev1();
				*temp_z_dev1 = CP_xy[index][0].Get_zeta_dev1();
			}
			else
			{
				*temp_x_dev1 += CP_xy[index][cot].Get_ksi_dev1() * caltBSP_XY->N_sig_dev_1_xy[n][cot];
				*temp_y_dev1 += CP_xy[index][cot].Get_eta_dev1() * caltBSP_XY->N_sig_dev_1_xy[n][cot];
				*temp_z_dev1 += CP_xy[index][cot].Get_zeta_dev1() * caltBSP_XY->N_sig_dev_1_xy[n][cot];
			}
		}
		
		for(cot=0;cot<*XYVER-2;cot++)
		{
			if(n==*XYNUM-1)
			{
				*temp_x_dev2 = CP_xy[index][*XYVER-3].Get_ksi_dev2();
				*temp_y_dev2 = CP_xy[index][*XYVER-3].Get_eta_dev2();
				*temp_z_dev2 = CP_xy[index][*XYVER-3].Get_zeta_dev2();
			}
			else if(n==0)
			{
				*temp_x_dev2 = CP_xy[index][0].Get_ksi_dev2();
				*temp_y_dev2 = CP_xy[index][0].Get_eta_dev2();
				*temp_z_dev2 = CP_xy[index][0].Get_zeta_dev2();
			}
			else
			{
				*temp_x_dev2 += CP_xy[index][cot].Get_ksi_dev2() * caltBSP_XY->N_sig_dev_2_xy[n][cot];
				*temp_y_dev2 += CP_xy[index][cot].Get_eta_dev2() * caltBSP_XY->N_sig_dev_2_xy[n][cot];
				*temp_z_dev2 += CP_xy[index][cot].Get_zeta_dev2() * caltBSP_XY->N_sig_dev_2_xy[n][cot];
			}
		}

		BSPL_xy->x[index][n] = *temp_x;
		BSPL_xy->y[index][n] = *temp_y;
		BSPL_xy->z[index][n] = *temp_z;

		BSPL_xy->x_dev1[index][n] = *temp_x_dev1;
		BSPL_xy->y_dev1[index][n] = *temp_y_dev1;
		BSPL_xy->z_dev1[index][n] = *temp_z_dev1;

		BSPL_xy->x_dev2[index][n] = *temp_x_dev2;
		BSPL_xy->y_dev2[index][n] = *temp_y_dev2;
		BSPL_xy->z_dev2[index][n] = *temp_z_dev2;
	
		BSPL_xy->nx_xy[index][n] = CaltMethod->cacu_nx(BSPL_xy->x_dev1[index][n], BSPL_xy->y_dev1[index][n]);
		BSPL_xy->ny_xy[index][n] = CaltMethod->cacu_ny(BSPL_xy->x_dev1[index][n], BSPL_xy->y_dev1[index][n]);

		BSPL_xy->kslope_xy[index][n] = CaltMethod->cacu_kslope(BSPL_xy->x_dev1[index][n], BSPL_xy->y_dev1[index][n], BSPL_xy->x_dev2[index][n], BSPL_xy->y_dev2[index][n]);

		Bsplinex<<BSPL_xy->x[index][n]<<" "<<BSPL_xy->y[index][n]<<" "<<BSPL_xy->z[index][n]<<endl;
		Bsplinedev1x<<BSPL_xy->x_dev1[index][n]<<" "<<BSPL_xy->y_dev1[index][n]<<" "<<BSPL_xy->z_dev1[index][n]<<endl;
		Bsplinedev2x<<BSPL_xy->x_dev2[index][n]<<" "<<BSPL_xy->y_dev2[index][n]<<" "<<BSPL_xy->z_dev2[index][n]<<endl;
		nxyx<<BSPL_xy->nx_xy[index][n]<<" "<<BSPL_xy->ny_xy[index][n]<<endl;
		Bsplinenxnyx<<"zone t=\"nxy\""<<endl;
		Bsplinenxnyx<<BSPL_xy->x[index][n]<<" "<<BSPL_xy->y[index][n]<<" "<<BSPL_xy->z[index][n]<<endl;
		Bsplinenxnyx<<BSPL_xy->x[index][n]+BSPL_xy->nx_xy[index][n]<<" "<<BSPL_xy->y[index][n]+BSPL_xy->ny_xy[index][n]<<" "<<BSPL_xy->z[index][n]<<endl;
		Kslopex<<"zone t=\"kslope\""<<endl;
		Kslopex<<BSPL_xy->x[index][n]<<" "<<BSPL_xy->y[index][n]<<" "<<BSPL_xy->z[index][n]<<endl;
		Kslopex<<BSPL_xy->x[index][n]+BSPL_xy->nx_xy[index][n]*BSPL_xy->kslope_xy[index][n]*rad<<" "<<BSPL_xy->y[index][n]+BSPL_xy->ny_xy[index][n]*BSPL_xy->kslope_xy[index][n]*rad<<" "<<BSPL_xy->z[index][n]<<endl;
	}
	
	delete temp_x; delete temp_y; delete temp_z;
	delete temp_x_dev1; delete temp_y_dev1; delete temp_z_dev1;*/
}

int main(void)
{

//////////////////////////////////Calculate BP////////////////////////////////////
	Init_Num_Ord();	
	Init_Method();
	Init_BP_XY();

	CALT_CP_XY();

	CALT_BSPLINE_XY();

	return 0;
}
