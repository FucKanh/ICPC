//Link: https://practice.geeksforgeeks.org/problems/allocate-minimum-number-of-pages0937/1

//{ Driver Code Starts
// Initial template for C++

#include<bits/stdc++.h>
using namespace std;


// } Driver Code Ends
//User function template in C++

class Solution
{
    public:
    //Function to find minimum number of pages.
#define ll long long
    ll findPages ( int arr [ ] , int n , int m )
    {
        //code here
        if ( m > n )
            return -1;
        ll low = 0 , high = 0;
        for ( int i = 1; i <= n; ++i )
        {
            low = max ( low , ( ll ) arr [ i - 1 ] );
            high += arr [ i - 1 ];
        }
        while ( low < high )
        {
            ll mid = ( low + high ) / 2;
            ll s = 0 , cnt = 1;
            bool chk = 1;
            for ( int i = 1; i <= n && chk; ++i )
            {
                if ( arr [ i - 1 ] <= mid )
                    s += arr [ i - 1 ];
                if ( s > mid )
                {
                    ++cnt;
                    s = arr [ i - 1 ];
                }
                if ( arr [ i - 1 ] > mid || cnt > m )
                    chk = 0;
            }
            if ( chk )
                high = mid;
            else
                low = mid + 1;
        }
        return low;
    }
};

//{ Driver Code Starts.

int main ( )
{
    int t;
    cin >> t;
    while ( t-- )
    {
        int n;
        cin >> n;
        int A [ n ];
        for ( int i = 0; i < n; i++ )
        {
            cin >> A [ i ];
        }
        int m;
        cin >> m;
        Solution ob;
        cout << ob.findPages ( A , n , m ) << endl;
    }
    return 0;
}

// } Driver Code Ends
