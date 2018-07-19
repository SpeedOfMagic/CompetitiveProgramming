/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Solution:
Let's make a oriented graph, where v -> u means u has preference over v.
Then, contradiction arises if and only if there is cycle in graph.
So, the answer is: cycles in condensated graph.
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

void run() {
    int m;
    bool z = 0;
    while(get m) {
        if (m == 0)
            break;
        if (z)
            eol;
        else
            z = 1;

        const int n = 26;

        bool exists[n];
        rep(i, 0, n)
            exists[i] = 0;

        rep(i, 0, n) {
            g[i].clear();
            rev[i].clear();
            g2[i].clear();
            color[i] = 0;
            vis[i] = 0;
            curColor = 0;
        }

        rep(i, 0, m) {
            int d[5];
            rep(j, 0, 5) {
                str s;
                get s;
                d[j] = s[0] - 'A';
                exists[d[j]] = 1;
            }

            str s;
            get s;
            int r = s[0] - 'A';
            rep(j, 0, 5)
                if (d[j] != r) {
                    g[d[j]].pb(r);
                    rev[r].pb(d[j]);
                }
        }

        rep(i, 0, n) {
            vis[i] = 0;
            color[i] = 0;
        }

        rep(i, 0, n)
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

        rep(i, 0, n)
            for (int j : g[i])
                if (color[i] != color[j])
                    g2[color[i]].pb(color[j]);

        vint ans[curColor];
        rep(i, 0, n)
            if (exists[i])
                ans[color[i]].pb(i);

        sort(ans, ans + curColor);
        for (vint i : ans) {
            if (i.empty())
                continue;
            for(int j : i)
                if (j != i.back())
                    print(char(j + 'A'));
                else
                    put char(j + 'A');
            eol;
        }
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
