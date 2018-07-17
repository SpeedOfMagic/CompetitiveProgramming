/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Solution:
1. Since only maximum danger matters, there may be some edges that optimal answer for each query will never use.
So, I can remove those edges.
2. Obviously, edges that optimal answer will never use are the one who have maximum weight,
and they are not bridges.
3. So, I want to iteratively remove edges, starting from maximum,
and if this edge is not a bridge in current graph, then I can safely remove it.
4. Also I want to prove that if I'll do that, then:
	1. There will be a tree.
	2. Sum of those edges' weight is minimum.
5. If I'll prove 4., then I can say that result will be MST. => MST of this graph doesn't change answer to queries.
6. Since I have a tree instead of normal graph now, problem becomes similiar to SPOJ DISQUERY.
**/
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
const int N = 5e4 + 1;
const int M = 20;
v<pair<int, int>> g[N];
int kthAncestor[N][M];
int height[N];
int danger[N][M];

void precalc(int cur, int pr = -1, int h = 0, int prevWeight = -1) {
    height[cur] = h;
    rep(i, 0, M) {
        kthAncestor[cur][i] = -1;
        danger[cur][i] = inf;
    }

    if (pr != -1) {
        kthAncestor[cur][0] = pr;
        danger[cur][0] = prevWeight;

        int p = pr;
        int k = 0;

        while (kthAncestor[p][k] != -1) {
            danger[cur][k + 1] = max(danger[cur][k], danger[p][k]);
            kthAncestor[cur][k + 1] = kthAncestor[p][k];
            p = kthAncestor[p][k];
            k++;
        }
    }

    for (auto i : g[cur])
        if (i.first != pr)
            precalc(i.first, cur, h + 1, i.second);
}

int lcaAndSolve(int v, int u) {
    if (height[v] > height[u])
        swap(v, u);
    int d = height[u] - height[v];

    int ans = 0;
    int k = 0;
    while (d) {
        if (d & 1) {
            ans = max(ans, danger[u][k]);
            u = kthAncestor[u][k];
        }
        k++;
        d >>= 1;
    }

    k = M - 1;
    while (v != u) {
        if (kthAncestor[v][k] != kthAncestor[u][k] || k == 0) {
            ans = max(ans, max(danger[v][k], danger[u][k]));
            v = kthAncestor[v][k];
            u = kthAncestor[u][k];
        } else
            k--;
    }

    return ans;
}

int repr[N], siz[N];

int _find(int a) {
    if (repr[a] == a)
        return a;
    else
        return repr[a] = _find(repr[a]);
}

bool connected(int a, int b) {
    return _find(a) == _find(b);
}

void unite(int a, int b) {
    if (connected(a, b))
        return;
    a = _find(a);
    b = _find(b);
    if (siz[a] > siz[b])
        swap(a, b);
    repr[a] = b;
    siz[b] += siz[a];
}

void run() {
    int n, m;
    bool zzz = 0;
    while (get n) {
        if (zzz)
            put '\n';
        zzz = 1;
        get m;
        n++;
        rep(i, 1, n) {
            repr[i] = i;
            siz[i] = 1;
        }

        rep(i, 1, n) {
            height[i] = -1;
            g[i].clear();
            rep(j, 0, M) {
                kthAncestor[i][j] = -1;
                danger[i][j] = -1;
            }
        }

        vint edg[m];
        rep(i, 0, m) {
            int v, u, w;
            read(v, u, w);
            edg[i] = {w, v, u};
        }

        sort(edg, edg + m);

        rep(i, 0, m)
            if (!connected(edg[i][1], edg[i][2])) {
                unite(edg[i][1], edg[i][2]);
                g[edg[i][1]].pb({edg[i][2], edg[i][0]});
                g[edg[i][2]].pb({edg[i][1], edg[i][0]});
            }

        rep(i, 1, n)
            height[i] = -1;

        rep(i, 1, n)
            if (height[i] == -1)
                precalc(i);

        int q;
        get q;
        for (; q; q--) {
            int v, u;
            read(v, u);
            int ans = lcaAndSolve(v, u);
            put ans;
            put '\n';
        }
    }
}
int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
