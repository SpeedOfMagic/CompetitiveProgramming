/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Solution:
This solution heavily relies on CF587-D1-C solution.
It's mostly the same, but instead of keeping set of 10 elements,
it keeps and updates minimum and maximum of encountered edges' weight.
Also, it doesn't check value of lca node, since any of its edges are not included in route.
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
const int N = 1e5 + 1, M = 18;
v<pair<int, int>> g[N];
int kthAncestor[N][M];
int minimum[N][M], maximum[N][M];
int height[N];

void calcHeightsAndLCA(int cur = 1, int pr = -1, int h = 0, int lastEdgeWeight = -1) {
    //debug(cur, pr, h);
    height[cur] = h;

    rep(j, 0, M) {
        kthAncestor[cur][j] = -1;
        minimum[cur][j] = inf;
        maximum[cur][j] = -inf;
    }

    if (pr != -1) {
        kthAncestor[cur][0] = pr;
        int p = pr;
        int k = 0;

        while (kthAncestor[p][k] != -1) {
            kthAncestor[cur][k + 1] = kthAncestor[p][k];
            p = kthAncestor[p][k];
            k++;
        }

        minimum[cur][0] = lastEdgeWeight;
        maximum[cur][0] = lastEdgeWeight;


        k = 1;
        while(kthAncestor[cur][k - 1] != -1) {
            minimum[cur][k] = minimum[cur][k - 1];
            maximum[cur][k] = maximum[cur][k - 1];

            minimum[cur][k] = min(minimum[cur][k], minimum[kthAncestor[cur][k - 1]][k - 1]);
            maximum[cur][k] = max(maximum[cur][k], maximum[kthAncestor[cur][k - 1]][k - 1]);

            k++;
        }
    }



    for (auto i : g[cur])
        if (i.first != pr)
            calcHeightsAndLCA(i.first, cur, h + 1, i.second);
}


void lcaAndSolve(int v, int u) {
    int ansMin = inf, ansMax = -inf;
    if (height[v] > height[u])
        swap(v, u);

    int d = height[u] - height[v];
    int k = 0;
    while(d) {
        if (d & 1) {
            ansMin = min(ansMin, minimum[u][k]);
            ansMax = max(ansMax, maximum[u][k]);
            u = kthAncestor[u][k];
        }

        d >>= 1;
        k++;
    }

    k = M - 1;
    while (v != u)
        if (kthAncestor[v][k] != kthAncestor[u][k] || k == 0) {

            ansMin = min(ansMin, minimum[v][k]);
            ansMax = max(ansMax, maximum[v][k]);

            ansMin = min(ansMin, minimum[u][k]);
            ansMax = max(ansMax, maximum[u][k]);

            v = kthAncestor[v][k];
            u = kthAncestor[u][k];
        } else
            k--;

    print(ansMin, ansMax);
    eol;
}

void run() {
    int n, q;
    read(n);
    n++;

    rep(i, 2, n) {
        int v, u, w;
        read(v, u, w);
        g[v].pb({u, w});
        g[u].pb({v, w});
    }

    calcHeightsAndLCA();

    get q;
    for (; q; q--) {
        int v, u;
        read(v, u);
        lcaAndSolve(v, u);
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
