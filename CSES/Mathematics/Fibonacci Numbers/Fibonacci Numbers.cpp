//Link: https://cses.fi/problemset/task/1722

#include <bits/stdc++.h>

#define endl "\n"
#define int unsigned long long
#define mod (int) (1e9 + 7)

using namespace std;

int n , f [ 2 ][ 2 ] = { {0, 1}, {1, 1} } , ans [ 2 ][ 2 ] = { {1, 1}, {1, 1} };

signed main ( )
{
	cin >> n;

	if ( !n )
		ans [ 0 ][ 0 ] = 0;

	( n ) ? --n : n;
  
  /*
	Nhân Ma Trận O(logn)
	     n
	[0 1]    = [Fn+1 Fn]
	[1 1]	   [Fn Fn+1]

	=>
	     n-1
	[0 1]	 = [Fn Fn-1]
	[1 1]	   [Fn-1 Fn]
  */
  
	while ( n )
	{
		int x , y , z , t;

		if ( n & 1 )
		{
			( x = ( ans [ 0 ][ 0 ] * f [ 0 ][ 0 ] ) % mod + ( ans [ 0 ][ 1 ] * f [ 1 ][ 0 ] ) % mod ) %= mod;
			( y = ( ans [ 0 ][ 0 ] * f [ 0 ][ 1 ] ) % mod + ( ans [ 0 ][ 1 ] * f [ 1 ][ 1 ] ) % mod ) %= mod;
			( z = ( ans [ 1 ][ 0 ] * f [ 0 ][ 0 ] ) % mod + ( ans [ 1 ][ 1 ] * f [ 1 ][ 0 ] ) % mod ) %= mod;
			( t = ( ans [ 1 ][ 0 ] * f [ 0 ][ 1 ] ) % mod + ( ans [ 1 ][ 1 ] * f [ 1 ][ 1 ] ) % mod ) %= mod;

			ans [ 0 ][ 0 ] = x;
			ans [ 0 ][ 1 ] = y;
			ans [ 1 ][ 0 ] = y;
			ans [ 1 ][ 1 ] = z;
		}

		( x = ( f [ 0 ][ 0 ] * f [ 0 ][ 0 ] ) % mod + ( f [ 0 ][ 1 ] * f [ 1 ][ 0 ] ) % mod ) %= mod;
		( y = ( f [ 0 ][ 0 ] * f [ 0 ][ 1 ] ) % mod + ( f [ 0 ][ 1 ] * f [ 1 ][ 1 ] ) % mod ) %= mod;
		( z = ( f [ 1 ][ 0 ] * f [ 0 ][ 0 ] ) % mod + ( f [ 1 ][ 1 ] * f [ 1 ][ 0 ] ) % mod ) %= mod;
		( t = ( f [ 1 ][ 0 ] * f [ 0 ][ 1 ] ) % mod + ( f [ 1 ][ 1 ] * f [ 1 ][ 1 ] ) % mod ) %= mod;

		f [ 0 ][ 0 ] = x;
		f [ 0 ][ 1 ] = y;
		f [ 1 ][ 0 ] = z;
		f [ 1 ][ 1 ] = t;

		n >>= 1;
	}

	cout << ans [ 0 ][ 0 ] << endl;
}
