//Link: https://practice.geeksforgeeks.org/problems/edit-distance3702/1

//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{
    public:
    int editDistance ( string s , string t )
    {
// Code here
        int n = s.size ( ) , m = t.size ( );
        int f [ n + 1 ][ m + 1 ] = { 0 };
        memset ( f , 0 , sizeof ( f ) );
        for ( int i = 1; i <= n; ++i )
            f [ i ][ 0 ] = i;
        for ( int i = 1; i <= m; ++i )
            f [ 0 ][ i ] = i;
        for ( int i = 1; i <= n; ++i )
            for ( int j = 1; j <= m; ++j )
                f [ i ][ j ] = min ( { f [ i - 1 ][ j - 1 ] + ( s [ i - 1 ] != t [ j - 1 ] ), f [ i - 1 ][ j ] + 1, f [ i ][ j - 1 ] + 1 } );
        return f [ n ][ m ];
    }
};

//{ Driver Code Starts.
int main ( )
{
    int T;
    cin >> T;
    while ( T-- )
    {
        string s , t;
        cin >> s >> t;
        Solution ob;
        int ans = ob.editDistance ( s , t );
        cout << ans << "\n";
    }
    return 0;
}

// } Driver Code Ends
