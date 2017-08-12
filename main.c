
#include <stdio.h>
#include <stdlib.h>
#define eps 0.00001

double f( double x ); 
float ermit( double( * fun )( double x ), double * Enter, int n, double t);
int main()
{    
    int i = 0;
    double otvet, coord;
    double abscissa[5];
    char filename[256];
    FILE *fin;
    printf("Enter filename -> ");
    scanf("%s", filename);
    fin=fopen(filename, "r");
    if ( !fin ) {
        printf( "Can't open %s\n", filename );
        return 0;
    }
    while ( fscanf( fin, "%lf", & abscissa[i] ) == 1 ) i++;
    printf( "Vvedite x -> " );
    scanf( "%lf", & coord );
    printf( "\n" );
    otvet = ermit(f, abscissa, i, coord);
    printf( "\n" );
    printf( "Result = %lf", otvet) ;
    return 0;
}

float ermit( double( * fun )( double x ), double * Enter, int n, double t )
{   
    float y = 0, Der = 1, sum = 0;
    int i = 0, j = 0;
    double Line[20], Matrix[20][20];
    for ( i = 0; i < 2 * n; i = i + 2 )
    {    
        Line[i] = Enter[j];
        Line[i + 1] = Enter[j];
        j++;
    }  
        for ( j = 0; j < 2 * n; j++ )
        {
            Matrix[0][j] = fun ( Line[j] );
        }
    for ( j = 0; j < 2 * n; j++ )
        {
            if (j < ( 2 * n - 1 ) ) {
                if ( Line[j] == Line[j + 1] ) {
                    Matrix[1][j] = ( fun ( Line[j] + eps ) - fun( Line[j] ) ) / eps;
                } else {
                    Matrix[1][j] = ( fun ( Line[j + 1] ) - fun ( Line[j] ) ) / ( Line[j + 1] - Line[j] );
                }
            }
        }
    for ( i = 2; i < 2 * n; i++ )
        for ( j = 0; j < 2 * n; j++ )
            if ( j < ( 2 * n - i ) ) 
                Matrix[i][j]=(Matrix[i-1][j+1]-Matrix[i-1][j])/(Line[j+i]-Line[j]);
        
    /// 
//  for (i = 0; i < 2*n; i++ ) {
//      for (j = 0; j < 2*n; j++ )
//          printf("m[%d][%d]=%lf ",i,j,Matrix[i][j]); 
//      printf("\n");
//  }
    /// 
        
    printf( "Interpolation polynomial is " );
    for ( j = 0; j < 2 * n; j++ )
        {
            for ( i = 0; i < j; i++ )
            {
               Der = Der * ( t - Line[i] );
               printf( "( x - ( %lf ) ) * ", Line[i] );
            }
            printf( "( %lf ) + ", Matrix[j][0] );
            sum = sum + Matrix[j][0] * Der ;
            Der = 1;
        }
    return sum;
}

double f(double x)
{
    return ( x * x * x + x * x - 10 * x + 2 );
}
