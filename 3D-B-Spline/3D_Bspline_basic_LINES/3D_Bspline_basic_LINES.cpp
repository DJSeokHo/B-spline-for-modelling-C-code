#include "3D_Bspline_Basic_LINES.h"

//...Out Put X-Y, Y-Z, X-Z
int *XYLINE, *YZLINE, *XZLINE;	
int *XYBP, *YZBP, *XZBP;
int *XYVER, *YZVER, *XZVER;
int *XYORD, *YZORD, *XZORD;
int *XYBPARR, *YZBPARR, *XZBPARR;
int *XYVERARR, *YZVERARR, *XZVERARR;
int *XYNUM, *YZNUM, *XZNUM;
int cacl_KV;

//...Init X-Y, Y-Z, X-Z malloc
BP **BP_xy, **BP_yz, **BP_xz;
CP **CP_xy, **CP_yz, **CP_xz;


CALT_MTHOD *CaltMethod;

CALTCP_XY *caltCP_XY;
CALTCP_YZ *caltCP_YZ;
CALTCP_XZ *caltCP_XZ;

CALTBSPLINE_XY *caltBSP_XY;
CALTBSPLINE_YZ *caltBSP_YZ;
CALTBSPLINE_XZ *caltBSP_XZ;

void Init_Num_Ord()
{
	XYLINE=new int; YZLINE=new int; XZLINE=new int;
	XYBP=new int; YZBP=new int; XZBP=new int;
	XYVER=new int; YZVER=new int; XZVER=new int;
	XYORD=new int; YZORD=new int; XZORD=new int;
	XYBPARR=new int; YZBPARR=new int; XZBPARR=new int;
	XYVERARR=new int; YZVERARR=new int; XZVERARR=new int;
	XYNUM=new int; YZNUM=new int; XZNUM=new int;

	//...Init Num Ord
	*XYLINE = 1;				//...Number of X-Y Line
	*YZLINE  = 1;				//...Number of Y-Z Line
	*XZLINE  = 1;				//...Number of X-Z Line

	*XYBP  = 11;
	*YZBP  = 13;
	*XZBP  = 15;
	
	*XYVER = *XYBP;
	*YZVER = *YZBP;
	*XZVER = *XZBP;

	*XYORD = 3;
	*YZORD = 3;
	*XZORD = 3;

	*XYNUM = 81;
	*YZNUM = 101;
	*XZNUM = 121;

	*XYVERARR = *XYORD + *XYVER;
	*YZVERARR = *YZORD + *YZVER;
	*XZVERARR = *XZORD + *XZVER;

	*XYBPARR = *XYORD + *XYBP;
	*YZBPARR = *YZORD + *YZBP;
	*XZBPARR = *XZORD + *XZBP;
}

void Init_Method()
{
	CaltMethod = new CALT_MTHOD;
}

void Init_BP_XY()
{
	int index, i;
	BP_xy = new BP*[*XYLINE];
	for(index=0;index<*XYLINE;index++)
	{
		BP_xy[index] = new BP[*XYBP];
	}
	ofstream BPx;
	BPx.open("BPx.dat");
	for(index=0;index<*XYLINE;index++)
	{	
		BPx<<"zone t=\"BPx\""<<endl;
		double *anglexy = new double;
		*anglexy = 0.0;
		for(i=0;i<*XYBP;i++)								//init the cycle							
		{																	
			BP_xy[index][i].Set_x(1.0*cos(CaltMethod->ang_to_rad(*anglexy)));									
			BP_xy[index][i].Set_y(1.0*sin(CaltMethod->ang_to_rad(*anglexy)));
			BP_xy[index][i].Set_z(0);
			*anglexy += 360.0 / (*XYBP-1);
			BPx<<BP_xy[index][i].Get_x()<<" "<<BP_xy[index][i].Get_y()<<" "<<BP_xy[index][i].Get_z()<<endl;
		}		
		delete anglexy;
	}
	BPx.close();
}

void Init_BP_YZ()
{
	int index, i;
	BP_yz = new BP*[*YZLINE];
	for(index=0;index<*YZLINE;index++)
	{
		BP_yz[index] = new BP[*YZBP];
	}
	ofstream BPy;
	BPy.open("BPy.dat");
	for(index=0;index<*YZLINE;index++)
	{
		BPy<<"zone t=\"BPy\""<<endl;
		double *angleyz = new double;
		angleyz = new double;
		*angleyz = 0.0;
		for(i=0;i<*YZBP;i++)								//init the cycle							
		{																	
			BP_yz[index][i].Set_x(0);									
			BP_yz[index][i].Set_y(2.0*cos(CaltMethod->ang_to_rad(*angleyz)));
			BP_yz[index][i].Set_z(2.0*sin(CaltMethod->ang_to_rad(*angleyz)));
			*angleyz += 360.0 / (*YZBP-1);
			BPy<<BP_yz[index][i].Get_x()<<" "<<BP_yz[index][i].Get_y()<<" "<<BP_yz[index][i].Get_z()<<endl;
		}		
		delete angleyz;
	}
	BPy.close();
}

void Init_BP_XZ()
{
	int index, i;
	BP_xz = new BP*[*XZLINE];
	for(index=0;index<*XZLINE;index++)
	{
		BP_xz[index] = new BP[*XZBP];
	}
	ofstream BPz;
	BPz.open("BPz.dat");
	for(index=0;index<*XZLINE;index++)
	{
		BPz<<"zone t=\"BPz\""<<endl;
		double *anglexz = new double;
		*anglexz = 0.0;
		for(i=0;i<*XZBP;i++)								//init the cycle							
		{																	
			BP_xz[index][i].Set_x(3.0*cos(CaltMethod->ang_to_rad(*anglexz)));									
			BP_xz[index][i].Set_y(0);
			BP_xz[index][i].Set_z(3.0*sin(CaltMethod->ang_to_rad(*anglexz)));
			*anglexz += 360.0 / (*XZBP-1);
			BPz<<BP_xz[index][i].Get_x()<<" "<<BP_xz[index][i].Get_y()<<" "<<BP_xz[index][i].Get_z()<<endl;
		}		
		delete anglexz;
	}
	BPz.close();
}

