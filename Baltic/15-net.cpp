/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Solution:
1. Suppose I add an edge v - u.
Then, I can say that all edges on all paths v - u and v - u edge are not bridges anymore.
2. In other words, I can make another problem statement, which is equal to starting one:
"Tree is given. You may perform operation f(v, u): 'Mark all edges on v - u path'.
You need to find such set of operations that it's minimized and all edges are marked".
3. It's easy to notice that almost all v and u on operations will be leaves.
5. It can be done by dp on trees:
	Suppose that dp[v] - vector of vertices, which are leaves. Let's call those leaves free.
	Obviously, if v is a leaf, then I need to return vector containing this leaf.
4. Then, let's go over all children. To make sure that edge v - father(v) is covered, dp[v] should not be empty.
To make sure that all edges in subtree of v are covered,
all operations should be done by using vertices that are contained in 2 different vectors.
In other words, if u1 and u2 belong to the same vector, then I shouldn't perform f(u1, u2).
5. As a result, size of dp[v] will always be < 3.
6. Suppose v is a root. Then, I want to prove that if size(dp[v]) == 2 and v is not a leaf,
then dp[v][0] and dp[v][1] belong to different vectors.
=> if v is a root and size(dp[v]) == 2, then I need to perform operation f(dp[v][0], dp[v][1]).
8. Special case is if v is a root and size(dp[v]) == 1. Then I want to make that vertex connect to root.
If it's already connected, then I may use any vertex.

Time complexity: O(n).
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
const int N = 500001;
vint g[N];
v<pair<int, int>> ans;
vint dfs(int cur, int p = -1) {
    if (sz(g[cur]) == 1)
        return vint({cur});
    else {
        vint pos;
        for (int i : g[cur]) {
            if (i == p)
                continue;
            vint z = dfs(i, cur);
 
            if (sz(z) == 2 && sz(pos) == 1)
                for (int j : z)
                    if (pos.empty())
                        pos.pb(j);
                    else {
                        ans.pb({pos.back(), j});
                        pos.pop_back();
                    }
            else
                for (int j : z)
                    if (sz(pos) < 2)
                        pos.pb(j);
                    else {
                        ans.pb({pos.back(), j});
                        pos.pop_back();
                    }
        }
 
        if (p == -1) {
            if (sz(pos) == 2)
                ans.pb({pos[0], pos[1]});
            else if (g[pos[0]][0] != cur)
                ans.pb({pos[0], cur});
            else
                rep(i, 1, N)
                    if (pos[0] != i && g[pos[0]][0] != i) {
                        ans.pb({pos[0], i});
                        break;
                    }
        }
 
        return pos;
    }
}
 
void run() {
    int n;
    get n;
    n++;
    rep(i, 2, n) {
        int v, u;
        read(v, u);
        g[v].pb(u);
        g[u].pb(v);
    }
 
    rep(i, 1, n)
        if (sz(g[i]) != 1) {
            dfs(i);
            break;
        }
 
    put sz(ans);
    eol;
    for (auto i : ans)
        debug(i.first, i.second);
}
 
int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}