#include "CPP_B_spline_Derivative.h"

DataProp *DP;
CalMethod *CM;
BsplineCurve *BC;
CalControlPoint *CCP;
CalBsplineCurve *CBC;
CalBsplineCurveSlope *CBCS;

void Init_Data();
void Init_BasePoint(int);
void Init_ControlPoint(int);
void Init_Curve(int);
void Init_Slope(int);

void Free_Data();

int main(void)
{
	Init_Data();
	
	//0: WaterLine 1:BodyLine 2:SheerLine
	Init_BasePoint(0);
	Init_ControlPoint(0);
	Init_Curve(0);
	Init_Slope(0);

	Init_BasePoint(1);
	Init_ControlPoint(1);
	Init_Curve(1);
	Init_Slope(1);

	Init_BasePoint(2);
	Init_ControlPoint(2);
	Init_Curve(2);
	Init_Slope(2);

	Free_Data();

	return 0;
}

void Init_Data()
{
	DP = new DataProp;
	CM = new CalMethod;
	CCP = new CalControlPoint;
	CBC = new CalBsplineCurve;
	CBCS = new CalBsplineCurveSlope;

	DP->Set_LineNum(3);	
	BC = new BsplineCurve[DP->Get_LineNum()];
}

void Init_BasePoint(int TL)
{
	ofstream BPxy;
	BPxy.open("BPxy.dat");

	//...init datapoint	
	double angle = 0.0;
	double arc = 0.0;
	
	int index = TL;

	if(index==0)
	{
		BC[0].Set_Data(290, 3, 32, 0);	//0: WaterLine 1:BodyLine 2:SheerLine
		BC[0].Cal_Data();
		BPxy<<"zone t=\"WaterLine\""<<endl;
		for(int i=0;i<BC[index].BP;i++)
		{
			CM->ang_to_rad(&angle, &arc);
			BC[index].BaseP_x[i] = 1.0 * cos(arc);									
			BC[index].BaseP_y[i] = 1.0 * sin(arc);	
			BC[index].BaseP_z[i] = 0.0;	

			angle += 360.0 / (BC[index].BP-1);
			BPxy<<BC[index].BaseP_x[i]<<" "<<BC[index].BaseP_y[i]<<" "<<BC[index].BaseP_z[i]<<endl;
		}
		BPxy.close();
	}
	else if(index==1)
	{
		BC[1].Set_Data(290, 3, 32, 1);	//0: WaterLine 1:BodyLine 2:SheerLine
		BC[1].Cal_Data();
		BPxy<<"zone t=\"BodyLine\""<<endl;
		for(int i=0;i<BC[index].BP;i++)
		{
			CM->ang_to_rad(&angle, &arc);
			BC[index].BaseP_x[i] = 0.0;									
			BC[index].BaseP_y[i] = 1.0 * cos(arc);
			BC[index].BaseP_z[i] = 1.0 * sin(arc);	

			angle += 360.0 / (BC[index].BP-1);
			BPxy<<BC[index].BaseP_x[i]<<" "<<BC[index].BaseP_y[i]<<" "<<BC[index].BaseP_z[i]<<endl;
		}
		BPxy.close();
	}
	else if(index==2)
	{
		BC[2].Set_Data(290, 3, 32, 2);	//0: WaterLine 1:BodyLine 2:SheerLine
		BC[2].Cal_Data();
		BPxy<<"zone t=\"SheerLine\""<<endl;
		for(int i=0;i<BC[index].BP;i++)
		{
			CM->ang_to_rad(&angle, &arc);
			BC[index].BaseP_x[i] = 1.0 * cos(arc);									
			BC[index].BaseP_y[i] = 0.0;
			BC[index].BaseP_z[i] = 1.0 * sin(arc);	

			angle += 360.0 / (BC[index].BP-1);
			BPxy<<BC[index].BaseP_x[i]<<" "<<BC[index].BaseP_y[i]<<" "<<BC[index].BaseP_z[i]<<endl;
		}
		BPxy.close();
	}
	
}

