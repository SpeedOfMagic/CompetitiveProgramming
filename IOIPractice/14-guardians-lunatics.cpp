/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14/editorial
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
#define int long long
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
v<vint> dp;

vint prefix;
int cost(int l, int r) {
    return (prefix[r] - (l ? prefix[l - 1] : 0)) * (r - l + 1);
}

int solve(int i, int j, int l, int r) {
    int res = inf;
    int p = -1;
    for (int k = l; k <= min(i - 1, r); k++) {
        int pos = dp[k][j - 1] + cost(k + 1, i);
        if (pos < res) {
            res = pos;
            p = k;
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
    //debug(j, a, b, x, y, p);

    calc(j, a, z - 1, x, max(p, 0ll));
    calc(j, z + 1, b, max(p, 0ll), y);
}

void run() {
    int n, k;
    read(n, k);
    k = min(n, k);
    int c[n];
    rep(i, 0, n)
        get c[i];

    prefix.pb(c[0]);
    rep(i, 1, n) {
        int val = prefix.back() + c[i];
        prefix.pb(val);
    }

    dp = v<vint>(n, vint(k));
    rep(i, 0, n)
        dp[i][0] = cost(0, i);

    rep(j, 1, k)
        calc(j, 0, n - 1, 0, n - 1);

    put dp[n - 1][k - 1];
}
int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
