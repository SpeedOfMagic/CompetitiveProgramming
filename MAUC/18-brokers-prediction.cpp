/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
template<typename T, typename U>  using hmap = __gnu_pbds::gp_hash_table<T, U>;
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
#define check(a) put #a << ": " << a << endl;
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
int getInt(){int a; get a; return a;}
//code goes here
struct dsu {
    vector<int> repr;
    vector<int> siz;

    int _find(int a) {
        if (repr[a] == a)
            return a;
        else
            return _find(repr[a]);
    }

    pair<int, int> unite(int a, int b) {
        if (connected(a, b))
            return {-1, -1};

        a = _find(a);
        b = _find(b);

        if (siz[a] > siz[b])
            swap(a, b);

        repr[a] = b;

        siz[b] += siz[a];
        return {a, b};
    }

    bool connected(int a, int b) {
        return _find(a) == _find(b);
    }

    dsu(int n) {
        for(int i = 0; i < n; i++) {
            repr.push_back(i);
            siz.push_back(1);
        }
    }

    dsu() {}

    void revoke(int a, int b) { //a -> b
        repr[a] = a;
        siz[b] -= siz[a];
    }
};

dsu man;
const int N = 4e5 + 1;
int powOf2[N];

int solve(vint query) {
    set<int> ans;
    rep(i, 0, sz(query))
        ans.insert(man._find(query[i]));

    return powOf2[sz(ans)];
}

vint g[N];

pair<int, int> toUnite[N];
v<pair<int, vint>> queries[N];
int ans[N];
inline void dfs(int cur) {
    pair<int, int> val = {-1, -1};
    if (cur)
        val = man.unite(toUnite[cur].fs, toUnite[cur].sc);
    for (int i : g[cur])
        dfs(i);

    for(auto i : queries[cur])
        ans[i.fs] = solve(i.sc);

    if (val.fs != -1)
        man.revoke(val.fs, val.sc);
}

void run() {
    //read: +0 min
    //think: +15 min
    //code: +15 min
    //debug: +1 min
    //start: 55 min
    const int mod = 1e9 + 7;
    int n, q;
    read(n, q);
    man = dsu(n + 1);
    powOf2[0] = 1;
    rep(i, 1, n + 1)
        powOf2[i] = (powOf2[i - 1] * 2) % mod;

    int tot = 0;

    rep(t, 0, q) {
        int type;
        get type;
        if (type == 1) {
            int p = t, si = t + 1, sj = t + 2;
            read(p, si, sj);
            g[p].pb(t + 1);
            toUnite[t + 1] = {si, sj};
        } else {
            int p, k;
            read(p, k);
            vint a(k);
            rep(i, 0, k)
                get a[i];
            queries[p].pb({tot++, a});
        }
    }
//
    dfs(0);

    rep(i, 0, tot)
        put ans[i] << endl;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
