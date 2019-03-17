/* Solution
Let n be size of A and q be amount of queries.
O(n log n * q):
1. Suppose there is array B which is {A[i], i} for all i. Also it's sorted.
2. Then the answer is max for all i in [0; n - 1] (i - j), where B[j] = {A[i], i}.
If we build B and calculate answer after each query, we get O(n log n * q) solution.
O((n + q) log n):
3. To build B faster it's easy to notice that only one element in B moves from one position to another. Then what is needed is to pull element out from one position and put it into another one. It can be easily done by treap.
4. To calculate answer, let every element with index i (according to A) in treap have value c = (i - j) where B[j] = {A[i], i}.
5. Since answer is maximum among them, then each treap should also store maximum value in its subtree.
6. After update, when element moves from one place to another, there is a segment which also moves. In other words, j for each element in this segment changes by the same amount. So, it's also needed to increase or decrease c on a treap by the same amount. It can be done by lazy propagation.
*/
#include "bubblesort2.h"
#include <bits/stdc++.h>
using namespace std;
#define fs first
#define sc second
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct treap {
	treap *l = nullptr, *r = nullptr;
	int x, y, p, siz = 1;
	int c;
	int lazy = 0;
	int val;
	
	void pushdown() {
		if (l != nullptr) l -> lazy += lazy;
		if (r != nullptr) r -> lazy += lazy;
		val += lazy;
		c += lazy;
		lazy = 0;
	}
	
	void upd() {
		pushdown();
		if (l != nullptr) l -> pushdown();
		if (r != nullptr) r -> pushdown();
		siz = ((l == nullptr) ? 0 : l -> siz) + ((r == nullptr) ? 0 : r -> siz) + 1;
		val = max(c, max((l == nullptr) ? c : l -> val, (r == nullptr) ? c : r -> val));
	}
	
	treap(int a, int pp, int cc) : x(a), y(rng()), p(pp), c(cc) {val = c;}
};

int siz(treap *t) { return (t == nullptr) ? 0 : t -> siz; }

treap* merge(treap *t1, treap *t2) {
	if (t1 == nullptr)
		return t2;
	if (t2 == nullptr)
		return t1;
	t1 -> pushdown();
	t2 -> pushdown();
	if (t1 -> y > t2 -> y) {
		t1 -> r = merge(t1 -> r, t2);
		t1 -> upd();
		return t1;
	} else {
		t2 -> l = merge(t1, t2 -> l);
		t2 -> upd();
		return t2;
	}
}

pair<treap*, treap*> split(treap *t, int x, int pos) {
	if (t == nullptr)
		return {nullptr, nullptr};
	t -> pushdown();
	if (t -> x > x || (t -> x == x && t -> p >= pos)) {
		auto tmp = split(t -> l, x, pos);
		t -> l = tmp.second;
		t -> upd();
		return {tmp.first, t};
	} else {
		auto tmp = split(t -> r, x, pos);
		t -> r = tmp.first;
		t -> upd();
		return {t, tmp.second};
	}
}

inline void addAll(treap *t, int a) { if (t != nullptr) t -> lazy += a; }

treap *root;

vector<int> countScans(vector<int> A, vector<int> X, vector<int> V) {
	int n = A.size();
	pair<int, int> B[n];
	for (int i = 0; i < n; i++)
		B[i] = {A[i], i};
	sort(B, B + n);
	
	for (int i = 0; i < n; i++) 
		root = merge(root, new treap(B[i].fs, B[i].sc, B[i].sc - i));
	
	vector<int> answer(X.size());
	for (unsigned int query = 0; query < X.size(); query++) {
		int pos = X[query], val = V[query];
		if (A[pos] > val) {
			//a.fs -end position of element- b.fs -this element- th.sc
			auto a = split(root, val, pos);
			auto b = split(a.sc, A[pos], pos);
			auto th = split(b.sc, A[pos], pos + 1);
			addAll(b.fs, -1);
			treap *d = new treap(val, pos, pos - siz(a.fs));
			root = merge(merge(a.fs, d), merge(b.fs, th.sc));
		} else {
			//a.fs -this element- b.fs -end position of element- b.sc
			auto a = split(root, A[pos], pos);
			auto th = split(a.sc, A[pos], pos + 1);
			auto b = split(th.sc, val, pos);
			addAll(b.fs, 1);
			treap *d = new treap(val, pos, pos - siz(a.fs) - siz(b.fs));
			root = merge(merge(a.fs, b.fs), merge(d, b.sc));
		}
		
		A[pos] = val;
		root -> pushdown();
		answer[query] = root -> val;
	}
		
	return answer;
}