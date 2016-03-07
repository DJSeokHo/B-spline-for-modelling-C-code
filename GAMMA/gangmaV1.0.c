#include <stdio.h>
#include <math.h>

#define pi 3.141592654
#define ganma -1
#define GANMA 2 * pi * ganma
#define rz 1
#define Uinf 1
#define rc 1
#define d 2 * rc
#define psi 0.5
double cyc( double );
double xiszero();
double sortpartment( double a[ 600 ], int N );
double xisnotzero( double );
double xisnotzero( double xvalue )
{
	double x, y, z, c, yvalue, lnsqrt, r;
	int i, count = 0;
	double temp[ 600 ];
	double realY;
	x = xvalue;
	switch( ganma )
	{
		case 1:
			for( i = -600; i <= 600; i++ )
			{
				y = ( double ) i / 100;
				lnsqrt = sqrt( x * x + y * y );
				r = x * x + y * y;
				c = ( ( -1 ) * Uinf * y * r ) + Uinf * ( rz * rz ) * y + r * psi;
				z = ( GANMA / ( 2 * pi ) ) * log( lnsqrt ) * r;
				yvalue = c - z;
				yvalue = fabs( yvalue );
				if( yvalue <= 0.05 )
				{
					return ( -1 ) * y;
					break;
				}
			}
			break;
		case -1:
			for( i = -600; i <= 600; i++ )
			{
				y = ( double ) i / 100;
				lnsqrt = sqrt( x * x + y * y );
				r = x * x + y * y;
				c = ( ( -1 ) * Uinf * y * r ) + Uinf * ( rz * rz ) * y + r * psi;
				z = ( -1 ) * ( GANMA / ( 2 * pi ) ) * log( lnsqrt ) * r;
				yvalue = c - z;
				yvalue = fabs( yvalue );
				if( yvalue <= 0.05 )
				{
					temp[ 0 + count ] = y;
					count++;
				}
			}
			if( count == 1 )
			{
				return temp[ 0 ];
			}
			else
			{
				realY = sortpartment( temp, count );
				return realY;
			}
			break;
		}
}

main()
{
	FILE *gangma = fopen( "gangma.dat", "wt" );
	FILE *drawstreaml = fopen( "streaml.dat", "wt" );

	int i, j;
	double xinput, a; 

	double cyup, cydown;
	double x;

	for( j = -250; j <= 250; j++ )
	{
		xinput = ( double ) j / 100;
		a = xisnotzero( xinput );
		fprintf( gangma, "%0.5lf  %0.5lf\n", xinput, a );
	}
	/***************************************************///drawcylinder
	printf( "****************************************************\n" );
	printf( "**************  draw cylinder  *********************\n" );
	printf( "****************************************************\n" );
	
	fprintf( drawstreaml, "\nTitle=“cylinder”\n");
	fprintf( drawstreaml, "Variables=“X”,“Y”,“Z”\n");
	fprintf( drawstreaml, "Zone I = %d \n\n", 20 * d + 1 );

	for( i = -20 * rc; i <= 20 * rc; i++ ){
		x = ( double ) i / 20;
		cyup = cyc( x );
		cydown = cyup * -1;
		fprintf( drawstreaml, "%0.5lf", x );
		fprintf( drawstreaml, "   %0.5lf    %0.5lf\n", cyup, cydown );
	}

	return 0;
}

double xiszero()
{
	double y, z, x, yvalue;
	int i;
	switch( ganma )
	{
		case 1:
			for( i = 1; i <= 3000; i++ )
			{
				y = ( double ) i / 1000;
				x = ( ( -1 ) * Uinf * y * y ) + Uinf * ( rz * rz ) + y * psi;
				z = ( GANMA / ( 2 * pi ) ) * log( y ) * y;
				yvalue = x - z;
				yvalue = fabs( yvalue );
				if( yvalue <= 0.005 )
				{
					return y ;
				}
			}
			break;
		case -1:
			for( i = 1; i <= 3000; i++ )
			{
				y = ( double ) i / 1000;
				x = ( ( -1 ) * Uinf * y * y ) + Uinf * ( rz * rz ) + y * psi;
				z = ( -1 ) * ( GANMA / ( 2 * pi ) ) * log( y ) * y;
				yvalue = x - z;
				yvalue = fabs( yvalue );
				if( yvalue <= 0.005 )
				{
					return  y;
				}
			}
			break;
		}
}

double sortpartment( double a[ 600 ], int N )
{
	int i, j;
	double temp;

	for( i = 0; i < N - 1; i++ )
	{
		for( j = i + 1; j < N; j++ )
		{
			if( a[ i ] < a[ j ] )
			{
			   temp = a[ i ];
			   a[ i ] = a[ j ];
			   a[ j ] = temp;
			}
		}
	}
	return a[ 1 ];
}

double cyc( double x )
{
	double cr = 0, cx = 0, temp = 0;
	cr = pow( rc, 2 );
	cx = pow( x, 2 );
	temp = cr - cx;
	temp = sqrt( temp );
	return temp;
}
