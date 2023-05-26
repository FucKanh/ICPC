//Link: https://practice.geeksforgeeks.org/problems/longest-common-substring1452/1

// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution{
    public:

    int longestCommonSubstr (string S1, string S2, int n, int m)
    {
        // your code here
        int f[n + 1][m + 1] = {0};
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (S1[i - 1] == S2[j - 1])
                    f[i][j] = f[i - 1][j - 1] + 1;
        return *max_element(&f[0][0], &f[0][0] + (n + 1) * (m + 1));
    }
};

//{ Driver Code Starts.

int main()
{
    int t; cin >> t;
    while (t--)
    {
        int n, m; cin >> n >> m;
        string s1, s2;
        cin >> s1 >> s2;
        Solution ob;

        cout << ob.longestCommonSubstr (s1, s2, n, m) << endl;
    }
}
// Contributed By: Pranay Bansal

// } Driver Code Ends
