/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://codeforces.com/blog/entry/60511
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
const int N = 2e5 + 1;
    int n, m;

v<vint> pos;


int k;

void run() {
    read(n, m, k);

    v<pair<int, int>> g[++n];
    rep(i, 0, m) {
        int v, u;
        read(v, u);
        g[v].pb({u, i});
        g[u].pb({v, i});
    }
    bool vis[n];
    rep(i, 1, n)
        vis[i] = 0;
    vis[1] = 1;

    queue<int> bfs;
    bfs.push(1);

    queue<pair<int, int>> posEdgesTo;


    vint posEdges[n];

    int leftToVisit = n - 2;
    while(1) {
        set<int> willBeVisited;
        queue<int> nxt;
        while(!bfs.empty()) {
            int cur = bfs.front();
            bfs.pop();

            for (pair<int, int> z : g[cur]) {
                int i = z.first;

                if (willBeVisited.count(i))
                    posEdgesTo.push(z);

                if (vis[i])
                    continue;
                vis[i] = 1;

                willBeVisited.insert(i);

                nxt.push(i);

                posEdgesTo.push(z);

                leftToVisit--;

            }
        }
        bfs = nxt;
        //debug(sz(posEdgesTo));
        if (leftToVisit == 0) {
            while(!posEdgesTo.empty()) {
                int i = posEdgesTo.front().first;
                int d = posEdgesTo.front().second;
                posEdges[i].pb(d);
                posEdgesTo.pop();
            }
            int tot = 1;

            rep(i, 1, n)
                if (posEdges[i].empty())
                    continue;
                else
                    pos.pb(posEdges[i]);

            for (vint i : pos)
                tot = min(sz(i) * tot , k);

            put tot;
            eol;

            n = sz(pos);
            int po[n];
            rep(i, 0, n)
                po[i] = 0;

            rep(i, 0, tot) {
                v<bool> paaa = v<bool>(m, 0);
                rep(j, 0, n)
                    paaa[pos[j][po[j]]] = 1;

                for (bool j : paaa)
                    put j;
                eol;

                for (int j = n-1; j>=0;j--) {
                    po[j]++;
                    if (po[j] != sz(pos[j]))
                        break;
                    else
                        po[j] = 0;
                }
            }

            return;
        } else {
            while(!posEdgesTo.empty()) {
                int i = posEdgesTo.front().first;
                int d = posEdgesTo.front().second;
                posEdges[i].pb(d);
                posEdgesTo.pop();
            }
        }
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}