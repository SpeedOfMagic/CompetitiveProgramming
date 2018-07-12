/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://codeforces.com/blog/entry/20971
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
const int N = 1e5 + 1, M = 18;
vint g[N];
int kthAncestor[N][M];
priority_queue<int> minimums[N][M];
vint belongsTo[N];
int height[N];

const int A = 10;

void mmerge(priority_queue<int>& mee, priority_queue<int> notHim) {
    while(!notHim.empty()) {
        int d = notHim.top();
        notHim.pop();
        mee.push(d);
        if (sz(mee) > A)
            mee.pop();
    }
}

void calcHeightsAndLCA(int cur = 1, int pr = -1, int h = 0) {
    debug(cur, pr);
    height[cur] = h;

    rep(j, 0, M)
        kthAncestor[cur][j] = -1;
    if (pr != -1) {
        kthAncestor[cur][0] = pr;
        int p = pr;
        int k = 0;

        while (kthAncestor[p][k] != -1) {
            kthAncestor[cur][k + 1] = kthAncestor[p][k];
            p = kthAncestor[p][k];
            k++;
        }
    }

    for (int i : belongsTo[cur]) {
        minimums[cur][0].push(i);
        if (sz(minimums[cur][0]) > A)
            minimums[cur][0].pop();
    }

    
    int k = 1;
    while(kthAncestor[cur][k] != -1) {
        minimums[cur][k] = minimums[cur][k - 1];
        mmerge(minimums[cur][k], minimums[cur + (1 << (k - 1))][k - 1]);
    }

    for (int i : g[cur])
        if (i != pr)
            calcHeightsAndLCA(i, cur, h + 1);
}


priority_queue<int> lcaAndSolve(int v, int u, int a) {
    priority_queue<int> ans;
    if (height[v] > height[u])
        swap(v, u);

    int d = height[u] - height[v];
    int k = 0;
    while(d) {
        if (d & 1) {
            mmerge(ans, minimums[u][k]);
            u = kthAncestor[u][k];
        }

        d >>= 1;
        k++;
    }

    k = M - 1;
    while (v != u)
        if (kthAncestor[v][k] != kthAncestor[u][k] || k == 0) {
            if (kthAncestor[v][k] != kthAncestor[u][k]) {
                mmerge(ans, minimums[v][k]);
                mmerge(ans, minimums[u][k]);
            }

            v = kthAncestor[v][k];
            u = kthAncestor[u][k];
        } else
            k--;

    mmerge(ans, minimums[v][0]);
    while (sz(ans) > a)
        ans.pop();

    return ans;
}

void run() {
    int n, m, q;
    read(n, m, q);
    n++;

    rep(i, 2, n) {
        int v, u;
        read(v, u);
        g[v].pb(u);
        g[u].pb(v);
    }

    rep(i, 0, m) {
        int c;
        get c;
        belongsTo[c].pb(i + 1);
    }

    calcHeightsAndLCA();

    for (; q; q--) {
        int v, u, a;
        read(v, u, a);
        priority_queue<int> ans = lcaAndSolve(v, u, a);
        print(sz(ans));
        vint k;
        while (!ans.empty()) {
            k.pb(ans.top());
            ans.pop();
        }
        for (int i : k)
            print(i);
        eol;
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
