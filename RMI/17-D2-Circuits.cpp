/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
template<typename T, typename U>  using hmap = __gnu_pbds::gp_hash_table<T, U>;
#define int long long
typedef long double ld;
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define fs first
#define sc second
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
#define check(a) put #a << ": " << a << endl;
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
int getInt(){int a; get a; return a;}
//code goes here

void run() {
    int n, m, k;
    read(n, m, k);

    char g[n][n];
    memset(g, 0, sizeof(g));
    rep(i, 0, m) {
        int v, u;
        read(v, u);
        g[--v][--u] = 1;
    }

    int dp[n][(1 << n)];
    memset(&dp, 0, sizeof(dp));
    //dp[i][mask] - amount of circuits going out of that city; i: i-th city; mask: visited cities including that one;

    dp[0][(1 << n) - 1] = 1;
    for (int mask = (1 << n) - 1; mask >= 0; mask--)
        rep(i, 0, n)
            if ((mask & (1 << i)) || (i == 0 && mask == 0))
                rep(j, 0, n)
                    if (!(mask & (1 << j)) && g[i][j]) {
                        dp[i][mask] += dp[j][mask | (1 << j)];
                    }
                    
    if (dp[0][0] < k) {
        put 0;
        return;
    }
    int cur = 0;
    int mask = 0;
    rep(i, 0, n) {
        print(cur + 1);
        rep(j, 0, n)
            if (g[cur][j] && (mask & (1 << j)) == 0) {
                if (dp[j][mask | (1 << j)] >= k) {
                    mask |= (1 << j);
                    cur = j;
                    break;
                } else
                    k -= dp[j][mask | (1 << j)];
            }
    }
    put 1;
}
int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
