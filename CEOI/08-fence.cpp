/** MIT License Copyright (c) 2018-2019 Vasilev Daniil **/
/* Solution
1. It's obvious that we should enclose as much trees as possible, and there is optimal answer that uses only 1 polygon R.
2. Let's remove all trees that can't be enclosed, then build convex hull C on the other trees.
3. It's obvious that R should contain C. Also let's assume that points of R must have clockwise order. 
4. Let's make oriented graph on n vertices, where edge u -> v means that we can go from post u to post v to
form a polygon that contains C.
5. Edge u -> v is correct if segment uv doesn't intersect with C and in R points u and v go in clockwise order. We can check that by using point which is inside of R. Since R contains C, then we can use any point from C.
6. To find R we can simply go through all vertexes, say that they are a part of R, then find a cycle of a minimum length that has this vertex, which can be done by bfs.
*/
#include <chrono>
#include <random>
#include "bits/stdc++.h"
using namespace std;
template<typename T> using v = vector<T>;
//#define int long long
typedef long double ld;
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define fs first
#define sc second
#define sz(a) ((int) a.size())
const long long inf = 1000000000000000000;
const long double EPS = 1e-10;
#if 0  //FileIO
const string fileName = "";
ifstream fin((fileName == "" ? "input.txt" : fileName + ".in"));
ofstream fout((fileName == "" ? "output.txt" : fileName + ".out"));
#define get fin >>
#define put fout <<
#else
#define get cin >>
#define put cout <<
#endif
#define eol put endl
void read() {} template<typename Arg, typename... Args> void read(Arg& arg, Args& ... args) { get(arg);read(args...); }
void print() {} template<typename Arg, typename... Args> void print(Arg  arg, Args...  args) { put(arg) << " ";print(args...); }
int getInt() { int a; get a; return a; }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//code starts here
struct pt {
	int x, y;
 
	pt() {}
	pt(int _x, int _y) : x(_x), y(_y) {}
	pt(pt a, pt b) : x(b.x - a.x), y(b.y - a.y) {}
	pt operator-(pt o) const { return { x - o.x, y - o.y }; }
	int operator*(pt o) const { return x * o.x + y * o.y; }
	int operator%(pt o) const { return x * o.y - y * o.x; }
};
 
int sgn(int a) { return (a < 0) ? -1 : !!a; }
bool belongs(pt a, pt b, pt p) { return (a - p) % (b - p) == 0 && (a - p) * (b - p) <= 0; }
bool segSeg(pt a, pt b, pt c, pt d, char en = 1) {
	if (belongs(a, b, c) || belongs(a, b, d) || belongs(c, d, a) || belongs(c, d, b))
		return en;
	pt ab = { a, b }, bc = { b, c }, bd = { b, d }, da = { d, a }, db = { d, b }, cd = { c, d };
	return (sgn(ab % bc) != sgn(ab % bd) && sgn(cd % da) != sgn(cd % db));
}
 
bool in(vector<pt> pol, pt p) {
	int n = pol.size();
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		pt a = pol[i], b = pol[(i + 1) % n];
		if (a.y > b.y)
			swap(a, b);
		if (belongs(a, b, p))
			return true;
		else if (a.y == p.y)
			continue;
		else if (segSeg(a, b, p, { 10000, p.y }))
			cnt++;
	}
	return cnt % 2;
}
 
v<pt> convexHull(v<pt> p) {
	sort(p.begin(), p.end(), [](pt a, pt b) { return (a.x == b.x) ? a.y < b.y : a.x < b.x; });
	int n = p.size();
	if (n < 3)
		return p;
	v<pt> hull;
	rep(i, 0, n) {
		while (sz(hull) >= 2) {
			pt a = hull[sz(hull) - 2], b = hull.back(), c = p[i];
			pt ab = { a, b }, bc = { b, c };
			if (ab % bc >= 0)
				hull.pop_back();
			else
				break;
		}
		hull.pb(p[i]);
	}
 
	hull.pb(p[n - 2]);
	int lim = sz(hull);
	for (int i = n - 3; i >= 0; i--) {
		while (sz(hull) >= lim) {
			pt a = hull[sz(hull) - 2], b = hull.back(), c = p[i];
			pt ab = { a, b }, bc = { b, c };
			if (ab % bc >= 0)
				hull.pop_back();
			else
				break;
		}
		hull.pb(p[i]);
	}
	hull.pop_back();
 
	return hull;
}
 
struct line {
	int a, b, c;
 
	line(int A, int B, int C) : a(A), b(B), c(C) {}
 
	line(pt A, pt B) {
		a = A.y - B.y;
		b = B.x - A.x;
		c = -(a * A.x + b * A.y);
	}
 
	int side(pt p) { return sgn(p.x * a + p.y * b + c); } //> 0 if on the left
};
 
bool polSeg(v<pt>& pol, pt a, pt b) {
	if (in(pol, a) || in(pol, b))
		return 1;
 
	rep(i, 0, sz(pol)) {
		pt c = pol[i], d = pol[(i + 1) % sz(pol)];
		if (segSeg(a, b, c, d))
			return 1;
	}
	return 0;
}
 
void run() {
	int n, m;
	read(n, m);
 
	pt p[n];
	rep(i, 0, n)
		read(p[i].x, p[i].y);
 
	pt apples[m];
	rep(i, 0, m)
		read(apples[i].x, apples[i].y);
 
	char useless[m];
	memset(useless, 0, sizeof useless);
	v<pt> fenceHull(n);
	rep(i, 0, n)
		fenceHull[i] = p[i];
	fenceHull = convexHull(fenceHull);
 
	int ans = 0;
	rep(i, 0, m)
		if (!in(fenceHull, apples[i])) {
			ans += 111;
			useless[i] = 1;
		}
 
	v<pt> applesHull;
	rep(i, 0, m)
		if (!useless[i])
			applesHull.pb(apples[i]);
	applesHull = convexHull(applesHull);
 
	m = sz(applesHull);
	if (m == 0) { put ans; return; }
 
	vint g[n];
	rep(i, 0, n)
		rep(j, 0, n)
			if (!polSeg(applesHull, p[i], p[j]) && line(applesHull[0], p[i]).side(p[j]) == -1) {
				g[i].pb(j);
			}
 
	int cost = 1e9;
	char vis[n];
	rep(st, 0, n) {
		memset(vis, 0, sizeof vis);
		vis[st] = 1;
		queue<int> bfs;
		queue<int> gen;
		bfs.push(st);
		gen.push(1);
		while (!bfs.empty()) {
			int cur = bfs.front();
			int pos = gen.front();
			bfs.pop();
			gen.pop();
			for (int i : g[cur])
				if (i == st) {
					cost = min(cost, pos * 20);
					goto nxt;
				} else if (!vis[i]) {
					bfs.push(i);
					gen.push(pos + 1);
					vis[i] = 1;
				}
		}
 
		nxt:;
	}
 
	put ans + cost; eol;
}
 
signed main() { srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(12); run(); }