void Init_ControlPoint(int TL)
{
	ofstream CP;
	CP.open("CP.dat");
	
	int index = TL;
	
	if(index==0)
	{
		CP<<"zone t=\"WaterLineCP\""<<endl;
		CCP->Set_Data(BC[index].ORD, BC[index].BP);
		CCP->Cal_Data();
		for(int i=0;i<BC[index].BP;i++)
		{
			if(i==0)
			{
				CCP->BP_sn[i] = 0.0;
			}
			else
			{
				CM->cacu_BP_sn(CCP->BP_sn[i-1], BC[index].BaseP_x[i], BC[index].BaseP_x[i-1], BC[index].BaseP_y[i], BC[index].BaseP_y[i-1], &CCP->BP_sn[i]);
			}
		}

		for(i=0;i<BC[index].BP;i++)
		{
			CM->cacu_BP_un(CCP->BP_sn[CCP->BP-1], CCP->BP_sn[i], &CCP->BP_un[i], CCP->BP, CCP->ORD);
		}

		CM->create_Uni_Knot_Ver(CCP->BP, CCP->ORD, CCP->U);

		for(i=0;i<CCP->BP;i++)
		{
			for(int j=0;j<CCP->BP;j++)
			{
				CCP->BP_N[i][j] = 0.0;
				CCP->temp_BP_N[i][j] = 0.0;
			}
		}
		
		for(int j=0;j<CCP->BP;j++) 
		{
			int spn = CM->FindSpan(CCP->BP-1, CCP->ORD, CCP->BP_un[j], CCP->U);
			CM->BasisFuns(spn, CCP->BP_un[j], CCP->ORD, CCP->U, CCP->N); 
			for(i=0;i<=CCP->ORD;i++) 
			{
				CCP->BP_N[j][spn-CCP->ORD+i] = CCP->N[i];
			}
		}

		CM->ludcmp(CCP->BP_N, CCP->temp_BP_N, CCP->BP, CCP->pivot, &CCP->plusminusone);  
		
		for(i=0;i<CCP->BP;i++) 
		{
			CCP->rhs[i] = BC[index].BaseP_x[i];
		}
		CM->lubksb(CCP->temp_BP_N,CCP->BP, CCP->pivot, CCP->rhs);
		for(i=0;i<CCP->BP;i++) 
		{
			BC[index].ksi[i] = CCP->rhs[i];
		}

		for(i=0;i<CCP->BP;i++) 
		{
			CCP->rhs[i] = BC[index].BaseP_y[i];
		}
		CM->lubksb(CCP->temp_BP_N, CCP->BP, CCP->pivot, CCP->rhs);
		for(i=0;i<CCP->BP;i++) 
		{
			BC[index].eta[i] = CCP->rhs[i];
		}
		
		for(i=0;i<BC[index].VER;i++)
		{
			BC[index].zeta[i] = 0.0;
			CP<<BC[index].ksi[i]<<" "<<BC[index].eta[i]<<" "<<BC[index].zeta[i]<<endl;
		}
		CP.close();
	}
	else if(index==1)
	{
		CP<<"zone t=\"BodyLineCP\""<<endl;
		CCP->Set_Data(BC[index].ORD, BC[index].BP);
		CCP->Cal_Data();
		for(int i=0;i<BC[index].BP;i++)
		{
			if(i==0)
			{
				CCP->BP_sn[i] = 0.0;
			}
			else
			{
				CM->cacu_BP_sn(CCP->BP_sn[i-1], BC[index].BaseP_y[i], BC[index].BaseP_y[i-1], BC[index].BaseP_z[i], BC[index].BaseP_z[i-1], &CCP->BP_sn[i]);
			}
		}

		for(i=0;i<BC[index].BP;i++)
		{
			CM->cacu_BP_un(CCP->BP_sn[CCP->BP-1], CCP->BP_sn[i], &CCP->BP_un[i], CCP->BP, CCP->ORD);
		}

		CM->create_Uni_Knot_Ver(CCP->BP, CCP->ORD, CCP->U);

		for(i=0;i<CCP->BP;i++)
		{
			for(int j=0;j<CCP->BP;j++)
			{
				CCP->BP_N[i][j] = 0.0;
				CCP->temp_BP_N[i][j] = 0.0;
			}
		}
		
		for(int j=0;j<CCP->BP;j++) 
		{
			int spn = CM->FindSpan(CCP->BP-1, CCP->ORD, CCP->BP_un[j], CCP->U);
			CM->BasisFuns(spn, CCP->BP_un[j], CCP->ORD, CCP->U, CCP->N); 
			for(i=0;i<=CCP->ORD;i++) 
			{
				CCP->BP_N[j][spn-CCP->ORD+i] = CCP->N[i];
			}
		}

		CM->ludcmp(CCP->BP_N, CCP->temp_BP_N, CCP->BP, CCP->pivot, &CCP->plusminusone);  
		
		for(i=0;i<CCP->BP;i++) 
		{
			CCP->rhs[i] = BC[index].BaseP_y[i];
		}
		CM->lubksb(CCP->temp_BP_N,CCP->BP, CCP->pivot, CCP->rhs);
		for(i=0;i<CCP->BP;i++) 
		{
			BC[index].eta[i] = CCP->rhs[i];
		}

		for(i=0;i<CCP->BP;i++) 
		{
			CCP->rhs[i] = BC[index].BaseP_z[i];
		}
		CM->lubksb(CCP->temp_BP_N, CCP->BP, CCP->pivot, CCP->rhs);
		for(i=0;i<CCP->BP;i++) 
		{
			BC[index].zeta[i] = CCP->rhs[i];
		}
		
		for(i=0;i<BC[index].VER;i++)
		{
			BC[index].ksi[i] = 0.0;
			CP<<BC[index].ksi[i]<<" "<<BC[index].eta[i]<<" "<<BC[index].zeta[i]<<endl;
		}
		CP.close();
	}
	else if(index==2)
	{
		CP<<"zone t=\"SheerLineCP\""<<endl;
		CCP->Set_Data(BC[index].ORD, BC[index].BP);
		CCP->Cal_Data();
		for(int i=0;i<BC[index].BP;i++)
		{
			if(i==0)
			{
				CCP->BP_sn[i] = 0.0;
			}
			else
			{
				CM->cacu_BP_sn(CCP->BP_sn[i-1], BC[index].BaseP_x[i], BC[index].BaseP_x[i-1], BC[index].BaseP_z[i], BC[index].BaseP_z[i-1], &CCP->BP_sn[i]);
			}
		}

		for(i=0;i<BC[index].BP;i++)
		{
			CM->cacu_BP_un(CCP->BP_sn[CCP->BP-1], CCP->BP_sn[i], &CCP->BP_un[i], CCP->BP, CCP->ORD);
		}

		CM->create_Uni_Knot_Ver(CCP->BP, CCP->ORD, CCP->U);

		for(i=0;i<CCP->BP;i++)
		{
			for(int j=0;j<CCP->BP;j++)
			{
				CCP->BP_N[i][j] = 0.0;
				CCP->temp_BP_N[i][j] = 0.0;
			}
		}
		
		for(int j=0;j<CCP->BP;j++) 
		{
			int spn = CM->FindSpan(CCP->BP-1, CCP->ORD, CCP->BP_un[j], CCP->U);
			CM->BasisFuns(spn, CCP->BP_un[j], CCP->ORD, CCP->U, CCP->N); 
			for(i=0;i<=CCP->ORD;i++) 
			{
				CCP->BP_N[j][spn-CCP->ORD+i] = CCP->N[i];
			}
		}

		CM->ludcmp(CCP->BP_N, CCP->temp_BP_N, CCP->BP, CCP->pivot, &CCP->plusminusone);  
		
		for(i=0;i<CCP->BP;i++) 
		{
			CCP->rhs[i] = BC[index].BaseP_x[i];
		}
		CM->lubksb(CCP->temp_BP_N,CCP->BP, CCP->pivot, CCP->rhs);
		for(i=0;i<CCP->BP;i++) 
		{
			BC[index].ksi[i] = CCP->rhs[i];
		}

		for(i=0;i<CCP->BP;i++) 
		{
			CCP->rhs[i] = BC[index].BaseP_z[i];
		}
		CM->lubksb(CCP->temp_BP_N, CCP->BP, CCP->pivot, CCP->rhs);
		for(i=0;i<CCP->BP;i++) 
		{
			BC[index].zeta[i] = CCP->rhs[i];
		}
		
		for(i=0;i<BC[index].VER;i++)
		{
			BC[index].eta[i] = 0.0;
			CP<<BC[index].ksi[i]<<" "<<BC[index].eta[i]<<" "<<BC[index].zeta[i]<<endl;
		}
		CP.close();
	}
}