void CALT_CP_XY()
{
	int index, i;
	CP_xy = new CP*[*XYLINE];
	for(index=0;index<*XYLINE;index++)
	{
		CP_xy[index] = new CP[*XYBP];
	}
	caltCP_XY = new CALTCP_XY;
	caltCP_XY->Init_N(*XYORD, *XYBP);
	caltCP_XY->Init_U(*XYLINE, *XYVERARR); 

	ofstream BP_snx;
	BP_snx.open("BP_snx.dat");
	ofstream BP_unx;
	BP_unx.open("BP_unx.dat");
	for(index=0;index<*XYLINE;index++)
	{
		BP_snx<<"zone t=\"BP_sn\""<<endl;
		BP_unx<<"zone t=\"BP_un\""<<endl;
		for(i=0;i<*XYBP;i++)
		{
			if(i==0)
			{
				BP_xy[index][i].Set_BP_sn(0.0);
			}
			else
			{
				BP_xy[index][i].Set_BP_sn(CaltMethod->cacu_BP_sn(BP_xy[index][i-1].Get_BP_sn(), BP_xy[index][i].Get_x(), BP_xy[index][i-1].Get_x(), BP_xy[index][i].Get_y(), BP_xy[index][i-1].Get_y()));
			}
			BP_snx<<BP_xy[index][i].Get_BP_sn()<<endl;
		}
		for(i=0;i<*XYBP;i++)
		{
			BP_xy[index][i].Set_BP_un(CaltMethod->cacu_BP_un(BP_xy[index][*XYBP-1].Get_BP_sn(), BP_xy[index][i].Get_BP_sn(),*XYORD,*XYBP));
			BP_unx<<BP_xy[index][i].Get_BP_un()<<endl;
		}

		CaltMethod->create_Uni_Knot_Ver(&cacl_KV, *XYBP, *XYORD, caltCP_XY->U_xy[index], *XYBPARR);
	}
	BP_snx.close();
	BP_unx.close();
	//...Calculate Basic Function N and Control Point
	ofstream uNBPx;
	uNBPx.open("uNBPx.dat");
	ofstream CPx;
	CPx.open("CPx.dat");

	int cout, n, j, k;
	for(index=0;index<*XYLINE;index++)
	{
		CPx<<"zone t=\"CP\""<<endl;
		for(cout=0;cout<*XYBP;cout++)
		{
			uNBPx<<"zone t=\"uNBP\""<<endl;
			for(n=0;n<*XYBP;n++)
			{
				uNBPx<<BP_xy[index][n].Get_BP_un()<<" ";
				for(k=0;k<=*XYORD;k++)
				{	
					for(i=0;i<*XYBP;i++)
					{	
						if(k==0)
						{
							if(BP_xy[index][n].Get_BP_un()>=caltCP_XY->U_xy[index][i] && BP_xy[index][n].Get_BP_un()<caltCP_XY->U_xy[index][i+1])
							{
								caltCP_XY->BP_N_xy[k][i] = 1.0;
							}
							else
							{
								caltCP_XY->BP_N_xy[k][i] = 0.0;
							}
						}
						else if(k==*XYORD&&n==*XYBP-1&&i==*XYBP-1)
						{
							caltCP_XY->BP_N_xy[k][i] = 1.0;				
						}
						else
						{
							caltCP_XY->BP_N_xy[k][i] = CaltMethod->cacu_Nki(BP_xy[index][n].Get_BP_un(), caltCP_XY->U_xy[index][i], caltCP_XY->BP_N_xy[k-1][i], caltCP_XY->U_xy[index][i+k], caltCP_XY->BP_N_xy[k-1][i+1], caltCP_XY->U_xy[index][i+k+1], caltCP_XY->U_xy[index][i+1]);
						}
					}
					if(k==*XYORD)
					{				
						caltCP_XY->temp_BP_N_xy[n][cout] = caltCP_XY->BP_N_xy[*XYORD][cout];
						uNBPx<<caltCP_XY->BP_N_xy[*XYORD][cout]<<endl;
					}
				}
			}
		}
		
		CaltMethod->matrix_inversion_using_elementary_operation(caltCP_XY->temp_BP_N_xy,caltCP_XY->inv_temp_BP_N_xy,*XYBP);
		
		for(i=0;i<*XYBP;i++)
		{
			double *temp_x = new double;
			double *temp_y = new double;
			double *temp_z = new double;
			*temp_x=0.0; *temp_y=0.0; *temp_z=0.0;
			for(j=0;j<*XYBP;j++)
			{
				*temp_x += caltCP_XY->inv_temp_BP_N_xy[i][j] * BP_xy[index][j].Get_x();
				*temp_y += caltCP_XY->inv_temp_BP_N_xy[i][j] * BP_xy[index][j].Get_y();
				*temp_z += caltCP_XY->inv_temp_BP_N_xy[i][j] * BP_xy[index][j].Get_z();
			}
			CP_xy[index][i].Set_ksi(*temp_x);
			CP_xy[index][i].Set_eta(*temp_y);
			CP_xy[index][i].Set_zeta(*temp_z);
			delete temp_x; delete temp_y; delete temp_z;
		}

		for(i=0;i<*XYVER;i++)
		{
			CPx<<CP_xy[index][i].Get_ksi()<<" "<<CP_xy[index][i].Get_eta()<<" "<<CP_xy[index][i].Get_zeta()<<endl;
		}
	}
	uNBPx.close();
	CPx.close();
}

