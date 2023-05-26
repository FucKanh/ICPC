//Link: https://practice.geeksforgeeks.org/problems/the-painters-partition-problem1535/1

//{ Driver Code Starts
// driver code

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
//User function template for C++
#pragma GCC optimize("Ofast", "unroll-loops")
#pragma GCC target("avx512f")
class Solution
{
  public:
    #define ll long long
    ll minTime(int arr[], int n, int m)
    {
        // code here
        // return minimum time
        m = min(m, n);
        ll ans, low = 0, high = 0;
        for (int i = 1; i <= n; ++i)
        {
            low = max(low, (ll) arr[i - 1]);
            high += arr[i - 1];
        }
        ans = high;
        while (low <= high)
        {
            ll mid = (low + high) / 2;
            ll s = 0, cnt = 1;
            bool chk = 1;
            for (int i = 1; i <= n && chk; ++i)
            {
                if (arr[i - 1] <= mid)
                    s += arr[i - 1];
                if (s > mid)
                {
                    ++cnt;
                    s = arr[i - 1];
                }
                if (arr[i - 1] > mid || cnt > m)
                    chk = 0;
            }
            if (chk)
            {
                ans = min(ans, mid);
                high = mid - 1;
            }
            else
                low = mid + 1;
        }
        return ans;
    }
};

//{ Driver Code Starts.

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int k,n;
		cin>>k>>n;

		int arr[n];
		for(int i=0;i<n;i++)
		    cin>>arr[i];
		Solution obj;
		cout << obj.minTime(arr, n, k) << endl;
	}
	return 0;
}
// } Driver Code Ends
