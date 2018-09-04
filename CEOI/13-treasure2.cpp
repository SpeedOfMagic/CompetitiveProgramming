#include "treasure.h"
#include <bits/stdc++.h>
using namespace std;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
/** Solution:
1. I want to prove that I need to make at least N * N queries.
2. Then, I want to make those queries take as least energy as possible, =>
I will go through all points and get largest possible rectangle.
3. After that, I want to calculate prefix-sum of subrectangle for each point. To do that,
and calculate prefix-sum based on which quarter this point is located.
4. Then, It's easy to find out whether some point has treasure or not.
Time complexity: O(n ^ 2).
**/
/**
01
23
**/
int n;
int quarter(int r, int c) { return (r > n / 2) * 2 + (c > n / 2); }
	
void findTreasure (int N) {
	n = N;
	int pref[n + 1][n + 1];
	memset(pref, 0, sizeof(pref));
	for (int i = n; i; i--)
		for (int j = n; j; j--)
			if (quarter(i, j) == 0)
				pref[i][j] = -(pref[n][n] - pref[n][j] - pref[i][n] - countTreasure(i + 1, j + 1, n, n));
			else if (quarter(i, j) == 1)
				pref[i][j] = pref[n][j] - countTreasure(i + 1, 1, n, j);
			else if (quarter(i, j) == 2)
				pref[i][j] = pref[i][n] - countTreasure(1, j + 1, i, n);
			else
				pref[i][j] = countTreasure(1, 1, i, j);
	
	rep(i, 1, n + 1)
        rep(j, 1, n + 1)
			if (pref[i][j] - pref[i - 1][j] - pref[i][j - 1] + pref[i - 1][j - 1])
				Report(i, j);
}