/** MIT License CopyRight (c) 2018-2019 Vasilev Daniil **/
/* Solution
Let's compress ids, then for each elements with equal ids we'll put them into separate vector
then we'll use two pointers method on each vector. Then, to check if we can remove k distinct ids so that only one remains, it's needed to check if amount of distinct elements on that segment > k + 1 or not. It can be done by persistent segment tree.
Time complexity: O(N log N).
*/
#include <bits/stdc++.h>
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
const long long inf = 4611686018427387903; //2^62 - 1
const long double EPS = 1e-11;
#if 10  //FileIO
const string fileName = "lineup";
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

const int N = 1 << 17;
const int D = 18;
const int Q = 200001;
int val[Q][D];
int Left[Q][D];
int Right[Q][D];

void init() {
	rep(i, 0, D) {
		val[0][i] = 0;
		Left[0][i] = 0;
		Right[0][i] = 0;
	}
}

int query(int l, int r, int curVersion, int d = 0, int ll = 1, int rr = N) {
    if (l > r)
        return 0;
    if (l == ll && r == rr)
        return val[curVersion][d];
    int mid = (ll + rr) >> 1;
    return query(l, min(r, mid), Left[curVersion][d], d + 1, ll, mid) +
		   query(max(l, mid + 1), r, Right[curVersion][d], d + 1, mid + 1, rr);
}

int versionCount = 1;
void update(int num, int v, int prevVersion) {
	int parallel = prevVersion;

	int cur = versionCount;
    int ll = 1, rr = N;
    for (int d = 0; ll != rr; d++) {
        int mid = (ll + rr) >> 1;
        if (num > mid) {
            ll = mid + 1;
			Left[cur][d] = Left[parallel][d];
			Right[cur][d] = cur;
			parallel = Right[parallel][d];
        } else {
            rr = mid;
			Left[cur][d] = cur;
			Right[cur][d] = Right[parallel][d];
			parallel = Left[parallel][d];
        }
    }

	val[cur][D - 1] = v;
	for (int i = D - 2; i >= 0; i--)
		val[cur][i] = val[Left[cur][i]][i + 1] + val[Right[cur][i]][i + 1];

	versionCount++;
}

void run() {
	init();
	int n, k;
	read(n, k);
	int a[n];

	pair<int, int> b[n];
	rep(i, 0, n) {
		get a[i];
		b[i] = {a[i], i};
	}
	sort(b, b + n);

	int ptr = 0;
	rep(i, 0, n) {
		if (i && b[i].fs > b[i - 1].fs)
			ptr++;
		a[b[i].sc] = ptr;
	}

	vint inv[n + 1];
	rep(i, 0, n)
		inv[a[i]].pb(i + 1);

	int v[n];
	memset(v, -1, sizeof v);
	rep(i, 0, n) {
		if (v[a[i]] == -1)
			update(n, 0, versionCount - 1);
		else
			update(v[a[i]], 0, versionCount - 1);
		v[a[i]] = i + 1;
		update(v[a[i]], 1, versionCount - 1);
	}

	//while (1) { int l, r; read(l, r); put query(l, r, r << 1); eol;}

	int ans = 0;
	rep(i, 0, n) {
		int l = 0;
		rep(r, 0, sz(inv[i])) {
			while (query(inv[i][l], inv[i][r], inv[i][r] << 1) > k + 1)
				l++;
			ans = max(ans, r - l + 1);
		}
	}

	put ans;
}

signed main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(12); run();}
