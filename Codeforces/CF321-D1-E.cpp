/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: https://codeforces.com/blog/entry/8192
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
//#define int long long
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
int getInt(){int a; get a; return a;}
//code goes here
const int N = 4000;
const int K = 800;
int cost[N][N];
int dp[N][K];

int solve(int i, int j, int l, int r) {
    int p = 0;
    int res = 1e9;

    for (int kk = l; kk <= r && kk < i; kk++) {
        int pos = dp[kk][j - 1] + cost[kk + 1][i - (kk + 1)];
        if (res > pos) {
            res = pos;
            p = kk;
        }
    }

    dp[i][j] = res;
    return p;
}

void calc(int j, int a, int b, int x, int y) {
    if (a > b)
        return;

    int z = (a + b) / 2;
    int p = solve(z, j, x, y);

    calc(j, a, z - 1, x, p);
    calc(j, z + 1, b, p, y);
}

void run() {
    int n, k;
    read(n, k);
    int mat[n][n];
    int prefixHor[n][n];

    str s;
    getline(cin, s);
    rep(i, 0, n) {
        getline(cin, s);
        rep(j, 0, n) {
            mat[i][j] = s[j * 2] - '0';//get mat[i][j];
            prefixHor[i][j] = mat[i][j];
            if (j)
                prefixHor[i][j] += prefixHor[i][j - 1];
        }
    }

    rep(l, 0, n) {
        int curCost = 0;
        rep(r, l, n) {
            curCost += prefixHor[r][r] - prefixHor[r][l] + mat[r][l];
            cost[l][r - l] = curCost;
        }
    }

    rep(i, 0, n)
        dp[i][0] = cost[0][i];

    rep(i, 1, k)
        calc(i, 0, n - 1, 0, n - 1);

    put dp[n - 1][k - 1];
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}