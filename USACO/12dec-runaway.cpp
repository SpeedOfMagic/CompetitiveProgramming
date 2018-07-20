/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://usaco.org/current/data/sol_runaway.html
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
const string fileName = "runaway";
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
v<pair<int, int>> g[N];

vint penOnPath, ind;

int d;

int queriesBeginAmount[N];
int queriesEndAmount[N];
int ans[N];

void makeQueries(int cur = 1, int penalty = 0) {
    penOnPath.pb(penalty);
    ind.pb(cur);

    int from = lower_bound(penOnPath.begin(), penOnPath.end(), penalty - d) - penOnPath.begin();
    queriesBeginAmount[cur]++;
    queriesEndAmount[ind[from]]++;
    //debug(cur, ind[from]);

    for (auto i : g[cur])
        makeQueries(i.first, penalty + i.second);

    penOnPath.pop_back();
    ind.pop_back();
}

int processQueries(int cur = 1) {
    int curAmount = 0;
    for (pair<int, int> i : g[cur])
        curAmount += processQueries(i.first);

    curAmount += queriesBeginAmount[cur];
    ans[cur] = curAmount;
    curAmount -= queriesEndAmount[cur];
    return curAmount;
}

void run() {
    int n;
    read(n, d);
    n++;

    rep(i, 2, n) {
        int p, l;
        read(p, l);
        g[p].pb({i, l});
    }

    rep(i, 1, n) {
        queriesBeginAmount[i] = 0;
        queriesEndAmount[i] = 0;
        ans[i] = 0;
    }

    makeQueries();
    processQueries();
    rep(i, 1, n)
        put ans[i] << endl;
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}
