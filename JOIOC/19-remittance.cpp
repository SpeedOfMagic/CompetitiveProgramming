/** MIT License Copyright (c) 2018-2019 Vasilev Daniil **/
/* Solution
It's needed to find x0, x1, ..., x[n - 1], such that:
a0 - 2x0 + x[n - 1] = b0
a1 - 2x1 + x0 = b1
...
a[n - 1] - 2x[n - 1] + x[n - 2] = b[n - 1]

Let ci = bi - ai. by simplifying this system we get:
xi = ci + 2x[i + 1], for i in [0; n - 2]
x[n - 1] = -(c0 + 2c1 + 4c2 + ... + 2^i * c[i] + ... + 2^(n - 1) * c[n - 1]) / (2^n - 1)
To calculate -(c0 + 2c2 + ... + ... + 2^(n - 1) * c[n - 1]) it's needed to use long arithmetics in binary counting system.
We can use long division to divide this by (2^n - 1). On each step, it there are n ones in a row, then we can remove them. Otherwise, we substract from current bit i, and then add bit in position i + n.
To use this long division it's needed to change elements and ask sum of some segment. It can be done by fenwick tree.
After we find x's, we can check if it's possible to do this in our array. It can be done with simple implementation.
Also it's needed to check if x[n - 1] is integer or some of x's are negative or they are too big to be done.
*/
#include <bits/stdc++.h>
using namespace std;
template<typename T> using v = vector<T>;
#define int long long
typedef double ld;
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define fs first
#define sc second
#define sz(a) ((int) a.size())
const long long inf = 1000000000000000000;
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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//code starts here
const int N = 1000100;
int fen[N];
int lsb(int a) { return a & -a; }
int rsq(int r) { return (r ? rsq(r - lsb(r)) + fen[r] : 0); }
void upd(int p, int val) { if (p < N) { fen[p] += val; upd(p + lsb(p), val); }}
void run() {
	int n;
	get n;
	int a[n], b[n];
	rep(i, 0, n) {
		read(a[i], b[i]);
	}

	int c[n];
	rep(i, 0, n)
		c[i] = b[i] - a[i];

	str plus, minus;
	int carry = 0;

	rep(i, 0, n) {
		carry += (c[i] > 0) * c[i];
		plus += '0' + (carry % 2);
		carry >>= 1;
	}

	while (carry) {
		plus += '0' + (carry % 2);
		carry >>= 1;
	}

	rep(i, 0, n) {
		carry += -(c[i] < 0) * c[i];
		minus += '0' + (carry % 2);
		carry >>= 1;
	}

	while (carry) {
		minus += '0' + (carry % 2);
		carry >>= 1;
	}

	while (sz(plus) > sz(minus))
		minus += "0";
	while (sz(plus) < sz(minus))
		plus += "0";
	//minus - plus
	str xn;
	
	rep(i, 0, sz(plus)) {
		if (plus[i] == '1' && minus[i] == '0') {
			carry = i + 1;
			plus[i] = '0';
			while (carry < sz(minus) && minus[carry] == '0')
				carry++;
			if (carry == sz(minus)) {
				put "No";
				return;
			}
			minus[carry] = '0';
			for (int j = carry - 1; j >= i; j--)
				minus[j] = '1';
		}

		xn += minus[i] - plus[i] + '0';
	}
	
	str res;
	xn += "0";
	reverse(xn.begin(), xn.end());
	//dividing xn by 2^n - 1
	rep(i, 0, sz(xn))
		upd(i + 1, xn[i] - '0');

	rep(i, 0, sz(xn) - n) {
		if (xn[i] == '0' && rsq(i + n + 1) - rsq(i + 1) == n) {
			res += "1";
			rep(j, i + 1, i + n + 1) {
				int change = '0' - xn[j];
				xn[j] = '0';
				upd(j + 1, change);
			}
		} else if (xn[i] == '1') {
			res += "1";
			xn[i]--;
			upd(i + 1, xn[i]);
			for (int j = i + n; j >= i; j--) {
				if (xn[j] == '0') {
					int change = '1' - xn[j];
					xn[j] = '1';
					upd(j + 1, change);
					break;
				}
				int change = '0' - xn[j];
				xn[j] = '0';
				upd(j + 1, change);
			}
		} else
			res += "0";
	}

	for (char i : xn)
		if (i == '1') {
			put "No"; eol;
			return;
		}
	
	int x[n];
	x[n - 1] = 0;
	reverse(res.begin(), res.end());
	for (int pw = 0; pw < sz(res); pw++) {
		if (pw > 60 && res[pw]) {
			put "No"; eol;
			return;
		} else
			x[n - 1] += (1ll << pw) * (res[pw] - '0');
	}
	
	for (int i = n - 2; i >= 0; i--) {
		x[i] = c[i + 1] + 2 * x[i + 1];
		if (x[i] < 0 || x[i] > (1ll << 60ll)) {
			put "No";
			return;
		}
	}

bool again = 1;
		while (again) {
			again = 0;
			rep(i, 0, n) {
				int can = min(x[i], a[i] / 2);
				again |= can;
				a[(i + 1) % n] += can;
				x[i] -= can;
				a[i] -= can * 2;
			}
		}
		rep(i, 0, n)
			if (a[i] != b[i]) {
				put "No";
				return;
			}

		put "Yes";
		return;
}

signed main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(12); run();}
