//Link: https://practice.geeksforgeeks.org/problems/maximum-difference-of-zeros-and-ones-in-binary-string4111/1

//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
//User function template for C++
class Solution
{
    public:
    int maxSubstring ( string S )
    {
        // Your code goes here
        int ans = -1e9 , s = 0;
        for ( int i = 1; i <= S.size ( ); ++i )
        {
            s += ( S [ i - 1 ] == '0' ? 1 : -1 );
            ans = max ( ans , s );
            s = max ( s , 0 );
        }
        return ans;
    }
};

//{ Driver Code Starts.

int main ( )
{


    ios_base::sync_with_stdio ( 0 );
    cin.tie ( NULL );
    cout.tie ( NULL );

    int t;
    cin >> t;
    while ( t-- )
    {
        string s;
        cin >> s;

        Solution ob;

        cout << ob.maxSubstring ( s ) << "\n";
    }

    return 0;
}

// } Driver Code Ends
