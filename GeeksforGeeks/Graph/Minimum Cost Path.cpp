//Link: https://practice.geeksforgeeks.org/problems/minimum-cost-path3833/1

//{ Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends


class Solution
{
    public:
#define pii pair <int, int>
#define piii pair <int, pii>
#define fi first
#define se second
#define mp make_pair
//Function to return the minimum cost to react at bottom
//right cell from top left cell.
    int minimumCostPath ( vector<vector<int>>& grid )
    {
        // Code here
        priority_queue <piii , vector <piii> , greater <piii>> pq;
        int n = grid.size ( );
        pii dir [ 4 ] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
        int f [ n + 1 ][ n + 1 ] = { 0 }; memset ( f , 0x7f , sizeof ( f ) );
        bool vst [ n + 1 ][ n + 1 ] = { 0 }; memset ( vst , 0 , sizeof ( vst ) );
        f [ 1 ][ 1 ] = grid [ 0 ][ 0 ];
        pq.push ( mp ( f [ 1 ][ 1 ] , mp ( 1 , 1 ) ) );
        while ( !pq.empty ( ) )
        {
            pii u = pq.top ( ).se; pq.pop ( );
            if ( u == mp ( n , n ) )
                break;
            if ( vst [ u.fi ][ u.se ] )
                continue;
            vst [ u.fi ][ u.se ] = 1;
            for ( int i = 1; i <= 4; ++i )
            {
                pii v = { u.fi + dir [ i - 1 ].fi, u.se + dir [ i - 1 ].se };
                if ( 1 <= v.fi && v.fi <= n &&
                    1 <= v.se && v.se <= n &&
                    !vst [ v.fi ][ v.se ] )
                {
                    int w = f [ u.fi ][ u.se ] + grid [ v.fi - 1 ][ v.se - 1 ];
                    if ( w < f [ v.fi ][ v.se ] )
                    {
                        f [ v.fi ][ v.se ] = w;
                        pq.push ( mp ( f [ v.fi ][ v.se ] , v ) );
                    }
                }
            }
        }
        return f [ n ][ n ];
    }
};

//{ Driver Code Starts.
int main ( )
{
    int tc;
    cin >> tc;
    while ( tc-- )
    {
        int n;
        cin >> n;
        vector<vector<int>>grid ( n , vector<int> ( n , -1 ) );
        for ( int i = 0; i < n; i++ )
        {
            for ( int j = 0; j < n; j++ )
            {
                cin >> grid [ i ][ j ];
            }
        }
        Solution obj;
        int ans = obj.minimumCostPath ( grid );
        cout << ans << "\n";
    }
    return 0;
}
// } Driver Code Ends
