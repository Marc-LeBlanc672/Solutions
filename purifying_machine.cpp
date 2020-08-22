#include <iostream>
#include <cstdio>
#include <cstring> 
#include <algorithm>
#include <cstdlib> 
#include <cmath>         
using namespace std ;
const int MAXN = 1e3 + 1 , MAXM = 1e6 + 1 ;
int Head[ MAXN ] , N , M , K , cnt = 0 , ans = 0 , used[ MAXN ] ;
bool visit[ MAXN ] ;
int n , m ;
char c[ MAXN ][ 10 ] ;
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
		if( visit[ y ] == false ){
			visit[ y ] = true ;
			if( used[ y ] == false || DFS( used[ y ] ) == true ){
				used[ y ] = x ;
				return true ;
			}
		}
	}
	return false ;
}


inline bool cmp( int x , int y ){
	int tot = 0 ;
	for( int i = 0 ; i < n ; i ++ ){
		if( c[ x ][ i ] != c[ y ][ i ] ){
			tot ++ ;
			if( tot > 1 ){
				return false ;
			}
		}
	}
	return true ;
}

inline void check( int x ){
	for( int i = 0 ; i < n ; i ++ ){
		if( c[ x ][ i ] == '*' ){
			c[ x ][ i ] = '1' ;
			m ++ ;
			for( int j = 0 ; j < n ; j ++ ){
				c[ m ][ j ] = c[ x ][ j ] ;
			}
			c[ m ][ i ] = '0' ;
		}
	}
}

int main(){
	while( scanf( "%d%d" , &n , &M ) != EOF && n && M ){
		m = 0 ;
		cnt = 0 ;
		for( int i = 1 ; i <= M ; i ++ ){
			m ++ ;
			cin >> c[ m ] ;
			check( m ) ;
		}
		int x = 0 ;
		for( int i = 1 ; i <= m ; i ++ ){
			int flag = 0 ;
			for( int j = 1 ; j <= x ; j ++ ){
				flag = 1 ;
				for( int k = 0 ; k < n ; k ++ ){
					if( c[ i ][ k ] != c[ j ][ k ] ){
						flag = 0 ;
						break ;
					}
				}
				if( flag ){
					break ;
				}
			}
			if( !flag ){
				memcpy( c[ ++ x ] , c[ i ] , sizeof( c[ i ] ) ) ;
			}
		}
		m = x ;
		for( int i = 1 ; i <= m ; i ++ ){
			for( int j = 1 ; j <= m ; j ++ ){
				if( i != j && cmp( i , j ) ){
					AddEdge( i , j ) ;
				}
			}
		}
	
		ans = 0 ;
	for( int i = 1 ; i <= m ; i ++ ){
		for( int j = 1 ; j <= m ; j ++ ){
			visit[ j ] = 0 ;
		} 
		if( DFS( i ) ){
			ans ++ ;
		}
	}
		printf( "%d\n" , m - ans / 2 ) ;
		for( int i = 1 ; i <= m ; i ++ ){
			used[ i ] = Head[ i ] = 0 ;
		}
	}
	return 0 ;
}
