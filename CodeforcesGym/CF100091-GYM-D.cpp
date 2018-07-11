/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Statement:
Graph with n vertices and m edges is given (1 <= n, m <= 10^5). Also, a number f is given (1 <= f <= n).
Proccess k (1 <= k <= 10^5) queries:
	Two vertices v and u (1 <= v, u <= n) are given.
	Find such route from v -> f and such route from u -> f, that those routes have minimum amount of common edges.
	Print minimum amount of common edges.
	
Solution:
1. Note that if for 2 vertices v and u if there is cycle that contains both of them,
then there are 2 different routes v -> u that doesn't have common edges.

2. Then, I can say that if there is cycle that contains both v and u, then,
if they'll 'merge' together into 1 vertice, result won't change.

3. In other words, condensation of this graph doesn't change result.

4. So, I condensate this graph and now have the same problem, but with tree.
5. I declare f as a root of tree.
6. Notice that there is only one route to f (because of tree property), and two routes to f intersect at lca(v, u).
7. => answer to each query is height[lca(v, u)].

Time complexity: O(n * log n + m).
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
#if 1 //FileIO
const string fileName = "magic";
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
const int N = 1e5 + 1;
vector<int> g[N]; //init me

set<int> g2Rev[N];
bool vis[N];
int col[N];
stack<int> l;
int color = 0;

void korasajuLike(int cur, bool todo) {
    if(todo){
        col[cur] = color;
        for(int i : g2Rev[cur])
            if(col[i] == 0)
                korasajuLike(i, todo);
    } else {
        vis[cur] = 1;
        for (int i : g[cur]) {
            if(!g2Rev[cur].count(i))
                g2Rev[i].insert(cur);

            if(!vis[i])
                korasajuLike(i, todo);
        }
        l.push(cur);
    }

}

vint condensation[N];

void makeCondensation(v<pair<int, int>> E) { //E - edges of a graph
    for (int i = 0; i < N; i++) {
        vis[i] = 0;
        col[i] = 0;
    }

    korasajuLike(1, 0);

    while(!l.empty()) {
        if(col[l.top()] == 0) {
            color++;
            korasajuLike(l.top(), 1);
        }

        l.pop();
    }

    for (auto edge : E) {
        int i = edge.first, j = edge.second;
        if(col[i] == col[j])
            continue;

        condensation[col[i]].push_back(col[j]);
        condensation[col[j]].push_back(col[i]);
    }
}

int height[N];

const int M = 20;
int kthAncestor[N][M];

void calcHeights(int cur, int h = 0, int p = -1) {
    vis[cur] = 1;
    height[cur] = h;

    if (p != -1) {
        rep(j, 0, M)
            kthAncestor[cur][j] = -1;
        
        kthAncestor[cur][0] = p;
        int pos = p;
        int k = 0;
        while (kthAncestor[pos][k] != -1) {
            kthAncestor[cur][k + 1] = kthAncestor[pos][k];
            pos = kthAncestor[pos][k];
            k++;
        }
    }

    for (int i : condensation[cur])
        if (!vis[i])
            calcHeights(i, h + 1, cur);
}

int lca(int v, int u) {
    if (height[v] > height[u])
        swap(v, u);
    int d = height[u] - height[v];
    int k = 0;
    while (d) {
        if (d & 1)
            u = kthAncestor[u][k];
        d >>= 1;
        k++;
    }

    k = M - 1;

    while (v != u)
        if (kthAncestor[v][k] != kthAncestor[u][k] || k == 0) {
            v = kthAncestor[v][k];
            u = kthAncestor[u][k];
        } else
            k--;

    return v;
}

void run() {
    int n, m, f;
    read(n, m, f);
    n++;

    v<pair<int, int>> E;
    rep(i, 0, m) {
        int a, b;
        read(a, b);
        E.pb({a, b});
        g[a].pb(b);
        g[b].pb(a);
    }

    makeCondensation(E);

    f = col[f];
    rep(i, 0, M)
        kthAncestor[f][i] = -1;
    rep(i, 1, n)
        vis[i] = 0;
    calcHeights(f);

    int k;
    get k;
    for (; k; k--) {
        int v, u;
        read(v, u);
        v = col[v];
        u = col[u];
        
        int t = lca(v, u);
        put height[t];
        eol;
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}