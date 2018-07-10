/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://codeforces.com/blog/entry/60511
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

void run() {
    str s;
    get s;
    int n = sz(s);

    int dp[n][3];
    rep(j, 0, 3)
        dp[0][j] = -inf;

    dp[0][(s[0] - '0') % 3] = 0;

    rep(i, 1, n) {
        int rem = (s[i] - '0') % 3;
        rep(j, 0, 3)
            dp[i][j] = -inf;

        dp[i][rem] = max(max(dp[i - 1][0] + 1, dp[i - 1][1]), dp[i - 1][2]);
        rep(j, 0, 3)
            dp[i][(rem + j) % 3] = max(dp[i][(rem + j) % 3], dp[i - 1][j]);
    }

    dp[n - 1][0]++;
    put max(max(dp[n - 1][0], dp[n - 1][1]), dp[n - 1][2]);
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}