void CALT_CP_YZ()
{
	int index, i;
	CP_yz = new CP*[*YZLINE];
	for(index=0;index<*YZLINE;index++)
	{
		CP_yz[index] = new CP[*YZBP];
	}
	caltCP_YZ = new CALTCP_YZ;
	caltCP_YZ->Init_N(*YZORD, *YZBP);
	caltCP_YZ->Init_U(*YZLINE, *YZVERARR); 

	ofstream BP_sny;
	BP_sny.open("BP_sny.dat");
	ofstream BP_uny;
	BP_uny.open("BP_uny.dat");
	for(index=0;index<*YZLINE;index++)
	{
		BP_sny<<"zone t=\"BP_sn\""<<endl;
		BP_uny<<"zone t=\"BP_un\""<<endl;
		for(i=0;i<*YZBP;i++)
		{
			if(i==0)
			{
				BP_yz[index][i].Set_BP_sn(0.0);
			}
			else
			{
				BP_yz[index][i].Set_BP_sn(CaltMethod->cacu_BP_sn(BP_yz[index][i-1].Get_BP_sn(), BP_yz[index][i].Get_y(), BP_yz[index][i-1].Get_y(), BP_yz[index][i].Get_z(), BP_yz[index][i-1].Get_z()));
			}
			BP_sny<<BP_yz[index][i].Get_BP_sn()<<endl;
		}
		for(i=0;i<*YZBP;i++)
		{
			BP_yz[index][i].Set_BP_un(CaltMethod->cacu_BP_un(BP_yz[index][*YZBP-1].Get_BP_sn(), BP_yz[index][i].Get_BP_sn(),*YZORD,*YZBP));
			BP_uny<<BP_yz[index][i].Get_BP_un()<<endl;
		}

		CaltMethod->create_Uni_Knot_Ver(&cacl_KV, *YZBP, *YZORD, caltCP_YZ->U_yz[index], *YZBPARR);
	}
	
	BP_sny.close();
	BP_uny.close();

	//...Calculate Basic Function N and Control Point
	ofstream uNBPy;
	uNBPy.open("uNBPy.dat");
	ofstream CPy;
	CPy.open("CPy.dat");

	int cout, n, j, k;
	for(index=0;index<*YZLINE;index++)
	{
		CPy<<"zone t=\"CP\""<<endl;
		for(cout=0;cout<*YZBP;cout++)
		{
			uNBPy<<"zone t=\"uNBP\""<<endl;
			for(n=0;n<*YZBP;n++)
			{
				uNBPy<<BP_yz[index][n].Get_BP_un()<<" ";
				for(k=0;k<=*YZORD;k++)
				{	
					for(i=0;i<*YZBP;i++)
					{	
						if(k==0)
						{
							if(BP_yz[index][n].Get_BP_un()>=caltCP_YZ->U_yz[index][i] && BP_yz[index][n].Get_BP_un()<caltCP_YZ->U_yz[index][i+1])
							{
								caltCP_YZ->BP_N_yz[k][i] = 1.0;
							}
							else
							{
								caltCP_YZ->BP_N_yz[k][i] = 0.0;
							}
						}
						else if(k==*YZORD&&n==*YZBP-1&&i==*YZBP-1)
						{
							caltCP_YZ->BP_N_yz[k][i] = 1.0;				
						}
						else
						{
							caltCP_YZ->BP_N_yz[k][i] = CaltMethod->cacu_Nki(BP_yz[index][n].Get_BP_un(), caltCP_YZ->U_yz[index][i], caltCP_YZ->BP_N_yz[k-1][i], caltCP_YZ->U_yz[index][i+k], caltCP_YZ->BP_N_yz[k-1][i+1], caltCP_YZ->U_yz[index][i+k+1], caltCP_YZ->U_yz[index][i+1]);
						}
					}
					if(k==*YZORD)
					{				
						caltCP_YZ->temp_BP_N_yz[n][cout] = caltCP_YZ->BP_N_yz[*YZORD][cout];
						uNBPy<<caltCP_YZ->BP_N_yz[*YZORD][cout]<<endl;
					}
				}
			}
		}
		
		CaltMethod->matrix_inversion_using_elementary_operation(caltCP_YZ->temp_BP_N_yz,caltCP_YZ->inv_temp_BP_N_yz,*YZBP);
		
		for(i=0;i<*YZBP;i++)
		{
			double *temp_x = new double;
			double *temp_y = new double;
			double *temp_z = new double;
			*temp_x=0.0; *temp_y=0.0; *temp_z=0.0;
			for(j=0;j<*YZBP;j++)
			{
				*temp_x += caltCP_YZ->inv_temp_BP_N_yz[i][j] * BP_yz[index][j].Get_x();
				*temp_y += caltCP_YZ->inv_temp_BP_N_yz[i][j] * BP_yz[index][j].Get_y();
				*temp_z += caltCP_YZ->inv_temp_BP_N_yz[i][j] * BP_yz[index][j].Get_z();
			}
			CP_yz[index][i].Set_ksi(*temp_x);
			CP_yz[index][i].Set_eta(*temp_y);
			CP_yz[index][i].Set_zeta(*temp_z);
			delete temp_x; delete temp_y; delete temp_z;
		}

		for(i=0;i<*YZVER;i++)
		{
			CPy<<CP_yz[index][i].Get_ksi()<<" "<<CP_yz[index][i].Get_eta()<<" "<<CP_yz[index][i].Get_zeta()<<endl;
		}
	}
	uNBPy.close();
	CPy.close();
}

void CALT_CP_XZ()
{
	int index, i;
	CP_xz = new CP*[*XZLINE];
	for(index=0;index<*XZLINE;index++)
	{
		CP_xz[index] = new CP[*XZBP];
	}
	caltCP_XZ = new CALTCP_XZ;
	caltCP_XZ->Init_N(*XZORD, *XZBP);
	caltCP_XZ->Init_U(*XZLINE, *XZVERARR); 

	ofstream BP_snz;
	BP_snz.open("BP_snz.dat");
	ofstream BP_unz;
	BP_unz.open("BP_unz.dat");
	for(index=0;index<*XZLINE;index++)
	{
		BP_snz<<"zone t=\"BP_sn\""<<endl;
		BP_unz<<"zone t=\"BP_un\""<<endl;
		for(i=0;i<*XZBP;i++)
		{
			if(i==0)
			{
				BP_xz[index][i].Set_BP_sn(0.0);
			}
			else
			{
				BP_xz[index][i].Set_BP_sn(CaltMethod->cacu_BP_sn(BP_xz[index][i-1].Get_BP_sn(), BP_xz[index][i].Get_x(), BP_xz[index][i-1].Get_x(), BP_xz[index][i].Get_z(), BP_xz[index][i-1].Get_z()));
			}
			BP_snz<<BP_xz[index][i].Get_BP_sn()<<endl;
		}
		for(i=0;i<*XZBP;i++)
		{
			BP_xz[index][i].Set_BP_un(CaltMethod->cacu_BP_un(BP_xz[index][*XZBP-1].Get_BP_sn(), BP_xz[index][i].Get_BP_sn(),*XZORD,*XZBP));
			BP_unz<<BP_xz[index][i].Get_BP_un()<<endl;
		}

		CaltMethod->create_Uni_Knot_Ver(&cacl_KV, *XZBP, *XZORD, caltCP_XZ->U_xz[index], *XZBPARR);
	}
	BP_snz.close();
	BP_unz.close();
	//...Calculate Basic Function N and Control Point
	ofstream uNBPz;
	uNBPz.open("uNBPz.dat");
	ofstream CPz;
	CPz.open("CPz.dat");

	int cout, n, j, k;	
	for(index=0;index<*XZLINE;index++)
	{
		CPz<<"zone t=\"CP\""<<endl;
		for(cout=0;cout<*XZBP;cout++)
		{
			uNBPz<<"zone t=\"uNBP\""<<endl;
			for(n=0;n<*XZBP;n++)
			{
				uNBPz<<BP_xz[index][n].Get_BP_un()<<" ";
				for(k=0;k<=*XZORD;k++)
				{	
					for(i=0;i<*XZBP;i++)
					{	
						if(k==0)
						{
							if(BP_xz[index][n].Get_BP_un()>=caltCP_XZ->U_xz[index][i] && BP_xz[index][n].Get_BP_un()<caltCP_XZ->U_xz[index][i+1])
							{
								caltCP_XZ->BP_N_xz[k][i] = 1.0;
							}
							else
							{
								caltCP_XZ->BP_N_xz[k][i] = 0.0;
							}
						}
						else if(k==*XZORD&&n==*XZBP-1&&i==*XZBP-1)
						{
							caltCP_XZ->BP_N_xz[k][i] = 1.0;				
						}
						else
						{
							caltCP_XZ->BP_N_xz[k][i] = CaltMethod->cacu_Nki(BP_xz[index][n].Get_BP_un(), caltCP_XZ->U_xz[index][i], caltCP_XZ->BP_N_xz[k-1][i], caltCP_XZ->U_xz[index][i+k], caltCP_XZ->BP_N_xz[k-1][i+1], caltCP_XZ->U_xz[index][i+k+1], caltCP_XZ->U_xz[index][i+1]);
						}
					}
					if(k==*XZORD)
					{				
						caltCP_XZ->temp_BP_N_xz[n][cout] = caltCP_XZ->BP_N_xz[*XZORD][cout];
						uNBPz<<caltCP_XZ->BP_N_xz[*XZORD][cout]<<endl;
					}
				}
			}
		}
		
		CaltMethod->matrix_inversion_using_elementary_operation(caltCP_XZ->temp_BP_N_xz,caltCP_XZ->inv_temp_BP_N_xz,*XZBP);
		
		for(i=0;i<*XZBP;i++)
		{
			double *temp_x = new double;
			double *temp_y = new double;
			double *temp_z = new double;
			*temp_x=0.0; *temp_y=0.0; *temp_z=0.0;
			for(j=0;j<*XZBP;j++)
			{
				*temp_x += caltCP_XZ->inv_temp_BP_N_xz[i][j] * BP_xz[index][j].Get_x();
				*temp_y += caltCP_XZ->inv_temp_BP_N_xz[i][j] * BP_xz[index][j].Get_y();
				*temp_z += caltCP_XZ->inv_temp_BP_N_xz[i][j] * BP_xz[index][j].Get_z();
			}
			CP_xz[index][i].Set_ksi(*temp_x);
			CP_xz[index][i].Set_eta(*temp_y);
			CP_xz[index][i].Set_zeta(*temp_z);
			delete temp_x; delete temp_y; delete temp_z;
		}

		for(i=0;i<*XZVER;i++)
		{
			CPz<<CP_xz[index][i].Get_ksi()<<" "<<CP_xz[index][i].Get_eta()<<" "<<CP_xz[index][i].Get_zeta()<<endl;
		}
	}
	uNBPz.close();
	CPz.close();
}

