/* Solution
Let's go through each pair of 2 points {i, j}; it can be proven that center of a circle containing these 2 points
belongs to perpendicular bisector L' of line that contains those 2 points. Also, let L be line that contains points i, j and goes up (or right it it's a horizontal line), and mid be the middle point of segment {i, j}.

We can assign to each of n points d[k] - position of x (or -y if L' is a vertical line) coordinate of a circle containing points i, j, k minus position of a mid, or 0 if there's no such circle. Also, every point can be divided into 3 groups:
1. This point belongs to L; then it always either belongs or doesn't to the circle, and it can be easily found.
2. If position of a circle <= d[k], then this point is included in it.
3. If position of a circle >= d[k], then this point is included in it.
We can differ groups 2 and 3 by checking side where it lies according to L.

Also, by using triangle inequality it's easy to understand that we need to minimize absolute value of position of a circle.
We can achieve it by sorting points in groups 2 and 3 according to their d[k], then go through these groups by using 2 pointers.
It's also required to check if a circle with center in mid fits.
Time complexity: O(N^3 log N)
*/
﻿#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#include "bits/stdc++.h"
#include <chrono>
#include <random>
using namespace std;
template<typename T> using v = vector<T>;
//#define int long long
typedef double ld;
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define fs first
#define sc second
#define sz(a) ((int) a.size())
const long long inf = 1000000000000000000;
const long double EPS = 1e-8;
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
mt19937 rng((unsigned int)chrono::steady_clock::now().time_since_epoch().count());
//code starts here
typedef ld T;
 
struct pt {
	T x, y;
 
	T sqDist(pt o) { return (o.x - x) * (o.x - x) + (o.y - y) * (o.y - y); }
 
	double dist(pt o) {
		return sqrt(sqDist(o));
	}
 
	pt operator-(pt o) const { return { x - o.x, y - o.y }; }
	T operator*(pt o) const { return x * o.x + y * o.y; }
	T operator%(pt o) const { return x * o.y - o.x * y; }
};
 
pt middle(pt a, pt b) { return { (a.x + b.x) / 2, (a.y + b.y) / 2 }; }
 
int sgn(T a) { return (int)(a < -EPS) * -1 + (a > EPS); }
 
struct line {
	T a, b, c;
 
	line(T A, T B, T C) : a(A), b(B), c(C) {}
	line() { a = 1; b = 1; c = 1; }
 
	line(pt A, pt B) {
		a = A.y - B.y;
		b = B.x - A.x;
		c = -(a * A.x + b * A.y);
	}
 
	bool intersect(line l, pt& ans) {
		if (abs((l.a * b - l.b * a)) < EPS)
			return false;
 
		ans.x = (l.b * c - l.c * b) / (-l.b * a + l.a * b);
		ans.y = (l.c * a - l.a * c) / (-l.b * a + l.a * b);
		//print(ans.x, ans.y, a, b, c, l.a, l.b, l.c); eol;
		//assert(abs(a * ans.x + b * ans.y + c) < EPS);
		//assert(abs(l.a * ans.x + l.b * ans.y + l.c) < EPS);
		return true;
	}
 
	int side(pt p) {
		T res = a * p.x + b * p.y + c;
		return sgn(res);
	}
};
 
line perpBisector(pt a, pt b) {
	pt mid2 = { a.x + b.x, a.y + b.y };
	line l = { a, b };
	return { l.b * 2, -l.a * 2, -(l.b * mid2.x - l.a * mid2.y) };
}
 
struct circle {
	pt o;
	T r;
 
	circle(pt O, T R) : o(O), r(R) {}
 
	circle(pt a, pt b, pt c) {
		line l1 = perpBisector(a, b), l2 = perpBisector(b, c);
		assert(l1.intersect(l2, o));
		r = o.dist(a);
	}
 
