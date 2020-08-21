#include <iostream>
#include <cstdio>
#include <cstring> 
using namespace std ;

const int MAXN = 1e3 + 1 , MAXM = 1e6 + 1 ;
int Head[ MAXN ] , N , M , K , cnt = 0 , ans = 0 , used[ MAXN ] ;
bool visit[ MAXN ] ;
struct Edge{
	int u , v ;
}Graph[ MAXM ] ;

inline int read(){
	int x = 0 , f = 1  ;
	char c = getchar() ;
	while( c < '0' || c > '9' ){
		if( c == '-' ){
			f = -1 ;
		}
		c = getchar() ;
	}
	while( c <= '9' && c >= '0' ){
		x = ( x << 1 ) + ( x << 3 ) + ( c ^ 48 ) ;
		c = getchar() ;
	}
	return f * x ;
}

inline void AddEdge( int u , int v ){
	Graph[ ++ cnt ].u = v ;
	Graph[ cnt ].v = Head[ u ] ;
	Head[ u ] = cnt ;
}

inline bool DFS( int x ){
	for( int i = Head[ x ] ; i ; i = Graph[ i ].v ){
		int y = Graph[ i ].u ;
		if( visit[ y ] == true ){
			visit[ y ] = false ;
			if( used[ y ] == false || DFS( used[ y ] ) == true ){
				used[ y ] = x ;
				return true ;
			}
		}
	}
	return false ;
}

inline void scan(){
	N = read() , K = read() ;
	M = N ;
	for( int i = 1 ; i <= K ; i ++ ){
		int x , y ;
		x = read() , y = read() ;
		if( x > N || y > M ){
			continue ;
		}
		AddEdge( x , y ) ;
	}
}

inline void Hungary(){
	memset( used , 0 , sizeof( used ) ) ;
	for( int i = 1 ; i <= N ; i ++ ){
		memset( visit , true , sizeof( visit ) ) ;
		if( DFS( i ) == true ){
			ans ++ ;
		}
	}
}

int main(){
	scan() ;
	Hungary() ;
	printf( "%d" , ans ) ;
	return 0 ;
}