void CALT_BSPLINE_XY()
{
	//...Calculate basic function N Ndev1 Ndev2
	int index, i, cout, n, k, uNt, cot;
	index = 0;
		
	BSPLINE_XY *BSPL_xy;
	BSPL_xy = new BSPLINE_XY;
	caltBSP_XY = new CALTBSPLINE_XY;

	BSPL_xy->Init(*XYLINE, *XYNUM);
	caltBSP_XY->Init_U(*XYLINE, *XYVERARR);
	caltBSP_XY->Init_N(*XYORD, *XYVER, *XYNUM);
	caltBSP_XY->Init_U_dev(*XYLINE, *XYVERARR-2);

	CaltMethod->create_Uni_Knot_Ver(&cacl_KV, *XYVER, *XYORD, caltBSP_XY->U_xy[index], *XYVERARR);

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
	
	double *temp_x, *temp_y, *temp_z;
	double *temp_x_dev1, *temp_y_dev1, *temp_z_dev1;
	double *temp_x_dev2, *temp_y_dev2, *temp_z_dev2;

	//...XYZ... u spn U
	for(i=0;i<*XYNUM;i++)
	{
		caltBSP_XY->u_xy[i] = (double)i/10.0;
	}

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
	CaltMethod->create_Uni_Knot_Ver(&cacl_KV, *XYVER-1, *XYORD-1, caltBSP_XY->U_xy_dev[index], *XYVERARR-2);

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
	delete temp_x_dev1; delete temp_y_dev1; delete temp_z_dev1;
}

