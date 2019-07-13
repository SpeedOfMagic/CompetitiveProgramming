/** MIT License Copyright (c) 2018-2019 Vasilev Daniil **/
/* Solution
Let's divide points into 2 arrays: those to the left of the line (L), and those to the right of the line (R)
Let's look at two neighbouring pair of points in L. There are 2 possible variants: polygon has inner part contained between these two points, or not.
Since polygon always has clockwise order, then it can be proven that if strictly between those two points there have never been rotation in counter-clockwise order, then the inner part of polygon is between those two points, which means that those two points make separate region right to the line.
So if we go through each neighbouring pair of points in L + first and last points in L, and check if amount of counter-clockwise rotations strictly between them is > 0, then we can decide if we should add another right region to the answer or not.
If we do the same to R, then we'll get the answer.
*/
#include <bits/stdc++.h>
#include "lookup.h"
using namespace std;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define sz(a) ((int) a.size())
//code starts here
const int N = 1e5 + 5;
 
int need = 1;
int pref[N];
int nxtDir[N];
int n;
bool valid(int pr, int i) {
	if (i - pr - 1 == 0 || n - (pr - i + 1) == 0)
		return 0;
	if (pr < i) 
		return pref[i] - pref[pr] - (nxtDir[i] == need) == 0;
	else 
		return pref[n - 1] - pref[pr] + pref[i] - (nxtDir[i] == need) == 0;
}
 
void run() {
	n = GetN();
	int pl[n];
	rep(i, 0, n)
		pl[i] = Drift(n + 1, n + 2, i + 1);
 
    char allLeft = 1, allRight = 1;
	rep(i, 0, n) {
		assert(pl[i]);
		allLeft &= pl[i] == 1;
		allRight &= pl[i] == -1;
	}
 
	if (allLeft) {
		Answer(1, 0);
		return;
	} else if (allRight) {
		Answer(0, 1);
		return;
	}
 
	rep(i, 0, n)
		nxtDir[i] = Drift((i - 1 + n) % n + 1, i + 1,  (i + 1) % n + 1);
 
	rep(i, 0, n)
		allLeft &= nxtDir[i] != -1;
 
	pref[0] = nxtDir[0] == need;
	rep(i, 1, n)
		pref[i] = pref[i - 1] + (nxtDir[i] == need);
 
	vint L;
	rep(i, 0, n)
		if (pl[i] == 1)
			L.pb(i);
	int left = 0;
	rep(z, 0, sz(L)) {
		int pr = L[z], i = L[(z + 1) % sz(L)];
		if (valid(pr, i))
			left++;
	}
 
	vint R;
	rep(i, 0, n)
		if (pl[i] == -1)
			R.pb(i);
	int right = 0;
	rep(z, 0, sz(R)) {
		int pr = R[z], i = R[(z + 1) % sz(R)];
		if (valid(pr, i))
			right++;
	}
 
	Answer(right, left);
}
 
signed main() {run();}