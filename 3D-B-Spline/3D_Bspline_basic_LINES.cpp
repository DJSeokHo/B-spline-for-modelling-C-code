#include "3D_Bspline_Basic_LINES.h"

using namespace std;

int main(void)
{
	//...................................INDEX...................................
	int index, i, j, k, cacl_KV, spn[Num], spn_dev[Num], n, cout, cot, uNt, Nv;

	//...Init X-Y, Y-Z, X-Z malloc
	BP_XY **BaseP_xy;
	BP_YZ **BaseP_yz;
	BP_XZ **BaseP_xz;

	BaseP_xy = new BP_XY*[XYLINE];
	for(index=0;index<XYLINE;index++)
	{
		BaseP_xy[index] = new BP_XY[BP];
	}
	
	BaseP_yz = new BP_YZ*[YZLINE];
	for(index=0;index<YZLINE;index++)
	{
		BaseP_yz[index] = new BP_YZ[BP];
	}

	BaseP_xz = new BP_XZ*[XZLINE];
	for(index=0;index<XZLINE;index++)
	{
		BaseP_xz[index] = new BP_XZ[BP];
	}

////////////////////////////////////////////////////////////////////////////////

	CALT_MTHOD *CaltMethod;
	CaltMethod = new CALT_MTHOD;

	//...Out Put X-Y, Y-Z, X-Z
	ofstream BPxyz;
	BPxyz.open("BPxyz.dat");
	
	BPxyz<<"zone t=\"BPxyz\""<<endl;
	double *anglexy = new double;
	*anglexy = 0.0;
	for(i=0;i<BP;i++)								//init the cycle							
	{																	
		BaseP_xy[0][i].Set_x(1.0*cos(CaltMethod->ang_to_rad(*anglexy)));									
		BaseP_xy[0][i].Set_y(1.0*sin(CaltMethod->ang_to_rad(*anglexy)));
		BaseP_xy[0][i].Set_z(0);
		*anglexy += 360.0 / (BP-1);
		BPxyz<<BaseP_xy[0][i].Get_x()<<" "<<BaseP_xy[0][i].Get_y()<<" "<<BaseP_xy[0][i].Get_z()<<endl;
	}		
	delete anglexy;

////////////////////////////////////////////////////////////////////////////////

	BPxyz<<"zone t=\"BPxyz\""<<endl;
	double *angleyz = new double;
	angleyz = new double;
	*angleyz = 0.0;
	for(i=0;i<BP;i++)								//init the cycle							
	{																	
		BaseP_yz[0][i].Set_x(0);									
		BaseP_yz[0][i].Set_y(1.0*cos(CaltMethod->ang_to_rad(*angleyz)));
		BaseP_yz[0][i].Set_z(1.0*sin(CaltMethod->ang_to_rad(*angleyz)));
		*angleyz += 360.0 / (BP-1);
		BPxyz<<BaseP_yz[0][i].Get_x()<<" "<<BaseP_yz[0][i].Get_y()<<" "<<BaseP_yz[0][i].Get_z()<<endl;
	}		
	delete angleyz;

////////////////////////////////////////////////////////////////////////////////
	
	BPxyz<<"zone t=\"BPxyz\""<<endl;
	double *anglexz = new double;
	*anglexz = 0.0;
	for(i=0;i<BP;i++)								//init the cycle							
	{																	
		BaseP_xz[0][i].Set_x(1.0*cos(CaltMethod->ang_to_rad(*anglexz)));									
		BaseP_xz[0][i].Set_y(0);
		BaseP_xz[0][i].Set_z(1.0*sin(CaltMethod->ang_to_rad(*anglexz)));
		*anglexz += 360.0 / (BP-1);
		BPxyz<<BaseP_xz[0][i].Get_x()<<" "<<BaseP_xz[0][i].Get_y()<<" "<<BaseP_xz[0][i].Get_z()<<endl;
	}		
	delete anglexz;

////////////////////////////////////////////////////////////////////////////////

	//...Calculate are length and parameter
	ofstream BP_sn;
	BP_sn.open("BP_sn.dat");
	ofstream BP_un;
	BP_un.open("BP_un.dat");
	
	CALTCP_XYZ **BP_sn_XY, **BP_sn_YZ, **BP_sn_XZ;
	
	BP_sn_XY = new CALTCP_XYZ*[XYLINE];
	for(index=0;index<XYLINE;index++)
	{
		BP_sn_XY[index] = new CALTCP_XYZ[BP];
	}
	BP_sn<<"zone t=\"BP_sn\""<<endl;
	BP_un<<"zone t=\"BP_un\""<<endl;
	for(i=0;i<BP;i++)
	{
		if(i==0)
		{
			BP_sn_XY[0][i].Set_BP_sn(0.0);
		}
		else
		{
			BP_sn_XY[0][i].Set_BP_sn(CaltMethod->cacu_BP_sn(BP_sn_XY[0][i-1].Get_BP_sn(), BaseP_xy[0][i].Get_x(), BaseP_xy[0][i-1].Get_x(), BaseP_xy[0][i].Get_y(), BaseP_xy[0][i-1].Get_y()));
		}
		BP_sn<<BP_sn_XY[0][i].Get_BP_sn()<<endl;
	}
	for(i=0;i<BP;i++)
	{
		BP_sn_XY[0][i].Set_BP_un((CaltMethod->cacu_BP_un(BP_sn_XY[0][BP-1].Get_BP_sn(), BP_sn_XY[0][i].Get_BP_sn())));
		BP_un<<BP_sn_XY[0][i].Get_BP_un()<<endl;
	}
	U_xy = new double*[XZLINE];
	for(index=0;index<XYLINE;index++)
	{
		U_xy[index] = new double[VER_ARR];
	}
	CaltMethod->create_Uni_Knot_Ver(&cacl_KV, VER, ORD, U_xy[0]);

////////////////////////////////////////////////////////////////////////////////

	BP_sn_YZ = new CALTCP_XYZ*[YZLINE];
	for(index=0;index<YZLINE;index++)
	{
		BP_sn_YZ[index] = new CALTCP_XYZ[BP];
	}
	BP_sn<<"zone t=\"BP_sn\""<<endl;
	BP_un<<"zone t=\"BP_un\""<<endl;
	for(i=0;i<BP;i++)
	{
		if(i==0)
		{	
			BP_sn_YZ[0][i].Set_BP_sn(0.0);
		}
		else
		{
			BP_sn_YZ[0][i].Set_BP_sn(CaltMethod->cacu_BP_sn(BP_sn_YZ[0][i-1].Get_BP_sn(), BaseP_yz[0][i].Get_y(), BaseP_yz[0][i-1].Get_y(), BaseP_yz[0][i].Get_z(), BaseP_yz[0][i-1].Get_z()));
		}
		BP_sn<<BP_sn_YZ[0][i].Get_BP_sn()<<endl;
	}
	for(i=0;i<BP;i++)
	{
		BP_sn_YZ[0][i].Set_BP_un((CaltMethod->cacu_BP_un(BP_sn_YZ[0][BP-1].Get_BP_sn(), BP_sn_YZ[0][i].Get_BP_sn())));
		BP_un<<BP_sn_YZ[0][i].Get_BP_un()<<endl;
	}
	U_yz = new double*[YZLINE];
	for(index=0;index<YZLINE;index++)
	{
		U_yz[index] = new double[VER_ARR];
	}
	CaltMethod->create_Uni_Knot_Ver(&cacl_KV, VER, ORD, U_yz[0]);

////////////////////////////////////////////////////////////////////////////////


	BP_sn_XZ = new CALTCP_XYZ*[XZLINE];
	for(index=0;index<XZLINE;index++)
	{
		BP_sn_XZ[index] = new CALTCP_XYZ[BP];
	}
	BP_sn<<"zone t=\"BP_sn\""<<endl;
	BP_un<<"zone t=\"BP_un\""<<endl;
	for(i=0;i<BP;i++)
	{
		if(i==0)
		{
			BP_sn_XZ[0][i].Set_BP_sn(0.0);
		}
		else
		{
			BP_sn_XZ[0][i].Set_BP_sn(CaltMethod->cacu_BP_sn(BP_sn_XZ[0][i-1].Get_BP_sn(), BaseP_xz[0][i].Get_x(), BaseP_xz[0][i-1].Get_x(), BaseP_xz[0][i].Get_z(), BaseP_xz[0][i-1].Get_z()));
		}
		BP_sn<<BP_sn_XY[0][i].Get_BP_sn()<<endl;
	}
	for(i=0;i<BP;i++)
	{
		BP_sn_XZ[0][i].Set_BP_un((CaltMethod->cacu_BP_un(BP_sn_XZ[0][BP-1].Get_BP_sn(), BP_sn_XZ[0][i].Get_BP_sn())));
		BP_un<<BP_sn_XZ[0][i].Get_BP_un()<<endl;
	}
	U_xz = new double*[XZLINE];
	for(index=0;index<XZLINE;index++)
	{
		U_xz[index] = new double[VER_ARR];
	}
	CaltMethod->create_Uni_Knot_Ver(&cacl_KV, VER, ORD, U_xz[0]);

////////////////////////////////////////////////////////////////////////////////

	//...Calculate Basic Function N and Control Point
	CP_XY **cp_xy;
	CP_YZ **cp_yz;
	CP_XZ **cp_xz;

	cp_xy = new CP_XY*[XYLINE];
	for(index=0;index<XYLINE;index++)
	{
		cp_xy[index] = new CP_XY[BP];
	}
	cp_yz = new CP_YZ*[YZLINE];
	for(index=0;index<XYLINE;index++)
	{
		cp_yz[index] = new CP_YZ[BP];
	}
	cp_xz = new CP_XZ*[XZLINE];
	for(index=0;index<XZLINE;index++)
	{
		cp_xz[index] = new CP_XZ[BP];
	}

	ofstream uNBP;
	uNBP.open("uNBP.dat");

	for(cout=0;cout<VER;cout++)
	{
		uNBP<<"zone t=\"uNBP\""<<endl;
		for(n=0;n<BP;n++)
		{
			uNBP<<BP_sn_XY[0][n].Get_BP_un()<<" ";
			for(k=0;k<=ORD;k++)
			{	
				for(i=0;i<VER;i++)
				{	
					if(k==0)
					{
						if(BP_sn_XY[0][n].Get_BP_un()>=U_xy[0][i] && BP_sn_XY[0][n].Get_BP_un()<U_xy[0][i+1])
						{
							CaltMethod->BP_N[k][i] = 1.0;
						}
						else
						{
							CaltMethod->BP_N[k][i] = 0.0;
						}
					}
					else if(k==ORD&&n==BP-1&&i==VER-1)
					{
						CaltMethod->BP_N[k][i] = 1.0;				
					}
					else
					{
						CaltMethod->BP_N[k][i] = CaltMethod->cacu_Nki(BP_sn_XY[0][n].Get_BP_un(), U_xy[0][i], CaltMethod->BP_N[k-1][i], U_xy[0][i+k], CaltMethod->BP_N[k-1][i+1], U_xy[0][i+k+1], U_xy[0][i+1]);
					}
				}
				if(k==ORD)
				{				
					CaltMethod->temp_BP_N[n][cout] = CaltMethod->BP_N[ORD][cout];
					uNBP<<CaltMethod->BP_N[ORD][cout]<<endl;
				}
			}
		}
	}

	CaltMethod->matrix_inversion_using_elementary_operation(CaltMethod->temp_BP_N,CaltMethod->inv_temp_BP_N,BP);

	for(i=0;i<BP;i++)
	{
		double *temp_x = new double;
		double *temp_y = new double;
		double *temp_z = new double;
		*temp_x=0.0; *temp_y=0.0; *temp_z=0.0;
		for(j=0;j<BP;j++)
		{
			*temp_x += CaltMethod->inv_temp_BP_N[i][j] * BaseP_xy[0][j].Get_x();
			*temp_y += CaltMethod->inv_temp_BP_N[i][j] * BaseP_xy[0][j].Get_y();
			*temp_z += CaltMethod->inv_temp_BP_N[i][j] * BaseP_xy[0][j].Get_z();
		}
		cp_xy[0][i].Set_ksi(*temp_x);
		cp_xy[0][i].Set_eta(*temp_y);
		cp_xy[0][i].Set_zeta(*temp_z);
	}

	ofstream CP;
	CP.open("CP.dat");
	for(i=0;i<VER;i++)
	{
		CP<<cp_xy[0][i].Get_ksi()<<" "<<cp_xy[0][i].Get_eta()<<" "<<cp_xy[0][i].Get_zeta()<<endl;
	}

////////////////////////////////////////////////////////////////////////////////

	for(index=0;index<XYLINE;index++)
	{
		delete[] BP_sn_XY[index];
	}
	delete[] BP_sn_XY;

	for(index=0;index<YZLINE;index++)
	{
		delete[] BP_sn_YZ[index];
	}
	delete[] BP_sn_YZ;

	for(index=0;index<XZLINE;index++)
	{
		delete[] BP_sn_XZ[index];
	}
	delete[] BP_sn_XZ;

////////////////////////////////////////////////////////////////////////////////

	//...Calculate parameter u and U
	LINE_XY **line_xy;
	LINE_YZ **line_yz;
	LINE_XZ **line_xz;
	
	line_xy = new LINE_XY*[XYLINE];
	for(index=0;index<Num;index++)
	{
		line_xy[index] = new LINE_XY[Num];
	}
	line_yz = new LINE_YZ*[YZLINE];
	for(index=0;index<Num;index++)
	{
		line_yz[index] = new LINE_YZ[Num];
	}
	line_xz = new LINE_XZ*[XZLINE];
	for(index=0;index<Num;index++)
	{
		line_xz[index] = new LINE_XZ[Num];
	}

	for(i=0;i<Num;i++)
	{
		line_xy[0][i].Set_u((double)i/10.0);
		line_xy[0][i].Set_spn(CaltMethod->FindSpan(VER, ORD, line_xy[0][i].Get_u(), U_xy[0]));
	}

////////////////////////////////////////////////////////////////////////////////

	//...Calculate basic function N Ndev1 Ndev2
	ofstream uN, uNdev1, uNdev2;
	uN.open("uN.dat");
	uNdev1.open("uNdev1.dat");
	uNdev2.open("uNdev2.dat");

	for(cout=0;cout<VER;cout++)
	{
		uN<<"zone t=\"uN\""<<endl;
		uNdev1<<"zone t=\"uNdev1\""<<endl;
		uNdev2<<"zone t=\"uNdev2\""<<endl;
		for(n=0;n<Num;n++)
		{
			uN<<line_xy[0][n].Get_u()<<" ";
			for(k=0;k<=ORD;k++)
			{	
				for(i=0;i<VER;i++)
				{	
					if(k==0)
					{
						if(line_xy[0][n].Get_u()>=U_xy[0][i] && line_xy[0][n].Get_u()<U_xy[0][i+1])
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
						N[k][i] = cacu_Nki(u[n], U_xy[0][i], N[k-1][i], U_xy[0][i+k], N[k-1][i+1], U_xy[0][i+k+1], U_xy[0][i+1]);
						N_dev1[k][i] = cacu_Nki_dev(k, U_xy[0][i], N[k-1][i], U_xy[0][i+k], N[k-1][i+1], U_xy[0][i+k+1], U_xy[0][i+1]);
						N_dev2[k][i] = cacu_Nki_dev(k, U_xy[0][i], N_dev1[k-1][i], U_xy[0][i+k], N_dev1[k-1][i+1], U_xy[0][i+k+1], U_xy[0][i+1]);						
					}
				}
				if(k==ORD)
				{				
					if(n==0 && cout==0)
					{
						for(uNt=0;uNt<2;uNt++)
						{
							uN_temp_dev1[uNt] = N_dev1[ORD][uNt];
						//	printf("%lf\n", uN_temp_dev1[uNt]);
						}
					}
					for(uNt=0;uNt<2;uNt++)
					{
						if(n==Num-1 && cout == VER - (uNt + 1))
						{
							N_dev1[ORD][VER - (uNt + 1)] = uN_temp_dev1[1 - uNt];
						}
					}

					if(n==0 && cout==0)
					{
						for(uNt=0;uNt<3;uNt++)
						{
							uN_temp_dev2[uNt] = N_dev2[ORD][uNt];
						//	printf("%lf\n", uN_temp_dev2[uNt]);
						}
					}
				
					for(uNt=0;uNt<3;uNt++)
					{
						if(n==Num-1 && cout == VER - (uNt + 1))
						{
							N_dev2[ORD][VER - (uNt + 1)] = uN_temp_dev2[uNt];
						}
					}

					fprintf(uN, "%lf\n", N[ORD][cout]);
					fprintf(uNdev1, "%lf\n", N_dev1[ORD][cout]);
					fprintf(uNdev2, "%lf\n", N_dev2[ORD][cout]);

					N_sig[n][cout] = N[ORD][cout];
					N_sig_dev_1[n][cout] = N[ORD-1][cout+1];		//dev 1 importent,this is right
					N_sig_dev_2[n][cout] = N[ORD-2][cout+2];		//dev 2 importent,this is right
				}
			}
		}
	}


  
	return 0;
}

