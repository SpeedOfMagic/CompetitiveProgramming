/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://codeforces.com/blog/entry/59350
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
//#define int long long
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
const int N = 1e6 + 1;

vector<int> g[N]; //init me
int height[N];
int parent[N];

const int M = 20;
int kthAncestor[N][M];

void precalc(int cur, int h = 0, int p = -1) {
    height[cur] = h;
    parent[cur] = p;

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

bool included[N];

void run() {
    int n, kk;
    read(n, kk);
    n++;

    rep(i, 2, n) {
        int v, u;
        read(v, u);
        g[v].pb(u);
        g[u].pb(v);
    }

    precalc(n - 1);

    rep(i, 1, n)
        included[i] = 0;
    included[n - 1] = 1;

    int leftToAdd = n - 2 - kk;
    set<int> ans;

    for (int i = n - 2; i; i--) {
        if (included[i])
            continue;

        int k = M - 1;
        int p = i;
        while (k >= 0) {
            if (kthAncestor[p][k] != -1 && !included[kthAncestor[p][k]]) {
                p = kthAncestor[p][k];
            } else
                k--;
        }

        int nearestIncludedAncestor = kthAncestor[p][0];

        int distance = height[i] - height[nearestIncludedAncestor];
        //debug(i, nearestIncludedAncestor, distance);

        if (distance > leftToAdd)
            ans.insert(i);
        else {
            leftToAdd -= height[i] - height[nearestIncludedAncestor];
            p = i;
            while (!included[p]) {
                included[p] = 1;
                p = parent[p];
            }
        }
    }

    for (int i : ans)
        print(i);
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}