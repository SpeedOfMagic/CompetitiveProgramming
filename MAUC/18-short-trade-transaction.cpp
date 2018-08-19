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
const int M = 110;
const int A = 111;
int dp[M][A][A];
int pref[M][A][A];

int solve(int a, int m) {
    memset(&dp[0][0][0], 0, sizeof(dp));
    memset(&pref[0][0][0], 0, sizeof(pref));
    //dp[i][j][k] - i-th guy, you currently have j shares, and you got k shares from that guy.
    rep(j, 0, a + 1)
        dp[0][j][j] = 1;
    rep(i, 0, a + 1)
        rep(j, 0, a + 1) {
            pref[0][i][j] += dp[0][i][j];
            if (j)
                pref[0][i][j] += pref[0][i][j - 1];
        }
    /**
    1 2

    dp[0][0][0] dp[0][0][1]
    dp[0][1][0] dp[0][1][1]

    dp[1][0][0] dp[1][0][1]
    dp[1][1][0] dp[1][1][1]

    1 0
    0 1

    1 0
    1 1
    **/

    rep(i, 1, m)
        rep(j, 0, a + 1) {
            rep(k, 0, a + 1) {
                if (j < k)
                    break;
                dp[i][j][k] += pref[i - 1][j - k][a] - pref[i - 1][j - k][k] + int32_t(k == 0) * dp[i - 1][j - k][0];
            }
            rep(k, 0, a + 1) {
                pref[i][j][k] += dp[i][j][k];
                if (k)
                    pref[i][j][k] += pref[i][j][k - 1];
            }
        }

    /**
    rep(k, 0, m) {
        rep(i, 0, a + 1) {
            rep(j, 0, a + 1)
                print(dp[k][i][j]);
            eol;
        }
        eol;
    }
    **/
    int ans = 0;
    rep(i, 0, a + 1)
        ans += dp[m - 1][a][i];
    return ans;
}

void run() {
    //think: 0 min
    //code: 3 min
    //debug: 23 min
    //start: 36 min
    int q;
    get q;
    while (q --> 0) {
        int a, m;
        read(a, m);
        if (a == 0) {
            put 1;
            eol;
        } else {
            put solve(a, m);
            eol;
        }
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
