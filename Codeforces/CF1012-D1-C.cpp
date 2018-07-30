/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
#define int long long
typedef long double ld;
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
int rem(int whereToBuildHouse, int whatToRemove) {
    return max(whatToRemove - whereToBuildHouse + 1, 0ll);
}
void run() {
    int n;
    read(n);
    if (n == 1) {
        put 0;
        return;
    }
    int k = n / 2 + n % 2;
    int a[n];
    rep(i, 0, n)
        get a[i];

    int dp[n][k + 1];
    rep(i, 0, n)
        rep(j, 0, k + 1)
            dp[i][j] = inf;
    dp[0][0] = 0;
    dp[0][1] = rem(a[0], a[1]);

    int mn[n][k + 1];
    rep(i, 0, n)
        rep(j, 0, k + 1)
            mn[i][j] = dp[i][j];
    rep(i, 1, n) {
        rep(j, 0, k + 1)
            if (j == 0)
                dp[i][j] = 0;
            else if (j == 1) {
              dp[i][j] = rem(a[i], a[i - 1]);
              if (i + 1 < n)
                    dp[i][j] += rem(a[i], a[i + 1]);
            } else {
                if (i >= 2) {
                    int val = dp[i - 2][j - 1];
                    if (i + 1 < n)
                        val += rem(a[i], a[i + 1]);
                    val += rem(a[i], min(a[i - 1], a[i - 2] - 1));

                    dp[i][j] = min(dp[i][j], val);
                }

                if (i >= 3) {
                    int val = mn[i - 3][j - 1];
                    if (i + 1 < n)
                        val += rem(a[i], a[i + 1]);
                    val += rem(a[i], a[i - 1]);
                    dp[i][j] = min(dp[i][j], val);
                }
            }
        rep(j, 0, k + 1) {
            mn[i][j] = min(mn[i - 1][j], dp[i][j]);
        }
    }

    rep(j, 1, k + 1)
        print(mn[n - 1][j]);
    eol;

    //rep(i, 0, n) debug(dp[i][3], dp[i][2]);
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}