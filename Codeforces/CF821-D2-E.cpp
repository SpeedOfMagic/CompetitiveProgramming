/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://codeforces.com/blog/entry/52895
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
#define int long long
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
const int mod = 1e9 + 7;
v<vint> mul(v<vint> a, v<vint> b) {
    int n = sz(a), m = sz(b[0]), k = sz(b);
    v<vint> res(n, vint(m, 0));
    rep(i, 0, n)
        rep(j, 0, m)
            rep(l, 0, k)
                res[i][j] = (res[i][j] + (a[i][l] * b[l][j]) % mod) % mod;

    return res;
}

v<vint> makeIdMatrix(int n) {
    v<vint> res(n, vint(n));
    rep(i, 0, n)
        rep(j, 0, n)
            res[i][j] = (i == j);
    return res;
}

v<vint> pow(v<vint> a, int k) {
    if (k == 0)
        return makeIdMatrix(sz(a));
    else if (k % 2)
        return mul(a, pow(a, k - 1));
    else {
        v<vint> b = pow(a, k / 2);
        return mul(b, b);
    }
}

const int MAX = 16;

v<vint> makeMatrix(int lim) {
    v<vint> res(MAX, vint(MAX, 0));
    rep(i, 0, lim + 1) {
        res[i][i] = 1;
        if (i)
            res[i][i - 1] = 1;
        if (i + 1 < MAX)
            res[i][i + 1] = 1;
    }

    return res;
}

void run() {
    int n, k;
    read(n, k);

    v<vint> cur(MAX, vint(1, 0));
    cur[0][0] = 1;
    int pc = -1;
    rep(i, 0, n) {
        int a, b, c;
        read(a, b, c);

        if (pc != -1)
            cur = mul(makeMatrix(min(c, pc)), cur);

        int d = min(b, k) - a;
        if (d == 0) {
            put cur[0][0];
            return;
        }

        cur = mul(pow(makeMatrix(c), d - 1), cur);
        pc = c;
    }

    cur = mul(makeMatrix(pc), cur);

    put cur[0][0];
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}