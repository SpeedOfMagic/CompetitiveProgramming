/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/*
Statement:
Rooted tree with n (1 <= n <= 10^5) vertices is given.
Answer m (1 <= m <= 10^7) lca queries (manually generated).

Idea:
It can be done with eulerian traversal array and sparse table for RMQ.
*/
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
const string fileName = "lca_rmq";
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
vint nodeId, height;
vint g[N];

int nodeIndice[N];

void dfs(int cur, int h = 0) {
    for (int i : g[cur]) {
        nodeId.pb(cur);
        height.pb(h);
        dfs(i, h + 1);
    }

    nodeId.pb(cur);
    height.pb(h);
}

void run() {
    int n, q;
    get n;
    get q;

    rep(i, 1, n) {
        int p;
        get p;
        g[p].pb(i);
    }

    dfs(0);

    rep(i, 0, n)
        nodeIndice[i] = -1;

    int m = sz(height);
    rep(i, 0, m)
        if (nodeIndice[nodeId[i]] == -1)
            nodeIndice[nodeId[i]] = i;

    const int M = 20;
    int sparse[m][M];
    rep(i, 0, m) {
        rep(j, 0, M)
            sparse[i][j] = -1;
        sparse[i][0] = i;
    }

    rep(j, 1, M)
        rep(i, 0, m)
            if (i + (1 << j) > m)
                break;
            else {
                int d1 = sparse[i][j - 1], d2 = sparse[i + (1 << (j - 1))][j - 1];
                if (height[d1] > height[d2])
                    swap(d1, d2);
                sparse[i][j] = d1;
            }

    int nearestPow2[m + 1];
    int p = 0;
    rep(i, 1, m + 1) {
        if ((1 << (p + 1)) == i)
            p++;

        nearestPow2[i] = p;
    }

    int a1, a2;
    int x, y, z;
    read(a1, a2, x, y, z);
    int s = 0;
    int v = 0;
    for (; q; q--) {
        int w = (a1 + v) % n, u = a2;

        int l = nodeIndice[w], r = nodeIndice[u];
        if (l > r)
            swap(l, r);

        int k = nearestPow2[r - l + 1];
        int pos1 = sparse[l][k], pos2 = sparse[r - (1 << k) + 1][k];
        if (height[pos1] > height[pos2])
            swap(pos1, pos2);

        v = nodeId[pos1];
        s += v;

        int a3 = (x * a1 + y * a2 + z) % n;
        int a4 = (x * a2 + y * a3 + z) % n;
        a1 = a3;
        a2 = a4;
    }

    put s;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
