/* Solution
Let's make convex hull H of size m from given points that goes in any order. Obviously, if a line intersects with H, then this is a bad line. Otherwise it's good.
Suppose we have to check whether vector p1p2 intersects with H. Let f(p) = p1p2 X p2p, where p is a point.
This function can have 2 possible templates:
1. First this function is non-increasing, then it's non-decreasing, then it's non-increasing; also, f(H[1]) < F(H[m]).
2. First this function is non-decreasing, then it's non-increasing, then it's non-decreasing; also, f(H[1]) > F(H[m]).
Suppose f has 2nd template, then we can simply swap p1 and p2, and f will have 1st template.

Let's look at f(H[1]). If it's < 0, then we need to find such x that f(H[x]) is maximum. Otherwise we need to find such x that f(H[x]) is minimum.
Such x can be found by using binary search. On each stage let mid be middle point current segment, and mid < nxt be the first point such that H[mid] != H[nxt]. It can be proven that nxt <= mid + 2.
By using f(H[mid]) and f(H[nxt]) we can easiy determine on which segment mid and nxt are located, and then change borders as needed.
*/
/** MIT License Copyright (c) 2018-2019 Vasilev Daniil **/
#include <fstream>
#include <map>
#include <cmath>
#include <string>
#include <cassert>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
typedef double ld;
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define fs first
#define sc second
#define sz(a) ((int) a.size())
const long long inf = 4611686018427387903; //2^62 - 1
const long double EPS = 1e-11;
#if 0  //FileIO
const string fileName = "";
ifstream fin ((fileName == "" ? "input.txt"  : fileName + ".in" ));
ofstream fout((fileName == "" ? "output.txt" : fileName + ".out"));
#define get fin >>
#define put fout <<
#else
#define get cin >>
#define put cout <<
#endif
#define eol put endl
void read() {} template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){} template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
int getInt(){int a; get a; return a;}
//code starts here
struct pt {
	ld x, y;

	pt() {}
	pt(ld _x, ld _y) : x(_x), y(_y) {}
	pt(pt p1, pt p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}

	ld operator%(pt o) { return x * o.y - y * o.x; }
	bool operator<(pt o) const { return (abs(x - o.x) < EPS) ? y < o.y : x < o.x; }
};

int sgn(ld a) { return (0 < a) - (a < 0); }

vector<pt> convexHull(vector<pt> p) {
	sort(p.begin(), p.end());
	int n = p.size();
	if (n < 3)
		return p;
	vector<pt> hull;
	rep(i, 0, n) {
		while (sz(hull) >= 2) {
			pt a = hull[sz(hull) - 2], b = hull.back(), c = p[i];
			pt ab = pt(a, b), bc = pt(b, c);
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
			pt ab = pt(a, b), bc = pt(b, c);
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
void run() {
	int n;
	scanf("%d", &n);
	vector<pt> pol(n);
	rep(i, 0, n)
	    scanf("%lf %lf",&pol[i].x,&pol[i].y);

	pol = convexHull(pol);
	n = sz(pol);

	pt p1, p2;
	while (scanf("%lf %lf %lf %lf",&p1.x,&p1.y,&p2.x,&p2.y) == 4) {
	    //scanf(" %lf %lf %lf %lf",&p1.x,&p1.y,&p2.x,&p2.y);
		if (sz(pol) <= 1) {
			printf("GOOD\n"); fflush(stdout);
			continue;
		}

		pt $12 = pt(p1, p2);
		if ($12 % pt(p2, pol[0]) > $12 % pt(p2, pol.back())) {
			swap(p1, p2);
			$12 = pt(p1, p2);
		}

		ld init = $12 % pt(p2, pol[0]);
		int S = sgn(init);
		if (S != sgn($12 % pt(p2, pol.back()))) {
			printf("BAD\n"); fflush(stdout);
			continue;
		}

		int l = 0, r = n - 1;
		ld A, B;
		ld res;
		if (S > 0) { //minimum
			while (l < r) {
				int mid = (l + r) >> 1;
				int nxt = mid + 1;
				while (nxt < n && abs($12 % pt(p2, pol[nxt]) - $12 % pt(p2, pol[mid])) < EPS)
					nxt++;

				A = $12 % pt(p2, pol[mid]);
				B = $12 % pt(p2, pol[nxt]);

				assert(nxt <= mid + 2);
				if (nxt == n)
					r = mid;
				else if (A < B)
					r = mid;
				else if (A < init) //A > B
					l = nxt;
				else
					r = mid;
			}
		} else { //maximum
			while (l < r) {
				int mid = (l + r) >> 1;
				int nxt = mid + 1;
				while (nxt < n && abs($12 % pt(p2, pol[nxt]) - $12 % pt(p2, pol[mid])) < EPS)
					nxt++;

				A = $12 % pt(p2, pol[mid]);
				B = $12 % pt(p2, pol[nxt]);

				assert(nxt <= mid + 2);
				if (nxt == n)
					r = mid;
				else if (A < B)
					l = nxt;
				else if (A < init) //A > B
					l = nxt;
				else
					r = mid;
			}
		}

		res = $12 % pt(p2, pol[l]);
		if (sgn(res) != sgn(init)) {
			printf("BAD\n"); fflush(stdout);
			continue;
		}
		printf("GOOD\n"); fflush(stdout);
	}
}

signed main() { ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(12); run();}