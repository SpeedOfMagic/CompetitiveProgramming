/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://codeforces.com/blog/entry/13758
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
const int N = 1e5 + 1;

vector<int> g[N]; //init me
int height[N];

const int M = 20;
int kthAncestor[N][M];

void precalc(int cur, int h = 0, int p = -1) {
    height[cur] = h;

    for (int j = 0; j < M; j++)
        kthAncestor[cur][j] = -1;
    if (p != -1) {
        kthAncestor[cur][0] = p;
        int pos = p;
        int k = 0;
        while (kthAncestor[pos][k] != -1) {
            kthAncestor[cur][k + 1] = kthAncestor[pos][k];
            pos = kthAncestor[pos][k];
            k++;
        }
    }

    for (int i : g[cur])
        if (i != p)
            precalc(i, h + 1, cur);
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



struct dsu {
    vector<int> repr;
    vector<int> siz;

    int fin(int a) {
        if (repr[a] == a)
            return a;
        else
            return repr[a] = fin(repr[a]);
    }

    void unite(int a, int b) {
        a = fin(a);
        b = fin(b);

        if (siz[a] > siz[b])
            swap(a, b);

        repr[a] = b;

        siz[b] += siz[a];
    }

    bool connected(int a, int b) {
        return fin(a) == fin(b);
    }

    dsu(int n) {
        for(int i = 0; i < n; i++) {
            repr.push_back(i);
            siz.push_back(1);
        }
    }
};

void run() {
    int n, m;
    get n;
    get m;
    n++;

    vint queries[m];
    v<vint> documentsToAnswer;
    documentsToAnswer.pb(vint());

    map<int, str> ans;

    bool roots[n];
    rep(i, 1, n)
        roots[i] = 1;

    rep(i, 0, m) {
        int t;
        get t;
        if (t == 1) {
            int x, y;
            read(x, y);
            queries[i] = vint({t, x, y});
            g[x].pb(y);
            g[y].pb(x);
            roots[x] = 0;
        } else if (t == 2) {
            int x;
            get x;
            queries[i] = vint({t, x});
            documentsToAnswer.pb(vint());

        } else {
            int x, j;
            read(x, j);
            queries[i] = vint({t, x, j});
            documentsToAnswer[j].pb(i);
        }
    }

    rep(i, 1, n)
        if (roots[i])
            precalc(i);

    dsu d = dsu(n);
    int p = 1;
    rep(q, 0, m)
        if (queries[q][0] == 1)
            d.unite(queries[q][1], queries[q][2]);
        else if (queries[q][0] == 2) {
            int y = queries[q][1];
            for (int j : documentsToAnswer[p]) {
                int x = queries[j][1];
                if (d.connected(x, y)) {
                    if (lca(x, y) == x)
                        ans[j] = "YES";
                    else
                        ans[j] = "NO";
                } else
                    ans[j] = "NO";
            }
            p++;
        }

    for (auto i : ans)
        put i.second << endl;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}