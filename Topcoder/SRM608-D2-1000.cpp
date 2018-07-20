#include <bits/stdc++.h>
using namespace std;
/**
Solution:
There are 2 known non-polynomials which exceed any possible polynomail: 2 ^ n and n!.
Let's look at 2 ^ n. It happens if and only if
there are at least 2 different cycles which have at least one common vertex.

So, I can simply brute force that common vertex, then brute force all cycles
which this vertex has. If amount of cycles >= 2, then answer is "Unbounded".

Time complexity: O(n ^ 3).
**/

const int N = 50;
int n;
vector<int> g[N];
bool vis[N];
bool hasCycle(int cur, int whereToEnd) {
    vis[cur] = 1;
    bool res = 0;
    for (int i : g[cur]) {
        if (i == whereToEnd)
        	return 1;
       	if (!vis[i])
            res |= hasCycle(i, whereToEnd);
    }
    
    return res;
}
struct BigOEasy {
  	  string isBounded(vector <string> graph) {
          	int n = graph.size();
          	for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                	if (graph[i][j] == 'Y')
                		g[i].push_back(j);
           	
            for (int i = 0; i < n; i++)
                if (g[i].size() >= 2) {
                	int cycles = 0;
                    for (int j : g[i]) {
                        for (int k = 0; k < n; k++)
                			vis[k] = 0;
                        
                        if (hasCycle(j, i))
                            cycles++;
                    }
                
                	if (cycles >= 2)
                        return "Unbounded";
                }
           
            return "Bounded";
      }
};