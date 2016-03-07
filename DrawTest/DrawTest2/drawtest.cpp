#include <graphics.h>
#include <stdio.h>
#include <conio.h>


void msDelay(unsigned int Delay);
void drawX( void );
void drawY( void );
void matrix_inversion_using_element_operation( float coeff[20][20], float inv_coeff[20][20], int num_eq );


int main()
{

	int drive, mode, width, height;
	int x[ 21 ], xx[ 21 ], y[ 21 ];
	int fixx,fixy;
	float b[21], xz[ 21 ];

	int i, j, num_eq, num_var, pointNUM;
	float coeff[ 20 ][ 20 ], inv_coeff[ 20 ][ 20 ], known[ 20 ];
	float var[ 20 ];
	float drawpoints[ 50 ];
	float  scope, interval;

	drive = DETECT;
	printf( "Enter the Number of Equations. : " );
	scanf( "%d", &num_eq );
	num_var = num_eq;
	for( i = 0; i < num_eq; i++ ){
		printf( "*********************************************\n" );
		printf( "Enter the Coefficients of eq. %d. \n", i + 1 );
		for( j = 0; j < num_var; j++ ){
			printf( "coefficient of variable %d. : ", j + 1 );
			scanf( "%f", &coeff[ i ][ j ] );
		}
		printf( "Enter the Known Value of eq. %d. : ", i + 1 );
		scanf( "%f", &known[ i ] );
	}
	
	printf( "*********************************************\n" );




	printf( "\n\n Entered Equations :\n" );
	for( i = 0; i < num_var; i++ ){
		for( j = 0; j < num_var; j++ ){
			printf( "%10.3f * X%d", coeff[ i ][ j ], j + 1);
			if( j != num_var - 1)
				printf( "+" );
			else
				printf( "=" );
		}
		printf("%10.3f\n", known[i] );
	}

matrix_inversion_using_element_operation( coeff, inv_coeff, num_eq );

	for( i = 0; i < num_var; i++ ){
		var[ i ] = 0.0;
		for( j = 0; j < num_eq; j++ )
			var[ i ] += inv_coeff[ i ][ j ] * known[ j ];
	}
	
	printf( "*********************************************\n" );
	printf( "Results : \n" );
	
	for( i = 0; i < num_var; i++ )
		printf( "X%d = %10.3f\n", i + 1, var[ i ] );

	for( i = num_eq; i >= 1; i-- ){
		printf( "%0.3fX^%d", var[ num_eq - i ], i - 1 );
		if( i > 1 )
			printf( " + " );

		xz[ num_eq - i ] = var[ num_eq - i];
	}
	
	

	printf( "\n\n" );
	printf( "Enter the scope of X: " );
	scanf( "%f", &scope );
	printf( "\n" );
	printf( "Enter the interval of test: " );
	scanf( "%f", &interval );
	printf( "\n\n" );


	pointNUM =( int )( scope / interval );

	for( i = 0; i <= pointNUM; i++ ){
		b[ i ] = ( xz[ num_eq - num_eq ] * i * i ) + ( xz[ num_eq - num_eq + 1 ] * i ) + ( xz[ num_eq - num_eq + 2 ] * ( num_eq - num_eq ) );
		printf( "%d B is :%10.3f\n", i, b[ i ] );
	}

	for( i = 0; i <= pointNUM; i++ ){
		printf( "Enter the %d number of X: ", i + 1);
		x[ i ] = i;
		xx[ i ] = x[ i ] * 46;
		printf( "%d\n", xx[ i ] );
	}

	for( i = 0; i <= pointNUM; i++ ){
		printf( "Enter the %d number of Y: ", i + 1);
		y[ i ] =(int)( 460 - b[ i ] * 46 );
		printf( "%d\n", y[ i ] );
	}
	printf( "\n\n\npass any key to draw the function line..." );
	getch();

	initgraph( &drive, &mode, "" );
	setbkcolor( BLUE );
	cleardevice();
	drawX();
	drawY();

	for( i = 0; i < pointNUM; i++ ){
		cleardevice();
		drawX();
		drawY();
		moveto( xx[ i + 1 ], y[ i + 1 ] );
		outtext( "*" );
		msDelay( 1000000 );
	}

	for( i = 0; i < pointNUM; i++ ){
		moveto( xx[ i + 1 ], y[ i + 1 ] );
		outtext( "*" );
		line( xx[ i ], y[ i ], xx[ i + 1], y[ i + 1 ] );
	}

	getch();
	closegraph();

}

void msDelay(unsigned int Delay) 
{ 
	unsigned int i; 
	for(;Delay> 0;Delay--) { 
		for(i=0;i <124;i++) { 
				; 
		} 
	} 
}

void matrix_inversion_using_element_operation( float coeff[20][20], float inv_coeff[20][20], int num_eq )
{
	{
		int row, column, pivot_column, max_index;
		float max_value, ftemp1, ftemp2, pivot_value;

		for( row = 0; row < num_eq; row++ )
			for( column = 0; column < num_eq; column++ ){
				if( row == column )
					inv_coeff[row][column] = 1;
				else
					inv_coeff[row][column] = 0;
			}

			for( pivot_column = 0; pivot_column < num_eq; pivot_column++ ){
				max_index = coeff[0][column];
				max_value = 0;

				for( row = pivot_column; row < num_eq; row++ )
					if( coeff[row][pivot_column]*coeff[row][pivot_column] > max_value*max_value ){
						max_index = row;
						max_value = coeff[row][pivot_column];
					}

					if(pivot_column != max_index )
						for( column = 0; column < num_eq; column++ ){
							ftemp1 = coeff[pivot_column][column];
							ftemp2 = inv_coeff[pivot_column][column];

							coeff[pivot_column][column] = coeff[max_index][column];
							
							inv_coeff[pivot_column][column] = inv_coeff[max_index][column];
							coeff[max_index][column] = ftemp1;
							inv_coeff[max_index][column] = ftemp2;
						}

						pivot_value = coeff[pivot_column][pivot_column];
						for(column = 0; column < num_eq; column++ ){
							coeff[pivot_column][column] /= pivot_value;
							inv_coeff[pivot_column][column] /= pivot_value;

						}

						for( row = 0; row < num_eq; row++ )
							if( row != pivot_column ){
								ftemp1 = coeff[row][pivot_column];
								for( column = 0; column < num_eq; column++ ){

									coeff[row][column] -= ftemp1*coeff[pivot_column][column];
									inv_coeff[row][column] -= ftemp1*inv_coeff[pivot_column][column];

								}
							}
			}
	}
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
