//Link: https://practice.geeksforgeeks.org/problems/expression-add-operators/1

//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution {
	  public:
		#define ll long long
		#define eb emplace_back
    	vector <string> a;
    	string S;
    	ll x;
    	void Backtrack(ll i = 0, ll sum = 0, ll s = 0, ll num = 0, ll mul = 0, string str = "", string sym = "")
    	{
        	if (i == S.size())
        	{
            	sum += s;
            	if (sum == x)
                	a.eb(str);
        	}
        	else
        	{
            	if (sym != "*")
                	Backtrack(i + 1, sum, 10 * s + (s >= 0 ? 1 : -1) * (S[i] - '0'), 10 * s + (s >= 0 ? 1 : -1) * (S[i] - '0'), 10 * s + (s >= 0 ? 1 : -1) * (S[i] - '0'), str + S[i], sym);
            	else
                	Backtrack(i + 1, sum, mul * (10 * num + (S[i] - '0')), 10 * num + (S[i] - '0'), mul, str + S[i], sym);
            	if (i && S[i] != '0')
            	{
                	Backtrack(i + 1, sum + s, S[i] - '0', S[i] - '0', S[i] - '0', str + "+" + S[i], "+");
                	Backtrack(i + 1, sum, s * (S[i] - '0'), S[i] - '0', s, str + "*" + S[i], "*");
                	Backtrack(i + 1, sum + s, -(S[i] - '0'), -(S[i] - '0'), -(S[i] - '0'), str + "-" + S[i], "-");
            	}
        	}
        	return;
    	}
    	vector<string> addOperators(string str, int target) {
        	// code here
        	a.clear();
        	S = str;
        	x = target;
        	Backtrack();
        	return a;
    	}
};

//{ Driver Code Starts.

int main() {
		int t;
		cin >> t;
		while (t--) {
			int target;
			string S;
			cin >> S >> target;

			Solution obj;
			vector<string> ans = obj.addOperators(S, target);
			sort(ans.begin(), ans.end());
			for (auto &it : ans) cout << it << ' ';
			cout << endl;
		}
		return 0;
}
// } Driver Code Ends
