// link: https://practice.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1?page=1&category[]=Graph&sortBy=submissions

//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends

class Solution {
  public:
    int ans=0;
    int vst[100001];
    // Function to detect cycle in an undirected graph.
    void check(int u, int pa, vector<int> adj[]) {
        vst[u] = 1;
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (v ==pa) continue;
            if (vst[v]) ans = 1;
            else check(v,u,adj);
            if (ans) return;
        }
    }
    bool isCycle(int V, vector<int> adj[]) {
        for (int i = 0; i < V; i++) vst[i] = 0;
        for (int i = 0; i < V; i++) {
            if (!vst[i]) check(i,-1,adj);
            if (ans) break;
        }   
        return ans;
    }
};

//{ Driver Code Starts.
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int V, E;
        cin >> V >> E;
        vector<int> adj[V];
        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        Solution obj;
        bool ans = obj.isCycle(V, adj);
        if (ans)
            cout << "1\n";
        else
            cout << "0\n";
    }
    return 0;
}
// } Driver Code Ends
