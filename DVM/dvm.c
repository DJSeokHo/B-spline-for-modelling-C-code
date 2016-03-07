#include <stdio.h>
#include <math.h>

#define GANMA 1.0
#define PI 3.1415926535

main()
{
	/* m是指圆上的点 */
	FILE *test = fopen("test.dat","wt");
	
	float K=0.0, Umj, Vmj, rmj;
	float Umi, Vmi, rmi;
	float Um0, Vm0, rm0;

	float xm,xj,xi,x0, ym,yj,yi,y0;
	float betam;
	float rhsm,rhsp;

	float qm,um,vm;
	float a,r;
	float ceta;
	int i=0;
	float deltaSn,deltaSp;
	float x,y,cr,oldx,oldy;
	float xp,yp,cpr,oldxp,oldyp;
	cr=0.5;
	cpr=0.8;

//	xm=0.0; xj=0.0; x0=0.0; xi=0.0;
//	ym=-0.5; yj=-0.8; y0=0.0;

	xm=0.0; xj=0.520000; x0=0.0; xi=0;
	ym=0.5; yj=0.0; y0=0.0;;

	r=0.52;
//	r=yj;
	a=ym;	
	yi = pow(a,2)/r;
	printf("yi %0.5f\n",yi);

/*	for(ceta=0;ceta<=(2*PI)-((2*PI)/30);ceta+=((2*PI)/30))
	{
		i++;
		x=cpr*sin(ceta);
		y=cpr*cos(ceta);
		if(i==2){
			deltaSn = sqrt( pow((x-oldx),2) + pow((y-oldy),2) );
			i=0;
		}
		oldx = x;
		oldy = y;
	}	
	for(ceta=0;ceta<=(2*PI)-((2*PI)/30);ceta+=((2*PI)/30))
	{
		i++;
		xp=cpr*sin(ceta);
		yp=cpr*cos(ceta);
		if(i==2){
			deltaSp = sqrt( pow((xp-oldxp),2) + pow((yp-oldyp),2) );
			i=0;
		}
		oldxp = xp;
		oldyp = yp;
	}	
*/
	rm0 = sqrt( pow((xm-x0),2) + pow((ym-y0),2) );
	Um0= (1/(2*PI)) * ((ym-y0)/pow(rm0,2));
	Vm0=(-1/(2*PI)) * ((xm-x0)/pow(rm0,2));
	printf( "rm0=%0.6f\n",rm0);
	printf( "Um0=%0.6f  Vm0=%0.6f\n",Um0,Vm0);

	rmi = sqrt( pow((xm-xi),2) + pow((ym-yi),2) );
	Umi= (1/(2*PI)) * ((ym-yi)/pow(rmi,2));
	Vmi=(-1/(2*PI)) * ((xm-xi)/pow(rmi,2));
	printf( "rm0=%0.6f\n",rmi);
	printf( "Umi=%0.6f  Vmi=%0.6f\n",Umi,Vmi);

	rmj = sqrt( pow((xm-xj),2) + pow((ym-yj),2) );
	Umj= (1/(2*PI)) * ((ym-yj)/pow(rmj,2));
	Vmj=(-1/(2*PI)) * ((xm-xj)/pow(rmj,2));
	printf( "rm0=%0.6f\n",rmj);
	printf( "Umj=%0.6f  Vmj=%0.6f\n",Umj,Vmj);

	um=GANMA*(Um0-Umi+Umj);
	vm=GANMA*(Vm0-Vmi+Vmj);
	printf( "um=%0.6f  vm=%0.6f\n",um,vm);

	qm=sqrt( pow(um,2)+pow(vm,2) );
	printf( "\nqm=%0.6f\n",qm);
	
/*	for(betam=0;betam<=(2*PI)-((2*PI)/30);betam+=((2*PI)/30))
	{
	
		K+=(-1*GANMA)*(Umj*cos(betam)+Vmj*sin(betam));
		rhsm=K;
		rhsm=rhsm*deltaSn;
	}
	rhsp=(-1 / deltaSp ) * rhsm;
//	printf("\nrhsp is %0.6f\n",rhsp);*/

	return 0;
}