void Init_Curve(int TL)
{
	ofstream Bspline;
	Bspline.open("Bspline.dat");

	int index = TL;

	if(index==0)
	{
		CBC->Set_Data(BC[index].Num, BC[index].ORD, BC[index].VER);
		CBC->Cal_Data();
		double maxu = (double)(CBC->VER - CBC->ORD);
		double delu = maxu / (double)(CBC->Num-1);	
		CM->create_Uni_Knot_Ver(CBC->VER, CBC->ORD, CBC->U);

		for(int i=0;i<CBC->Num;i++)
		{
			CBC->u[i] = (double)i * delu;
			BC[index].z[i] = 0.0;
			CM->CurvePoint(CBC->VER-1, CBC->ORD, CBC->U, BC[index].ksi, CBC->u[i], &BC[index].x[i]);
			CM->CurvePoint(CBC->VER-1, CBC->ORD, CBC->U, BC[index].eta, CBC->u[i], &BC[index].y[i]);
			Bspline<<BC[index].x[i]<<" "<<BC[index].y[i]<<" "<<BC[index].z[i]<<endl;
		}
		Bspline.close();
	}
	else if(index==1)
	{
		CBC->Set_Data(BC[index].Num, BC[index].ORD, BC[index].VER);
		CBC->Cal_Data();
		double maxu = (double)(CBC->VER - CBC->ORD);
		double delu = maxu / (double)(CBC->Num-1);	
		CM->create_Uni_Knot_Ver(CBC->VER, CBC->ORD, CBC->U);

		for(int i=0;i<CBC->Num;i++)
		{
			CBC->u[i] = (double)i * delu;
			BC[index].x[i] = 0.0;
			CM->CurvePoint(CBC->VER-1, CBC->ORD, CBC->U, BC[index].eta, CBC->u[i], &BC[index].y[i]);
			CM->CurvePoint(CBC->VER-1, CBC->ORD, CBC->U, BC[index].zeta, CBC->u[i], &BC[index].z[i]);
			Bspline<<BC[index].x[i]<<" "<<BC[index].y[i]<<" "<<BC[index].z[i]<<endl;
		}
		Bspline.close();
	}
	else if(index==2)
	{
		CBC->Set_Data(BC[index].Num, BC[index].ORD, BC[index].VER);
		CBC->Cal_Data();
		double maxu = (double)(CBC->VER - CBC->ORD);
		double delu = maxu / (double)(CBC->Num-1);	
		CM->create_Uni_Knot_Ver(CBC->VER, CBC->ORD, CBC->U);

		for(int i=0;i<CBC->Num;i++)
		{
			CBC->u[i] = (double)i * delu;
			BC[index].y[i] = 0.0;
			CM->CurvePoint(CBC->VER-1, CBC->ORD, CBC->U, BC[index].ksi, CBC->u[i], &BC[index].x[i]);
			CM->CurvePoint(CBC->VER-1, CBC->ORD, CBC->U, BC[index].zeta, CBC->u[i], &BC[index].z[i]);
			Bspline<<BC[index].x[i]<<" "<<BC[index].y[i]<<" "<<BC[index].z[i]<<endl;
		}
		Bspline.close();
	}
}

