#include "CPP_B_surface_Derivative.h"

DataProp *DPP;
CalMethod *method;
Bsurface *bsurf;

void Init_Data();
void Init_ControlPoint();

int main(void)
{
	Init_Data();
	Init_ControlPoint();

	return 0;
}

void Init_Data()
{
	DPP = new DataProp;
	DPP->Set_LineNum(1);
	method = new CalMethod;

	bsurf = new Bsurface[DPP->Get_LineNum()];
	int index = DPP->Get_LineNum()-1;
	bsurf[index].Set_Data_Bsurf(20, 3, 5, 20, 3, 5);
	bsurf[index].Cal_Data_Bsurf();
}

void Init_ControlPoint()
{
	ofstream CP;
	CP.open("CP.dat");
	int index = DPP->Get_LineNum()-1;
	
	bsurf[index].ksi[0][0] = 0.0;
	bsurf[index].ksi[0][1] = 1.0;
	bsurf[index].ksi[0][2] = 2.0;
	bsurf[index].ksi[0][3] = 3.0;
	bsurf[index].ksi[0][4] = 4.0;
	
	bsurf[index].ksi[1][0] = 0.0;
	bsurf[index].ksi[1][1] = 1.0;
	bsurf[index].ksi[1][2] = 2.0;
	bsurf[index].ksi[1][3] = 3.0;
	bsurf[index].ksi[1][4] = 4.0;

	bsurf[index].ksi[2][0] = 0.0;
	bsurf[index].ksi[2][1] = 1.0;
	bsurf[index].ksi[2][2] = 2.0;
	bsurf[index].ksi[2][3] = 3.0;
	bsurf[index].ksi[2][4] = 4.0;

	bsurf[index].ksi[3][0] = 0.0;
	bsurf[index].ksi[3][1] = 1.0;
	bsurf[index].ksi[3][2] = 2.0;
	bsurf[index].ksi[3][3] = 3.0;
	bsurf[index].ksi[3][4] = 4.0;

	bsurf[index].ksi[4][0] = 0.0;
	bsurf[index].ksi[4][1] = 1.0;
	bsurf[index].ksi[4][2] = 2.0;
	bsurf[index].ksi[4][3] = 3.0;
	bsurf[index].ksi[4][4] = 4.0;

	bsurf[index].eta[0][0] = 0.0;
	bsurf[index].eta[0][1] = 0.0;
	bsurf[index].eta[0][2] = 0.0;
	bsurf[index].eta[0][3] = 0.0;
	bsurf[index].eta[0][4] = 0.0;
	
	bsurf[index].eta[1][0] = 1.0;
	bsurf[index].eta[1][1] = 1.0;
	bsurf[index].eta[1][2] = 1.0;
	bsurf[index].eta[1][3] = 1.0;
	bsurf[index].eta[1][4] = 1.0;

	bsurf[index].eta[2][0] = 2.0;
	bsurf[index].eta[2][1] = 2.0;
	bsurf[index].eta[2][2] = 2.0;
	bsurf[index].eta[2][3] = 2.0;
	bsurf[index].eta[2][4] = 2.0;

	bsurf[index].eta[3][0] = 3.0;
	bsurf[index].eta[3][1] = 3.0;
	bsurf[index].eta[3][2] = 3.0;
	bsurf[index].eta[3][3] = 3.0;
	bsurf[index].eta[3][4] = 3.0;

	bsurf[index].eta[4][0] = 4.0;
	bsurf[index].eta[4][1] = 4.0;
	bsurf[index].eta[4][2] = 4.0;
	bsurf[index].eta[4][3] = 4.0;
	bsurf[index].eta[4][4] = 4.0;

	bsurf[index].zeta[0][0] = 0.0;
	bsurf[index].zeta[0][1] = 0.5;
	bsurf[index].zeta[0][2] = 1.0;
	bsurf[index].zeta[0][3] = 1.0;
	bsurf[index].zeta[0][4] = 0.5;
	
	bsurf[index].zeta[1][0] = 0.0;
	bsurf[index].zeta[1][1] = 0.3;
	bsurf[index].zeta[1][2] = 2.0;
	bsurf[index].zeta[1][3] = 3.0;
	bsurf[index].zeta[1][4] = 2.0;

	bsurf[index].zeta[2][0] = 1.0;
	bsurf[index].zeta[2][1] = 0.6;
	bsurf[index].zeta[2][2] = 3.0;
	bsurf[index].zeta[2][3] = 2.0;
	bsurf[index].zeta[2][4] = 1.0;

	bsurf[index].zeta[3][0] = 2.0;
	bsurf[index].zeta[3][1] = 4.0;
	bsurf[index].zeta[3][2] = 0.6;
	bsurf[index].zeta[3][3] = 2.0;
	bsurf[index].zeta[3][4] = 3.0;

	bsurf[index].zeta[4][0] = 1.0;
	bsurf[index].zeta[4][1] = 2.0;
	bsurf[index].zeta[4][2] = 4.0;
	bsurf[index].zeta[4][3] = 0.6;
	bsurf[index].zeta[4][4] = 3.0;

	for(int i=0;i<bsurf[index].VER_u;i++)
	{
		CP<<"zone t=\"Net\""<<endl;
		for(int j=0;j<bsurf[index].VER_v;j++)
		{
			CP<<bsurf[index].ksi[i][j]<<" "<<bsurf[index].eta[i][j]<<" "<<bsurf[index].zeta[i][j]<<endl;
		}
	}

	for(int j=0;j<bsurf[index].VER_u;j++)
	{
		CP<<"zone t=\"Net\""<<endl;
		for(i=0;i<bsurf[index].VER_v;i++)
		{
			CP<<bsurf[index].ksi[i][j]<<" "<<bsurf[index].eta[i][j]<<" "<<bsurf[index].zeta[i][j]<<endl;
		}
	}

	CP.close();
}