/** MIT License Copyright (c) 2018-2019 Vasilev Daniil **/
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
 
signed main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(12); run();}