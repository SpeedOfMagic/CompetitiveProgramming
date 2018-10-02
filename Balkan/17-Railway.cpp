/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/* Solution
1. For each minister let l = LCA(si[0], si[1], ...). I can split values into routes (si[0], l), (si[1], l), ...
2. So, I want to go reverse dfs, add value when I reach vertices si[0], si[1], ... and remove this value at l.
3. Let vals[i] - initial values which belong to vertex #i. Naive solution would be to add all values from his children
into his own set.
4. To optimize it, I'll keep reference to some other vertex, whose set is initially largest,
then add all elements to that set.
5. Since smaller set merges with greatest, then each element will be transfered no more than log(S) times.
Time complexity: O(n + m + S * log(S)).
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
template<typename T, typename U>  using hmap = __gnu_pbds::gp_hash_table<T, U>;
#define int long long
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
void println(){eol;} template<typename Arg,typename... Args> void println(Arg  arg,Args...  args){put (arg)<<" ";println(args...);}
int getInt(){int a; get a; return a;}
//code goes here
const int N = 1e5 + 1;
v<pair<int, int>> g[N];
int h[N];
const int M = 17;
int kthAncestor[N][M];

void precalc(int cur = 1, int p = -1) {
    if (p == -1) {
        h[cur] = 1;
        rep(i, 0, N)
            rep(j, 0, M)
                kthAncestor[i][j] = -1;
    } else {
        h[cur] = h[p] + 1;
        int c = p, k = 0;
        kthAncestor[cur][0] = p;
        while (kthAncestor[c][k] != -1) {
            c = kthAncestor[c][k];
            k++;
            kthAncestor[cur][k] = c;
        }
    }

    for (auto i : g[cur])
        if (i.fs != p)
            precalc(i.fs, cur);
}

int lca(int v, int u) {
    if (h[v] > h[u])
        swap(v, u);

    for (int k = 0; h[u] - h[v]; k++) {
        //debug(v, u, k, h[v], h[u]);
        if ((h[u] - h[v]) & (1 << k))
            u = kthAncestor[u][k];
    }

    for (int k = M - 1; v != u;)
        if (kthAncestor[v][k] != kthAncestor[u][k] || k == 0) {
            v = kthAncestor[v][k];
            u = kthAncestor[u][k];
        } else
            k--;

    return v;
}

int K;
set<int> vals[N];
vint toRem[N];
int rf[N];
vint ans;

void dfs(int cur, int num = -1, int p = -1) {
    int ind = cur;
    for (pair<int, int> i : g[cur])
        if (i.fs != p) {
            dfs(i.fs, i.sc, cur);
            if (sz(vals[rf[i.fs]]) > sz(vals[rf[ind]]))
                ind = rf[i.fs];
        }

    rf[cur] = ind;
    for (int i : vals[cur])
        vals[ind].insert(i);

    for (pair<int, int> i : g[cur])
        if (rf[i.fs] != ind && i.fs != p)
            for (int j : vals[rf[i.fs]])
                vals[ind].insert(j);

    for (int i : toRem[cur])
        vals[ind].erase(i);

    //print(cur, ":"); for (int i : vals[ind]) print(i);eol;

    if (sz(vals[ind]) >= K && num != -1)
        ans.pb(num);
}

void run() {
    int n, m;
    read(n, m, K);
    rep(i, 1, n) {
        int v, u;
        read(v, u);
        g[v].pb({u, i});
        g[u].pb({v, i});
    }

    precalc();

    rep(i, 0, m) {
        int k;
        get k;
        int l;
        get l;
        vals[l].insert(i);
        rep(j, 1, k) {
            int s;
            get s;
            vals[s].insert(i);
            l = lca(l, s);
        }
        toRem[l].pb(i);
    }

    dfs(1);
    sort(ans.begin(), ans.end());
    put sz(ans), eol;
    for (int i : ans)
        print(i);
}
int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
