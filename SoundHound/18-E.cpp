/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
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
#define check(a) put #a << ": " << a << endl;
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
int getInt(){int a; get a; return a;}
//code goes here
const int N = 1e5 + 1;
v<vint> g[N];
int l[N], r[N];
int k[N], m[N]; //y = kx + m

int onlyOne = -2;
bool vis[N];
void dfs(int cur = 1, int prev = -1, int prevWeight = 0) {
    if (onlyOne != -2)
        return;

    if (prev == -1) {
        l[cur] = 1;
        r[cur] = 1e9;
        k[cur] = 1;
        m[cur] = 0;
    } else {
        int pk = -k[prev];
        int pm = prevWeight - m[prev];
        if (l[cur] != -1 && (pm != m[cur] || pk != k[cur])) {
            if (pk == k[cur] || (pm - m[cur]) % (k[cur] - pk))
                onlyOne = -1;
            else
                onlyOne = (pm - m[cur]) / (k[cur] - pk);
            return;
        } else if (l[cur] != -1)
            return;
        else {
            k[cur] = pk;
            m[cur] = pm;
            l[cur] = 1;
            r[cur] = 1e9;

            if (m[cur] <= 0 && k[cur] < 0) {
                onlyOne = -1;
                return;
            } else if (m[cur] <= 0 && k[cur] > 0)
                l[cur] = -m[cur] + 1;
            else if (m[cur] > 0 && k[cur] < 0)
                r[cur] = m[cur] - 1;
            else
                r[cur] = prevWeight - m[cur] - 1;
        }
    }

    for (vint i : g[cur])
        if (!vis[i[2]]) {
            vis[i[2]] = 1;
            dfs(i[0], cur, i[1]);
        }
}

int val[N];
bool valid = 1;
void dfs2(int cur = 1, int prev = -1, int prevWeight = 0) {
    vis[cur] = 1;
    if (!valid)
        return;
    if (prev != -1) {
        if (val[cur] != -inf && val[cur] != prevWeight - val[prev]) {
            valid = 0;
            return;
        }
        val[cur] = prevWeight - val[prev];
    }
    if (val[cur] <= 0) {
        valid = 0;
        return;
    }

    for (vint i : g[cur]) {
        if (!vis[i[0]])
            dfs2(i[0], cur, i[1]);
        else {
            if (val[i[0]] + val[cur] != i[1]) {
                valid = 0;
                return;
            }
        }
    }
}

void run() {
    int n, M;
    read(n, M);
    n++;
    rep(i, 0, M) {
        int v, u, s;
        read(v, u, s);
        g[v].pb({u, s, i});
        g[u].pb({v, s, i});
    }
    rep(i, 0, M)
        vis[i] = 0;
    rep(i, 1, n)
        l[i] = -1;
    dfs();

    if (onlyOne == -2) {
        int L = 1, R = 1e9;
        rep(i, 1, n)
            L = max(L, l[i]),
            R = min(R, r[i]);
        if (L > R)
            put 0;
        else
            put R - L + 1;
    } else {
        rep(i, 1, n)
            vis[i] = 0;
        rep(i, 1, n)
            val[i] = -inf;
        val[1] = onlyOne;
        if (onlyOne <= 0)
            put 0;
        else {
            dfs2();
            put valid;
        }
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
