/** Solution:
1. Make another graph with double amount of vertices, which is normal successor graph.
2. Determine if P which leads to minimum edge is in the cycle, the same with another P' which leads to subminimum edge.
3. For each vertex find amount of trails which lead to P and to P'.
4. For each query go through all vertices and check if amount of trails matches with required one for P or P'.
**/
#include "garden.h"
#include "gardenlib.h"
#include <bits/stdc++.h>

using namespace std;
const int MX = 150000;
int g[2 * MX];
int cycle[2 * MX];
char vis[2 * MX];
int turns[2 * MX][2];

void dfs(int cur, int z) {
	if (cycle[cur] != -1) {
		turns[cur][z] = cycle[cur];
		return;
	}
	
	vis[cur] = 1;
	if (!vis[g[cur]])
		dfs(g[cur], z);
	turns[cur][z] = turns[g[cur]][z] + 1;
}

void count_routes(int N, int M, int P, int R[][2], int Q, int G[]) {
	int fs[N], sc[N];
	for (int i = 0; i < N; i++)
		fs[i] = -1;
	for (int i = M - 1; i >= 0; i--) {
		sc[R[i][1]] = fs[R[i][1]];
		fs[R[i][1]] = R[i][0];
		sc[R[i][0]] = fs[R[i][0]];
		fs[R[i][0]] = R[i][1];
	}
	
	for (int i = 0; i < 2 * N; i++) 
		if (i >= N) {
			if (sc[i - N] == -1)
				g[i] = g[i - N];
			else if (fs[sc[i - N]] == i - N)
				g[i] = sc[i - N] + N;
			else
				g[i] = sc[i - N];
		} else {
			if (fs[fs[i]] == i)
				g[i] = fs[i] + N;
			else
				g[i] = fs[i];
		}
	
	int cycleSize[2];
	for (int z = 0; z < 2; z++) {
		for (int i = 0; i < 2 * N; i++)
			cycle[i] = -1;
		memset(vis, 0, sizeof vis);
		for (int i = 0; i < 2 * N; i++)
			turns[i][z] = 2000000000;
		
		cycleSize[z] = 0;
		int cur = P + N * z;
		while (!vis[cur]) {
			vis[cur] = 1;
			cycle[cur] = cycleSize[z]++;
			cur = g[cur];
		}
		
		for (int i = 0; i < 2 * N; i++)
			if (cycle[i] != -1)
				cycle[i] = (cycleSize[z] - cycle[i]) % cycleSize[z];
		
		if (cur != P + N * z) { //P is not in cycle
			for (int i = 0; i < 2 * N; i++)
				cycle[i] = -1;
			cycle[P + N * z] = 0;
			cycleSize[z] = 1;
		}
		
		memset(vis, 0, sizeof vis);
		for (int i = 0; i < 2 * N; i++)
			if (!vis[i])
				dfs(i, z);
	}
	
	//for (int i = 0; i < 2 * N; i++)
		//cout << i << ": " << turns[i][0] << " " << turns[i][1] << " " << g[i] << " " << fs[i] << " " << sc[i] << endl;
	
	for (int i = 0; i < Q; i++) {
		int ans = 0;
		for (int j = 0; j < N; j++)
			ans += ((turns[j][0] == G[i] ||
					(cycleSize[0] > 1 && G[i] >= turns[j][0] && (G[i] - turns[j][0]) % cycleSize[0] == 0)) ||
					(turns[j][1] == G[i] ||
					(cycleSize[1] > 1 && G[i] >= turns[j][1] && (G[i] - turns[j][1]) % cycleSize[1] == 0)));
		
		answer(ans);
	}
}
