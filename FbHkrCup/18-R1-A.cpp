/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: https://www.facebook.com/notes/facebook-hacker-cup/hacker-cup-2018-round-1-solutions/2267977239884831/
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
const int mod = 1e9 + 7;
void run() {
    int t;
    get t;
    for (int test = 1; test <= t; test++) {
        int n;
        get n;
        int dp[n][3][4];
        rep(i, 0, n)
            rep(j, 0, 3)
                rep(k, 0, 4)
                    dp[i][j][k] = 0;
        str a[3];
        read(a[0], a[1], a[2]);

        /**
        0 - >V
            .V

        1 - .^
            >^

        2 - V.
            >>

        3 - >>
            ^.
        **/

        dp[0][0][0] = (a[0][0] == '.') * 1;
        dp[0][1][2] = (a[1][0] == '.') * dp[0][0][0];
        rep(i, 1, n) {
            dp[i][1][0] = (a[1][i] == '.') * ((dp[i - 1][1][3] + dp[i - 1][1][2]) % mod);
            dp[i][1][1] = (a[1][i] == '.') * ((dp[i - 1][1][3] + dp[i - 1][1][2]) % mod);

            dp[i][0][0] = (a[0][i] == '.') * dp[i - 1][0][3];
            dp[i][0][3] = (a[0][i] == '.') * dp[i][1][1];

            dp[i][2][1] = (a[2][i] == '.') * dp[i - 1][2][2];
            dp[i][2][2] = (a[2][i] == '.') * dp[i][1][0];

            dp[i][1][2] = (a[1][i] == '.') * dp[i][0][0];
            dp[i][1][3] = (a[1][i] == '.') * dp[i][2][1];
        }

        put "Case #" << test << ": " << dp[n - 1][2][2] << endl;
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
