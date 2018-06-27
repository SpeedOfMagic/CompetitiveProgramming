/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
#include <bits/stdc++.h>
using namespace std;
template<typename T> using v = vector<T>;
#define int long long
typedef string str;
typedef vector<int> vint;
#define rep(a,l,r) for(int a = (l); a < (r); a++)
#define pb push_back
#define sz(a) ((int) a.size())
const int inf = 4611686018427387903; //2^62 - 1
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
int dp[N];
int sum[N];
int maxHas[N];
int submaxHas[N];
int a[N];
vint g[N];

int ans = -inf;

int dfs1(int cur, int p = -1) {
    sum[cur] = a[cur];

    for (int i : g[cur]) {
        if (i == p)
            continue;

        sum[cur] += dfs1(i, cur);
    }
    return sum[cur];
}

void dfs2(int cur, int p = -1) {
    vint possibleMax;

    if(sz(g[cur]) == 0ll || (sz(g[cur]) == 1ll && g[cur][0] == p)) {
        maxHas[cur] = a[cur];
        return;
    }

    possibleMax.pb(-inf);
    for (int i : g[cur]) {
        if (i == p)
            continue;

        dfs2(i, cur);
        possibleMax.pb(max(maxHas[i], sum[i]));
    }

    sort(possibleMax.begin(), possibleMax.end());

    maxHas[cur] = possibleMax.back();

    if (possibleMax.back() == -inf || possibleMax[sz(possibleMax) - 2] == -inf)
        return;
    ans = max(ans, possibleMax.back() + possibleMax[sz(possibleMax) - 2]);
}

void run() {
    int n;
    get n;
    n++;

    rep(i, 1, n)
        get a[i];

    rep(i, 2, n) {
        int v, u;
        read(v, u);
        g[v].pb(u);
        g[u].pb(v);
    }

    dfs1(1);
    dfs2(1);

    if (ans == -inf)
        put "Impossible";
    else
        put ans;
}
int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}
