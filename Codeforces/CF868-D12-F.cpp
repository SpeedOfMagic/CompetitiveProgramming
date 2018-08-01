/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://codeforces.com/blog/entry/55046
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
//#define int long long
typedef long long ll;
typedef long double ld;
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define sz(a) ((int) a.size())
const long long inf = 4611686018427387903; //2^62 - 1
#if 0  //FileIO
const string fileName = "";
ifstream fin ((fileName == "" ? "input.txt"  : fileName + ".in" ));
ofstream fout((fileName == "" ? "output.txt" : fileName + ".out"));
#define get fin>>
#define put fout<<
#else
#define get cin>>
#define put cout<<
#endif
#define eol put endl
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
char curFlag = 'A'; void flag() {put curFlag++ << endl;}
int getInt(){int a; get a; return a;}
//code goes here
const int N = 1e5;
const int K = 20;
ll dp[N][K];

int arr[N];

vint indices[N];
int wherePoints[N];
int n;
int _rank(int r, int x) {
    return upper_bound(indices[x].begin(), indices[x].end(), r) - indices[x].begin();
}
pair<int, int> solve(int i, int j, int l, int r, ll curCost, bool leftSegment) {
    ll res = inf;
    int p = 0;
    ll c = 0;

    if (leftSegment) {
        /**
        cost(p + 1, zz)
        cost(p, zz)
        cost(p - 1, zz)
        ...
        cost(l, zz)
        **/
        for (int k = r; k >= l; k--) {
            //debug(k + 1, i, curCost, "L");
            ll pos = curCost + dp[k][j - 1];
            if (res >= pos) {
                res = pos;
                p = k;
                c = curCost;
            }

            curCost += _rank(i, arr[k]) - wherePoints[k] - 1;
        }
    } else {
        /**
        cost(p + 1, zz)
        cost(p + 2, zz) = cost(p + 1, zz) - rank(p + 2, zz, arr[p + 1])
        **/
        for (int k = l; k <= r; k++) {
            //debug(k + 1, i, curCost, "R");
            int pos = curCost + dp[k][j - 1];
            if (res > pos) {
                res = pos;
                p = k;
                c = curCost;
            }

            curCost -= _rank(i, arr[k + 1]) - wherePoints[k + 1] - 1;
        }
    }
    //debug(l + 1, i, curCost);


    dp[i][j] = res;
    return {p, c};
}

void calc(int j, int a, int b, int x, int y, ll previousCost, bool leftSegment) {
    if (a > b)
        return;
    int z = (a + b) / 2;

    /**
    cost(a, b) = cost(a - 1, b) - rank(a, b, arr[a - 1])
    cost(a, b) = cost(a + 1, b) + rank(a + 1, b, arr[a])
    cost(a, b) = cost(a, b - 1) + rank(a, b - 1, arr[b])
    cost(a, b) = cost(a, b + 1) - rank(a, b, arr[b])
    **/
    if (leftSegment) {
        /**
        [a; b] -> [a; z - 1]
        [x; y] -> [x; p]
        cost(p + 1, z) -> cost(y + 1, b + 1)
        zz < z

        cost(p + 1, z - 1) = cost(p + 1, z) - rank(p + 1, z - 1, arr[z])
        cost(p + 1, z - 2)
        ...
        cost(p + 1, zz)
        **/
        if (z <= y) {
            previousCost = 0;
        } else {
            for (int k = b; k >= z; k--)
                previousCost -= wherePoints[k + 1] - _rank(y, arr[k + 1]);
        }
    } else {
        /**
        [a; b] -> [z + 1; b]
        [x; y] -> [p; y]
        cost(p + 1, z) -> cost(x + 1, a - 1)
        zz > z

        cost(p + 1, z)
        cost(p + 1, z + 1) = cost(p + 1, a) = cost(p + 1, z) + rank(p + 1, z, arr[z + 1])
        ...
        cost(p + 1, zz)
        cost(p + 2, zz)
        cost(p + 3, zz)
        ...
        cost(y, zz)
        **/
        for (int k = a; k <= z; k++)
            previousCost += wherePoints[k] - _rank(x, arr[k]);
    }


    auto xx = solve(z, j, x, min(y, z - 1), previousCost, leftSegment);
    int p = xx.first;
    ll c = xx.second;

    calc(j, a, z - 1, x, p, c, 1);
    calc(j, z + 1, b, p, y, c, 0);
}

void run() {
    int k;
    read(n, k);

    rep(i, 0, n) {
        arr[i] = getInt() - 1;
        wherePoints[i] = sz(indices[arr[i]]);
        indices[arr[i]].pb(i);
    }

    int cur[N];
    rep(i, 0, N)
        cur[i] = 0;

    ll val = 0;
    rep(i, 0, n) {
        val += cur[arr[i]];
        cur[arr[i]]++;
        dp[i][0] = val;
    }

    rep(j, 1, k)
        calc(j, 0, n - 1, 0, n - 1, val, 1);

    put dp[n - 1][k - 1];
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
