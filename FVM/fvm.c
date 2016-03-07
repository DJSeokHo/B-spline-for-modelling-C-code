#include <stdio.h>
#include <math.h>

#define CV 5
#define N 10
#define L 0.5

void draw(void);
float init_cp(float, float); 

main()
{
	draw();
	return 0;
}

void draw(void)
{
	FILE *domain=fopen("domain.dat","wt");
	FILE *pivotalP=fopen("pivotalP.dat","wt");

	int i, j;
	float bound_X[N], bound_Y[N];
	float cp_X[N], cp_Y[N];
	float EX, EY, WX, WY, eX, eY, wX, wY, PX, PY;
	float delx_PE, delx_WP, delX;

	float ke, kw, TE, TW, TP, Ae, Aw, AW, AE, k=1000;
	
	float GAMw, GAMW, GAMP, GAMe, GAM, GAME;

	for(i=0;i<=CV;i++)													
	{																				
		bound_X[i] = (float)i*(L/CV);										
		bound_Y[i] = 0.0;									
		fprintf(domain, "%0.4f %0.4f\n", bound_X[i], bound_Y[i]);																
	}																				

	for(i=0;i<CV;i++)													
	{																			
		cp_X[i] = init_cp(bound_X[i+1],bound_X[i]);									
		cp_Y[i] = init_cp(bound_Y[i+1],bound_Y[i]);									
		fprintf(pivotalP, "%0.4f %0.4f\n", cp_X[i], cp_Y[i]);					
	}	
	


}

float init_cp(float V_1, float V)
{
	float temp_cp_, temp_v1_, temp_v_;
	temp_v1_ = V_1; temp_v_ = V;
	temp_cp_=0.5*(temp_v1_ + temp_v_);
	return temp_cp_;
}
