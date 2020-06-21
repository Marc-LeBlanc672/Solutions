#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std ;
const double pai = acos( -1.0 ) ;
const int MAX = 5e5 + 1 ;
int N , limit = 1 , L , R[ MAX ] ; 
struct complex{
	double Real ;
	double Virtual_Part ;
	complex ( double x = 0 , double y = 0 ) { Real = x , Virtual_Part = y ; } 
}a[ MAX ] , b[ MAX ] , c[ MAX ] ;
//double _a[ MAX ] ;
inline int read(){
	char c = getchar () ;
	int f = 1 , x = 0 ;
	while( c < '0' || c > '9' ){
		if( c == '-' ){
			f = -1 ;
		}
		c = getchar () ;
	}
	while( c <= '9' && c >= '0' ){
		x = ( x << 3 ) + ( x << 1 ) + ( c ^ 48 ) ;
		c = getchar () ;
	}
	return f * x ;
} 

complex operator + ( complex a , complex b ) { return complex( a.Real + b.Real , a.Virtual_Part + b.Virtual_Part ) ; }
complex operator - ( complex a , complex b ) { return complex( a.Real - b.Real , a.Virtual_Part - b.Virtual_Part ) ; }
complex operator * ( complex a , complex b ) { return complex( a.Real * b.Real - a.Virtual_Part * b.Virtual_Part , a.Real * b.Virtual_Part + a.Virtual_Part * b.Real ) ; }



inline void FFT ( complex *s , int type ){
	for( register int i = 0 ; i < limit ; i ++ ){
		if( i < R[ i ] ) {
			swap( s[ i ] , s[ R[ i ] ] ) ;
		}
	}
	for( register int middle = 1 ; middle < limit ; middle <<= 1 ){
		complex Plural( cos( pai / middle ) , type * sin( pai / middle ) ) ;
		for( register int r = middle << 1 , j = 0 ; j < limit ; j += r ){
			complex temple( 1 , 0 ) ;
			for( register int k = 0 ; k < middle ; k ++ , temple = temple * Plural ) {
				complex x = s[ j + k ] ;
				complex y = temple * s[ j + middle + k ] ;
				s[ j + k ] = x + y ;
				s[ j + middle + k ] = x - y ;
			}
		}
	}
	if( type == -1 ){
		for( register int i = 0 ; i < limit ; i ++ ){
			s[ i ].Real /= limit ;
		}
	}
	return ;
}


int main(){
	N = read() ;
	for( int i = 1 ; i <= N ; i ++ ){
		scanf( "%lf" , &a[ i ].Real ) ;
		c[ N - i ].Real = a[ i ].Real ;
		b[ i ].Real = ( double )( 1.0 / i / i ) ;
	}
	while( limit <= ( N << 1 ) ){
		limit <<= 1 ;
		++ L ;
	}
	for( register int i = 0 ; i < limit ; i ++ ){
		R[ i ] = ( R[ i >> 1 ] >> 1 ) | ( ( i & 1 ) << ( L - 1 ) ) ;
	}
	FFT ( a , 1 ) ;
	FFT ( b , 1 ) ;
	FFT ( c , 1 ) ;
	for( register int i = 0 ; i < limit ; i ++ ){
		a[ i ] = a[ i ] * b[ i ] ;
		c[ i ] = c[ i ] * b[ i ] ;
	}
	FFT( a , -1 ) ;
	FFT( c , -1 ) ;
	for( register int i = 1 ; i <= N ; i ++ ){
		printf( "%.3lf\n" , a[ i ].Real - c[ N - i ].Real ) ;
	}
	return 0 ;
}
/*
5
4006373.885184
15375036.435759
1717456.469144
8514941.004912
1410681.345880

-16838672.693
3439.793
7509018.566
4595686.886
10903040.872
*/
