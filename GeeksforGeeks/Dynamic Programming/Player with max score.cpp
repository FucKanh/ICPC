//Link: https://practice.geeksforgeeks.org/problems/player-with-max-score/1

//{ Driver Code Starts
//Initial template for C++

#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends
//User function Template for C++

class Solution
{
    public:
    bool is1winner ( int n , int arr [ ] )
    {
#define ll long long
// code here
        ll f [ n + 2 ][ n + 2 ] = { 0 };
        for ( ll i = n; i >= 1; --i )
            for ( ll j = i; j <= n; ++j )
                if ( ( ( j - i + 1 ) & 1 ) == ( n & 1 ) )
                    f [ i ][ j ] = max ( f [ i + 1 ][ j ] + arr [ i - 1 ] , f [ i ][ j - 1 ] + arr [ j - 1 ] );
                else
                    f [ i ][ j ] = min ( f [ i + 1 ][ j ] - arr [ i - 1 ] , f [ i ][ j - 1 ] - arr [ j - 1 ] );
        return ( f [ 1 ][ n ] >= 0 );
    }
};

//{ Driver Code Starts.
int main ( )
{
    int t;
    cin >> t;
    while ( t-- )
    {
        int N , X;
        cin >> N;
        int arr [ N ];
        for ( int i = 0; i < N; i++ )
        {
            cin >> arr [ i ];
        }

        Solution ob;
        cout << ob.is1winner ( N , arr ) << endl;
    }
    return 0;
}

// } Driver Code Ends
