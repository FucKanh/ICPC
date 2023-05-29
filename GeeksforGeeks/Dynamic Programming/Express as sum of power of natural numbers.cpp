//Link: https://practice.geeksforgeeks.org/problems/express-as-sum-of-power-of-natural-numbers5647/1

//{ Driver Code Starts
// Initial Template for C++


#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
//User function Template for C++
class Solution
{
    public:
    int pow ( int a , int b )
    {
        if ( b == 0 )
            return 1;
        if ( a == 0 || b == 1 )
            return a;
        int ans = 1;
        while ( b )
        {
            if ( b & 1 )
                ans *= a;
            a *= a;
            b >>= 1;
        }
        return ans;
    }
    int numOfWays ( int n , int x )
    {
        // code here
        int f [ n + 1 ] , mod = 1e9 + 7;
        memset ( f , 0 , sizeof ( f ) );
        f [ 0 ] = 1;
        for ( int val = 1 , i = 1; val <= n; ++i , val = pow ( i , x ) )
            for ( int j = n; j >= val; --j )
                ( f [ j ] += f [ j - val ] ) %= mod;
        return f [ n ];
    }
};

//{ Driver Code Starts.
int main ( )
{
    int t;
    cin >> t;
    while ( t-- )
    {
        int  n , x;
        cin >> n >> x;
        Solution ob;
        cout << ob.numOfWays ( n , x ) << endl;
    }
    return 0;
}

// } Driver Code Ends
