#include <iostream>
#include <cstdio>
#include <cstring> 
using namespace std ;

const int MAX = 550 ;

inline int read(){
	int f = 1 , x = 0 ;
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

struct Edge{
	int to , next ;
}Graph[ MAX * MAX * 4 ] ;
bool visit[ MAX ] ;
int match[ MAX ] , Head[ MAX ] ;

bool DFS( int u ){
	for( int i = Head[ u ] ; i ; i = Graph[ i ].next ){
		int v = Graph[ i ].to ;
		if( !visit[ v ] ){
			visit[ v ] = 1 ;
			if( !match[ v ] || DFS( match[ v ] ) ){
				match[ v ] = u ;
				return true ;
			}
		}
	}
	return false ;
}
int N , M , K , cnt = 1 ;
void AddEdge( int x , int y ){
	Graph[ ++ cnt ].to = y ;
	Graph[ cnt ].next = Head[ x ] ;
	Head[ x ] = cnt ;
}

int main(){
	int t , a , b ;
	while( true ){
		N = read() ;
		if( N == 0 ){
			break ;
		}
		M = read() , K = read() ;
		memset( Graph , 0 , sizeof( Graph ) ) ;
		cnt = 1 ;
		memset( Head , 0 , sizeof( Head ) ) ;
		memset( match , 0 , sizeof( match ) ) ;
		for( int i = 1 ; i <= K ; i ++ ){
			t = read() , a = read() , b = read() ;
			if( a == 0 || b == 0 ){
				continue ;
			} 
			AddEdge( a , b + N ) ;
			AddEdge( b + N , a ) ;
		}
		int ans = 0 ;
		for( int i = 0 ; i < N ; i ++ ){
			memset( visit , 0 , sizeof( visit ) ) ;
			if( DFS( i ) ){
				ans ++ ;
			}
		}
		printf( "%d\n" , ans ) ;
	}
	
	return 0 ;
}
