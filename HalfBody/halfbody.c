#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#define Pi 3.1415926

void drawX( void );
void drawY( void );

float gety( float x )
{
	float y;
	y =(float) 1 * 1 * x + ( 1 / ( 2 * Pi ) ) * 1 / 1;
	
	return y;
}



main()
{
	int drive, mode, width, height;

	float r, u, cseta, m, lnr, v, x;
	int x1, v1;
	scanf( "%f", &x );

	v = gety( x );

	printf( "%10.3f", v );

	x1 =(int)x * 46;
	
	v1 =(int)(460 - v * 46);

	drive = DETECT;

	getch();

	
	initgraph( &drive, &mode, "" );
	setbkcolor( BLUE );
	cleardevice();

	drawX();
	drawY();

	line( 0, 460, x1, v1 );
	getch();
	closegraph();
}

void drawX( void )
{
	line( 0, 460, 46, 460 );
	line( 0, 460, 0, 455 );
	moveto( 0, 465 );
	outtext( "0" );

	line( 46, 460, 92, 460 );
	line( 46, 460, 46, 455 );
	moveto( 46, 465 );
	outtext( "1" );

	line( 92, 460, 138, 460 );
	line( 92, 460, 92, 455 );
	moveto( 92, 465 );
	outtext( "2" );

	line( 138, 460, 184, 460 );
	line( 138, 460, 138, 455 );
	moveto( 138, 465 );
	outtext( "3" );

	line( 184, 460, 230, 460 );
	line( 184, 460, 184, 455 );
	moveto( 184, 465 );
	outtext( "4" );

	line( 230, 460, 276, 460 );
	line( 230, 460, 230, 455 );
	moveto( 230, 465 );
	outtext( "5" );

	line( 276, 460, 322, 460 );
	line( 276, 460, 276, 455 );
	moveto( 276, 465 );
	outtext( "6" );

	line( 322, 460, 368, 460 );
	line( 322, 460, 322, 455 );
	moveto( 322, 465 );
	outtext( "7" );

	line( 368, 460, 414, 460 );
	line( 368, 460, 368, 455 );
	moveto( 368, 465 );
	outtext( "8" );

	line( 414, 460, 460, 460 );
	line( 414, 460, 414, 455 );
	moveto( 414, 465 );
	outtext( "9" );

	line( 460, 460, 460, 460 );
	line( 460, 460, 460, 455 );
	moveto( 460, 465 );
	outtext( "10" );
}


void drawY( void )
{
	line( 0, 460, 0, 414 );
	line( 0, 460, 5, 460 );
	moveto( 5, 414 );
	outtext( "1" );

	line( 0, 414, 0, 368 );
	line( 0, 414, 5, 414 );
	moveto( 5, 368 );
	outtext( "2" );

	line( 0, 368, 0, 322 );
	line( 0, 368, 5, 368 );
	moveto( 5, 322 );
	outtext( "3" );

	line( 0, 322, 0, 276 );
	line( 0, 322, 5, 322 );
	moveto( 5, 276 );
	outtext( "4" );

	line( 0, 276, 0, 230 );
	line( 0, 276, 5, 276 );
	moveto( 5, 230 );
	outtext( "5" );

	line( 0, 230, 0, 184 );
	line( 0, 230, 5, 230 );
	moveto( 5, 184 );
	outtext( "6" );

	line( 0, 184, 0, 138 );
	line( 0, 184, 5, 184 );
	moveto( 5, 138 );
	outtext( "7" );

	line( 0, 138, 0, 92 );
	line( 0, 138, 5, 138 );
	moveto( 5, 92 );
	outtext( "8" );

	line( 0, 92, 0, 46 );
	line( 0, 92, 5, 92 );
	moveto( 5, 46 );
	outtext( "9" );

	line( 0, 46, 0, 0 );
	line( 0, 0, 5, 0 );
	moveto( 5, 0 );
	outtext( "10" );
}
