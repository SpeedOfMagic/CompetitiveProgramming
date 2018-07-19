/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Solution:
I want to make condensation of graph, then bottom is a sink in the condensation.
Condensation can be done by Kosaraju's algorithm.
So, I keep array of sink vertices in condensation
and if some vertex v in original graph belongs to any of those, then I add v to answer.
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
const int N = 1e5 + 1;
vint g[N], rev[N];

stack<int> l;
bool vis[N];
int color[N];
int curColor = 0;
void kosaraju(int cur, bool todo) {
    if (todo) {
        color[cur] = curColor;
        for (int i : rev[cur])
            if (color[i] == 0)
                kosaraju(i, 1);
    } else {
        vis[cur] = 1;
        for (int i : g[cur])
            if (!vis[i])
                kosaraju(i, 0);
        l.push(cur);
    }
}

vint g2[N];
set<int> colorAns;
void dfs(int cur) {
    vis[cur] = 1;
    if (sz(g2[cur]) == 0)
        colorAns.insert(cur);
    for (int i : g2[cur])
        if (!vis[i])
            dfs(i);
}

void run() {
    int n;
    while(get n) {
        if (n == 0)
            break;

        int m;
        get m;
        n++;

        rep(i, 1, n) {
            g[i].clear();
            rev[i].clear();
            g2[i].clear();
            color[i] = 0;
            vis[i] = 0;
            curColor = 0;
            g2[i].clear();
        }
        colorAns.clear();

        rep(i, 0, m) {
            int v, u;
            read(v, u);
            g[v].pb(u);
            rev[u].pb(v);
        }

        rep(i, 1, n) {
            vis[i] = 0;
            color[i] = 0;
        }

        rep(i, 1, n)
            if (!vis[i])
                kosaraju(i, 0);

        while (!l.empty()) {
            int d = l.top();
            l.pop();
            if (color[d] == 0) {
                curColor++;
                kosaraju(d, 1);
            }
        }
        curColor++;

        rep(i, 1, n)
            for (int j : g[i])
                if (color[i] != color[j])
                    g2[color[i]].pb(color[j]);

        rep(i, 1, curColor)
            vis[i] = 0;

        rep(i, 1, curColor)
            if (!vis[i])
                dfs(i);
        rep(i, 1, n)
            if (colorAns.count(color[i]))
                print(i);
        eol;
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