void CALT_BSPLINE_YZ()
{
		//...Calculate basic function N Ndev1 Ndev2
	int index, i, cout, n, k, uNt, cot;
	index = 0;
		
	BSPLINE_YZ *BSPL_yz;
	BSPL_yz = new BSPLINE_YZ;
	caltBSP_YZ = new CALTBSPLINE_YZ;

	BSPL_yz->Init(*YZLINE, *YZNUM);
	caltBSP_YZ->Init_U(*YZLINE, *YZVERARR);
	caltBSP_YZ->Init_N(*YZORD, *YZVER, *YZNUM);
	caltBSP_YZ->Init_U_dev(*YZLINE, *YZVERARR-2);

	CaltMethod->create_Uni_Knot_Ver(&cacl_KV, *YZVER, *YZORD, caltBSP_YZ->U_yz[index], *YZVERARR);

	ofstream uNy, uNdev1y, uNdev2y;
	uNy.open("uNy.dat");
	uNdev1y.open("uNdev1y.dat");
	uNdev2y.open("uNdev2y.dat");
		
	ofstream CPdev1y;
	CPdev1y.open("CPdev1y.dat");
	ofstream CPdev2y;
	CPdev2y.open("CPdev2y.dat");
	
	ofstream Bspliney;
	Bspliney.open("Bspliney.dat");
	ofstream Bsplinedev1y;
	Bsplinedev1y.open("Bsplinedev1y.dat");
	ofstream Bsplinedev2y;
	Bsplinedev2y.open("Bsplinedev2y.dat");
	ofstream nxyy;
	nxyy.open("nxyy.dat");
	ofstream Bsplinenxnyy;
	Bsplinenxnyy.open("Bsplinenxnyy.dat");
	ofstream Kslopey;
	Kslopey.open("Kslopey.dat");
	
	double *temp_x, *temp_y, *temp_z;
	double *temp_x_dev1, *temp_y_dev1, *temp_z_dev1;
	double *temp_x_dev2, *temp_y_dev2, *temp_z_dev2;

	//...XYZ... u spn U
	for(i=0;i<*YZNUM;i++)
	{
		caltBSP_YZ->u_yz[i] = (double)i/10.0;
	}

////////////////////////////////////////////////////////////////////////////////
	
	//...YZ...N
	for(cout=0;cout<*YZVER;cout++)
	{
		uNy<<"zone t=\"uN\""<<endl;
		uNdev1y<<"zone t=\"uNdev1\""<<endl;
		uNdev2y<<"zone t=\"uNdev2\""<<endl;
		for(n=0;n<*YZNUM;n++)
		{
			uNy<<caltBSP_YZ->u_yz[n]<<" ";
			uNdev1y<<caltBSP_YZ->u_yz[n]<<" ";
			uNdev2y<<caltBSP_YZ->u_yz[n]<<" ";
			for(k=0;k<=*YZORD;k++)
			{	
				for(i=0;i<*YZVER;i++)
				{	
					if(k==0)
					{
						if(caltBSP_YZ->u_yz[n]>=caltBSP_YZ->U_yz[index][i] && caltBSP_YZ->u_yz[n]<caltBSP_YZ->U_yz[index][i+1])
						{
							caltBSP_YZ->N_yz[k][i] = 1.0;
						}
						else
						{
							caltBSP_YZ->N_yz[k][i] = 0.0;
						}
					}
					else if(k==*YZORD&&n==*YZNUM-1&&i==*YZVER-1)
					{
						caltBSP_YZ->N_yz[k][i] = 1.0;				
					}
					else
					{
						caltBSP_YZ->N_yz[k][i]	= CaltMethod->cacu_Nki(caltBSP_YZ->u_yz[n], caltBSP_YZ->U_yz[index][i], caltBSP_YZ->N_yz[k-1][i], caltBSP_YZ->U_yz[index][i+k], caltBSP_YZ->N_yz[k-1][i+1], caltBSP_YZ->U_yz[index][i+k+1], caltBSP_YZ->U_yz[index][i+1]);
						caltBSP_YZ->N_dev1_yz[k][i] = CaltMethod->cacu_Nki_dev(k, caltBSP_YZ->U_yz[index][i], caltBSP_YZ->N_yz[k-1][i], caltBSP_YZ->U_yz[index][i+k], caltBSP_YZ->N_yz[k-1][i+1], caltBSP_YZ->U_yz[index][i+k+1], caltBSP_YZ->U_yz[index][i+1]);
						caltBSP_YZ->N_dev2_yz[k][i] = CaltMethod->cacu_Nki_dev(k, caltBSP_YZ->U_yz[index][i], caltBSP_YZ->N_dev1_yz[k-1][i], caltBSP_YZ->U_yz[index][i+k], caltBSP_YZ->N_dev1_yz[k-1][i+1], caltBSP_YZ->U_yz[index][i+k+1], caltBSP_YZ->U_yz[index][i+1]);
					}
				}
				if(k==*YZORD)
				{			
					if(n==0 && cout==0)
					{
						for(uNt=0;uNt<2;uNt++)
						{
							caltBSP_YZ->uN_temp_dev1[uNt] = caltBSP_YZ->N_dev1_yz[*YZORD][uNt];
						}
					}
					for(uNt=0;uNt<2;uNt++)
					{
						if(n==*YZNUM-1 && cout == *YZVER - (uNt + 1))
						{
							caltBSP_YZ->N_dev1_yz[*YZORD][*YZVER - (uNt + 1)] = caltBSP_YZ->uN_temp_dev1[1 - uNt];
						}
					}

					if(n==0 && cout==0)
					{
						for(uNt=0;uNt<3;uNt++)
						{
							caltBSP_YZ->uN_temp_dev2[uNt] = caltBSP_YZ->N_dev2_yz[*YZORD][uNt];
						}
					}
					for(uNt=0;uNt<3;uNt++)
					{
						if(n==*YZNUM-1 && cout == *YZVER - (uNt + 1))
						{
							caltBSP_YZ->N_dev2_yz[*YZORD][*YZVER - (uNt + 1)] = caltBSP_YZ->uN_temp_dev2[uNt];
						}
					}

					uNy<<caltBSP_YZ->N_yz[*YZORD][cout]<<endl;
					uNdev1y<<caltBSP_YZ->N_dev1_yz[*YZORD][cout]<<endl;
					uNdev2y<<caltBSP_YZ->N_dev2_yz[*YZORD][cout]<<endl;

					caltBSP_YZ->N_sig_yz[n][cout] = caltBSP_YZ->N_yz[*YZORD][cout];
					caltBSP_YZ->N_sig_dev_1_yz[n][cout] = caltBSP_YZ->N_yz[*YZORD-1][cout+1];		//dev 1 importent,this is right
					caltBSP_YZ->N_sig_dev_2_yz[n][cout] = caltBSP_YZ->N_yz[*YZORD-2][cout+2];		//dev 2 importent,this is right
				}
			}
		}
	}
	
	//...YZ...CP...dev
	for(i=0;i<*YZVER-1;i++)
	{		
		CP_yz[index][i].Set_ksi_dev1(((*YZORD)/(caltBSP_YZ->U_yz[index][i+*YZORD+1]-caltBSP_YZ->U_yz[index][i+1]))*(CP_yz[index][i+1].Get_ksi()-CP_yz[index][i].Get_ksi()));
		CP_yz[index][i].Set_eta_dev1(((*YZORD)/(caltBSP_YZ->U_yz[index][i+*YZORD+1]-caltBSP_YZ->U_yz[index][i+1]))*(CP_yz[index][i+1].Get_eta()-CP_yz[index][i].Get_eta()));		
		CP_yz[index][i].Set_zeta_dev1(((*YZORD)/(caltBSP_YZ->U_yz[index][i+*YZORD+1]-caltBSP_YZ->U_yz[index][i+1]))*(CP_yz[index][i+1].Get_zeta()-CP_yz[index][i].Get_zeta()));		
		
		CPdev1y<<CP_yz[index][i].Get_ksi_dev1()<<" "<<CP_yz[index][i].Get_eta_dev1()<<" "<<CP_yz[index][i].Get_zeta_dev1()<<endl;
	}
	CaltMethod->create_Uni_Knot_Ver(&cacl_KV, *YZVER-1, *YZORD-1, caltBSP_YZ->U_yz_dev[index], *YZVERARR-2);

	for(i=0;i<*YZVER-2;i++)
	{
		CP_yz[index][i].Set_ksi_dev2(((*YZORD-1)/(caltBSP_YZ->U_yz_dev[index][i+*YZORD-1+1]-caltBSP_YZ->U_yz_dev[index][i+1]))*(CP_yz[index][i+1].Get_ksi_dev1()-CP_yz[index][i].Get_ksi_dev1()));
		CP_yz[index][i].Set_eta_dev2(((*YZORD-1)/(caltBSP_YZ->U_yz_dev[index][i+*YZORD-1+1]-caltBSP_YZ->U_yz_dev[index][i+1]))*(CP_yz[index][i+1].Get_eta_dev1()-CP_yz[index][i].Get_eta_dev1()));		
		CP_yz[index][i].Set_zeta_dev2(((*YZORD-1)/(caltBSP_YZ->U_yz_dev[index][i+*YZORD-1+1]-caltBSP_YZ->U_yz_dev[index][i+1]))*(CP_yz[index][i+1].Get_zeta_dev1()-CP_yz[index][i].Get_zeta_dev1()));		
		
		CPdev2y<<CP_yz[index][i].Get_ksi_dev2()<<" "<<CP_yz[index][i].Get_eta_dev2()<<" "<<CP_yz[index][i].Get_zeta_dev2()<<endl;
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
	
	//...YZ...Bspline...normal vector...kslope
	for(n=0;n<*YZNUM;n++)
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

		for(cot=0;cot<*YZVER;cot++)
		{
			*temp_x += CP_yz[index][cot].Get_ksi() * caltBSP_YZ->N_sig_yz[n][cot];
			*temp_y += CP_yz[index][cot].Get_eta() * caltBSP_YZ->N_sig_yz[n][cot];
			*temp_z += CP_yz[index][cot].Get_zeta() * caltBSP_YZ->N_sig_yz[n][cot];
		}
		
		for(cot=0;cot<*YZVER-1;cot++)
		{
			if(n==*YZNUM-1)
			{
				*temp_x_dev1 = CP_yz[index][*YZVER-2].Get_ksi_dev1();
				*temp_y_dev1 = CP_yz[index][*YZVER-2].Get_eta_dev1();
				*temp_z_dev1 = CP_yz[index][*YZVER-2].Get_zeta_dev1();
			}
			else if(n==0)
			{
				*temp_x_dev1 = CP_yz[index][0].Get_ksi_dev1();
				*temp_y_dev1 = CP_yz[index][0].Get_eta_dev1();
				*temp_z_dev1 = CP_yz[index][0].Get_zeta_dev1();
			}
			else
			{
				*temp_x_dev1 += CP_yz[index][cot].Get_ksi_dev1() * caltBSP_YZ->N_sig_dev_1_yz[n][cot];
				*temp_y_dev1 += CP_yz[index][cot].Get_eta_dev1() * caltBSP_YZ->N_sig_dev_1_yz[n][cot];
				*temp_z_dev1 += CP_yz[index][cot].Get_zeta_dev1() * caltBSP_YZ->N_sig_dev_1_yz[n][cot];
			}
		}
		
		for(cot=0;cot<*YZVER-2;cot++)
		{
			if(n==*YZNUM-1)
			{
				*temp_x_dev2 = CP_yz[index][*YZVER-3].Get_ksi_dev2();
				*temp_y_dev2 = CP_yz[index][*YZVER-3].Get_eta_dev2();
				*temp_z_dev2 = CP_yz[index][*YZVER-3].Get_zeta_dev2();
			}
			else if(n==0)
			{
				*temp_x_dev2 = CP_yz[index][0].Get_ksi_dev2();
				*temp_y_dev2 = CP_yz[index][0].Get_eta_dev2();
				*temp_z_dev2 = CP_yz[index][0].Get_zeta_dev2();
			}
			else
			{
				*temp_x_dev2 += CP_yz[index][cot].Get_ksi_dev2() * caltBSP_YZ->N_sig_dev_2_yz[n][cot];
				*temp_y_dev2 += CP_yz[index][cot].Get_eta_dev2() * caltBSP_YZ->N_sig_dev_2_yz[n][cot];
				*temp_z_dev2 += CP_yz[index][cot].Get_zeta_dev2() * caltBSP_YZ->N_sig_dev_2_yz[n][cot];
			}
		}

		BSPL_yz->x[index][n] = *temp_x;
		BSPL_yz->y[index][n] = *temp_y;
		BSPL_yz->z[index][n] = *temp_z;

		BSPL_yz->x_dev1[index][n] = *temp_x_dev1;
		BSPL_yz->y_dev1[index][n] = *temp_y_dev1;
		BSPL_yz->z_dev1[index][n] = *temp_z_dev1;

		BSPL_yz->x_dev2[index][n] = *temp_x_dev2;
		BSPL_yz->y_dev2[index][n] = *temp_y_dev2;
		BSPL_yz->z_dev2[index][n] = *temp_z_dev2;
	
		BSPL_yz->nx_yz[index][n] = CaltMethod->cacu_nx(BSPL_yz->y_dev1[index][n], BSPL_yz->z_dev1[index][n]);
		BSPL_yz->ny_yz[index][n] = CaltMethod->cacu_ny(BSPL_yz->y_dev1[index][n], BSPL_yz->z_dev1[index][n]);

		BSPL_yz->kslope_yz[index][n] = CaltMethod->cacu_kslope(BSPL_yz->y_dev1[index][n], BSPL_yz->z_dev1[index][n], BSPL_yz->y_dev2[index][n], BSPL_yz->z_dev2[index][n]);

		Bspliney<<BSPL_yz->x[index][n]<<" "<<BSPL_yz->y[index][n]<<" "<<BSPL_yz->z[index][n]<<endl;
		Bsplinedev1y<<BSPL_yz->x_dev1[index][n]<<" "<<BSPL_yz->y_dev1[index][n]<<" "<<BSPL_yz->z_dev1[index][n]<<endl;
		Bsplinedev2y<<BSPL_yz->x_dev2[index][n]<<" "<<BSPL_yz->y_dev2[index][n]<<" "<<BSPL_yz->z_dev2[index][n]<<endl;
		nxyy<<BSPL_yz->nx_yz[index][n]<<" "<<BSPL_yz->ny_yz[index][n]<<endl;
		Bsplinenxnyy<<"zone t=\"nxy\""<<endl;
		Bsplinenxnyy<<BSPL_yz->x[index][n]<<" "<<BSPL_yz->y[index][n]<<" "<<BSPL_yz->z[index][n]<<endl;
		Bsplinenxnyy<<BSPL_yz->x[index][n]<<" "<<BSPL_yz->y[index][n]+BSPL_yz->nx_yz[index][n]<<" "<<BSPL_yz->z[index][n]+BSPL_yz->ny_yz[index][n]<<endl;
		Kslopey<<"zone t=\"kslope\""<<endl;
		Kslopey<<BSPL_yz->x[index][n]<<" "<<BSPL_yz->y[index][n]<<" "<<BSPL_yz->z[index][n]<<endl;
		Kslopey<<BSPL_yz->x[index][n]<<" "<<BSPL_yz->y[index][n]+BSPL_yz->nx_yz[index][n]*BSPL_yz->kslope_yz[index][n]*rad<<" "<<BSPL_yz->z[index][n]+BSPL_yz->ny_yz[index][n]*BSPL_yz->kslope_yz[index][n]*rad<<endl;
	}
	
	delete temp_x; delete temp_y; delete temp_z;
	delete temp_x_dev1; delete temp_y_dev1; delete temp_z_dev1;

}

