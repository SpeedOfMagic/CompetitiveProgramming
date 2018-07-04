/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/*
Statement:
An isolated directed graph with n (1 <= n <= 2000) vertices is given.
Proccess m (1 <= m <= 2000) queries:
1. v u - add edge v -> u
2. v - find amount of vertices u such that:
	1. there is vertice r such that edges v -> r and edges r -> u exist;
	2. there is no edge v -> u.
	
Solution:
It's easy to notice that u fullfils conditions for v in query #2
if and only if shortest distance from v to u = 2.
Then, this query can be proccessed by simple bfs.

Time complexity: O(nm).
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
#if 1  //FileIO
const string fileName = "enemy";
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
void run() {
    int n, m;
    read(n, m);

    set<int> g[n];

    for (; m; m--) {
        str s;get s;
        if (s == "+") {
            int v, u;
            read(v, u);
            v--; u--;
            g[v].insert(u);
        } else {
            int v; get v;
            v--;

            queue<int> bfs;
            bool vis[n];
            rep(i, 0, n)
                vis[i] = 0;
            vis[v] = 1;
            for (int i : g[v]) {
                bfs.push(i);
                vis[i] = 1;
            }

            int ans = 0;
            while(!bfs.empty()) {
                for (int i : g[bfs.front()]) {
                    if (!vis[i] && !g[v].count(i)) {
                        vis[i] = 1;
                        ans++;
                    }
                }
                bfs.pop();
            }
            put ans;
            eol;
        }
    }
}


int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}