void Init_Slope(int TL)
{
	ofstream Bsplineslope;
	Bsplineslope.open("Bsplineslope.dat");
	
	int index = TL;
	
	if(index==0)
	{
		CBCS->Set_Data(BC[index].Num, BC[index].ORD, BC[index].VER);
		CBCS->Cal_Data();
		double maxu = (double)(CBCS->VER - CBCS->ORD);
		double delu = maxu / (double)(CBCS->Num-1);

		CM->create_Uni_Knot_Ver(CBCS->VER, CBCS->ORD, CBCS->U);

		for(int k=0;k<2;k++)
		{
			for(int i=0;i<CBCS->Num;i++)
			{
				CBCS->u[i] = (double)i * delu;
				BC[index].xdev[k][i] = 0.0;
				BC[index].ydev[k][i] = 0.0;
				int spn = CM->FindSpan(CBCS->VER-1, CBCS->ORD, CBCS->u[i], CBCS->U);
				CM->DersBasisFuns(spn, CBCS->u[i], CBCS->ORD, k+1, CBCS->U, CBCS->nders);
				for(int j=0;j<=CBCS->ORD;j++)
				{
					BC[index].xdev[k][i] += CBCS->nders[k+1][j] * BC[index].ksi[spn-CBCS->ORD+j];
					BC[index].ydev[k][i] += CBCS->nders[k+1][j] * BC[index].eta[spn-CBCS->ORD+j];
				}
			}
		}
		
		for(int i=0;i<CBCS->Num;i++)
		{
			Bsplineslope<<"zone t=\"Bsplineslope\""<<endl;
			CM->cacu_nx(BC[index].xdev[0][i], BC[index].ydev[0][i], &BC[index].nx[i]);
			CM->cacu_ny(BC[index].xdev[0][i], BC[index].ydev[0][i], &BC[index].ny[i]);
			CM->cacu_kslope(BC[index].xdev[0][i], BC[index].ydev[0][i], BC[index].xdev[1][i], BC[index].ydev[1][i], &BC[index].kslope[i]);
			Bsplineslope<<BC[index].x[i]<<" "<<BC[index].y[i]<<" "<<BC[index].z[i]<<endl;
			Bsplineslope<<BC[index].x[i]+BC[index].nx[i]*BC[index].kslope[i]*rad<<" "<<BC[index].y[i]+BC[index].ny[i]*BC[index].kslope[i]*rad<<" "<<BC[index].z[i]<<endl;
		}
		Bsplineslope.close();
	}
	else if(index==1)
	{
		CBCS->Set_Data(BC[index].Num, BC[index].ORD, BC[index].VER);
		CBCS->Cal_Data();
		double maxu = (double)(CBCS->VER - CBCS->ORD);
		double delu = maxu / (double)(CBCS->Num-1);

		CM->create_Uni_Knot_Ver(CBCS->VER, CBCS->ORD, CBCS->U);

		for(int k=0;k<2;k++)
		{
			for(int i=0;i<CBCS->Num;i++)
			{
				CBCS->u[i] = (double)i * delu;
				BC[index].xdev[k][i] = 0.0;
				BC[index].ydev[k][i] = 0.0;
				int spn = CM->FindSpan(CBCS->VER-1, CBCS->ORD, CBCS->u[i], CBCS->U);
				CM->DersBasisFuns(spn, CBCS->u[i], CBCS->ORD, k+1, CBCS->U, CBCS->nders);
				for(int j=0;j<=CBCS->ORD;j++)
				{
					BC[index].xdev[k][i] += CBCS->nders[k+1][j] * BC[index].eta[spn-CBCS->ORD+j];
					BC[index].ydev[k][i] += CBCS->nders[k+1][j] * BC[index].zeta[spn-CBCS->ORD+j];
				}
			}
		}
		
		for(int i=0;i<CBCS->Num;i++)
		{
			Bsplineslope<<"zone t=\"Bsplineslope\""<<endl;
			CM->cacu_nx(BC[index].xdev[0][i], BC[index].ydev[0][i], &BC[index].nx[i]);
			CM->cacu_ny(BC[index].xdev[0][i], BC[index].ydev[0][i], &BC[index].ny[i]);
			CM->cacu_kslope(BC[index].xdev[0][i], BC[index].ydev[0][i], BC[index].xdev[1][i], BC[index].ydev[1][i], &BC[index].kslope[i]);
			Bsplineslope<<BC[index].x[i]<<" "<<BC[index].y[i]<<" "<<BC[index].z[i]<<endl;
			Bsplineslope<<BC[index].x[i]<<" "<<BC[index].y[i]+BC[index].nx[i]*BC[index].kslope[i]*rad<<" "<<BC[index].z[i]+BC[index].ny[i]*BC[index].kslope[i]*rad<<endl;
		}
		Bsplineslope.close();
	}
	else if(index==2)
	{
		CBCS->Set_Data(BC[index].Num, BC[index].ORD, BC[index].VER);
		CBCS->Cal_Data();
		double maxu = (double)(CBCS->VER - CBCS->ORD);
		double delu = maxu / (double)(CBCS->Num-1);

		CM->create_Uni_Knot_Ver(CBCS->VER, CBCS->ORD, CBCS->U);

		for(int k=0;k<2;k++)
		{
			for(int i=0;i<CBCS->Num;i++)
			{
				CBCS->u[i] = (double)i * delu;
				BC[index].xdev[k][i] = 0.0;
				BC[index].ydev[k][i] = 0.0;
				int spn = CM->FindSpan(CBCS->VER-1, CBCS->ORD, CBCS->u[i], CBCS->U);
				CM->DersBasisFuns(spn, CBCS->u[i], CBCS->ORD, k+1, CBCS->U, CBCS->nders);
				for(int j=0;j<=CBCS->ORD;j++)
				{
					BC[index].xdev[k][i] += CBCS->nders[k+1][j] * BC[index].ksi[spn-CBCS->ORD+j];
					BC[index].ydev[k][i] += CBCS->nders[k+1][j] * BC[index].zeta[spn-CBCS->ORD+j];
				}
			}
		}
		
		for(int i=0;i<CBCS->Num;i++)
		{
			Bsplineslope<<"zone t=\"Bsplineslope\""<<endl;
			CM->cacu_nx(BC[index].xdev[0][i], BC[index].ydev[0][i], &BC[index].nx[i]);
			CM->cacu_ny(BC[index].xdev[0][i], BC[index].ydev[0][i], &BC[index].ny[i]);
			CM->cacu_kslope(BC[index].xdev[0][i], BC[index].ydev[0][i], BC[index].xdev[1][i], BC[index].ydev[1][i], &BC[index].kslope[i]);
			Bsplineslope<<BC[index].x[i]<<" "<<BC[index].y[i]<<" "<<BC[index].z[i]<<endl;
			Bsplineslope<<BC[index].x[i]+BC[index].nx[i]*BC[index].kslope[i]*rad<<" "<<BC[index].y[i]<<" "<<BC[index].z[i]+BC[index].ny[i]*BC[index].kslope[i]*rad<<endl;
		}
		Bsplineslope.close();
	}
}	

void Free_Data()
{
	delete DP;
	delete CM;
	delete BC;	
	delete CCP;
	delete CBC;
	delete CBCS;
}