	bool in(pt a) {
		return o.sqDist(a) - r * r < EPS;
	}
};
 
 
int n, K;
pt p[500];
double Less[500], more[500], d[500];
line pBis[500][500];
bool check(circle c) {
	int cnt = 0;
	rep(l, 0, n)
		if (c.in(p[l]))
			cnt++;
	return cnt >= K;
}
 
 
void run() {
	read(n, K);
	rep(i, 0, n) {
		p[i].x = rng() % 10000;
		p[i].y = rng() % 10000;
		read(p[i].x, p[i].y);
	}
 
	circle ans = { {0, 0}, 30000 };
	rep(i, 0, n)
		rep(j, 0, n)
		if (i != j)
			pBis[i][j] = perpBisector(p[i], p[j]);
	rep(i, 0, n)
		rep(j, i + 1, n) {
		bool swapped = 0;
		if (p[i].y > p[j].y || (p[i].y == p[j].y && p[i].x > p[j].x)) {
			swapped = 1;
			swap(p[i], p[j]);
		}
		circle g = { middle(p[i], p[j]), middle(p[i], p[j]).dist(p[i]) };
		int Cnt = 0;
 
		ld optimalDist = 30000;
		int lptr = 0, mptr = 0;
 
		int cnt = 2;
		pt mid = middle(p[i], p[j]);
		double C = (abs(pBis[i][j].b) < EPS) ? -mid.y : mid.x;
		line L(p[i], p[j]);
		ld a = pBis[i][j].a, b = pBis[i][j].b, c = pBis[i][j].c;
		rep(k, 0, n) {
			Cnt += g.in(p[k]);
			if (L.side(p[k]) == 0) {
				d[k] = 0;
				cnt += (p[i] - p[k]) * (p[j] - p[k]) < -EPS;
			}
			else {
				ld la = pBis[j][k].a, lb = pBis[j][k].b, lc = pBis[j][k].c;
				d[k] = ((abs(pBis[i][j].b) < EPS) ?
					(la * c - lc * a) :
					(lb * c - lc * b))
					/ (la * b - lb * a) - C;
				if (L.side(p[k]) > 0)
					Less[lptr++] = d[k];
				else
					more[mptr++] = d[k];
			}
		}
		
		if (Cnt >= K && g.r - ans.r < -EPS)
			ans = g;
		
		if (lptr + mptr + cnt < K)
			continue;
			
		sort(Less, Less + lptr);
		sort(more, more + mptr);
		if (cnt >= K)
			optimalDist = 0;
 
		int l = 0;
		rep(k, 0, lptr) {
			ld act = min(Less[k], 0.0);
			while (l < mptr && more[l] - act < EPS) //more[l] < less[k]
				l++;
 
			if (l + lptr - k + cnt >= K)
				optimalDist = act;
 
			if (act > -EPS)
				break;
		}
 
		l = 0;
		rep(k, 0, mptr) if (more[k] > EPS) { //more[k] > 0
			while (l < lptr && Less[l] - more[k] < -EPS)//less[l] < more[k]
				l++;
			if (k + 1 + lptr - l + cnt >= K) {
				if (more[k] - abs(optimalDist) < -EPS) //more[k] < abs(optimalDist)
					optimalDist = more[k];
				break;
			}
		}
 
		rep(k, 0, n)
			if (abs(d[k] - optimalDist) < EPS) {
				circle pos = { {0, 0}, 30000 };
				if (line(p[i], p[j]).side(p[k]) == 0)
					pos = { middle(p[i], p[j]), middle(p[i], p[j]).dist(p[i]) };
				else
					pos = { p[i], p[j], p[k] };
				//print(p[i].x, p[i].y, p[j].x, p[j].y, p[k].x, p[k].y); eol;
				if (pos.r - ans.r < -EPS) //pos.r < ans.r
					ans = pos;
				break;
			}
		if (swapped)
			swap(p[i], p[j]);
	}
 
	assert(check(ans));
	put ans.r; eol;
	print(ans.o.x, ans.o.y); eol;
}
 
signed main() { srand((unsigned int)time(0)); ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(12); run(); }