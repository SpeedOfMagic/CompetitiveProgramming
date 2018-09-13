/** Solution:
1. To minimize R, note that if I can sort array in K moves, then I can also do that in K + 1:
just cancel last operation; => I can minimize R by using binary search.
2. To make optimal answer, I make all swaps beforehand, and then try to sort resulting array.
3. After each swap, I only store values of elements I swapped.
After that I get starting array and simulate actions, where my indices are indices of elements whose value is stored.
Time complexity: O(N log M).
**/
#include <bits/stdc++.h>
#include "sorting.h"
using namespace std;

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
    int l = 0, r = M;
	while (l < r) {
		int res[N];
		for (int i = 0; i < N; i++)
			res[i] = S[i];
		
		int mid = (l + r) / 2;
		for (int i = 0; i < mid; i++)
			swap(res[X[i]], res[Y[i]]);
		
		int invRes[N];
		for (int i = 0; i < N; i++)
			invRes[res[i]] = i;
		
		vector<pair<int, int>> elementsToSwap;
		for (int i = 0; i < N; i++)
			if (res[i] != i) {
				int other = invRes[i];
				invRes[res[i]] = other;
				invRes[i] = i;
				elementsToSwap.push_back({res[i], i});
				swap(res[i], res[other]);
			}
		
		if (elementsToSwap.size() > mid)
			l = mid + 1;
		else {
			for (int i = 0; i < N; i++) {
				res[i] = S[i];
				invRes[res[i]] = i;
			}
			
			for (int i = 0; i < mid; i++) {
				invRes[res[X[i]]] = Y[i];
				invRes[res[Y[i]]] = X[i];
				swap(res[X[i]], res[Y[i]]);
				
				if (elementsToSwap.size() <= i)
					P[i] = Q[i] = 0;
				else {
					P[i] = invRes[elementsToSwap[i].first];
					Q[i] = invRes[elementsToSwap[i].second];
					swap(invRes[elementsToSwap[i].first], invRes[elementsToSwap[i].second]);
					swap(res[invRes[elementsToSwap[i].first]], res[invRes[elementsToSwap[i].second]]);
				}
			}
					
			assert(is_sorted(res, res + N));
			r = mid;
		}
	}
	
	return r;
}


