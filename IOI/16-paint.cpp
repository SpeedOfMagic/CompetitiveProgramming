/* Solution
1. Let dp[i][j] = if it's possible to cover all first i characters by using first j segments and position i should also be covered
After calculating dp there are pairs (i, j) where dp[i][j] = 1 and there's no solution that has end of j-th segment on position i. It's needed to remove them.
Then for each cell it's needed to find whether they can contain black cell or a white one.
Time complexity: O(nk).
*/
#include "paint.h"
#include <bits/stdc++.h>
using namespace std;
string solve_puzzle(string s, vector<int> c) {
	int k = c.size(), n = s.size();
	//dp[i][j] - if it's possible to cover all first i characters by using j segments
	int dp[n][k];
	memset(dp, 0, sizeof dp);
	int blackPref[n], whitePref[n];
	for (int i = 0; i < n; i++) {
		whitePref[i] = (i ? whitePref[i - 1] : 0) + (s[i] == '_');
		blackPref[i] = (i ? blackPref[i - 1] : 0) + (s[i] == 'X');
	}
	
	int closest[k];
	memset(closest, -1, sizeof closest);
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < k; j++)
			if (i > c[j] && dp[i - c[j] - 1][j - 1]) {
				closest[j - 1] = i - c[j] - 1;
			}
			
		if (i + 1 >= c[0]) {
			if (i < c[0])
				dp[i][0] = whitePref[i] == 0;
			else
				dp[i][0] = (whitePref[i] - whitePref[i - c[0]] == 0) && (blackPref[i - c[0]] == 0) && (i + 1 == n || s[i + 1] != 'X');
			
			dp[i][0] &= (i + 1 == n) || (s[i + 1] != 'X'); 
		}
		
		for (int j = 1; j < k; j++)
			if (i > c[j])
				dp[i][j] = (whitePref[i] - whitePref[i - c[j]] == 0) && (s[i - c[j]] != 'X') && 
			(i + 1 == n || s[i + 1] != 'X') && (closest[j - 1] != -1) &&
			(blackPref[i - c[j]] - blackPref[closest[j - 1]] == 0);
		
		dp[i][k - 1] &= blackPref[n - 1] - blackPref[i] == 0;
	}
	
	//for (int i = 0; i < k; i++) { for (int j = 0; j < n; j++) cout << dp[j][i]; cout << endl; }
	
	int save[n][k];
	memset(save, 0, sizeof save);
	save[0][k - 1]++;
	
	int nearest[k];
	memset(nearest, -1, sizeof nearest);
	for (int j = 0; j < k; j++)
		for (int i = 0; i < n; i++)
			if (dp[i][j]) {
				nearest[j] = i;
				break;
			}
	
	for (int j = k - 1; j >= 0; j--) {
		int sum = 0;
		for (int i = 0; i < n; i++) {
			sum += save[i][j];
			if (!sum)
				dp[i][j] = 0;
		
			if (j && dp[i][j]) {
				while (blackPref[i - c[j]] - blackPref[nearest[j - 1]])
					nearest[j - 1]++;
				
				save[nearest[j - 1]][j - 1]++;
				save[i - c[j]][j - 1]--;
			}
		}
	}
			
	//for (int i = 0; i < k; i++) { for (int j = 0; j < n; j++) cout << dp[j][i]; cout << endl; }
	
	string ans = s;
	for (char& i : ans)
		if (i == '.')
			i = '?';
		
	int canBeBlack[n], canBeWhite[n];
	memset(canBeBlack, 0, sizeof canBeBlack);
	memset(canBeWhite, 0, sizeof canBeWhite);
	
	memset(nearest, -1, sizeof nearest);
	for (int j = 0; j < k; j++)
		for (int i = 0; i < n; i++)
			if (dp[i][j]) {
				nearest[j] = i;
				break;
			}
	
	for (int i = 0; i < n; i++) {
			
		for (int j = 0; j < k; j++)
			if (dp[i][j]) {
				canBeBlack[i - c[j] + 1]++;
				if (i + 1 < n) 
					canBeBlack[i + 1]--;
				
				if (j == 0) {
					canBeWhite[0]++;
					if (i - c[j] + 1 < n)
						canBeWhite[i - c[j] + 1]--;
				}
				
				if (j == k - 1) {
					if (i + 1 < n)
						canBeWhite[i + 1]++;
				}
				
				if (j > 0 && i - c[j] >= 0) {
					while (blackPref[i - c[j]] - blackPref[nearest[j - 1]])
						nearest[j - 1]++;
					while (nearest[j - 1] < n && !dp[nearest[j - 1]][j - 1])
						nearest[j - 1]++;
				
					//cout << i << " " << j << " " << nearest[j - 1] << endl;
					assert(nearest[j - 1] != -1);
					canBeWhite[nearest[j - 1] + 1]++;
					if (i - c[j] + 1 < n)
						canBeWhite[i - c[j] + 1]--;
				}
			}
	}
		
	int sum = 0, sumw = 0;
	for (int i = 0; i < n; i++) {
		sum += canBeBlack[i];
		sumw += canBeWhite[i];
		//cout << i << " " << sum << " " << sumw << endl;
		if (sum && sumw) 
			assert(ans[i] == '?');
		else if (sum) {
			assert(ans[i] != '_');
			ans[i] = 'X';
		} else if (sumw) {
			assert(ans[i] != 'X');
			ans[i] = '_';
		} else
			assert(0);
	}		
	
	return ans;
}
/* X_X_X
.....
3 1 1 1
*//* ??_X_??
...X...
2 1 1
*//* ?X?__XX__
...__.._.
2 2 2
*//* _X_
.X.
1 1
*//* XX_XX___
.X.X...
2 2 2
*/