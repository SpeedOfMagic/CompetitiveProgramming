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
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
int getInt(){int a; get a; return a;}
//code goes here
const int N = 1e6 + 1;
vint g[N];
bool vis[N];
void dfs(int cur) {
    vis[cur] = 1;
    for (int i : g[cur])
        if (!vis[i])
            dfs(i);
}

void run() {
    int n, m;
    read(n, m);
    n++;

    int ans = 0;
    bool hasRoad[n];
    rep(i, 1, n)
        hasRoad[i] = 0;


    int loops = 0;
    rep(i, 0, m) {
        int v, u;
        read(v, u);
        hasRoad[v] = 1;
        hasRoad[u] = 1;
        if (v == u) {
            loops++;
            continue;
        }

        g[v].pb(u);
        g[u].pb(v);
    }

    ans += loops * (m - loops);
    ans += loops * (loops - 1) / 2;

    rep(i, 1, n)
        vis[i] = 0;

    rep(i, 1, n)
        if (hasRoad[i]) {
            dfs(i);
            break;
        }

    rep(i, 1, n)
        if (!vis[i] && hasRoad[i]) {
            put 0;
            return;
        }


    rep(i, 1, n)
        ans += sz(g[i]) * (sz(g[i]) - 1) / 2;

    put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}