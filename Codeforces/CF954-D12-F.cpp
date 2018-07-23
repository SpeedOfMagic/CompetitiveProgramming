/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: https://codeforces.com/blog/entry/58519
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

    v<vint> res(n, vint(m));

    rep(i, 0, n)
        rep(j, 0, m) {
            res[i][j] = 0;
            rep(l, 0, k)
                res[i][j] = (res[i][j] + (a[i][l] * b[l][j]) % mod) % mod;
        }

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
        b = mul(b, b);
        return b;
    }
}

v<vint> makeMatrix(int mask) {
    v<vint> res;
    res.pb({!!(mask & 4), !!(mask & 4), 0});
    res.pb({!!(mask & 2), !!(mask & 2), !!(mask & 2)});
    res.pb({0, !!(mask & 1), !!(mask & 1)});
    return res;
}

void run() {
    int n, m;
    read(n, m);

    v<vint> event;
    rep(i, 0, n) {
        int a, l, r;
        read(a, l, r);
        event.pb({l, 1, a});
        event.pb({r + 1, -1, a});
    }
    event.pb({m, 0, 2});

    sort(event.begin(), event.end());

    v<vint> cur;
    cur.pb({0});
    cur.pb({1});
    cur.pb({0});

    int curX = 1;
    
    int up = 0, mid = 0, down = 0;
    for (int p = 0; p < sz(event);) {
        int d = event[p][0] - curX - 1;
        int mask = (!up) * 4 + (!mid) * 2 + !down;
        cur = mul(pow(makeMatrix(mask), d), cur);
        //debug(cur[0][0], cur[1][0], cur[2][0], curX, event[p][0], mask);
        
        curX = event[p][0];
        while (p < sz(event) && event[p][0] == curX) {
            int a = event[p][2];
            if (a == 1)
                up += event[p][1];
            else if (a == 2)
                mid += event[p][1];
            else
                down += event[p][1];

            p++;
        }
        
        mask = (!up) * 4 + (!mid) * 2 + !down;
        cur = mul(makeMatrix(mask), cur);
    }

    put cur[1][0];
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}