void CALT_BSPLINE_XZ()
{
	//...Calculate basic function N Ndev1 Ndev2
	int index, i, cout, n, k, uNt, cot;
	index = 0;
		
	BSPLINE_XZ *BSPL_xz;
	BSPL_xz = new BSPLINE_XZ;
	caltBSP_XZ = new CALTBSPLINE_XZ;

	BSPL_xz->Init(*XZLINE, *XZNUM);
	caltBSP_XZ->Init_U(*XZLINE, *XZVERARR);
	caltBSP_XZ->Init_N(*XZORD, *XZVER, *XZNUM);
	caltBSP_XZ->Init_U_dev(*XZLINE, *XZVERARR-2);

	CaltMethod->create_Uni_Knot_Ver(&cacl_KV, *XZVER, *XZORD, caltBSP_XZ->U_xz[index], *XZVERARR);

	ofstream uNz, uNdev1z, uNdev2z;
	uNz.open("uNz.dat");
	uNdev1z.open("uNdev1z.dat");
	uNdev2z.open("uNdev2z.dat");
		
	ofstream CPdev1z;
	CPdev1z.open("CPdev1z.dat");
	ofstream CPdev2z;
	CPdev2z.open("CPdev2z.dat");
	
	ofstream Bsplinez;
	Bsplinez.open("Bsplinez.dat");
	ofstream Bsplinedev1z;
	Bsplinedev1z.open("Bsplinedev1z.dat");
	ofstream Bsplinedev2z;
	Bsplinedev2z.open("Bsplinedev2z.dat");
	ofstream nxyz;
	nxyz.open("nxyz.dat");
	ofstream Bsplinenxnyz;
	Bsplinenxnyz.open("Bsplinenxnyz.dat");
	ofstream Kslopez;
	Kslopez.open("Kslopez.dat");
	
	double *temp_x, *temp_y, *temp_z;
	double *temp_x_dev1, *temp_y_dev1, *temp_z_dev1;
	double *temp_x_dev2, *temp_y_dev2, *temp_z_dev2;

	//...XYZ... u spn U
	for(i=0;i<*XZNUM;i++)
	{
		caltBSP_XZ->u_xz[i] = (double)i/10.0;
	}

////////////////////////////////////////////////////////////////////////////////
	
	//...XZ...N
	for(cout=0;cout<*XZVER;cout++)
	{
		uNz<<"zone t=\"uN\""<<endl;
		uNdev1z<<"zone t=\"uNdev1\""<<endl;
		uNdev2z<<"zone t=\"uNdev2\""<<endl;
		for(n=0;n<*XZNUM;n++)
		{
			uNz<<caltBSP_XZ->u_xz[n]<<" ";
			uNdev1z<<caltBSP_XZ->u_xz[n]<<" ";
			uNdev2z<<caltBSP_XZ->u_xz[n]<<" ";
			for(k=0;k<=*XZORD;k++)
			{	
				for(i=0;i<*XZVER;i++)
				{	
					if(k==0)
					{
						if(caltBSP_XZ->u_xz[n]>=caltBSP_XZ->U_xz[index][i] && caltBSP_XZ->u_xz[n]<caltBSP_XZ->U_xz[index][i+1])
						{
							caltBSP_XZ->N_xz[k][i] = 1.0;
						}
						else
						{
							caltBSP_XZ->N_xz[k][i] = 0.0;
						}
					}
					else if(k==*XZORD&&n==*XZNUM-1&&i==*XZVER-1)
					{
						caltBSP_XZ->N_xz[k][i] = 1.0;				
					}
					else
					{
						caltBSP_XZ->N_xz[k][i]	= CaltMethod->cacu_Nki(caltBSP_XZ->u_xz[n], caltBSP_XZ->U_xz[index][i], caltBSP_XZ->N_xz[k-1][i], caltBSP_XZ->U_xz[index][i+k], caltBSP_XZ->N_xz[k-1][i+1], caltBSP_XZ->U_xz[index][i+k+1], caltBSP_XZ->U_xz[index][i+1]);
						caltBSP_XZ->N_dev1_xz[k][i] = CaltMethod->cacu_Nki_dev(k, caltBSP_XZ->U_xz[index][i], caltBSP_XZ->N_xz[k-1][i], caltBSP_XZ->U_xz[index][i+k], caltBSP_XZ->N_xz[k-1][i+1], caltBSP_XZ->U_xz[index][i+k+1], caltBSP_XZ->U_xz[index][i+1]);
						caltBSP_XZ->N_dev2_xz[k][i] = CaltMethod->cacu_Nki_dev(k, caltBSP_XZ->U_xz[index][i], caltBSP_XZ->N_dev1_xz[k-1][i], caltBSP_XZ->U_xz[index][i+k], caltBSP_XZ->N_dev1_xz[k-1][i+1], caltBSP_XZ->U_xz[index][i+k+1], caltBSP_XZ->U_xz[index][i+1]);
					}
				}
				if(k==*XZORD)
				{			
					if(n==0 && cout==0)
					{
						for(uNt=0;uNt<2;uNt++)
						{
							caltBSP_XZ->uN_temp_dev1[uNt] = caltBSP_XZ->N_dev1_xz[*XZORD][uNt];
						}
					}
					for(uNt=0;uNt<2;uNt++)
					{
						if(n==*XZNUM-1 && cout == *XZVER - (uNt + 1))
						{
							caltBSP_XZ->N_dev1_xz[*XZORD][*XZVER - (uNt + 1)] = caltBSP_XZ->uN_temp_dev1[1 - uNt];
						}
					}

					if(n==0 && cout==0)
					{
						for(uNt=0;uNt<3;uNt++)
						{
							caltBSP_XZ->uN_temp_dev2[uNt] = caltBSP_XZ->N_dev2_xz[*XZORD][uNt];
						}
					}
					for(uNt=0;uNt<3;uNt++)
					{
						if(n==*XZNUM-1 && cout == *XZVER - (uNt + 1))
						{
							caltBSP_XZ->N_dev2_xz[*XZORD][*XZVER - (uNt + 1)] = caltBSP_XZ->uN_temp_dev2[uNt];
						}
					}

					uNz<<caltBSP_XZ->N_xz[*XZORD][cout]<<endl;
					uNdev1z<<caltBSP_XZ->N_dev1_xz[*XZORD][cout]<<endl;
					uNdev2z<<caltBSP_XZ->N_dev2_xz[*XZORD][cout]<<endl;

					caltBSP_XZ->N_sig_xz[n][cout] = caltBSP_XZ->N_xz[*XZORD][cout];
					caltBSP_XZ->N_sig_dev_1_xz[n][cout] = caltBSP_XZ->N_xz[*XZORD-1][cout+1];		//dev 1 importent,this is right
					caltBSP_XZ->N_sig_dev_2_xz[n][cout] = caltBSP_XZ->N_xz[*XZORD-2][cout+2];		//dev 2 importent,this is right
				}
			}
		}
	}
	
	//...XZ...CP...dev
	for(i=0;i<*XZVER-1;i++)
	{		
		CP_xz[index][i].Set_ksi_dev1(((*XZORD)/(caltBSP_XZ->U_xz[index][i+*XZORD+1]-caltBSP_XZ->U_xz[index][i+1]))*(CP_xz[index][i+1].Get_ksi()-CP_xz[index][i].Get_ksi()));
		CP_xz[index][i].Set_eta_dev1(((*XZORD)/(caltBSP_XZ->U_xz[index][i+*XZORD+1]-caltBSP_XZ->U_xz[index][i+1]))*(CP_xz[index][i+1].Get_eta()-CP_xz[index][i].Get_eta()));		
		CP_xz[index][i].Set_zeta_dev1(((*XZORD)/(caltBSP_XZ->U_xz[index][i+*XZORD+1]-caltBSP_XZ->U_xz[index][i+1]))*(CP_xz[index][i+1].Get_zeta()-CP_xz[index][i].Get_zeta()));		
		
		CPdev1z<<CP_xz[index][i].Get_ksi_dev1()<<" "<<CP_xz[index][i].Get_eta_dev1()<<" "<<CP_xz[index][i].Get_zeta_dev1()<<endl;
	}
	CaltMethod->create_Uni_Knot_Ver(&cacl_KV, *XZVER-1, *XZORD-1, caltBSP_XZ->U_xz_dev[index], *XZVERARR-2);

	for(i=0;i<*XZVER-2;i++)
	{
		CP_xz[index][i].Set_ksi_dev2(((*XZORD-1)/(caltBSP_XZ->U_xz_dev[index][i+*XZORD-1+1]-caltBSP_XZ->U_xz_dev[index][i+1]))*(CP_xz[index][i+1].Get_ksi_dev1()-CP_xz[index][i].Get_ksi_dev1()));
		CP_xz[index][i].Set_eta_dev2(((*XZORD-1)/(caltBSP_XZ->U_xz_dev[index][i+*XZORD-1+1]-caltBSP_XZ->U_xz_dev[index][i+1]))*(CP_xz[index][i+1].Get_eta_dev1()-CP_xz[index][i].Get_eta_dev1()));		
		CP_xz[index][i].Set_zeta_dev2(((*XZORD-1)/(caltBSP_XZ->U_xz_dev[index][i+*XZORD-1+1]-caltBSP_XZ->U_xz_dev[index][i+1]))*(CP_xz[index][i+1].Get_zeta_dev1()-CP_xz[index][i].Get_zeta_dev1()));		
		
		CPdev2z<<CP_xz[index][i].Get_ksi_dev2()<<" "<<CP_xz[index][i].Get_eta_dev2()<<" "<<CP_xz[index][i].Get_zeta_dev2()<<endl;
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
	
	//...XZ...Bspline...normal vector...kslope
	for(n=0;n<*XZNUM;n++)
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

		for(cot=0;cot<*XZVER;cot++)
		{
			*temp_x += CP_xz[index][cot].Get_ksi() * caltBSP_XZ->N_sig_xz[n][cot];
			*temp_y += CP_xz[index][cot].Get_eta() * caltBSP_XZ->N_sig_xz[n][cot];
			*temp_z += CP_xz[index][cot].Get_zeta() * caltBSP_XZ->N_sig_xz[n][cot];
		}
		
		for(cot=0;cot<*XZVER-1;cot++)
		{
			if(n==*XZNUM-1)
			{
				*temp_x_dev1 = CP_xz[index][*XZVER-2].Get_ksi_dev1();
				*temp_y_dev1 = CP_xz[index][*XZVER-2].Get_eta_dev1();
				*temp_z_dev1 = CP_xz[index][*XZVER-2].Get_zeta_dev1();
			}
			else if(n==0)
			{
				*temp_x_dev1 = CP_xz[index][0].Get_ksi_dev1();
				*temp_y_dev1 = CP_xz[index][0].Get_eta_dev1();
				*temp_z_dev1 = CP_xz[index][0].Get_zeta_dev1();
			}
			else
			{
				*temp_x_dev1 += CP_xz[index][cot].Get_ksi_dev1() * caltBSP_XZ->N_sig_dev_1_xz[n][cot];
				*temp_y_dev1 += CP_xz[index][cot].Get_eta_dev1() * caltBSP_XZ->N_sig_dev_1_xz[n][cot];
				*temp_z_dev1 += CP_xz[index][cot].Get_zeta_dev1() * caltBSP_XZ->N_sig_dev_1_xz[n][cot];
			}
		}
		
		for(cot=0;cot<*XZVER-2;cot++)
		{
			if(n==*XZNUM-1)
			{
				*temp_x_dev2 = CP_xz[index][*XZVER-3].Get_ksi_dev2();
				*temp_y_dev2 = CP_xz[index][*XZVER-3].Get_eta_dev2();
				*temp_z_dev2 = CP_xz[index][*XZVER-3].Get_zeta_dev2();
			}
			else if(n==0)
			{
				*temp_x_dev2 = CP_xz[index][0].Get_ksi_dev2();
				*temp_y_dev2 = CP_xz[index][0].Get_eta_dev2();
				*temp_z_dev2 = CP_xz[index][0].Get_zeta_dev2();
			}
			else
			{
				*temp_x_dev2 += CP_xz[index][cot].Get_ksi_dev2() * caltBSP_XZ->N_sig_dev_2_xz[n][cot];
				*temp_y_dev2 += CP_xz[index][cot].Get_eta_dev2() * caltBSP_XZ->N_sig_dev_2_xz[n][cot];
				*temp_z_dev2 += CP_xz[index][cot].Get_zeta_dev2() * caltBSP_XZ->N_sig_dev_2_xz[n][cot];
			}
		}
		
		BSPL_xz->x[index][n] = *temp_x;
		BSPL_xz->y[index][n] = *temp_y;
		BSPL_xz->z[index][n] = *temp_z;

		BSPL_xz->x_dev1[index][n] = *temp_x_dev1;
		BSPL_xz->y_dev1[index][n] = *temp_y_dev1;
		BSPL_xz->z_dev1[index][n] = *temp_z_dev1;

		BSPL_xz->x_dev2[index][n] = *temp_x_dev2;
		BSPL_xz->y_dev2[index][n] = *temp_y_dev2;
		BSPL_xz->z_dev2[index][n] = *temp_z_dev2;
	
		BSPL_xz->nx_xz[index][n] = CaltMethod->cacu_nx(BSPL_xz->x_dev1[index][n], BSPL_xz->z_dev1[index][n]);
		BSPL_xz->ny_xz[index][n] = CaltMethod->cacu_ny(BSPL_xz->x_dev1[index][n], BSPL_xz->z_dev1[index][n]);

		BSPL_xz->kslope_xz[index][n] = CaltMethod->cacu_kslope(BSPL_xz->x_dev1[index][n], BSPL_xz->z_dev1[index][n], BSPL_xz->x_dev2[index][n], BSPL_xz->z_dev2[index][n]);

		Bsplinez<<BSPL_xz->x[index][n]<<" "<<BSPL_xz->y[index][n]<<" "<<BSPL_xz->z[index][n]<<endl;
		Bsplinedev1z<<BSPL_xz->x_dev1[index][n]<<" "<<BSPL_xz->y_dev1[index][n]<<" "<<BSPL_xz->z_dev1[index][n]<<endl;
		Bsplinedev2z<<BSPL_xz->x_dev2[index][n]<<" "<<BSPL_xz->y_dev2[index][n]<<" "<<BSPL_xz->z_dev2[index][n]<<endl;
		nxyz<<BSPL_xz->nx_xz[index][n]<<" "<<BSPL_xz->ny_xz[index][n]<<endl;
		Bsplinenxnyz<<"zone t=\"nxy\""<<endl;
		Bsplinenxnyz<<BSPL_xz->x[index][n]<<" "<<BSPL_xz->y[index][n]<<" "<<BSPL_xz->z[index][n]<<endl;
		Bsplinenxnyz<<BSPL_xz->x[index][n]+BSPL_xz->nx_xz[index][n]<<" "<<BSPL_xz->y[index][n]<<" "<<BSPL_xz->z[index][n]+BSPL_xz->ny_xz[index][n]<<endl;
		Kslopez<<"zone t=\"kslope\""<<endl;
		Kslopez<<BSPL_xz->x[index][n]<<" "<<BSPL_xz->y[index][n]<<" "<<BSPL_xz->z[index][n]<<endl;
		Kslopez<<BSPL_xz->x[index][n]+BSPL_xz->nx_xz[index][n]*BSPL_xz->kslope_xz[index][n]*rad<<" "<<BSPL_xz->y[index][n]<<" "<<BSPL_xz->z[index][n]+BSPL_xz->ny_xz[index][n]*BSPL_xz->kslope_xz[index][n]*rad<<endl;
	}
	
	delete temp_x; delete temp_y; delete temp_z;
	delete temp_x_dev1; delete temp_y_dev1; delete temp_z_dev1;
	
}


int main(void)
{

//////////////////////////////////Calculate BP////////////////////////////////////
	Init_Num_Ord();	
	Init_Method();
	Init_BP_XY();
	Init_BP_YZ();
	Init_BP_XZ();

	CALT_CP_XY();
	CALT_CP_YZ();
	CALT_CP_XZ();
	CALT_BSPLINE_XY();
	CALT_BSPLINE_YZ();
	CALT_BSPLINE_XZ();

	return 0;
}